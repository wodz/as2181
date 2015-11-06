/*
 *		ADSP EZ-Kit Communicator
 *
 *		(c) 1996 Martin Mares, <mj@k332.feld.cvut.cz>
 *
 *		This software may be freely distributed and used according to the terms
 *		of the GNU General Public License. See file COPYING in any of the GNU utilities.
 */

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <termios.h>
#include <signal.h>
#include <unistd.h>

#include "glob.h"

static char *name = "/dev/adsp";
static int fd;

static void cerr(char *, char *) NONRET;
static void perr(char *, char *) NONRET;

static struct termios tios = {
	IGNBRK | IGNPAR,
	0,
	CS8 | CREAD | CLOCAL | B9600,
	0,
	0,
	{ 0, 0, 0, 0, 0, 5, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
	};

static void
cerr(char *err, char *par)
{
	fputs("adspc: ", stderr);
	fprintf(stderr, err, par);
	fputc('\n', stderr);
	exit(1);
}

static void
perr(char *err, char *par)
{
	char x[256];
	sprintf(x, err, par);
	perror(x);
	exit(1);
}

static void
sig(int unused)
{
	cerr("Timed out", NULL);
}

static char outbuf[256];
static char *outbuf_curr = outbuf;
static char *outbuf_end = outbuf + sizeof(outbuf);

static void
cflush(void)
{
	if (outbuf_curr != outbuf)
		{
			if (write(fd, outbuf, outbuf_curr - outbuf) != outbuf_curr - outbuf)
				perr("Error sending data", NULL);
			outbuf_curr = outbuf;
		}
}

static inline void
cputc(int c)
{
	if (outbuf_curr == outbuf_end)
		cflush();
	*outbuf_curr++ = c;
}

static void
cputw(int c)
{
	cputc(c >> 8);
	cputc(c);
}

static void
cputs(char *k)
{
	while (*k)
		cputc(*k++);
}

static int
cgetc(void)
{
	static byte inbuf[256];
	static byte *instart;
	static byte *instop;

	if (instart == instop)
		{
			int l;
			alarm(10);
			l = read(fd, inbuf, sizeof(inbuf));
			alarm(0);
			if (l < 0)
				perr("Read error", NULL);
			if (!l)
				cerr("EOF detected (why?)", NULL);
			instart = inbuf;
			instop = inbuf + l;
		}
#if 0
	printf("%d\n", *instart);
#endif
	return *instart++;
}

static void
cwait(word i)
{
	word k = 0;

	cflush();
	while (k != i)
		k = (k << 8) | cgetc();
}

static int
cgetw(void)
{
	int c = cgetc();
	return (c << 8) | cgetc();
}

static void
progress(char *c, int i)
{
	fputc('\r', stdout);
	fprintf(stdout, c, i);
	fflush(stdout);
}

static void
beep(void)
{
	int a,b,c;
	cputs("$$$");
	cwait(('o' << 8) | 'k');
	a = cgetc();
	b = cgetc();
	c = cgetw();
	cwait(0x0a0d);
	printf("beep: Cnt=%d Alive=%d SelfTest=%d\n", a, b, c);
}

static void
test(void)
{
	int a,b,c;
	cputs("$OK");
	cwait(('o' << 8) | 'k');
	a = cgetc();
	b = cgetc();
	c = cgetw();
	cwait(0x0a0d);
	printf("test: Cnt=%d Alive=%d SelfTest=%d\n", a, b, c);
}

static char *
get_word(char **k)
{
	char *c = *k;
	char *d = c;

	if (!c)
		cerr("Argument expected", NULL);
	while (*c && *c != ',')
		c++;
	if (!*c)
		c = NULL;
	else
		*c++ = 0;
	*k = c;
	return d;
}

static void
test_end(char *k)
{
	if (k)
		cerr("Too many arguments", NULL);
}

static ulg
get_hex(char **k)
{
	char *c = get_word(k);
	ulg i;
	char *d;

	i = strtoul(c, &d, 16);
	if (d && *d)
		cerr("Malformed number: %s", c);
	return i;
}

static ulg
get_hex16(char **k)
{
	ulg i  = get_hex(k);
	if (i > 0xffff)
		cerr("Number too large: %x", (char *) i);
	return i;
}

static void
memsend_raw(char *addr, ulg aa, ulg s, int prog)
{
	ulg r;

	printf("Transmitting %s %04x/%04x\n", prog ? "Program" : "Data", aa, s);
	cputs("$D");
	cputc(prog ? 'P' : 'D');
	cputw(aa);
	cputw(s);
	cflush();
	r = 0;
	while (s--)
		{
			byte m[3];
			ulg n;
			
			if (!(s & 255))
				progress("%d words to go     ", s);
			m[0] = *addr++;
			m[1] = *addr++;
			cputc(m[0]);
			cputc(m[1]);
			n = (((ulg)m[0]) << 8) | (ulg) m[1];
			if (prog)
				{
					m[2] = *addr++;
					cputc(m[2]);
					n = (n << 8) | (ulg) m[2];
				}
			r += n;
		}
	cflush();
	progress("Waiting for checksum", 0);
	s = (cgetc() << 8) | cgetc();
	if (prog)
		s = (s << 8) | cgetc();
	r &= (prog ? 0xffffff : 0xffff);
	if (s != r)
		{
			fprintf(stderr, "\radspc: Checksum failed: expected %x, got %x\n", r, s);
			exit(1);
		}
	printf("\r%s memory upload completed OK\n", prog ? "Program" : "Data");
}

static void
memsend(char *addr, ulg aa, ulg s, int prog)
{
	if (prog && aa < 0x30)
		{
			int l = 0x30 - aa;
			if (l > s)
				l = s;
			memsend_raw(addr, 0x3fc0 + aa, l, 1);
			addr += 3 * l;
			aa += l;
			s -= l;
		}
	if (s)
		memsend_raw(addr, aa, s, prog);
}

static void
upload(char c, char *name)
{
	FILE *f;
	char *ff = get_word(&name);
	ulg aa = get_hex16(&name);
	ulg s, r;
	int prog = c == 'P';

	test_end(name);
	if (!(f = fopen(ff, "r")))
		perr("Unable to read %s", ff);
	fseek(f, 0, SEEK_END);
	s = ftell(f);
	fseek(f, 0, SEEK_SET);
	if (prog && s % 3 || !prog && s % 2)
		cerr("Invalid size of %s", ff);
	if (prog)
		s /= 3;
	else
		s >>= 1;
	if (s > 65535 || s + aa > 65535)
		cerr("File %s is too long", ff);
	cputs("$D");
	cputc(c);
	cputw(aa);
	cputw(s);
	cflush();
	r = 0;
	while (s--)
		{
			byte m[3];
			ulg n;
			
			if (!(s & 255))
				progress("%d words to go     ", s);
			m[0] = fgetc(f);
			m[1] = fgetc(f);
			cputc(m[0]);
			cputc(m[1]);
			n = (((ulg)m[0]) << 8) | (ulg) m[1];
			if (prog)
				{
					m[2] = fgetc(f);
					cputc(m[2]);
					n = (n << 8) | (ulg) m[2];
				}
			r += n;
		}
	cflush();
	progress("Waiting for checksum", 0);
	s = (cgetc() << 8) | cgetc();
	if (prog)
		s = (s << 8) | cgetc();
	r &= (prog ? 0xffffff : 0xffff);
	if (s != r)
		{
			fprintf(stderr, "\radspc: Checksum failed: expected %x, got %x\n", r, s);
			exit(1);
		}
	printf("\r%s memory upload completed OK\n", prog ? "Program" : "Data");
	fclose(f);
}

static void
download(char c, char *name)
{
	FILE *f;
	char *ff = get_word(&name);
	ulg aa = get_hex16(&name);
	ulg ll = get_hex16(&name);
	ulg s, r;
	int prog = c == 'P';

	test_end(name);
	if (aa + ll > 65535)
		cerr("Memory block for download too long", NULL);
	if (!(f = fopen(ff, "w")))
		perr("Unable to write %s", ff);
	cputs("$U");
	cputc(c);
	cputw(aa);
	cputw(ll);
	cflush();
	r = 0;
	while (ll--)
		{
			byte m[3];

			if (!(ll & 255))
				{
					printf("\r%d words to go    ", ll);
					fflush(stdout);
				}
			m[0] = cgetc();
			m[1] = cgetc();
			fputc(m[0], f);
			fputc(m[1], f);
			s = (((ulg)m[0]) << 8) | (ulg) m[1];
			if (prog)
				{
					m[2] = cgetc();
					fputc(m[2], f);
					s = (s << 8) | (ulg) m[2];
				}
			r += s;
		}
	progress("Waiting for checksum", 0);
	fflush(stdout);
	s = (cgetc() << 8) | cgetc();
	if (prog)
		s = (s << 8) | cgetc();
	r &= (prog ? 0xffffff : 0xffff);
	if (s != r)
		{
			fprintf(stderr, "\radspc: Checksum failed: expected %x, got %x\n", r, s);
			exit(1);
		}
	printf("\r%s memory download completed OK\n", prog ? "Program" : "Data");
	fclose(f);
}

static ulg
cparse(char c)
{
	if (c >= '0' && c <= '9')
		return c - '0';
	else if (c >= 'A' && c <= 'F')
		return c - 'A' + 10;
	cerr("Unknown character in hexadecimal number: `%c'", (char *)(int) c);
}

static void
send(char *l)
{
	FILE *f;
	char *ff = get_word(&l);
	char buf[64];
	char *k;
	ulg pos, xpos, dbs, cs, css, adr;
	int prog;
	byte *db;

	test_end(l);
	if (!(f = fopen(ff, "r")))
		perr("Unable to read %s", ff);
	dbs = 16384 * 3;
	db = malloc(dbs);
	if (!db)
		cerr("Out of memory", NULL);
	prog = -1;
	if (fgetc(f) != 27 || fgetc(f) != 27 || fgetc(f) != 'i' || fgetc(f) != '\r' || fgetc(f) != '\n')
		cerr("Missing header", NULL);
	pos = 0;
	xpos = 0;
	adr = 0;
	for(;;)
		{
			if (!fgets(buf, 63, f))
				break;
			if (!buf[0])
				continue;
			if (buf[0] == 27 && buf[1] == 27 && buf[2] == 'o')
				break;
			k = strchr(buf, '\n');
			if (!k)
				cerr("Line too long in %s", ff);
			*k = 0;
			k = strchr(buf, '\r');
			if (k)
				*k = 0;
			if (prog < -1)
				{
					sscanf(buf, "%x", &css);
					adr = css;
					prog += 3;
					continue;
				}
			if (buf[0] == '#')
				{
					if (prog < 0)
						cerr("Misplaced `#' in `%s'", buf);
					if (buf[1] != '1' || buf[2] != '2' || buf[3] != '3')
						cerr("Invalid command: `%s'", buf);
					sscanf(buf+4, "%x", &cs);
					if (cs != css)
						cerr("Mismatched checksum in input file", NULL);
					memsend(db, adr, xpos, prog);
					pos = 0;
					xpos = 0;
					prog = -1;
				}
			else if (buf[0] == '@')
				{
					if (prog != -1)
						cerr("Misplaced `@' in `%s'", buf);
					if ((buf[1] != 'P' && buf[1] != 'D') || buf[2] != 'A' || buf[3])
						cerr("Invalid command: `%s'", buf);
					prog = (buf[1] == 'P') ? -2 : -3;
				}
			else
				{
					int z = strlen(buf);
					if (prog < 0)
						cerr("Misplaced binary data in `%s'", buf);
					if (z != (prog ? 6 : 4))
						cerr("Invalid length of binary data in `%s'", buf);
					k = buf;
					cs = 0;
					while (k[0])
						{
							int l = (cparse(k[0]) << 4) | cparse(k[1]);
							if (pos >= dbs)
								cerr("Section too long, cannot handle", NULL);
							db[pos++] = l;
							cs = (cs << 8) | l;
							k += 2;
						}
					css += cs;
					xpos++;
				}
		}
	if (prog >= 0)
		cerr("Missing final '#'", NULL);
	fclose(f);
}

static void
go(char *k)
{
	int z = get_hex16(&k);

	test_end(k);
	cputs("$GO");
	cputw(z);
	cflush();
	if (cgetw() != z)
		cerr("Invalid reply", NULL);
	puts("Started.");
}

int
main(int argc, char **argv)
{
	if (argc < 2)
		cerr("Nothing happens...", NULL);
	argv++;
	argc--;
	if (!strcmp(argv[0], "-f") && argc >= 2)
		{
			name = argv[1];
			argv += 2;
			argc -= 2;
		}
	if ((fd = open(name, O_RDWR | O_NOCTTY)) < 0)
		perr("Unable to open %s", name);
	if (tcsetattr(fd, TCSANOW, &tios) < 0)
		perr("Unable to set termios on %s", name);
	signal(SIGALRM, sig);
	while (argc-- > 0)
		{
			char *k = *argv++;
			char *p = NULL;
			
			if (k[0] != '-' || !k[1] || k[2])
				cerr("Invalid request: %s", k);
			if (strchr("pdPDuG", k[1]))
				{
					if (!argc--)
						cerr("Missing parameter for %s", k);
					p = *argv++;
				}
			switch (k[1])
				{
					case 'b':
						beep();
						break;
					case 't':
						test();
						break;
					case 'D':
						upload('D', p);
						break;
					case 'P':
						upload('P', p);
						break;
					case 'd':
						download('D', p);
						break;
					case 'p':
						download('P', p);
						break;
					case 'G':
						go(p);
						break;
					case 'u':
						send(p);
						break;
					default:
						cerr("Invalid request: %s", k);
				}
		}
	return 0;
}

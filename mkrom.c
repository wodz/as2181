/*
 *		ADSP ROM File Maker
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
#include <unistd.h>

#include "glob.h"

static ulg rom_size;
static byte *rom;

static void cerr(char *, char *) NONRET;
static void perr(char *, char *) NONRET;

static void
cerr(char *err, char *par)
{
  fputs("mkrom: ", stderr);
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

static ulg
cparse(char c)
{
	if (c >= '0' && c <= '9')
		return c - '0';
	else if (c >= 'A' && c <= 'F')
		return c - 'A' + 10;
	cerr("Unknown character in hexadecimal number: `%c'", (char *)(int) c);
}

static void *
xmalloc(ulg size)
{
  void *x = malloc(size);
  if (!x)
	cerr("Out of memory", NULL);
  return x;
}

static void
romify(char *ff, ulg pbase, ulg plen, ulg dbase, ulg dlen)
{
  FILE *f;
  char buf[64];
  char *k;
  ulg pos, xpos, cs, css, adr, base, len, ws;
  int prog;

  printf(" %s", ff);
  fflush(stdout);
  
  if (!(f = fopen(ff, "r")))
	perr("Unable to read %s", ff);
  prog = -1;
  if (fgetc(f) != 27 || fgetc(f) != 27 || fgetc(f) != 'i' || fgetc(f) != '\r' || fgetc(f) != '\n')
	cerr("Missing header", NULL);
  ws = pos = xpos = adr = base = len = 0;
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
		  ws = prog ? 3 : 2;
		  base = (prog ? pbase : dbase) + adr * ws;
		  len = prog ? plen : dlen;
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
		  printf(" %04x-%04x[%c]", base, xpos*ws-1+base, "DP"[prog]);
		  fflush(stdout);
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
			  if (pos >= len)
				cerr("Section too long, cannot handle", NULL);
			  rom[base + pos++] = l;
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
write_out(char *name)
{
  int f;

  printf(" ... ");
  fflush(stdout);
  f = open(name, O_WRONLY | O_CREAT, 0644);
  if (f < 0)
	perr("Unable to write %s", name);
  if (write(f, rom, rom_size) != rom_size)
	perr("Error writing %s", name);
  close(f);
  puts("OK");
}

int
main(int argc, char **argv)
{
  char *dest_name;

  if (argc < 4)
	{
	  fprintf(stderr, "mkrom 1.0 (c) 1996 Martin Mares\n\
\n\
Usage: mkrom dest-file rom-size-KB paddr,plen,daddr,dlen,file ...\n");
	  return 1;
	}
  dest_name = argv[1];
  rom_size = atol(argv[2]);
  if (rom_size < 1 || rom_size > 4096)
	cerr("Invalid ROM size", NULL);
  printf("Building %dK ROM:", rom_size);
  fflush(stdout);
  rom_size *= 1024;
  rom = xmalloc(rom_size);
  memset(rom, 0xff, rom_size);
  while (argc >= 4)
	{
	  char *p = argv[3];
	  char *l[4];
	  ulg x[4];
	  int c;

	  for(c=0; c<4; c++)
		{
		  l[c] = p;
		  while (*p && *p != ',')
			p++;
		  if (!*p)
			{
			  cerr("Argument syntax error", NULL);
			  return 1;
			}
		  *p++ = 0;
		  x[c] = strtol(l[c], NULL, 16);
		}
	  if (x[0] + x[1] > rom_size || x[2] + x[3] > rom_size)
		cerr("Out of ROM space", NULL);
	  romify(p, x[0], x[1], x[2], x[3]);
	  argc--;
	  argv++;
	}
  write_out(dest_name);
  return 0;
}

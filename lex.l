/* Hey, Emacs, this is not -*- C -*-, but it should look like as it were...
 *
 *		ADSP 2181 Assembler -- Lexical Analysis
 *
 *		(c) 1996 Martin Mares, <mj@k332.feld.cvut.cz>
 *
 *		This software may be freely distributed and used according to the terms
 *		of the GNU General Public License. See file COPYING in any of the GNU utilities.
 */

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include "as2181.h"
#include "syn.tab.h"

#define YY_NO_UNPUT

/* Internal functions */

static void map_lines(ulg, char *);
static void upcase_it(char *);

/* Scanner input */

FILE *infile;
#define yyin infile

ulg lino;								/* Line number */
int err_max = 10;						/* Maximal number of errors before stopping */
%}

%x PCOMM CCOMM

ALPHA [a-zA-Z_]
DIGIT [0-9]
ODIGIT [0-7]
HDIGIT [0-9a-fA-F]
ALNUM [0-9a-zA-Z_@]
WHITE [ \t]

%%

0{ODIGIT}+ {							/* Numbers */
  yylval.i = strtoul(yytext+1, NULL, 8);
  return NUM;
}

0x{HDIGIT}+ {
  yylval.i = strtoul(yytext+2, NULL, 16);
  return NUM;
}

{DIGIT}+ {
  yylval.i = strtoul(yytext, NULL, 10);
  return NUM;
}

"H#"{HDIGIT}+ {
  yylval.i = strtoul(yytext+2, NULL, 16);
  return NUM;
}

"B#"[01]+ {
  yylval.i = strtoul(yytext+2, NULL, 2);
  return NUM;
}

"(SS)" { yylval.i = MC_SS; return MACCLASS; } /* Classes */
"(SU)" { yylval.i = MC_SU; return MACCLASS; }
"(US)" { yylval.i = MC_US; return MACCLASS; }
"(UU)" { yylval.i = MC_UU; return MACCLASS; }
"(RND)" { yylval.i = MC_RND; return MACCLASS; }

"(HI)" { yylval.i = SC_HI; return SHCLASS; }
"(LO)" { yylval.i = SC_LO; return SHCLASS; }
"(HIX)" { yylval.i = SC_HIX; return SHCLASS; }

"MR" { return MR; }
"MF" { return MF; }
"SR" { return SR; }

"<<" return LL;							/* Operators */
">>" return RR;
[-+*()/\[\],;:=%^] return yytext[0];

'.' {									/* Character constants */
  yylval.i = yytext[1];
  return NUM;
}

{ALPHA}{ALNUM}* {						/* Symbols */
  const struct as_kwd *k;
  char buf[64];

  if (yyleng > 63)
	{
	  cerr("Symbol too long");
	  yytext[63] = 0;
	  yyleng = 63;
	}
  upcase_it(buf);
  k = is_kwd(buf, yyleng);
  if (k)
	{
	  yylval.i = k->value;
	  return k->class;
	}
  yylval.s = find_symbol(case_insensitive ? buf : yytext, yyleng, thismod);
  return SYM;
}

"."{ALNUM}+ {							/* Directives */
  const struct as_kwd *k;

  upcase_it(yytext);
  k = is_kwd(yytext, yyleng);
  if (k)
	{
	  yylval.i = k->value;
	  return k->class;
	}
  err("Invalid compiler directive");
}

<INITIAL><<EOF>> {						/* End of file */
  return GOT_EOF;
}

"# ".*\n {								/* CPP line info */
  char *c = yytext + 2;
  char *d = c;
  char *e = yytext + yyleng - 2;
  ulg xxx;

  while (*d >= '0' && *d <= '9')
	d++;
  while (c != e && *e != '"')
	e--;
  if (c == d || *d != ' ' || d[1] != '"' || *e != '"')
	err("Invalid CPP file / line number information");
  *e = *d = 0;
  xxx = strtoul(c, NULL, 10);
  map_lines(xxx, d+2);
}

<*>\n lino++;

"{" BEGIN(PCOMM);						/* Comments */
<PCOMM>"}" BEGIN(INITIAL);
<PCOMM>"{" warn("'{' in comment");

"/*" BEGIN(CCOMM);
<CCOMM>"*/" BEGIN(INITIAL);
<CCOMM>"/*" warn("/* in comment");

<PCOMM,CCOMM>. ;
<PCOMM,CCOMM><<EOF>> err("Non-terminated comment");

{WHITE}+ ;								/* Eat up white space */

. err("Invalid character (`%c')", yytext[0]); /* "Catch all" rule */

%%

/* LEX Wrapper Function */

int
yywrap(void)
{
  return 1;
}

/* Line lookup */

struct line_info {
  struct line_info *next;
  ulg abs, rel;
  char filename[1];
};

static struct line_info *first_li;
static struct line_info **last_li = &first_li;

static void
map_lines(ulg rel, char *name)
{
  struct line_info *l = xmalloc(sizeof(struct line_info) + strlen(name));

  *last_li = l;
  last_li = &l->next;
  l->next = NULL;
  l->abs = lino;
  l->rel = rel;
  strcpy(l->filename, name);
}

ulg
lookup_line(ulg abs, char **name)
{
  struct line_info *l;
  static struct line_info *cache = NULL;

  if (cache && cache->abs <= abs)
	l = cache;
  else
	l = first_li;
  if (!l)
	fatal_error("Corrupted line list");
  while (l->next && l->next->abs <= abs)
	l = l->next;
  *name = l->filename;
  cache = l;
  return abs - l->abs + l->rel;
}

/* Error messages */

static int err_count, warn_count;

static void
repnum(char *form, int count)
{
  fprintf(stderr, form, count, (count == 1) ? "" : "s");
}

void
report_warns(void)
{
  if (warn_count)
	repnum("%d warning%s detected.\n", warn_count);
}

static void errhalt(void) NONRET;
static void
errhalt(void)
{
  if (warn_count)
	repnum("%d warning%s, ", warn_count);
  repnum("%d error%s detected.\n", err_count);
  exit(1);
}

void
errstop(void)
{
  if (err_count)
	errhalt();
}

static void
vmsg(char *msg, va_list args, char *start, char *finish, ulg line)
{
  char *fn;

  if (line == ~0)
	fprintf(stderr, "%s: ", start);
  else
	{
	  line = lookup_line(line, &fn);
	  fprintf(stderr, "%s in file %s, line %d: ", start, fn, line);
	}
  vfprintf(stderr, msg, args);
  fputs(finish, stderr);
}

static void
errcheck(void)
{
  if (++err_count >= err_max)
	{
	  if (err_max > 1)
		fprintf(stderr, "That makes %d errors, try again...\n", err_count);
	  errstop();
	}
}

static char emsg[] = "Error", wmsg[] = "Warning", imsg[] = "Internal error",
            etrail[] = "!\n", wtrail[] = ".\n", nmsg[] = "Note";

void
err(char *msg, ...)
{
  va_list args;

  va_start(args, msg);
  vmsg(msg, args, emsg, etrail, lino);
  errcheck();
  errhalt();
}

void
cerr(char *msg, ...)
{
  va_list args;

  va_start(args, msg);
  vmsg(msg, args, emsg, etrail, lino);
  errcheck();
  va_end(args);
}

void
ierr(char *msg, ...)
{
  va_list args;

  va_start(args, msg);
  vmsg(msg, args, imsg, etrail, lino);
  errcheck();
  errhalt();
}

void
warn(char *msg, ...)
{
  va_list args;

  va_start(args, msg);
  if (!hide_warns)
	{
	  vmsg(msg, args, wmsg, wtrail, lino);
	  warn_count++;
	}
  va_end(args);
}

void
lerr(ulg li, char *msg, ...)
{
  va_list args;

  va_start(args, msg);
  vmsg(msg, args, emsg, etrail, li);
  errcheck();
  errhalt();
}

void
clerr(ulg li, char *msg, ...)
{
  va_list args;

  va_start(args, msg);
  vmsg(msg, args, emsg, etrail, li);
  errcheck();
  va_end(args);
}

void
ilerr(ulg li, char *msg, ...)
{
  va_list args;

  va_start(args, msg);
  vmsg(msg, args, imsg, etrail, li);
  errcheck();
  errhalt();
}

void
lwarn(ulg li, char *msg, ...)
{
  va_list args;

  va_start(args, msg);
  if (!hide_warns)
	{
	  vmsg(msg, args, wmsg, wtrail, li);
	  warn_count++;
	}
  va_end(args);
}

void
lnote(ulg li, char *msg, ...)
{
  va_list args;

  va_start(args, msg);
  vmsg(msg, args, nmsg, wtrail, li);
  va_end(args);
}

char *
syserr(void)
{
  return strerror(errno);
}

/* Symbols */

#define HASH_SIZE 1024

static struct symbol *hash[HASH_SIZE];

ulg
hash_value(char *c, ulg len)
{
  ulg h;
  char *d;

  h = len;
  for(d=c; *d; d++)
	h = 13*h + *d;
  h = h % HASH_SIZE;
  return h;
}

struct symbol *
find_symbol(char *c, ulg len, struct module *context)
{
  struct symbol *s, *b;
  ulg h = hash_value(c, len);

  b = NULL;
  for(s=hash[h]; s; s=s->next)
	if (!strcmp(s->name, c) && (!s->scope || s->scope == context) && (!b || b->scope))
	  b = s;
  if (b)
	return b;

  s = xmalloc(sizeof(struct symbol) + len);
  strcpy(s->name, c);
  s->next = hash[h];
  s->value = NULL;
  s->scope = context;
  hash[h] = s;
  return s;
}

void
expose_symbol(struct symbol *s)
{
  ulg h;
  struct symbol *k;
  ulg coll = 0;

  h = hash_value(s->name, strlen(s->name));
  for(k=hash[h]; k; k=k->next)
	if (!strcmp(k->name, s->name) && k != s)
	  {
		if (!k->scope)
		  {
			coll++;
			cerr("`%s' already defined as public");
		  }
		else if (k->value)
		  {
			if (!coll++)
			  cerr("`%s' already defined elsewhere", s->name);
			lnote(LINE(k->value), "See this line for previous definition");
		  }
		else
		  {
			struct symref *m = NEW_NODE(symref, N_SYMREF);
			m->sym = s;
			k->value = NODE m;
		  }
	  }
  if (!coll)
	s->scope = NULL;
}

/* Init */

void
init_lex(char *src, int preprocess)
{
  lino = ~0;
  if (!preprocess)
	{
	  infile = fopen(src, "r");
	  if (!infile)
		err("Unable to open `%s': %s", src, syserr());
	}
  else
	{
	  pid_t pid;
	  int fh;
	  int pip[2];
	  char *cpp = "/lib/cpp";

	  fh = open(src, O_RDONLY);			/* Test if the file exists */
	  if (fh < 0)
		err("Unable to open `%s': %s", src, syserr());
	  close(fh);
	  if (pipe(pip) < 0)
		err("Unable to create pipe: %s", syserr());
	  pid = fork();
	  if (pid < 0)
		err("Fork failed: %s", src, syserr());
	  if (!pid)							/* CPP process */
		{
		  close(1);						/* Redirect stdout to pipe */
		  dup(pip[1]);
		  close(pip[0]);
		  close(pip[1]);
		  execlp(cpp, cpp, "-Wall", "-nostdinc", "-undef", "-DADSP2181", "-traditional", "-$", src, NULL);
		  err("Cannot execute %s: %s", cpp, syserr());
		}
	  close(pip[1]);					/* Get FILE for the pipe */
	  infile = fdopen(pip[0], "r");
	  if (!infile)
		err("Error opening cpp pipe: %s", syserr());
	}
  lino = 0;
  map_lines(1, src);
}

static void
upcase_it(char *d)
{
  char *c;

  for(c=yytext; *c; c++)
	if (*c >= 'a' && *c <= 'z')
	  *d++ = *c - 0x20;
    else
	  *d++ = *c;
  *d = 0;
}

/*
 *		ADSP 2181 Assembler -- Option Analysis and main()
 *
 *		(c) 1996 Martin Mares, <mj@k332.feld.cvut.cz>
 *
 *		This software may be freely distributed and used according to the terms
 *		of the GNU General Public License. See file COPYING in any of the GNU utilities.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdarg.h>

#include "as2181.h"

static char *options = "o:pve:d:iwl";

static char *help_string = "\n\
Usage: as2181 [<options>] <source>\n\
\n\
-o file\tuse given output file instead of the default\n\
-p\tuse the C preprocessor\n\
-v\tbe verbose\n\
-e max\tset maximal number of errors before stopping\n\
-d flags\tset debugging flags\n\
-i\tbe case-insensitive\n\
-w\thide all warnings\n\
-l\tgenerate listing\n\
\n";

static int preprocess;
int verbose, case_insensitive, hide_warns, do_listing;
ulg debug;

void
fatal_error(char *text, ...)
{
  va_list va;

  va_start(va, text);
  fputs("as2181: ", stderr);
  vfprintf(stderr, text, va);
  fputs("!\n", stderr);
  exit(1);
}

void *
xmalloc(ulg size)
{
  void *k = malloc(size);
  if (!k)
	fatal_error("Unable to allocate %d bytes of memory", size);
  return k;
}

static void help(void) NONRET;
static void
help(void)
{
  fprintf(stderr, help_string);
  exit(1);
}

char *
find_ext(char *c)
{
  char *l = NULL;

  while (*c)
	{
	  if (*c == '/')
		l = NULL;
	  else if (*c == '.')
		l = c;
	  c++;
	}
  return l;
}

static ulg
parse_switches(char *sw, char *t, char *e)
{
  ulg x = 0;

  while (*t)
	{
	  char *k = strchr(sw, *t++);
	  if (!k)
		fatal_error("Unknown %s switch: %c", e, t[-1]);
	  x |= 1 << (k - sw);
	}
  return x;
}

int
main(int argc, char **argv)
{
  int i;
  char *out_file = NULL;
  char *in_file;
  ulg dov;

  while ((i = getopt(argc, argv, options)) != -1)
	switch (i)
	  {
	  case 'o':
		out_file = optarg;
		break;
	  case 'v':
		verbose++;
		break;
	  case 'p':
		preprocess = 1;
		break;
	  case 'e':
		err_max = atol(optarg);
		break;
	  case 'd':
		debug |= parse_switches(DEBUG_SWITCHES, optarg, "debug");
		break;
	  case 'i':
		case_insensitive = 1;
		break;
	  case 'w':
		hide_warns = 1;
		break;
	  case 'l':
		do_listing++;
		break;
	  default:
		help();
	  }
  if (optind != argc-1)
	help();
  in_file = argv[optind];
  if (!out_file)
	{
	  char *k;

	  out_file = xmalloc(strlen(in_file) + 4);
	  strcpy(out_file, in_file);
	  if (k = find_ext(out_file))
		*k = 0;
	  strcat(out_file, ".exe");
	}
  if (verbose)
	printf("Compiling %s to %s...\n", in_file, out_file);
  init_lex(in_file, preprocess);
  init_syn();
  init_mem();
  if (verbose > 1)
	puts("Parsing.");
  if (yyparse())
	{
	  errstop();
	  return 1;
	}
  dov = (verbose > 1);
  if (dov)
	puts("Allocating memory.");
  process_mem();
  if (dov)
	puts("Processing expressions.");
  do_exprs();
  if (dov)
	puts("Processing initializers.");
  do_inits();
  if (dov)
	puts("Creating program binary.");
  copy_prog();
  if (dov)
	puts("Writing output file.");
  write_result(out_file);
  if (do_listing)
	dump_listing();
  report_warns();
  return 0;
}

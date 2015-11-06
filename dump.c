/*
 *		ADSP 2181 Assembler -- Listing Functions
 *
 *		(c) 1996 Martin Mares, <mj@k332.feld.cvut.cz>
 *
 *		This module is worth of being completely rewritten...
 *
 *		This software may be freely distributed and used according to the terms
 *		of the GNU General Public License. See file COPYING in any of the GNU utilities.
 */

#include <stdio.h>
#include <string.h>

#include "as2181.h"

#define MAX_CACHED 8

struct file_slot {
  node n;
  char *name;
  ulg line;
  FILE *f;
};

static list file_cache;
static struct file_slot *file_cache_cache;
static ulg cached_files, dino;
static char lstbuf[256];

static char *
get_line(ulg n)
{
  char *b;
  ulg m;
  struct file_slot *ca;

  m = lookup_line(n, &b);
  if (m == ~0)
	ierr("Attempt to lookup non-existent line %d", n);
  if (file_cache_cache && file_cache_cache->name == b)
	ca = file_cache_cache;
  else
	{
	  DO_FOR_ALL(ca, file_cache)
		if (ca->name == b)
		  break;
	  if (!ca->n.next)
		{
		  if (cached_files == MAX_CACHED)
			{
			  ca = (struct file_slot *) file_cache.tail.prev;
			  rem_node(&ca->n);
			  fclose(ca->f);
			}
		  else
			{
			  cached_files++;
			  ca = xmalloc(sizeof(struct file_slot));
			}
		  ca->name = b;
		  ca->line = 1;
		  ca->f = fopen(b, "r");
		  if (!ca->f)
			err("Unable to open `%s' for inclusion in the listing", b);
		  add_head(&file_cache, &ca->n);
		}
	  file_cache_cache = ca;
	}

  if (ca->line > m)
	ierr("Forward reference in listing not allowed");
  while (ca->line <= m)
	{
	  fgets(lstbuf, 255, ca->f);
	  b = strchr(lstbuf, '\n');
	  if (b)
		*b = 0;
	  dino = ca->line++;
	}
  return lstbuf;
}

static inline byte
get_byte(struct memblock *m, ulg offs)
{
  if (!m->init || m->initlen < offs)
	return 0;
  else
	return m->init[offs];
}

void
dump_listing(void)
{
  struct module *mod;
  struct insn *ins;
  struct var *var;
  struct constant *con;
  ulg il, vl, cl, g, ipos, ioff, gl;
  char buf[64];
  char *k;

  init_list(&file_cache);
  mod = HEAD(modules);
  var = HEAD(varlist);
  con = HEAD(constlist);
  ins = HEAD(mod->insns);

  g = ioff = 0;
  ipos = mod->mem->addr;
  while (g < src_lines)
	{
	  if (ins && !ins->n.next)
		{
		  if (mod->n.next)
			{
			  mod = (struct module *) mod->n.next;
			  ins = HEAD(mod->insns);
			  ipos = mod->mem->addr;
			  ioff = 0;
			}
		  else
			ins = NULL;
		}
	  if (var && !var->n.next)
		var = NULL;
	  if (con && !con->n.next)
		con = NULL;
	  if (!ins && !var && !con)
		{
		  gl = src_lines - 1;
		  strcpy(buf, "\t\t");
		}
	  else
		{
		  il = ins ? LINE(ins) : ~0;
		  vl = var ? var->line : ~0;
		  cl = con ? con->line : ~0;
		  if (il <= vl && il <= cl)
			{
			  if (TYPE(ins) == N_INSN)
				{
				  sprintf(buf, "P %04X\t%06X\t", ipos++, (get_byte(mod->mem, ioff) << 16) |
						  (get_byte(mod->mem, ioff+1) << 8) | (get_byte(mod->mem, ioff+2)));
				  ioff += 3;
				}
			  else if (ins->n.next->next && LINE(ins->n.next) == ins->line)
				{
				  ins = (struct insn *) ins->n.next;
				  continue;
				}
			  else
				sprintf(buf, "P %04X\t\t", ipos);
			  gl = il;
			  ins = (struct insn *) ins->n.next;
			}
		  else if (vl <= il && vl <= cl)
			{
			  sprintf(buf, "%c %04X\t[%04X]\t", var->mem->isprog ? 'P' : 'D',
					  var->offs + var->mem->addr, var->size);
			  gl = vl;
			  do
				var = (struct var *) var->n.next;
			  while (var->n.next && var->line == gl);
			}
		  else
			{
			  sprintf(buf, "C\t[%04X]\t", con->value);
			  gl = cl;
			  con = (struct constant *) con->n.next;
			}
		}
	  while (g < gl)
		{
#if 0
		  printf("%5d\t", g);
#endif
		  k = get_line(g++);
		  if (k)
			printf("\t\t%5d\t%s\n", dino, k);
		  else
			break;
		}
#if 0
	  printf("%5d\t", g);
#endif
	  fputs(buf, stdout);
	  if (g <= gl && (k = get_line(g++)))
		printf("%5d\t%s\n", dino, k);
	  else
		puts("");
	}
}

/*
 *		ADSP 2181 Assembler -- DSP Memory Allocation & Output File Generation
 *
 *		(c) 1996 Martin Mares, <mj@k332.feld.cvut.cz>
 *
 *		This software may be freely distributed and used according to the terms
 *		of the GNU General Public License. See file COPYING in any of the GNU utilities.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "as2181.h"

static list memblocks,					/* Overall list of memory blocks */
            mem_p,						/* Program memory blocks */
            mem_d;						/* Data memory blocks */

struct memblock *
new_memblock(void)
{
  struct memblock *m = xmalloc(sizeof(struct memblock));

  add_tail(&memblocks, &m->n);
  m->addr = ~0;
  m->len = 0;
  m->isprog = 0xff;
  m->isram = 0xff;
  m->sym = NULL;
  m->init = NULL;
  m->initlen = 0;
  return m;
}

static char *							/* Get name of memory regions */
get_name(struct memblock *m)
{
  if (m->sym)
	return m->sym->name;
  return "unknown region";
}

static ulg
get_ctext_line(struct memblock *m)
{
  if (m->sym && m->sym->value)
	return LINE(m->sym->value);
  return ~0;
}

static void								/* Divide to P and D lists */
divide_pd(void)
{
  struct memblock *m, *n;

  init_list(&mem_p);
  init_list(&mem_d);
  for(m = HEAD(memblocks); n = (struct memblock *) m->n.next; m = n)
	{
	  if (m->len == 0xffff)
		ierr("Memory allocation with no length given attemted for %s", get_name(m));
	  rem_node(&m->n);
	  if (!m->isram)
		clerr(get_ctext_line(m), "ROM modules not supported");
	  else
		add_tail((m->isprog) ? &mem_p : &mem_d, &m->n);
	}
}

struct freelist {						/* Free block list */
  node n;
  ulg base;
  ulg len;
};

static list freelist;

static void								/* Create a free block list */
fb_create(ulg base, ulg len)
{
  struct freelist *k = xmalloc(sizeof(struct freelist));

  init_list(&freelist);
  add_tail(&freelist, &k->n);
  k->base = base;
  k->len = len;
}

static void
fb_free(void)							/* Delete the free block list */
{
  struct freelist *k, *l;

  for(k = HEAD(freelist); l = (struct freelist *) k->n.next; k = l)
	{
	  rem_node(&k->n);
	  free(k);
	}
}

static ulg								/* Allocate an absolute block */
fb_alloc_abs(ulg base, ulg len)
{
  struct freelist *k;

  if (!len)
	return 1;
  DO_FOR_ALL(k, freelist)
	if (k->base <= base && k->base + k->len >= base + len)
	  {
		if (k->base < base && k->base + k->len > base + len) /* Mid: split */
		  {
			struct freelist *z = xmalloc(sizeof(struct freelist));
			z->base = k->base;
			z->len = base - k->base;
			insert_node(&z->n, k->n.prev);
			k->base = base;
			k->len -= z->len;			/* Convert to start */
		  }
		k->len -= len;
		if (k->base == base)			/* At the beginning */
		  {
			k->base += len;
			if (!k->len)
			  rem_node(&k->n);
			return 1;
		  }
		return 1;
	  }
  return 0;
}

static ulg								/* Allocate */
fb_alloc(ulg len)
{
  struct freelist *k, *best = NULL;
  ulg r;

  if (!len)
	return 0;
  DO_FOR_ALL(k, freelist)
	if (k->len >= len)
	  if (!best || best->len > k->len)
		best = k;
  if (!best)
	return ~0;							/* Out of memory */
  r = best->base;
  best->len -= len;
  best->base += len;
  if (!best->len)
	rem_node(&best->n);
  return r;
}

static ulg
get_circ_align(ulg len)
{
  ulg i;
  for(i=1; i<len; i *= 2)
	;
  return i - 1;
}

static ulg								/* Allocate memory on 4-byte boundary */
fb_alloc_circular(ulg len)
{
  struct freelist *k, *best = NULL;
  ulg r, align;

  if (!len)
    return 0;
  align = get_circ_align(len);
  DO_FOR_ALL(k, freelist)
    if (k->len >= len + (k->base & align))
	  if (!best || best->len > k->len)
		best = k;
  if (!best)
	return ~0;
  r = (best->base + align) & ~align;
  if (!fb_alloc_abs(r, len))
	ierr("fb_alloc_circular failed for %d bytes", len);
  return r;
}

static int
cmp_them(struct memblock **a, struct memblock **b)
{
  ulg x = (*b)->len;
  ulg y = (*a)->len;

  if (x < y)
	return -1;
  if (x > y)
	return 1;
  return 0;
}

static int
overlays(struct memblock *a, struct memblock *b)
{
  ulg x0 = a->addr;
  ulg x1 = x0 + a->len;
  ulg y0 = b->addr;
  ulg y1 = y0 + b->len;

  if (x0 < y0)
	x0 = y0;
  if (x1 > y1)
	x1 = y1;
  return x1 - x0;
}

static void
alloc_memory(list *l, ulg base, ulg len)
{
  struct memblock *m, *n, **dir, **diw;
  list donelist;
  ulg cnt;

  fb_create(base, len);
  init_list(&donelist);

  cnt = 0;
  for(m = HEAD(*l); n = (struct memblock *) m->n.next; m = n) /* Allocate absolutes */
	{
	  if (m->addr != 0xffff)
		{
		  rem_node(&m->n);
		  if (m->iscirc && (m->addr & get_circ_align(m->len)))
			clerr(get_ctext_line(m), "Misaligned circular buffer");
		  if (!fb_alloc_abs(m->addr, m->len))
			{
			  struct memblock *a;
			  DO_FOR_ALL(a, donelist)
				if (overlays(a, m))
				  clerr(get_ctext_line(a), "%s overlaying with %s", get_name(a), get_name(m));
			}
		  else
			add_tail(&donelist, &m->n);
		}
	  else
		cnt++;
	}

  diw = dir = xmalloc(sizeof(struct memblock *) * cnt);	/* Sort relatives */
  for(m = HEAD(*l); n = (struct memblock *) m->n.next; m = n)
	{
	  rem_node(&m->n);
	  *diw++ = m;
	}
  qsort(dir, cnt, sizeof(struct memblock *), (int (*)(const void *, const void *)) cmp_them);
  diw = dir;
  while (cnt--)							/* And allocate them... */
	{
	  m = *diw++;
	  m->addr = m->iscirc ? fb_alloc_circular(m->len) : fb_alloc(m->len);
	  if (m->addr == 0xffff)
		clerr(get_ctext_line(m), "Out of memory for %s", get_name(m));
	  add_tail(&memblocks, &m->n);
	}
  free(dir);

  add_tail_list(&memblocks, &donelist);
  fb_free();
}

static void								/* Measure size of all modules */
measure_prog(void)
{
  struct module *m;

  DO_FOR_ALL(m, modules)
	{
	  ulg cnt = 0;
	  struct pheader *k;
	  DO_FOR_ALL(k, m->insns)
		{
		  if (k->type == N_INSN)
			cnt++;
		  else if (k->type != N_LABEL)
			ierr("measure_prog: unknown type %d", k->type);
		}
	  m->mem->len = cnt;
	}
}

static void								/* Set values of all labels */
set_labels(void)
{
  struct module *m;

  DO_FOR_ALL(m, modules)
	{
	  ulg cnt = 0;
	  struct pheader *k;
	  DO_FOR_ALL(k, m->insns)
		{
		  if (k->type == N_INSN)
			cnt++;
		  else if (k->type == N_LABEL)
			{
			  DECL_NODE(l, label, k);
			  l->addr = cnt + m->mem->addr;
			}
		  else
			ierr("set_labels: unknown type %d", k->type);
		}
	}
}

static void
debug_memlist(void)
{
  struct memblock *m;

  DO_FOR_ALL(m, memblocks)
	printf("R%cM %c %04x %04x %s\n",
		   m->isram ? 'A' : 'M',
		   m->isprog ? 'P' : 'D',
		   m->addr,
		   m->len,
		   get_name(m));
}

void									/* Process all memory block related things */
process_mem(void)
{
  measure_prog();						/* Measure module sizes and estimate label locations */
  divide_pd();							/* Allocate memory blocks */
  alloc_memory(&mem_p, 0, 0x4000);
  alloc_memory(&mem_d, 0, 0x3fe0);
  errstop();
  set_labels();
  if (debug & DEBUG_MEMLIST_FINAL)
	debug_memlist();
  if (debug & DEBUG_VARS_MEM)
	dump_list(&varlist);
}

static void
mem_set(struct memblock *m, ulg addr, byte data)
{
  if (!m->init)
	{
	  ulg size = m->len * (m->isprog ? 3 : 2);
	  m->init = xmalloc(size);
	  bzero(m->init, size);
	}
  m->init[addr++] = data;
  if (m->initlen < addr)
	m->initlen = addr;
}

void									/* Process initializers */
do_inits(void)
{
  struct var *v;
  struct init *i;
  ulg r;
  node *n;

  DO_FOR_ALL(v, varlist)
	if (i = v->init)
	  for(r=0; r<v->size; r++)
		if (n = i->k[r])
		  if (!resolve_expr(&n))
			clerr(LINE(n), "Initializer not constant");
		  else
			{
			  int k = expr_to_num(n);
			  ulg a = k;
			  ulg m;
			  struct memblock *z = v->mem;

			  if (z->isprog && (k > 0xffffff || k < -0x800000) ||
				  !z->isprog && (k > 0xffff || k < -0x8000))
				  clerr(LINE(n), "Initializer %d out of range", k);
			  if (z->isprog)
				{
				  m = (r + v->offs) * 3;
				  mem_set(z, m++, a >> 16);
				}
			  else
				m = (r + v->offs) * 2;
			  mem_set(z, m++, a >> 8);
			  mem_set(z, m, a);
			}
  errstop();
}

void
copy_prog(void)
{
  struct module *m;
  struct insn *i;
  struct memblock *r;
  ulg ofs;

  DO_FOR_ALL(m, modules)
	{
	  r = m->mem;
	  ofs = 0;
	  DO_FOR_ALL(i, m->insns)
		if (i->type == N_INSN)
		  {
			if (i->expr && !resolve_insn(i))
			  clerr(i->line, "Unresolved expression");
			mem_set(r, ofs++, i->code >> 16);
			mem_set(r, ofs++, i->code >> 8);
			mem_set(r, ofs++, i->code);
		  }
	  if (ofs != r->len*3)
		ilerr(m->line, "Mismatched module sizes %d != %d", ofs, r->len*3);
	}
}

void
write_result(char *name)
{
  FILE *x = fopen(name, "w");
  struct memblock *m;
  ulg csum, i;
  byte *j;
  int prog, skip;

  if (!x)
	fatal_error("Unable to open output file `%s'", name);
  fputs("\033\033i\r\n", x);
  DO_FOR_ALL(m, memblocks)
	{
	  if (!m->init)
		continue;
	  prog = m->isprog;
	  skip = prog ? 3 : 2;
	  fprintf(x, "@%cA\r\n%04X\r\n", prog ? 'P' : 'D', m->addr);
	  csum = m->addr;
	  j = m->init;
	  for(i=0; i<m->initlen; i += skip)
		{
		  ulg z = (j[0] << 8 | j[1]);
		  fprintf(x, "%02X%02X", j[0], j[1]);
		  j += 2;
		  if (prog)
			{
			  fprintf(x, "%02X", *j);
			  z = (z << 8) | *j++;
			}
		  csum += z;
		  fputc('\n', x);
		}
	  fprintf(x, "#123%08X\r\n", csum);
	}
  fputs("\033\033o\r\n", x);
}

void
init_mem(void)
{
  init_list(&memblocks);
}

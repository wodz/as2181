/*
 *		ADSP 2181 Assembler -- List Functions
 *
 *		(c) 1996 Martin Mares, <mj@k332.feld.cvut.cz>
 *
 *		This software may be freely distributed and used according to the terms
 *		of the GNU General Public License. See file COPYING in any of the GNU utilities.
 */

#include <stdio.h>

#include "as2181.h"

void
add_tail(list *l, node *n)
{
node *z = l->tail.prev;
	n->next = &l->tail;
	n->prev = z;
	z->next = n;
	l->tail.prev = n;
}

void
add_head(list *l, node *n)
{
node *z = l->head.next;
	n->next = z;
	n->prev = &l->head;
	z->prev = n;
	l->head.next = n;
}

void
insert_node(node *n, node *after)
{
node *z = after->next;
	n->next = z;
	n->prev = after;
	after->next = n;
	z->prev = n;
}

void
rem_node(node *n)
{
node *z = n->prev;
node *x = n->next;
	z->next = x;
	x->prev = z;
}

void
init_list(list *l)
{
	l->head.next = &l->tail;
	l->head.prev = NULL;
	l->tail.next = NULL;
	l->tail.prev = &l->head;
}

void
add_tail_list(list *to, list *l)
{
node *p = to->tail.prev;
node *q = l->head.next;
	p->next = q;
	q->prev = p;
	q = l->tail.prev;
	q->next = &to->tail;
	to->tail.prev = q;
}

void *
new_node(int type, int len, int lin)
{
  struct pheader *p = xmalloc(len);

  p->type = type;
  p->flags = 0;
  p->line = lin;
  return (void *) p;
}

/* Checking */

int
check_list(list *l)
{
node *e, *n;
int cnt = 0;
	if (l->head.prev || l->tail.next)
		ierr("Inconsistent list header");
	e = &l->head;
	DO_FOR_ALL(n, *l)
		{
		cnt++;
		if (n->prev != e)
			ierr("Inconsistent back link");
		e=n;
		}
	if (l->tail.prev != e)
			ierr("Inconsistent list tail");
	return cnt;
}

/* Debugging dumps */

static ulg last_line;

static void
dump_memblock(struct memblock *m)
{
  printf("[%04x,%04x,%d,%d,%d]", m->addr, m->len, m->isprog, m->isram, m->iscirc);
}

static void
dump_node0(void *n)
{
  struct pheader *p = n;

  if (!n)
	{
	  printf("NIL");
	  return;
	}
  if (last_line != p->line)
	{
	  printf("@%d ", p->line);
	  last_line = p->line;
	}
  switch (p->type)
	{
	case N_LABEL:
	  {
		struct label *k = n;
		printf("LABEL(%s,%04x)", k->sym->name, k->addr);
		break;
	  }
	case N_INSN:
	  {
		struct insn *k = n;
		printf("INSN(%06x,%02x,%02x,", k->code, k->dest, k->comp);
		dump_node0(k->expr);
		putchar(')');
		break;
	  }
	case N_CONST:
	  {
		struct constant *k = n;
		printf("CONST(%s,%08x,", k->sym->name, k->value);
		dump_node0(k->expr);
		putchar(')');
		break;
	  }
	case N_VAR:
	  {
		struct var *k = n;
		int i;
		printf("VAR(%s,%d @%d,", k->sym->name, k->size, k->offs);
		dump_memblock(k->mem);
		printf(",{");
		if (k->init)
		  {
			for(i=0; i<k->size; i++)
			  {
				if (i)
				  putchar(' ');
				dump_node0(k->init->k[i]);
			  }
		  }
		printf("})");
		break;
	  }
	case N_MODULE:
	  {
		struct module *k = n;
		printf("MODULE(%s,", k->sym->name);
		dump_memblock(k->mem);
		printf(",{");
		dump_list(&k->insns);
		printf("})");
		break;
	  }
	case N_NUM:
	  {
		struct numeric *k = n;
		printf("NUM(%d)", k->value);
		break;
	  }
	case N_BINARY:
	  {
		struct binary *k = n;
		printf("BIN(%c,", k->op);
		dump_node0(k->l);
		putchar(',');
		dump_node0(k->r);
		putchar(')');
		break;
	  }
	case N_UNARY:
	  {
		struct unary *k = n;
		printf("UN(%c,", k->op);
		dump_node0(k->l);
		putchar(')');
		break;
	  }
	case N_SYMREF:
	  {
		struct symref *k = n;
		printf("SREF(%s)", k->sym->name);
		break;
	  }
	default:
	  printf("???");
	}
}

void
dump_node(void *k)
{
  last_line = ~1;
  dump_node0(k);
  putchar('\n');
}

void
dump_list(list *l)
{
  node *n;

  DO_FOR_ALL(n, *l)
	dump_node(n);
}

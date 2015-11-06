/*
 *		ADSP 2181 Assembler -- Expression Manipulations
 *
 *		(c) 1996 Martin Mares, <mj@k332.feld.cvut.cz>
 *
 *		This software may be freely distributed and used according to the terms
 *		of the GNU General Public License. See file COPYING in any of the GNU utilities.
 */

#include <stdlib.h>

#include "as2181.h"

int report_unresolved;

static node *
resolve_bin(node *n)
{
  DECL_NODE(b, binary, n);
  ulg x,y;
  node *a;

  x = resolve_expr(&b->l);				/* Cannot be combined to single if due to shortcut boolean evaluation */
  y = resolve_expr(&b->r);
  if (!x || !y)
	return n;
  x = NUMBER(b->l);
  y = NUMBER(b->r);
  switch (b->op)
	{
	case '+':
	  x += y; break;
	case '-':
	  x -= y; break;
	case '*':
	  x = (int) x * (int) y; break;
	case '/':
	  if (!y)
		{
		  clerr(b->line, "Division by zero");
		  x = 0;
		}
	  else
		x = (int) x / (int) y;
	  break;
	case '&':
	  x &= y; break;
	case '|':
	  x |= y; break;
	case '^':
	  x ^= y; break;
	case '<':
	  x <<= y; break;
	case '>':
	  x >>= y; break;
	default:
	  ilerr(b->line, "Unknown operation `%c'", b->op);
	}
  a = b->l;
  NUMBER(a) = x;
  free(b->r);
  free(b);
  return a;
}

static node *
resolve_un(node *n)
{
  DECL_NODE(b, unary, n);
  ulg x;
  node *a;

  if (b->op == '^' || b->op == '%')		/* Address / Length Operators */
	{
	  DECL_NODE(c, symref, b->l);
	  struct var *v;
	  struct numeric *d;

	  if (lino != ~0)					/* Parsing... */
		return n;
	  if (c->type != N_SYMREF || !c->sym || !c->sym->value || TYPE(c->sym->value) != N_VAR)
		{
		  clerr(b->line, "Variable reference expected for `%c'", b->op);
		  return n;
		}
	  v = (struct var *) c->sym->value;
	  if (report_unresolved)
		{
		  clerr(b->line, "Unresolvable `%c%s'", b->op, c->sym->name);
		  return n;
		}
	  if (b->op == '^')					/* "Take address" */
		x = v->offs + v->mem->addr;
	  else								/* "Take length" */
		x = v->size;
	  if (x == 0xffff)
		return n;
	  free(c);
	  d = NEW_NODE(numeric, N_NUM);
	  a = NODE d;
	  goto replace;
	}

  if (!resolve_expr(&b->l))
	return n;
  x = NUMBER(b->l);
  switch (b->op)
	{
	case '|':
	  if ((int) x >= 0)
		break;
	  /* Fall-thru */
	case '-':
	  x = -x; break;
	case '~':
	  x = ~x; break;
	default:
	  ilerr(b->line, "Unknown operation `%c'", b->op);
	}
  a = b->l;
replace:
  NUMBER(a) = x;
  free(b);
  return a;
}

node *
resolve_sr(node *n)
{
  DECL_NODE(b, symref, n);
  struct symbol *s;
  node *r;
  ulg m;
  struct numeric *x;

 retry:
  s = b->sym;
  r = s->value;
  if (!r)								/* Undefined */
	{
	  if (lino == ~0)					/* End of syntax analysis */
		clerr(b->line, "Undefined symbol `%s'", s->name);
	  return n;
	}
  if (report_unresolved)
	{
	  clerr(b->line, "Unresolved reference to `%s'", s->name);
	  return n;
	}
  switch (TYPE(r))
	{
	case N_LABEL:
	  {
		struct label *l = (struct label *) r;
		if (l->addr == 0xffff)
		  return n;
		m = l->addr;
		break;
	  }
	case N_CONST:
	  {
		struct constant *c = (struct constant *) r;
		if (c->expr)
		  return n;
		m = c->value;
		break;
	  }
	case N_VAR:
	  {
		struct var *v = (struct var *) r;
		if (v->mem->addr == 0xffff)
		  return n;
		m = v->mem->addr + v->offs;
		break;
	  }
	case N_SYMREF:
	  {
		b = (struct symref *) r;
		goto retry;
	  }
	default:
	  cerr("Invalid symbol reference to `%s'", s->name);
	  return n;
	}
  x = NEW_NODE(numeric, N_NUM);
  x->value = m;
  free(n);
  return NODE x;
}

int
resolve_expr(node **m)
{
  switch (TYPE(*m))
	{
	case N_NUM:
	  return 1;
	case N_BINARY:
	  *m = resolve_bin(*m);
	  break;
	case N_UNARY:
	  *m = resolve_un(*m);
	  break;
	case N_SYMREF:
	  *m = resolve_sr(*m);
	  break;
	default:
#ifdef DEBUG
	  dump_node(m);
#endif
	  ilerr(LINE(*m), "Invalid expression in resolve_expr");
	}
  return (TYPE(*m) == N_NUM);
}

ulg
expr_to_num(node *n)
{
  ulg k;

  if (TYPE(n) != N_NUM)
	{
#ifdef DEBUG
	  dump_node(n);
#endif
	  ilerr(LINE(n), "expr_to_num called for a non-number");
	}
  k = NUMBER(n);
  free(n);
  return k;
}

int
resolve_const(struct constant *c)
{
  if (!c->expr || !resolve_expr(&c->expr))
	return 0;
  c->value = expr_to_num(c->expr);
  c->expr = NULL;
  return 1;
}

static void
subst_ins_arg(struct insn *i, ulg a)
{
  switch (i->flags)
	{
	case IF_IMM16:
	  if ((int) a >= 65536 || (int) a < -32768)
		clerr(i->line, "Immediate out of range");
	  a &= 0xffff;
	  break;
	case IF_IMM14:
	case IF_IMM14X:
	  if ((int) a >= 16384 || (int) a < -8192)
		clerr(i->line, "Address out of range");
	  a &= 0x3fff;
	  if (i->flags == IF_IMM14X)
		{
		  i->code |= ((a >> 10) & 0xc) | ((a & 0xfff) << 4);
		  return;
		}
	  break;
	case IF_IMM11:
	  if ((int) a >= 2048 || (int) a < -1024)
		clerr(i->line, "Port out of range");
	  a &= 0x7ff;
	  break;
	default:
	  ilerr(i->line, "Invalid subst_in_arg");
	}
  i->code |= a << 4;
}

int
resolve_insn(struct insn *i)
{
  if (!i->expr || !resolve_expr(&i->expr))
	return 0;
  subst_ins_arg(i, expr_to_num(i->expr));
  i->expr = NULL;
  return 1;
}

void									/* Resolve all expressions */
do_exprs(void)
{
  int conv;								/* Convergence flag */
  int div;								/* Divergence flag */
  struct constant *c;
  struct insn *i;
  struct module *m;

  for(;;)
	{
	  conv = 0;
	  div = 0;
	  DO_FOR_ALL(c, constlist)
		if (c->expr)
		  {
			div = 1;
			if (resolve_const(c))
			  conv = 1;
		  }
	  DO_FOR_ALL(m, modules)
		DO_FOR_ALL(i, m->insns)
		  if (i->type == N_INSN && i->expr)
			{
			  div = 1;
			  if (resolve_insn(i))
				conv = 1;
			}
	  errstop();
	  if (!div)							/* Everything resolved */
		break;
	  if (report_unresolved)
		ierr("Unannounced && unresolved symbols found");
	  if (!conv)
		report_unresolved = 1;
	}
  if (debug & DEBUG_RESOLVED_PROG)
	dump_list(&modules);
  if (debug & DEBUG_RESOLVED_CONSTS)
	dump_list(&constlist);
}

/* Hey, Emacs, this is not -*- C -*-, but it should look like as it were...
 *
 *		ADSP 2181 Assembler -- Syntax Analysis
 *
 *		(c) 1996 Martin Mares, <mj@k332.feld.cvut.cz>
 *
 *		This software may be freely distributed and used according to the terms
 *		of the GNU General Public License. See file COPYING in any of the GNU utilities.
 */

%{
#include <string.h>
#include <stdlib.h>

#include "as2181.h"

#define yyerror(x) cerr(x)

struct glue {
  ulg x,y,z,a,t;
};

struct insar {							/* Instruction array */
  ulg cnt;
  void *i[16];
  byte type[16];
};

list modules, varlist, constlist;
ulg src_lines;
struct module *thismod;

static void end_of_file(void);
static void *add_unary(int, node *);
static void *add_binary(int, node *, node *);
static void symdef(struct symbol *, struct symbol **, node *);
static struct insn *alu_op(ulg, ulg, ulg, ulg);
static struct insn *alloc_insn(ulg, ulg);
static ulg reg_set(ulg, ulg *);
static struct glue *new_glue(void);
static ulg resolve_aluc(ulg, int);
static struct insn *alu_num(ulg, ulg, ulg);
static struct insn *alu_addi(ulg, ulg, ulg);
static ulg std_reg(ulg);
static ulg d_reg(ulg);
static ulg negate_cond(ulg);
static struct insn *insn_chain(struct insar *);
static struct insar *init_ichain(void);

static ulg alux_regs[] = { R_AX0, R_AX1, R_AR, R_MR0, R_MR1, R_MR2, R_SR0, R_SR1, ~0 };
static ulg aluy_regs[] = { R_AY0, R_AY1, R_AF, ~0 };
static ulg macx_regs[] = { R_MX0, R_MX1, R_AR, R_MR0, R_MR1, R_MR2, R_SR0, R_SR1, ~0 };
static ulg macy_regs[] = { R_MY0, R_MY1, R_MF, ~0 };
static ulg shix_regs[] = { R_SI, ~1, R_AR, R_MR0, R_MR1, R_MR2, R_SR0, R_SR1, ~0 };
static ulg xferd_regs[] = { R_AX0, R_AX1, R_MX0, R_MX1, ~0 };
static ulg xferp_regs[] = { R_AY0, R_AY1, R_MY0, R_MY1, ~0 };

#define IS_ALU_YOP(r) (reg_set(r, aluy_regs) != ~0)
#define IS_POWER_OF_2(x) ((x) && !((x) & ((x) - 1)))
%}

%union {
  int i;
  struct symbol *s;
  node *n;
  struct memblock *m;
  struct var *v;
  struct glue *g;
  struct insn *a;
  struct insar *r;
}

/* Tokens */

%token GOT_EOF CARRY AND OR XOR IF PASS NOT ABS DIVS DIVQ TSTBIT DM PM IO OF
%token SETBIT CLRBIT TGLBIT ASHIFT LSHIFT NORM EXP EXPADJ BY DMOVLAY DO NONE
%token UNTIL JUMP CALL FLAG_IN NOT RTS RTI IDLE NOP MODIFY PUSH POP SET CONST SR
%token RESET TOGGLE ENA DIS FOREVER MODULE VAR ROM RAM ENDMOD CIRC LL RR INIT MR MF
%token INTS SAT ENTRY EXTERNAL GLOBAL
%token <i> NUM REG COND MACCLASS SHCLASS FLAG POPREG ENADISREG
%token <s> SYM

/* Non-terminal typed symbols */

%left OR XOR
%left AND
%left '+' '-'
%left '*' '/'
%nonassoc LL RR
%left 'U' NOT ABS '^' '%'

%type <i> romram varsize alucomm pmdm carried regplus regminus nexpr bitop mrormf mrpm macr
%type <i> regeq mayshor shifter calljump enadis srt cond ucond maybenot popreg pmdml
%type <n> expr insn label ioref
%type <m> memattr memattra memattrb var varstart
%type <v> init inita
%type <a> alu alur iins mac macrs macmul shift shreg shrega spec
%type <g> pdxfer regxfer memref gins iff
%type <r> ichain jchain
%type <s> consym

%%

main:
   /* empty */
 | main GOT_EOF {						/* End of file */
	 end_of_file();
	 return 0;
   }
| error ';' {							/* Error recovery */
     yyerrok;
  }
| error GOT_EOF {
     end_of_file();
     return 1;
  }
| main pseudo ';'
| main insn {
     if (!thismod)
   	   err("Instruction encountered outside module");
	 if ($2)
	   add_tail(&thismod->insns, $2);
  }
;

/* Pseudoinstructions */

pseudo:
   module
 | var { }
 | init { }
 | endmod
 | constant
 | global
 | external
 | unsupp { warn("Directive not supported"); }
   ;

global:
   globala SYM {
	 if (!$2->scope)
	   cerr("Symbol `%s' is already declared global", $2->name);
	 else
	   expose_symbol($2);
   }
   ;

globala:
   global ','
 | ENTRY
   ;

external:								/* In our implementation, every global is automatically imported. */
   external ',' SYM						/* Therefore the EXTERNAL directive is ignored. */
 | EXTERNAL SYM
   ;

unsupp:
   GLOBAL SYM
 | unsupp ',' SYM
   ;

init:
   inita expr {
      struct init *i;
	  $$ =$1;
	  if ($1)
		{
		  i = $1->init;
		  if (i->current >= $1->size)
			{
			  cerr("Excess elements in initializer");
			  $$ = NULL;
			}
		  else
			{
			  node *z = $2;
			  resolve_expr(&z);
			  i->k[i->current++] = z;
			}
		}
   }
   ;

inita:
   INIT SYM varsize ':' {
      if (!$2->value || TYPE($2->value) != N_VAR)
		{
		  cerr("`%s' expected to be a variable", $2->name);
		  $$ = NULL;
		}
	  else
		{
		  struct var *v = (struct var *) $2->value;
		  ulg s = ($3 == -1) ? 0 : $3;
		  struct init *i = v->init;

		  if (!i)
			{
			  i = v->init = xmalloc(sizeof(struct init) + (v->size-1) * sizeof(node *));
			  bzero(i->k, v->size * sizeof(node *));
			}
		  i->current = s;
		  $$ = v;
		}
	}
 | init ','
    ;

constant:
   consym '=' expr {
	 struct constant *m = NEW_NODE(constant, N_CONST);
	 symdef($1, &m->sym, NODE m);
	 m->expr = $3;
	 resolve_const(m);
	 add_tail(&constlist, &m->n);
   }
   ;

consym:
   CONST SYM { $$ = $2; }
 | constant ',' SYM { $$ = $3; }
   ;

module:
   MODULE memattr SYM { 
	 struct module *n = NEW_NODE(module, N_MODULE);
	 DECL_NODE(m, memblock, $2);
	 if (thismod)
	   cerr("Module nesting not possible");
	 if (!m->isprog)
	   cerr("Modules must reside in program memory");
	 else if (m->isprog == 0xff)
	   m->isprog = 1;
	 symdef($3, &n->sym, NODE n);
	 m->sym = $3;
	 n->mem = m;
	 init_list(&n->insns);
	 add_tail(&modules, NODE n);
	 expose_symbol(m->sym);
	 thismod = n;
   }
   ;

endmod:
   ENDMOD {
	  if (!thismod)
		cerr("Closing unopened module");
	  else
		thismod = NULL;
	}
    ;

var:
   varstart SYM varsize {
	  struct var *v = NEW_NODE(var, N_VAR);
	  symdef($2, &v->sym, NODE v);
	  if (!$1->sym)
		$1->sym = $2;
	  v->mem = $1;
	  v->size = ($3 == -1) ? 1 : $3;
	  if (!v->size)
		{
		  cerr("Zero-sized arrays not allowed");
		  v->size = 1;
		}
	  v->offs = v->mem->len;
	  v->mem->len += v->size;
	  v->init = NULL;
	  add_tail(&varlist, NODE v);
	  $$ = $1;
   }
   ;

varstart:
   VAR memattr {
	 $2->len = 0;
	 if ($2->isprog == 0xff)
	   $2->isprog = 0;
	 $$ = $2;
   }
 | var ','
   ;

varsize:
   /* empty */ { $$ = -1; }
 | '[' expr ']' {
     node *ex = $2;
	 if (!resolve_expr(&ex))
	   {
		 cerr("Array size must be constant");
		 $$ = 1;
	   }
	 else
	   $$ = expr_to_num(ex);
   }
   ;

memattra:
   /* empty */ {
	 struct memblock *mem = new_memblock();
	 $$ = mem;
   }
 | memattra '/' romram {
     DECL_NODE(l, memblock, $1);
	 if (l->isram != 0xff)
	   cerr("ROM/RAM already specified");
	 l->isram = $3;
	 $$ = $1;
   }
 | memattra '/' pmdm {
      DECL_NODE(l, memblock, $1);
	  if (l->isprog != 0xff)
		cerr("PM/DM already specified");
	  l->isprog = $3;
	  $$ = $1;
	}
 | memattra '/' CIRC {
      DECL_NODE(l, memblock, $1);
	  l->iscirc = 1;
	  $$ = $1;
	}
    ;

memattrb:
   memattra
 | memattra '/' ABS '=' expr {
      DECL_NODE(l, memblock, $1);
	  node *ex = $5;
	  if (l->addr != 0xffff)
		cerr("Address already specified");
	  if (!resolve_expr(&ex))
		cerr("Address expression must be constant");
	  else
		l->addr = expr_to_num(ex);
	  $$ = $1;
	}

memattr:
   memattrb {
	  DECL_NODE(l, memblock, $1);
	  if (l->isram)
		l->isram = 1;
	  $$ = $1;
	}
    ;

romram:
   ROM { $$ =  0; }
 | RAM { $$ = 1; }
   ;

/* Instructions */

insn:
   label
 | ichain ';' { $$ = NODE insn_chain($1); }
   ;

label:
   SYM ':' {
	 struct label *n = NEW_NODE(label, N_LABEL);
	 symdef($1, &n->sym, NODE n);
	 n->addr = ~0;
	 $$ = NODE n;
   }
   ;

ichain:
   iins {
	 struct insar *i = init_ichain();
	 i->type[0] = $1->comp;
	 i->i[0] = $1;
	 $$ = i;
   }
 | gins {
     struct insar *i = init_ichain();	/* Looks the same, but differs! */
     i->type[0] = $1->t;
	 i->i[0] = $1;
	 $$ = i;
   }
 | jchain iins {
     if ($1->cnt > 15)
	   cerr("Instruction chain too long");
	 else
	   {
		 $1->type[$1->cnt] = $2->comp;
		 $1->i[$1->cnt++] = $2;
	   }
   }
 | jchain gins {						/* Grrrr... */
     if ($1->cnt > 15)
	   cerr("Instruction chain too long");
	 else
	   {
		 $1->type[$1->cnt] = $2->t;
		 $1->i[$1->cnt++] = $2;
	   }
   }
   ;

jchain:
   ichain ','
 | iff {
     struct insar *i = init_ichain();
     i->type[0] = $1->t;
	 i->i[0] = $1;
	 $$ = i;
   }
   ;

iins:									/* Instructions returning "struct insn *" */
   alu
 | mac
 | shift
 | spec
   ;

gins:									/* Instructions returning "struct glue *" */
   pdxfer
 | regxfer
   ;

/* IF's */

iff:
   IF cond {
	 struct glue *g = new_glue();
	 g->t = IC_IF;
	 g->x = $2;
	 g->a = ~0;
	 if ($2 == C_CE)
	   cerr("Invalid IF condition");
	 $$ = g;
   }
 | IF maybenot FLAG_IN {
     struct glue *g = new_glue();
	 g->t = IC_IFFLAG;
	 g->x = $2;
	 g->a = ~0;
	 $$ = g;
   }
   ;

maybenot:
   /* empty */ { $$ = 0; }
 | NOT { $$ = 1; }
   ;

/* P/D Memory Xfer group */

pdxfer: regeq memref {
   $2->a = $1;
   $2->t = IC_MEMF;
   $$ = $2;
   }
 | memref '=' REG {
   $1->a = $3;
   $1->t = IC_MEMS;
   $$ = $1;
   }
   ;

memref: pmdml REG ',' REG ')' {
  struct glue *g = new_glue();
  g->x = $1;
  g->y = $2;
  g->z = $4;
  $$ = g;
  }
  ;

pmdml:
   pmdm '('
   ;

pmdm:
   PM { $$ = 1; }
 | DM { $$ = 0; }
   ;

/* Register transfer group */

regxfer: regeq REG {
   struct glue *g = new_glue();
   g->x = std_reg($1);
   g->y = std_reg($2);
   g->t = IC_MOVE;
   $$ = g;
   }
   ;

/* ALU */

alu:
   regeq alur {
      if ($1 != R_AR && $1 != R_AF)
		cerr("ALU destination must be AR or AF");
	  if ($1 == R_AF)
		  $2->code |= 0x040000;
	  $2->dest = $1;
	  $$ = $2;
	}
 | NONE '=' alur {						/* Discard */
	  if ($3->code & 0x0000ff)
            cerr("Invalid NONE = <ALU> operation");
	  $3->code = ($3->code & 0x01ff00) | 0x2a00aa;
	  $3->comp = IC_INCOMP;
	  $$ = $3;
	}
 | DIVS REG ',' REG {					/* Division */
      struct insn *i = alloc_insn(0x060000, IC_INCOMP);
	  ulg a,b;
	  if ((a = reg_set($2, aluy_regs)) == ~0 || $2 == R_AY0 || (b = reg_set($4, alux_regs)) == ~0)
		{
		  cerr("Invalid argument of DIVS");
		  a = 0; b = 0;
		}
	  i->code |= (b << 8) | (a << 11);
	  $$ = i;
	}
 | DIVQ REG {
      struct insn *i = alloc_insn(0x071000, IC_INCOMP);
	  ulg a;
	  if ((a = reg_set($2, alux_regs)) == ~0)
		cerr("Invalid argument of DIVQ");
	  i->code |= (a << 8);
	  $$ = i;
	}
   ;

alur:
   REG alucomm REG { $$ = alu_op($1, $3, $2, $2); }
 | regplus REG { $$ = alu_op($1, $2, 3, 3); }
 | regplus carried { $$ = alu_op($1, $2, 2, 2); }
 | regminus REG { $$ = alu_op($1, $2, 7, 9); }
 | regminus REG '+' CARRY '-' NUM {
      if ($6 != 1)
		cerr("1 expected instead of %d", $6);
	  $$ = alu_op($1, $2, 6, 10);
	}
 | PASS REG {
      if (IS_ALU_YOP($2))				/* Here begin dirty tricks */
		$$ = alu_op(~0, $2, 0, ~0);
	  else
		$$ = alu_op($2, ~0, 3, ~0);		/* ADD 0 */
	}
 | '-' REG {
      if (IS_ALU_YOP($2))
		$$ = alu_op(~0, $2, 5, ~0);
	  else
		$$ = alu_op($2, ~0, 9, ~0);
	}
 | NOT REG {
      if (IS_ALU_YOP($2))
		$$ = alu_op(~0, $2, 4, ~0);
	  else
		$$ = alu_op($2, R_AY0, 11, ~0);	/* R_AY0 instead of ~0 to be binary compatible with original assembler */
	}
 | ABS REG { $$ = alu_op($2, R_AY0, 15, ~0); } /* Here too */
 | regplus nexpr { $$ = alu_addi($1, $2, 0); }
 | regminus nexpr { $$ = alu_addi($1, -$2, 1); }
 | PASS nexpr {
      ulg k = $2;
	  if (k == 0)
		$$ = alu_op(R_AX0, ~0, 0, ~0);	/* PASS 0 */
	  else if (k == ~0)
		$$ = alu_op(R_AX0, ~0, 8, ~0);	/* PASS ~0 */
	  else if (k == 1)
		$$ = alu_op(R_AX0, ~0, 1, ~0);	/* PASS 1 */
	  else if ((k = resolve_aluc($2, 1)) != ~0)
		$$ = alu_num(R_AX0, k, 0);		/* PASS y */
	  else if ((k = resolve_aluc($2 + 1, 1)) != ~0)
		$$ = alu_num(R_AX0, k, 8);		/* DEC y */
	  else
		{
		  k = resolve_aluc($2 - 1, 0);
		  $$ = alu_num(R_AX0, k, 1);	/* INC y */
		}
	}
 | bitop nexpr OF REG {
      ulg aflag = $1 & 0x80;
	  ulg op = $1 & 0x7f;
	  ulg bit = 1<<$2;

	  if ($2 >= 16 || $2 < 0)
		cerr("Invalid bit number");
	  $$ = alu_num($4, resolve_aluc(aflag ? ~bit : bit, 0), op);
	}
   ;

carried:
   regplus CARRY { $$ = $1; }
 | CARRY { $$ = ~0; }
   ;

regplus:
   REG '+' { $$ = $1; }
   ;

regminus:
   REG '-' { $$ = $1; }
   ;

alucomm:
   AND { $$ = 12; }
 | OR { $$ = 13; }
 | XOR { $$ = 14; }
   ;

bitop:
   TSTBIT { $$ = 12; }
 | SETBIT { $$ = 13; }
 | CLRBIT { $$ = 0x8c; }
 | TGLBIT { $$ = 14; }
   ;

regeq:
   REG '=' { $$ = $1; }
   ;

nexpr: expr {
   node *n = $1;
   if (!resolve_expr(&n))
	 {
	   cerr("Absolute expression expected");
	   $$ = 0;
	 }
   else
	 $$ = expr_to_num(n);
   }
   ;

/* MAC */

mac:
   mrormf '=' macrs {
	 $3->code |= $1;
	 $$ = $3;
   }
   ;

mrormf:
   MR { $$ = 0; }
 | MF { $$ = 0x240000; }
   ;

macrs:
   macmul {
	 ulg op = ($1->code & 0x01e000) >> 13;
	 if (op < 4)
	   op += 4;
	 else
	   op = 1;
	 $1->code = ($1->code & 0xfe1fff) | (op << 13);
	 $$ = $1;
   }
 | mrpm macmul {
     ulg op = ($2->code & 0x01e000) >> 13;
	 if (op < 4)
	   op |= (8 + $1);
	 else
	   op = 2 + ($1 >> 2);
	 $2->code = ($2->code & 0xfe1fff) | (op << 13);
	 $$ = $2;
   }
 | MR { $$ = alloc_insn(0x211800, IC_MAC); }
 | MR MACCLASS {
      if ($2 != MC_RND)
		cerr("Only (RND) allowed here");
	  $$ = alloc_insn(0x205800, IC_MAC);
	}
 | expr {
      node *n = $1;
	  if (!resolve_expr(&n) || expr_to_num(n))
		cerr("Only zero may be used here");
	  $$ = alloc_insn(0x209800, IC_MAC);
	}
   ;

mrpm:
   MR '+' { $$ = 0; }
 | MR '-' { $$ = 4; }
   ;

macmul:
   REG '*' macr MACCLASS {
      struct insn *i = alloc_insn(0x200000, IC_MAC);
	  ulg a,b;
	  a = reg_set($1, macx_regs);
	  b = reg_set($3, macy_regs);
	  if (a != ~0 && b != ~0)			/* Standard multiplication */
		i->code |= (a << 8) | (b << 11);
	  else if (a != ~0 && (b = reg_set($3, macx_regs)) != ~0 && a == b)
		{								/* Square */
		  if ($4 != MC_SS && $4 != MC_UU && $4 != MC_RND)
			cerr("Only SS, SU and RND modes may be used for square operation");
		  i->code |= (a << 8) | 0x10;
		  i->comp = IC_ICMAC;
		}
	  else
		cerr("Invalid multiplication");
	  i->code |= ($4 << 13);
	  $$ = i;
   }
   ;

macr:
   REG { $$ = $1; }
 | MF { $$ = R_MF; }
   ;

/* Shifter */

shift:
   SR '=' mayshor shifter shrega SHCLASS {
	 if ($6 == SC_HIX)
	   cerr("(HIX) not allowed here");
	 $5->code |= ($4 << 13) | ($6 << 12) | $3;
	 $$ = $5;
   }
 | regeq EXP shreg SHCLASS {
	 if ($1 != R_SE)
	   cerr("Destination of EXP must be the SE register");
     if ($4 == SC_HIX)
	   $3->code |= 0x800;
	 else
	   $3->code |= ($4 << 12);
	 $3->code |= 0x006000;
	 $$ = $3;
   }
 | regeq EXPADJ shreg {
     if ($1 != R_SB)
	   cerr("Destination of EXPADJ must be the SB register");
	 $3->code |= 0x007800;
	 $$ = $3;
   }
 | SAT MR { $$ = alloc_insn(0x050000, IC_SAT); }
   ;

shreg:
   REG {
	 struct insn *i = alloc_insn(0x0e0000, IC_SHIFT);
	 ulg r = reg_set($1, shix_regs);
	 if (r == ~0)
	   cerr("Invalid register for shifter operation");
     i->code |= (r << 8);
     $$ = i;
   }
   ;

shrega:
   shreg
 | shreg BY expr {
      node *n = $3;
	  ulg c;

	  if (!resolve_expr(&n))
		{
		  cerr("Shift count must be an absolute constant");
		  c = 0;
		}
	  else
		{
		  c = expr_to_num(n);
		  if ((int) c < -128 || (int) c > 127)
			cerr("Shift count out of range");
		}
	  $1->code |= 0x010000 | (c & 0xff);
	  $1->comp = IC_INCOMP;
	  $$ = $1;
   }

shifter:
   ASHIFT { $$ = 1; }
 | LSHIFT { $$ = 0; }
 | NORM { $$ = 2; }
   ;

mayshor:
   /* empty */ { $$ = 0; }
 | SR OR { $$ = 0x800; }
   ;

/* Special instructions */

spec:
   regeq DMOVLAY {
	 $$ = alloc_insn(0x0d010f, IC_INCOMP);
	 $$->code |= (d_reg($1) << 4);
   }
 | DMOVLAY '=' REG {
     $$ = alloc_insn(0x0d04f0, IC_INCOMP);
	 $$->code |= d_reg($3);
   }
 | regeq expr {
     struct insn *i = alloc_insn(0x400000, IC_INCOMP);
	 i->expr = $2;
	 if ($1 < 16)						/* DREG */
	   {
		 i->flags = IF_IMM16;
		 i->code |= $1;
	   }
	 else
	   {
		 ulg k = std_reg($1);
		 i->flags = IF_IMM14;
		 i->code = (k & 0x0f) | ((k & 0x30) << 14) | 0x300000;
	   }
	 $$ = i;
   }
 | regeq ioref {
     struct insn *i = alloc_insn(0x010000, IC_INCOMP);
	 i->flags = IF_IMM11;
	 i->expr = $2;
	 i->code |= d_reg($1);
	 $$ = i;
   }
 | ioref '=' REG {
     struct insn *i = alloc_insn(0x018000, IC_INCOMP);
	 i->flags = IF_IMM11;
	 i->expr = $1;
	 i->code |= d_reg($3);
	 $$ = i;
   }
 | NOP { $$ = alloc_insn(0, IC_INCOMP); }
 | IDLE { $$ = alloc_insn(0x028000, IC_INCOMP); }
 | IDLE expr {
      struct insn *i = alloc_insn(0x028000, IC_INCOMP);
      node *n = $2;
	  if (!resolve_expr(&n))
		cerr("IDLE argument must be an absolute expression");
	  else
		{
		  ulg m = expr_to_num(n);
		  if (m == 16 || m == 32 || m == 64 || m == 128)
			i->code |= m >> 4;
		  else
			cerr("IDLE argument must be 16, 32, 64 or 128");
		}
	  $$ = i;
	}
 | MODIFY '(' REG ',' REG ')' {
      struct insn *i = alloc_insn(0x090000, IC_INCOMP);
	  if ($3 >= R_I0 && $3 <= R_I3 && $5 >= R_M0 && $5 <= R_M3)
		i->code |= ($5 - R_M0) | (($3 - R_I0) << 2);
	  else if ($3 >= R_I4 && $3 <= R_I7 && $5 >= R_M4 && $5 <= R_M7)
		i->code |= ($5 - R_M4) | (($3 - R_I4) << 2) | 0x10;
	  else
		cerr("Invalid register combination for MODIFY");
	  $$ = i;
	}
 | PUSH popreg {
      $$ = alloc_insn(0x040002, IC_PUSHPOP);
	  if ($2 != PP_STS)
		cerr("Only STS may be pushed");
	}
 | POP popreg { $$ = alloc_insn(0x040000 | $2, IC_PUSHPOP); }
 | enadis INTS {
      $$ = alloc_insn(0x040040, IC_INCOMP);
	  if ($1)
		$$->code |= 0x20;
	}
 | enadis ENADISREG {
      $$ = alloc_insn(0x0c0000 | $2, IC_ENADIS);
	  if ($1)
		$$->code |= ($2 >> 1);
	}
 | srt FLAG { $$ = alloc_insn(0x020000 + ($1 << $2), IC_FLAGS); }
 | DO expr ucond {
      struct insn *i = alloc_insn(0x140000, IC_INCOMP);
	  i->expr = $2;
	  i->flags = IF_IMM14;
	  i->code |= $3;
	  $$ = i;
	}
 | RTS { $$ = alloc_insn(0x0a0000, IC_IFIN); }
 | RTI { $$ = alloc_insn(0x0a0010, IC_IFIN); }
 | calljump '(' REG ')' {
      struct insn *i = alloc_insn(0x0b0000, IC_IFIN);
	  if ($3 < R_I4 || $3 > R_I7)
		cerr("CALL/JUMP allowed only for I4 to I7");
	  else
		i->code |= (($3 - R_I4) << 6) | ($1 << 4);
	  $$ = i;
	}
 | calljump expr {
      struct insn *i = alloc_insn($1 ? 0x1c0000 : 0x180000, IC_JUMP);
	  i->expr = $2;
	  i->flags = IF_IMM14;
	  $$ = i;
	}
 | regeq pmdml expr ')' {
      struct insn *i = alloc_insn(0x800000, IC_INCOMP);
      int reg = std_reg($1);
	  i->code |= (reg & 0x0f) | ((reg & 0x30) << 14);
	  i->expr = $3;
	  i->flags = IF_IMM14;
	  if ($2)
		cerr("Only DM allowed here");
	  $$ = i;
	}
 | pmdml expr ')' '=' REG {
      struct insn *i = alloc_insn(0x900000, IC_INCOMP);
      int reg = std_reg($5);
	  i->code |= (reg & 0x0f) | ((reg & 0x30) << 14);
	  i->expr = $2;
	  i->flags = IF_IMM14;
	  if ($1)
		cerr("Only DM allowed here");
	  $$ = i;
	}
 | memref '=' expr {
      struct insn *i = alloc_insn(0xa00000, IC_INCOMP);
	  struct glue *g = $1;

	  if (g->x)
		cerr("Only DM can be used for the `store immediate' operation");
	  if (g->y >= R_I0 && g->y <= R_I3 && g->z >= R_M0 && g->z <= R_M3)
		i->code |= ((g->y - R_I0) << 2) | (g->z - R_M0);
	  else if (g->y >= R_I4 && g->y <= R_I7 && g->z >= R_M4 && g->z <= R_M7)
		i->code |= 0x100000 | ((g->y - R_I4) << 2) | (g->z - R_M4);
	  else
		cerr("Invalid register combination for DM transfer");
	  i->expr = $3;
	  i->flags = IF_IMM16;
	  free(g);
	  $$ = i;
	}
   ;

popreg:
   POPREG
 | REG {
      if ($1 == R_CNTR)
	     $$ = PP_CNTR;
	  else
		cerr("Invalid register for PUSH/POP");
	}
   ;

ucond:
   UNTIL cond {
	 $$ = negate_cond($2);
	 if ($$ > 15)
		cerr("Invalid condition for DO UNTIL");
   }
 | /* empty */ { $$ = C_TRUE; }
 | UNTIL FOREVER { $$ = C_TRUE; }
   ;

srt:
   SET { $$ = 3; }
 | RESET { $$ = 2; }
 | TOGGLE { $$ = 1; }
   ;

ioref:
   IO '(' expr ')' { $$ = $3; }
   ;

calljump:
   CALL { $$ = 1; }
 | JUMP { $$ = 0; }
   ;

enadis:
   ENA { $$ = 1; }
 | DIS { $$ = 0; }
   ;

cond:
   COND { $$ = $1; }
 | NOT COND { $$ = negate_cond($2); }
   ;

/* Expressions */

expr:
   NUM {
	 struct numeric *n = NEW_NODE(numeric, N_NUM);
	 n->value = $1;
	 $$ = NODE n;
   }
 | '(' expr ')' {
     $$ = $2;
   }
 | expr '+' expr { $$ = add_binary('+', $1, $3); }
 | expr '-' expr { $$ = add_binary('-', $1, $3); }
 | expr '*' expr { $$ = add_binary('*', $1, $3); }
 | expr '/' expr { $$ = add_binary('/', $1, $3); }
 | expr AND expr { $$ = add_binary('&', $1, $3); }
 | expr OR  expr { $$ = add_binary('|' , $1, $3); }
 | expr XOR expr { $$ = add_binary('^', $1, $3); }
 | expr LL  expr { $$ = add_binary('<' , $1, $3); }
 | expr RR  expr { $$ = add_binary('>' , $1, $3); }
 | '-' expr %prec 'U' { $$ = add_unary('-', $2); }
 | NOT expr { $$ = add_unary('~', $2); }
 | ABS expr { $$ = add_unary('|', $2); }
 | '^' expr { $$ = add_unary('^', $2); }
 | '%' expr { $$ = add_unary('%', $2); }
 | SYM {
    struct symref *n = NEW_NODE(symref, N_SYMREF);
	n->sym = $1;
	$$ = NODE n;
  }
   ;

%%

void
init_syn(void)
{
  init_list(&modules);
  init_list(&varlist);
  init_list(&constlist);
}

static void
end_of_file(void)
{
  if (thismod)
	cerr("Module `%s' not closed", thismod->sym->name);
  src_lines = lino;
  lino = ~0;
  if (debug & DEBUG_PARSE_PROG)
	{
	  puts("Program after parsing:");
	  dump_list(&modules);
	}
  if (debug & DEBUG_PARSE_CONST)
	{
	  puts("Constants:");
	  dump_list(&constlist);
	}
  if (debug & DEBUG_PARSE_VAR)
	{
	  puts("Variables:");
	  dump_list(&varlist);
	}
  errstop();
}

static void *
add_unary(int op, node *l)
{
  struct unary *u = NEW_NODE(unary, N_UNARY);
  u->op = op;
  u->l = l;
  return u;
}

static void *
add_binary(int op, node *l, node *r)
{
  struct binary *u = NEW_NODE(binary, N_BINARY);
  u->op = op;
  u->l = l;
  u->r = r;
  return u;
}

static void
symdef(struct symbol *s, struct symbol **k, node *n)
{
  if (s->value)
	cerr("Symbol `%s' already defined", s->name);
  else
	s->value = n;
  *k = s;
}

static ulg
reg_set(ulg r, ulg *i)
{
  ulg c = 0;
  while (*i != ~0 && *i != r)
	i++, c++;
  return (*i == ~0) ? *i : c;
}

static struct insn *
alloc_insn(ulg code, ulg class)
{
  struct insn *i = NEW_NODE(insn, N_INSN);
  i->code = code;
  i->comp = class;
  i->dest = ~0;
  i->expr = NULL;
  return i;
}

static struct insn *
alu_op(ulg x, ulg y, ulg xo, ulg yo)
{
  ulg k,l;
  struct insn *i = alloc_insn(0x220000, IC_ALU);

  if (x == ~0)
	k = 0;
  else
	k = reg_set(x, alux_regs);
  if (k == ~0)
	{
	  if (y != ~0)
		{
		  l = reg_set(x, aluy_regs);
		  k = reg_set(y, alux_regs);
		  xo = yo;
		  if (k == ~0 || l == ~0)
			goto bad;
		}
	  else
		goto bad;
	}
  else if (y != ~0)
	{
	  l = reg_set(y, aluy_regs);
	  if (l == ~0)
		goto bad;
	}
  else
	l = 3;
  i->code |= (k << 8) | (l << 11) | (xo << 13);
  return i;

 bad:
  cerr("Invalid combination of registers for ALU operation");
  return i;
}

static struct glue *
new_glue(void)
{
  return xmalloc(sizeof(struct glue));
}

static ulg								/* Expecting power of two! */
binary_log(ulg x)
{
  ulg k = 0xffff;
  ulg d = 16;
  ulg l = 0;

  while (d)
	{
	  if (!(x & (k << l)))
		l += d;
	  d >>= 1U;
	  k >>= d;
	}
  return l;
}

static ulg
resolve_aluc(ulg c, int noerr)
{
  ulg z = ~0;

  if (c >= 0xffff8000 || c < 0x10000)
	{
	  c &= 0xffff;
	  if (IS_POWER_OF_2(c) && ((z = binary_log(c)) < 16))
		z = 2*z;
	  else
		{
		  c ^= 0xffff;
		  if (IS_POWER_OF_2(c) && ((z = binary_log(c)) < 16))
			z = 2*z + 1;
		}
	}
  if (z == ~0 && !noerr)
	cerr("Invalid ALU constant");
  return z;
}

static struct insn *
alu_num(ulg r, ulg c, ulg op)
{
  struct insn *i = alloc_insn(0x220010, IC_ICALU);
  if (r == ~0)
	r = 0;
  else if ((r = reg_set(r, alux_regs)) == ~0)
	cerr("Invalid register for ALU operation");
  i->code |= (r << 8) | ((c & 7) << 5) | ((c & 0x18) << 8) | (op << 13);
  return i;
}

static struct insn *
alu_addi(ulg r, ulg i, ulg prefer_sub)
{
  ulg k;

  if (i == 1 && IS_ALU_YOP(r))			/* INC yop */
	return alu_op(~0, r, 1, ~0);
  else if (i == -1 && IS_ALU_YOP(r))	/* DEC yop */
	return alu_op(~0, r, 8, ~0);
  else if (prefer_sub && (k = resolve_aluc(-i, 1)) != ~0) /* Preferred SUB */
	return alu_num(r, k, 7);
  else if ((k = resolve_aluc(i, 1)) != ~0) /* ADD */
	return alu_num(r, k, 3);
  else									/* SUB */
	{
	  k = resolve_aluc(-i, 0);
	  return alu_num(r, k, 7);
	}
}

static ulg
std_reg(ulg x)
{
  if (x < 0x40)
	return x;
  cerr("Invalid register");
  return 0;
}

static ulg
d_reg(ulg x)
{
  if (x < 0x10)
	return x;
  cerr("Invalid register");
  return 0;
}

static ulg
negate_cond(ulg x)
{
  if (x == C_NOTCE)
	return C_CE;
  if (x == C_CE)
	return C_NOTCE;
  if (x == C_TRUE)
	{
	  cerr("Invalid condition");
	  return x;
	}
  return x ^ 1;
}

static struct insar *
init_ichain(void)
{
  struct insar *r = xmalloc(sizeof(struct insar));

  r->cnt = 1;
  return r;
}

static struct insn *
insn_chain(struct insar *g)
{
  struct insn *i = NULL;
  struct glue *h,*H;
  ulg j,x,y,m;

  m = 0;
  h = NULL;

  if (debug & DEBUG_COMBINE)
	{
	  printf("Combining @%d [", lino);
	  for(j=0; j<g->cnt; j++)
		printf(j ? ",%d" : "%d", g->type[j]);
	  printf("]\n");
	}

  if (g->type[0] == IC_IF)				/* IF + IFable instruction */
	{
	  if (g->cnt == 2)
		{
		  h = g->i[0];
		  switch (g->type[1])
			{
			case IC_ALU:
			case IC_MAC:
			case IC_ICMAC:
			case IC_SHIFT:
			case IC_IFIN:
			case IC_JUMP:
			case IC_ICALU:
			  i = g->i[1];
			  i->code |= h->x;
			  free(h);
			  goto done;
			case IC_SAT:
			  i = g->i[1];
			  if (h->x != C_MV)
				cerr("Only MV condition may be used for SAT MR");
			  free(h);
			  goto done;
			}
		}
	  if (g->type[1] == IC_FLAGS)
		{
		  i = g->i[1];
		  i->code |= h->x;
		  free(h);
		  m = 1;
		  goto doflags;
		}
		
	  cerr("Invalid conditional instruction");
	  goto done;
	}

  if (g->type[0] == IC_IFFLAG)			/* IF FLAG_IN + JUMP/CALL */
	{
	  if (g->type[1] != IC_JUMP || g->cnt != 2)
		goto donebad;
	  h = g->i[0];
	  i = g->i[1];
	  if (i->code & 0x040000)			/* CALL */
		i->code = 0x030001;
	  else								/* JUMP */
		i->code = 0x030000;
	  if (!h->x)						/* Positive */
		i->code |= 2;
	  i->flags = IF_IMM14X;
	  free(h);
	  goto done;
	}

  if (g->cnt == 1)						/* Single instructions -- simple cases */
	{
	  switch (g->type[0])
		{
		case IC_INCOMP:
		case IC_PUSHPOP:
		case IC_ENADIS:
		  i = g->i[0];
		  goto done;
		case IC_FLAGS:
		  goto doflags;
		case IC_ALU:						/* IFable, but no IF */
		case IC_MAC:
		case IC_ICMAC:
		case IC_SHIFT:
		case IC_IFIN:
		case IC_JUMP:
		case IC_ICALU:
		  i = g->i[0];
		  i->code |= 0x0f;
		  goto done;
		case IC_SAT:
		  cerr("SAT instruction must be conditional");
		  return NULL;
		case IC_MOVE:					/* REG <- REG move */
		  i = alloc_insn(0x0d0000, IC_INCOMP);
		  h = g->i[0];
		  i->code |= ((h->x & 15) << 4) | (h->y & 15) | ((h->x & 0x30) << 6) | ((h->y & 0x30) << 4);
		  free(h);
		  goto done;
		case IC_MEMF:
		case IC_MEMS:
		  i = alloc_insn(0, IC_INCOMP);
		  h = g->i[0];
		  if (!h->x)
			{
			  if (h->y >= R_I0 && h->y <= R_I3 && h->z >= R_M0 && h->z <= R_M3)
				i->code = 0x600000 | ((h->y - R_I0) << 2) | (h->z - R_M0);
			  else if (h->y >= R_I4 && h->y <= R_I7 && h->z >= R_M4 && h->z <= R_M7)
				i->code = 0x700000 | ((h->y - R_I4) << 2) | (h->z - R_M4);
			  else
				goto movebad;
			}
		  else if (h->y >= R_I4 && h->y <= R_I7 && h->z >= R_M4 && h->z <= R_M7)
			i->code = 0x500000 | ((h->y - R_I4) << 2) | (h->z - R_M4);
		  else
			goto donebad;
		  if (h->a > 15)
			goto movebad;
		  i->code |= h->a << 4;
		  if (g->type[0] == IC_MEMS)
			i->code |= 0x080000;
		  free(h);
		  goto done;
		default:
		  goto donebad;
		}
	}

 doflags:
  if (g->type[m] == IC_PUSHPOP || g->type[m] == IC_ENADIS || g->type[m] == IC_FLAGS)	/* SET-type */
	{
	  i = g->i[0];
	  if (g->type[m] == IC_FLAGS && !m)
		i->code |= 0x0f;
	  m++;
	  for (j=m; j<g->cnt; j++)
		if (g->type[j] != g->type[0])
		  goto donebad;
	  for (j=m; j<g->cnt; j++)
		{
		  struct insn *a = g->i[j];

		  switch (g->type[j])
			{
			case IC_PUSHPOP:
			  if (i->code & a->code & 0xff)
				goto donebad;
			  break;
			case IC_ENADIS:
			  x = ((i->code & 0x00aaaa) >> 1) | (i->code & 0x005555);
			  y = ((a->code & 0x00aaaa) >> 1) | (a->code & 0x005555);
			  if (x & y)
				goto donebad;
			  break;
			case IC_FLAGS:
			  x = ((i->code & 0x000aa0) >> 1) | (i->code & 0x000550);
			  y = ((a->code & 0x000aa0) >> 1) | (a->code & 0x000550);
			  if (x & y)
				goto donebad;
			  break;
			}
		  i->code |= a->code;
		  free(a);
		}
	  goto done;
	}

  if (g->cnt == 2 && g->type[0] == IC_MEMF && g->type[1] == IC_MEMF) /* MEMF,MEMF */
	{
	  i = alloc_insn(0xc00000, IC_INCOMP);
	  h = g->i[0];
	  H = g->i[1];
	  if (h->x && !H->x)			/* PM,DM */
		{
		  h = g->i[1];
		  H = g->i[0];
		}
	  else if (h->x || !H->x)		/* not DM,PM */
		goto donebad;
	  if (h->y < R_I0 || h->y > R_I3 || h->z < R_M0 || h->z > R_M3 ||
		  H->y < R_I4 || H->y > R_I7 || H->z < R_M4 || H->z > R_M7)
		goto donebad;
	  x = reg_set(h->a, xferd_regs);
	  y = reg_set(H->a, xferp_regs);
	  if (x == ~0 || y == ~0)
		goto donebad;
	  i->code |= (x << 18) | (y << 20) |
		((h->y - R_I0) << 2) | (h->z - R_M0) |
		((H->y - R_I4) << 6) | ((H->z - R_M4) << 4);
	  free(h);
	  free(H);
	  goto done;
	}

  for(x=0; x < g->cnt; x++)				/* Let's bubblesort them */
	for(y=0; y < x; y++)
	  if (g->type[y] > g->type[y+1])
		{
		  void *p = g->i[y];
		  g->i[y] = g->i[y+1];
		  g->i[y+1] = p;
		  j = g->type[y];
		  g->type[y] = g->type[y+1];
		  g->type[y+1] = j;
		}

  if (g->type[0] == IC_ALU || g->type[0] == IC_MAC || g->type[0] == IC_SHIFT) /* ALU/MAC/SHIFT combinations */
	{
	  ulg shift = (g->type[0] == IC_SHIFT);
	  i = g->i[0];
	  if (g->cnt == 2)
		{
		  h = g->i[1];
		  switch (g->type[1])
			{
			case IC_MOVE:
			  if (shift)
				i->code = (i->code & 0x00ffff) | 0x100000;
			  else
				i->code |= 0x080000;
			  if (h->x > 15 || h->y > 15)
				goto movebad;
			  i->code |= (h->x << 4) | h->y;
			  break;
			case IC_MEMF:
			case IC_MEMS:
			  if (!shift)
				i->code &= i->code & 0x07ffff;
			  else
				i->code &= 0x00ffff;
			  if (!h->x)				/* DM */
				{
				  if (h->y >= R_I0 && h->y <= R_I3 && h->z >= R_M0 && h->z <= R_M3)
					i->code |= ((h->y - R_I0) << 2) | (h->z - R_M0) | (shift ? 0x120000 : 0x600000);
				  else if (h->y >= R_I4 && h->y <= R_I7 && h->z >= R_M4 && h->z <= R_M7)
					i->code |= ((h->y - R_I4) << 2) | (h->z - R_M4) | (shift ? 0x130000 : 0x700000);
				  else
					goto movebad;
				}
			  else						/* PM */
				if (h->y >= R_I4 && h->y <= R_I7 && h->z >= R_M4 && h->z <= R_M7)
				  i->code |= ((h->y - R_I4) << 2) | (h->z - R_M4) | (shift ? 0x110000 : 0x500000);
			  else
				goto movebad;
			  i->code |= d_reg(h->a) << 4;
			  if (g->type[1] == IC_MEMS)
				i->code |= (shift ? 0x008000 : 0x080000);
			  break;
			default:
			  goto donebad;
			}
		  free(h);
		  goto done;
		}
	  if (g->cnt == 3 && g->type[1] == g->type[2] && g->type[2] == IC_MEMF)	/* 2*fetch */
		{
		  if (shift || i->code & 0x040000) /* MF/AF not allowed here */
			goto donebad;
		  h = g->i[1];
		  H = g->i[2];
		  if (h->x && !H->x)			/* PM,DM */
			{
			  h = g->i[2];
			  H = g->i[1];
			}
		  else if (h->x || !H->x)		/* not DM,PM */
			goto donebad;
		  if (h->y < R_I0 || h->y > R_I3 || h->z < R_M0 || h->z > R_M3 ||
			  H->y < R_I4 || H->y > R_I7 || H->z < R_M4 || H->z > R_M7)
			goto donebad;
		  x = reg_set(h->a, xferd_regs);
		  y = reg_set(H->a, xferp_regs);
		  if (x == ~0 || y == ~0)
			goto donebad;
		  i->code = (i->code & 0x03ff00) | (x << 18) | (y << 20) | 0xc00000 |
			((h->y - R_I0) << 2) | (h->z - R_M0) |
			((H->y - R_I4) << 6) | ((H->z - R_M4) << 4);
		  free(h);
		  free(H);
		  goto done;
		}
	}

  goto donebad;

 movebad:
  cerr("Invalid data move instruction");
  return NULL;

 donebad:
  cerr("Invalid instruction combination");
  i = NULL;
 done:
  free(g);

  if (i && !(debug & DEBUG_NO_IMMED_RESOLVE))
	resolve_insn(i);
  return i;
}

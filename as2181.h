/*
 *		ADSP 2181 Assembler -- Global Declarations
 *
 *		(c) 1996 Martin Mares, <mj@k332.feld.cvut.cz>
 *
 *		This software may be freely distributed and used according to the terms
 *		of the GNU General Public License. See file COPYING in any of the GNU utilities.
 */

#include "glob.h"

/* main.c */

void fatal_error(char *, ...) NONRET;
void *xmalloc(ulg);

extern int verbose, case_insensitive, hide_warns, do_listing, dm24bit;
extern ulg debug;

#define DEBUG_SWITCHES "pcvmVPCxr"
#define DEBUG_PARSE_PROG 1
#define DEBUG_PARSE_CONST 2
#define DEBUG_PARSE_VAR 4
#define DEBUG_MEMLIST_FINAL 8
#define DEBUG_VARS_MEM 0x10
#define DEBUG_RESOLVED_PROG 0x20
#define DEBUG_RESOLVED_CONSTS 0x40
#define DEBUG_COMBINE 0x80
#define DEBUG_NO_IMMED_RESOLVE 0x100

/* lists.c */

struct node {
	struct node *next, *prev;
	};
typedef struct node node;

struct list {
	struct node head, tail;
	};
typedef struct list list;

#define NODE (node *)
#define DECL_NODE(name,type,var) struct type *name = \
	(struct type *) var
#define HEAD(list) ((void *)((list).head.next))
#define DO_FOR_ALL(n,list) for((n)=HEAD(list);(NODE (n))->next; \
	n=(void *)((NODE (n))->next))
#define EMPTY_LIST(list) (!(list).head.next->next)
#define NEW_NODE(type,class) new_node(class, sizeof(struct type), lino)
#define NEW_LNODE(type,class,lin) new_node(class, sizeof(struct type), lin)

void add_tail(list *, node *);
void add_head(list *, node *);
void rem_node(node *);
void add_tail_list(list *, list *);
void init_list(list *);
void insert_node(node *, node *);
void *new_node(int, int, int);

int check_list(list *);
void dump_node(void *);
void dump_list(list *);

/* dump.c */

void dump_listing(void);

/* lex.l */

extern int err_max;
extern ulg lino;
struct module;

struct symbol {
  struct symbol *next;
  struct module *scope;
  void *value;
  char name[1];
};

struct symbol *find_symbol(char *, ulg, struct module *);
void expose_symbol(struct symbol *);
void init_lex(char *, int);
int yylex(void);
ulg lookup_line(ulg, char **);
void report_warns(void);
void errstop(void);
void err(char *, ...) NONRET;
void ierr(char *, ...) NONRET;
void warn(char *, ...);
void cerr(char *, ...);
void lerr(ulg, char *, ...) NONRET;
void ilerr(ulg, char *, ...) NONRET;
void lwarn(ulg, char *, ...);
void clerr(ulg, char *, ...);
void cnote(ulg, char *, ...);
char *syserr(void);

/* kwds.k */

struct as_kwd {
  char *name;
  word class;
  word value;
};

const struct as_kwd *is_kwd(register const char *, register unsigned int);

/* syn.y */

extern list modules, varlist, constlist;
extern struct module *thismod;
extern ulg src_lines;

int yyparse(void);
void init_syn(void);

/* Registers */

#define R_AX0 0
#define R_AX1 1
#define R_MX0 2
#define R_MX1 3
#define R_AY0 4
#define R_AY1 5
#define R_MY0 6
#define R_MY1 7
#define R_SI 8
#define R_SE 9
#define R_AR 10
#define R_MR0 11
#define R_MR1 12
#define R_MR2 13
#define R_SR0 14
#define R_SR1 15

#define R_EXTEND 16

#define R_I0 0x10
#define R_I1 0x11
#define R_I2 0x12
#define R_I3 0x13
#define R_M0 0x14
#define R_M1 0x15
#define R_M2 0x16
#define R_M3 0x17
#define R_L0 0x18
#define R_L1 0x19
#define R_L2 0x1a
#define R_L3 0x1b
#define R_XXX0 0x1c
#define R_XXX1 0x1d
#define R_XXX2 0x1e
#define R_XXX3 0x1f

#define R_I4 0x20
#define R_I5 0x21
#define R_I6 0x22
#define R_I7 0x23
#define R_M4 0x24
#define R_M5 0x25
#define R_M6 0x26
#define R_M7 0x27
#define R_L4 0x28
#define R_L5 0x29
#define R_L6 0x2a
#define R_L7 0x2b
#define R_XXX4 0x2c
#define R_XXX5 0x2d
#define R_XXX6 0x2e
#define R_XXX7 0x2f

#define R_ASTAT 0x30
#define R_MSTAT 0x31
#define R_SSTAT 0x32					/* R/O */
#define R_IMASK 0x33
#define R_ICNTL 0x34
#define R_CNTR 0x35
#define R_SB 0x36
#define R_PX 0x37
#define R_RX0 0x38
#define R_TX0 0x39
#define R_RX1 0x3a
#define R_TX1 0x3b
#define R_IFC 0x3c						/* W/O */
#define R_OWRCNTR 0x3d					/* W/O */
#define R_XXX8 0x3e
#define R_XXX9 0x3f

#define R_AF 0x40
#define R_MF 0x41
#define R_MR 0x42

/* Conditions */

#define C_EQ 0
#define C_NE 1
#define C_GT 2
#define C_LE 3
#define C_LT 4
#define C_GE 5
#define C_AV 6
#define C_NOTAV 7
#define C_AC 8
#define C_NOTAC 9
#define C_NEG 10
#define C_POS 11
#define C_MV 12
#define C_NOTMV 13
#define C_NOTCE 14
#define C_TRUE 15
#define C_CE 16

/* MAC classes */

#define MC_SS 0
#define MC_SU 1
#define MC_US 2
#define MC_UU 3
#define MC_RND 4

/* Shifter classes */

#define SC_HI 0
#define SC_LO 1
#define SC_HIX 2

/* Flags */

#define FL_OUT 4
#define FL_0 6
#define FL_1 8
#define FL_2 10

/* PUSH/POP operands */

#define PP_STS 3
#define PP_CNTR 4
#define PP_LOOP 8
#define PP_PC 16

/* ENA/DIS operands */

#define ED_SEC_REG 0x20
#define ED_BIT_REV 0x80
#define ED_AV_LATCH 0x200
#define ED_AR_SAT 0x800
#define ED_M_MODE 0x2000
#define ED_TIMER 0x8000
#define ED_G_MODE 0x0008

#define ED_INTS ~0

/* Memory allocation system */

struct memblock {
  node n;
  word addr;							/* ~0=not assigned */
  word len;								/* Length (~0=unknown) */
  byte isprog;							/* 1=program, 0=data */
  byte isram;							/* 0=ROM, 1=RAM */
  byte iscirc;							/* Is a circular buffer (align it!) */
  byte *init;							/* Binary data (NULL=uninitialized) */
  word initlen;							/* Used initializer space */
  struct symbol *sym;					/* Reference symbol */
};

void init_mem(void);
struct memblock *new_memblock(void);
void process_mem(void);
void do_inits(void);
void write_result(char *);
void copy_prog(void);

/* Program nodes */

#define PHDR node n; byte type, flags; word line

struct pheader {
  PHDR;
};

#define TYPE(n) (((struct pheader *)(n))->type)
#define LINE(n) (((struct pheader *)(n))->line)
#define FLAGS(n) (((struct pheader *)(n))->flags)

#define N_LABEL 1

struct label {
  PHDR;
  word addr;
  struct symbol *sym;
};

#define N_INSN 2

struct insn {
  PHDR;
  ulg code;								/* Instruction code */
  byte dest;							/* Destination register if any (for collision checks) */
  byte comp;							/* Compatibility flags */
  node *expr;							/* Possible unresolved expression (only for imm. instructions) */
};

#define IC_INCOMP 0						/* Incompatible instruction */
#define IC_ALU 1						/* Compatible ALU instruction */
#define IC_MAC 2						/* Compatible MAC instruction */
#define IC_SHIFT 3						/* Compatible shifter instruction */
#define IC_MEMF 4						/* Compatible memory fetch instruction [glue] */
#define IC_MOVE 5						/* Compatible move instruction [glue] */
#define IC_MEMS 6						/* Compatible memory store instruction [glue] */
#define IC_JUMP 7						/* Jump or call */
#define IC_PUSHPOP 8					/* PUSH / POP combinations */
#define IC_ENADIS 9						/* ENA / DIS combinations */
#define IC_FLAGS 10						/* SET / RESET / TOGGLE combinations */
#define IC_IF 11						/* Plain IF [glue] */
#define IC_IFFLAG 12					/* IF FL_IN [glue] */
#define IC_IFIN 13						/* IFable, but incompatible */
#define IC_SAT 14						/* SAT MR */
#define IC_ICMAC 15						/* Incompatible, but IFable MAC ins'n */
#define IC_ICALU 16						/* Incompatible, but IFable ALU ins'n */

#define IF_IMM16 0						/* Immediate 16-bit */
#define IF_IMM14 1						/* Immediate 14-bit */
#define IF_IMM11 2						/* Immediate 11-bit */
#define IF_IMM14X 3						/* Immediate 14-bit in shifted form for IF FLAG_IN insn's */

#define N_CONST 3

struct constant {
  PHDR;
  node *expr;			  				/* NULL if already resolved */
  struct symbol *sym;
  ulg value;
};

#define N_VAR 4

struct var {
  PHDR;
  struct symbol *sym;
  struct memblock *mem;
  word size;
  word offs;
  struct init *init;
};

#define N_MODULE 5						/* Program module */

struct module {
  PHDR;
  list insns;
  struct symbol *sym;
  struct memblock *mem;
};

#define N_INIT 6						/* Initializer */

struct init {
  PHDR;
  ulg current;
  node *k[1];
};

#define N_NUM 0x80

struct numeric {
  PHDR;
  ulg value;
};

#define NUMBER(x) (((struct numeric *)(x))->value)

#define N_BINARY 0x81

struct binary {
  PHDR;
  word op;
  node *l, *r;
};

#define N_UNARY 0x82

struct unary {
  PHDR;
  word op;
  node *l;
};

#define N_SYMREF 0x83

struct symref {
  PHDR;
  struct symbol *sym;
};

/* expr.c */

int resolve_expr(node **);
ulg expr_to_num(node *);
int resolve_const(struct constant *);
int resolve_insn(struct insn *);
void do_exprs(void);

extern int report_unresolved;

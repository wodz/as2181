/* A Bison parser, made by GNU Bison 2.7.12-4996.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.7.12-4996"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 11 "syn.y"

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

/* Line 371 of yacc.c  */
#line 119 "syn.tab.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "syn.tab.h".  */
#ifndef YY_YY_SYN_TAB_H_INCLUDED
# define YY_YY_SYN_TAB_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     GOT_EOF = 258,
     CARRY = 259,
     AND = 260,
     OR = 261,
     XOR = 262,
     IF = 263,
     PASS = 264,
     NOT = 265,
     ABS = 266,
     DIVS = 267,
     DIVQ = 268,
     TSTBIT = 269,
     DM = 270,
     PM = 271,
     IO = 272,
     OF = 273,
     SETBIT = 274,
     CLRBIT = 275,
     TGLBIT = 276,
     ASHIFT = 277,
     LSHIFT = 278,
     NORM = 279,
     EXP = 280,
     EXPADJ = 281,
     BY = 282,
     DMOVLAY = 283,
     DO = 284,
     NONE = 285,
     UNTIL = 286,
     JUMP = 287,
     CALL = 288,
     FLAG_IN = 289,
     RTS = 290,
     RTI = 291,
     IDLE = 292,
     NOP = 293,
     MODIFY = 294,
     PUSH = 295,
     POP = 296,
     SET = 297,
     CONST = 298,
     SR = 299,
     RESET = 300,
     TOGGLE = 301,
     ENA = 302,
     DIS = 303,
     FOREVER = 304,
     MODULE = 305,
     VAR = 306,
     ROM = 307,
     RAM = 308,
     ENDMOD = 309,
     CIRC = 310,
     LL = 311,
     RR = 312,
     INIT = 313,
     MR = 314,
     MF = 315,
     INTS = 316,
     SAT = 317,
     ENTRY = 318,
     EXTERNAL = 319,
     GLOBAL = 320,
     NUM = 321,
     REG = 322,
     COND = 323,
     MACCLASS = 324,
     SHCLASS = 325,
     FLAG = 326,
     POPREG = 327,
     ENADISREG = 328,
     SYM = 329
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 62 "syn.y"

  int i;
  struct symbol *s;
  node *n;
  struct memblock *m;
  struct var *v;
  struct glue *g;
  struct insn *a;
  struct insar *r;


/* Line 387 of yacc.c  */
#line 248 "syn.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_SYN_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 276 "syn.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef __attribute__
/* This feature is available in gcc versions 2.5 and later.  */
# if (! defined __GNUC__ || __GNUC__ < 2 \
      || (__GNUC__ == 2 && __GNUC_MINOR__ < 5))
#  define __attribute__(Spec) /* empty */
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif


/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   623

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  90
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  62
/* YYNRULES -- Number of rules.  */
#define YYNRULES  179
/* YYNRULES -- Number of states.  */
#define YYNSTATES  299

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   329

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    81,     2,     2,
      89,    88,    77,    75,    83,    76,     2,    78,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    84,    82,
       2,    85,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,    79,     2,     2,     2,     2,
       2,    86,     2,    87,    80,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     7,    10,    13,    17,    20,    22,
      24,    26,    28,    30,    32,    34,    36,    39,    42,    44,
      48,    51,    54,    58,    61,    66,    69,    73,    76,    80,
      84,    86,    90,    93,    96,    97,   101,   102,   106,   110,
     114,   116,   122,   124,   126,   128,   130,   133,   136,   138,
     140,   143,   146,   149,   151,   153,   155,   157,   159,   161,
     163,   166,   170,   171,   173,   176,   180,   186,   189,   191,
     193,   196,   199,   203,   208,   211,   215,   218,   221,   224,
     231,   234,   237,   240,   243,   246,   249,   252,   257,   260,
     262,   265,   268,   270,   272,   274,   276,   278,   280,   282,
     285,   287,   291,   293,   295,   297,   300,   302,   305,   307,
     310,   313,   318,   320,   322,   329,   334,   338,   341,   343,
     345,   349,   351,   353,   355,   356,   359,   362,   366,   369,
     372,   376,   378,   380,   383,   390,   393,   396,   399,   402,
     405,   409,   411,   413,   418,   421,   426,   432,   436,   438,
     440,   443,   444,   447,   449,   451,   453,   458,   460,   462,
     464,   466,   468,   471,   473,   477,   481,   485,   489,   493,
     497,   501,   505,   509,   513,   516,   519,   522,   525,   528
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      91,     0,    -1,    -1,    91,     3,    -1,     1,    82,    -1,
       1,     3,    -1,    91,    92,    82,    -1,    91,   110,    -1,
     101,    -1,   103,    -1,    97,    -1,   102,    -1,    99,    -1,
      93,    -1,    95,    -1,    96,    -1,    94,    74,    -1,    93,
      83,    -1,    63,    -1,    95,    83,    74,    -1,    64,    74,
      -1,    65,    74,    -1,    96,    83,    74,    -1,    98,   151,
      -1,    58,    74,   105,    84,    -1,    97,    83,    -1,   100,
      85,   151,    -1,    43,    74,    -1,    99,    83,    74,    -1,
      50,   108,    74,    -1,    54,    -1,   104,    74,   105,    -1,
      51,   108,    -1,   103,    83,    -1,    -1,    86,   151,    87,
      -1,    -1,   106,    78,   109,    -1,   106,    78,   121,    -1,
     106,    78,    55,    -1,   106,    -1,   106,    78,    11,    85,
     151,    -1,   107,    -1,    52,    -1,    53,    -1,   111,    -1,
     112,    82,    -1,    74,    84,    -1,   114,    -1,   115,    -1,
     113,   114,    -1,   113,   115,    -1,   112,    83,    -1,   116,
      -1,   123,    -1,   132,    -1,   138,    -1,   143,    -1,   118,
      -1,   122,    -1,     8,   150,    -1,     8,   117,    34,    -1,
      -1,    10,    -1,   130,   119,    -1,   119,    85,    67,    -1,
     120,    67,    83,    67,    88,    -1,   121,    89,    -1,    16,
      -1,    15,    -1,   130,    67,    -1,   130,   124,    -1,    30,
      85,   124,    -1,    12,    67,    83,    67,    -1,    13,    67,
      -1,    67,   128,    67,    -1,   126,    67,    -1,   126,   125,
      -1,   127,    67,    -1,   127,    67,    75,     4,    76,    66,
      -1,     9,    67,    -1,    76,    67,    -1,    10,    67,    -1,
      11,    67,    -1,   126,   131,    -1,   127,   131,    -1,     9,
     131,    -1,   129,   131,    18,    67,    -1,   126,     4,    -1,
       4,    -1,    67,    75,    -1,    67,    76,    -1,     5,    -1,
       6,    -1,     7,    -1,    14,    -1,    19,    -1,    20,    -1,
      21,    -1,    67,    85,    -1,   151,    -1,   133,    85,   134,
      -1,    59,    -1,    60,    -1,   136,    -1,   135,   136,    -1,
      59,    -1,    59,    69,    -1,   151,    -1,    59,    75,    -1,
      59,    76,    -1,    67,    77,   137,    69,    -1,    67,    -1,
      60,    -1,    44,    85,   142,   141,   140,    70,    -1,   130,
      25,   139,    70,    -1,   130,    26,   139,    -1,    62,    59,
      -1,    67,    -1,   139,    -1,   139,    27,   151,    -1,    22,
      -1,    23,    -1,    24,    -1,    -1,    44,     6,    -1,   130,
      28,    -1,    28,    85,    67,    -1,   130,   151,    -1,   130,
     147,    -1,   147,    85,    67,    -1,    38,    -1,    37,    -1,
      37,   151,    -1,    39,    89,    67,    83,    67,    88,    -1,
      40,   144,    -1,    41,   144,    -1,   149,    61,    -1,   149,
      73,    -1,   146,    71,    -1,    29,   151,   145,    -1,    35,
      -1,    36,    -1,   148,    89,    67,    88,    -1,   148,   151,
      -1,   130,   120,   151,    88,    -1,   120,   151,    88,    85,
      67,    -1,   119,    85,   151,    -1,    72,    -1,    67,    -1,
      31,   150,    -1,    -1,    31,    49,    -1,    42,    -1,    45,
      -1,    46,    -1,    17,    89,   151,    88,    -1,    33,    -1,
      32,    -1,    47,    -1,    48,    -1,    68,    -1,    10,    68,
      -1,    66,    -1,    89,   151,    88,    -1,   151,    75,   151,
      -1,   151,    76,   151,    -1,   151,    77,   151,    -1,   151,
      78,   151,    -1,   151,     5,   151,    -1,   151,     6,   151,
      -1,   151,     7,   151,    -1,   151,    56,   151,    -1,   151,
      57,   151,    -1,    76,   151,    -1,    10,   151,    -1,    11,
     151,    -1,    80,   151,    -1,    81,   151,    -1,    74,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   104,   104,   106,   110,   113,   117,   118,   129,   130,
     131,   132,   133,   134,   135,   136,   140,   149,   150,   154,
     155,   159,   160,   164,   186,   207,   211,   221,   222,   226,
     246,   255,   276,   282,   286,   287,   300,   304,   311,   318,
     326,   327,   340,   349,   350,   356,   357,   361,   370,   376,
     382,   391,   403,   404,   413,   414,   415,   416,   420,   421,
     427,   436,   446,   447,   452,   457,   464,   474,   478,   479,
     484,   496,   504,   511,   522,   533,   534,   535,   536,   537,
     542,   548,   554,   560,   561,   562,   563,   581,   593,   594,
     598,   602,   606,   607,   608,   612,   613,   614,   615,   619,
     622,   637,   644,   645,   649,   658,   667,   668,   673,   682,
     683,   687,   709,   710,   716,   722,   732,   738,   742,   753,
     754,   775,   776,   777,   781,   782,   788,   792,   796,   812,
     819,   826,   827,   828,   843,   853,   858,   859,   864,   869,
     870,   877,   878,   879,   887,   893,   903,   913,   933,   934,
     943,   948,   949,   953,   954,   955,   959,   963,   964,   968,
     969,   973,   974,   980,   985,   988,   989,   990,   991,   992,
     993,   994,   995,   996,   997,   998,   999,  1000,  1001,  1002
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "GOT_EOF", "CARRY", "AND", "OR", "XOR",
  "IF", "PASS", "NOT", "ABS", "DIVS", "DIVQ", "TSTBIT", "DM", "PM", "IO",
  "OF", "SETBIT", "CLRBIT", "TGLBIT", "ASHIFT", "LSHIFT", "NORM", "EXP",
  "EXPADJ", "BY", "DMOVLAY", "DO", "NONE", "UNTIL", "JUMP", "CALL",
  "FLAG_IN", "RTS", "RTI", "IDLE", "NOP", "MODIFY", "PUSH", "POP", "SET",
  "CONST", "SR", "RESET", "TOGGLE", "ENA", "DIS", "FOREVER", "MODULE",
  "VAR", "ROM", "RAM", "ENDMOD", "CIRC", "LL", "RR", "INIT", "MR", "MF",
  "INTS", "SAT", "ENTRY", "EXTERNAL", "GLOBAL", "NUM", "REG", "COND",
  "MACCLASS", "SHCLASS", "FLAG", "POPREG", "ENADISREG", "SYM", "'+'",
  "'-'", "'*'", "'/'", "'U'", "'^'", "'%'", "';'", "','", "':'", "'='",
  "'['", "']'", "')'", "'('", "$accept", "main", "pseudo", "global",
  "globala", "external", "unsupp", "init", "inita", "constant", "consym",
  "module", "endmod", "var", "varstart", "varsize", "memattra", "memattrb",
  "memattr", "romram", "insn", "label", "ichain", "jchain", "iins", "gins",
  "iff", "maybenot", "pdxfer", "memref", "pmdml", "pmdm", "regxfer", "alu",
  "alur", "carried", "regplus", "regminus", "alucomm", "bitop", "regeq",
  "nexpr", "mac", "mrormf", "macrs", "mrpm", "macmul", "macr", "shift",
  "shreg", "shrega", "shifter", "mayshor", "spec", "popreg", "ucond",
  "srt", "ioref", "calljump", "enadis", "cond", "expr", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,    43,    45,    42,    47,    85,
      94,    37,    59,    44,    58,    61,    91,    93,    41,    40
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    90,    91,    91,    91,    91,    91,    91,    92,    92,
      92,    92,    92,    92,    92,    92,    93,    94,    94,    95,
      95,    96,    96,    97,    98,    98,    99,   100,   100,   101,
     102,   103,   104,   104,   105,   105,   106,   106,   106,   106,
     107,   107,   108,   109,   109,   110,   110,   111,   112,   112,
     112,   112,   113,   113,   114,   114,   114,   114,   115,   115,
     116,   116,   117,   117,   118,   118,   119,   120,   121,   121,
     122,   123,   123,   123,   123,   124,   124,   124,   124,   124,
     124,   124,   124,   124,   124,   124,   124,   124,   125,   125,
     126,   127,   128,   128,   128,   129,   129,   129,   129,   130,
     131,   132,   133,   133,   134,   134,   134,   134,   134,   135,
     135,   136,   137,   137,   138,   138,   138,   138,   139,   140,
     140,   141,   141,   141,   142,   142,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   144,   144,
     145,   145,   145,   146,   146,   146,   147,   148,   148,   149,
     149,   150,   150,   151,   151,   151,   151,   151,   151,   151,
     151,   151,   151,   151,   151,   151,   151,   151,   151,   151
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     2,     2,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     1,     3,
       2,     2,     3,     2,     4,     2,     3,     2,     3,     3,
       1,     3,     2,     2,     0,     3,     0,     3,     3,     3,
       1,     5,     1,     1,     1,     1,     2,     2,     1,     1,
       2,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       2,     3,     0,     1,     2,     3,     5,     2,     1,     1,
       2,     2,     3,     4,     2,     3,     2,     2,     2,     6,
       2,     2,     2,     2,     2,     2,     2,     4,     2,     1,
       2,     2,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     3,     1,     1,     1,     2,     1,     2,     1,     2,
       2,     4,     1,     1,     6,     4,     3,     2,     1,     1,
       3,     1,     1,     1,     0,     2,     2,     3,     2,     2,
       3,     1,     1,     2,     6,     2,     2,     2,     2,     2,
       3,     1,     1,     4,     2,     4,     5,     3,     1,     1,
       2,     0,     2,     1,     1,     1,     4,     1,     1,     1,
       1,     1,     2,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     2,     2,     2,     2,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     5,     4,     1,     3,    62,     0,     0,
      69,    68,     0,     0,     0,     0,   158,   157,   141,   142,
     132,   131,     0,     0,     0,   153,     0,     0,   154,   155,
     159,   160,    36,    36,    30,     0,   102,   103,     0,    18,
       0,     0,     0,     0,     0,    13,     0,    14,    15,    10,
       0,    12,     0,     8,    11,     9,     0,     7,    45,     0,
       0,    48,    49,    53,    58,     0,     0,     0,    59,    54,
       0,    55,     0,    56,    57,     0,     0,     0,     0,    63,
     161,     0,    60,     0,    74,     0,     0,     0,     0,   163,
     179,     0,     0,     0,     0,   151,     0,   133,     0,   149,
     148,   135,   136,    27,   124,    40,    42,     0,    32,    34,
     117,    20,    21,    99,    47,     6,    17,    16,     0,     0,
      25,    23,     0,     0,    33,    34,    46,    52,    50,    51,
       0,     0,     0,    67,     0,     0,     0,    95,    96,    97,
      98,     0,     0,   126,    70,     0,    64,     0,    71,     0,
       0,     0,   129,   128,     0,   139,     0,     0,   144,   137,
     138,   162,    61,     0,     0,   127,   175,   176,   174,   177,
     178,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   140,     0,     0,     0,     0,    72,     0,     0,
       0,     0,    29,     0,     0,    19,    22,    28,    26,    31,
      65,   147,     0,     0,    80,    86,   100,    82,    83,   118,
       0,   116,    92,    93,    94,    90,    91,     0,    81,     0,
      89,    76,    77,     0,    84,    78,    85,     0,   106,     0,
     101,     0,   104,   108,   130,     0,    73,   156,   164,   169,
     170,   171,     0,   152,   150,   172,   173,   165,   166,   167,
     168,     0,   125,   121,   122,   123,     0,     0,    43,    44,
      39,    37,    38,     0,    24,     0,     0,   115,    75,   145,
      88,     0,     0,   107,   109,   110,     0,   105,   143,     0,
     119,     0,     0,    35,    66,   146,     0,    87,   113,   112,
       0,   134,     0,   114,    41,     0,   111,   120,    79
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,   194,   105,   106,   107,   261,
      57,    58,    59,    60,    61,    62,    63,    81,    64,    65,
      66,    67,    68,    69,   148,   222,   149,   150,   217,   151,
      70,   205,    71,    72,   230,   231,   232,   290,    73,   210,
     281,   256,   190,    74,   101,   182,    75,    76,    77,    78,
      82,   206
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -142
static const yytype_int16 yypact[] =
{
     427,     2,   495,  -142,  -142,  -142,  -142,    -8,   -59,   -55,
    -142,  -142,   -74,   -63,   327,   -50,  -142,  -142,  -142,  -142,
     327,  -142,   -56,   -38,   -38,  -142,   -48,   -42,  -142,  -142,
    -142,  -142,  -142,  -142,  -142,   -12,  -142,  -142,     7,  -142,
      -2,    14,     6,    10,    13,    16,    22,    24,    27,    28,
     327,    29,    23,  -142,  -142,    31,    46,  -142,  -142,   -45,
     551,  -142,  -142,  -142,  -142,    44,   175,    41,  -142,  -142,
     219,  -142,    47,  -142,  -142,    66,    53,   345,   -52,    71,
    -142,   107,  -142,    59,  -142,   327,    80,   327,   327,  -142,
    -142,   327,   327,   327,   327,   545,    30,   440,    81,  -142,
    -142,  -142,  -142,  -142,   105,    79,  -142,    87,  -142,    84,
    -142,  -142,  -142,  -142,  -142,  -142,  -142,  -142,    97,    98,
    -142,   440,    99,   327,  -142,    84,  -142,  -142,  -142,  -142,
     193,    91,    25,  -142,   243,   255,   273,  -142,  -142,  -142,
    -142,   108,   108,  -142,    11,   291,  -142,   175,  -142,     9,
     294,   327,  -142,   440,   117,  -142,   110,   315,   440,  -142,
    -142,  -142,  -142,   111,    48,  -142,  -142,  -142,  -142,  -142,
    -142,   112,   327,   327,   327,    -7,   327,   327,   327,   327,
     327,   327,  -142,   113,   114,    11,   115,  -142,   109,   188,
      35,    12,  -142,   327,   121,  -142,  -142,  -142,   440,  -142,
    -142,   440,   132,   122,  -142,  -142,   440,  -142,  -142,  -142,
     138,  -142,  -142,  -142,  -142,  -142,  -142,   142,  -142,   139,
    -142,   135,  -142,   207,  -142,   137,  -142,   195,   -65,   141,
    -142,   157,  -142,   440,  -142,   143,  -142,  -142,  -142,    78,
     214,   214,    71,  -142,  -142,    -9,    -9,   -32,   -32,    36,
      36,   158,  -142,  -142,  -142,  -142,   108,   152,  -142,  -142,
    -142,  -142,  -142,   145,  -142,   155,   159,  -142,  -142,  -142,
    -142,   242,   181,  -142,  -142,  -142,   -53,  -142,  -142,   162,
     225,   187,   327,  -142,  -142,  -142,   182,  -142,  -142,  -142,
     192,  -142,   327,  -142,   440,   196,  -142,   440,  -142
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -142,  -142,  -142,  -142,  -142,  -142,  -142,  -142,  -142,  -142,
    -142,  -142,  -142,  -142,  -142,   147,  -142,  -142,   230,  -142,
    -142,  -142,  -142,  -142,   215,   216,  -142,  -142,  -142,   209,
     210,    86,  -142,  -142,   185,  -142,   148,  -142,  -142,  -142,
    -142,   -81,  -142,  -142,  -142,  -142,    56,  -142,  -142,  -141,
    -142,  -142,  -142,  -142,   264,  -142,  -142,   224,  -142,  -142,
     123,   -14
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -3
static const yytype_int16 yytable[] =
{
      95,   211,    79,   242,   273,     3,    97,   288,    83,   159,
     274,   275,    84,   220,   289,    85,   212,   213,   214,    87,
      88,   160,    86,   257,   176,   177,   103,    10,    11,    99,
     172,   173,   174,    98,   100,    96,   121,   126,   127,   134,
     183,   184,   243,   104,   137,   180,   181,    -3,    -3,   138,
     139,   140,   132,   172,   173,   174,   153,   253,   254,   255,
      80,    80,   109,   158,   258,   259,   110,   260,   224,   226,
     227,   164,   111,   166,   167,    89,   221,   168,   169,   170,
     171,   176,   177,    90,     4,    91,   215,   216,   112,    92,
      93,   113,   176,   177,   114,   115,   117,   185,    94,   116,
     178,   179,   180,   181,   176,   177,   186,   118,   123,   198,
     119,   120,   122,   203,   124,   280,   201,   172,   173,   174,
     125,   166,   167,   178,   179,   180,   181,    87,    88,   130,
     133,   168,   154,   219,   176,   177,   237,   155,   156,   161,
     233,   162,   163,   171,   172,   173,   174,   165,   188,   189,
     172,   173,   174,   178,   179,   180,   181,   191,   239,   240,
     241,   192,   245,   246,   247,   248,   249,   250,   176,   177,
     193,   195,   196,   197,   202,   209,   228,   234,   236,   263,
     207,   208,   218,    89,   229,    87,    88,   178,   179,   180,
     181,    90,   251,    91,   252,   176,   177,    92,    93,   265,
     238,   176,   177,    87,    88,   264,    94,   266,   267,   268,
     215,   270,   271,   272,   178,   179,   180,   181,   276,   172,
     178,   179,   180,   181,   229,   279,   285,   269,   134,   135,
     136,   278,   283,   137,    10,    11,    12,   282,   138,   139,
     140,    89,   131,   284,   141,   142,   286,   143,   287,    90,
     291,    91,   292,    87,    88,    92,    93,   293,   295,    89,
     200,   296,   298,   108,    94,    87,    88,    90,   294,    91,
     176,   177,   199,    92,    93,   128,   129,   262,   297,   146,
     147,   187,    94,    87,    88,    89,   144,   277,   102,   178,
     179,   180,   181,    90,   152,   145,     0,   223,   244,    92,
      93,    87,    88,     0,    87,    88,     0,     0,    94,    89,
     204,     0,     0,     0,     0,     0,     0,    90,     0,    91,
       0,    89,   207,    92,    93,    87,    88,     0,     0,    90,
       0,    91,    94,     0,     0,    92,    93,    87,    88,    89,
     208,     0,     0,     0,    94,     0,     0,    90,     0,    91,
       0,     0,     0,    92,    93,    87,    88,    89,   218,     0,
      89,   225,    94,     0,     0,    90,     0,    91,    90,     0,
      91,    92,    93,     0,    92,    93,     0,     0,     0,     0,
      94,    89,   235,    94,     0,     0,     0,     0,     0,    90,
       0,    91,     0,    89,     0,    92,    93,     0,     0,     0,
       0,    90,     0,    91,    94,     0,     0,    92,    93,     0,
       0,    89,     0,     0,     0,     0,    94,     0,     0,    90,
       0,    91,     0,     0,     0,    92,    93,    -2,     1,     0,
      -2,     0,     0,     0,   157,    -2,     0,     0,     0,    -2,
      -2,     0,    -2,    -2,    -2,   172,   173,   174,     0,     0,
       0,     0,     0,     0,     0,    -2,    -2,    -2,     0,    -2,
      -2,     0,    -2,    -2,    -2,    -2,    -2,    -2,    -2,    -2,
      -2,    -2,    -2,    -2,    -2,    -2,     0,    -2,    -2,     0,
       0,    -2,     0,     0,     0,    -2,    -2,    -2,     0,    -2,
      -2,    -2,    -2,     0,    -2,     5,   176,   177,     6,     0,
       0,    -2,     0,     7,     0,     0,     0,     8,     9,     0,
      10,    11,    12,     0,     0,   178,   179,   180,   181,     0,
       0,     0,     0,    13,    14,    15,     0,    16,    17,     0,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,     0,    32,    33,     0,     0,    34,
     172,   173,   174,    35,    36,    37,     0,    38,    39,    40,
      41,     0,    42,     8,     9,     0,    10,    11,    12,    43,
       0,     0,     0,     0,     0,     0,   175,     0,     0,    13,
      14,    15,     0,    16,    17,     0,    18,    19,    20,    21,
      22,    23,    24,    25,     0,    27,    28,    29,    30,    31,
       0,   176,   177,     0,     0,     0,     0,     0,     0,     0,
      36,    37,     0,    38,     0,     0,     0,     0,    42,     0,
     178,   179,   180,   181
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-142)))

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-3)))

static const yytype_int16 yycheck[] =
{
      14,   142,    10,    10,    69,     3,    20,    60,    67,    61,
      75,    76,    67,     4,    67,    89,     5,     6,     7,    10,
      11,    73,    85,    11,    56,    57,    74,    15,    16,    67,
       5,     6,     7,    89,    72,    85,    50,    82,    83,     9,
      10,    11,    49,    85,    14,    77,    78,    56,    57,    19,
      20,    21,    66,     5,     6,     7,    70,    22,    23,    24,
      68,    68,    74,    77,    52,    53,    59,    55,   149,   150,
     151,    85,    74,    87,    88,    66,    67,    91,    92,    93,
      94,    56,    57,    74,    82,    76,    75,    76,    74,    80,
      81,    85,    56,    57,    84,    82,    74,    67,    89,    83,
      75,    76,    77,    78,    56,    57,    76,    83,    85,   123,
      83,    83,    83,    88,    83,   256,   130,     5,     6,     7,
      74,   135,   136,    75,    76,    77,    78,    10,    11,    85,
      89,   145,    85,   147,    56,    57,    88,    71,    85,    68,
     154,    34,    83,   157,     5,     6,     7,    67,    67,    44,
       5,     6,     7,    75,    76,    77,    78,    78,   172,   173,
     174,    74,   176,   177,   178,   179,   180,   181,    56,    57,
      86,    74,    74,    74,    83,    67,    59,    67,    67,   193,
      67,    67,    67,    66,    67,    10,    11,    75,    76,    77,
      78,    74,    83,    76,     6,    56,    57,    80,    81,    67,
      88,    56,    57,    10,    11,    84,    89,    85,    70,    67,
      75,     4,    75,    18,    75,    76,    77,    78,    77,     5,
      75,    76,    77,    78,    67,    67,    67,    88,     9,    10,
      11,    88,    87,    14,    15,    16,    17,    85,    19,    20,
      21,    66,    67,    88,    25,    26,     4,    28,    67,    74,
      88,    76,    27,    10,    11,    80,    81,    70,    76,    66,
      67,    69,    66,    33,    89,    10,    11,    74,   282,    76,
      56,    57,   125,    80,    81,    60,    60,   191,   292,    70,
      70,    96,    89,    10,    11,    66,    67,   231,    24,    75,
      76,    77,    78,    74,    70,    76,    -1,   149,   175,    80,
      81,    10,    11,    -1,    10,    11,    -1,    -1,    89,    66,
      67,    -1,    -1,    -1,    -1,    -1,    -1,    74,    -1,    76,
      -1,    66,    67,    80,    81,    10,    11,    -1,    -1,    74,
      -1,    76,    89,    -1,    -1,    80,    81,    10,    11,    66,
      67,    -1,    -1,    -1,    89,    -1,    -1,    74,    -1,    76,
      -1,    -1,    -1,    80,    81,    10,    11,    66,    67,    -1,
      66,    67,    89,    -1,    -1,    74,    -1,    76,    74,    -1,
      76,    80,    81,    -1,    80,    81,    -1,    -1,    -1,    -1,
      89,    66,    67,    89,    -1,    -1,    -1,    -1,    -1,    74,
      -1,    76,    -1,    66,    -1,    80,    81,    -1,    -1,    -1,
      -1,    74,    -1,    76,    89,    -1,    -1,    80,    81,    -1,
      -1,    66,    -1,    -1,    -1,    -1,    89,    -1,    -1,    74,
      -1,    76,    -1,    -1,    -1,    80,    81,     0,     1,    -1,
       3,    -1,    -1,    -1,    89,     8,    -1,    -1,    -1,    12,
      13,    -1,    15,    16,    17,     5,     6,     7,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    28,    29,    30,    -1,    32,
      33,    -1,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    -1,    50,    51,    -1,
      -1,    54,    -1,    -1,    -1,    58,    59,    60,    -1,    62,
      63,    64,    65,    -1,    67,     0,    56,    57,     3,    -1,
      -1,    74,    -1,     8,    -1,    -1,    -1,    12,    13,    -1,
      15,    16,    17,    -1,    -1,    75,    76,    77,    78,    -1,
      -1,    -1,    -1,    28,    29,    30,    -1,    32,    33,    -1,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    -1,    50,    51,    -1,    -1,    54,
       5,     6,     7,    58,    59,    60,    -1,    62,    63,    64,
      65,    -1,    67,    12,    13,    -1,    15,    16,    17,    74,
      -1,    -1,    -1,    -1,    -1,    -1,    31,    -1,    -1,    28,
      29,    30,    -1,    32,    33,    -1,    35,    36,    37,    38,
      39,    40,    41,    42,    -1,    44,    45,    46,    47,    48,
      -1,    56,    57,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      59,    60,    -1,    62,    -1,    -1,    -1,    -1,    67,    -1,
      75,    76,    77,    78
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,    91,     3,    82,     0,     3,     8,    12,    13,
      15,    16,    17,    28,    29,    30,    32,    33,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    50,    51,    54,    58,    59,    60,    62,    63,
      64,    65,    67,    74,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   110,   111,   112,
     113,   114,   115,   116,   118,   119,   120,   121,   122,   123,
     130,   132,   133,   138,   143,   146,   147,   148,   149,    10,
      68,   117,   150,    67,    67,    89,    85,    10,    11,    66,
      74,    76,    80,    81,    89,   151,    85,   151,    89,    67,
      72,   144,   144,    74,    85,   106,   107,   108,   108,    74,
      59,    74,    74,    85,    84,    82,    83,    74,    83,    83,
      83,   151,    83,    85,    83,    74,    82,    83,   114,   115,
      85,    67,   151,    89,     9,    10,    11,    14,    19,    20,
      21,    25,    26,    28,    67,    76,   119,   120,   124,   126,
     127,   129,   147,   151,    85,    71,    85,    89,   151,    61,
      73,    68,    34,    83,   151,    67,   151,   151,   151,   151,
     151,   151,     5,     6,     7,    31,    56,    57,    75,    76,
      77,    78,   145,    10,    11,    67,    76,   124,    67,    44,
     142,    78,    74,    86,   105,    74,    74,    74,   151,   105,
      67,   151,    83,    88,    67,   131,   151,    67,    67,    67,
     139,   139,     5,     6,     7,    75,    76,   128,    67,   151,
       4,    67,   125,   126,   131,    67,   131,   131,    59,    67,
     134,   135,   136,   151,    67,    67,    67,    88,    88,   151,
     151,   151,    10,    49,   150,   151,   151,   151,   151,   151,
     151,    83,     6,    22,    23,    24,   141,    11,    52,    53,
      55,   109,   121,   151,    84,    67,    85,    70,    67,    88,
       4,    75,    18,    69,    75,    76,    77,   136,    88,    67,
     139,   140,    85,    87,    88,    67,     4,    67,    60,    67,
     137,    88,    27,    70,   151,    76,    69,   151,    66
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YYUSE (yytype);
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:
/* Line 1787 of yacc.c  */
#line 106 "syn.y"
    {						/* End of file */
	 end_of_file();
	 return 0;
   }
    break;

  case 4:
/* Line 1787 of yacc.c  */
#line 110 "syn.y"
    {							/* Error recovery */
     yyerrok;
  }
    break;

  case 5:
/* Line 1787 of yacc.c  */
#line 113 "syn.y"
    {
     end_of_file();
     return 1;
  }
    break;

  case 7:
/* Line 1787 of yacc.c  */
#line 118 "syn.y"
    {
     if (!thismod)
   	   err("Instruction encountered outside module");
	 if ((yyvsp[(2) - (2)].n))
	   add_tail(&thismod->insns, (yyvsp[(2) - (2)].n));
  }
    break;

  case 9:
/* Line 1787 of yacc.c  */
#line 130 "syn.y"
    { }
    break;

  case 10:
/* Line 1787 of yacc.c  */
#line 131 "syn.y"
    { }
    break;

  case 15:
/* Line 1787 of yacc.c  */
#line 136 "syn.y"
    { warn("Directive not supported"); }
    break;

  case 16:
/* Line 1787 of yacc.c  */
#line 140 "syn.y"
    {
	 if (!(yyvsp[(2) - (2)].s)->scope)
	   cerr("Symbol `%s' is already declared global", (yyvsp[(2) - (2)].s)->name);
	 else
	   expose_symbol((yyvsp[(2) - (2)].s));
   }
    break;

  case 23:
/* Line 1787 of yacc.c  */
#line 164 "syn.y"
    {
      struct init *i;
	  (yyval.v) =(yyvsp[(1) - (2)].v);
	  if ((yyvsp[(1) - (2)].v))
		{
		  i = (yyvsp[(1) - (2)].v)->init;
		  if (i->current >= (yyvsp[(1) - (2)].v)->size)
			{
			  cerr("Excess elements in initializer");
			  (yyval.v) = NULL;
			}
		  else
			{
			  node *z = (yyvsp[(2) - (2)].n);
			  resolve_expr(&z);
			  i->k[i->current++] = z;
			}
		}
   }
    break;

  case 24:
/* Line 1787 of yacc.c  */
#line 186 "syn.y"
    {
      if (!(yyvsp[(2) - (4)].s)->value || TYPE((yyvsp[(2) - (4)].s)->value) != N_VAR)
		{
		  cerr("`%s' expected to be a variable", (yyvsp[(2) - (4)].s)->name);
		  (yyval.v) = NULL;
		}
	  else
		{
		  struct var *v = (struct var *) (yyvsp[(2) - (4)].s)->value;
		  ulg s = ((yyvsp[(3) - (4)].i) == -1) ? 0 : (yyvsp[(3) - (4)].i);
		  struct init *i = v->init;

		  if (!i)
			{
			  i = v->init = xmalloc(sizeof(struct init) + (v->size-1) * sizeof(node *));
			  bzero(i->k, v->size * sizeof(node *));
			}
		  i->current = s;
		  (yyval.v) = v;
		}
	}
    break;

  case 26:
/* Line 1787 of yacc.c  */
#line 211 "syn.y"
    {
	 struct constant *m = NEW_NODE(constant, N_CONST);
	 symdef((yyvsp[(1) - (3)].s), &m->sym, NODE m);
	 m->expr = (yyvsp[(3) - (3)].n);
	 resolve_const(m);
	 add_tail(&constlist, &m->n);
   }
    break;

  case 27:
/* Line 1787 of yacc.c  */
#line 221 "syn.y"
    { (yyval.s) = (yyvsp[(2) - (2)].s); }
    break;

  case 28:
/* Line 1787 of yacc.c  */
#line 222 "syn.y"
    { (yyval.s) = (yyvsp[(3) - (3)].s); }
    break;

  case 29:
/* Line 1787 of yacc.c  */
#line 226 "syn.y"
    { 
	 struct module *n = NEW_NODE(module, N_MODULE);
	 DECL_NODE(m, memblock, (yyvsp[(2) - (3)].m));
	 if (thismod)
	   cerr("Module nesting not possible");
	 if (!m->isprog)
	   cerr("Modules must reside in program memory");
	 else if (m->isprog == 0xff)
	   m->isprog = 1;
	 symdef((yyvsp[(3) - (3)].s), &n->sym, NODE n);
	 m->sym = (yyvsp[(3) - (3)].s);
	 n->mem = m;
	 init_list(&n->insns);
	 add_tail(&modules, NODE n);
	 expose_symbol(m->sym);
	 thismod = n;
   }
    break;

  case 30:
/* Line 1787 of yacc.c  */
#line 246 "syn.y"
    {
	  if (!thismod)
		cerr("Closing unopened module");
	  else
		thismod = NULL;
	}
    break;

  case 31:
/* Line 1787 of yacc.c  */
#line 255 "syn.y"
    {
	  struct var *v = NEW_NODE(var, N_VAR);
	  symdef((yyvsp[(2) - (3)].s), &v->sym, NODE v);
	  if (!(yyvsp[(1) - (3)].m)->sym)
		(yyvsp[(1) - (3)].m)->sym = (yyvsp[(2) - (3)].s);
	  v->mem = (yyvsp[(1) - (3)].m);
	  v->size = ((yyvsp[(3) - (3)].i) == -1) ? 1 : (yyvsp[(3) - (3)].i);
	  if (!v->size)
		{
		  cerr("Zero-sized arrays not allowed");
		  v->size = 1;
		}
	  v->offs = v->mem->len;
	  v->mem->len += v->size;
	  v->init = NULL;
	  add_tail(&varlist, NODE v);
	  (yyval.m) = (yyvsp[(1) - (3)].m);
   }
    break;

  case 32:
/* Line 1787 of yacc.c  */
#line 276 "syn.y"
    {
	 (yyvsp[(2) - (2)].m)->len = 0;
	 if ((yyvsp[(2) - (2)].m)->isprog == 0xff)
	   (yyvsp[(2) - (2)].m)->isprog = 0;
	 (yyval.m) = (yyvsp[(2) - (2)].m);
   }
    break;

  case 34:
/* Line 1787 of yacc.c  */
#line 286 "syn.y"
    { (yyval.i) = -1; }
    break;

  case 35:
/* Line 1787 of yacc.c  */
#line 287 "syn.y"
    {
     node *ex = (yyvsp[(2) - (3)].n);
	 if (!resolve_expr(&ex))
	   {
		 cerr("Array size must be constant");
		 (yyval.i) = 1;
	   }
	 else
	   (yyval.i) = expr_to_num(ex);
   }
    break;

  case 36:
/* Line 1787 of yacc.c  */
#line 300 "syn.y"
    {
	 struct memblock *mem = new_memblock();
	 (yyval.m) = mem;
   }
    break;

  case 37:
/* Line 1787 of yacc.c  */
#line 304 "syn.y"
    {
     DECL_NODE(l, memblock, (yyvsp[(1) - (3)].m));
	 if (l->isram != 0xff)
	   cerr("ROM/RAM already specified");
	 l->isram = (yyvsp[(3) - (3)].i);
	 (yyval.m) = (yyvsp[(1) - (3)].m);
   }
    break;

  case 38:
/* Line 1787 of yacc.c  */
#line 311 "syn.y"
    {
      DECL_NODE(l, memblock, (yyvsp[(1) - (3)].m));
	  if (l->isprog != 0xff)
		cerr("PM/DM already specified");
	  l->isprog = (yyvsp[(3) - (3)].i);
	  (yyval.m) = (yyvsp[(1) - (3)].m);
	}
    break;

  case 39:
/* Line 1787 of yacc.c  */
#line 318 "syn.y"
    {
      DECL_NODE(l, memblock, (yyvsp[(1) - (3)].m));
	  l->iscirc = 1;
	  (yyval.m) = (yyvsp[(1) - (3)].m);
	}
    break;

  case 41:
/* Line 1787 of yacc.c  */
#line 327 "syn.y"
    {
      DECL_NODE(l, memblock, (yyvsp[(1) - (5)].m));
	  node *ex = (yyvsp[(5) - (5)].n);
	  if (l->addr != 0xffff)
		cerr("Address already specified");
	  if (!resolve_expr(&ex))
		cerr("Address expression must be constant");
	  else
		l->addr = expr_to_num(ex);
	  (yyval.m) = (yyvsp[(1) - (5)].m);
	}
    break;

  case 42:
/* Line 1787 of yacc.c  */
#line 340 "syn.y"
    {
	  DECL_NODE(l, memblock, (yyvsp[(1) - (1)].m));
	  if (l->isram)
		l->isram = 1;
	  (yyval.m) = (yyvsp[(1) - (1)].m);
	}
    break;

  case 43:
/* Line 1787 of yacc.c  */
#line 349 "syn.y"
    { (yyval.i) =  0; }
    break;

  case 44:
/* Line 1787 of yacc.c  */
#line 350 "syn.y"
    { (yyval.i) = 1; }
    break;

  case 46:
/* Line 1787 of yacc.c  */
#line 357 "syn.y"
    { (yyval.n) = NODE insn_chain((yyvsp[(1) - (2)].r)); }
    break;

  case 47:
/* Line 1787 of yacc.c  */
#line 361 "syn.y"
    {
	 struct label *n = NEW_NODE(label, N_LABEL);
	 symdef((yyvsp[(1) - (2)].s), &n->sym, NODE n);
	 n->addr = ~0;
	 (yyval.n) = NODE n;
   }
    break;

  case 48:
/* Line 1787 of yacc.c  */
#line 370 "syn.y"
    {
	 struct insar *i = init_ichain();
	 i->type[0] = (yyvsp[(1) - (1)].a)->comp;
	 i->i[0] = (yyvsp[(1) - (1)].a);
	 (yyval.r) = i;
   }
    break;

  case 49:
/* Line 1787 of yacc.c  */
#line 376 "syn.y"
    {
     struct insar *i = init_ichain();	/* Looks the same, but differs! */
     i->type[0] = (yyvsp[(1) - (1)].g)->t;
	 i->i[0] = (yyvsp[(1) - (1)].g);
	 (yyval.r) = i;
   }
    break;

  case 50:
/* Line 1787 of yacc.c  */
#line 382 "syn.y"
    {
     if ((yyvsp[(1) - (2)].r)->cnt > 15)
	   cerr("Instruction chain too long");
	 else
	   {
		 (yyvsp[(1) - (2)].r)->type[(yyvsp[(1) - (2)].r)->cnt] = (yyvsp[(2) - (2)].a)->comp;
		 (yyvsp[(1) - (2)].r)->i[(yyvsp[(1) - (2)].r)->cnt++] = (yyvsp[(2) - (2)].a);
	   }
   }
    break;

  case 51:
/* Line 1787 of yacc.c  */
#line 391 "syn.y"
    {						/* Grrrr... */
     if ((yyvsp[(1) - (2)].r)->cnt > 15)
	   cerr("Instruction chain too long");
	 else
	   {
		 (yyvsp[(1) - (2)].r)->type[(yyvsp[(1) - (2)].r)->cnt] = (yyvsp[(2) - (2)].g)->t;
		 (yyvsp[(1) - (2)].r)->i[(yyvsp[(1) - (2)].r)->cnt++] = (yyvsp[(2) - (2)].g);
	   }
   }
    break;

  case 53:
/* Line 1787 of yacc.c  */
#line 404 "syn.y"
    {
     struct insar *i = init_ichain();
     i->type[0] = (yyvsp[(1) - (1)].g)->t;
	 i->i[0] = (yyvsp[(1) - (1)].g);
	 (yyval.r) = i;
   }
    break;

  case 60:
/* Line 1787 of yacc.c  */
#line 427 "syn.y"
    {
	 struct glue *g = new_glue();
	 g->t = IC_IF;
	 g->x = (yyvsp[(2) - (2)].i);
	 g->a = ~0;
	 if ((yyvsp[(2) - (2)].i) == C_CE)
	   cerr("Invalid IF condition");
	 (yyval.g) = g;
   }
    break;

  case 61:
/* Line 1787 of yacc.c  */
#line 436 "syn.y"
    {
     struct glue *g = new_glue();
	 g->t = IC_IFFLAG;
	 g->x = (yyvsp[(2) - (3)].i);
	 g->a = ~0;
	 (yyval.g) = g;
   }
    break;

  case 62:
/* Line 1787 of yacc.c  */
#line 446 "syn.y"
    { (yyval.i) = 0; }
    break;

  case 63:
/* Line 1787 of yacc.c  */
#line 447 "syn.y"
    { (yyval.i) = 1; }
    break;

  case 64:
/* Line 1787 of yacc.c  */
#line 452 "syn.y"
    {
   (yyvsp[(2) - (2)].g)->a = (yyvsp[(1) - (2)].i);
   (yyvsp[(2) - (2)].g)->t = IC_MEMF;
   (yyval.g) = (yyvsp[(2) - (2)].g);
   }
    break;

  case 65:
/* Line 1787 of yacc.c  */
#line 457 "syn.y"
    {
   (yyvsp[(1) - (3)].g)->a = (yyvsp[(3) - (3)].i);
   (yyvsp[(1) - (3)].g)->t = IC_MEMS;
   (yyval.g) = (yyvsp[(1) - (3)].g);
   }
    break;

  case 66:
/* Line 1787 of yacc.c  */
#line 464 "syn.y"
    {
  struct glue *g = new_glue();
  g->x = (yyvsp[(1) - (5)].i);
  g->y = (yyvsp[(2) - (5)].i);
  g->z = (yyvsp[(4) - (5)].i);
  (yyval.g) = g;
  }
    break;

  case 68:
/* Line 1787 of yacc.c  */
#line 478 "syn.y"
    { (yyval.i) = 1; }
    break;

  case 69:
/* Line 1787 of yacc.c  */
#line 479 "syn.y"
    { (yyval.i) = 0; }
    break;

  case 70:
/* Line 1787 of yacc.c  */
#line 484 "syn.y"
    {
   struct glue *g = new_glue();
   g->x = std_reg((yyvsp[(1) - (2)].i));
   g->y = std_reg((yyvsp[(2) - (2)].i));
   g->t = IC_MOVE;
   (yyval.g) = g;
   }
    break;

  case 71:
/* Line 1787 of yacc.c  */
#line 496 "syn.y"
    {
      if ((yyvsp[(1) - (2)].i) != R_AR && (yyvsp[(1) - (2)].i) != R_AF)
		cerr("ALU destination must be AR or AF");
	  if ((yyvsp[(1) - (2)].i) == R_AF)
		  (yyvsp[(2) - (2)].a)->code |= 0x040000;
	  (yyvsp[(2) - (2)].a)->dest = (yyvsp[(1) - (2)].i);
	  (yyval.a) = (yyvsp[(2) - (2)].a);
	}
    break;

  case 72:
/* Line 1787 of yacc.c  */
#line 504 "syn.y"
    {						/* Discard */
	  if ((yyvsp[(3) - (3)].a)->code & 0x0000ff)
            cerr("Invalid NONE = <ALU> operation");
	  (yyvsp[(3) - (3)].a)->code = ((yyvsp[(3) - (3)].a)->code & 0x01ff00) | 0x2a00aa;
	  (yyvsp[(3) - (3)].a)->comp = IC_INCOMP;
	  (yyval.a) = (yyvsp[(3) - (3)].a);
	}
    break;

  case 73:
/* Line 1787 of yacc.c  */
#line 511 "syn.y"
    {					/* Division */
      struct insn *i = alloc_insn(0x060000, IC_INCOMP);
	  ulg a,b;
	  if ((a = reg_set((yyvsp[(2) - (4)].i), aluy_regs)) == ~0 || (yyvsp[(2) - (4)].i) == R_AY0 || (b = reg_set((yyvsp[(4) - (4)].i), alux_regs)) == ~0)
		{
		  cerr("Invalid argument of DIVS");
		  a = 0; b = 0;
		}
	  i->code |= (b << 8) | (a << 11);
	  (yyval.a) = i;
	}
    break;

  case 74:
/* Line 1787 of yacc.c  */
#line 522 "syn.y"
    {
      struct insn *i = alloc_insn(0x071000, IC_INCOMP);
	  ulg a;
	  if ((a = reg_set((yyvsp[(2) - (2)].i), alux_regs)) == ~0)
		cerr("Invalid argument of DIVQ");
	  i->code |= (a << 8);
	  (yyval.a) = i;
	}
    break;

  case 75:
/* Line 1787 of yacc.c  */
#line 533 "syn.y"
    { (yyval.a) = alu_op((yyvsp[(1) - (3)].i), (yyvsp[(3) - (3)].i), (yyvsp[(2) - (3)].i), (yyvsp[(2) - (3)].i)); }
    break;

  case 76:
/* Line 1787 of yacc.c  */
#line 534 "syn.y"
    { (yyval.a) = alu_op((yyvsp[(1) - (2)].i), (yyvsp[(2) - (2)].i), 3, 3); }
    break;

  case 77:
/* Line 1787 of yacc.c  */
#line 535 "syn.y"
    { (yyval.a) = alu_op((yyvsp[(1) - (2)].i), (yyvsp[(2) - (2)].i), 2, 2); }
    break;

  case 78:
/* Line 1787 of yacc.c  */
#line 536 "syn.y"
    { (yyval.a) = alu_op((yyvsp[(1) - (2)].i), (yyvsp[(2) - (2)].i), 7, 9); }
    break;

  case 79:
/* Line 1787 of yacc.c  */
#line 537 "syn.y"
    {
      if ((yyvsp[(6) - (6)].i) != 1)
		cerr("1 expected instead of %d", (yyvsp[(6) - (6)].i));
	  (yyval.a) = alu_op((yyvsp[(1) - (6)].i), (yyvsp[(2) - (6)].i), 6, 10);
	}
    break;

  case 80:
/* Line 1787 of yacc.c  */
#line 542 "syn.y"
    {
      if (IS_ALU_YOP((yyvsp[(2) - (2)].i)))				/* Here begin dirty tricks */
		(yyval.a) = alu_op(~0, (yyvsp[(2) - (2)].i), 0, ~0);
	  else
		(yyval.a) = alu_op((yyvsp[(2) - (2)].i), ~0, 3, ~0);		/* ADD 0 */
	}
    break;

  case 81:
/* Line 1787 of yacc.c  */
#line 548 "syn.y"
    {
      if (IS_ALU_YOP((yyvsp[(2) - (2)].i)))
		(yyval.a) = alu_op(~0, (yyvsp[(2) - (2)].i), 5, ~0);
	  else
		(yyval.a) = alu_op((yyvsp[(2) - (2)].i), ~0, 9, ~0);
	}
    break;

  case 82:
/* Line 1787 of yacc.c  */
#line 554 "syn.y"
    {
      if (IS_ALU_YOP((yyvsp[(2) - (2)].i)))
		(yyval.a) = alu_op(~0, (yyvsp[(2) - (2)].i), 4, ~0);
	  else
		(yyval.a) = alu_op((yyvsp[(2) - (2)].i), R_AY0, 11, ~0);	/* R_AY0 instead of ~0 to be binary compatible with original assembler */
	}
    break;

  case 83:
/* Line 1787 of yacc.c  */
#line 560 "syn.y"
    { (yyval.a) = alu_op((yyvsp[(2) - (2)].i), R_AY0, 15, ~0); }
    break;

  case 84:
/* Line 1787 of yacc.c  */
#line 561 "syn.y"
    { (yyval.a) = alu_addi((yyvsp[(1) - (2)].i), (yyvsp[(2) - (2)].i), 0); }
    break;

  case 85:
/* Line 1787 of yacc.c  */
#line 562 "syn.y"
    { (yyval.a) = alu_addi((yyvsp[(1) - (2)].i), -(yyvsp[(2) - (2)].i), 1); }
    break;

  case 86:
/* Line 1787 of yacc.c  */
#line 563 "syn.y"
    {
      ulg k = (yyvsp[(2) - (2)].i);
	  if (k == 0)
		(yyval.a) = alu_op(R_AX0, ~0, 0, ~0);	/* PASS 0 */
	  else if (k == ~0)
		(yyval.a) = alu_op(R_AX0, ~0, 8, ~0);	/* PASS ~0 */
	  else if (k == 1)
		(yyval.a) = alu_op(R_AX0, ~0, 1, ~0);	/* PASS 1 */
	  else if ((k = resolve_aluc((yyvsp[(2) - (2)].i), 1)) != ~0)
		(yyval.a) = alu_num(R_AX0, k, 0);		/* PASS y */
	  else if ((k = resolve_aluc((yyvsp[(2) - (2)].i) + 1, 1)) != ~0)
		(yyval.a) = alu_num(R_AX0, k, 8);		/* DEC y */
	  else
		{
		  k = resolve_aluc((yyvsp[(2) - (2)].i) - 1, 0);
		  (yyval.a) = alu_num(R_AX0, k, 1);	/* INC y */
		}
	}
    break;

  case 87:
/* Line 1787 of yacc.c  */
#line 581 "syn.y"
    {
      ulg aflag = (yyvsp[(1) - (4)].i) & 0x80;
	  ulg op = (yyvsp[(1) - (4)].i) & 0x7f;
	  ulg bit = 1<<(yyvsp[(2) - (4)].i);

	  if ((yyvsp[(2) - (4)].i) >= 16 || (yyvsp[(2) - (4)].i) < 0)
		cerr("Invalid bit number");
	  (yyval.a) = alu_num((yyvsp[(4) - (4)].i), resolve_aluc(aflag ? ~bit : bit, 0), op);
	}
    break;

  case 88:
/* Line 1787 of yacc.c  */
#line 593 "syn.y"
    { (yyval.i) = (yyvsp[(1) - (2)].i); }
    break;

  case 89:
/* Line 1787 of yacc.c  */
#line 594 "syn.y"
    { (yyval.i) = ~0; }
    break;

  case 90:
/* Line 1787 of yacc.c  */
#line 598 "syn.y"
    { (yyval.i) = (yyvsp[(1) - (2)].i); }
    break;

  case 91:
/* Line 1787 of yacc.c  */
#line 602 "syn.y"
    { (yyval.i) = (yyvsp[(1) - (2)].i); }
    break;

  case 92:
/* Line 1787 of yacc.c  */
#line 606 "syn.y"
    { (yyval.i) = 12; }
    break;

  case 93:
/* Line 1787 of yacc.c  */
#line 607 "syn.y"
    { (yyval.i) = 13; }
    break;

  case 94:
/* Line 1787 of yacc.c  */
#line 608 "syn.y"
    { (yyval.i) = 14; }
    break;

  case 95:
/* Line 1787 of yacc.c  */
#line 612 "syn.y"
    { (yyval.i) = 12; }
    break;

  case 96:
/* Line 1787 of yacc.c  */
#line 613 "syn.y"
    { (yyval.i) = 13; }
    break;

  case 97:
/* Line 1787 of yacc.c  */
#line 614 "syn.y"
    { (yyval.i) = 0x8c; }
    break;

  case 98:
/* Line 1787 of yacc.c  */
#line 615 "syn.y"
    { (yyval.i) = 14; }
    break;

  case 99:
/* Line 1787 of yacc.c  */
#line 619 "syn.y"
    { (yyval.i) = (yyvsp[(1) - (2)].i); }
    break;

  case 100:
/* Line 1787 of yacc.c  */
#line 622 "syn.y"
    {
   node *n = (yyvsp[(1) - (1)].n);
   if (!resolve_expr(&n))
	 {
	   cerr("Absolute expression expected");
	   (yyval.i) = 0;
	 }
   else
	 (yyval.i) = expr_to_num(n);
   }
    break;

  case 101:
/* Line 1787 of yacc.c  */
#line 637 "syn.y"
    {
	 (yyvsp[(3) - (3)].a)->code |= (yyvsp[(1) - (3)].i);
	 (yyval.a) = (yyvsp[(3) - (3)].a);
   }
    break;

  case 102:
/* Line 1787 of yacc.c  */
#line 644 "syn.y"
    { (yyval.i) = 0; }
    break;

  case 103:
/* Line 1787 of yacc.c  */
#line 645 "syn.y"
    { (yyval.i) = 0x240000; }
    break;

  case 104:
/* Line 1787 of yacc.c  */
#line 649 "syn.y"
    {
	 ulg op = ((yyvsp[(1) - (1)].a)->code & 0x01e000) >> 13;
	 if (op < 4)
	   op += 4;
	 else
	   op = 1;
	 (yyvsp[(1) - (1)].a)->code = ((yyvsp[(1) - (1)].a)->code & 0xfe1fff) | (op << 13);
	 (yyval.a) = (yyvsp[(1) - (1)].a);
   }
    break;

  case 105:
/* Line 1787 of yacc.c  */
#line 658 "syn.y"
    {
     ulg op = ((yyvsp[(2) - (2)].a)->code & 0x01e000) >> 13;
	 if (op < 4)
	   op |= (8 + (yyvsp[(1) - (2)].i));
	 else
	   op = 2 + ((yyvsp[(1) - (2)].i) >> 2);
	 (yyvsp[(2) - (2)].a)->code = ((yyvsp[(2) - (2)].a)->code & 0xfe1fff) | (op << 13);
	 (yyval.a) = (yyvsp[(2) - (2)].a);
   }
    break;

  case 106:
/* Line 1787 of yacc.c  */
#line 667 "syn.y"
    { (yyval.a) = alloc_insn(0x211800, IC_MAC); }
    break;

  case 107:
/* Line 1787 of yacc.c  */
#line 668 "syn.y"
    {
      if ((yyvsp[(2) - (2)].i) != MC_RND)
		cerr("Only (RND) allowed here");
	  (yyval.a) = alloc_insn(0x205800, IC_MAC);
	}
    break;

  case 108:
/* Line 1787 of yacc.c  */
#line 673 "syn.y"
    {
      node *n = (yyvsp[(1) - (1)].n);
	  if (!resolve_expr(&n) || expr_to_num(n))
		cerr("Only zero may be used here");
	  (yyval.a) = alloc_insn(0x209800, IC_MAC);
	}
    break;

  case 109:
/* Line 1787 of yacc.c  */
#line 682 "syn.y"
    { (yyval.i) = 0; }
    break;

  case 110:
/* Line 1787 of yacc.c  */
#line 683 "syn.y"
    { (yyval.i) = 4; }
    break;

  case 111:
/* Line 1787 of yacc.c  */
#line 687 "syn.y"
    {
      struct insn *i = alloc_insn(0x200000, IC_MAC);
	  ulg a,b;
	  a = reg_set((yyvsp[(1) - (4)].i), macx_regs);
	  b = reg_set((yyvsp[(3) - (4)].i), macy_regs);
	  if (a != ~0 && b != ~0)			/* Standard multiplication */
		i->code |= (a << 8) | (b << 11);
	  else if (a != ~0 && (b = reg_set((yyvsp[(3) - (4)].i), macx_regs)) != ~0 && a == b)
		{								/* Square */
		  if ((yyvsp[(4) - (4)].i) != MC_SS && (yyvsp[(4) - (4)].i) != MC_UU && (yyvsp[(4) - (4)].i) != MC_RND)
			cerr("Only SS, SU and RND modes may be used for square operation");
		  i->code |= (a << 8) | 0x10;
		  i->comp = IC_ICMAC;
		}
	  else
		cerr("Invalid multiplication");
	  i->code |= ((yyvsp[(4) - (4)].i) << 13);
	  (yyval.a) = i;
   }
    break;

  case 112:
/* Line 1787 of yacc.c  */
#line 709 "syn.y"
    { (yyval.i) = (yyvsp[(1) - (1)].i); }
    break;

  case 113:
/* Line 1787 of yacc.c  */
#line 710 "syn.y"
    { (yyval.i) = R_MF; }
    break;

  case 114:
/* Line 1787 of yacc.c  */
#line 716 "syn.y"
    {
	 if ((yyvsp[(6) - (6)].i) == SC_HIX)
	   cerr("(HIX) not allowed here");
	 (yyvsp[(5) - (6)].a)->code |= ((yyvsp[(4) - (6)].i) << 13) | ((yyvsp[(6) - (6)].i) << 12) | (yyvsp[(3) - (6)].i);
	 (yyval.a) = (yyvsp[(5) - (6)].a);
   }
    break;

  case 115:
/* Line 1787 of yacc.c  */
#line 722 "syn.y"
    {
	 if ((yyvsp[(1) - (4)].i) != R_SE)
	   cerr("Destination of EXP must be the SE register");
     if ((yyvsp[(4) - (4)].i) == SC_HIX)
	   (yyvsp[(3) - (4)].a)->code |= 0x800;
	 else
	   (yyvsp[(3) - (4)].a)->code |= ((yyvsp[(4) - (4)].i) << 12);
	 (yyvsp[(3) - (4)].a)->code |= 0x006000;
	 (yyval.a) = (yyvsp[(3) - (4)].a);
   }
    break;

  case 116:
/* Line 1787 of yacc.c  */
#line 732 "syn.y"
    {
     if ((yyvsp[(1) - (3)].i) != R_SB)
	   cerr("Destination of EXPADJ must be the SB register");
	 (yyvsp[(3) - (3)].a)->code |= 0x007800;
	 (yyval.a) = (yyvsp[(3) - (3)].a);
   }
    break;

  case 117:
/* Line 1787 of yacc.c  */
#line 738 "syn.y"
    { (yyval.a) = alloc_insn(0x050000, IC_SAT); }
    break;

  case 118:
/* Line 1787 of yacc.c  */
#line 742 "syn.y"
    {
	 struct insn *i = alloc_insn(0x0e0000, IC_SHIFT);
	 ulg r = reg_set((yyvsp[(1) - (1)].i), shix_regs);
	 if (r == ~0)
	   cerr("Invalid register for shifter operation");
     i->code |= (r << 8);
     (yyval.a) = i;
   }
    break;

  case 120:
/* Line 1787 of yacc.c  */
#line 754 "syn.y"
    {
      node *n = (yyvsp[(3) - (3)].n);
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
	  (yyvsp[(1) - (3)].a)->code |= 0x010000 | (c & 0xff);
	  (yyvsp[(1) - (3)].a)->comp = IC_INCOMP;
	  (yyval.a) = (yyvsp[(1) - (3)].a);
   }
    break;

  case 121:
/* Line 1787 of yacc.c  */
#line 775 "syn.y"
    { (yyval.i) = 1; }
    break;

  case 122:
/* Line 1787 of yacc.c  */
#line 776 "syn.y"
    { (yyval.i) = 0; }
    break;

  case 123:
/* Line 1787 of yacc.c  */
#line 777 "syn.y"
    { (yyval.i) = 2; }
    break;

  case 124:
/* Line 1787 of yacc.c  */
#line 781 "syn.y"
    { (yyval.i) = 0; }
    break;

  case 125:
/* Line 1787 of yacc.c  */
#line 782 "syn.y"
    { (yyval.i) = 0x800; }
    break;

  case 126:
/* Line 1787 of yacc.c  */
#line 788 "syn.y"
    {
	 (yyval.a) = alloc_insn(0x0d010f, IC_INCOMP);
	 (yyval.a)->code |= (d_reg((yyvsp[(1) - (2)].i)) << 4);
   }
    break;

  case 127:
/* Line 1787 of yacc.c  */
#line 792 "syn.y"
    {
     (yyval.a) = alloc_insn(0x0d04f0, IC_INCOMP);
	 (yyval.a)->code |= d_reg((yyvsp[(3) - (3)].i));
   }
    break;

  case 128:
/* Line 1787 of yacc.c  */
#line 796 "syn.y"
    {
     struct insn *i = alloc_insn(0x400000, IC_INCOMP);
	 i->expr = (yyvsp[(2) - (2)].n);
	 if ((yyvsp[(1) - (2)].i) < 16)						/* DREG */
	   {
		 i->flags = IF_IMM16;
		 i->code |= (yyvsp[(1) - (2)].i);
	   }
	 else
	   {
		 ulg k = std_reg((yyvsp[(1) - (2)].i));
		 i->flags = IF_IMM14;
		 i->code = (k & 0x0f) | ((k & 0x30) << 14) | 0x300000;
	   }
	 (yyval.a) = i;
   }
    break;

  case 129:
/* Line 1787 of yacc.c  */
#line 812 "syn.y"
    {
     struct insn *i = alloc_insn(0x010000, IC_INCOMP);
	 i->flags = IF_IMM11;
	 i->expr = (yyvsp[(2) - (2)].n);
	 i->code |= d_reg((yyvsp[(1) - (2)].i));
	 (yyval.a) = i;
   }
    break;

  case 130:
/* Line 1787 of yacc.c  */
#line 819 "syn.y"
    {
     struct insn *i = alloc_insn(0x018000, IC_INCOMP);
	 i->flags = IF_IMM11;
	 i->expr = (yyvsp[(1) - (3)].n);
	 i->code |= d_reg((yyvsp[(3) - (3)].i));
	 (yyval.a) = i;
   }
    break;

  case 131:
/* Line 1787 of yacc.c  */
#line 826 "syn.y"
    { (yyval.a) = alloc_insn(0, IC_INCOMP); }
    break;

  case 132:
/* Line 1787 of yacc.c  */
#line 827 "syn.y"
    { (yyval.a) = alloc_insn(0x028000, IC_INCOMP); }
    break;

  case 133:
/* Line 1787 of yacc.c  */
#line 828 "syn.y"
    {
      struct insn *i = alloc_insn(0x028000, IC_INCOMP);
      node *n = (yyvsp[(2) - (2)].n);
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
	  (yyval.a) = i;
	}
    break;

  case 134:
/* Line 1787 of yacc.c  */
#line 843 "syn.y"
    {
      struct insn *i = alloc_insn(0x090000, IC_INCOMP);
	  if ((yyvsp[(3) - (6)].i) >= R_I0 && (yyvsp[(3) - (6)].i) <= R_I3 && (yyvsp[(5) - (6)].i) >= R_M0 && (yyvsp[(5) - (6)].i) <= R_M3)
		i->code |= ((yyvsp[(5) - (6)].i) - R_M0) | (((yyvsp[(3) - (6)].i) - R_I0) << 2);
	  else if ((yyvsp[(3) - (6)].i) >= R_I4 && (yyvsp[(3) - (6)].i) <= R_I7 && (yyvsp[(5) - (6)].i) >= R_M4 && (yyvsp[(5) - (6)].i) <= R_M7)
		i->code |= ((yyvsp[(5) - (6)].i) - R_M4) | (((yyvsp[(3) - (6)].i) - R_I4) << 2) | 0x10;
	  else
		cerr("Invalid register combination for MODIFY");
	  (yyval.a) = i;
	}
    break;

  case 135:
/* Line 1787 of yacc.c  */
#line 853 "syn.y"
    {
      (yyval.a) = alloc_insn(0x040002, IC_PUSHPOP);
	  if ((yyvsp[(2) - (2)].i) != PP_STS)
		cerr("Only STS may be pushed");
	}
    break;

  case 136:
/* Line 1787 of yacc.c  */
#line 858 "syn.y"
    { (yyval.a) = alloc_insn(0x040000 | (yyvsp[(2) - (2)].i), IC_PUSHPOP); }
    break;

  case 137:
/* Line 1787 of yacc.c  */
#line 859 "syn.y"
    {
      (yyval.a) = alloc_insn(0x040040, IC_INCOMP);
	  if ((yyvsp[(1) - (2)].i))
		(yyval.a)->code |= 0x20;
	}
    break;

  case 138:
/* Line 1787 of yacc.c  */
#line 864 "syn.y"
    {
      (yyval.a) = alloc_insn(0x0c0000 | (yyvsp[(2) - (2)].i), IC_ENADIS);
	  if ((yyvsp[(1) - (2)].i))
		(yyval.a)->code |= ((yyvsp[(2) - (2)].i) >> 1);
	}
    break;

  case 139:
/* Line 1787 of yacc.c  */
#line 869 "syn.y"
    { (yyval.a) = alloc_insn(0x020000 + ((yyvsp[(1) - (2)].i) << (yyvsp[(2) - (2)].i)), IC_FLAGS); }
    break;

  case 140:
/* Line 1787 of yacc.c  */
#line 870 "syn.y"
    {
      struct insn *i = alloc_insn(0x140000, IC_INCOMP);
	  i->expr = (yyvsp[(2) - (3)].n);
	  i->flags = IF_IMM14;
	  i->code |= (yyvsp[(3) - (3)].i);
	  (yyval.a) = i;
	}
    break;

  case 141:
/* Line 1787 of yacc.c  */
#line 877 "syn.y"
    { (yyval.a) = alloc_insn(0x0a0000, IC_IFIN); }
    break;

  case 142:
/* Line 1787 of yacc.c  */
#line 878 "syn.y"
    { (yyval.a) = alloc_insn(0x0a0010, IC_IFIN); }
    break;

  case 143:
/* Line 1787 of yacc.c  */
#line 879 "syn.y"
    {
      struct insn *i = alloc_insn(0x0b0000, IC_IFIN);
	  if ((yyvsp[(3) - (4)].i) < R_I4 || (yyvsp[(3) - (4)].i) > R_I7)
		cerr("CALL/JUMP allowed only for I4 to I7");
	  else
		i->code |= (((yyvsp[(3) - (4)].i) - R_I4) << 6) | ((yyvsp[(1) - (4)].i) << 4);
	  (yyval.a) = i;
	}
    break;

  case 144:
/* Line 1787 of yacc.c  */
#line 887 "syn.y"
    {
      struct insn *i = alloc_insn((yyvsp[(1) - (2)].i) ? 0x1c0000 : 0x180000, IC_JUMP);
	  i->expr = (yyvsp[(2) - (2)].n);
	  i->flags = IF_IMM14;
	  (yyval.a) = i;
	}
    break;

  case 145:
/* Line 1787 of yacc.c  */
#line 893 "syn.y"
    {
      struct insn *i = alloc_insn(0x800000, IC_INCOMP);
      int reg = std_reg((yyvsp[(1) - (4)].i));
	  i->code |= (reg & 0x0f) | ((reg & 0x30) << 14);
	  i->expr = (yyvsp[(3) - (4)].n);
	  i->flags = IF_IMM14;
	  if ((yyvsp[(2) - (4)].i))
		cerr("Only DM allowed here");
	  (yyval.a) = i;
	}
    break;

  case 146:
/* Line 1787 of yacc.c  */
#line 903 "syn.y"
    {
      struct insn *i = alloc_insn(0x900000, IC_INCOMP);
      int reg = std_reg((yyvsp[(5) - (5)].i));
	  i->code |= (reg & 0x0f) | ((reg & 0x30) << 14);
	  i->expr = (yyvsp[(2) - (5)].n);
	  i->flags = IF_IMM14;
	  if ((yyvsp[(1) - (5)].i))
		cerr("Only DM allowed here");
	  (yyval.a) = i;
	}
    break;

  case 147:
/* Line 1787 of yacc.c  */
#line 913 "syn.y"
    {
      struct insn *i = alloc_insn(0xa00000, IC_INCOMP);
	  struct glue *g = (yyvsp[(1) - (3)].g);

	  if (g->x)
		cerr("Only DM can be used for the `store immediate' operation");
	  if (g->y >= R_I0 && g->y <= R_I3 && g->z >= R_M0 && g->z <= R_M3)
		i->code |= ((g->y - R_I0) << 2) | (g->z - R_M0);
	  else if (g->y >= R_I4 && g->y <= R_I7 && g->z >= R_M4 && g->z <= R_M7)
		i->code |= 0x100000 | ((g->y - R_I4) << 2) | (g->z - R_M4);
	  else
		cerr("Invalid register combination for DM transfer");
	  i->expr = (yyvsp[(3) - (3)].n);
	  i->flags = IF_IMM16;
	  free(g);
	  (yyval.a) = i;
	}
    break;

  case 149:
/* Line 1787 of yacc.c  */
#line 934 "syn.y"
    {
      if ((yyvsp[(1) - (1)].i) == R_CNTR)
	     (yyval.i) = PP_CNTR;
	  else
		cerr("Invalid register for PUSH/POP");
	}
    break;

  case 150:
/* Line 1787 of yacc.c  */
#line 943 "syn.y"
    {
	 (yyval.i) = negate_cond((yyvsp[(2) - (2)].i));
	 if ((yyval.i) > 15)
		cerr("Invalid condition for DO UNTIL");
   }
    break;

  case 151:
/* Line 1787 of yacc.c  */
#line 948 "syn.y"
    { (yyval.i) = C_TRUE; }
    break;

  case 152:
/* Line 1787 of yacc.c  */
#line 949 "syn.y"
    { (yyval.i) = C_TRUE; }
    break;

  case 153:
/* Line 1787 of yacc.c  */
#line 953 "syn.y"
    { (yyval.i) = 3; }
    break;

  case 154:
/* Line 1787 of yacc.c  */
#line 954 "syn.y"
    { (yyval.i) = 2; }
    break;

  case 155:
/* Line 1787 of yacc.c  */
#line 955 "syn.y"
    { (yyval.i) = 1; }
    break;

  case 156:
/* Line 1787 of yacc.c  */
#line 959 "syn.y"
    { (yyval.n) = (yyvsp[(3) - (4)].n); }
    break;

  case 157:
/* Line 1787 of yacc.c  */
#line 963 "syn.y"
    { (yyval.i) = 1; }
    break;

  case 158:
/* Line 1787 of yacc.c  */
#line 964 "syn.y"
    { (yyval.i) = 0; }
    break;

  case 159:
/* Line 1787 of yacc.c  */
#line 968 "syn.y"
    { (yyval.i) = 1; }
    break;

  case 160:
/* Line 1787 of yacc.c  */
#line 969 "syn.y"
    { (yyval.i) = 0; }
    break;

  case 161:
/* Line 1787 of yacc.c  */
#line 973 "syn.y"
    { (yyval.i) = (yyvsp[(1) - (1)].i); }
    break;

  case 162:
/* Line 1787 of yacc.c  */
#line 974 "syn.y"
    { (yyval.i) = negate_cond((yyvsp[(2) - (2)].i)); }
    break;

  case 163:
/* Line 1787 of yacc.c  */
#line 980 "syn.y"
    {
	 struct numeric *n = NEW_NODE(numeric, N_NUM);
	 n->value = (yyvsp[(1) - (1)].i);
	 (yyval.n) = NODE n;
   }
    break;

  case 164:
/* Line 1787 of yacc.c  */
#line 985 "syn.y"
    {
     (yyval.n) = (yyvsp[(2) - (3)].n);
   }
    break;

  case 165:
/* Line 1787 of yacc.c  */
#line 988 "syn.y"
    { (yyval.n) = add_binary('+', (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); }
    break;

  case 166:
/* Line 1787 of yacc.c  */
#line 989 "syn.y"
    { (yyval.n) = add_binary('-', (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); }
    break;

  case 167:
/* Line 1787 of yacc.c  */
#line 990 "syn.y"
    { (yyval.n) = add_binary('*', (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); }
    break;

  case 168:
/* Line 1787 of yacc.c  */
#line 991 "syn.y"
    { (yyval.n) = add_binary('/', (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); }
    break;

  case 169:
/* Line 1787 of yacc.c  */
#line 992 "syn.y"
    { (yyval.n) = add_binary('&', (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); }
    break;

  case 170:
/* Line 1787 of yacc.c  */
#line 993 "syn.y"
    { (yyval.n) = add_binary('|' , (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); }
    break;

  case 171:
/* Line 1787 of yacc.c  */
#line 994 "syn.y"
    { (yyval.n) = add_binary('^', (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); }
    break;

  case 172:
/* Line 1787 of yacc.c  */
#line 995 "syn.y"
    { (yyval.n) = add_binary('<' , (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); }
    break;

  case 173:
/* Line 1787 of yacc.c  */
#line 996 "syn.y"
    { (yyval.n) = add_binary('>' , (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n)); }
    break;

  case 174:
/* Line 1787 of yacc.c  */
#line 997 "syn.y"
    { (yyval.n) = add_unary('-', (yyvsp[(2) - (2)].n)); }
    break;

  case 175:
/* Line 1787 of yacc.c  */
#line 998 "syn.y"
    { (yyval.n) = add_unary('~', (yyvsp[(2) - (2)].n)); }
    break;

  case 176:
/* Line 1787 of yacc.c  */
#line 999 "syn.y"
    { (yyval.n) = add_unary('|', (yyvsp[(2) - (2)].n)); }
    break;

  case 177:
/* Line 1787 of yacc.c  */
#line 1000 "syn.y"
    { (yyval.n) = add_unary('^', (yyvsp[(2) - (2)].n)); }
    break;

  case 178:
/* Line 1787 of yacc.c  */
#line 1001 "syn.y"
    { (yyval.n) = add_unary('%', (yyvsp[(2) - (2)].n)); }
    break;

  case 179:
/* Line 1787 of yacc.c  */
#line 1002 "syn.y"
    {
    struct symref *n = NEW_NODE(symref, N_SYMREF);
	n->sym = (yyvsp[(1) - (1)].s);
	(yyval.n) = NODE n;
  }
    break;


/* Line 1787 of yacc.c  */
#line 3262 "syn.tab.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2050 of yacc.c  */
#line 1009 "syn.y"


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

/* A Bison parser, made by GNU Bison 2.7.12-4996.  */

/* Bison interface for Yacc-like parsers in C
   
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
/* Line 2053 of yacc.c  */
#line 62 "syn.y"

  int i;
  struct symbol *s;
  node *n;
  struct memblock *m;
  struct var *v;
  struct glue *g;
  struct insn *a;
  struct insar *r;


/* Line 2053 of yacc.c  */
#line 143 "syn.tab.h"
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

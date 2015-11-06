%{ 	/* Hey, Emacs, this is -*- C -*- */

/*
 *		ADSP 2181 Assembler -- Keyword Table
 *
 *		(c) 1996 Martin Mares, <mj@k332.feld.cvut.cz>
 *
 *		This software may be freely distributed and used according to the terms
 *		of the GNU General Public License. See file COPYING in any of the GNU utilities.
 */

#include <string.h>

#include "as2181.h"
#include "syn.tab.h"
%}
struct as_kwd {
  char *name;
  word class;
  word value;
};
%%
AX0,			REG,			R_AX0
AX1,			REG,			R_AX1
MX0,			REG,			R_MX0
MX1,			REG,			R_MX1
AY0,			REG,			R_AY0
AY1,			REG,			R_AY1
MY0,			REG,			R_MY0
MY1,			REG,			R_MY1
SI,				REG,			R_SI
SE,				REG,			R_SE
AR,				REG,			R_AR
MR0,			REG,			R_MR0
MR1,			REG,			R_MR1
MR2,			REG,			R_MR2
SR0,			REG,			R_SR0
SR1,			REG,			R_SR1
I0,				REG,			R_I0
I1,				REG,			R_I1
I2,				REG,			R_I2
I3,				REG,			R_I3
M0,				REG,			R_M0
M1,				REG,			R_M1
M2,				REG,			R_M2
M3,				REG,			R_M3
L0,				REG,			R_L0
L1,				REG,			R_L1
L2,				REG,			R_L2
L3,				REG,			R_L3
I4,				REG,			R_I4
I5,				REG,			R_I5
I6,				REG,			R_I6
I7,				REG,			R_I7
M4,				REG,			R_M4
M5,				REG,			R_M5
M6,				REG,			R_M6
M7,				REG,			R_M7
L4,				REG,			R_L4
L5,				REG,			R_L5
L6,				REG,			R_L6
L7,				REG,			R_L7
ASTAT,			REG,			R_ASTAT
MSTAT,			REG,			R_MSTAT
SSTAT,			REG,			R_SSTAT
IMASK,			REG,			R_IMASK
ICNTL,			REG,			R_ICNTL
SB,				REG,			R_SB
PX,				REG,			R_PX
RX0,			REG,			R_RX0
TX0,			REG,			R_TX0
RX1,			REG,			R_RX1
TX1,			REG,			R_TX1
IFC,			REG,			R_IFC
OWRCNTR,		REG,			R_OWRCNTR
AF,				REG,			R_AF
C,				CARRY,			0
AND,	   		AND,			0
OR,				OR,			0
XOR,			XOR,			0
IF,				IF,			0
PASS,			PASS,			0
NOT,			NOT,			0
ABS,			ABS,			0
DIVS,			DIVS,			0
DIVQ,			DIVQ,			0
TSTBIT,			TSTBIT,			0
SETBIT,			SETBIT,			0
CLRBIT,			CLRBIT,			0
TGLBIT,			TGLBIT,			0
DM,				DM,			0
PM,				PM,			0
IO,				IO,			0
ASHIFT,			ASHIFT,			0
LSHIFT,			LSHIFT,			0
NORM,			NORM,			0
EXP,			EXP,			0
EXPADJ,		   	EXPADJ,			0
BY,				BY,			0
DMOVLAY,		DMOVLAY,			0
DO,				DO,			0
UNTIL,			UNTIL,			0
JUMP,			JUMP,			0
CALL,			CALL,			0
FLAG_IN,		FLAG_IN,			0
RTS,			RTS,			0
RTI,			RTI,			0
IDLE,			IDLE,			0
NOP,			NOP,			0
MODIFY,			MODIFY,			0
PUSH,			PUSH,			0
POP,			POP,			0
SET,			SET,			0
RESET,			RESET,			0
TOGGLE,			TOGGLE,			0
ENA,			ENA,			0
DIS,			DIS,			0
FOREVER,		FOREVER,			0
EQ,				COND,			C_EQ
NE,				COND,			C_NE
GT,				COND,			C_GT
LE,				COND,			C_LE
LT,				COND,			C_LT
GE,				COND,			C_GE
AV,				COND,			C_AV
AC,				COND,			C_AC
NEG,			COND,			C_NEG
POS,			COND,			C_POS
MV,				COND,			C_MV
CE,				COND,			C_CE
FLAG_OUT,		FLAG,			FL_OUT
FL0,			FLAG,			FL_0
FL1,			FLAG,			FL_1
FL2,			FLAG,			FL_2
STS,			POPREG,			PP_STS
CNTR,			REG,			R_CNTR
LOOP,			POPREG,			PP_LOOP
PC,				POPREG,			PP_PC
SEC_REG,		ENADISREG,			ED_SEC_REG
BIT_REV,		ENADISREG,			ED_BIT_REV
AV_LATCH,		ENADISREG,			ED_AV_LATCH
AR_SAT,			ENADISREG,			ED_AR_SAT
M_MODE,			ENADISREG,			ED_M_MODE
TIMER,			ENADISREG,			ED_TIMER
G_MODE,			ENADISREG,			ED_G_MODE
INTS,			INTS,			0
.VAR,			VAR,			0
.MODULE,		MODULE,			0
.ENDMOD,		ENDMOD,			0
.CONST,			CONST,			0
.INIT,			INIT,			0
.ENTRY,			ENTRY,			0
.EXTERNAL,		EXTERNAL,		0
.GLOBAL,	    GLOBAL,			0
CIRC,			CIRC,			0
ROM,			ROM,			0
RAM,			RAM,			0
NONE,			NONE,			0
OF,				OF,				0
SAT,			SAT,			0

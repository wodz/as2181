/*
 *		ADSP Utilities -- Global Declarations
 *
 *		(c) 1996 Martin Mares, <mj@k332.feld.cvut.cz>
 *
 *		This software may be freely distributed and used according to the terms
 *		of the GNU General Public License. See file COPYING in any of the GNU utilities.
 */

#include <stdint.h>
#define NONRET __attribute__ ((noreturn))

typedef uint32_t ulg;
typedef uint16_t word;
typedef uint8_t byte;

#ifndef NULL
#define NULL ((void *)0)
#endif

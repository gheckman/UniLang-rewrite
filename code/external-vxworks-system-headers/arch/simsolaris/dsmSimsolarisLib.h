/* dsmSparcLib.h - header for Sparc disassembler library */

/* Copyright 1984-2004, 2010 Wind River Systems, Inc. */
/*
modification history
--------------------
01n,29apr10,pad  Moved extern C statement after include statements.
01m,10may04,dbt  updated prototypes for dsmData() and dsmInst()
01l,22apr04,jmp  move instruction fields to instrSparc.h.
01k,15mar96,dat  changed RD to DR, name conflict with streams pkg
01j,22sep92,rrr  added support for c++
01i,26may92,jwt  upgraded to SPARC Version 8.
01h,26may92,rrr  the tree shuffle
01g,09jan92,jwt  added ANSI function prototypes.
01f,19dec91,jwt  passed through the ansification filter
		  -fixed #else and #endif
		  -changed copyright notice
01e,27apr89,mcl  changed to dsmSparcLib.h; changes trap mask.
01d,07apr89,mcl  adds more SHIFT_CT fields; changes OPC to OPFC; bug in RS1_i4.
01c,06apr89,mcl  adds f[x] fields.
01b,05apr89,mcl  adds itClr and itClrAsi.
01a,05aug88,mcl  written by adapting version 01j of 26oct87 of dsmLib.h.
*/

#ifndef __INCdsmSparcLibh
#define __INCdsmSparcLibh

#include "vwModNum.h"
#include "arch/simsolaris/instrSparc.h"

#ifdef __cplusplus
extern "C" {
#endif


/* dsmLib status codes */

#define S_dsmLib_UNKNOWN_INSTRUCTION	(M_dsmLib | 1)

/*
 * The following structure is not size compatible with the
 * one for the Motorola 68k family due to changed word size.
 */

typedef struct
    {
    char *		name;
    unsigned long	op;
    unsigned long	mask;
    int			type;
    } INST;

/* function declarations */

IMPORT int	dsmData		(INSTR * binInst, unsigned int address,
				 FUNCPTR oFn, int oArg);
IMPORT int	dsmInst		(FAST INSTR * binInst, unsigned int address,
                                 VOIDFUNCPTR prtAddress, FUNCPTR oFn, int oArg);
IMPORT int	dsmNbytes	(FAST INSTR *binInst);

#ifdef __cplusplus
}
#endif

#endif /* __INCdsmSparcLibh */

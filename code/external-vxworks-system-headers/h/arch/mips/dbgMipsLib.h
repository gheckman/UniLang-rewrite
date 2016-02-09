/* dbgMipsLib.h - MIPS debugger header */

/*
 * Copyright 1992, 1993, 1996-1999, 2001, 2003-2005, 2008-2009
 *, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
 * This file has been developed or significantly modified by the
 * MIPS Center of Excellence Dedicated Engineering Staff.
 * This notice is as per the MIPS Center of Excellence Master Partner
 * Agreement, do not remove this notice without checking first with
 * WR/Platforms MIPS Center of Excellence engineering management.
 */

/*
modification history
--------------------
01p,29apr10,pad  Moved extern C statement after include statements.
01o,27aug09,pch  CQ159556: remove MIPS16
01n,29oct08,rlg  WIND00115621 - hw breakpoints in user space - add define for
		 watchHi bits
01m,23aug05,rlg  modifications for MIPS 32/64 compliant cores - hw breakpoints
01l,01mar04,pes  Add definition of DBG_SYSCALL_SIZE.
01k,12may03,pes  PAL conditional compilation cleanup. Phase 2.
01j,16jul01,ros  add CofE comment
01i,08sep99,myz  added a few macros for CW4000_16
01h,17mar98,dbt  added definition of DBG_CRET (no cret() support).
01g,30dec97,dbt  modified for new breakpoint scheme
01f,15jul96,kkk  added R4650 support
01e,27sep93,cd   added R4000 support, including hardware breakpoint.
01d,25jul93,caf  removed definition of DBG_TT.  tt() is now supported.
01c,05aug93,jwt  removed DBG_SAVE structure - not used; copyright 1993.
01b,22sep92,rrr  added support for c++
01a,05may92,yao  written based on sparc/dbgLib.c.
*/

#ifndef __INCdbgMipsLibh
#define __INCdbgMipsLibh

#include "dsmLib.h"
#include "iv.h"
#include "esf.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DBG_TRAP_NUM		IV_BP_VEC
#define	DBG_BREAK_INST		0x0000000d
#define DBG_NO_SINGLE_STEP	1	/* no single step support */
#define DBG_CRET		FALSE	/* no cret support */

#define	DBG_BREAK_INST		0x0000000d
#define DBG_SYSCALL_SIZE	1

#define DBG_HARDWARE_BP		1	/* support of hardware breakpoint */
/*
*	modifications for MIPS 32/64 compliant cores - hw breakpoints
*/
#define MAX_WATCH               8       /* # of bp regs for 32/64 compliancy */
/*
*       offsets for indexing into the watch array
*/

#define DBG_WATCHLO_0           0
#define DBG_WATCHHI_0           DBG_WATCHLO_0 + _WRS_INT_REGISTER_SIZE

#define DBG_WATCHLO_1           DBG_WATCHHI_0 + _WRS_INT_REGISTER_SIZE
#define DBG_WATCHHI_1           DBG_WATCHLO_1 + _WRS_INT_REGISTER_SIZE

#define DBG_WATCHLO_2           DBG_WATCHHI_1 + _WRS_INT_REGISTER_SIZE
#define DBG_WATCHHI_2           DBG_WATCHLO_2 + _WRS_INT_REGISTER_SIZE

#define DBG_WATCHLO_3           DBG_WATCHHI_2 + _WRS_INT_REGISTER_SIZE
#define DBG_WATCHHI_3           DBG_WATCHLO_3 + _WRS_INT_REGISTER_SIZE

#define DBG_WATCHLO_4           DBG_WATCHHI_3 + _WRS_INT_REGISTER_SIZE
#define DBG_WATCHHI_4           DBG_WATCHLO_4 + _WRS_INT_REGISTER_SIZE

#define DBG_WATCHLO_5           DBG_WATCHHI_4 + _WRS_INT_REGISTER_SIZE
#define DBG_WATCHHI_5           DBG_WATCHLO_5 + _WRS_INT_REGISTER_SIZE

#define DBG_WATCHLO_6           DBG_WATCHHI_5 + _WRS_INT_REGISTER_SIZE
#define DBG_WATCHHI_6           DBG_WATCHLO_6 + _WRS_INT_REGISTER_SIZE

#define DBG_WATCHLO_7           DBG_WATCHHI_6 + _WRS_INT_REGISTER_SIZE
#define DBG_WATCHHI_7           DBG_WATCHLO_7 + _WRS_INT_REGISTER_SIZE

/*
*  	offsets for wdbRegisterType
*/
#define WDB_REGTYPE_0		0
#define WDB_REGTYPE_1		WDB_REGTYPE_0 + 4  /* add 32 bit offset */
#define WDB_REGTYPE_2		WDB_REGTYPE_1 + 4  /* to each location */
#define WDB_REGTYPE_3		WDB_REGTYPE_2 + 4
#define WDB_REGTYPE_4		WDB_REGTYPE_3 + 4
#define WDB_REGTYPE_5		WDB_REGTYPE_4 + 4
#define WDB_REGTYPE_6		WDB_REGTYPE_5 + 4
#define WDB_REGTYPE_7		WDB_REGTYPE_6 + 4

#ifndef	_ASMLANGUAGE

typedef struct
    {
/*
*	new struct for mips32/64 compliant hw break points
*	can have up to max of 8 register pairs
*/
    struct _watch
	{
	    _RType        watchLo_reg;        /* watch low register */
	    UINT32        watchHi_reg;        /* watch high register */
	}watch[MAX_WATCH];
/*
*	special defines for non compliant hw break points
*	allows old code to work
*/
#define watchLo watch[0].watchLo_reg
#define watchHi watch[0].watchHi_reg
    UINT32      cause;          /* cause register */
/*
*	new for compliant hw break points
*/
    INSTR       *epc;
    VOID        *badVaddr;
    } DBG_REGS;

/* for R4650 */
#define iWatch watchLo
#define dWatch watchHi

#endif /* _ASMLANGUAGE */

#define BRK_INST	0x0	/* hardware instruction breakpoint */
#define BRK_WRITE	0x1	/* hardware data breakpoint for write */
#define BRK_READ	0x2	/* hardware data breakpoint for read */
#define BRK_RW		0x3	/* hardware data breakpoint for read/write */
#define WDB_BRK_INST    0x4     /* hardware instruction type watch reg for */
				/* mips 32/64 compliant hardware */
#define WDB_BRK_DATA    0x3     /* hardware data type watch regs for */
				/* mips 32/64 compliant hardware */
#define WDB_BRK_BOTH    0x7     /* both data and instruction type reg */
				/* for mips 32/64 compliant */

#define WDB_REG_CHK     0x80000000 /* mask for msb - used to determine */
				   /* if more watchLo and watchHi present */
#define WDB_REG_WP_CLR  0xffbfffff /* mask for watch point bit in cause reg */

#define DEFAULT_HW_BP	BRK_RW	/* default hardware breakpoint */

#define BRK_HARDWARE    0x10	/* hardware breakpoint bit */
#define BRK_HARDMASK    0x03	/* hardware breakpoint mask */

/*	 definition of watch hi bits */

#define WATCHHI_MBIT 	0x80000000	/* more registers are defined */
#define WATCHHI_GBIT 	0x40000000	/* global bit when set match */
					/* address in any address space */
#define WATCHHI_IBIT	0x00000004	/* set when instr addr match */
#define WATCHHI_RBIT	0x00000002	/* set when read addr match */
#define WATCHHI_WBIT	0x00000001	/* set when write  addr match */
					/* also used to clear the bit */
#define WATCHHI_BITCA	0x00000007	/* clear all bits */

#define WATCHHI_ASID_MASK 0x00ff0000	/* mask to get asid bits */
#define WATCHHI_ASID_SHFT 16		/* shift value to get to asid */

#ifndef _ASMLANGUAGE
#define WDB_CTX_LOAD(pRegs) _wdbDbgCtxLoad (pRegs)
#define WDB_CTX_SAVE(pRegs) _wdbDbgCtxSave (pRegs)
extern void _wdbDbgCtxLoad();
extern int _wdbDbgCtxSave();
#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCdbgMipsLibh */

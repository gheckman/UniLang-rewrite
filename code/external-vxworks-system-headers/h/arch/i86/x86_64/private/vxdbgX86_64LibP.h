/* vxdbgX86_64LibP.h - private X86_64 VxDBG library header file */

/*
 * Copyright (c) 2009-2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use  of this
 * software may be licensed only pursuant to the terms of an applicable Wind
 * River license agreement.
 */

/*
modification history
--------------------
01e,09feb11,rlp  Defined VXDBG_INT_LOCK_LEVEL_COMPUTE macro for both UP and
                 SMP (CQ:WIND00253870).
01d,29apr10,pad  Moved extern C statement after include statements.
01c,06may09,rlp  Added wdbDbgPreBreakpoint and wdbDbgPreTrace prototypes.
01b,24feb09,jb   Update register reference
01a,18feb09,jb   Created from 32-bit version 01d
*/

#ifndef __INCvxdbgX86_64LibPh
#define __INCvxdbgX86_64LibPh

#ifndef _ASMLANGUAGE

#include <vsbConfig.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * This macro returns the <level> parameter modified with the interrupt lock
 * level defined into the <value> parameter. The <level> parameter must be
 * previously get with either intCpuLock() or intRegsLock() API.
 */

#define VXDBG_INT_LOCK_LEVEL_COMPUTE(level, value) \
		((level & ~INT_FLAG) | (value & INT_FLAG))

#ifdef	_WRS_CONFIG_SMP

/* return TRUE if interrupts are locked in specified register set. */

#define	VXDBG_INT_REGS_IS_LOCKED(pRegs)	(((pRegs->rflags & INT_FLAG) == \
		INT_FLAG) ? FALSE : TRUE)

#endif	/* _WRS_CONFIG_SMP */

/* function declarations */

extern void wdbDbgPreBreakpoint (BREAK_ESF * info, long * regs, BOOL hardware);
extern void wdbDbgPreTrace (BREAK_ESF * info, long * regs, BOOL hardware);

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif	/* __INCvxdbgX86_64LibPh */

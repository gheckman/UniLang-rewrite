/* vxdbgI86LibP.h - private I86 VxDBG library header file */

/*
 * Copyright (c) 2007-2008, 2010-2011 Wind River Systems, Inc.  
 *
 * The right to copy, distribute, modify or otherwise make use  of this 
 * software may be licensed only pursuant to the terms of an applicable Wind 
 * River license agreement.
 */

/*
modification history
--------------------
01f,09feb11,rlp  Defined VXDBG_INT_LOCK_LEVEL_COMPUTE macro for both UP and
                 SMP (CQ:WIND00253870).
01e,29apr10,pad  Moved extern C statement after include statements.
01d,27aug08,jpb  Renamed VSB header file
01c,24jun08,jpb  Added include path for kernel configurations options set in
                 vsb.  Renamed _WRS_VX_SMP to _WRS_CONFIG_SMP.
01b,26oct07,rlp  Added the VXDBG_INT_LOCK_LEVEL_COMPUTE macro (CQ:WIND00109321).
01a,11oct07,rlp  Written
*/

#ifndef __INCvxdbgI86LibPh
#define __INCvxdbgI86LibPh

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

#define	VXDBG_INT_REGS_IS_LOCKED(pRegs)	(((pRegs->eflags & INT_FLAG) == \
		INT_FLAG) ? FALSE : TRUE)

#endif	/* _WRS_CONFIG_SMP */

#ifdef __cplusplus
}
#endif

#endif	/* __INCvxdbgI86LibPh */

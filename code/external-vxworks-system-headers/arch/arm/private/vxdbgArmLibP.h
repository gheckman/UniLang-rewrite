/* vxdbgArmLibP.h - private ARM VxDBG library header file */

/*
 * Copyright (c) 2007-2012 Wind River Systems, Inc.  
 *
 * The right to copy, distribute, modify or otherwise make use  of this 
 * software may be licensed only pursuant to the terms of an applicable Wind 
 * River license agreement.
 */

/*
modification history
--------------------
01h,24apr12,jdw  Update for ARM-M
01g,09feb11,rlp  Defined VXDBG_INT_LOCK_LEVEL_COMPUTE macro for both UP and
                 SMP (CQ:WIND00253870).
01f,29apr10,pad  Moved extern C statement after include statements.
01e,25feb09,j_b  merge ARM SMP support:
                 12nov07,jmp  Added support for VxDBG cpu control library.
01d,27aug08,jpb  Renamed VSB header file
01c,24jun08,jpb  Added include path for kernel configurations options set in
                 vsb.  Renamed _WRS_VX_SMP to _WRS_CONFIG_SMP.
01b,26oct07,rlp  Added the VXDBG_INT_LOCK_LEVEL_COMPUTE macro (CQ:WIND00109321).
01a,11oct07,rlp  Written
*/

#ifndef __INCvxdbgArmLibPh
#define __INCvxdbgArmLibPh

	
#include <vsbConfig.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * This macro returns the <level> parameter modified with the interrupt lock
 * level defined into the <value> parameter. The <level> parameter must be
 * previously get with either intCpuLock() or intRegsLock() API.
 */
#if (CPU == ARMARCH7M)
#define VXDBG_INT_LOCK_LEVEL_COMPUTE(level, value) \
		((level & ~PRIMASK_PM) | (value & PRIMASK_PM))
#else /* CPU == ARMARCH7M */
#define VXDBG_INT_LOCK_LEVEL_COMPUTE(level, value) \
		((level & ~I_BIT) | (value & I_BIT))
#endif /* CPU == ARMARCH7M */

#ifdef	_WRS_CONFIG_SMP

/* return TRUE if interrupts are locked in specified register set. */

#define	VXDBG_INT_REGS_IS_LOCKED(pRegs)	(((pRegs->cpsr & I_BIT) == \
		I_BIT) ? TRUE : FALSE)

/*
 * _WRS_VXDBG_CPU_CTRL_VARS_ALIGN sets the alignment constraint for
 * vxdbgCpuCtrlVars array.
 * The value must be:
 *   a power of two no smaller than sizeof(vxdbgCpuCtrlVars), and
 *   a multiple of the cache line size on every ARM variant that supports SMP.
 */

#define _WRS_VXDBG_CPU_CTRL_VARS_ALIGN          128
#define _WRS_VXDBG_CPU_CTRL_VARS_ALIGN_SHIFT    7
#define ARM_VXDBG_CPU_CTRL_VARS_ALIGN_SHIFT	\
					#(_WRS_VXDBG_CPU_CTRL_VARS_ALIGN_SHIFT)

#ifdef _CPU_CACHE_ALIGN_SIZE
/*
 * Validate _WRS_VXDBG_CPU_CTRL_VARS_ALIGN vs current build's
 *  _CPU_CACHE_ALIGN_SIZE
 *
 * If any SMP-enabled variant fails this test, _WRS_VXDBG_CPU_CTRL_VARS_ALIGN
 * must be increased. Since this limit also applies to any subsequent arch-only
 * release against the same generic binary release, it may be desirable to
 * allow for growth.
 */

#if (_CPU_CACHE_ALIGN_SIZE > _WRS_VXDBG_CPU_CTRL_VARS_ALIGN)
#error Must increase "_WRS_VXDBG_CPU_CTRL_VARS_ALIGN" to at least _CPU_CACHE_ALIGN_SIZE
#endif  /* _CPU_CACHE_ALIGN_SIZE > _WRS_VXDBG_CPU_CTRL_VARS_ALIGN */
#endif /* _CPU_CACHE_ALIGN_SIZE */

/* externals */

#ifndef _ASMLANGUAGE
extern void intVxdbgCpuRegsGet (void);
#endif  /* _ASMLANGUAGE */

#endif	/* _WRS_CONFIG_SMP */

#ifdef __cplusplus
}
#endif

#endif	/* __INCvxdbgArmLibPh */

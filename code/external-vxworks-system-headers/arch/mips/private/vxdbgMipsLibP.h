/* vxdbgMipsLibP.h - private MIPS VxWorks debug library (VxDBG) header file */

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
01h,09feb11,rlp  Defined VXDBG_INT_LOCK_LEVEL_COMPUTE macro for both UP and
                 SMP (CQ:WIND00253870).
01g,29apr10,pad  Moved extern C statement after include statements.
01f,03sep08,jpb  Renamed VSB header file
01e,27aug08,slk  change extern excIntStub_xxxx for SDA support
01d,24jun08,jpb  Added include path for kernel configurations options set in
                 vsb.  Renamed _WRS_VX_SMP to _WRS_CONFIG_SMP.
01c,26oct07,rlp  Added the VXDBG_INT_LOCK_LEVEL_COMPUTE macro (CQ:WIND00109321).
01b,11oct07,rlp  Added the VXDBG_INT_REGS_IS_LOCKED macro (CQ:WIND00107725).
01a,01jun07,jmp  Written
*/

#ifndef __INCvxdbgMipsLibPh
#define __INCvxdbgMipsLibPh

	
#include <vsbConfig.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * This macro returns the <level> parameter modified with the interrupt lock
 * level defined into the <value> parameter. The <level> parameter must be
 * previously get with either intCpuLock() or intRegsLock() API.
 */

#define	VXDBG_INT_LOCK_LEVEL_COMPUTE(level, value) \
		((level & ~SR_INT_ENABLE) | (value & SR_INT_ENABLE))

#ifdef	_WRS_CONFIG_SMP

/* defines */

/* return TRUE if interrupts are locked in specified register set. */

#define	VXDBG_INT_REGS_IS_LOCKED(pRegs)	(((pRegs->sr & SR_INT_ENABLE) == \
		SR_INT_ENABLE) ? FALSE : TRUE)

/*
 * _WRS_VXDBG_CPU_CTRL_VARS_ALIGN sets the alignment constraint for
 * vxdbgCpuCtrlVars array.
 * The value must be:
 *   a power of two no smaller than sizeof(vxdbgCpuCtrlVars), and
 *   a multiple of the cache line size on every MIPS variant that supports SMP.
 */

#if	_WRS_MIPS_32BIT_CPU
#define _WRS_VXDBG_CPU_CTRL_VARS_ALIGN          256
#define _WRS_VXDBG_CPU_CTRL_VARS_ALIGN_SHIFT    8
#else	/* _WRS_MIPS_32BIT_CPU */
#define _WRS_VXDBG_CPU_CTRL_VARS_ALIGN          512
#define _WRS_VXDBG_CPU_CTRL_VARS_ALIGN_SHIFT    9
#endif	/* _WRS_MIPS_32BIT_CPU */

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
extern void excIntStub_intExitOpAddr ();
extern void excIntStub_intVxdbgCpuRegsGetOpAddr ();
#endif	/* _ASMLANGUAGE */

#endif	/* _WRS_CONFIG_SMP */

#ifdef __cplusplus
}
#endif

#endif	/* __INCvxdbgMipsLibPh */

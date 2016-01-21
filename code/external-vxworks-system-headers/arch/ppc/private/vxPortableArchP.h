/* vxPortableArchP.h - PowerPC portable library configuration */

/*
 * Copyright (c) 2007-2008, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01m,20oct10,s_s  renamed _WRS_PORTABLE_vxCpuIndexGet to _WRS_PORTABLE_vxCpuLib
                 (CQ:WIND00199670)
01l,29apr10,pad  Moved extern C statement after include statements.
01k,10oct08,kk   renamed _WRS_PORTABLE_spinlockIsrNdLib to
                 _WRS_PORTABLE_spinLockIsrNdLib
01j,27aug08,jpb  Renamed VSB header file
01i,24jun08,jpb  Added include path for kernel configurations options set in
                 vsb.  Renamed _WRS_VX_SMP to _WRS_CONFIG_SMP.
01h,10jun08,to   enabled optimized intContext for SMP
01g,18mar08,to   enabled optimized taskIdSelf for SMP
01f,13feb08,to   enabled optimized syscallDispatch
01e,16jan08,dlk  Rename spinLockFastLib --> spinlockIsrNdLib.
01d,11dec07,dlk  Add ppc-specific spinLockFastLib.
01c,22sep07,zl   enabled optimized kernel lock library.
01b,11jul07,kk   disabled optimized vxAtomicLib for UP
01a,04may07,zl   created
*/

#ifndef __INCvxPortableArchPh
#define __INCvxPortableArchPh

	
#include <vsbConfig.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * This file is included from <private/vxPortableP.h>. It may undefine
 * portable library definitions in order to enable architecture specific
 * implementation of a library or routine.
 */

/* the following can be overridden with PORTABLE */

#ifndef PORTABLE

#undef _WRS_PORTABLE_bLib
#undef _WRS_PORTABLE_ffsLib
#undef _WRS_PORTABLE_ffsTbl
#undef _WRS_PORTABLE_kernelLockLib
#undef _WRS_PORTABLE_swab
#undef _WRS_PORTABLE_spinLockIsrNdLib
#undef _WRS_PORTABLE_syscallDispatch

#ifdef _WRS_CONFIG_SMP
/*
 * These functions' optimized implementations are only used for SMP,
 * as portable implementations are already optimal for UP.
 */
#undef _WRS_PORTABLE_intContext
#undef _WRS_PORTABLE_taskIdSelf
#endif /* _WRS_CONFIG_SMP */

#endif /* PORTABLE */

/* the following cannot be overridden with PORTABLE */

#ifdef _WRS_CONFIG_SMP
/*
 * UP can disable the cache, hence the optimized version that uses the
 * lwarx/stwcx. can't be used
 */

#undef _WRS_PORTABLE_vxAtomicLib
#endif /* _WRS_CONFIG_SMP */

#undef _WRS_PORTABLE_vxCpuLib

#ifdef __cplusplus
}
#endif

#endif /* __INCvxPortableArchPh */

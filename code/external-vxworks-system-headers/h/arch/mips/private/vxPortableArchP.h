/* vxPortableArchP.h - MIPS portable library configuration */

/* 
 * Copyright (c) 2007-2010 Wind River Systems, Inc. 
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
01l,28apr09,slk  enable optimized mutex semaphore code
01k,04apr09,slk  undefine _WRS_PORTABLE_semBLib and _WRS_PORTABLE_semCLib
                 for UP
01j,10oct08,kk   renamed _WRS_PORTABLE_spinlockIsrNdLib to
                 _WRS_PORTABLE_spinLockIsrNdLib
01i,29aug08,slk  undef _WRS_PORTABLE_schedLib for UP MIPS adding optimzed
                 reschedule
01h,17jun08,slk  undefine _WRS_PORTABLE_syscallDispatch adding optimized MIPS
                 syscallDispatch
01g,11apr08,slk  undef _WRS_PORTABLE_workQLib adding MIPS workQALib.s
01f,25mar08,slk  undef _WRS_PORTABLE_qPriBMapNext and
                 _WRS_PORTABLE_qPriBMapLib
01e,16jan08,dlk  Rename spinLockFastLib --> spinlockIsrNdLib.
01d,19dec07,dlk  Enable mips-optimized fast spin locks.
01c,06jul07,zl   enabled optimized libraries
01b,03jul07,pes  Re-enable optimized bLib.
01a,04may07,zl   created
*/

#ifndef __INCvxPortableArchPh
#define __INCvxPortableArchPh

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
#undef _WRS_PORTABLE_spinLockIsrNdLib
#undef _WRS_PORTABLE_qPriBMapNext
#undef _WRS_PORTABLE_qPriBMapLib
#undef _WRS_PORTABLE_workQLib
#undef _WRS_PORTABLE_syscallDispatch
#ifndef _WRS_CONFIG_SMP
#undef _WRS_PORTABLE_schedLib
#undef _WRS_PORTABLE_semBLib
#undef _WRS_PORTABLE_semCLib
#undef _WRS_PORTABLE_semMLib
#endif  /* _WRS_CONFIG_SMP */

#endif /* PORTABLE */

/* the following cannot be overridden with PORTABLE */

#undef _WRS_PORTABLE_vxAtomicLib
#undef _WRS_PORTABLE_vxCpuLib

#ifdef __cplusplus
}
#endif

#endif /* __INCvxPortableArchPh */

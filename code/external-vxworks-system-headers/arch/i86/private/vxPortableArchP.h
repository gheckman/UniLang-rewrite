/* vxPortableArchP.h - x86/x86_64 portable library configuration */

/* 
 * Copyright (c) 2007-2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01w,20jan11,scm  WIND00251661 - PORTABLE macro should not be defined by
                 default.
01v,20oct10,s_s  renamed _WRS_PORTABLE_vxCpuIndexGet to _WRS_PORTABLE_vxCpuLib
                 (CQ:WIND00199670)
01u,26may10,scm  enable optimized syscallDispatcher...
01t,23mar10,scm  enable _WRS_PORTABLE_vxAtomicLib for 64 bit...
01s,18mar10,scm  enable _WRS_PORTABLE_kernelLockLib and 
                 _WRS_PORTABLE_spinLockIsrNdLib
01r,04feb10,scm  add ffs 64 bit flag...
01q,20jan10,scm  enable qPriBMapLib & qPriBMapNext...
01p,07jan10,scm  enable optimized libs for bLib, workQLib, dllLib, sllLib, 
                 and ffsLib.
01o,09dec09,cww  64-bit ffsLib update
01n,27jul09,jb   Make vxAtomic portable for LP64
01m,19jun09,mze  replacing PAD64
01l,20apr09,cww  Temp enabling of portable vxAtomicLib for LP64
01k,16oct08,jb   64bit - Enabling PORTABLE - To be disabled as optimized
                 routines are ported
01j,10oct08,kk   renamed _WRS_PORTABLE_spinlockIsrNdLib to
                 _WRS_PORTABLE_spinLockIsrNdLib
01i,24mar08,scm  enable optimized workQ routines...
01h,16mar08,scm  enable optimized qPriBMapNext...
01g,13mar08,scm  enabled optimized syscallDispatch...
01f,16jan08,dlk  Rename spinLockFastLib --> spinlockIsrNdLib.
01e,10dec07,dlk  Enabled i86-optimized fast spin locks.
01d,22sep07,zl   enabled optimized kernel lock library.
01c,04jun07,scm  update to support optimized implementations...
01b,15may07,scm  restore settings
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

#ifdef  _WRS_CONFIG_LP64
#ifndef PORTABLE
#undef  _WRS_PORTABLE_kernelLockLib
#undef  _WRS_PORTABLE_spinLockIsrNdLib
#undef  _WRS_PORTABLE_vxAtomicLib
#undef  _WRS_PORTABLE_bLib
#undef  _WRS_PORTABLE_workQLib
#undef  _WRS_PORTABLE_dllLib
#undef  _WRS_PORTABLE_sllLib
#undef  _WRS_PORTABLE_ffsLib
#undef  _WRS_PORTABLE_ffs64Lib
#undef  _WRS_PORTABLE_qPriBMapLib
#undef  _WRS_PORTABLE_qPriBMapNext
#undef  _WRS_PORTABLE_syscallDispatch
#endif

#else /* (LP64) */

#ifndef PORTABLE
#undef _WRS_PORTABLE_bLib
#undef _WRS_PORTABLE_dllLib
#undef _WRS_PORTABLE_ffsLib
#define _WRS_PORTABLE_ffs64Lib
#undef _WRS_PORTABLE_kernelLockLib
#undef _WRS_PORTABLE_sllLib
#undef _WRS_PORTABLE_spinLockIsrNdLib
#undef _WRS_PORTABLE_syscallDispatch
#undef _WRS_PORTABLE_qPriBMapLib
#undef _WRS_PORTABLE_qPriBMapNext
#undef _WRS_PORTABLE_workQLib
#undef _WRS_PORTABLE_vxAtomicLib
#endif
#endif /* (LP64) */

/* the following cannot be overridden with PORTABLE */

#undef _WRS_PORTABLE_vxCpuLib

#ifdef __cplusplus
}
#endif

#endif /* __INCvxPortableArchPh */

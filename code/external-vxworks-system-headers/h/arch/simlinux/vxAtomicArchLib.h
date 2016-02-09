/* vxAtomicArchLib.h - VxSim specific atomic library header */

/*
 * Copyright (c) 2006, 2008-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/*
modification history
--------------------
01f,22oct10,elp  fixed 32-bits warnings caused by previous changes.
01e,22oct10,elp  added inline macros
01d,29apr10,pad  Moved extern C statement after include statements.
01c,15may09,gls  made memory barriers available in user space
01b,16jun08,zl   use _WRS_BARRIER() for memory barrier implementations.
01a,27nov06,dbt  created based on PPC version
*/

#ifndef __INCvxAtomicArchLibh
#define __INCvxAtomicArchLibh

#include <arch/simsolaris/vxAtomicArchLibCommon.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WRS_CONFIG_LP64
#define vxCas_inline vxAtomicCas_inline
#endif 

#ifdef __cplusplus
}
#endif

#endif /* __INCvxAtomicArchLibh */

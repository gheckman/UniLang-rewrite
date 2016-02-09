/* vxAtomicArchLibCommon.h - x86_64 specific atomic library header */

/*
 * Copyright (c) 2010, 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01b,27apr12,scm  WIND00346365 - VX_MEM_BARRIER_R()/_W()/_RW all using
                 mfence...
01a,23mar10,scm  written.
*/

#ifndef __INCvxAtomicArchLibCommonh
#define __INCvxAtomicArchLibCommonh

#ifdef __cplusplus
extern "C" {
#endif

#define _WRS_ARCH_SUPPORTS_MEM_BARRIER

/* 
 * Macros to provide memory barrier. 
 */

#define VX_MEM_BARRIER_R()	    _WRS_BARRIER("lfence");
#define VX_MEM_BARRIER_W()	    _WRS_BARRIER("sfence");
#define VX_MEM_BARRIER_RW()	    _WRS_BARRIER("mfence");
#define VX_INSTR_BARRIER()          _WRS_BARRIER("mfence")

#ifdef __cplusplus
}
#endif

#endif /* __INCvxAtomicArchLibCommonh */

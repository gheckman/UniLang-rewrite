/* vxAtomicArchLibCommon.h - VxSim specific atomic library header */

/*
 * Copyright (c) 2009 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01a,17may09,gls  written.
*/

#ifndef __INCvxAtomicArchLibCommonh
#define __INCvxAtomicArchLibCommonh

#ifdef __cplusplus
extern "C" {
#endif

#define _WRS_ARCH_SUPPORTS_MEM_BARRIER

#define VX_MEM_BARRIER_R()	    _WRS_BARRIER("nop");
#define VX_MEM_BARRIER_W()	    _WRS_BARRIER("nop");
#define VX_MEM_BARRIER_RW()	    _WRS_BARRIER("nop");
#define VX_INSTR_BARRIER()          _WRS_BARRIER("nop")

#ifdef __cplusplus
}
#endif

#endif /* __INCvxAtomicArchLibCommonh */

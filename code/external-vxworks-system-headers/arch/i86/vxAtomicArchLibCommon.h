/* vxAtomicArchLibCommon.h - IA32 specific atomic library header */

/*
 * Copyright (c) 2009, 2011-2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01c,27apr12,scm  WIND00346365 - VX_MEM_BARRIER_R()/_W()/_RW all using
                 mfence...
01b,05jan11,kk   make VX_MEM_BARRIER_X() macros CPU variant dependent
01a,17may09,gls  written.
*/

#ifndef __INCvxAtomicArchLibCommonh
#define __INCvxAtomicArchLibCommonh

#ifdef __cplusplus
extern "C" {
#endif

#define _WRS_ARCH_SUPPORTS_MEM_BARRIER

/* 
 * Macros to provide memory barrier. 
 * 
 * For variants older than PENTIUM4, the mfence instruction
 * is not supported.
 */

#if (CPU==PENTIUM)
#define VX_MEM_BARRIER_R()      _WRS_ASM("NOP")
#define VX_MEM_BARRIER_W()      _WRS_ASM("NOP")
#define VX_MEM_BARRIER_RW()     _WRS_ASM("NOP")
#define VX_INSTR_BARRIER()      _WRS_ASM("NOP")
#else
#define VX_MEM_BARRIER_R()	    _WRS_BARRIER("lfence");
#define VX_MEM_BARRIER_W()	    _WRS_BARRIER("sfence");
#define VX_MEM_BARRIER_RW()	    _WRS_BARRIER("mfence");
#define VX_INSTR_BARRIER()          _WRS_BARRIER("mfence");
#endif
#ifdef __cplusplus
}
#endif

#endif /* __INCvxAtomicArchLibCommonh */

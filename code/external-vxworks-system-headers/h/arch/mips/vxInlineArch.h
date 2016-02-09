/* vxInlineArch.h - MIPS inline macro configuration */

/* 
 * Copyright (c) 2007-2009 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01f,07jul09,slk  add _WRS_INLINE_intCpuMicroLock and 
                 _WRS_INLINE_intCpuMicroUnlock defines
01e,16feb09,slk  add _WRS_INLINE_intCpuLock and _WRS_INLINE_intCpuUnlock
                 for UP
01d,15aug08,slk  add additional inline atomic operators
01c,14dec07,wap  Add support for some inline vxAtomic functions
01b,11jul07,zl   enabled inlined ffsLib macros.
01a,19jun07,zl   created
*/

#ifndef __INCvxInlineArchh
#define __INCvxInlineArchh

#ifdef __cplusplus
extern "C" {
#endif

/*
 * This file is included from <vxInline.h>. It may define _WRS_INLINE_xxx 
 * build configuration macros in order to enable architecture specific
 * inlined implementation of a macro definition.
 */

#ifdef _WRS_CPU_HAS_CLZ_INSTR

#define _WRS_INLINE_ffsLsb
#define _WRS_INLINE_ffsMsb

#endif /* _WRS_CPU_HAS_CLZ_INSTR */

#define _WRS_INLINE_intCpuLock
#define _WRS_INLINE_intCpuUnlock
#define _WRS_INLINE_intCpuMicroLock
#define _WRS_INLINE_intCpuMicroUnlock
#define _WRS_INLINE_vxCas
#define _WRS_INLINE_vxAtomicSet
#define _WRS_INLINE_vxAtomicGet
#define _WRS_INLINE_vxAtomicAnd
#define _WRS_INLINE_vxAtomicNand
#define _WRS_INLINE_vxAtomicOr
#define _WRS_INLINE_vxAtomicXor
#define _WRS_INLINE_vxAtomicDec
#define _WRS_INLINE_vxAtomicInc
#define _WRS_INLINE_vxAtomicSub
#define _WRS_INLINE_vxAtomicAdd
#define _WRS_INLINE_vxAtomicClear

#ifdef __cplusplus
}
#endif

#endif /* __INCvxInlineArchh */

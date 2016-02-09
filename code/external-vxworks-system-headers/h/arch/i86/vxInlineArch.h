/* vxInlineArch.h - i86/x86_64 inline macro configuration */

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
01g,24mar10,scm  enable remaining inlines for 64 bit...
01f,24mar10,scm  enable vxAtomic inlines...
01e,23mar10,scm  adjust for vxAtomics...
01d,15apr09,sem  Add new intCpuMicroLock API
01d,18nov08,pad  For LP64 do not use inlines until they are adapted.
01c,29aug08,to   add more inline atomic routines
01b,11dec07,gls  added _WRS_INLINE_vxCas
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

#define _WRS_INLINE_intCpuLock
#define _WRS_INLINE_intCpuUnlock
#define _WRS_INLINE_intCpuMicroLock
#define _WRS_INLINE_intCpuMicroUnlock
#define _WRS_INLINE_vxAtomicAdd
#define _WRS_INLINE_vxAtomicSub
#define _WRS_INLINE_vxAtomicInc
#define _WRS_INLINE_vxAtomicDec
#define _WRS_INLINE_vxAtomicGet
#define _WRS_INLINE_vxAtomicSet
#define _WRS_INLINE_vxAtomicClear
#define _WRS_INLINE_vxCas

#ifdef __cplusplus
}
#endif

#endif /* __INCvxInlineArchh */

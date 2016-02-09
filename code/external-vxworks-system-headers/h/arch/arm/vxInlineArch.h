/* vxInlineArch.h - ARM inline macro configuration */

/*
 * Copyright (c) 2007, 2009-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01c,21may10,m_h  Thumb-2 Support
01b,18may09,j_b  add _inline_intCpuMicroLock/Unlock support
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

#if	!(ARM_THUMB) && !(ARM_THUMB2)

#define _WRS_INLINE_intCpuLock
#define _WRS_INLINE_intCpuUnlock
#define _WRS_INLINE_intCpuMicroLock
#define _WRS_INLINE_intCpuMicroUnlock

#endif /* !ARM_THUMB && !ARM_THUMB2 */

#ifdef __cplusplus
}
#endif

#endif /* __INCvxInlineArchh */

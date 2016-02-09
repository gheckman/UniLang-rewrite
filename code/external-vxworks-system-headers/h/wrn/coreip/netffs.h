/* netffs.h - structures for netffs.c */

/*
 * Copyright (c) 2006 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. No license to Wind River intellectual property rights
 * is granted herein. All rights not licensed by Wind River are reserved
 * by Wind River.
 */

/*
modification history
--------------------
01e,20jun06,jpb  Updated for POSIX namespace conformance.
                 Changed C preprocessor macro CPU_FAMILY to _VX_CPU_FAMILY.
01d,02mar06,dlk  Remove extra tokens "(x)" at end of "#ifndef FFS".
01c,03feb06,dlk  Remove ffsMsb() declaration, but do not add include
		 for ffsLib.h yet.
01b,10jan06 hya  removed ARM CPU variant code.
01a,09aug05 niq  created.
*/

#ifndef __INCnetffsh
#define __INCnetffsh

#ifdef __cplusplus
extern "C" {
#endif

/*
 * We want the fastest possible 'ffsMsb() - 1' for each architecture,
 * ideally inlined assembly.
 * Eventually, this stuff should be moved to architecture-specific
 * headers.
 */

#if !defined (__GNUC__) && !defined (_DIAB_TOOL)
#define USE_FFSMSB_PORTABLE
#endif

#if defined (USE_FFSMSB_PORTABLE)

#define FFS(x) (ffsMsb(x) - 1)

#else /* !defined (USE_FFSMSB_PORTABLE) */

#if (_VX_CPU_FAMILY == _VX_I80X86)

#define FFS(x) _firstBit(x)

#if defined (__GNUC__)

/*
 * Return the index of the most significant bit on in x.
 * We don't have to handle the x=0 case, this is only called
 * when x != 0. Returns a value y in the range 31 >= y >= 0.
 * 31 indicates the most significant bit.
 */

static __inline__ UINT32 _firstBit
    (
    UINT32 x
    )
    {
    UINT32 y;

    __asm__ ("bsrl %1, %0"
	     : "=r" (y)
	     : "r" (x)
	     : "cc");

    return y;
    }

#else /* _DIAB_TOOL */

/* SPR #110427 is now fixed, restore inline assembly for I80X806/diab */
#pragma pure_function _firstBit

__asm UINT32 _firstBit
    (
    UINT32 x
    )
{
% mem x
! "ax"
	bsrl  x, %eax
}

#endif /* _DIAB_TOOL */

#elif (_VX_CPU_FAMILY == _VX_PPC)

#define FFS(x) (31 - _countLeadingZeroes(x))

#if defined (__GNUC__)

/*
 * Return the number of zero bits in bit positions more significant
 * than the first set bit.
 * We don't have to handle the x=0 case, this is only called
 * when x != 0. Returns a value y in the range 31 >= y >= 0.
 * 0 indicates the most significant bit.
 */

static __inline__ UINT32 _countLeadingZeroes
    (
    UINT32 x
    )
    {
    UINT32 y;

    __asm__ ("cntlzw %0, %1"
	     : "=r" (y)
	     : "r" (x)
	    );

    return y;
    }
#else /* _DIAB_TOOL */

#pragma pure_function _countLeadingZeroes

__asm UINT32 _countLeadingZeroes
    (
    UINT32 x
    )
{
% reg x
! "r3"
	cntlzw  r3, x
}

#endif /* _DIAB_TOOL */

#else /* unknown or unsupported _VX_CPU_FAMILY */

#ifndef FFS
#define FFS(x) (ffsMsb(x) - 1)
#endif
#endif /* _VX_CPU / _VX_CPU_FAMILY */

#endif /* !defined (USE_FFSMSB_PORTABLE) */


#ifdef __cplusplus
}
#endif

#endif /* __INCnetffsh */

/* ffsMipsLib.h - MIPS-specific ffs library header */

/*
 * Copyright (c) 2007,2009 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01d,10dec09,cww  64-bit ffsLib update
01c,21aug09,slk  defect 166685 don't corrupt i parameter in _inline_ffsMsb and
                 _inline_ffsLsb
01b,12oct07,pes  Change reference to zero register to '$0'
01a,19jun07,zl   created, based on ffsALib.s vn 01g.
*/

#ifndef __INCffsMipsLibh
#define __INCffsMipsLibh

#ifdef __cplusplus
extern "C" {
#endif


#ifndef _ASMLANGUAGE

/*
 * find most and least significant bit set inline macros.  diab version takes
 * advantage of the __ff1 intrinsic that provides a 'C' compatible clz
 * instruction that will work for all ISA levels for these functions
 */

#if defined (__DCC__)

#define _inline_ffs32Msb(x)   (32 - __ff1(x))
#define _inline_ffs32Lsb(x)   (32 - __ff1(x & -x))

#elif	defined (__GNUC__)

#ifdef _WRS_CPU_HAS_CLZ_INSTR
static __inline__ int _inline_ffs32Msb (UINT32 i)
    {
    int j, tmp;
    __asm__ 
	(
	"clz	%0, %2			\n"	/* count leading zeros */
	"li	%1, 32			\n"	/* load 32 */
	"subu	%0, %1, %0		\n"	/* 32 - count */
	: "=&r" (j), "=r" (tmp)			/* output: j is %0 (register) */
	: "r" (i)				/* input: i is %1 */
						/* no clobbered registers */
	);
    return (j);
    }

static __inline__ int _inline_ffs32Lsb (UINT32 i)
    {
    int j, tmp;
    __asm__ 
	(
	"subu	%0, $0, %2	 	\n"	/* get -i */
	"and	%0, %2, %0		\n"	/* i & (-i): only LSB set */ 
	"clz	%0, %0			\n"	/* count leading zeros */
	"li	%1, 32			\n"	/* load 32  */
	"subu	%0, %1, %0		\n"	/* 32 - count */
	: "=&r" (j), "=r" (tmp)			/* output: j is %0 (register) */
	: "r" (i) 				/* input: i is %1 */
						/* no clobbered registers */
	);
    return (j);
    }

#else	/* _WRS_CPU_HAS_CLZ_INSTR */

#define _inline_ffs32Msb(i)	ffs32Msb(i)
#define _inline_ffs32Lsb(i)	ffs32Lsb(i)

#endif /* _WRS_CPU_HAS_CLZ_INSTR */
#endif /* __GNUC__ */


#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INCffsMipsLibh */

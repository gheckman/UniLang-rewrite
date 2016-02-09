/* ppc32.h - generic 32-bit PowerPC header */

/* Copyright 2002-2003 Wind River Systems, Inc. */

/*
modification history
--------------------
01c,05dec03,jtp  Add _WRS_TLB_MISS_CLASS_HW
01b,04feb03,pch  add _fp60x variant
01a,12dec02,pch  written.
*/

#ifndef	__INCppc32h
#define	__INCppc32h

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * If compiling for a variant, the preprocessor symbol CPU_VARIANT will be
 * defined as the directory suffix, e.g. _fp60x for PPC60x hardware floating
 * point support (whose objects go in target/lib/ppc/PPC32/ *_fp60x).
 *
 * We really want something like #if ("CPU_VARIANT" == "_fp60x")
 * which ANSI C does not allow.  However, it does allow the expansion
 * of CPU_VARIANT to be re-expanded according to another #define.
 */
#ifdef	CPU_VARIANT
#define	_fp60x	603
#if (CPU_VARIANT == _fp60x)
#define	PPC32_fp60x	1
#endif	/* CPU_VARIANT == _fp60x */
#undef	_fp60x
#endif	/* CPU_VARIANT */

/*
 * Tell the loader this processor can't handle any misalignment.
 * This is necessary for 403; for others the loader will
 * take a performance hit but it is otherwise harmless.
 */
#define	_WRS_STRICT_ALIGNMENT	1

/*
 * FP variant needs to define _PPC_MSR_FP (used elsewhere to indicate
 * "FP present".  Base variant should have no floating point support
 * in target shell.
 */
#ifdef	PPC32_fp60x
#define _PPC_MSR_FP		0x2000	/* floating-point available */
#else	/* PPC32_fp60x */
#define	_WRS_NO_TGT_SHELL_FP	1
#endif	/* PPC32_fp60x */

/* No MMU support in architecture library */
#undef _WRS_TLB_MISS_CLASS_SW
#undef _WRS_TLB_MISS_CLASS_HW

#ifdef	__cplusplus
}
#endif

#endif	/* __INCppc32h */

/* intMipsLib.h - MIPS-specific interrupt library header file */

/* Copyright 1999,2007, 2009-2011 Wind River Systems, Inc. */

/*
modification history
--------------------
01h,25may11,slk  Add 64bit interrupt support for xlx
01g,29apr10,pad  Moved extern C statement after include statements.
01f,07jul09,slk  add _inline_intCpuMicroLock and _inline_intCpuMicroUnlock
01e,13mar09,slk  fix _ASMLANGUAGE defined area
01d,24feb09,slk  fix zero register references
01c,16feb09,slk  add inline intCpuLock and intCpuUnlock macros for R2 variants
01b,04oct07,d_c  Add extended interrupts for RMI _xlr variant
01a,26oct99,dra  created.
*/

#ifndef __INCintMipsLibh
#define __INCintMipsLibh

#ifndef _ASMLANGUAGE
#include <vsbConfig.h>
#include <arch/mips/mipsExcPage.h>
#if defined(MIPSXX_xlp) || defined(MIPSXX_xlr) || \
    defined(_WRS_MIPS_NETLOGIC_CPU)
#include <arch/mips/xlxLib.h>
#endif  /* defined(MIPSXX_xlp) || defined(MIPSXX_xlr) || 
           defined(_WRS_MIPS_NETLOGIC_CPU) */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WRS_INLINE_intCpuLock

#if defined(_WRS_MIPS_ENABLE_R2_ISA)
#if defined (__DCC__)
__asm volatile int _inline_intCpuLock ()
{
! "$2"
        di      $2
        ehb
}
#elif defined (__GNUC__)
#define _inline_intCpuLock()       intCpuLock()
#else /* __GNUC__ */
#define _inline_intCpuLock()       intCpuLock()
#endif /* __DCC__ */
#else /* _WRS_MIPS_ENABLE_R2_ISA */
#define _inline_intCpuLock()       intCpuLock()
#endif /* _WRS_MIPS_ENABLE_R2_ISA */
#endif /* _WRS_INLINE_intCpuLock */

#ifdef _WRS_INLINE_intCpuMicroLock

#if defined(_WRS_MIPS_ENABLE_R2_ISA)
#if defined (__DCC__)
__asm volatile int _inline_intCpuMicroLock ()
{
! "$2"
        di      $2
        ehb
}
#elif defined (__GNUC__)
#define _inline_intCpuMicroLock()       intCpuMicroLock()
#else /* __GNUC__ */
#define _inline_intCpuMicroLock()       intCpuMicroLock()
#endif /* __DCC__ */
#else /* _WRS_MIPS_ENABLE_R2_ISA */
#define _inline_intCpuMicroLock()       intCpuMicroLock()
#endif /* _WRS_MIPS_ENABLE_R2_ISA */
#endif /* _WRS_INLINE_intCpuMicroLock */

#ifdef _WRS_INLINE_intCpuUnlock

#if defined(_WRS_MIPS_ENABLE_R2_ISA)
#if defined (__DCC__)
#define _inline_intCpuUnlock(key)       intCpuUnlock(key)
#elif defined (__GNUC__)
#define _inline_intCpuUnlock(key)       intCpuUnlock(key)
#else /* __GNUC__ */
#define _inline_intCpuUnlock(key)       intCpuUnlock(key)
#endif /* __DCC__ */
#else /* _WRS_MIPS_ENABLE_R2_ISA */
#define _inline_intCpuUnlock(key)       intCpuUnlock(key)
#endif /* _WRS_MIPS_ENABLE_R2_ISA */
#endif /* _WRS_INLINE_intCpuUnlock */

#ifdef _WRS_INLINE_intCpuMicroUnlock

#if defined(_WRS_MIPS_ENABLE_R2_ISA)
#if defined (__DCC__)
__asm volatile void _inline_intCpuMicroUnlock (int key)
{
% reg key ;
        .set noreorder
        mtc0 key, $12
        ehb
        .set reorder
}
#elif defined (__GNUC__)
#define _inline_intCpuMicroUnlock(key)       intCpuMicroUnlock(key)
#else /* __GNUC__ */
#define _inline_intCpuMicroUnlock(key)       intCpuMicroUnlock(key)
#endif /* __DCC__ */
#else /* _WRS_MIPS_ENABLE_R2_ISA */
#define _inline_intCpuMicroUnlock(key)       intCpuMicroUnlock(key)
#endif /* _WRS_MIPS_ENABLE_R2_ISA */
#endif /* _WRS_INLINE_intCpuMicroUnlock */

#if defined(__STDC__) || defined(__cplusplus)

extern int	intCRGet (void);
extern void	intCRSet (int value);
extern int	intSRGet (void);
extern int	intSRSet (int value);
extern int	intDisable (int);
extern int	intEnable (int);
#if defined(MIPSXX_xlp) || defined(MIPSXX_xlr) || \
    defined(_WRS_MIPS_NETLOGIC_CPU)
extern UINT64   intExtendedEnable (UINT64);
extern UINT64   intExtendedDisable (UINT64);
#endif  /* defined(MIPSXX_xlp) || defined(MIPSXX_xlr) ||
           defined(_WRS_MIPS_NETLOGIC_CPU) */

#else /* defined(__STDC__) || defined(__cplusplus) */

extern int	intCRGet ();
extern void	intCRSet ();
extern int	intSRGet ();
extern int	intSRSet ();
extern int	intDisable ();
extern int	intEnable ();
#if defined(MIPSXX_xlp) || defined(MIPSXX_xlr) || \
    defined(_WRS_MIPS_NETLOGIC_CPU)
extern UINT64   intExtendedEnable (UINT64);
extern UINT64   intExtendedDisable (UINT64);
#endif  /* defined(MIPSXX_xlp) || defined(MIPSXX_xlr) ||
           defined(_WRS_MIPS_NETLOGIC_CPU) */

#endif /* defined(__STDC__) || defined(__cplusplus) */
#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INCintMipsLibh */

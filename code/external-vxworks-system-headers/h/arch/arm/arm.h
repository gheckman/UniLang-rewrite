/* arm.h - ARM CPU flags etc */

/*
 * Copyright (c) 1996-2006, 2008-2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */


/*
modification history
--------------------
17apr14,c_l  add the write protection of L2 page table. (VXW6-73478)
02l,16mar13,yjw  Update for ARMv7M 
02k,08oct12,jdw  Update FAST MATH for ARMARCH7
02j,14sep12,j_b  fix whitespace issues
02i,28jun12,j_b  add Cortex-A15 cache support
02h,09feb12,jdw  Update definitions for __ieee_status(), WIND00332894
02g,01feb12,rec  WIND00329076 - cleanup assembly macros to be consistent
02f,11aug11,jdw  Add support for ARMv7 core optimizations
02e,23aug11,rec  WIND00292261 - transition to common power management API
02d,15apr11,jdw  Enable cached page tables
02c,13jan11,m_h  Define _CACHE_ALIGN_SIZE as cacheArchAlignSize for ARMARCH7
02b,09jul10,fao  add endianness state bit define
02a,21may10,m_h  Thumb-2 Support
01z,02feb10,j_b  add _WRS_ARM_HAS_ASID macro, defined for ARMv6+
01y,23sep09,j_b  add LDREX/STREX support for ARMARCH7
01x,06jun09,mdo  Don't check IEEE status for FAST_MATH
01w,25feb09,j_b  merge ARM SMP:
                 11jul07,j_b  add ARMMMU_11MPCORE support
                 11jul07,to   added ARM_HAS_LDREX_STREX feature macro
                 02jul07,m_h  Adding types for MPCore varient
01v,27feb09,m_h  ARMARCH7 Support
01u,12jun08,j_b  add Cortex-A MMU and Cortex-A/-R cache support
01t,28apr08,m_h  Create macro for NOP after LDM^ and STM^
01s,13jul06,m_h  MPU support
01r,25jan06,m_h  Manzano support
01o,10oct05,scm  correct SPR 111664
01n,04apr05,jb   Adding ARMARCH6 and 1136 support
01m,21mar05,mdo  Add define for ansiMath testing
01l,02mar05,mdo  Add prototype for __ieee_status() and definitions for
                 exception flags
01k,10aug04,scm  remove MPU support...
01j,25nov03,sn   Avoid gcc 3.3.2 preprocessor token pasting error
01i,26aug03,rec  remove SYS_PWR_MGMT conditional
01h,07jul03,rec  revert to non-portable kernel
01g,01jul03,rec  code review comments
01f,28may03,rec  Power Management
01f,17dec02,jb  Adding ARM10 and 926E support
01e,15jan02,m_h  ARMARCH5 thumb problem
01d,05nov01,t_m  remove leading underscores via FUNC/VAR macros
01c,05nov01,t_m  Undo underscores
01b,19jul01,ed   Fixing to be compatible with Diab compiler.
01d,17oct01,t_m  Merge in DIAB
01c,10oct01,jb  Enabling removal of pre-pended underscores for new compilers
                 (Diab/Gnu elf)
01b,23jul01,scm  change XScale name to conform to coding standards...
01a,11dec00,scm  replace references to ARMSA2 with XScale
01g,16oct00,scm  reverse back I & F bits for SA2
01f,01sep00,scm  add sa2 support...
01e,08feb99,jpd  added further MMU/CACHE types.
01d,20jan99,cdp  removed support for old ARM libraries.
01c,24aug98,cdp  added MMU/cache types, ARM_HAS_MPU/ARM_THUMB, ARMST16/ARMST32.
01b,21aug97,cdp  added _?_FUNCTION macros and HAS_HALFWORD_
01a,08may96,cdp  written
*/

#ifndef	__INCarmh
#define	__INCarmh

#ifdef __cplusplus
extern "C" {
#endif

#if (CPU == ARMARCH7M)

#include "arch/arm/arm-m/arm-m.h"

#else /* (CPU == ARMARCH7M) */


/* Make sure excArmLib.h also has same settings */

/* bits in the PSR */

#define	V_BIT	(1<<28)
#define	C_BIT	(1<<29)
#define	Z_BIT	(1<<30)
#define	N_BIT	(1<<31)
#define E_BIT   (1<<9)
#define I_BIT   (1<<7)
#define F_BIT   (1<<6)
#define	T_BIT	(1<<5)


/* mode bits */

#define MODE_SYSTEM32	0x1F
#define MODE_UNDEF32	0x1B
#define	MODE_ABORT32	0x17
#define MODE_SVC32	0x13
#define MODE_IRQ32      0x12
#define MODE_FIQ32      0x11
#define MODE_USER32	0x10
#define MODE_MONITOR	0x16

/* masks for getting bits from PSR */

#ifdef ARM_INTERWORKINGSUPPORT
#define MASK_MODE	0x0000003F
#else /*ARM_INTERWORKINGSUPPORT*/
#define MASK_MODE	0x0000001F
#endif /*ARM_INTERWORKINGSUPPORT*/
#define	MASK_32MODE	0x0000001F
#define	MASK_SUBMODE	0x0000000F
#define MASK_INT	0x000000C0
#define	MASK_CC		0xF0000000


/* shifts to access bits in the PSR */

#define INT_MASK_SHIFT	6


/* The coprocessor number of the MMU System Control Processor */

#define CP_MMU 15


/* ARM MMU types */

#define ARMMMU_NONE	0
#define ARMMMU_710A	1
#define ARMMMU_810	2
#define ARMMMU_SA110	3
#define ARMMMU_940T	4
#define ARMMMU_740T	5
#define ARMMMU_SA1100	6
#define ARMMMU_SA1500	7
#define ARMMMU_720T	8
#define ARMMMU_920T	9
#define ARMMMU_946E     10
#define ARMMMU_XSCALE   11
#define ARMMMU_926E	12
#define ARMMMU_1020E	13
#define ARMMMU_1022E	14
#define ARMMMU_1136JF   15
#define ARMMMU_MANZANO  16
#define ARMMMU_CORTEXA8 17
#define ARMMMU_11MPCORE 18

#define ARMMPU_940T	ARMMMU_940T
#define ARMMPU_740T	ARMMMU_740T
#define ARMMPU_946E     ARMMMU_946E

/* ARM cache types */

#define ARMCACHE_NONE	  0
#define ARMCACHE_710A	  1
#define ARMCACHE_810	  2
#define ARMCACHE_SA110	  3
#define ARMCACHE_940T	  4
#define ARMCACHE_740T	  5
#define ARMCACHE_SA1100	  6
#define ARMCACHE_SA1500	  7
#define ARMCACHE_720T	  8
#define ARMCACHE_920T	  9
#define ARMCACHE_946E     10
#define ARMCACHE_XSCALE   11
#define ARMCACHE_926E	  12
#define ARMCACHE_1020E	  13
#define ARMCACHE_1022E	  14
#define ARMCACHE_1136JF	  15
#define ARMCACHE_MANZANO  16
#define ARMCACHE_CORTEXA8 17
#define ARMCACHE_11MPCORE 18
#define ARMCACHE_CORTEXA15  19


/* check CPU/cache/MMU features */

/* Cache Line sizes */

#if defined (_WRS_CONFIG_ARMV7_CORE_CTX_A8) || \
    defined (_WRS_CONFIG_ARMV7_CORE_CTX_A15)

#define _CPU_CACHE_ALIGN_SIZE 64 /* Cortex-A8 and Cortex-A15 use 64 bytes */

#else /* _WRS_CONFIG_ARMV7_CORE_CTX_A8 || _WRS_CONFIG_ARMV7_CORE_CTX_A15 */

/*
 * Most ARM cores have a cache line size of 32 bytes.
 *
 * This can be overridden through use of the global variable
 * cacheArchAlignSize.  See below.
 */

#define _CPU_CACHE_ALIGN_SIZE 32

#endif /* _WRS_CONFIG_ARMV7_CORE_CTX_A8 || _WRS_CONFIG_ARMV7_CORE_CTX_A15 */

/*
 * The way in which _CACHE_ALIGN_SIZE is defined has been changed
 * somewhat and is no longer strictly related to the CPU type defined,
 * but is instead related to the cache type selected.  Therefore, it would
 * be better if drivers that need to know the cache line size, use this
 * variable, rather than the constant.  The variable will be initialized
 * to the appropriate cache-type-dependent value by the variant of the
 * cache library initialisation code.
 */

#ifndef	_ASMLANGUAGE
extern int cacheArchAlignSize;
#endif	/* _ASMLANGUAGE */

/*
 * Cached page tables are supported by ARM v6 and ARM v7 processors by
 * default. Turn them on here for default builds (e.g. builds not
 * configured by vxprj / VSBs).
 */

#if (!defined(_WRS_CONFIG_ARM_PRJ_BUILD) && \
     ((CPU == ARMARCH6) || (CPU == ARMARCH7) || (CPU == ARMARCH7_T2)))
#define _WRS_CONFIG_ENABLE_CACHED_PAGE_TBL
#endif

/*
 * Cached page tables are not supported for ARMv6 MPCore BSPs, so
 * disable this feature here for default & VSB builds
 */

#if ((defined (_WRS_CONFIG_SMP) && (CPU == ARMARCH6)) && \
     defined (_WRS_CONFIG_ENABLE_CACHED_PAGE_TBL))
#undef _WRS_CONFIG_ENABLE_CACHED_PAGE_TBL
#endif

/*
 * Cached page tables are not supported for ARM v4 and  ARM v5 processors, so
 * disable this feature here for default & VSB builds
 */

#if (((CPU == ARMARCH4) || (CPU == ARMARCH5) || (CPU == XSCALE)) && \
     defined (_WRS_CONFIG_ENABLE_CACHED_PAGE_TBL))
#undef _WRS_CONFIG_ENABLE_CACHED_PAGE_TBL
#endif

#if ((CPU == ARMARCH7) || (CPU == ARMARCH7_T2))

/*
 * By default cache alignment for ARMv7 is 32 bytes.  This is accomplished by
 * assigning cacheArchAlignSize as _CPU_CACHE_ALIGN_SIZE where it is declared
 * in cacheArchVars.c.  But some cores can have a cache alignment that is not
 * 32 bytes.  These cores will adjust the global variable cacheAlignSize
 * during runtime initialization.  See cacheAimCortexA8LibInit for an example
 * of this.
 */

#undef _CACHE_ALIGN_SIZE
#define _CACHE_ALIGN_SIZE cacheArchAlignSize

/* this cpu family supports power management framework */

#define _WRS_ARCH_HAS_CPU_PWR_MGMT

#else /* ((CPU == ARMARCH7) || (CPU == ARMARCH7_T2)) */

/* Cache alignment is 32 bytes */

#undef _CACHE_ALIGN_SIZE
#define _CACHE_ALIGN_SIZE _CPU_CACHE_ALIGN_SIZE

#endif /* ((CPU == ARMARCH7) || (CPU == ARMARCH7_T2)) */

#if (CPU == ARMARCH3)
#define ARM_HAS_HALFWORD_INSTRUCTIONS FALSE
#else
#define ARM_HAS_HALFWORD_INSTRUCTIONS TRUE
#endif

#define ARM_HAS_MPU FALSE

#if defined(ARMMMU) && (ARMMMU == ARMMMU_NONE)
#define ARM_HAS_NO_MMU TRUE
#else
#define ARM_HAS_NO_MMU FALSE
#endif

#if (CPU == ARMARCH4_T) || (CPU == ARMARCH5_T)
#define ARM_THUMB TRUE
#else
#define ARM_THUMB FALSE
#endif

#if (CPU == ARMARCH7_T2)
#define ARM_THUMB2 TRUE
#else /* (CPU == ARMARCH7_T2) */
#define ARM_THUMB2 FALSE
#endif /* (CPU == ARMARCH7_T2) */

#if (ARM_THUMB2)
#define PORTABLE
#endif /* ARM_THUMB2 */

 /*
  * For ARMv5 and earlier, STM(2) and LDM(2) instructions
  * must not be immediately followed by an
  * instruction that accesses a banked register.
  * Banked registers are: R8-R14.  STM(2) and LDM(2) are
  * the variations of the OP codes that end with "^"
  * (load or store registers from a different mode -- user mode)
  * and do not load the PC (do not branch).
  *
  * One possible solution to this (suggested by the
  * ARM Architecture Reference Manual) is to insert
  * a NOP between the STM or LDM call and the access
  * to a banked register.
  *
  * Here is an example of where a NOP would be required
  * because sp is one of the banked registers:
  *
  *   LDMIA   r1, {sp, lr}^
  *   NOP
  *   LDR     r1, [sp, #SC_SAVE_USERSR]
  *
  * The asm macro ARM_NOP_AFTER_USER_LDM_STM is used for
  * inserting the NOP only if the version of the architecture
  * requires it.
  */


#if (CPU == ARMARCH4) || (CPU == ARMARCH5) || (CPU == XSCALE)
#define ARM_NOP_AFTER_USER_LDM_STM  NOP
#else
#define ARM_NOP_AFTER_USER_LDM_STM
#endif

#if (CPU == ARMARCH6) || (CPU==ARMARCH7) || (CPU==ARMARCH7_T2)
#define ARM_HAS_LDREX_STREX TRUE
#define _WRS_ARM_HAS_ASID   TRUE
#else /* (CPU == ARMARCH6) || (CPU==ARMARCH7) || (CPU==ARMARCH7_T2) */
#define ARM_HAS_LDREX_STREX FALSE
#define _WRS_ARM_HAS_ASID   FALSE
#endif /* (CPU == ARMARCH6) || (CPU==ARMARCH7) || (CPU==ARMARCH7_T2) */

/** Power management for XSCALE **/

#if (CPU==XSCALE)

/* The coprocessor number of the Power Mode Register */

#define CP_CCLKCFG      14

/* OPCODE for idle */

#define PWRMODE_IDLE    1

#endif  /* Power management for XSCALE */

/** Power management for ARM **/

#if (CPU==ARMARCH5) || (CPU==ARMARCH5_T) || (CPU==ARMARCH6) \
      || (CPU==ARMARCH7) || (CPU==ARMARCH7_T2)

/* The coprocessor number of the Power Mode Register */

#define CP_CORECTL      15

/* OPCODE for idle */

#define PWRMODE_IDLE    1

#endif  /* CPU==ARMARCH5 ... ARMARCH7_T2 */

#if !defined(_WRS_CONFG_FAST_MATH) || (VFPVARIANT != VFPV3)

/* Define __ieee_status exception flags */
#define FE_IEEE_FLUSHZERO		    (0x01000000)
#define FE_IEEE_ROUND_TONEAREST		(0x00000000)
#define FE_IEEE_ROUND_UPWARD		(0x00400000)
#define FE_IEEE_ROUND_DOWNWARD		(0x00800000)
#define FE_IEEE_ROUND_TOWARDZERO	(0x00C00000)
#define FE_IEEE_ROUND_MASK		    (0x00C00000)
#define FE_IEEE_MASK_INVALID		(0x00000100)
#define FE_IEEE_MASK_DIVBYZERO		(0x00000200)
#define FE_IEEE_MASK_OVERFLOW		(0x00000400)
#define FE_IEEE_MASK_UNDERFLOW		(0x00000800)
#define FE_IEEE_MASK_INEXACT		(0x00001000)
#define FE_IEEE_MASK_ALL_EXCEPT		(0x00001F00)
#define FE_IEEE_INVALID			    (0x00000001)
#define FE_IEEE_DIVBYZERO		    (0x00000002)
#define FE_IEEE_OVERFLOW		    (0x00000004)
#define FE_IEEE_UNDERFLOW		    (0x00000008)
#define FE_IEEE_INEXACT			    (0x00000010)
#define FE_IEEE_ALL_EXCEPT		    (0x0000001F)

/* Define which of the IEEE status bits are reserved */
#define IEEE_RESERVED_MASK       (0xF63FE0E0)        

#ifndef _ASMLANGUAGE
extern unsigned int __ieee_status (unsigned int mask, unsigned int flags);
#endif

/* Define for ansiMath Testing */
#define _WRS_ARM_IEEE_STATUS
#endif

/* 
 * The default for ARMARCH7 and ARMARCH7_T2 is to use _WRS_CONFIG_FAST_MATH to
 * optimize builds created with VFP enabled. The flag to enable this behavior
 * is from the make fragments for a CPU/TOOL pair.
 * 
 * Builds that use a SW FP tool chain should not use FAST MATH to get best
 * performance. 
 *
 * Override VSB options here because VSB configuration does not detect the
 * tool chain / floating point configuration properly.
 */

#if defined(ARM_USE_VFP)
/* Vector floating point builds use FAST MATH */
#undef _WRS_CONFIG_FAST_MATH
#define _WRS_CONFIG_FAST_MATH 1
#else
/* Software floating point build does NOT use FAST MATH */
#undef _WRS_CONFIG_FAST_MATH
#endif /* defined(USE_ARM_FP) ... */

/* 
 * The default for ARMARCH7 and ARMARCH7_T2 is to use _WRS_CONFIG_FAST_MATH to
 * optimize builds created with VFP enabled. The flag to enable this behavior
 * is from the make fragments for a CPU/TOOL pair.
 * 
 * Builds that use a SW FP tool chain should not use FAST MATH to get best
 * performance. 
 *
 * Override VSB options here because VSB configuration does not detect the
 * tool chain / floating point configuration properly.
 */

#if defined(ARM_USE_VFP)
/* Vector floating point builds use FAST MATH */
#undef _WRS_CONFIG_FAST_MATH
#define _WRS_CONFIG_FAST_MATH 1
#else
/* Software floating point build does NOT use FAST MATH */
#undef _WRS_CONFIG_FAST_MATH
#endif /* defined(USE_ARM_FP) ... */

#ifdef _ASMLANGUAGE

/* 
 * File below inclusion must be after ARCH specific defines such as ARM_THUMB2. 
 */

#include <asm.h> 


/** I80310 (coyanosa) specific helper macros **/
#if ((CPU==XSCALE) || (CPU==ARMSA110))
/*
 * The following macro should be used when software needs to be assured that a
 * CP15 update has taken effect. It may only used while in a privileged mode,
 * because it accesses CP15. Ref. Coyanosa EAS 2.3.4 Additions to CP15
 * functionality
 */
#define CPWAIT(a) \
    mrc         p15, 0, a, c2, c0, 0  /* arbitrary read of CP15 */ ;\
    mov         a, a                  /* wait for it */ ;\
    sub         pc, pc, IMMED4            /* branch to next instruction */ ;
#define IMMED4  #4

/*
 * at this point, any previous CP15 writes are guaranteed
 * to have taken effect
 */


/*
 * The following macro should be used when software needs to be assure that
 * BCU has finish all outstanding operations.
 */

/*
 * CAUTION: This macro should be used only from the cacheable region, or it may
 * keep the BCU eternally busy fetching the code.
 */

#define BCUWAIT(a) \
    mrc		p13, 0, a, c0, c1, 0; /* Read BCUCTL,updates conditon code */ \
    submi       pc, pc, IMMED12 ;          /* If BCU busy (bit 31 set) try again */
#define IMMED12  #12

#endif /* if CPU=XSCALE */

#endif	/* _ASMLANGUAGE */

#endif /* (CPU == ARMARCH7M) */

#ifdef __cplusplus
}
#endif

#endif	/* __INCarmh */

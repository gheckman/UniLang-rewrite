/* mmuArmPalLib.h - ARM MPU library header file */

/* Copyright (c) 2006, 2007, 2010, 2012 Wind River Systems, Inc.
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
01e,16mar12,rec  WIND00318272 - POSIX signals conformance
01d,29apr10,pad  Moved extern C statement after include statements.
01c,21sep07,j_b  add _func_mmuFaultAddrGet prototype
01b,13jul06,m_h  Generic MPU definitions
01a,13jul06,m_h  Created from mmuArmPalLib.h and vxWorks 5.5 mmuArmLib.h

*/

#ifndef	__INCmpuArmPalLibh
#define	__INCmpuArmPalLibh

#ifndef	_ASMLANGUAGE

#include <memLib.h>

#ifdef __cplusplus
extern "C" {
#endif

#endif /* _ASMLANGUAGE */

#define MPU_NUM_REGIONS 8

#ifndef	_ASMLANGUAGE
#if (_BYTE_ORDER == _LITTLE_ENDIAN)
typedef struct
    {
    UINT enable : 1;		/* 1 => region enabled */
    UINT size	: 5;		/* size  */
    UINT pad	: 6;		/* padding */
    UINT base	: 20;		/* region base address */
    } MPU_REGION_FIELDS;
#else /* (_BYTE_ORDER == _LITTLE_ENDIAN) */
/* Big-Endian */

typedef struct
    {
    UINT base	: 20;		/* region base address */
    UINT pad	: 6;		/* padding */
    UINT size	: 5;		/* size  */
    UINT enable : 1;		/* 1 => region enabled */
    } MPU_REGION_FIELDS;
#endif /* (_BYTE_ORDER == _LITTLE_ENDIAN) */

typedef union
    {
    MPU_REGION_FIELDS fields;
    UINT32 bits;
    } MPU_REGION_REG;

typedef struct mpuTransTblStruct
    {
    MPU_REGION_REG regs[MPU_NUM_REGIONS];
    } MPU_TRANS_TBL;

#endif /* _ASMLANGUAGE */

/*
 * Architecture-dependent MPU states. These are states settable for regions.
 */

/* The size must be larger than 0x0A so zero in these fields 
 * is an invalid MPU state is it is enabled (bit-0 = 1)
 */
#define MMU_STATE_INVALID_STATE 0xFFFFFFFF

#define MPU_REGION_BASE_MASK		0xFFFFF000
#define MPU_REGION_SIZE_MASK		0x0000003E
#define MPU_REGION_SIZE_MAX		0x0000003E

#define MMU_STATE_MASK_CACHEABLE	0xC0	/* CB bits */
#define MMU_STATE_MASK_BUFFERABLE       0x40

#define MMU_STATE_MASK_VALID		0x100	/* allows 4 AP bits */
#define MMU_STATE_VALID			0x100	/* Full Access */
#define MMU_STATE_VALID_NOT		0x000	/* No access */

#ifdef MPU_USE_EXTENDED_PERMISSIONS

#define MMU_STATE_NUM_AP_BITS           4
#define MMU_STATE_MASK_PROTECTION       0xF

#else /*MPU_USE_EXTENDED_PERMISSIONS*/

#define MMU_STATE_NUM_AP_BITS           2
#define MMU_STATE_MASK_PROTECTION       0x3

#endif /*MPU_USE_EXTENDED_PERMISSIONS*/

/* cacheable and bufferable states are not real physical bit definitions */

#ifdef ARMCACHE_HAS_WRITETHROUGH
/* Write-through mode is not available on all CPUs */

#define MMU_STATE_CACHEABLE_WRITETHROUGH	0x80
#endif /*ARMCACHE_HAS_WRITETHROUGH*/

#define MMU_STATE_CACHE_BIT			0x80

#define MMU_STATE_CACHEABLE_COPYBACK		0xC0

/*
 * Set the default state to be copyback. CACHEABLE_WRITETHROUGH can also be
 * selected on 740T/946E.
 */

#define MMU_STATE_CACHEABLE		MMU_STATE_CACHEABLE_COPYBACK

#define MMU_STATE_CACHEABLE_NOT		0x0

#define MMU_STATE_BUFFERABLE		0x40	/* bufferable, not cacheable */
#define MMU_STATE_BUFFERABLE_NOT	0x0	/* will also set not cacheable*/

/*
 * We need a size for a region that means the entire address
 * space.  It is perfectly reasonable to wish to define such a region
 * and it is of course, not expressible within a UINT. So, define a
 * special size.
 */

#define MMU_ENTIRE_SPACE 0

#define MMU_STATE_SUP_RW                0x01
#define MMU_STATE_USR_RO_SUP_RW         0x02
#define MMU_STATE_USR_RW_SUP_RW         0x03
#define MMU_STATE_SUP_RO                0x05
#define MMU_STATE_USR_RO_SUP_RO         0x06

/*
 * When setting either of the attributes SPL_0 or SPL_1 it is necessary to:
 *
 * 1. specify MMU_ATTR_SPL_MSK ORred with MMU_ATTR_CACHE_MSK in the mask
 *    argument to the routine, and:
 * 2. specify the appropriate cache state ORred in to the state argument
 *    to the routine.
 *
 * So, to set a page as bufferable not cacheable, it is necessary to
 * specify both MMU_ATTR_SPL_0 and specify MMU_ATTR_CACHE_OFF in the
 * state argument. To mark a page as cacheable in the minicache,
 * MMU_ATTR_SPL_1 and MMU_ATTR_CACHE_COPYBACK must be specified in the
 * state argument. In both cases, specify MMU_ATTR_SPL_MSK ORred with
 * MMU_ATTR_CACHE_MSK in the mask argument.
 *
 * To "unset" the special attibutes SPL_0 or SPL_1, specify
 * MMU_ATTR_CACHE_MSK in the mask parameter (without MMU_ATTR_SPL_MSK),
 * and specify the cacheability required in the state argument.
 *
 * We provide the following alias on ARM, to make life easier.
 */

#define MMU_ATTR_BUFFERABLE		(MMU_ATTR_SPL_0)

/* MMU Control Register bit allocations */

#define MMUCR_M_ENABLE	 (1<<0)  /* MMU enable */
#define MMUCR_A_ENABLE	 (1<<1)  /* Address alignment fault enable */
#define MMUCR_C_ENABLE	 (1<<2)  /* (data) cache enable */
#define MMUCR_W_ENABLE	 (1<<3)  /* write buffer enable */
#define MMUCR_PROG32	 (1<<4)  /* PROG32 */
#define MMUCR_DATA32	 (1<<5)  /* DATA32 */
#define MMUCR_L_ENABLE	 (1<<6)  /* Late abort on earlier CPUs */
#define MMUCR_BIGEND	 (1<<7)  /* Big-endian (=1), little-endian (=0) */
#define MMUCR_SYSTEM	 (1<<8)  /* System bit, modifies MMU protections */
#define MMUCR_ROM	 (1<<9)  /* ROM bit, modifies MMU protections */
#define MMUCR_F		 (1<<10) /* Should Be Zero */
#define MMUCR_Z_ENABLE	 (1<<11) /* Branch prediction enable on 810 */
#define MMUCR_I_ENABLE	 (1<<12) /* Instruction cache enable */
#define MMUCR_V_ENABLE	 (1<<13) /* Exception vectors remap to 0xFFFF0000 */
#define MMUCR_ALTVECT    MMUCR_V_ENABLE /* alternate vector select */
#define MMUCR_RR_ENABLE	 (1<<14) /* Round robin cache replacement enable */
#define MMUCR_ROUND_ROBIN MMUCR_RR_ENABLE  /* round-robin placement */
#define MMUCR_DISABLE_TBIT   (1<<15) /* disable TBIT */
#define MMUCR_DSRAM_EN       (1<<16) /* D-SRAM enable  */
#define MMUCR_DSRAM_LOADMODE (1<<17) /* D-SRAM load mode select  */
#define MMUCR_ISRAM_EN       (1<<18) /* I-SRAM enable  */
#define MMUCR_ISRAM_LOADMODE (1<<19) /* I-SRAM load mode select  */

#ifndef	_ASMLANGUAGE

/* Externally visible mpuLib routines */

IMPORT UINT32 mmuReadId (void);

IMPORT UINT32	(* mmuCrGet) (void);
IMPORT void	(* mmuModifyCr) (UINT32 value, UINT32 mask);
IMPORT UINT32	mmuHardCrGet (void);
IMPORT UINT32	mmuSoftCrGet (void);
IMPORT void	mmuModifyHardCr (UINT32 value, UINT32 mask);
IMPORT void	mmuModifySoftCr (UINT32 value, UINT32 mask);

IMPORT UINT32   (* _func_mmuFaultAddrGet) (void);
IMPORT UINT32   (* _func_mmuFaultStatusGet) (void);
#if (CPU == ARMARCH6) || (CPU==ARMARCH7) || (CPU==ARMARCH7_T2)
IMPORT UINT32   (* _func_mmuIFaultStatusGet) (void);
#endif /* ARMARCH6 || ARMARCH7 || ARMARCH7_T2 */

IMPORT  void    mpuPrrSet (const MPU_REGION_REG *pRegs);
IMPORT  void    mpuPrrGet (MPU_REGION_REG *pRegs);
IMPORT  void    mpuCcrSet (UINT32 val);
IMPORT  UINT32  mpuCcrGet (void);
IMPORT  void    mpuWbcrSet (UINT32 val);
IMPORT  UINT32  mpuWbcrGet (void);
IMPORT  void    mpuPrSet (UINT32 val);
IMPORT  UINT32  mpuPrGet (void);
IMPORT  void    mpuAEnable (UINT32 cacheState);
IMPORT  void    mpuADisable (void);
IMPORT  UINT32  mpuGetEnable (void);

#endif  /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif  /* __INCmpuArmPalLibh */

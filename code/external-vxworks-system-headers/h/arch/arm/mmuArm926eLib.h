/* mmuArm926eLib.h - ARM 926E MMU library header file */

/* 
 * Copyright (c) 2002, 2004, 2005, 2007, 2010-2011 Wind River Systems, Inc.
 * 
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01h,21dec11,jdw  Update APIs to clear up warnings related to ttbr APIs
01g,29apr10,pad  Moved extern C statement after include statements.
01f,15oct07,j_b  fix MMU_INIT_VALUE (WIND00060071)
01e,18apr05,jb   Fix for SPR 108034
01d,08feb05,rec  use VIRT_ADDR and PHYS_ADDR instead of void
01c,10feb05,jb   Reverting to ROM mode for shared data/libraries
01b,09dec04,jb   Palify Arm MMU
01a,09dec02,jpd  created, based on mmuArm920tLib.h, version 01a.
*/

#ifndef	__INCmmuArm926eLibh
#define	__INCmmuArm926eLibh

#define MMU_ID_ARM926E          0x069260

#include "mmuArmPalLib.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Values to be used when mmuEnable() is called. This will be after the MMU has
 * been initialised by sysInit()/romInit() and after cacheLib has set whatever
 * cache enable settings have been chosen.
 *
 * M 1 Enable MMU
 * A 0 Disable address alignment fault
 * C X ((D-)Cache Enable) Controlled by cacheLib
 * W X (Write Buffer) Controlled by cacheLib
 * P 1 (PROG32) should be set before this
 * D 1 (DATA32) should be set before this
 * L 1 (Late abort on earlier CPUs) ignore
 * B X (Big/Little-endian) should be set before this
 * S 1 (System)
 * R 0 (ROM)
 * F 0 Should be Zero
 * Z X (Branch prediction enable on 810) Controlled by cacheLib
 * I X (I-cache enable) Controlled by cacheLib
 *
 * For time being, do not enable the address alignment fault, as GCC
 * currently generates unaligned accesses in its code, and switching this
 * on will cause immediate faults. So, do not put it into the enable
 * mask.
 *
 * We used to clear all the Reserved/Should Be Zero bits when the
 * MMU/MPU was enabled, by including one bits for them in the definition
 * of MMU_ENABLE_MASK. We no longer do this, as CPU designers may extend
 * the definitions of the bits within the MMU Control Register. The MMU
 * Control register is initialised within romInit()/sysInit(), as the BSP
 * is the only place where the particular details of the CPU/MMU are
 * actually known. In general, it will be appropriate for the BSP to
 * initialise the MMUCR Reserved/Should Be Zero bits to zero. When the
 * MMU is enabled, we will only change the bits we are particularly
 * concerned about, by using a Read-Modify-Write strategy.
 */

 /* This defines the operating mode MMUCR_ROM, MMUCR_SYSTEM, or neither */

#define MMUCR_MODE MMUCR_ROM    /* This MUST remain ROM for shared libraries */

#define MMUCR_L4_ENABLE      (1<<15) /* L4 enable, ARMv4 behavior */

#define MMU_ENABLE_MASK  (MMUCR_M_ENABLE | MMUCR_SYSTEM | MMUCR_ROM)

#define MMU_ENABLE_VALUE (MMUCR_M_ENABLE | MMUCR_MODE)

#define MMUCR_926E_SBO  ((1<<18) | (1<<16))  /* Should Be One bits */

    /*
     * Values to be used when the MMU Control Register is initialised from
     * within romInit.s or sysALib.s (before the MMU is enabled). Note that
     * on 710A, this is also used to initialise the soft-copy of the MMU CR
     * that we need to keep (in order to emulate Read-Modify-Write
     * operations). So, the BSP *MUST* initialise the MMU CR with the value
     * contained here, or else trouble will ensue. This restriction does
     * not apply to non-710A BSPs, but caution must be exercised in choosing a
     * value different to that defined here.
     */

#if (_BYTE_ORDER == _LITTLE_ENDIAN)

    /* W bit is Should Be One */
#define MMU_INIT_VALUE (MMUCR_PROG32 | MMUCR_DATA32 | MMUCR_L_ENABLE | \
                                            MMUCR_MODE | MMUCR_926E_SBO)

#else /* _BYTE_ORDER == _LITTLE_ENDIAN now _BIG_ENDIAN */

    /* big endian */

#define MMU_INIT_VALUE (MMUCR_PROG32 | MMUCR_DATA32 | MMUCR_L_ENABLE | \
                             MMUCR_BIGEND | MMUCR_MODE | MMUCR_926E_SBO)

#endif  /* _BYTE_ORDER == _LITTLE_ENDIAN */

#ifndef _ASMLANGUAGE

IMPORT	void	mmuArm926eLibInstall (VIRT_ADDR(physToVirt) (PHYS_ADDR),
                                        PHYS_ADDR(virtToPhys) (VIRT_ADDR));
IMPORT  MMU_LEVEL_1_DESC *  mmuArm926eTtbrGet ( void);
IMPORT	void	mmuArm926eTtbrSet (MMU_LEVEL_1_DESC *);
IMPORT  UINT32  mmuArm926eTtbrGetAll (void);
IMPORT	void	mmuArm926eTtbrSetAll (UINT32);
IMPORT	void	mmuArm926eDacrSet (UINT32 dacrVal);
IMPORT	void	mmuArm926eTLBIDFlushEntry (void *addr);
IMPORT	void	mmuArm926eTLBIDFlushAll (void);
IMPORT	void	mmuArm926eAEnable (UINT32 cacheState);
IMPORT	void	mmuArm926eADisable (void);

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif	/* __INCmmuArm926eLibh */

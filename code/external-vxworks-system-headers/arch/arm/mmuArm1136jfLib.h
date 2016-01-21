/* mmuArm1136jfLib.h - ARM 1136JF MMU library header file */

/*
 * Copyright (c) 2004, 2010-2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01d,20dec11,jdw  Add missing APIs to clear up warnings related to ttbr APIs
01c,29apr10,pad  Moved extern C statement after include statements.
01b,09feb10,j_b  update mmuArm1136jfTtbrSet for ASID support
01a,07dec04,jb   created
*/

#ifndef	__INCmmuArm1136jfLibh
#define	__INCmmuArm1136jfLibh

#include "memLib.h"

#define MMU_ID_ARM1136JF       0x07B360

#include "mmuArmArch6PalLib.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 1136JF Specific definitions follow */

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

#define MMUCR_MODE 0       /* This is specific to ARMARCH6 */

#define MMU_ENABLE_MASK  (MMUCR_M_ENABLE | MMUCR_EXTENDED_PAGE)

#define MMU_ENABLE_VALUE (MMUCR_M_ENABLE | MMUCR_MODE | MMUCR_EXTENDED_PAGE)

#define MMU_MUST_SET_VALUE      ( MMUCR_PROG32 | MMUCR_DATA32 | MMUCR_L_ENABLE | \
                                 MMUCR_W_ENABLE )

#if (_BYTE_ORDER == _LITTLE_ENDIAN)
#define MMU_INIT_VALUE ( MMU_MUST_SET_VALUE | MMUCR_MODE)
#else
#define MMU_INIT_VALUE ( MMU_MUST_SET_VALUE | MMUCR_BIGEND | MMUCR_MODE)
#endif

#ifndef _ASMLANGUAGE

IMPORT  void    mmuArm1136jfLibInstall (VIRT_ADDR(physToVirt) (PHYS_ADDR),
                                        PHYS_ADDR(virtToPhys) (VIRT_ADDR));
IMPORT  void    mmuArm1136jfTtbrSet (MMU_LEVEL_1_DESC *pTable, UINT32 asid);
IMPORT  MMU_LEVEL_1_DESC *  mmuArm1136jfTtbrGet (void);
IMPORT  void    mmuArm1136jfTtbrSetAll (UINT32 ttbr, UINT32 asid);
IMPORT  UINT32  mmuArm1136jfTtbrGetAll (void);
IMPORT  void    mmuArm1136jfDacrSet (UINT32 dacrVal);
IMPORT  void    mmuArm1136jfTLBIDFlushEntry (VIRT_ADDR *addr);
IMPORT  void    mmuArm1136jfTLBIDFlushAll (void);
IMPORT  void    mmuArm1136jfAEnable (UINT32 cacheState);
IMPORT  void    mmuArm1136jfADisable (void);
IMPORT  STATUS  mmuArm1136jfPBitSet (VIRT_ADDR virtAddr, UINT32 size);
IMPORT  STATUS  mmuArm1136jfPBitClear (VIRT_ADDR virtAddr, UINT32 size);
IMPORT  STATUS  mmuArm1136jfPBitGet (VIRT_ADDR virtAddr );
IMPORT  STATUS  mmuArm1136jfAcrGet (void );
IMPORT  void    mmuArm1136jfAcrSet (UINT32 acrVal);
IMPORT  STATUS  mmuArm1136jfITcmrGet (void );
IMPORT  void    mmuArm1136jfITcmrSet (UINT32 acrVal);
IMPORT  STATUS  mmuArm1136jfDTcmrGet (void );
IMPORT  void    mmuArm1136jfDTcmrSet (UINT32 acrVal);

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif	/* __INCmmuArm1136jfLibh */

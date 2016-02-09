/* mmuArm11MPCoreLib.h - ARM 11MPCORE MMU library header file */

/*
 * Copyright (c) 2007, 2010-2011 Wind River Systems, Inc.
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
01b,09feb10,j_b  update mmuArm11MPCoreTtbrSet for ASID support
01a,09jul07,j_b  Written
*/

#ifndef	__INCmmuArm11MPCoreLibh
#define	__INCmmuArm11MPCoreLibh

#include "memLib.h"

#define MMU_ID_ARM11MPCORE     0x0FB024  /* from CP15 ID Code Register c0 */

#include "mmuArmArch6PalLib.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 11MPCORE Specific definitions follow */

/*
 * Values to be used when mmuEnable() is called. This will be after the MMU has
 * been initialised by sysInit()/romInit() and after cacheLib has set whatever
 * cache enable settings have been chosen.
 *
 * M  1 Enable MMU
 * A  0 Disable address alignment fault
 * C  X ((D-)Cache Enable) Controlled by cacheLib
 * W  1 (Write Buffer - obsolete) Should be One
 * P  1 (PROG32 - obsolete) Should be One
 * D  1 (DATA32 - obsolete) Should be One
 * L  1 (Late abort - obsolete) Should be One
 * B  0 (Big/Little-endian - unsupported) Should be Zero
 * S  0 (System protection - deprecated)
 * R  0 (ROM protection - deprecated)
 * F  0 Should be Zero
 * Z  X (Branch prediction) Controlled by cacheLib
 * I  X (I-cache enable) Controlled by cacheLib
 * V  0 (Vector table location: Normal/High Address)
 * RR 1 (Random/Round-Robin cache replacement - unsupported) Should be One
 * L4 0 Load instructions to PC set T bit
 * DT 1 (Data TCM enable - obsolete) Write has no effect; Read as One
 * -  0  Should be Zero
 * IT 1 (Instruction TCM enable - unsupported) Write has no effect; Read as One
 * -  0 Should be Zero
 * -  0 Should be Zero
 * FI 0 (Fast Interrupt enable - obsolete) Should be Zero
 * U  0 Disable Unaligned data access enable
 * XP 1 Enable eXtended Page table configuration (disable subpage AP bits)
 * VE 0 (VEctored Interrupt- unsupported) Should be Zero
 * EE 0 E bit of CPSR upon Exception
 * -  0 Should be Zero
 * NM 0 Disable NMFI behavior for FIQs
 * TR 0 Disable TEX Remapping
 * FA 0 Disable Force AP[0] as access bit
 * -  0 Should be Zero
 * -  0 Should be Zero
 *
 * NOTE: All defined control register bits are set to 0 on Reset, except
 * V, U and EE which are dependent on system configuration pin signal levels.
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

IMPORT  void    mmuArm11MPCoreLibInstall (VIRT_ADDR(physToVirt) (PHYS_ADDR),
                                        PHYS_ADDR(virtToPhys) (VIRT_ADDR));
IMPORT  void    mmuArm11MPCoreTtbrSet (MMU_LEVEL_1_DESC *pTable, UINT32 asid);
IMPORT  MMU_LEVEL_1_DESC *  mmuArm11MPCoreTtbrGet (void);
IMPORT  void    mmuArm11MPCoreTtbrSetAll (UINT32 ttbr, UINT32 asid);
IMPORT  UINT32  mmuArm11MPCoreTtbrGetAll (void);
IMPORT  void    mmuArm11MPCoreDacrSet (UINT32 dacrVal);
IMPORT  void    mmuArm11MPCoreTLBIDFlushEntry (VIRT_ADDR *addr);
IMPORT  void    mmuArm11MPCoreTLBIDFlushAll (void);
IMPORT  void    mmuArm11MPCoreAEnable (UINT32 cacheState);
IMPORT  void    mmuArm11MPCoreADisable (void);
IMPORT  STATUS  mmuArm11MPCorePBitSet (VIRT_ADDR virtAddr, UINT32 size);
IMPORT  STATUS  mmuArm11MPCorePBitClear (VIRT_ADDR virtAddr, UINT32 size);
IMPORT  STATUS  mmuArm11MPCorePBitGet (VIRT_ADDR virtAddr);
IMPORT  STATUS  mmuArm11MPCoreAcrGet (void);
IMPORT  void    mmuArm11MPCoreAcrSet (UINT32 acrVal);
IMPORT  STATUS  mmuArm11MPCoreITcmrGet (void);
IMPORT  void    mmuArm11MPCoreITcmrSet (UINT32 acrVal);
IMPORT  STATUS  mmuArm11MPCoreDTcmrGet (void);
IMPORT  void    mmuArm11MPCoreDTcmrSet (UINT32 acrVal);

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif	/* __INCmmuArm11MPCoreLibh */

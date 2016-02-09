/* mmuCortexA8Lib.h - Cortex-A8 MMU library header file */

/* 
 * Copyright (c) 2008, 2010-2012, 2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01j,19aug13,zgl  LPAE support (WIND00357632)
01i,17jul12,j_b  fix mmuCortexA8AcrGet API
01h,20dec11,jdw  Add missing APIs to clear up warnings related to ttbr APIs
01g,25aug10,my_  Remove MMUCR_BIGEND in MMU_INIT_VALUE and add
                 MMUCR_EE in MMU_INIT_VALUE (WIND00229795)
01f,29apr10,pad  Moved extern C statement after include statements.
01e,09feb10,j_b  update mmuCortexA8TtbrSet for ASID support
01d,25aug10,my_  make EE bit default in BE8 mode (WIND00228157)
01c,05aug10,j_b  enable branch prediction by default (CQID: 222896)
01b,05aug10,m_h  Thumb-mode exception handling for Thumb-2
01a,11jun08,j_b  Created from mmuArm1136jfLib.h, rev 01a
*/

#ifndef	__INCmmuCortexALibh
#define	__INCmmuCortexALibh

#include "memLib.h"

#ifndef _WRS_CONFIG_ARM_LPAE
#include <arch/arm/mmuArmArch6PalLib.h>
#else /* _WRS_CONFIG_ARM_LPAE */
#include <arch/arm/mmuArmLpaeLib.h>
#endif /* !_WRS_CONFIG_ARM_LPAE */

#ifdef __cplusplus
extern "C" {
#endif

/* Cortex-A Specific definitions follow */

/*
 * Values to be used when mmuEnable() is called. This will be after the MMU has
 * been initialised by sysInit()/romInit() and after cacheLib has set whatever
 * cache enable settings have been chosen.
 * See "ARM Architecture Reference Manual ARMv7-A and ARMv7-R edition" 
 * (ARM DDI 0406) and "Cortex-A8 Processor Technical Reference Manual"
 * (ARM DDI 0344) for details.
 *
 * M     1 Enable MMU
 * A     0 Disable address alignment fault
 * C     X ((D-)Cache Enable) Controlled by cacheLib
 * -     1 (Write Buffer - obsolete) Reserved; SBO
 * -     1 (PROG32 - obsolete) Reserved; SBO
 * -     1 (DATA32 - obsolete) Reserved; SBO
 * -     1 (Late abort - obsolete) Reserved; SBO
 * B     0 (Big/Little-endian - obsolete) Reserved; SBZ
 * -     0 (System - obsolete) Reserved; SBZ
 * -     0 (ROM - obsolete) Reserved; SBZ
 * SW    0 (SWP/SWPB Enable - unsupported) SBZ; Reserved for Multiprocessing
 * Z     1 (Branch prediction enable)
 * I     X (I-cache enable) Controlled by cacheLib
 * V     0 (Vector table location: Normal/High Address)
 * RR    0 (Random/Round-Robin cache replacement - unsupported) SBZ
 * -     0 (Load instructions to PC set T bit - obsolete) SBZ
 * -     1 (Data TCM enable - obsolete) SBO
 * HA    0 (Hardware Access flag enable - unsupported) SBZ
 * -     1 (Instruction TCM enable - obsolete) SBO
 * -     0 Reserved; SBZ
 * -     0 Reserved; SBZ
 * FI    0 (Fast Interrupt enable - unsupported) SBZ
 * U     1 (Unaligned access enable); SBO
 * -     1 (extended PTE format enable - obsolete) SBO
 * VE    0 (VEctored Interrupt - unsupported) SBZ
 * EE    0 Exception Endian set to Little-Endian
 * -     0 Reserved; SBZ
 * NMFI  0 Disable NMFI behavior for FIQs
 * TRE   0 Disable TEX Remap
 * AFE   0 Disable Access Flag
 * TE    X if Thumb-2 enable Thumb Exceptions
 * -     0 Reserved; SBZ
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

#define MMU_ENABLE_MASK	    (MMUCR_M_ENABLE)

#define MMU_ENABLE_VALUE    (MMUCR_M_ENABLE)

#if (ARM_THUMB2)
#define MMU_EXCEPTION_MODE   MMUCR_THUMB_EXCEPTIONS
#else /* (ARM_THUMB2) */
#define MMU_EXCEPTION_MODE   0x0
#endif /* (ARM_THUMB2) */

/* Control Register SBO bits */

#define MMU_MUST_SET_VALUE  (MMUCR_PROG32 | MMUCR_DATA32 | MMUCR_L_ENABLE | \
			     MMUCR_W_ENABLE | MMUCR_ENABLE_DTCM | \
			     MMUCR_ENABLE_ITCM | MMUCR_UNALIGNED_ENABLE | \
			     MMUCR_EXTENDED_PAGE | MMU_EXCEPTION_MODE)

#if (_BYTE_ORDER == _LITTLE_ENDIAN)
#define MMU_INIT_VALUE	(MMU_MUST_SET_VALUE | MMUCR_Z_ENABLE)
#else
#define MMU_INIT_VALUE	(MMU_MUST_SET_VALUE | MMUCR_Z_ENABLE | MMUCR_EE)
#endif

#ifndef _ASMLANGUAGE

IMPORT  void    mmuCortexA8LibInstall (VIRT_ADDR(physToVirt) (PHYS_ADDR),
                                       PHYS_ADDR(virtToPhys) (VIRT_ADDR));
#ifndef _WRS_CONFIG_ARM_LPAE
IMPORT  void    mmuCortexA8TtbrSet (MMU_LEVEL_1_DESC *pTable, UINT32 asid);
IMPORT  MMU_LEVEL_1_DESC *  mmuCortexA8TtbrGet (void);
IMPORT  void    mmuCortexA8TtbrSetAll (UINT32 ttbr, UINT32 asid);
IMPORT  UINT32  mmuCortexA8TtbrGetAll (void);
IMPORT  void    mmuCortexA8DacrSet (UINT32 dacrVal);
#else /* _WRS_CONFIG_ARM_LPAE */
IMPORT  void    mmuCortexA8TtbrSet64 (UINT64 ttbr);
IMPORT  UINT64  mmuCortexA8TtbrGet64 (void);
IMPORT  void    mmuCortexA8MairSet(UINT32 mair0Val, UINT32 mair1Val);
IMPORT  void    mmuCortexA8TtbcrSet (UINT32 ttbcr);
IMPORT  UINT32  mmuCortexA8TtbcrGet (void);
#endif /* !_WRS_CONFIG_ARM_LPAE */

IMPORT  void    mmuCortexA8TLBIDFlushEntry (VIRT_ADDR *addr);
IMPORT  void    mmuCortexA8TLBIDFlushAll (void);
IMPORT  void    mmuCortexA8AEnable (UINT32 cacheState);
IMPORT  void    mmuCortexA8ADisable (void);
IMPORT  STATUS  mmuCortexA8PBitSet (VIRT_ADDR virtAddr, UINT32 size);
IMPORT  STATUS  mmuCortexA8PBitClear (VIRT_ADDR virtAddr, UINT32 size);
IMPORT  STATUS  mmuCortexA8PBitGet (VIRT_ADDR virtAddr);
IMPORT  UINT32  mmuCortexA8AcrGet (void);
IMPORT  void    mmuCortexA8AcrSet (UINT32 acrVal);
IMPORT  STATUS  mmuCortexA8ITcmrGet (void);
IMPORT  void    mmuCortexA8ITcmrSet (UINT32 acrVal);
IMPORT  STATUS  mmuCortexA8DTcmrGet (void);
IMPORT  void    mmuCortexA8DTcmrSet (UINT32 acrVal);

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif	/* __INCmmuCortexALibh */

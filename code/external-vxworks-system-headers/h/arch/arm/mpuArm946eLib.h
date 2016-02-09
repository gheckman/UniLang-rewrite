/* mpuArm946eLib.h - ARM 946E MPU library header file */

/* Copyright (c) 1998-2006, 2010 Wind River Systems, Inc.
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
01f,29apr10,pad  Moved extern C statement after include statements.
01e,13jul06,m_h  MPU not MMU
01d,22may06,m_h  Palify
01c,08feb05,rec  use VIRT_ADDR and PHYS_ADDR instead of void
01b,10aug04,scm  adjust for MPU removal...
01a,19jul00,jpd  created, based on mmuArm940tLib.h.
*/

#ifndef	__INCmpuArm946eLibh
#define	__INCmpuArm946eLibh

#define MMU_ID_ARM946E          0x059460

#include "mpuArmPalLib.h"

#ifdef __cplusplus
extern "C" {
#endif

 /* This defines the operating mode MMUCR_ROM, MMUCR_SYSTEM, or neither */

#define MMUCR_MODE MMUCR_ROM    /* This MUST remain ROM for shared libraries */

#define MMUCR_L4_ENABLE      (1<<15) /* L4 enable, ARMv4 behavior */

#define MMU_ENABLE_MASK  (MMUCR_M_ENABLE | MMUCR_SYSTEM | MMUCR_ROM)

#define MMU_ENABLE_VALUE (MMUCR_M_ENABLE | MMUCR_MODE)

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

    /* W bit should Be One */
#define MMU_INIT_VALUE (MMUCR_PROG32 | MMUCR_DATA32 | MMUCR_L_ENABLE | \
                                            MMUCR_MODE)

#else /* _BYTE_ORDER == _LITTLE_ENDIAN now _BIG_ENDIAN */

    /* big endian */

    /* W bit should Be One */
#define MMU_INIT_VALUE (MMUCR_PROG32 | MMUCR_DATA32 | MMUCR_L_ENABLE | \
                                            MMUCR_BIGEND | MMUCR_MODE)
#endif  /* _BYTE_ORDER == _LITTLE_ENDIAN */

#ifndef _ASMLANGUAGE

IMPORT	void    mpuArm946eLibInstall (void);
IMPORT	STATUS  mpuArm946eShowInstall (void);

IMPORT  void    mpuArm946ePrrSet (const MPU_REGION_REG *pRegs);
IMPORT  void    mpuArm946ePrrGet (MPU_REGION_REG *pRegs);

IMPORT  void    mpuArm946eCcrSet (UINT32 val);
IMPORT  UINT32  mpuArm946eCcrGet (void);
IMPORT  void    mpuArm946eWbcrSet (UINT32 val);
IMPORT  UINT32  mpuArm946eWbcrGet (void);
IMPORT  void    mpuArm946ePrSet (UINT32 val);
IMPORT  UINT32  mpuArm946ePrGet (void);
IMPORT  void    mpuArm946eAEnable (UINT32 cacheState);
IMPORT  void    mpuArm946eADisable (void);

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif	/* __INCmpuArm946eLibh */

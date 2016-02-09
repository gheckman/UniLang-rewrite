/* mmuArmManzano.h - Manzano (XScale varient) MMU library header file */

/* Copyright (c) 1998-2006 Wind River Systems, Inc.
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
012,22feb06,m_h  Manzano Support
011,25jan06,m_h  created.
*/

#ifndef __INCmmuArmManzanoLibh
#define __INCmmuArmManzanoLibh

/* Enable support for supersection descriptors */
#undef INCLUDE_MMU_SUPERSECTION_SUPPORT
#define INCLUDE_MMU_SUPERSECTION_SUPPORT

#ifdef INCLUDE_MMU_SUPERSECTION_SUPPORT
  /* Supersections require "section" functionality */
  #undef INCLUDE_MMU_SECTION_SUPPORT
  #define INCLUDE_MMU_SECTION_SUPPORT
#endif /* INCLUDE_MMU_SUPERSECTION_SUPPORT */


#undef INCLUDE_MMU_SBIT_SUPPORT
#define INCLUDE_MMU_SBIT_SUPPORT

#include "arch/arm/mmuArmXSCALELib.h"

#ifndef _ASMLANGUAGE

#if defined(__STDC__) || defined(__cplusplus)


IMPORT  void    mmuMANZANOLibInstall (VIRT_ADDR(physToVirt) (PHYS_ADDR),
                                        PHYS_ADDR(virtToPhys) (VIRT_ADDR));
IMPORT  void    mmuMANZANOTtbrSet (MMU_LEVEL_1_DESC *);
IMPORT  MMU_LEVEL_1_DESC *  mmuMANZANOTtbrGet ( void);
IMPORT  void    mmuMANZANODacrSet (UINT32 dacrVal);
IMPORT  void    mmuMANZANOTLBIDFlushEntry (void *addr);
IMPORT  void    mmuMANZANOTLBIDFlushAll (void);
IMPORT  void    mmuMANZANOAEnable (UINT32 cacheState);
IMPORT  void    mmuMANZANOADisable (void);
IMPORT  STATUS  mmuMANZANOPBitSet ( void * virtAddr, UINT32 size);
IMPORT  STATUS  mmuMANZANOPBitClear ( void * virtAddr, UINT32 size);
IMPORT  STATUS  mmuMANZANOPBitGet ( void * virtAddr );
IMPORT  STATUS  mmuMANZANOAcrGet (void );
IMPORT  void    mmuMANZANOAcrSet (UINT32 acrVal);

#else   /* __STDC__ */

IMPORT  void    mmuMANZANOLibInstall ();
IMPORT  void    mmuMANZANOTtbrSet ();
IMPORT  MMU_LEVEL_1_DESC *  mmuMANZANOTtbrGet ();
IMPORT  void    mmuMANZANODacrSet ();
IMPORT  void    mmuMANZANOTLBIDFlushEntry ();
IMPORT  void    mmuMANZANOTLBIDFlushAll ();
IMPORT  void    mmuMANZANOAEnable ();
IMPORT  void    mmuMANZANOADisable ();
IMPORT  STATUS  mmuMANZANOPBitSet ();
IMPORT  STATUS  mmuMANZANOPBitClear ();
IMPORT  STATUS  mmuMANZANOPBitGet ();
IMPORT  STATUS  mmuMANZANOAcrGet ();
IMPORT  void    mmuMANZANOAcrSet ();

#endif  /* __STDC__ */

#endif  /* _ASMLANGUAGE */

#endif  /* __INCmmuArmManzanoLibh */

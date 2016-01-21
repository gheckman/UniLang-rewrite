/* mmuArm710aLib.h - ARM 710a MMU library header file */

/* Copyright 1998-2005 Wind River Systems, Inc. */

/*
modification history
--------------------
01c,08feb05,rec  use VIRT_ADDR and PHYS_ADDR instead of void
01b,20jan99,cdp  removed support for old ARM libraries.
01a,24nov98,cdp  created.
*/

#ifndef	__INCmmuArm710aLibh
#define	__INCmmuArm710aLibh

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ASMLANGUAGE

IMPORT	void	mmuArm710aLibInstall (VIRT_ADDR(physToVirt) (PHYS_ADDR),
                                      PHYS_ADDR(virtToPhys) (VIRT_ADDR));
IMPORT  void    mmuArm710aTtbrSet (LEVEL_1_DESC *);
IMPORT  void    mmuArm710aDacrSet (UINT32 dacrVal);
IMPORT  void    mmuArm710aTLBIDFlushEntry (void *addr);
IMPORT  void    mmuArm710aTLBIDFlushAll (void);
IMPORT  void    mmuArm710aAEnable (UINT32 cacheState);
IMPORT  void    mmuArm710aADisable (void);

#endif	/* _ASMLANGUAGE */


#ifdef __cplusplus
}
#endif

#endif	/* __INCmmuArm710aLibh */

/* cacheArmXSCALELib.h - ARM XScale cache library header file */

/* Copyright 199-2005 Wind River Systems, Inc. */

/*
modification history
--------------------
01h,08feb05,rec  use VIRT_ADDR and PHYS_ADDR instead of void
01g,07dec04,jb   Further Palify ARM Aim cache
01f,01dec03,scm  flushing out aim...
01e,25jul01,scm  add btbInvalidate...
01d,23jul01,scm  change XScale name to conform to coding standards...
01c,09feb01,scm  add support for cache & TLB locking...
01b,19dec00,scm  correct cache sizes...
01a,31aug00,scm  created
*/

#ifndef	__INCcacheArmXSCALELibh
#define	__INCcacheArmXSCALELibh

#ifdef __cplusplus
extern "C" {
#endif

#define D_CACHE_SIZE		(32*1024) /* 32 kbytes DCache */
#define I_CACHE_SIZE		(32*1024) /* 32 kbytes ICache */

#define MINI_CACHE_SIZE		(2*1024)  /* 2 kbytes minicache */
#define MINI_CACHE_LINE_SIZE	32	 /* 32 bytes per line*/

/*
 * Some cache designs (e.g. Harvard) have D-cache either fully or
 * partially not coherent with I-cache
 */

#define ARMCACHE_NOT_COHERENT TRUE

/*
 * This is a writethrough cache
 */

#define ARMCACHE_HAS_WRITETHROUGH TRUE

/*
 * Has a mini-cache
 */

#define ARMCACHE_HAS_MINICACHE TRUE

/*
 * Does not need an Instruction Memory Barrier
 */

#define ARMCACHE_NEEDS_IMB FALSE


#ifndef _ASMLANGUAGE

IMPORT void	cacheArmXSCALELibInstall (VIRT_ADDR(physToVirt) (PHYS_ADDR),
                                          PHYS_ADDR(virtToPhys) (VIRT_ADDR));


/* definitions to allow for non-cacheAim direct calls */

#define cacheArmXSCALEDClearDisable cacheAimXSCALEDClearDisable
#define cacheArmXSCALEIClearDisable cacheAimXSCALEIClearDisable

IMPORT void	cacheAimXSCALEDClearDisable (void);
IMPORT void	cacheAimXSCALEIClearDisable (void);

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif	/* __INCcacheArmXSCALELibh */

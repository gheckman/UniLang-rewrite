/* cacheArm920tLib.h - ARM 920T cache library header file */

/* Copyright 1998-2005 Wind River Systems, Inc. */

/*
modification history
--------------------
01d,08feb05,rec  use VIRT_ADDR and PHYS_ADDR instead of void
01c,09dec04,jb   Further Palify ARM Aim cache
01b,11dec03,scm  flushing out aim...
01a,04feb99,jpd  created
*/

#ifndef	__INCcacheArm920tLibh
#define	__INCcacheArm920tLibh

#ifdef __cplusplus
extern "C" {
#endif

#define D_CACHE_SIZE	(16*1024) /* 16 kbytes DCache */
#define I_CACHE_SIZE	(16*1024) /* 16 kbytes ICache */

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
 * Does not have a mini-cache
 */

#define ARMCACHE_HAS_MINICACHE FALSE

/*
 * Do not need an Instruction Memory Barrier
 */

#define ARMCACHE_NEEDS_IMB FALSE


#ifndef _ASMLANGUAGE

IMPORT	void	cacheArm920tLibInstall (VIRT_ADDR(physToVirt) (PHYS_ADDR),
                                        PHYS_ADDR(virtToPhys) (VIRT_ADDR));

/* definitions to allow for non-cacheAiIM direct calls */

#define cacheArm920tDClearDisable  cacheAim920tDClearDisable
#define cacheArm920tIClearDisable  cacheAim920tIClearDisable

#endif	/* _ASMLANGUAGE */


#ifdef __cplusplus
}
#endif

#endif	/* __INCcacheArm920tLibh */

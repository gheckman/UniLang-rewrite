/* cacheArm926eLib.h - ARM 926E cache library header file */

/* Copyright 2002-2005 Wind River Systems, Inc. */

/*
modification history
--------------------
01d,08feb05,rec  use VIRT_ADDR and PHYS_ADDR instead of void
01c,07dec04,jb   Further Palify ARM Aim cache
01b,11dec03,scm  flushing out aim...
01a,09dec02,jpd  created, based on cacheArm946eLib.h
*/

#ifndef	__INCcacheArm926eLibh
#define	__INCcacheArm926eLibh

#ifdef __cplusplus
extern "C" {
#endif

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

IMPORT void	cacheArm926eLibInstall (VIRT_ADDR(physToVirt) (PHYS_ADDR),
                                        PHYS_ADDR(virtToPhys) (VIRT_ADDR));


#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif	/* __INCcacheArm926eLibh */

/* cacheArm1136jfLib.h - ARM 1136JF cache library header file */

/* Copyright 2005, 2010 Wind River Systems, Inc. */

/*
modification history
--------------------
01c,29apr10,pad  Moved extern C statement after include statements.
01b,18apr05,jb   Fix for SPR 108034
01a,07dec04,jb   created
*/

#ifndef	__INCcacheArm1136jfLibh
#define	__INCcacheArm1136jfLibh

/*
 * Include ARCH6 common defines.
 */

#include "arch/arm/cacheArmArch6.h"

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

#define ARMCACHE_NEEDS_IMB TRUE

/*
 * Most of the cache designs are virtually addressed, but some newer
 * ones have physically addressed caches. Note that this is the method of
 * addressing, not whether the cache has physical address tags within
 * it.
 */

#define ARMCACHE_IS_PHYSICALLY_ADDRESSED TRUE

#ifndef _ASMLANGUAGE

IMPORT void     cacheArm1136jfLibInstall (VIRT_ADDR(physToVirt) (PHYS_ADDR),
                                           PHYS_ADDR(virtToPhys) (VIRT_ADDR));

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif	/* __INCcacheArm1136jfLibh */

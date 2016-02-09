/* cacheCortexA9Lib.h - Cortex-A9 cache library header file */

/*
 * Copyright (c) 2009, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01c,29apr10,pad  Moved extern C statement after include statements.
01b,20oct09,z_l  Created from cacheCortexA8Lib.h, rev 01a
*/

#ifndef __INCcacheCortexA9Libh
#define __INCcacheCortexA9Libh

/* Include ARCH7 common defines. */

#include "arch/arm/cacheArmArch7.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Some cache designs (e.g. Harvard) have D-cache either fully or
 * partially not coherent with I-cache
 */

#define ARMCACHE_NOT_COHERENT TRUE

/* This is a writethrough cache */

#define ARMCACHE_HAS_WRITETHROUGH TRUE

/* Does not have a mini-cache */

#define ARMCACHE_HAS_MINICACHE FALSE

/* Do not need an Instruction Memory Barrier */

#define ARMCACHE_NEEDS_IMB TRUE

/*
 * Most of the cache designs are virtually addressed, but some newer
 * ones have physically addressed caches. Note that this is the method of
 * addressing, not whether the cache has physical address tags within
 * it.
 */

#define ARMCACHE_IS_PHYSICALLY_ADDRESSED TRUE

#ifndef _ASMLANGUAGE

IMPORT void cacheCortexA9LibInstall (VIRT_ADDR(physToVirt) (PHYS_ADDR),
                                     PHYS_ADDR(virtToPhys) (VIRT_ADDR));
IMPORT void cacheCortexA9DClearDisable (void);

/* SMP support functions */

#ifdef _WRS_CONFIG_SMP
IMPORT void cacheCortexA9MPCoreSMPInit(void);
#endif /* _WRS_CONFIG_SMP */

#endif    /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCcacheCortexA9Libh */

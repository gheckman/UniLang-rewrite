/* cacheCortexA8Lib.h - Cortex-A8 cache library header file */

/*
 * Copyright 2008, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01c,23sep10,j_b  add cacheCortexL2ClearAll() prototype
01b,29apr10,pad  Moved extern C statement after include statements.
01a,03jun08,j_b  Created from cacheArm1136jfLib.h, rev 01b
*/

#ifndef	__INCcacheCortexA8Libh
#define	__INCcacheCortexA8Libh

/*
 * Include ARCH7 common defines.
 */

#include "arch/arm/cacheArmArch7.h"

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

IMPORT void cacheCortexA8LibInstall (VIRT_ADDR(physToVirt) (PHYS_ADDR),
                                     PHYS_ADDR(virtToPhys) (VIRT_ADDR));

IMPORT void cacheCortexA8DClearDisable (void);  /* includes L2 cache */

/* L2 Cache support functions */

IMPORT UINT32	cacheCortexA8L2CacrGet (void);
IMPORT void	cacheCortexA8L2CacrSet (UINT32 cacr);
IMPORT void	cacheCortexA8L2Enable (void);
IMPORT void	cacheCortexA8L2Disable (void);
IMPORT void	cacheCortexA8L2ClearAll (void);

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif	/* __INCcacheCortexA8Libh */

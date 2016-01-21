/* cacheCortexA15Lib.h - Cortex-A15 cache library header file */

/*
 * Copyright 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01b,31aug12,ggm  Added SMP support.
01a,14jul12,j_b  Created from cacheCortexA8Lib.h, rev 01c
*/

#ifndef	__INCcacheCortexA15Libh
#define	__INCcacheCortexA15Libh

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
 * Does need an Instruction Memory Barrier
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

IMPORT void cacheCortexA15LibInstall (VIRT_ADDR(physToVirt) (PHYS_ADDR),
                                     PHYS_ADDR(virtToPhys) (VIRT_ADDR));

IMPORT void cacheCortexA15DClearDisable (void);  /* includes L2 cache */

/* L2 Cache support functions */

IMPORT UINT32	cacheCortexA15L2CacrGet (void);
IMPORT void	cacheCortexA15L2CacrSet (UINT32 cacr);
IMPORT UINT32	cacheCortexA15L2EcrGet (void);
IMPORT void	cacheCortexA15L2EcrSet (UINT32 ecr);

IMPORT void	cacheCortexA8L2ClearAll (void);

/* CPU ID access function and definitions */

IMPORT UINT32 mmuReadId (void);

/* SMP support functions */

#ifdef _WRS_CONFIG_SMP
IMPORT void cacheCortexA15MPCoreSMPInit(void);
#endif

#define  MAIN_ID_PART_MASK		0xFFF0
#define  MAIN_ID_PART_SHIFT		0x4
#define  MAIN_ID_PART_CORTEXA15		0xC0F

/* Auxiliary Control Register access functions and definitions */

IMPORT UINT32 mmuCortexA8AcrGet (void);
IMPORT void mmuCortexA8AcrSet (UINT32 acrVal);

  /* enable invalidation of branch tgt buffer with I-cache invalidate */

#define  ACTLR_BTB_INVAL_EN		0x1 

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif	/* __INCcacheCortexA15Libh */

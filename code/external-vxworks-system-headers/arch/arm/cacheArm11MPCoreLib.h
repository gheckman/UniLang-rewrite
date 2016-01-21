/* cacheArm11MPCoreLib.h - ARM 11 MPCore cache library header file */

/*
 * Copyright (c) 2007, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01b,29apr10,pad  Moved extern C statement after include statements.
01a,10jul07,m_h   created
*/

#ifndef	__INCcacheArm11MPCoreLibh
#define	__INCcacheArm11MPCoreLibh

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

/* Offsets from PERIPHBASE into MPCore Private Memory Region */

#define MPCORE_PMR_SNU_CTRL_OFFSET          (0x00)
#define MPCORE_PMR_SNU_CONFIG_OFFSET        (0x04)
#define MPCORE_PMR_CPU_STATUS_OFFSET        (0x08)
#define MPCORE_PMR_INVALIDATE_ALL_OFFSET    (0x0C)

/* Snoop Control Unit -- control register masks */

#define MPCORE_PMR_SNU_CTRL_EN           (0x00000001)

#ifndef _ASMLANGUAGE

IMPORT UINT32 arm11MPCorePeriphBaseAddr;

IMPORT void  cacheArm11MPCoreLibInstall (VIRT_ADDR(physToVirt) (PHYS_ADDR),
                                         PHYS_ADDR(virtToPhys) (VIRT_ADDR));

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif	/* __INCcacheArm11MPCoreLibh */

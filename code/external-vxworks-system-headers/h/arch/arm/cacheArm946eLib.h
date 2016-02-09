/* cacheArm946eLib.h - ARM 946E cache library header file */

/* 
 * Copyright (c) 2000-2006 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 


/*
modification history
--------------------
01e,16jun06,m_h  non-cacheAIM direct calls
01d,22may06,m_h  Palify
01c,08feb05,rec  use VIRT_ADDR and PHYS_ADDR instead of void
01b,11dec03,scm  flushing out aim...
01a,20jul00,jpd  created, based on cacheArm940tLib.h
*/

#ifndef	__INCcacheArm946eLibh
#define	__INCcacheArm946eLibh

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

IMPORT void	cacheArm946eLibInstall (VIRT_ADDR(physToVirt) (PHYS_ADDR),
                                        PHYS_ADDR(virtToPhys) (VIRT_ADDR));

/* definitions to allow for non-cacheAIM direct calls */

#define cacheArm946eDClearDisable  cacheAim946eDClearDisable

IMPORT void	cacheArm946eDClearDisable (void);

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif	/* __INCcacheArm946eLibh */

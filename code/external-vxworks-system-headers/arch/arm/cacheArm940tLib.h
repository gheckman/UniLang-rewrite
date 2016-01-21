/* cacheArm940tLib.h - ARM 940T cache library header file */

/* Copyright 1998-2005 Wind River Systems, Inc. */

/*
modification history
--------------------
01d,27jul06,m_h  vxWorks 6.x Support
01c,08feb05,rec  use VIRT_ADDR and PHYS_ADDR instead of void
01b,11dec03,scm  flushing out aim...
01a,24nov98,jpd  created
*/

#ifndef	__INCcacheArm940tLibh
#define	__INCcacheArm940tLibh

#ifdef __cplusplus
extern "C" {
#endif

#define D_CACHE_SIZE            (4*1024) /* 4 kbytes DCache */

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

IMPORT void	cacheArm940tLibInstall (VIRT_ADDR(physToVirt) (PHYS_ADDR),
                                        PHYS_ADDR(virtToPhys) (VIRT_ADDR));

#if 0

/* if true, not building with cacheAIM support... */

/* The following prototypes are pre-cacheAIM support */

IMPORT void	cacheArm940tDClearDisable (void);
IMPORT void	cacheArm940tDFlush (void * addr);
IMPORT void	cacheArm940tDFlushAll (void);
IMPORT void	cacheArm940tDInvalidateAll (void);
IMPORT void	cacheArm940tIInvalidateAll (void);
IMPORT void	cacheArm940tIInvalidate (void * addr);
IMPORT void	cacheArm940tDClearAll (void);
IMPORT void	cacheArm940tDClear (void * addr);
IMPORT void	cacheArm940tIClearDisable (void);
IMPORT void	cacheArm940tArchPipeFlush (void);

#else

/* else, cacheAIM support... */

/* definitions to allow for non-cacheAiIM direct calls */

#define cacheArm940tDClearDisable  cacheAim940tDClearDisable
#define cacheArm940tIClearDisable  cacheAim940tIClearDisable

#endif

#endif	/* _ASMLANGUAGE */


#ifdef __cplusplus
}
#endif

#endif	/* __INCcacheArm940tLibh */

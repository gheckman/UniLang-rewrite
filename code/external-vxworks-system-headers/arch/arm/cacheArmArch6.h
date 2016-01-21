/* cacheArmArch6.h - ARM ARCH6 cache library header file */

/* Copyright 2004-2005, 2009, 2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01e,30sep11,cwl  define functions for cache enable/disable. (WIND00284079)
01d,18feb11,my_  Declare new functions which support L2 cache.
01c,18sep09,j_b  add core-specific function ptr for DClearDisable operation
01b,20apr05,jb   Fix for SPR 108034
01a,07dec04,jb   created
*/

#ifndef	__INCcacheArmArch6h
#define	__INCcacheArmArch6h

#ifdef __cplusplus
extern "C" {
#endif

#ifndef	_ASMLANGUAGE

/*
 * Common definitions for Arm Arch6 Cache support
 */

extern STATUS cacheAimArch6IEnable (void);
extern STATUS cacheAimArch6DEnable (void);

extern STATUS cacheAimArch6IDisable (void);
extern STATUS cacheAimArch6DDisable (void);

extern STATUS cacheAimArch6IProbe (void);
extern STATUS cacheAimArch6DProbe (void);

extern BOOL   cacheAimArch6IIsOn (void);
extern BOOL   cacheAimArch6DIsOn (void);

extern STATUS cacheAimArch6TextUpdate (void * start, UINT32 count, UINT32 IcacheLineSize, UINT32 DcacheLineSize);

extern void * cacheAimArch6DmaMalloc (size_t bytes);
extern STATUS cacheAimArch6DmaFree (void * pBuf);

extern BOOL   cacheAimArch6MmuIsOn (void);

extern STATUS cacheAimArch6DInvalidate (void * start, void * end, UINT32 step);
extern STATUS cacheAimArch6DInvalidateAll (void);

extern STATUS cacheAimArch6IInvalidate (void * start, void * end, UINT32 step);
extern STATUS cacheAimArch6IInvalidateAll (void);

extern STATUS cacheAimArch6DFlush (void * start, void * end, UINT32 step);
extern STATUS cacheAimArch6DFlushAll (void);

extern STATUS cacheAimArch6DClear (void * start, void * end, UINT32 step);

extern STATUS cacheAimArch6PipeFlush (void);

extern void cacheAimArch6IMB (void);

extern void cacheAimArch6IClearDisable (void);
extern void cacheAimArch6DClearDisableWithVerify (void);
extern void cacheAimArch6DClearDisableNoVerify (void);

extern UINT32 cacheAimArch6Identify (void);

extern  FUNCPTR  sysCacheLibInit;
extern  UINT32   cacheArchState;

extern STATUS cacheArchIInvalidate(void * start, void * end, UINT32 step);
extern STATUS cacheArchIInvalidateAll(void);
extern STATUS cacheArchDFlush(void * start, void * end, UINT32 step);
extern STATUS cacheArchDFlushAll(void);
extern STATUS cacheArchDInvalidate(void * start, void * end, UINT32 step);
extern STATUS cacheArchDInvalidateAll(void);
extern STATUS cacheArchDClear(void * start, void * end, UINT32 step);
extern STATUS cacheArchDClearAll (void);

/* 
 * Core-specific function pointer for D-cache ClearDisable operation.
 * These must be initialized by the cacheAim<core>LibInit() routine.
 */

extern  VOIDFUNCPTR  _func_cacheAimArch6DClearDisable;

extern void (*_pSysL2CacheEnable)(CACHE_TYPE cacheType);
extern void (*_pSysL2CacheDisable)(CACHE_TYPE cacheType);
extern void (*_pSysL2CacheInvFunc)(CACHE_TYPE cacheType, void * start, void * end);
extern void (*_pSysL2CacheFlush)(CACHE_TYPE cacheType, void * start, void * end);
extern void (*_pSysL2CacheClear)(CACHE_TYPE cacheType, void * start, void * end);

extern void cacheArchL2CacheEnable(void);
extern void cacheArchL2CacheDisable(void);

extern BOOL cacheArchL2CacheIsOn(void);

#endif

#ifdef __cplusplus
}
#endif

#endif	/* __INCcacheArmArch6h */

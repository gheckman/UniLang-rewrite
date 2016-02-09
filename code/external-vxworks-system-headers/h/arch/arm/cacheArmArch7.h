/* cacheArmArch7.h - ARM ARCH7 cache library header file */

/*
 * Copyright (c) 2008, 2010, 2012, 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
06jan14,c_l  Improve cache operation. (VXW6-27040)
01h,09nov12,j_b  remove unnecessary L1 data cache operation macro
01g,04oct12,j_b  add macro to operate only on entire L1 D-cache
01f,21sep12,j_b  Add DSB to end of _CORTEX_AR_ENTIRE_DATA_CACHE_OP
01e,10sep12,m_h  L2 cachePipeFlush (WIND00240234)
01d,02jun10,m_h  Thumb-2 Support
01c,19may10,z_l  Declare new functions which support L2 cache.
01b,01aug08,j_b  fix _CORTEX_AR_ENTIRE_DATA_CACHE_OP labels
01a,11jun08,j_b  Created from cacheArmArch6.h, rev 01b
*/

#ifndef	__INCcacheArmArch7h
#define	__INCcacheArmArch7h

#ifdef __cplusplus
extern "C" {
#endif

#ifndef	_ASMLANGUAGE

/*
 * Common definitions for Arm Arch7 Cache support
 */

/* cache levels: 7 possible, indexed starting from 0 */

#define ARMV7_CACHE_LVL1	0
#define ARMV7_CACHE_LVL2	1
#define ARMV7_CACHE_LVL3	2
#define ARMV7_CACHE_LVL4	3
#define ARMV7_CACHE_LVL5	4
#define ARMV7_CACHE_LVL6	5
#define ARMV7_CACHE_LVL7	6

/* cache types from Cache Level ID register (CLIDR) */

#define ARMV7_CLID_ICACHE_TYPE	0x1	/* instruction cache */
#define ARMV7_CLID_DCACHE_TYPE	0x2	/* data cache */
#define ARMV7_CLID_UCACHE_TYPE	0x4	/* unified cache */

/* cache types for Cache Size Selection register (CSSEL) */

#define ARMV7_CSSEL_ICACHE_TYPE	0x1	/* select instruction cache */
#define ARMV7_CSSEL_DCACHE_TYPE	0x0	/* select data or unified cache */

/* cache size info from Cache Size ID register (CCSIDR) */

#define ARMV7_CCSID_LINESIZE_MSK	0x7	/* line size bit mask */
#define ARMV7_CCSID_WAYNUM_MSK		0x1FF8	/* associativity bit mask */
#define ARMV7_CCSID_SETNUM_MSK		0xFFFE000  /* set number bit mask */
#define ARMV7_CCSID_MODE_MSK		0xF0000000  /* mode bit mask */

#define ARMV7_CCSID_WAYNUM_SHFT		3	/* associativity field shift */
#define ARMV7_CCSID_SETNUM_SHFT		13	/* set number field shift */

#define ARMV7_CCSID_MODE_WT		0x80000000  /* write-through mode */
#define ARMV7_CCSID_MODE_WB		0x40000000  /* write-back mode */
#define ARMV7_CCSID_MODE_RA		0x20000000  /* read-allocate mode */
#define ARMV7_CCSID_MODE_WA		0x10000000  /* write-allocate mode */

/*
 * Common routines for Arm Arch7 Cache support
 * 
 * Note that many of the Arch 6 routines are still valid for Arch 7 and
 * have been brought forward.
 */

extern STATUS cacheAimArch7IEnable (void);
extern STATUS cacheAimArch7DEnable (void);

extern STATUS cacheAimArch7IDisable (void);
extern STATUS cacheAimArch7DDisable (void);

extern STATUS cacheAimArch7IProbe (void);
extern STATUS cacheAimArch7DProbe (void);

extern BOOL   cacheAimArch7IIsOn (void);
extern BOOL   cacheAimArch7DIsOn (void);

extern STATUS cacheAimArch7TextUpdate (void * start,
                                       UINT32 count,
                                       UINT32 IcacheLineSize,
                                       UINT32 DcacheLineSize);

extern void * cacheAimArch7DmaMalloc (size_t bytes);
extern STATUS cacheAimArch7DmaFree (void * pBuf);

extern BOOL   cacheAimArch7MmuIsOn (void);

extern STATUS cacheAimArch6DInvalidate (void * start, void * end, UINT32 step);
extern STATUS cacheAimArch7DInvalidateAll (void);

extern STATUS cacheAimArch6IInvalidate (void * start, void * end, UINT32 step);
extern STATUS cacheAimArch6IInvalidateAll (void);

extern STATUS cacheAimArch6DFlush (void * start, void * end, UINT32 step);
extern STATUS cacheAimArch7DFlushAll (void);
extern STATUS cacheAimArch7DFlushPoU (void * start, void * end, UINT32 step);

extern STATUS cacheAimArch6DClear (void * start, void * end, UINT32 step);
extern STATUS cacheAimArch7DClearAll (void);

extern STATUS cacheAimArch6PipeFlush (void);

extern void cacheAimArch7IMB (void);

extern void cacheAimArch6IClearDisable (void);

extern UINT32 cacheAimArch7Identify (UINT32 level);
extern UINT32 cacheAimArch7SizeInfoGet (UINT32 level, UINT32 type);

extern STATUS cacheArchIInvalidate(void * start, void * end, UINT32 step);
extern STATUS cacheArchIInvalidateAll(void);
extern STATUS cacheArchDFlush(void * start, void * end, UINT32 step);
extern STATUS cacheArchDFlushAll(void);
extern STATUS cacheArchDInvalidate(void * start, void * end, UINT32 step);
extern STATUS cacheArchDInvalidateAll(void);
extern STATUS cacheArchDClear(void * start, void * end, UINT32 step);
extern STATUS cacheArchDClearAll (void);
extern STATUS cacheArchPipeFlush (void);

extern size_t cacheArchLocSizeGet (void);
extern size_t cacheArchLouSizeGet (void);

extern  FUNCPTR  sysCacheLibInit;
extern  UINT32   cacheArchState;

/* 
 * Core-specific function pointers for ARMv7 multilevel cache handling.
 * These must be initialized by the cacheAim<core>LibInit() routine.
 */

extern  VOIDFUNCPTR  _func_cacheAimArch7IClearDisable;
extern  VOIDFUNCPTR  _func_cacheAimArch7DClearDisable;

extern void (*_pSysL2CacheEnable)(CACHE_TYPE cacheType);
extern void (*_pSysL2CacheDisable)(CACHE_TYPE cacheType);
extern void (*_pSysL2CacheInvFunc)(CACHE_TYPE cacheType, void * start, void * end);
extern void (*_pSysL2CacheFlush)(CACHE_TYPE cacheType, void * start, void * end);
extern void (*_pSysL2CacheClear)(CACHE_TYPE cacheType, void * start, void * end);

extern void cacheArchL2CacheEnable(void);
extern void cacheArchL2CacheDisable(void);

extern BOOL cacheArchL2CacheIsOn(void);
	       
#else	/* _ASMLANGUAGE */

/* 
 * Using "#" in the middle of a complex #define generates garbage 
 * passed to the assembler which results in a syntax error.  ARM_IMM is
 * used by this file in order to tell the assembler to use an immediate
 * value.
 */

#define ARM_IMM #

#define ARM_LOC_MASK #0x7000000		/* level of coherency mask of CLIDR */

/* 
 * Common code for cache operations on entire data/unified caches,
 * performed by set/way to the point of coherency (PoC).
 * This code is based on 'Example code for cache maintenance operations'
 * provided in "ARM Architecture Reference Manual ARMv7-A and ARMv7-R edition 
 * (ARM DDI 0406)" .
 * 
 * Registers used: For ARM ISA, r0-r8, though r4-r8 are saved/restored.
 *                 For THUMB-2, r0-r9, though r4-r9 are saved/restored.
 *                 Also, note that r0 is 0 when this code completes.
 */

#if ARM_THUMB2  /* LSL is less capable in Thumb-2 */

#define _CORTEX_AR_ENTIRE_DATA_CACHE_OP(crm) \
        STMFD   sp!, {r4-r9}		/* save registers */;\
					\
	MRC	p15, 1, r0, c0, c0, 1	/* r0 = Cache Lvl ID register info */;\
	ANDS	r3, r0, ARM_LOC_MASK	/* get level of coherency (LoC) */;\
	MOV	r3, r3, LSR ARM_IMM 23	/* r3 = LoC << 1 */;\
	BEQ	5f			;\
					\
	MOV	r7, ARM_IMM 0		/* r7 = cache level << 1; start at 0 */;\
					\
1:					;\
	AND	r1, r0, ARM_IMM 0x7	/* r1 = cache type(s) for this level */;\
	CMP	r1, ARM_IMM 2		;\
	BLT	4f			/* no data cache at this level */;\
					\
	MCR	p15, 2, r7, c0, c0, 0	/* select the Cache Size ID register */;\
	ISB				/* ISB: sync change to Cache Size ID */;\
	MRC	p15, 1, r1, c0, c0, 0	/* r1 = current Cache Size ID info */;\
	AND	r2, r1, ARM_IMM 0x7	/* r2 = line length */;\
	ADD	r2, r2, ARM_IMM 4  /* add line length offset = log2(16 bytes) */;\
	LDR	r4, =0x3FF		;\
	ANDS	r4, r4, r1, LSR ARM_IMM 3 /* r4 = (# of ways - 1); way index */;\
	CLZ	r5, r4		  /* r5 = bit position of way size increment */;\
	LDR	r6, =0x00007FFF		;\
	ANDS	r6, r6, r1, LSR ARM_IMM 13/* r6 = (# of sets - 1); set index */;\
					\
2:					;\
	MOV	r1, r4			/* r1 = working copy of way number */;\
3:					;\
	LSL	r9, r1, r5		/* r8 = set/way operation data word: */;\
	ORR	r8, r7, r9		;\
	LSL	r9, r6, r2		/* cache level, way and set info */;\
	ORR	r8, r8, r9		;\
					\
	MCR	p15, 0, r8, c7, crm, 2	/* dcache operation by set/way */;\
					\
	SUBS	r1, r1, ARM_IMM 1	/* decrement the way index */;\
	BGE	3b			;\
	SUBS	r6, r6, ARM_IMM 1	/* decrement the set index */;\
	BGE	2b			;\
					\
4:					;\
	ADD	r7, r7, ARM_IMM 2	/* increment cache index = level << 1 */;\
	CMP	r3, r7			/* done when LoC is reached */;\
	MOVGT	r0, r0, LSR ARM_IMM 3	/* rt-align type of next cache level */;\
	BGT	1b			;\
					\
5:					;\
	DSB				;\
        LDMIA   sp!, {r4-r9}		/* restore registers */;

#else /* !ARM_THUMB2 */

#define _CORTEX_AR_ENTIRE_DATA_CACHE_OP(crm) \
        STMFD   sp!, {r4-r8}		/* save registers */;\
					\
	MRC	p15, 1, r0, c0, c0, 1	/* r0 = Cache Lvl ID register info */;\
	ANDS	r3, r0, ARM_LOC_MASK	/* get level of coherency (LoC) */;\
	MOV	r3, r3, LSR ARM_IMM 23	/* r3 = LoC << 1 */;\
	BEQ	5f			;\
					\
	MOV	r7, ARM_IMM 0		/* r7 = cache level << 1; start at 0 */;\
					\
1:					;\
	AND	r1, r0, ARM_IMM 0x7	/* r1 = cache type(s) for this level */;\
	CMP	r1, ARM_IMM 2		;\
	BLT	4f			/* no data cache at this level */;\
					\
	MCR	p15, 2, r7, c0, c0, 0	/* select the Cache Size ID register */;\
	ISB				/* ISB: sync change to Cache Size ID */;\
	MRC	p15, 1, r1, c0, c0, 0	/* r1 = current Cache Size ID info */;\
	AND	r2, r1, ARM_IMM 0x7	/* r2 = line length */;\
	ADD	r2, r2, ARM_IMM 4  /* add line length offset = log2(16 bytes) */;\
	LDR	r4, =0x3FF		;\
	ANDS	r4, r4, r1, LSR ARM_IMM 3 /* r4 = (# of ways - 1); way index */;\
	CLZ	r5, r4		  /* r5 = bit position of way size increment */;\
	LDR	r6, =0x00007FFF		;\
	ANDS	r6, r6, r1, LSR ARM_IMM 13/* r6 = (# of sets - 1); set index */;\
					\
2:					;\
	MOV	r1, r4			/* r1 = working copy of way number */;\
3:					;\
	ORR	r8, r7, r1, LSL r5	/* r8 = set/way operation data word: */;\
	ORR	r8, r8, r6, LSL r2	/* cache level, way and set info */;\
					\
	MCR	p15, 0, r8, c7, crm, 2	/* dcache operation by set/way */;\
					\
	SUBS	r1, r1, ARM_IMM 1	/* decrement the way index */;\
	BGE	3b			;\
	SUBS	r6, r6, ARM_IMM 1	/* decrement the set index */;\
	BGE	2b			;\
					\
4:					;\
	ADD	r7, r7, ARM_IMM 2	/* increment cache index = level << 1 */;\
	CMP	r3, r7			/* done when LoC is reached */;\
	MOVGT	r0, r0, LSR ARM_IMM 3	/* rt-align type of next cache level */;\
	BGT	1b			;\
					\
5:					;\
	DSB				;\
        LDMIA   sp!, {r4-r8}		/* restore registers */;

#endif /*ARM_THUMB2*/


#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif	/* __INCcacheArmArch7h */

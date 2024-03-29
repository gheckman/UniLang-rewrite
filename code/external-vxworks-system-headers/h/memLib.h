/* memLib.h - memory management library header file */

/* 
 * Copyright (c) 1984-2005, 2009-2010 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
01i,05aug10,cww  Updated memFindMax/memPartFindMax return type
01h,29apr10,pad  Moved extern C statement after include statements.
01g,12nov09,pcs  Add prototypes for the kernel Proximity heap API's.
01f,24mar09,pcs  Updated to add support for the LP64 data model.
01e,16jun06,zl   moved library init functions to private header.
01d,26sep05,zl   added ED&R error handling flags (SPR#112822).
01c,05may04,zl   changed memAddToPool(), memOptionsSet()/Get() to return status.
03u,27jun03,tam  switch to VxWorks AE heap allocator: added a few errno, added
		 'maxBytesAlloc' to MEM_PART_STATS struct, added
		 memPartOptionsGet(), memPartInit() returns STATUS instead of
		 void.
03t,14mar03,dcc  moved PART_ID definition to types/vxWind.h
03s,19aug96,dbt  added memPartAlignedAlloc prototype (fixed SPR #6898).
03r,30oct94,kdl  merge cleanup - removed extra "#ifndef _ASMLANGUAGE".
03o,15oct93,cd   added #ifndef _ASMLANGUAGE.
03q,27oct94,ism  Fixed assembly problem from merge
03p,01dec93,jag  added struct MEM_PART_STATS and function memPartInfoGet.
03o,02apr93,edm  ifdef'd out non-ASMLANGUAGE portions
03n,05feb93,smb  added include of vxWorks.h
03m,22sep92,rrr  added support for c++
03l,19jul92,pme  added external declarations for sm partition functions.
03k,13jul92,rdc  added prototype for valloc.
03j,04jul92,jcf  cleaned up.
03i,22jun92,rdc  added memalign and memPartAlignedAlloc.
03h,26may92,rrr  the tree shuffle
03g,25mar92,jmm  added new options for error handling
03f,04oct91,rrr  passed through the ansification filter
		  -fixed #else and #endif
		  -changed VOID to void
		  -changed copyright notice
03e,10jun91.del  added pragma for gnu960 alignment.
03d,05oct90,dnw  deleted private routines.
03c,05oct90,shl  added ANSI function prototypes.
                 made #endif ANSI style.
                 added copyright notice.
03b,10aug90,dnw  added declaration of memPartInit().
03a,18jul90,jcf  made partitions objects.
		 changed malloc(),realloc(),calloc() etc to return void *.
02c,17mar90,jcf  added structure type definition.
02b,28jun89,llk  added declaration for free();
02a,11jun88,dnw  changed for rev 03a of memLib.
01l,28mar88,gae  added function decl. of calloc().
01j,13nov87,gae  removed FRAGMENT definition; made function decl.'s IMPORTs.
01h,23oct87,rdc  added PARTITION defenitions.
01g,24dec86,gae  changed stsLib.h to vwModNum.h.
01f,21may86,rdc	 added forward declarations for malloc and realloc.
		 added FRAGMENT structure.
01e,13aug84,ecs  changed S_memLib_NO_MORE_MEMORY to S_memLib_NOT_ENOUGH_MEMORY.
01d,07aug84,ecs  added include of stsLib.h, and status codes.
01c,15jun84,dnw  removed declaration of memEnd (no longer exists).
01b,27jan84,ecs  added inclusion test.
01a,24may83,dnw  written
*/

#ifndef __INCmemLibh
#define __INCmemLibh

#include <vxWorks.h>
#include <vwModNum.h>

#ifdef __cplusplus
extern "C" {
#endif

/* status codes */

#define S_memLib_NOT_ENOUGH_MEMORY		(M_memLib | 1)
#define S_memLib_INVALID_NBYTES			(M_memLib | 2)
#define S_memLib_BLOCK_ERROR			(M_memLib | 3)
#define S_memLib_NO_PARTITION_DESTROY		(M_memLib | 4)
#define S_memLib_PAGE_SIZE_UNAVAILABLE		(M_memLib | 5)
#define S_memLib_WRONG_PART_ID			(M_memLib | 6)
#define S_memLib_INVALID_ADDRESS		(M_memLib | 7)
#define S_memLib_INVALID_ALIGNMENT		(M_memLib | 8)
#define S_memLib_FUNC_NOT_AVAILABLE		(M_memLib | 9)

/* types */

#ifndef _ASMLANGUAGE

/* Partition statistics structure */

typedef struct
    {
    unsigned long numBytesFree,	   /* Number of Free Bytes in Partition       */
		  numBlocksFree,   /* Number of Free Blocks in Partition      */
		  maxBlockSizeFree,/* Maximum block size that is free.	      */
		  numBytesAlloc,   /* Number of Allocated Bytes in Partition  */
		  numBlocksAlloc,  /* Number of Allocated Blocks in Partition */
		  maxBytesAlloc;   /* Maximum number of Allocated Bytes at any*/
		  		   /* time */

    }  MEM_PART_STATS;
#endif /* ~ _ASMLANGUAGE */

/* partition options */

/* optional check for bad blocks */

#define MEM_BLOCK_CHECK			0x10

/* response to errors when allocating memory */

#define MEM_ALLOC_ERROR_EDR_WARN_FLAG	0x200
#define MEM_ALLOC_ERROR_EDR_FATAL_FLAG	0x400
#define MEM_ALLOC_ERROR_LOG_FLAG	0x20
#define MEM_ALLOC_ERROR_SUSPEND_FLAG	0x40	/* deprecated */

/* response to errors when freeing memory */

#define MEM_BLOCK_ERROR_EDR_WARN_FLAG	0x800
#define MEM_BLOCK_ERROR_EDR_FATAL_FLAG	0x1000
#define MEM_BLOCK_ERROR_LOG_FLAG	0x80
#define MEM_BLOCK_ERROR_SUSPEND_FLAG	0x100	/* deprecated */

/* old style allocation errors - block too big, insufficient space */

#define MEM_ALLOC_ERROR_MASK		0x03	/* deprecated */
#define MEM_ALLOC_ERROR_RETURN		0	/* deprecated */
#define MEM_ALLOC_ERROR_LOG_MSG		0x01	/* deprecated */
#define MEM_ALLOC_ERROR_LOG_AND_SUSPEND	0x02	/* deprecated */

/* old style bad block found */

#define MEM_BLOCK_ERROR_MASK		0x0c	/* deprecated */
#define MEM_BLOCK_ERROR_RETURN		0	/* deprecated */
#define MEM_BLOCK_ERROR_LOG_MSG		0x04	/* deprecated */
#define MEM_BLOCK_ERROR_LOG_AND_SUSPEND	0x08	/* deprecated */

#ifndef _ASMLANGUAGE

/* variable declarations */

/* system partition */

extern PART_ID memSysPartId;

/* shared memory manager function pointers */

extern FUNCPTR  smMemPartOptionsSetRtn;
extern FUNCPTR  smMemPartFindMaxRtn;
extern FUNCPTR  smMemPartReallocRtn;
extern FUNCPTR  smMemPartShowRtn;

/* function declarations */

extern PART_ID 	memPartCreate		(char * pPool, size_t poolSize);
extern STATUS	memPartDelete		(PART_ID partId);
extern STATUS 	memPartInit		(PART_ID partId, char * pPool,
					 size_t poolSize);
extern STATUS 	memPartAddToPool	(PART_ID partId, char * pPool,
					 size_t poolSize);
extern STATUS	memAddToPool		(char * pPool, size_t poolSize);
extern void *	memPartAlloc		(PART_ID partId, size_t nBytes);
extern void *   memPartAlignedAlloc	(PART_ID partId, size_t nBytes,
					 size_t alignment);
extern void *	memalign		(size_t alignment, size_t size);
extern void *   valloc			(size_t size);
extern STATUS 	memPartFree		(PART_ID partId, char * pBlock);
extern STATUS 	memPartOptionsSet	(PART_ID partId, unsigned options);
extern STATUS   memPartOptionsGet	(PART_ID partId, UINT * pOptions);
extern ssize_t 	memFindMax		(void);
extern ssize_t 	memPartFindMax		(PART_ID partId);
extern void *	memPartRealloc		(PART_ID partId, char * pBlock,
					 size_t nBytes);
extern STATUS	memOptionsGet		(UINT * pOptions);
extern STATUS	memOptionsSet		(unsigned options);
extern STATUS 	cfree			(char * pBlock);
extern void 	memShowInit		(void);
extern STATUS	memShow			(int type);
extern STATUS 	memPartShow		(PART_ID partId, int type);
extern STATUS   memPartInfoGet		(PART_ID partId,
					 MEM_PART_STATS * ppartStats);
extern STATUS   memInfoGet		(MEM_PART_STATS * ppartStats);

#ifdef _WRS_CONFIG_LP64
extern void *	kProxHeapAlloc		(size_t size);
extern STATUS 	kProxHeapFree		(void * ptr);
extern void *	kProxHeapAlignedAlloc	(size_t size, size_t alignment);
extern void *	kProxHeapRealloc	(void * pNewBlock, size_t newSize);
#endif

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCmemLibh */

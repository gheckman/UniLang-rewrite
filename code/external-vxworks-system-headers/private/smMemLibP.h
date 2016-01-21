/* smMemLibP.h - private shared memory management library header file */

/* Copyright 1984-2002, 2010 Wind River Systems, Inc. */

/*
modification history
--------------------
01j,15sep10,swg  remove VxMP APIs for these APIs will be published(WIND00145226)
01i,29apr10,pad  Moved extern C statement after include statements.
01h,05may02,mas  added volatile pointers (SPR 68334)
01g,29jan93,pme  added little endian support
		 changed SM_BLOCK_HDR structure to avoid bit field use.
01f,29sep92,pme  added smMemPartShow prototype 
01e,22sep92,rrr  added support for c++
01d,14sep92,smb  removed the prototype for smMemPartShow()
01c,28jul92,pme  added align pragma for I960.
01b,21jul92,pme  removed MEM_ROUND_UP and  MEM_IS_ROUND.
01a,19jul92,pme  extracted from smMemLib v1b.
*/

#ifndef __INCsmMemLibPh
#define __INCsmMemLibPh

#include "vwModNum.h"
#include "smMemLib.h"
#include "smDllLib.h"
#include "private/semSmLibP.h"

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#define MEM_PART_TYPE_SM_STD	20	/* standard shared memory partition */

#if (defined (CPU_FAMILY) && (CPU_FAMILY==I960) && (defined __GNUC__))
#pragma align 1                 /* tell gcc960 not to optimize alignments */
#endif  /* CPU_FAMILY==I960 */

/* typedefs */

typedef struct sm_obj_partition
    {
    UINT32       verify;              	/* partition is initialized */
    UINT32       objType;              	/* partition type */

    SM_DL_LIST   freeList;              /* list of free blocks */
    SM_SEMAPHORE sem;                   /* partition semaphore */
    unsigned     totalWords;            /* total number of words in pool */
    unsigned     minBlockWords;         /* min blk size in words includes hdr */
    unsigned     options;               /* options */

    /* allocation statistics */

    unsigned curBlocksAllocated;        /* current # of blocks allocated */
    unsigned curWordsAllocated;         /* current # of words allocated */
    unsigned cumBlocksAllocated;        /* cumulative # of blocks allocated */
    unsigned cumWordsAllocated;         /* cumulative # of words allocated */

    } SM_PARTITION;

typedef struct sm_block_hdr     /* SM_BLOCK_HDR */
    {
    struct sm_block_hdr * pPrevHdr; 	/* pointer to previous block hdr */
    unsigned              nWords;	/* size in words of this block */
    unsigned              free;		/* TRUE = this block is free */
    UINT32		  pad;		/* 4 byte pad for round up */
    } SM_BLOCK_HDR;

/* SM_FREE_BLOCK is the structure for a free block.  It includes the freelist
 * node in addition to the usual header. */

typedef struct sm_free_block    /* SM_FREE_BLOCK */
    {
    SM_BLOCK_HDR 	hdr;	/* normal block header */
    SM_DL_NODE 		node;	/* freelist links */
    UINT32              pad;	/* 4 byte pad for round up */
    } SM_FREE_BLOCK;

/* defines */

/* macros for getting to next and previous blocks */

#define SM_NEXT_HDR(pHdr) \
    ((SM_BLOCK_HDR *) ((char *) (pHdr) + (2 * ntohl ((int) ((pHdr)->nWords)))))
#define SM_PREV_HDR(pHdr) \
    ((SM_BLOCK_HDR *) (GLOB_TO_LOC_ADRS (ntohl ((int) ((pHdr)->pPrevHdr)))))

/* macros for converting between the "block" that caller knows
 * (actual available data area) and the block header in front of it */

#define SM_HDR_TO_BLOCK(pHdr)   ((char *) ((int) pHdr + sizeof (SM_BLOCK_HDR)))
#define SM_BLOCK_TO_HDR(pBlock) ((SM_BLOCK_HDR *) ((int) pBlock - \
                                                sizeof(SM_BLOCK_HDR)))

/* macros for converting between the "node" that is strung on the freelist
 * and the block header in front of it */

#define SM_HDR_TO_NODE(pHdr)    (& ((SM_FREE_BLOCK *) pHdr)->node)
#define SM_NODE_TO_HDR(pNode)   ((SM_BLOCK_HDR *) ((int) pNode - \
                                                OFFSET (SM_FREE_BLOCK, node)))

#if defined(__STDC__) || defined(__cplusplus)

extern void   smMemPartLibInit (void);
extern void   smMemPartInit (SM_PART_ID partId, char * pPool,
                             unsigned poolSize);
extern STATUS smMemPartAccessGet (SM_PART_ID partId);
extern STATUS smMemPartAccessRelease (SM_PART_ID partId);
extern BOOL   smMemPartBlockIsValid (SM_PART_ID volatile partId,
                                     SM_BLOCK_HDR volatile * pHdr,
                                     BOOL isFree);

#else   /* __STDC__ */

extern void   smMemPartLibInit ();
extern STATUS smMemPartAccessGet ();
extern STATUS smMemPartAccessRelease ();
extern BOOL   smMemPartBlockIsValid ();

#endif  /* __STDC__ */

#if (defined (CPU_FAMILY) && (CPU_FAMILY==I960) && (defined __GNUC__))
#pragma align 0                 /* turn off alignment requirement */
#endif  /* CPU_FAMILY==I960 */

#ifdef __cplusplus
}
#endif

#endif /* __INCsmMemLibPh */

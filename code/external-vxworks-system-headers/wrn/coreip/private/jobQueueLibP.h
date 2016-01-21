/* jobQueueLibP.h - private header file for jobQueueLib */

/*
 * Copyright (c) 2005, 2007-2008 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01h,15jun12,xhs  WIND00137567 - Network job queues can stall if a posting 
                 task is deleted at just the wrong time
01g,30jul09,dlk  WIND00168645 - use deterministic spin locks by default.
01f,18jun08,jpb  Renamed _WRS_VX_SMP to _WRS_CONFIG_SMP.  Added include path
                 for kernel configurations options set in vsb.
01e,16jan08,dlk  Rename spinLockFastLib --> spinlockIsrNdLib.
01d,10dec07,dlk  Use fast spin locks.
01c,20feb07,kch  Merged from base6_iter12_smp-dev - Use spinlocks instead of
                 intLock.
01b,13jul05,dlk  Added taskId member to JOB_QUEUE.
01a,06may05,dlk  Written.
*/

/* Note, jobQueueLib.h should be included before this private header */

#ifndef __INCjobQueueLibPh
#define __INCjobQueueLibPh

#include <vsbConfig.h>

#include <semLib.h>
#include <private/semLibP.h>
#include <setjmp.h>
#include <intLib.h>

#ifdef _WRS_CONFIG_SMP
#ifdef _WRS_CONFIG_DETERMINISTIC
#include <spinLockLib.h>

#define JOBQ_LOCK(x, key)					\
    do { (void)(key); SPIN_LOCK_ISR_TAKE (x); } while ((0))
#define JOBQ_UNLOCK(x, key) \
    do { SPIN_LOCK_ISR_GIVE (x); (void)(key); } while ((0))
#define JOBQ_LOCK_INIT(x) \
    do { SPIN_LOCK_ISR_INIT (x, 0); } while ((0))
#else
#include <spinlockIsrNdLib.h>

#define JOBQ_LOCK(x, key)				\
    do { key = spinLockIsrNdTake (x); } while ((0))
#define JOBQ_UNLOCK(x, key) \
    do { spinLockIsrNdGive ((x), (key)); } while ((0))
#define JOBQ_LOCK_INIT(x) \
    do { spinLockIsrNdInit (x); } while ((0))
#endif /* _WRS_CONFIG_DETERMINISTIC */

#else /* Uniprocessor */

#define JOBQ_LOCK(x, key)			\
    do { key = INT_CPU_LOCK( ); } while ((0))
#define JOBQ_UNLOCK(x, key) \
    do { INT_CPU_UNLOCK(key); } while ((0))
#define JOBQ_LOCK_INIT(x) do { } while ((0))

#endif /* _WRS_CONFIG_SMP */

#ifdef __cplusplus
extern "C" {
#endif

#define QJOB_ENQUEUED	0x100
#define QJOB_POOL_ALLOC 0x200

typedef struct _QJOB_QUEUE_HEAD
    {
    QJOB * pHead;
    QJOB ** ppTail;
    } QJOB_QUEUE_HEAD;

typedef struct _QJOB_FREE_HEAD
    {
    QJOB_STANDARD * pHead;
    } QJOB_FREE_HEAD;

typedef QJOB_FREE_HEAD QJOB_BLOCK_HEAD; /* [;^] */

typedef struct _QJOB_STD_POOL
    {
    QJOB_FREE_HEAD  free;		/* The free list of standard jobs */
    QJOB_BLOCK_HEAD blocks;		/* The list of blocks of std. jobs */
#ifdef _WRS_CONFIG_SMP
#ifdef _WRS_CONFIG_DETERMINISTIC
    spinlockIsr_t *   qLock;
#else
    spinlockIsrNd_t * qLock;
#endif
#endif
    UINT32 refCount;			/* How many attached job queues? */
    } QJOB_STD_POOL;

typedef struct _QUIT_QJOB
    {
    QJOB job;
    volatile int * pQuitValue;
    jmp_buf * pJmpBuf;
    VOIDFUNCPTR qFunc;
    void * arg1;
    void * arg2;
    } QUIT_QJOB;

typedef struct _JOB_QUEUE
    {
    QJOB_QUEUE_HEAD	jobs [32];	/* The enqueued jobs */
    UINT32		activePri;	/* which queues hold jobs? */
#ifdef JOBQ_PRI_MASKABLE
    UINT32		priMask;	/* which priorities are enabled? */
#endif
    QJOB_STD_POOL *	pStdPool;	/* pool for standard jobs */
    SEMAPHORE		sem;		/* binary semaphore */
    QJOB_BLOCK_HEAD	blocks;		/* list of blocks of standard jobs */
    UINT32		flags;		/* Is queue in use? */
#define JOBQ_FLG_RUNNING	0x1
#define JOBQ_FLG_CREATED	0x2
#define JOBQ_FLG_AWAKE		0x4
    TASK_ID		taskId;		/* Task currently running */
					/* jobQueueProcess(). */

    QUIT_QJOB		quitJob;
    void *		userVal;	/* reserved for queue creator */
#ifdef _WRS_CONFIG_SMP
#ifdef _WRS_CONFIG_DETERMINISTIC
    spinlockIsr_t	qLock;
#else
    spinlockIsrNd_t	qLock;
#endif
#endif
    } JOB_QUEUE;

#define QUIT_JOB_TO_JOB_QUEUE(q) \
    ((JOB_QUEUE *)((char *)(q) - offsetof (JOB_QUEUE, quitJob)))

#ifdef __cplusplus
}
#endif

#endif /* __INCjobQueueLibPh */

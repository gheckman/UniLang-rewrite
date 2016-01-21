/* dshmRwLock.h - DSHM multiple-Readers one-Writer Locks */

/*
 * Copyright (c) 2006-2007, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01i,15jul10,gjj  deprecated the DSHM technology and added deprecation macros.
01h,29apr10,pad  Moved extern C statement after include statements.
01g,24aug07,bwa  changed DSHM_ATOMIC_SET/CLEAR to DSHM_TAS/CLEAR
01f,21jun07,bwa  changed RMW to ATOMIC_SET and _CLEAR
01e,24feb07,bwa  added local descriptor for storage of local info;
		 removed keeping track of reader nodes, left only reader count.
01d,31jan07,bwa  modified locking policy.
01c,22jan07,bwa  added reader death detection.
01b,21dec06,bwa  standards update.
01a,05jul06,bwa  written.
*/

#ifndef __INCdshmRwLockh
#define __INCdshmRwLockh

#include <dshm/dshm.h>
#include <dshm/util/dshmSpinLock.h>

#ifdef __cplusplus
extern "C" {
#endif

/* The RW lock object in shared memory.
 * (HBO = host byte-order, NBO = network byte-order)
 * The threshold to hit before breaking a read-lock can be stored in host
 * byte-order because it is always accessed from the same node, the one that
 * creates the lock.
 */
typedef struct _dshmRwLockSm
    {
    DSHM_SPINLOCK spinlock;	/* protection for the data structure */
    uint16_t wLock;		/* write lock: taken or not (NBO) */
    volatile uint16_t nReaders;	/* current number of readers (NBO) */
    } DSHM_RW_LOCK_SM;

/* The RW lock descriptor in local memory.
 */
typedef struct _dshmRwLock
    {
    DSHM_RW_LOCK_SM *pSm;	/* pointer to the real lock in SM */
    DSHM_TAS tas;               /* test-and-set on shared memory */
    DSHM_TAS_CLEAR clear;       /* test-and-set clear on SM */
    int nSpinLockRetries;	/* number of tries to retry taking a spinlock */
    uint16_t thWriteTries;	/* threshold before breaking the lock (HBO) */
    uint16_t nLocalReaders;	/* number of local threads reading */
    } DSHM_RW_LOCK;

#define DSHM_RWLOCK_SPINLOCK_RETRIES_DEFAULT	256

#define DSHM_RWLOCK_WLOCK_TAKEN 0xffff

void dshmRwLockLibInit (void) 
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
STATUS dshmRwLockSmInit (DSHM_RW_LOCK_SM * const pLockSm) 
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
DSHM_RW_LOCK* dshmRwLockCreate (DSHM_RW_LOCK_SM *pLockSm,
                                const DSHM_TAS tas,
                                const DSHM_TAS_CLEAR clear,
			        const uint16_t thWriteTries) 
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
STATUS dshmRwLockInit (DSHM_RW_LOCK *pLock,
                        DSHM_RW_LOCK_SM *pLockSm,
                        const DSHM_TAS tas,
                        const DSHM_TAS_CLEAR clear,
                        const uint16_t thWriteTries) 
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
int dshmRwLockWTake (DSHM_RW_LOCK * const pLock) 
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
STATUS dshmRwLockRTake (DSHM_RW_LOCK * const pLock) 
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
STATUS dshmRwLockWGive (DSHM_RW_LOCK * const pLock) 
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
STATUS dshmRwLockRGive (DSHM_RW_LOCK * const pLock) 
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");

#ifdef __cplusplus
}
#endif

#endif /* __INCdshmRwLockh */


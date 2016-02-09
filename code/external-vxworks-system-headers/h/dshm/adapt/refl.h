/* refl.h - local one-modifier/several-user lock */

/*
 * Copyright (c) 2007~2008, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01f,29apr10,pad  Moved extern C statement after include statements.
01e,05sep08,cwu  add static declaration for DSHM_INLINE related function
01d,05sep07,bwa  changed intLockKey into a stack variable (103613)
01c,17jun07,bwa  updated following code review.
01b,03apr07,bwa  added comments.
01a,15mar07,bwa  written.
*/

/* This module implements a read-write lock (use-modify) with a reference
 * count, used for local data structures. It is primarily used to protect
 * service data structures and driver data structures that are mostly accessed
 * in read mode.
 * 
 * This type of lock should be used sparingly, since the data structure is
 * relatively heavy, using two semaphores.
 */

#ifndef __INCdshmReflh
#define __INCdshmReflh

#include <dshm/dshm.h>
#include <private/semLibP.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct __REF_LOCK
    {
    int nReaders;       /* number of read takes */
    BOOL isWriter;      /* modifier wants or has the lock */
    SEMAPHORE wlock;    /* writer signal */
    SEMAPHORE rlock;    /* reader signal */
    } _REF_LOCK;

/*******************************************************************************
*
* reflInit - initialize a reference count lock
*
* RETURNS: N/A
*/

static DSHM_INLINE void reflInit (_REF_LOCK *pLock)
    {
    pLock->nReaders = 0;
    pLock->isWriter = FALSE;
    (void)semBInit (&pLock->rlock, SEM_Q_FIFO, SEM_EMPTY);
    (void)semBInit (&pLock->wlock, SEM_Q_FIFO, SEM_EMPTY);
    }
    
/*******************************************************************************
*
* reflUseTake - obtain a reference count lock in 'use' mode
* 
* This routine tries to obtain the lock in 'use' mode. It can block the current
* thread of control if the lock is currently taken in 'modify' mode. After
* being unblocked, the thread will retry taking the lock.
*
* RETURNS: TRUE, always
*/

static DSHM_INLINE BOOL reflUseTake (_REF_LOCK *pLock)
    {
    FOREVER
        {
        int intLockKey = DSHM_INTLOCK ();
        if (!pLock->isWriter)
	    {
	    ++pLock->nReaders;
	    DSHM_INTUNLOCK (intLockKey);
	    return TRUE;
	    }
        else
	    {
	    DSHM_INTUNLOCK (intLockKey);
	    semTake (&pLock->rlock, WAIT_FOREVER);
	    }
        }
    }

/*******************************************************************************
*
* reflUseGive - give a lock that was previously taken in 'use' mode.
* 
* This routine gives a lock taken in 'use' mode. Care must be taken to only
* call this routine if the lock had previously been acquired in 'use' mode,
* since no verification is done. If this is not observed, the lock will end up
* in an incorrect state, will most probably cause deadlocks.
*
* RETURNS: N/A
*/

static DSHM_INLINE void reflUseGive (_REF_LOCK *pLock)
    {
    int intLockKey = DSHM_INTLOCK ();
    if (--pLock->nReaders == 0)
	{
	if (pLock->isWriter)
	    {
	    DSHM_INTUNLOCK (intLockKey);
	    semGive (&pLock->wlock);
	    return;
	    }
	}
    DSHM_INTUNLOCK (intLockKey);
    }

/*******************************************************************************
*
* reflModTake - obtain a lock in 'modify' mode
* 
* This routine tries to obtain the lock in 'modify' mode. If the lock is
* currently held in this mode, the operation will fail. If the lock is
* held in 'use' mode, the thread will block until the lock is released by all
* threads owning it.
* 
* When a thread tries to obtain the lock in 'modify' mode, all further attempts
* to take it in 'use' mode will block until the lock is acquired and released
* in 'modify' mode.
* 
* RETURNS: TRUE on success, FALSE on failure.
*/

static DSHM_INLINE BOOL reflModTake (_REF_LOCK *pLock)
    {
    int intLockKey = DSHM_INTLOCK ();
    /* someone is already making changes */
    if (pLock->isWriter)
	{
	DSHM_INTUNLOCK (intLockKey);
	return FALSE;
	}
    pLock->isWriter = TRUE;
    if (pLock->nReaders)
	{
	DSHM_INTUNLOCK(intLockKey);
	semTake (&pLock->wlock, WAIT_FOREVER);
	return TRUE;
	}
    DSHM_INTUNLOCK(intLockKey);
    return TRUE;
    }

/*******************************************************************************
*
* reflDemote - turn a lock held in 'modify' mode to a lock held in 'use' mode
* 
* This routine demotes a 'modify' lock to a 'use' lock. If threads are waiting
* to acquire it in 'use' mode, they will awaken.
* 
* Care must be taken to only
* call this routine if the lock had previously been acquired in 'modify' mode,
* since no verification is done. If this is not observed, the lock will end up
* in an incorrect state, will most probably cause deadlocks.
*
* RETURNS: N/A
*/

static DSHM_INLINE void reflDemote (_REF_LOCK *pLock)
    {
    int intLockKey = DSHM_INTLOCK ();
    pLock->isWriter = FALSE;
    pLock->nReaders = 1;
    DSHM_INTUNLOCK (intLockKey);
    semFlush (&pLock->rlock);
    }

/*******************************************************************************
*
* reflModGive - release a lock that was held in 'modify' mode
* 
* Give a lock held in 'modify' mode. Threads waiting to acquire the lock in
* 'use' mode will be unblocked and will obtain the lock.
* 
* Care must be taken to only
* call this routine if the lock had previously been acquired in 'modify' mode,
* since no verification is done. If this is not observed, the lock will end up
* in an incorrect state, will most probably cause deadlocks.
*
* RETURNS: N/A
*/

static DSHM_INLINE void reflModGive (_REF_LOCK *pLock)
    {
    int intLockKey = DSHM_INTLOCK ();
    pLock->isWriter = FALSE;
    DSHM_INTUNLOCK(intLockKey);
    semFlush (&pLock->rlock);
    }

#ifdef __cplusplus
}
#endif

#endif /* __INCdshmReflh */

/* test cases */
#if 0
void __helper (_REF_LOCK *pLock)
    {
    printf ("__helper spawned\n");
    if (reflModTake (pLock))
	{
	printf ("__helper: got lock\n");
	}
    else
	{
	printf ("error helper 1\n");
	return;
	}
    
    if (!reflModTake (pLock))
	{
	printf ("__helper: failed taking lock twice, GOOD\n");
	}
    else
	{
	printf ("error helper 2\n");
	return;
	}
    
    printf ("__helper: releasing\n");
    reflModGive (pLock);
    printf ("__helper: released\n");
    
    printf ("__helper: done\n");
    }
	
void __test (void)
    {
    _REF_LOCK lock;
    reflInit (&lock);
    
    if (reflUseTake (&lock))
	printf ("got ref lock once\n");
    else
	{
	printf ("error 1\n");
	return;
	}
    
    if (reflUseTake (&lock))
	printf ("got ref lock twice\n");
    else
	{
	printf ("error 2\n");
	return;
	}
    
    if (reflUseTake (&lock))
	printf ("got ref lock thrice\n");
    else
	{
	printf ("error 3\n");
	return;
	}
    
    reflUseGive (&lock);
    printf ("gave ref lock once\n");
    
    reflUseGive (&lock);
    printf ("gave ref lock twice\n");
    
    {
    int prio;
    taskPriorityGet (taskIdSelf(), &prio);
    printf ("spawning task @ priority %d\n", prio);
    if (ERROR == taskSpawn (NULL, prio-1, 0, 20000, (FUNCPTR)__helper, (int)&lock, 0,0,0,0,0,0,0,0,0))
	{
	printf ("can't spawn task\n");
	taskSuspend (taskIdSelf());
	}
    printf ("spawned helper\n");
    }
    
    reflUseGive (&lock);
    printf ("gave ref lock thrice\n");
    
    if (reflUseTake (&lock))
	printf ("got ref final lock\n");
    else
	{
	printf ("error 7\n");
	return;
	}
    
    reflUseGive (&lock);
    printf ("gave ref final lock\n");
    }
#endif


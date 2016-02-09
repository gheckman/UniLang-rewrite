/* multios_adapt.h - MULTIOS adaptation header file for VxWorks */

/*
 * Copyright (c) 2008-2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
02g,29dec11,swg  Add the macro MULTIOS_CURR_TIME(). (WIND00261229)
02f,05dec11,zhw  Modify the bcopy calling to match its prototype (WIND00304594)
02e,18feb11,ebh  Update with changes from VBE project
02d,05jan11,wyl  Ensure timer delay is a minimum of 1 tick (WIND00246398)
02c,04jan11,ste  Add MIPC_SM_ADAPT_CHECK_TIMER
02b,26aug10,jlk  Make sure #ifdef __cplusplus starts after #includes
02a,02jul10,h_w  Add MULTIOS_SEM_TERM definition
01z,22apr10,als  Terminate semaphores when socket is closed (WIND00201777)
01y,02mar10,als  Add support for 64-bit memory addressing
01x,30sep09,als  Specify return type for timer start API
01w,15sep09,bwa  add and use multios task delay
01v,07aug09,ebh  Code inspection updates
01u,05aug09,als  Introduce MULTIOS_ADDR type
01t,30jun09,als  Hide unused spinlock APIs
01s,23jun09,als  Fix issues with handling of timers
01r,19jun09,ebh  Change MULTIOS_COPY_FROM/TO_USR to return success or fail
01q,03jun09,als  Rework system configuration/initialization as per HLD and CI
01p,26may09,ebh  Code Inspection Modifications
01o,12may09,ebh  Allow WAIT_FOREVER to work with SEM_DOWN_WITH_TIMEOUT
01n,05may09,h_W  Remove including vxAtomicLib.h
01m,28apr09,ebh  Remove unused macros
01l,22apr09,ebh  Add prototype for semaphores
01k,21apr09,ebh  Add in MULTIOS_TIMER_ARG type
01j,19mar09,ebh  Use VxWorks AMP Atomic operators instead of arch specific
                 ones
01i,13mar09,ebh  Update MULTIOS_SEM_DOWN_WITH_TIMEOUT and add general comments
01h,15dec08,apa  MIPC 2.0 changes
01g,26sep08,ebh  changes as per code review
01f,02sep08,apa  Rename the byte order conversion macros.
01e,20jun08,jlk  Added MULTIOS_SEM_CINIT macro.
01e,05may08,apa  Adding counting semaphores.
01d,02may08,jlk  added copy to/from usr macros
01c,30mar08,bwa  added description.
01b,24mar08,bwa  added SEMAPHORE, fixed MUTEX_UP()
01a,22feb08,bwa  written, forked from dshm/adapt/types.h:01k.
*/

/*
DESCRIPTION

VxWorks adaptation main header file. Contains VxWorks definitions of multiple
types of OS-specific objects, such as semaphores, mutexes and spinlocks and
APIs such as 'round up' and ntoh.
The definitions in this file are to allow users to operate on, and port to,
different OSs.  Some items are for inter-OS compatibility while others are
strictly for portability of code.
*/

#ifndef __INC_multios_adapt_h
#define __INC_multios_adapt_h

#include <vxWorks.h>
#include <assert.h>
#include <errnoLib.h>
#include <ffsLib.h>
#include <intLib.h>
#include <logLib.h>
#include <semLib.h>
#include <spinLockLib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysLib.h>
#include <taskLib.h>
#include <tickLib.h>
#include <wdLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* miscellaneous adaptation */

#define MULTIOS_INLINE			__inline__

#define MULTIOS_ROUND_UP(ptr, align)	ROUND_UP(ptr, align)
#define MULTIOS_STRUCT_MEMBER_OFFSET(s,m)  OFFSET(s, m)

/* assertion */

#define MULTIOS_ASSERT			assert

/* console output */

#define MULTIOS_PRINT			printf
#define MULTIOS_IPRINT			logMsg  /* interrupt-safe printout */

/* memory manipulation */

#define MULTIOS_CACHE_ALIGN		_CACHE_ALIGN_SIZE

#define MULTIOS_MEM_BARRIER()		VX_MEM_BARRIER_RW()

#define MULTIOS_KALLOC(size)		malloc(size)
#define MULTIOS_KFREE(ptr)		free(ptr)

#define MULTIOS_MSB(value)		(ffsMsb((UINT32)value) - 1)
#define MULTIOS_LSB(value)		(ffsLsb((UINT32)value) - 1)

/* Copy to user space - return number of uncopied bytes, 0 on success */
static MULTIOS_INLINE int MULTIOS_COPY_TO_USR(void *dst, const void *src,
				       unsigned long sz)
{
	bcopy ((const char *)src, (char *)dst, (size_t)sz);
	return 0;
}

/* Copy from user space - return number of uncopied bytes, 0 on success */
static MULTIOS_INLINE int MULTIOS_COPY_FROM_USR(void *dst, const void *src,
					 unsigned long sz)
{
	bcopy ((const char *)src, (char *)dst, (size_t)sz);
	return 0;
}

/* multi-OS atomic operators */

typedef uint32_t	MULTIOS_ATOMIC_VAL;
typedef atomic32_t	MULTIOS_ATOMIC;

/*
 * The following routines are simple wrappers that utilize the standard VxWorks
 * kernel 32-bit atomic operators.  They are only needed because the multi-os
 * operators deal with unsigned values, rather than signed values.
 */

static MULTIOS_INLINE MULTIOS_ATOMIC_VAL MULTIOS_ATOMIC_GET(MULTIOS_ATOMIC *a)
{
	return (MULTIOS_ATOMIC_VAL)atomic32Get(a);
}

static MULTIOS_INLINE MULTIOS_ATOMIC_VAL MULTIOS_ATOMIC_SET(MULTIOS_ATOMIC *a,
							    MULTIOS_ATOMIC_VAL v)
{
	return (MULTIOS_ATOMIC_VAL)atomic32Set(a, (atomic32Val_t)v);
}

static MULTIOS_INLINE MULTIOS_ATOMIC_VAL MULTIOS_ATOMIC_ADD(MULTIOS_ATOMIC *a,
							    MULTIOS_ATOMIC_VAL v)
{
	return (MULTIOS_ATOMIC_VAL)atomic32Add(a, (atomic32Val_t)v);
}

static MULTIOS_INLINE MULTIOS_ATOMIC_VAL MULTIOS_ATOMIC_SUB(MULTIOS_ATOMIC *a,
							    MULTIOS_ATOMIC_VAL v)
{
	return (MULTIOS_ATOMIC_VAL)atomic32Sub(a, (atomic32Val_t)v);
}

static MULTIOS_INLINE MULTIOS_ATOMIC_VAL MULTIOS_ATOMIC_INC(MULTIOS_ATOMIC *a)
{
	return (MULTIOS_ATOMIC_VAL)atomic32Inc(a);
}

static MULTIOS_INLINE MULTIOS_ATOMIC_VAL MULTIOS_ATOMIC_DEC(MULTIOS_ATOMIC *a)
{
	return (MULTIOS_ATOMIC_VAL)atomic32Dec(a);
}

static MULTIOS_INLINE MULTIOS_ATOMIC_VAL MULTIOS_ATOMIC_AND(MULTIOS_ATOMIC *a,
							    MULTIOS_ATOMIC_VAL v)
{
	return (MULTIOS_ATOMIC_VAL)atomic32And(a, (atomic32Val_t)v);
}

static MULTIOS_INLINE MULTIOS_ATOMIC_VAL MULTIOS_ATOMIC_OR(MULTIOS_ATOMIC *a,
							   MULTIOS_ATOMIC_VAL v)
{
	return (MULTIOS_ATOMIC_VAL)atomic32Or(a, (atomic32Val_t)v);
}

static MULTIOS_INLINE int MULTIOS_ATOMIC_CAS(MULTIOS_ATOMIC *a,
					     MULTIOS_ATOMIC_VAL o,
					     MULTIOS_ATOMIC_VAL n)
{
	return (int)atomic32Cas(a, (atomic32Val_t)o, (atomic32Val_t)n);
}

/* timers */

#define MULTIOS_WAIT_FOREVER		WAIT_FOREVER

#define MULTIOS_TIMER_ID		WDOG_ID
#define MULTIOS_TIMER_INVALID		NULL

#define MULTIOS_TIMER_ARG		_Vx_usr_arg_t
typedef void (*MULTIOS_TIMER_FUNC) (MULTIOS_TIMER_ARG);

static MULTIOS_INLINE MULTIOS_TIMER_ID MULTIOS_TIMER_CREATE(void)
{
	return wdCreate();
}

static MULTIOS_INLINE void MULTIOS_TIMER_START(MULTIOS_TIMER_ID timer, int ms,
					       MULTIOS_TIMER_FUNC func,
					       MULTIOS_TIMER_ARG arg)
{
	int tick = ((ms) * sysClkRateGet() + 999) / 1000;

	(void)wdStart(timer, tick, (WD_RTN)func, arg);
}

#define MIPC_SM_ADAPT_CHECK_TIMER(timer) do {} while(0)

/* spinlocks (currently unused) */

#if 0

#define MULTIOS_SPIN_LOCK_T		spinlockIsr_t
#define MULTIOS_SPIN_LOCK_INIT(lock)	SPIN_LOCK_ISR_INIT((lock), 0)
#define MULTIOS_SPIN_LOCK(lock)		SPIN_LOCK_ISR_TAKE(lock)
#define MULTIOS_SPIN_UNLOCK(lock)	SPIN_LOCK_ISR_GIVE(lock)

#endif

/* task delay */

/*
 * MULTIOS_TASK_DELAY() - delay a task by X ms
 */
static MULTIOS_INLINE void MULTIOS_TASK_DELAY(int delay_in_ms)
{
	taskDelay((((delay_in_ms * sysClkRateGet()) + 999) / 1000) + 1);
}

/* semaphores */

#define MULTIOS_SEM			SEMAPHORE
#define MULTIOS_SEM_ID			SEM_ID
#define MULTIOS_SEM_INIT(sem)		(void)semBInit(sem, SEM_Q_FIFO, SEM_EMPTY)
#define MULTIOS_SEM_INIT_FULL(sem)	(void)semBInit(sem, SEM_Q_FIFO, SEM_FULL)
#define MULTIOS_SEM_TERM(sem)		(void)semTerminate(sem)
#define MULTIOS_SEM_CREATE()		semBCreate(SEM_Q_FIFO, SEM_EMPTY)
#define MULTIOS_SEM_CREATE_FULL()	semBCreate(SEM_Q_FIFO, SEM_FULL)
#define MULTIOS_SEM_DELETE(sem)		semDelete(sem)

extern int multios_down_timeout(MULTIOS_SEM_ID sem, int timeout);

/* 
 * MULTIOS_SEM_DOWN(sem) - get a multi-OS semaphore
 * Parameters: semaphore to wait on
 * Returns: 0 if successful; -EINVAL if any error occurred
 */
static __inline__ int MULTIOS_SEM_DOWN(MULTIOS_SEM_ID sem)
{
    return semTake(sem, MULTIOS_WAIT_FOREVER) ? -EINVAL : 0;
}

/*
 * MULTIOS_SEM_DOWN_WITH_TIMEOUT - get a multi-OS semaphore within a time limit
 * Parameters: semaphore to wait on; timeout in ms (or MULTIOS_WAIT_FOREVER)
 * Returns: time remaining if semaphore is taken
 *          (is >= 0 if timeout >= 0; is 0 if timeout == MULTIOS_WAIT_FOREVER);
 *          -ETIMEDOUT if time limit expired without getting semaphore;
 *          -EINVAL if any other error occurred
 */
static __inline__ int MULTIOS_SEM_DOWN_WITH_TIMEOUT(MULTIOS_SEM_ID sem, int timeout)
{

    return multios_down_timeout(sem, timeout);

}

#define MULTIOS_SEM_UP(sem)		semGive(sem)
#define MULTIOS_SEM_FLUSH(sem)		semFlush(sem)

/* linked lists */

#define MULTIOS_LIST			DL_LIST	/* list type */
#define MULTIOS_LIST_NODE		DL_NODE	/* element-in-the-list type */

#define MULTIOS_LIST_INIT(list)		dllInit (list)
#define MULTIOS_LIST_ADD(list, elem)	dllAdd (list, elem)
#define MULTIOS_LIST_GET(list)		dllGet (list)

/* byte-order macros (currently only support same endianness on all nodes) */

#define MULTIOS_ntoh16(x)	(x)
#define MULTIOS_ntoh32(x)	(x)
#define MULTIOS_ntoh64(x)	(x)

#define MULTIOS_hton16(x)	(x)
#define MULTIOS_hton32(x)	(x)
#define MULTIOS_hton64(x)	(x)

/* current time, in millisecond */

#define MULTIOS_CURR_TIME() (unsigned int)(tickGet() * 1000 / sysClkRateGet())

#ifdef __cplusplus
}
#endif

#endif 	/* __INC_multios_adapt_h */
 

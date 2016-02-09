/* wdbRtIfLib.h - header file for the WDB agents runtime interface */

/*
 * Copyright (c) 1994-1995,1999-2005,2007, 2009-2011, 2013-2014
 * Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this
 * software may be licensed only pursuant to the terms of an applicable Wind
 * River license agreement.
 */

/*
modification history
--------------------
17nov14,rlp  Resource lock macros return a lock-out key (VXW6-83803).
02d,12sep13,elp  resource lock/unlock return value check.
02c,06may11,jmp  Updated excHookAdd to no longer take structures as parameters,
                 we now use pointers on structures (CQ:WIND00266088).
02b,29jul10,pad  Moved extern C statement after include statements.
02a,10dec09,rlp  Changed excHookAdd function pointer signature.
01z,11sep09,rlp  Adapted to LP64 model.
01y,11jul07,rlp  Added System mode support for SMP.
01x,26jun07,tbu  Added 64 bit support
          + p_b  completed support
01w,02may07,rlp  Added resource lock/unlock routines to WDB_RT_IF structure.
01v,18nov05,dbt  Added OS specific memory scan API; removed OS specific memory
                 problem API.
01u,14nov05,dbt  Added APIs to access memory. Removed wdbRegs.h inclusion.
01t,13aug04,dbt  Added signal information in exception notification.
01s,31mar04,elg  Change prototype of excHookAdd() pointer.
01r,30sep03,elg  Fix build warnings.
		 Fix pointer error with memory probe runtime interface.
01q,12sep03,tbu  Moved inclusion of netinet/in_systm.h to wdbOsLib.h
01p,27feb03,elg  Merge file with BSD and define new runtime interface.
01o,25apr02,jhw  Added C++ support (SPR 76304).
01n,01feb01,dtr  Adding in call for test for Altivec Registers.
01m,28aug00,elg  Change pdIsValid() to pdIdVerify().
01l,16aug00,elg  Change memProtect() prototype.
01k,25apr00,elg  Add taskCtxGet() routine.
01j,12apr00,elg  Add parmeters in pdCreate().
01i,02feb00,dbt  Added pdIsValid and removed pdListGet.
01h,15nov99,elg  Add returnNodeGet() in WDB runtime interface.
01g,08nov99,elg  Add ltExitCreate().
01f,15oct99,elg  Change pdCreate() interface.
01e,09sep99,elg  Add taskCtxSwitch() to Runtime interface.
01d,06may99,elg  Add 2 new routines in the Runtime Interface: taskDebugStart()
                 and taskDebugEnd().
01c,01jun95,ms	added taskLock/Unlock, removed timers
01b,05apr95,ms  new data types.
01a,23sep94,ms  written.
*/

#ifndef __INCwdbRtIfLibh
#define __INCwdbRtIfLibh

/* includes */

#include <wdb/wdb.h>
#include <wdb/wdbCtxIfLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* data types */

typedef enum wdb_rt_mem_access
    {
    WDB_READ		= 0,	/* memory read access */
    WDB_WRITE		= 1	/* memory write access */
    } WDB_MEM_ACCESS;

typedef enum wdb_lock_type	/* type of lock */
    {
    INT_LOCK		= 0,
    SCHED_LOCK		= 1,
    TASK_RESOURCE_LOCK	= 2,
    ISR_RESOURCE_LOCK	= 3
    } WDB_LOCK_TYPE;

typedef struct wdb_rt_if
    {
    /* this function must be provided always */

    UINT32	(*rtConnectInfoGet) (WDB_CONNECT_INFO * pRtInfo);

    UINT32	(*rtInfoGet)	(WDB_RT_INFO * pRtInfo);

    /* function call to reboot machine */

    UINT32	(*reboot)	(void);

    /* function to call after loading text */

    UINT32	(*cacheTextUpdate)	(char * addr, UINT32 nBytes);

    /* function to call to write protect memory */

    UINT32	(*memProtect)		(
    					ULONG		ctx,
					char *		addr,
					UINT32		nBytes,
					BOOL		protect,
					UINT32 *	oldAttr
					);

    /* required memory access operations */

    UINT32	(*memWrite)		(
					char *	pSource,	
					char *	pDestination,	
					UINT32	nBytes,		
					UINT32	width		
					);

    UINT32	(*memFill)		(
					char *	addr,
					UINT32	nBytes,
					UINT32	pattern,
					UINT32	width
					);

    UINT32	(*memRead)		(
					char *		addr,
					char *		dest,
					UINT32		nBytes,
					UINT32		width
					);

    UINT32	(*memCksum)		(
					char *		addr,
					UINT32		nBytes,
					UINT32 *	pCksum
					);

    /* optional memory access APIs */

    UINT32	(*memMove)		(
					char *		pSource,
					char *		pDestination,
					UINT32		nBytes
					);

    UINT32	(*memScan)		(
					char *		start,
					char *		end,
					char *		pattern,
					UINT32		size,
					BOOL		match,
					char **		pAddr
					);

    /* memory management operations */

    void *	(*memalloc)		(size_t nBytes);
    UINT32 	(*memfree)		(void * pData);

    /* Memory context switch operation */

    ULONG	(*memCtxSwitch)	(ULONG newCtx);

    /* Internal resource lock/unlock routines */

    STATUS	(*resourceLock)		(WDB_LOCK_TYPE intResourceType,
    						int * pLockLvl);
    STATUS	(*resourceUnlock)	(WDB_LOCK_TYPE intResourceType,
    						int lockLvl);

    /* errno management */

    int		(*errnoGet)	(void);
    STATUS	(*errnoSet)	(int);

    /* function to install an exception hook (for exc event notification) */

    UINT32	(*excHookAdd)	(void (*hook)	(
						WDB_CTX *	pStoppedCtx,
						WDB_CTX *	pExcCtx,
						UINT32		vec,
						UINT32		sigNum,
						void *		pESF,
						WDB_IU_REGS *	pRegs,
						BOOL		systemSuspend
						));

    /* Page Size information */

    int		pageSize;

    /* node on context specific routines */

    WDB_CTX_IF *	pWdbCtxIf [WDB_CTX_TYPE_NUM];
    } WDB_RT_IF;

/* global variables */

extern WDB_RT_IF *      pWdbRtIf;	/* runtime interface */

/* macros */

/* info macro */

#define	WDB_RT_CONNECT_INFO_GET(pRtInfo)				\
	(pWdbRtIf->rtConnectInfoGet == NULL ?				\
	    WDB_ERR_NO_RT_PROC :					\
	    pWdbRtIf->rtConnectInfoGet (pRtInfo))

#define	WDB_RT_INFO_GET(pRtInfo)					\
	(pWdbRtIf->rtInfoGet == NULL ?					\
	    WDB_ERR_NO_RT_PROC :					\
	    pWdbRtIf->rtInfoGet (pRtInfo))

/* reboot macro */

#define	WDB_RT_REBOOT()							\
	(pWdbRtIf->reboot == NULL ?					\
	    WDB_ERR_NO_RT_PROC :					\
	    pWdbRtIf->reboot ())

/* memory macros */

#define	WDB_RT_MEM_CACHE_UPDATE(addr, nBytes)				\
	(pWdbRtIf->cacheTextUpdate == NULL ?				\
	    WDB_ERR_NO_RT_PROC :					\
	    pWdbRtIf->cacheTextUpdate ((addr), (nBytes)))

#define	WDB_RT_MEM_PROTECT(memCtx, dest, nBytes, protect, oldAttr)	\
	(pWdbRtIf->memProtect == NULL ?					\
	    WDB_ERR_NO_RT_PROC :					\
	    pWdbRtIf->memProtect ((memCtx), (dest), (nBytes),		\
	    			  (protect), (oldAttr)))

#define	WDB_RT_MEM_READ(source, dest, nBytes, width)			\
	(pWdbRtIf->memRead == NULL ?					\
	    WDB_ERR_NO_RT_PROC :					\
	    pWdbRtIf->memRead ((char*)(source),	(char*)(dest), 		\
		    	       (nBytes), (width)))

#define	WDB_RT_MEM_WRITE(source, dest, nBytes, width)			\
	(pWdbRtIf->memWrite == NULL ?					\
	    WDB_ERR_NO_RT_PROC :					\
	    pWdbRtIf->memWrite ((source), (dest), (nBytes), (width)))

#define	WDB_RT_MEM_FILL(source, nBytes, pattern, width)			\
	(pWdbRtIf->memFill == NULL ?					\
	    WDB_ERR_NO_RT_PROC :					\
	    pWdbRtIf->memFill ((source), (nBytes), (pattern), (width)))

#define	WDB_RT_MEM_MOVE(source, dest, nBytes)				\
	(pWdbRtIf->memMove == NULL ?					\
	    WDB_ERR_NO_RT_PROC :					\
	    pWdbRtIf->memMove ((source), (dest), (nBytes)))

#define	WDB_RT_MEM_SCAN(start, end, pattern, size, match, pAddr)	\
	(pWdbRtIf->memScan == NULL ?					\
	    WDB_ERR_NO_RT_PROC :					\
	    pWdbRtIf->memScan ((start), (end), (pattern), (size),	\
	    			(match), (pAddr)))

#define	WDB_RT_MEM_CKSUM(addr, size, pCksum)				\
	(pWdbRtIf->memCksum == NULL ?					\
	    WDB_ERR_NO_RT_PROC :					\
	    pWdbRtIf->memCksum ((addr), (size), (pCksum)))

#define	WDB_RT_MEM_ALLOC(type, size)					\
	(pWdbRtIf->memalloc == NULL ?					\
	    (type *) NULL :						\
	    (type *) pWdbRtIf->memalloc ((size_t) ((size) * sizeof (type))))

#define	WDB_RT_MEM_FREE(addr)						\
	(pWdbRtIf->memfree == NULL ?					\
	    WDB_ERR_NO_RT_PROC :					\
	    pWdbRtIf->memfree (addr))

#define	WDB_RT_MEM_SWITCH(memCtx)					\
	(pWdbRtIf->memCtxSwitch == NULL ?				\
	    WDB_ERR_NO_RT_PROC :					\
	    pWdbRtIf->memCtxSwitch (memCtx))

/* Internal resource lock/unlock macros */

/*
 * This lock disables scheduling on the local CPU. This effectively prevents
 * any other task from running on the local CPU and prevents the calling
 * from migrating to another CPU until the lock is released. Note that in
 * system mode, it's nop operation.
 */

#define WDB_RT_SCHED_LOCK(pLevel)					\
	(pWdbRtIf->resourceLock == NULL ?				\
	    WDB_ERR_NO_RT_PROC :					\
	    (void)pWdbRtIf->resourceLock (SCHED_LOCK, pLevel))

#define WDB_RT_SCHED_UNLOCK(level)     					\
	(pWdbRtIf->resourceUnlock == NULL ?				\
	    WDB_ERR_NO_RT_PROC :					\
	    (void)pWdbRtIf->resourceUnlock (SCHED_LOCK, level))

/*
 * This lock disables interrupts on the local CPU. An architecture-dependent
 * lock-out key for the interrupt state prior to the call is returned. This
 * value will be used by WDB_RT_INT_UNLOCK() as input parameter to unlock
 * resource.
 */

#define WDB_RT_INT_LOCK(pLevel)						\
	(pWdbRtIf->resourceLock == NULL ?				\
	    WDB_ERR_NO_RT_PROC :					\
	    pWdbRtIf->resourceLock (INT_LOCK, pLevel))

#define WDB_RT_INT_UNLOCK(level)					\
	(pWdbRtIf->resourceUnlock == NULL ?				\
	    WDB_ERR_NO_RT_PROC :					\
	    pWdbRtIf->resourceUnlock (INT_LOCK, level))

/*
 * This lock is used to control mutually exclusive access to task-level and
 * interrupt-level WDB internal resource. An architecture dependent lock-out
 * key for the interrupt state prior to the call is returned. This lock-out
 * key will be used to unlock resource. Note that in system mode (SMP system
 * only), it's nop.
 */

#define	WDB_RT_ISR_RESOURCE_LOCK(pLockLvl)				\
	(pWdbRtIf->resourceLock == NULL ?				\
	    WDB_ERR_NO_RT_PROC :					\
	    pWdbRtIf->resourceLock (ISR_RESOURCE_LOCK, pLockLvl))

#define	WDB_RT_ISR_RESOURCE_UNLOCK(lockLvl)				\
	(pWdbRtIf->resourceUnlock == NULL ?				\
	    WDB_ERR_NO_RT_PROC :					\
	    pWdbRtIf->resourceUnlock (ISR_RESOURCE_LOCK, lockLvl))

/*
 * This lock is used to control mutually exclusive access to a task-level
 * WDB internal resource, it cannot be used at interrupt-level. Return OK on
 * success or ERROR if the we cannot lock the resource. Note that in system
 * mode, it's nop operation.
 */

#define	WDB_RT_TASK_RESOURCE_LOCK(pLockLvl)				\
	(pWdbRtIf->resourceLock == NULL ?				\
	    WDB_ERR_NO_RT_PROC :					\
	    pWdbRtIf->resourceLock (TASK_RESOURCE_LOCK, pLockLvl))

#define	WDB_RT_TASK_RESOURCE_UNLOCK(lockLvl)				\
	(pWdbRtIf->resourceUnlock == NULL ?				\
	    WDB_ERR_NO_RT_PROC :					\
	    pWdbRtIf->resourceUnlock (TASK_RESOURCE_LOCK, lockLvl))

/* errno management */

#define	WDB_RT_ERRNO_GET()						\
	(pWdbRtIf->errnoGet == NULL ?					\
	    ERROR :							\
	    pWdbRtIf->errnoGet ())

#define	WDB_RT_ERRNO_SET(x)						\
	(pWdbRtIf->errnoSet == NULL ?					\
	    ERROR :							\
	    pWdbRtIf->errnoSet (x))

/* hooks */

#define	WDB_RT_EXC_HOOK_ADD(hook)					\
	(pWdbRtIf->excHookAdd == NULL ?					\
	    WDB_ERR_NO_RT_PROC :					\
	    pWdbRtIf->excHookAdd (hook))

#ifdef __cplusplus
}
#endif

#endif  /* __INCwdbRtIfLibh */

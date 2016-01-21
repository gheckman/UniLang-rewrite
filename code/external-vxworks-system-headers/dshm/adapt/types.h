/* types.h - DSHM adaptation layer: types declaration */

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
01l,15jul10,gjj  deprecated the DSHM technology and added deprecation macros.
01k,29apr10,pad  Moved extern C statement after include statements.
01j,05sep07,bwa  added check for usage of DSHM_RW_LOCAL_LOCK
01i,24aug07,bwa  added refl.h include; shuffled location of DSHM_RW_LOCAL macros
01h,24aug07,bwa  memory barrier definition now uses kernel version;
		 changed DSHM_ATOMIC_SET/CLEAR() to DSHM_TAS/CLEAR pair.
01g,21jun07,bwa  changed RMW to ATOMIC_SET and _CLEAR
01f,17jun07,bwa  added DSHM_RW_LOCK_LOCAL, CACHE, LIST and ROUND_UP macros.
01e,03apr07,bwa  added linked-list macros.
01d,13feb07,bwa  added DSHM_DRV_REG type.
01c,26jan07,bwa  added DSHM_LSB().
01b,21dec06,bwa  added memory barrier; removed FUNCPTR usage;
                 made DSHM_LOCK creation Linux-friendly.
01a,05jul06,bwa  written.
*/

/* types adaptation header file for VxWorks DSHM */

#ifndef __INCdshmAdaptTypesh
#define __INCdshmAdaptTypesh

#include <vxWorks.h>
#include <intLib.h>
#include <taskLib.h>
#include <errnoLib.h>
#include <vxBusLib.h>
#include <wdLib.h>
#include <rebootLib.h>
#include <semLib.h>
#include <jobQueueLib.h>
#include <stdlib.h>
#include <string.h>
#include <hwif/vxbus/vxBus.h>
#include <ffsLib.h>
#include <vxAtomicLib.h>

#define DSHM_INLINE			__inline__
#define DSHM_HW_ID			VXB_DEVICE_ID
#define DSHM_PEER_ID			VXB_DEVICE_ID
#define DSHM_TIMER_ID			WDOG_ID
#define DSHM_LOCK_ID			SEM_ID
#define DSHM_LOCK_OPTIONS		(SEM_Q_FIFO | SEM_DELETE_SAFE)
#define DSHM_HANDLE                     int

#define DSHM_LOCK_CREATE(lock)		lock = semMCreate(DSHM_LOCK_OPTIONS)
#define DSHM_LOCK_VERIFY(lock)		(lock != NULL)
#define DSHM_LOCK_ACQUIRE(lock)		semTake(lock, WAIT_FOREVER)
#define DSHM_LOCK_READ(lock)		semTake(lock, WAIT_FOREVER)
#define DSHM_LOCK_RELEASE(lock)		semGive(lock)
#define DSHM_LOCK_DELETE(lock)		semDelete(lock)

#define DSHM_KALLOC(size)		malloc(size)
#define DSHM_KFREE(size)		free(size)

#define DSHM_MSB(value)			(ffsMsb((UINT32)value) - 1)
#define DSHM_LSB(value)			(ffsLsb((UINT32)value) - 1)

#define DSHM_INTLOCK()			intLock()
#define DSHM_INTUNLOCK(key)		intUnlock(key)

#define DSHM_LIST                       DL_LIST
#define DSHM_LIST_NODE                  DL_NODE
#define DSHM_LIST_INIT(pList)		dllInit (pList)
#define DSHM_LIST_ADD(pList, pElem)	dllAdd (pList, pElem)
#define DSHM_LIST_GET(pList)		dllGet (pList)

#define DSHM_CACHE_FLUSH(ptr, size)     CACHE_USER_FLUSH(ptr, size);
#define DSHM_CACHE_ALIGN                _CACHE_ALIGN_SIZE

#define DSHM_ROUND_UP(ptr, align)       ROUND_UP(ptr, align)

#include <stdio.h>
#define DSHM_PRINT			printf
#include <logLib.h>
#define DSHM_IPRINT                     logMsg  /* interrupt-safe printout */

#define DSHM_MUX_RESET_REGISTER(reset)	rebootHookAdd((FUNCPTR)reset)

/* local read-write lock: using the refl implementation: needs to be after the
 * other definitions since it is making use of some of them.
 *
 * WARNING
 * -------
 * In VxWorks, the DSHM_RW_LOCAL_LOCK_xxx definitions use the 'refl'
 * implementation, which is inlined for performance reasons. However, warnings
 * will be generated if the current file is included in a source file and the
 * reflX() routines are not used. To prevent this, the DSHM_RW_LOCAL_LOCK_USE
 * macro must be defined _before_ including dshm/dshm.h in source code _if_
 * the DSHM_RW_LOCAL_LOCK_xxx definitions are to be used.
 *
 * This is mostly for internal use and should not impact users.
 */

#ifdef DSHM_RW_LOCAL_LOCK_USE
#include "refl.h"
#define DSHM_RW_LOCAL_LOCK_INIT(lock)       reflInit(lock)
#define DSHM_RW_LOCAL_LOCK_READ_TAKE(lock)  reflUseTake(lock)
#define DSHM_RW_LOCAL_LOCK_WRITE_TAKE(lock) reflModTake(lock)
#define DSHM_RW_LOCAL_LOCK_READ_GIVE(lock)  reflUseGive(lock)
#define DSHM_RW_LOCAL_LOCK_WRITE_GIVE(lock) reflModGive(lock)
#define DSHM_RW_LOCAL_LOCK_DEMOTE(lock)     reflDemote(lock)
#endif  /* DSHM_RW_LOCAL_LOCK_USE */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _DSHM_DRV_REG
    {
    struct vxbDevRegInfo info;
    void(*pProbeSwitch)(void);
    } DSHM_DRV_REG;
    
STATUS dshmAdaptDriverRegister (const DSHM_DRV_REG * const pDriver) 
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
JOB_QUEUE_ID dshmAdaptJobQGet (void) 
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");

/* function pointer types (to keep our sanity) */
typedef int (*DSHM_TAS) (char *);
typedef int (*DSHM_TAS_CLEAR) (char *);
typedef void (*DSHM_NODE_ISR) (void *);

/* memory barrier */
#define DSHM_MEM_BARRIER	VX_MEM_BARRIER_RW

#ifdef __cplusplus
}
#endif

#endif 	/* __INCdshmAdaptTypesh */
 

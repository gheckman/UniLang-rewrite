/* dshmSpinLock.h - DSHM spinlocks */

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
01g,15jul10,gjj  deprecated the DSHM technology and added deprecation macros.
01f,29apr10,pad  Moved extern C statement after include statements.
01e,24aug07,bwa  changed DSHM_ATOMIC_SET/CLEAR to DSHM_TAS/CLEAR
01d,21jun07,bwa  changed RMW to ATOMIC_SET and _CLEAR
01c,29jan07,bwa  added tracking of spinlock holder.
01b,21dec06,bwa  updated to meet code standards.
01a,05jul06,bwa  written.
*/

#ifndef __INCdshmSpinLockh
#define __INCdshmSpinLockh

#include <vxWorks.h>
#include <dshm/dshm.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _DSHM_SPINLOCK_OWNER
    {
    uint32_t seqnum;		/* sequence number of 'take' operation
				 * that is considered to be holding the
				 * lock for too long. */
    uint16_t holder;		/* rogue entity holding lock */
    uint16_t pad;
    } DSHM_SPINLOCK_OWNER;

typedef struct _DSHM_SPINLOCK
    {
    volatile int8_t lock;	/* the actual lock location */
    volatile int8_t breaklock;	/* if held, the lock is getting broken */
    uint16_t pad;
    DSHM_SPINLOCK_OWNER owner;
    } DSHM_SPINLOCK;

extern void dshmSpinLockLibInit (void)
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
extern void dshmSpinLockInit (DSHM_SPINLOCK * const pLock)
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
extern int dshmSpinLockTake (DSHM_SPINLOCK * const pLock,
                                const DSHM_TAS tas,
				DSHM_SPINLOCK_OWNER * const pOwner,
                                const int nTries)
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
extern STATUS dshmSpinLockGive (DSHM_SPINLOCK * const pLock,
                                    const DSHM_TAS_CLEAR clear,
				    const int intlvl )
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
extern void dshmSpinLockBreak (DSHM_SPINLOCK * const pLock,
                                    const DSHM_TAS tas,
                                    const DSHM_TAS_CLEAR clear,
				    DSHM_SPINLOCK_OWNER * const pOwner)
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
    
#ifdef __cplusplus
}
#endif

#endif  /* __INCdshmSpinLockh */


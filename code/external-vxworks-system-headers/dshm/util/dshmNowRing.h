/* dshmNowRing.h - dSHM Non-OverWritable Rings */

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
01h,15jul10,gjj  deprecated the DSHM technology and added deprecation macros.
01g,29apr10,pad  Moved extern C statement after include statements.
01f,27sep07,bwa  fixed WIND104510: DSHM crash on little-endian targets.
01e,24aug07,bwa  changed DSHM_ATOMIC_SET/CLEAR to DSHM_TAS/CLEAR
01d,21jun07,bwa  changed RMW to ATOMIC_SET and _CLEAR
01c,01feb07,bwa  adapted to new spinlock type.
01b,21dec06,bwa  added volatile qualifiers;
                 remove non-portable _PACK_ attribute.
01a,05jul06,bwa  written.
*/

#ifndef __INCdshmNowRingh
#define __INCdshmNowRingh

#include <dshm/dshm.h>
#include <dshm/util/dshmSpinLock.h>

#ifdef __cplusplus
extern "C" {
#endif

/* this is the ring descriptor in shared memory */
typedef struct _dshmNowRing
    {
    DSHM_SPINLOCK spinlock;	/* atomic access to the ring */
    uint16_t szEntry;		/* entry size */
    volatile uint16_t iRead;	/* read index */
    volatile uint16_t iWrite;	/* write index */
    uint16_t nEntries;		/* actually ((number of entries in the ring)-1)
				 * because in the time-critical places this is
				 * accessed, 1 would always have to be
				 * substracted from the number of entries.
				 */
    } DSHM_NOW_RING;

/*
This is what the ring data structure looks like with the entries following
the ring descriptor in shared memory. This data structure is currently not
used and only kept for reference.

typedef struct _dshmNowRingReal
    {
    DSHM_NOW_RING hdr;
    char entries[1];
    } DSHM_NOW_RING_REAL;
*/

#define DSHM_NOW_RING_ENTRY_SIZE(pRing)	\
    (ntohs(pRing->szEntry))
#define DSHM_NOW_RING_SIZE(nEntries, szEntry) \
    (szEntry * nEntries + sizeof(DSHM_NOW_RING))

#define DSHM_NOW_RING_SPINLOCK_RETRIES_DEFAULT	256

void dshmNowRingLibInit (void)
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
STATUS dshmNowRingInit (DSHM_NOW_RING * const pRing,
			    uint16_t * const pnEntries,
			    const uint16_t szEntry)
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
STATUS dshmNowRingRead (DSHM_NOW_RING * const pRing,
                            const DSHM_TAS tas,
                            const DSHM_TAS_CLEAR clear,
			    char * const pData)
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
STATUS dshmNowRingWrite (DSHM_NOW_RING * const pRing,
                            const DSHM_TAS tas,
                            const DSHM_TAS_CLEAR clear,
			    const char * const pData)
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");

#ifdef __cplusplus
}
#endif

#endif /* __INCdshmNowRingh */

 

/* dshmOwRing.h - DSHM OverWritable Rings */

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
01j,15jul10,gjj  deprecated the DSHM technology and added deprecation macros.
01i,29apr10,pad  Moved extern C statement after include statements.
01h,24aug07,bwa  changed DSHM_ATOMIC_SET/CLEAR to DSHM_TAS/CLEAR
01g,21jun07,bwa  changed RMW to ATOMIC_SET and _CLEAR
01f,17jun07,bwa  updated following code review.
01e,24feb07,bwa  modified to handle local RW lock descriptors and revised API.
01d,02feb07,bwa  modified RW lock handling policies.
01c,24jan07,bwa  added self-address field into DSHM_OW_RING.
01b,21dec06,bwa  standards and portability update.
01a,05jul06,bwa  written.
*/

#ifndef __INCdshmOwRingh
#define __INCdshmOwRingh

#include <dshm/dshm.h>
#include <dshm/util/dshmRwLock.h>

#ifdef __cplusplus
extern "C" {
#endif

/* in network byte-order */
typedef struct _dshmOwrSmEntry	/* over-writable ring entry */
    {				/* ------------------------ */
    uint16_t seq;		/* sequence number for read verification */
    uint16_t szData;		/* size of current data in octets */
    DSHM_RW_LOCK_SM rwLock;	/* RW lock on the ring entry */
    } DSHM_OWR_SM_ENTRY;

/* in network byte-order */
typedef struct _dshmOwrSm	/* over-writable ring - shared memory portion */
    {				/* ------------------------------------------ */
    uint16_t nEntries;		/* number of entries: must be power-of-two */
    uint16_t szDataMax;		/* size of data section in each entry */
    uint16_t iWrite;		/* index of the next write access, access is
				 * protected by intLock()/intUnlock() */
    uint16_t pad;               /* unused */
    } DSHM_OWR_SM;

/* in host byte-order */
typedef struct _dshmOwRing	/* over-writable ring - host memory portion */
    {				/* ----------------------------------------- */
    DSHM_OWR_SM *pSmRing;	/* pointer to SM portion */
    DSHM_RW_LOCK *pRwLockTbl;   /* pointer to table of RW locks */
    DSHM_TAS tas;               /* test-and-set on shared memory */
    DSHM_TAS_CLEAR clear;       /* test-and-set clear on SM */
    uint16_t nEntries;		/* number of entries in the ring */
    uint16_t szDataMax;		/* size of the data in one entry (in octets) */
    } DSHM_OW_RING;

void dshmOwRingLibInit (void) 
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
int dshmOwRingCreate ( DSHM_OWR_SM * const pSmRing,
                        const DSHM_TAS tas,
                        const DSHM_TAS_CLEAR clear,
                        const int thWriteTries) 
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
STATUS dshmOwRingSmInit (DSHM_OWR_SM * const pSmRing, const uint16_t nEntries,
			    const uint16_t szData) 
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
int dshmOwRingSmSizeGet (const int nEntries, const int szData) 
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
uint16_t dshmOwRingRead ( const int handle, const uint32_t tag,
			    char * const pBuffer) 
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
STATUS dshmOwRingWrite ( const int handle, const char * const pData,
			    const int szData, uint32_t * const pTag ) 
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
void dshmOwRingDelete ( const int handle ) 
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
		    
#ifdef __cplusplus
}
#endif

#endif /* __INCdshmOwRingh */


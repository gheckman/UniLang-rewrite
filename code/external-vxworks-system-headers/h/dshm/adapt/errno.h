/* errno.h - dSHM adaptation layer: errno definitions */

/*
 * Copyright (c) 2006, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01e,29apr10,pad  Moved extern C statement after include statements.
01d,23jun07,bwa  removed temporary M_dshm.
01c,26jan07,bwa  added _RW_LOCK_READ_LOCK_HELD and _OW_RING_BROKE_LOCK
01b,12jan07,bwa  more errnos.
01a,29jul06,bwa  written.
*/

#ifndef __INCdshmAdaptErrnoh
#define __INCdshmAdaptErrnoh

#include <vwModNum.h>

#ifdef __cplusplus
extern "C" {
#endif

#define S_dshm_MUX_HW_TABLE_FULL			(M_dshm | 0x0001)
#define S_dshm_MUX_HW_NAME_EXISTS			(M_dshm | 0x0002)
#define S_dshm_DSHM_RW_LOCK_READ_LOCK_HELD		(M_dshm | 0x0003)
#define S_dshm_MUX_HW_TABLE_NOT_INITIALIZED		(M_dshm | 0x0004)
#define S_dshm_MUX_SERVICE_NOT_REGISTERED		(M_dshm | 0x0005)
#define S_dshm_INVALID_HANDLE				(M_dshm | 0x0006)
#define S_dshm_DSHM_RW_LOCK_WRITE_LOCK_TAKEN		(M_dshm | 0x0007)
#define S_dshm_DSHM_RW_LOCK_READ_LOCK_TAKEN		(M_dshm | 0x0008)
#define S_dshm_DSHM_OW_RING_OBSOLETE_TAG		(M_dshm | 0x0009)
#define S_dshm_DSHM_NOW_RING_EMPTY			(M_dshm | 0x000a)
#define S_dshm_DSHM_NOW_RING_FULL			(M_dshm | 0x000b)
#define S_dshm_SM_LOAD_TOO_BIG				(M_dshm | 0x000c)
#define S_dshm_SM_CAN_NOT_SEND				(M_dshm | 0x000d)
#define S_dshm_SPINLOCK_UNAVAILABLE			(M_dshm | 0x000e)
#define S_dshm_SM_BUFFER_TOO_SMALL			(M_dshm | 0x000f)
#define S_dshm_MUX_SERVICE_TABLE_FULL			(M_dshm | 0x0010)
#define S_dshm_MUX_SERVICE_TABLE_NOT_INITIALIZED	(M_dshm | 0x0011)
#define S_dshm_MUX_NODE_TABLE_FULL			(M_dshm | 0x0012)
#define S_dshm_MUX_HW_INDEX_NOT_REGISTERED		(M_dshm | 0x0013)
#define S_dshm_NUMBER_OF_ENTRIES_NOT_POWER_OF_TWO	(M_dshm | 0x0014)
#define S_dshm_MEM_POOL_NOT_INITIALIZED			(M_dshm | 0x0015)
#define S_dshm_MEM_INVALID_SLAB				(M_dshm | 0x0016)
#define S_dshm_MEM_OUT_OF_MEMORY			(M_dshm | 0x0017)
#define S_dshm_MUX_NODE_NOT_REGISTERED			(M_dshm | 0x0018)
#define S_dshm_INVALID_POOL_OR_BUFFER_SIZE		(M_dshm | 0x0019)
#define S_dshm_RW_LOCK_ALREADY_READING			(M_dshm | 0x001a)
#define S_dshm_INVALID_PARAMETER			(M_dshm | 0x001b)
#define S_dshm_PKT_SIZE_OVER_MTU			(M_dshm | 0x001c)
#define S_dshm_TABLE_FULL				(M_dshm | 0x001d)
#define S_dshm_OW_RING_BROKE_LOCK			(M_dshm | 0x001e)

#ifdef __cplusplus
}
#endif

#endif /* __INCdshmAdaptErrnoh */


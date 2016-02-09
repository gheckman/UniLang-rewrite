/* hwMemLib.h - hardware memory allocation library header file */

/*
 * Copyright (c) 2005, 2009, 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/* 
Modification history
--------------------
01g,08aug12,l_z  remove HWMEM_MAX_ALLOC. (WIND00364661)
01f,09dec09,h_k  reverted the hwMemAlloc prototype for LP64.
01e,05nov09,h_k  mapped hwMemAlloc() to calloc.
01d,23jun09,jc0  fix WIND00170079, move hwMemShow() from hwMemLib.c to
                 vxbShow.c
01c,16jun09,x_s  restriction hwMemFree() for small footprint 
01b,23feb09,h_k  updated for LP64 support.
01a,31Jan05,tor  created
*/

#ifndef INC_HWMEMLIB_H
#define INC_HWMEMLIB_H

#ifdef __cplusplus
extern "C" {
#endif

/* includes */

/* defines */

#define VMR_MINSIZE	(1<<2)		/* minimum size to allocate */

#ifndef	_WRS_CONFIG_DELAYED_HW_INIT

/* typedefs */

/*
 * Note: for the hwMemBuf stucture, we need to make sure that the stuff
 * immediately preceeding the actual memory buffer is 16 bytes in size.
 * The problem is that in VxWorks, a pointer on a 64-bit arch (e.g. mips64)
 * is 32 bits wide. For now, this means we need to insert a 4 byte pad
 * into the structure. However, in the future, its possible that pointers
 * will actually become 64 bits wide, at which point the structure
 * definition will need to be fixed.
 */

struct hwMemBuf
    {
    long    preSentinel;         /* sentinel value */
    UINT32  pad;
    struct hwMemBuf * pNextBuff; /* next buffer in chain */
    long    postSentinel;        /* sentinel value */
    char    pData[1];            /* beginning of data buffer */
    };

struct hwMemPool
    {
    struct hwMemPool *  pNext;  /* multi-pool support */
    char *  pLowerLimit;        /* pointer to beginning of pool */
    char *  pUpperLimit;        /* pointer to end of pool */
    char *  pStore;             /* unallocated space */
    size_t  poolSize;           /* size of unallocated space */
    struct hwMemBuf *   pHead[6];   /* 48-byte through 2032-byte pools */
    struct hwMemBuf *   pAlloc[6];  /* allocated buffers */
    UINT32  pad;
    };

/* externs */

IMPORT char hwMemPool[];

/* locals */

/* forward declarations */

void hwMemLibInit (void);
STATUS hwMemPoolCreate
    (
    char *	pMem,
    size_t	size
    );

void hwMemInit (void);

#endif	/* !_WRS_CONFIG_DELAYED_HW_INIT */

char * hwMemAlloc (size_t reqSize);

#ifndef _WRS_CONFIG_VXBUS_BASIC
STATUS hwMemFree (char * pMem);
#endif /* !_WRS_CONFIG_VXBUS_BASIC */

void * hwVMRInit (char * pSpace, size_t size);
void * hwVMRAlloc (void * pVMRCookie, int alignShift);
char * hwVMRAddrGet (void * pVMRCookie);
STATUS hwVMRDeActivate (void * pVMRCookie);

#ifdef __cplusplus
}
#endif

#endif /* INC_HWMEMLIB_H */

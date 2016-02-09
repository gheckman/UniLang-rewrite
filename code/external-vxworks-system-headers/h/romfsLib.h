/* romfsLib.h - ROMFS file system driver */

/*
 * Copyright 2003, 2009-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
-------------------- 
01c,27may10,pad  Moved extern C statement after include statements.
01b,07may09,zly  LP64 support 
01a,05may03,md   written
*/

#ifndef romfsLib_h
#define romfsLib_h

#include <vxWorks.h>
#include <sys/types.h>
#include <iosLib.h>
#include <blkIo.h>
#include <semLib.h>
#include <romfsDrv.h>

#ifdef __cplusplus
extern "C" {
#endif

				/* block size of underlying device */
#define	DEV_BSIZE	ROMFS_BLOCK_SIZE

				/* magic number to identify ROMFS_VOL_DESC */
#define	ROMFS_MAGIC	0xDEADF00D

typedef struct romfsVolDescr	/* volume descriptor, one per mounted volume */
    {
    DEV_HDR   devHdr;		  /* for adding to device table		    */
    BLK_DEV  *pBlkDev;		  /* pointer to block device structure	    */
    int	      magic;		  /* magic number for identifying structure */
    u_char    cache[DEV_BSIZE];	  /* buffer cache for one block		    */
    int	      cBlockNum;	  /* cached block number		    */
    SEM_ID    devSem;		  /* device mutual-exclusion semaphore	    */
} ROMFS_VOL_DESC;

typedef ROMFS_VOL_DESC *	ROMFS_VOL_DESC_ID;

int vxBlkIO (void *p, int type,	daddr_t bn,	uint_t bsize, char *rfsbuf,	uint_t *rs);
STATUS romfsFsInit (void);

/* user-callable functions prototypes */

extern ROMFS_VOL_DESC_ID romfsFsDevCreate( char * devName, BLK_DEV * pBlkDev );

#ifdef __cplusplus
}
#endif

#endif /* romfsLib_h */

/* virtualDiskLib.h - VxSim virtual disk driver header */

/* Copyright 2003, 2010 Wind River Systems, Inc. */
/*
modification history
--------------------
01c,29apr10,pad  Moved extern C statement after include statements.
01b,16oct03,jeg  added virtualDiskClose () prototype.
01a,22jun03,jeg written 
*/

#ifndef __INCvirtualDiskLibh
#define __INCvirtualDiskLibh

/* includes */

#include "blkIo.h"
#include "private/virtualDiskLibP.h"

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#define DEFAULT_SIZE   		512		/* default parameters value */
#define	BLOCKSIZE		8192		/* default block size	    */
#define DEFAULT_DISK_SIZE  	(1024*1024)	/* default disk size	    */

/* function declarations */

extern BLK_DEV * virtualDiskCreate (char * hostFile, int bytesPerBlk, 
	int blksPerTrack, int nBlocks);
extern STATUS virtualDiskInit (void);
extern STATUS virtualDiskClose (BLK_DEV * blkDev);

#ifdef __cplusplus
}
#endif

#endif /* __INCvirtualDiskLibh */

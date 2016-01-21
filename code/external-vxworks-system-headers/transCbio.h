/* transCbio.h - Transaction Block I/O library */

/*
 * Copyright (c) 2004-2005 Wind River Systems, Inc.
 * 
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */

/*
modification history
--------------------
01c,18aug05,act  add prototype for xbdTransInit
01b,31may05,act  convert from CBIO to XBD
01a,23sep04,rfr  Added include guards
    17mai04,alr  created
*/

/*
DESCRIPTION

This library provides...

See description of XBDs.


SEE ALSO
.I "VxWorks Programmers Guide: I/O System"

INCLUDE FILES
transCbio.h

INTERNAL
*/

#ifndef __INCtransCbioh
#define __INCtransCbioh

#include "vxWorks.h"
#include "semLib.h"
#include "cbioLib.h"			/* XXX - for block_t */
#include "drv/xbd/bio.h"
#include "drv/xbd/xbd.h"

#ifdef __cplusplus
extern "C" {
#endif

/* error codes */
#define ERROR_LOCK		0	/* error acquiring lock (semTake()) */
#define ERROR_TRANS_WRITE	1	/* error writing transaction */
#define ERROR_CONSISTENCY	3	/* internal consistency check error */
#define ERROR_IO_OPERATION	4	/* general IO error (underlying layer should not return error!) */
#define ERROR_OUTOFMEMORY	5	/* out of heap memory */
#define ERROR_UNCATCHED		6	/* system was unable to recover from warning */
#define ERROR_OUT_OF_UNITS	7	/* out of physical units */
#define ERROR_DEFRAG		8	/* error while defragmenting */

/* warning codes */
#define WARN_OUT_OF_UNITS	10	/* out of physical units */
#define WARN_TRANS_CRC_MIS	11	/* transaction CRC mismatch */

/* Implementation dependent data structures */
typedef struct transCtrl TRANS_CTRL;

/*
 * Transaction data, some stored on disk (via TRANS_MASTER; see xbdTran.c).
 * Note that block_t should probably be sector_t, but we store block_t
 * values on disk.
 */
struct transCtrl
    {
    /* physical disk geometry */
    block_t	physStartOffset;	/* spare offset to leave on disk (e.g. TFFS=1) */
    block_t	physTrans1Offset;	/* physical block offset translation table 1 */
    block_t	physTrans2Offset;	/* physical block offset translation table 2 */
    block_t	physTransSize;		/* # of physical data blocks for a translation table */
    block_t	physDataOffset;		/* physical block offset for data */
    block_t	physDataSize;		/* # of physical data blocks */

    /* translation information */
    int		blkshift;		/* blk size shifter (used to increase the logical block sizes) */
    int		overhead;		/* overhead size */
	
    /* physical disk geometry seen in units (blocks including blkshift) */
    block_t	physDataUnits;		/* # of physical data units */
    block_t	physFreeUnits;		/* # of free physical data units */
    block_t	physReplacedUnits;	/* # of replaced physical data units */
    char *	physUnitFree;		/* physical units free table */
    char *	physUnitReplaced;	/* physical units replaced table */
    block_t	physLastFreeUnit;	/* last found free physical data units */
	
    /* logical disk geometry */
    block_t *	virtToPhys;		/* virtual # to physical # mapping table */
    char *	virtToPhysDirty1;	/* virtToPhys dirty table */
    char *	virtToPhysDirty2;	/* virtToPhys dirty table */

    /* transaction information */
    u_long	transSerial;		/* current transaction serial number */
    u_char	transNumber;		/* current transaction image */

    /* disk identification */
    u_long	diskSerial1;		/* disk serial number 1 (random) */
    u_long	diskSerial2;		/* disk serial number 2 (random hash) */

    /* transaction layer options */
    u_long	options;		/* options for transaction layer */
    };

typedef struct transXbd TRANS_XBD, *TRANS_XBD_ID;
/* the actual details of a transXbd are only in xbdTrans.c */

/* Function Pointers */
extern STATUS (*transpanic)(TRANS_XBD *dev, int code, char * message);
extern STATUS (*transwarning)(TRANS_XBD *dev, int code, char * message);

/* format structure + types */
#define FORMAT_REGULAR	0	/* Regular type. It includes a TMR at the
				 * beginning and end of the media to
				 * increase reliability. It should be used
				 * for all regular devices, which are neither
				 * TFFS, nor require DosFS compatiblity
				 * (will never be accessed in a pure FAT
				 * system). */

#define FORMAT_TFFS	1	/* TFFS type. It leaves the first sector
				 * empty (for TFFS), and only uses a TMR
				 * on the end of the media. */

#define FORMAT_DOS	2	/* DOS FAT compatiblity type. It immediately
				 * starts the media, moving all transaction
				 * data and TMR to the end of the media.
				 * A media prepared with this (and
				 * defragmented) will be read and
				 * accessible in a Dos FAT system. */

/* XXX this structure is obsolete (? but do we want to handle the ioctl?) */
typedef struct transFmt
    {
    /* translation information */
    int		blkshift;	/* blk size shifter (used to increase logical block sizes) */
    int		overhead;	/* overhead size */
    int		type;		/* format type */
    } TRANS_FORMAT;

TRANS_XBD *transDevCreate(device_t subDev);
STATUS formatTrans(int rawFd, int blkshift, int overhead, int type);
STATUS transShow(TRANS_XBD *dev, int verb);
device_t xbdTransDevCreate(device_t subDev);
STATUS xbdTransInit(void);

#ifdef __cplusplus
}
#endif

#endif /* __INCtransCbioh */

/* hrfsLib.h - Highly reliabe file system header file */

/*
 * Copyright (c) 2005-2006, 2008 - 2009 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement. 
 */ 
 
/* modification history
-------------------- 
02e,01jul09,hui  WIND142041 - HRFS performance improvement
02d,19aug08,hui  WIND000129267 - HRFS poor performance when performing more than 
                 one writes.
02c,01jun06,jlk  added commit policy stuff
02b,21dec05,dcc  modified declaration of hrfsDevCreate2() (SPR: 113785)
02a,15nov05,md   move time functions to private header file
01z,26aug05,jlk  Added HRFS_BAD_CHAR macro
01y,05aug05,jlk  Added prototype for hrfsChkDsk()
01x,04aug05,jlk  Moved formatter function pointer, hrfsFmtRtn, from hrFsLibP.h
01w,03aug05,pcm  changed parameters to hrfsDevLibInit()
01v,26jul05,jlk  removed unused errnos
01u,22jul05,jlk  code review changes
01t,17jun05,jlk  removed format structure. Adjusted and added formatter 
                 prototypes
01s,07jun05,jlk  added format structure
01r,18may05,jlk  updated errnos and added prototypes
01q,10may05,pcm  changed parameters to hrfsFormat()
01p,29apr05,jlk  updated HRFS version numbers.
01o,29apr05,jlk  updated errnos.
01n,25apr05,jlk  added version #defines and id string from hrFsLibP.h
01m,21apr05,jlk  updated HRFS errno codes
01l,18apr05,pcm  moved _PC_xxx macros for pathconf() to unistd.h
01k,18apr05,pcm  added _PC_xxx macros for pathconf stuff
01j,11apr05,pcm  changed HRFS_MAX_FILENAME_LEN from 252 to 251
01i,10mar05,act  remove phys block size parameter to hrfsDevCreate
01h,09mar05,pcm  added hrfsFormat() and hrfsFormatLibInit()
01g,08mar05,jlk  hrfsDevCreate() uses a device_t now for the XBD
01f,08mar05,pcm  added hrfsDevLibInit() 
01e,08mar05,jlk  added another errno
01d,21feb05,jlk  added an errno
01c,01feb05,pcm  fixed compiler errors
01b,01feb05,pcm  added HRFS time routines
01a,24jan05,jlk  written
*/

#ifndef __INChrfsLib
#define __INChrfsLib

/* includes */

#include "vxWorks.h"

#include "ioLib.h"
#include "time.h"
#include "drv/xbd/xbd.h"

/* defines */
#define TM_BLK_FSB 0
#define TM_BLK_FIB 1

/* Identifiers and version numbers */
#define HRFS_ID_STRING     "WR_HRFS"

#define HRFS_MAJOR_VERSION1  0x01
#define HRFS_MAJOR_VERSION   HRFS_MAJOR_VERSION1

#define HRFS_MINOR_VERSION1  0x01
#define HRFS_MINOR_VERSION2  0x02
#define HRFS_MINOR_VERSION   HRFS_MINOR_VERSION2

#define HRFS_INODE_VERSION1  0x00
#define HRFS_INODE_VERSION2  0x01
#define HRFS_INODE_VERSION   HRFS_INODE_VERSION2

/* The maximum chars in a path, excluding EOS */
#define HRFS_MAX_PATH_LEN         PATH_MAX
/* The maximum chars in a file name, including EOS */
#define HRFS_MAX_FILENAME_LEN     (251)
/* Defines a character that is not allowed in file/directory name */
#define HRFS_BAD_CHAR    (':')
/* Defines how deeply nested subdirs can be */
#define HRFS_MAX_DIRECTORY_DEPTH  MAX_DIRNAMES
/* Defines how many hard links to a file can exist */
#define HRFS_MAX_HARD_LINKS       ((linkCount_t) -1)

/* Limits for the logical block sizes */

/* The minium supported logical block size in bytes */
#define HRFS_MIN_LOGICAL_BLK_SIZE     512
/* The minium supported logical block size in bytes as a power of 2 */
#define HRFS_MIN_LOGICAL_BLK_SIZE_2   9
/* The maximum supported logical block size in bytes */
#define HRFS_MAX_LOGICAL_BLK_SIZE     32768
/* The maximum supported logical block size in bytes as a power of 2 */
#define HRFS_MAX_LOGICAL_BLK_SIZE_2   15

/* Limits for the physical block sizes */

/* The minium supported logical block size in bytes */
#define HRFS_MIN_PHYSICAL_BLK_SIZE    512
/* The minium supported logical block size in bytes as a power of 2 */
#define HRFS_MIN_PHYSICAL_BLK_SIZE_2  9
/* The maximum supported logical block size in bytes */
#define HRFS_MAX_PHYSICAL_BLK_SIZE    HRFS_MAX_LOGICAL_BLK_SIZE
/* The maximum supported logical block size in bytes as a power of 2 */
#define HRFS_MAX_PHYSICAL_BLK_SIZE_2  HRFS_MAX_LOGICAL_BLK_SIZE_2


#define HRFS_DEV_MIN_BUFFERS   16  /* minimum # of buffers for HRFS devices */

/* error codes */

#define S_hrfsLib_DISK_FULL                (M_hrfsLib |  1)
#define S_hrfsLib_OUT_OF_INODES            (M_hrfsLib |  2)
#define S_hrfsLib_INVALID_TMR              (M_hrfsLib |  3)
#define S_hrfsLib_UNKNOWN_VOLUME_FORMAT    (M_hrfsLib |  4)
#define S_hrfsLib_BLOCK_NOT_FOUND          (M_hrfsLib |  5)
#define S_hrfsLib_INODE_JOURNAL_FULL       (M_hrfsLib |  6)
#define S_hrfsLib_PROTECT_BEGIN_FAIL       (M_hrfsLib |  7)

/* flags used by hrfsChkDsk */

#define HRFS_CHKDSK_FLAG_NONE			0x00
#define HRFS_CHKDSK_FLAG_UPGRADE		0x01
#define HRFS_CHKDSK_FLAG_REWIND_INODE_JOURNAL	0x02

/* typedefs */

typedef struct hrfs_dev *           HRFS_DEV_ID;
typedef struct hrfs_volume_desc *   HRFS_VOLUME_DESC_ID;

/* forward declarations */

#ifdef __cplusplus
extern "C" {
#endif

extern STATUS (*hrfsFmtRtn)( char *path, UINT64 diskSize, UINT32 blockSize, 
                             UINT32 files, UINT32 majorVer, UINT32 minorVer,
			     UINT32 options); 

extern STATUS      hrfsFormatLibInit (void);
extern STATUS      hrfsFormatFd    (int fd, UINT64 diskSize,
				    UINT32 blkSize, UINT32 numInodes);
extern STATUS      hrfsAdvFormatFd (int fd, UINT64 diskSize,
				    UINT32 blkSize, UINT32 numInodes,
				    UINT32 majorVersion, UINT32 minorVersion,
				    UINT32 options);
extern STATUS      hrfsFormat	 (char *path, UINT64 diskSize,
				  UINT32 blkSize, UINT32 numInodes);
extern STATUS      hrfsAdvFormat (char *path, UINT64 diskSize,
				  UINT32 blkSize, UINT32 numInodes,
				  UINT32 majorVersion, UINT32 minorVersion,
				  UINT32 options);

extern STATUS      hrfsDevLibInit (int _maxBufs, int _maxFiles);
extern HRFS_DEV_ID hrfsDevCreate (char * _pDevName, device_t _xbd, int _numBufs,
                                  int _maxFiles);
extern STATUS      hrfsDevCreate2 (device_t  xbdId, char * pDevName);
extern STATUS      hrfsDevDelete (HRFS_DEV_ID hrfsDevId);
extern int         hrfsDiskProbe (device_t  xbdDevice);

extern STATUS      hrfsChkDsk (char *path, int verbLevel, int flag);


#ifdef __cplusplus
    }
#endif

#endif /* __INChrfsLib */


/* dosFsCommon.h - DOS file system header file (common elements) */

/* Copyright 1999-2004, 2009 Wind River Systems, Inc. */

/*
modification history
-------------------- 
01d,18jun09,zly  added macro PRINT_MSG 
01c,17aug06,kuo  added macro DOS_CHK_VERB_MASK
01b,02may04,jkf  fixed SPR#83487, DOS_MAX_DIR_LEVELS to 124
01a,09apr04,dat  written (from dosFsLib.h ver 01q)
*/

/*
These are the common DOS file system macros needed for both
kernel and RTP space.  (This file is referenced as usrFsLib.h from
RTP space).
*/

#ifndef __INCdosFsCommonh
#define __INCdosFsCommonh

#ifdef __cplusplus
extern "C" {
#endif


/* defines */
#define	DOS_FS_COMPAT	/* enable definition for backwards compatibility */

/* dosDevCreateOptions - check disk levels */

#define	DOS_CHK_FLAGS_MASK	0x000000ff /* all "control" flags in here */
#define DOS_CHK_ONLY		0x00000001
#define DOS_CHK_REPAIR		0x00000002
#define DOS_CHK_NONE		0x00000004
#define	DOS_CHK_FORCE		0x00000008 /* force chkdsk even if clean */
#define DOS_CHK_VERB_0		0x0000ff00 /* verbosity level/flags */
#define DOS_CHK_VERB_SILENT	DOS_CHK_VERB_0
#define DOS_CHK_VERB_1		0x00000100
#define DOS_CHK_VERB_2		0x00000200
#define DOS_CHK_VERB_MASK       0x0000ff00

/* misc max definitions */
#define DOS_MAX_DIR_LEVELS      124     /* max expected directory levels */
#define DOS_VOL_LABEL_LEN 	11	/* length of volume label */

/* ioctl FIOCHKDSK - check disk levels */

#define CHK_ONLY	1
#define CHK_REPAIR	2

/* additional open() flags */

#define DOS_O_CONTIG_CHK	0x10000	/* check file for contiguity */
#define DOS_O_CASENS		0x20000	/* case-sensitive file lookup */

/* File attribute byte values */

#define DOS_ATTR_RDONLY         0x01            /* read-only file */
#define DOS_ATTR_HIDDEN         0x02            /* hidden file */
#define DOS_ATTR_SYSTEM         0x04            /* system file */
#define DOS_ATTR_VOL_LABEL      0x08            /* volume label (not a file) */
#define DOS_ATTR_DIRECTORY      0x10            /* entry is a sub-directory */
#define DOS_ATTR_ARCHIVE        0x20            /* file subject to archiving */

/* error codes */
/*
 * The codes which are defined with ERRNO_PX_FLAG can be mapped
 * to POSIX error codes:
 * if (errno & ERRNO_PX_FLAG) errno &= 0x7fff ;
 */

#define S_dosFsLib_32BIT_OVERFLOW		(M_dosFsLib |  1)
#define S_dosFsLib_DISK_FULL			(M_dosFsLib |  2)
#define S_dosFsLib_FILE_NOT_FOUND		(M_dosFsLib |  3)
#define S_dosFsLib_NO_FREE_FILE_DESCRIPTORS 	(M_dosFsLib |  4)
#define S_dosFsLib_NOT_FILE			(M_dosFsLib |  5)
#define S_dosFsLib_NOT_SAME_VOLUME	        (M_dosFsLib |  6)
#define S_dosFsLib_NOT_DIRECTORY		(M_dosFsLib |  7)
#define S_dosFsLib_DIR_NOT_EMPTY		(M_dosFsLib |  8)
#define S_dosFsLib_FILE_EXISTS			(M_dosFsLib |  9)
#define S_dosFsLib_INVALID_PARAMETER		(M_dosFsLib | 10)
#define S_dosFsLib_NAME_TOO_LONG		(M_dosFsLib | 11)
#define S_dosFsLib_UNSUPPORTED			(M_dosFsLib | 12)
#define S_dosFsLib_VOLUME_NOT_AVAILABLE		(M_dosFsLib | 13)
#define S_dosFsLib_INVALID_NUMBER_OF_BYTES	(M_dosFsLib | 14)
#define S_dosFsLib_ILLEGAL_NAME			(M_dosFsLib | 15)
#define S_dosFsLib_CANT_DEL_ROOT		(M_dosFsLib | 16)
#define S_dosFsLib_READ_ONLY			(M_dosFsLib | 17)
#define S_dosFsLib_ROOT_DIR_FULL		(M_dosFsLib | 18)
#define S_dosFsLib_NO_LABEL			(M_dosFsLib | 19)
#define S_dosFsLib_NO_CONTIG_SPACE		(M_dosFsLib | 20)
#define S_dosFsLib_FD_OBSOLETE			(M_dosFsLib | 21)
#define S_dosFsLib_DELETED			(M_dosFsLib | 22)
#define S_dosFsLib_INTERNAL_ERROR		(M_dosFsLib | 23)
#define S_dosFsLib_WRITE_ONLY			(M_dosFsLib | 24)
#define S_dosFsLib_ILLEGAL_PATH			(M_dosFsLib | 25)
#define S_dosFsLib_ACCESS_BEYOND_EOF		(M_dosFsLib | 26)
#define S_dosFsLib_DIR_READ_ONLY		(M_dosFsLib | 27)
#define S_dosFsLib_UNKNOWN_VOLUME_FORMAT	(M_dosFsLib | 28)
#define S_dosFsLib_ILLEGAL_CLUSTER_NUMBER	(M_dosFsLib | 29)

/* 
 * user`s printing message level :
 * 0  - print nothing 
 * 1  - print message at level-1 
 * >1 - for future extension 
 */

IMPORT int dosFsMsgLevel;

/* 
 *Classification of message
 *By default all message at level-1 
 */

#define CLSMSG_NORMAL 1


/*
 * print message according to dosFsMsgLevel (DOSFS_PRTMSG_LEVEL)
 * class : default value is CLSMSG_NORMAL
 */

#define PRINT_MSG(class, fmt, ...)                  \
    do {                                            \
        if ((dosFsMsgLevel) != 0) {                   \
            if ((dosFsMsgLevel) <= (class)) {         \
                    printf((fmt),##__VA_ARGS__);    \
            }                                       \
        }                                           \
    } while (0)

/* macros */

/* typedefs */

/* interface functions prototypes */

#ifdef __cplusplus
    }
#endif

#endif /* __INCdosFsCommonh */

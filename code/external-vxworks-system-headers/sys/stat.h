/* stat.h - POSIX definitions for obtaining file characteristics */

/* Copyright 1984-1995, 2001-2006, 2008-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
01v,05mar10,pcs  Add S_IFDEVMEM & S_TYPEISDEVMEM.
01u,09sep08,lyc  fix WIND00132892
01t,10may06,pcm  undid changes from version 01s
01s,05may06,pcm  updated struct stat as ino_t changed to 64 bits
01r,06feb06,jlk  updated struct stat for POSIX. Added S_ISLNK macro
01q,23jan06,act  add fchmod
01p,25oct05,zl   added S_TYPEISMQ(), S_TYPEISSEM() S_TYPEISSHM() macros.
01o,09aug05,hya  added chmod().
01n,26jan05,jlk  SPR 105359 - added const to stat() for POSIX compliance
01m,23sep01,jkf  added const to mkdir
01l,28mar95,kdl  removed obsolete date/time fields from stat structure.
01k,19apr94,jmm  added support for file system stat ({f}statfs())
01j,22sep92,rrr  added support for c++
01i,18sep92,smb  added mkdir prototype
01h,26may92,rrr  the tree shuffle
01g,04oct91,rrr  passed through the ansification filter
		  -fixed #else and #endif
		  -changed TINY and UTINY to INT8 and UINT8
		  -changed copyright notice
01f,10jun91.del  added pragma for gnu960 alignment.
01e,05oct90,dnw  added fstat() and stat() declarations.
01d,05oct90,shl  added copyright notice.
                 made #endif ANSI style.
01c,03oct90,kdl  changed comments.
01b,05may90,llk  added st_blksize and st_blocks fields so that net directory
		   can use stat structure.  Coincided with removal of
		   h/net/stat.h.
01a,30apr90,kdl  written.
*/

#ifndef __INCstath
#define __INCstath

/*#include <time.h>*/  /* For time_t */

#ifdef __cplusplus
extern "C" {
#endif

#define	TIME	ULONG		/* type for file time fields */


struct	stat_old
    {
    ULONG	st_dev;		/* device ID number */
    ULONG	st_ino;		/* file serial number */
    USHORT	st_mode;	/* file mode (see below) */
    short	st_nlink;	/* number of links to file */
    short	st_uid;		/* user ID of file's owner */
    short	st_gid;		/* group ID of file's group */
    ULONG	st_rdev;	/* device ID, only if special file */
    ULONG	st_size;	/* size of file, in bytes */
    TIME	st_atime;	/* time of last access */
    TIME	st_mtime;	/* time of last modification */
    TIME	st_ctime;	/* time of last change of file status */
    long	st_blksize;
    long	st_blocks;
    UINT8	st_attrib;	/* file attribute byte (dosFs only) */
    int		reserved1;	/* reserved for future use */
    int		reserved2;	/* reserved for future use */
    int		reserved3;	/* reserved for future use */
    int		reserved4;	/* reserved for future use */
    int		reserved5;	/* reserved for future use */
    int		reserved6;	/* reserved for future use */
    };

struct stat
    {
    dev_t       st_dev;     /* Device ID number */
    ino_t       st_ino;     /* File serial number */
    mode_t      st_mode;    /* Mode of file */
    nlink_t     st_nlink;   /* Number of hard links to file */
    uid_t       st_uid;     /* User ID of file */
    gid_t       st_gid;     /* Group ID of file */
    dev_t       st_rdev;    /* Device ID if special file */
    INT64       st_size;    /* File size in bytes */
    time_t      st_atime;   /* Time of last access */
    time_t      st_mtime;   /* Time of last modification */
    time_t      st_ctime;   /* Time of last status change */
    blksize_t   st_blksize; /* File system block size */
    blkcnt_t    st_blocks;  /* Number of blocks containing file */
    UINT8       st_attrib;  /* DOSFS only - file attributes */
    int         st_reserved1;  /* reserved for future use */
    int         st_reserved2;  /* reserved for future use */
    int         st_reserved3;  /* reserved for future use */
    int         st_reserved4;  /* reserved for future use */
    };

typedef struct
    {
    long val[2];                    /* file system id type */
    } fsid_t;

/*
 * file system statistics
 */
struct statfs
    {
    long f_type;                    /* type of info, zero for now */
    long f_bsize;                   /* fundamental file system block size */
    long f_blocks;                  /* total blocks in file system */
    long f_bfree;                   /* free block in fs */
    long f_bavail;                  /* free blocks avail to non-superuser */
    long f_files;                   /* total file nodes in file system */
    long f_ffree;                   /* free file nodes in fs */
    fsid_t f_fsid;                  /* file system id */
    long f_spare[7];                /* spare for later */
    };

/*
 * file system statistics
 */
struct statfs64
    {
    long f_type;                    /* type of info, zero for now */
    long f_bsize;                   /* fundamental file system block size */
    INT64 f_blocks;                  /* total blocks in file system */
    INT64 f_bfree;                   /* free block in fs */
    INT64 f_bavail;                  /* free blocks avail to non-superuser */
    INT64 f_files;                   /* total file nodes in file system */
    INT64 f_ffree;                   /* free file nodes in fs */
    fsid_t f_fsid;                  /* file system id */
    long f_spare[7];                /* spare for later */
    };


/* File mode (st_mode) bit masks */

#define	S_IFMT	 0xf000		/* file type field */
#define	S_IFIFO	 0x1000		/*  fifo */
#define	S_IFCHR	 0x2000		/*  character special */
#define	S_IFDIR	 0x4000		/*  directory */
#define	S_IFBLK	 0x6000		/*  block special */
#define	S_IFREG	 0x8000		/*  regular */
#define	S_IFLNK	 0xa000		/*  symbolic link */
#define	S_IFSHM  0xb000		/*  shared memory object */
#define	S_IFDEVMEM  0xd000	/*  device memory object */
#define	S_IFSOCK 0xc000		/*  socket */

#define	S_ISUID	 0x0800		/* set user id on execution */
#define	S_ISGID	 0x0400		/* set group id on execution */

#define	S_IRUSR  0x0100		/* read permission, owner */
#define	S_IWUSR  0x0080		/* write permission, owner */
#define	S_IXUSR  0x0040		/* execute/search permission, owner */
#define	S_IRWXU	 0x01c0		/* read/write/execute permission, owner */

#define	S_IRGRP  0x0020		/* read permission, group */
#define	S_IWGRP  0x0010		/* write permission, group */
#define	S_IXGRP  0x0008		/* execute/search permission, group */
#define	S_IRWXG	 0x0038		/* read/write/execute permission, group */

#define	S_IROTH  0x0004		/* read permission, other */
#define	S_IWOTH  0x0002		/* write permission, other */
#define	S_IXOTH  0x0001		/* execute/search permission, other */
#define	S_IRWXO	 0x0007		/* read/write/execute permission, other */


/* File type test macros */

#define	S_ISDIR(mode)	((mode & S_IFMT) == S_IFDIR)	/* directory */
#define	S_ISCHR(mode)	((mode & S_IFMT) == S_IFCHR)	/* character special */
#define	S_ISBLK(mode)	((mode & S_IFMT) == S_IFBLK)	/* block special */
#define	S_ISREG(mode)	((mode & S_IFMT) == S_IFREG)	/* regular file */
#define	S_ISFIFO(mode)	((mode & S_IFMT) == S_IFIFO)	/* fifo special */
#define	S_ISLNK(mode)	((mode & S_IFLNK) == S_IFLNK)	/* symbolic link special */

/* 
 * POSIX.1b objects.  The macros that evaluate to zero (false) are 
 * defined so that they provide syntax checking for the parameter.
 */

#define S_TYPEISMQ(buf)     ((buf)->st_mode - (buf)->st_mode)
#define S_TYPEISSEM(buf)    ((buf)->st_mode - (buf)->st_mode)
#define S_TYPEISSHM(buf)    (((buf)->st_mode & S_IFMT) == S_IFSHM)
#define S_TYPEISDEVMEM(buf) (((buf)->st_mode & S_IFMT) == S_IFDEVMEM)

/* function declarations */

extern    STATUS       mkdir (const char *_dirName);
extern	  STATUS       fstat (int fd, struct stat *_pStat);
extern	  STATUS       stat (const char *_name, struct stat *_pStat);
extern	  STATUS       fstatfs (int _fd, struct statfs *_pStat);
extern	  STATUS       statfs (char *_name, struct statfs *_pStat);
extern	  STATUS       fstatfs64 (int _fd, struct statfs64 *_pStat);
extern	  STATUS       statfs64 (char *_name, struct statfs64 *_pStat);
extern	  int	       chmod (const char *_path, mode_t _mode);
extern	  int	       fchmod (int _fd, mode_t _mode);

#ifdef __cplusplus
}
#endif

#endif /* __INCstath */

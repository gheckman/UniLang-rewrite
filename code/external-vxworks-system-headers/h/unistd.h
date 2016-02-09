/* unistd.h - unix standard library header file */

/* Copyright 1991-1994, 2000-2001, 2003-2006, 2009-2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
02z,12sep11,cww  deprecate alarm (WIND00270279)
02y,29apr10,pad  Moved extern C statement after include statements.
02x,24mar09,hps  LP64 support
02w,31aug06,mwv  move kernel definitions of read(),write(),close() 
                 to unistd.h (WIND00038902)
02v,30mar06,jlk  SPR 119715. Fix prototype for getcwd()
02u,26jan06,mil  Removed define of _POSIX_VERSION and _POSIX_C_SOURCE.
02t,02aug05,pad  Removed user-side elements, now useless since this file is no
                 longer shared. Updated copyright information.
02s,04jul05,hya  Added more _POSIX macros.
02r,18apr05,pcm  moved _PC_xxx macros for pathconf() from hrFsLib.h to here
02q,18apr05,hya  Added file system posix prototypes.
02p,17mar05,dlk  Make 'place' a member of the GETOPT type.
02o,25feb05,niq  Added definitions for reentrant version of getopt
02n,06oct04,pad  Added declaration of the environ array for the user side.
02m,01oct04,yvp  Change lseek args to use off_t (for Posix).
02l,13sep04,yvp  Added prorotype for _exit().
02k,09jun04,kk   added getpid() & getppid() prototypes SPR#98109
02j,29mar04,job  Added getopt prototype. Removed non-STDC function prototypes
02i,08dec03,dat  adding const to unlink and chdir
02h,20jul00,jgn  add POSIX version information + removed old style prototypes
02g,24sep01,jkf  added const to rmdir()
02f,19aug94,ism  added getcwd() prototypes (SPR #3536)
02e,12nov93,dvs  added prototype for ftruncate.
02d,08feb93,smb  changed int to size_t in protype for read() and write()
02c,22sep92,rrr  added support for c++
02b,18sep92,smb  added the rmdir prototype.
02a,04jul92,jcf  cleaned up.
01c,26may92,rrr  the tree shuffle
01b,05dec91,rrr  added SEEK_ macros (was in ioLib.h)
01a,19nov91,rrr  written.
*/

#ifndef __INCunistdh
#define __INCunistdh

#include <vxWorks.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef SEEK_SET
#define SEEK_SET    0           /* absolute offset, was L_SET */
#define SEEK_CUR    1           /* relative to current offset, was L_INCR */
#define SEEK_END    2           /* relative to end of file, was L_XTND */
#endif

/* Symbolic constants for the "access" routine: */
#define R_OK        4           /* Test for Read permission */
#define W_OK        2           /* Test for Write permission */
#define X_OK        1           /* Test for eXecute permission */
#define F_OK        0           /* Test for existence of File */

/* command names for POSIX pathconf, fpathconf */
#define _PC_2_SYMLINKS          1
#define _PC_ALLOC_SIZE_MIN      2
#define _PC_ASYNC_IO            3
#define _PC_CHOWN_RESTRICTED    4
#define _PC_FILESIZEBITS        5
#define _PC_LINK_MAX            6
#define _PC_MAX_CANON           7
#define _PC_MAX_INPUT           8
#define _PC_NAME_MAX            9
#define _PC_NO_TRUNC            10
#define _PC_PATH_MAX            11
#define _PC_PIPE_BUF            12
#define _PC_PRIO_IO             13
#define _PC_REC_INCR_XFER_SIZE  14
#define _PC_REC_MAX_XFER_SIZE   15
#define _PC_REC_MIN_XFER_SIZE   16
#define _PC_REC_XFER_ALIGN      17
#define _PC_SYMLINK_MAX         18
#define _PC_SYNC_IO             19
#define _PC_VDISABLE            20

/*
 * compile-time symbolic constants,
 */
#define _POSIX_ASYNC_IO         0
#define _POSIX_PRIO_IO          0
#define _POSIX_SYNC_IO          0
#define _POSIX_NO_TRUNC         0
#define _POSIX_SYNCHRONIZED_IO  0

extern char *optarg;
extern int optind, opterr, optopt;
extern int optreset;

struct getopt_s
    {
    int     opterr;     /* if error message should be printed */
    int     optind;     /* index into parent argv vector */
    int     optopt;     /* character checked for validity */
    int     optreset;   /* reset getopt */
    char *  optarg;     /* argument associated with option */
    char *  place;
    };

typedef struct getopt_s GETOPT;
typedef struct getopt_s * GETOPT_ID;

/* function declarations */

extern STATUS       unlink	(const char *name);
extern STATUS       link	(const char *, const char *);
extern STATUS       fsync	(int);
extern STATUS       fdatasync	(int);
extern STATUS       rename	(const char *, const char *);
extern long         fpathconf	(int, int);
extern long         pathconf	(const char *, int);
extern STATUS       access	(const char *, int);
extern int          close	(int fd);
extern ssize_t      read	(int fd, char * buffer, size_t maxbytes);
extern ssize_t      write	(int fd, char * buffer, size_t nbytes);
extern off_t        lseek	(int fd, off_t offset, int whence);
extern STATUS       chdir	(const char *pathname);
extern STATUS       pause	(void);
extern BOOL         isatty	(int fd);
extern STATUS       rmdir	(const char *dirName);
extern char *       getcwd	(char *buffer, size_t size);
extern int          ftruncate	(int fildes, off_t length);
extern unsigned int sleep	(unsigned int);
extern unsigned int alarm	(unsigned int) \
		_WRS_DEPRECATED ("please use timer_create() "
				 "and timer_settime() instead");
extern int          getopt	(int, char * const [], const char *);
extern int          getopt_r	(int, char * const [], const char *,
				 GETOPT_ID pGetOpt);
extern void         getoptInit	(GETOPT_ID pArg);
extern STATUS       getOptServ	(char * ParamString, const char * progName,
                                int * argc, char * argvloc[], int argvlen);

extern RTP_ID       getpid	(void); /* for porting from user to kernel */

#ifdef __cplusplus
}
#endif

#endif /* __INCunistdh */

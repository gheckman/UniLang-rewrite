/* iosLibP.h - private I/O system header file */

/*
 * Copyright (c) 1992-2011, 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
02m,13oct14,jpb  VXW6-83050: Updated prototype of iosRtpFdInvalid()
02l,22apr11,jxu  Added support for kernel per-task CWD feature (WIND00131452).
02k,09nov10,jxu  Added _func_netChDirByName.
02j,25sep10,jxu  Added _func_ioTaskStdSet, _func_ioGlobalStdGet and
		 _func_consoleOut.
02i,31aug10,jxu  Moved IOS related hooks from funcBind.c to this file.
02h,29apr10,pad  Moved extern C statement after include statements.
02g,23feb10,zl   replaced off_t64 with off64_t
02f,27jan10,lxj  added iosRtpTableSizeSet()
02e,09nov09,lyc  remove error for merge
02d,12jun09,lxj  WIND00161785 - remove references of setLib API from core IO
                 libraries
02c,22apr09,hps  LP64: no need drv_val_t any more
02b,21apr09,hps  LP64: move drv_val_t to private header iosLibP.h
02a,16mar09,hps  LP64 support
01z,27aug08,jpb  Renamed VSB header file
01y,24jun08,jpb  Added include path for kernel configurations options set in
                 vsb.  Renamed _WRS_VX_SMP to _WRS_CONFIG_SMP.
01x,01aug07,act  io footprint work (from pcm)
01w,13nov06,act  SMP: per-fd refCnt uses atomics
01v,30mar06,act  an FD_CNTRL entry should not be considered "valid"
                 (FD_ENTRY_VALID macro); make iosRtpFdUnmap smarter
01u,14feb06,md   added flags member to FD_ENTRY
01t,07feb06,zl   added _func_ftruncateMmanHook in iosIoctlInLine()
01s,07feb06,jlk  Added iosRtpIoTableSizeSet() and iosRtpIoTableSizeGet()
01r,21jul05,tcr  add System Viewer instrumentation
01q,13jul05,hya  made removability change.
01p,13apr05,hya  removed iosFdEntryXXX call from iosXXXInLine.
01o,01mar05,hya  change for user memory validation in ioctl
01n,24jan05,aeg  added prototypes for iosRtpFdReserve, etc. (SPR #106381).
01m,28apr04,dat  remove iosCloseInLine(), 96826
01l,27feb04,dat  merging iosLib with rtpIoLib
01k,17feb04,dat  separating public/private APIs
01j,05jan04,dat  92873, improved test for valid FD_ENTRY
01i,21nov03,dat  adding new refCnt macros, removing obsolete, auxValue,
                 and reserved fields from FD_ENTRY.
01h,11nov03,dat  refactored routines
01g,27oct03,dat  Adding RTP ios support, new fields
01f,20jun03,ymz  added iosObjIdFdGet and iosFdObjIdGet prototype.
01e,02apr03,ymz  objectized FDs.
01d,22dec98,lrn  add more fields to FD_ENTRY, added obsolete state
01c,09nov93,rrr  added aio support
01b,22sep92,rrr  added support for c++
01a,23aug92,jcf  written.
*/

#ifndef __INCiosLibPh
#define __INCiosLibPh

#include <vsbConfig.h>
#include <private/classLibP.h>
#include <private/objLibP.h>
#include <private/kernelBaseLibP.h>
#include <iosLib.h>
#include <dllLib.h>
#include <errnoLib.h>
#include <poolLib.h>
#include <taskLib.h>            /* for taskIdCurrent */
#ifdef _WRS_CONFIG_SMP
#include <vxAtomicLib.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* typedefs */

typedef struct drvEntry         /* DRV_ENTRY - entries in driver jump table */
    {
    DRV_CREATE_PTR      de_create;
    DRV_REMOVE_PTR      de_delete;
    DRV_OPEN_PTR        de_open;
    DRV_CLOSE_PTR       de_close;
    DRV_READ_PTR        de_read;
    DRV_WRITE_PTR       de_write;
    DRV_IOCTL_PTR       de_ioctl;
    DRV_IOCTL_PTR       de_ioctlMemValidate;
    BOOL                de_inuse;
    } DRV_ENTRY;

/* DEV_HDR structure is in ioLib.h */

typedef struct fdObjEntry       /* FD_ENTRY - entries in file table */
    {
    OBJ_CORE    objCore;        /* FDs are objects */
    DEV_HDR *   pDevHdr;        /* device header for this file */
    void *      value;          /* driver open file cookie, maybe reloaded */
    void *      driverCookie;   /* driver open file cookie */
#ifdef _WRS_CONFIG_SMP
    atomic_t    refCnt;         /* reference count */
#else
    volatile int    refCnt;     /* reference count */
#endif
    int         flags;          /* fd flags */
    DRV_ENTRY * pDrvEntry;      /* dev driver, remove support, invalidated fd drv */
    DRV_ENTRY * pDevDrvEntry;   /* device driver entry slot pointer */
    } FD_ENTRY;

typedef void (*FTRUNC_HOOK_FUNCPTR) (int fd, off64_t off);

typedef struct devClose         /* device close arguments */
    {
    DEV_HDR *   pDevHdr;        /* device header for close */
    BOOL        forceClose;     /* indicate force close or invalidated */
    } DEV_CLOSE;

typedef struct cwdInfo          /* task's private CWD info */
    {
    char *      pCwd;           /* pointer to cwd */
    size_t      cwdLen;         /* length of cwd buffer */ 
    } CWD_INFO;

/* macros */

/* values for driver to return */
#define DRV_VAL_OK          ((void *) 0)
#define DRV_VAL_ERROR       ((void *) -1)

#define fdClassId     (&fdClass)
#define fdInstClassId (&fdInstClass)

#define FD_RESERVED ((FD_ENTRY *) -1)
#define FD_CNTRL    ((FD_ENTRY *) -2)
#define FD_ENTRY_VALID(pFd) \
    ((pFd) != NULL && (pFd) != FD_RESERVED && (pFd) != FD_CNTRL)

/*
 * Most aspects of file descriptors are protected by a per-RTP lock,
 * but file descriptors can be shared across separate RTPs, so we
 * must atomically adjust these reference counts.
 */
#ifdef _WRS_CONFIG_SMP
#define FD_ENTRY_LINK(pFd)      vxAtomicInc(&(pFd)->refCnt)
#define FD_ENTRY_UNLINK(pFd)    vxAtomicDec(&(pFd)->refCnt)
#else
#define FD_ENTRY_LINK(pFd) \
    do { \
        TASK_LOCK (); \
        (pFd)->refCnt++; \
        TASK_UNLOCK (); \
    } while ((0))
#define FD_ENTRY_UNLINK(pFd) \
    do { \
        TASK_LOCK (); \
        (pFd)->refCnt--; \
        TASK_UNLOCK (); \
    } while ((0))
#endif

#define iosRtpFdUnmap(pRtp, fd) iosRtpFdUnmap2(pRtp, fd, 0)

/* To obtain current working directory and check if the CWD is 
 * private or global. 
 */

#ifdef _WRS_CONFIG_PERTASK_CWD

#define TASK_CWD_INFO(tid)                      \
    (                                           \
    (CWD_INFO *)(((WIND_TCB *)tid)->pCwdInfo)   \
    )

#define TASK_CWD_BUF(tid)                       \
    (                                           \
    TASK_CWD_INFO(tid)->pCwd                    \
    )

#define IS_CWD_PRIVATE(tid) (TASK_CWD_INFO(tid) != NULL)

#define CUR_WORK_DIR                            \
    (                                           \
    (IS_CWD_PRIVATE(taskIdCurrent)  ?           \
        TASK_CWD_BUF(taskIdCurrent) : CUR_RTP_ID->defPath)            \
    )   

#define CWD_BUF_LEN                             \
    (                                           \
    (IS_CWD_PRIVATE(taskIdCurrent)  ?           \
        TASK_CWD_INFO(taskIdCurrent)->cwdLen: CUR_RTP_ID->defPathLen) \
    )   

#else /* !_WRS_CONFIG_PERTASK_CWD */

#define IS_CWD_PRIVATE(tid) (FALSE) 
#define CUR_WORK_DIR     (CUR_RTP_ID->defPath) 

#endif /* _WRS_CONFIG_PERTASK_CWD */

/* We use iosLock to protect CWD, before change it to other lock, 
 * make sure that each reference to the global CWD are protected 
 * by the lock. 
 */

#define IOS_CWD_LOCK()   iosLock()
#define IOS_CWD_UNLOCK() iosUnlock()

/* conditional lock/unlock, no protection is needed for accessing 
 * current task's private CWD by itself. 
 */

#define IOS_CWD_LOCK_COND()                  \
    do {                                     \
        if (!IS_CWD_PRIVATE(taskIdCurrent))  \
            IOS_CWD_LOCK();                  \
    }while (0)

#define IOS_CWD_UNLOCK_COND()                \
    do {                                     \
        if (!IS_CWD_PRIVATE(taskIdCurrent))  \
            IOS_CWD_UNLOCK();                \
    }while (0)

/* variable declarations */

IMPORT OBJ_CLASS    fdClass;
IMPORT char         ioDefPath[];
IMPORT DL_LIST      iosDvList;
IMPORT int          iosMaxDrivers;
IMPORT DRV_ENTRY *  drvTable;
IMPORT int          iosMaxFiles;
IMPORT FD_ENTRY **  iosFdTable;
IMPORT POOL_ID      iosFdEntryPool;

IMPORT FTRUNC_HOOK_FUNCPTR _func_ftruncMmanHook;

/* functions that are available but not public */

IMPORT  int     iosObjIdFdGet (OBJ_ID objId);
IMPORT  OBJ_ID  iosFdObjIdGet (int fd);

/* Refactored routines to be more obj oriented these are PRIVATE */

IMPORT  int     iosKernelFdFind (void);
IMPORT  int     iosFdEntryIoctl (FD_ENTRY *, int cmd, _Vx_usr_arg_t arg, BOOL sc);
IMPORT  STATUS  iosFdEntrySet (FD_ENTRY *, DEV_HDR * pDevHdr,
                               const char * name, void * value);
IMPORT  FD_ENTRY *  iosFdEntryGet (void);
IMPORT  STATUS  iosFdEntryReturn (FD_ENTRY *);

IMPORT  STATUS  iosLock (void);
IMPORT  STATUS  iosUnlock (void);

IMPORT  STATUS  iosFdTableLock (RTP_ID pRtp);
IMPORT  STATUS  iosFdTableUnlock (RTP_ID pRtp);

IMPORT  int     iosRtpFdReserve (RTP_ID pRtp);
IMPORT  int     iosRtpFdReserveCntrl (RTP_ID pRtp);
IMPORT  int     iosRtpFdUnmap2 (RTP_ID pRtp, int fd, int flags);
IMPORT  STATUS  iosRtpFdSetup (RTP_ID pRtp, FD_ENTRY * pFdEntry, int  fd,
                               DEV_HDR * pDevHdr, const char * name, void * value);
IMPORT  STATUS  iosRtpDefPathSet (RTP_ID pRtp, const char * pBuff);
IMPORT  STATUS  iosRtpDefPathGet (RTP_ID pRtp, char * pBuff, size_t length);
IMPORT  STATUS  iosRtpFdEntryMap (RTP_ID pRtp, int fd, FD_ENTRY * pFdEntry);
IMPORT  size_t  iosRtpFdTableSizeGet (RTP_ID pRtp);
IMPORT  STATUS  iosRtpTableSizeSet(RTP_ID pRtp, size_t newSize);

#ifdef _WRS_CONFIG_PERTASK_CWD
IMPORT  STATUS  iosTaskCwdGet (TASK_ID taskId, char *pBuff, size_t length);
IMPORT  STATUS  iosTaskCwdSet (TASK_ID taskId, const char *pBuff);
#endif /* _WRS_CONFIG_PERTASK_CWD */

IMPORT  void    iosDrvInit (DRV_ENTRY * drvTable, int nullDrvNum);

/* Routines that used to be in iosLib.h, now 'private' */

extern int      iosFdNew (DEV_HDR * pDevHdr, const char * name, void * value);
extern void *   iosFdDrvValue (int fd, int drvNum);

IMPORT void *   iosCreate (DEV_HDR * pDevHdr, const char * fileName, int mode);
IMPORT void *   iosOpen (DEV_HDR * pDevHdr, const char * fileName,
                         int flags, int mode);
IMPORT int      iosDelete (DEV_HDR * pDevHdr, const char * fileName);
IMPORT int      iosClose (int fd);
IMPORT ssize_t  iosRead (int fd, char * buffer, size_t maxbytes);
IMPORT ssize_t  iosWrite (int fd, char * buffer, size_t nbytes);
IMPORT int      iosIoctl (int fd, int function, _Vx_usr_arg_t arg);
IMPORT int      iosIoctlInternal (int fd, int function,
                                  _Vx_usr_arg_t arg, BOOL syscall);

IMPORT STATUS   iosFdSet (int fd, DEV_HDR * pDevHdr, const char * name, void * value);

IMPORT FD_ENTRY *   iosFdMap (int fd);
extern BOOL     iosRtpDevCloseOrInvalidate (RTP_ID pRtp, DEV_CLOSE * pDevClose);
extern STATUS   iosDrvIoctlMemValSet (int drvnum, DRV_IOCTL_PTR pIoctlMemVal);
extern int      iosDrvIoctl (int drvNum, int function, _Vx_usr_arg_t arg);
extern size_t   iosRtpIoTableSizeGet (RTP_ID pRtp);
extern STATUS   iosRtpIoTableSizeSet (RTP_ID pRtp, size_t newSize);

extern STATUS   ioDefPathValidate (const char * pBuff);

extern STATUS   iosRtpFdInvalid (RTP_ID pRtp, DEV_HDR *pDev);
extern void *   iosFdValue (int fd)
        _WRS_DEPRECATED("use iosFdDrvValue instead");

extern DEV_HDR * iosDevMatch (const char * name);

/* APIs that no longer exist */

IMPORT VOIDFUNCPTR  iosFdNewHookRtn _WRS_DEPRECATED("no longer exists");
IMPORT VOIDFUNCPTR  iosFdFreeHookRtn _WRS_DEPRECATED("no longer exists");

/* Hooks for IO subsystem */

extern size_t (*_func_iosRtpIoTableSizeGet)	(RTP_ID pRtp);

extern STATUS (*_func_iosRtpIoTableSizeSet)	(RTP_ID pRtp, size_t newSize);

extern STATUS (*_func_ioTaskStdSet)	(TASK_ID taskId, int stdFd, 
					 int newFd);              

extern int	(*_func_ioGlobalStdGet)	(int stdFd);

extern ssize_t	(*_func_consoleOut)	(int fd, char* buf, size_t len);

extern STATUS (* _func_netChDirByName) (const char* dirName);

#ifdef __cplusplus
}
#endif

#endif /* __INCiosLibPh */

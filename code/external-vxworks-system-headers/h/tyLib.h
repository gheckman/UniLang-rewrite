/* tyLib.h - tty handler support library header */

/* Copyright 1984-2010, 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
03s,28jan15,jpb  Added new flag to keep track of passing the threshold.
                 (VXW6-83684)
03r,27jul10,jxu  LP64: removed usage of FUNCPTR.
03q,08jun10,jxu  LP64: added TY_ABORT_PTR for removing usage of FUNCPTR.
03p,29apr10,pad  Moved extern C statement after include statements.
03o,14oct09,lyc  LP64: change tyIoctl() interface
03n,20mar09,lyc  LP64 support
03m,24sep08,vhe  Added tyAbortFuncGet() to solve CQ:WIND00113428
03l,08jun07,jlk  more SMP work.
03k,20dec06,h_k  updated for SMP.
03j,14aug06,jlk  Fix WIND00061854: Added flags field to TY_DEV struct
03i,10nov05,md   port SPR 110998, added tyEOFGet
03h,10may04,dat  SPR 70498, change canceled flag to a counter
03g,07apr04,dat  merge from AE for 88437
03f,20jun03,bpn  added tyAbortGet() prototype.
03e,29jan00,dat  added threshold values and xoff funcptr (SPR 20978)
03d,11nov98,aeg  added tyDevTerminate().
03c,08may97,db   added numOpen entry to TY_DEV structure(SPR #7637).
03b,22sep92,rrr  added support for c++
03a,04jul92,jcf  cleaned up.
02u,26may92,rrr  the tree shuffle
02t,04oct91,rrr  passed through the ansification filter
                  -changed VOID to void
                  -changed copyright notice
02s,11jul91,jwt  removed divisible bit-field operations in TY_DEV structure.
02r,05oct90,shl  added ANSI function prototypes.
                 made #endif ANSI style.
                 added copyright notice.
02q,07aug90,shl  added function declarations comment.
02p,26jun90,jcf  embedded the TY_DEV semaphores.
02o,12may90,gae  added IMPORTs of ty{Read,Write,ITx,IRd}.
                 removed unused wdog.  changed UTINY to UINT8.
02n,29mar90,rdc  reworked to lower interrupt latency.
02m,16mar90,rdc  added select support.
02l,27jul89,hjb  added protoHook and protoArg to TY_DEV.
02k,18nov88,dnw  removed NOT_GENERIC stuff.
02j,04may88,jcf  changed SEMAPHORE to SEM_ID.
02i,15jun87,ecs  added canceled to rdState & wrtState of TY_DEV.
02h,24dec86,gae  changed stsLib.h to vwModNum.h.
02g,07apr86,dnw  removed ST_ERROR status and added rdError flag to smpte mode.
02f,23mar86,jlf  changed GENERIC to NOT_GENERIC.
02e,22aug85,dnw  replaced xState with rdState and wrtState structures.
                 added rdSmpteState and wrtSmpteState to SMPTE only version.
02d,16aug84,dnw  removed S_tyLib_SMPTE_READ_ERROR from GENERIC version.
                 added lnNBytes and lnBytesLeft members to TY_DEV for
                 line-protocol mode.
02c,15aug84,jlf  changed back to tyLib.h
02b,13aug84,ecs  got rid of S_tyLib_UNKNOWN_REQUEST.
                 changed S_tyLib_READ_ERROR to S_tyLib_SMPTE_READ_ERROR.
02a,10aug84,jlf  changed to tyLib.hx - new mega-file format.
01g,08aug84,ecs  added include of stsLib.h, status codes.
01f,15jun84,dnw  changed TY_DEV to work with new i/o system and ring buffer lib.
01e,27jan84,ecs  added inclusion test.
01d,15sep83,dnw  added xon/xoff stuff: xState field in TY_DEV and definitions
                 of states XST_...
01c,29jul83,dnw  added ST_TX_CR and removed txStopped.
                 diddled with TY_DEV to make it simpler & more consistent.
                 fiddled with device states to put them in order and
                 confuse the innocent.
01b,22jul83,ecs  added options & status, changed expectCk to TBOOL.
01a,24jun83,ecs  written
*/

#ifndef __INCtyLibh
#define __INCtyLibh

#include <iosLib.h>
#include <rngLib.h>
#include <selectLib.h>
#include <vwModNum.h>
#include <private/semLibP.h>
#include <spinLockLib.h>
#include <ioLib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*TY_HWFLOW_PTR) (_Vx_usr_arg_t , BOOL);
typedef BOOL (*TY_PROTOHOOK_PTR) (_Vx_usr_arg_t, int);
typedef void (*TY_DEVSTART_PTR) (void *);

typedef int (*TY_ABORT_PTR) (void);

/* HIDDEN */

typedef struct                  /* TY_DEV - tty device descriptor */
    {
    DEV_HDR     devHdr;         /* I/O device header */

    RING_ID     rdBuf;          /* ring buffer for read */
    SEMAPHORE   rdSyncSem;      /* reader synchronization semaphore */
    SEMAPHORE   mutexSem;       /* mutual exclusion semaphore */
    struct                      /* current state of the read channel */
        {
        UINT16 canceled;        /* read has been canceled */
        unsigned char xoff;     /* input has been XOFF'd */
        unsigned char pending;  /* XON/XOFF will be sent when xmtr is free*/
        unsigned char flushingRdBuf;    /* critical section marker */
        } rdState;

    RING_ID     wrtBuf;         /* ring buffer for write */
    SEMAPHORE   wrtSyncSem;     /* writer synchronization semaphore */
    struct                      /* current state of the write channel */
        {
        UINT16 canceled;        /* write has been canceled */
        unsigned char busy;     /* transmitter is busy sending character */
        unsigned char xoff;     /* output has been XOFF'd */
        unsigned char cr;       /* CR should be inserted next (after LF) */
        unsigned char flushingWrtBuf;   /* critical section marker */
        unsigned char wrtBufBusy;       /* task level writing to buffer */
        } wrtState;

    UINT8       lnNBytes;       /* number of bytes in unfinished new line */
    UINT8       lnBytesLeft;    /* number of bytes left in incompletely 
				  dequeued line */
    USHORT           options;        /* options in effect for this channel */
    TY_DEVSTART_PTR  txStartup;      /* pointer to routine to start xmitter */
    TY_PROTOHOOK_PTR protoHook;      /* protocol specific hook routine */
    _Vx_usr_arg_t    protoArg;       /* protocol specific argument */
    SEL_WAKEUP_LIST  selWakeupList;  /* tasks that are selected on this dev */
    atomic_t         numOpen;        /* number of open paths to device */

    size_t         xoffThreshold;  /* Rx Threshold for sending XOFF */
    size_t         xonThreshold;   /* Rx Threshold for sending XON */
    size_t         wrtThreshold;   /* Tx Threshold for other senders */
    TY_HWFLOW_PTR  xoffHook;       /* device specific Xoff/Xon routine */
    _Vx_usr_arg_t  xoffArg;        /* argument 1 for xoff/xon routine */
    int            flags;
    spinlockIsr_t  spinlockIsr;    /* ISR-callable spinlock */
    BOOL           wrtThresholdPassed; /* flag to keep track of threshold */
    } TY_DEV;

/* END_HIDDEN */

typedef TY_DEV * TY_DEV_ID;

/* function declarations */

extern STATUS   tyLibInit (int xoffThresh, int xonThresh, size_t wrtThresh);
extern STATUS   tyDevInit (TY_DEV_ID pTyDev, size_t rdBufSize, 
                    size_t wrtBufSize, TY_DEVSTART_PTR txStartup);
extern STATUS   tyDevTerminate (TY_DEV_ID pTyDev);
extern STATUS   tyITx (TY_DEV_ID pTyDev, char * pChar);
extern STATUS   tyIRd (TY_DEV_ID pTyDev, char inchar);
extern int      tyIoctl (TY_DEV_ID pTyDev, int request, _Vx_ioctl_arg_t arg);
extern ssize_t  tyRead (TY_DEV_ID pTyDev, char * buffer, size_t maxbytes);
extern ssize_t  tyWrite (TY_DEV_ID pTyDev, char * buffer, size_t nbytes);
extern void     tyAbortFuncSet (TY_ABORT_PTR func);
extern TY_ABORT_PTR    tyAbortFuncGet(void);
extern void     tyAbortSet (char ch);
extern char     tyAbortGet (void);
extern void     tyBackspaceSet (char ch);
extern void     tyDeleteLineSet (char ch);
extern void     tyEOFSet (char ch);
extern char     tyEOFGet (void);
extern void     tyMonitorTrapSet (char ch);
extern STATUS   tyXoffHookSet (TY_DEV_ID pTyDev, TY_HWFLOW_PTR func,
                    _Vx_usr_arg_t arg);
extern STATUS   tyDevRemove(TY_DEV_ID pTyDev);
extern char     tyAbortGet (void);

#ifdef __cplusplus
}
/*
 * Inlined C++ wrapper for the old-style FUNCPTR based tyDevInit() and 
 * tyXoffHookSet() functions prototype.
 */

extern STATUS   tyDevInit (TY_DEV_ID pTyDev, size_t rdBufSize, 
                    size_t wrtBufSize, FUNCPTR txStartup) \
       _WRS_DEPRECATED ("please use fully qualified function pointer "
                "version of API");

inline STATUS tyDevInit
    (
    FAST TY_DEV_ID     pTyDev,     /* ptr to tty dev descriptor to init */
    size_t             rdBufSize,  /* size of read buffer in bytes */
    size_t             wrtBufSize, /* size of write buffer in bytes */
    FUNCPTR            txStartup   /* device transmit start-up routine */
    )
    {
    return tyDevInit(pTyDev, rdBufSize, wrtBufSize, 
                     (TY_DEVSTART_PTR )txStartup);
    }

extern STATUS   tyXoffHookSet (TY_DEV_ID pTyDev, FUNCPTR func,
                    _Vx_usr_arg_t arg) \
       _WRS_DEPRECATED ("please use fully qualified function pointer "
                "version of API");

inline STATUS tyXoffHookSet
    (
    TY_DEV_ID       pTyDev,     /* pointer to device structure */
    FUNCPTR         func,       /* Hardware flow control routine */
    _Vx_usr_arg_t   arg         /* First argument to func routine */
    )
    {
    return tyXoffHookSet(pTyDev, (TY_HWFLOW_PTR)func, arg);   
    }

#endif /* __cplusplus */

#endif /* __INCtyLibh */

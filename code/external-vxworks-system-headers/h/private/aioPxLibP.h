/* aioPxLibP.h - asynchronous I/O header file */

/* Copyright 1984-2006, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
01n,30jun10,jxu  LP64:change member(maxFiles) of structure aio_dev from 
                 int to size_t. 
01m,28apr10,pad  Moved extern C statement after include statements.
01l,24jul06,jpb  Removed duplicate definition of AIO_SYS.
01k,14jul06,jlk  Added SIGEV_THREAD support
01j,07mar06,mil  Removed stdbool.h.  Added conditional for non-POSIX code.
01i,20jan06,mil  Updated for POSIX namespace conformance.
01h,30jan04,dat  Rework for RTP compatibility
01g,18jul96,dbt  moved aioPxLibInit() and aioShow() prototypes to aio.h 
		 (SPR #3227).
		 Updated copyright.
01f,15apr94,kdl  changed FD_NODE_TO_SYS macro to use offsetof().
01e,08apr94,kdl  changed aio_show() to aioShow().
01d,26jan94,kdl  changed include of ioQPxLib.h to ioQLib.h.
01c,12jan94,kdl  changed aioInit() to aioPxLibInit(); general cleanup.
01b,06dec93,dvs  changed M_aioLib to M_aioPxLib
                 changed S_aioLib* to S_aioPxLib*
01a,04apr93,elh  written.
*/

#ifndef __INCaioPxLibh
#define __INCaioPxLibh

/* includes */

#ifdef _WRS_KERNEL
#include <sigLib.h> /* need generic signal send rtn in RTP space!*/
#endif

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
#include <semLib.h>
#include <pthread.h>
#include <selectLib.h>
#include <lstLib.h>
#include <semLib.h>
#include <ioQLib.h>
#include <dllLib.h>
#include <stddef.h>
#else   /* _POSIX_xxx_SOURCE */
#include <base/b_union_sigval.h>
#include <types/vxWind.h>
#include <types/vxTypesOld.h>
#include <base/b_pthread_mutex_t.h>
#include <base/b_pthread_cond_t.h>
#include <ioQLib.h>
#include <dllLib.h>
#endif  /* _POSIX_xxx_SOURCE */

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)

/* aio driver ioctl functions */

#define  FAIO_PUSH		1		/* push request to head */
#define  FAIO_CANCEL		2		/* cancel a request */

/* aio control block states */

#define AIO_FREE		0		/* not submitted */
#define AIO_COMPLETED		1		/* completed */
#define AIO_READY		2		/* ready to be submitted */
#define AIO_QUEUED		3		/* queued */
#define AIO_WAIT   		4		/* waiting */
#define AIO_RUNNING		5		/* running */

#define AIO_CLUST_MAX           100             /* default max clusters */

/* easy access to aio_sys */

#define aio_state		aio_sys.state
#define aio_retVal 		aio_sys.ioNode.retVal
#define aio_errorVal		aio_sys.ioNode.errorVal

/* mark request done */

#define AIO_DONE_SET(pAiocb, _ret, _err) 	\
    {						\
    (pAiocb)->aio_sys.state    = AIO_COMPLETED;	\
    (pAiocb)->aio_sys.ioNode.retVal   = (_ret);	\
    (pAiocb)->aio_sys.ioNode.errorVal = (_err);	\
    }

#define FD_NODE_TO_SYS(pNode)			\
	((AIO_SYS *)(void *)((char *)(pNode) - offsetof(AIO_SYS, fdNode)))

/* typedefs */

typedef struct aio_clust			/* aio cluster */
    {
    BOOL		inuse;			/* cluster in use */
    int			refCnt;			/* reference count */
#ifdef _WRS_KERNEL
    struct sigpend	sigpend;		/* signal */
#else
    struct sigevent	aio_clust_sigevent;	/* signal info for cluster */
#endif
    pthread_mutex_t	lock;
    pthread_cond_t	wake;			/* cluster cond var */
    } AIO_CLUST;

#endif  /* _POSIX_xxx_SOURCE */

#if defined(_POSIX_C_SOURCE) || defined(_XOPEN_SOURCE) || \
    defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
#undef ioNode
#undef state
#undef pClust
#undef pAiocb
#undef sigNo
#undef sigVal
#undef lock
#undef wake
#undef wait
#undef fdNode
#endif

typedef struct aio_sys				/* aio system info */
    {
    _Vx_IO_NODE		ioNode;			/* I/O queue node */
    int			state;			/* state */
    struct aio_clust *	pClust;			/* lio cluster */
    struct aiocb *	pAiocb;			/* A-I/O control block */
#ifdef _WRS_KERNEL
    struct sigpend     	sigpend;		/* signal */
#else  /* _WRS_KERNEL */
    int			sigNo;
    union sigval	sigVal;
#endif /* _WRS_KERNEL */
    pthread_mutex_t	lock;			/* aiocb lock */
						/* protects the wait list*/
    pthread_cond_t	wake;			/* aiocb cond var */
    _Vx_LIST		wait; 			/* wait list */
    _Vx_DL_NODE		fdNode;			/* node for fd list */
    } AIO_SYS;

struct aio_clust;
struct aiocb;

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
typedef struct aio_wait_id			/* wait structure */
    {
    NODE		node;			/* wait list node */
    BOOL		done;			/* completed */
    pthread_mutex_t	lock;			/* wait id lock */
    pthread_cond_t	wake;			/* wait id cond var */
    } AIO_WAIT_ID;

typedef struct aio_fd_entry			/* A-I/O fd table entry */
    {
    DL_LIST 		ioQ;			/* I/O queue */
    SEM_ID	   	ioQSem;			/* semaphore for I/O queue */
    } AIO_FD_ENTRY;

typedef struct aio_dev				/* driver A-I/O struct */
    {
    IO_Q		ioQ;			/* I/O queues */
    size_t		maxFiles;		/* max files */
    SEM_ID		lockSem;		/* system lock semaphore */
    AIO_FD_ENTRY *	fdTable;		/* table array */
    AIO_CLUST *		clustTable;		/* cluster array */
    int			clustMax;		/* cluster array size */
    FUNCPTR		printRtn;		/* print rtn */
    SEM_ID		ioSem;			/* mutex ?? */
    SEM_ID		qSem;			/* work and done ? */
    SEM_ID		workSem;		/* work semaphore */
    int			waitFd;			/* wait pipe fd */
    fd_set		ioWait[2];		/* Yuch ! */
    fd_set		io[2];			/* more yuch ! */
    } AIO_DEV;
#endif  /* _POSIX_xxx_SOURCE */

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)

extern AIO_DEV	aioDev;				/* single global struct */

/* forward declarations These are PRIVATE */

extern STATUS 	aioCancel (AIO_DEV * pDev, struct aiocb * pAiocb);
extern STATUS 	aioPush (AIO_DEV * pDev, struct aiocb * pAiocb);
extern STATUS 	aioSync (AIO_DEV * pDev, struct aiocb * pAiocb, 
	       	         FUNCPTR syncReqRtn, int op);
extern void 	aioDone (AIO_SYS * pReq);

extern AIO_SYS* aioNext (AIO_DEV * pDev);
extern AIO_FD_ENTRY* aioEntryFind (int fd);

#endif  /* _POSIX_xxx_SOURCE */

#ifdef __cplusplus
}
#endif

#endif /* __INCaioPxLibh */

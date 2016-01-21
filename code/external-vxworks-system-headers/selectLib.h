/* selectLib.h - select header file */

/*
 * Copyright (c) 1990-1992, 2001, 2003-2005, 2010 Wind River Systems, Inc.
 * 
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
02k,06sep10,jxu  Removed inclusion of selectLibP.h, moved typedef selectLib.h
                 and SEL_WAKEUP_LIST from selectLibP.h.
02j,20may10,pad  Fixed previous change which mistakenly included
                 private/selectLibP.h on the user-side.
02i,18may10,pad  Moved extern C statement after include statements.
02h,17aug05,mcm  Using sys/time.h for RTP space.
02g,25mar04,mcm  Including time.h instead of sys/time.h in user-space
02f,10dec03,dat  adding SELEXCEPT select type
02e,12nov03,dat  modifications for RTP support
02d,18sep01,aeg  added selWakeupListTerm(); moved private definitions to
		 private/selectLibP.h; added S_selectLib_NO_SELECT_CONTEXT
		 and S_selectLib_WIDTH_OUT_OF_RANGE error codes.
02c,22sep92,rrr  added support for c++
02b,19aug92,smb  changed systime.h to sys/times.h
02a,04jul92,jcf  cleaned up.
01k,26may92,rrr  the tree shuffle
01j,04oct91,rrr  passed through the ansification filter
		  -removed comma from end of enum
		  -changed includes to have absolute path from h/
		  -changed VOID to void
		  -changed copyright notice
01i,25oct90,dnw  changed utime.h to systime.h.
01h,19oct90,shl  added #include of "utime.h".
01g,05oct90,shl  added ANSI function prototypes.
                 made #endif ANSI style.
                 added copyright notice.
01f,07aug90,shl  added function declarations comment.
01e,01aug90,jcf  clean up.
01d,13jul90,rdc  added original read and write fd_sets to wakeup node struct.
01c,30apr90,gae  added HIDDEN comments to internal data structures.
01b,20mar90,jcf  cleanup.
01a,26jan90,rdc  written
*/

#ifndef __INCselectLibh
#define __INCselectLibh

#include <sys/types.h>

#ifdef _WRS_KERNEL
#   include <sys/times.h>
#   include <taskLib.h>
#   include <lstLib.h>
#   include <private/semLibP.h>
#else
#   include <sys/time.h>
#   include <sys/select.h>	/* select() API */
#endif

/* error codes are shared */

#define S_selectLib_NO_SELECT_SUPPORT_IN_DRIVER  (M_selectLib | 1)
#define S_selectLib_NO_SELECT_CONTEXT		 (M_selectLib | 2)
#define S_selectLib_WIDTH_OUT_OF_RANGE		 (M_selectLib | 3)

#ifdef _WRS_KERNEL

#ifdef __cplusplus
extern "C" {
#endif

extern int select (int width, fd_set * pReadFds, fd_set * pWriteFds,
		   fd_set * pExceptFds, struct timeval * pTimeOut);

/* Only the kernel defines the driver support routines */

typedef enum
    {
    SELREAD,
    SELWRITE,
    SELEXCEPT
    } SELECT_TYPE;

typedef struct selWkNode
    {
    NODE        linkedListHooks;        /* hooks for wakeup list */
    BOOL        dontFree;               /* first in free list isn't malloc'ed */
    WIND_TCB *  taskId;                 /* taskId of select'ed task */
    USHORT      fd;                     /* fd to set in fd_set on activity */
    USHORT      ready;                  /* device is ready flag */
    SELECT_TYPE type;                   /* activity task is interested in */
    fd_set *    returnSet;              /* return fd set */
    } SEL_WAKEUP_NODE;

typedef struct
    {
    SEMAPHORE           listMutex;      /* mutex semaphore for list */
    SEL_WAKEUP_NODE     firstNode;      /* usually one deep, stash first one */
    LIST                wakeupList;     /* list of SEL_WAKEUP_NODE's */
    } SEL_WAKEUP_LIST;

/* function declarations */

extern SELECT_TYPE  selWakeupType 	(SEL_WAKEUP_NODE *pWakeupNode);
extern STATUS 	    selNodeAdd 	      	(SEL_WAKEUP_LIST *pWakeupList,
			    		 SEL_WAKEUP_NODE *pWakeupNode);
extern STATUS 	    selNodeDelete 	(SEL_WAKEUP_LIST *pWakeupList,
			       		 SEL_WAKEUP_NODE *pWakeupNode);
extern int 	    selWakeupListLen 	(SEL_WAKEUP_LIST *pWakeupList);
extern void 	    selWakeup 		(SEL_WAKEUP_NODE *pWakeupNode);
extern void 	    selWakeupAll 	(SEL_WAKEUP_LIST *pWakeupList, 
					 SELECT_TYPE type);
extern void 	    selWakeupListInit 	(SEL_WAKEUP_LIST *pWakeupList);
extern void 	    selWakeupListTerm 	(SEL_WAKEUP_LIST *pWakeupList);

#ifdef __cplusplus
}
#endif

#endif /* _WRS_KERNEL */

#endif /* __INCselectLibh */

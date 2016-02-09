/* msgQSmLibP.h - private shared message queue library header file */

/*
 * Copyright (c) 1992-1993, 1997-1998, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */


/*
modification history
--------------------
01j,15sep10,swg  remove VxMP APIs for these APIs will be published(WIND00145226)
01i,09sep10,jpb  Removed unused function pointer msgQSmInfoGetRtn.
01h,29apr10,pad  Moved extern C statement after include statements.
01g,17apr98,rlp  canceled SM_MSG_Q modification for backward compatibility.
01f,04nov97,rlp  modified SM_MSG_Q structure for tracking messages sent.
01e,29jan93,pme  added little endian support
01d,29sep92,pme  added msgQSmNumMsgs(), msgQSmSend(), msgQSmReceived()
		 and msgQSmInfoGet() functions prototypes. 
01c,22sep92,rrr  added support for c++
01b,17sep92,pme  added shared message queue info get support.
01a,19jul92,pme  written.
*/

#ifndef __INCmsgQSmLibPh
#define __INCmsgQSmLibPh

#include <vxWorks.h>
#include <vwModNum.h>
#include <msgQSmLib.h>
#include <smDllLib.h>
#include <private/semSmLibP.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#define MSG_Q_TYPE_SM 	10		/* shared message queue */

#if (defined (CPU_FAMILY) && (CPU_FAMILY==I960) && (defined __GNUC__))
#pragma align 1                 /* tell gcc960 not to optimize alignments */
#endif  /* CPU_FAMILY==I960 */

/* typedefs */

typedef struct sm_msg_q                 /* SM_MSG_Q */
    {
    UINT32              verify;         /* msgQ verification */
    UINT32		objType;	/* msgQ type */

    SM_SEMAPHORE        msgQSem;        /* msgQ shared counting semaphore */
    UINT32              msgQLock;       /* spinlock for msgQ */
    SM_DL_LIST          msgQ;           /* message queue head */

    SM_SEMAPHORE        freeQSem;       /* freeQ shared counting semaphore */
    UINT32              freeQLock;      /* spinlock for freeQ */
    SM_DL_LIST          freeQ;          /* free message queue head */

    UINT32              options;        /* message queue options */
    UINT32              maxMsgs;        /* max number of messages in queue */
    UINT32              maxMsgLength;   /* max length of message */
    UINT32              sendTimeouts;   /* number of send timeouts */
    UINT32              recvTimeouts;   /* number of receive timeouts */
    } SM_MSG_Q;

typedef struct  sm_msg_node             /* SM_MSG_NODE */
    {
    SM_DL_NODE          node;           /* queue node */
    int                 msgLength;      /* number of bytes of data */
    } SM_MSG_NODE;

#if (defined (CPU_FAMILY) && (CPU_FAMILY==I960) && (defined __GNUC__))
#pragma align 0                 /* turn off alignment requirement */
#endif  /* CPU_FAMILY==I960 */

#define SM_MSG_NODE_DATA(pNode)   (((char *) pNode) + sizeof (SM_MSG_NODE))

/* variable declarations */

extern FUNCPTR msgQSmShowRtn;		/* shared msgQ show routine ptr */

/* function declarations */

extern void   msgQSmLibInit (void);
extern STATUS msgQSmInit (SM_MSG_Q * pMsgQ, int maxMsgs, int maxMsgLength,
			  int options, void * pMsgPool);

#ifdef __cplusplus
}
#endif

#endif /* __INCmsgQSmLibPh */

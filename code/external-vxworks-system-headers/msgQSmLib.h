/* msgQSmLib.h - shared message queue library header file */

/* Copyright 1984-1992, 2010 Wind River Systems, Inc. */
/*
modification history
--------------------
01g,15sep10,swg  change the parameter type of VXMP dedicated APIs:
           from SM_XXX_ID to XXX_ID(WIND00145226)
01f,23jul10,swg  Add VxMP dedicated APIs
01e,29apr10,pad  Moved extern C statement after include statements.
01d,29sep92,pme  removed msgQSmNumMsgs(), msgQSmSend(), msgQSmReceived()
		 and msgQSmInfoGet() functions prototypes.
01b,22sep92,rrr  added support for c++
01a,19jul92,pme  cleaned up according to code review.
                 written.
*/

#ifndef __INCmsgQSmLibh
#define __INCmsgQSmLibh

#include "vxWorks.h"
#include "vwModNum.h"
#include "msgQLib.h"

#ifdef __cplusplus
extern "C" {
#endif


/* typedefs */

typedef struct sm_msg_q * SM_MSG_Q_ID;		/* shared message queue ID */

/* macros */

/* The following macro determines the number of bytes needed to buffer
 * a message of the specified length.  The node size is rounded up for
 * efficiency an alignement.  The total buffer space required for a pool for
 * <maxMsgs> messages each of up to <maxMsgLength> bytes is:
 *
 *     maxMsgs * SM_MSG_NODE_SIZE (maxMsgLength)
 */

#define SM_MSG_NODE_SIZE(msgLength)	\
	(((sizeof (SM_MSG_NODE) + msgLength) + 3) & ~3)

/* function declarations */

#if defined(__STDC__) || defined(__cplusplus)

extern MSG_Q_ID  msgQSmCreate (int maxMsgs, int maxMsgLength, int options);
extern void      msgQSmShowInit ();
extern STATUS    msgQSmSend(MSG_Q_ID smMsgQIdIn, char * buffer, UINT nBytes,
                                  int timeout, int priority);
extern int       msgQSmReceive(MSG_Q_ID smMsgQIdIn, char * buffer, UINT maxNBytes,
                                  int timeout);
extern int       msgQSmNumMsgs(MSG_Q_ID smMsgQIdIn);
extern STATUS    msgQSmInfoGet(MSG_Q_ID smMsgQIdIn, MSG_Q_INFO * pInfo);
extern STATUS    msgQSmShow(MSG_Q_ID smMsgQIdIn, int level);

#else   /* __STDC__ */

extern MSG_Q_ID  msgQSmCreate ();
extern void      msgQSmShowInit ();

extern STATUS    msgQSmSend();
extern int       msgQSmReceive();
extern int       msgQSmNumMsgs();
extern STATUS    msgQSmInfoGet();
extern STATUS    msgQSmShow();
#endif  /* __STDC__ */
#ifdef __cplusplus
}
#endif

#endif /* __INCmsgQSmLibh */

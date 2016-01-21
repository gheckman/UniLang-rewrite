/* qosIngressLibP.h - private definitions for qos support on ingress */

/*
 * Copyright (c) 2005 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. No license to Wind River intellectual property rights
 * is granted herein. All rights not licensed by Wind River are reserved
 * by Wind River.
 */

/*
modification history
--------------------
01b,08sep05,niq  Code review changes + enhanced statistics gathering
01a,09aug05 niq  created.
*/

#ifndef __INCqosIngressLibPh
#define __INCqosIngressLibPh
#ifdef __cplusplus
extern "C" {
#endif

#define QOS_MAX_PRI	31	/* Maximum QOS priority */

/*
 * Structure defining a queue for queuing packets for qos processing
 * Each queue contains packets having the same priority.
 * We have a array of 32 qos queues that allow 32 different priority
 * queues.
 */
struct	qosqueue 
{
    struct mbuf * 	qosq_head;
    struct mbuf * 	qosq_tail;
#ifdef QOS_STATS
    int			qosq_len;	/* Num packets in queue */
    int			qosq_maxlen;	/* Max qlen at any time */	
    int			qosq_total;	/* Cumulative total of packets queued*/
    int			qosq_maxlim;	/* Not used. Queue max limit */
    int			qosq_drops;	/* Not used. Packets dropped */
#endif /* QOS_STATS */
};

struct qosqFlushJob
{
    QJOB		flushJob; /* Job for flushing packets on the qosq */
    void *		pEnd;	  /* Device whose pakcets have to be flushed*/ 
    BOOL		done;

};

typedef struct _qosqVars
{
    QJOB		processJob;/* Job for processing packets on the qosq */
    UINT32		qosqActivePri;
    JOB_QUEUE_ID 	pJobQueue; /* Job queue to use */
    int			qosDefaultPri; /* Default pri for queuing packets */
    struct qosqueue	qosqArr [QOS_MAX_PRI + 1];
#ifdef QOS_STATS
    UINT32		numPackets;
    UINT32		discards;
    UINT32		delivered;
#endif /* QOS_STATS */
} QOSQ_VARS;

#ifdef QOS_STATS
#define INC_QLEN(qosq)	\
    do { \
	(qosq)->qosq_len++; \
	(qosq)->qosq_total++; \
	if ((qosq)->qosq_maxlen < (qosq)->qosq_len) \
	    (qosq)->qosq_maxlen = (qosq)->qosq_len; \
    } while (0)

#define DEC_QLEN(qosq)	(qosq)->qosq_len--
#else
#define INC_QLEN(qosq)	
#define DEC_QLEN(qosq)	
#endif /* QOS_STATS */


/* These macros should be used to manipulate the qos queue */
/* 
 * We currently manipulate the queues inline for better performance. Hence 
 * these macros are ununsed for now. 
 */

/* The following two macros are unused currently */

#define	QOS_QFULL(qosq)		((qosq)->qosq_len >= (qosq)->qosq_maxlen)
#define	QOS_DROP(qosq)		((qosq)->qosq_drops++)

#define	QOS_ENQUEUE(qosq, m) \
    do  { \
	(m)->m_nextpkt = 0; \
	if ((qosq)->qosq_tail == 0) \
		(qosq)->qosq_head = m; \
	else \
		(qosq)->qosq_tail->m_nextpkt = m; \
	(qosq)->qosq_tail = m; \
	INC_QLEN(qosq); \
    } while (0)

/* The following macro is unused currently */
#define	QOS_PREPEND(qosq, m) \
    do {				 \
	(m)->m_nextpkt = (qosq)->qosq_head; \
	if ((qosq)->qosq_tail == 0) \
		(qosq)->qosq_tail = (m); \
	(qosq)->qosq_head = (m); \
	INC_QLEN(qosq); \
    } while (0)

#define	QOS_DEQUEUE(qosq, m) \
    do {				 \
	(m) = (qosq)->qosq_head; \
	if (m) { \
		if (((qosq)->qosq_head = (m)->m_nextpkt) == 0) \
			(qosq)->qosq_tail = 0; \
		(m)->m_nextpkt = 0; \
		DEC_QLEN(qosq);		 \
	} \
    } while (0)

#ifdef __cplusplus
}
#endif

#endif /* __INCqosIngressLibPh*/


/* netLib.h - header file for the tNetTask */

/* 
 * Copyright 2001-2003, 2005-2007, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */


/*
modification history
--------------------
01u,10nov10,dlk  Move extern "C" after last header file include. WIND00240828.
01t,12oct07,dlk  Changed netDaemonQ() to take an signed int argument;
                 add the inverse function netDaemonQnum().
01s,09jun07,dlk  Make netDaemonQ() public. Add netDaemonsCount().
                 netLibInitialize() takes additional netTaskFunc() argument.
01r,06mar07,dlk  Remove references to netJobInfo.
01q,09sep06,kch  Added string.h include.
01p,20jun06,jpb  Removed I960 check.
01o,25aug05,dlk  Added section tags.
01n,08jul05,dlk  Implement netJobAdd() using jobQueueLib.
01m,25nov03,wap  Merge in changes for Snowflake
01l,20nov03,niq  Remove copyright_wrs.h file inclusion
01k,05nov03,cdw  Removal of unnecessary _KERNEL guards.
01j,04nov03,rlm  Ran batch header path update for header re-org.
01i,03nov03,rlm  Removed wrn/coreip/ prefix from #includes for header re-org.
01h,15aug03,nee  Merging from ACCORDION_BASE6_MERGE_BASELINE
01g,10jun03,vvv  include netVersion.h
01f,13may03,vvv  deleted TCP_MSL_CFG to avoid duplicate definitions
01e,01may03,spm  Tornado 2.2 CP1 merge (from ver 01p,22jan03,wap:
                 TOR2_2-CP1-F label, tor2_2-patch branch, /wind/river VOB)
01d,30dec02,ann  changing the value of IP_PROTO_NUM_MAX to 16
01c,26feb02,ham  renamed to netLib.h
01b,23aug01,ann  correcting the references to netlibh after the rename
01a,15aug01,ann  ported to clarinet from AE1.1 version 01o.
*/

#ifndef __INCnetLibh
#define __INCnetLibh

#include <netVersion.h>
#include <string.h>    

#include <jobQueueLib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define NET_TASK_QJOB_PRI	16

/* For convenience only. Using &netJobInfo avoids a dereference. */

extern JOB_QUEUE_ID netJobQueueId;

extern void * netGtfTickInformation; /* read only */

/* function declarations */

extern STATUS   netJobAdd (FUNCPTR routine,
			   _Vx_usr_arg_t param1,
			   _Vx_usr_arg_t param2,
			   _Vx_usr_arg_t param3,
                           _Vx_usr_arg_t param4,
			   _Vx_usr_arg_t param5);

extern STATUS   netLibInitialize (unsigned int numDaemons, BOOL affinityLock,
			  int (*netTaskFunc) (JOB_QUEUE_ID qId, int qIndex));
extern unsigned int netDaemonsCount (void);
extern JOB_QUEUE_ID netDaemonQ (int i);
extern int netDaemonQnum (JOB_QUEUE_ID qId);

extern void     netErrnoSet (int status);
extern void     mbinit (void * pNetPoolCfg);
extern STATUS	netJobAlloc (u_int numJobs);
_WRS_FASTTEXT
extern void	netGtfTickFunc (void * pTm, void * arg);


/* backwards compatibility */
#define netJobAdd(f, a1, a2, a3, a4, a5) \
    (jobQueueStdPost (netJobQueueId, NET_TASK_QJOB_PRI,		    \
		      (VOIDFUNCPTR)(f), (void *)(a1), (void *)(a2), \
		      (void *)(a3), (void *)(a4), (void *)(a5)))

#ifdef __cplusplus
}
#endif

#endif /* __INCnetLibh */


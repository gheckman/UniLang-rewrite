/* qosIngressLib.h - definitions for qos support on ingress */

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
01b,22sep09 zhr Fixed WIND00180271
01a,09aug05 niq  created.
*/

#ifndef __INCqosIngressLibh
#define __INCqosIngressLibh

#ifdef __cplusplus
extern "C" {
#endif

/* defines for the return value of the packet classification hook */

typedef enum
{ 
    QOS_HOOK_FAIL = -1,
    QOS_DELIVER_PKT,
    QOS_DEFER_PKT,
    QOS_IGNORE_PKT
} QOS_HOOK_RETVAL;

/* definition for the packet classification hook */
typedef QOS_HOOK_RETVAL (*QOS_ING_HOOK) (END_OBJ *, M_BLK_ID *, int *);


/* Configuration structure */

typedef struct _qosConfig
{
    JOB_QUEUE_ID    cfg_pJobQueue;     /* Job queue to use */
    int 	    cfg_jobQPri;       /* Priority for the process job */
    int		    cfg_qosDefaultPri; /* Default pri for queuing packets */
} QOS_CONFIG_PARAMS;

/* External APIs */

IMPORT STATUS qosIngressLibInit (void * cfgParams);
IMPORT STATUS qosIngressHookSet (int unit, char * ifname, QOS_ING_HOOK hookRtn);

#ifdef __cplusplus
}
#endif

#endif /* __INCqosIngressLibh */


 /* odgPolicyMgrLib.h - OnDemand Governor Power Policy Management */

/*
 * Copyright (c) 2010, 2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01d,22mar11,rec  WIND00262608 initialize sysLowIoThreshold
01c,04jan11,rec  add sleepFilterInterval
01b,07dec10,rec  add msgQueues for RTP interface
01a,19nov10,rec  created

*/
#ifndef __INCodgPolicyMgrLibh
#define __INCodgPolicyMgrLibh

#define CPU_UTILIZATION_EVENT   0X01
#define LOW_IO_HEADROOM_EVENT   0x02
#define HEADROOM_ANY            0x03

#ifndef _ASMLANGUAGE

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#define MSGQPOLICY  "/msgQPolicyChange"
#define MSGQNOTIFY  "/msgQNotify"


typedef struct power_policy {
    UINT32  sampleInterval;
    UINT32  lowFilterInterval;
    UINT32  highFilterInterval;
    UINT32  sleepFilterInterval;
    UINT32  lowHeadroomThresh;
    UINT32  highHeadroomThresh;
    UINT32  lowHeadroomAlarmThresh;
    UINT32  sleepMaxInterrupts;
    UINT32  sleepHeadroomThresh;
    UINT32  minPState;
    UINT32  maxPState;
    } POWER_POLICY;

typedef enum  policy_msg {
    POLICY_SET,         /* body is POWER_POLICY */
    POLICY_ENABLE,      /* no body */
    POLICY_DISABLE,     /* no body */
    CSTATE_SET          /* body is new cstate */
    } POLICY_MSG_TYPE;

typedef struct policy_q_msg {
    POLICY_MSG_TYPE  msgType;
    union   {
        POWER_POLICY policy;
        UINT32       cState;
        } msg;
    } POLICY_MESSAGE;


#if !defined(__RTP__)  /* define only if not RTP */
/* 
 * Policy manager event notification objects
 * These events are available for registration through erfLib. 
 */

IMPORT UINT16 policyMgrEventCategory;
IMPORT UINT16 policyMgrUpEvent;     /* increase performance */
IMPORT UINT16 policyMgrDownEvent;   /* decrease performance */
IMPORT UINT16 policyMgrC3state;     /* system goes into C3 */
IMPORT UINT16 policyMgrC1state;     /* system comes out of C3 */

/* BSP support functions */

IMPORT void sysC3StateConfig (BOOL enable);
IMPORT STATUS sysCpuUtilInit (TASK_ID tPolicyMgr);
IMPORT void sysUtilSampleWindowSet (UINT32 sampleWindow);
IMPORT UINT32 sysCpuUtilGet (void);
IMPORT UINT32 sysIoUtilGet (void);
IMPORT void sysIoThresholdSet (UINT32 ioThreshold);
IMPORT UINT32 sysIoThresholdGet (void);


/* public API */

IMPORT STATUS odgPolicyMgrSet (POWER_POLICY *pPolicy);
IMPORT STATUS odgPolicyMgrInit 
    (
    UINT32  sampleInterval,
    UINT32  lowFilterInterval,
    UINT32  highFilterInterval,
    UINT32  sleepFilterInterval,
    UINT32  lowHeadroomThresh,
    UINT32  highHeadroomThresh,
    UINT32  lowHeadroomAlarmThresh,
    UINT32  sleepMaxInterrupts,
    UINT32  sleepHeadroomThresh,
    UINT32  minPState,
    UINT32  maxPState,
    UINT32  daemonPriority
    );

IMPORT void odgPolicyMgrEnable (void);
IMPORT void odgPolicyMgrDisable (void); 
#endif /* __RTP__ */


#endif /* _ASMLANGUAGE */

#endif /* __INCodgPolicyMgrLib */


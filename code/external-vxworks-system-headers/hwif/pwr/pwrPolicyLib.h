/* pwrPolicyLib.h - Power Policy Library Manager */

/*
 * Copyright (c) 2011, 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01k,12jan12,jlv  WIND00325767 - Change PEV_Tickless to a single event
01j,19sep11,jlv  WIND00303250 - Remove unused APIs
01i,15sep11,jlv  WIND00299523 - Remove System Power Policy
01h,06sep11,jlv  WIND00299143 - Add C3 state change notification
                 Add numTicks to pwrPolicyPEVSend function
01g,22aug11,j_l  WIND00255353: Tickless mode/IA PPM integration.
01f,22aug11,jlv  WIND00295172 - Remove CPU PowerId
01e,18aug11,jlv  Move default CPU Policy ini to pwrCpuLib
01d,05aug11,jlv  Add PEV_TICKLESS for tickless notifications
01c,02aug11,jlv  Remove pollInterval from sysPolicy
01b,25jul11,jlv  Add errno macros, move extern after includes
01a,14jun11,jlv  created WIND00255352

*/

#ifndef __INCpwrPolicyLibh
#define __INCpwrPolicyLibh

#include <drv/erf/erfLib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define PWR_POLICY_DEV_NAME_SIZE   24

/* errno macros */

#define S_pwrPolicyLib_INVALID_POLICY   (M_pwrPolicyLib | 1)
#define S_pwrPolicyLib_INVALID_CPU_NUM  (M_pwrPolicyLib | 2)
#define S_pwrPolicyLib_UNKNOWN_DEV      (M_pwrPolicyLib | 3)

/*
 * Policy Definitions
 */

/* There is one CPU Power Policy for each running CPU. */

typedef struct cpu_power_policy
    {
    UINT32               sampleInterval;          /* CPU utilization sample interval */
    UINT32               lowFilterInterval;       /* low headroom filter interval    */
    UINT32               highFilterInterval;      /* high headroom filter interval   */
    UINT32               sleepFilterInterval;     /* sleep filter interval           */
    UINT32               lowHeadroomThresh;       /* low headroom threshold          */
    UINT32               highHeadroomThresh;      /* high headroom threshold         */
    UINT32               lowHeadroomAlarmThresh;  /* low headroom alarm threshold    */
    UINT32               sleepMaxInterrupts;      /* maximum sleep interrupts        */
    UINT32               sleepHeadroomThresh;     /* sleep headroom threshold        */
    UINT32               pStateCapability;        /* bitmask indicate states supported */
    UINT32               cStateCapability;        /* bitmask indicate states supported */
    } PWR_POLICY_CPU;

/* There is one Device Power Policy for each power-managed device. */

typedef struct device_power_policy
    {
    UINT32               timeout;                 /* device inactivity timeout */
    UINT32               dStateCapability;        /* bitmask indicate states supported */
    } PWR_POLICY_DEV;

/*
 * Power Event
 */

/* Event bits for Power Event <eventBitMask> */

#define PEV_CPU_UTIL_HIGH        0X001
#define PEV_CPU_UTIL_LOW         0x002
#define PEV_HEADROOM_HIGH        0x004
#define PEV_HEADROOM_LOW         0x008
#define PEV_TICKLESS             0x010

#define PPM_MAX_EVENTS              32

/* CPU event types */

#define PEV_UTILIZATION     (PEV_CPU_UTIL_HIGH | PEV_CPU_UTIL_LOW)
#define PEV_HEADROOM        (PEV_HEADROOM_HIGH | PEV_HEADROOM_LOW)

/*
 * pwrEventType are the actions that may occur upon receipt of an event.  The event
 * type are to be used for callback registration for PEV (pwrPolicyPEVCallbackRegister).
 * A P-State or C-state change will trigger the registered callbacks for each action.
 * The utilization events may cause these state changes.
 */

typedef enum {
    PSTATE_CHANGE = 0,   /* P-state change notification */
    C1STATE_CHANGE,      /* Prior to entering C1 sleep state */
    C3STATE_CHANGE       /* Prior to entering C3 sleep state */
} pwrEventType;

typedef struct pevCpuCallbackParam
    {
    UINT32    cpuNum;
    UINT32    stateNum;
    } PEV_CALLBACK_PARAM;

typedef struct pevTicklessParam   /* Used with PEV_TICKLESS PEV */
    {
    UINT32        cpuNum;         /* Logical CPU Number */
    UINT32        sleepStateNum;  /* Sleep State Number (non-C0) */
    _Vx_ticks64_t sleepTick;      /* Sleep tick count */
    BOOL          ticklessOn;     /* Tickless mode enabled */
    } PEV_TICKLESS_PARAM;

typedef struct power_event
    {
    UINT32    		eventId;      /* PEV event bitmask */
    void    		*param;       /* opaque power param for event sender */
    _Vx_ticks64_t 	tickCount;    /* tick count at PEV execution */
    } POWER_EVENT;

/*
 * Message interface to Power Policy Manager
 */

typedef struct cpu_policy_msg
    {
    UINT32          cpuNum;
    PWR_POLICY_CPU  cpuPolicy;
    } CPU_POLICY_MSG;

typedef struct dev_policy_msg
    {
    char            devName[PWR_POLICY_DEV_NAME_SIZE+1];
    UINT32          unitNum;
    PWR_POLICY_DEV  devPolicy;
    } DEV_POLICY_MSG;

typedef enum  power_policy_msg {
    PPM_POLICY_SET_CPU,    /* body is PWR_POLICY_CPU */
    PPM_POLICY_SET_DEV,    /* body is PWR_POLICY_DEV */
    PPM_POLICY_ENABLE,     /* no body */
    PPM_POLICY_DISABLE,    /* no body */
    PPM_POWER_EVENT        /* body is POWER_EVENT */
} PPM_MSG_TYPE;

typedef struct power_policy_q_msg {
    PPM_MSG_TYPE msgType;

    union
        {
        POWER_EVENT      event;
        CPU_POLICY_MSG   cpu;
        DEV_POLICY_MSG   dev;
        } msgBuf;

    } PPM_MESSAGE;

/* public API functions */

/* Enable/Disable Policy monitoring */

IMPORT STATUS pwrPolicyEnable (void);
IMPORT STATUS pwrPolicyDisable (void);

/* CPU Policy Mgmt */

IMPORT STATUS pwrPolicyCpuSet (UINT32 cpuNum,
                               PWR_POLICY_CPU *cpuPolicy);
IMPORT STATUS pwrPolicyCpuGet (UINT32 cpuNum,
                               PWR_POLICY_CPU *cpuPolicy);
IMPORT STATUS pwrPolicyCpuShow(UINT32 cpuNum);

IMPORT UINT32 pwrPolicyPstateCapabilityGet (UINT32 cpuNum);
IMPORT UINT32 pwrPolicyCstateCapabilityGet (UINT32 cpuNum);

/* Device Policy Mgmt */

IMPORT STATUS pwrPolicyDevSet (char *devName,
                               UINT32 unitNum,
                               PWR_POLICY_DEV *devPolicy);
IMPORT STATUS pwrPolicyDevGet (char *devName,
                               UINT32 unitNum,
                               PWR_POLICY_DEV *devPolicy);
IMPORT STATUS pwrPolicyDevShow (char *devName, UINT32 unitNum);

/* Power Event */

IMPORT STATUS pwrPolicyPEVSend(UINT32 eventBitMask, 
                               _Vx_ticks64_t numTicks,
                               void *param);

IMPORT STATUS pwrPolicyPEVCallbackRegister(pwrEventType eventType,
                                           erfHandlerPrototype *pEventHandler,
                                           void *pUserData);
IMPORT STATUS pwrPolicyPEVCallbackUnregister(pwrEventType eventType,
                                             erfHandlerPrototype *pEventHandler,
                                             void *pUserData);

#ifdef __cplusplus
}
#endif

#endif /* __INCpwrPolicyLibh */


/* pwrPolicyMgr.h - Power Policy Management */

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
01j,12jan12,jlv  WIND00325775 - Add CPU Pwr Mgr event callbacks
01i,05oct11,sem  WIND00308566 - Add CPU event metrics API
01h,19sep11,jlv  WIND00303250 - Remove unused APIs
01g,15sep11,jlv  WIND00299523 - Remove System Power Policy
01f,12sep11,rbc  WIND00295395 - Fix build error.
01e,06sep11,jlv  WIND00295395 - Remove macro access to PPM db
                 WIND00295992 - Add support for show commands
01d,22aug11,jlv  WIND00295172 - Remove CPU PowerId
01c,02aug11,jlv  Add event metrics per CPU
01b,25jul11,jlv  Move extern after includes, remove unused APIs
01a,14jun11,jlv  created WIND00255253

*/

#ifndef __INCpwrPolicyMgrh
#define __INCpwrPolicyMgrh

#include <sllLib.h>
#include <hwif/vxbus/vxBus.h>
#include <hwif/pwr/pwrPolicyLib.h>

#ifdef __cplusplus
extern "C" {
#endif


#define PPM_MSG_SIZE     25

#define MAX_PERCENT      100

#define PPMSET_ISSET(bitmask, n)     (bitmask & (1 << n))


/*
 * Define support Power States for the PPM.
 * The pwrStateType parameter is used for pwrPolicyMgrStateGet
 * function to specify the type of state being requested.
 */

typedef enum {
    PPM_PSTATE = 1,
    PPM_CSTATE,
    PPM_DSTATE
} pwrStateType;

/*
 * Power Policy Manager Power State data
 */

typedef struct power_state_metric
    {
    UINT32              stateNum;         /* actual power state number */
    UINT32              numTimesEntered;  /* number of times entered this state */
    _Vx_ticks_t         maxTicks;         /* maximum tick run in this state */
    _Vx_ticks64_t       totalTicksInState;/* cumulative tick count in this state */
    _Vx_ticks64_t       tickEnteredState; /* tick count entered this state */
    _Vx_ticks64_t       tickExitedState;  /* tick count exited this state */
    } PWR_STATE_METRIC;

typedef struct power_event_cpu_metric
    {
    UINT32              utilHigh;      /* number of high utilization PEV */
    UINT32              utilLow;       /* number of low utilization PEV */
    UINT32              hdrmHigh;      /* number of high headroom PEV */
    UINT32              hdrmLow;       /* number of low headroom PEV */
    UINT32              tickless;      /* number of tickless PEV */
    UINT32              tickSleep;     /* number of non-tickless sleep PEV */
    } PWR_EVENT_CPU_METRIC;

typedef struct cpu_power_data
    {
    UINT32              currentPwrState;  /* current P-state according to PPM */
    UINT32              currentCState;    /* current C-state according to PPM */

    UINT32              numPwrStates;     /* number P-states supported by CPU */
    UINT32              numCStates;       /* number C-states supported by CPU */

    PWR_EVENT_CPU_METRIC cpuPev;          /* PEV metrics */

    PWR_POLICY_CPU      cpuPolicy;        /* Active CPU Power Policy */

    _Vx_ticks64_t       baseTicks;        /* Base ticks for start of Power Stats */

    PWR_STATE_METRIC    *pPwrStateAddr;   /* P-state Power State statistics */
    PWR_STATE_METRIC    *pCStateAddr;     /* C-state Power state statistics */

    } PWR_DATA_CPU;

typedef struct device_power_data
    {
    SL_NODE             node;             /* SL list node */
    char                *pName;           /* Name of device */
    UINT32              unitNum;          /* Unit number of device */

    UINT32              currentDState;    /* current D-state according to PPM */
    UINT32              numDStates;       /* number of D-states supported by device */

    void                *powerId;         /* device power id */

    _Vx_ticks64_t        baseTicks;       /* Base ticks for start of Power Stats */

    PWR_POLICY_DEV      devPolicy;        /* Active device Power Policy */

    PWR_STATE_METRIC    *pDStateAddr;     /* D-state Power state statistics */
    } PWR_DATA_DEV;

typedef struct system_power_data
    {

    /* CPU power data */

    UINT32               numCpus;         /* Number of running CPUs */
    PWR_DATA_CPU        *cpuDataAddr;     /* Offset to Power data for each CPU */

    /* Device power data */

    UINT32               numDevs;         /* Number of power-managed devices */
    SL_LIST             *pDevList;        /* Head of SL list for devices */
    UINT32               pevDevTimeout;   /* Total number of device timeouts */

    } PWR_DATA_SYS;

/* Public APIs */

IMPORT STATUS pwrPolicyMgrCpuShow (UINT32 cpuNum, UINT32 level);
IMPORT STATUS pwrPolicyMgrCpuShowAll (void);
IMPORT STATUS pwrPolicyMgrDevShow (char  *devName, UINT32 unitNum, UINT32 level);
IMPORT STATUS pwrPolicyMgrDevShowAll (void);
IMPORT STATUS pwrPolicyMgrShow (void);

IMPORT STATUS pwrPolicyMgrCpuStateReset (UINT32 cpuNum);
IMPORT STATUS pwrPolicyMgrCpuStateShow (UINT32 cpuNum);
IMPORT STATUS pwrPolicyMgrCpuStateGet (UINT32 cpuNum, UINT32 stateNum,
                                       pwrStateType stateType, PWR_STATE_METRIC *pMetric);
IMPORT STATUS pwrPolicyMgrCpuPevGet (UINT32 cpuNum, PWR_EVENT_CPU_METRIC *pMetric);

IMPORT STATUS pwrPolicyMgrDevStateReset (char  *devName, UINT32 unitNum);
IMPORT STATUS pwrPolicyMgrDevStateShow (char  *devName, UINT32 unitNum);
IMPORT STATUS pwrPolicyMgrDevStateGet (char *devName, UINT32 unitNum,
                                       UINT32 stateNum, PWR_STATE_METRIC *pMetric);

#ifdef __cplusplus
}
#endif

#endif /* __INCpwrPolicyMgrh */


/* pwrLibFuncs.h - power management library functions header file */

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
01j,12jan12,jlv WIND00325771 - Add Power Policy Stats API to new component
                WIND00325775 - CPU Power Mgr API for event callbacks
01i,04jan12,jlv WIND00311593 - Add event metrics API
01h,25oct11,jlv WIND00312777 - Tickless optimizations
01g,20sep11,j_l WIND00297582 - Add libFuncs for Idle Power Management
                Move extern C statement after include statements.
01f,19sep11,jlv WIND00303250 - Remove unused PPM APIs
01e,13sep11,rbc WIND00299531 - Fix build error.
01d,12sep11,rbc WIND00299531 - Add libFuncs for PolicyLib and PolicyMgr
01c,07sep11,jjk WIND00296077 - Added support for device timeout polling
01b,01sep11,rbc WIND00295402 - Fix build error for guest OS with
                INCLUDE_PWR_POLICY_MGR
01a,19Aug11,rbc Created
*/

#ifndef PWRLIBFUNCS_H
#define PWRLIBFUNCS_H

/* includes */

#include <vxWorks.h>
#include <hwif/pwr/pwrDeviceLib.h>
#include <hwif/pwr/pwrCpuLib.h>
#include <hwif/pwr/pwrCpuMonLib.h>
#include <hwif/pwr/pwrPolicyLib.h>
#include <hwif/pwr/pwrPolicyMgr.h>
#include <hwif/pwr/pwrTickless.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

/* INCLUDE_DEV_PWR_MGMT */

#define PWR_DEV_INIT (pwrLibFuncs.pwrDeviceLibInit != NULL)
#define PWR_DEV_INIT_FUNC (*(pwrLibFuncs.pwrDeviceLibInit))
#define PWR_DEV_START (pwrLibFuncs.pwrDeviceLibStart != NULL)
#define PWR_DEV_START_FUNC (*(pwrLibFuncs.pwrDeviceLibStart))
#define PWR_DEV_ROOT_GET (pwrLibFuncs.pwrDeviceRootGet != NULL)
#define PWR_DEV_ROOT_GET_FUNC (*(pwrLibFuncs.pwrDeviceRootGet))
#define PWR_DEV_ID_GET (pwrLibFuncs.pwrDeviceIdGet != NULL)
#define PWR_DEV_ID_GET_FUNC (*(pwrLibFuncs.pwrDeviceIdGet))
#define PWR_DEV_ANNOUNCE (pwrLibFuncs.pwrDeviceAnnounce != NULL)
#define PWR_DEV_ANNOUNCE_FUNC (*(pwrLibFuncs.pwrDeviceAnnounce))
#define PWR_DEV_UTIL_SET (pwrLibFuncs.pwrDeviceUtilizationSet != NULL)
#define PWR_DEV_UTIL_SET_FUNC (*(pwrLibFuncs.pwrDeviceUtilizationSet))
#define PWR_DEV_UTIL_GET (pwrLibFuncs.pwrDeviceUtilizationGet != NULL)
#define PWR_DEV_UTIL_GET_FUNC (*(pwrLibFuncs.pwrDeviceUtilizationGet))
#define PWR_DEV_STATE_SET (pwrLibFuncs.pwrDeviceStateSet != NULL)
#define PWR_DEV_STATE_SET_FUNC (*(pwrLibFuncs.pwrDeviceStateSet))
#define PWR_DEV_STATE_GET (pwrLibFuncs.pwrDeviceStateGet != NULL)
#define PWR_DEV_STATE_GET_FUNC (*(pwrLibFuncs.pwrDeviceStateGet))
#define PWR_DEV_STATE_REQ_GET (pwrLibFuncs.pwrDeviceStateRequestedGet != NULL)
#define PWR_DEV_STATE_REQ_GET_FUNC (*(pwrLibFuncs.pwrDeviceStateRequestedGet))
#define PWR_DEV_TO_SET (pwrLibFuncs.pwrDeviceTimeoutSet != NULL)
#define PWR_DEV_TO_SET_FUNC (*(pwrLibFuncs.pwrDeviceTimeoutSet))
#define PWR_DEV_METRICS_GET (pwrLibFuncs.pwrDeviceMetricsGet != NULL)
#define PWR_DEV_METRICS_GET_FUNC (*(pwrLibFuncs.pwrDeviceMetricsGet))
#define PWR_DEV_SHOW (pwrLibFuncs.pwrDeviceShow != NULL)
#define PWR_DEV_SHOW_FUNC (*(pwrLibFuncs.pwrDeviceShow))
#define PWR_DEV_SHOW_ALL (pwrLibFuncs.pwrDeviceShowAll != NULL)
#define PWR_DEV_SHOW_ALL_FUNC (*(pwrLibFuncs.pwrDeviceShowAll))
#define PWR_DEV_STATE_SHOW_ALL (pwrLibFuncs.pwrDeviceStateShowAll != NULL)
#define PWR_DEV_STATE_SHOW_ALL_FUNC (*(pwrLibFuncs.pwrDeviceStateShowAll))
#define PWR_DEV_EVT_HNDLR_REG (pwrLibFuncs.pwrDeviceEventHandlerRegister != NULL)
#define PWR_DEV_EVT_HNDLR_REG_FUNC (*(pwrLibFuncs.pwrDeviceEventHandlerRegister))
#define PWR_DEV_EVT_HNDLR_UNREG (pwrLibFuncs.pwrDeviceEventHandlerUnregister != NULL)
#define PWR_DEV_EVT_HNDLR_UNREG_FUNC (*(pwrLibFuncs.pwrDeviceEventHandlerUnregister))
#define PWR_DEV_ENA_SET (pwrLibFuncs.pwrDeviceEnableSet != NULL)
#define PWR_DEV_ENA_SET_FUNC (*(pwrLibFuncs.pwrDeviceEnableSet))
#define PWR_DEV_ENA_GET (pwrLibFuncs.pwrDeviceEnableGet != NULL)
#define PWR_DEV_ENA_GET_FUNC (*(pwrLibFuncs.pwrDeviceEnableGet))
#define PWR_DEV_CAP_SET (pwrLibFuncs.pwrDeviceCapabilitySet != NULL)
#define PWR_DEV_CAP_SET_FUNC (*(pwrLibFuncs.pwrDeviceCapabilitySet))
#define PWR_DEV_CAP_GET (pwrLibFuncs.pwrDeviceCapabilityGet != NULL)
#define PWR_DEV_CAP_GET_FUNC (*(pwrLibFuncs.pwrDeviceCapabilityGet))
#define PWR_DEV_SAVE (pwrLibFuncs.pwrDeviceLibSave != NULL)
#define PWR_DEV_SAVE_FUNC (*(pwrLibFuncs.pwrDeviceLibSave))
#define PWR_DEV_RESTORE (pwrLibFuncs.pwrDeviceLibRestore != NULL)
#define PWR_DEV_RESTORE_FUNC (*(pwrLibFuncs.pwrDeviceLibRestore))
#define PWR_DEV_CNTXT_SET (pwrLibFuncs.pwrDeviceContextSet != NULL)
#define PWR_DEV_CNTXT_SET_FUNC (*(pwrLibFuncs.pwrDeviceContextSet))
#define PWR_DEV_CNTXT_GET (pwrLibFuncs.pwrDeviceContextGet != NULL)
#define PWR_DEV_CNTXT_GET_FUNC (*(pwrLibFuncs.pwrDeviceContextGet))

/* INCLUDE_CPU_PWR_MGMT */

#define PWR_CPU_EVT_HNDLR_REG (pwrLibFuncs.pwrCpuEventHandlerRegister != NULL)
#define PWR_CPU_EVT_HNDLR_REG_FUNC (*(pwrLibFuncs.pwrCpuEventHandlerRegister))
#define PWR_CPU_EVT_HNDLR_UNREG (pwrLibFuncs.pwrCpuEventHandlerUnregister != NULL)
#define PWR_CPU_EVT_HNDLR_UNREG_FUNC (*(pwrLibFuncs.pwrCpuEventHandlerUnregister))

/* INCLUDE_PWR_CPU_MON */

#define PWR_CPU_MON_INIT (pwrLibFuncs.pwrCpuMonLibInit != NULL)
#define PWR_CPU_MON_INIT_FUNC (*(pwrLibFuncs.pwrCpuMonLibInit))
#define PWR_CPU_MON_RST (pwrLibFuncs.pwrCpuMonReset != NULL)
#define PWR_CPU_MON_RST_FUNC (*(pwrLibFuncs.pwrCpuMonReset))
#define PWR_CPU_MON_CFG (pwrLibFuncs.pwrCpuMonConfigure != NULL)
#define PWR_CPU_MON_CFG_FUNC (*(pwrLibFuncs.pwrCpuMonConfigure))
#define PWR_CPU_MON_CFG_GET (pwrLibFuncs.pwrCpuMonConfigGet != NULL)
#define PWR_CPU_MON_CFG_GET_FUNC (*(pwrLibFuncs.pwrCpuMonConfigGet))
#define PWR_CPU_MON_EVT_REG (pwrLibFuncs.pwrCpuMonEventRegister != NULL)
#define PWR_CPU_MON_EVT_REG_FUNC (*(pwrLibFuncs.pwrCpuMonEventRegister))
#define PWR_CPU_MON_UTIL_REG (pwrLibFuncs.pwrCpuMonUtilRegister != NULL)
#define PWR_CPU_MON_UTIL_REG_FUNC (*(pwrLibFuncs.pwrCpuMonUtilRegister))
#define PWR_CPU_MON_UTIL_GET (pwrLibFuncs.pwrCpuMonUtilGet != NULL)
#define PWR_CPU_MON_UTIL_GET_FUNC (*(pwrLibFuncs.pwrCpuMonUtilGet))
#define PWR_CPU_MON_METRICS_GET (pwrLibFuncs.pwrCpuMonMetricsGet != NULL)
#define PWR_CPU_MON_METRICS_GET_FUNC (*(pwrLibFuncs.pwrCpuMonMetricsGet))

/* INCLUDE_PWR_POLICY_MGR */

#define PWR_POLICY_MGR_CPU_SHOW (pwrLibFuncs.pwrPolicyMgrCpuShow != NULL)
#define PWR_POLICY_MGR_CPU_SHOW_FUNC (*(pwrLibFuncs.pwrPolicyMgrCpuShow))
#define PWR_POLICY_MGR_CPU_SHOW_ALL (pwrLibFuncs.pwrPolicyMgrCpuShowAll != NULL)
#define PWR_POLICY_MGR_CPU_SHOW_ALL_FUNC (*(pwrLibFuncs.pwrPolicyMgrCpuShowAll))
#define PWR_POLICY_MGR_DEV_SHOW (pwrLibFuncs.pwrPolicyMgrDevShow != NULL)
#define PWR_POLICY_MGR_DEV_SHOW_FUNC (*(pwrLibFuncs.pwrPolicyMgrDevShow))
#define PWR_POLICY_MGR_DEV_SHOW_ALL (pwrLibFuncs.pwrPolicyMgrDevShowAll != NULL)
#define PWR_POLICY_MGR_DEV_SHOW_ALL_FUNC (*(pwrLibFuncs.pwrPolicyMgrDevShowAll))
#define PWR_POLICY_MGR_SHOW (pwrLibFuncs.pwrPolicyMgrShow != NULL)
#define PWR_POLICY_MGR_SHOW_FUNC (*(pwrLibFuncs.pwrPolicyMgrShow))
#define PWR_POLICY_ENABLE (pwrLibFuncs.pwrPolicyEnable != NULL)
#define PWR_POLICY_ENABLE_FUNC (*(pwrLibFuncs.pwrPolicyEnable))
#define PWR_POLICY_DISABLE (pwrLibFuncs.pwrPolicyDisable != NULL)
#define PWR_POLICY_DISABLE_FUNC (*(pwrLibFuncs.pwrPolicyDisable))
#define PWR_POLICY_CPU_SET (pwrLibFuncs.pwrPolicyCpuSet != NULL)
#define PWR_POLICY_CPU_SET_FUNC (*(pwrLibFuncs.pwrPolicyCpuSet))
#define PWR_POLICY_CPU_GET (pwrLibFuncs.pwrPolicyCpuGet != NULL)
#define PWR_POLICY_CPU_GET_FUNC (*(pwrLibFuncs.pwrPolicyCpuGet))
#define PWR_POLICY_CPU_SHOW (pwrLibFuncs.pwrPolicyCpuShow != NULL)
#define PWR_POLICY_CPU_SHOW_FUNC (*(pwrLibFuncs.pwrPolicyCpuShow))
#define PWR_POLICY_PSTATE_CAP_GET (pwrLibFuncs.pwrPolicyPstateCapabilityGet != NULL)
#define PWR_POLICY_PSTATE_CAP_GET_FUNC (*(pwrLibFuncs.pwrPolicyPstateCapabilityGet))
#define PWR_POLICY_CSTATE_CAP_GET (pwrLibFuncs.pwrPolicyCstateCapabilityGet != NULL)
#define PWR_POLICY_CSTATE_CAP_GET_FUNC (*(pwrLibFuncs.pwrPolicyCstateCapabilityGet))
#define PWR_POLICY_DEV_SET (pwrLibFuncs.pwrPolicyDevSet != NULL)
#define PWR_POLICY_DEV_SET_FUNC (*(pwrLibFuncs.pwrPolicyDevSet))
#define PWR_POLICY_DEV_GET (pwrLibFuncs.pwrPolicyDevGet != NULL)
#define PWR_POLICY_DEV_GET_FUNC (*(pwrLibFuncs.pwrPolicyDevGet))
#define PWR_POLICY_DEV_SHOW (pwrLibFuncs.pwrPolicyDevShow != NULL)
#define PWR_POLICY_DEV_SHOW_FUNC (*(pwrLibFuncs.pwrPolicyDevShow))
#define PWR_POLICY_PEV_REG (pwrLibFuncs.pwrPolicyPEVCallbackRegister != NULL)
#define PWR_POLICY_PEV_REG_FUNC (*(pwrLibFuncs.pwrPolicyPEVCallbackRegister))
#define PWR_POLICY_PEV_UNREG (pwrLibFuncs.pwrPolicyPEVCallbackUnregister != NULL)
#define PWR_POLICY_PEV_UNREG_FUNC (*(pwrLibFuncs.pwrPolicyPEVCallbackUnregister))

/* INCLUDE_PWR_POLICY_STATS */

#define PWR_POLICY_MGR_CPU_STATE_RST (pwrLibFuncs.pwrPolicyMgrCpuStateReset != NULL)
#define PWR_POLICY_MGR_CPU_STATE_RST_FUNC (*(pwrLibFuncs.pwrPolicyMgrCpuStateReset))
#define PWR_POLICY_MGR_CPU_STATE_SHOW (pwrLibFuncs.pwrPolicyMgrCpuStateShow != NULL)
#define PWR_POLICY_MGR_CPU_STATE_SHOW_FUNC (*(pwrLibFuncs.pwrPolicyMgrCpuStateShow))
#define PWR_POLICY_MGR_CPU_STATE_GET (pwrLibFuncs.pwrPolicyMgrCpuStateGet != NULL)
#define PWR_POLICY_MGR_CPU_STATE_GET_FUNC (*(pwrLibFuncs.pwrPolicyMgrCpuStateGet))
#define PWR_POLICY_MGR_CPU_PEV_GET (pwrLibFuncs.pwrPolicyMgrCpuPevGet != NULL)
#define PWR_POLICY_MGR_CPU_PEV_GET_FUNC (*(pwrLibFuncs.pwrPolicyMgrCpuPevGet))
#define PWR_POLICY_MGR_DEV_STATE_RST (pwrLibFuncs.pwrPolicyMgrDevStateReset != NULL)
#define PWR_POLICY_MGR_DEV_STATE_RST_FUNC (*(pwrLibFuncs.pwrPolicyMgrDevStateReset))
#define PWR_POLICY_MGR_DEV_STATE_SHOW (pwrLibFuncs.pwrPolicyMgrDevStateShow != NULL)
#define PWR_POLICY_MGR_DEV_STATE_SHOW_FUNC (*(pwrLibFuncs.pwrPolicyMgrDevStateShow))
#define PWR_POLICY_MGR_DEV_STATE_GET (pwrLibFuncs.pwrPolicyMgrDevStateGet != NULL)
#define PWR_POLICY_MGR_DEV_STATE_GET_FUNC (*(pwrLibFuncs.pwrPolicyMgrDevStateGet))
#define PWR_POLICY_PEV_SEND (pwrLibFuncs.pwrPolicyPEVSend != NULL)
#define PWR_POLICY_PEV_SEND_FUNC (*(pwrLibFuncs.pwrPolicyPEVSend))

/* INCLUDE_TICKLESS_IDLE */

#define PWR_TICKLESS_CSTATE_CONFIG (pwrLibFuncs.pwrTicklessCStateConfig != NULL)
#define PWR_TICKLESS_CSTATE_CONFIG_FUNC (*(pwrLibFuncs.pwrTicklessCStateConfig))

#define PWR_TICKLESS_ONE_SHOT_TIMER_FIND (pwrLibFuncs.pwrTicklessOneShotTimerFind != NULL)
#define PWR_TICKLESS_ONE_SHOT_TIMER_FIND_FUNC (*(pwrLibFuncs.pwrTicklessOneShotTimerFind))
#define PWR_TICKLESS_ONE_SHOT_TIMER_ENABLE (pwrLibFuncs.pwrTicklessOneShotTimerEnable != NULL)
#define PWR_TICKLESS_ONE_SHOT_TIMER_ENABLE_FUNC (*(pwrLibFuncs.pwrTicklessOneShotTimerEnable))
#define PWR_TICKLESS_ONE_SHOT_TIMER_DISABLE (pwrLibFuncs.pwrTicklessOneShotTimerDisable != NULL)
#define PWR_TICKLESS_ONE_SHOT_TIMER_DISABLE_FUNC (*(pwrLibFuncs.pwrTicklessOneShotTimerDisable))
#define PWR_TICKLESS_CONVERT_TO_TICKS (pwrLibFuncs.pwrTicklessConvertToTicks != NULL)
#define PWR_TICKLESS_CONVERT_TO_TICKS_FUNC (*(pwrLibFuncs.pwrTicklessConvertToTicks))
#define PWR_TICKLESS_CONVERT_FROM_TICKS (pwrLibFuncs.pwrTicklessConvertFromTicks != NULL)
#define PWR_TICKLESS_CONVERT_FROM_TICKS_FUNC (*(pwrLibFuncs.pwrTicklessConvertFromTicks))
#define PWR_TICKLESS_SYSTEM_CLOCK_OFF (pwrLibFuncs.pwrTicklessSystemClockOff != NULL)
#define PWR_TICKLESS_SYSTEM_CLOCK_OFF_FUNC (*(pwrLibFuncs.pwrTicklessSystemClockOff))
#define PWR_TICKLESS_SYSTEM_CLOCK_ON (pwrLibFuncs.pwrTicklessSystemClockOn != NULL)
#define PWR_TICKLESS_SYSTEM_CLOCK_ON_FUNC (*(pwrLibFuncs.pwrTicklessSystemClockOn))
#define PWR_TICKLESS_CSTATE_SET_RETENTION (pwrLibFuncs.pwrTicklessCStateSetRetention != NULL)
#define PWR_TICKLESS_CSTATE_SET_RETENTION_FUNC (*(pwrLibFuncs.pwrTicklessCStateSetRetention))
#define PWR_TICKLESS_CSTATE_SET_REFRESH (pwrLibFuncs.pwrTicklessCStateSetRefresh != NULL)
#define PWR_TICKLESS_CSTATE_SET_REFRESH_FUNC (*(pwrLibFuncs.pwrTicklessCStateSetRefresh))
#define PWR_TICKLESS_CSTATE_SET (pwrLibFuncs.pwrTicklessCStateSet != NULL)
#define PWR_TICKLESS_CSTATE_SET_FUNC (*(pwrLibFuncs.pwrTicklessCStateSet))

/* forward declarations */

/* locals */

/* imports */

typedef struct
    {

    /* INCLUDE_DEV_PWR_MGMT */

    STATUS (*pwrDeviceLibInit) (void);

    STATUS (*pwrDeviceLibStart)
        (
        BOOL createMonitor,
        _Vx_ticks_t pollTicks
        );

    PWR_DEVICE_ID (*pwrDeviceRootGet) (void);

    PWR_DEVICE_ID (*pwrDeviceIdGet)
        (
        char *name,
        int unitNumber
        );

    PWR_DEVICE_ID (*pwrDeviceAnnounce)
        (
        VXB_DEVICE_ID vxbDevId,
        void *  pArg            /* not used */
        );

    STATUS (*pwrDeviceUtilizationSet)
        (
        PWR_DEVICE_ID pwrDeviceId
        );

    BOOL (*pwrDeviceUtilizationGet)
        (
        PWR_DEVICE_ID pwrDeviceId
        );

    STATUS (*pwrDeviceStateSet)
        (
        char *name,
        UINT32 unitNumber,
        UINT32 state
        );

    UINT32 (*pwrDeviceStateGet)
        (
        PWR_DEVICE_ID pwrDeviceId
        );

    UINT32 (*pwrDeviceStateRequestedGet)
        (
        PWR_DEVICE_ID pwrDeviceId
        );

    void (*pwrDeviceTimeoutSet)
        (
        PWR_DEVICE_ID pwrDeviceId,
        UINT32 timeout
        );

    void (*pwrDeviceMetricsGet)
        (
        PWR_DEVICE_ID pwrDeviceId,
        PWR_DEVICE_METRIC *pMetric
        );

    void (*pwrDeviceShow)
        (
        char *name,
        UINT32 unitNumber
        );

    void (*pwrDeviceShowAll) (void);
    void (*pwrDeviceStateShowAll) (void);

    STATUS (*pwrDeviceEventHandlerRegister)
        (
        PWR_DEVICE_ID           pwrDeviceId,
        erfHandlerPrototype     *pEventHandler,
        void                    *pUserData
        );

    STATUS (*pwrDeviceEventHandlerUnregister)
        (
        PWR_DEVICE_ID           pwrDeviceId,
        erfHandlerPrototype     *pEventHandler,
        void                    *pUserData
        );

    void (*pwrDeviceEnableSet)
        (
        PWR_DEVICE_ID pwrDeviceId,
        UINT32 flags
        );

    UINT32 (*pwrDeviceEnableGet)
        (
        PWR_DEVICE_ID pwrDeviceId
        );

    void (*pwrDeviceCapabilitySet)
        (
        PWR_DEVICE_ID pwrDeviceId,
        UINT32 flags
        );

    UINT32 (*pwrDeviceCapabilityGet)
        (
        PWR_DEVICE_ID pwrDeviceId
        );

    void (*pwrDeviceLibSave) (void);
    void (*pwrDeviceLibRestore) (void);

    void (*pwrDeviceContextSet)
        (
        PWR_DEVICE_ID pwrDeviceId,
        void *context
        );

    void * (*pwrDeviceContextGet)
        (
        PWR_DEVICE_ID pwrDeviceId
        );

    /* INCLUDE_CPU_PWR_MGMT */

    STATUS (*pwrCpuEventHandlerRegister)
        (
        pwrEventType 	eventType,
        erfHandlerPrototype *pEventHandler,
        void 		*pUserData
        );

    STATUS (*pwrCpuEventHandlerUnregister)
        (
        pwrEventType 	eventType,
        erfHandlerPrototype *pEventHandler,
        void 		*pUserData
        );

    /* INCLUDE_PWR_CPU_MON */

    STATUS (*pwrCpuMonLibInit) (void);
    STATUS (*pwrCpuMonReset)
        (
        UINT32 cpuNum
        );
    STATUS (*pwrCpuMonConfigure)
        (
        UINT32 cpuNum,
        PWR_POLICY_CPU *cfg
        );
    STATUS (*pwrCpuMonConfigGet)
        (
        UINT32 cpuNum,
        PWR_POLICY_CPU *cfg
        );
    STATUS (*pwrCpuMonEventRegister)
        (
        UINT32 cpuNum,
        PWR_CPU_MON_EVENT_HANDLERS *handlers
        );
    STATUS (*pwrCpuMonUtilRegister)
        (
        UINT32 cpuNum,
        PWR_CPU_MON_UTIL_HANDLERS *handlers
        );
    UINT32 (*pwrCpuMonUtilGet)
        (
        UINT32 cpuNum
        );
    STATUS (*pwrCpuMonMetricsGet)
        (
        UINT32 cpuNum,
        PWR_CPU_MON_METRICS *metrics
        );

    /* INCLUDE_PWR_POLICY_MGR */

    STATUS (*pwrPolicyMgrCpuShow)
        (
        UINT32 cpuNum,
        UINT32 level
        );

    STATUS (*pwrPolicyMgrCpuShowAll) (void);

    STATUS (*pwrPolicyMgrDevShow)
        (
        char *devName,
        UINT32 unitNum,
        UINT32 level
        );

    STATUS (*pwrPolicyMgrDevShowAll) (void);
    STATUS (*pwrPolicyMgrShow) (void);

    STATUS (*pwrPolicyEnable) (void);
    STATUS (*pwrPolicyDisable) (void);

    STATUS (*pwrPolicyCpuSet)
        (
        UINT32 cpuNum,
        PWR_POLICY_CPU *cpuPolicy
        );

    STATUS (*pwrPolicyCpuGet)
        (
        UINT32 cpuNum,
        PWR_POLICY_CPU *cpuPolicy
        );

    STATUS (*pwrPolicyCpuShow)
        (
        UINT32 cpuNum
        );

    UINT32 (*pwrPolicyPstateCapabilityGet)
        (
        UINT32 cpuNum
        );

    UINT32 (*pwrPolicyCstateCapabilityGet)
        (
        UINT32 cpuNum
        );

    STATUS (*pwrPolicyDevSet)
        (
        char *devName,
        UINT32 unitNum,
        PWR_POLICY_DEV *devPolicy
        );

    STATUS (*pwrPolicyDevGet)
        (
        char *devName,
        UINT32 unitNum,
        PWR_POLICY_DEV *devPolicy
        );

    STATUS (*pwrPolicyDevShow)
        (
        char *devName,
        UINT32 unitNum
        );

    STATUS (*pwrPolicyPEVCallbackRegister)
        (
        pwrEventType eventType,
        erfHandlerPrototype *pEventHandler,
        void *pUserData
        );

    STATUS (*pwrPolicyPEVCallbackUnregister)
        (
        pwrEventType eventType,
        erfHandlerPrototype *pEventHandler,
        void *pUserData
        );

    /* INCLUDE_PWR_POLICY_STATS */

    STATUS (*pwrPolicyMgrCpuStateReset)
        (
        UINT32 cpuNum
        );

    STATUS (*pwrPolicyMgrCpuStateShow)
        (
        UINT32 cpuNum
        );

    STATUS (*pwrPolicyMgrCpuStateGet)
        (
        UINT32 cpuNum,
        UINT32 stateNum,
        pwrStateType stateType,
        PWR_STATE_METRIC *pMetric
        );

    STATUS (*pwrPolicyMgrCpuPevGet)
        (
        UINT32 cpuNum,
        PWR_EVENT_CPU_METRIC *pMetric
        );

    STATUS (*pwrPolicyMgrDevStateReset)
        (
        char *devName,
        UINT32 unitNum
        );

    STATUS (*pwrPolicyMgrDevStateShow)
        (
        char *devName,
        UINT32 unitNum
        );

    STATUS (*pwrPolicyMgrDevStateGet)
        (
        char *devName,
        UINT32 unitNum,
        UINT32 stateNum,
        PWR_STATE_METRIC *pMetric
        );

    STATUS (*pwrPolicyPEVSend)
        (
        UINT32 eventBitMask,
        _Vx_ticks64_t numTicks,
        void *param
        );

    /* INCLUDE_TICKLESS_IDLE */

    void (*pwrTicklessCStateConfig)
        (
        UINT32 cpu,
        UINT32 config
        );

    VXB_DEVICE_ID (*pwrTicklessOneShotTimerFind) (void);

    STATUS (*pwrTicklessOneShotTimerEnable)
        (
        VXB_DEVICE_ID pInst,
        PWR_TICKLESS_ONE_SHOT_TICK_TYPE val,
        void *pIsr,
        UINT32 arg
        );

    PWR_TICKLESS_ONE_SHOT_TICK_TYPE (*pwrTicklessOneShotTimerDisable)
        (
        VXB_DEVICE_ID pInst
        );

    PWR_TICKLESS_CLOCK_TICK_TYPE (*pwrTicklessConvertToTicks)
        (
        PWR_TICKLESS_ONE_SHOT_TICK_TYPE val
        );

    PWR_TICKLESS_ONE_SHOT_TICK_TYPE (*pwrTicklessConvertFromTicks)
        (
        PWR_TICKLESS_CLOCK_TICK_TYPE ticks
        );

    void (*pwrTicklessSystemClockOff) (void);

    void (*pwrTicklessSystemClockOn) (void);

    void (*pwrTicklessCStateSetRetention)
        (
        UINT32 cState
        );

    void (*pwrTicklessCStateSetRefresh)
        (
        UINT32 cState
        );

    void (*pwrTicklessCStateSet)
        (
        UINT32 cState
        );

    } PWR_LIB_FUNCS;


/* Global Structure Instantiation */

    PWR_LIB_FUNCS pwrLibFuncs;

#ifdef __cplusplus
}
#endif

#endif /* PWRLIBFUNCS_H */


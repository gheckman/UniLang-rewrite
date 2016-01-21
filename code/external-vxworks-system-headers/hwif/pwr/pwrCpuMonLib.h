/* pwrCpuMonLib.h - CPU load monitor library header file */

/*
 * Copyright (c) 2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01h,19oct11,sem  WIND00312771 - Update timestamp API
01g,19sep11,jlv  Add pwrCpuMonConfigGet API
01f,25aug11,sem  WIND00295172 - Remove pwrCpuMonIdGet
01e,22aug11,jlv  WIND00295172 - Remove CPU PowerId
01d,16aug11,sem  WIND00255354 - Optimize for SMP
01c,10aug11,sem  WIND00292261 - Update load monitor timestamping
01b,02aug11,sem  Add support for sleep headroom - Reqt WIND00255354
01a,15jul11,sem  created - Reqt WIND00255354
*/

#ifndef __INCpwrCpuMonLibh
#define __INCpwrCpuMonLibh

#include <vxWorks.h>
#include <vsbConfig.h>
#include <hwif/pwr/pwrPolicyLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* CPU monitor timestamp type */

#if (CPU_FAMILY == I80X86) && (CPU != PENTIUM)
typedef UINT64 PWR_CPU_MON_TIMESTAMP;
#else
typedef UINT32 PWR_CPU_MON_TIMESTAMP;
#endif /* ((CPU_FAMILY == I80X86) && (CPU != PENTIUM)) */

/* CPU monitor timestamp routine signatures */

typedef PWR_CPU_MON_TIMESTAMP (*pwrCpuMonTimestampGet_func)(void);
typedef void   (*pwrCpuMonTimestampReset_func)(void);

/* CPU montitor event handler routine signature */

typedef void (*pwrCpuMonEventRtn) (UINT32 param, UINT32 cpuNum);
 
 /* CPU monitor event handler routines and parameters */
 
typedef struct pwrCpuMonEventHandlers
    {
    pwrCpuMonEventRtn    lowHeadroomAlarmRtn;    /* callback routine for low headroom alarm events */
    UINT32               lowHeadroomAlarmParam;  /* callback parameter for low headroom alarm events */
    pwrCpuMonEventRtn    lowHeadroomRtn;         /* callback routine for low headroom events */
    UINT32               lowHeadroomParam;       /* callback parameter for low headroom events */
    pwrCpuMonEventRtn    sleepHeadroomRtn;       /* callback routine for sleep headroom events */
    UINT32               sleepHeadroomParam;     /* callback parameter for sleep headroom events */
    pwrCpuMonEventRtn    highHeadroomRtn;        /* callback routine for high headroom events */
    UINT32               highHeadroomParam;      /* callback parameter for high headroom events */
    } PWR_CPU_MON_EVENT_HANDLERS;

/* CPU monitor utilization handler routine signature */

typedef UINT32 (*pwrCpuMonUtilRtn) (UINT32 param, UINT32 cpuNum);

/* CPU monitor utilization handlers and parameters */

typedef struct pwrCpuMonUtilHandlers
    {
    pwrCpuMonUtilRtn     utilRtn;         /* callback routine for cpu utilization */          
    UINT32               utilParam;       /* callback parameter for cpu utilization */        
    } PWR_CPU_MON_UTIL_HANDLERS;
    
/* CPU monitor metrics */

typedef struct pwrCpuMonMetrics
    {
    UINT32        util;                    /* utilization computed over last completed sample interval */
    UINT32        sampleCnt;               /* sample intervals completed */
    UINT32        intrCnt;                 /* interrupt count from last completed sample interval */
    } PWR_CPU_MON_METRICS;

/* timestamp functions */

extern pwrCpuMonTimestampGet_func pwrCpuMonTimestampGetFunc;
extern pwrCpuMonTimestampReset_func pwrCpuMonTimestampResetFunc;
    
extern STATUS pwrCpuMonLibInit (void);
extern STATUS pwrCpuMonReset (UINT32 cpuNum);
extern STATUS pwrCpuMonConfigure (UINT32 cpuNum, PWR_POLICY_CPU *cfg);
extern STATUS pwrCpuMonConfigGet (UINT32 cpuNum, PWR_POLICY_CPU *cfg);
extern STATUS pwrCpuMonEventRegister (UINT32 cpuNum, PWR_CPU_MON_EVENT_HANDLERS *handlers);
extern STATUS pwrCpuMonUtilRegister (UINT32 cpuNum, PWR_CPU_MON_UTIL_HANDLERS *handlers);
extern UINT32 pwrCpuMonUtilGet (UINT32 cpuNum);
extern STATUS pwrCpuMonMetricsGet (UINT32 cpuNum, PWR_CPU_MON_METRICS *metrics);

#ifdef __cplusplus
}
#endif

#endif /* __INCpwrCpuMonLibh */

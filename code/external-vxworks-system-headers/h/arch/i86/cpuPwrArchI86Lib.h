/* cpuPwrArchI86Lib.h - CPU Power Mgmt. H/W library specific header */

/*
 * Copyright (c) 2011, 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
*/

/*
modification history
--------------------
01j,27aug12,c_t  WIND00350715 - Add cpuPwrArchTurboUnSet
01i,23aug11,sem  WIND00294323, undef P-state and C-State propagation
01h,18aug11,sem  WIND00294323, fix default P-state values
01g,02aug11,scm  WIND00255355, allow for propagation of CPU C-States...
01f,22jul11,scm  WIND00255355, allow for propagation of CPU[0] P-States...
01e,18jul11,jlv  WIND00255352, add cpuPwrArchPStateGetByCpu
01d,06jul11,rdl  move common APIs to the common header file
01c,05jul11,scm  WIND00255355, adjust inclusion wrapper...
01b,28jun11,scm  WIND00255255, add pwr mgmt arch abstraction...
01a,31may11,scm  WIND00255355, CPU Power State Device Management...
*/

#ifndef __INCcpuPwrArchI86Libh
#define __INCcpuPwrArchI86Libh

#include <vsbConfig.h>

#ifdef __cplusplus
extern "C" {
#endif
	
/* allow for duplication of CPU[0] P-States */

#undef ACPI_PWR_CPU_ARCH_PROPAGATE_CPU_PERF_0

/* allow for duplication of CPU[0] C-States */

#undef ACPI_PWR_CPU_ARCH_PROPAGATE_CPU_C_STATE

/* Power Management support definitions */
	
#define PM_CPUID_KEY                    0x06

#define MSR_IA32_MPERF                  0x00E7
#define MSR_IA32_APERF                  0x00E8

#define MSR_IA32_PERF_STAT              0x0198
#define MSR_IA32_PERF_CTL               0x0199

#define MSR_IA32_MISC_ENABLE            0x01A0

#define MSR_IA32_ENERGY_PERF_BIAS       0x01B0

#define PM_EAX_MSK                      0x00000077
#define PM_EBX_MSK                      0x0000000F
#define PM_ECX_MSK                      0x00000009

#define PM_DTS                          0x00000001
#define PM_TBT                          0x00000002
#define PM_ARAT                         0x00000004
#define PM_PLN                          0x00000010
#define PM_ECMD                         0x00000020
#define PM_PTM                          0x00000040

#define PM_HCFC                         0x00000001

#define PM_OPPO                         0x00000040

#define PM_PEB                          0x00000004
#define PM_PEBH_MSK1                    0x0000000F
#define PM_PEBH_MSK2                    0xFFFFFFF0

#define TM_DISENGAGE_BIT                0x00000001
#define TM_DISENGAGE_MSK                0xFFFFFFFE

#define TM_EIST_TRG_MSK                 0x0000ffff

#ifdef _WRS_CONFIG_LP64
#define cpuPwrArchPMSup1_Offset         0x70
#define cpuPwrArchPMSup2_Offset         0x74
#define cpuPwrArchPMIntThrsh_Offset     0x78
#else
#define cpuPwrArchPMSup1_Offset         0x50
#define cpuPwrArchPMSup2_Offset         0x54
#define cpuPwrArchPMIntThrsh_Offset     0x58
#endif /* _WRS_CONFIG_LP64 */

/* Thermal Management support definitions */
	
#define TM_CPUID_KEY                    0x01

#define MSR_THERM2_CTL                  0x019D

#define MSR_IA32_CLOCK_MODULATION       0x019A

#define MSR_IA32_THERM_INTERRUPT        0x019B
#define MSR_IA32_THERM_STATUS           0x019C

#define MSR_IA32_PACKAGE_THERM_STATUS       0x01B1
#define MSR_IA32_PACKAGE_THERM_INTERRUPT    0x01B2

#define TM_ECX_MSK                      0x00000180
#define TM_EDX_MSK                      0x20400000

#define TM_TM2_TRANS_TRG_MSK            0x0000FFFF
#define TM_TM2_SELECT                   0x00010000

#define TM_ENABLE                       0x00000008

#define TM_TM2                          0x00000100
#define TM_EST                          0x00000080

#define TM_TURBO_EN_BIT                 0x00000040
#define TM_TURBO_EN_MSK                 0xFFFFFFBF

#define TM_TM1                          0x20000000
#define TM_ACPI                         0x00400000

/* ODCM - On-Demand Clock Modulation */

#define TM_ODCM_RES                     0x0000  /* Duty Cycle Reserved */
#define TM_ODCM_06_25                   0x0001  /* Extended Duty Cycle 06.25% */
#define TM_ODCM_12_50                   0x0002  /* Duty Cycle 12.50% -default */
#define TM_ODCM_18_75                   0x0003  /* Extended Duty Cycle 18.75% */
#define TM_ODCM_25_00                   0x0004  /* Duty Cycle 25.00% */
#define TM_ODCM_31_25                   0x0005  /* Extended Duty Cycle 31.25% */
#define TM_ODCM_37_50                   0x0006  /* Duty Cycle 37.50% */
#define TM_ODCM_43_75                   0x0007  /* Extended Duty Cycle 43.75% */
#define TM_ODCM_50_00                   0x0008  /* Duty Cycle 50.00% */
#define TM_ODCM_56_25                   0x0009  /* Extended Duty Cycle 56.25% */
#define TM_ODCM_63_50                   0x000A  /* Duty Cycle 63.50% */
#define TM_ODCM_69_75                   0x000B  /* Extended Duty Cycle 69.75% */
#define TM_ODCM_75_00                   0x000C  /* Duty Cycle 75.00% */
#define TM_ODCM_81_25                   0x000D  /* Extended Duty Cycle 81.25% */
#define TM_ODCM_87_50                   0x000E  /* Duty Cycle 87.50% */
#define TM_ODCM_93_75                   0x000F  /* Extended Duty Cycle 93.75% */

#define TM_ODCM_ENABLE                  0x00000010
#define TM_ODCM_ENABLE_MSK              0xFFFFFFEF

#define TM_ODCM_MSK                     0xFFFFFFF1
#define TM_ODCM_EXT_MSK                 0xFFFFFFF0

#define TM_ODCM_DC_MSK1                 0x0000000E
#define TM_ODCM_DC_MSK2                 0xFFFFFFF1

#define TM_ODCM_DC_EXT_MSK1             0x0000000F
#define TM_ODCM_DC_EXT_MSK2             0xFFFFFFF0

/* IA32_THERM_STATUS Register */

#define TM_STATUS_REG_MSK               0xF87F0FFF

#define TM_STAT_READ_VALID              0x80000000

#define TM_STAT_RES_CELS_MSK            0x71000000
#define TM_STAT_RES_CELS_SHFT           0x19

#define TM_STAT_DIG_READ_MSK            0x007F0000
#define TM_STAT_DIG_READ_SHFT           0x10

#define TM_STAT_PLN_LOG                 0x00000800
#define TM_STAT_PLN_LOG_MSK             0xFFFFF7FF
#define TM_STAT_PLN_STAT                0x00000400

#define TM_STAT_THRSH2_LOG              0x00000200
#define TM_STAT_THRSH2_LOG_MSK          0xFFFFFDFF
#define TM_STAT_THRSH2_STAT             0x00000100

#define TM_STAT_THRSH1_LOG              0x00000080
#define TM_STAT_THRSH1_LOG_MSK          0xFFFFFF7F
#define TM_STAT_THRSH1_STAT             0x00000040

#define TM_STAT_CTEMP_LOG               0x00000020
#define TM_STAT_CTEMP_LOG_MSK           0xFFFFFFDF
#define TM_STAT_CTEMP_STAT              0x00000010

#define TM_STAT_PF_LOG                  0x00000008
#define TM_STAT_PF_LOG_MSK              0xFFFFFFF7
#define TM_STAT_PF_STAT                 0x00000004

#define TM_STATUS_LOG                   0x00000002
#define TM_STATUS_LOG_MSK               0xFFFFFFFD

#define TM_STATUS                       0x00000001

/* IA32_THERM_INTERRUPT Register */

#define TM_INTERRUPT_REG_MSK            0x01FFFF1F

#define TM_INT_PLN_EN                   0x01000000
#define TM_INT_PLN_EN_MSK               0xFEFFFFFF

#define TM_INT_THRSH2_EN                0x00800000
#define TM_INT_THRSH2_EN_MSK            0xFF7FFFFF

#define TM_INT_THRSH2_VAL_MSK1          0x007F0000
#define TM_INT_THRSH2_VAL_MSK2          0xFF80FFFF
#define TM_INT_THRSH2_VAL_SHFT          0x10

#define TM_INT_THRSH1_EN                0x00008000
#define TM_INT_THRSH1_EN_MSK            0xFFFF7FFF

#define TM_INT_THRSH1_VAL_MSK1          0x00007F00
#define TM_INT_THRSH1_VAL_MSK2          0xFFFF80FF
#define TM_INT_THRSH1_VAL_SHFT          0x08

#define TM_INT_OH_EN                    0x00000010
#define TM_INT_OH_EN_MSK                0xFFFFFFEF

#define TM_INT_FORCEPR_EN               0x00000008
#define TM_INT_FORCEPR_EN_MSK           0xFFFFFFF7

#define TM_INT_PROCHOT_EN               0x00000004
#define TM_INT_PROCHOT_EN_MSK           0xFFFFFFFB

#define TM_INT_LTEMP_EN                 0x00000002
#define TM_INT_LTEMP_EN_MSK             0xFFFFFFFD

#define TM_INT_HTEMP_EN                 0x00000001
#define TM_INT_HTEMP_EN_MSK             0xFFFFFFFE

#ifdef _WRS_CONFIG_LP64
#define cpuPwrArchTMSup1_Offset         0x7C
#define cpuPwrArchTMSup2_Offset         0x80 
#else
#define cpuPwrArchTMSup1_Offset         0x5C
#define cpuPwrArchTMSup2_Offset         0x60
#endif /* _WRS_CONFIG_LP64 */

/* thermal zone cooling policy */

#define CPU_PWR_ARCH_COOLING_NONE       0   /* let things cook until hardware limits */
#define CPU_PWR_ARCH_COOLING_ACTIVE     1   /* use fans etc */
#define CPU_PWR_ARCH_COOLING_PASSIVE    2   /* throttle cpu and device utilization */

#ifndef _ASMLANGUAGE

#include <base/b_cpuset_t.h>

#if defined (ACPI_PWR_CPU_ARCH_PROPAGATE_CPU_PERF_0)
/* default Performance options when table missing (based on Emerson) */

#define CPU_PWR_ARCH_DOMAIN_ID                  0x00
#define CPU_PWR_ARCH_COOR_TYPE                  0xFC
#define CPU_PWR_ARCH_NUM_CPUS_IN_DOMAIN         0x01

#define CPU_PWR_ARCH_NUM_PERF			13  
#define CPU_PWR_ARCH_NUM_PERF_NOT_SUP           0
#define CPU_PWR_ARCH_NUM_P_STATES		CPU_PWR_ARCH_NUM_PERF

#define CPU_PWR_ARCH_PERF_CONTROL		0x00000199
#define CPU_PWR_ARCH_PERF_STATUS 		0x00000198

#define CPU_PWR_ARCH_PERF_DFLT_1_CORE_FREQ      2667 
#define CPU_PWR_ARCH_PERF_DFLT_1_POWER          25000 
#define CPU_PWR_ARCH_PERF_DFLT_1_TRANSITION     10   
#define CPU_PWR_ARCH_PERF_DFLT_1_BUS_MASTER     10    
#define CPU_PWR_ARCH_PERF_DFLT_1_CTRL_REG_VAL   0x0015
#define CPU_PWR_ARCH_PERF_DFLT_1_STAT_REG_VAL   0x0015

#define CPU_PWR_ARCH_PERF_DFLT_2_CORE_FREQ      2666
#define CPU_PWR_ARCH_PERF_DFLT_2_POWER          25000 
#define CPU_PWR_ARCH_PERF_DFLT_2_TRANSITION     10  
#define CPU_PWR_ARCH_PERF_DFLT_2_BUS_MASTER     10  
#define CPU_PWR_ARCH_PERF_DFLT_2_CTRL_REG_VAL   0x0014
#define CPU_PWR_ARCH_PERF_DFLT_2_STAT_REG_VAL   0x0014

#define CPU_PWR_ARCH_PERF_DFLT_3_CORE_FREQ      2533 
#define CPU_PWR_ARCH_PERF_DFLT_3_POWER          23465
#define CPU_PWR_ARCH_PERF_DFLT_3_TRANSITION     10   
#define CPU_PWR_ARCH_PERF_DFLT_3_BUS_MASTER     10    
#define CPU_PWR_ARCH_PERF_DFLT_3_CTRL_REG_VAL   0x0013
#define CPU_PWR_ARCH_PERF_DFLT_3_STAT_REG_VAL   0x0013

#define CPU_PWR_ARCH_PERF_DFLT_4_CORE_FREQ      2399 
#define CPU_PWR_ARCH_PERF_DFLT_4_POWER          21982 
#define CPU_PWR_ARCH_PERF_DFLT_4_TRANSITION     10   
#define CPU_PWR_ARCH_PERF_DFLT_4_BUS_MASTER     10    
#define CPU_PWR_ARCH_PERF_DFLT_4_CTRL_REG_VAL   0x0012
#define CPU_PWR_ARCH_PERF_DFLT_4_STAT_REG_VAL   0x0012

#define CPU_PWR_ARCH_PERF_DFLT_5_CORE_FREQ      2266 
#define CPU_PWR_ARCH_PERF_DFLT_5_POWER          20527 
#define CPU_PWR_ARCH_PERF_DFLT_5_TRANSITION     10   
#define CPU_PWR_ARCH_PERF_DFLT_5_BUS_MASTER     10    
#define CPU_PWR_ARCH_PERF_DFLT_5_CTRL_REG_VAL   0x0011
#define CPU_PWR_ARCH_PERF_DFLT_5_STAT_REG_VAL   0x0011

#define CPU_PWR_ARCH_PERF_DFLT_6_CORE_FREQ      2133 
#define CPU_PWR_ARCH_PERF_DFLT_6_POWER          19080 
#define CPU_PWR_ARCH_PERF_DFLT_6_TRANSITION     10   
#define CPU_PWR_ARCH_PERF_DFLT_6_BUS_MASTER     10    
#define CPU_PWR_ARCH_PERF_DFLT_6_CTRL_REG_VAL   0x0010
#define CPU_PWR_ARCH_PERF_DFLT_6_STAT_REG_VAL   0x0010

#define CPU_PWR_ARCH_PERF_DFLT_7_CORE_FREQ      1999 
#define CPU_PWR_ARCH_PERF_DFLT_7_POWER          17681 
#define CPU_PWR_ARCH_PERF_DFLT_7_TRANSITION     10   
#define CPU_PWR_ARCH_PERF_DFLT_7_BUS_MASTER     10    
#define CPU_PWR_ARCH_PERF_DFLT_7_CTRL_REG_VAL   0x000F
#define CPU_PWR_ARCH_PERF_DFLT_7_STAT_REG_VAL   0x000F

#define CPU_PWR_ARCH_PERF_DFLT_8_CORE_FREQ      1866 
#define CPU_PWR_ARCH_PERF_DFLT_8_POWER          16310 
#define CPU_PWR_ARCH_PERF_DFLT_8_TRANSITION     10   
#define CPU_PWR_ARCH_PERF_DFLT_8_BUS_MASTER     10    
#define CPU_PWR_ARCH_PERF_DFLT_8_CTRL_REG_VAL   0x000E
#define CPU_PWR_ARCH_PERF_DFLT_8_STAT_REG_VAL   0x000E

#define CPU_PWR_ARCH_PERF_DFLT_9_CORE_FREQ      1733 
#define CPU_PWR_ARCH_PERF_DFLT_9_POWER          14966 
#define CPU_PWR_ARCH_PERF_DFLT_9_TRANSITION     10   
#define CPU_PWR_ARCH_PERF_DFLT_9_BUS_MASTER     10    
#define CPU_PWR_ARCH_PERF_DFLT_9_CTRL_REG_VAL   0x000D
#define CPU_PWR_ARCH_PERF_DFLT_9_STAT_REG_VAL   0x000D

#define CPU_PWR_ARCH_PERF_DFLT_10_CORE_FREQ      1599 
#define CPU_PWR_ARCH_PERF_DFLT_10_POWER          13665 
#define CPU_PWR_ARCH_PERF_DFLT_10_TRANSITION     10   
#define CPU_PWR_ARCH_PERF_DFLT_10_BUS_MASTER     10    
#define CPU_PWR_ARCH_PERF_DFLT_10_CTRL_REG_VAL   0x000C
#define CPU_PWR_ARCH_PERF_DFLT_10_STAT_REG_VAL   0x000C

#define CPU_PWR_ARCH_PERF_DFLT_11_CORE_FREQ      1466 
#define CPU_PWR_ARCH_PERF_DFLT_11_POWER          12375 
#define CPU_PWR_ARCH_PERF_DFLT_11_TRANSITION     10   
#define CPU_PWR_ARCH_PERF_DFLT_11_BUS_MASTER     10    
#define CPU_PWR_ARCH_PERF_DFLT_11_CTRL_REG_VAL   0x000B
#define CPU_PWR_ARCH_PERF_DFLT_11_STAT_REG_VAL   0x000B

#define CPU_PWR_ARCH_PERF_DFLT_12_CORE_FREQ      1333 
#define CPU_PWR_ARCH_PERF_DFLT_12_POWER          11112 
#define CPU_PWR_ARCH_PERF_DFLT_12_TRANSITION     10   
#define CPU_PWR_ARCH_PERF_DFLT_12_BUS_MASTER     10    
#define CPU_PWR_ARCH_PERF_DFLT_12_CTRL_REG_VAL   0x000A
#define CPU_PWR_ARCH_PERF_DFLT_12_STAT_REG_VAL   0x000A

#define CPU_PWR_ARCH_PERF_DFLT_13_CORE_FREQ      1199 
#define CPU_PWR_ARCH_PERF_DFLT_13_POWER          9877  
#define CPU_PWR_ARCH_PERF_DFLT_13_TRANSITION     10   
#define CPU_PWR_ARCH_PERF_DFLT_13_BUS_MASTER     10    
#define CPU_PWR_ARCH_PERF_DFLT_13_CTRL_REG_VAL   0x0009
#define CPU_PWR_ARCH_PERF_DFLT_13_STAT_REG_VAL   0x0009
#endif /* ACPI_PWR_CPU_ARCH_PROPAGATE_CPU_PERF_0 */

#if defined (ACPI_PWR_CPU_ARCH_PROPAGATE_CPU_C_STATE)
/* default C-State options when table missing (based on Emerson) */

#define CPU_PWR_ARCH_C_STATE_DFLT_COUNT		0x3

#define CPU_PWR_ARCH_C_STATE_SUB_DFLT_1_ADDRESS 0x00000000
#define CPU_PWR_ARCH_C_STATE_SUB_DFLT_1_TYPE    0x01
#define CPU_PWR_ARCH_C_STATE_SUB_DFLT_1_LATENCY 0x03
#define CPU_PWR_ARCH_C_STATE_SUB_DFLT_1_POWER   0x3E8

#define CPU_PWR_ARCH_C_STATE_SUB_DFLT_2_ADDRESS 0x00000414
#define CPU_PWR_ARCH_C_STATE_SUB_DFLT_2_TYPE    0x02
#define CPU_PWR_ARCH_C_STATE_SUB_DFLT_2_LATENCY 0xCD
#define CPU_PWR_ARCH_C_STATE_SUB_DFLT_2_POWER   0x1F4

#define CPU_PWR_ARCH_C_STATE_SUB_DFLT_3_ADDRESS 0x00000415
#define CPU_PWR_ARCH_C_STATE_SUB_DFLT_3_TYPE    0x03
#define CPU_PWR_ARCH_C_STATE_SUB_DFLT_3_LATENCY 0xF5
#define CPU_PWR_ARCH_C_STATE_SUB_DFLT_3_POWER   0x15E
#endif /* ACPI_PWR_CPU_ARCH_PROPAGATE_CPU_C_STATE */

/*
 * This structure defines an HPET descriptor table entries. See section
 * 3.2.4 in the IA-PC HPET Specification for detailsi.
 */

typedef struct cpuPwrArchHpetStruct
    {
    UINT32  Id;                     /* Hardware Id of Event Timer Block */
    UINT64  Address;                /* Address of Event Timer Block */
    UINT8   AddrSpaceId;            /* 0 = System memory, 1 = System I/O */
    UINT8   Sequence;               /* HPET sequence number */
    UINT16  MinimumTick;            /* Main counter min tick, periodic mode */
    UINT8   Flags;                  /* attribute specific */
    UINT8   pad_1;                  /* padding for alignment */
    UINT16  pad_2;
    } CPU_PWR_ARCH_HPET;

/*
 * This structure represents a defined thermal zone. 
 */

typedef struct cpuPwrArchThermalZoneStruct
    {
    void   *handle;                 /* HANDLE */
    void   *context;                /* THERMAL_ZONE [0..n-1] */
    UINT32  DomainId;               /* domain number */
    UINT32  activeCoolingThresh;    /* active cooling threshold (degK/10) */
    UINT32  criticalTrip;           /* hardware shutdown trip (degK/10) */
    UINT32  hotTemp;                /* software shutdown trip (degK/10) */
    UINT32  passiveTrip;            /* software passive cool trip (degK/10) */
    UINT32  currentTemp;            /* current zone temperature (degK/10) */
    UINT32  currentAccuracy;        /* see ACPI spec 11.4.7 (_NTT) */
    UINT32  coolingPolicy;          /* thermal zone cooling policy */
    } CPU_PWR_ARCH_THERMAL_ZONE;

/*
 * This structure defines the supported performance states.
 */

typedef struct cpuPwrArchPerfStruct 
    {
    UINT32  coreFreq;               /* core frequency (MHZ) */
    UINT32  power;                  /* max power consumption (mw) */
    UINT32  transitionLatency;      /* us */
    UINT32  busMasterLatency;       /* us */
    UINT32  control;                /* performance control register value */
    UINT32  status;                 /* expected control status value */
    } CPU_PWR_ARCH_PERFORMANCE;

/*
 * This structure defines the supported throttling states.
 */

typedef struct cpuPwrArchThrottleStruct 
    {
    UINT32  percentage;             /* percentage of clock rate (1%..100%) */
    UINT32  power;                  /* power consumption (mw) */
    UINT32  transitionLatency;      /* us */
    UINT32  control;                /* throttle control register value */
    UINT32  status;                 /* expected control status value */
    } CPU_PWR_ARCH_THROTTLE;

/*
 * This structure defines declare the supported processor power
 * states (C States).
 */

typedef struct cpuPwrArchCStateSubStruct 
    {
    UINT64  address;            /* address of reg to read to set C State */
    UINT32  type;               /* C State type (1=C1, 2=C2 3=C3, etc.) */
    UINT32  latency;            /* worst case latency, in microseconds */
    UINT32  power;              /* average power consumption milliwatts */
    } CPU_PWR_ARCH_C_STATE_SUB;

typedef struct cpuPwrArchCStateStruct 
    {
    UINT32  count;                        /* number of C State sub-packages */
    CPU_PWR_ARCH_C_STATE_SUB *pCStateSub; /* pointer to C State record */
    } CPU_PWR_ARCH_C_STATE;

/*
 * This structure holds information reported by Power and Thermal
 * Management for one CPU.
 */

typedef struct cpuPwrArchStruct
    {
    void   *handle;                 /* HANDLE */
    void   *context;                /* CPU [0..n-1] */
    UINT32  procId;                 /* not necessarilly 0..n-1 */
    UINT32  coordType;              /* see P-state dependency definitions */
    UINT32  cpuPState;              /* current cpu P-state (0..numPerfSup)*/
    UINT32  DomainId;               /* dependency domain number (see _PSD) */
    UINT32  numCpusInDomain;        /* number of CPUs in domain */
    UINT32  numThrottle;            /* number of throttle states defined */
    UINT32  numThrottleNotSup;      /* number of T-states not supported */
    UINT32  numPerf;                /* number of performance states defined */
    UINT32  numPerfNotSup;          /* number of P-states not supported */
    UINT32  numPstates;             /* number of supported P-states */
    UINT32 *pThControl;             /* throttle control register address */
    UINT32 *pThStatus;              /* throttle status address */
    UINT32 *pPerfControl;           /* peformance control register address */
    UINT32 *pPerfStatus;            /* performance status address */
    CPU_PWR_ARCH_THROTTLE *pThrottle;   /* pointer to throttle record */
    CPU_PWR_ARCH_PERFORMANCE *pPerf;    /* pointer to performance record */
    char    nodeName[5];            /* CPU name */
    char    fill[3];
    UINT32  cpuPwrArchPMSup1;       /* Power Management capabilities */
    UINT32  cpuPwrArchPMSup2;       /* Power Management capabilities */
    UINT32  cpuPwrArchPMIntThrsh;   /* Power Management capabilities */
    UINT32  cpuPwrArchTMSup1;       /* Thermal Management capabilities */
    UINT32  cpuPwrArchTMSup2;       /* Thermal Management capabilities */
    CPU_PWR_ARCH_C_STATE cpuCState; /* optional variable C State record */
    cpuset_t pStates;               /* bit map of supported P States for cpu */
    cpuset_t tStates;               /* bit map of supported T States for cpu */
    cpuset_t cStates;               /* bit map of supported C States for cpu */
    } CPU_PWR_ARCH;

/*
 * This structure represents information that describes the target board.
 */

typedef struct cpuPwrArchBoardStruct
    {
    UINT32                     cpuPwrArchNumCpus;
    CPU_PWR_ARCH              *pCpuPwrArch;
    UINT32                     cpuPwrArchValHpet;
    CPU_PWR_ARCH_HPET         *pHpet;
    UINT32                     cpuPwrArchNumThermZones;
    CPU_PWR_ARCH_THERMAL_ZONE *pThermalZone;
    } CPU_PWR_ARCH_BOARD_INFO;

IMPORT CPU_PWR_ARCH_BOARD_INFO  sysCpuPwrArchBoardInfo, *pSysCpuPwrArchBoardInfo;

/* function declarations */

#if defined (__STDC__) || defined (__cplusplus)

IMPORT CPU_PWR_ARCH * cpuPwrArchGetCpuInfo (int cpuIndex);

IMPORT cpuset_t cpuPwrArchPStates (int cpuIndex);
IMPORT cpuset_t cpuPwrArchTStates (int cpuIndex);
IMPORT cpuset_t cpuPwrArchCStates (int cpuIndex);
IMPORT UINT32   cpuPwrArchPStateGetByCpu (int cpuIndex);

IMPORT void cpuPwrArchCStateSet (UINT8 cStateHint);

#if ((CPU_FAMILY==I80X86) && (CPU != PENTIUM))
IMPORT STATUS cpuPwrArchTurboSet (void);
IMPORT STATUS cpuPwrArchTurboUnSet (void);
#endif /* (CPU_FAMILY==I80X86) && (CPU != PENTIUM) */

IMPORT void cpuPwrArchGetCapabilities (CPU_PWR_ARCH *pCpu);

IMPORT STATUS cpuPwrArchShowCapabilities (void);
IMPORT STATUS cpuPwrArchBoardShow (void);

#ifdef _WRS_CONFIG_LP64
IMPORT void cpuPwrArchMperfGet (long *pData);
IMPORT void cpuPwrArchMperfSet (long *pData);
IMPORT void cpuPwrArchAperfGet (long *pData);
IMPORT void cpuPwrArchAperfSet (long *pData);

IMPORT BOOL cpuPwrArchOPP (void);
IMPORT void cpuPwrArchOPPEnable (void);
IMPORT void cpuPwrArchOPPDisable (void);

IMPORT UINT8 cpuPwrArchPEBHGet (void);
IMPORT void cpuPwrArchPEBHSet (UINT8 pebHint);
#else
IMPORT void cpuPwrArchMperfGet (long long int *pData);
IMPORT void cpuPwrArchMperfSet (long long int *pData);
IMPORT void cpuPwrArchAperfGet (long long int *pData);
IMPORT void cpuPwrArchAperfSet (long long int *pData);
#endif /* _WRS_CONFIG_LP64 */

IMPORT BOOL cpuPwrArchODCM (void);
IMPORT void cpuPwrArchODCM_Enable (void);
IMPORT void cpuPwrArchODCM_Disable (void);
IMPORT UINT8 cpuPwrArchODCM_DCGet (void);
IMPORT void cpuPwrArchODCM_DCSet (UINT8 dutyCycle);

IMPORT UINT8 cpuPwrArchODCM_DCExtGet (void);
IMPORT void cpuPwrArchODCM_DCExtSet (UINT8 dutyCycle);

#ifdef _WRS_CONFIG_LP64
IMPORT void cpuPwrArchTM_StatRegGet (long *pData);
IMPORT void cpuPwrArchTM_StatRegSet (long *pData);
#else
IMPORT void cpuPwrArchTM_StatRegGet (long long int *pData);
IMPORT void cpuPwrArchTM_StatRegSet (long long int *pData);
#endif /* _WRS_CONFIG_LP64 */

IMPORT BOOL cpuPwrArchTM_Status (void);
IMPORT BOOL cpuPwrArchTM_StatLog (void);
IMPORT void cpuPwrArchTM_StatLogClr (void);

IMPORT BOOL cpuPwrArchTM_PFEvent (void);
IMPORT BOOL cpuPwrArchTM_PFEventLog (void);
IMPORT void cpuPwrArchTM_PFEventLogClr (void);

IMPORT BOOL cpuPwrArchTM_CTempStat (void);
IMPORT BOOL cpuPwrArchTM_CTempLog (void);
IMPORT void cpuPwrArchTM_CTempLogClr (void);

IMPORT BOOL cpuPwrArchTM_Thrsh1Stat (void);
IMPORT BOOL cpuPwrArchTM_Thrsh1Log (void);
IMPORT void cpuPwrArchTM_Thrsh1LogClr (void);

IMPORT BOOL cpuPwrArchTM_Thrsh2Stat (void);
IMPORT BOOL cpuPwrArchTM_Thrsh2Log (void);
IMPORT void cpuPwrArchTM_Thrsh2LogClr (void);

IMPORT BOOL cpuPwrArchTM_PLNStat (void);
IMPORT BOOL cpuPwrArchTM_PLNLog (void);
IMPORT void cpuPwrArchTM_PLNLogClr (void);

IMPORT UINT8 cpuPwrArchTM_DigReadOut (void);

IMPORT UINT8 cpuPwrArchTM_ResCelsius (void);

IMPORT BOOL cpuPwrArchTM_DigReadOutValid (void);

#ifdef _WRS_CONFIG_LP64
IMPORT void cpuPwrArchTM_pkgStatRegGet (long *pData);
IMPORT void cpuPwrArchTM_pkgStatRegSet (long *pData);
#else
IMPORT void cpuPwrArchTM_pkgStatRegGet (long long int *pData);
IMPORT void cpuPwrArchTM_pkgStatRegSet (long long int *pData);
#endif /* _WRS_CONFIG_LP64 */

IMPORT BOOL cpuPwrArchTM_pkgStatus (void);
IMPORT BOOL cpuPwrArchTM_pkgStatLog (void);
IMPORT void cpuPwrArchTM_pkgStatLogClr (void);

IMPORT BOOL cpuPwrArchTM_pkgPFEvent (void);
IMPORT BOOL cpuPwrArchTM_pkgPFEventLog (void);
IMPORT void cpuPwrArchTM_pkgPFEventLogClr (void);

IMPORT BOOL cpuPwrArchTM_pkgCTempStat (void);
IMPORT BOOL cpuPwrArchTM_pkgCTempLog (void);
IMPORT void cpuPwrArchTM_pkgCTempLogClr (void);

IMPORT BOOL cpuPwrArchTM_pkgThrsh1Stat (void);
IMPORT BOOL cpuPwrArchTM_pkgThrsh1Log (void);
IMPORT void cpuPwrArchTM_pkgThrsh1LogClr (void);

IMPORT BOOL cpuPwrArchTM_pkgThrsh2Stat (void);
IMPORT BOOL cpuPwrArchTM_pkgThrsh2Log (void);
IMPORT void cpuPwrArchTM_pkgThrsh2LogClr (void);

IMPORT BOOL cpuPwrArchTM_pkgPLNStat (void);
IMPORT BOOL cpuPwrArchTM_pkgPLNLog (void);
IMPORT void cpuPwrArchTM_pkgPLNLogClr (void);

IMPORT UINT8 cpuPwrArchTM_pkgDigReadOut (void);

#ifdef _WRS_CONFIG_LP64
IMPORT void cpuPwrArchTM_intRegGet (long *pData);
IMPORT void cpuPwrArchTM_intRegSet (long *pData);
#else
IMPORT void cpuPwrArchTM_intRegGet (long long int *pData);
IMPORT void cpuPwrArchTM_intRegSet (long long int *pData);
#endif /* _WRS_CONFIG_LP64 */

IMPORT BOOL cpuPwrArchTM_intHT (void);
IMPORT void cpuPwrArchTM_intHTEn (void);
IMPORT void cpuPwrArchTM_intHTDis (void);

IMPORT BOOL cpuPwrArchTM_intLT (void);
IMPORT void cpuPwrArchTM_intLTEn (void);
IMPORT void cpuPwrArchTM_intLTDis (void);

IMPORT BOOL cpuPwrArchTM_intPROCHOT (void);
IMPORT void cpuPwrArchTM_intPROCHOTEn (void);
IMPORT void cpuPwrArchTM_intPROCHOTDis (void);

IMPORT BOOL cpuPwrArchTM_intFORCEPR (void);
IMPORT void cpuPwrArchTM_intFORCEPREn (void);
IMPORT void cpuPwrArchTM_intFORCEPRDis (void);

IMPORT BOOL cpuPwrArchTM_intOHeat (void);
IMPORT void cpuPwrArchTM_intOHeatEn (void);
IMPORT void cpuPwrArchTM_intOHeatDis (void);

IMPORT UINT8 cpuPwrArchTM_intThrsh1Get (void);
IMPORT void cpuPwrArchTM_intThrsh1Set (UINT8 thrsh1Val);
IMPORT BOOL cpuPwrArchTM_intThrsh1 (void);
IMPORT void cpuPwrArchTM_intThrsh1En (void);
IMPORT void cpuPwrArchTM_intThrsh1Dis (void);

IMPORT UINT8 cpuPwrArchTM_intThrsh2Get (void);
IMPORT void cpuPwrArchTM_intThrsh2Set (UINT8 thrsh2Val);
IMPORT BOOL cpuPwrArchTM_intThrsh2 (void);
IMPORT void cpuPwrArchTM_intThrsh2En (void);
IMPORT void cpuPwrArchTM_intThrsh2Dis (void);

IMPORT BOOL cpuPwrArchTM_intPLN (void);
IMPORT void cpuPwrArchTM_intPLNEn (void);
IMPORT void cpuPwrArchTM_intPLNDis (void);

#ifdef _WRS_CONFIG_LP64
IMPORT void cpuPwrArchTM_pkgIntRegGet (long *pData);
IMPORT void cpuPwrArchTM_pkgIntRegSet (long *pData);
#else
IMPORT void cpuPwrArchTM_pkgIntRegGet (long long int *pData);
IMPORT void cpuPwrArchTM_pkgIntRegSet (long long int *pData);
#endif /* _WRS_CONFIG_LP64 */

IMPORT BOOL cpuPwrArchTM_pkgIntHT (void);
IMPORT void cpuPwrArchTM_pkgIntHTEn (void);
IMPORT void cpuPwrArchTM_pkgIntHTDis (void);

IMPORT BOOL cpuPwrArchTM_pkgIntLT (void);
IMPORT void cpuPwrArchTM_pkgIntLTEn (void);
IMPORT void cpuPwrArchTM_pkgIntLTDis (void);

IMPORT BOOL cpuPwrArchTM_pkgIntPROCHOT (void);
IMPORT void cpuPwrArchTM_pkgIntPROCHOTEn (void);
IMPORT void cpuPwrArchTM_pkgIntPROCHOTDis (void);

IMPORT BOOL cpuPwrArchTM_pkgIntFORCEPR (void);
IMPORT void cpuPwrArchTM_pkgIntFORCEPREn (void);
IMPORT void cpuPwrArchTM_pkgIntFORCEPRDis (void);

IMPORT BOOL cpuPwrArchTM_pkgIntOHeat (void);
IMPORT void cpuPwrArchTM_pkgIntOHeatEn (void);
IMPORT void cpuPwrArchTM_pkgIntOHeatDis (void);

IMPORT UINT8 cpuPwrArchTM_pkgIntThrsh1Get (void);
IMPORT void cpuPwrArchTM_pkgIntThrsh1Set (UINT8 thrsh1Val);
IMPORT BOOL cpuPwrArchTM_pkgIntThrsh1 (void);
IMPORT void cpuPwrArchTM_pkgIntThrsh1En (void);
IMPORT void cpuPwrArchTM_pkgIntThrsh1Dis (void);

IMPORT UINT8 cpuPwrArchTM_pkgIntThrsh2Get (void);
IMPORT void cpuPwrArchTM_pkgIntThrsh2Set (UINT8 thrsh2Val);
IMPORT BOOL cpuPwrArchTM_pkgIntThrsh2 (void);
IMPORT void cpuPwrArchTM_pkgIntThrsh2En (void);
IMPORT void cpuPwrArchTM_pkgIntThrsh2Dis (void);

IMPORT BOOL cpuPwrArchTM_pkgIntPLN (void);
IMPORT void cpuPwrArchTM_pkgIntPLNEn (void);
IMPORT void cpuPwrArchTM_pkgIntPLNDis (void);

IMPORT BOOL cpuPwrArchODCM (void);
IMPORT void cpuPwrArchODCM_Enable (void);
IMPORT void cpuPwrArchODCM_Disable (void);
IMPORT UINT8 cpuPwrArchODCM_DCGet (void);
IMPORT void cpuPwrArchODCM_DCSet (UINT8 dutyCycle);

IMPORT UINT8 cpuPwrArchODCM_DCExtGet (void);
IMPORT void cpuPwrArchODCM_DCExtSet (UINT8 dutyCycle);
#else

IMPORT STATUS cpuPwrArchLibInit ();
IMPORT STATUS cpuPwrArchEnable ();
IMPORT STATUS cpuPwrArchDisable ();

IMPORT CPU_PWR_ARCH * cpuPwrArchGetCpuInfo ();

IMPORT UINT32 cpuPwrArchPStateSet ();
IMPORT UINT32 cpuPwrArchPStateGet ();

IMPORT cpuset_t cpuPwrArchPStates ();
IMPORT cpuset_t cpuPwrArchTStates ();
IMPORT cpuset_t cpuPwrArchCStates ();

IMPORT void vxC1StateSet ();
IMPORT void cpuPwrArchCStateSet ();

#if ((CPU_FAMILY==I80X86) && (CPU != PENTIUM))
IMPORT STATUS cpuPwrArchTurboSet ();
IMPORT STATUS cpuPwrArchTurboUnSet ();
#endif /* (CPU_FAMILY==I80X86) && (CPU != PENTIUM) */

IMPORT void cpuPwrArchGetCapabilities ();

IMPORT STATUS cpuPwrArchShowCapabilities ();
IMPORT STATUS cpuPwrArchBoardShow ();

IMPORT void cpuPwrArchMperfGet ();
IMPORT void cpuPwrArchMperfSet ();
IMPORT void cpuPwrArchAperfGet ();
IMPORT void cpuPwrArchAperfSet ();

#ifdef _WRS_CONFIG_LP64
IMPORT BOOL cpuPwrArchOPP ();
IMPORT void cpuPwrArchOPPEnable ();
IMPORT void cpuPwrArchOPPDisable ();

IMPORT UINT8 cpuPwrArchPEBHGet ();
IMPORT void cpuPwrArchPEBHSet ();
#endif /* _WRS_CONFIG_LP64 */

IMPORT BOOL cpuPwrArchODCM ();
IMPORT void cpuPwrArchODCM_Enable ();
IMPORT void cpuPwrArchODCM_Disable ();
IMPORT UINT8 cpuPwrArchODCM_DCGet ();
IMPORT void cpuPwrArchODCM_DCSet ();

IMPORT UINT8 cpuPwrArchODCM_DCExtGet ();
IMPORT void cpuPwrArchODCM_DCExtSet ();

/* IA32 Thermal Status  Register */

IMPORT void cpuPwrArchTM_StatRegGet ();
IMPORT void cpuPwrArchTM_StatRegSet ();

IMPORT BOOL cpuPwrArchTM_Status ();
IMPORT BOOL cpuPwrArchTM_StatLog ();
IMPORT void cpuPwrArchTM_StatLogClr ();

IMPORT BOOL cpuPwrArchTM_PFEvent ();
IMPORT BOOL cpuPwrArchTM_PFEventLog ();
IMPORT void cpuPwrArchTM_PFEventLogClr ();

IMPORT BOOL cpuPwrArchTM_CTempStat ();
IMPORT BOOL cpuPwrArchTM_CTempLog ();
IMPORT void cpuPwrArchTM_CTempLogClr ();

IMPORT BOOL cpuPwrArchTM_Thrsh1Stat ();
IMPORT BOOL cpuPwrArchTM_Thrsh1Log ();
IMPORT void cpuPwrArchTM_Thrsh1LogClr ();

IMPORT BOOL cpuPwrArchTM_Thrsh2Stat ();
IMPORT BOOL cpuPwrArchTM_Thrsh2Log ();
IMPORT void cpuPwrArchTM_Thrsh2LogClr ();

IMPORT BOOL cpuPwrArchTM_PLNStat ();
IMPORT BOOL cpuPwrArchTM_PLNLog ();
IMPORT void cpuPwrArchTM_PLNLogClr ();

IMPORT UINT8 cpuPwrArchTM_DigReadOut ();

IMPORT UINT8 cpuPwrArchTM_ResCelsius ();

IMPORT BOOL cpuPwrArchTM_DigReadOutValid ();

/* IA32 Package Thermal Status  Register */

IMPORT void cpuPwrArchTM_pkgStatRegGet ();
IMPORT void cpuPwrArchTM_pkgStatRegSet ();

IMPORT BOOL cpuPwrArchTM_pkgStatus ();
IMPORT BOOL cpuPwrArchTM_pkgStatLog ();
IMPORT void cpuPwrArchTM_pkgStatLogClr ();

IMPORT BOOL cpuPwrArchTM_pkgPFEvent ();
IMPORT BOOL cpuPwrArchTM_pkgPFEventLog ();
IMPORT void cpuPwrArchTM_pkgPFEventLogClr ();

IMPORT BOOL cpuPwrArchTM_pkgCTempStat ();
IMPORT BOOL cpuPwrArchTM_pkgCTempLog ();
IMPORT void cpuPwrArchTM_pkgCTempLogClr ();

IMPORT BOOL cpuPwrArchTM_pkgThrsh1Stat ();
IMPORT BOOL cpuPwrArchTM_pkgThrsh1Log ();
IMPORT void cpuPwrArchTM_pkgThrsh1LogClr ();

IMPORT BOOL cpuPwrArchTM_pkgThrsh2Stat ();
IMPORT BOOL cpuPwrArchTM_pkgThrsh2Log ();
IMPORT void cpuPwrArchTM_pkgThrsh2LogClr ();

IMPORT BOOL cpuPwrArchTM_pkgPLNStat ();
IMPORT BOOL cpuPwrArchTM_pkgPLNLog ();
IMPORT void cpuPwrArchTM_pkgPLNLogClr ();

IMPORT UINT8 cpuPwrArchTM_pkgDigReadOut ();

/* IA32 Thermal Interrupt Register */

IMPORT void cpuPwrArchTM_intRegGet ();
IMPORT void cpuPwrArchTM_intRegSet ();

IMPORT BOOL cpuPwrArchTM_intHT ();
IMPORT void cpuPwrArchTM_intHTEn ();
IMPORT void cpuPwrArchTM_intHTDis ();

IMPORT BOOL cpuPwrArchTM_intLT ();
IMPORT void cpuPwrArchTM_intLTEn ();
IMPORT void cpuPwrArchTM_intLTDis ();

IMPORT BOOL cpuPwrArchTM_intPROCHOT ();
IMPORT void cpuPwrArchTM_intPROCHOTEn ();
IMPORT void cpuPwrArchTM_intPROCHOTtDis ();

IMPORT BOOL cpuPwrArchTM_intFORCEPR ();
IMPORT void cpuPwrArchTM_intFORCEPREn ();
IMPORT void cpuPwrArchTM_intFORCEPRDis ();

IMPORT BOOL cpuPwrArchTM_intOHeat ();
IMPORT void cpuPwrArchTM_intOHeatEn ();
IMPORT void cpuPwrArchTM_intOHeatDis ();

IMPORT UINT8 cpuPwrArchTM_intThrsh1Get ();
IMPORT void cpuPwrArchTM_intThrsh1Set ();
IMPORT BOOL cpuPwrArchTM_intThrsh1 ();
IMPORT void cpuPwrArchTM_intThrsh1En ();
IMPORT void cpuPwrArchTM_intThrsh1Dis ();

IMPORT UINT8 cpuPwrArchTM_intThrsh2Get ();
IMPORT void cpuPwrArchTM_intThrsh2Set ();
IMPORT BOOL cpuPwrArchTM_intThrsh2 ();
IMPORT void cpuPwrArchTM_intThrsh2En ();
IMPORT void cpuPwrArchTM_intThrsh2Dis ();

IMPORT BOOL cpuPwrArchTM_intPLN ();
IMPORT void cpuPwrArchTM_intPLNEn ();
IMPORT void cpuPwrArchTM_intPLNDis ();

/* IA32 Package Thermal Interrupt Register */

IMPORT void cpuPwrArchTM_pkgIntRegGet ();
IMPORT void cpuPwrArchTM_pkgIntRegSet ();

IMPORT BOOL cpuPwrArchTM_pkgIntHT ();
IMPORT void cpuPwrArchTM_pkgIntHTEn ();
IMPORT void cpuPwrArchTM_pkgIntHTDis ();

IMPORT BOOL cpuPwrArchTM_pkgIntLT ();
IMPORT void cpuPwrArchTM_pkgIntLTEn ();
IMPORT void cpuPwrArchTM_pkgIntLTDis ();

IMPORT BOOL cpuPwrArchTM_pkgIntPROCHOT ();
IMPORT void cpuPwrArchTM_pkgIntPROCHOTEn ();
IMPORT void cpuPwrArchTM_pkgIntPROCHOTDis ();

IMPORT BOOL cpuPwrArchTM_pkgIntFORCEPR ();
IMPORT void cpuPwrArchTM_pkgIntFORCEPREn ();
IMPORT void cpuPwrArchTM_pkgIntFORCEPRDis ();

IMPORT BOOL cpuPwrArchTM_pkgIntOHeat ();
IMPORT void cpuPwrArchTM_pkgIntOHeatEn ();
IMPORT void cpuPwrArchTM_pkgIntOHeatDis ();

IMPORT UINT8 cpuPwrArchTM_pkgIntThrsh1Get ();
IMPORT void cpuPwrArchTM_pkgIntThrsh1Set ();
IMPORT BOOL cpuPwrArchTM_pkgIntThrsh1 ();
IMPORT void cpuPwrArchTM_pkgIntThrsh1En ();
IMPORT void cpuPwrArchTM_pkgIntThrsh1Dis ();

IMPORT UINT8 cpuPwrArchTM_pkgIntThrsh2Get ();
IMPORT void cpuPwrArchTM_pkgIntThrsh2Set ();
IMPORT BOOL cpuPwrArchTM_pkgIntThrsh2 ();
IMPORT void cpuPwrArchTM_pkgIntThrsh2En ();
IMPORT void cpuPwrArchTM_pkgIntThrsh2Dis ();

IMPORT BOOL cpuPwrArchTM_pkgIntPLN ();
IMPORT void cpuPwrArchTM_pkgIntPLNEn ();
IMPORT void cpuPwrArchTM_pkgIntPLNDis ();
#endif  /* __STDC__ || __cplusplus */

#endif  /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCcpuPwrArchI86Libh */

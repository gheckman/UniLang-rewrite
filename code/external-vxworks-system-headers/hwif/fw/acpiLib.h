/* acpiLib.h - ACPI library support 
 */

/*
 * Copyright (c) 2008-2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
                                                                     
/*
modification history
--------------------
01q,30jan14,jjk  VXW6-70049 - Merge making ACPI static mem pool configurable.
01p,09may13,jjk  WIND00364942 - Adding support for Unified BSP.
01o,18oct12,c_t  reduce ACPI footprint
01n,19apr12,g_x  remove ACPI_MSG_LEN_MAX definition (WIND00278438)
01m,23aug11,sem  WIND00294323 - add _PDC support
01l,22jul11,scm  WIND00255355, allow for propagation of CPU[0] P-States...
01k,29jun11,scm  WIND00255355, remove un-needed cpuPwrArch specific items 
                 now found in PM abstraction...
01j,26may11,scm  WIND00255355,adjust MAX values, add ACPI_CPU_C_STATE...
01i,04apr11,scm  WIND00238999, add 64 bit support...
01h,30jun10,rec  WIND00220964 - fix _STATIC_BUF_SIZE
01g,21jan10,rec  decouple MPAPIC tables from ACPI component
01f,10aug09,rec  WIND00176001 - multiple IO Apic support mods...
01e,06aug08,rbc  Fix pci config access.
01d,14jul08,rec  pass buf pointer to acpiLibShow
01c,17jun08,rec  pass MP table to acpiLibInit
01b,22may08,rec  add support for miscowabic board
01a,29Apr08,rec  created.
*/

/*
 * DESCRIPTION
 * This is the ACPI library support file
 */

#ifndef __INCacpiLib  
#define __INCacpiLib
                                                                       
#include <base/b_cpuset_t.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ACPI_MAX_DEVICE_ID_LENGTH   20
#define ACPI_MAX_STRING_PREFIX      5

#define ACPI_MAX_PSS_ELEMENTS       6

/* P-state dependency definitions */

#define ACPI_SW_ALL 0xFC    /* write is needed to all cores */
#define ACPI_SW_ANY 0xFD    /* last write to any core affects all cores */ 
#define ACPI_HW_ALL 0xFE    /* no knowledge needed.  Fastest speed wins */

/* thermal zone cooling policy */

#define ACPI_COOLING_NONE       0   /* let things cook until hardware limits */
#define ACPI_COOLING_ACTIVE     1   /* use fans etc */
#define ACPI_COOLING_PASSIVE    2   /* throttle cpu and device utilization */

/* processor driver capability bits */

#define ACPI_PERF_MSR           0x00000001 /* performance state MSR's */
#define ACPI_MP_C1_IOHALT       0x00000002 /* MP C1 I/O then HALT FFH seq */
#define ACPI_THROT_MSR          0x00000004 /* on demand throttling MSR's */
#define ACPI_MP_C1PT_INDEP      0x00000008 /* MP independent C1, P-States and T-States */
#define ACPI_MP_C2C3_INDEP      0x00000010 /* MP independent C2 and C3 */
#define ACPI_MP_PSTATE_SW_COORD 0x00000020 /* P-State sw coord using BIOS _PSD */
#define ACPI_MP_CSTATE_SW_COORD 0x00000040 /* C-State sw coord using BIOS _CSD */
#define ACPI_MP_THROT_SW_COORD  0x00000080 /* throttling sw coord using BIOS _TSD */
#define ACPI_MP_C1_INSTR        0x00000100 /* MP C-State instructions for C1 handlers */
#define ACPI_MP_C2C3_INSTR      0x00000200 /* MP C-State instructions for C2/C3 handlers */ 
#define ACPI_PDC_RSVD           0x00000400 /* reserved */
#define ACPI_PSTATE_HW_COORD    0x00000800 /* P-State hw coord using ACNT/MCNT */

/* BOOTAPP ACPI initialization can't use malloc */

#define _USE_STATIC_BUF_ALLOCATION  /* use static memory allocation instead */

typedef struct irqOverride
    {
    UINT8   sourceIrq;          /* Interrupt source (IRQ) */
    UINT32  globalIrq;          /* Global system interrupt */
    UINT16  intiFlags;
    BOOL    prepend;            /* TRUE if prepend to list */
    } IRQ_OVERRIDE;

/* defines in usrMpApic.c */

IMPORT char acpiOsBuf[]; 
IMPORT char *acpiOsBufTop;

IMPORT char *acpiOsBufPtr;
IMPORT char *acpiOsBufBase;

/*
 * This structure defines an ACPI HPET descriptor table entries. See section 
 * 3.2.4 in the IA-PC HPET Specification for details.
 */

typedef struct acpiHpetStruct
    {
    UINT32  Id;                     /* Hardware Id of Event Timer Block */    
    UINT64  Address;                /* Address of Event Timer Block */    
    UINT8   AddrSpaceId;            /* 0 = System memory, 1 = System I/O */
    UINT8   Sequence;               /* HPET sequence number */    
    UINT16  MinimumTick;            /* Main counter min tick, periodic mode */
    UINT8   Flags;                  /* attribute specific */
    UINT8   pad_1;                  /* padding for alignment */
    UINT16  pad_2;
    } ACPI_HPET;

/*
 * This structure defines an ACPI thermal zone. See section 11 in the ACPI 
 * spec for details.
 */

typedef struct acpiThermalZoneStruct
    {
    void   *handle;                 /* ACPI_HANDLE */
    void   *context;                /* ACPI_THERMAL_ZONE [0..n-1] */
    UINT32  DomainId;               /* domain number */
    UINT32  activeCoolingThresh;    /* active cooling threshold (degK/10) */
    UINT32  criticalTrip;           /* hardware shutdown trip (degK/10) */
    UINT32  hotTemp;                /* software shutdown trip (degK/10) */
    UINT32  passiveTrip;            /* software passive cool trip (degK/10) */
    UINT32  currentTemp;            /* current zone temperature (degK/10) */
    UINT32  currentAccuracy;        /* see ACPI spec 11.4.7 (_NTT) */
    UINT32  coolingPolicy;          /* thermal zone cooling policy */
    } ACPI_THERMAL_ZONE;
    
/*
 * This structure defines ACPI performance supported states.  
 * See section 8.4.4.2 in the ACPI spec for details.
 */

typedef struct acpiCpuPerfStruct   /* from _PSS */
    {
    UINT32  coreFreq;               /* core frequency (MHZ) */
    UINT32  power;                  /* max power consumption (mw) */
    UINT32  transitionLatency;      /* us */
    UINT32  busMasterLatency;       /* us */
    UINT32  control;                /* performance control register value */
    UINT32  status;                 /* expected control status value */
    } ACPI_CPU_PERFORMANCE;

/*
 * This structure defines ACPI throttling states.  
 * See section 8.4.3.2 in the ACPI spec for details.
 */

typedef struct acpiCpuThrottleStruct /* from _TSS */
    {
    UINT32  percentage;             /* percentage of clock rate (1%..100%) */
    UINT32  power;                  /* power consumption (mw) */
    UINT32  transitionLatency;      /* us */
    UINT32  control;                /* throttle control register value */
    UINT32  status;                 /* expected control status value */
    } ACPI_CPU_THROTTLE;

/*
 * This structure defines declare the supported processor power 
 * states (C States).
 * See section 8.4.2.1 in the ACPI spec for details.
 */

typedef struct acpiCpuCStateSubStruct /* from _CST */
    {
    UINT64 address;             /* address of reg to read to set C State */
    UINT32  type;               /* C State type (1=C1, 2=C2 3=C3, etc.) */
    UINT32  latency;            /* worst case latency, in microseconds */
    UINT32  power;              /* average power consumption milliwatts */
    } ACPI_CPU_C_STATE_SUB;

typedef struct acpiCpuCStateStruct    /* from _CST */
    {
    UINT32  count;                    /* number of C State sub-packages */
    ACPI_CPU_C_STATE_SUB *pCStateSub; /* pointer to C State record */
    } ACPI_CPU_C_STATE;

/*
 * This structure holds information reported by ACPI for one CPU,  
 * (See section 8 in the ACPI spec for details.)
 *
 * ...as well as the CPU's Power & Thermal Management capabilities.
 */
 
typedef struct acpiCpuStruct
    {
    void   *handle;                 /* ACPI_HANDLE */
    void   *context;                /* ACPI_CPU [0..n-1] */
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
    ACPI_CPU_THROTTLE *pThrottle;   /* pointer to throttle record */
    ACPI_CPU_PERFORMANCE *pPerf;    /* pointer to performance record */
    char    nodeName[5];            /* CPU name */
    char    fill[3];
    ACPI_CPU_C_STATE cpuCState;     /* optional variable C State record */
    } ACPI_CPU;

/*
 * This structure represents information that describes the target board.  
 * It may be collected by ACPI or hard-coded with static tables.
 */
 
typedef struct acpiBoardStruct
    {
    UINT32             acpiNumCpus;
    ACPI_CPU          *pAcpiCpu;
    UINT32             acpiValHpet;
    ACPI_HPET         *pHpet;
    UINT32             acpiNumThermZones;
    ACPI_THERMAL_ZONE *pThermalZone;
    } ACPI_BOARD_INFO;

IMPORT ACPI_BOARD_INFO  sysAcpiBoardInfo,  *pSysBoardInfo;

/*
 * the function below can be loaded by the BSP to change the interrupt routing
 * table.  This would be used in cases where the table created by ACPI is 
 * wrong.  The correct signature for the BSP function call is shown below.
 *
 *      IRQ_OVERRIDE *sysIrqOverride(int index);
 *
 * If registered, the function will be iteratively called by ACPI starting
 * with index = 0 and incremented with each call.  The BSP will return override
 * records if it has one registered at that index.  ACPI will stop asking if 
 * it recieves a NULL pointer.
 */

IMPORT IRQ_OVERRIDE *(*func_irqOverride)(int index);

/*
 * registering an early print function to this callback allows 
 * early status and error reporting by the ACPI subsystem as it
 * initializes and creates the MP table.
 */

IMPORT void (*func_acpiEarlyPrint)(char *outString);
 
IMPORT STATUS acpiLibInit (BOOL earlyInit);

IMPORT void acpiLibDisable (void);

/* acpiTables functions */

STATUS acpiTablesShow (void);
IMPORT STATUS acpiTableInit (void);
STATUS acpiTableValidate
    (
    UINT8  *pBuffer,    /* pointer to table */
    UINT32  length,
    char   *pSignature, /* NULL if don't validate signature */
    BOOL    probeMem    /* TRUE = use vxMemProbe to test memory access */
    );

UINT8 acpiChecksum
    (
    UINT8  *buffer, 
    UINT32  length
    );

/* acpiConfig functions */

IMPORT STATUS acpiLibDevScan (BOOL earlyInit,
		              BOOL pciAccess, 
		              char *pBuf, 
                              UINT32 mpApicBufSize);
IMPORT int    vxMpTablePrint (void);
IMPORT void   acpiConfigInit (void);

/* acpiLibShow functions */

IMPORT void   acpiLibShowInit (void);
IMPORT STATUS acpiDevicesShow (void);
IMPORT STATUS acpiObjectsShow (void);
IMPORT STATUS acpiBoardShow (void);
STATUS sysBoardInfoPrint (void);

/* acpiCpu functions */

IMPORT STATUS acpiCpuInit (void);
IMPORT STATUS acpiHpetInit (void);
IMPORT UINT32 acpiNumPerfEntriesGet (void);
IMPORT UINT32 acpiNumPerfProfilesGet (void);

#ifdef __cplusplus
}
#endif
                                                                    
#endif  /* __INCacpiLib */

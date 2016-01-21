/* pwrDeviceLib.h - device power library manager header file */

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
01g,26jul12,sye  Removed duplicate method declaration. (WIND00365654)
01f,09apr12,rbc  WIND00315814 - Fix power management image reboot if
                 INCLUDE_NETWORK is excluded
01e,02sep11,jjk  Add support for device timeout polling
01d,26aug11,rec  WIND00295764 - Add state D0-uninitialized for warm reboot
01c,05aug11,rbc  WIND00290401 - Callback for orphan device power management
01b,05jul11,rdl  split initialization into early and late steps
01a,03may11,rec created
*/

#ifndef _PWR_DEVICE_LIB_H
#define _PWR_DEVICE_LIB_H

/* includes */

#include <dllLib.h>
#include <hwif/vxbus/vxBus.h>
#include <drv/erf/erfLib.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* defines */

#define WILDCARD                0xFFFFFFFF
#define MAX_PARENTS             16      /* maximum number of domain parents */

#define HIERARCY_END            {NULL,0}

/*
 * Each enabled power state is represented by a binary one in the 
 * corresponding bit position. 
 */

#define WRS_D0_FLAG                  0x1
#define WRS_D1_FLAG                  0x2
#define WRS_D2_FLAG                  0x4
#define WRS_D3_FLAG                  0x8

#define WRS_D0_STATES       WRS_D0_FLAG     /* no power management for device */
#define WRS_D0D3_STATES     (WRS_D0_FLAG | WRS_D3_FLAG)  /* minimum */
#define WRS_D0D1D3_STATES   (WRS_D0_FLAG | WRS_D1_FLAG | WRS_D3_FLAG)
#define WRS_D0D2D3_STATES   (WRS_D0_FLAG | WRS_D2_FLAG | WRS_D3_FLAG)
#define WRS_D0D1D2D3_STATES  \
    (WRS_D0_FLAG | WRS_D1_FLAG | WRS_D2_FLAG | WRS_D3_FLAG)

/* 
 * This flag is set in the state number used by the device manager to indicate
 * that a D-0 state request is made during the reboot process.  It is only
 * intended to be used during a warm-boot and should not be set by software
 * for other purposes. Internally, STATE_UNINITIALIZED is saved in the device 
 * record as D-0 and treated accordinaly.
 */
 
#define WRS_D0_UNINITIALIZED 0x80000000

/* 
 * The macro below is provided as an optimization for function
 * pwrDeviceUtilizationSet.  Argument pwrDeviceId must be checked
 * for null before using this.
 *
 * This may be called from either an ISR or task context.
 *
 * evaluates to OK or ERROR if the device is not in state D-0.
 */
 
#define PWR_DEVICE_UTILIZATION_SET(pwrDeviceId)\
    (pwrDeviceId == NULL) ? OK : (\
    pwrDeviceId->utilization = TRUE, \
    pwrDeviceId->currentState == 0 ? OK : ERROR)

/* 
 * The macros below are provided as an optimization for function
 * getting the current and requested device states.  Argument pwrDeviceId 
 * must be checked for null before using these.
 *
 */
 
#define PWR_DEVICE_IS_HOT(pwrDeviceId) \
    ((pwrDeviceId == NULL) ? FALSE :\
    (pwrDeviceId->currentState != pwrDeviceId->requestedState)})
    
#define PWR_DEVICE_CURRENT_STATE(pwrDeviceId) \
    ((pwrDeviceId == NULL) ? 0 :\
    pwrDeviceId->currentState)   /* USE THIS FOR READING ONLY */

#define PWR_DEVICE_REQUESTED_STATE(pwrDeviceId) \
    ((pwrDeviceId == NULL) ? 0 :\
    pwrDeviceId->requestedState)  /* USE THIS FOR READING ONLY */

#define PWR_DEVICE_STATE_ENABLED(pwrDeviceId, state) \
    ((pwrDeviceId == NULL) ? FALSE :\
    ((pwrDeviceId->enabledStates & (1 << state)) != 0))

#define PWR_DEVICE_STATE_UNKNOWN 0xFFFFFFFF

#define PWR_DEVICE_EVENT_ALL    NULL


/* types */

typedef enum
    {
    DEVICE,
    DOMAIN
    } pwrRecordType;

typedef struct pwr_device PWR_DEVICE;
typedef struct pwr_device *PWR_DEVICE_ID;

typedef enum
    {
    DEPENDENT,
    INDEPENDENT
    } pwrDomainBehavior;
    
typedef STATUS (*PWR_DEVICE_CALLOUT_func)(UINT32 state, void * context);

typedef struct pwr_device_callout
    {
    PWR_DEVICE_CALLOUT_func   fct;
    void *                  context;
    STATUS                  functionReturnStatus;
    } PWR_DEVICE_CALLOUT;

/*
 * This is the device power record used internally by the device power manager.
 * Although it is public, care must be taken before manipulating any fields
 * that might be used by devices that are in the process of changing state.
 */
 
typedef struct pwr_device
    {
    DL_NODE	        node;		/* device head */
    char *              pName;          /* device name */
    UINT32	        unitNumber;	/* unit number */
    pwrRecordType       recordType;     /* DEVICE or DOMAIN */
    pwrDomainBehavior   behavior;       /* DEPENDENT or INDEPENDENT */
    UINT32              stateConstraint; /* minimum child state (DOMAIN ONLY) */
    UINT32              pwrCapability;  /* flags indicate states supported */
    UINT32              enabledStates;  /* flags indicate states enabled */
    UINT32              numMembership;  /* number of parent domains */
    UINT32              numFunctions;   /* number of callout functions */
    PWR_DEVICE_CALLOUT  *pFunctList;    /* pointer to first function callout */

        /* the following seven fields must match the PWR_DEVICE_METRIC struct */

    _Vx_ticks_t         timeout;        /* utilization timeout (ticks) */

        /* above fields must match the PWR_DEVICE_CONFIG structure */

    _Vx_ticks_t         upTime;         /* last period of activity (ticks) */
    UINT32              numTransitions; /* number of power transitions */
    UINT32              currentState;   /* actual D-state */
    UINT32              requestedState; /* requested D-state */
    _Vx_ticks_t         inactivity;  /* current period of inactivity (ticks) */
    BOOL                utilization;    /* true if active in last period */
    struct vxbDev       *vxbDevId;      /* NULL if not vxBus device */
    UINT16              pwrDeviceEvent; /* event reporting for this device */
    BOOL                transitioning;  /* device is transitioning states */
    UINT32              savedState;     /* saved state (for retore) */
    void                *context;       /* user context */
    DL_LIST             domainList;     /* list of children (DOMAIN ONLY) */
    
    /*
     * following this record is an array of type PWR_DEVICE_NODE used as
     * links to the parent devices.  The array is allocated during device
     * record creation.
     * PWR_DEVICE_NODE       parentList[];    /@ pointer to parent list @/
     */
     
    } PWR_DEVICE;

/*
 * This structure is used to report metrics.  The order of these fileds
 * must match the order in PWR_DEVICE above.
 */

typedef struct pwr_device_metric
    {
    _Vx_ticks_t         timeout;        /* utilization timeout (ticks) */
    _Vx_ticks_t         upTime;         /* last period of activity (ticks) */
    UINT32              numTransitions; /* number of power transitions */
    UINT32              currentState;   /* actual D-state */
    UINT32              requestedState; /* requested D-state */
    _Vx_ticks_t         inactivity;   /* current period of inactivity (ticks) */
    } PWR_DEVICE_METRIC;

/*
 * This structure is used to initialize new device records.  The order of these
 * fileds must match the order in PWR_DEVICE above.
 */

typedef struct pwr_device_config
    {
    char *              pName;          /* device name */
    UINT32	        unitNumber;	/* unit number */
    pwrRecordType       recordType;     /* DEVICE or DOMAIN */
    pwrDomainBehavior   behavior;       /* DEPENDENT or INDEPENDENT */
    UINT32              stateConstraint; /* minimum child state (DOMAIN ONLY) */
    UINT32              pwrCapability;  /* flags indicate states supported */
    UINT32              enabledStates;  /* flags indicate states enabled */
    UINT32              numMembership;  /* number of parent domains */
    UINT32              numFunctions;   /* number of callout functions */
    PWR_DEVICE_CALLOUT  *pFunctList;    /* pointer to first function callout */
    _Vx_ticks_t         timeout;        /* utilization timeout (ticks) */
    } PWR_DEVICE_CONFIG;

    /*
     * This structure is used to initialize static (known) devices into
     * a hierarchy of domains.  Topology is described as a set of device
     * domains.  Each domain is described as one array of this type.  The
     * first record has the domain name.  The last record has a NULL name.
     * remaining records describe devices that belong to that domain.
     *
     * Each list describes a domain starting with the domain name and unit
     * number.  Subsequent records list domain members.
     *
     * An array of such lists is provided by the BSP.  The last entry in that
     * array is NULL.
     */

typedef struct pwr_device_hierarcy
    {
    char *              pName;          /* device name */
    UINT32	        unitNumber;	/* unit number */
    } PWR_DEVICE_HIERARCHY;



typedef struct	pwr_device_node	/* PWR_DEVICE_NODE */
    {
    DL_NODE	node;		/* member links */
    PWR_DEVICE_ID pDomain;      /* pointer to parent (domain) */
    PWR_DEVICE_ID deviceId;     /* pointer to device */
    STATUS      status;         /* OK if state granted by parent */
    } PWR_DEVICE_NODE;

typedef struct pwr_device_event_data
    {
    PWR_DEVICE_ID pwrDeviceId; 
    UINT32 state;
    } pwrDeviceEventData;
    
typedef PWR_DEVICE_ID (*pwrDeviceAnnounce_func)
    (VXB_DEVICE_ID vxbDevId, void *pArg);
typedef STATUS (*pwrDeviceUtilizationSet_func)(PWR_DEVICE_ID pwrDeviceId);
typedef STATUS (*pwrDeviceStateSet_func)(PWR_DEVICE_ID pwrDeviceId, 
    UINT32 state);
typedef STATUS (*pwrDeviceShow_func)(PWR_DEVICE_ID pwrDeviceId);
typedef _Vx_ticks_t (*pwrDeviceCheck_func)(_Vx_ticks_t nTicks);

/* Function pointer for orphan device power management */

typedef void (*pwrOrphanDeviceSetD0_func)(void);
typedef void (*pwrOrphanDeviceSetD3_func)(void);

/* forward declarations */

IMPORT STATUS pwrDeviceLibInit (void);

IMPORT STATUS pwrDeviceLibStart (BOOL createMonitor, _Vx_ticks_t pollTicks);

IMPORT PWR_DEVICE_ID pwrDeviceRootGet (void);
    
IMPORT PWR_DEVICE_ID pwrDeviceIdGet 
    (
    char *name, 
    int unitNumber
    );
    
IMPORT PWR_DEVICE_ID pwrDeviceAnnounce 
    (
    VXB_DEVICE_ID vxbDevId,
    void *  pArg            /* not used */
    );
    
IMPORT STATUS pwrDeviceUtilizationSet
    (
    PWR_DEVICE_ID pwrDeviceId
    );
    
IMPORT BOOL pwrDeviceUtilizationGet
    (
    PWR_DEVICE_ID pwrDeviceId
    );
    
IMPORT STATUS pwrDeviceStateSet 
    (
    char *name, 
    UINT32 unitNumber, 
    UINT32 state
    );
    
IMPORT UINT32 pwrDeviceStateGet 
    (
    PWR_DEVICE_ID pwrDeviceId
    );
    
IMPORT UINT32 pwrDeviceStateRequestedGet 
    (
    PWR_DEVICE_ID pwrDeviceId
    );
    
IMPORT void pwrDeviceTimeoutSet 
    (
    PWR_DEVICE_ID pwrDeviceId, 
    UINT32 timeout
    );
    
IMPORT void pwrDeviceMetricsGet 
    (
    PWR_DEVICE_ID pwrDeviceId,
    PWR_DEVICE_METRIC *pMetric
    );

IMPORT void pwrDeviceShow 
    (
    char *name, 
    UINT32 unitNumber 
    );
    
IMPORT void pwrDeviceShowAll (void);
IMPORT void pwrDeviceStateShowAll (void);

IMPORT STATUS pwrDeviceEventHandlerRegister 
    (
    PWR_DEVICE_ID           pwrDeviceId, 
    erfHandlerPrototype     *pEventHandler, 
    void                    *pUserData 
    );
    
IMPORT STATUS pwrDeviceEventHandlerUnregister 
    (
    PWR_DEVICE_ID           pwrDeviceId, 
    erfHandlerPrototype     *pEventHandler, 
    void                    *pUserData 
    );
    
IMPORT UINT32 pwrDeviceCapabilityGet 
    (
    PWR_DEVICE_ID pwrDeviceId
    );
    
IMPORT UINT32 pwrDeviceEnableGet 
    (
    PWR_DEVICE_ID pwrDeviceId
    );

IMPORT void pwrDeviceCapabilitySet 
    (
    PWR_DEVICE_ID pwrDeviceId, 
    UINT32 flags
    );

IMPORT void pwrDeviceEnableSet 
    (
    PWR_DEVICE_ID pwrDeviceId, 
    UINT32 flags
    );

IMPORT void pwrDeviceLibSave (void);
IMPORT void pwrDeviceLibRestore (void);

/* externals */

IMPORT PWR_DEVICE_CONFIG *pSysStaticConfigTable[];
IMPORT PWR_DEVICE_CONFIG *pSysDynamicConfigTable[];
IMPORT PWR_DEVICE_CONFIG *pDefaultConfigEntry;
IMPORT PWR_DEVICE_HIERARCHY *ppSysPwrDeviceHierarchy[];

IMPORT pwrDeviceAnnounce_func vxbPwrDeviceAnnounceFunc;
IMPORT pwrDeviceUtilizationSet_func vxbPwrDeviceUtilizationSetFunc;
IMPORT pwrDeviceStateSet_func vxbPwrDeviceStateSetFunc; 
IMPORT pwrDeviceShow_func vxbPwrDeviceShowFunc;
IMPORT pwrDeviceCheck_func pwrDeviceCheckFunc;
IMPORT pwrOrphanDeviceSetD0_func pwrOrphanDeviceSetD0;
IMPORT pwrOrphanDeviceSetD3_func pwrOrphanDeviceSetD3;

IMPORT void pwrDeviceContextSet 
    (
    PWR_DEVICE_ID pwrDeviceId,
    void *context
    );

IMPORT void * pwrDeviceContextGet 
    (
    PWR_DEVICE_ID pwrDeviceId
    );


#if !defined(__RTP__)  /* define only if not RTP */
/* 
 * Device state change event notification objects
 * These events are available for registration through erfLib. 
 */

IMPORT UINT16 pwrDeviceEventCategory;
IMPORT UINT16 pwrDeviceEvent;     /* state change */
#endif /* define only if not RTP */

#ifdef __cplusplus
}
#endif

#endif /* _PWR_DEVICE_LIB_H */

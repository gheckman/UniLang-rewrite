/* vxBus.h - VxBus subsystem header file */

/*
 * Copyright (c) 2005-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
03c,18sep13,e_d  add SD bus support.
03b,15jan13,j_z  add multiple MSI/MSI-X support. (WIND00333514)
03a,12nov12,w_x  remove vxbBusRemovalAnnounce() (WIND00387497)
02z,04aug12,w_x  add VXB_BUSID_USB_HOST (WIND00372413)
02y,19jul12,w_x  add vxbBusRemovalAnnounce() API (WIND00338041)
02x,03nov11,sye  fix comment error. (WIND00288567)
02w,22sep11,mze  fix vxbMethodDecl move
02v,11aug11,rbc  WIND00238999 - Fix build errors
02u,28jul11,rbc  WIND00238999 - Add VSB _WRS_CONFIG_PWR_MGMT
02t,01jun11,rec  WIND00255358 add device power management
02s,07sep10,ghs  added USB MHCI BUS type.
02r,29jul10,pad  Moved extern C statement after include statements.
02q,13jul10,y_c  Add macro VXB_REG_BASE_0.(WIND00199486)
02p,17nov09,m_y  Add support for synopsys USB host controller(WIND00123426).
02o,09dec09,h_k  added pRegBasePhys and regBaseSize for ILP32. added
                 VXB_VER_5_0_0.
02n,10nov09,h_k  added HCF_RES_LONG.
02m,26aug09,h_k  added pRegBasePhys and regBaseSize.
02l,12jun09,x_s  changed the element of struct vxbLock for small footprint.
02k,28may09,h_k  changed the type of the initDone to atomic32_t.
                 added VXB_LOW32/HIGH32.
02j,23feb09,h_k  updated for LP64 support.
02i,02dec08,h_k  added vxbLockDelete.
02h,29sep08,h_k  added VXB_DMA_BUF_DEBUG_CHECKS when VXB_PERFORM_SANITY_CHECKS
                 is defined.
02g,17jun08,h_k  removed pAccessList usage.
                 cleaned up compiler warnings in VIP build.
02f,09jun08,tor  i2c bus type
02e,01may08,tor  increment version
02d,22apr08,tor  add shutdown flags
02c,20may07,dlk  Support SPIN_LOCK_TRACE.
02b,25jul07,tor  vxbLock uses semRW
02a,18jul07,tor  share struct
01z,29jun07,dtr  Export some interrupt structs.
01y,04jun07,tor  add VxBus locks
01x,04may07,wap  Add flags fields for BARs
01w,17apr07,pch  add ASSERT macros and standard resource name strings
01v,03apr07,pdg  critical section locks added
01u,29mar07,tor  update methods
01t,28feb07,tor  Add additional DEVMETHOD macros
01s,12feb07,bwa  added vxbDeviceDriverRelease() and vxbDrvRescan().
01r,08jan07,sup  Macros for USB added
01q,30nov06,wap  Make sure pNext is first element in all structures
01p,17oct06,pdg  updated VXB_METHOD_DRIVER_UNLINK macro and added method
                 related macros
01o,22jul06,wap  Add flags field to VxBus instance structure
01n,19Jul06,tor  added multi-function bus type
01m,02jul06,bwa  added virtual bus type.
01l,08feb06,pdg  added new macro for identifying lost devices
01k,31jan06,pdg  updated vxbus version
01j,04jan06,wap  Add MII bus type
01i,05dec05,mdo  add parameter ptr to dev struct
01h,05dec05,pdg  Prototype of vxbSubDevAction () added
01g,28nov05,pdg  Fix for SPR #112638 (unit number variable added)
01f,17nov05,pdg  Added vxbIntAcknowledge()
01e,25oct05,mdo  Adding additional routine
01d,20sep05,pdg  Fixed warning(SPR #112565)
01c,01sep05,mdo  Add vxb prefix
01b,10aug05,mdo  Phase in new access method
01a,17jan05,tor  written
*/

#ifndef _INC_VXBUS_H
#define _INC_VXBUS_H

/* includes */

#include <sllLib.h>
#include <spinLockLib.h>
#include <../src/hwif/h/vxbus/vxbAccess.h>
#include <hwif/vxbus/hwConf.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

/* vxbDevRegInfo->devID */
#define VXB_DEVID_DEVICE    0
#define VXB_DEVID_BUSCTRL   1

/* vxbDevRegInfo->busID */
#define VXB_BUSID_LOCAL		    1	/* processor local bus */
#define VXB_BUSID_PLB		    1	/* alt name for local bus */
#define VXB_BUSID_NEXUS		    1	/* alt name for local bus */
#define VXB_BUSID_VME		    2	/* VME */
#define VXB_BUSID_PCI		    3	/* PCI */
#define VXB_BUSID_PCIX		    4	/* PCI w/ PCI-X ext */
#define VXB_BUSID_PCIEXPRESS	    5	/* PCI w/ PCI-Express ext */
#define VXB_BUSID_HYPERTRANSPORT    6	/* PCI w/ HyperTransport ext */
#define VXB_BUSID_RAPIDIO	    7	/* RapidIO */
#define VXB_BUSID_MII		    8	/* Media Independent Interface */
#define VXB_BUSID_VIRTUAL	    9	/* virtual bus */

#define VXB_BUSID_MF		   10	/* multi-function device bus */
#define VXB_BUSID_USB_HOST_EHCI    11	/* EHCI Bus Type */
#define VXB_BUSID_USB_HOST_OHCI    12	/* OHCI Bus Type */
#define VXB_BUSID_USB_HOST_UHCI    13	/* UHCI Bus Type */
#define VXB_BUSID_USB_HUB	   14	/* hub bus type */
#define VXB_BUSID_USB_HOST_SYNOPSYSHCI      15  /*Synopsys HCI Bus Type*/
#define VXB_BUSID_USB_HOST_MHCI    16	/* MHCI Bus Type */
#define VXB_BUSID_USB_HOST         17	/* USB Host Bus Type */

#define VXB_BUSID_I2C		   20	/* I2C bus type */
#define VXB_BUSID_SPI		   21	/* Serial Periph Interconnect */
#define VXB_BUSID_SD               22   /* SD/SDIO bus type */

/* vxbDevRegInfo->vxbVersion */

/*
 * Starting with version 4 we split the version word into
 * three fields: 16-bit major, 8-bit minor, 8-bit patch-rev.
 */

#define VXB_VER_MAJOR(x)	((x)>>16)
#define VXB_VER_MINOR(x)	(((x)>>8)&0x0ff)
#define VXB_VER_PATCH(x)	((x)&0x0ff)

/*
 * For version 4 and 5 we provide macros in the old style, but
 * we also allow a new, expanded format specifying all three
 * components.  For subsequent versions, we only use the 
 * expanded format.
 */

#define VXB_VER_4_0_0		0x00040000
#define VXB_VER_5_0_0		0x00050000

#define VXBUS_VERSION_1		1
#define VXBUS_VERSION_2		2
#define VXBUS_VERSION_3		3
#define VXBUS_VERSION_4		VXB_VER_4_0_0
#define VXBUS_VERSION_5		VXB_VER_5_0_0

/* pName: device name */

#define MAX_DRV_NAME_LEN        31  /* 31-byte device names */

/* vxbDevIterate flags */
#define VXB_ITERATE_INSTANCES   1   /* instances */
#define VXB_ITERATE_ORPHANS     2   /* dev w/o drv */
#define VXB_LOST_DEVICES	3   /* lost devices */	
#define VXB_ITERATE_VERBOSE     8   /* print diagnostics while running */

#define FIRST_CUSTOM_BUS_ACCESS_METHOD  0x00000100

/* byte-order and other bus access method flags */

/* flags for operation and debug 0x01000000 ... 0x80000000 */

#define BUSAF_VERBOSE           0x01000000

/* debug/test */

#ifdef	VXB_PERFORM_SANITY_CHECKS

/* enable sanity checks in vxbDmaBufLib */

#define VXB_DMA_BUF_DEBUG_CHECKS

#define	VXB_ASSERT_NONNULL(pVar, errVal) \
    if ( pVar == NULL ) \
	return(errVal);

#define	VXB_ASSERT(cond, errVal) \
    if ( ! (cond) ) \
	return(errVal);

#define	VXB_ASSERT_NONNULL_V(pVar) \
    if ( pVar == NULL ) \
	return;

#define	VXB_ASSERT_V(cond) \
    if ( ! (cond) ) \
	return;

#else	/* VXB_PERFORM_SANITY_CHECKS */
#define	VXB_ASSERT_NONNULL(pVar, errVal)
#define	VXB_ASSERT(cond, errVal)
#define	VXB_ASSERT_NONNULL_V(pVar)
#define	VXB_ASSERT_V(cond)
#endif	/* VXB_PERFORM_SANITY_CHECKS */


/* method related macros, for driver use and method caller use */

#define DEVMETHOD(NAME, FUNC)         { (VXB_METHOD_ID)&NAME##_desc, (FUNCPTR) FUNC }
#define DEVMETHOD_END                 { 0, NULL }
#define METHOD_DECL(NAME)             IMPORT char NAME##_desc[];
#define DEVMETHOD_DEF(METHOD, STRING) char METHOD##_desc[]=STRING; 
#define DEVMETHOD_CALL(METHOD)        ((VXB_METHOD_ID)(&METHOD##_desc[0]))

#ifdef __cplusplus
}
#endif

/* list of available methods in vxbMethodDecl.h */

#include <hwif/vxbus/vxbMethodDecl.h>

#ifdef __cplusplus
extern "C" {
#endif

/* vxbus spinlock macros */

#ifdef SPIN_LOCK_TRACE
#define VXB_SPIN_LOCK_TAKE(x)	(*pVxbSpinLockTake)(x, __FILE__, __LINE__)	
#else
#define VXB_SPIN_LOCK_TAKE(x)	(*pVxbSpinLockTake)(x)	
#endif
#define VXB_SPIN_LOCK_GIVE(x)	(*pVxbSpinLockGive)(x)

#define VXB_MAXBARS		10

#define VXB_REG_NONE		0x00000000	/* Unpopulated */
#define VXB_REG_IO		0x00000001	/* I/O space BAR */
#define VXB_REG_MEM		0x00000002	/* memory mapped */
#define VXB_REG_SPEC		0x00000003	/* special/custom */

/*
 * There may not be enough MSI interrupt vectors for all the devices,
 * So the default implementation is sharing the first MSI vector when
 * there is no free vectors to use. This flag is used to disable the
 * shared vector usage. Interrupt controller driver should check this
 * flag to enable or disable this usage.
 */

#define VXB_MSI_NOSHARED_FLAG      0x10

#define VXB_INT_TYPE(type)         ((type) & 0xF)

typedef struct vxbDeviceMethod device_method_t;

/* forward structure/typedefs definitions */

typedef struct vxbDev BUS_DEVICE;
typedef struct vxbDev * BUS_DEVICE_ID;

typedef struct drvBusFuncs DRIVER_INITIALIZATION;
typedef struct vxbDevRegInfo DRIVER_REGISTRATION;
typedef struct vxbDeviceMethod DRIVER_METHOD;

typedef STATUS (*VXB_SUBDEV_ACTION_FUNC)
    (
    struct vxbDev *	devID,  	/* device ID */
    struct vxbDev *	busDevID,	/* bus device ID */
    char *		pArg    /* user-supplied argument */
    );

#define VXB_MULTIPLE_MSI_CNT_FLAG  0xBEEF0000
#define VXB_MULTIPLE_MSI_CNT_MASK  0x0000FFFF

/* dynamic vectors */

struct vxbIntDynaVecInfo
    {
    void (*isr)(void *  ISR);
    void *              pArg;
    UINT64              vecAddr;
    UINT32              vecVal;
    UINT32              inputPin;
    UINT32              vecType;
    UINT32              index;
    /*
     * When program multiple vxbIntDynaVecInfo instance, such as
     * struct vxbIntDynaVecInfo dynaVec[10], the count parameter
     * is used to specified the number of vxbIntDynaVecInfo,
     * the parameter is valid only when it OR on VXB_MULTIPLE_MSI_CNT_FLAG,
     * (count | VXB_MULTIPLE_MSI_CNT_FLAG), otherwise it is useless.
     * refer to vxbPciMSIProgram() routine.
     */
    UINT32              count;
    };

/* structure used for allocate interrupt management */

struct vxbIntPropertyMgmt
    {
    BOOL              found;
    struct vxbDev *   pDev;
    UINT32            type;  /* VXB_INT_PCI_MSI/VXB_INT_PCI_MSIX*/
    UINT32            count;
    int               retValue;
    };

/* VxBus locks */

typedef struct vxbLock * VXB_LOCK;
struct vxbLock 
    {
#ifdef _VXBUS_BASIC_RWSEM
    int                 key;
    int                 counter;
#else
    atomic32_t          initDone;
    SEM_ID              semID;
    int                 readerCount;
#endif /* _VXBUS_BASIC_RWSEM */
    };

/* structure used for interrupt management */

struct vxbintCtlrMgmt
    {
    BOOL              found;
    struct vxbDev *   pIntCtlr;
    int               inputPin;
    struct vxbDev *   pDev;
    int               index;
    VOIDFUNCPTR       pIsr;
    void *            pArg;
    };

#define VXB_LOCK_IMPORT(x) IMPORT struct vxbLock x
#ifdef _VXBUS_BASIC_RWSEM
#define VXB_LOCK_DECL(x) struct vxbLock x = { 0, 0 }
#else
#define VXB_LOCK_DECL(x) struct vxbLock x = { FALSE, NULL, 0 }
#endif /* _VXBUS_BASIC_RWSEM */
#define VXB_LOCK_READER	TRUE
#define VXB_LOCK_WRITER	FALSE

/* typedefs */

/*
 *  An alternative method for bus controllers to provide the
 *  methods used by downstream devices.  This structure is
 *  provided so that the controller can provide a null-terminated
 *  list of method/handler pairs.
 *
 *  When a driver fetches the access methods, the standard methods
 *  are used first.  If the method is not one of the standard
 *  methods (specified in the vxbAccessList structure), or if the
 *  method specified is NULL in the controller's standard methods,
 *  then the vxbAccessMethodsGet() routine searches through any
 *  methods listed in the pMethods field of the vxbAccessList
 *  structure.
 *
 *  In addition, this structure is used by all devices to provide
 *  services to OS modules such as power management.
 */

struct vxbDeviceMethod
    {
    VXB_METHOD_ID	devMethodId;
    FUNCPTR     handler;
    };

/*===============================================================
*
* vxbBusTypeInfo - structure containing busType entry points
*
*  This structure provides entry points into the busType
*  for use by the bus sub-system during initialization and
*  operation.
*
*/

struct vxbBusTypeInfo
    {
    struct vxbBusTypeInfo * pNext;
    UINT32  busID;      /* busID */

/*===============================================================
*
*  The first routines are used during system boot, during
*  bus enumeration and configuration.
*/

    /* init1 */

    STATUS (*busTypeInit1)
        (
        );

    /* init2 */

    STATUS (*busTypeInit2)
        (
        );

    /* connect */

    STATUS (*busTypeConnect)
        (
        );

    /* check for new devices */

    BOOL (*busTypeNewDevPresent)
        (
        );

    /* check whether device and driver match */

    BOOL (*vxbDevMatch)
        (
        struct vxbDevRegInfo * pDriver,
        struct vxbDev * pDev
        );

    };


/*
 * Keep track of busses which are known to be present on the system.
 * This is only used internally, so the structure definition is here
 * instead of in the header file.
 */

struct vxbBusPresent
    {
    struct vxbBusPresent *     pNext;
    struct vxbBusTypeInfo *    pBusType;
    struct vxbDev *     pCtlr;
    struct vxbDev *     instList;
    struct vxbDev *     devList;
    struct vxbLock	listLock; /* for instances/orphans lists protection */
    };

/*
 *  This structure identifies the driver to the bus subsystem.
 *  It is used for driver registration with the bus subsystem.
 *
 *  Each driver or bus controller calls the vxbDevRegister()
 *  routine (prototype is shown below) with a pointer to a
 *  structure declared by the driver.  The information in the
 *  structure is static, so it can be included in the driver's
 *  initialized data segment.
 *
 *  This structure should never be used directly.  Instead,
 *  each bus type defines a structure of its own, with this
 *  structure as the first element (included, not as a pointer).
 *  The bus-defined structure may contain additional information,
 *  such as DEV_ID and VEND_ID on the PCI bus.  To get access
 *  to these structures, include the bus{TYPE}Lib.h file, e.g.
 *  "pciBusLib.h" or "busRioLib.h".
 */

struct vxbDevRegInfo
    {

    /* for next bus type */

    struct vxbDevRegInfo * pNext;

    /* device or bus controller: BUS_DEVID_DEVICE or BUS_DEVID_BUSCTRL */
    UINT32  devID;

    /* bus type and bus subsystem version */
    UINT32  busID;
    UINT32  vxbVersion;

    /* dev/drv name */
    char    drvName[MAX_DRV_NAME_LEN+1];

    /* default registration functions */
    struct drvBusFuncs * pDrvBusFuncs;
    struct vxbDeviceMethod * pMethods;

    /* NULL probe routine indicates always true */

    BOOL (*devProbe)
        (
    struct vxbDev * pDevInfo    /* device info */
    );

    struct vxbParams * pParamDefaults;

    };

/*===============================================================
*
* drvBusFuncs - structure containing driver entry points
*
*  This structure provides entry points into the driver
*  for use by the bus sub-system during initialization and
*  operation.
*
*/

struct drvBusFuncs
    {

/*===============================================================
*
*  The first routines are used during system boot, during
*  bus enumeration and configuration.
*/

    /* initialize driver and device */
    /* called (indirectly) from sysHwInit() */
    /* may be empty function [nullDrv()] for normal drivers */
    void (*devInstanceInit)
        (
        struct vxbDev * pDevInfo    /* device info */
        );

    /* initialize driver and device - second level */
    /* called (indirectly) from sysHwInit2() */
    /* may be empty function [nullDrv()] for bus controller drivers */
    void (*devInstanceInit2)
        (
        struct vxbDev * pDevInfo    /* device info */
        );

    /* connect to higher level entity */
    /* called (indirectly) at the end of sysHwInit2() */
    /* may be empty function [nullDrv()] for bus controllers */
    void (*devInstanceConnect)
        (
        struct vxbDev * pDevInfo    /* device info */
        );

    };

/*
 *  The following structures are used during bus and device
 *  configuration.  Drivers must have already registered with
 *  the bus subsystem.  This information is used during the
 *  bus probe and enumeration phase.
 *
 *  Note that the bus subsystem provides a pCookie pointer,
 *  which can optionally be used by the specific bus
 *  implementation.
 */

struct vxbDev
    {
    /* for bus subsystem internal use */

    struct vxbDev * pNext;
    struct vxbBusPresent * pParentBus; /* parent bus */
    UINT32      versionCounter; /* version number */
    UINT32	unitNumber;	/* unit number */

    /* access functions for use by driver */

    pVXB_ACCESS_LIST pAccess;

    /* access functions provided by driver */

    struct vxbDeviceMethod * pMethods;

    /* register base addresses */

    void *      pRegBase[VXB_MAXBARS];
    void *      pRegBasePhys[VXB_MAXBARS];
    size_t	regBaseSize[VXB_MAXBARS];
    UINT32	regBaseFlags[VXB_MAXBARS];

    /* bus-specific information */

    union
        {
        struct vxbBusPresent * pSubordinateBus;
        void *          pDevPrivate;
        }       u;

    void *      pBusSpecificDevInfo;
    UINT32      busID;

    /* interrupt information */

    void *      pIntrInfo;

    /* device name */

    char *      pName;

    /* driver registration info */

    struct vxbDevRegInfo * pDriver;

    /* per-driver info */

    void *      pDrvCtrl;

    /* parameter info */

    struct vxbParams * pParams;

    UINT32	flags;

    struct vxbLock	devLock; /* lock for protecting device operations */
    
#if (defined _WRS_CONFIG_PWR_MGMT) && (defined _WRS_ARCH_HAS_DEV_PWR_MGMT)
    struct pwr_device *pwrDeviceId;  /* device power management ID */
#endif /* (_WRS_CONFIG_PWR_MGMT) && (_WRS_ARCH_HAS_DEV_PWR_MGMT) */
 
    };

/*
 * The following flags are defined for use with the flags field in
 * the VxBus device instance structure above.
 */

#define VXB_INST_INIT_DONE	0x00000001
#define VXB_INST_INIT2_DONE	0x00000002
#define VXB_INST_CONNECT_DONE	0x00000004

#define VXB_REMOVAL_MASK	0x0000f000
#define VXB_REMOVAL_INSTANCE	0x00001000
#define VXB_REMOVAL_ORPHAN	0x00002000

/* hcfResource.hcfType values */
#define	HCF_RES_STRING	1
#define	HCF_RES_INT	2
#define	HCF_RES_ADDR	3
#define	HCF_RES_LONG	4
#define	RES_STRING	1
#define	RES_INT		2
#define	RES_ADDR	3
#define	RES_LONG	4

/* standard resource names */

#define	VXB_BAUD_RATE	"baudRate"
#define	VXB_CLK_FREQ	"clkFreq"
#define	VXB_MODE	"mode"
#define	VXB_OPTIONS	"options"
#define	VXB_REG_BASE	"regBase"
#define	VXB_REG_BASE_0	"regBase0"
#define	VXB_REG_BASE_1	"regBase1"
#define	VXB_REG_BASE_2	"regBase2"
#define	VXB_REG_BASE_3	"regBase3"
#define	VXB_REG_BASE_4	"regBase4"
#define	VXB_REG_BASE_5	"regBase5"
#define	VXB_REG_BASE_6	"regBase6"
#define	VXB_REG_BASE_7	"regBase7"
#define	VXB_REG_BASE_8	"regBase8"
#define	VXB_REG_BASE_9	"regBase9"
#define	VXB_REG_INTERVAL "regInterval"
#define	VXB_REG_WIDTH	"regWidth"

#define VXB_MMU_ATTR_BUS_MASK	"mmuAttrBusMask"
#define VXB_MMU_ATTR_BUS	"mmuAttrBus"
#define VXB_MMU_ATTR_IO_MASK	"mmuAttrIoMask"
#define VXB_MMU_ATTR_IO		"mmuAttrIo"

/* macros for extracting 32-bit halves of a 64-bit number */

#ifdef	_WRS_CONFIG_LP64
#define VXB_ADDR_LOW32(x)	(UINT32) ((ULONG)(x) & 0xffffffff)
#define VXB_ADDR_HIGH32(x)	(UINT32) (((ULONG)(x) >> 32) & 0xffffffff)
#else
#define VXB_ADDR_LOW32(x)	(UINT32) (x)
#define VXB_ADDR_HIGH32(x)	0
#endif	/* _WRS_CONFIG_LP64 */

/* global data */

IMPORT pVXB_ACCESS_LIST _archAccessFuncs;

/* forward declarations */

IMPORT STATUS vxbLockInit (VXB_LOCK lockId);
IMPORT STATUS vxbLockDelete (VXB_LOCK lockId);
IMPORT STATUS vxbLockGive (VXB_LOCK lockId, BOOL reader);
IMPORT STATUS vxbLockTake (VXB_LOCK lockId, BOOL reader);

IMPORT VOIDFUNCPTR * vxbIntVectorGet (struct vxbDev * pDev, int index);

IMPORT STATUS vxbDriverUnregister (struct vxbDevRegInfo *pDriver);
IMPORT char * vxbBusTypeString (int busType);
IMPORT struct vxbDev * vxbDevStructAlloc (int flags);
IMPORT void vxbDevStructFree (struct vxbDev * pDev);

IMPORT int vxbIntAlloc
    (
    struct vxbDev * pDev,
    UINT32          type,
    UINT32          count
    );
IMPORT void vxbIntFree
    (
    struct vxbDev * pDev
    );
IMPORT STATUS vxbIntConnect
    (
    struct vxbDev * pDev,
    int         index,
    VOIDFUNCPTR     pIsr,
    void *      pArg
    );
IMPORT STATUS vxbIntDisconnect
    (
    struct vxbDev * pDev,
    int         index,
    VOIDFUNCPTR     pIsr,
    void *      pArg
    );
IMPORT BOOL vxbDrvRescan
    (
    struct vxbDevRegInfo * pDriver
    );
IMPORT STATUS vxbDeviceDriverRelease
    (
    struct vxbDev *pDev
    );
IMPORT STATUS vxbIntEnable
    (
    struct vxbDev * pDev,
    int         index,
    VOIDFUNCPTR     pIsr,
    void *      pArg
    );
IMPORT STATUS vxbIntDisable
    (
    struct vxbDev * pDev,
    int         index,
    VOIDFUNCPTR     pIsr,
    void *      pArg
    );

IMPORT STATUS vxbIntAcknowledge
    (
    struct vxbDev * pDev,       /* device information */
    int             index,      /* index of interrupt vector */
    VOIDFUNCPTR     pIsr,       /* ISR */
    void *          pArg        /* parameter */
    );

IMPORT STATUS vxbDevRegister
    (
    struct vxbDevRegInfo * pDevInfo /* per-bus recognition info */
    );

IMPORT STATUS   vxbBusTypeRegister
    (
    struct vxbBusTypeInfo * pBusType
    );

IMPORT  STATUS vxbBusTypeUnregister
    (
    struct vxbBusTypeInfo * pBusType
    );

IMPORT STATUS vxbDevError (void);	/* driver does not support specified
					 * functionality
					 */
IMPORT STATUS nullDrv (void);	/* no action required */
IMPORT BOOL noDev (void);	/* returns FALSE */

IMPORT STATUS vxbBusAnnounce
    (
    struct vxbDev * pBusDev,    /* bus controller */
    UINT32      busID           /* bus type */
    );

IMPORT STATUS vxbDeviceAnnounce
    (
    struct vxbDev *     pBusDev
    );

IMPORT  STATUS vxbDevRemovalAnnounce
    (
    struct vxbDev * pBusDev
    );

IMPORT STATUS vxbLibInit (void);

IMPORT STATUS vxbDevMethodRun
    (
    VXB_METHOD_ID	method,
    void *              pArg
    );
IMPORT FUNCPTR vxbDevMethodGet
    (
    struct vxbDev * pDev,
    VXB_METHOD_ID	method
    );
IMPORT STATUS vxbResourceFind
    (
    struct vxbDev * instance,
    VXB_METHOD_ID	method,
    char * pArg,
    UINT flags
    );
IMPORT STATUS vxbDevIterate
    (
    FUNCPTR     func,           /* function to call */
    void *      pArg,           /* 2nd argument to func */
    UINT32      flags           /* flags to determine what to do */
    );
IMPORT STATUS vxbDevPath
    (
    struct vxbDev *     pBusDev,        /* device */
    FUNCPTR             func,           /* func @ each ctlr */
    void *              pArg            /* 2nd arg to func */
    );

IMPORT	STATUS vxbSubDevAction
    (
    struct vxbDev *		pBusCtlr,
    VXB_SUBDEV_ACTION_FUNC	actionFunc,
    char *			pArg,
    UINT32			flags
    );

IMPORT STATUS vxbInit (void);
IMPORT STATUS vxbDevInit (void);
IMPORT STATUS vxbDevConnect (void);
IMPORT STATUS vxbDevInitInternal (void);
IMPORT STATUS vxbDevConnectInternal (void);
struct vxbDev * vxbDevParent(struct vxbDev * pDev);

pVXB_ACCESS_LIST vxbAccessListGet
    (
    struct vxbDev *     pDev
    );

FUNCPTR vxbAccessMethodGet
    (
    struct vxbDev * pDev,
    UINT32      accessType
    );

IMPORT SPIN_LOCK_ISR_TAKE_FUNC pVxbSpinLockTake;

IMPORT void (*pVxbSpinLockGive)(spinlockIsr_t * lock);

/*
 *  The following structure is used during configuration.  The
 *  BSP provides interrupt routing information in a table containing
 *  the routines that drivers use to enable, disable, and acknowledge
 *  interrupts on interrupt controllers between the device and the
 *  driver.
 *
 *  It's possible that this information may be kept on a per-device
 *  basis.
 *
 *  The configuration file contains a reference to this information,
 *  and stores the information in the HCF record for any device.
 *  The interrupt vector/irq information is extracted from the HCF
 *  record by the routine devResourceIntrGet(), which also checks
 *  for this information.
 */

struct hwIntRoute
    {
    /*
     * NOTE: if the following entries are modified, you must
     * also modify the busAccessList structure, above.
     */

    /* ensure the bus controller does not prevent the specified interrupt */

    STATUS (*vxbHwIntEnable)
        (
        struct vxbDev * pDevInfo,   /* device info */
        int     intNo,              /* additional vector info */
        VOIDFUNCPTR pISR,           /* IRQ */
        void *      pArg
        );

    STATUS (*vxbHwIntDisable)
        (
        struct vxbDev * pDevInfo,   /* device info */
        int     intNo,              /* additional vector info */
        VOIDFUNCPTR pISR,           /* IRQ */
        void *      pArg
        );

    /* clear interrupt on bus controller */

    STATUS (*vxbHwIntAcknowledge)
        (
        struct vxbDev * pDevInfo,   /* device info */
        int     intNo,              /* additional vector info */
        VOIDFUNCPTR pISR,           /* IRQ */
        void *      pArg
        );
    };

IMPORT int vxbTopoShow (void);
IMPORT STATUS vxbPresStructShow
    (
    struct vxbBusPresent * pPres
    );
IMPORT STATUS vxbDevStructShow
    (
    struct vxbDev * pDev
    );
IMPORT void vxbDevPathShow
    (
    struct vxbDev * pDev
    );
IMPORT STATUS plbIntrShow
    (
    VXB_DEVICE_ID       pDev,
    int                 verboseLevel
    );
IMPORT int vxbBusListPrint
    (
    struct vxbBusPresent * pBusPres
    );
IMPORT int devResourceIntrShow
    (
    VXB_DEVICE_ID       pDev
    );
IMPORT void hcfResourceAllShow (void);
IMPORT void hcfResourceShow
    (
    const struct hcfResource * pRes    /* HCF record */
    );
IMPORT void hcfResourceDevShow
    (
    const struct hcfDevice *        pHcf    /* HCF record */
    );
IMPORT void vxbShowLibInit (void);
IMPORT void hwMemShow (void);

IMPORT STATUS vxbLibInit (void);
IMPORT STATUS vxbInit (void);
IMPORT STATUS vxbLibError
    (
    FUNCPTR pAddr,  /* calling routine */
    char *  pMsg    /* error message */
    );
IMPORT BOOL noDev (void);
IMPORT void drvUnloadLibInit (void);
IMPORT STATUS drvUnloadAll (void);
IMPORT int vxbDevTblEnumerate
    (
    VXB_DEVICE_ID       pParent,        /* parent bus controller */
    VXB_ACCESS_LIST *   pAccess,        /* device access API */
    UINT32              busType,        /* bus type */
    STATUS (*busOverride)               /* bus-specific init rtn */
                (VXB_DEVICE_ID pDev)    /* (init rtn arg) */
    );

#ifdef __cplusplus
}
#endif

#endif /* _INC_VXBUS_H */

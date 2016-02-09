/* vxbPciLib.h - PCI bus header file for vxBus */

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
01v,15jan13,j_z  added some PCI MSI process functions declaration.
                 and PCI MSI/MSI-X type defines. (WIND00333514)
01u,31oct12,l_z  Add vxbPciMSIGet declaration. (WIND00373602)
01t,04sep12,l_z  Add vxbPciIntEnable/Disable support. (WIND365027)
01s,26jul12,sye  Removed duplicate method declaration. (WIND00365654)
01r,17oct11,h_k  added pciMinBus member in vxbPciConfig structure.
                 added vxbPciConfigLibWithMinBusInit() prototype. (CQ:288091)
01q,29apr10,pad  Moved extern C statement after include statements.
01p,21apr09,h_k  updated vxbPciIntDisconnect2() for LP64.
                 moved vxbPciConfigBdfPack, vxbPciBusTypeInit, vxbPciIntLibInit
                 vxbPciConfigLibInit, vxbPciAutoConfig, vxbPciIntConnect to
                 vxbPciLib.h.
01o,23feb09,h_k  updated for LP64 support.
01n,01aug08,h_k  added missing vxbPciConfigModifyXxx. (CQ:120805)
01m,09jul08,tor  add struct pciDevAnnounceInfo
01l,18jun08,h_k  changed struct vxbAccessList to VXB_ACCESS_LIST.
01k,01may08,h_k  added busCtlrDevCfgRead_desc and busCtlrDevCfgWrite_desc.
                 removed unused fields from vxbPciDevice structure.
01j,14apr08,h_k  Change structure elements to remove dead code.
01i,20aug07,dtr  Provide spinlock for dll protection.
01h,15jul07,tor  MSI API
01g,11jun07,tor  remove VIRT_ADDR
01f,08mar07,h_k  moved type declarations from vxbPci.c.
01e,06mar07,h_k  added missing dllLib.h inclusion.
01d,17jan07,dtr  Add in Config and IntLib info ptrs here in vxbPciDevice.
01e,09oct06,pdg  placed the earlier method id macros back with the updated id
                 values
01d,19sep06,pdg  replaced method constants with addresses
01c,25oct05,mdo  Add new PCI ctlr define
01b,01sep05,mdo  Add vxb prefix
01a,10aug05,mdo  Phase in new access method
17Jan05,tor  written
*/

#ifndef INC_VXBPCILIB_H
#define INC_VXBPCILIB_H

#include <dllLib.h>
#include <hwif/vxbus/vxbPlbLib.h>
#include <hwif/vxbus/hwConf.h>
#include <spinLockLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#define PCI_CONTROLLER_METHOD_CFG_READ			\
	((VXB_METHOD_ID)busCtlrCfgRead_desc)
#define PCI_CONTROLLER_METHOD_CFG_WRITE			\
	((VXB_METHOD_ID)busCtlrCfgWrite_desc)
#define PCI_CONTROLLER_METHOD_DEV_CFG_READ		\
	((VXB_METHOD_ID)busCtlrDevCfgRead_desc)
#define PCI_CONTROLLER_METHOD_DEV_CFG_WRITE		\
	((VXB_METHOD_ID)busCtlrDevCfgWrite_desc)
#define PCI_CONTROLLER_METHOD_BUS_ACCESS_OVERRIDE	\
	((VXB_METHOD_ID)busCtlrAccessOverride_desc)
#define PCI_CONTROLLER_METHOD_CONVERT_BASE_ADDR		\
	((VXB_METHOD_ID)busCtlrBaseAddrCvt_desc)

/* 
 * Provide method to access PCI bus controllers config lib and 
 * interrupt information.
 */

#define PCI_CONTROLLER_METHOD_CFG_INFO			\
	((VXB_METHOD_ID)busCtlrCfgInfo_desc)
#define PCI_CONTROLLER_METHOD_INTERRUPT_INFO		\
	((VXB_METHOD_ID)busCtlrInterruptInfo_desc)

#define VXB_INT_PCI_INTX           (0x0)
#define VXB_INT_PCI_MSI            (0x1)
#define VXB_INT_PCI_MSIX           (0x2)

/*
 * The previous MSI implementation doesn't use vxbIntAlloc and vxbIntFree
 * routines, but it also allocate the MSI vectors. The vxbIntDisconnect
 * routine doesn't know if it should free the vectors, so add this flag
 * to distinguish this, it is called internal in vxbIntDynaVecConnect
 * method. When this flag is used, vxbIntDisconnect will free the vectors,
 * otherwise vxbIntDisconnect doesn't do anyting, and the driver should
 * explicitly call vxbIntFree to release the vectors.
 */

#define VXB_INT_PCI_LEGACY_MSI     (0x3)

#define VXB_IS_CONTINUOUS_MSI(type) \
    (((type)&(VXB_INT_PCI_MSI))?TRUE:FALSE)

#define VXB_IS_MSI_INT(type) \
    (((type)&(0xF))?TRUE:FALSE)

#ifndef DOC
#define PCI_INT_LINES   255
#endif  /* !DOC */

/* typedefs */

typedef struct vxbPciID         PCI_DEVVEND;
typedef struct vxbPciRegister   PCI_DRIVER_REGISTRATION;
typedef struct vxbPciDevice     PCI_HARDWARE;
typedef struct vxbPciInt        PCI_INTERRUPT_RECORD;
typedef STATUS (*VXB_PCI_FOREACH_FUNC)(VXB_DEVICE_ID busCtrlID,int bus, int dev,
 int func, void *pArg);

/*
 *  The PCI busType uses DEV_ID and VEND_ID to pair devices up
 *  with their drivers.  The driver provides a busPciRegInfo
 *  structure when it registers with the bus subsystem.  If the
 *  bus subsystem finds that the driver registered a bus type
 *  of PCI (or one of the PCI variants), and finds that PCI is
 *  present on the system, then the bus subsystem calls the
 *  PCI-specific device check routine.
 *
 *  In addition, the PCI bus tracks the standard bus, device,
 *  and function values.
 */

struct vxbPciID
    {
    UINT16  pciDevId;
    UINT16  pciVendId;
    };

struct vxbPciRegister
    {
    struct vxbDevRegInfo b;
    int         idListLen;
    struct vxbPciID *   idList;
    };

struct vxbPciConfig
    {
    int         pciMaxBus;	/* Max number of sub-busses */
    STATUS      pciLibInitStatus;
    int         pciMinBus;	/* Minimum number of sub-busses */
    };

struct vxbPciInt
    {
    struct plbIntrEntry plbIntr; /* must be first */
    void *  pCookie;    /* PCI bus cookie: see pciAutoConfigLib */
    spinlockIsr_t pciIntLibSpinlockIsr;
    /* [b,d,f] */
    UINT8   pciBus;     /* bus: device identification */
    UINT8   pciDev;     /* device: device identification */
                        /* function: not required. */

    /* PCI interrupt lines */
    VOIDFUNCPTR * intA;       /* interrupt vector on int-A */
    VOIDFUNCPTR * intB;       /* interrupt vector on int-B */
    VOIDFUNCPTR * intC;       /* interrupt vector on int-C */
    VOIDFUNCPTR * intD;       /* interrupt vector on int-D */
    DL_LIST     * pciIntList;
    void *        msiAddress;
    UINT16        msiData;

    /* interrupt route functions */

    FUNCPTR intEnable;      /* enable interrupt line on intr controller */
    FUNCPTR intDisable;     /* disable interrupt line on intr controller */
    FUNCPTR intAcknowledge; /* acknowledge & clear int line on intr ctrl */
    STATUS  pciIntLibInitStatus;

    BOOL pciIntEnableUsed;  /* 
                             * true when using the vxbPciIntEnable/Disable 
                             * this field is added for compatible. 
                             */
    };

struct vxbPciIntHandlerInfo
    {
    DL_NODE 	node;
    struct vxbPciInt *pIntInfo;
    int irq;
    spinlockIsr_t pciIntHandlerSpinlockIsr;
    DL_LIST	pciIntHandlerList;
    };

struct vxbPciDevice
    {
    UINT8   pciBus;
    UINT8   pciDev;
    UINT8   pciFunc;
    UINT16  pciDevId;
    UINT16  pciVendId;
    void *  pCookie;
    struct vxbPciConfig *pPciConfig; /* PCI config lib info */
    struct vxbPciInt *pIntInfo; /* interrupt info */
    VXB_DEVICE_ID devID; /* bus controller vxBus ID */
    };

/*
*
* pciDevAnnounceInfo - structure used by pciBusAnnounceDevices()
*
* pciBusAnnounceDevices is called after the legacy PCI bus configuration
* has been performed.  The purpose of the routine is to traverse the
* bus and find all devices which are present on the bus.  For each device
* found, the bus subsystem calls vxbDeviceAnnounce() to notify the bus 
* subsystem that a device is present, and establish an instance if the
* driver can be found.
*
* The pciBusAnnounceDevices() routine uses pciConfigForeachFunc() to
* traverse the PCI bus hierarchy.  The information required by each 
* device, in order to establish a working instance, is contained in
* the pciDevAnnounceInfo structure.  This includes the PCI bus methods 
* which the driver will use to access methods, as well as a vxbDev
* struct pointer to indicate the pci controller, which contains
* information about the PCI device's parent bus.
*/

struct pciDevAnnounceInfo
    {
    struct vxbDev *     pDev;   
    pVXB_ACCESS_LIST    pMethods;
    void *              pCookie;
    };

IMPORT STATUS pciRegister (void);
IMPORT void pciBusAnnounceDevices
    (
    pVXB_ACCESS_LIST            pArg,
    struct vxbDev *             pDev,
    void *                      pCookie
    );
IMPORT STATUS vxbPciConfigInByte
    (
    VXB_DEVICE_ID busCtrlID,
    int busNo,    /* bus number */
    int deviceNo, /* device number */
    int funcNo,   /* function number */
    int offset,   /* offset into the configuration space */
    UINT8 * pData /* data read from the offset */
    );
IMPORT STATUS vxbPciConfigInWord
    (
    VXB_DEVICE_ID busCtrlID,
    int busNo,      /* bus number */
    int deviceNo,   /* device number */
    int funcNo,     /* function number */
    int offset,     /* offset into the configuration space */
    UINT16 * pData  /* data read from the offset */
    );
IMPORT STATUS vxbPciConfigInLong
    (
    VXB_DEVICE_ID busCtrlID,
    int busNo,     /* bus number */
    int deviceNo,  /* device number */
    int funcNo,    /* function number */
    int offset,    /* offset into the configuration space */
    UINT32 * pData /* data read from the offset */
    );
IMPORT STATUS vxbPciConfigOutByte
    (
    VXB_DEVICE_ID busCtrlID,
    int busNo,    /* bus number */
    int deviceNo, /* device number */
    int funcNo,   /* function number */
    int offset,   /* offset into the configuration space */
    UINT8 data    /* data written to the offset */
    );
IMPORT STATUS vxbPciConfigOutWord
    (
    VXB_DEVICE_ID busCtrlID,
    int busNo,    /* bus number */
    int deviceNo, /* device number */
    int funcNo,   /* function number */
    int offset,   /* offset into the configuration space */
    UINT16 data   /* data written to the offset */
    );
IMPORT STATUS vxbPciConfigOutLong
    (
    VXB_DEVICE_ID busCtrlID,
    int busNo,    /* bus number */
    int deviceNo, /* device number */
    int funcNo,   /* function number */
    int offset,   /* offset into the configuration space */
    UINT32 data   /* data written to the offset */
    );
IMPORT STATUS vxbPciConfigModifyByte
    (
    VXB_DEVICE_ID       busCtrlID,
    int busNo,          /* bus number */
    int deviceNo,       /* device number */
    int funcNo,         /* function number */
    int offset,         /* offset into the configuration space */
    UINT8 bitMask,      /* Mask which defines field to alter */
    UINT8 data          /* data written to the offset */
    );
IMPORT STATUS vxbPciConfigModifyWord
    (
    VXB_DEVICE_ID busCtrlID,
    int busNo,          /* bus number */
    int deviceNo,       /* device number */
    int funcNo,         /* function number */
    int offset,         /* offset into the configuration space */
    UINT16 bitMask,     /* Mask which defines field to alter */
    UINT16 data         /* data written to the offset */
    );
IMPORT STATUS vxbPciConfigModifyLong
    (
    VXB_DEVICE_ID       busCtrlID,
    int busNo,          /* bus number */
    int deviceNo,       /* device number */
    int funcNo,         /* function number */
    int offset,         /* offset into the configuration space */
    UINT32 bitMask,     /* Mask which defines field to alter */
    UINT32 data         /* data written to the offset */
    );
IMPORT STATUS vxbPciConfigForeachFunc
    (
    VXB_DEVICE_ID pDev,
    UINT8 bus,                      /* bus to start on */
    BOOL recurse,                   /* if TRUE, do subordinate busses */
    VXB_PCI_FOREACH_FUNC funcCheckRtn,  /* routine to call for each PCI func */
    void *pArg                      /* argument to funcCheckRtn */
    );
IMPORT STATUS vxbPciMSIProgram
    (
    VXB_DEVICE_ID pDev,
    struct vxbIntDynaVecInfo *dynaVec
    );
IMPORT STATUS vxbPciMSIEnable
    (
    VXB_DEVICE_ID pDev,
    struct vxbIntDynaVecInfo *dynaVec
    );
IMPORT STATUS vxbPciMSIDisable
    (
    VXB_DEVICE_ID pDev,
    struct vxbIntDynaVecInfo *dynaVec
    );
IMPORT STATUS vxbPciMSIGet
    (
    VXB_DEVICE_ID pInst,
    struct vxbIntDynaVecInfo *dynaVec
    );
IMPORT BOOL vxbPciMSIIsCap
    (
    VXB_DEVICE_ID
    );
IMPORT HCF_DEVICE * pciHcfRecordFind
    (
    int pciBus,      /* PCI Bus number */
    int pciDevice    /* PCI device number */
    );
IMPORT STATUS pciDeviceAnnounce
    (
    VXB_DEVICE_ID busCtrlID,
    UINT8       bus,     /* PCI bus number */
    UINT8       dev,     /* PCI device number */
    UINT8       func,    /* PCI function number */
    void *      pArg     /* pDev */
    );
IMPORT STATUS vxbPciFindDevice
    (
    VXB_DEVICE_ID busCtrlID,
    int    vendorId,    /* vendor ID */
    int    deviceId,    /* device ID */
    int    index,       /* desired instance of device */
    int *  pBusNo,      /* bus number */
    int *  pDeviceNo,   /* device number */
    int *  pFuncNo      /* function number */
    );
IMPORT STATUS vxbPciFindClass
    (
    VXB_DEVICE_ID busCtrlID,
    int    classCode,   /* 24-bit class code */
    int    index,       /* desired instance of device */
    int *  pBusNo,      /* bus number */
    int *  pDeviceNo,   /* device number */
    int *  pFuncNo      /* function number */
    );
IMPORT STATUS vxbPciDevConfig
    (
    VXB_DEVICE_ID busCtrlID,
    int pciBusNo,          /* PCI bus number */
    int pciDevNo,          /* PCI device number */
    int pciFuncNo,         /* PCI function number */
    UINT32 devIoBaseAdrs,  /* device IO base address */
    UINT32 devMemBaseAdrs, /* device memory base address */
    UINT32 command         /* command to issue */
    );
IMPORT STATUS vxbPciConfigReset
    (
    VXB_DEVICE_ID busCtrlID,
    int                 startType       /* for reboot hook, ignored */
    );
IMPORT STATUS     vxbPciMSICtl
    (
    VXB_DEVICE_ID pDev,
    struct vxbIntDynaVecInfo *dynaVec,
    BOOL enable
    );
IMPORT void vxbPciInt
    (
    struct vxbPciIntHandlerInfo *pIntHandlerInfo
    );
IMPORT STATUS vxbPciIntDisconnect
    (
    VXB_DEVICE_ID pDev,
    VOIDFUNCPTR *vector,        /* interrupt vector to attach to     */
    VOIDFUNCPTR routine         /* routine to be called              */
    );
IMPORT STATUS vxbPciIntDisconnect2
    (
    VXB_DEVICE_ID pDev,
    VOIDFUNCPTR *vector,        /* interrupt vector to attach to     */
    VOIDFUNCPTR routine,        /* routine to be called              */
    _Vx_usr_arg_t parameter     /* routine parameter         */
    );
IMPORT void pciConfigEnable
    (
    VXB_DEVICE_ID busCtrlID
    );
IMPORT int vxbPciConfigBdfPack
    (
    int	busNo,    /* bus number */
    int	deviceNo, /* device number */
    int	funcNo    /* function number */
    );
IMPORT STATUS vxbPciBusTypeInit
    (
    struct vxbDev * pDev
    );
IMPORT STATUS vxbPciIntLibInit
    (
    struct vxbPciInt * pIntInfo
    );
IMPORT STATUS vxbPciConfigLibInit
    (
    struct vxbPciConfig *pPciConfig,
    int         pciMaxBus	/* Max number of sub-busses */
    );
IMPORT STATUS vxbPciConfigLibWithMinBusInit
    (
    struct vxbPciConfig *pPciConfig,
    int         pciMaxBus,	/* Max number of sub-busses */
    int         pciMinBus	/* Minimum number of sub-busses */
    );
IMPORT STATUS vxbPciAutoConfig
    (
    VXB_DEVICE_ID busCtrlID
    );
IMPORT STATUS vxbPciIntConnect
    (
    VXB_DEVICE_ID pDev,
    VOIDFUNCPTR *vector,        /* interrupt vector to attach to     */
    VOIDFUNCPTR routine,        /* routine to be called              */
    _Vx_usr_arg_t parameter     /* parameter to be passed to routine */
    );

IMPORT STATUS vxbPciIntEnable
    (
    VXB_DEVICE_ID pDev,
    VOIDFUNCPTR *vector,        /* interrupt vector to attach to     */
    VOIDFUNCPTR routine,        /* routine to be called              */
    _Vx_usr_arg_t parameter,    /* parameter to be passed to routine */
    int level
    );

IMPORT STATUS vxbPciIntDisable
    (
    VXB_DEVICE_ID pDev,
    VOIDFUNCPTR *vector,        /* interrupt vector to attach to     */
    VOIDFUNCPTR routine,        /* routine to be called              */
    _Vx_usr_arg_t parameter,    /* parameter to be passed to routine */
    int level
    );

IMPORT STATUS vxbPciMSIEnable
    (
    VXB_DEVICE_ID              pDev,
    struct vxbIntDynaVecInfo * dynaVec
    );

IMPORT STATUS vxbPciMSIDisable
    (
    VXB_DEVICE_ID              pDev,
    struct vxbIntDynaVecInfo * dynaVec
    );

IMPORT STATUS vxbPciMSIProgram
    (
    VXB_DEVICE_ID              pDev,
    struct vxbIntDynaVecInfo * dynaVec
    );

IMPORT STATUS vxbPciMSIErase
    (
    VXB_DEVICE_ID              pDev,
    struct vxbIntDynaVecInfo * dynaVec
    );

IMPORT STATUS vxbPciDevIntCapabCheck
   (
   VXB_DEVICE_ID               pDev,
   UINT32                      type,
   UINT32                      count
   );

IMPORT VXB_DEVICE_ID vxbPciGetDevInstance
    (
    VXB_DEVICE_ID              busCtrlID,
    UINT8                      busNo,
    UINT8                      deviceNo,
    UINT8                      funcNo
    );

#ifdef __cplusplus
}
#endif

#endif /* INC_VXBPCILIB_H */

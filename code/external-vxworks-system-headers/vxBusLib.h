/* vxBusLib.h - vxBus definitions and API to OS/middleware */

/*
 * Copyright (c) 2005-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01f,29apr10,h_k  added vxbIntToCpuRoute and vxbIntReroute prototype
                 declarations.
01e,18jue09,x_s  Added a subset of the VXBUS_BASIC VSB option macros.
01e,23feb09,h_k  updated for LP64 support.
01d,20jun06,wap  Add vxbNextUnitGet()
01c,28nov05,pdg  Fix for SPR #112638(unit number APIs added)
01b,01sep05,mdo  Add vxb prefix
01a,06jul05,tor  Written
*/

#ifndef _INC_VXBUSLIB_H
#define _INC_VXBUSLIB_H

#ifdef __cplusplus
extern "C" {
#endif

/* types */

typedef struct vxbDev VXB_DEVICE;
typedef struct vxbDev * VXB_DEVICE_ID;

/* Type for method ID */

#ifdef _WRS_CONFIG_LP64
typedef ULONG  VXB_METHOD_ID;
#else
typedef UINT32 VXB_METHOD_ID;
#endif

/*
 * Driver Method callback function for device instances.
 */

typedef STATUS (*VXB_ITERATE_FUNC)
    (
    VXB_DEVICE_ID   devID,  /* device ID */
    void *          pArg    /* user-supplied argument */
    );

/* defines */

/*
 * when OS/Middleware define or use driver methods, they
 * should use the following macros to reference and declare
 * the methodID.
 */

#define VXB_DRIVER_METHOD(NAME)      ((VXB_METHOD_ID)&NAME##_desc[0])
#define VXB_DRIVER_METHOD_DECL(NAME) IMPORT char NAME##_desc[];

/* forward declarations */

/*
 * Run the specified driver method on all devices supporting
 * it, giving pArg as an argument to each VXB_ITERATE_FUNC  */

IMPORT STATUS vxbDeviceMethodRun
    (
    VXB_DEVICE_ID   devID,  /* device ID */
    void *          pArg
    );

/*
 * Iterate through devices and/or instances, and perform
 * the specified action on each.
 */

IMPORT STATUS vxbDeviceIterate
    (
    VXB_ITERATE_FUNC    func,   /* function to call */
    void *      pArg,   /* 2nd argument to func */
    UINT32      flags   /* flags to determine what to do */
    );

/* set the unit number for an instance */

IMPORT	STATUS	vxbInstUnitSet
    (
    VXB_DEVICE_ID	pDev,
    UINT32		unitNumber
    );

/* get the unit number of the instance */

IMPORT	STATUS	vxbInstUnitGet
    (
    VXB_DEVICE_ID	pDev,
    UINT32 *		pUnitNumber	
    );

/* Get the next available unit number */

IMPORT	STATUS	vxbNextUnitGet
    (
    VXB_DEVICE_ID	pDev
    );

/* Re-route all interrupts for a specified CPU */

IMPORT STATUS vxbIntToCpuRoute
    (
    unsigned int destCpu    /* logical index of destination CPU for reroute */
    );

/* Route specified interrupt to destination CPU */

IMPORT STATUS vxbIntReroute
    (
    VXB_DEVICE_ID pRequestor,
    int           interruptIndex,
    cpuset_t      destCpu
    );

/*
 * Show vxBus state
 */

IMPORT void vxBusShow(int verboseLevel);

/* 
 * The subset of the _WRS_CONFIG_VXBUS_BASIC VSB option, this apply to small
 * footprint 
 */

#ifdef _WRS_CONFIG_VXBUS_BASIC
#define _VXBUS_BASIC_VXBDELAY	/* disable system clock vxbDelay() */
#define _VXBUS_BASIC_HWMEMLIB 	/* basic hwMemLib library */
#define _VXBUS_BASIC_SIOPOLL    /* polled mode serial driver */
#define _VXBUS_BASIC_RWSEM      /* disable RW semaphore */
#endif /* _WRS_CONFIG_VXBUS_BASIC */

#ifdef __cplusplus
}
#endif

#endif /* _INC_VXBUSLIB_H */

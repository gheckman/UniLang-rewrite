/* usbTgtFuncDemo.h - Definitions for USB target */

/*
 * Copyright (c) 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
Modification history
--------------------
01a,17may10,s_z  created
*/

/*
DESCRIPTION

Common definitions for the Omap USB controler (device side).
*/

#ifndef __INCusbTgtFuncDemoh
#define __INCusbTgtFuncDemoh

#ifdef  __cplusplus
extern "C" {
#endif

/* includes */

#include <semLib.h>
#include <lstLib.h>
#include <vwModNum.h>
#include <hwif/vxbus/vxBus.h>
#include <usb/usb.h>

IMPORT STATUS usbTgtFuncDemoInit
    (
    void
    );
	
IMPORT STATUS usbTgtFuncDemoUnInit
    (
    void
    );

#ifdef  __cplusplus
}
#endif

#endif  /* usbTgtFuncDemo */

/* driverControl.h -- VxBus Driver Control for 3rd-party driver classes */ 

/*********************************************************************
*
* Copyright (C) 2007, 2010  Wind River Systems, Inc.
* 
* The right to copy, distribute, modify, or otherwise make use
* of this software may be licensed only pursuant to the terms
* of an applicable Wind River license agreement.
*/

/* 
modification history 
--------------------
01b,27may10,pad  Added 'extern C' statement.
01a,21aug07,tor  created 
*/

#ifndef __INCdriverControlh
#define __INCdriverControlh

/* includes */

#include <vxWorks.h>
#include <vxBusLib.h>
#include <hwif/vxbus/vxBus.h>

#ifdef __cplusplus
extern "C" {
#endif

/* typedefs */

struct vxbDriverControl
    {
    char *	driverName;
    int		drvCtrlCmd;
    void *	drvCtrlInfo;
    };

#ifdef __cplusplus
}
#endif

#endif /* __INCdriverControlh */

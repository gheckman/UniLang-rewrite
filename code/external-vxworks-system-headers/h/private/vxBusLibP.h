/* vxBusLibP.h - vxbus private header */

/*
 * Copyright (c) 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01a,31aug10,jpb  written.
*/

#ifndef __INCvxBusLibPh
#define __INCvxBusLibPh

#ifdef __cplusplus
extern "C" {
#endif

#include <vxWorks.h>
#include <vxBusLib.h>

extern STATUS (*_func_vxbIntConnect)(VOIDFUNCPTR * vector, 
                                     VOIDFUNCPTR routine,
                                     _Vx_usr_arg_t parameter);
extern STATUS (*_func_vxbIntDisconnect)(VOIDFUNCPTR * vector, 
                                        VOIDFUNCPTR routine,
                                        _Vx_usr_arg_t parameter);
extern STATUS (*_func_vxbIntEnable)(int vector);
extern STATUS (*_func_vxbIntDisable)(int vector);

extern void   (*_func_vxbUserHookDevInit)(void);

extern STATUS (*_func_vxbPciDevCfgRead)(VXB_DEVICE_ID  pDev,
                                        UINT32         byteOffset,
                                        UINT32         transactionSize,
                                        void *         pDataBuf);

extern STATUS (*_func_vxbPciDevCfgWrite)(VXB_DEVICE_ID       pDev,
                                         UINT32              byteOffset,
                                         UINT32              transactionSize,
                                         UINT32              data);

#ifdef __cplusplus
}
#endif

#endif /* __INCvxBusLibPh */

/* usbTcdFslLib.h - Defines interface to FSL TCD */

/*
 * Copyright (c) 2009, 2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
Modification history
--------------------
01c,09aug13,ljg  Set USB_SBUSCFG to INCR8 for MPC5125 errata workaround 
                 (WIND00405093)
01b,09sep09,w_x  moved config options to usbTcdFslConfig.h (WIND00180575)
01a,08feb09,w_x  created based on fsl_rdb8313 BSP
*/

/*
DESCRIPTION

Defines the interface to the USB TCD (target controller driver) for the
Freescale USB Dual-Role device.
*/

#ifndef __INCusbTcdFslLibh
#define __INCusbTcdFslLibh

#ifdef  __cplusplus
extern "C" {
#endif

/* defines */

#define FSL_USB_DR_PHY_ULPI         0x0001
#define FSL_USB_DR_PHY_UTMI8        0x0002
#define FSL_USB_DR_PHY_UTMI16       0x0003
#define FSL_USB_DR_PHY_SERIAL       0x0004

/* typedefs */

typedef struct usbTcdFslParamsType
    {
    UINT32      ioBase;         /* Base I/O address range */
    UINT16      usbIrq;         /* USB IRQ channel */
    BOOL        hasSysConfig;
    BOOL        hasBigEndianReg;
    BOOL        hasBigEndianDesc;
    BOOL        hasBigEndianSetup;
    BOOL        hasBufferES;
    FUNCPTR     hwInitRoutine;
    UINT32      phyMode;
    UINT32      platformType;
#ifdef FSL_DR_DMA_SUPPORTED
    UINT16      dmaIrq;         /* DMA IRQ channel */
    UINT16      msgIrq;         /* Message/Doorbell IRQ channel */
#endif /* FSL_DR_DMA_SUPPORTED */

    } USB_TCD_FSL_PARAMS_TYPE, *pUSB_TCD_FSL_PARAMS_TYPE;


/* function declaration */

extern STATUS usbTcdFslExec (pVOID pTrb);/* Primary TCD entry point */

#ifdef  __cplusplus
}
#endif

#endif  /* __INCusbTcdFslLibh */

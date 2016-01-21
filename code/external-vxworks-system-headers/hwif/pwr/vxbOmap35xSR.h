/* vxbOmap35xSR.h - OMAP35x vxBus Smart Reflex header file */

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
01c,14dec10,rdl  add some additional voltage control register addresses
01b,16nov10,rdl create OPP specific structures for each vdd
01a,30Aug10,rec created
*/

/*
This file contains data definitions and prototypes for the vxBus driver for 
the OMAP35x Smart Reflex.

See Also OMAP35xx Applications Processor NDA Technical Reference Manual,
Texas Instruments.

*/

#ifndef _INC_VXBOMPAP35XSR_H
#define _INC_VXBOMPAP35XSR_H

/* data definitions */

/* 
 * structure for maintaining data vales tied to OPPs
 */

struct vddOpVals {
    UINT32 nValReciprocal; /* the reciprocal of the SenN and SenP
			    * values used in the error generation */
    UINT32 vdd;		/* set voltage */
    UINT32 errGain;	/* error in voltage gain value */
    UINT32 errWeight;
    UINT32 errMinLimit;
    UINT32 errMaxLimit;
};

typedef struct voltage_control /* device context passed from hwconf to driver */
    {
    VXB_DEVICE_ID	pDev;       /* filled in during driver init */
    volatile UINT32     *vpRegBase; /* voltage processor register base */
    volatile UINT32	*vcCmdRegBase;  /* voltage channel cmd register base */
    UINT32              srClkLength;/* Calculated from TRM Equation 1 */
    UINT32 		avgWeight;  	/* SENP,SENN Average weight */
    int                 opp;        /* current OPP  1..7 */
    int                 numOpp;     /* number of supported OPPs */
    UINT32              scmRegVal;  /* from CONTROL_FUSE_SR */
    UINT32		fClkAddr;   /* functional clock address */
    UINT32		fClkMask;   /* functional clock mask */
    UINT32 		vddMin;	/* minimum voltage */
    UINT32 		vddMax;	/* maximum voltage */
    struct vddOpVals	*oppVal;    /* for OPP specific values */
    } VOLTAGE_CONTROL;


/* global data */


/* public API */

IMPORT void vxbOmap35xSRDrvRegister (void);

IMPORT void vxbOmap35xSRSet
    (
    VXB_DEVICE_ID	pDev,
    int                 opp         /* range 1..n where n is the highest opp */
    );

IMPORT int vxbOmap35xSRGet
    (
    VXB_DEVICE_ID	pDev
    );

IMPORT void vxbOmap35xVPDisable
    (
    VXB_DEVICE_ID	pDev
    );

IMPORT void vxbOmap35xSRDisable
    (
    VXB_DEVICE_ID	pDev
    );

IMPORT void vxbOmap35xVPEnable
    (
    VXB_DEVICE_ID	pDev
    );

IMPORT void vxbOmap35xSREnable
    (
    VXB_DEVICE_ID	pDev
    );

#endif  /* _INC_VXBOMPAP35XSR_H */

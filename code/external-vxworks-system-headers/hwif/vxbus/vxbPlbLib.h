/* vxbPlbLib.h - Processor Local Bus header file for vxBus */

/*
 * Copyright (c) 2005-2010, 2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01o,20jan13,j_z  add intrFlag for plbIntrEntry.
01n,29apr10,pad  Moved extern C statement after include statements.
01m,23feb09,h_k  updated for LP64 support. (CQ:160416)
01l,18jun08,h_k  added pPlbDevControl.
01k,13dec07,slk  temp increase of VXB_INTR_ENTSZ from 4 to 32 for raza
                 int ctlr output pin requirements
01j,04sep07,h_k  fixed an apigen error.
01i,19jul07,rlg  allow more output pins
01h,19jun07,tor  add plbIntrGet forward declaration
01g,15Mar07,tor  update structures
01f,05Mar07,tor  Add #include for required headers
01e,10Oct06,tor  Add intCtlr support
01d,18jul06,wap  Add declaration for pPlbAccessFunctionOverride
01c,16sep05,jb  Adding interrupt level support
01b,01sep05,mdo  Add vxb prefix
01a,10aug05,mdo  Phase in new access method
01_,17Jan05,tor  written
*/

#ifndef INC_VXBPLBLIB_H
#define INC_VXBPLBLIB_H

#include <vxBusLib.h>
#include <hwif/vxbus/vxBus.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

/* these two numbers when mutiplied together determine the number
 * of downstream outputs
 */
#define VXB_INTR_ENTSZ		32	
#define VXB_INTR_TABSZ	124	

/* typedefs */

typedef struct plbDevEntry  PLB_DEVICE_ENTRY;
typedef struct vxbPlbRegister    PLB_DRIVER_REGISTRATION;
typedef struct plbIntrEntry PLB_INTERRUPT;
typedef struct plbIntrEntry     VXB_INTR_ENTRY;

#define INVALD_INDEX  0x0BADBEEF

struct plbIntCtlrEntry
    {
    VXB_DEVICE_ID       intCtlr;
    int                 intCtlrPin;
    };

struct plbIntCtlrTable
    {
    struct plbIntCtlrEntry      intCtlr[VXB_INTR_ENTSZ];
    };

struct pIntCtlrTable
    {
    struct plbIntCtlrTable *    pList[VXB_INTR_TABSZ];
    };


struct plbIntrEntry
    {
    int         		numVectors;
    VOIDFUNCPTR **    		intVecList;
    UINT32 *	    		intLvlList;
    VXB_DEVICE_ID *		intCtlrList;
    struct pIntCtlrTable *      pIntCtlrTable;
    UINT32                      intrFlag;
    };

struct plbDevEntry
    {
    void *      	baseAddress;
    char        	drvName[MAX_DRV_NAME_LEN+1];
    int         	numVectors;
    VOIDFUNCPTR **    	intVecList;
    UINT32 *	    	intLvlList;
    VXB_DEVICE_ID *	intCtlrList;
    };

struct vxbPlbRegister
    {
    struct vxbDevRegInfo    b;
    };

/* global data */

/* forward declarations */

IMPORT STATUS plbInit1
    (
    struct vxbDev * pCtlr
    );
IMPORT void plbRegister (void);

IMPORT VOIDFUNCPTR pPlbAccessFunctionOverride;
IMPORT VOIDFUNCPTR pPlbOptimizedFunctionOverride;
IMPORT VOIDFUNCPTR pPlbDevControl;

IMPORT STATUS plbIntrSet
    (
    VXB_DEVICE_ID       pDev,
    int                 indx,
    VXB_DEVICE_ID       pIntCtlr,
    int                 inputPin
    );
IMPORT STATUS plbIntrGet
    (
    VXB_DEVICE_ID       pDev,
    int                 indx,
    VXB_DEVICE_ID *     ppIntCtlr,      /* out */
    int *               pInputPin       /* out */
    );

IMPORT void vxbLegacyIntInit (void);

#ifdef __cplusplus
}
#endif

#endif /* INC_VXBPLBLIB_H */

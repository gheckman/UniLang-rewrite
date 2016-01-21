/* hwConf.h - hardware configuration resources */

/*
 * Copyright (c) 2005, 2008-2010, 2014 Wind River Systems, Inc. All rights are reserved.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
10jun14,d_l  add _WRS_CONFIG_DYNA_HCF_DEVICE. (VXW6-4795)
01e,29apr10,pad  Moved extern C statement after include statements.
01d,10nov09,h_k  added HCF_RES_LONG type.
01f,03oct08,to   use _WRS_CONFIG_WRHV_GUEST for guest OS build
01e,14jul08,mmi  resource data structure is a constant
01d,13jul08,mmi  make hcfDevices non-constant
01c,06may08,tor  add hwConfig routines
01b,14dec05,pdg  prototype of hcfDeviceGet () added
01a,10May05,tor  created
*/

#ifndef __INChwConfigh
#define __INChwConfigh


/* includes */

#include <vxWorks.h>
#include <vsbConfig.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

/* typedefs */

typedef const struct hcfResource	HCF_RESOURCE;
#if defined(_WRS_CONFIG_WRHV_GUEST) || defined(_WRS_CONFIG_DYNA_HCF_DEVICE)
typedef struct hcfDevice	HCF_DEVICE;
#else   /* _WRS_CONFIG_WRHV_GUEST */
typedef const struct hcfDevice	HCF_DEVICE;
#endif  /* _WRS_CONFIG_WRHV_GUEST || _WRS_CONFIG_DYNA_HCF_DEVICE */

struct hcfResource
    {
    char *  name;
    UINT32  type;
    union
        {
        char *  string;
        UINT32  integer;
        void *  addr;
        ULONG   longval;
        } u;
    };

struct hcfDevice
    {
    char *      devName;
    int         devUnit;
    int         busType;
    int         busIndex;
    int         count;
    const struct hcfResource * pResource;
    };

/* globals */

IMPORT const VOIDFUNCPTR hcfDriverList[];
IMPORT const int hcfDriverNum;

IMPORT HCF_DEVICE hcfDeviceList[];
#ifdef _WRS_CONFIG_DYNA_HCF_DEVICE
IMPORT int hcfDeviceNum;
#else
IMPORT const int hcfDeviceNum;
#endif /* _WRS_CONFIG_DYNA_HCF_DEVICE */

/* locals */

/* forward declarations */

IMPORT	STATUS devResourceGet
    (
    const struct hcfDevice *    pDevice,
    char *                      name,
    int                         type,
    void **                     pDest
    );
IMPORT STATUS devResourceIntrGet
    (
    VXB_DEVICE_ID               pDev,   /* device information */
    const struct hcfDevice *    pHcf    /* HCF record */
    );

IMPORT	HCF_DEVICE * hcfDeviceGet
    (
    VXB_DEVICE_ID	pInst
    );

#ifdef __cplusplus
}
#endif

#endif /* __INChwConfigh */

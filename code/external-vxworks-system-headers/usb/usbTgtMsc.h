/* usbTgtMsc.h - usb target mass storage common header file */

/*
 * Copyright (c) 2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01d,18may12,s_z  Add support for USB 3.0 target (WIND00326012)
01c,12jul11,s_z  Import usbTgtMscInit and usbTgtMscExit routines
01b,24mar11,s_z  Changed based on the code review
01a,24mar11,m_y  written
*/

#ifndef __INCusbTgtMsch
#define __INCusbTgtMsch

/* includes */

#include <usb/usbTgt.h>

#ifdef __cplusplus
extern "C" {
#endif

#define USBTGT_MSC_MAX_ERP_BUF_SIZE       0x800

/* USB target MSC function driver configuration */

typedef struct usr_usbTgt_msc_config
    {
    char  tcdName[USBTGT_MAX_NAME_SZ];
    UINT8 tcdUnit;
    char  funcName[USBTGT_COMMON_STR_LEN];
    char  devProtocol[USBTGT_COMMON_STR_LEN];
    UINT8 funcUnit;
    UINT8 configNum;
    char  devName[255];
    char  devRemovable[USBTGT_COMMON_STR_LEN];
    char  devReadonly[USBTGT_COMMON_STR_LEN];
    }USR_USBTGT_MSC_CONFIG, *pUSR_USBTGT_MSC_CONFIG;

STATUS usbTgtMscLunAdd
    (
    char *     tcdName,
    int        tcdUnit,
    char *     devName,
    char *     devReadonly,
    char *     devRemovable,
    char *     devProtocol
    );
STATUS usbTgtMscLunDel
    (
    char *     tcdName,
    int        tcdUnit,
    char *     devName
    );

void usbTgtMscExit(void);
STATUS usbTgtMscInit
    (
    int devCount
    );


#ifdef __cplusplus
}
#endif

#endif /* __INCusbTgtMsch */


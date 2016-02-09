/* xbdCbioDev.h - CBIO_DEV_ID to XBD interface converter */

/*
 * Copyright (c) 2006, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01b,29apr10,pad  Moved extern C statement after include statements.
01a,11oct06,jlk  Written
*/

#ifndef __INCxbdCbioDevh
#define __INCxbdCbioDevh

/* includes */

#include <cbioLib.h>
#include <drv/xbd/xbd.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

/* Device creation options */
#define XBD_CBIO_OPT_DEFAULT_OPTS  0x00000000
#define XBD_CBIO_OPT_NOWAIT        0x00000001
#define XBD_CBIO_OPT_NOPART        0x00000002

/* forward declarations */

extern STATUS   xbdCbioDevLibInit     (void);
extern device_t xbdCbioDevCreate      (CBIO_DEV_ID cbio, const char *name, 
    unsigned int opts);
extern STATUS   xbdCbioDevDelete      (device_t d, CBIO_DEV_ID *pCbio);

#ifdef __cplusplus
}
#endif

#endif /* __INCxbdCbioDevh */

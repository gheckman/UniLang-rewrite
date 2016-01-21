/* ftlFlashIf.h - interfaces between ftl and underlying flash drivers */ 

/*
 * Copyright (c) 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01a,15jun12,jxu  written.
*/

#ifndef __INCftlFlashIfh
#define __INCftlFlashIfh

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* includes */

#include <private/ftl/ftlOsIf.h>
#include <private/ftl/ftlBm.h>
#include <private/ftl/ftlLibP.h>

/* defines */

/* declarations */

/* ftl flash interfaces */

int ftlFlashErase (FTL_BM_DESC * pBm, fblock_t blkNo, int option);
int ftlFlashRW (FTL_BM_DESC * pBm, FTL_ADDR * pFromAddr, 
            size_t dataLen, char * pBuf, FTL_ADDR * pErrorAddr, 
            size_t * pRetIoLen, int rwFlag);
BOOL ftlIsFactBadBlk (FTL_BM_DESC * pBm, fblock_t blkNo);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INCftlFlashIfh */


/* cavPacket.h - Cavium packet processor date types */

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
01c,20oct10,d_c  Include SDK data types directly from SDK
01b,19aug10,d_c Revert back original SDK names for copied data types
01a,06aug10,d_c  written
*/

#ifndef __INCcavPacketh
#define __INCcavPacketh

#include <arch/mips/private/cavSdkDrvInclude.h>
#include CAV_SDK_DRV_INCLUDE(cvmx-packet.h)

#ifdef	__cplusplus
extern "C" {
#endif

/* Cavium buffer pointer structure */

typedef cvmx_buf_ptr_t CAV_BUF_PTR_T;

#ifdef	__cplusplus
}
#endif

#endif /*  __INCcavPacketh */


/* vbiErrors.h - vbi errors */

/*
 * Copyright (c) 2009-2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01f,08feb11,jlv  Sync with HV 1.3 04-Feb-11 DVD
01e,26may10,jl   Sync with HV 1.2 25-May-10
01d,29apr10,pad  Moved extern C statement after include statements.
01c,16jul09,to   not used for VBI 1.0
                 add vbi memory errors
01b,13jul09,to   add vbMgmt error numbers from v01d for HV 1.1
01a,29jun09,to   created from vbiErrors.h, v01c for HV 1.1
*/

#ifndef __INCvbiErrorsh
#define __INCvbiErrorsh

#include <vxWorks.h>
#include <vsbConfig.h>
#include <wrhv/vbiVersion.h>

#ifdef __cplusplus
extern "C" {
#endif


#define VBI_ERRORS_START		(0)

/* generic vbi errors */

#define VBI_INVALID_VERSION		(VBI_ERRORS_START + (-1))
#define VBI_INVALID_IRQ			(VBI_ERRORS_START + (-2))
#define VBI_INVALID_SHMEM		(VBI_ERRORS_START + (-3))
#define VBI_INVALID_MEM			(VBI_ERRORS_START + (-4))

/* vbi Exceptions error */

#define VBI_EXC_ERROR_START		(VBI_ERRORS_START + (-1000))
#define VBI_EXCBASE_SET_ERROR		(VBI_EXC_ERROR_START + (-1))

/* VIOAPIC errors   */

#define VBI_VIOAPIC_ERROR_START		(VBI_EXC_ERROR_START + (-100))
#define VBI_VIOAPIC_NULL		(VBI_VIOAPIC_ERROR_START + (-1))
#define VBI_VIOAPIC_IRQ_OUTBOUND	(VBI_VIOAPIC_ERROR_START + (-2))
#define VBI_VIOAPIC_IRQ_INVALID_DIR	(VBI_VIOAPIC_ERROR_START + (-3))
#define VBI_VIOAPIC_UNAVAIL		(VBI_VIOAPIC_ERROR_START + (-4))

/* VB MANAGEMENT errors */

#define VBI_VBMGMT_ERROR_START		(VBI_VIOAPIC_ERROR_START + (-100))
#define VBI_ERR_VBMGMT_VB_INVALID	(VBI_VBMGMT_ERROR_START + (-1))
#define VBI_ERR_VBMGMT_INVALID_ARG	(VBI_VBMGMT_ERROR_START + (-2))
#define VBI_ERR_VBMGMT_RESET_FAILED	(VBI_VBMGMT_ERROR_START + (-3))
#define VBI_ERR_VBMGMT_CTX_INVALID	(VBI_VBMGMT_ERROR_START + (-4))

/* VB Device Driver errors */

#define VBI_DEVDRV_ERROR_START		(VBI_VBMGMT_ERROR_START +  (-100))
#define VBI_ERR_ADD_RETRY		(VBI_DEVDRV_ERROR_START +  (-1))
#define VBI_ERR_DEVDRV_NULL_NAME	(VBI_DEVDRV_ERROR_START +  (-2))
#define VBI_ERR_DEVDRV_NULL_HANDLE	(VBI_DEVDRV_ERROR_START +  (-3))

#ifdef __cplusplus
}
#endif

#endif /* __INCvbiVersionh */

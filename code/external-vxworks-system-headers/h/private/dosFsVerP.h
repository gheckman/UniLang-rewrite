/* dosFsVerP.h - dosFs2 vxWorks version header file */

/* Copyright 2001-2002, 2010 Wind River Systems, Inc. */

/*
modification history
--------------------
01c,29apr10,pad  Moved extern C statement after include statements.
01b,21dec03,jkf  moving define of _WRS_DOSFS2_VXWORKS_AE to dosFsVerP.h
01a,20sep01,jkf  written - SPR#69031, common code for both AE & 5.x.
*/

#ifndef __INCdosFsVerPh
#define __INCdosFsVerPh

/* This WRS private header file is subject to change by WRS without notice. */

/* include's */

#include "vxWorks.h"

#ifdef __cplusplus
extern "C" {
#endif

/* XXX temporary workaround for Base6 */    
#define _WRS_DOSFS2_VXWORKS_AE

#ifndef _WRS_VXWORKS_5_X
#   define _WRS_DOSFS2_VXWORKS_AE /* define to build for VxWorks AE */
#endif  /* !_WRS_VXWORKS_5_X */

#ifdef _WRS_DOSFS2_VXWORKS_AE

#   include "memPartLib.h"

/* XXX temporary workaround for Base6 */    
/* #   include "pdLib.h" */

#   include "private/handleLibP.h"	/* for VxWorks AE, use HANDLE */

#   ifndef KHEAP_REALLOC
#       define KHEAP_REALLOC(pBuf,newsize) \
	       memPartRealloc(memPartIdKernel,pBuf,newsize)
#   endif /* KHEAP_REALLOC */

#else /* _WRS_DOSFS2_VXWORKS_AE */

#   include "memPartLib.h"
#   include "classLib.h"		/* for VxWorks 5.x, use OBJ_CORE */
#   include "objLib.h"
#   include "private/objLibP.h"

#endif /* DOSFS2_VXWORKS_AE */

#ifdef __cplusplus
}
#endif

#endif /* __INCdosFsVerPh */

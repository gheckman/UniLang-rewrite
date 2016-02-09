/* dshmSvcMng.h - dSHM node manager service functionalities */

/*
 * Copyright (c) 2006-2007, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01d,15jul10,gjj  deprecated the DSHM technology and added deprecation macros.
01c,29apr10,pad  Moved extern C statement after include statements.
01b,06apr07,bwa  added HW_ID to args of Install().
01a,17nov06,bwa  written.
*/

#ifndef __INCdshmSvcMngh
#define __INCdshmSvcMngh

#include <dshm/dshm.h>

#ifdef __cplusplus
extern "C" {
#endif

STATUS dshmSvcMngInstall (const int hw, const DSHM_HW_ID id) 
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
    
#ifdef __cplusplus
}
#endif

#endif	/* __INCdshmSvcMngh */


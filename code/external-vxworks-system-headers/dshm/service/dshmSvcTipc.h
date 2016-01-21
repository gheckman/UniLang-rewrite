/* dshmSvcTipc.h - DSHM TIPC bearer */

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
01e,15jul10,gjj  deprecated the DSHM technology and added deprecation macros.
01d,29apr10,pad  Moved extern C statement after include statements.
01c,02jul07,bwa  replaced thRealloc by szLinkWindow
01b,03apr07,bwa  added nAllocBufMax parameter.
01a,22sep06,bwa  written.
*/

#ifndef __INCdshmSvcTipch
#define __INCdshmSvcTipch

#include <dshm/dshm.h>

#ifdef __cplusplus
extern "C" {
#endif

void dshm_mediaInit ( const char * const pHwName, const int tSvc,
			const int szReqSmPool, const int szMinSmPool,
			const int szSmBuffer, const int szLinkWindow,
			const int nBcastEntries,
                        const int nAllocBufMax) 
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");

#ifdef __cplusplus
}
#endif

#endif	/* __INCdshmSvcTipch */


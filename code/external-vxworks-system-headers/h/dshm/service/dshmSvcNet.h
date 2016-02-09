/* dshmSvcNet.h - dSHM network interface service backbone */

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
01g,15jul10,gjj  deprecated the DSHM technology and added deprecation macros.
01f,29apr10,pad  Moved extern C statement after include statements.
01e,02jul07,bwa  removed unused parameters to Setup().
01d,07jun07,bwa  added 'resume' handler for congestion.
01c,18mar07,bwa  APIs now take a service number instead of a service object.
01b,19feb07,bwa  updated some function prototypes.
01a,19jul06,bwa  written.
*/

#ifndef __INCdshmSvcNeth
#define __INCdshmSvcNeth

#include <dshm/adapt/pool.h>

#ifdef __cplusplus
extern "C" {
#endif

/* per-service callbacks */
typedef struct _DSHM_SVC_NET_HOOKS
    {
    STATUS(*hTypNetSend)(void *, DSHM_NET_BUF);	/* handling of SEND messages */
    STATUS(*hTypNetBcast)(void *, DSHM_NET_BUF);/* handling of BCAST messages */
    void(*hResume)(void *);			/* tell driver to resume tx */
    void(*unused1)(void *);                     /* future expansion */
    void(*unused2)(void *);                     /* future expansion */
    void(*unused3)(void *);                     /* future expansion */
    } DSHM_SVC_NET_HOOKS;

void * dshmSvcNetSetup ( const char * const pHwName, const int tSvc,
			    const int szReqSmPool, const int szMinSmPool,
			    const int mtu,
			    const int nBcastEntries,
			    const DSHM_SVC_NET_HOOKS * const pHooks,
			    const int nTxAllocBufMax,
                            const int nRxAllocBufMax) 
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
int dshmSvcNetMtuGet ( const uint_t hw, const uint_t svc ) 
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
void dshmSvcNetEnable ( const uint_t hw, const uint_t svc,
			    void * const pDrvObj ) 
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
void dshmSvcNetDisable ( const uint_t hw, const uint_t svc ) 
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
STATUS dshmSvcNetUnicast ( const uint_t hw, const uint_t svc, const int dest,
                            const char * const pData, const int szData) 
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
STATUS dshmSvcNetBcast ( const uint_t hw, const uint_t svc,
			    const char * const pData, const int szData ) 
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");

#ifdef __cplusplus
}
#endif

#endif	/* __INCdshmSvcNeth */


/* dshmMuxLib.h - DSHM service/hw/nodes multiplexer */

/*
 * Copyright (c) 2006-2007, 2009-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01j,14jul10,gjj  deprecated the DSHM technology and added deprecation macros.
01i,29apr10,pad  Moved extern C statement after include statements.
01h,27jan09,pcs  Update due to change in bcopy signature.
01g,24aug07,bwa  renamed to dshmMuxLib.h
01f,24aug07,bwa  changed DSHM_ATOMIC_SET/CLEAR to DSHM_TAS/CLEAR
01e,21jun07,bwa  changed RMW to ATOMIC_SET and _CLEAR
01d,01mar07,bwa  removed node references, added bus hooks.
01c,21dec06,bwa  removed usage of FUNCPTR.
01b,29jul06,bwa  added hooks data structures;
                 updated routine prototypes.
01a,05jul06,bwa  written.
*/

#ifndef __INCdshmMuxh
#define __INCdshmMuxh

#include <dshm/dshm.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _DSHM_HW_HOOKS
    {
    void*(*alloc)	/* memory allocation */
	(
	DSHM_PEER_ID,
	int * const,
	const int
	);
    STATUS(*free)	/* memory deallocation */
	(
	DSHM_PEER_ID,
	void * const
	);
    STATUS(*tx)		/* regular transmit */
	(
	DSHM_PEER_ID,
	DSHM_TYPE()
	);
    STATUS(*bcast)	/* broadcast on hw bus */
	(
	DSHM_PEER_ID,
	DSHM_TYPE()
	);

    DSHM_TAS tas;       /* test-and-set routine */
    DSHM_TAS_CLEAR clear;   /* test-and-set clear routine */

    void*(*offToAddr)	/* sm offset to local address */
	(
	DSHM_PEER_ID,
	const uint32_t
	);
    uint32_t(*addrToOff)/* local address to sm offset */
	(
	DSHM_PEER_ID,
	const void * const
	);
    uint16_t(*localAddr)/* obtain address of local node */
	(
	DSHM_PEER_ID
	);
    VIRT_ADDR(*vmAlloc)	/* address range allocation (manager only) */
	(
	DSHM_PEER_ID,
	const int
	);
    void(*fastcopy)	/* fast bcopy, dma, page swap, etc */
	(
	const char *,
	char *,
	size_t
	);
    } DSHM_HW_HOOKS;
    
typedef struct _DSHM_SVC_HOOKS
    {
    STATUS (*rx)	/* called when traffic for the service is received */
	(
	void * const pSvcObj,
	DSHM_TYPE()
	);
    STATUS (*join)	/* called when a node joins the system */
	(
	void * const pSvcObj,
	const uint_t addr
	);
    void (*leave)	/* called when a node leaves the system */
	(
	void * const pSvcObj,
	const uint_t addr
	);
    void (*stop)	/* called when the service stops */
	(
	void * const pSvcObj
	);
    } DSHM_SVC_HOOKS;

/*
 * Note that this is the last version of VxWorks that will include DSHM.
 * Current versions of VxWorks include the technology called MIPC whose 
 * functionality replaces that of DSHM. New applications should consider 
 * use of MIPC as a better alternative for multi-OS use.
 */

void dshmMuxLibInit ( const uint_t maxHwReg, const uint_t maxSvc ) 
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
int dshmMuxHwRegister ( const DSHM_HW_ID id, const char * const name,
			    const uint_t maxNodes,
			    const DSHM_HW_HOOKS * const pHooks ) 
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
int dshmMuxHwGet ( const char * const name ) 
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
int dshmMuxHwNodesNumGet ( const uint_t hw ) 
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
DSHM_TAS dshmMuxHwTasGet ( const uint_t hw ) 
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
DSHM_TAS_CLEAR dshmMuxHwTasClearGet ( const uint_t hw ) 
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
void * dshmMuxHwOffToAddr ( const uint_t hw, const uint32_t offset ) 
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
uint32_t dshmMuxHwAddrToOff ( const uint_t hw, const void * const addr ) 
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
uint16_t dshmMuxHwLocalAddrGet ( const uint_t hw ) 
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
void dshmMuxSvcNodeJoin ( const uint_t hw, const uint16_t addr ) 
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
void dshmMuxSvcNodeLeave ( const uint_t hw, const uint16_t addr ) 
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
STATUS dshmMuxSvcRegister ( const uint_t hw, const uint_t svc,
				const void * const pObj,
				const DSHM_SVC_HOOKS * const pHooks ) 
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
void * dshmMuxSvcObjGet ( const uint_t hw, const uint_t svc ) 
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
void dshmMuxSvcObjRelease ( const uint_t hw, const uint_t svc ) 
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
STATUS dshmMuxSvcWithdraw ( const uint_t hw, const uint_t svc ) 
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
STATUS dshmMuxSvcWithdrawComplete ( const uint_t hw, const uint_t svc ) 
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
int dshmMuxBcast ( const uint_t hw, DSHM(msg), int timeout ) 
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
int dshmMuxMsgSend ( const uint_t hw, DSHM(msg), int unused1, int unused2 ) 
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
int dshmMuxMsgRecv ( const uint_t hw, DSHM(msg), int unused1, int unused2 ) 
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
void * dshmMuxMemAlloc ( const uint_t hw, int * const pSize, const int min ) 
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
STATUS dshmMuxMemFree ( const uint_t hw, void * const pMem ) 
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");

#ifdef __cplusplus
}
#endif

#endif	/* __INCdshmMuxh */


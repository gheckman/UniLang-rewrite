/* dshmSm.h - DSHM protocol for messaging over shared memory */

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
01k,15jul10,gjj  deprecated the DSHM technology and added deprecation macros.
01j,29apr10,pad  Moved extern C statement after include statements.
01i,24aug07,bwa  changed DSHM_ATOMIC_SET/CLEAR to DSHM_TAS/CLEAR
01h,21jun07,bwa  changed RMW to ATOMIC_SET and _CLEAR
01g,18jun07,bwa  updated following code review.
01f,11may07,bwa  added handshaking.
01e,08apr07,bwa  udpate routine prototypes.
01d,02feb07,bwa  adapted to new spinlock data type.
01c,21dec06,bwa  major update to support anchor not contiguous with rest of sm.
01b,29jul06,bwa  added pinging of heartbeat.
01a,05jul06,bwa  written.
*/

#ifndef __INCdshmSmh
#define __INCdshmSmh

#include <dshm/dshm.h>
#include <dshm/util/dshmNowRing.h>

#ifdef __cplusplus
extern "C" {
#endif

#define DSHM_SM_NRETRIES_DEFAULT 256

#define DSHM_SM_HANDSHAKE 	uint32_t

#define DSHM_HANDSHAKE_PRESENT  0xffffffff

#define DSHM_SM_RST             0x55555555  /* no endianness issue with these */
#define DSHM_SM_ACK             0xaaaaaaaa

/* in SM, either local RAM or remote: network byte-order
 */
typedef struct _DSHM_ANCHOR
    {
    volatile uint16_t heartbeat;    /* increments every heartbeat */
    uint16_t version;		    /* SM messaging version */
    uint32_t oSM;		    /* offset to rest of shared memory */
    DSHM_SM_HANDSHAKE scanHandshake;/* set if a handshake is present */
    DSHM_SM_HANDSHAKE handshake[1]; /* really an array of one entry per node in
                                     * the system. */
    } DSHM_ANCHOR;

#define DSHM_ANCHOR_SIZE(n) \
    (sizeof(DSHM_ANCHOR) + ((n - 1) * sizeof (DSHM_SM_HANDSHAKE)))

typedef struct _DSHM_SM_SM_INFO
    {
    uint32_t oRingTbl;	        /* offset to table of offsets to rings */
    uint16_t nNodesMax;	        /* maximum number of nodes in the system */
    uint16_t nEntries;	        /* number of entries in each ring */
    uint16_t szEntry;	        /* size of one entry in each ring */
    uint16_t szRingTblEntry;	/* size of one table entry */
    uint32_t bsp[2];		/* BSP-specifics */
    } DSHM_SM_SM_INFO;

/* in local RAM: host byte-order
 */
typedef struct _DSHM_SM_INFO
    {
    DSHM_SM_SM_INFO *pSmSmInfo;	/* pointer to local info in SM */
    DSHM_ANCHOR *pAnchor;	/* pointer to local anchor */
    void *pSmPool;		/* pointer to local pool of SM */
    DSHM_TIMER_ID heart;	/* heartbeat timer ID */
    DSHM_TAS tas;               /* test-and-set on shared memory */
    DSHM_TAS_CLEAR clear;       /* test-and-set clear on SM */
    uint32_t *pRingTbl;		/* pointer to ring offset table */
    void *pRings;		/* pointer to messaging rings */
    int szPool;			/* size of the local SM pool */
    uint32_t nRetries;		/* number of retries trying to write */
    uint16_t node;		/* current node's number */
    uint16_t nNodesMax;		/* max number of nodes in the msg'ing system*/
    } DSHM_SM_INFO;

/* configuration parameters from user
 */
typedef struct _DSHM_SM_CFG_PARAMS 
    {
    DSHM_TAS tas;               /* test-and-set on shared memory */
    DSHM_TAS_CLEAR clear;       /* test-and-set clear on SM */
    void * pAnchor;	        /* pointer to local anchor */
    void * pSmPool;	        /* pointer to local pool of SM */
    int szPool;		        /* size of one node's pool */
    int node;		        /* current node's number */
    int nRetries;	        /* number of retries trying write in a ring */
    int nNodesMax;	        /* maximum number of nodes in the system */
    int nEntries;	        /* number of message entries, -1 for default */
    int szEntry;	        /* size of 1 entry */
    uint32_t bsp[2];	        /* BSP-specifics */
    } DSHM_SM_CFG_PARAMS;

void* dshmSmInit ( DSHM_SM_INFO * const pSmInfo,
		    const DSHM_SM_CFG_PARAMS * const pParams )
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
STATUS dshmSmSystemStart ( DSHM_SM_INFO * pInfo )
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
void dshmSmSystemStop ( DSHM_SM_INFO *pInfo )
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
BOOL dshmSmIsSystemReady (const DSHM_ANCHOR * const pAnchor)
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
void dshmSmBspSpecificsGet (const DSHM_ANCHOR * const pAnchor,
				uint32_t container[])
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
STATUS dshmSmMsgInit (DSHM_SM_INFO * const pInfo, const uint16_t node)
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
uint16_t dshmSmAddrGet ( DSHM_SM_INFO *pInfo )
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
STATUS dshmSmTx ( const DSHM_SM_INFO * const pInfo,
		    const DSHM_ANCHOR * const pAnchor,
		    const char * const load, const int size )
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
STATUS dshmSmBc ( const DSHM_SM_INFO * const pInfo,
		    const DSHM_ANCHOR * const pAnchor,
		    const char * const load, const int size )
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
STATUS dshmSmRx ( const DSHM_SM_INFO * const pSmInfo, int src,
		    char * const buffer, const int size )
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
uint16_t dshmSmPing ( const DSHM_ANCHOR * const pAnchor )
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
BOOL dshmSmIsHandshakePresent (DSHM_SM_INFO * const pSmInfo)
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
void dshmSmHandshakeSend (const DSHM_SM_INFO * const pSmInfo,
                            DSHM_ANCHOR * const pAnchor,
                            const DSHM_SM_HANDSHAKE event)
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
DSHM_SM_HANDSHAKE dshmSmHandshakeRead (DSHM_SM_INFO * const pSmInfo,
                                        uint16_t peer)
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");

#ifdef __cplusplus
}
#endif

#endif  /* __INCdshmSmh */

 

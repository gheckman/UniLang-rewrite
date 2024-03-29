/* endLib.h - definitions for Enhanced Network Drivers */

/*
 * Copyright (c) 1996-1997, 1999-2004, 2006-2008, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
02u,27may10,pad  Moved extern C statement after include statements.
02t,25nov08,dlk  Use scalable semaphore APIs rather than the inline APIs
                 to avoid increasing image size. Use ordinary semaphore APIs
		 for the uniprocessor case.
02s,31oct08,dlk  Added end2BufferPoolConfig().
02r,03sep08,jpb  Renamed VSB header file
02q,27aug08,dlk  Move from deprecated 'minimal' semaphore API to 'inline' API.
                 Use inline semaphores for both UP and SMP.
02p,23jul08,dlk  To avoid problems with redundant Ipcom_pkt typedefs, use
                 'struct Ipcom_pkt_struct *' rather than 'Ipcom_pkt *' args.
02o,24jun08,jpb  Added include path for kernel configurations options set in
                 vsb.  Renamed _WRS_VX_SMP to _WRS_CONFIG_SMP.
02n,05jun08,dlk  Introduce END2_TX_SEM_TAKE()/END2_TX_SEM_GIVE().
02m,08may08,dlk  Added _end2_linkBufPool and end2EtherIIFormLinkHdr().
02l,28apr08,dlk  Added END2_PKT_START() macro.
02k,15apr08,dlk  Added END2_RXPKT_START_SET() macro.
02j,08apr08,dlk  Added end2EtherHdrParse() prototype.
02i,28mar08,dlk  Scalability of endEther/end8023 functions out of endCommon.
02h,22mar08,dlk  MUX2 redesign. 1st checkin.
02g,18jan08,dlk  Rename _inline_semMMinimalTake() --> semMMinimalTake_inline()
                 and so on.
02f,07jan08,gls  Fast semaphores renamed to minimal semaphores
02e,13dec07,dlk  Use fast mutex for the END TX semaphore.
02d,23oct07,dlk  Disable the tuple cache (MCache) for endPoolTupleGet/Free().
02c,05sep07,dlk  Remove excess NULL arguments passed by END_RCV_RTN_CALL().
02b,07dec06,wap  Add jumbo frame support
02a,19jun06,wap  Add flag for making mBlks to be cached
01z,25may06,wap  Add some utility routines
01y,25jun04,rcs  added END_NET_POOL_INIT & END_NET_POOL_CREATE
01x,14jun04,vvv  fixed endM2 stuff (SPR #98070)
01w,22apr04,rae  endM2Packet does not belong here
01v,16apr04,rae  Add endM2Init() etc.
01u,25feb04,vvv  fixed memory leak (SPR #92692)
01t,25nov03,wap  Merge in changes from Snowflake
01s,29sep03,rp   merged from base6_networking_itn2-int
01r,22jan03,rcs  Added MBLK_SIZE and CLBLK_SIZE
01q,13jan03,rae  Merged from velocecp branch (SPR 83033)
01p,17may02,rcs  add for MIB-II interface callbacks. SPR# 77478
01o,08nov01,wap  Add missing prototype for txRcvRtnCall()
01n,10oct01,rae  update copyright
01m,27jun01,rcs  Merge Tor2.0.2 to Tornado-Comp-Drv
01l,23oct00,rae  fixed SPR #33687 by removing semicolon from END_OBJ_READY
01k,16oct00,spm  merged version 01k from tor3_0_x branch (base version 01j):
                 adds link-level broadcast support
01j,29apr99,pul  Upgraded NPT phase3 code to tor2.0.0
01i,18mar99,sj   fixed typo in TK_RCV_RTN_CALL
01h,08dec97,gnn  END code review fixes.
01g,17oct97,vin  changed prototypes.
01f,25sep97,gnn  SENS beta feedback fixes
01e,19aug97,gnn  changes due to new buffering scheme.
01d,12aug97,gnn  changes necessitated by MUX/END update.
01c,07apr97,map  Added more prototypes and END_OBJ_UNLOAD.
01b,03feb97,gnn  Added speed as an argument to MIB stuff.
01a,26dec96,gnn	 written.

*/
 
/*
DESCRIPTION

This include file contains definitions used by the Enhanced Network Driver
library (endLib.c) and by all of the ENDs.

If the macro END_MACROS is set during compilation then all of the functions in
the library will included as macros instead of functions, otherwise all of the
routines will be functions.  This is a time/space tradeoff that can be made at
compile time.

INCLUDE FILES:
*/

#ifndef __INCendLibh
#define __INCendLibh

/* includes */
#include <vsbConfig.h>

#include <wrn/netVersion.h>

#include <end.h>
#include "muxLib.h"

/*
 * 6.7 FIXME:
 * The following is only included because it appears some files
 * came to depend upon some headers that it includes indirectly,
 * during the time we used the inline semaphore APIs, and I
 * don't now have time to fix all the files that wrongly depended
 * upon this. It should be safe, if ugly.
 */
#include <inline/semLibInline.h>

#if defined (_WRS_CONFIG_SMP)
#define END_TX_SEM_SCALABLE
#endif

#ifdef END_TX_SEM_SCALABLE
/* Add SEM_INVERSION_SAFE or SEM_DELETE_SAFE if required... */
#define END_TXSEM_SCALABLE_OPTS \
    (SEM_Q_PRIORITY | \
     SEM_NO_ID_VALIDATE | \
     SEM_NO_ERROR_CHECK | \
     SEM_NO_SYSTEM_VIEWER | \
     SEM_NO_EVENT_SEND)
#endif

#undef END_TX_SEM_INLINE

#ifdef END_TX_SEM_INLINE
#include <inline/semLibInline.h>
/* Add SEM_INVERSION_SAFE or SEM_DELETE_SAFE if required... */
#define END_TXSEM_INLINE_OPTS \
    (SEM_Q_PRIORITY | \
     SEM_NO_ID_VALIDATE | \
     SEM_NO_ERROR_CHECK | \
     SEM_NO_SYSTEM_VIEWER | \
     SEM_NO_EVENT_SEND)
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#define END_MCACHE_SIZE		128
#define END_MCACHE_TAG		0xFABCAC4E
#define END_MCACHE_CLSIZE	1536
#define END_JUMBO_CLSIZE	9056
#define END_MCACHE_INC(x)	(x) = ((x + 1) & (END_MCACHE_SIZE - 1))

#define ETHER_CRC_POLY_BE	0x04c11db6

#define MBLK_SIZE               64
#define CLBLK_SIZE              64

#define END_NET_POOL_CREATE     0
#define END_NET_POOL_INIT       1

#define MIB2_IN_ERRS	0
#define MIB2_IN_UCAST	1
#define MIB2_OUT_ERRS	2
#define MIB2_OUT_UCAST	3

#if 0  /* MIB_ALLOC and MIB_FREE are deprecated */
#define MIB_ALLOC(m2Id, ifType, enetAddr, addrLen, mtu, speed, name, unit)   \
if ((pMibRtn != NULL) && (pMibRtn->mibAlloc != NULL))			     \
    ((* (pMibRtn->mibAlloc)) (m2Id, ifType, (UINT8 *)enetAddr, addrLen, mtu, \
                              speed, name, unit))                            

#define MIB_FREE(m2Id)							    \
if ((pMibRtn != NULL) && (pMibRtn->mibFree != NULL))			    \
    ((* (pMibRtn->mibFree)) (m2Id))
#endif

#define MIB_CNT_UPDATE(m2Id, cntName, pktData, pktLen)			    \
if ((pMibRtn != NULL) && (pMibRtn->mibCntUpdate != NULL))		    \
    ((* (pMibRtn->mibCntUpdate)) (m2Id, cntName, pktLen, pktData))

#define MIB_VAR_UPDATE(m2Id, varName, data)			    \
if ((pMibRtn != NULL) && (pMibRtn->mibVarUpdate != NULL))		    \
    ((* (pMibRtn->mibVarUpdate)) (m2Id, varName, (caddr_t)(ptrdiff_t)data))

#define END2_RCV_RTN_CALL(pEnd, pkt) \
    do  { \
        (pEnd)->receiveRtn ((pEnd), (pkt)); \
        } while ((0))

#define END2_RXPKT_START_SET(pkt, mtu, maxlinkhdr) \
    do  { \
        (pkt)->start = ((((pkt)->maxlen - mtu) & ~0x3) - maxlinkhdr); \
        } while ((0))

#define END2_PKT_START(pkt, mtu, maxlinkhdr) \
    ((((pkt)->maxlen - mtu) & ~0x3) - maxlinkhdr)

#ifdef END_MACROS

#define END_RCV_RTN_CALL(pEnd,pMblk) \
            { \
	    if ((pEnd)->receiveRtn) \
		{ \
		(pEnd)->receiveRtn ((pEnd), pMblk); \
		} \
            else \
		netMblkClChainFree (pMblk); \
            }

#define TK_RCV_RTN_CALL(pEnd,pMblk, netSvcOffset, netSvcType, \
			uniPromiscuous, pSpareData) \
            { \
            if ((pEnd)->receiveRtn) \
                { \
                (pEnd)->receiveRtn ((pEnd), pMblk, netSvcOffset, netSvcType, \
				    uniPromiscuous, pSpareData); \
                } \
            else \
		netMblkClChainFree (pMblk); \
            }

#ifdef END_TX_SEM_INLINE
#define END_TX_SEM_TAKE(pEnd, tmout) \
            (semMTake_inline ((pEnd)->txSem, tmout, END_TXSEM_INLINE_OPTS))

#define END_TX_SEM_GIVE(pEnd) \
            (semMGive_inline ((pEnd)->txSem, END_TXSEM_INLINE_OPTS))
#elif defined (END_TX_SEM_SCALABLE)
#define END_TX_SEM_TAKE(pEnd, tmout) \
            (semMTakeScalable ((pEnd)->txSem, tmout, END_TXSEM_SCALABLE_OPTS))

#define END_TX_SEM_GIVE(pEnd) \
            (semMGiveScalable ((pEnd)->txSem, END_TXSEM_SCALABLE_OPTS))
#elif defined (END_TX_SEM_MINIMAL)
#define END_TX_SEM_TAKE(pEnd, tmout) (semMMinTake ((pEnd)->txSem, tmout))

#define END_TX_SEM_GIVE(pEnd) (semMMinGive ((pEnd)->txSem))
#else
#define END_TX_SEM_TAKE(pEnd, tmout) \
	    (semTake ((pEnd)->txSem,tmout))

#define END_TX_SEM_GIVE(pEnd) \
	    (semGive ((pEnd)->txSem))
#endif /* END_TX_SEMMINIMAL */

#define	END_FLAGS_CLR(pEnd,clrBits) \
            ((pEnd)->flags &= ~(clrBits))

#define	END_FLAGS_SET(pEnd,setBits) \
            ((pEnd)->flags |= (setBits))

#define	END_FLAGS_GET(pEnd) \
	    ((pEnd)->flags)

#define END_MULTI_LST_CNT(pEnd) \
	    (lstCount (&(pEnd)->multiList))

#define END_MULTI_LST_FIRST(pEnd) \
	    (ETHER_MULTI *)(lstFirst (&(pEnd)->multiList))

#define END_MULTI_LST_NEXT(pCurrent) \
	    (ETHER_MULTI *)(lstNext (&pCurrent->node))

#define END_DEV_NAME(end) \
	    (end.devObject.name)
		
#define END_OBJECT_UNLOAD(pEnd) \
	    (endObjectUnload (pEnd))

#define	END_OBJ_INIT(pEnd,pDev,name,unit,pFuncs, pDesc) \
	    endObjInit ((pEnd),pDev,name,unit,pFuncs, pDesc)

#define END_OBJ_READY(pEnd, flags) \
	    endObjFlagSet ((pEnd),flags)

#define END_ERR_ADD(pEnd,code,value) \
	    (mib2ErrorAdd(&(pEnd)->mib2Tbl, code, value))

#define END_MIB_INIT(pEnd,type,addr,addrLen,mtu,speed) \
	    (mib2Init(&(pEnd)->mib2Tbl, type,addr, addrLen, mtu, speed))
#else

#define END_RCV_RTN_CALL(pEnd,pData) \
                endRcvRtnCall((pEnd), pData)
                
#define TK_RCV_RTN_CALL(pEnd,pData, netSvcOffset, netSvcType, \
			uniPromiscuous, pSpareData) \
            tkRcvRtnCall((pEnd), pData, netSvcOffset, netSvcType, \
			     uniPromiscuous, pSpareData)

#define END_TX_SEM_TAKE(pEnd,tmout) \
                endTxSemTake((pEnd), tmout)

#define END_TX_SEM_GIVE(pEnd) \
                endTxSemGive(pEnd)

#define	END_FLAGS_CLR(pEnd,clrBits) \
                endFlagsClr((pEnd), clrBits)

#define	END_FLAGS_SET(pEnd,setBits) \
                endFlagsSet((pEnd), setBits)

#define	END_FLAGS_GET(pEnd) \
                (endFlagsGet((pEnd)))

#define END_MULTI_LST_CNT(pEnd) \
                (endMultiLstCnt((pEnd)))

#define END_MULTI_LST_FIRST(pEnd) \
                (endMultiLstFirst((pEnd)))

#define END_MULTI_LST_NEXT(pCurrent) \
                (endMultiLstNext((pCurrent)))

#define END_DEV_NAME(pEnd) \
                (endDevName((pEnd)))
		
#define END_OBJECT_UNLOAD(pEnd) \
                endObjectUnload((pEnd))
                
#define END_OBJ_UNLOAD(X)	END_OBJECT_UNLOAD(X)


#define	END_OBJ_INIT(pEnd,pDev,name,unit,pFuncs, pDescription) \
	    endObjInit ((pEnd),pDev,name,unit,pFuncs, pDescription)

#define END_OBJ_READY(pEnd, flags) \
	    endObjFlagSet ((pEnd),flags)

#define END_ERR_ADD(pEnd,code,value) \
	    (mib2ErrorAdd(&(pEnd)->mib2Tbl, code, value))

#define END_MIB_INIT(pEnd,type,addr,len,mtu,speed) \
	    (mib2Init(&(pEnd)->mib2Tbl, type, addr, len, mtu, speed))
#endif /* END_MACROS */
                
/*
 * Eventually we may want END2_TX_SEM_TAKE/GIVE to test pEnd->txSem
 * and do nothing if it is NULL, for cases where the TX semaphore is
 * not needed and not allocated.  For now, no such cases are implemented,
 * so we just use END_TX_SEM_TAKE/GIVE.
 */
#define END2_TX_SEM_TAKE(pEnd,tmout) END_TX_SEM_TAKE (pEnd, tmout)
#define END2_TX_SEM_GIVE(pEnd) END_TX_SEM_GIVE (pEnd)

/* typedefs */

typedef struct mib_routines
    {
    FUNCPTR mibTblInit;
    FUNCPTR mibAlloc; 
    FUNCPTR mibFree; 
    FUNCPTR mibCntUpdate; 
    FUNCPTR mibVarUpdate;
    } MIB_ROUTINES;


/* globals */

IMPORT MIB_ROUTINES * pMibRtn; 
IMPORT FUNCPTR endM2Packet;
IMPORT VOIDFUNCPTR _func_end2VxBusConnect;
IMPORT NET_POOL_ID _end2_linkBufPool;

/* These four match prototypes from NET_FUNCS in end.h: */
IMPORT M_BLK_ID (*_func_endEtherAddressForm) ();
IMPORT M_BLK_ID (*_func_end8023AddressForm) ();
IMPORT STATUS (*_func_endEtherPacketDataGet) ();
IMPORT STATUS (*_func_endEtherPacketAddrGet) (M_BLK_ID, M_BLK_ID,
					      M_BLK_ID, M_BLK_ID, M_BLK_ID);

/* locals */

/* forward declarations */


void    end2LibInit (void);
void    endLibInit (void);

STATUS  endMibIfInit (FUNCPTR pMibInitRtn, FUNCPTR pMibAllocRtn,
		      FUNCPTR pMibFreeRtn,
                      FUNCPTR pMibCtrUpdate, FUNCPTR pMibVarUpdate); 
STATUS	endObjInit (END_OBJ* pEndObj, DEV_OBJ* pDevice,
                    char* pBaseName ,int unit, NET_FUNCS* pFuncTable,
                    char* pDescription);
STATUS	endObjFlagSet (END_OBJ*,UINT);
STATUS	mib2Init (M2_INTERFACETBL*,long,UCHAR*,int, int, int);
STATUS	mib2ErrorAdd (M2_INTERFACETBL*, int, int);
void	endTxSemTake (END_OBJ*, int);
void	endTxSemGive (END_OBJ*);
void	endRcvRtnCall (END_OBJ*, M_BLK_ID);
void	tkRcvRtnCall (END_OBJ *, M_BLK_ID, long, long, BOOL, void *);
void	endObjectUnload (END_OBJ*);
void	endFlagsSet (END_OBJ *, int);
void	endFlagsClr (END_OBJ *, int);
int	endFlagsGet (END_OBJ *);
ETHER_MULTI*	endMultiLstFirst (END_OBJ *);
ETHER_MULTI*	endMultiLstNext (ETHER_MULTI *);
M_BLK_ID    endEtherAddressForm (M_BLK_ID pNBuff, M_BLK_ID pSrcAddr,
                                 M_BLK_ID pDstAddr, BOOL bcastFlag);
M_BLK_ID    end8023AddressForm (M_BLK_ID pNBuff, M_BLK_ID pSrcAddr,
                                M_BLK_ID pDstAddr, BOOL bcastFlag);
STATUS  endEtherPacketDataGet (M_BLK_ID pMblk, LL_HDR_INFO * pLinkHdrInfo);
STATUS  endEtherPacketAddrGet (M_BLK_ID pMblk,
                               M_BLK_ID pSrc,
                               M_BLK_ID pDst,
                               M_BLK_ID pESrc,
                               M_BLK_ID pEDst);
STATUS endEtherResolve (void* arg1, void* arg2, void* arg3, void* arg4,
                        void* arg5, void* arg6);

int    end2EtherHdrParse (END_OBJ * pEnd, struct Ipcom_pkt_struct * pkt);
int    end2EtherIIFormLinkHdr (END_OBJ * pEnd, struct Ipcom_pkt_struct * pkt,
			       UINT8 * dstAddr, UINT8 * srcAddr,
			       UINT16 netType);
void   end2BufferPoolConfig (size_t alignment, size_t extra_space);

STATUS endPollStatsInit (void *, FUNCPTR);
STATUS endM2Init (END_OBJ *,  long, UCHAR *, int, int, int, UINT);
STATUS endM2Free (END_OBJ *);
STATUS endM2Ioctl (END_OBJ *, UINT32, caddr_t);

STATUS endPoolCreate (int, NET_POOL_ID *);
STATUS endPoolJumboCreate (int, NET_POOL_ID *);
STATUS endPoolDestroy (NET_POOL_ID);

#undef END_POOL_MCACHE
#ifdef END_POOL_MCACHE

M_BLK_ID endPoolTupleGet (NET_POOL_ID);
void   endPoolTupleFree (M_BLK_ID);
void endMcacheFlush (void);
M_BLK_ID endMcacheGet (void);
STATUS endMcachePut (M_BLK_ID);

#else

/*
 * The Mcache is never hit with the ipnet stack; just use bare
 * linkBufPool operations.
 */
_WRS_INLINE M_BLK_ID endPoolTupleGet
    (
    NET_POOL_ID pNetPool
    )
    {
    /* From a linkBufPool, mBlkGet() returns a full tuple */
    M_BLK_ID pMblk = mBlkGet (pNetPool, M_DONTWAIT, MT_DATA);
    if (pMblk != NULL)
	pMblk->mBlkHdr.mLen = pMblk->mBlkPktHdr.len =
	    pMblk->pClBlk->clSize - pNetPool->clOffset;

    return pMblk;
    }

#define endPoolTupleFree(__m) netMblkClChainFree (__m)

#define endMcacheFlush() do {} while ((0))

#define endMcacheGet() (NULL)

#define endMcachePut() (ERROR)

#endif /* END_POOL_MCACHE */

UINT32 endEtherCrc32BeGet (const UINT8 *, size_t);
UINT32 endEtherCrc32LeGet (const UINT8 *, size_t);

#ifdef __cplusplus
}
#endif

#endif /* __INCendLibh */

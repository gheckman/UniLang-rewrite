/* smEnd.h - WRS shared memory driver header file */

/* Copyright 1984 - 2004, 2010 Wind River Systems, Inc. */

/*
modification history
--------------------
01n,29apr10,pad  Moved extern C statement after include statements.
01m,05oct04,jln  changed EADDR_LEN to SM_EADDR_LEN (spr#102310) 
01l,06feb04,jln  ported to T221 and Base6;
                 add new configuration flags. 
01k,20sep01,mas  added lastError to SM_END_DEV (SPR 70181)
01j,15jun01,mas  removed SM_END_CLST_SIZ, fixed SM_PACKET_ROUNDUP, added
		 SM_MTU (SPR 68195)
01i,30mar01,mas  added netmask storage to SM_END_DEV struct and pre-AE
		 compatibility flag (SPR 64957)
01h,15mar01,mas  added ethernet address support per IEEE-802.3 (SPR 34766)
01g,17jun00,mas  added pRxPktCnt and rxInts to SM device control structure
01f,11jun00,ham  removed reference to etherLib.
01e,07apr00,mas  moved SM common parameters to smLib.h
01d,11feb00,mas  added media support for T3
01c,08oct99,mas  smEnd componentized.
01b,16sep99,mas  removed unused macros; added IOCTL codes for callout hook
		 routines smEndCopyRtn() and smEndMblkCopyRtn(); released
		 (SPR 25573).
01a,28jan99,mas  written based on if_sm.h rev 01f,22sep92.
*/

#ifndef __INCsmEndh
#define __INCsmEndh

/* includes */

#include "end.h"
#include "m2Lib.h"
#include "netinet/if_ether.h"
#include "ioctl.h"
#include "bootLib.h"
#include "smLib.h"
#include "smPktLib.h"

#ifdef __cplusplus
extern "C" {
#endif


/* defines */

/*
 * Definitions for the shared memory END State flags field
 *
 * Flag			Use
 * ---------------	------------------------------------------------------
 * S_LOADED		smEnd successfully loaded
 * S_CPU_ATTACHED	local CPU is attached to shared memory
 * S_ARP_PUB		ethernet H/W address is published to ARP table
 * S_RUNNING		local CPU active in shared memory
 * S_POLLED_SM		shared memory interface is operating in polled mode
 * S_POLLED_END		MUX interface is operating in polled mode
 * S_RCV_TASK_ACTIVE	interrupt driven receive task is active
 * S_MSTR_PRE_AE_COMPAT	pre-AE master node, don't wait for address publishing
 */

#define S_LOADED		0x0001
#define S_CPU_ATTACHED		0x0002
#define S_RUNNING		0x0004
#define S_ARP_PUB		0x0008
#define S_POLLED_SM		0x0010
#define S_POLLED_END		0x0020
#define S_RCV_TASK_ACTIVE	0x0040
#define S_MSTR_PRE_AE_COMPAT	0x8000

#define SM_PARAMS_MAX     256

#define SM_NAME_MAX	  15

#define SM_END_COOKIE     0xfab0fad0

#define SM_MIN_MBLK_NUM   0x10
#define SM_DFLT_MBLK_NUM  0x30

#define SM_MIN_CLBLK_NUM  0x10
#define SM_DFLT_CLBLK_NUM 0x20

#define SM_END_MIN_FBUF	  (1536)	/* min first buffer size */

#define SM_PACKET_ROUNDUP(siz) \
    ( \
     ((((siz) + sizeof(SM_PKT_HDR)) % 16) == 0) ? 0 : \
     (16 - (((siz) + sizeof(SM_PKT_HDR)) % 16)) \
    )

#define SM_END_MIB2_SPEED -1

/* IP address length */

#define IPADDR_LEN	  4

/* ethernet address length and positions */

#define SM_EADDR_LEN         (sizeof(struct ether_addr))

/* maximum smEnd payload (maximum tranfer unit) */

#define	SM_MTU(pDev) \
    ((UINT)pDev->maxPktBytes - (SIZEOF_ETHERHEADER + SM_EADDR_LEN))

/* smEnd ethernet MAC address octet positions */

#define	SM_ETHER_ID_FIRST     (0)
#define	SM_ETHER_ID_SECOND    (1)
#define	SM_ETHER_ID_THIRD     (2)
#define SM_ETHER_EUI64_FOURTH (3)
#define SM_ETHER_EUI64_FIFTH  (4)
#define	SM_ETHER_USER_OPT     (SM_EADDR_LEN-3)
#define	SM_ETHER_UNIT         (SM_EADDR_LEN-2)
#define	SM_ETHER_CPU          (SM_EADDR_LEN-1)

/* configuration flag for SM end */

#define SMEND_SM_SEQ_ADDR             0x0001
#define SMEND_PROXY_SERVER_FLAG       0x0002
#define SMEND_PROXY_CLIENT_FLAG       0x0004 
#define SMEND_PROXY_DEFAULT_ADDR_FLAG 0x0008

/*
 * Maximum delay for initial access to sm from slave processor in ticks.
 * At 100 ticks per second, this is about 30 seconds.
 */

#define SM_MAX_WAIT       3000

#define M_BLK_OVERHEAD    4
#define CL_BLK_OVERHEAD   4
#define CL_OVERHEAD       4

#define PKT_TYPE_MULTI	0x1	/* packet with a multicast address */
#define PKT_TYPE_UNI	0x2	/* packet with a unicast address */
#define PKT_TYPE_NONE	0x4	/* address type is not meaningful */

#define SMEND_DEV_NAME  "sm"

#ifndef _ASMLANGUAGE

/* Macros */

#define etherAdrsPtr(eaddr)	(u_char *)(eaddr)

#define smEndInputCount(pSmEndDev, cpu)  \
    (pSmEndDev)->smPktDesc.cpuLocalAdrs [(cpu)].inputList.count

#define SM_END_ETHER_ADDR_GET(pEnd)                                          \
    ((pEnd)->mib2Tbl.ifPhysAddress.phyAddress)

#define SM_END_ETHER_ADDR_LEN_GET(pEnd)                                      \
    ((pEnd)->mib2Tbl.ifPhysAddress.addrLength)

/* IOCTL codes */

/* get mblk copy routine pointer */

#define SMIOCGMCPYRTN _IOR('s', 1, FUNCPTR)

/* set mblk copy routine pointer */

#define SMIOCSMCPYRTN _IOW('s', 2, FUNCPTR)

/* get chained mblk copy routine pointer */

#define SMIOCGCCPYRTN _IOR('s', 3, FUNCPTR)

/* set chained mblk copy routine pointer */

#define SMIOCSCCPYRTN _IOW('s', 4, FUNCPTR)

/* typedefs */

/* The definition of the shared memory device control structure */

typedef struct sm_end_device	/* SM_END_DEV */
    {
    END_OBJ		end;		/* The class we inherit from. */
    UINT		cookie;		/* sm device validation cookie */
    int			unit;		/* unit number */
    char		devName[SM_NAME_MAX+1]; /* device name */
    SM_ANCHOR *		pAnchor;	/* SM anchor local address */
    char *		pMem;		/* SM local base address */
    char *              pMemAlloc;      /* memory allocated by smEnd */
    ULONG		memSize;	/* total shared memory size in bytes */
    unsigned		tasType;	/* test-and-set type (HARD/SOFT) */
    unsigned		maxCpus;	/* max #CPUs supported in 'sm' */
    unsigned		masterCpu;	/* master CPU number */
    unsigned		localCpu;	/* local cpu number */
    ULONG		maxPktBytes;	/* max size of shared memory packet */
    ULONG		startAddr;	/* start of seq addrs (0 = not seq) */
    ULONG		ipAddr;		/* network address of node */
    int			maxPackets;	/* max #packets CPU can receive */
    int			intType;	/* interrupt method */
    int			intArg1;	/* 1st interrupt argument */
    int			intArg2;	/* 2nd interrupt argument */
    int			intArg3;	/* 3rd interrupt argument */
    int			ticksPerBeat;	/* #CPU ticks per heartbeat */
    ULONG		mbNum;		/* number of mBlks to allocate */
    ULONG		cbNum;		/* number of clBlks to allocate */
    void		(* pSmFree) (void *); /* routine to free memory*/
    BOOL		smAlloc;	/* sm allocated? */
    BOOL		isMaster;	/* we are master CPU? */
    BOOL		isBoot;		/* we are boot device? */
    ULONG		flags;		/* Our local flags. */
    SM_PKT_MEM_HDR *	pSmPktHdr;	/* sm packet header */
    int *		pRxPktCnt;	/* SM pkt CPU input pkt count */
    UINT		rxInts;		/* interrupt counter for rec'vd pkts */
    CL_POOL_ID		clPoolId;	/* cluster pool ID */
    M_BLK_ID		tupleId;	/* receive-ready tuple (mBlk) ID */
    M_BLK_ID		pollQ;		/* polled tuple queue */
    M_BLK_ID		pollQLast;	/* polled tuple queue last entry */
    void *		pMclBlkCfg;	/* mBlk/clBlk config memory */
    void *		pClustMem;	/* cluster pool memory */
    u_char		enPhyAddr[MAXIFPHYADDR]; /* ethernet physical address*/
    SM_PKT_DESC		smPktDesc;	/* shared mem packet desc */
    u_long		masterAddr;	/* master's IP address */
    unsigned		netmask;	/* network address mask */
    END_ERR		lastError;	/* last Mux error recorded */
    BOOT_PARAMS  *      pBootParams;    /* pointer to the boot parameter structure */
    ULONG               configFlag;     /* configuration flag passed by user */
    } SM_END_DEV;

/* externals */

extern SM_END_DEV ** unitTbl;

/* function prototypes */

#if defined(__STDC__) || defined(__cplusplus)
extern STATUS    smEndDevInit (SM_END_DEV * pSmEndDev);
extern void      smEndShowInit (void);
extern STATUS    smNetShow (char * ifName, BOOL zero);
extern END_OBJ * smEndLoad (char * initString);
extern STATUS    smEndInetAddrGet (char *, int, int, char *); 
#else
extern STATUS    smEndDevInit ();
extern void      smEndShowInit ();
extern STATUS    smNetShow ();
extern END_OBJ * smEndLoad ();
extern STATUS    smEndInetAddrGet (); 
#endif /* defined(__STDC__) || defined(__cplusplus) */

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCsmEndh */

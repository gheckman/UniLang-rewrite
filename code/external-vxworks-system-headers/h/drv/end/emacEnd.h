/* emacEnd.h - END based IBM EMAC Ethernet header */

/*
*******************************************************************************
   This source and object code has been made available to you by IBM on an
   AS-IS basis.

   IT IS PROVIDED WITHOUT WARRANTY OF ANY KIND, INCLUDING THE WARRANTIES OF
   MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE OR OF NONINFRINGEMENT
   OF THIRD PARTY RIGHTS.  IN NO EVENT SHALL IBM OR ITS LICENSORS BE LIABLE
   FOR INCIDENTAL, CONSEQUENTIAL OR PUNITIVE DAMAGES.  IBMS OR ITS LICENSORS
   DAMAGES FOR ANY CAUSE OF ACTION, WHETHER IN CONTRACT OR IN TORT, AT LAW OR
   AT EQUITY, SHALL BE LIMITED TO A MAXIMUM OF $1,000 PER LICENSE.  No license
   under IBM patents or patent applications is to be implied by the copyright
   license.

   Any user of this software should understand that neither IBM nor its
   licensors will be responsible for any consequences resulting from the use
   of this software.

   Any person who transfers this source code or any derivative work must
   include the IBM copyright notice, this paragraph, and the preceding two
   paragraphs in the transferred software.

   Any person who transfers this object code or any derivative work must
   include the IBM copyright notice in the transferred software.

   COPYRIGHT   I B M   CORPORATION 2000
   LICENSED MATERIAL  -  PROGRAM PROPERTY OF  I B M"

********************************************************************************
\NOMANUAL
*/

/* Copyright 1984-2004, 2010 Wind River Systems, Inc. */

/*
modification history
--------------------
02b,29apr10,pad  Moved extern C statement after include statements.
02a,07apr06,mmi  added EMAC_AMCC_440EP
01z,16jul04,jln  add TAH definition; add tahBase for TAH; 2 Byte offset
01y,03sep04,mdo  Documentation fixes for apigen
01x,30jun04,jln  add pRxMblkArray member; 10 byte offset
01w,28may04,jln  add EMAC_GIGABIT_CAPABLE_INTERFACE
01v,19may04,jb3  change local flags for SPR 95025
01u,26aug03,jln  change malLib.h to ibmMalDma.h;
                 define EMAC_RX_GROUP_POLL_ENABLE 
01t,18aug03,jln  add emacBspInfo structure; add burstLength
01s,24jul03,jln  add pTxPollBufAdr member
01r,16jul03,jln  rename ibmEmacEnd.h to emacEnd.h; add PHY definition
01q,24jun03,jln  remove restart timer from EMAC_DRV_CTRL
01p,13jun03,jln  modified EMAC_DRV_CTRL structure
01o,29may03,jln  merge ibm440gx change for gigabit support; modify DRV_CTRL
01n,28may03,jtp  Merge IBM changes; add CICADA PHY errata processing to ignore
                  Loss of Carrier Sense.
01m,06nov01,alr  fix (SPR 71487) ibmEmacEnd: driver may instruct MUX to block
 		  (EMAC_TX_BLOCKED/END_ERR_BLOCK) but never call muxTxRestart
01l,18oct01,mcg  Polled mode fixes, added OPB speed variables to main struct.
01k,20aug01,kab  Change ibmEmac to emac - max 4 letter boot dev in DHCP, other
01j,25jul01,pmr  added macro to control memory allocation for loaning buffers
01i,10may01,mcg  extensive changes to driver to remove data cache coherency
                  code, add support for both TX channels, add full-duplex flow
                  control support.  405 kernel must be used.
01h,09may01,pmr  changed ENET_HDR_REAL_SIZ to SIZEOF_ETHERHEADER.
01g,29nov00,s_m  changes from ibm
01f,02nov00,mcg  added semMutexRX to device structure
01e,05jul00,mcg  added phyAnlpr to device structure
01d,15may00,mcg  register name updates to match 405GP User Manual
01c,03mar00 mcg  Added bit fields. TX and RX descriptor queues to 64 entries
01b,07dec99 mcg  Increased default TX and RX descriptor queues to 128 entries
01a,11oct99,mcg  created.
*/

#ifndef __INCibmEmacEndh
#define __INCibmEmacEndh

#ifndef _ASMLANGUAGE

#include "end.h"
#include "cacheLib.h"
#include "drv/dma/ibmMalDma.h"
#include "wdLib.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Defines for inputFlags in the ibmEmacEnd load string.  If none of the flags
 * below are set in the input string, the driver will use one transmit
 * channel, will use cached buffer/clusters (and manage the data cache
 * coherency), and will do transmits without copying (zero copy).  The flags
 * below can be used change the default behavior.
 */

#define EMAC_INPUT_TX_COPY       0x01          /* Do transmits with copy      */
#define EMAC_INPUT_UNCACHED_BUF  0x02          /* Use uncached buffers        */
#define EMAC_INPUT_TX_2_CHANNEL  0x04          /* Use both TX channels        */

#define EMAC_RXCHAN_GROUP_ENABLE       0x1000  /* group all RX channels       */
#define EMAC_RXCHAN_GROUP_POLL_ENABLE  0x2000  /* polling in grouping mode    */

#define EMAC_GIGABIT_CAPABLE_INTERFACE 0x4000  /* flag for 440GX Gigabit port */ 
#define EMAC_XSUM_OFFLOAD_SUPPORT      0x8000  /* flag for 440GX XSUM support */

/*
 * A common buffer descriptor structure is used for transmit and receive
 * operations.  Only the status/control bits have different meaning for TX
 * and RX. Bits 0:5 are used to control the RX and TX behavior of MAL on a
 * per-packet basis.  See malLib.h for the MAL buffer descriptor structure,
 * and the definitions of bits 0:5.
 *
 * Bits 6:15 are used to control the EMAC TX behavior, and to get status
 * about the TX and RX behavior of the EMAC on a per packet basis.
 */

/* EMAC Transmit Control */
#define EMAC_TX_CTRL_GFCS     0x0200           /* Generate FCS                */
#define EMAC_TX_CTRL_GP       0x0100           /* Generate padding            */
#define EMAC_TX_CTRL_ISA      0x0080           /* Insert source address       */
#define EMAC_TX_CTRL_RSA      0x0040           /* Replace source address      */
#define EMAC_TX_CTRL_IVT      0x0020           /* Insert VLAN tag             */
#define EMAC_TX_CTRL_RVT      0x0010           /* Replace VLAN tag            */

#define EMAC_TX_CTRL_XM_SSR0  0x0002           /* TCP xsum and seg on SSR0    */ 
#define EMAC_TX_CTRL_XM_SSR1  0x0004           /* TCP xsum and seg on SSR1    */ 
#define EMAC_TX_CTRL_XM_SSR2  0x0006           /* TCP xsum and seg on SSR2    */ 
#define EMAC_TX_CTRL_XM_SSR3  0x0008           /* TCP xsum and seg on SSR3    */ 
#define EMAC_TX_CTRL_XM_SSR4  0x000a           /* TCP xsum and seg on SSR4    */ 
#define EMAC_TX_CTRL_XM_SSR5  0x000c           /* TCP xsum and seg on SSR5    */ 
#define EMAC_TX_CTRL_XM_ONLY  0x000e           /* tcp xsum only               */

/* EMAC Transmit Status */
#define EMAC_TX_STAT_BFCS     0x0200           /* Bad FCS in packet           */
#define EMAC_TX_STAT_BPP      0x0100           /* Bad previous packet         */
#define EMAC_TX_STAT_LCS      0x0080           /* Loss of carrier sense       */
#define EMAC_TX_STAT_ED       0x0040           /* Excessive deferral          */
#define EMAC_TX_STAT_EC       0x0020           /* Excessive collisions        */
#define EMAC_TX_STAT_LC       0x0010           /* Late collision              */
#define EMAC_TX_STAT_MC       0x0008           /* Multiple collision          */
#define EMAC_TX_STAT_SC       0x0004           /* Single collision            */
#define EMAC_TX_STAT_UR       0x0002           /* Underrun                    */
#define EMAC_TX_STAT_SQE      0x0001           /* Signal quality error (SQE)  */
#define EMAC_TX_STAT          0x03FF           /* All TX STAT bits above      */

/* All the TX status bits that are considered errors */
#ifdef CICADA_PHY_RGMII_10MPS_12DUPLEX_ERRATA
/* Ignore Loss of Carrier Sense Errors for Cicada PHY errata */
#define EMAC_TX_ERRORS       (                     EMAC_TX_STAT_EC   |  \
                              EMAC_TX_STAT_LC   |  EMAC_TX_STAT_UR   |  \
                              EMAC_TX_STAT_SQE)
#else
#define EMAC_TX_ERRORS       (EMAC_TX_STAT_LCS  |  EMAC_TX_STAT_EC   |  \
                              EMAC_TX_STAT_LC   |  EMAC_TX_STAT_UR   |  \
                              EMAC_TX_STAT_SQE)
#endif

/* EMAC Receive Status */
#define EMAC_RX_STAT_OE       0x0200           /* Overrun error               */
#define EMAC_RX_STAT_PP       0x0100           /* Pause packet received       */
#define EMAC_RX_STAT_BP       0x0080           /* Bad packet                  */
#define EMAC_RX_STAT_RP       0x0040           /* Runt packet                 */
#define EMAC_RX_STAT_SE       0x0020           /* Short event                 */
#define EMAC_RX_STAT_AE       0x0010           /* Alignment error             */
#define EMAC_RX_STAT_BFCS     0x0008           /* Bad FCS                     */
#define EMAC_RX_STAT_PTL      0x0004           /* Packet too long             */
#define EMAC_RX_STAT_ORE      0x0002           /* Out of range error          */
#define EMAC_RX_STAT_IRE      0x0001           /* In range error              */
#define EMAC_RX_STAT          0x03FF           /* All RX STAT bits above      */

/* Range error */

#define EMAC_RX_STAT_RE       (EMAC_RX_STAT_IRE |  EMAC_RX_STAT_ORE)

/* RX XSUM error */

#define EMAC_RX_STAT_RX_XSUM  EMAC_RX_STAT_RE

/* All the RX status bits that are considered errors */
#define EMAC_RX_ERRORS       (EMAC_RX_STAT_OE   |  EMAC_RX_STAT_BP   |  \
                              EMAC_RX_STAT_RP   |  EMAC_RX_STAT_SE   |  \
                              EMAC_RX_STAT_AE   |  EMAC_RX_STAT_BFCS |  \
                              EMAC_RX_STAT_PTL  |  EMAC_RX_STAT_RE )

/*
 * Default descriptor initialization values.
 */

#define EMAC_TX_DESC_INIT       (EMAC_TX_CTRL_GFCS | EMAC_TX_CTRL_GP)

#define EMAC_RX_DESC_INIT       (MAL_RX_CTRL_EMPTY | MAL_RX_CTRL_INTR)

/* Definitions for localFlags bits in the EMAC_DRV_CTRL structure */

#define EMAC_HANDLE_RX_RUNNING    0x01        /* HandleRcvInt job running     */
#define EMAC_POLLING_MODE         0x02        /* Currently in polling mode    */
#define EMAC_TX_CLEAN_RUNNING     0x04        /* TX clean in progress         */
#define EMAC_TX_BLOCKED           0x08        /* Ran out of TX descriptors    */
#define EMAC_TX_NOT_RESTARTED     0x10        /* netJob emacTxRestart running */

/*
 * EMAC_BUF_SIZE is 1500 + 14 + 18 = 1532 which is 4 less than an even number
 * of 32 byte cache lines.  Add sizeof(long) cluster overhead and it is 1536.
 * The 18 bytes is padding.
 */

#define EMAC_BUF_SIZE       (ETHERMTU + SIZEOF_ETHERHEADER + 18)
#define EMAC_MIN_FBUF       100        /* Minsize of first buffer in chain */
#define EMAC_SPEED          10000000   /* 10Mbps                              */
#define EMAC_RXD_MIN        8          /* minimum # of RX descriptors/MAL chn */
#define EMAC_TXD_MIN        8          /* minimum # of TX descriptors/MAL chn */
#define EMAC_RXD_DFT        64         /* default # of RX descriptors/MAL chn */
#define EMAC_TXD_DFT        256        /* default # of TX descriptors/MAL chn */
#define EMAC_RXD_MAX        MAL_MAX_DESC   /* max # of RX descriptors/MAL chn */
#define EMAC_TXD_MAX        MAL_MAX_DESC   /* max # of TX descriptors/MAL chn */

#define EMAC_RXD_LOAN_X	    4		/* multiply no. of RX desc. to allow */
					/* for buffer loaning		     */
#define EMAC_RXBUF_OFFSET    0x2        /* force 2 byte offset */

#define EMAC_DEV_NAME       "emac"      /* Name of this device - max 4 char  */
#define EMAC_DEV_DESC       "IBM EMAC End Driver"     /* Description         */

/*
 * Basic unit, maximum, minimum, and default memory sizes.
 * The sizeof(long) in EMAC_BSC_MEM_SIZE is for cluster overhead.
 */
#define EMAC_BSC_MEM_SIZE    (EMAC_BUF_SIZE + sizeof(long))

#define EMAC_MAX_MEM_SIZE    ((EMAC_RXD_MAX * EMAC_RXD_LOAN_X) * EMAC_BSC_MEM_SIZE)
#define EMAC_MIN_MEM_SIZE    ((EMAC_RXD_MIN * EMAC_RXD_LOAN_X) * EMAC_BSC_MEM_SIZE)
#define EMAC_DFT_MEM_SIZE    ((EMAC_RXD_DFT * EMAC_RXD_LOAN_X) * EMAC_BSC_MEM_SIZE)

/* Multiple Individual and Group Address Filter definitions */

#define EMAC_FILTER_CRC_POLY  0x04C11DB6
#define EMAC_ADDR_BYTES       6
#define EMAC_ADDR_BITS        8

/* EMAC type */

#define EMAC_IBM_405GP        2
#define EMAC_IBM_440GP        3
#define EMAC_IBM_440GX        4
#define EMAC_AMCC_440EP       5

/* EMAC speed */

#define EMAC_SPEED_10Mbps        10
#define EMAC_SPEED_100Mbps       100
#define EMAC_SPEED_1000Mbps      1000

/* mode supported in EMAC */

#define PHY_MODE_DISABLED       0x00
#define PHY_MODE_MII            0x01
#define PHY_MODE_SMII           0x02
#define PHY_MODE_RMII           0x03
#define PHY_MODE_GMII           0x04
#define PHY_MODE_RGMII          0x05
#define PHY_MODE_TBI            0x06
#define PHY_MODE_RTBI           0x07

#define PHY_TYPE_UNKNOWN        0xff

#define PHY_HALF_DUPLEX         22
#define PHY_FULL_DUPLEX         44

/* PHY register offsets */

#define PHY_BMCR         0x00        /* Basic Mode Control Reg */
#define PHY_BMSR         0x01        /* Basic Mode Status Reg */
#define PHY_PHYIDR1      0x02        /* PHY identifier Reg 1 */
#define PHY_PHYIDR2      0x03        /* PHY identifier Reg 2 */
#define PHY_ANAR         0x04        /* Auto-neg Advertisement Reg */
#define PHY_ANLPAR       0x05        /* Auto-neg Link Partner Ability Reg */
#define PHY_ANER         0x06        /* Auto-neg Expansion Reg */
#define PHY_ANNPTR       0x07        /* Auto-neg Next Page TX */
#define PHY_PHYSTS       0x10        /* PHY Status Reg  */
#define PHY_MIPSCR       0x11
#define PHY_MIPGSR       0x12
#define PHY_DCR          0x13
#define PHY_FCSCR        0x14
#define PHY_RECR         0x15
#define PHY_PCSR         0x16
#define PHY_LBR          0x17
#define PHY_10BTSCR      0x18
#define PHY_PHYCTRL      0x19

/* PHY BMCR */

#define PHY_BMCR_RESET          0x8000
#define PHY_BMCR_LOOP           0x4000
#define PHY_BMCR_100MB          0x2000
#define PHY_BMCR_AUTON          0x1000
#define PHY_BMCR_POWD           0x0800
#define PHY_BMCR_ISO            0x0400
#define PHY_BMCR_RST_NEG        0x0200
#define PHY_BMCR_DPLX           0x0100
#define PHY_BMCR_COL_TST        0x0080

/* PHY BMSR */

#define PHY_BMSR_100T4          0x8000
#define PHY_BMSR_100TXF         0x4000
#define PHY_BMSR_100TXH         0x2000
#define PHY_BMSR_10TF           0x1000
#define PHY_BMSR_10TH           0x0800
#define PHY_BMSR_PRE_SUP        0x0040
#define PHY_BMSR_AUTN_COMP      0x0020
#define PHY_BMSR_RF             0x0010
#define PHY_BMSR_AUTN_ABLE      0x0008
#define PHY_BMSR_LS             0x0004
#define PHY_BMSR_JD             0x0002
#define PHY_BMSR_EXT            0x0001

/*PHY ANLPAR */

#define PHY_ANLPAR_NP           0x8000
#define PHY_ANLPAR_ACK          0x4000
#define PHY_ANLPAR_RF           0x2000
#define PHY_ANLPAR_T4           0x0200
#define PHY_ANLPAR_TXFD         0x0100
#define PHY_ANLPAR_TX           0x0080
#define PHY_ANLPAR_10FD         0x0040
#define PHY_ANLPAR_10           0x0020
#define PHY_ANLPAR_100          0x0380

/* PHY 10BTSCR */

#define PHY_10BTSCR_HBDS        0x0080

/* Structure to keep track of resources to be freed by ibmEmacSendCleanup */

typedef struct
    {
    UCHAR  * pFree;                     /* Cluster address, Mblk, etc.       */
    int      descNum;                   /* desc num used for this packet     */
    int      lastIndex;                 /* last index for this packet        */
    int      typeFree;                  /* padding                           */
    } EMAC_FREE;

/* Structure to keep track of TX descriptor queue information */

typedef struct
    {
    volatile MAL_BD * pTxDesc;          /* First descriptor in the TX ring    */
    volatile int indexTxD;              /* Current TX descriptor index        */
    volatile int indexTxDClean;         /* Current TX cleanup descriptor index*/
    int          txFreeDesc;            /* free descriptor in this channel    */
    int          numTxD;                /* Number of TX descriptors           */
    int          freeMblkNum;           /* Number of Mblk needed to be free   */
    UINT         getNewPacketTX;        /* Write to EMAC_TMR0 to kick off TX  */
    UINT         fifoAeTX;              /* Tx Fifo Almost Empty value         */
    EMAC_FREE    txFree[EMAC_TXD_MAX];  /* array of info for TX free cleanup  */
    } TX_INFO;

/* Flags used by the txFree arrays */

#define EMAC_TX_FREE_NONE        0
#define EMAC_TX_FREE_CLUSTER     1
#define EMAC_TX_FREE_MBLK        2
#define EMAC_TX_FREE_MBLK_LAST   3

typedef struct emac_phy_info EMAC_PHY_INFO;

typedef struct emacBspInfo
   {
   UINT emacBaseAdr;                     /* EMAC base address */ 
   int malTxChn0;                        /* TX channel 0 No.  */
   int malTxChn1;                        /* TX channel 1 No.  */
   int malRxChn0;                        /* RX channel 0 No.  */

   int intVec;                           /* Interrupt vector  */
   int intLvl;                           /* Interrupt Level   */
   int cacheLineSz;                      /* Cache line size   */   

   int emacType;                         /* type of EMAC (405/440GP/440GX) */
   int burstLength;                      /* burst length      */
   int phyAdrs;                          /* PHY address       */
   int opbSpeedMhz;                      /* OPB bus speed in MHz */
   MAL_DATA      * pMalData;             /* pointer to MAL struct*/
   EMAC_PHY_INFO * pEmacPhyInfo;         /* pointer to PHY_INFO struct */
   
   UINT extFlag1;                        /* reserved flag 1   */ 
   UINT extFlag2;                        /* reserved flag 2   */ 
   UINT tahBase;                         /* TAH base address for EMAC2/3 */
   int  tahIntLvl;                       /* TAH interrupt level */
   UINT reserved3;                       /* reserved 3        */   
   UINT reserved4;                       /* reserved 4        */

   void * pExtBspInfo;                   /* reserved forward compatibility */ 
   } EMAC_BSP_INFO;

/*
 * The definition of the overall driver control structure.  Each instance of
 * the driver creates its own copy of this structure.
 */

typedef struct ibmEmacDevice
    {
    END_OBJ     end;                    /* END_OBJ for this device            */
    int         unit;                   /* Unit number of this EMAC device    */
    UINT        baseAdrs;               /* Base address of EMAC registers     */
    UINT        tahBase;                /* Base address for TAH               */
    UINT8       enetAddr[6];            /* Ethernet MAC address               */
    int         txChn0MalChannel;       /* MAL channel # for EMAC TX channel 0*/
    int         txChn1MalChannel;       /* MAL channel # for EMAC TX channel 1*/
    int         rxChn0MalChannel;       /* MAL channel # for EMAC RX channel 0*/
    MAL_DATA *  pMalData;               /* ptr to MAL data for this EMAC      */
    int         numTxChannels;          /* using 1 or 2 TX Channels           */
    int         txChannel;              /* TX channel next for next transmit  */
    TX_INFO     txInfo[2];              /* Tx desc info                       */
    M_BLK_ID *  pRxMblkArray;           /* pointer to Mblk Array              */
    volatile MAL_BD *    pRxDesc;       /* First descriptor in the RX ring    */
    volatile int indexRxD;              /* Current RX descriptor index        */
    int         maxRxCountPerInt;       /* max Rx packets per ISR             */
    int         numRxD;                 /* Number of RX descriptors           */
    int         totalTxD;               /* Number of TX descriptors           */
    int         ivec;                   /* Ethernet Interrupt vector          */
    int         ilevel;                 /* Ethernet Interrupt level           */
    int         phyAdrs;                /* Address of PHY to be used          */
    USHORT      phyAnlpar;              /* Results of auto-negotiation        */
    char *      memInputAdrs;           /* Memory address from input string   */
    char *      memAdrsMalloc;          /* Memory that was malloced           */
    int         memSizeMalloc;          /* Size of memory that was malloced   */
    char *      memAdrs;                /* Actual address to be used          */
    int         memInputSize;           /* Memory size from input string      */
    int         memSize;                /* Actual memory size to be used      */
    UINT        inputFlags;             /* Flags passed in load string        */
    volatile UINT localFlags;           /* Local status flags                 */
    CACHE_FUNCS * pCacheFuncs;          /* pointer to Cache function          */
    CL_POOL_ID  pClPoolId;              /* Cluster pool Id                    */
    M_CL_CONFIG mClCfg;                 /* mBlk & cluster config structure    */
    CL_DESC     clDesc;                 /* Cluster descriptor table           */
    END_ERR     lastError;              /* Last error sent to muxError        */
    UINT        errorEmac;              /* saves last EMAC error              */
    int         intErrorTX;             /* number of TX error interrupts      */
    int         intErrorRX;             /* number of RX error interrupts      */
    int         cacheLineSize;          /* size of the processor cache line   */
    int         opbSpeedMhz;            /* OPB bus speed in MHz               */
    UINT        stacrOpbSpeed;          /* used in STACR reg OPB speed field  */
    volatile int txFreeDesc;            /* number of free TX descriptor       */
    int         txIntDescCount;         /* TX packets since last TX INT set   */
    int         wMarkLow;               /* low water mark to set TX INT       */
    int         wMarkHigh;              /* high water mark to cleanup TX desc */
    BOOL        recount;                /* flag to set TX interrupt           */
    int         lastIntPktCount;        /* packet count since last TX INT set */
    UCHAR       intNumTbl[64];          /* TX INT setup table                 */
    int         txError;                /* TX error counter                   */
    int         txMacRestart;           /* TX MAC restart counter             */ 
    int         txStallCount;           /* TX stall counter                   */
    int         txStallDescNum;         /* required TX desc num to unblock    */
    UINT32      txEoBIntCount;          /* count of TX EOF interrrupt         */
    int         rxEoBIntCount;          /* RX EOB interrupt count             */
    int         rxDescError;            /* RX descriptor  count               */
    WDOG_ID     monitorTimer;           /* WD to monitor device               */
    int         monitorInterval;        /* time to fire monitor timer in sec  */
    int         txPacketCount;          /* statistic for TX packets           */
    int         rxPacketCount;          /* statistic for RX packets           */
    BOOL        startFlag;              /* device start flag                  */
    EMAC_PHY_INFO * phyInfo;            /* PHY info structure                 */
    int         emacType;               /* EMAC type                          */
    int         burstLength;            /* burst length                       */
    EMAC_BSP_INFO *pEmacBspInfo;        /* pointer to EMAC_BSP_INFO           */
    STATUS      linkStatus;             /* link status                        */ 
    UINT        phySpeed;               /* PHY speed                          */
    UINT        phyDuplex;              /* PHY Duplex                         */
    UINT        phyType;                /* PHY type                           */
    char *      pTxPollBufAdr;          /* cache-safe buffer for TX polling   */
    int         initType;               /* buffer initialization typr         */
    int         tahIntLvl;              /* TAH interrupt                      */
    BOOL        xsumUsrflag;            /* IP/TCP/UDP XSUM flag               */
    BOOL        tahEnableFlag;          /* TAH enabled in BSP                 */
    END_CAPABILITIES    hwCaps;         /* interface capability structure     */
    } EMAC_DRV_CTRL;

/* Struct for PHY information */

struct emac_phy_info
   {
   STATUS  (* phyPreInit)(EMAC_DRV_CTRL *);          /* PHY/MAC interface setup func */
   void    (* phyPreConfig)(EMAC_DRV_CTRL *);        /* Pre autoNegotiation func */
   STATUS  (* phyConfigStart)(EMAC_DRV_CTRL *, UINT); /* start auto negotiation func */
   void    (* phyPostConfig)(EMAC_DRV_CTRL *);       /* Post autoNegotiation func */
   UINT    (* phySpeedGet)(EMAC_DRV_CTRL *);         /* phySpeedGet func pointer */
   UINT    (* phyDuplexGet)(EMAC_DRV_CTRL *);        /* phyDuplexGet func pointer */
   UINT    (* phyTypeGet)(EMAC_DRV_CTRL *);          /* phyTypeGet func pointer */
   UINT    reserved1;                                /* reserved 1 */
   UINT    reserved2;                                /* reserved 2 */
   UINT    reserved3;                                /* reserved 3 */
   UINT    reserved4;                                /* reserved 4 */
   };

/* 
 * TAH register and BIT definitions 
 * The base address of TAH0/TAH1 is passed by loadstring
 */

#define TAH_REVID        0x50                      /* Revision ID            */
#define TAH_MR           0x60                      /* Mode                   */   
#define TAH_SSR0         0x64                      /* Segment size 0         */
#define TAH_SSR1         0x68                      /* Segment size 1         */
#define TAH_SSR2         0x6c                      /* Segment size 2         */
#define TAH_SSR3         0x70                      /* Segment size 3         */
#define TAH_SSR4         0x74                      /* Segment size 4         */
#define TAH_SSR5         0x78                      /* Segment size 5         */
#define TAH_TSR          0x7c                      /* Transmit status (RO)   */

/* TAH REVID register bits */

#define TAH_REVID_RN     0x000fff00                /* REVID_RN               */
#define TAH_REVID_BRN    0x000000FF                /* REVID_BRN              */

/* TAH Mode register bits */

#define TAH_MR_CVR       0x80000000                /* XSUM verify on RX      */ 
#define TAH_MR_SR        0x40000000                /* reset                  */
#define TAH_MR_ST        0x3f000000                /* send threshod          */
#define TAH_MR_TFS       0x00e00000                /* TX FIFO size           */
#define TAH_MR_DTFP      0x00100000                /* parity protection      */
#define TAH_MR_DIG       0x00010000                /* TAH interrupt          */

#define TAH_MR_ST_256    0x01000000                /* 256B Send Threshold    */
#define TAH_MR_ST_512    0x02000000                /* 512B Send Threshold    */
#define TAH_MR_ST_1024   0x04000000                /* 1024B Send Threshold   */
#define TAH_MR_ST_1536   0x06000000                /* 1536B Send Threshold   */   

#define TAH_MR_TFS_2K    0x00200000                /* 2K for TFS             */
#define TAH_MR_TFS_4K    0x00400000                /* 4K for TFS             */
#define TAH_MR_TFS_6K    0x00600000                /* 6K for TFS             */
#define TAH_MR_TFS_8K    0x00800000                /* 8K for TFS             */
#define TAH_MR_TFS_10K   0x00A00000                /* 10K for TFS            */
#define TAH_MR_TFS_16K   0x00000000                /* 16K for TFS            */

/* TAH Segment Size Registers(0 - 5) bits */

#define TAH_SSR_SS       0x3ffe0000                /* Segment Size           */

/* TAH transmit status register bits */

#define TAH_TSR_TFTS     0x80000000                /* TX FIFO too small      */
#define TAH_TSR_UH       0x40000000                /* Unrecognized header    */
#define TAH_TSR_NIPF     0x20000000                /* Not IP V4              */
#define TAH_TSR_IPOP     0x10000000                /* IP Option present      */
#define TAH_TSR_NISF     0x08000000                /* No IEEE SNAP Format    */
#define TAH_TSR_ILTS     0x04000000                /* ip length too short    */
#define TAH_TSR_IPFP     0x02000000                /* ip fragment present    */
#define TAH_TSR_UP       0x01000000                /* Upsupported Protocal   */
#define TAH_TSR_TFP      0x00800000                /* some TCP flag present  */
#define TAH_TSR_SUDP     0x00400000                /* Segmentation for UDP   */
#define TAH_TSR_DLM      0x00200000                /* Data length mismatch   */
#define TAH_TSR_SIEEE    0x00100000                /* segmentation for IEEE  */
#define TAH_TSR_TFPE     0x00080000                /* TX Fifo parity error   */
#define TAH_TSR_SSTS     0x00040000                /* Segment size too small */

/*
 * Ethernet Register and Register Bit Definitions
 * The base address of the EMAC is one of the load string parameters.
 */

#define EMAC_MR0         0x00                      /* Mode Reg 0              */
#define EMAC_MR1         0x04                      /* Mode Reg 1              */
#define EMAC_TMR0        0x08                      /* Transmit Mode 0         */
#define EMAC_TMR1        0x0C                      /* Transmit Mode 1         */
#define EMAC_RMR         0x10                      /* Receive Mode            */
#define EMAC_ISR         0x14                      /* Interrupt Status        */
#define EMAC_ISER        0x18                      /* Interrupt Status Enable */
#define EMAC_IAHR        0x1C                      /* Individual Adrs High    */
#define EMAC_IALR        0x20                      /* Individual Adrs Low     */
#define EMAC_VTPID       0x24                      /* VLAN TPID Reg           */
#define EMAC_VTCI        0x28                      /* VLAN TCI Reg            */
#define EMAC_PTR         0x2C                      /* Pause Timer             */
#define EMAC_IAHT1       0x30                      /* Ind Adrs Hash Table 1   */
#define EMAC_IAHT2       0x34                      /* Ind Adrs Hash Table 2   */
#define EMAC_IAHT3       0x38                      /* Ind Adrs Hash Table 3   */
#define EMAC_IAHT4       0x3C                      /* Ind Adrs Hash Table 4   */
#define EMAC_GAHT1       0x40                      /* Group Adrs Hash Table 1 */
#define EMAC_GAHT2       0x44                      /* Group Adrs Hash Table 2 */
#define EMAC_GAHT3       0x48                      /* Group Adrs Hash Table 3 */
#define EMAC_GAHT4       0x4C                      /* Group Adrs Hash Table 4 */
#define EMAC_LSAH        0x50                      /* Last Source Adrs High   */
#define EMAC_LSAL        0x54                      /* Last Source Adrs Low    */
#define EMAC_IPGVR       0x58                      /* Inter-Frame Gap Value   */
#define EMAC_STACR       0x5C                      /* STA Control             */
#define EMAC_TRTR        0x60                      /* TX Request Threshold    */
#define EMAC_RWMR        0x64                      /* RX High/Low Water Mark  */
#define EMAC_OCTX        0x68                      /* MIB Octets transmitted  */
#define EMAC_OCRX        0x6C                      /* MIB Octets received     */

/*
 * EMAC Mode Reg 0 bit definitions
 */
#define EMAC_MR0_RXI            0x80000000      /* RX MAC idle                */
#define EMAC_MR0_TXI            0x40000000      /* TX MAC idle                */
#define EMAC_MR0_SRST           0x20000000      /* Soft reset                 */
#define EMAC_MR0_TXE            0x10000000      /* TX MAC enable              */
#define EMAC_MR0_RXE            0x08000000      /* RX MAC enable              */
#define EMAC_MR0_WKE            0x04000000      /* Wake up enable             */

#define EMAC_MR0_BOTH_IDLE      (EMAC_MR0_RXI | EMAC_MR0_TXI)

/*
 * EMAC Mode Reg 1 bit definitions
 */
#define EMAC_MR1_FDE            0x80000000      /* Full Duplex enable         */
#define EMAC_MR1_ILE            0x40000000      /* Internal loopback          */
#define EMAC_MR1_VLE            0x20000000      /* VLAN enable                */
#define EMAC_MR1_EIFC           0x10000000      /* Enable Int. Flow Control   */
#define EMAC_MR1_APP            0x08000000      /* Allow pause packet         */
#define EMAC_MR1_IST            0x01000000      /* Ignore SQE test            */

#define EMAC_MR1_MF_10MBPS      0x00000000      /* Medium frequency = 10Mbps  */
#define EMAC_MR1_MF_100MBPS     0x00400000      /* Medium frequency = 100Mbps */
#define EMAC_MR1_MF_1GBPS       0x00800000      /* Medium frequency = 1000Mbps*/
#define EMAC_MR1_MF_1GBPS_GPCS  0x00C00000      /* 1000Mbps using GPCS        */
#define EMAC_MR1_RFS_512        0x00000000      /* Receive FIF0 = 512B        */
#define EMAC_MR1_RFS_1K         0x00080000      /* Receive FIF0 = 1KB         */
#define EMAC_MR1_RFS_2K         0x00100000      /* Receive FIF0 = 2KB         */
#define EMAC_MR1_RFS_4K         0x00180000      /* Receive FIF0 = 4KB         */
#define EMAC_MR1_RFS_8K         0x00200000      /* Receive FIF0 = 8KB         */
#define EMAC_MR1_RFS_16K        0x00280000      /* Receive FIF0 = 16KB        */
#define EMAC_MR1_TFS_512        0x00000000      /* Transmit FIFO = 512B       */
#define EMAC_MR1_TFS_1K         0x00010000      /* Transmit FIFO = 1KB        */
#define EMAC_MR1_TFS_2K         0x00020000      /* Transmit FIFO = 2KB        */
#define EMAC_MR1_TFS_4K         0x00030000      /* Transmit FIFO = 4KB        */
#define EMAC_MR1_TFS_8K         0x00040000      /* Transmit FIFO = 8KB        */
#define EMAC_MR1_TFS_16K        0x00050000      /* Transmit FIFO = 16KB       */

/* walnut/ebony only */ 
#define EMAC_MR1_TR0_SINGLE     0x00000000      /* TX 0 single packet mode    */
#define EMAC_MR1_TR0_DEPEND     0x00010000      /* TX 0 multi packet mode     */
#define EMAC_MR1_TR0_MULTI      0x00008000      /* TX 0 dependent mode        */
#define EMAC_MR1_TR1_SINGLE     0x00000000      /* TX 1 single packet mode    */
#define EMAC_MR1_TR1_DEPEND     0x00004000      /* TX 1 multi packet mode     */
#define EMAC_MR1_TR1_MULTI      0x00002000      /* TX 1 dependent mode        */

#define EMAC_MR1_TR             0x00008000     /* Transmit request           */
#define EMAC_MR1_MWSW           0x00007000     /* Max wait status words      */
#define EMAC_MR1_MWSW_VAL       0x00001000     /* Max wait status words val  */
#define EMAC_MR1_JPSM           0x00000800     /* Jumbo packet support mode  */
#define EMAC_MR1_IPPA           0x000007C0     /* Internal PCS PHY address   */
#define EMAC_MR1_IPPA_ENCODE(n) ((((unsigned long)(n))&0x1F)<<6)                
#define EMAC_MR1_OBCI           0x00000038     /* OPB bus clock indication   */
#define EMAC_MR1_OBCI_50MHZ     0x00000000     /* OPB bus clock freq 50MHz    */
#define EMAC_MR1_OBCI_66MHZ     0x00000008     /* OPB bus clock freq 66MHz    */
#define EMAC_MR1_OBCI_83MHZ     0x00000010     /* OPB bus clock freq 83MHz    */
#define EMAC_MR1_OBCI_100MHZ    0x00000018     /* OPB bus clock freq 100MHz   */
#define EMAC_MR1_OBCI_G100MHZ   0x00000020     /* OPB bus clock freq 100MHz   */

/*
 * EMAC Transmit Mode Register 0 bit definitions
 */
#define EMAC_TMR0_GNP0          0x80000000     /* TX 0 get new packet         */
#define EMAC_TMR0_GNP1          0x40000000     /* TX 1 get new packet         */

/* walnut / ebony only */
#define EMAC_TMR0_GNPD          0x20000000     /* TX dependent get new packet */
#define EMAC_TMR0_FC            0x10000000     /* First channel               */

#define EMAC_TMR0_TFAE          0x00000007     /* TX fifo almost empty        */
#define EMAC_TMR0_TFAE_DIS      0x00000007     /* '111'b disables             */

/*
 * EMAC Receive Mode Register bit definitions
 */
#define EMAC_RMR_SP             0x80000000     /* Strip padding               */
#define EMAC_RMR_SFCS           0x40000000     /* Strip FCS                   */
#define EMAC_RMR_RRP            0x20000000     /* RX runt packets             */
#define EMAC_RMR_RFP            0x10000000     /* RX packets with FCS error   */
#define EMAC_RMR_ROP            0x08000000     /* RX oversize packets         */
#define EMAC_RMR_RPIR           0x04000000     /* RX packets w/ inrange error */
#define EMAC_RMR_PPP            0x02000000     /* Propagate pause packets     */
#define EMAC_RMR_PME            0x01000000     /* Promiscuous mode enable     */
#define EMAC_RMR_PMME           0x00800000     /* Promiscuous multicast mode  */
#define EMAC_RMR_IAE            0x00400000     /* Individual address enable   */
#define EMAC_RMR_MIAE           0x00200000     /* Multiple individual address */
#define EMAC_RMR_BAE            0x00100000     /* Broadcast address enable    */
#define EMAC_RMR_MAE            0x00080000     /* Multicast address enable    */
#define EMAC_RMR_RFAF           0x00000007     /* Rx Fifo Almost Full         */
#define EMAC_RMR_RFAF_DIS       0x00000007     /* '111'b disables             */

/*
 * EMAC Interrupt Status & Enable registers bit definitions
 */
/* RX bits */
#define EMAC_ISR_OVR            0x02000000     /* Overrun error               */
#define EMAC_ISR_PP             0x01000000     /* Pause packet received       */
#define EMAC_ISR_BP             0x00800000     /* Bad packet                  */
#define EMAC_ISR_RP             0x00400000     /* Runt packet                 */
#define EMAC_ISR_SE             0x00200000     /* Short event                 */
#define EMAC_ISR_SYE            0x00100000     /* Symbol error                */
#define EMAC_ISR_BFCS           0x00080000     /* Bad FCS                     */
#define EMAC_ISR_PTLE           0x00040000     /* Packet too long             */
#define EMAC_ISR_ORE            0x00020000     /* Out of range error          */
#define EMAC_ISR_IRE            0x00010000     /* In range error              */
/* TX bits */
#define EMAC_ISR_DBDM           0x00000200     /* Dead bit TX dependent mode  */
#define EMAC_ISR_DB0            0x00000100     /* Dead bit TX channel 0       */
#define EMAC_ISR_SE0            0x00000080     /* SQE error TX channel 0      */
#define EMAC_ISR_TE0            0x00000040     /* TX error channel 0          */
#define EMAC_ISR_DB1            0x00000020     /* Dead bit TX channel 1       */
#define EMAC_ISR_SE1            0x00000010     /* SQE error TX channel 1      */
#define EMAC_ISR_TE1            0x00000008     /* TX error channel 1          */
#define EMAC_ISR_MOS            0x00000002     /* MMA operation succeeded     */
#define EMAC_ISR_MOF            0x00000001     /* MMA operation failed        */
#define EMAC_ISR_NO_INTS        0x00000000     /* No interrupts               */

/* The set of bits above we want to cause an Ethernet interrupt for RX error */

#define EMAC_ISR_RX_INTS    0

/* The set of bits above we want to cause an Ethernet interrupt for TX error */

#define EMAC_ISR_TX_INTS    0

/*
 * EMAC MII station management unit (STA Control) register bit definitions
 */
#define EMAC_STACR_OC           0x00008000     /* Operation complete          */
#define EMAC_STACR_PHYE         0x00004000     /* PHY error                   */
#define EMAC_STACR_WRITE        0x00002000     /* STA command WRITE           */
#define EMAC_STACR_READ         0x00001000     /* STA command READ            */

/* Walnut / Ebony only */
#define EMAC_STACR_CLK_50MHZ    0x00000000     /* OPB bus clock freq 50MHz    */
#define EMAC_STACR_CLK_83MHZ    0x00000800     /* OPB bus clock freq 83MHz    */
#define EMAC_STACR_CLK_66MHZ    0x00000400     /* OPB bus clock freq 66MHz    */
#define EMAC_STACR_CLK_100MHZ   0x00000C00     /* OPB bus clock freq 100MHz   */

/*
 * EMAC Transmit Request Threshold Register bit definitions
 */
#define EMAC_TRTR_64            0x00000000
#define EMAC_TRTR_128           0x01000000
#define EMAC_TRTR_192           0x02000000
#define EMAC_TRTR_256           0x03000000
#define EMAC_TRTR_1024          0x0F000000
#define EMAC_TRTR_1536          0x17000000

#if defined(__STDC__) || defined(__cplusplus)
#else
#endif  /* __STDC__ */

#endif  /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCibmEmacEndh */

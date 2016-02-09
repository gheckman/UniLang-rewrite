/* motFcc2End.h - Second Generation Motorola FCC Ethernet network interface.*/

/*
 * Copyright (c) 2003-2009 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01k,02feb09,wap  Complete driver rewrite (legacy maintenance)
01j,19mar05,dlk  Enhancements. Combine buffer descriptor status and length
                 fields.
01j,19aug04,mdo  Clean up unused variables.
01h,23jul04,mdo  Base 6 Enhancements
01g,15jun04,mdo  Fix compiler warning with gnu compiler.
01f,04jun04,mil  Changed cacheArchXXX funcs to cacheXXX funcs.
01e,30mar04,mdo  SPR's 81336, 93209, 94561, 94562 and general cleanup.
01d,12jan04,dat  lint removal
01c,05dec03,rcs  fixed warnings for base6
01b,13aug03,gjc  Fixed SPRs #89689,#89649,#87812,#87749,90135,#86434
01a,16jan03,gjc  SPR#85164 :Second Generation Motorola FCC END header.
*/


#ifndef __INCmotFccEnd2h
#define __INCmotFccEnd2h

#ifdef __cplusplus
extern "C" {
#endif

IMPORT STATUS	sysFccEnetAddrGet (int, UINT8 *);
IMPORT STATUS   sysFccEnetEnable (UINT32, UINT8);
IMPORT STATUS   sysFccEnetDisable (UINT32, UINT8);

#define MOT_FCC_INUM(pDrvCtrl)				\
	(pDrvCtrl)->fccIvec

#define MOT_FCC_IVEC(pDrvCtrl)				\
	INUM_TO_IVEC ((pDrvCtrl)->fccIvec)

#ifndef SYS_FCC_INT_CONNECT
#define SYS_FCC_INT_CONNECT(pDrvCtrl, pFunc, arg, ret)	\
	intConnect ((VOIDFUNCPTR*) MOT_FCC_IVEC (pDrvCtrl), \
		(pFunc), (int) (arg));
#endif /* SYS_FCC_INT_CONNECT */

#ifndef SYS_FCC_INT_DISCONNECT
#define SYS_FCC_INT_DISCONNECT(pDrvCtrl, pFunc, arg, ret)
#endif /* SYS_FCC_INT_DISCONNECT */

#ifndef SYS_FCC_INT_ENABLE
#define SYS_FCC_INT_ENABLE(pDrvCtrl, ret)		\
	intEnable ((int) (MOT_FCC_INUM (pDrvCtrl)));
#endif /* SYS_FCC_INT_ENABLE */

#ifndef SYS_FCC_INT_DISABLE
#define SYS_FCC_INT_DISABLE(pDrvCtrl, ret)		\
    intDisable ((int) (MOT_FCC_INUM (pDrvCtrl)));
#endif /* SYS_FCC_INT_DISABLE */

/*
 * For compatibility with older driver. The FCC_END_FUNCS
 * structure and the old user flags are not used by the
 * new driver.
 */

/*
 * This is the bsp boot information structure for the Mii/Phy, Dpram
 * and misc functions. It contains bsp specific call backs for the driver.
 * A pointer to the structure is passed in the load string.
 */

typedef struct
    {
    FUNCPTR miiPhyInit;       /* bsp MiiPhy init function */
    FUNCPTR miiPhyInt;        /* Driver function for BSP to call */
    FUNCPTR miiPhyBitRead;    /* Bit Read function */
    FUNCPTR miiPhyBitWrite;   /* Bit Write function */
    FUNCPTR miiPhyDuplex;     /* duplex status call back */
    FUNCPTR miiPhySpeed;      /* speed status call back */
    FUNCPTR hbFail;           /* heart beat fail */
    FUNCPTR intDisc;          /* disconnect Function */
    FUNCPTR dpramFree;
    FUNCPTR dpramFccMalloc;
    FUNCPTR dpramFccFree;
    FUNCPTR reserved[4];      /* future use */
    } FCC_END_FUNCS;

/*
 * user flags: full duplex mode, loopback mode, serial interface etc.
 * the user may configure some of this options according to his needs
 * by setting the related bits in the <userFlags> field of the load string.
 */

#define MOT_FCC_USR_PHY_NO_AN   0x00000001  /* do not auto-negotiate */
#define MOT_FCC_USR_PHY_TBL     0x00000002  /* use negotiation table */
#define MOT_FCC_USR_PHY_NO_FD   0x00000004  /* do not use full duplex */
#define MOT_FCC_USR_PHY_NO_100  0x00000008  /* do not use 100Mbit speed */
#define MOT_FCC_USR_PHY_NO_HD   0x00000010  /* do not use half duplex */
#define MOT_FCC_USR_PHY_NO_10   0x00000020  /* do not use 10Mbit speed */
#define MOT_FCC_USR_PHY_MON     0x00000040  /* use PHY Monitor */
#define MOT_FCC_USR_PHY_ISO     0x00000100  /* isolate a PHY */
#define MOT_FCC_USR_RMON        0x00000200  /* enable RMON support */
#define MOT_FCC_USR_LOOP        0x00000400  /* external loopback mode */
                                            /* only use it for testing */
#define MOT_FCC_USR_HBC         0x00000800  /* perform heartbeat control */
#define MOT_FCC_USR_BUF_LBUS    0x00001000  /* buffers are on the local bus */
#define MOT_FCC_USR_BD_LBUS     0x00002000  /* BDs are on the local bus */
#define MOT_FCC_USR_NO_ZCOPY    0x00004000  /* inhibit zcopy mode */

/* required if bufs are on local bus, optional otherwise */
#define MOT_FCC_USR_DPRAM_ALOC  0x00008000  /* Using DPRAM auto allocation */
/* allow snooping of memory operations */
#define MOT_FCC_USR_SNOOP_ENABLE 0x00010000  /* Enable snooping from FCC */

#ifndef BSP_VERSION

#define FCC_CLSIZE      1600
#define FCC_NAME        "motfcc"
#define FCC_TIMEOUT     10000
#define FCC_INTRS       \
        (M8260_FEM_ETH_BSY|M8260_FEM_ETH_RXF|M8260_FEM_ETH_RXC| \
        M8260_FEM_ETH_TXB|M8260_FEM_ETH_TXC|M8260_FEM_ETH_TXE)

#define FCC_RXINTRS (M8260_FEM_ETH_BSY|M8260_FEM_ETH_RXF|M8260_FEM_ETH_RXC)
#define FCC_TXINTRS (M8260_FEM_ETH_TXB|M8260_FEM_ETH_TXC|M8260_FEM_ETH_TXE)

#define FCC_ADJ(x)      m_adj(x, 18)
#define FCC_INC_DESC(x, y)      (x) = (((x) + 1) % y)
#define FCC_MAXFRAG             16
#define FCC_MAX_RX              16

#define FCC_RX_DESC_CNT         32
#define FCC_TX_DESC_CNT         32

#define ETHER_ADDR_LEN		6
#define ETHER_CRC_LEN		4

typedef struct endNetPool
    {
    NET_POOL            pool;
    void                * pMblkMemArea;
    void                * pClMemArea;
    } END_NET_POOL;

#define fccEndPoolTupleFree(x) netMblkClChainFree(x)
#define fccEndPoolTupleGet(x)      \
        netTupleGet((x), (x)->clTbl[0]->clSize, M_DONTWAIT, MT_DATA, 0)

#define FCC_PRAM 0
#define FCC_IRAM 1

#define IFM_ETHER       0x00000020
#define IFM_10_T        3               /* 10BaseT - RJ45 */
#define IFM_10_2        4               /* 10Base2 - Thinnet */
#define IFM_10_5        5               /* 10Base5 - AUI */
#define IFM_100_TX      6               /* 100BaseTX - RJ45 */
#define IFM_100_FX      7               /* 100BaseFX - Fiber */
#define IFM_100_T4      8               /* 100BaseT4 - 4 pair cat 3 */
#define IFM_100_VG      9               /* 100VG-AnyLAN */
#define IFM_100_T2      10              /* 100BaseT2 */
#define IFM_1000_SX     11              /* 1000BaseSX - multi-mode fiber */
#define IFM_10_STP      12              /* 10BaseT over shielded TP */
#define IFM_10_FL       13              /* 10BaseFL - Fiber */
#define IFM_1000_LX     14              /* 1000baseLX - single-mode fiber */
#define IFM_1000_CX     15              /* 1000baseCX - 150ohm STP */
#define IFM_1000_T      16              /* 1000baseT - 4 pair cat 5 */
#define IFM_HPNA_1      17              /* HomePNA 1.0 (1Mb/s) */

/*
 * Shared media sub-types
 */
#define IFM_AUTO        0               /* Autoselect best media */
#define IFM_MANUAL      1               /* Jumper/dipswitch selects media */
#define IFM_NONE        2               /* Deselect all media */

/*
 * Shared options
 */
#define IFM_FDX         0x00100000      /* Force full duplex */
#define IFM_HDX         0x00200000      /* Force half duplex */
#define IFM_FLAG0       0x01000000      /* Driver defined flag */
#define IFM_FLAG1       0x02000000      /* Driver defined flag */
#define IFM_FLAG2       0x04000000      /* Driver defined flag */
#define IFM_LOOP        0x08000000      /* Put hardware in loopback */

/*
 * Masks
 */
#define IFM_NMASK       0x000000e0      /* Network type */
#define IFM_TMASK       0x0000001f      /* Media sub-type */
#define IFM_IMASK       0xf0000000      /* Instance */
#define IFM_ISHIFT      28              /* Instance shift */
#define IFM_OMASK       0x0000ff00      /* Type specific options */
#define IFM_MMASK       0x00070000      /* Mode */
#define IFM_MSHIFT      16              /* Mode shift */
#define IFM_GMASK       0x0ff00000      /* Global options */

/*
 * Status bits
 */
#define IFM_AVALID      0x00000001      /* Active bit valid */
#define IFM_ACTIVE      0x00000002      /* Interface attached to working net */

/*
 * Macros to extract various bits of information from the media word.
 */
#define IFM_TYPE(x)         ((x) & IFM_NMASK)
#define IFM_SUBTYPE(x)      ((x) & IFM_TMASK)
#define IFM_TYPE_OPTIONS(x) ((x) & IFM_OMASK)
#define IFM_INST(x)         (((x) & IFM_IMASK) >> IFM_ISHIFT)
#define IFM_OPTIONS(x)  ((x) & (IFM_OMASK|IFM_GMASK))
#define IFM_MODE(x)         ((x) & IFM_MMASK)

#define IFM_INST_MAX    IFM_INST(IFM_IMASK)

typedef struct _FCC_MEDIA
    {
    UINT32                      endMediaActive;
    UINT32                      endMediaStatus;
    } FCC_MEDIA;

/* number of seconds to wait between link state checks */

#define FCC_LINKPOLL	3

typedef struct fcc_desc
    {
    volatile UINT16     bdSts;
    volatile UINT16     bdLen;
    volatile UINT32     bdAddr;
    } FCC_DESC;

/*
 * Private adapter context structure.
 */

typedef struct fcc_drv_ctrl
    {
    END_OBJ             fccEndObj;
    UINT32		fccImmrVal;
    int			fccUnit;
    void *		fccPram;
    void *		fccIram;
    int			fccIvec;

    volatile BOOL       fccIntPending;

    volatile BOOL       fccRxPending;

    volatile BOOL       fccTxPending;
    UINT8               fccTxCur;
    UINT8               fccTxLast;
    volatile BOOL       fccTxStall;
    UINT16              fccTxThresh;

    BOOL                fccPolling;
    M_BLK_ID            fccPollBuf;
    UINT16              fccIntMask;

    UINT8               fccAddr[ETHER_ADDR_LEN];

    FCC_DESC            *fccRxDescMem;

    FCC_DESC            *fccTxDescMem;

    M_BLK_ID            fccRxMblk[FCC_RX_DESC_CNT];
    M_BLK_ID            fccTxMblk[FCC_TX_DESC_CNT];

    UINT32              fccTxProd;
    UINT32              fccTxCons;
    UINT32              fccTxFree;
    UINT32              fccRxIdx;

    int                 fccNum;
    int			fccPhyAddr;
    END_ERR             fccLastError;

    UINT16		fccMiiSts;
    UINT32              fccCurMedia;
    UINT32              fccCurStatus;
    WDOG_ID		fccMiiWd;

    void *              fccRxDpram;
    void *              fccTxDpram;
    void *              fccPadDpram;

    UINT32		fccMdioClk;
    UINT32		fccMdioData;

    /* Compatibility with old driver. */
    BOOL		intrConnect;
    } FCC_DRV_CTRL;

LOCAL UINT32 csr_read_4
    ( 
    FCC_DRV_CTRL * pDrv,
    UINT32 addr,
    int ix
    )
    {
    UINT32 data;
    if (ix == FCC_PRAM)
        data = *(UINT32 *)((UINT8 *)pDrv->fccPram + addr);
    else
        data = *(UINT32 *)((UINT8 *)pDrv->fccIram + addr);
    return (data);
    }

LOCAL void csr_write_4
    (
    FCC_DRV_CTRL * pDrv,
    UINT32 addr,
    int ix,
    UINT32 data
    )
    {
    UINT32 * reg;

    if (ix == FCC_PRAM)
        reg = (UINT32 *)((UINT8 *)pDrv->fccPram + addr);
    else    
        reg = (UINT32 *)((UINT8 *)pDrv->fccIram + addr);
    *reg = data;
    return;
    }

LOCAL UINT16 csr_read_2
    ( 
    FCC_DRV_CTRL * pDrv,
    UINT16 addr,
    int ix
    )
    {
    UINT16 data;
    if (ix == FCC_PRAM)
        data = *(UINT16 *)((UINT8 *)pDrv->fccPram + addr);
    else
        data = *(UINT16 *)((UINT8 *)pDrv->fccIram + addr);
    return (data);
    }

LOCAL void csr_write_2
    (
    FCC_DRV_CTRL * pDrv,
    UINT16 addr,
    int ix,
    UINT16 data
    )
    {
    UINT16 * reg;

    if (ix == FCC_PRAM)
        reg = (UINT16 *)((UINT8 *)pDrv->fccPram + addr);
    else    
        reg = (UINT16 *)((UINT8 *)pDrv->fccIram + addr);
    *reg = data;
    return;
    }

#ifdef notused
LOCAL UINT8 csr_read_1
    ( 
    FCC_DRV_CTRL * pDrv,
    UINT8 addr,
    int ix
    )
    {
    UINT16 data;
    if (ix == FCC_PRAM)
        data = *(UINT8 *)((UINT8 *)pDrv->fccPram + addr);
    else
        data = *(UINT8 *)((UINT8 *)pDrv->fccIram + addr);
    return (data);
    }
#endif

LOCAL void csr_write_1
    (
    FCC_DRV_CTRL * pDrv,
    UINT8 addr,
    int ix,
    UINT8 data
    )
    {
    UINT8 * reg;

    if (ix == FCC_PRAM)
        reg = (UINT8 *)((UINT8 *)pDrv->fccPram + addr);
    else    
        reg = (UINT8 *)((UINT8 *)pDrv->fccIram + addr);
    *reg = data;
    return;
    }

#define CSR_READ_4 csr_read_4
#define CSR_READ_2 csr_read_2
#define CSR_READ_1 csr_read_1
#define CSR_WRITE_4 csr_write_4
#define CSR_WRITE_2 csr_write_2
#define CSR_WRITE_1 csr_write_1

#define CSR_SETBIT_1(pDev, offset, ix, val)          \
        CSR_WRITE_1(pDev, offset, ix, CSR_READ_1(pDev, offset, ix) | (val))

#define CSR_CLRBIT_1(pDev, offset, ix, val)          \
        CSR_WRITE_1(pDev, offset, CSR_READ_1(pDev, offset, ix) & ~(val))

#define CSR_SETBIT_2(pDev, offset, ix, val)          \
        CSR_WRITE_2(pDev, offset, ix, CSR_READ_2(pDev, offset, ix) | (val))

#define CSR_CLRBIT_2(pDev, offset, ix, val)          \
        CSR_WRITE_2(pDev, offset, ix, CSR_READ_2(pDev, offset, ix) & ~(val))

#define CSR_SETBIT_4(pDev, offset, ix, val)          \
        CSR_WRITE_4(pDev, offset, ix, CSR_READ_4(pDev, offset, ix) | (val))

#define CSR_CLRBIT_4(pDev, offset, ix, val)          \
        CSR_WRITE_4(pDev, offset, ix, CSR_READ_4(pDev, offset, ix) & ~(val))

/* Most boards use port C, pins 9/10 for MDIO. */

#define FCC_PC10    (0x00200000)
#define FCC_PC9     (0x00400000)

/* The ADS8272 uses port C, pins 18/19 */

#define FCC_PC19    (0x00001000)
#define FCC_PC18    (0x00002000)

#define MII_CLK_DIR_OUT *M8260_IOP_PCDIR(pDrvCtrl->fccImmrVal) |= (pDrvCtrl->fccMdioClk)
#define MII_CLK_DIR_IN *M8260_IOP_PCDIR(pDrvCtrl->fccImmrVal) &= ~(pDrvCtrl->fccMdioClk)

#define MII_CLK_HIGH *M8260_IOP_PCDAT(pDrvCtrl->fccImmrVal) |= (pDrvCtrl->fccMdioClk)
#define MII_CLK_LOW *M8260_IOP_PCDAT(pDrvCtrl->fccImmrVal) &= ~(pDrvCtrl->fccMdioClk)

#define MII_DATA_DIR_OUT *M8260_IOP_PCDIR(pDrvCtrl->fccImmrVal) |= (pDrvCtrl->fccMdioData)
#define MII_DATA_DIR_IN *M8260_IOP_PCDIR(pDrvCtrl->fccImmrVal) &= ~(pDrvCtrl->fccMdioData)

#define MII_DATA_HIGH *M8260_IOP_PCDAT(pDrvCtrl->fccImmrVal) |= (pDrvCtrl->fccMdioData)
#define MII_DATA_LOW *M8260_IOP_PCDAT(pDrvCtrl->fccImmrVal) &= ~(pDrvCtrl->fccMdioData)
#define MII_DATA_GET *M8260_IOP_PCDAT(pDrvCtrl->fccImmrVal) & (pDrvCtrl->fccMdioData)

#define IDR2_OUILSB     0xfc00  /* OUI LSB */
#define IDR2_MODEL      0x03f0  /* vendor model */
#define IDR2_REV        0x000f  /* vendor revision */

#define MII_OUI(id1, id2)       (((id1) << 6) | ((id2) >> 10))
#define MII_MODEL(id2)          (((id2) & IDR2_MODEL) >> 4)
#define MII_REV(id2)            ((id2) & IDR2_REV)

#define MII_OUI_8260ATM         0x0004de
#define MII_MODEL_8260ATM       0x000e

#define LXT_CR          16

#define LXT_CR_FORCELNK         0x4000  /* force link pass */
#define LXT_CR_TXDIS            0x2000  /* disable transmit */
#define LXT_CR_SCRAM            0x1000  /* bypass scrambler/descrambler */
#define LXT_CR_JABDIS           0x0400  /* disable jabber detection */
#define LXT_CR_SQE              0x0200  /* enable heartbeat */
#define LXT_CR_TPLOOPDIS        0x0100  /* disable loopback in half-duplex */
#define LXT_CR_CRS              0x0080  /* CRS select */
#define LXT_CR_PREAMBLE         0x0020  /* preamble enable */
#define LXT_CR_ALTNP            0x0002  /* alternate next-page feature */

#define MII_OUI_BROADCOM        0x001018        /* Broadcom Corporation */
#define MII_MODEL_BROADCOM_BCM5221      0x001e

/* Auxiliary control/status register */

#define BMT_ACSR        24

#define BMT_ACSR_JABBER_DIS     0x8000  /* jabber disable */
#define BMT_ACSR_FLINK          0x4000  /* force 10baseT link pass */
#define BMT_ACSR_TXPWR          0x0100  /* 10Mbps tx power: 0 = low, 1 = hi */
#define BMT_ACSR_HSQ            0x0080  /* SQ high */
#define BMT_ACSR_LSQ            0x0040  /* SQ low */
#define BMT_ACSR_ER1            0x0020  /* edge rate 1 */
#define BMT_ACSR_ER0            0x0010  /* edge rate 0 */
#define BMT_ACSR_ANEG           0x0008  /* auto-negotiation activated */
#define BMT_ACSR_F100           0x0004  /* force 100base */
#define BMT_ACSR_SPEED          0x0002  /* 1 = 100, 0 = 10 */
#define BMT_ACSR_FDX            0x0001  /* full-duplex */

#define MII_OUI_DAVICOM 0x00606e        /* Davicom Semiconductor */
#define MII_MODEL_DAVICOM_DM9161        0x0008
#define MII_MODEL_DAVICOM_DM9161A       0x000a

/* Specified configuration register */

#define DAVICOM_SCR     16

#define DAVICOM_SCR_BP_4B5B     0x8000  /* bypass 4B5B encoding/decoding */
#define DAVICOM_SCR_BP_SCRAM    0x4000  /* bypass scrambler/descrambler */
#define DAVICOM_SCR_BP_ALIGN    0x2000  /* bypass symbol alignment */
#define DAVICOM_SCR_BP_ADPOK    0x1000  /* bypass ADPOK */
#define DAVICOM_SCR_REPEATER    0x0800  /* repeater mode enable */
#define DAVICOM_SCR_TX          0x0400  /* 1 = 100baseTX, 0 = 100baseFX */
#define DAVICOM_SCR_FEF         0x0200  /* far end fault enable */
#define DAVICOM_SCR_RMII        0x0100  /* reduced MII enable */
#define DAVICOM_SCR_FORCE100    0x0080  /* force good 100Mbps link */
#define DAVICOM_SCR_SPDLED      0x0040  /* speed LED enable */
#define DAVICOM_SCR_COLLED      0x0020  /* collision LED enable */
#define DAVICOM_SCR_RPWREN      0x0010  /* reduced power down enable */
#define DAVICOM_SCR_SMRST       0x0008  /* reset state machine */
#define DAVICOM_SCR_MFPSC       0x0004  /* management preamble suppression */
#define DAVICOM_SCR_SLEEP       0x0002  /* sleep mode */
#define DAVICOM_SCR_RLOUT       0x0001  /* remote loopout control */

/* 10baseT config/status register */

#define DAVICOM_10BTCSR 18

#define DAVICOM_10BTCSR_LPEN    0x4000  /* enable link pulse transmission */
#define DAVICOM_10BTCSR_HBE     0x2000  /* heartbeat enable */
#define DAVICOM_10BTCSR_SQUELCH 0x1000  /* squelch enable */
#define DAVICOM_10BTCSR_JABEN   0x0800  /* jabber detect enable */
#define DAVICOM_10BTCSR_10BTSER 0x0400  /* 0 = 10BT MII, 1 == 10BT GPSI */
#define DAVICOM_10BTCSR_POLR    0x0001  /* polarity reversal indicator */

#endif /* BSP_VERSION */

#ifdef __cplusplus
}
#endif

#endif /* __INCfccVxbEndh */

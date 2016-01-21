/* amd8111LanEnd.h - END style AMD 8111 LAN PCI Ethernet driver header */

/*
 * Copyright (c) 1998-2005, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01c,29apr10,pad  Moved extern C statement after include statements.
01b,01sep05,gtf modified for AMD8111 LAN END driver.
01a,07dec98,snk	added support 7997x[012] across architectures.
		written from 01b of lnPciEnd.h
*/

#ifndef __INCamd8111LanEndh
#define __INCamd8111LanEndh

#ifndef _ASMLANGUAGE

#include <end.h>
#include <cacheLib.h>
#include <netinet/if_ether.h>

#ifdef __cplusplus
extern "C" {
#endif


/* board level/bus specific and architecture specific macros */

#if (CPU_FAMILY == PPC)

#ifndef AMD_LONG_WR
#define AMD_LONG_WR(addr, value) (sysOutLong ((ULONG) addr, (ULONG) value))
#endif

#ifndef AMD_WORD_WR
#define AMD_WORD_WR(addr, value) (sysOutWord ((ULONG) addr, (USHORT) value))
#endif

#ifndef AMD_BYTE_WR
#define AMD_BYTE_WR(addr, value) (sysOutByte ((ULONG) addr, (UCHAR) value))
#endif

#ifndef AMD_LONG_RD
#define AMD_LONG_RD(addr, value) (value = sysInLong ((ULONG) addr))
#endif

#ifndef AMD_WORD_RD
#define AMD_WORD_RD(addr, value) (value = sysInWord ((ULONG) addr))
#endif

#ifndef AMD_BYTE_RD
#define AMD_BYTE_RD(addr, value) (value = sysInByte ((ULONG) addr))
#endif

#endif /* CPU_FAMILY == PPC */

#ifndef AMD_LONG_WR
#define AMD_LONG_WR(addr, value)                                        \
    (* (volatile UINT32 *) (addr) = ((UINT32) AMD_SWAP_LONG (value) ))
#endif /* FEI_LONG_WR */

#ifndef AMD_WORD_WR
#define AMD_WORD_WR(addr, value)                                        \
    (* (volatile UINT16 *) (addr) = ((UINT16) AMD_SWAP_WORD (value) ))
#endif /* FEI_WORD_WR */

#ifndef AMD_BYTE_WR
#define AMD_BYTE_WR(addr, value)                                        \
    (* (volatile UINT8 *) (addr) = (UINT8) (value) )
#endif /* FEI_BYTE_WR */

#ifndef AMD_LONG_RD
#define AMD_LONG_RD(addr, value)                                        \
    do  {								\
	UINT32 _temp_ = *(volatile UINT32 *)(addr);			\
	(value) = (UINT32) AMD_SWAP_LONG (_temp_);			\
	} while (0)
#endif /* FEI_LONG_RD */

#ifndef AMD_WORD_RD
#define AMD_WORD_RD(addr, value)                                        \
    do  {								\
	UINT16 _temp_ = *(volatile UINT16 *)(addr);			\
	(value) = (UINT16) AMD_SWAP_WORD (_temp_);			\
	} while (0)
#endif /* FEI_WORD_RD */

#ifndef AMD_BYTE_RD
#define AMD_BYTE_RD(addr, value)                                        \
    do  {								\
	(value) = (UINT8) (*(volatile UINT8 *)(addr));			\
	} while (0)
#endif /* FEI_BYTE_RD */

#if _BYTE_ORDER==_BIG_ENDIAN
# define PCI_SWAP(x) ((amd8111LanBusEndianess) ? (int)(x) : LONGSWAP((int)(x)))
#else
# define PCI_SWAP(x) (x)
#endif

/* 32-bits */

#define CHIPID                      (0x004)
#define AUTO_POLL_VAL               (0x098)

/* 16-bites */

#define AP0                         (0x088)

#define AP0_PHY0_ADDR_MASK          0x001f

#define AP1                         (0x08a)

#define AP1_REG1_EN                 0x8000
#define AP1_REG1_ADDR_MASK          0x1f00
#define AP1_PRE_SUP1                0x0040
#define AP1_PHY1_DFLT               0x0020
#define AP1_PHY1_ADDR_MASK          0x001f

#define AP2                         (0x08c)
#define AP3                         (0x08e)
#define AP4                         (0x090)
#define AP5                         (0x092)

/* 32-bits */

#define BADR                        (0x120)
#define BADX0                       (0x100)
#define BADX1                       (0x108)
#define BADX2                       (0x110)
#define BADX3                       (0x118)

#define CMD0                        (0x048)

#define CMD0_RDMD0                  0x00010000
#define CMD0_TDMD3                  0x00000800
#define CMD0_TDMD2                  0x00000400
#define CMD0_TDMD1                  0x00000200
#define CMD0_TDMD0                  0x00000100
#define CMD0_UINTCMD                0x00000040
#define CMD0_RX_FAST_SPND           0x00000020
#define CMD0_TX_FAST_SPND           0x00000010
#define CMD0_RX_SPND                0x00000008
#define CMD0_TX_SPND                0x00000004
#define CMD0_INTREN                 0x00000002
#define CMD0_RUN                    0x00000001

#define CMD2                        (0x050)

#define CMD2_CONDUIT_MODE           0x20000000
#define CMD2_RPA                    0x00100000
#define CMD2_DRCVPA                 0x00080000
#define CMD2_DRCVBC                 0x00040000
#define CMD2_PROM                   0x00020000
#define CMD2_ASTRIP_RCV             0x00002000
#define CMD2_RCV_DROP0              0x00001000
#define CMD2_EMBA                   0x00000800
#define CMD2_DXMT2PD                0x00000400
#define CMD2_LTINTEN                0x00000200
#define CMD2_DXMTFCS                0x00000100
#define CMD2_APAD_XMT               0x00000040
#define CMD2_DRTY                   0x00000020
#define CMD2_INLOOP                 0x00000010
#define CMD2_EXLOOP                 0x00000008
#define CMD2_REXUFLO                0x00000002

#define CMD3                        (0x054)

#define CMD3_JUMBO                  0x00400000
#define CMD3_VSIZE                  0x00200000
#define CMD3_VLONLY                 0x00100000
#define CMD3_VL_TAG_DEL             0x00080000
#define CMD3_EN_PMGR                0x00004000
#define CMD3_FORCE_FULL_DUPLEX      0x00001000
#define CMD3_FORCE_LINK_STATUS      0x00000800
#define CMD3_APEP                   0x00000400
#define CMD3_MPPLBA                 0x00000200
#define CMD3_BKPRS_EN               0x00000100
#define CMD3_RESET_PHY_PULSE        0x00000004
#define CMD3_RESET_PHY              0x00000002
#define CMD3_PHY_RST_POL            0x00000001

#define CMD7                        (0x064)

#define CMD7_PMAT_SAVE_MATCH        0x00000010
#define CMD7_PMAT_MODE              0x00000008
#define CMD7_MPEN_SW                0x00000002
#define CMD7_LCMODE_SW              0x00000001

#define CTRL1                       (0x06c)

#define CTRL1_RESET_PHY_WIDTH_MASK  0x001f0000
#define CTRL1_XMTSP_MASK            0x00000300
#define CTRL1_CACHE_ALIGN           0x00000010
#define CTRL1_BURST_LIMIT_MASK      0x0000000f

#define CTRL2                       (0x070)

#define CTRL2_FMDC_MASK             0x00000300
#define CTRL2_XPHYRST               0x00000080
#define CTRL2_XPHYANE               0x00000040
#define CTRL2_XPHYFD                0x00000020
#define CTRL2_XPHYSP_MASK           0x00000018
#define CTRL2_APDW_MASK             0x00000007

#define DLY_INT_A                   (0x0a8)
#define DLY_INT_B                   (0x0ac)

#define FLOW                        (0x0c8)

/* 8-bits */
#define IPG                         (0x18d)
#define IFS1                        (0x18c)

/* 32-bits */

#define INT0                        (0x038)

#define INT0_INTR                   0x80000000
#define INT0_INTPN                  0x40000000
#define INT0_LCINT                  0x08000000
#define INT0_APINT5                 0x04000000
#define INT0_APINT4                 0x02000000
#define INT0_APINT3                 0x01000000
#define INT0_APINT2                 0x00800000
#define INT0_APINT1                 0x00400000
#define INT0_APINT0                 0x00200000
#define INT0_MIIPDINT               0x00100000
#define INT0_MCCINT                 0x00020000
#define INT0_MREINT                 0x00010000
#define INT0_SPNDINT                0x00004000
#define INT0_MPINT                  0x00002000
#define INT0_TINT3                  0x00000800
#define INT0_TINT2                  0x00000400
#define INT0_TINT1                  0x00000200
#define INT0_TINT0                  0x00000100
#define INT0_UINT                   0x00000080
#define INT0_STINT                  0x00000010
#define INT0_RINT0                  0x00000001

#define INTEN0                      (0x040)

#define INTEN0_LCINTEN              0x08000000
#define INTEN0_APINT5EN             0x04000000
#define INTEN0_APINT4EN             0x02000000
#define INTEN0_APINT3EN             0x01000000
#define INTEN0_APINT2EN             0x00400000
#define INTEN0_APINT1EN             0x00200000
#define INTEN0_APINT0EN             0x00100000
#define INTEN0_MIIPDINTEN           0x00080000
#define INTEN0_MCCINTEN             0x00020000
#define INTEN0_MREINTEN             0x00010000
#define INTEN0_SPNDINTEN            0x00004000
#define INTEN0_MPNINTEN             0x00002000
#define INTEN0_TINTEN3              0x00000800
#define INTEN0_TINTEN2              0x00000400
#define INTEN0_TINTEN1              0x00000200
#define INTEN0_TINTEN0              0x00000100
#define INTEN0_STINTEN              0x00000010
#define INTEN0_RINTEN0              0x00000001

/* 64-bits */

#define LADRF_L                     (0x168)
#define LADRF_H                     (0x16c)

/* 16-bits */

#define MIB_ADRS                    (0x014)

#define MIB_CMD_ACTIVE              0x8000
#define MIB_RD_CMD                  0x2000
#define MIB_CLEAR                   0x1000
#define MIB_ADDRESS_MASK            0x001f

/* 32-bits */

#define MIB_DATA                    (0x010)

/* 48-bits */

#define MAC_ADRS                    (0x160)

/* 32-bits */

#define PHY_ACCESS                  (0x0d0)

/* 32-bits */

#define ON_NOW_PTRN0                (0x190)
#define ON_NOW_PTRN1                (0x194)

/* 16-bits */

#define RCV_RING_LEN                (0x150)

/* 16-bits */

#define SRAM_BND                    (0x17a)
#define SRAM_BND_DEFAULT            0x08
#define SRAM_SIZE                   (0x178)
#define SRAM_SIZE_DEFAULT           0x10

/* 32-bits */

#define STAT0                       (0x030)

#define STAT0_PMAT_DET              0x00010000
#define STAT0_MP_DET                0x00008000
#define STAT0_LC_DET                0x00004000
#define STAT0_SPEED_MASK            0x00000380
#define STAT0_FULL_DUPLEX           0x00000040
#define STAT0_LINK_STATUS           0x00000020
#define STAT0_AUTONEG_COMPLETE      0x00000010
#define STAT0_MIIPD                 0x00000008
#define STAT0_RX_SUSPENDED          0x00000004
#define STAT0_TX_SUSPENDED          0x00000002
#define STAT0_RUNNING               0x00000001

/* 16-bits */

#define STVAL                       (0x0d8)

/* 16-bits */

#define XMT_RING0_LEN               (0x140)
#define XMT_RING1_LEN               (0x144)
#define XMT_RING2_LEN               (0x148)
#define XMT_RING3_LEN               (0x14c)

/* 32-bits */

#define XMT_RING_LIMIT              (0x07c)

/* Bit Fields */

typedef struct rxDesc
    {
    UINT32      RD[4] ;
    } AMD_RD ;

typedef struct txDesc
    {
    UINT32      TD[4] ;
    } AMD_TD ;

#define RD_USER_SPACE 0
#define RD_WORD1      1
#define RD_MCNT       1
#define RD_WORD2      2
#define RD_BCNT       2
#define RD_FLAGS      2
#define RD_RBADR      3

/* Word 0x8 */

#define RD_OWN        0x80000000
#define RD_ERR        0x40000000
#define RD_FRAM       0x20000000
#define RD_OFLO       0x10000000
#define RD_CRC        0x08000000
#define RD_BUFF       0x04000000
#define RD_STP        0x02000000
#define RD_ENP        0x01000000
#define RD_PAM        0x00400000
#define RD_LAFM       0x00200000
#define RD_BAM        0x00100000
#define RD_TT_MASK    0x000c0000
#define RD_BCNT_MASK  0x0000ffff

#define TD_WORD0      0
#define TD_BCNT       0
#define TD_FLAGS      0
#define TD_WORD1      1
#define TD_TCC        1
#define TD_TCI        1
#define TD_TBADR      2
#define TD_USER_SPACE 3

/* Word 0x0 */

#define TD_OWN        0x80000000
#define TD_ADD_FCS    0x20000000
#define TD_LTINT      0x10000000
#define TD_PRI_LOCK   0x04000000
#define TD_STP        0x02000000
#define TD_ENP        0x01000000
#define TD_KILL       0x00400000
#define TD_BCNT_MASK  0x0000ffff

/* Word 0x4 */

#define TD_TCC_MASK   0x00030000
#define TD_TCI_MASK   0x0000ffff

/* Control block definitions for AMD PCnet (Ethernet) chip. */

typedef union addrFilter        /* logical address filter layout */
    {
    UINT8  lafBytes  [8];       /* (8) bytes */
    UINT16 lafWords  [4];       /* (4) 16-bit words */
    UINT32 lafDwords [2];       /* (2) 32-bit dwords */
    } ADDR_FILTER;

typedef enum filterModCmd       /* addrFilterMod() commands */
    {
    AMD_LADRF_ADD,               /* add a logical address */
    AMD_LADRF_DEL,               /* delete a logical address */
    AMD_LADRF_ADD_ALL,           /* add all logical addresses */
    AMD_LADRF_DEL_ALL            /* delete all logical addresses */
    } FILTER_MOD_CMD;

/* CRC for logical address filter */

#define AMD_CRC_POLYNOMIAL      (0xedb88320)    /* Ethernet CRC polynomial */
#define AMD_CRC_TO_LAF_IX(crc)  ((crc) >> 26)   /* get 6 MSBits */
#define AMD_LAF_LEN             (8)             /* logical addr filter length */
#define AMD_LA_LEN              (6)             /* logical address length */
#define BITS_PER_LA             (8 * AMD_LA_LEN) /* logical addr length bits */


/* Definitions for the drvCtrl specific flags field */

#define LS_PROMISCUOUS_FLAG     0x1     /* set the promiscuous mode */
#define LS_MEM_ALLOC_FLAG       0x2     /* allocating memory flag */
#define LS_PAD_USED_FLAG        0x4     /* padding used flag */
#define LS_RCV_HANDLING_FLAG    0x8     /* handling recv packet */
#define LS_START_OUTPUT_FLAG    0x10    /* trigger output flag */
#define LS_POLLING              0x20    /* polling flag */
#define LS_MODE_MEM_IO_MAP      0x100   /* device registers memory mapped */
#define LS_MODE_DWIO            0x200   /* device in 32 bit mode */
#define LS_MODE_NOSWAP_MASTER	0x400   /* don't swap PCI master I/O ops */

/* descriptor size */

#define RD_SIZ                 sizeof(AMD_RD)
#define TD_SIZ                 sizeof(AMD_TD)

/* How much work we're allowed to do in the RX handler (# of pkts processed) */

#define AMD_RX_LIMIT  32

/* How many descriptors we want to use up in a single gather-write transmit */

#define AMD_MAX_FRAGS 32


/* */

typedef struct amd8111LanBoardInfoType
{
    UINT32 vector;               /* interrupt vector number */
    UINT32 baseAddr;             /* memory base address for CSR */
    UINT32 pciMemAddr ;          /* PCI memory base address from CPU */
    UCHAR  enetAddr[6];          /* ethernet address */
    int (*intEnable)(int unit);  /* board specific interrupt enable routine */
    int (*intDisable)(int unit); /* board specific interrupt disable routine */
    int (*intAck) (int unit);    /* interrupt ack */
    STATUS (*intConnect) (VOIDFUNCPTR * vector, VOIDFUNCPTR routine, int parameter);
    STATUS (*intDisconnect) (VOIDFUNCPTR * vector, VOIDFUNCPTR routine, int parameter);
    UINT32 (*sysLocalToBus)(int unit,UINT32 localAdr);
    UINT32 (*sysBusToLocal)(int unit,UINT32 sysAdr);

    /* configuration parameters, user can override in the BSP */
    UINT8 phyAddr;  /* PHY device address, valid addresses: 0-32 */
    UINT8 phySpeed;
    UINT8 phyDpx;
    UINT8 fill0;
} AMD8111_LAN_BOARD_INFO ;

/* The definition of the driver control structure */

typedef struct amd8111LanDevice
    {
    END_OBJ           endObj;            /* The class we inherit from */

    int               unit;              /* unit number of the device */

    int               rdNum ;            /* total number of RDs */
    int               rdIndex;           /* current RD send index */
    int               rringSize;         /* RD ring size */
    int               rringLen;          /* RD ring length (bytes) */
    volatile AMD_RD * pRring;            /* RD ring start */

    int               tdNum ;            /* total number of TDs */
    int               tdIndex;           /* current TD transmit index */
    int               tdIndexC;          /* current TD cleaning index */
    int               tringSize;         /* TD ring size */
    int               tringLen;          /* TD ring length (bytes) */
    volatile AMD_TD * pTring;            /* TD ring start */

    int               inum;              /* interrupt number */
    int               ilevel;            /* interrupt level */

    volatile char *   pShMem;            /* real ptr to shared memory */
    volatile char *   pShMemEnd;	 /* real ptr to shared memory end */
    volatile char *   memBase;           /* PCnet memory pool base */
    volatile char *   memAdrs;           /* PCnet memory pool base */

    UINT32	      shMemPtoVOffset;	 /* bias to convert pShMem P->V */

    UINT32            devAdrs;           /* device structure address */

    UINT32            chipId;            /* (csr88|csr89) chip ID value */
    int               memSize;           /* PCnet memory pool size */
    int               memWidth;          /* width of data port */
    int               offset;            /* offset of data in the buffer */
    volatile UINT32   flags;             /* Our local flags */
    UINT32            pciMemBase;        /* memory base as seen from PCI*/
    UINT8             enetAddr[6];       /* ethernet address */
    CACHE_FUNCS       cacheFuncs;        /* cache function pointers */

    volatile BOOL     txBlocked;         /* transmit flow control */
    volatile BOOL     txCleaning;        /* transmit descriptor cleaning */

    CL_POOL_ID        pClPoolId;         /* cluster pool Id */
    M_CL_CONFIG       mClCfg;            /* mBlk & cluster config structure */
    CL_DESC           clDesc;            /* cluster descriptor table */

    END_ERR           lastError;         /* Last error passed to muxError */
    volatile BOOL     errorHandling;     /* task level error handling */

    M_BLK_ID *        mBlks;             /* saved mBlk pointers */

    AMD8111_LAN_BOARD_INFO board ;

    /* Hold current values of these registers */

    UINT32            cmd0 ;
    UINT32            cmd2 ;
    UINT32            cmd3 ;
    UINT32            cmd7 ;
    UINT32            inten0 ;

    } AMD8111_LAN_DRV_CTRL;

/*
 * MIB statistics.  The variable positions correspond the the index position
 * required to access the given value.  For example, rxvMissPkts is index 0,
 * rcvOctets is index 1 and so on.
 */

typedef struct amd8111LanStatCounterType {
    UINT32      rcvMissPkts ;           /* 0x0 */
    UINT32      rcvOctets ;
    UINT32      rcvBroadCastPkts ;
    UINT32      rcvMultiCastPkts ;
    UINT32      rcvUndersizePkts ;
    UINT32      rcvOversizePkts ;
    UINT32      rcvFragments ;
    UINT32      rcvJabbers ;
    UINT32      rcvUnicastPkts ;
    UINT32      rcvAlignmentErrors  ;
    UINT32      rcvFCSErrors ;
    UINT32      rcvGoodOctets ;
    UINT32      rcvMACCtrl ;
    UINT32      rcvFlowCtrl ;
    UINT32      rcvPkts64Octets ;
    UINT32      rcvPkts65to127Octets ;
    UINT32      rcvPkts128to255ctets ;  /* 0x10 */
    UINT32      rcvPkts256to511ctets ;
    UINT32      rcvPkts512to1023ctets ;
    UINT32      rcvPkts1024to1518ctets ;
    UINT32      rcvUnsupportedOpcode ;
    UINT32      rcvSymbolErrors ;
    UINT32      rcvDropPktsRing0 ;
    UINT32      reserved0[3] ;
    UINT32      rcvJumboPkts ;
    UINT32      reserved1[5] ;
    UINT32      xmtUnderrunPkts ;       /* 0x20 */
    UINT32      xmtOctets ;
    UINT32      xmtPackets ;
    UINT32      xmtBroadCastPkts ;
    UINT32      xmtMultiCastPkts ;
    UINT32      xmtCollisions ;
    UINT32      xmtUnicastPkts ;
    UINT32      xmtOneCollision ;
    UINT32      xmtMultipleCollision ;
    UINT32      xmtDeferredTransmit ;
    UINT32      xmtLateCollision ;
    UINT32      xmtExcessiveDefer ;
    UINT32      xmtLossCarrier ;
    UINT32      xmtExcessiveCollision ;
    UINT32      xmtBackPressure ;
    UINT32      xmtFlowCtrl ;
    UINT32      xmtPkts64Octets ;       /* 0x30 */
    UINT32      xmtPkts65to127Octets ;
    UINT32      xmtPkts128to255Octets ;
    UINT32      xmtPkts256to511Octets ;
    UINT32      xmtPkts512to1023Octets ;
    UINT32      xmtPkts1024to1518Octets ;
    UINT32      xmtOversizePkts ;
    UINT32      xmtJumboPkts ;          /* 0x37 */

} AMD8111_LAN_STAT_COUNTER ;

/* Configuration items */

#define AMD_MIN_FBUF            (100)     /* Min sizeof first buffer in chain */

#define AMD_BUFSIZ              (ETHERMTU + SIZEOF_ETHERHEADER + 6)

#define AMD_SPEED               (10000000)

#define AMD_RD_RLEN             (7)       /* ring size as a ^ 2 => 128 RD's */
#define AMD_TD_TLEN             (7)       /* ring size as a ^ 2 => 128 TD's */

#define AMD_RD_MIN              (2)       /* min descriptors 4 */
#define AMD_TD_MIN              (2)       /* min descriptors 4 */

#define AMD_RD_MAX              (9)       /* max descriptors 512 */
#define AMD_TD_MAX              (9)       /* max descriptors 512 */

#define AMD8111_LAN_DEV_NAME    "amdPci"  /* name of the device */
#define AMD8111_LAN_DEV_NAME_LEN (7)      /* length of the name string */
#define AMD8111_LAN_APROM_SIZE  (32)      /* hardware Address PROM size bytes */

#define AMD_LITTLE_ENDIAN        (0)       /* little endian PCI bus      */
#define AMD_BIG_ENDIAN           (1)       /* big endian PCI bus         */
#define AMD_ACTIVE_LOW           (0)       /* active-low interrupt line  */
#define AMD_ACTIVE_HI            (1)       /* active-high interrupt line */

#define AMD_RD_OWNED(rd)       ( PCI_SWAP ((rd)->RD [RD_FLAGS]) & RD_OWN )
#define AMD_TD_OWNED(td)       ( PCI_SWAP ((td)->TD [TD_FLAGS]) & TD_OWN )

#define AMD_PKT_LEN_GET(rd)    ( PCI_SWAP ((rd)->RD [RD_MCNT]) & RD_BCNT_MASK )

#if defined(__STDC__) || defined(__cplusplus)

IMPORT STATUS    amd8111LanInitParse (AMD8111_LAN_DRV_CTRL * pDrvCtrl, char * initString);
IMPORT END_OBJ * amd8111LanEndLoad (char * initString);

#else

IMPORT STATUS    amd8111LanInitParse ();
IMPORT END_OBJ * amd8111LanEndLoad ();

#endif  /* __STDC__ */

#endif  /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCamd8111LanEndh */

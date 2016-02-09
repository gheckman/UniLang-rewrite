/* motTsecEnd.h - Motorola TSEC Ethernet network interface.*/

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
01r,05feb09,wap  Complete driver rewrite (legacy maintenance)
01q,22mar07,dlk  Remove references to netJobInfo.
01p,06mar06,dlk  Initialize the RXIC register.
01o,26jun05,dlk  Replace netJobAdd() with jobQueuePost().
01j,24mar05,dtr  Changes from code review.
01i,31jan05,dtr  Decouple from interrupt controller.
01h,23nov04,rcs  Fixed SPR 104568 - fails large pings when attached to a
                 gigabit switch 
01g,22oct04,dtr  Added Interrupt coalescing defines. Changed some defaults 
                 for increased performance.SPR 102536
01f,22jul04,rcs  Added PHY Access definitions
01e,21jun04,mil  Changed cacheArchXXX funcs to cacheXXX funcs.
01d,27apr04,mdo  Latest updates for B6 build
01c,13apr04,mil  Fixed location of header file.
01c,26mar04,rcs  Fixed SPR 95432
01b,12feb04,rcs  Adjusted default settings
01b,04feb04,mil  Fixed problem if compiled with GNU.
01a,10mar03,gjc  Motorola TSEC Ethernet.
*/


#ifndef __INCmotTsecEndh
#define __INCmotTsecEndh

#ifdef __cplusplus
extern "C" {
#endif

#ifndef BSP_VERSION

#define TSEC_IEVENT                         0x010
#define TSEC_IMASK                          0x014
#define TSEC_EDIS                           0x018
#define TSEC_ECNTRL                         0x020
#define TSEC_MINFLR                         0x024
#define TSEC_PTV                            0x028
#define TSEC_DMACTRL                        0x02C
#define TSEC_TBIPA                          0x030
#define TSEC_FIFO_PAUSE_CTRL                0x04C
#define TSEC_FIFO_TX_THR                    0x08C
#define TSEC_FIFO_STRV                      0x098
#define TSEC_FIFO_STRV_SHUT                 0x09C
#define TSEC_TCTRL                          0x100
#define TSEC_TSTAT                          0x104
#define TSEC_TBDLEN                         0x10C
#define TSEC_TXIC                           0x110
#define TSEC_CTBPTR                         0x124
#define TSEC_TBPTR                          0x184
#define TSEC_TBASE                          0x204
#define TSEC_OSTBD                          0x2b0
#define TSEC_OSTBDP                         0x2b4
#define TSEC_RCTRL                          0x300
#define TSEC_RSTAT                          0x304
#define TSEC_RBDLEN                         0x30C
#define TSEC_RXIC                           0x310
#define TSEC_CRBPTR                         0x324
#define TSEC_MRBLR                          0x340
#define TSEC_RBPTR                          0x384
#define TSEC_RBASE                          0x404
#define TSEC_MACCFG1                        0x500
#define TSEC_MACCFG2                        0x504
#define TSEC_IPGIFG                         0x508
#define TSEC_HAFDUP                         0x50C
#define TSEC_MAXFRM                         0x510
#define TSEC_MIIMCFG                        0x520
#define TSEC_MIIMCOM                        0x524
#define TSEC_MIIMADD                        0x528
#define TSEC_MIIMCON                        0x52C
#define TSEC_MIIMSTAT                       0x530
#define TSEC_MIIMIND                        0x534
#define TSEC_IFSTAT                         0x53C
#define TSEC_PAR0                           0x540
#define TSEC_PAR1                           0x544
#define TSEC_TR64                           0x680
#define TSEC_TR127                          0x684
#define TSEC_TR255                          0x688
#define TSEC_TR511                          0x68C
#define TSEC_TR1K                           0x690
#define TSEC_TRMAX                          0x694
#define TSEC_TRMGV                          0x698
#define TSEC_RBYT                           0x69C
#define TSEC_RPKT                           0x6A0
#define TSEC_RFCS                           0x6A4
#define TSEC_RMCA                           0x6A8
#define TSEC_RBCA                           0x6AC
#define TSEC_RXCF                           0x6B0
#define TSEC_RXPF                           0x6B4
#define TSEC_RXUO                           0x6B8
#define TSEC_RALN                           0x6BC
#define TSEC_RFLR                           0x6C0
#define TSEC_RCDE                           0x6C4
#define TSEC_RCSE                           0x6C8
#define TSEC_RUND                           0x6CC
#define TSEC_ROVR                           0x6D0
#define TSEC_RFRG                           0x6D4
#define TSEC_RJBR                           0x6D8
#define TSEC_RDRP                           0x6DC
#define TSEC_TBYT                           0x6E0
#define TSEC_TPKT                           0x6E4
#define TSEC_TMCA                           0x6E8
#define TSEC_TBCA                           0x6EC
#define TSEC_TXPF                           0x6F0
#define TSEC_TDFR                           0x6F4
#define TSEC_TEDF                           0x6F8
#define TSEC_TSCL                           0x6FC
#define TSEC_TMCL                           0x700
#define TSEC_TLCL                           0x704
#define TSEC_TXCL                           0x708
#define TSEC_TNCL                           0x70C
#define TSEC_TDRP                           0x714
#define TSEC_TJBR                           0x718
#define TSEC_TFCS                           0x71C
#define TSEC_TXCF                           0x720
#define TSEC_TOVR                           0x724
#define TSEC_TUND                           0x728
#define TSEC_TFRG                           0x72C
#define TSEC_CAR1                           0x730
#define TSEC_CAR2                           0x734
#define TSEC_CAM1                           0x738
#define TSEC_CAM2                           0x73C
#define TSEC_IADDR0                         0x800
#define TSEC_IADDR1                         0x804
#define TSEC_IADDR2                         0x808
#define TSEC_IADDR3                         0x80C
#define TSEC_IADDR4                         0x810
#define TSEC_IADDR5                         0x814
#define TSEC_IADDR6                         0x818
#define TSEC_IADDR7                         0x81C
#define TSEC_GADDR0                         0x880
#define TSEC_GADDR1                         0x884
#define TSEC_GADDR2                         0x888
#define TSEC_GADDR3                         0x88C
#define TSEC_GADDR4                         0x890
#define TSEC_GADDR5                         0x894
#define TSEC_GADDR6                         0x898
#define TSEC_GADDR7                         0x89C
#define TSEC_ATTR                           0xBF8
#define TSEC_ATTRELI                        0xBFC

/* IEVENT and IMASK Register definitions */

#define TSEC_IEVENT_BABR		0x80000000 /* giant frame RXed */
#define TSEC_IEVENT_RXC			0x40000000 /* pause frame RXed */
#define TSEC_IEVENT_BSY			0x20000000 /* RX overrun */
#define TSEC_IEVENT_EBERR		0x10000000 /* eth bus error */
#define TSEC_IEVENT_MSRO		0x04000000 /* stats oflow */
#define TSEC_IEVENT_GTSC		0x02000000 /* graceful TX stop done */
#define TSEC_IEVENT_BABT		0x01000000 /* giant frame TXed */
#define TSEC_IEVENT_TXC			0x00800000 /* pause frame TXed */
#define TSEC_IEVENT_TXE			0x00400000 /* TX error */
#define TSEC_IEVENT_TXB			0x00200000 /* TX descriptor updated */
#define TSEC_IEVENT_TXF			0x00100000 /* TX frame completed */
#define TSEC_IEVENT_LC			0x00040000 /* late collision */
#define TSEC_IEVENT_CRL			0x00020000 /* excess collision */
#define TSEC_IEVENT_XFUN		0x00010000 /* TX underrun */
#define TSEC_IEVENT_RXB			0x00008000 /* RX descriptor updated */
#define TSEC_IEVENT_MMRD		0x00000400 /* MDIO read, 8349 only */
#define TSEC_IEVENT_MMWR		0x00000200 /* MDIO write, 8349 only */
#define TSEC_IEVENT_GRSC		0x00000100 /* graceful RX stop done */
#define TSEC_IEVENT_RXF			0x00000080 /* RX frame completed */

/*
 * Error event disable register. Note that with the IMASK
 * register, setting a bit enables the interrupt, whereas with
 * this register, setting a bit disables the interrupt.
 */

#define TSEC_EDIS_BSYDIS		0x20000000
#define TSEC_EDIS_EBERRDIS		0x10000000
#define TSEC_EDIS_TXEDIS		0x00400000
#define TSEC_EDIS_LCDIS			0x00040000
#define TSEC_EDIS_CRLDIS		0x00020000
#define TSEC_EDIS_XFUNDIS		0x00010000

/* Ethernet Control Register */

#define TSEC_ECNTRL_CLRCNT		0x00004000 /* zero status counters */
#define TSEC_ECNTRL_AUTOZ		0x00002000 /* zero counter on read */
#define TSEC_ECNTRL_STEN		0x00001000 /* status enable */
#define TSEC_ECNTRL_GMIIM		0x00000040 /* GMII mode (strap) */
#define TSEC_ECNTRL_TBIM		0x00000020 /* TBI mode (strap) */
#define TSEC_ECNTRL_RPM			0x00000010 /* reduced pin mode 1000 */
#define TSEC_ECNTRL_R100M		0x00000008 /* 0 = R10, 1 == R100 */
#define TSEC_ECNTRL_RMM			0x00000004 /* reduced pin mode 10/100*/

/* Pause time value register */

#define TSEC_PTV_PT			0x0000FFFF /* pause time value */
#define TSEC_PTV_PTE			0xFFFF0000 /* extended pause control */

/* DMA control register */

#define TSEC_DMACTRL_TDSEN		0x00000080 /* TX data snoop */
#define TSEC_DMACTRL_TBDSEN		0x00000040 /* TX bd snoop */
#define TSEC_DMACTRL_GRS		0x00000010 /* graceful RX stop */
#define TSEC_DMACTRL_GTS		0x00000008 /* graceful TX stop */
#define TSEC_DMACTRL_TOD		0x00000004 /* TX on demand */
#define TSEC_DMACTRL_WWR		0x00000002 /* write with response */
#define TSEC_DMACTRL_WOP		0x00000001 /* wait or poll */

/* Transmit control register */

#define TSEC_TCTRL_THDF			0x00000800 /* half duplex flow ctl */
#define TSEC_TCTRL_RFC_PAUSE		0x00000010 /* received pause frame */
#define TSEC_TCTRL_TFC_PAUSE		0x00000008 /* send pause frame */

/*
 * Transmit status register
 * The THLT bit will be set whenever the TX DMA engine encounters
 * an error condition, including when it runs out of ready descriptors
 * to process. The transmitter is resumed by clearing the bit (i.e.
 * writing 0 to this register).
 */

#define TSEC_TSTAT_THLT			0x80000000 /* TX halted / resume */

/* Transmit interrupt coalescing register */

#define TSEC_TXIC_ICEN			0x80000000 /* TX coal enable */
#define TSEC_TXIC_ICFCT			0x1FE00000 /* frame count thresh */
#define TSEC_TXIC_ICTT			0x0000FFFF /* timer thresh */

/* Receive control register */

#define TSEC_RCTRL_BC_REJ		0x00000010 /* reject broadcasts */
#define TSEC_RCTRL_PROM			0x00000008 /* promisc mode */
#define TSEC_RCTRL_RSF			0x00000004 /* receive short frames */

/*
 * Receive status register
 * Like the TSTAT register, the QHLT bit indicates the RX DMA engine
 * has stalled due to running out of descriptors, or encountering an
 * error. The bit must be cleared to resume the RX engine.
 */

#define TSEC_RSTAT_QHLT			0x00800000 /* RX halted / resume */

/* Receive interrupt coalescing register */

#define TSEC_RXIC_ICEN			0x80000000 /* RX coal enable */
#define TSEC_RXIC_ICFCT			0x1FE00000 /* frame count thresh */
#define TSEC_RXIC_ICTT			0x0000FFFF /* timer thresh */

#define TSEC_COAL_FRAMES(x)		((x) & 0xFF) << 21
#define TSEC_COAL_TIMER(x)		((x) & 0xFFFF)

/* MAC configuration 1 register */

#define TSEC_MACCFG1_SOFT_RESET		0x80000000 /* Reset the entire MAC */
#define TSEC_MACCFG1_RESET_RX_MC	0x00080000 /* Reset RX mac control */
#define TSEC_MACCFG1_RESET_TX_MC	0x00040000 /* Reset TX mac control */
#define TSEC_MACCFG1_RESET_RX_FUN	0x00020000 /* Reset RX function */
#define TSEC_MACCFG1_RESET_TX_FUN	0x00010000 /* Reset TX function */
#define TSEC_MACCFG1_LOOPBACK		0x00000100 /* MAC loopback mode */
#define TSEC_MACCFG1_RX_FLOW		0x00000020 /* enable RX flow control */
#define TSEC_MACCFG1_TX_FLOW		0x00000010 /* enable TX flow control */
#define TSEC_MACCFG1_SYNCD_RX_EN	0x00000008 /* RX sync'ed */
#define TSEC_MACCFG1_RX_EN		0x00000004 /* RX enable */
#define TSEC_MACCFG1_SYNCD_TX_EN	0x00000002 /* TX sync'ed */
#define TSEC_MACCFG1_TX_EN		0x00000001 /* TX enable */


/* MAC configuration 2 register */

#define TSEC_MACCFG2_IF_MODE_MASK	0x00000003
#define TSEC_MACCFG2_IF_MODE_MII        0x00000001
#define TSEC_MACCFG2_IF_MODE_GMII_TBI   0x00000002

#define TSEC_MACCFG2_PREAMBLE_LEN	0x0000F000
#define TSEC_MACCFG2_IF_MODE		0x00000300
#define TSEC_MACCFG2_HUGE_FRAME		0x00000020 
#define TSEC_MACCFG2_LENGTH_CHECK	0x00000010
#define TSEC_MACCFG2_PADCRC		0x00000004
#define TSEC_MACCFG2_CRC_EN		0x00000002
#define TSEC_MACCFG2_FULL_DUPLEX	0x00000001

#define TSEC_IFMODE_RSVD0		0x00000000
#define TSEC_IFMODE_MII			0x00000100 /* nibble mode */
#define TSEC_IFMODE_GMII_TBI		0x00000200 /* byte mode */
#define TSEC_IFMODE_RSVD1		0x00000300

/* Interpacket gap register */

#define TSEC_IPGIFG_BACKTOBACK		0x0000007F
#define TSEC_IPGIFG_MINIMUM		0x00007F00
#define TSEC_IPGIFG_NONBACKTOBACK1	0x007F0000
#define TSEC_IPGIFG_NONBACKTOBACK2	0x7F000000

/* Halfduplex register */

#define TSEC_HALFDUP_ALTBEB_TRUNC	0x00F00000
#define TSEC_HALFDUP_BEB		0x00080000
#define TSEC_HALFDUP_BPNBO		0x00040000
#define TSEC_HALFDUP_NBO		0x00020000
#define TSEC_HALFDUP_EXCESS_DEF		0x00010000
#define TSEC_HALFDUP_RETRY		0x0000F000
#define TSEC_HALFDUP_COL_WINDOW		0x0000003F

/* MII management configuration register */

#define TSEC_MIIMCFG_RESET		0x80000000
#define TSEC_MIIMCFG_NO_PRE		0x00000010
#define TSEC_MIIMCFG_MGMT_CLK		0x0000000F

#define TSEC_MIIMCFG_MCS_2		0x00000000
#define TSEC_MIIMCFG_MCS_4		0x00000001
#define TSEC_MIIMCFG_MCS_6		0x00000002
#define TSEC_MIIMCFG_MCS_8		0x00000003
#define TSEC_MIIMCFG_MCS_10		0x00000004
#define TSEC_MIIMCFG_MCS_14		0x00000005
#define TSEC_MIIMCFG_MCS_20		0x00000006
#define TSEC_MIIMCFG_MCS_28		0x00000007

/* MII management command register */

#define TSEC_MIIMCOM_SCAN		0x00000002
#define TSEC_MIIMCOM_READ		0x00000001

/* MII management address register */

#define TSEC_MIIMADD_PHYADDR		0x0000001F
#define TSEC_MIIMADD_REGADDR		0x00001F00

/* MII management control register */

#define TSEC_MIIMCON_WRDATA		0x0000FFFF

/* MII management status register */

#define TSEC_MIIMSTAT_RDDATA		0x0000FFFF

/* MII management indicator register */

#define TSEC_MIIMIND_NOT_VALID		0x00000004
#define TSEC_MIIMIND_SCAN		0x00000002
#define TSEC_MIIMIND_BUSY		0x00000001

/* Attribute register */

#define TSEC_ATTR_ELCWT			0x00006000 /* data L2 cache extract */
#define TSEC_ATTR_BDLWT			0x00000C00 /* BD L2 cache extract */
#define TSEC_ATTR_RDSEN			0x00000080 /* RX buffer snooping */
#define TSEC_ATTR_RBDSEN		0x00000040 /* RX descriptor snooping */

#define TSEC_ELCWT_NONE			0x00000000
#define TSEC_ELCWT_RSVD			0x00002000
#define TSEC_ELCWT_L2			0x00004000
#define TSEC_ELCWT_L2_LOCK		0x00006000

#define TSEC_BDLWT_NONE			0x00000000
#define TSEC_BDLWT_RSVD			0x00000400
#define TSEC_BDLWT_L2			0x00000800
#define TSEC_BDLWT_L2_LOCK		0x00000C00

/* Attribute extract length and index register */

#define TSEC_ATTRELI_EXTLEN		0x3FFF0000
#define TSEC_ATTRELI_EXTIDX		0x00003FFF

#define TSEC_ATTRELI_EL(x)	(((x) & 0x3FFF) << 16)
#define TSEC_ATTRELI_EI(x)      ((x) & 0x3FFF)

/*
 * Buffer descriptor format
 *
 * The descriptor structure is always 8 bytes. For the ETSEC, there's
 * an additional field frame descriptor field which is hidden in
 * the packet buffer, which is used for specifying additional
 * information related to checksum offload.
 *
 * The descriptor layout is much the same as it is for all of
 * Motorola/Freescale's ethernet MACs (including the TSEC, SCC
 * and CPM). There's a 16 bit status field, 16 bit length field,
 * and a 32-bit address field. Each descriptor describes a single
 * fragment. The last fragment has the 'last in frame' bit set.
 * Since there is no 'next' pointer, descriptors are allocated
 * in contiguous arrays. The last descriptor in the array must
 * have the 'wrap' bit set.
 */

typedef struct tsecDesc
    {
    volatile UINT16	bdSts;
    volatile UINT16	bdLen;
    volatile UINT32	bdAddr;
    } TSEC_DESC;

/* Transmit descriptor status bits */

#define TSEC_TBD_R		0x8000 /* owner, 0 == host, 1 == chip */
#define TSEC_TBD_PADCRC		0x4000 /* autopad and append CRC */
#define TSEC_TBD_W		0x2000 /* wrap, last descriptor in ring */
#define TSEC_TBD_I		0x1000 /* interrupt after processing is done */
#define TSEC_TBD_L		0x0800 /* last descriptor in frame */
#define TSEC_TBD_TC		0x0400 /* append CRC */
#define TSEC_TBD_DEF		0x0200 /* excess deferral condition */
#define TSEC_TBD_TO1		0x0100 /* software scratch bit */
#define TSEC_TBD_HFE_LC		0x0080 /* huge frame, or late collision */
#define TSEC_TBD_RL		0x0040 /* retry limit exceeded */
#define TSEC_TBD_RC		0x003C /* retry count */
#define TSEC_TBD_UN		0x0002 /* TX underrun */
#define TSEC_TBD_TR		0x0001 /* packet truncated */

/* Receive descriptor status bits */

#define TSEC_RBD_E		0x8000 /* owner, 0 == host, 1 == chip */
#define TSEC_RBD_RO1		0x4000 /* software scratch bit */
#define TSEC_RBD_W		0x2000 /* wrap, last descriptor in ring */
#define TSEC_RBD_I		0x1000 /* interrupt after processing is done */
#define TSEC_RBD_L		0x0800 /* last descriptor in frame */
#define TSEC_RBD_F		0x0400 /* first descriptor in frame */
#define TSEC_RBD_M		0x0200 /* filter miss */
#define TSEC_RBD_BC		0x0080 /* broadcast frame */
#define TSEC_RBD_MC		0x0040 /* multicast frame */
#define TSEC_RBD_LG		0x0020 /* giant frame error */
#define TSEC_RBD_NO		0x0010 /* alignment error */
#define TSEC_RBD_SH		0x0008 /* runt frame error */
#define TSEC_RBD_CR		0x0004 /* CRC error */
#define TSEC_RBD_OV		0x0002 /* FIFO overrun */
#define TSEC_RBD_TR		0x0001 /* packet truncated */

#define TSEC_RX_DESC_CNT	128
#define TSEC_TX_DESC_CNT	128

/*#define TSEC_INC_DESC(x, y)	(x) = (((x) + 1) % y)*/
#define TSEC_INC_DESC(x, y)	(x) = ((x + 1) & (y - 1))
#define TSEC_MAXFRAG		16
#define TSEC_MAX_RX		16

#define TSEC_MTU	1500
#define TSEC_JUMBO_MTU	9000
#define TSEC_CLSIZE	1600
#define TSEC_JUMBO_CLSIZE	9056

#define TSEC_BOUND	(_CACHE_ALIGN_SIZE - 1)
#define TSEC_ALIGN(x)		\
    (char *)(((UINT32)(x) + (TSEC_BOUND)) & ~(TSEC_BOUND))

#define TSEC_ADJ(x)		\
    (x)->m_data = TSEC_ALIGN((x)->m_data)

#define TSEC_NAME	"mottsec"
#define TSEC_TIMEOUT	10000
#define TSEC_INTRS	(TSEC_RXINTRS|TSEC_TXINTRS|TSEC_ERRINTRS)
#define TSEC_RXINTRS	(/*TSEC_IEVENT_RXB|*/TSEC_IEVENT_RXF|TSEC_IEVENT_RXC)
#define TSEC_TXINTRS	(/*TSEC_IEVENT_TXB|*/TSEC_IEVENT_TXF|TSEC_IEVENT_TXC)
#define TSEC_ERRINTRS	(TSEC_IEVENT_XFUN|TSEC_IEVENT_EBERR|TSEC_IEVENT_BSY)

#define ETHER_CRC_LEN           4
#define ETHER_CRC_POLY_BE       0x04c11db6

#ifndef MII_SR_EXT_STS
#define MII_SR_EXT_STS          0x0100          /* extended sts in reg 15 */
#endif

#ifndef MII_CR_1000
#define MII_CR_1000             0x0040          /* 1 = 1000mb when
                                                   MII_CR_100 is also 1 */
#endif

#define bswap16(x)      ((LSB(x) << 8) | MSB(x))
#define bswap32(x)      LONGSWAP((UINT32)(x))
#define bswap64(x)      /* not yet */

typedef struct endNetPool
    {
    NET_POOL            pool;
    void                * pMblkMemArea;
    void                * pClMemArea;
    } END_NET_POOL;

#define tsecEndPoolTupleFree(x) netMblkClChainFree(x)
#define tsecEndPoolTupleGet(x)      \
        netTupleGet((x), (x)->clTbl[0]->clSize, M_DONTWAIT, MT_DATA, 0)

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

typedef struct _TSEC_END_MEDIA
    {
    UINT32                      endMediaActive;
    UINT32                      endMediaStatus;
    } TSEC_END_MEDIA;

/* number of seconds to wait between link state checks */

#define TSEC_LINKPOLL    2

/* Default interrupt vectors */

#define TSEC_TXINUM	25
#define TSEC_RXINUM	26
#define TSEC_ERRINUM	30

#define ETHER_ADDR_LEN          6

/*
 * Private adapter context structure.
 */

typedef struct tsec_drv_ctrl
    {
    END_OBJ		tsecEndObj;
    int			tsecUnit;
    void *		tsecRegBase;
    UINT32		tsecInumTx;
    UINT32		tsecInumRx;
    UINT32		tsecInumErr;

    volatile BOOL	tsecErrPending;

    volatile BOOL	tsecRxPending;

    volatile BOOL	tsecTxPending;
    UINT8		tsecTxCur;
    UINT8		tsecTxLast;
    volatile BOOL	tsecTxStall;
    UINT16		tsecTxThresh;

    BOOL		tsecPolling;
    M_BLK_ID		tsecPollBuf;
    UINT32		tsecIntMask;
    UINT32		tsecRxIntrs;
    UINT32		tsecTxIntrs;
    UINT32		tsecErrIntrs;

    UINT8		tsecAddr[ETHER_ADDR_LEN];

    UINT16		tsecMiiSts;
    WDOG_ID		tsecMiiWd;
    END_ERR		tsecLastError;
    UINT32		tsecCurMedia;
    UINT32		tsecCurStatus;
    struct tsec_drv_ctrl *tsecMiiDev;
    int			tsecMiiPhyAddr;

    /* DMA tags and maps. */

    TSEC_DESC		*tsecRxDesc;
    TSEC_DESC		*tsecTxDesc;

    M_BLK_ID		tsecRxMblk[TSEC_RX_DESC_CNT];
    M_BLK_ID		tsecTxMblk[TSEC_TX_DESC_CNT];

    UINT32		tsecTxProd;
    UINT32		tsecTxCons;
    UINT32		tsecTxFree;
    UINT32		tsecRxIdx;

    SEM_ID		tsecDevSem;

    UINT32		tsecErrInt;
    } TSEC_DRV_CTRL;

#define CSR_READ_4(pDev, addr)					\
	*(volatile UINT32 *)((UINT32)pDev->tsecRegBase + addr)

#define CSR_WRITE_4(pDev, addr, data)				\
	do {							\
	    volatile UINT32 *pReg =				\
	        (UINT32 *)((UINT32)pDev->tsecRegBase + addr);	\
	    *(pReg) = (UINT32)(data);				\
	    WRS_ASM("eieio");					\
	} while ((0))

#define CSR_SETBIT_4(pDev, offset, val)          \
        CSR_WRITE_4(pDev, offset, CSR_READ_4(pDev, offset) | (val))

#define CSR_CLRBIT_4(pDev, offset, val)          \
        CSR_WRITE_4(pDev, offset, CSR_READ_4(pDev, offset) & ~(val))


#endif /* BSP_VERSION */

/* Compatibility cruft with old motTsecEnd driver */

/* MII/PHY PHY_DEF_MODE flags to init the phy driver */
#define MOT_TSEC_USR_MODE_DEFAULT         0
#define MOT_TSEC_USR_PHY_NO_AN   0x00000001  /* do not auto-negotiate */
#define MOT_TSEC_USR_PHY_TBL     0x00000002  /* use negotiation table */
#define MOT_TSEC_USR_PHY_NO_FD   0x00000004  /* do not use full duplex */
#define MOT_TSEC_USR_PHY_NO_100  0x00000008  /* do not use 100Mbit speed */
#define MOT_TSEC_USR_PHY_NO_HD   0x00000010  /* do not use half duplex */
#define MOT_TSEC_USR_PHY_NO_10   0x00000020  /* do not use 10Mbit speed */
#define MOT_TSEC_USR_PHY_MON     0x00000040  /* use PHY Monitor */
#define MOT_TSEC_USR_PHY_ISO     0x00000080  /* isolate a PHY */


/* ECNTRL Ethernet Control */
#define MOT_TSEC_USR_STAT_CLEAR     0x00000100 /* init + runtime clear mstats*/
#define MOT_TSEC_USR_STAT_AUTOZ     0x00000200 /* init */
#define MOT_TSEC_USR_STAT_ENABLE    0x00000400 /* init */

/* PHY bus configuration selections */
#define MOT_TSEC_USR_MODE_MASK      0x0003f800
#define MOT_TSEC_USR_MODE_TBI       0x00000800
#define MOT_TSEC_USR_MODE_RTBI      0x00001000
#define MOT_TSEC_USR_MODE_MII       0x00002000
#define MOT_TSEC_USR_MODE_GMII      0x00004000
#define MOT_TSEC_USR_MODE_RGMII     0x00008000
#define MOT_TSEC_USR_MODE_RGMII_10  0x00010000
#define MOT_TSEC_USR_MODE_RGMII_100 0x00020000

typedef struct
    {
    /* function pointers for BSP and Driver call backs */
    FUNCPTR miiPhyInit;     /* BSP Phy driver init callback */
    FUNCPTR miiPhyInt;      /* BSP call back to process PHY status change interrupt */
    FUNCPTR miiPhyStatusGet;   /* Driver call back to get duplex status  */
    FUNCPTR miiPhyRead;     /* BSP call back to read MII/PHY registers */
    FUNCPTR miiPhyWrite;    /* BSP call back to write MII/PHY registers */
    FUNCPTR enetAddrGet;    /* Driver call back to get the Ethernet address */
    FUNCPTR enetAddrSet;    /* Driver call back to set the Ethernet address */
    FUNCPTR enetEnable;     /* Driver call back to enable the ENET interface */
    FUNCPTR enetDisable;    /* Driver call back to disable the ENET interface */
    FUNCPTR extWriteL2AllocFunc;    /* Driver call back to put tx bd in L2 */
    } MOT_TSEC_FUNC_TABLE;

typedef struct
    {
    UINT32   phyAddr;        /* phy physical address */
    UINT32   phyDefMode;     /* default mode */
    UINT32   phyMaxDelay;    /* max delay */
    UINT32   phyDelayParm;   /* poll interval if in poll mode */
    MII_AN_ORDER_TBL * phyAnOrderTbl;  /* autonegotiation table */
    } MOT_TSEC_PHY_PARAMS;

typedef struct
    {
    UINT8  autonegError;            /* 0-N/A, 0 - none,   1- error */
    UINT8  duplex;                  /* 1 - half,   2- full */
#define MOT_TSEC_PHY_DUPLEX_HALF    (1)
#define MOT_TSEC_PHY_DUPLEX_FULL    (2)
    UINT8  speed;                   /* 0-N/A, 1 - 10, 2- 100, 3 -1G */
#define MOT_TSEC_PHY_SPEED_10       (1)
#define MOT_TSEC_PHY_SPEED_100      (2)
#define MOT_TSEC_PHY_SPEED_1000     (3)
    UINT8  link;                    /* 0-N/A, 1 - down, 2- up */
    UINT8  symbolError;             /* 0-N/A, 1 - none, 2- error */
    UINT8  autoNegComplete;         /* 0-N/A, 1 - no, 2- completed */
    UINT8  energyDetect;            /* 0-N/A, 1 - no, 2- detected */
    UINT8  falseCarrier;            /* 0-N/A, 1 - no, 2- detected */
    UINT8  downShift;               /* 0-N/A, 1 - no, 2- detected */
    UINT8  fifoError;               /* 0-N/A, 1 - none, 2- error */
    UINT8  xover;                   /* 0-N/A, 1 - MDI, 2- MDIX */
    UINT8  polarity;                /* 0-N/A, 1 - normal, 2- reversed */
    UINT8  jabber;                  /* 0-N/A, 1 - no, 2- detected */
    UINT8  pageReceived;            /* 0-N/A, 1 - no, 2- detected */
    UINT8  cableLength;             /* 0-N/A */
    UINT8  txPause;                 /* 0-N/A, 1 - no, 2- detected */
    UINT8  rxPause;                 /* 0-N/A, 1 - no, 2- detected */
    UINT8  farEndFault;             /* 0-N/A, 1 - no, 2- detected */
    UINT32 rxErrorCntr;             /* 0-N/A, number of rx errors */
    UINT32 reserved[4];             /* future use */
    } MOT_TSEC_PHY_STATUS;

typedef struct
    {
    UINT8   *memBufPtr;    /* Buffer pointer for allocated buffer space */
    UINT32   memBufSize;   /* Buffer pool size */
    void     *bdBasePtr;    /* Descriptor Base Address */
    UINT32   bdSize;       /* Descriptor Size */
    UINT32   rbdNum;       /* Number of Receive Buffer Descriptors  */
    UINT32   tbdNum;       /* Number of Transmit Buffer Descriptors */
    UINT32   unit0TxVec;
    UINT32   unit0RxVec;
    UINT32   unit0ErrVec;
    UINT32   unit1TxVec;
    UINT32   unit1RxVec;
    UINT32   unit1ErrVec;
    } MOT_TSEC_PARAMS;

typedef struct
    {
    UINT32   inum_tsecTx;    /* Transmit Interrupt */
    UINT32   inum_tsecRx;    /* Receive Interrupt */
    UINT32   inum_tsecErr;    /* Error Interrupt */
    FUNCPTR  inumToIvec;     /* function to convert INUM to IVEC */
    FUNCPTR  ivecToInum;     /* function to convert IVEC to INUM */
    } MOT_TSEC_INT_CTRL;

#define MOT_TSEC_MAX_DEVS        2
#define MOT_TSEC_DEV_1           0
#define MOT_TSEC_DEV_2           1
#define MOT_TSEC_ADRS_OFFSET_1  0x00024000
#define MOT_TSEC_ADRS_OFFSET_2  0x00025000
#define MOT_TSEC_DEV_NAME        "mottsec"
#define MOT_TSEC_DEV_NAME_LEN    8

#ifdef __cplusplus
}
#endif

#endif /* __INCmotTsecEndh */

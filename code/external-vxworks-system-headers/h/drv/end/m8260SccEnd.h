/* m8260SccEnd.h - Motorola MPC8260 Serial Communication Controllers (SCC) Ethernet interface header */

/*
 * Copyright (c) 1996-2009 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01e,28jan09,wap  Complete driver rewrite (WIND00146685)
01d,16jan03,gjc  SPR#85071 and SPR#85093 :Added define to support DUPLEX.
01c,17may02,gjc  #SPR 75922, undef SCC_BUF if prev defined.
01b,09may02,gjc  Fixing SPR #75046 by setting SCC to Full Duplex Mode.
01a,10may01,g_h  adapted from sbcM8260CpmEnd.h (ver. 01b).
*/


#ifndef __INCm8260SccEndh
#define __INCm8260SccEndh

#ifdef __cplusplus
extern "C" {
#endif

#define ETHER_ADDR_LEN          6
#define ETHER_CRC_LEN           4

typedef struct endNetPool
    {
    NET_POOL            pool;
    void                * pMblkMemArea;
    void                * pClMemArea;
    } END_NET_POOL;

#define sccEndPoolTupleFree(x) netMblkClChainFree(x)
#define sccEndPoolTupleGet(x)      \
        netTupleGet((x), (x)->clTbl[0]->clSize, M_DONTWAIT, MT_DATA, 0)


#define SCC_GSMR_L	0x00	/* SCC General Mode */
#define SCC_GSMR_H	0x04	/* SCC General Mode */
#define SCC_PSMR	0x08	/* SCC Proto. Spec */
#define SCC_TODR	0x0C	/* SCC Tx On Demand */
#define SCC_DSR		0x0E	/* SCC Data Sync */
#define SCC_SCCER	0x10	/* SCC Event Reg */
#define SCC_SCCMR	0x14	/* SCC Mask Reg */
#define SCC_SCCSR	0x17	/* SCC Status Reg */


#define SCC_GSMRL_HDLC          0x00000000      /* HDLC mode */
#define SCC_GSMRL_APPLETALK     0x00000002      /* AppleTalk mode (LocalTalk) */
#define SCC_GSMRL_SS7           0x00000003      /* SS7 mode (microcode) */
#define SCC_GSMRL_UART          0x00000004      /* UART mode */
#define SCC_GSMRL_PROFI_BUS     0x00000005      /* Profi-Bus mode (microcode) */
#define SCC_GSMRL_ASYNC_HDLC    0x00000006      /* async HDLC mode (microcode)*/
#define SCC_GSMRL_V14           0x00000007      /* V.14 mode */
#define SCC_GSMRL_BISYNC        0x00000008      /* BISYNC mode */
#define SCC_GSMRL_DDCMP         0x00000009      /* DDCMP mode (microcode) */
#define SCC_GSMRL_ETHERNET      0x0000000c      /* ethernet mode (SCC1 only) */
#define SCC_GSMRL_ENT           0x00000010      /* enable transmitter */
#define SCC_GSMRL_ENR           0x00000020      /* enable receiver */
#define SCC_GSMRL_LOOPBACK      0x00000040      /* local loopback mode */
#define SCC_GSMRL_ECHO          0x00000080      /* automatic echo mode */
#define SCC_GSMRL_TENC          0x00000700      /* transmitter encoding method*/
#define SCC_GSMRL_RENC          0x00003800      /* receiver encoding method */
#define SCC_GSMRL_RDCR_X8       0x00004000      /* receive DPLL clock x8 */
#define SCC_GSMRL_RDCR_X16      0x00008000      /* receive DPLL clock x16 */
#define SCC_GSMRL_RDCR_X32      0x0000c000      /* receive DPLL clock x32 */
#define SCC_GSMRL_TDCR_X8       0x00010000      /* transmit DPLL clock x8 */
#define SCC_GSMRL_TDCR_X16      0x00020000      /* transmit DPLL clock x16 */
#define SCC_GSMRL_TDCR_X32      0x00030000      /* transmit DPLL clock x32 */
#define SCC_GSMRL_TEND          0x00040000      /* transmitter frame ending */
#define SCC_GSMRL_TPP_00        0x00180000      /* Tx preamble pattern = 00 */
#define SCC_GSMRL_TPP_10        0x00080000      /* Tx preamble pattern = 10 */
#define SCC_GSMRL_TPP_01        0x00100000      /* Tx preamble pattern = 01 */
#define SCC_GSMRL_TPP_11        0x00180000      /* Tx preamble pattern = 11 */
#define SCC_GSMRL_TPL_NONE      0x00000000      /* no Tx preamble (default) */
#define SCC_GSMRL_TPL_8         0x00200000      /* Tx preamble = 1 byte */
#define SCC_GSMRL_TPL_16        0x00400000      /* Tx preamble = 2 bytes */
#define SCC_GSMRL_TPL_32        0x00600000      /* Tx preamble = 4 bytes */
#define SCC_GSMRL_TPL_48        0x00800000      /* Tx preamble = 6 bytes */
#define SCC_GSMRL_TPL_64        0x00a00000      /* Tx preamble = 8 bytes */
#define SCC_GSMRL_TPL_128       0x00c00000      /* Tx preamble = 16 bytes */
#define SCC_GSMRL_TINV          0x01000000      /* DPLL transmit input invert */
#define SCC_GSMRL_RINV          0x02000000      /* DPLL receive input invert */
#define SCC_GSMRL_TSNC          0x0c000000      /* transmit sense */
#define SCC_GSMRL_TCI           0x10000000      /* transmit clock invert */
#define SCC_GSMRL_EDGE          0x60000000      /* adjustment edge +/- */

#define SCC_GSMRH_RSYN          0x00000001      /* receive sync timing*/
#define SCC_GSMRH_RTSM          0x00000002      /* RTS* mode */
#define SCC_GSMRH_SYNL          0x0000000c      /* sync length */
#define SCC_GSMRH_TXSY          0x00000010      /* transmitter/receiver sync */
#define SCC_GSMRH_RFW           0x00000020      /* Rx FIFO width */
#define SCC_GSMRH_TFL           0x00000040      /* transmit FIFO length */
#define SCC_GSMRH_CTSS          0x00000080      /* CTS* sampling */
#define SCC_GSMRH_CDS           0x00000100      /* CD* sampling */
#define SCC_GSMRH_CTSP          0x00000200      /* CTS* pulse */
#define SCC_GSMRH_CDP           0x00000400      /* CD* pulse */
#define SCC_GSMRH_TTX           0x00000800      /* transparent transmitter */
#define SCC_GSMRH_TRX           0x00001000      /* transparent receiver */
#define SCC_GSMRH_REVD          0x00002000      /* reverse data */
#define SCC_GSMRH_TCRC          0x0000c000      /* transparent CRC */
#define SCC_GSMRH_GDE           0x00010000      /* glitch detect enable */

/* CPM - Communication Processor Module */

/* SCC Ethernet Protocol Specific Mode Register definitions */

#define SCC_ETHER_PSMR_FDE      0x0001
#define SCC_ETHER_PSMR_NIB_13   0x0000          /* SFD 13 bits after TENA */
#define SCC_ETHER_PSMR_NIB_14   0x0002          /* SFD 14 bits after TENA */
#define SCC_ETHER_PSMR_NIB_15   0x0004          /* SFD 15 bits after TENA */
#define SCC_ETHER_PSMR_NIB_16   0x0006          /* SFD 16 bits after TENA */
#define SCC_ETHER_PSMR_NIB_21   0x0008          /* SFD 21 bits after TENA */
#define SCC_ETHER_PSMR_NIB_22   0x000a          /* SFD 22 bits after TENA */
#define SCC_ETHER_PSMR_NIB_23   0x000c          /* SFD 23 bits after TENA */
#define SCC_ETHER_PSMR_NIB_24   0x000e          /* SFD 24 bits after TENA */
#define SCC_ETHER_PSMR_LCW      0x0010          /* late collision window */
#define SCC_ETHER_PSMR_SIP      0x0200          /* sample input pins */
#define SCC_ETHER_PSMR_LPB      0x0040          /* loopback operation */
#define SCC_ETHER_PSMR_SBT      0x0080          /* stop backoff timer */
#define SCC_ETHER_PSMR_BRO      0x0100          /* broadcast address */
#define SCC_ETHER_PSMR_PRO      0x0200          /* promiscuous mode */
#define SCC_ETHER_PSMR_CRC      0x0800          /* CRC selection */
#define SCC_ETHER_PSMR_IAM      0x1000          /* individual address mode */
#define SCC_ETHER_PSMR_RSH      0x2000          /* receive short frame */
#define SCC_ETHER_PSMR_FC       0x4000          /* force collision */
#define SCC_ETHER_PSMR_HBC      0x8000          /* heartbeat checking*/

/* SCC Ethernet Event and Mask Register definitions */

#define SCC_ETHER_SCCX_RXB      0x0001          /* buffer received event */
#define SCC_ETHER_SCCX_TXB      0x0002          /* buffer transmitted event */
#define SCC_ETHER_SCCX_BSY      0x0004          /* busy condition */
#define SCC_ETHER_SCCX_RXF      0x0008          /* frame received event */
#define SCC_ETHER_SCCX_TXE      0x0010          /* transmission error event */
#define SCC_ETHER_SCCX_GRA      0x0080          /* graceful stop event */

/* SCC Ethernet Receive Buffer Descriptor definitions */

#define SCC_ETHER_RX_BD_CL      0x0001          /* collision condition */
#define SCC_ETHER_RX_BD_OV      0x0002          /* overrun condition */
#define SCC_ETHER_RX_BD_CR      0x0004          /* Rx CRC error */
#define SCC_ETHER_RX_BD_SH      0x0008          /* short frame received */
#define SCC_ETHER_RX_BD_NO      0x0010          /* Rx nonoctet aligned frame */
#define SCC_ETHER_RX_BD_LG      0x0020          /* Rx frame length violation */
#define SCC_ETHER_RX_BD_M       0x0100          /* miss bit for prom mode */
#define SCC_ETHER_RX_BD_F       0x0400          /* buffer is first in frame */
#define SCC_ETHER_RX_BD_L       0x0800          /* buffer is last in frame */
#define SCC_ETHER_RX_BD_I       0x1000          /* interrupt on receive */
#define SCC_ETHER_RX_BD_W       0x2000          /* last BD in ring */
#define SCC_ETHER_RX_BD_E       0x8000          /* buffer is empty */

/* SCC Ethernet Transmit Buffer Descriptor definitions */

#define SCC_ETHER_TX_BD_CSL     0x0001          /* carrier sense lost */
#define SCC_ETHER_TX_BD_UN      0x0002          /* underrun */
#define SCC_ETHER_TX_BD_RC      0x003c          /* retry count */
#define SCC_ETHER_TX_BD_RL      0x0040          /* retransmission limit */
#define SCC_ETHER_TX_BD_LC      0x0080          /* late collision */
#define SCC_ETHER_TX_BD_HB      0x0100          /* heartbeat */
#define SCC_ETHER_TX_BD_DEF     0x0200          /* defer indication */
#define SCC_ETHER_TX_BD_TC      0x0400          /* auto transmit CRC */
#define SCC_ETHER_TX_BD_L       0x0800          /* buffer is last in frame */
#define SCC_ETHER_TX_BD_I       0x1000          /* interrupt on transmit */
#define SCC_ETHER_TX_BD_W       0x2000          /* last BD in ring */
#define SCC_ETHER_TX_BD_PAD     0x4000          /* auto pad short frames */
#define SCC_ETHER_TX_BD_R       0x8000          /* buffer is ready */

/* SCC Parameter RAM registers in ethernet mode */

#define SCC_RBASE	0x00
#define	SCC_TBASE	0x02
#define SCC_RFCR	0x04
#define SCC_TFCR	0x05
#define SCC_MRBLR	0x06
#define SCC_RSTATE	0x08
#define SCC_RIP		0x0C
#define SCC_RBPTR	0x10
#define SCC_RCOUNT	0x12
#define SCC_RTEMP	0x14
#define SCC_TSTATE	0x18
#define SCC_TIP		0x1C
#define SCC_TBPTR	0x20
#define SCC_TCOUNT	0x22
#define SCC_TTEMP	0x24
#define SCC_RCRC	0x28
#define SCC_TCRC	0x2C
#define SCC_C_PRES	0x30
#define SCC_C_MASK	0x34
#define SCC_CRCEC	0x38
#define SCC_ALEC	0x3C
#define SCC_DISFC	0x40
#define SCC_PADS	0x44
#define SCC_RET_LIM	0x46
#define SCC_RET_CNT	0x48
#define SCC_MFLR	0x4A
#define SCC_MINFLR	0x4C
#define SCC_MAXD1	0x4E
#define SCC_MAXD2	0x50
#define SCC_MAXD	0x52
#define SCC_DMA_CNT	0x54
#define SCC_MAX_B	0x56
#define SCC_GADDR1	0x58
#define SCC_GADDR2	0x5A
#define SCC_GADDR3	0x5C
#define SCC_GADDR4	0x5E
#define SCC_TBUF0_DATA0	0x60
#define SCC_TBUF0_DATA1	0x64
#define SCC_TBUF0_RBA0	0x68
#define SCC_TBUF0_CRC	0x6C
#define SCC_TBUF0_BCNT	0x80
#define SCC_PADDR_H	0x72
#define SCC_PADDR_M	0x74
#define SCC_PADDR_L	0x7C
#define SCC_P_PER	0x78
#define SCC_RFBD_PTR	0x7A
#define SCC_TFBD_PTR	0x7C
#define SCC_TLBD_PTR	0x7E
#define SCC_TBUF1_DATA0	0x80
#define SCC_TBUF1_DATA1	0x84
#define SCC_TBUF1_RBA0	0x88
#define SCC_TBUF1_CRC	0x8C
#define SCC_TBUF1_BCNT	0x90
#define SCC_TX_LEN	0x92
#define SCC_IADDR1	0x94
#define SCC_IADDR2	0x96
#define SCC_IADDR3	0x98
#define SCC_IADDR4	0x9A
#define SCC_BOFF_CNT	0x9C
#define SCC_TADDR_H	0x9E
#define SCC_TADDR_M	0xA0
#define SCC_TADDR_L	0xA2


/* RFCR and TFCR registers */

#define FCR_DTB		0x02
#define FCR_TC2		0x04
#define FCR_BO_LE	0x08
#define FCR_BO_BE	0x10
#define FCR_GBL		0x20

#define SCC_NAME	"motscc"
#define SCC_TIMEOUT 10000
#define SCC_INTRS	\
     (SCC_ETHER_SCCX_RXB|SCC_ETHER_SCCX_BSY|SCC_ETHER_SCCX_RXF|	\
      SCC_ETHER_SCCX_TXB|SCC_ETHER_SCCX_TXE)

#define SCC_RXINTRS 	\
     (SCC_ETHER_SCCX_RXB|SCC_ETHER_SCCX_BSY|SCC_ETHER_SCCX_RXF)

#define SCC_TXINTRS	\
     (SCC_ETHER_SCCX_TXB|SCC_ETHER_SCCX_TXE)

#define SCC_LINKINTRS 0

#define SCC_RBD_ALIGN 16

#define SCC_ALIGN(x)    (char *)(((UINT32)(x) + (15 * 2)) & ~15)

#define SCC_ADJ(x)      \
        (x)->m_data = SCC_ALIGN((x)->m_data)

#define SCC_CLSIZE	1600

#define SCC_INC_DESC(x, y)      (x) = ((x + 1) & (y - 1))
#define SCC_MAXFRAG             16
#define SCC_MAX_RX              16

/*
 * We deliberately specify a large number of DMA descriptors here,
 * in order to avoid losing any frames on receive. The number of
 * buffers (SCC_BUF_CNT) should be at least twice the number of
 * RX descriptors (SCC_RX_DESC_CNT), plus the number of TX descriptors
 * (SCC_TX_DESC_CNT).
 *
 * Note that unlike the FEC and FCC interfaces, the DMA descriptor
 * rings for the CPM/SCC must reside in DPRAM. Normally, the range
 * from 0x2000 to 0x21FF is used, howeve this is very small and only
 * allows for 32 descriptors for RX and TX. The MPC860/MPC850 has
 * additional DPRAM located at 0x3000 through 0x3BFF. We use this
 * region instead, so that we can have a fairly large RX ring.
 */

#define SCC_BUF_CNT		(256)
#define SCC_RX_DESC_CNT         32
#define SCC_TX_DESC_CNT         32

#define SCC_RX_DPRAM		0x3000
#define SCC_TX_DPRAM		0x3400

/*
#define SCC_BUF_CNT		768
#define SCC_RX_DESC_CNT		256
#define SCC_TX_DESC_CNT		128

#define SCC_RX_DPRAM		0x3000
#define SCC_TX_DPRAM		0x3800
*/

typedef struct scc_desc
    {
    volatile UINT16     bdSts;
    volatile UINT16     bdLen;
    volatile UINT32     bdAddr;
    } SCC_DESC;

/*
 * Private adapter context structure.
 */

typedef struct scc_drv_ctrl
    {
    END_OBJ		sccEndObj;
    void *              sccPram;
    void *              sccIram;
    int                 sccUnit;
    int                 sccIvec;
    int                 sccIlevel;

    volatile BOOL	sccIntPending;

    volatile BOOL	sccRxPending;

    volatile BOOL	sccTxPending;
    UINT8		sccTxCur;
    UINT8		sccTxLast;
    volatile BOOL	sccTxStall;
    UINT16		sccTxThresh;

    BOOL		sccPolling;
    M_BLK_ID		sccPollBuf;
    UINT16		sccIntMask;

    UINT8		sccAddr[ETHER_ADDR_LEN + 2];

    SCC_DESC            *sccRxDescMem;

    SCC_DESC            *sccTxDescMem;

    M_BLK_ID            sccRxMblk[SCC_RX_DESC_CNT];
    M_BLK_ID            sccTxMblk[SCC_TX_DESC_CNT];

    UINT32              sccTxProd;
    UINT32              sccTxCons;
    UINT32              sccTxFree;
    UINT32              sccRxIdx;

    int                 sccNum;

    END_ERR		sccLastError;
    } SCC_DRV_CTRL;


#ifndef BSP_VERSION

LOCAL UINT32 csr_read_4 (SCC_DRV_CTRL *, UINT32, int);
LOCAL void csr_write_4 (SCC_DRV_CTRL *, UINT32, int, UINT32);
LOCAL UINT16 csr_read_2 (SCC_DRV_CTRL *, UINT16, int);
LOCAL void csr_write_2 (SCC_DRV_CTRL *, UINT16, int, UINT16);
#ifdef notused
LOCAL UINT8 csr_read_1 (SCC_DRV_CTRL *, UINT8, int);
#endif
LOCAL void csr_write_1 (SCC_DRV_CTRL *, UINT8, int, UINT8);

#define SCC_PRAM 0
#define SCC_IRAM 1

LOCAL UINT32 csr_read_4
    ( 
    SCC_DRV_CTRL * pDrv,
    UINT32 addr,
    int ix
    )
    {
    UINT32 data;
    if (ix == SCC_PRAM)
        data = *(UINT32 *)((UINT8 *)pDrv->sccPram + addr);
    else
        data = *(UINT32 *)((UINT8 *)pDrv->sccIram + addr);
    return (data);
    }

LOCAL void csr_write_4
    (
    SCC_DRV_CTRL * pDrv,
    UINT32 addr,
    int ix,
    UINT32 data
    )
    {
    UINT32 * reg;

    if (ix == SCC_PRAM)
        reg = (UINT32 *)((UINT8 *)pDrv->sccPram + addr);
    else    
        reg = (UINT32 *)((UINT8 *)pDrv->sccIram + addr);
    *reg = data;
    return;
    }

LOCAL UINT16 csr_read_2
    ( 
    SCC_DRV_CTRL * pDrv,
    UINT16 addr,
    int ix
    )
    {
    UINT16 data;
    if (ix == SCC_PRAM)
        data = *(UINT16 *)((UINT8 *)pDrv->sccPram + addr);
    else
        data = *(UINT16 *)((UINT8 *)pDrv->sccIram + addr);
    return (data);
    }

LOCAL void csr_write_2
    (
    SCC_DRV_CTRL * pDrv,
    UINT16 addr,
    int ix,
    UINT16 data
    )
    {
    UINT16 * reg;

    if (ix == SCC_PRAM)
        reg = (UINT16 *)((UINT8 *)pDrv->sccPram + addr);
    else    
        reg = (UINT16 *)((UINT8 *)pDrv->sccIram + addr);
    *reg = data;
    return;
    }

#ifdef notused
LOCAL UINT8 csr_read_1
    ( 
    SCC_DRV_CTRL * pDrv,
    UINT8 addr,
    int ix
    )
    {
    UINT16 data;
    if (ix == SCC_PRAM)
        data = *(UINT8 *)((UINT8 *)pDrv->sccPram + addr);
    else
        data = *(UINT8 *)((UINT8 *)pDrv->sccIram + addr);
    return (data);
    }
#endif

LOCAL void csr_write_1
    (
    SCC_DRV_CTRL * pDrv,
    UINT8 addr,
    int ix,
    UINT8 data
    )
    {
    UINT8 * reg;

    if (ix == SCC_PRAM)
        reg = (UINT8 *)((UINT8 *)pDrv->sccPram + addr);
    else    
        reg = (UINT8 *)((UINT8 *)pDrv->sccIram + addr);
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

#endif /* BSP_VERSION */

/*
 * Note: these have no meaning for this driver. They're provided only
 * for backwards compatibility with some BSPs, which expect these flags
 * to be defined.
 */

#define SCC_USR_RUNNING_FROM_ROM    0x00000001  /* inhibit zcopy mode */
#define SCC_USR_DUPLEX_HALF         0x00000000  /* Half duplex */
#define SCC_USR_DUPLEX_FULL         0x00000002  /* Full duplex */

#ifdef __cplusplus
}
#endif

#endif /* __INCm8260SccEndh */

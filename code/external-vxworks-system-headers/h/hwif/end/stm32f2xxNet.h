/* stm32f2xxNet.h - STM32F20x/STM32F21x network controller header file  */

/*
 * Copyright (c) 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01c,31jul12,rec  Move STM32F_DMAIER_INITVAL to code body
01b,12jul12,rec  update bit fields
01a,03apr12,rec  written
*/

#ifndef __INCstm32f2xxNeth
#define __INCstm32f2xxNeth

#ifdef __cplusplus
extern "C" {
#endif

/* MAC register definitions */

#define STM32F_MACCR            0x0000  /* MAC configuration register */
#define STM32F_MACCR_RE     0x00000004  /* Receiver enable */
#define STM32F_MACCR_TE     0x00000008  /* Transmitter enable */
#define STM32F_MACCR_DC     0x00000010  /* Deferral check */
#define STM32F_MACCR_BL1    0x00000060  /* Backoff limit 1 */
#define STM32F_MACCR_BL4    0x00000040  /* Backoff limit 4 */
#define STM32F_MACCR_BL8    0x00000020  /* Backoff limit 8 */
#define STM32F_MACCR_BL10   0x00000000  /* Backoff limit 10 */
#define STM32F_MACCR_BLMSK  0x00000060  /* Backoff limit mask */
#define STM32F_MACCR_APCS   0x00000080  /* Automatic PAD/CRC stipping */
#define STM32F_MACCR_RD     0x00000200  /* Retry disable */
#define STM32F_MACCR_IPCO   0x00000400  /* IPv4 checksum offload */
#define STM32F_MACCR_DM     0x00000800  /* Duplex mode */
#define STM32F_MACCR_LM     0x00001000  /* Loopback mode */
#define STM32F_MACCR_ROD    0x00002000  /* Receive own disable */
#define STM32F_MACCR_FES    0x00004000  /* Fast ethernet speed */
#define STM32F_MACCR_CSD    0x00010000  /* Carrier sense disable */
#define STM32F_MACCR_IFGMSK 0x000E0000  /* Interframe gap mask */
#define STM32F_MACCR_IFGSHFT        17  /* Interframe gap shift */
#define STM32F_MACCR_JD     0x00400000  /* Jabber disable */
#define STM32F_MACCR_WD     0x00800000  /* Watchdog disable */
#define STM32F_MACCR_CSTF   0x02000000  /* CRC stripping for type frames */

#define STM32F_MACFFR           0x0004  /* MAC frame filter register */
#define STM32F_MACFFR_PM    0x00000001  /* Promiscuous mode */
#define STM32F_MACFFR_HU    0x00000002  /* Hash unicast */
#define STM32F_MACFFR_HM    0x00000004  /* Hash multicast */
#define STM32F_MACFFR_DAIF  0x00000008  /* Dest address inverse filtering */
#define STM32F_MACFFR_PAM   0x00000010  /* Pass all multicast */
#define STM32F_MACFFR_BFD   0x00000020  /* Broadcast frames disable */
#define STM32F_MACFFR_PCFMSK 0x000000C0 /* Pass control frames mask */
#define STM32F_MACFFR_PCFSHFT        6  /* Pass control frames shift */
#define STM32F_MACFFR_SAIF  0x00000100  /* Source address inverse filtering */
#define STM32F_MACFFR_SAF   0x00000200  /* Source address filtering */
#define STM32F_MACFFR_HPF   0x00000400  /* Hash or perfect filter */
#define STM32F_MACFFR_RA    0x80000000  /* Receive all */

#define STM32F_MACHTHR          0x0008  /* MAC hash table high register */

#define STM32F_MACHTLR          0x000C  /* MAC hash table low register */

#define STM32F_MACMIIAR         0x0010  /* MAC MII address register */
#define STM32F_MACMIIARMB   0x00000001  /* MII busy */
#define STM32F_MACMIIARMW   0x00000002  /* MII write */
#define STM32F_MACMIIARCRMSK 0x0000001C /* Clock range mask */
#define STM32F_MACMIIARCRSHFT        2  /* Clock range shift */
#define STM32F_MACMIIARMRMSK 0x000007C0 /* MII register mask */
#define STM32F_MACMIIARMRSHFT        6  /* MII register shift */
#define STM32F_MACMIIARPAMSK 0x0000F800 /* PHY address mask */
#define STM32F_MACMIIARPASHFT       11  /* PHY address shift */
#define STM32F_MACMIIARMRVALIDMSK 0x1F  /* Max MII register number */
#define STM32F_MACMIIARPAVALIDMSK 0x1F  /* Max PHY address number */

#define STM32F_MACMIIDR         0x0014  /* MAC MII data register */
#define STM32F_MACMIIDRMSK  0x0000FFFF  /* MAC MII data register mask */

#define STM32F_MACFCR           0x0018  /* MAC flow control register */
#define STM32F_MACFCRFCB    0x00000001  /* Flow control busy/backpressure */
#define STM32F_MACFCRTFCE   0x00000002  /* Transmit flow control enable */
#define STM32F_MACFCRRFCE   0x00000004  /* Receive flow control enable */
#define STM32F_MACFCRUPFD   0x00000008  /* Unicast pause frame detect */
#define STM32F_MACFCRPLT0   0x00000000  /* Pause Low threshold 4 slots */
#define STM32F_MACFCRPLT1   0x00000010  /* Pause Low threshold 28 slots */
#define STM32F_MACFCRPLT2   0x00000020  /* Pause Low threshold 144 slots */
#define STM32F_MACFCRPLT3   0x00000030  /* Pause Low threshold 256 slots */
#define STM32F_MACFCRZQPD   0x00000080  /* Zero-quanta pause disable */
#define STM32F_MACFCRPTMSK  0xFFFF0000  /* Pause time mask */
#define STM32F_MACFCRPTSHFT         16  /* Pause time shift */

#define STM32F_MACVLANTR        0x001C  /* MAC VLAN tag register */
#define STM32F_MACVLANTIMSK 0x0000FFFF  /* Tag identifier for receive frames*/
#define STM32F_MACVLANTC    0x00010000  /* 12-bit tag comparison */

#define STM32F_MACWUFFR         0x0028  /* MAC wakeup frame fill register */

#define STM32F_MACPMTCSR        0x002C  /* MAC PMT control and status reg */
#define STM32F_MACPMTCRSPD  0x00000001  /* Power down */
#define STM32F_MACPMTCRSMPE 0x00000002  /* Magic packet enable */
#define STM32F_MACPMTCRWFE  0x00000004  /* Wakeup frame enable */
#define STM32F_MACPMTCRMPR  0x00000020  /* Magic packet receive */
#define STM32F_MACPMTCRWFR  0x00000040  /* Wakeup frame receive */
#define STM32F_MACPMTCRGU   0x00000200  /* Global unicast */
#define STM32F_MACPMTCRPR   0x80000000  /* Wakeup frame register ptr reset */

#define STM32F_MACDBGR          0x0034  /* MAC debug register */
#define STM32F_MACDBGRMMRPEA 0x00000001 /* MII receive protocol active */
#define STM32F_MACDBGRMSFRWCSMSK \
                            0x00000006  /* Small fifo status flags */
#define STM32F_MACDBGRRFWA  0x00000010  /* RCV fifo controller active */
#define STM32F_MACDBGRRFRCSMASK \
                            0x00000060  /* Rx FIFO read cont. status mask */
#define STM32F_MACDBGRRFRCSSHFT      5  /* Rx FIFO read cont. status mask */
#define STM32F_MACDBGRRFRCSIDLE \
                            0x00000000  /* Rx FIFO read controller idle */
#define STM32F_MACDBGRRFRCSREADING \
                            0x00000020  /* Rx FIFO read controller reading */
#define STM32F_MACDBGRRFRCRDSTAT \
                            0x00000040  /* Rx FIFO read cont. read status */
#define STM32F_MACDBGRRFRCFLUSH \
                            0x00000060  /* Rx FIFO read controller flushing */
#define STM32F_MACDBGRRFFLMSK \
                            0x00000300  /* Rx FIFO fill level mask */
#define STM32F_MACDBGRRFFLSHFT       8  /* Rx FIFO fill level shift */
#define STM32F_MACDBGRRFFLEMPTY \
                            0x00000000  /* Rx FIFO fill level empty */
#define STM32F_MACDBGRRFFLBDA \
                            0x00000100  /* Rx FIFO fill below de-active */
#define STM32F_MACDBGRRFFLADA \
                            0x00000200  /* Rx FIFO fill above de-active */
#define STM32F_MACDBGRRFFLFULL \
                            0x00000300  /* Rx FIFO fill full */
#define STM32F_MACDBGRMMTEA 0x00010000  /* MAC MII transmit engine active */
#define STM32F_MACDBGRMTFCSMSK \
                            0x00060000  /* MAC transmit frame cont. stat msk */
#define STM32F_MACDBGRMTFCSSHFT     17  /* MAC transmit frame cont. stat shft*/
#define STM32F_MACDBGRMTFCSIDLE \
                            0x00000000  /* MAC transmit frame cont. idle */
#define STM32F_MACDBGRMTFCSWAIT \
                            0x00020000  /* MAC transmit frame cont. waiting */
#define STM32F_MACDBGRMTFCSGEN \
                            0x00040000  /* MAC transmit frame cont. generatin*/
#define STM32F_MACDBGRMTFCSTRANS \
                            0x00060000  /* MAC transmit frame cont. transfer*/
#define STM32F_MACDBGRMTP   0x00080000  /* MAC transmit pause */
#define STM32F_MACDBGRTFRSMSK \
                            0x00300000  /* Tx FIFO read status mask */
#define STM32F_MACDBGRTFRSSHFT       20 /* Tx FIFO read status shift */
#define STM32F_MACDBGRTFRSIDLE \
                            0x00000000  /* Tx FIFO read status idle */
#define STM32F_MACDBGRTFRSREAD \
                            0x00100000  /* Tx FIFO read status reading */
#define STM32F_MACDBGRTFRSWAIT \
                            0x00200000  /* Tx FIFO read status waiting */
#define STM32F_MACDBGRTFRSWRITE \
                            0x00300000  /* Tx FIFO read status writing */
#define STM32F_MACDBGRTFWA  0x00400000  /* Tx FIFO write active */
#define STM32F_MACDBGRTFNE  0x01000000  /* Tx FIFO not empty */
#define STM32F_MACDBGRTFF   0x02000000  /* Tx FIFO full */

#define STM32F_MACSR            0x0038  /* MAC status register */
#define STM32F_MACSRPMTS    0x00000008  /* PMT status */
#define STM32F_MACSRMMCS    0x00000010  /* MMC status */
#define STM32F_MACSRMMCRS   0x00000020  /* Receive status */
#define STM32F_MACSRMMCTS   0x00000040  /* Transmit status */
#define STM32F_MACSRTSTS    0x00000200  /* Timestamp trigger status */

#define STM32F_MACIMR           0x003C  /* MAC Interrupt mask register */
#define STM32F_MACIMRPMTIM  0x00000008  /* PMT interrupt mask */
#define STM32F_MACIMRTSTIM  0x00000200  /* Timestamp trigger interrupt mask */
#define STM32F_MACIMR_INITVAL STM32F_MACIMRPMTIM /* power management wakeup*/

#define STM32F_MACA0HR          0x0040  /* MAC address 0 high register */
#define STM32F_MACA0LR          0x0044  /* MAC address 0 low register */
#define STM32F_MACA1HR          0x0048  /* MAC address 1 high register */
#define STM32F_MACA1LR          0x004C  /* MAC address 1 low register */
#define STM32F_MACA2HR          0x0050  /* MAC address 2 high register */
#define STM32F_MACA2LR          0x0054  /* MAC address 2 low register */
#define STM32F_MACA3HR          0x0058  /* MAC address 3 high register */
#define STM32F_MACA3LR          0x005C  /* MAC address 3 low register */
#define STM32F_MACA0HRMO    0x80000000  /* Must be 1 */
#define STM32F_MACAHRMSK    0x0000FFFF  /* MAC address high mask */
#define STM32F_MACAHMBC0MSK 0x01000000  /* MAC byte 0 mask control */
#define STM32F_MACAHMBC1MSK 0x02000000  /* MAC byte 1 mask control */
#define STM32F_MACAHMBC2MSK 0x04000000  /* MAC byte 2 mask control */
#define STM32F_MACAHMBC3MSK 0x08000000  /* MAC byte 3 mask control */
#define STM32F_MACAHMBC4MSK 0x10000000  /* MAC byte 4 mask control */
#define STM32F_MACAHMBC5MSK 0x20000000  /* MAC byte 5 mask control */
#define STM32F_MACAHRSA     0x40000000  /* MAC source address */
#define STM32F_MACAHRAE     0x80000000  /* MAC address enable */

/* MMC register definitions */

#define STM32F_MMCCR           0x0100  /* MMC control register */
#define STM32F_MMCCRCR     0x00000001  /* Counter reset */
#define STM32F_MMCCRCSR    0x00000002  /* Counter stop register */
#define STM32F_MMCCRROR    0x00000004  /* Reset on read */
#define STM32F_MMCCRMCF    0x00000008  /* MMC counter freeze */
#define STM32F_MMCCRMCP    0x00000010  /* MMC counter preset */
#define STM32F_MMCCRFHP    0x00000020  /* MMC counter full-half preset */

#define STM32F_MMCRIR          0x0104  /* MMC receive interrupt register */
#define STM32F_MMCRIMR         0x010C  /* MMC receive interrupt mask reg */
#define STM32F_MMCRIRFCES  0x00000020  /* Receive frames CRC error status */
#define STM32F_MMCRIRFAES  0x00000040  /* Receive frames align error status */
#define STM32F_MMCRIRGUFS  0x00020000  /* Receive good unicast frame status */
#define STM32F_MMCRIMR_INITVAL STM32F_MMCRIRGUFS

#define STM32F_MMCTIR          0x0108  /* MMC transmit interrupt register */
#define STM32F_MMCTIMR         0x0110  /* MMC transmit interrupt mask reg */
#define STM32F_MMCTITGFSCS 0x00004000  /* Trans good frame single collision */
#define STM32F_MMCTITGFMSCS 0x00008000 /* More TGFSCS */
#define STM32F_MMCTITGFS   0x00200000  /* Transmitted good frame status */
#define STM32F_MMCTIR_INITVAL STM32F_MMCTITGFS

#define STM32F_MMCTGFSCCR      0x014C  /* Trans good frame single col ctr */
#define STM32F_MMCTGFMSCCR     0x0150  /* TGF after more than a single col */
#define STM32F_MMCTGFCR        0x0168  /* MMC TGF counter register */
#define STM32F_MMCRFCECR       0x0194  /* MMC RCV frames w/CRC err count */
#define STM32F_MMCRFAECR       0x0198  /* MMC RCV frames w/align err count */
#define STM32F_MMCRGUFCR       0x01C4  /* MMC RCV good unicast count reg */

/*
 * PTP register definitions (not used at this time)
 */

/*
 * DMA register definitions
 */

#define STM32F_DMABMR           0x1000  /* DMA bus mode register register */
#define STM32F_DMABMRSR     0x00000001  /* Software reset */
#define STM32F_DMABMRDA     0x00000002  /* DMA arbitration */
#define STM32F_DMABMRDSLMSK 0x0000007C  /* Descriptor skip length mask */
#define STM32F_DMABMRDSLSHFT         2  /* Descriptor skip length shift */
#define STM32F_DMABMREDFE   0x00000080  /* Enhanced descriptor format enable */
#define STM32F_DMABMRPBLMSK 0x00003F00  /* Programmable burst length mask */
#define STM32F_DMABMRPBLSHFT         8  /* Programmable burst length shift */
#define STM32F_DMABMRPBL(arg) (arg << STM32F_DMABMRPBLSHFT)
#define STM32F_DMABMRRTPR0  0x00000000  /* Rx/Tx priority ratio 1:1 */
#define STM32F_DMABMRRTPR1  0x00004000  /* Rx/Tx priority ratio 2:1 */
#define STM32F_DMABMRRTPR2  0x00008000  /* Rx/Tx priority ratio 3:1 */
#define STM32F_DMABMRRTPR3  0x0000C000  /* Rx/Tx priority ratio 4:1 */
#define STM32F_DMABMRFB     0x00010000  /* Fixed burst */
#define STM32F_DMABMRRDPMSK 0x007E0000  /* Rx DMA PBL mask */
#define STM32F_DMABMRRDPSHFT        17  /* Rx DMA PBL shift */
#define STM32F_DMABMRRDP(arg) (arg << STM32F_DMABMRRDPSHFT)
#define STM32F_DMABMRUSP    0x00800000  /* Use separate PBL */
#define STM32F_DMABMRFPM    0x01000000  /* 4x PBL mode */
#define STM32F_DMABMRAAB    0x02000000  /* Adress-aligned beats */
#define STM32F_DMABMRMB     0x04000000  /* Mixed bursts */
#define STM32F_DMABMR_RESERVED_BITS \
                            0xF8000000

#define STM32F_DMATPDR          0x1004  /* DMA transmit poll demand register */
#define STM32F_DMARPDR          0x1008  /* DMA receive poll demand register */
#define STM32F_DMARDLAR         0x100C  /* DMA receive desc list adr register*/
#define STM32F_DMATDLAR         0x1010  /* DMA transmit desc list adr reg */

#define STM32F_DMASR            0x1014  /* DMA status register register */
#define STM32F_DMASRTS      0x00000001  /* Transmit status */
#define STM32F_DMASRTPSS    0x00000002  /* Transmitter process stopped status*/
#define STM32F_DMASRTBUS    0x00000004  /* Transmitter buffer unavail status */
#define STM32F_DMASRTJTS    0x00000008  /* Transmitter jabber timeout status */
#define STM32F_DMASRROS     0x00000010  /* Receiver overflow status */
#define STM32F_DMASRTUS     0x00000020  /* Transmitter underflow status */
#define STM32F_DMASRRS      0x00000040  /* Receive status */
#define STM32F_DMASRRBUS    0x00000080  /* Receive buffer unavailable */
#define STM32F_DMASRRPSS    0x00000100  /* Receiver process stopped */
#define STM32F_DMASRRWTS    0x00000200  /* Receive watchdog timeout status */
#define STM32F_DMASRETS     0x00000400  /* Early transmit status */
#define STM32F_DMASRFBES    0x00002000  /* Fatal bus error status */
#define STM32F_DMASRERS     0x00004000  /* Early receiver status */
#define STM32F_DMASRAIS     0x00008000  /* Abnormal interrupt summary */
#define STM32F_DMASRNIS     0x00010000  /* Normal interrupt summary */
#define STM32F_DMASRRPSMSK  0x000E0000  /* Receiver process state mask */
#define STM32F_DMASRRPSSHFT         17  /* Receiver process state shift */
#define STM32F_DMASRTPSMSK  0x00700000  /* Transmit process state mask */
#define STM32F_DMASRTPSSHFT         20  /* Transmit process state shift */
#define STM32F_DMASREBSMSK  0x03800000  /* Error bit status mask */
#define STM32F_DMASREBSSHFT         23  /* Error bit status shift */
#define STM32F_DMASRMMCS    0x08000000  /* MMC status */
#define STM32F_DMASRPMTS    0x10000000  /* PMT state */
#define STM32F_DMASRTSTS    0x20000000  /* Timestamp trigger status */
#define STM32F_DMASRMASK    0x0001E7FF  /* Status bits that can be cleared */

#define STM32F_DMAOMR           0x1018  /* DMA operation mode register */
#define STM32F_DMAOMRSR     0x00000002  /* Start receive */
#define STM32F_DMAOMROSF    0x00000004  /* Operate on second frame */
#define STM32F_DMAOMRRTC0   0x00000000  /* Receive threshold control 64 */
#define STM32F_DMAOMRRTC1   0x00000008  /* Receive threshold control 32 */
#define STM32F_DMAOMRRTC2   0x00000010  /* Receive threshold control 96 */
#define STM32F_DMAOMRRTC3   0x00000018  /* Receive threshold control 128 */
#define STM32F_DMAOMRRMSK   0x00000018  /* Receive threshold control mask */
#define STM32F_DMAOMRFUGF   0x00000040  /* Forward undersized good frames */
#define STM32F_DMAOMRFEF    0x00000080  /* Forward error frames */
#define STM32F_DMAOMRST     0x00002000  /* Start transmission */
#define STM32F_DMAOMRTT64   0x00000000  /* Transmitter threshold control 64 */
#define STM32F_DMAOMRTT128  0x00004000  /* Transmitter threshold control 128 */
#define STM32F_DMAOMRTT192  0x00008000  /* Transmitter threshold control 192 */
#define STM32F_DMAOMRTT256  0x0000C000  /* Transmitter threshold control 256 */
#define STM32F_DMAOMRTT40   0x00010000  /* Transmitter threshold control 40 */
#define STM32F_DMAOMRTT32   0x00014000  /* Transmitter threshold control 32 */
#define STM32F_DMAOMRTT24   0x00018000  /* Transmitter threshold control 24 */
#define STM32F_DMAOMRTT16   0x0001C000  /* Transmitter threshold control 16 */
#define STM32F_DMAOMR_RESERVED_BITS \
                            0xF0CE1F00

#define STM32F_DMAOMRTTCMSK 0x0001C000  /* Transmitter threshold control mask*/
#define STM32F_DMAOMRFTF    0x00100000  /* Flush transmitter fifo */
#define STM32F_DMAOMRTSF    0x00200000  /* Transmit store and forward */
#define STM32F_DMAOMRDFRF   0x01000000  /* Disable flushing of receiv frames */
#define STM32F_DMAOMRRSF    0x02000000  /* Receive store and forward */
#define STM32F_DMAOMRDTCEFD 0x04000000  /* Dropping of TCP/IP checksum errs */

#define STM32F_DMAIER           0x101C  /* DMA interrupt enable regiser */
#define STM32F_DMAIERTIE    0x00000001  /* Transmit interrupt enable */
#define STM32F_DMAIERTPSIE  0x00000002  /* Transmit process stopped */
#define STM32F_DMAIERTBUIE  0x00000004  /* Transmit buffer unavailable */
#define STM32F_DMAIERTJTIE  0x00000008  /* Transmit jabber timeout */
#define STM32F_DMAIERROIE   0x00000010  /* Receiver overflow */
#define STM32F_DMAIERTUIE   0x00000020  /* Transmit underflow */
#define STM32F_DMAIERRIE    0x00000040  /* Receive interrupt enable */
#define STM32F_DMAIERRBUIE  0x00000080  /* Receive buffer unavailable */
#define STM32F_DMAIERRPSIE  0x00000100  /* Receive processor stopped */
#define STM32F_DMAIERRWTIE  0x00000200  /* Receive watchdog timeout */
#define STM32F_DMAIERETIE   0x00000400  /* Early transmit interrupt enable */
#define STM32F_DMAIERFBEIE  0x00002000  /* Fatal bus error */
#define STM32F_DMAIERERIE   0x00004000  /* Early receive */
#define STM32F_DMAIERAISE   0x00008000  /* Abnormal interrupt summary */
#define STM32F_DMAIERNISE   0x00010000  /* Normal interrupt summary */

#define STM32F_DMAMFBOCR        0x1020  /* DMA missed frame and overflow reg */
#define STM32F_DMAMFBOCRMFCMSAK  0x0000FFFF /* Missed frame count mask */
#define STM32F_DMAMFBOCROMFC     0x00010000 /* Missed frame overflow */
#define STM32F_DMAMFBOCRMFAMSK  0x0FFE0000  /* Missed frames by appl mask */
#define STM32F_DMAMFBOCRMFASHFT         17  /* Missed frames by appl shift */
#define STM32F_DMAMFBOCROFOC    0x10000000  /* Fifo counter overflow */

#define STM32F_DMARSWTR         0x1024  /* Receive status watchdog timer reg */
#define STM32F_DMACHTDR         0x1048  /* Current host transmit descript reg*/
#define STM32F_DMACHRDR         0x104C  /* Current host receive descript reg */
#define STM32F_DMACHTBAR        0x1050  /* Current host trans buf reg addr */
#define STM32F_DMACHRBAR        0x1054  /* Current host rcv buf reg addr */

#ifdef __cplusplus
}
#endif

#endif /* __INCstm32f2xxNeth */

/* fslSoc913x.h - Freescale BSC913X SOC header */

/*
 * Copyright (c) 2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01a,30may13,ylu  Created.
*/

/*
 * This file contains I/O addresses and related constants for the
 * FreeScale QorIQ BSC913X series platform.
 */

#ifndef __INCfslsoc913xh
#define __INCfslsoc913xh

#ifdef __cplusplus
    extern "C" {
#endif /* __cplusplus */

#ifdef  _ASMLANGUAGE
#   define CAST(x)
#else /* _ASMLANGUAGE */
typedef volatile UCHAR  VCHAR;      /* shorthand for volatile UCHAR */
typedef volatile INT32  VINT32;     /* volatile unsigned word */
typedef volatile INT16  VINT16;     /* volatile unsigned halfword */
typedef volatile INT8   VINT8;      /* volatile unsigned byte */
typedef volatile UINT32 VUINT32;    /* volatile unsigned word */
typedef volatile UINT16 VUINT16;    /* volatile unsigned halfword */
typedef volatile UINT8  VUINT8;     /* volatile unsigned byte */
#   define CAST(x) (x)
#endif  /* _ASMLANGUAGE */

/* Base Address of Memory Mapped Registers */

#define MP_MAGIC_RBV            0xfeedfeed
#define MP_MAGIC_CACHE_FLUSHED  0xD07ED07E

#define M85XX_ALTCBAR(base)     (CAST(VUINT32 *)((base) + 0x08))
#define M85XX_ALTCAR(base)      (CAST(VUINT32 *)((base) + 0x10))
#define M85XX_BPTR(base)        (CAST(VUINT32 *)((base) + 0x20))

#define BPTR_EN                 0x80000000
#define CPU1CHECK               (vxHid1Get() & 0x1)

/*
 * Shift 36bit physical address to 24 bit ie lowest 4k predefined as 0xffc
 * We only every use 32 bit for this so shift by 8 not 12
 */

#define BPTR_BOOT_PAGE_SHIFT    12

/* PA CCSBAR */

#define CCSBAR_RESET            0xff700000
#define CCSBAR                  0xff700000
#define CCSR_SIZE               0x00100000

/* SC3850 CCSBAR */

#define DSP_CCSBAR_RESET        0xff600000
#define DSP_CCSBAR              0xff600000
#define CCSR_SIZE               0x00100000

/* Vectors */
/*
 * Extra Duarts are available in Simics.  This allows for each CPU in
 * an AMP system to have its own dedicated console port.  Note that because
 * these are duarts, there are two serial devices available for each interrupt
 * line.  But since two CPUs cannot share a device on the same interrupt, this
 * requires that we create six additional duarts.  To keep things consistent,
 * these are set up like the two stock duarts.  Thus, twelve additional
 * serial ports are created, potentially allowing for two ports to be
 * dedicated to each CPU.
 */

/* EPIC defines */

#define EPIC_EX_IRQ_NUM                 12
#define EPIC_IN_IRQ_NUM                 64
#define EPIC_GT_IRQ_NUM                 4
#define EPIC_MSG_IRQ_NUM                8
#define EPIC_SMSG_IRQ_NUM               8
#define EPIC_IPI_IRQ_NUM                4
#define EPIC_EX_REG_BASE                0x50000
#define EPIC_IN_REG_BASE                0x50200
#define EPIC_GT_A_REG_BASE              0x41120
#define EPIC_GT_B_REG_BASE              0x42120
#define EPIC_MSG_REG_BASE               0x51600
#define EPIC_SMSG_REG_BASE              0x51c00
#define EPIC_IPI_REG_BASE               0x410a0
#define EPIC_EX_REG_INTERVAL            0x20
#define EPIC_IN_REG_INTERVAL            0x20
#define EPIC_GT_REG_INTERVAL            0x40
#define EPIC_MSG_REG_INTERVAL           0x20
#define EPIC_SMSG_REG_INTERVAL          0x20
#define EPIC_IPI_REG_INTERVAL           0x10

/* Interrupt vectors */

#undef EPIC_USB1_INT_VEC               
#undef EPIC_USB1_INT_NUM               
#define EPIC_USB1_INT_NUM               24
#define EPIC_USB1_INT_VEC               (EPIC_USB1_INT_NUM + \
                                        EPIC_VEC_IN_IRQ0)

#undef EPIC_DUART_INT_VEC
#undef EPIC_DUART_INT_NUM
#define EPIC_DUART_INT_NUM              0x2              
#define EPIC_DUART_INT_VEC              ( EPIC_DUART_INT_NUM + \
                                         EPIC_VEC_IN_IRQ0 ) 
#undef EPIC_I2C_INT_NUM
#undef EPIC_I2C_INT_VEC
#define EPIC_I2C_INT_NUM                0x1             
#define EPIC_I2C_INT_VEC                ( EPIC_I2C_INT_NUM + \
                                         EPIC_VEC_IN_IRQ0 ) 
#undef EPIC_TSEC1TX_INT_NUM
#undef EPIC_TSEC1TX_INT_VEC
#define EPIC_TSEC1TX_INT_NUM            10 
#define EPIC_TSEC1TX_INT_VEC            ( EPIC_TSEC1TX_INT_NUM + \
                                         EPIC_VEC_IN_IRQ0 )  

#undef EPIC_TSEC1RX_INT_NUM           
#undef EPIC_TSEC1RX_INT_VEC           
#define EPIC_TSEC1RX_INT_NUM            11   
#define EPIC_TSEC1RX_INT_VEC            ( EPIC_TSEC1RX_INT_NUM + \
                                         EPIC_VEC_IN_IRQ0 )

#undef EPIC_TSEC1ERR_INT_NUM
#undef EPIC_TSEC1ERR_INT_VEC
#define EPIC_TSEC1ERR_INT_NUM           12 
#define EPIC_TSEC1ERR_INT_VEC           ( EPIC_TSEC1ERR_INT_NUM + \
                                         EPIC_VEC_IN_IRQ0 ) 

#undef EPIC_TSEC2TX_INT_NUM           
#undef EPIC_TSEC2TX_INT_VEC          
#define EPIC_TSEC2TX_INT_NUM            17
#define EPIC_TSEC2TX_INT_VEC            ( EPIC_TSEC2TX_INT_NUM + \
                                         EPIC_VEC_IN_IRQ0 ) 

#undef EPIC_TSEC2RX_INT_NUM             
#undef EPIC_TSEC2RX_INT_VEC             
#define EPIC_TSEC2RX_INT_NUM            18  
#define EPIC_TSEC2RX_INT_VEC            ( EPIC_TSEC2RX_INT_NUM + \
                                         EPIC_VEC_IN_IRQ0 ) 

#undef EPIC_TSEC2ERR_INT_NUM          
#undef EPIC_TSEC2ERR_INT_VEC          
#define EPIC_TSEC2ERR_INT_NUM           19
#define EPIC_TSEC2ERR_INT_VEC           ( EPIC_TSEC2ERR_INT_NUM + \
                                         EPIC_VEC_IN_IRQ0 )

#undef EPIC_DMA1_CHAN0_INT_NUM
#undef EPIC_DMA1_CHAN0_INT_VEC
#define EPIC_DMA1_CHAN0_INT_NUM         46
#define EPIC_DMA1_CHAN0_INT_VEC         (EPIC_DMA1_CHAN0_INT_NUM +  \
                                         EPIC_VEC_IN_IRQ0)

#define EPIC_DMA1_CHAN1_INT_NUM         47
#define EPIC_DMA1_CHAN1_INT_VEC         (EPIC_DMA1_CHAN1_INT_NUM +  \
                                         EPIC_VEC_IN_IRQ0)
#define EPIC_DMA1_CHAN2_INT_NUM         48
#define EPIC_DMA1_CHAN2_INT_VEC         (EPIC_DMA1_CHAN2_INT_NUM +  \
                                         EPIC_VEC_IN_IRQ0)
#define EPIC_DMA1_CHAN3_INT_NUM         49
#define EPIC_DMA1_CHAN3_INT_VEC         (EPIC_DMA1_CHAN3_INT_NUM +  \
                                         EPIC_VEC_IN_IRQ0)

#undef EPIC_USB_INT_NUM
#undef EPIC_USB_INT_VEC
#define EPIC_USB_INT_NUM                24
#define EPIC_USB_INT_VEC                (EPIC_USB_INT_NUM + \
                                         EPIC_VEC_IN_IRQ0)

#undef EPIC_SPI_INT_NUM
#undef EPIC_SPI_INT_VEC
#define EPIC_SPI_INT_NUM                6
#define EPIC_SPI_INT_VEC                (EPIC_SPI_INT_NUM + \
                                         EPIC_VEC_IN_IRQ0)

#undef EPIC_SPI1_INT_NUM
#undef EPIC_SPI1_INT_VEC
#define EPIC_SPI1_INT_NUM               7
#define EPIC_SPI1_INT_VEC               (EPIC_SPI_INT_NUM + \
                                         EPIC_VEC_IN_IRQ0)

#undef EPIC_DMA2_CHAN0_INT_NUM
#undef EPIC_DMA2_CHAN0_INT_VEC
#define EPIC_DMA2_CHAN0_INT_NUM         50
#define EPIC_DMA2_CHAN0_INT_VEC         (EPIC_DMA2_CHAN0_INT_NUM +  \
                                         EPIC_VEC_IN_IRQ0)

#undef EPIC_DMA2_CHAN1_INT_NUM
#undef EPIC_DMA2_CHAN1_INT_VEC
#define EPIC_DMA2_CHAN1_INT_NUM         51
#define EPIC_DMA2_CHAN1_INT_VEC         (EPIC_DMA2_CHAN1_INT_NUM +  \
                                         EPIC_VEC_IN_IRQ0)

#undef EPIC_DMA2_CHAN2_INT_NUM
#undef EPIC_DMA2_CHAN2_INT_VEC
#define EPIC_DMA2_CHAN2_INT_NUM         52
#define EPIC_DMA2_CHAN2_INT_VEC         (EPIC_DMA2_CHAN2_INT_NUM +  \
                                         EPIC_VEC_IN_IRQ0)

#undef EPIC_DMA2_CHAN3_INT_NUM
#undef EPIC_DMA2_CHAN3_INT_VEC
#define EPIC_DMA2_CHAN3_INT_NUM         53
#define EPIC_DMA2_CHAN3_INT_VEC         (EPIC_DMA2_CHAN3_INT_NUM +  \
                                         EPIC_VEC_IN_IRQ0)

#undef EPIC_I2C_INT_NUM
#undef EPIC_I2C_INT_VEC
#define EPIC_I2C_INT_NUM                1
#define EPIC_I2C_INT_VEC                (EPIC_I2C_INT_NUM + \
                                         EPIC_VEC_IN_IRQ0)

#undef EPIC_SDHC_INT_NUM
#undef EPIC_SDHC_INT_VEC
#define EPIC_SDHC_INT_NUM               25
#define EPIC_SDHC_INT_VEC               (EPIC_SDHC_INT_NUM + \
                                         EPIC_VEC_IN_IRQ0)

#undef EPIC_SEC_INT_NUM
#undef EPIC_SEC_INT_VEC
#define EPIC_SEC_INT_NUM                41
#define EPIC_SEC_INT_VEC                (EPIC_SEC_INT_NUM + \
                                         EPIC_VEC_IN_IRQ0)

/* OpenPIC timer vectors */

#define OPENPIC_TIMERA0_INT_VEC         0x4C
#define OPENPIC_TIMERA1_INT_VEC         0x4D
#define OPENPIC_TIMERA2_INT_VEC         0x4E
#define OPENPIC_TIMERA3_INT_VEC         0x4F
#define OPENPIC_TIMERB0_INT_VEC         0x50
#define OPENPIC_TIMERB1_INT_VEC         0x51
#define OPENPIC_TIMERB2_INT_VEC         0x52
#define OPENPIC_TIMERB3_INT_VEC         0x53

/* PCIe */

/* PCI Express Host Controller */
        
/* ATMU register defines */
        
#define PCI_WINDOW_ENABLE_BIT           0x80000000
#define PCI_SNOOP_ENABLE                0x40000000
#define PCI_PREFETCHABLE                0x20000000
        
/* outbound window attributes */
        
#define PCI_OUT_ATTR_RTT_MEM            0x00040000
#define PCI_OUT_ATTR_RTT_IO             0x00080000
#define PCI_OUT_ATTR_WTT_MEM            0x00004000
#define PCI_OUT_ATTR_WTT_IO             0x00008000
        
#define PCI_ATTR_WS_4K                  0x0000000B
#define PCI_ATTR_WS_8K                  0x0000000C
#define PCI_ATTR_WS_16K                 0x0000000D
#define PCI_ATTR_WS_32K                 0x0000000E
#define PCI_ATTR_WS_64K                 0x0000000F
#define PCI_ATTR_WS_128K                0x00000010
#define PCI_ATTR_WS_256K                0x00000011
#define PCI_ATTR_WS_512K                0x00000012
#define PCI_ATTR_WS_1M                  0x00000013
#define PCI_ATTR_WS_2M                  0x00000014
#define PCI_ATTR_WS_4M                  0x00000015
#define PCI_ATTR_WS_8M                  0x00000016
#define PCI_ATTR_WS_16M                 0x00000017
#define PCI_ATTR_WS_32M                 0x00000018
#define PCI_ATTR_WS_64M                 0x00000019
#define PCI_ATTR_WS_128M                0x0000001A
#define PCI_ATTR_WS_256M                0x0000001B
#define PCI_ATTR_WS_512M                0x0000001C
#define PCI_ATTR_WS_1G                  0x0000001D
#define PCI_ATTR_WS_2G                  0x0000001E
#define PCI_ATTR_WS_4G                  0x0000001F
#define PCI_ATTR_WS_8G                  0x00000020
#define PCI_ATTR_WS_16G                 0x00000021
#define PCI_ATTR_WS_32G                 0x00000022
#define PCI_ATTR_WS_64G                 0x00000023

/* Inbound window attributes */

#define PCI_IN_ATTR_TGI_LM                                  0x00000000
#define PCI_IN_ATTR_RTT_LM_READ_NO_SNOOP                    0x00040000
#define PCI_IN_ATTR_RTT_LM_READ_SNOOP                       0x00050000
#define PCI_IN_ATTR_RTT_LM_READ_UNLOCK_L2_CACHE_LINE        0x00070000
#define PCI_IN_ATTR_RTT_LM_WRITE_NO_SNOOP                   0x00004000
#define PCI_IN_ATTR_RTT_LM_WRITE_SNOOP                      0x00005000
#define PCI_IN_ATTR_RTT_LM_WRITE_ALLOC_L2_CACHE_LINE        0x00006000
#define PCI_IN_ATTR_RTT_LM_WRITE_ALLOC_LOCK_L2_CACHE_LINE   0x00007000

/* Local Access Windows Regster Offsets from CCSBAR */

#define  M85XX_LAWBAR0(base)    (CAST(VUINT32 *)((base) + 0xc08))
#define  M85XX_LAWAR0(base)     (CAST(VUINT32 *)((base) + 0xc10))

#define  M85XX_LAWBAR1(base)    (CAST(VUINT32 *)((base) + 0xc28))
#define  M85XX_LAWAR1(base)     (CAST(VUINT32 *)((base) + 0xc30))

#define  M85XX_LAWBAR2(base)    (CAST(VUINT32 *)((base) + 0xc48))
#define  M85XX_LAWAR2(base)     (CAST(VUINT32 *)((base) + 0xc50))

#define  M85XX_LAWBAR3(base)    (CAST(VUINT32 *)((base) + 0xc68))
#define  M85XX_LAWAR3(base)     (CAST(VUINT32 *)((base) + 0xc70))

#define  M85XX_LAWBAR4(base)    (CAST(VUINT32 *)((base) + 0xc88))
#define  M85XX_LAWAR4(base)     (CAST(VUINT32 *)((base) + 0xc90))

#define  M85XX_LAWBAR5(base)    (CAST(VUINT32 *)((base) + 0xca8))
#define  M85XX_LAWAR5(base)     (CAST(VUINT32 *)((base) + 0xcb0))

#define  M85XX_LAWBAR6(base)    (CAST(VUINT32 *)((base) + 0xcc8))
#define  M85XX_LAWAR6(base)     (CAST(VUINT32 *)((base) + 0xcd0))

#define  M85XX_LAWBAR7(base)    (CAST(VUINT32 *)((base) + 0xce8))
#define  M85XX_LAWAR7(base)     (CAST(VUINT32 *)((base) + 0xcf0))

#define  M85XX_LAWBAR8(base)    (CAST(VUINT32 *)((base) + 0xd08))
#define  M85XX_LAWAR8(base)     (CAST(VUINT32 *)((base) + 0xd10))

#define  M85XX_LAWBAR9(base)    (CAST(VUINT32 *)((base) + 0xd28))
#define  M85XX_LAWAR9(base)     (CAST(VUINT32 *)((base) + 0xd30))

#define  M85XX_LAWBAR10(base)   (CAST(VUINT32 *)((base) + 0xd48))
#define  M85XX_LAWAR10(base)    (CAST(VUINT32 *)((base) + 0xd50))

#define  M85XX_LAWBAR11(base)   (CAST(VUINT32 *)((base) + 0xd68))
#define  M85XX_LAWAR11(base)    (CAST(VUINT32 *)((base) + 0xd70))

#define  M85XX_LAW_CNT          12
#define  M85XX_LAW_SIZE         0x20
#define  LAWBAR_ADRS_SHIFT      12

#define  LAWAR_ENABLE           0x80000000
#define  LAWAR_TGTIF_PCIEX2     0x00200000
#define  LAWAR_TGTIF_LBC        0x00400000
#define  LAWAR_TGTIF_RAPIDIO    0x00C00000
#define  LAWAR_TGTIF_RAPIDIO2   0x00D00000
#define  LAWAR_TGTIF_DDRSDRAM   0x00F00000

#define  LAWAR_TGTIF_M3         0x00D00000
#define  LAWAR_TGTIF_M2         0x00300000
#define  LAWAR_TGTIF            0x01F00000 /* Target ID */

#define QORIQ_TGTID_PCIE1       0x02    /* PCI Express1 */
#define QORIQ_TGTID_PCIE2       0x01    /* PCI Express2 */
#define QORIQ_TGTID_PCIE3       0x03    /* PCI Express3 */    

/* LAWAR SIZE Settings */

#define  LAWAR_SIZE_4KB         0x0000000B
#define  LAWAR_SIZE_8KB         0x0000000C
#define  LAWAR_SIZE_16KB        0x0000000D
#define  LAWAR_SIZE_32KB        0x0000000E
#define  LAWAR_SIZE_64KB        0x0000000F
#define  LAWAR_SIZE_128KB       0x00000010
#define  LAWAR_SIZE_256KB       0x00000011
#define  LAWAR_SIZE_512KB       0x00000012
#define  LAWAR_SIZE_1MB         0x00000013
#define  LAWAR_SIZE_2MB         0x00000014
#define  LAWAR_SIZE_4MB         0x00000015
#define  LAWAR_SIZE_8MB         0x00000016
#define  LAWAR_SIZE_16MB        0x00000017
#define  LAWAR_SIZE_32MB        0x00000018
#define  LAWAR_SIZE_64MB        0x00000019
#define  LAWAR_SIZE_128MB       0x0000001A
#define  LAWAR_SIZE_256MB       0x0000001B
#define  LAWAR_SIZE_512MB       0x0000001C
#define  LAWAR_SIZE_1GB         0x0000001D
#define  LAWAR_SIZE_2GB         0x0000001E

/* Integrated Flash Controller (IFC) Registers */

#define IFC                     (CCSBAR + IFC_OFFSET)
#define IFC_OFFSET              0x1E000
 
#define IFC_CSPR0               0x010
#define IFC_CSPR1               0x01C
#define IFC_CSPR2               0x028
#define IFC_CSPR3               0x034
#define IFC_AMASK0              0x0A0
#define IFC_AMASK1              0x0AC
#define IFC_AMASK2              0x0B8
#define IFC_AMASK3              0x0C4
#define IFC_CSOR0               0x130
#define IFC_CSOR1               0x13C
#define IFC_CSOR2               0x148
#define IFC_CSOR3               0x154
#define IFC_FTIM0_CS0           0x1C0
#define IFC_FTIM1_CS0           0x1C4
#define IFC_FTIM2_CS0           0x1C8
#define IFC_FTIM3_CS0           0x1CC
#define IFC_FTIM0_CS1           0x1F0
#define IFC_FTIM1_CS1           0x1F4
#define IFC_FTIM2_CS1           0x1F8
#define IFC_FTIM3_CS1           0x1FC
#define IFC_FTIM0_CS2           0x220
#define IFC_FTIM1_CS2           0x224
#define IFC_FTIM2_CS2           0x228 
#define IFC_FTIM3_CS2           0x22C 
#define IFC_FTIM0_CS3           0x250 
#define IFC_FTIM1_CS3           0x254 
#define IFC_FTIM2_CS3           0x258 
#define IFC_FTIM3_CS3           0x25C 
#define IFC_GCR                 0x40C 

/* DDR */
/* Offsets for DDR registers */

#define DDR1_OFFSET             0x2000
#define DDR2_OFFSET             0x10000   
#define DDRBA                  (CCSBAR | DDR1_OFFSET)

#define DDR1_BASE              (CCSBAR | DDR1_OFFSET)
#define DDR2_BASE              (DSP_CCSBAR | DDR2_OFFSET)   

#define CS0_BNDS                0x000
#define CS1_BNDS                0x008
#define CS2_BNDS                0x010
#define CS3_BNDS                0x018
#define CS0_CONFIG              0x080
#define CS1_CONFIG              0x084
#define CS2_CONFIG              0x088
#define CS3_CONFIG              0x08C
#define CS0_CONFIG_2            0x0c0
#define CS1_CONFIG_2            0x0c4
#define CS2_CONFIG_2            0x0c8
#define CS3_CONFIG_2            0x0CC
#define TIMING_CFG_3            0x100
#define TIMING_CFG_0            0x104
#define TIMING_CFG_1            0x108
#define TIMING_CFG_2            0x10C
#define DDR_SDRAM_CFG           0x110
#define DDR_SDRAM_CFG_2         0x114
#define DDR_SDRAM_MODE_CFG      0x118
#define DDR_SDRAM_MODE_CFG_2    0x11c
#define DDR_SDRAM_MD_CNTL       0x120
#define DDR_SDRAM_INTERVAL      0x124
#define DDR_DATA_INIT           0x128
#define DDR_SDRAM_CLK_CTRL      0x130
#define DDR_INIT_ADDR           0x148
#define DDR_INIT_EXT_ADDRESS    0x14C
#define TIMING_CFG_4            0x160
#define TIMING_CFG_5            0x164
#define DDR_DDR_ZQ_CNTL         0x170
#define DDR_DDR_WRLVL_CNTL      0x174
#define DDR_DDRDSR_1            0xB20
#define DDR_DDRDSR_2            0xB24
#define DDR_DDRCDR_1            0xB28
#define DDR_DDRCDR_2            0xB2C
#define DDR_DDR_IP_REV1         0xBF8
#define DDR_DDR_IP_REV2         0xBFC
#define DATA_ERR_INJECT_HI      0xE00
#define DATA_ERR_INJECT_LO      0xE04
#define ECC_ERR_INJECT          0xE08
#define CAPTURE_DATA_HI         0xE20
#define CAPTURE_DATA_LO         0xE24
#define CAPTURE_ECC             0xE28
#define ERR_DETECT              0xE40
#define ERR_DISABLE             0xE44
#define ERR_INT_EN              0xE48
#define CAPTURE_ATTRIBUTES      0xE4c
#define CAPTURE_ADDRESS         0xE50
#define ERR_SBE                 0xE58

#define DDR_IO_OVCR             0x000E0F24

/* DMA */

#define DMA1_REGBASE            (CCSBAR + 0x21100)
#define DMA_CHAN_OFFSET         0x80
#define DMA_CHAN_NUM            4

/* I2C */

#define I2C_BUS1_BASE           (CCSBAR + 0x3000)
#define I2C_BUS2_BASE           (CCSBAR + 0x3100)

/* USB */

#define USB1_BASE               (CCSBAR + 0x22000)
#define USB2_BASE               (CCSBAR + 0x23000)

/* eSPI */

#define SPI_REG_BASE            (CCSBAR + 0x7000)
#define SPI1_REG_BASE           (CCSBAR + 0x6000)

/* ETSEC */

#define ETSEC0_GROUP0_BASE      (CCSBAR + 0xB0000)
#define ETSEC1_GROUP0_BASE      (CCSBAR + 0xB1000)
#define ETSEC2_GROUP0_BASE      (CCSBAR + 0xB2000)

/* MDIO */

#define ETSEC0_MDIO_BASE        (CCSBAR + 0x24000)
#define ETSEC1_MDIO_BASE        (CCSBAR + 0x25000)
#define ETSEC2_MDIO_BASE        (CCSBAR + 0x26000)

/* UART */

#define UART0_BASE              (CCSBAR + 0x4500)
#define UART1_BASE              (CCSBAR + 0x4600)
#define DUART_REG_ADDR_INTERVAL 1

/* TIMER */

#define T4_OPENPIC_TIMER1_BASE  (CCSBAR + 0x0410F0)
#define T4_OPENPIC_TIMER2_BASE  (CCSBAR + 0x0420F0)

/* SDHC */

#define SDHC_BASE               (CCSBAR + 0x2E000)
#define SD_DATA                 0x80000000
#define SDHC_CD                 0x40000000
#define SDHC_WP                 0x20000000

/* GPIO Registers */

#define GPIO_BASE               (CCSBAR + 0xF000)
#define GPDIR                   (GPIO_BASE + 0xC00)
#define GPODR                   (GPIO_BASE + 0xC04)
#define GPDAT                   (GPIO_BASE + 0xC08)
#define GPIER                   (GPIO_BASE + 0xC0C)
#define GPIMR                   (GPIO_BASE + 0xC10)
#define GPICR                   (GPIO_BASE + 0xC14)

/* ECM Registers */

#define ECM_OFFSET              0x1000
#define ECMBA                   (CCSBAR + ECM_OFFSET)

#define EEB_ABCR(base)          (CAST(VUINT32 *)((base) + ECM_OFFSET + 0x0))
#define EEB_DBCR(base)          (CAST(VUINT32 *)((base) + ECM_OFFSET + 0x8))
#define EEB_PCR(base)           (CAST(VUINT32 *)((base) + ECM_OFFSET + 0x10))
#define EEB_REV1(base)          (CAST(VUINT32 *)((base) + ECM_OFFSET + 0xBF8))
#define EEB_REV2(base)          (CAST(VUINT32 *)((base) + ECM_OFFSET + 0xBFC))
#define EEB_EDR(base)           (CAST(VUINT32 *)((base) + ECM_OFFSET + 0xE00))
#define EEB_EER(base)           (CAST(VUINT32 *)((base) + ECM_OFFSET + 0xE08))
#define EEB_EATR(base)          (CAST(VUINT32 *)((base) + ECM_OFFSET + 0xE0C))
#define EEB_ELADR(base)         (CAST(VUINT32 *)((base) + ECM_OFFSET + 0xE10))
#define EEB_EHADR(base)         (CAST(VUINT32 *)((base) + ECM_OFFSET + 0xE14))

#define EEB_PCR_CORE1_ENABLE    0x02000000
#define EEB_PCR_CORE0_ENABLE    0x01000000

/* EHCI registers */

#define EHCI_CAPLENGTH(base)        ((base) + 0x00100)

#define EHCI_BURSTSIZE(base)        ((base) + 0x00160)
#define EHCI_TXTTFILLTUNING_L(base) ((base) + 0x00164)
#define EHCI_TXTTFILLTUNING_H(base) ((base) + 0x00168)
#define EHCI_CONFIGFLAG(base)       ((base) + 0x00180)
#define EHCI_PORTSC(base)           ((base) + 0x00184)
#define EHCI_USBMODE(base)          ((base) + 0x001a8)

#define EHCI_SNOOP1(base)           ((base) + 0x00400)
#define EHCI_SNOOP2(base)           ((base) + 0x00404)
#define EHCI_AGE_CNT_THRESH(base)   ((base) + 0x00408)
#define EHCI_PRI_CTRL(base)         ((base) + 0x0040c)
#define EHCI_SI_CTRL(base)          ((base) + 0x00410)
#define EHCI_CONTROL(base)          ((base) + 0x00500)

#define EHCI_USBMODE_IDLE           0x00000000
#define EHCI_USBMODE_DEVICE         0x00000002
#define EHCI_USBMODE_HOST           0x00000003

#define EHCI_PORTSC_ULPI            0x80000000

#define EHCI_SNOOP_SIZE_4K          0x0000000B
#define EHCI_SNOOP_SIZE_8K          0x0000000C
#define EHCI_SNOOP_SIZE_16K         0x0000000D
#define EHCI_SNOOP_SIZE_32K         0x0000000E
#define EHCI_SNOOP_SIZE_64K         0x0000000F
#define EHCI_SNOOP_SIZE_128K        0x00000010
#define EHCI_SNOOP_SIZE_256K        0x00000011
#define EHCI_SNOOP_SIZE_512K        0x00000012
#define EHCI_SNOOP_SIZE_1M          0x00000013
#define EHCI_SNOOP_SIZE_2M          0x00000014
#define EHCI_SNOOP_SIZE_4M          0x00000015
#define EHCI_SNOOP_SIZE_8M          0x00000016
#define EHCI_SNOOP_SIZE_16M         0x00000017
#define EHCI_SNOOP_SIZE_32M         0x00000018
#define EHCI_SNOOP_SIZE_64M         0x00000019
#define EHCI_SNOOP_SIZE_128M        0x0000001A
#define EHCI_SNOOP_SIZE_256M        0x0000001B
#define EHCI_SNOOP_SIZE_512M        0x0000001C
#define EHCI_SNOOP_SIZE_1G          0x0000001D
#define EHCI_SNOOP_SIZE_2G          0x0000001E

#ifdef INCLUDE_AMP
#   define EHCI_SNOOP_SIZE          EHCI_SNOOP_SIZE_512M
#else /* INCLUDE_AMP */
#   define EHCI_SNOOP_SIZE          EHCI_SNOOP_SIZE_1G
#endif /* INCLUDE_AMP */

#define EHCI_CONTROL_USB_EN         0x00000004

#ifdef __cplusplus
    }
#endif /* __cplusplus */

#endif /* __INCfslsoc913xh */


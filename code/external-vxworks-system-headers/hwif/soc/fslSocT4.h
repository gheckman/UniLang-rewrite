/* fslSocT4.h - Freescale T4XXX SOC header */

/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
22aug14,wyt  add boot space translation registers.
01k,09jul14,j_x  add USB related macros.
01j,14jan14,wyt  add device base address macros.
01i,18apr13,j_z  add SRIO, RMAN base address macros.
01h,06feb13,wyt  add device base address macros.
01g,31jan13,wyt  wrap vxbReadxxx and vxbWritexxx.
01f,27jan13,y_y  Added eSPI macros.
01e,21jan13,wyt  fixed some macro defines.
01d,09jan13,x_s  removed QIXIS register set to t4240qds.h.
01c,17dec12,x_s  removed DDR configuration parameters.
01b,05dec12,h_k  removed SPR631_INIT_VAL.
01a,30nov12,x_s  Created from t4240qds.h.
*/

/*
 * This file contains I/O addresses and related constants for the
 * FreeScale QorIQ T4xxx series platform.
 */

#ifndef __INCfslsocT4h
#define __INCfslsocT4h

#ifdef __cplusplus
    extern "C" {
#endif /* __cplusplus */

#define CCSBAR                      0xFE000000
#define CCSBAR_RESET                0xFE000000
#define CCSBAR_COMMIT               0x80000000
#define CCSRBARH_OFFSET             0x0
#define CCSRBARL_OFFSET             0x4
#define CCSRAR_OFFSET               0x8

/* 1. Vectors */
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

#undef  EPIC_VEC_IN_IRQ0
#define EPIC_VEC_IN_IRQ0            16

#define EPIC_DMA1_CHAN0_INT_VEC     (EPIC_VEC_IN_IRQ0 + 12)
#define EPIC_DMA1_CHAN1_INT_VEC     (EPIC_VEC_IN_IRQ0 + 13)
#define EPIC_DMA1_CHAN2_INT_VEC     (EPIC_VEC_IN_IRQ0 + 14)
#define EPIC_DMA1_CHAN3_INT_VEC     (EPIC_VEC_IN_IRQ0 + 15)
#define EPIC_DMA2_CHAN0_INT_VEC     (EPIC_VEC_IN_IRQ0 + 16)
#define EPIC_DMA2_CHAN1_INT_VEC     (EPIC_VEC_IN_IRQ0 + 17)
#define EPIC_DMA2_CHAN2_INT_VEC     (EPIC_VEC_IN_IRQ0 + 18)
#define EPIC_DMA2_CHAN3_INT_VEC     (EPIC_VEC_IN_IRQ0 + 19)

#undef  EPIC_DUART_INT_VEC
#define EPIC_DUART_INT_VEC          (EPIC_VEC_IN_IRQ0 + 20)
#undef  EPIC_DUART2_INT_VEC
#define EPIC_DUART2_INT_VEC         (EPIC_VEC_IN_IRQ0 + 21)
#define EPIC_DI2C1_INT_VEC          (EPIC_VEC_IN_IRQ0 + 22)
#define EPIC_DI2C2_INT_VEC          (EPIC_VEC_IN_IRQ0 + 23)
#define EPIC_USB0_INT_VEC           (EPIC_VEC_IN_IRQ0 + 28)
#define EPIC_SDHC_INT_VEC           (EPIC_VEC_IN_IRQ0 + 32)
#define EPIC_ESPI_INT_VEC           (EPIC_VEC_IN_IRQ0 + 37)
#define EPIC_SATA1_INT_VEC          (EPIC_VEC_IN_IRQ0 + 52)
#define EPIC_SATA2_INT_VEC          (EPIC_VEC_IN_IRQ0 + 53)
#define EPIC_DMA1_CHAN4_INT_VEC     (EPIC_VEC_IN_IRQ0 + 60)
#define EPIC_DMA1_CHAN5_INT_VEC     (EPIC_VEC_IN_IRQ0 + 61)
#define EPIC_DMA1_CHAN6_INT_VEC     (EPIC_VEC_IN_IRQ0 + 62)
#define EPIC_DMA1_CHAN7_INT_VEC     (EPIC_VEC_IN_IRQ0 + 63)
#define EPIC_DMA2_CHAN4_INT_VEC     (EPIC_VEC_IN_IRQ0 + 64)
#define EPIC_DMA2_CHAN5_INT_VEC     (EPIC_VEC_IN_IRQ0 + 65)
#define EPIC_DMA2_CHAN6_INT_VEC     (EPIC_VEC_IN_IRQ0 + 66)
#define EPIC_DMA2_CHAN7_INT_VEC     (EPIC_VEC_IN_IRQ0 + 67)

#define EPIC_QMAN_PORTAL0_INT_VEC   104
#define EPIC_QMAN_PORTAL1_INT_VEC   106
#define EPIC_QMAN_PORTAL2_INT_VEC   108
#define EPIC_QMAN_PORTAL3_INT_VEC   110
#define EPIC_QMAN_PORTAL4_INT_VEC   112
#define EPIC_QMAN_PORTAL5_INT_VEC   114
#define EPIC_QMAN_PORTAL6_INT_VEC   116
#define EPIC_QMAN_PORTAL7_INT_VEC   118
#define EPIC_QMAN_PORTAL8_INT_VEC   120
#define EPIC_QMAN_PORTAL9_INT_VEC   122
#define EPIC_QMAN_PORTAL10_INT_VEC  124
#define EPIC_QMAN_PORTAL11_INT_VEC  126
#define EPIC_QMAN_PORTAL12_INT_VEC  128
#define EPIC_QMAN_PORTAL13_INT_VEC  130
#define EPIC_QMAN_PORTAL14_INT_VEC  132
#define EPIC_QMAN_PORTAL15_INT_VEC  134
#define EPIC_QMAN_PORTAL16_INT_VEC  136
#define EPIC_QMAN_PORTAL17_INT_VEC  138
#define EPIC_QMAN_PORTAL18_INT_VEC  140
#define EPIC_QMAN_PORTAL19_INT_VEC  142
#define EPIC_QMAN_PORTAL20_INT_VEC  144
#define EPIC_QMAN_PORTAL21_INT_VEC  146
#define EPIC_QMAN_PORTAL22_INT_VEC  148
#define EPIC_QMAN_PORTAL23_INT_VEC  150

#define EPIC_BMAN_PORTAL0_INT_VEC   105
#define EPIC_BMAN_PORTAL1_INT_VEC   107
#define EPIC_BMAN_PORTAL2_INT_VEC   109
#define EPIC_BMAN_PORTAL3_INT_VEC   111
#define EPIC_BMAN_PORTAL4_INT_VEC   113
#define EPIC_BMAN_PORTAL5_INT_VEC   115
#define EPIC_BMAN_PORTAL6_INT_VEC   117
#define EPIC_BMAN_PORTAL7_INT_VEC   119
#define EPIC_BMAN_PORTAL8_INT_VEC   121
#define EPIC_BMAN_PORTAL9_INT_VEC   123
#define EPIC_BMAN_PORTAL10_INT_VEC  125
#define EPIC_BMAN_PORTAL11_INT_VEC  127
#define EPIC_BMAN_PORTAL12_INT_VEC  129
#define EPIC_BMAN_PORTAL13_INT_VEC  131
#define EPIC_BMAN_PORTAL14_INT_VEC  133
#define EPIC_BMAN_PORTAL15_INT_VEC  135
#define EPIC_BMAN_PORTAL16_INT_VEC  137
#define EPIC_BMAN_PORTAL17_INT_VEC  139
#define EPIC_BMAN_PORTAL18_INT_VEC  141
#define EPIC_BMAN_PORTAL19_INT_VEC  143
#define EPIC_BMAN_PORTAL20_INT_VEC  145
#define EPIC_BMAN_PORTAL21_INT_VEC  147
#define EPIC_BMAN_PORTAL22_INT_VEC  149
#define EPIC_BMAN_PORTAL23_INT_VEC  151

/* OpenPIC timer vectors */

#define OPENPIC_TIMERA0_INT_VEC     200
#define OPENPIC_TIMERB0_INT_VEC     204

/* GPIO vector */

#define GPIO_INT_VEC                55

/* USB vectors */

#define EPIC_USB1_INT_VEC           (28 + EPIC_VEC_IN_IRQ0)
#define EPIC_USB2_INT_VEC           (29 + EPIC_VEC_IN_IRQ0)

/* 2. PCI defines */
/* SOC T4XXX supports four PCIe controllers */

/*

CPU Addr                                  PCI Addr ( PCI1 or PCI2)
PCI_LOCAL_MEM_BUS        -------------------------- PCI_MSTR_MEM_BUS
                         -                        -
                         -                        -
PCI_LOCAL_MEM_BUS +      -------------------------- PCI_MSTR_MEM_BUS +
PCI_LOCAL_MEM_SIZE       -                        - PCI_MSTR_MEM_SIZE
                         -                        -
                         -                        ----- PCI Bridge (for PCI1 only)
                         -                        -     configuration regs
                         -                        -
CPU_PCI_MEM_ADRS (PCIEX1) -------------------------- PCI_MEM_ADRS
CPU_PCI_MEM_ADRS2(PCIEX2) -                        - PCI_MEM_ADRS2
CPU_PCI_MEM_ADRS3(PCIEX3) -------------------------- PCI_MEM_ADRS3
                         -                        -
CPU_PCI_MEMIO_ADRS       -------------------------- PCI_MEMIO_ADRS
CPU_PCI_MEMIO_ADRS2      -                        - PCI_MEMIO_ADRS2
CPU_PCI_MEMIO_ADRS3      -                        - PCI_MEMIO_ADRS3
                         -                        -
CPU_PCI_IO_ADRS (PCIEX1) -------------------------- PCI_IO_ADRS
CPU_PCI_IO_ADRS2(PCIEX2) -                        - PCI_IO_ADRS2
CPU_PCI_IO_ADRS3(PCIEX3) -                        - PCI_IO_ADRS3
                         -                        -
CPU_PCI_IO_ADRS (PCIEX1)+-------------------------- PCI_IO_ADRS +
CPU_PCI_IO_ADRS2(PCIEX2)+                           PCI_IO_ADRS2 +
CPU_PCI_IO_ADRS2(PCIEX3)                            PCI_IO_ADRS3
CPU_PCI_IO_SIZE          -                        - PCI_IO_SIZE
                         -                        -
*/

/*
 * PCI based addresses
 * Note: the LAW_BASE values have been chosen to coincide
 * with those used by U-Boot on the T4DS board.
 */

#define T4_PCIEX1_BASE             (CCSBAR + 0x240000) /* PCI-EX slot 0 */
#define T4_PCIEX2_BASE             (CCSBAR + 0x250000) /* PCI-EX slot 1 */
#define T4_PCIEX3_BASE             (CCSBAR + 0x260000) /* PCI-EX slot 2 */
#define T4_PCIEX4_BASE             (CCSBAR + 0x270000) /* PCI-EX slot 3 */

/*
 * The T4 processor has four PCIe bridges, each bridges's interrupt supports
 * two mechanisms, INTx emulation and Message Signaled Interrupt (MSI) mode.
 * The bridge provide four Virtual Wires(INTA, INTB, INTC and INTD) for
 * signaling interrupts across a Link. When the bridge works on INTx emulation
 * mode, the virtual Wires INTA are routed to dedicated internal
 * interrupts (24, 25, 26, and 27) in the MPIC, the others INTx are logically
 * combined with the IRQn signals so that they share the external interrupts.
 * If the bridge interrupts works on MSI mode, interrupts generated from
 * the EP device will be routed to the MSIIR register in the PIC, virtual Wires
 * INTx will not be triggered.
 *
 * The follow configuration is fit for INTx emulation mode, the INTA interrupts
 * work as expected, but INTB, INTC and INTD may not.
 */

#define EPIC_VEC_PCIE1_INTA         (EPIC_VEC_IN_IRQ0 + 24)
#define EPIC_VEC_PCIE2_INTA         (EPIC_VEC_IN_IRQ0 + 25)
#define EPIC_VEC_PCIE3_INTA         (EPIC_VEC_IN_IRQ0 + 26)
#define EPIC_VEC_PCIE4_INTA         (EPIC_VEC_IN_IRQ0 + 27)

#define PCIEX1_XINT1_LVL            (EPIC_VEC_PCIE1_INTA)
#define PCIEX1_XINT2_LVL            (EPIC_VEC_EXT_IRQ0 + 1)
#define PCIEX1_XINT3_LVL            (EPIC_VEC_EXT_IRQ0 + 2)
#define PCIEX1_XINT4_LVL            (EPIC_VEC_EXT_IRQ0 + 3)

#define PCIEX2_XINT1_LVL            (EPIC_VEC_PCIE2_INTA)
#define PCIEX2_XINT2_LVL            (EPIC_VEC_EXT_IRQ0 + 5)
#define PCIEX2_XINT3_LVL            (EPIC_VEC_EXT_IRQ0 + 6)
#define PCIEX2_XINT4_LVL            (EPIC_VEC_EXT_IRQ0 + 7)

#define PCIEX3_XINT1_LVL            (EPIC_VEC_PCIE3_INTA)
#define PCIEX3_XINT2_LVL            (EPIC_VEC_EXT_IRQ0 + 9)
#define PCIEX3_XINT3_LVL            (EPIC_VEC_EXT_IRQ0 + 10)
#define PCIEX3_XINT4_LVL            (EPIC_VEC_EXT_IRQ0 + 11)

#define PCIEX4_XINT1_LVL            (EPIC_VEC_PCIE4_INTA)
#define PCIEX4_XINT2_LVL            (EPIC_VEC_EXT_IRQ0 + 0)
#define PCIEX4_XINT3_LVL            (EPIC_VEC_EXT_IRQ0 + 4)
#define PCIEX4_XINT4_LVL            (EPIC_VEC_EXT_IRQ0 + 8)

#define EPIC_USB1_INT_VEC           (28 + EPIC_VEC_IN_IRQ0)
#define EPIC_USB2_INT_VEC           (29 + EPIC_VEC_IN_IRQ0)

/* 3. Local Access Windows Regster Offsets from CCSBAR */
/* Used for Flash ROM */

#define  T4_LAWBARH0                (CCSBAR + 0xc00)
#define  T4_LAWBARL0                (CCSBAR + 0xc04)
#define  T4_LAWAR0                  (CCSBAR + 0xc08)

#define  T4_LAWBARH1                (CCSBAR + 0xc10)
#define  T4_LAWBARL1                (CCSBAR + 0xc14)
#define  T4_LAWAR1                  (CCSBAR + 0xc18)

#define  T4_LAWBARH2                (CCSBAR + 0xc20)
#define  T4_LAWBARL2                (CCSBAR + 0xc24)
#define  T4_LAWAR2                  (CCSBAR + 0xc28)

#define  T4_LAWBARH3                (CCSBAR + 0xc30)
#define  T4_LAWBARL3                (CCSBAR + 0xc34)
#define  T4_LAWAR3                  (CCSBAR + 0xc38)

#define  T4_LAWBARH4                (CCSBAR + 0xc40)
#define  T4_LAWBARL4                (CCSBAR + 0xc44)
#define  T4_LAWAR4                  (CCSBAR + 0xc48)

#define  T4_LAWBARH5                (CCSBAR + 0xc50)
#define  T4_LAWBARL5                (CCSBAR + 0xc54)
#define  T4_LAWAR5                  (CCSBAR + 0xc58)

#define  T4_LAWBARH6                (CCSBAR + 0xc60)
#define  T4_LAWBARL6                (CCSBAR + 0xc64)
#define  T4_LAWAR6                  (CCSBAR + 0xc68)

#define  T4_LAWBARH7                (CCSBAR + 0xc70)
#define  T4_LAWBARL7                (CCSBAR + 0xc74)
#define  T4_LAWAR7                  (CCSBAR + 0xc78)

#define  T4_LAWBARH8                (CCSBAR + 0xc80)
#define  T4_LAWBARL8                (CCSBAR + 0xc84)
#define  T4_LAWAR8                  (CCSBAR + 0xc88)

#define  T4_LAWBARH9                (CCSBAR + 0xc90)
#define  T4_LAWBARL9                (CCSBAR + 0xc94)
#define  T4_LAWAR9                  (CCSBAR + 0xc98)

#define  T4_LAWBARH10               (CCSBAR + 0xca0)
#define  T4_LAWBARL10               (CCSBAR + 0xca4)
#define  T4_LAWAR10                 (CCSBAR + 0xca8)

#define  T4_LAWBARH11               (CCSBAR + 0xcb0)
#define  T4_LAWBARL11               (CCSBAR + 0xcb4)
#define  T4_LAWAR11                 (CCSBAR + 0xcb8)

#define  T4_LAWBARH30               (CCSBAR + 0xde0)
#define  T4_LAWBARL30               (CCSBAR + 0xde4)
#define  T4_LAWAR30                 (CCSBAR + 0xde8)

#define  T4_LAWBARH31               (CCSBAR + 0xdf0)
#define  T4_LAWBARL31               (CCSBAR + 0xdf4)
#define  T4_LAWAR31                 (CCSBAR + 0xdf8)

#define  T4_LAWBARH8_RESET          (CCSBAR_RESET + 0xc80)
#define  T4_LAWBARL8_RESET          (CCSBAR_RESET + 0xc84)
#define  T4_LAWAR8_RESET            (CCSBAR_RESET + 0xc88)


#define  LAWBAR_ADRS_SHIFT          0
#define  LAWAR_ENABLE               0x80000000
#define  LAWAR_TGTIF_PCIEX1         0x00000000
#define  LAWAR_TGTIF_PCIEX2         0x00100000
#define  LAWAR_TGTIF_PCIEX3         0x00200000
#define  LAWAR_TGTIF_PCIEX4         0x00300000
#define  LAWAR_TGTIF_RAPIDIO        0x00800000
#define  LAWAR_TGTIF_RAPIDIO2       0x00900000
#define  LAWAR_TGTIF_DDRSDRAM       0x01000000
#define  LAWAR_TGTIF_DDRSDRAM2      0x01100000
#define  LAWAR_TGTIF_DDRSDRAM3      0x01200000
#define  LAWAR_TGTIF_MEM_INTRL      0x01400000
#define  LAWAR_TGTIF_BMAN           0x01800000
#define  LAWAR_TGTIF_DCSR           0x01D00000
#define  LAWAR_TGTIF_RESERVE        0x01E00000
#define  LAWAR_TGTIF_IFC            0x01F00000
#define  LAWAR_TGTIF_QMAN           0x03C00000

/* LAWAR SIZE Settings */

#define  LAWAR_SIZE_4KB             0x0000000B
#define  LAWAR_SIZE_8KB             0x0000000C
#define  LAWAR_SIZE_16KB            0x0000000D
#define  LAWAR_SIZE_32KB            0x0000000E
#define  LAWAR_SIZE_64KB            0x0000000F
#define  LAWAR_SIZE_128KB           0x00000010
#define  LAWAR_SIZE_256KB           0x00000011
#define  LAWAR_SIZE_512KB           0x00000012
#define  LAWAR_SIZE_1MB             0x00000013
#define  LAWAR_SIZE_2MB             0x00000014
#define  LAWAR_SIZE_4MB             0x00000015
#define  LAWAR_SIZE_8MB             0x00000016
#define  LAWAR_SIZE_16MB            0x00000017
#define  LAWAR_SIZE_32MB            0x00000018
#define  LAWAR_SIZE_64MB            0x00000019
#define  LAWAR_SIZE_128MB           0x0000001A
#define  LAWAR_SIZE_256MB           0x0000001B
#define  LAWAR_SIZE_512MB           0x0000001C
#define  LAWAR_SIZE_1GB             0x0000001D
#define  LAWAR_SIZE_2GB             0x0000001E

/* 4. Integrated Flash Controller (IFC) Registers */

#define T4_IFC_BASE                 (CCSBAR + 0x124000)
#define T4_IFC_REV                  (T4_IFC_BASE + 0x0000)
#define T4_IFC_CSPR0_EXT            (T4_IFC_BASE + 0x000c)
#define T4_IFC_CSPR0                (T4_IFC_BASE + 0x0010)
#define T4_IFC_CSPR1_EXT            (T4_IFC_BASE + 0x0018)
#define T4_IFC_CSPR1                (T4_IFC_BASE + 0x001c)
#define T4_IFC_CSPR2_EXT            (T4_IFC_BASE + 0x0024)
#define T4_IFC_CSPR2                (T4_IFC_BASE + 0x0028)
#define T4_IFC_CSPR3_EXT            (T4_IFC_BASE + 0x0030)
#define T4_IFC_CSPR3                (T4_IFC_BASE + 0x0034)
#define T4_IFC_CSPR4_EXT            (T4_IFC_BASE + 0x003c)
#define T4_IFC_CSPR4                (T4_IFC_BASE + 0x0040)
#define T4_IFC_CSPR5_EXT            (T4_IFC_BASE + 0x0048)
#define T4_IFC_CSPR5                (T4_IFC_BASE + 0x004c)
#define T4_IFC_CSPR6_EXT            (T4_IFC_BASE + 0x0054)
#define T4_IFC_CSPR6                (T4_IFC_BASE + 0x0058)
#define T4_IFC_CSPR7_EXT            (T4_IFC_BASE + 0x0060)
#define T4_IFC_CSPR7                (T4_IFC_BASE + 0x0064)
#define T4_IFC_AMASK0               (T4_IFC_BASE + 0x00a0)
#define T4_IFC_AMASK1               (T4_IFC_BASE + 0x00ac)
#define T4_IFC_AMASK2               (T4_IFC_BASE + 0x00b8)
#define T4_IFC_AMASK3               (T4_IFC_BASE + 0x00c4)
#define T4_IFC_AMASK4               (T4_IFC_BASE + 0x00d0)
#define T4_IFC_AMASK5               (T4_IFC_BASE + 0x00dc)
#define T4_IFC_AMASK6               (T4_IFC_BASE + 0x00e8)
#define T4_IFC_AMASK7               (T4_IFC_BASE + 0x00f4)
#define T4_IFC_CSOR0                (T4_IFC_BASE + 0x0130)
#define T4_IFC_CSOR0_EXT            (T4_IFC_BASE + 0x0134)
#define T4_IFC_CSOR1                (T4_IFC_BASE + 0x013c)
#define T4_IFC_CSOR1_EXT            (T4_IFC_BASE + 0x0140)
#define T4_IFC_CSOR2                (T4_IFC_BASE + 0x0148)
#define T4_IFC_CSOR2_EXT            (T4_IFC_BASE + 0x014c)
#define T4_IFC_CSOR3                (T4_IFC_BASE + 0x0154)
#define T4_IFC_CSOR3_EXT            (T4_IFC_BASE + 0x0158)
#define T4_IFC_CSOR4                (T4_IFC_BASE + 0x0160)
#define T4_IFC_CSOR4_EXT            (T4_IFC_BASE + 0x0164)
#define T4_IFC_CSOR5                (T4_IFC_BASE + 0x016c)
#define T4_IFC_CSOR5_EXT            (T4_IFC_BASE + 0x0170)
#define T4_IFC_CSOR6                (T4_IFC_BASE + 0x0178)
#define T4_IFC_CSOR6_EXT            (T4_IFC_BASE + 0x017c)
#define T4_IFC_CSOR7                (T4_IFC_BASE + 0x0184)
#define T4_IFC_CSOR7_EXT            (T4_IFC_BASE + 0x0188)
#define T4_IFC_FTIM0_CS0            (T4_IFC_BASE + 0x01c0)
#define T4_IFC_FTIM1_CS0            (T4_IFC_BASE + 0x01c4)
#define T4_IFC_FTIM2_CS0            (T4_IFC_BASE + 0x01c8)
#define T4_IFC_FTIM3_CS0            (T4_IFC_BASE + 0x01cc)
#define T4_IFC_FTIM0_CS1            (T4_IFC_BASE + 0x01f0)
#define T4_IFC_FTIM1_CS1            (T4_IFC_BASE + 0x01f4)
#define T4_IFC_FTIM2_CS1            (T4_IFC_BASE + 0x01f8)
#define T4_IFC_FTIM3_CS1            (T4_IFC_BASE + 0x01fc)
#define T4_IFC_FTIM0_CS2            (T4_IFC_BASE + 0x0220)
#define T4_IFC_FTIM1_CS2            (T4_IFC_BASE + 0x0224)
#define T4_IFC_FTIM2_CS2            (T4_IFC_BASE + 0x0228)
#define T4_IFC_FTIM3_CS2            (T4_IFC_BASE + 0x022c)
#define T4_IFC_FTIM0_CS3            (T4_IFC_BASE + 0x0250)
#define T4_IFC_FTIM1_CS3            (T4_IFC_BASE + 0x0254)
#define T4_IFC_FTIM2_CS3            (T4_IFC_BASE + 0x0258)
#define T4_IFC_FTIM3_CS3            (T4_IFC_BASE + 0x025c)
#define T4_IFC_FTIM0_CS4            (T4_IFC_BASE + 0x0280)
#define T4_IFC_FTIM1_CS4            (T4_IFC_BASE + 0x0284)
#define T4_IFC_FTIM2_CS4            (T4_IFC_BASE + 0x0288)
#define T4_IFC_FTIM3_CS4            (T4_IFC_BASE + 0x028c)
#define T4_IFC_FTIM0_CS5            (T4_IFC_BASE + 0x02b0)
#define T4_IFC_FTIM1_CS5            (T4_IFC_BASE + 0x02b4)
#define T4_IFC_FTIM2_CS5            (T4_IFC_BASE + 0x02b8)
#define T4_IFC_FTIM3_CS5            (T4_IFC_BASE + 0x02bc)
#define T4_IFC_FTIM0_CS6            (T4_IFC_BASE + 0x02e0)
#define T4_IFC_FTIM1_CS6            (T4_IFC_BASE + 0x02e4)
#define T4_IFC_FTIM2_CS6            (T4_IFC_BASE + 0x02e8)
#define T4_IFC_FTIM3_CS6            (T4_IFC_BASE + 0x02ec)
#define T4_IFC_FTIM0_CS7            (T4_IFC_BASE + 0x0310)
#define T4_IFC_FTIM1_CS7            (T4_IFC_BASE + 0x0314)
#define T4_IFC_FTIM2_CS7            (T4_IFC_BASE + 0x0318)
#define T4_IFC_FTIM3_CS7            (T4_IFC_BASE + 0x031c)
#define T4_IFC_RB_STAT              (T4_IFC_BASE + 0x0400)
#define T4_IFC_GCR                  (T4_IFC_BASE + 0x040c)
#define T4_IFC_CM_EVTER_STAT        (T4_IFC_BASE + 0x0418)
#define T4_IFC_CM_EVTER_EN          (T4_IFC_BASE + 0x0424)
#define T4_IFC_CM_EVTER_INTR_EN     (T4_IFC_BASE + 0x0430)
#define T4_IFC_CM_ERATTR0           (T4_IFC_BASE + 0x043c)
#define T4_IFC_CM_ERATTR1           (T4_IFC_BASE + 0x0440)
#define T4_IFC_CCR                  (T4_IFC_BASE + 0x044c)
#define T4_IFC_CSR                  (T4_IFC_BASE + 0x0450)
#define T4_IFC_NCFGR                (T4_IFC_BASE + 0x1000)
#define T4_IFC_NAND_FCR0            (T4_IFC_BASE + 0x1014)
#define T4_IFC_NAND_FCR1            (T4_IFC_BASE + 0x1018)
#define T4_IFC_ROW0                 (T4_IFC_BASE + 0x103c)
#define T4_IFC_COL0                 (T4_IFC_BASE + 0x1044)
#define T4_IFC_ROW1                 (T4_IFC_BASE + 0x104c)
#define T4_IFC_COL1                 (T4_IFC_BASE + 0x1054)
#define T4_IFC_ROW2                 (T4_IFC_BASE + 0x105c)
#define T4_IFC_COL2                 (T4_IFC_BASE + 0x1064)
#define T4_IFC_ROW3                 (T4_IFC_BASE + 0x106c)
#define T4_IFC_COL3                 (T4_IFC_BASE + 0x1074)
#define T4_IFC_NAND_BC              (T4_IFC_BASE + 0x1108)
#define T4_IFC_NAND_FIR0            (T4_IFC_BASE + 0x1110)
#define T4_IFC_NAND_FIR1            (T4_IFC_BASE + 0x1114)
#define T4_IFC_NAND_FIR2            (T4_IFC_BASE + 0x1118)
#define T4_IFC_NAND_CSEL            (T4_IFC_BASE + 0x115c)
#define T4_IFC_NANDSEQ_STRT         (T4_IFC_BASE + 0x1164)
#define T4_IFC_NAND_EVTER_STAT      (T4_IFC_BASE + 0x116c)
#define T4_IFC_PGRDCMPL_EVT_STAT    (T4_IFC_BASE + 0x1174)
#define T4_IFC_NAND_EVTER_EN        (T4_IFC_BASE + 0x1180)
#define T4_IFC_NAND_EVTER_INTR_EN   (T4_IFC_BASE + 0x118c)
#define T4_IFC_NAND_ERATTR0         (T4_IFC_BASE + 0x1198)
#define T4_IFC_NAND_ERATTR1         (T4_IFC_BASE + 0x119c)
#define T4_IFC_NAND_FSR             (T4_IFC_BASE + 0x11e0)
#define T4_IFC_ECCSTAT0             (T4_IFC_BASE + 0x11e8)
#define T4_IFC_ECCSTAT1             (T4_IFC_BASE + 0x11ec)
#define T4_IFC_ECCSTAT2             (T4_IFC_BASE + 0x11f0)
#define T4_IFC_ECCSTAT3             (T4_IFC_BASE + 0x11f4)
#define T4_IFC_NANDCR               (T4_IFC_BASE + 0x1278)
#define T4_IFC_NAND_AUTOBOOT_TRGR   (T4_IFC_BASE + 0x1284)
#define T4_IFC_NAND_MDR             (T4_IFC_BASE + 0x128c)
#define T4_IFC_NOR_EVTER_STAT       (T4_IFC_BASE + 0x1400)
#define T4_IFC_NOR_EVTER_EN         (T4_IFC_BASE + 0x140c)
#define T4_IFC_NOR_EVTER_INTR_EN    (T4_IFC_BASE + 0x1418)
#define T4_IFC_NOR_ERATTR0          (T4_IFC_BASE + 0x1424)
#define T4_IFC_NOR_ERATTR1          (T4_IFC_BASE + 0x1428)
#define T4_IFC_NOR_ERATTR2          (T4_IFC_BASE + 0x142c)
#define T4_IFC_NORCR                (T4_IFC_BASE + 0x1440)
#define T4_IFC_GPCM_EVTER_STAT      (T4_IFC_BASE + 0x1800)
#define T4_IFC_GPCM_EVTER_EN        (T4_IFC_BASE + 0x180c)
#define T4_IFC_GPCM_EVTER_INTR_EN   (T4_IFC_BASE + 0x1818)
#define T4_IFC_GPCM_ERATTR0         (T4_IFC_BASE + 0x1824)
#define T4_IFC_GPCM_ERATTR1         (T4_IFC_BASE + 0x1828)
#define T4_IFC_GPCM_ERATTR2         (T4_IFC_BASE + 0x182c)
#define T4_IFC_GPCM_STAT            (T4_IFC_BASE + 0x1830)

/* 4. DDR */
/* Offsets for DDR registers */

#define T4_DDR1_BASE                (CCSBAR + 0x8000)
#define T4_DDR2_BASE                (CCSBAR + 0x9000)
#define T4_DDR3_BASE                (CCSBAR + 0xA000)

#define T4_CS0_BNDS                 0x000
#define T4_CS1_BNDS                 0x008
#define T4_CS2_BNDS                 0x010
#define T4_CS3_BNDS                 0x018
#define T4_CS0_CONFIG               0x080
#define T4_CS1_CONFIG               0x084
#define T4_CS2_CONFIG               0x088
#define T4_CS3_CONFIG               0x08C
#define T4_TIMING_CFG_3             0x100
#define T4_TIMING_CFG_0             0x104
#define T4_TIMING_CFG_1             0x108
#define T4_TIMING_CFG_2             0x10C
#define T4_DDR_SDRAM_CFG            0x110
#define T4_DDR_SDRAM_CFG_2          0x114
#define T4_DDR_SDRAM_MODE_CFG       0x118
#define T4_DDR_SDRAM_MODE_CFG_2     0x11c
#define T4_DDR_SDRAM_MD_CNTL        0x120
#define T4_DDR_SDRAM_INTERVAL       0x124
#define T4_DDR_DATA_INIT            0x128
#define T4_DDR_SDRAM_CLK_CTRL       0x130
#define T4_TIMING_CFG_4             0x160
#define T4_TIMING_CFG_5             0x164
#define T4_DDR_ZQ_CNTL              0x170
#define T4_DDR_WRLVL_CNTL           0x174
#define T4_DDR_SR_CNTR              0x17C
#define T4_DDR_WRLVL_CNTL_2         0x190
#define T4_DDR_WRLVL_CNTL_3         0x194
#define T4_DDRx_DDR_SDRAM_MODE_3    0x200
#define T4_DDRx_DDR_SDRAM_MODE_4    0x204
#define T4_DDRx_DDR_SDRAM_MODE_5    0x208
#define T4_DDRx_DDR_SDRAM_MODE_6    0x20C
#define T4_DDRx_DDR_SDRAM_MODE_7    0x210
#define T4_DDRx_DDR_SDRAM_MODE_8    0x214

#define T4_DDRCDR_1                 0xB28
#define T4_DDRCDR_2                 0xB2C

#define T4_DDR_DATA_ERR_INJECT_HI   0xe00
#define T4_DDR_DATA_ERR_INJECT_LO   0xe04
#define T4_DDR_ECC_ERR_INJECT       0xe08
#define T4_DDR_CAPTURE_DATA_HI      0xe20
#define T4_DDR_CAPTURE_DATA_LO      0xe24
#define T4_DDR_CAPTURE_ECC          0xe28
#define T4_DDR_ERR_DETECT           0xe40
#define T4_DDR_ERR_DISABLE          0xe44
#define T4_DDR_ERR_INT_EN           0xe48
#define T4_DDR_CAPTURE_ATTRIBUTES   0xe4c
#define T4_DDR_CAPTURE_ADDRESS      0xe50
#define T4_DDR_ERR_SBE              0xe58

/* 5. DMA */

#define T4_DMA1_BASE                (CCSBAR + 0x100100)
#define T4_DMA2_BASE                (CCSBAR + 0x101100)

/* 6. I2C */

#define T4_I2C1_BASE                (CCSBAR + 0x118000)
#define T4_I2C2_BASE                (CCSBAR + 0x118100)
#define T4_I2C3_BASE                (CCSBAR + 0x119000)
#define T4_I2C4_BASE                (CCSBAR + 0x119100)

/* 7. USB */

#define T4_USB1_BASE                (CCSBAR + 0x210000)
#define T4_USB2_BASE                (CCSBAR + 0x211000)

/* 8. eSPI */

#define T4_ESPI1_BASE               (CCSBAR + 0x110000)

/* 9. MEMAC */

#define T4_MEMAC1_BASE              (CCSBAR + 0x4E0000)
#define T4_MEMAC2_BASE              (CCSBAR + 0x4E2000)
#define T4_MEMAC3_BASE              (CCSBAR + 0x4E4000)
#define T4_MEMAC4_BASE              (CCSBAR + 0x4E6000)
#define T4_MEMAC5_BASE              (CCSBAR + 0x4E8000)
#define T4_MEMAC6_BASE              (CCSBAR + 0x4EA000)
#define T4_MEMAC7_BASE              (CCSBAR + 0x4F0000)
#define T4_MEMAC8_BASE              (CCSBAR + 0x4F2000)
#define T4_MEMAC9_BASE              (CCSBAR + 0x5E0000)
#define T4_MEMAC10_BASE             (CCSBAR + 0x5E2000)
#define T4_MEMAC11_BASE             (CCSBAR + 0x5E4000)
#define T4_MEMAC12_BASE             (CCSBAR + 0x5E6000)
#define T4_MEMAC13_BASE             (CCSBAR + 0x5E8000)
#define T4_MEMAC14_BASE             (CCSBAR + 0x5EA000)
#define T4_MEMAC15_BASE             (CCSBAR + 0x5F0000)
#define T4_MEMAC16_BASE             (CCSBAR + 0x5F2000)

/* 10. MDIO */

#define T4_MDIO1_BASE               (CCSBAR + 0x4FC000)
#define T4_MDIO2_BASE               (CCSBAR + 0x4FD000)
#define T4_MDIO3_BASE               (CCSBAR + 0x5FC000)
#define T4_MDIO4_BASE               (CCSBAR + 0x5FD000)

/* 11. FMAN */

#define T4_FMAN1_BASE               (CCSBAR + 0x400000)
#define T4_FMAN2_BASE               (CCSBAR + 0x500000)

/* 12. QMAN */

#define T4_QMAN1_BASE               (CCSBAR + 0x318000)

/* 13. BMAN */

#define T4_BMAN1_BASE               (CCSBAR + 0x31A000)

/* 14. UART */

#define T4_DUART1_BASE              (CCSBAR + 0x11C500)
#define T4_DUART2_BASE              (CCSBAR + 0x11C600)
#define T4_DUART3_BASE              (CCSBAR + 0x11D500)
#define T4_DUART4_BASE              (CCSBAR + 0x11D600)

/* 15. TIMER */

#define T4_OPENPIC_TIMER1_BASE      (CCSBAR + 0x0410F0)
#define T4_OPENPIC_TIMER2_BASE      (CCSBAR + 0x0420F0)

/* 16. SDHC */

#define T4_SDHC1_BASE               (CCSBAR + 0x114000)

/* 17. SATA */

#define T4_SATA1_BASE               (CCSBAR + 0x220000)
#define T4_SATA2_BASE               (CCSBAR + 0x221000)

/* 18. SRIO */

#define T4_SRIO_BASE                (CCSBAR + 0xC0000)

/* 19. RMAN */

#define T4_RMAN_BASE                (CCSBAR + 0x1E0000)

/* EHCI registers */

#define T4_EHCI_CAPLENGTH(base)     ((base) + 0x00100)
#define T4_EHCI_BURSTSIZE(base)     ((base) + 0x00160)
#define T4_EHCI_TXTTFILLTUNING(base)((base) + 0x00164)
#define T4_EHCI_CONFIGFLAG(base)    ((base) + 0x00180)
#define T4_EHCI_PORTSC(base)        ((base) + 0x00184)
#define T4_EHCI_USBMODE(base)       ((base) + 0x001a8)
#define T4_EHCI_SNOOP1(base)        ((base) + 0x00400)
#define T4_EHCI_SNOOP2(base)        ((base) + 0x00404)
#define T4_EHCI_AGE_CNT_THRESH(base)((base) + 0x00408)
#define T4_EHCI_PRI_CTRL(base)      ((base) + 0x0040c)
#define T4_EHCI_SI_CTRL(base)       ((base) + 0x00410)
#define T4_EHCI_CONTROL(base)       ((base) + 0x00500)

#define EHCI_USBMODE_IDLE           0x00000000
#define EHCI_USBMODE_DEVICE         0x00000002
#define EHCI_USBMODE_HOST           0x00000003

#define EHCI_PORTSC_ULPI            0x80000000
#define EHCI_PORTSC_UTMI            0x00000000

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

#define EHCI_PRI_EN                 0x00000008

#define EHCI_CONTROL_UTMI_PHY_EN    0x00000200
#define EHCI_CONTROL_USB_EN         0x00000004

/* USB PHY */

#define T4_USB1_PHY_BASE            (CCSBAR + 0x214004)
#define T4_USB2_PHY_BASE            (CCSBAR + 0x214080)

#define T4_USB_PHY_CTLR(base)       ((base) + 0x00)
#define T4_USB_PHY_VBUS_CFG(base)   ((base) + 0x04)
#define T4_USB_PHY_STS(base)        ((base) + 0x0c)

#define T4_USB_PHY_PLL_PRG1         (CCSBAR + 0x214000 + 0x60)
#define T4_USB_PHY_PLL_PRG2         (CCSBAR + 0x214000 + 0x64)
#define T4_USB_PHY_PLL_PRG3         (CCSBAR + 0x214000 + 0x68)
#define T4_USB_PHY_PLL_PRG4         (CCSBAR + 0x214000 + 0x6c)

#define PLL_PRG1_INIT_VALUE         0x000083E8
#define PLL_PRG2_INIT_VALUE         0x00252013
#define USB_PORT_ENABLE             0x00000001
#define PHY_PLL_VALID               0x00000001
#define PHY_VBUS_ENABLE             0x00000002
#define PHY_VBUS_VALID              0x00000002
#define PLL_PRG1_QUAN_MASK          (0x01 << 3)
#define PLL_PRG1_SDM_MASK           (0x01 << 2)
#define USB_PHY_EN_OVERRIDE         0x00000001

/* clocking */

#define T4_CLKC1CSR                (CCSBAR + 0xE1000)
#define T4_CLKCG1HWACSR            (CCSBAR + 0xE1010)
#define T4_CLKC2CSR                (CCSBAR + 0xE1020)
#define T4_CLKCG2HWACSR            (CCSBAR + 0xE1030)
#define T4_CLKC3CSR                (CCSBAR + 0xE1040)
#define T4_CLKCG3HWACSR            (CCSBAR + 0xE1050)
#define T4_CLKC4CSR                (CCSBAR + 0xE1060)
#define T4_CLKCG4HWACSR            (CCSBAR + 0xE1070)
#define T4_CLKCG5HWACSR            (CCSBAR + 0xE1090)
#define T4_PLLC1GSR                (CCSBAR + 0xE1800)
#define T4_PLLC2GSR                (CCSBAR + 0xE1820)
#define T4_PLLC3GSR                (CCSBAR + 0xE1840)
#define T4_PLLC4GSR                (CCSBAR + 0xE1860)
#define T4_PLLC5GSR                (CCSBAR + 0xE1880)
#define T4_CLKPCSR                 (CCSBAR + 0xE1A00)
#define T4_PLLPGSR                 (CCSBAR + 0xE1C00)
#define T4_PLLDGSR                 (CCSBAR + 0xE1C20)

/* Thread PH10 status and control registers - bits are 1 << CPU index */

#define T4_TPH10SR3                (CCSBAR + 0xE2000)
#define T4_TPH10SR2                (CCSBAR + 0xE2004)
#define T4_TPH10SR1                (CCSBAR + 0xE2008)
#define T4_TPH10SR0                (CCSBAR + 0xE200C)
#define T4_TPH10SETR3              (CCSBAR + 0xE2010)
#define T4_TPH10SETR2              (CCSBAR + 0xE2014)
#define T4_TPH10SETR1              (CCSBAR + 0xE2018)
#define T4_TPH10SETR0              (CCSBAR + 0xE201C)
#define T4_TPH10CLRR3              (CCSBAR + 0xE2020)
#define T4_TPH10CLRR2              (CCSBAR + 0xE2024)
#define T4_TPH10CLRR1              (CCSBAR + 0xE2028)
#define T4_TPH10CLRR0              (CCSBAR + 0xE202C)
#define T4_TPH10PSR3               (CCSBAR + 0xE2030)
#define T4_TPH10PSR2               (CCSBAR + 0xE2034)
#define T4_TPH10PSR1               (CCSBAR + 0xE2038)
#define T4_TPH10PSR0               (CCSBAR + 0xE203C)
#define T4_TWAITSR3                (CCSBAR + 0xE2040)
#define T4_TWAITSR2                (CCSBAR + 0xE2044)
#define T4_TWAITSR1                (CCSBAR + 0xE2048)
#define T4_TWAITSR0                (CCSBAR + 0xE204C)

/* Processor reset register */

#define T4_EPICPRR                 (CCSBAR + 0x41098)

/* Feature Reporting Register (FRR) */

#define T4_EPICFRR                 (CCSBAR + 0x41000)

/* Processor initialization register */

#define T4_EPICPIR                 (CCSBAR + 0x41090)
#define T4_EPICWHOAMI              (CCSBAR + 0x40090)

/*
 * CPU-private current task priority and end-of-interrupt registers
 * (used for CPU reset)
 */

#define T4_EPICCTPRn(n)            (CCSBAR + 0x60080 + (n)*0x1000)
#define T4_EPICEOIn(n)             (CCSBAR + 0x600b0 + (n)*0x1000)
#define EPIC_CTPR_MAX               15  /* maximum priority (mask) */
#define RESET_EOI_NUM               15  /* EOIs to send RM:31.5.1.3 */

#define T4_PVR                     (CCSBAR + 0xE00A0)
#define T4_SVR                     (CCSBAR + 0xE00A4)

#define T4_BRR                     (CCSBAR + 0xE00E4)
#define T4_BSTRH                   (CCSBAR + 0x20)
#define T4_BSTRL                   (CCSBAR + 0x24)
#define T4_BSTAR                   (CCSBAR + 0x28)

/* Core reset status register */

#define T4_CRSTSR(n)               (CCSBAR + 0xE0400 + (n)*4)
#define CRSTSR_RST_WRT             0x08000000
#define CRSTSR_RST_MPIC            0x00800000
#define CRSTSR_RST_CORE            0x00080000
#define CRSTSR_READY               0x00008000
#define CRSTSR_RST_HRST            0x00000002
#define CRSTSR_RST_PORST           0x00000001

/* Reset configuration word status registers (0 <= n < 16) */

#define T4_RCWSR(n)                (CCSBAR + 0xE0100 + (n)*4)
#define MEM_PLL_RAT_MSK            0x003E0000
#define MEM_PLL_RAT_SFT            17
#define MEM_PLL_RAT                \
        ((T4_CSR_READ_32(T4_RCWSR(0)) & MEM_PLL_RAT_MSK) >> MEM_PLL_RAT_SFT)

#define SYS_PLL_RAT_MSK            0x3E000000
#define SYS_PLL_RAT_SFT            25
#define SYS_PLL_RAT                \
        ((T4_CSR_READ_32(T4_RCWSR(0)) & SYS_PLL_RAT_MSK) >> SYS_PLL_RAT_SFT)

#define CCN_PLL_RAT_MSK(n)        (0x3E000000 >> (8 * n))
#define CCN_PLL_RAT_SFT(n)        (25 - (8 * n))
#define CCN_PLL_RAT(n)            \
        ((T4_CSR_READ_32(T4_RCWSR(2)) & CCN_PLL_RAT_MSK(n)) >> CCN_PLL_RAT_SFT(n))

#define CN_PLL_SEL_MSK(n)         (0xF0000000 >> (4 * n))
#define CN_PLL_SEL_SFT(n)         (28 - (4 * n))
#define CN_PLL_SEL(n)             \
        ((T4_CSR_READ_32(T4_RCWSR(3)) & CN_PLL_SEL_MSK(n)) >> CN_PLL_SEL_SFT(n))

#define SRDS_PRTCL                ((T4_CSR_READ_32(T4_RCWSR(4)) & 0xfc000000) >> 26)

/* Timebase enable register */

#define T4_CTBENR                 (CCSBAR + 0xE21A0)

#define T4_RSTCR                  (CCSBAR + 0xE00B0)

/* Branch Unit Control and Status Register (BUCSR) bit defines */

#define _PPC_BUCSR_FI               0x200       /* Invalidate branch cache */
#define _PPC_BUCSR_E                0x1         /* Enable branch prediction */

/* MMU and CACHE defines used in romInit.s */

#ifndef MMU_STATE_IPROT
#   define MMU_STATE_IPROT          0x40000000
#endif /* MMU_STATE_IPROT */

#define MMU_ROM_ACCESS              (_MMU_TLB_ATTR_W | \
                                     _MMU_TLB_ATTR_M | \
                                     _MMU_TLB_ATTR_G)

#define MMU_UNCACHED                (_MMU_TLB_ATTR_I | \
                                     _MMU_TLB_ATTR_G)
#define MMU_CACHED                  _MMU_TLB_ATTR_M

#define MMU_IO_ACCESS               MMU_UNCACHED  /* WIMGE bits for IO */

#define T4_CSR_READ_8(x)		\
	vxbRead8 ((void *)VXB_HANDLE_ORDERED , (UINT8 *)(x))

#define T4_CSR_WRITE_8(x, y)	\
	vxbWrite8 ((void *)VXB_HANDLE_ORDERED , (UINT8 *)(x), (y))

#define T4_CSR_READ_16(x)		\
	vxbRead16 ((void *)VXB_HANDLE_ORDERED , (UINT16 *)(x))

#define T4_CSR_WRITE_16(x, y)	\
	vxbWrite16 ((void *)VXB_HANDLE_ORDERED , (UINT16 *)(x), (y))

#define T4_CSR_SWAP_READ_16(x)		\
	vxbRead16 ((void *)VXB_HANDLE_SWAP(VXB_HANDLE_ORDERED ), (UINT16 *)(x))

#define T4_CSR_SWAP_WRITE_16(x, y)	\
	vxbWrite16 ((void *)VXB_HANDLE_SWAP(VXB_HANDLE_ORDERED ), (UINT16 *)(x), (y))

#define T4_CSR_READ_32(x)		\
	vxbRead32 ((void *)VXB_HANDLE_ORDERED , (UINT32 *)(x))

#define T4_CSR_WRITE_32(x, y)	\
	vxbWrite32 ((void *)VXB_HANDLE_ORDERED , (UINT32 *)(x), (y))

#define T4_CSR_SWAP_READ_32(x)		\
	vxbRead32 ((void *)VXB_HANDLE_SWAP(VXB_HANDLE_ORDERED ), (UINT32 *)(x))

#define T4_CSR_SWAP_WRITE_32(x, y)	\
	vxbWrite32 ((void *)VXB_HANDLE_SWAP(VXB_HANDLE_ORDERED ), (UINT32 *)(x), (y))

#ifdef __cplusplus
    }
#endif /* __cplusplus */

#endif /* __INCfslsocT4h */


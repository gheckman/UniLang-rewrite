/* omapIRQ.h - Interrupt IRQ definitions for LogicPD OMAP35x */

/*
 * Copyright (c) 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01d,07oct10,dbr  Add interrupts defs for GPIO
01c,05oct10,dbr  add interrupts defs for I2C
01b,20sep10,rdl  add support for MPU PRCM interrupts
01a,11aug10,chs  port to LogicPD board
*/

/*
This file contains definitions for mapping Interrupts on the LogicPD OMAP35x
board.

See Also OMAP35xx Applications Processor Technical Reference Manual,
 Texas Instruments.
*/

#ifndef __INComapIRQh
#define __INComapIRQh

#ifdef __cplusplus
extern "C" {
#endif

/* Interrupt priority */

#define OMAP_INT_PRI_UART_1          3 /* UART 1 */
#define OMAP_INT_PRI_UART_2          3 /* UART 2 */
#define OMAP_INT_PRI_UART_3          3 /* UART 3 */
#define OMAP_INT_PRI_I2C_1           4 /* I2C  1 */
#define OMAP_INT_PRI_I2C_2           4 /* I2C  2 */
#define OMAP_INT_PRI_I2C_3           4 /* I2C  3 */
#define OMAP_INT_PRI_TIMER_1         0 /* timer 1 */
#define OMAP_INT_PRI_TIMER_2         6 /* timer 2 */
#define OMAP_INT_PRI_TIMER_3         8 /* timer 3 */
#define OMAP_INT_PRI_ENET            4 /* ethernet interrupt(GPIO-E) */
#define OMAP_INT_PRI_MAIL_U0_MPU     9 /* mailbox interrupt */
#define OMAP_INT_PRI_IVA2_MMU        9 /* iva2 subsystem interrupt */ 
#define OMAP_INT_PRI_MHCI            10 /* mhci */
#define OMAP_INT_PRI_GPIO_1          7 /* GPIO module 1 */
#define OMAP_INT_PRI_GPIO_2          7 /* GPIO module 2 */
#define OMAP_INT_PRI_GPIO_3          7 /* GPIO module 3 */
#define OMAP_INT_PRI_GPIO_4          7 /* GPIO module 4 */
#define OMAP_INT_PRI_GPIO_5          7 /* GPIO module 5 */
#define OMAP_INT_PRI_GPIO_6          7 /* GPIO module 6 */

/* IRQ numbers */

#define OMAP_M_IRQ_0 0
#define OMAP_M_IRQ_1 1
#define OMAP_M_IRQ_2 2
#define OMAP_M_IRQ_3 3
#define OMAP_M_IRQ_4 4
#define OMAP_M_IRQ_5 5
#define OMAP_M_IRQ_6 6
#define OMAP_M_IRQ_7 7
#define OMAP_M_IRQ_8 8
#define OMAP_M_IRQ_9 9
#define OMAP_M_IRQ_10 10
#define OMAP_M_IRQ_11 11
#define OMAP_M_IRQ_12 12
#define OMAP_M_IRQ_13 13
#define OMAP_M_IRQ_14 14
#define OMAP_M_IRQ_15 15
#define OMAP_M_IRQ_16 16
#define OMAP_M_IRQ_17 17
#define OMAP_M_IRQ_18 18
#define OMAP_M_IRQ_19 19
#define OMAP_M_IRQ_20 20
#define OMAP_M_IRQ_21 21
#define OMAP_M_IRQ_22 22
#define OMAP_M_IRQ_23 23
#define OMAP_M_IRQ_24 24
#define OMAP_M_IRQ_25 25
#define OMAP_M_IRQ_26 26
#define OMAP_M_IRQ_27 27
#define OMAP_M_IRQ_28 28
#define OMAP_M_IRQ_29 29
#define OMAP_M_IRQ_30 30
#define OMAP_M_IRQ_31 31
#define OMAP_M_IRQ_32 32
#define OMAP_M_IRQ_33 33
#define OMAP_M_IRQ_34 34
#define OMAP_M_IRQ_35 35
#define OMAP_M_IRQ_36 36
#define OMAP_M_IRQ_37 37
#define OMAP_M_IRQ_38 38
#define OMAP_M_IRQ_39 39
#define OMAP_M_IRQ_40 40
#define OMAP_M_IRQ_41 41
#define OMAP_M_IRQ_42 42
#define OMAP_M_IRQ_43 43
#define OMAP_M_IRQ_44 44
#define OMAP_M_IRQ_45 45
#define OMAP_M_IRQ_46 46
#define OMAP_M_IRQ_47 47
#define OMAP_M_IRQ_48 48
#define OMAP_M_IRQ_49 49
#define OMAP_M_IRQ_50 50
#define OMAP_M_IRQ_51 51
#define OMAP_M_IRQ_52 52
#define OMAP_M_IRQ_53 53
#define OMAP_M_IRQ_54 54
#define OMAP_M_IRQ_55 55
#define OMAP_M_IRQ_56 56
#define OMAP_M_IRQ_57 57
#define OMAP_M_IRQ_58 58
#define OMAP_M_IRQ_59 59
#define OMAP_M_IRQ_60 60
#define OMAP_M_IRQ_61 61
#define OMAP_M_IRQ_62 62
#define OMAP_M_IRQ_63 63
#define OMAP_M_IRQ_64 64
#define OMAP_M_IRQ_65 65
#define OMAP_M_IRQ_66 66
#define OMAP_M_IRQ_67 67
#define OMAP_M_IRQ_68 68
#define OMAP_M_IRQ_69 69
#define OMAP_M_IRQ_70 70
#define OMAP_M_IRQ_71 71
#define OMAP_M_IRQ_72 72
#define OMAP_M_IRQ_73 73
#define OMAP_M_IRQ_74 74
#define OMAP_M_IRQ_75 75
#define OMAP_M_IRQ_76 76
#define OMAP_M_IRQ_77 77
#define OMAP_M_IRQ_78 78
#define OMAP_M_IRQ_79 79
#define OMAP_M_IRQ_80 80
#define OMAP_M_IRQ_81 81
#define OMAP_M_IRQ_82 82
#define OMAP_M_IRQ_83 83
#define OMAP_M_IRQ_84 84
#define OMAP_M_IRQ_85 85
#define OMAP_M_IRQ_86 86
#define OMAP_M_IRQ_87 87
#define OMAP_M_IRQ_88 88
#define OMAP_M_IRQ_89 89
#define OMAP_M_IRQ_90 90
#define OMAP_M_IRQ_91 91
#define OMAP_M_IRQ_92 92
#define OMAP_M_IRQ_93 93
#define OMAP_M_IRQ_94 94
#define OMAP_M_IRQ_95 95

#define OMAP_TOP_MPU_IRQ  OMAP_M_IRQ_95 + 1

/* Interrupt Mappings to the MPU Subsystem */

#define OMAP_EMUINT        OMAP_M_IRQ_0    /* MPU emulation(2) */
#define OMAP_COMMTX        OMAP_M_IRQ_1    /* MPU emulation(2) */
#define OMAP_COMMRX        OMAP_M_IRQ_2    /* MPU emulation(2) */
#define OMAP_BENCH         OMAP_M_IRQ_3    /* MPU emulation(2) */
#define OMAP_MCBSP2_ST_IRQ OMAP_M_IRQ_4    /* Sidetone MCBSP2 overflow */
#define OMAP_MCBSP3_ST_IRQ OMAP_M_IRQ_5    /* Sidetone MCBSP3 overflow */
#define OMAP_SSM_ABORT_IRQ OMAP_M_IRQ_6    /* MPU subsys secure st-mach abrt */
#define OMAP_SYS_NIRQ      OMAP_M_IRQ_7    /* External source (active low) */
#define OMAP_SMX_DBG_IRQ   OMAP_M_IRQ_9    /* SMX error for debug */
#define OMAP_SMX_APP_IRQ   OMAP_M_IRQ_10   /* SMX error for application */
#define OMAP_PRCM_MPU_IRQ  OMAP_M_IRQ_11   /* PRCM module IRQ */
#define OMAP_SDMA_IRQ0     OMAP_M_IRQ_12   /* System DMA request 0(3) */
#define OMAP_SDMA_IRQ1     OMAP_M_IRQ_13   /* System DMA request 1(3) */
#define OMAP_SDMA_IRQ2     OMAP_M_IRQ_14   /* System DMA request 2 */
#define OMAP_SDMA_IRQ3     OMAP_M_IRQ_15   /* System DMA request 3 */
#define OMAP_MCBSP1_IRQ    OMAP_M_IRQ_16   /* McBSP module 1 IRQ (3) */
#define OMAP_MCBSP2_IRQ    OMAP_M_IRQ_17   /* McBSP module 2 IRQ (3) */
#define OMAP_SR1_IRQ       OMAP_M_IRQ_18   /* SmartReflex 1 */
#define OMAP_SR2_IRQ       OMAP_M_IRQ_19   /* SmartReflex 2 */
#define OMAP_GPMC_IRQ      OMAP_M_IRQ_20   /* General-purpose mem ctrlr */
#define OMAP_SGX_IRQ       OMAP_M_IRQ_21   /* 2D/3D graphics module */
#define OMAP_MCBSP3_IRQ    OMAP_M_IRQ_22   /* McBSP module 3(3) */
#define OMAP_MCBSP4_IRQ    OMAP_M_IRQ_23   /* McBSP module 4(3) */
#define OMAP_CAOMAP_M_IRQ0 OMAP_M_IRQ_24   /* Camera interface request 0 */
#define OMAP_DSS_IRQ       OMAP_M_IRQ_25   /* Display subsystem module(3) */
#define OMAP_MAIL_U0_MPU_IRQ OMAP_M_IRQ_26 /* Mailbox user 0 request */
#define OMAP_MCBSP5_IRQ    OMAP_M_IRQ_27   /* McBSP module 5 (3) */
#define OMAP_IVA2_MMU_IRQ  OMAP_M_IRQ_28   /* IVA2 MMU */
#define OMAP_GPIO1_MPU_IRQ OMAP_M_IRQ_29   /* GPIO module 1(3) */
#define OMAP_GPIO2_MPU_IRQ OMAP_M_IRQ_30   /* GPIO module 2(3) */
#define OMAP_GPIO3_MPU_IRQ OMAP_M_IRQ_31   /* GPIO module 3(3) */
#define OMAP_GPIO4_MPU_IRQ OMAP_M_IRQ_32   /* GPIO module 4(3) */
#define OMAP_GPIO5_MPU_IRQ OMAP_M_IRQ_33   /* GPIO module 5(3) */
#define OMAP_GPIO6_MPU_IRQ OMAP_M_IRQ_34   /* GPIO module 6(3) */
#define OMAP_USIOMAP_M_IRQ OMAP_M_IRQ_35   /* USIM interrupt (HS devs)(4) */
#define OMAP_WDT3_IRQ      OMAP_M_IRQ_36   /* Watchdog timer module 3 ovrflow */
#define OMAP_GPT1_IRQ      OMAP_M_IRQ_37   /* General-purpose timer module 1 */
#define OMAP_GPT2_IRQ      OMAP_M_IRQ_38   /* General-purpose timer module 2 */
#define OMAP_GPT3_IRQ      OMAP_M_IRQ_39   /* General-purpose timer module 3 */
#define OMAP_GPT4_IRQ      OMAP_M_IRQ_40   /* General-purpose timer module 4 */
#define OMAP_GPT5_IRQ      OMAP_M_IRQ_41   /* General-purpose timer mod 5(3) */
#define OMAP_GPT6_IRQ      OMAP_M_IRQ_42   /* General-purpose timer mod 6(3) */
#define OMAP_GPT7_IRQ      OMAP_M_IRQ_43   /* General-purpose timer mod 7(3) */
#define OMAP_GPT8_IRQ      OMAP_M_IRQ_44   /* General-purpose timer mod 8(3) */
#define OMAP_GPT9_IRQ      OMAP_M_IRQ_45   /* General-purpose timer module 9 */
#define OMAP_GPT10_IRQ     OMAP_M_IRQ_46   /* General-purpose timer module 10 */
#define OMAP_GPT11_IRQ     OMAP_M_IRQ_47   /* General-purpose timer module 11 */
#define OMAP_SPI4_IRQ      OMAP_M_IRQ_48   /* McSPI module 4 */
#define OMAP_SHA1MD5_IRQ2  OMAP_M_IRQ_49   /* SHA-1/MD5 crypto-acc 2(HS devs) */
#define OMAP_FPKA_IRQREADY_N OMAP_M_IRQ_50   /* PKA crypto-accel (HS devs) */
#define OMAP_SHA2MD5_IRQ   OMAP_M_IRQ_51   /* SHA-2/MD5 crypto-accel1(HS devs */
#define OMAP_RNG_IRQ       OMAP_M_IRQ_52   /* RNG module (HS devices only) */
#define OMAP_MG_IRQ        OMAP_M_IRQ_53   /* MG function (3) */
#define OMAP_MCBSP4_IRQ_TX OMAP_M_IRQ_54   /* McBSP module 4 transmit(3) */
#define OMAP_MCBSP4_IRQ_RX OMAP_M_IRQ_55   /* McBSP module 4 receive(3) */
#define OMAP_I2C1_IRQ      OMAP_M_IRQ_56   /* I2C module 1 */
#define OMAP_I2C2_IRQ      OMAP_M_IRQ_57   /* I2C module 2 */
#define OMAP_HDQ_IRQ       OMAP_M_IRQ_58   /* HDQ/One-wire */
#define OMAP_McBSP1_IRQ_TX OMAP_M_IRQ_59   /* McBSP module 1 transmit(3) */
#define OMAP_McBSP1_IRQ_RX OMAP_M_IRQ_60   /* McBSP module 1 receive(3) */
#define OMAP_I2C3_IRQ      OMAP_M_IRQ_61   /* I2C module 3 */
#define OMAP_McBSP2_IRQ_TX OMAP_M_IRQ_62   /* McBSP module 2 transmit(3) */
#define OMAP_McBSP2_IRQ_RX OMAP_M_IRQ_63   /* McBSP module 2 receive(3) */
#define OMAP_FPKA_IRQRERROR_N OMAP_M_IRQ_64   /* PKA crypto-accel (HS devs) */
#define OMAP_SPI1_IRQ      OMAP_M_IRQ_65   /* McSPI module 1 */
#define OMAP_SPI2_IRQ      OMAP_M_IRQ_66   /* McSPI module 2 */
#define OMAP_UART1_IRQ     OMAP_M_IRQ_72   /* UART module 1 */
#define OMAP_UART2_IRQ     OMAP_M_IRQ_73   /* UART module 2 */
#define OMAP_UART3_IRQ     OMAP_M_IRQ_74   /* UART module 3 (& infrared)(3) */
#define OMAP_PBIAS_IRQ     OMAP_M_IRQ_75   /* Merged itrpt for PBIASlite1 & 2 */
#define OMAP_OHCI_IRQ      OMAP_M_IRQ_76   /* OHCI ctrlr HSUSB MP Host Intrpt */
#define OMAP_EHCI_IRQ      OMAP_M_IRQ_77   /* EHCI ctrlr HSUSB MP Host Intrpt */
#define OMAP_TLL_IRQ       OMAP_M_IRQ_78   /* HSUSB MP TLL Interrupt */
#define OMAP_PARTHASH_IRQ  OMAP_M_IRQ_79   /* SHA2/MD5 crypto-accel 1 HS devs */
#define OMAP_MCBSP5_IRQ_TX OMAP_M_IRQ_81   /* McBSP module 5 transmit(3) */
#define OMAP_MCBSP5_IRQ_RX OMAP_M_IRQ_82   /* McBSP module 5 receive(3) */
#define OMAP_MMC1_IRQ      OMAP_M_IRQ_83   /* MMC/SD module 1 */
#define OMAP_MS_IRQ        OMAP_M_IRQ_84   /* MS-PRO module */
#define OMAP_MMC2_IRQ      OMAP_M_IRQ_86   /* MMC/SD module 2 */
#define OMAP_MPU_ICR_IRQ   OMAP_M_IRQ_87   /* MPU ICR */
#define OMAP_MCBSP3_IRQ_TX OMAP_M_IRQ_89   /* McBSP module 3 transmit(3) */
#define OMAP_MCBSP3_IRQ_RX OMAP_M_IRQ_90   /* McBSP module 3 receive(3) */
#define OMAP_SPI3_IRQ      OMAP_M_IRQ_91   /* McSPI module 3 */
#define OMAP_HSUSB_MC_NINT OMAP_M_IRQ_92   /* High-Speed USB OTG controller */
#define OMAP_HSUSB_DMA_NINT OMAP_M_IRQ_93  /* High-Speed USB OTG DMA ctrlr */
#define OMAP_MMC3_IRQ      OMAP_M_IRQ_94   /* MMC/SD module 3 */
#define OMAP_GPT12_IRQ     OMAP_M_IRQ_95   /* General-purpose timer module 12 */

#define OMAP_LAN9115_IRQ    OMAP_GPIO5_MPU_IRQ


/* MPU PRCM interrupts */

#define OMAP_MPU_PRCM_WKUP_IRQ                   (OMAP_TOP_MPU_IRQ + 0)
#define OMAP_MPU_PRCM_RESERVED_IRQ               (OMAP_TOP_MPU_IRQ + 1)
#define OMAP_MPU_PRCM_EVGENON_IRQ                (OMAP_TOP_MPU_IRQ + 2)
#define OMAP_MPU_PRCM_EVGENOFF_IRQ               (OMAP_TOP_MPU_IRQ + 3)
#define OMAP_MPU_PRCM_TRANSITION_IRQ             (OMAP_TOP_MPU_IRQ + 4)
#define OMAP_MPU_PRCM_CORE_DPLL_IRQ              (OMAP_TOP_MPU_IRQ + 5)
#define OMAP_MPU_PRCM_PERIPH_DPLL_IRQ            (OMAP_TOP_MPU_IRQ + 6)
#define OMAP_MPU_PRCM_MPU_DPLL_IRQ               (OMAP_TOP_MPU_IRQ + 7)
#define OMAP_MPU_PRCM_IVA2_DPLL_IRQ              (OMAP_TOP_MPU_IRQ + 8)
#define OMAP_MPU_PRCM_IO_IRQ                     (OMAP_TOP_MPU_IRQ + 9)
#define OMAP_MPU_PRCM_VP1_OPPCHANGEDONE_IRQ      (OMAP_TOP_MPU_IRQ + 10)
#define OMAP_MPU_PRCM_VP1_MINVDD_IRQ             (OMAP_TOP_MPU_IRQ + 11)
#define OMAP_MPU_PRCM_VP1_MAXVDD_IRQ             (OMAP_TOP_MPU_IRQ + 12)
#define OMAP_MPU_PRCM_VP1_NOSMPSACK_IRQ          (OMAP_TOP_MPU_IRQ + 13)
#define OMAP_MPU_PRCM_VP1_EQVALUE_IRQ            (OMAP_TOP_MPU_IRQ + 14)
#define OMAP_MPU_PRCM_VP1_TRANXDONE_IRQ          (OMAP_TOP_MPU_IRQ + 15)
#define OMAP_MPU_PRCM_VP2_OPPCHANGEDONE_IRQ      (OMAP_TOP_MPU_IRQ + 16)
#define OMAP_MPU_PRCM_VP2_MINVDD_IRQ             (OMAP_TOP_MPU_IRQ + 17)
#define OMAP_MPU_PRCM_VP2_MAXVDD_IRQ             (OMAP_TOP_MPU_IRQ + 18)
#define OMAP_MPU_PRCM_VP2_NOSMPSACK_IRQ          (OMAP_TOP_MPU_IRQ + 19)
#define OMAP_MPU_PRCM_VP2_EQVALUE_IRQ            (OMAP_TOP_MPU_IRQ + 20)
#define OMAP_MPU_PRCM_VP2_TRANXDONE_IRQ          (OMAP_TOP_MPU_IRQ + 21)
#define OMAP_MPU_PRCM_VC_SAERR_IRQ               (OMAP_TOP_MPU_IRQ + 22)
#define OMAP_MPU_PRCM_VC_RAERR_IRQ               (OMAP_TOP_MPU_IRQ + 23)
#define OMAP_MPU_PRCM_VC_TIMEOUTERR_IRQ          (OMAP_TOP_MPU_IRQ + 24)
#define OMAP_MPU_PRCM_SND_PERIPH_DPLL_RECAL_IRQ  (OMAP_TOP_MPU_IRQ + 25)


#ifdef __cplusplus
}
#endif

#endif /* __INComapIRQh */

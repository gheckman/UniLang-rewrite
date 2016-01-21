/* mcf5329.h - Freescale M5329 CPU control registers */

/*
 * Copyright (c) 2007, 2008, 2010 Wind River Systems, Inc.
 * 
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01g,29apr10,pad  Moved extern C statement after include statements.
01f,12mar08,rec  move multifunction header files to h/hwif/..
01e,01feb08,rec  WIND00116361 - add vxBus support
01d,21jun07,rec	 change macro prefix to MCF
01c,19jun07,rec	 fix comment format to prevent doc errors
01b,13jun07,rec	 initial version created for vxWorks 6.4
01a,12jun07,dpo	 Created
*/

/*
 * This file contains I/O addresses and related constants for the M532X5329.
 * Each section is referenced to the appropriate chapter in "M532X5329 Reference
 * Manual".
 */

#ifndef __INCMCF5329h
#define __INCMCF5329h

/*
 * Need to use a distinct cast macro in order to not conflict with other
 * include files.
 */

#ifdef	_ASMLANGUAGE
#define CAST_MCF(x)
#define CAST_MCF_VOL(x)
#define CAST_MCF_VOLPTR(x)
#else	/* _ASMLANGUAGE */
#define CAST_MCF(x)	    (x)
#define CAST_MCF_VOL(x)(volatile x *)
#define CAST_MCF_VOLPTR(x) *(volatile x *)
#endif	/* _ASMLANGUAGE */

/* Size of internal SRAM */
#define M5329_SRAM_SIZE		32768		/* size of SRAM */

/*
 *
 * Phase Locked Loop (PLL) - Chapter 7
 *
 */

/* Register read/write macros */
#define MCF_PLL_PODR	      ((volatile UINT8 *)(0xFC0C0000))
#define MCF_PLL_PLLCR	      ((volatile UINT8 *)(0xFC0C0004))
#define MCF_PLL_PMDR	      ((volatile UINT8 *)(0xFC0C0008))
#define MCF_PLL_PFDR	      0xFC0C000C

/* Bit definitions and macros for MCF_PLL_PODR */
#define MCF_PLL_PODR_BUSDIV(x)	  (((x)&0x0F)<<0)
#define MCF_PLL_PODR_CPUDIV(x)	  (((x)&0x0F)<<4)

/* Bit definitions and macros for MCF_PLL_PLLCR */
#define MCF_PLL_PLLCR_DITHDEV(x)  (((x)&0x07)<<0)
#define MCF_PLL_PLLCR_DITHEN	    (0x80)

/* Bit definitions and macros for MCF_PLL_PMDR */
#define MCF_PLL_PMDR_MODDIV(x)	  (((x)&0xFF)<<0)

/* Bit definitions and macros for MCF_PLL_PFDR */
#define MCF_PLL_PFDR_MFD(x)	    (((x)&0xFF)<<0)

/*
 *
 * Power Management Module (PMM) - Chapter 8
 *
 */

/* Register read/write macros */
#define MCF_PMM_WCR	      (*(volatile UINT8 *)(0xFC040013))
#define MCF_PMM_PPMSR0	      (*(volatile UINT8 *)(0xFC04002C))
#define MCF_PMM_PPMSR1	      (*(volatile UINT8 *)(0xFC04002E))
#define MCF_PMM_PPMCR0	      (*(volatile UINT8 *)(0xFC04002D))
#define MCF_PMM_PPMCR1	      (*(volatile UINT8 *)(0xFC04002F))
#define MCF_PMM_PPMHR0	      (*(volatile UINT32*)(0xFC040030))
#define MCF_PMM_PPMLR0	      (*(volatile UINT32*)(0xFC040034))
#define MCF_PMM_PPMHR1	      (*(volatile UINT32*)(0xFC040038))
#define MCF_PMM_LPCR	      (*(volatile UINT8 *)(0xFC0A0007))

/* Bit definitions and macros for MCF_PMM_WCR */
#define MCF_PMM_WCR_PRILVL(x)		    (((x)&0x07)<<0)
#define MCF_PMM_WCR_ENBWCR	      (0x80)

/* Bit definitions and macros for MCF_PMM_PPMSR */
#define MCF_PMM_PPMSR_SMCD(x)		    (((x)&0x3F)<<0)
#define MCF_PMM_PPMSR_SAMCD	      (0x40)

/* Bit definitions and macros for MCF_PMM_PPMCR */
#define MCF_PMM_PPMCR_CMCD(x)		    (((x)&0x3F)<<0)
#define MCF_PMM_PPMCR_CAMCD	      (0x40)

/* Bit definitions and macros for MCF_PMM_PPMHR0 */
#define MCF_PMM_PPMHR0_CD32	      (0x00000001)
#define MCF_PMM_PPMHR0_CD33	      (0x00000002)
#define MCF_PMM_PPMHR0_CD34	      (0x00000004)
#define MCF_PMM_PPMHR0_CD35	      (0x00000008)
#define MCF_PMM_PPMHR0_CD36	      (0x00000010)
#define MCF_PMM_PPMHR0_CD37	      (0x00000020)
#define MCF_PMM_PPMHR0_CD38	      (0x00000040)
#define MCF_PMM_PPMHR0_CD40	      (0x00000100)
#define MCF_PMM_PPMHR0_CD41	      (0x00000200)
#define MCF_PMM_PPMHR0_CD42	      (0x00000400)
#define MCF_PMM_PPMHR0_CD43	      (0x00000800)
#define MCF_PMM_PPMHR0_CD44	      (0x00001000)
#define MCF_PMM_PPMHR0_CD45	      (0x00002000)
#define MCF_PMM_PPMHR0_CD46	      (0x00004000)
#define MCF_PMM_PPMHR0_CD47	      (0x00008000)
#define MCF_PMM_PPMHR0_CD48	      (0x00010000)

/* Bit definitions and macros for MCF_PMM_PPMLR0 */
#define MCF_PMM_PPMLR0_CD2	      (0x00000004)
#define MCF_PMM_PPMLR0_CD8	      (0x00000100)
#define MCF_PMM_PPMLR0_CD12	      (0x00001000)
#define MCF_PMM_PPMLR0_CD17	      (0x00020000)
#define MCF_PMM_PPMLR0_CD18	      (0x00040000)
#define MCF_PMM_PPMLR0_CD19	      (0x00080000)
#define MCF_PMM_PPMLR0_CD21	      (0x00200000)
#define MCF_PMM_PPMLR0_CD22	      (0x00400000)
#define MCF_PMM_PPMLR0_CD23	      (0x00800000)
#define MCF_PMM_PPMLR0_CD24	      (0x01000000)
#define MCF_PMM_PPMLR0_CD25	      (0x02000000)
#define MCF_PMM_PPMLR0_CD26	      (0x04000000)
#define MCF_PMM_PPMLR0_CD28	      (0x10000000)
#define MCF_PMM_PPMLR0_CD29	      (0x20000000)
#define MCF_PMM_PPMLR0_CD30	      (0x40000000)
#define MCF_PMM_PPMLR0_CD31	      (0x80000000)

/* Bit definitions and macros for MCF_PMM_PPMHR1 */
#define MCF_PMM_PPMHR1_CD32	      (0x00000001)
#define MCF_PMM_PPMHR1_CD33	      (0x00000002)
#define MCF_PMM_PPMHR1_CD34	      (0x00000004)

/* Bit definitions and macros for MCF_PMM_LPCR */
#define MCF_PMM_LPCR_STPMD(x)	      (((x)&0x03)<<3)
#define MCF_PMM_LPCR_FWKUP	      (0x20)
#define MCF_PMM_LPCR_LPMD(x)	      (((x)&0x03)<<6)
#define MCF_PMM_LPCR_LPMD_RUN	      (0x00)
#define MCF_PMM_LPCR_LPMD_DOZE	      (0x40)
#define MCF_PMM_LPCR_LPMD_WAIT	      (0x80)
#define MCF_PMM_LPCR_LPMD_STOP	      (0xC0)
#define MCF_PMM_LPCR_STPMD_SYS_DISABLED		(0x00)
#define MCF_PMM_LPCR_STPMD_SYS_BUSCLK_DISABLED	(0x04)
#define MCF_PMM_LPCR_STPMD_ONLY_OSC_ENABLED	(0x08)
#define MCF_PMM_LPCR_STPMD_ALL_DISABLED		(0x0C)

/*
 *
 * Chip Configuration Module (CCM) - Chapter 9
 *
 */

/* Register read/write macros */
#define MCF_CCM_CCR	      ((volatile UINT16*)(0xFC0A0004))
#define MCF_CCM_CCREG	      0xFC0A0004
#define MCF_CCM_RCON	      ((volatile UINT16*)(0xFC0A0008))
#define MCF_CCM_CIR	      ((volatile UINT16*)(0xFC0A000A))
#define MCF_CCM_MISCCR	      ((volatile UINT16*)(0xFC0A0010))
#define MCF_CCM_MISCCREG      0xFC0A0010
#define MCF_CCM_CDR	      ((volatile UINT16*)(0xFC0A0012))
#define MCF_CCM_CDREG	      0xFC0A0012
#define MCF_CCM_UHCSR	      ((volatile UINT16*)(0xFC0A0014))
#define MCF_CCM_UOCSR	      ((volatile UINT16*)(0xFC0A0016))

/* Bit definitions and macros for MCF_CCM_CCR */
#define MCF_CCM_CCR_RESERVED	    (0x0001)
#define MCF_CCM_CCR_PLL_MODE	    (0x0003)
#define MCF_CCM_CCR_OSC_MODE	    (0x0005)
#define MCF_CCM_CCR_BOOTPS(x)	    (((x)&0x0003)<<3|0x0001)
#define MCF_CCM_CCR_LOAD	    (0x0021)
#define MCF_CCM_CCR_LIMP	    (0x0041)
#define MCF_CCM_CCR_CSC(x)	    (((x)&0x0003)<<8|0x0001)

/* Bit definitions and macros for MCF_CCM_RCON */
#define MCF_CCM_RCON_RESERVED	    (0x0001)
#define MCF_CCM_RCON_PLL_MODE	    (0x0003)
#define MCF_CCM_RCON_OSC_MODE	    (0x0005)
#define MCF_CCM_RCON_BOOTPS(x)	    (((x)&0x0003)<<3|0x0001)
#define MCF_CCM_RCON_LOAD	    (0x0021)
#define MCF_CCM_RCON_LIMP	    (0x0041)
#define MCF_CCM_RCON_CSC(x)	    (((x)&0x0003)<<8|0x0001)

/* Bit definitions and macros for MCF_CCM_CIR */
#define MCF_CCM_CIR_PRN(x)	    (((x)&0x003F)<<0)
#define MCF_CCM_CIR_PIN(x)	    (((x)&0x03FF)<<6)

/* Bit definitions and macros for MCF_CCM_MISCCR */
#define MCF_CCM_MISCCR_USBSRC	    (0x0001)
#define MCF_CCM_MISCCR_USBDIV	    (0x0002)
#define MCF_CCM_MISCCR_SSI_SRC	    (0x0010)
#define MCF_CCM_MISCCR_TIM_DMA	    (0x0020)
#define MCF_CCM_MISCCR_SSI_PUS	    (0x0040)
#define MCF_CCM_MISCCR_SSI_PUE	    (0x0080)
#define MCF_CCM_MISCCR_LCD_CHEN	    (0x0100)
#define MCF_CCM_MISCCR_LIMP	    (0x1000)
#define MCF_CCM_MISCCR_PLL_LOCK	    (0x2000)

/* Bit definitions and macros for MCF_CCM_CDR */
#define MCF_CCM_CDR_SSIDIV(x)	    (((x)&0x000F)<<0)
#define MCF_CCM_CDR_LPDIV(x)	    (((x)&0x000F)<<8)

/* Bit definitions and macros for MCF_CCM_UHCSR */
#define MCF_CCM_UHCSR_XPDE	    (0x0001)
#define MCF_CCM_UHCSR_UHMIE	    (0x0002)
#define MCF_CCM_UHCSR_WKUP	    (0x0004)
#define MCF_CCM_UHCSR_PORTIND(x)  (((x)&0x0003)<<14)

/* Bit definitions and macros for MCF_CCM_UOCSR */
#define MCF_CCM_UOCSR_XPDE	    (0x0001)
#define MCF_CCM_UOCSR_UOMIE	    (0x0002)
#define MCF_CCM_UOCSR_WKUP	    (0x0004)
#define MCF_CCM_UOCSR_PWRFLT	    (0x0008)
#define MCF_CCM_UOCSR_SEND	    (0x0010)
#define MCF_CCM_UOCSR_VVLD	    (0x0020)
#define MCF_CCM_UOCSR_BVLD	    (0x0040)
#define MCF_CCM_UOCSR_AVLD	    (0x0080)
#define MCF_CCM_UOCSR_DPPU	    (0x0100)
#define MCF_CCM_UOCSR_DCR_VBUS	    (0x0200)
#define MCF_CCM_UOCSR_CRG_VBUS	    (0x0400)
#define MCF_CCM_UOCSR_DRV_VBUS	    (0x0800)
#define MCF_CCM_UOCSR_DMPD	    (0x1000)
#define MCF_CCM_UOCSR_DPPD	    (0x2000)
#define MCF_CCM_UOCSR_PORTIND(x)    (((x)&0x0003)<<14)

/*
 *
 * Reset Controller Module (RCM) - Chapter 10
 *
 */

/* Register read/write macros */
#define MCF_RCM_RCR	   (*(volatile UINT8 *)(0xFC0A0000))
#define MCF_RCM_RSR	   (*(volatile UINT8 *)(0xFC0A0001))

/* Bit definitions and macros for MCF_RCM_RCR */
#define MCF_RCM_RCR_FRCRSTOUT	 (0x40)
#define MCF_RCM_RCR_SOFTRST	 (0x80)

/* Bit definitions and macros for MCF_RCM_RSR */
#define MCF_RCM_RSR_LOL	 (0x01)
#define MCF_RCM_RSR_WDR_CORE	 (0x02)
#define MCF_RCM_RSR_EXT	 (0x04)
#define MCF_RCM_RSR_POR	 (0x08)
#define MCF_RCM_RSR_WDR_CHIP	 (0x10)
#define MCF_RCM_RSR_SOFT	 (0x20)

/*
 *
 * System Control Module (SCM) - Chapter 11
 *
 */

/* Register read/write macros */
#define MCF_SCM_MPR0		(*(volatile UINT32*)(0xEC000000))
#define MCF_SCM_MPR1		(*(volatile UINT32*)(0xFC000000))
#define MCF_SCM_BMT0		(*(volatile UINT32*)(0xEC000054))
#define MCF_SCM_BMT1		(*(volatile UINT32*)(0xFC000054))
#define MCF_SCM_PACRA		(*(volatile UINT32*)(0xFC000020))
#define MCF_SCM_PACRB		(*(volatile UINT32*)(0xFC000024))
#define MCF_SCM_PACRC		(*(volatile UINT32*)(0xFC000028))
#define MCF_SCM_PACRD		(*(volatile UINT32*)(0xFC00002C))
#define MCF_SCM_PACRE		(*(volatile UINT32*)(0xFC000040))
#define MCF_SCM_PACRF		(*(volatile UINT32*)(0xFC000044))
#define MCF_SCM_PACRG		(*(volatile UINT32*)(0xEC000048))
#define MCF_SCM_PACRH		(*(volatile UINT32*)(0xEC000040))
#define MCF_SCM_CWCR		(*(volatile UINT16*)(0xFC040016))
#define MCF_SCM_CWSR		(*(volatile UINT8 *)(0xFC04001B))
#define MCF_SCM_CWIR		(*(volatile UINT8 *)(0xFC04001F))
#define MCF_SCM_BCR		(*(volatile UINT32*)(0xFC040024))
#define MCF_SCM_CFADR		(*(volatile UINT32*)(0xFC040070))
#define MCF_SCM_CFIER		(*(volatile UINT8 *)(0xFC040075))
#define MCF_SCM_CFLOC		(*(volatile UINT8 *)(0xFC040076))
#define MCF_SCM_CFATR		(*(volatile UINT8 *)(0xFC040077))
#define MCF_SCM_CFDTR		(*(volatile UINT32*)(0xFC04007C))

/* Bit definitions and macros for MCF_SCM_MPR */
#define MCF_SCM_MPR_MPROT6(x)	      (((x)&0x0000000F)<<4)
#define MCF_SCM_MPR_MPROT5(x)	      (((x)&0x0000000F)<<8)
#define MCF_SCM_MPR_MPROT4(x)	      (((x)&0x0000000F)<<12)
#define MCF_SCM_MPR_MPROT2(x)	      (((x)&0x0000000F)<<20)
#define MCF_SCM_MPR_MPROT1(x)	      (((x)&0x0000000F)<<24)
#define MCF_SCM_MPR_MPROT0(x)	      (((x)&0x0000000F)<<28)
#define MCF_SCM_MPR_MPROT_MTR	      (0x4)
#define MCF_SCM_MPR_MPROT_MTW	      (0x2)
#define MCF_SCM_MPR_MPROT_MPL	      (0x1)

/* Bit definitions and macros for MCF_SCM_BMT */
#define MCF_SCM_BMT_BMT(x)	      (((x)&0x00000007)<<0)
#define MCF_SCM_BMT_BME		      (0x00000008)
#define MCF_SCM_BMT_BMT_1024	      (0x00000000)
#define MCF_SCM_BMT_BMT_512	      (0x00000001)
#define MCF_SCM_BMT_BMT_256	      (0x00000002)
#define MCF_SCM_BMT_BMT_128	      (0x00000003)
#define MCF_SCM_BMT_BMT_64	      (0x00000004)
#define MCF_SCM_BMT_BMT_32	      (0x00000005)
#define MCF_SCM_BMT_BMT_16	      (0x00000006)
#define MCF_SCM_BMT_BMT_8	      (0x00000007)

/* Bit definitions and macros for MCF_SCM_PACRA */
#define MCF_SCM_PACRA_PACR2(x)	      (((x)&0x0000000F)<<20)
#define MCF_SCM_PACRA_PACR1(x)	      (((x)&0x0000000F)<<24)
#define MCF_SCM_PACRA_PACR0(x)	      (((x)&0x0000000F)<<28)
#define MCF_SCM_PACRA_PACR_SP	      (0x4)
#define MCF_SCM_PACRA_PACR_WP	      (0x2)
#define MCF_SCM_PACRA_PACR_TP	      (0x1)

/* Bit definitions and macros for MCF_SCM_PACRB */
#define MCF_SCM_PACRB_PACR12(x)	    (((x)&0x0000000F)<<12)
#define MCF_SCM_PACRB_PACR8(x)	    (((x)&0x0000000F)<<28)

/* Bit definitions and macros for MCF_SCM_PACRC */
#define MCF_SCM_PACRC_PACR23(x)	    (((x)&0x0000000F)<<0)
#define MCF_SCM_PACRC_PACR22(x)	    (((x)&0x0000000F)<<4)
#define MCF_SCM_PACRC_PACR21(x)	    (((x)&0x0000000F)<<8)
#define MCF_SCM_PACRC_PACR19(x)	    (((x)&0x0000000F)<<16)
#define MCF_SCM_PACRC_PACR18(x)	    (((x)&0x0000000F)<<20)
#define MCF_SCM_PACRC_PACR17(x)	    (((x)&0x0000000F)<<24)
#define MCF_SCM_PACRC_PACR16(x)	    (((x)&0x0000000F)<<28)

/* Bit definitions and macros for MCF_SCM_PACRD */
#define MCF_SCM_PACRD_PACR31(x)	    (((x)&0x0000000F)<<0)
#define MCF_SCM_PACRD_PACR30(x)	    (((x)&0x0000000F)<<4)
#define MCF_SCM_PACRD_PACR29(x)	    (((x)&0x0000000F)<<8)
#define MCF_SCM_PACRD_PACR28(x)	    (((x)&0x0000000F)<<12)
#define MCF_SCM_PACRD_PACR26(x)	    (((x)&0x0000000F)<<20)
#define MCF_SCM_PACRD_PACR25(x)	    (((x)&0x0000000F)<<24)
#define MCF_SCM_PACRD_PACR24(x)	    (((x)&0x0000000F)<<28)

/* Bit definitions and macros for MCF_SCM_PACRE */
#define MCF_SCM_PACRE_PACR38(x)	    (((x)&0x0000000F)<<4)
#define MCF_SCM_PACRE_PACR37(x)	    (((x)&0x0000000F)<<8)
#define MCF_SCM_PACRE_PACR36(x)	    (((x)&0x0000000F)<<12)
#define MCF_SCM_PACRE_PACR35(x)	    (((x)&0x0000000F)<<16)
#define MCF_SCM_PACRE_PACR34(x)	    (((x)&0x0000000F)<<20)
#define MCF_SCM_PACRE_PACR33(x)	    (((x)&0x0000000F)<<24)
#define MCF_SCM_PACRE_PACR32(x)	    (((x)&0x0000000F)<<28)

/* Bit definitions and macros for MCF_SCM_PACRF */
#define MCF_SCM_PACRF_PACR47(x)	    (((x)&0x0000000F)<<0)
#define MCF_SCM_PACRF_PACR46(x)	    (((x)&0x0000000F)<<4)
#define MCF_SCM_PACRF_PACR45(x)	    (((x)&0x0000000F)<<8)
#define MCF_SCM_PACRF_PACR44(x)	    (((x)&0x0000000F)<<12)
#define MCF_SCM_PACRF_PACR43(x)	    (((x)&0x0000000F)<<16)
#define MCF_SCM_PACRF_PACR42(x)	    (((x)&0x0000000F)<<20)
#define MCF_SCM_PACRF_PACR41(x)	    (((x)&0x0000000F)<<24)
#define MCF_SCM_PACRF_PACR40(x)	    (((x)&0x0000000F)<<28)

/* Bit definitions and macros for MCF_SCM_PACRG */
#define MCF_SCM_PACRG_PACR48(x)	    (((x)&0x0000000F)<<28)

/* Bit definitions and macros for MCF_SCM_PACRH */
#define MCF_SCM_PACRH_PACR58(x)	    (((x)&0x0000000F)<<20)
#define MCF_SCM_PACRH_PACR57(x)	    (((x)&0x0000000F)<<24)
#define MCF_SCM_PACRH_PACR56(x)	    (((x)&0x0000000F)<<28)

/* Bit definitions and macros for MCF_SCM_CWCR */
#define MCF_SCM_CWCR_CWT(x)	      (((x)&0x001F)<<0)
#define MCF_SCM_CWCR_CWRI(x)	      (((x)&0x0003)<<5)
#define MCF_SCM_CWCR_CWE	      (0x0080)
#define MCF_SCM_CWCR_CWR_WH	      (0x0100)
#define MCF_SCM_CWCR_RO		      (0x8000)
#define MCF_SCM_CWCR_CWRI_INT	      (0x0000)
#define MCF_SCM_CWCR_CWRI_INT_THEN_RESET  (0x0020)
#define MCF_SCM_CWCR_CWRI_RESET	      (0x0040)
#define MCF_SCM_CWCR_CWRI_WINDOW      (0x0060)

/* Bit definitions and macros for MCF_SCM_CWSR */
#define MCF_SCM_CWSR_CWSR(x)	      (((x)&0xFF)<<0)

/* Bit definitions and macros for MCF_SCM_CWIR */
#define MCF_SCM_CWIR_CWIC	      (0x01)
#define MCF_SCM_CWIR_CFEI	      (0x02)

/* Bit definitions and macros for MCF_SCM_BCR */
#define MCF_SCM_BCR_S1		(0x00000002)
#define MCF_SCM_BCR_S4		(0x00000010)
#define MCF_SCM_BCR_S6		(0x00000040)
#define MCF_SCM_BCR_S7		(0x00000080)
#define MCF_SCM_BCR_GBW		(0x00000100)
#define MCF_SCM_BCR_GBR		(0x00000200)

/* Bit definitions and macros for MCF_SCM_CFADR */
#define MCF_SCM_CFADR_ADDR(x)	      (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF_SCM_CFIER */
#define MCF_SCM_CFIER_ECFEI	      (0x01)

/* Bit definitions and macros for MCF_SCM_CFLOC */
#define MCF_SCM_CFLOC_LOC	      (0x80)

/* Bit definitions and macros for MCF_SCM_CFATR */
#define MCF_SCM_CFATR_TYPE	      (0x01)
#define MCF_SCM_CFATR_MODE	      (0x02)
#define MCF_SCM_CFATR_CACHE	      (0x08)
#define MCF_SCM_CFATR_SIZE(x)	      (((x)&0x07)<<4)
#define MCF_SCM_CFATR_WRITE	      (0x80)

/* Bit definitions and macros for MCF_SCM_CFDTR */
#define MCF_SCM_CFDTR_CFDTR(x)	    (((x)&0xFFFFFFFF)<<0)

/*
 *
 * Cross-bar switch (XBS) - Chapter 12
 *
 */

/* Register read/write macros */
#define MCF_XBS_PRS1	       (*(volatile UINT32*)(0xFC004100))
#define MCF_XBS_PRS2	       (*(volatile UINT32*)(0xFC004200))
#define MCF_XBS_PRS3	       (*(volatile UINT32*)(0xFC004300))
#define MCF_XBS_PRS4	       (*(volatile UINT32*)(0xFC004400))
#define MCF_XBS_PRS5	       (*(volatile UINT32*)(0xFC004500))
#define MCF_XBS_PRS6	       (*(volatile UINT32*)(0xFC004600))
#define MCF_XBS_PRS7	       (*(volatile UINT32*)(0xFC004700))
#define MCF_XBS_PRS(x)	       (*(volatile UINT32*)(0xFC004100+((x-1)*0x100)))
#define MCF_XBS_CRS1	       (*(volatile UINT32*)(0xFC004110))
#define MCF_XBS_CRS2	       (*(volatile UINT32*)(0xFC004210))
#define MCF_XBS_CRS3	       (*(volatile UINT32*)(0xFC004310))
#define MCF_XBS_CRS4	       (*(volatile UINT32*)(0xFC004410))
#define MCF_XBS_CRS5	       (*(volatile UINT32*)(0xFC004510))
#define MCF_XBS_CRS6	       (*(volatile UINT32*)(0xFC004610))
#define MCF_XBS_CRS7	       (*(volatile UINT32*)(0xFC004710))
#define MCF_XBS_CRS(x)	       (*(volatile UINT32*)(0xFC004110+((x-1)*0x100)))

/* Bit definitions and macros for MCF_XBS_PRS */
#define MCF_XBS_PRS_M0(x)	     (((x)&0x00000007)<<0)
#define MCF_XBS_PRS_M1(x)	     (((x)&0x00000007)<<4)
#define MCF_XBS_PRS_M2(x)	     (((x)&0x00000007)<<8)
#define MCF_XBS_PRS_M4(x)	     (((x)&0x00000007)<<16)
#define MCF_XBS_PRS_M5(x)	     (((x)&0x00000007)<<20)
#define MCF_XBS_PRS_M6(x)	     (((x)&0x00000007)<<24)

/* Bit definitions and macros for MCF_XBS_CRS */
#define MCF_XBS_CRS_PARK(x)	     (((x)&0x00000007)<<0)
#define MCF_XBS_CRS_PCTL(x)	     (((x)&0x00000003)<<4)
#define MCF_XBS_CRS_ARB		     (0x00000100)
#define MCF_XBS_CRS_RO		     (0x80000000)
#define MCF_XBS_CRS_PCTL_PARK_FIELD	   (0x00000000)
#define MCF_XBS_CRS_PCTL_PARK_ON_LAST	   (0x00000010)
#define MCF_XBS_CRS_PCTL_PARK_NO_MASTER	   (0x00000020)
#define MCF_XBS_CRS_PCTL_PARK_CORE	   (0x00000000)
#define MCF_XBS_CRS_PCTL_PARK_EDMA	   (0x00000001)
#define MCF_XBS_CRS_PCTL_PARK_FEC	   (0x00000002)

/*
 *
 * General Purpose I/O (GPIO) - Chapter 13
 *
 */

/* Register read/write macros */
#define MCF_GPIO_PODR_FECH		 ((volatile UINT8 *)(0xFC0A4000))
#define MCF_GPIO_PODR_FECL		 ((volatile UINT8 *)(0xFC0A4001))
#define MCF_GPIO_PODR_SSI		 ((volatile UINT8 *)(0xFC0A4002))
#define MCF_GPIO_PODR_BUSCTL		 ((volatile UINT8 *)(0xFC0A4003))
#define MCF_GPIO_PODR_BE		 ((volatile UINT8 *)(0xFC0A4004))
#define MCF_GPIO_PODR_CS		 ((volatile UINT8 *)(0xFC0A4005))
#define MCF_GPIO_PODR_PWM		 ((volatile UINT8 *)(0xFC0A4006))
#define MCF_GPIO_PODR_FECI2C		 ((volatile UINT8 *)(0xFC0A4007))
#define MCF_GPIO_PODR_UART		 ((volatile UINT8 *)(0xFC0A4009))
#define MCF_GPIO_PODR_QSPI		 ((volatile UINT8 *)(0xFC0A400A))
#define MCF_GPIO_PODR_TIMER		 ((volatile UINT8 *)(0xFC0A400B))
#define MCF_GPIO_PODR_LCDDATAH		 ((volatile UINT8 *)(0xFC0A400D))
#define MCF_GPIO_PODR_LCDDATAM		 ((volatile UINT8 *)(0xFC0A400E))
#define MCF_GPIO_PODR_LCDDATAL		 ((volatile UINT8 *)(0xFC0A400F))
#define MCF_GPIO_PODR_LCDCTLH		 ((volatile UINT8 *)(0xFC0A4010))
#define MCF_GPIO_PODR_LCDCTLL		 ((volatile UINT8 *)(0xFC0A4011))
#define MCF_GPIO_PDDR_FECH		 ((volatile UINT8 *)(0xFC0A4014))
#define MCF_GPIO_PDDR_FECL		 ((volatile UINT8 *)(0xFC0A4015))
#define MCF_GPIO_PDDR_SSI		 ((volatile UINT8 *)(0xFC0A4016))
#define MCF_GPIO_PDDR_BUSCTL		 ((volatile UINT8 *)(0xFC0A4017))
#define MCF_GPIO_PDDR_BE		 ((volatile UINT8 *)(0xFC0A4018))
#define MCF_GPIO_PDDR_CS		 ((volatile UINT8 *)(0xFC0A4019))
#define MCF_GPIO_PDDR_PWM		 ((volatile UINT8 *)(0xFC0A401A))
#define MCF_GPIO_PDDR_FECI2C		 ((volatile UINT8 *)(0xFC0A401B))
#define MCF_GPIO_PDDR_UART		 ((volatile UINT8 *)(0xFC0A401D))
#define MCF_GPIO_PDDR_QSPI		 ((volatile UINT8 *)(0xFC0A401E))
#define MCF_GPIO_PDDR_TIMER		 ((volatile UINT8 *)(0xFC0A401F))
#define MCF_GPIO_PDDR_LCDDATAH		 ((volatile UINT8 *)(0xFC0A4021))
#define MCF_GPIO_PDDR_LCDDATAM		 ((volatile UINT8 *)(0xFC0A4022))
#define MCF_GPIO_PDDR_LCDDATAL		 ((volatile UINT8 *)(0xFC0A4023))
#define MCF_GPIO_PDDR_LCDCTLH		 ((volatile UINT8 *)(0xFC0A4024))
#define MCF_GPIO_PDDR_LCDCTLL		 ((volatile UINT8 *)(0xFC0A4025))
#define MCF_GPIO_PPDSDR_FECH		 ((volatile UINT8 *)(0xFC0A4028))
#define MCF_GPIO_PPDSDR_FECL		 ((volatile UINT8 *)(0xFC0A4029))
#define MCF_GPIO_PPDSDR_SSI		 ((volatile UINT8 *)(0xFC0A402A))
#define MCF_GPIO_PPDSDR_BUSCTL		 ((volatile UINT8 *)(0xFC0A402B))
#define MCF_GPIO_PPDSDR_BE		 ((volatile UINT8 *)(0xFC0A402C))
#define MCF_GPIO_PPDSDR_CS		 ((volatile UINT8 *)(0xFC0A402D))
#define MCF_GPIO_PPDSDR_PWM		 ((volatile UINT8 *)(0xFC0A402E))
#define MCF_GPIO_PPDSDR_FECI2C		 ((volatile UINT8 *)(0xFC0A402F))
#define MCF_GPIO_PPDSDR_UART		 ((volatile UINT8 *)(0xFC0A4031))
#define MCF_GPIO_PPDSDR_QSPI		 ((volatile UINT8 *)(0xFC0A4032))
#define MCF_GPIO_PPDSDR_TIMER		 ((volatile UINT8 *)(0xFC0A4033))
#define MCF_GPIO_PPDSDR_LCDDATAH	 ((volatile UINT8 *)(0xFC0A4035))
#define MCF_GPIO_PPDSDR_LCDDATAM	 ((volatile UINT8 *)(0xFC0A4036))
#define MCF_GPIO_PPDSDR_LCDDATAL	 ((volatile UINT8 *)(0xFC0A4037))
#define MCF_GPIO_PPDSDR_LCDCTLH		 ((volatile UINT8 *)(0xFC0A4038))
#define MCF_GPIO_PPDSDR_LCDCTLL		 ((volatile UINT8 *)(0xFC0A4039))
#define MCF_GPIO_PCLRR_FECH		 ((volatile UINT8 *)(0xFC0A403C))
#define MCF_GPIO_PCLRR_FECL		 ((volatile UINT8 *)(0xFC0A403D))
#define MCF_GPIO_PCLRR_SSI		 ((volatile UINT8 *)(0xFC0A403E))
#define MCF_GPIO_PCLRR_BUSCTL		 ((volatile UINT8 *)(0xFC0A403F))
#define MCF_GPIO_PCLRR_BE		 ((volatile UINT8 *)(0xFC0A4040))
#define MCF_GPIO_PCLRR_CS		 ((volatile UINT8 *)(0xFC0A4041))
#define MCF_GPIO_PCLRR_PWM		 ((volatile UINT8 *)(0xFC0A4042))
#define MCF_GPIO_PCLRR_FECI2C		 ((volatile UINT8 *)(0xFC0A4043))
#define MCF_GPIO_PCLRR_UART		 ((volatile UINT8 *)(0xFC0A4045))
#define MCF_GPIO_PCLRR_QSPI		 ((volatile UINT8 *)(0xFC0A4046))
#define MCF_GPIO_PCLRR_TIMER		 ((volatile UINT8 *)(0xFC0A4047))
#define MCF_GPIO_PCLRR_LCDDATAH		 ((volatile UINT8 *)(0xFC0A4049))
#define MCF_GPIO_PCLRR_LCDDATAM		 ((volatile UINT8 *)(0xFC0A404A))
#define MCF_GPIO_PCLRR_LCDDATAL		 ((volatile UINT8 *)(0xFC0A404B))
#define MCF_GPIO_PCLRR_LCDCTLH		 ((volatile UINT8 *)(0xFC0A404C))
#define MCF_GPIO_PCLRR_LCDCTLL		 ((volatile UINT8 *)(0xFC0A404D))
#define MCF_GPIO_PAR_FEC		 ((volatile UINT8 *)(0xFC0A4050))
#define MCF_GPIO_PAR_PWM		 ((volatile UINT8 *)(0xFC0A4051))
#define MCF_GPIO_PAR_BUSCTL		 ((volatile UINT8 *)(0xFC0A4052))
#define MCF_GPIO_PAR_FECI2C		 ((volatile UINT8 *)(0xFC0A4053))
#define MCF_GPIO_PAR_BE			 ((volatile UINT8 *)(0xFC0A4054))
#define MCF_GPIO_PAR_CS			 ((volatile UINT8 *)(0xFC0A4055))
#define MCF_GPIO_PAR_SSI		 ((volatile UINT16*)(0xFC0A4056))
#define MCF_GPIO_PAR_UART		 ((volatile UINT16*)(0xFC0A4058))
#define MCF_GPIO_PAR_QSPI		 ((volatile UINT16*)(0xFC0A405A))
#define MCF_GPIO_PAR_TIMER		 ((volatile UINT8 *)(0xFC0A405C))
#define MCF_GPIO_PAR_LCDDATA		 ((volatile UINT8 *)(0xFC0A405D))
#define MCF_GPIO_PAR_LCDCTL		 ((volatile UINT16*)(0xFC0A405E))
#define MCF_GPIO_PAR_IRQ		 ((volatile UINT16*)(0xFC0A4060))
#define MCF_GPIO_MSCR_FLEXBUS		 ((volatile UINT8 *)(0xFC0A4064))
#define MCF_GPIO_MSCR_SDRAM		 ((volatile UINT8 *)(0xFC0A4065))
#define MCF_GPIO_DSCR_I2C		 ((volatile UINT8 *)(0xFC0A4068))
#define MCF_GPIO_DSCR_PWM		 ((volatile UINT8 *)(0xFC0A4069))
#define MCF_GPIO_DSCR_FEC		 ((volatile UINT8 *)(0xFC0A406A))
#define MCF_GPIO_DSCR_UART		 ((volatile UINT8 *)(0xFC0A406B))
#define MCF_GPIO_DSCR_QSPI		 ((volatile UINT8 *)(0xFC0A406C))
#define MCF_GPIO_DSCR_TIMER		 ((volatile UINT8 *)(0xFC0A406D))
#define MCF_GPIO_DSCR_SSI		 ((volatile UINT8 *)(0xFC0A406E))
#define MCF_GPIO_DSCR_LCD		 ((volatile UINT8 *)(0xFC0A406F))
#define MCF_GPIO_DSCR_DEBUG		 ((volatile UINT8 *)(0xFC0A4070))
#define MCF_GPIO_DSCR_CLKRST		 ((volatile UINT8 *)(0xFC0A4071))
#define MCF_GPIO_DSCR_IRQ		 ((volatile UINT8 *)(0xFC0A4072))

/* Bit definitions and macros for MCF_GPIO_PODR_FECH */
#define MCF_GPIO_PODR_FECH_PODR_FECH0	       (0x01)
#define MCF_GPIO_PODR_FECH_PODR_FECH1	       (0x02)
#define MCF_GPIO_PODR_FECH_PODR_FECH2	       (0x04)
#define MCF_GPIO_PODR_FECH_PODR_FECH3	       (0x08)
#define MCF_GPIO_PODR_FECH_PODR_FECH4	       (0x10)
#define MCF_GPIO_PODR_FECH_PODR_FECH5	       (0x20)
#define MCF_GPIO_PODR_FECH_PODR_FECH6	       (0x40)
#define MCF_GPIO_PODR_FECH_PODR_FECH7	       (0x80)

/* Bit definitions and macros for MCF_GPIO_PODR_FECL */
#define MCF_GPIO_PODR_FECL_PODR_FECL0	       (0x01)
#define MCF_GPIO_PODR_FECL_PODR_FECL1	       (0x02)
#define MCF_GPIO_PODR_FECL_PODR_FECL2	       (0x04)
#define MCF_GPIO_PODR_FECL_PODR_FECL3	       (0x08)
#define MCF_GPIO_PODR_FECL_PODR_FECL4	       (0x10)
#define MCF_GPIO_PODR_FECL_PODR_FECL5	       (0x20)
#define MCF_GPIO_PODR_FECL_PODR_FECL6	       (0x40)
#define MCF_GPIO_PODR_FECL_PODR_FECL7	       (0x80)

/* Bit definitions and macros for MCF_GPIO_PODR_SSI */
#define MCF_GPIO_PODR_SSI_PODR_SSI0	       (0x01)
#define MCF_GPIO_PODR_SSI_PODR_SSI1	       (0x02)
#define MCF_GPIO_PODR_SSI_PODR_SSI2	       (0x04)
#define MCF_GPIO_PODR_SSI_PODR_SSI3	       (0x08)
#define MCF_GPIO_PODR_SSI_PODR_SSI4	       (0x10)

/* Bit definitions and macros for MCF_GPIO_PODR_BUSCTL */
#define MCF_GPIO_PODR_BUSCTL_PODR_BUSCTL0    (0x01)
#define MCF_GPIO_PODR_BUSCTL_PODR_BUSCTL1    (0x02)
#define MCF_GPIO_PODR_BUSCTL_PODR_BUSCTL2    (0x04)
#define MCF_GPIO_PODR_BUSCTL_PODR_BUSCTL3    (0x08)

/* Bit definitions and macros for MCF_GPIO_PODR_BE */
#define MCF_GPIO_PODR_BE_PODR_BE0	       (0x01)
#define MCF_GPIO_PODR_BE_PODR_BE1	       (0x02)
#define MCF_GPIO_PODR_BE_PODR_BE2	       (0x04)
#define MCF_GPIO_PODR_BE_PODR_BE3	       (0x08)

/* Bit definitions and macros for MCF_GPIO_PODR_CS */
#define MCF_GPIO_PODR_CS_PODR_CS1	       (0x02)
#define MCF_GPIO_PODR_CS_PODR_CS2	       (0x04)
#define MCF_GPIO_PODR_CS_PODR_CS3	       (0x08)
#define MCF_GPIO_PODR_CS_PODR_CS4	       (0x10)
#define MCF_GPIO_PODR_CS_PODR_CS5	       (0x20)

/* Bit definitions and macros for MCF_GPIO_PODR_PWM */
#define MCF_GPIO_PODR_PWM_PODR_PWM2	       (0x04)
#define MCF_GPIO_PODR_PWM_PODR_PWM3	       (0x08)
#define MCF_GPIO_PODR_PWM_PODR_PWM4	       (0x10)
#define MCF_GPIO_PODR_PWM_PODR_PWM5	       (0x20)

/* Bit definitions and macros for MCF_GPIO_PODR_FECI2C */
#define MCF_GPIO_PODR_FECI2C_PODR_FECI2C0    (0x01)
#define MCF_GPIO_PODR_FECI2C_PODR_FECI2C1    (0x02)
#define MCF_GPIO_PODR_FECI2C_PODR_FECI2C2    (0x04)
#define MCF_GPIO_PODR_FECI2C_PODR_FECI2C3    (0x08)

/* Bit definitions and macros for MCF_GPIO_PODR_UART */
#define MCF_GPIO_PODR_UART_PODR_UART0	       (0x01)
#define MCF_GPIO_PODR_UART_PODR_UART1	       (0x02)
#define MCF_GPIO_PODR_UART_PODR_UART2	       (0x04)
#define MCF_GPIO_PODR_UART_PODR_UART3	       (0x08)
#define MCF_GPIO_PODR_UART_PODR_UART4	       (0x10)
#define MCF_GPIO_PODR_UART_PODR_UART5	       (0x20)
#define MCF_GPIO_PODR_UART_PODR_UART6	       (0x40)
#define MCF_GPIO_PODR_UART_PODR_UART7	       (0x80)

/* Bit definitions and macros for MCF_GPIO_PODR_QSPI */
#define MCF_GPIO_PODR_QSPI_PODR_QSPI0	       (0x01)
#define MCF_GPIO_PODR_QSPI_PODR_QSPI1	       (0x02)
#define MCF_GPIO_PODR_QSPI_PODR_QSPI2	       (0x04)
#define MCF_GPIO_PODR_QSPI_PODR_QSPI3	       (0x08)
#define MCF_GPIO_PODR_QSPI_PODR_QSPI4	       (0x10)
#define MCF_GPIO_PODR_QSPI_PODR_QSPI5	       (0x20)

/* Bit definitions and macros for MCF_GPIO_PODR_TIMER */
#define MCF_GPIO_PODR_TIMER_PODR_TIMER0	     (0x01)
#define MCF_GPIO_PODR_TIMER_PODR_TIMER1	     (0x02)
#define MCF_GPIO_PODR_TIMER_PODR_TIMER2	     (0x04)
#define MCF_GPIO_PODR_TIMER_PODR_TIMER3	     (0x08)

/* Bit definitions and macros for MCF_GPIO_PODR_LCDDATAH */
#define MCF_GPIO_PODR_LCDDATAH_PODR_LCDDATAH0	     (0x01)
#define MCF_GPIO_PODR_LCDDATAH_PODR_LCDDATAH1	     (0x02)

/* Bit definitions and macros for MCF_GPIO_PODR_LCDDATAM */
#define MCF_GPIO_PODR_LCDDATAM_PODR_LCDDATAM0	     (0x01)
#define MCF_GPIO_PODR_LCDDATAM_PODR_LCDDATAM1	     (0x02)
#define MCF_GPIO_PODR_LCDDATAM_PODR_LCDDATAM2	     (0x04)
#define MCF_GPIO_PODR_LCDDATAM_PODR_LCDDATAM3	     (0x08)
#define MCF_GPIO_PODR_LCDDATAM_PODR_LCDDATAM4	     (0x10)
#define MCF_GPIO_PODR_LCDDATAM_PODR_LCDDATAM5	     (0x20)
#define MCF_GPIO_PODR_LCDDATAM_PODR_LCDDATAM6	     (0x40)
#define MCF_GPIO_PODR_LCDDATAM_PODR_LCDDATAM7	     (0x80)

/* Bit definitions and macros for MCF_GPIO_PODR_LCDDATAL */
#define MCF_GPIO_PODR_LCDDATAL_PODR_LCDDATAL0	     (0x01)
#define MCF_GPIO_PODR_LCDDATAL_PODR_LCDDATAL1	     (0x02)
#define MCF_GPIO_PODR_LCDDATAL_PODR_LCDDATAL2	     (0x04)
#define MCF_GPIO_PODR_LCDDATAL_PODR_LCDDATAL3	     (0x08)
#define MCF_GPIO_PODR_LCDDATAL_PODR_LCDDATAL4	     (0x10)
#define MCF_GPIO_PODR_LCDDATAL_PODR_LCDDATAL5	     (0x20)
#define MCF_GPIO_PODR_LCDDATAL_PODR_LCDDATAL6	     (0x40)
#define MCF_GPIO_PODR_LCDDATAL_PODR_LCDDATAL7	     (0x80)

/* Bit definitions and macros for MCF_GPIO_PODR_LCDCTLH */
#define MCF_GPIO_PODR_LCDCTLH_PODR_LCDCTLH0	     (0x01)

/* Bit definitions and macros for MCF_GPIO_PODR_LCDCTLL */
#define MCF_GPIO_PODR_LCDCTLL_PODR_LCDCTLL0	     (0x01)
#define MCF_GPIO_PODR_LCDCTLL_PODR_LCDCTLL1	     (0x02)
#define MCF_GPIO_PODR_LCDCTLL_PODR_LCDCTLL2	     (0x04)
#define MCF_GPIO_PODR_LCDCTLL_PODR_LCDCTLL3	     (0x08)
#define MCF_GPIO_PODR_LCDCTLL_PODR_LCDCTLL4	     (0x10)
#define MCF_GPIO_PODR_LCDCTLL_PODR_LCDCTLL5	     (0x20)
#define MCF_GPIO_PODR_LCDCTLL_PODR_LCDCTLL6	     (0x40)
#define MCF_GPIO_PODR_LCDCTLL_PODR_LCDCTLL7	     (0x80)

/* Bit definitions and macros for MCF_GPIO_PDDR_FECH */
#define MCF_GPIO_PDDR_FECH_PDDR_FECH0	       (0x01)
#define MCF_GPIO_PDDR_FECH_PDDR_FECH1	       (0x02)
#define MCF_GPIO_PDDR_FECH_PDDR_FECH2	       (0x04)
#define MCF_GPIO_PDDR_FECH_PDDR_FECH3	       (0x08)
#define MCF_GPIO_PDDR_FECH_PDDR_FECH4	       (0x10)
#define MCF_GPIO_PDDR_FECH_PDDR_FECH5	       (0x20)
#define MCF_GPIO_PDDR_FECH_PDDR_FECH6	       (0x40)
#define MCF_GPIO_PDDR_FECH_PDDR_FECH7	       (0x80)

/* Bit definitions and macros for MCF_GPIO_PDDR_FECL */
#define MCF_GPIO_PDDR_FECL_PDDR_FECL0	       (0x01)
#define MCF_GPIO_PDDR_FECL_PDDR_FECL1	       (0x02)
#define MCF_GPIO_PDDR_FECL_PDDR_FECL2	       (0x04)
#define MCF_GPIO_PDDR_FECL_PDDR_FECL3	       (0x08)
#define MCF_GPIO_PDDR_FECL_PDDR_FECL4	       (0x10)
#define MCF_GPIO_PDDR_FECL_PDDR_FECL5	       (0x20)
#define MCF_GPIO_PDDR_FECL_PDDR_FECL6	       (0x40)
#define MCF_GPIO_PDDR_FECL_PDDR_FECL7	       (0x80)

/* Bit definitions and macros for MCF_GPIO_PDDR_SSI */
#define MCF_GPIO_PDDR_SSI_PDDR_SSI0	       (0x01)
#define MCF_GPIO_PDDR_SSI_PDDR_SSI1	       (0x02)
#define MCF_GPIO_PDDR_SSI_PDDR_SSI2	       (0x04)
#define MCF_GPIO_PDDR_SSI_PDDR_SSI3	       (0x08)
#define MCF_GPIO_PDDR_SSI_PDDR_SSI4	       (0x10)

/* Bit definitions and macros for MCF_GPIO_PDDR_BUSCTL */
#define MCF_GPIO_PDDR_BUSCTL_PDDR_BUSCTL0    (0x01)
#define MCF_GPIO_PDDR_BUSCTL_PDDR_BUSCTL1    (0x02)
#define MCF_GPIO_PDDR_BUSCTL_PDDR_BUSCTL2    (0x04)
#define MCF_GPIO_PDDR_BUSCTL_PDDR_BUSCTL3    (0x08)

/* Bit definitions and macros for MCF_GPIO_PDDR_BE */
#define MCF_GPIO_PDDR_BE_PDDR_BE0	       (0x01)
#define MCF_GPIO_PDDR_BE_PDDR_BE1	       (0x02)
#define MCF_GPIO_PDDR_BE_PDDR_BE2	       (0x04)
#define MCF_GPIO_PDDR_BE_PDDR_BE3	       (0x08)

/* Bit definitions and macros for MCF_GPIO_PDDR_CS */
#define MCF_GPIO_PDDR_CS_PDDR_CS1	       (0x02)
#define MCF_GPIO_PDDR_CS_PDDR_CS2	       (0x04)
#define MCF_GPIO_PDDR_CS_PDDR_CS3	       (0x08)
#define MCF_GPIO_PDDR_CS_PDDR_CS4	       (0x10)
#define MCF_GPIO_PDDR_CS_PDDR_CS5	       (0x20)

/* Bit definitions and macros for MCF_GPIO_PDDR_PWM */
#define MCF_GPIO_PDDR_PWM_PDDR_PWM2	       (0x04)
#define MCF_GPIO_PDDR_PWM_PDDR_PWM3	       (0x08)
#define MCF_GPIO_PDDR_PWM_PDDR_PWM4	       (0x10)
#define MCF_GPIO_PDDR_PWM_PDDR_PWM5	       (0x20)

/* Bit definitions and macros for MCF_GPIO_PDDR_FECI2C */
#define MCF_GPIO_PDDR_FECI2C_PDDR_FECI2C0    (0x01)
#define MCF_GPIO_PDDR_FECI2C_PDDR_FECI2C1    (0x02)
#define MCF_GPIO_PDDR_FECI2C_PDDR_FECI2C2    (0x04)
#define MCF_GPIO_PDDR_FECI2C_PDDR_FECI2C3    (0x08)

/* Bit definitions and macros for MCF_GPIO_PDDR_UART */
#define MCF_GPIO_PDDR_UART_PDDR_UART0	       (0x01)
#define MCF_GPIO_PDDR_UART_PDDR_UART1	       (0x02)
#define MCF_GPIO_PDDR_UART_PDDR_UART2	       (0x04)
#define MCF_GPIO_PDDR_UART_PDDR_UART3	       (0x08)
#define MCF_GPIO_PDDR_UART_PDDR_UART4	       (0x10)
#define MCF_GPIO_PDDR_UART_PDDR_UART5	       (0x20)
#define MCF_GPIO_PDDR_UART_PDDR_UART6	       (0x40)
#define MCF_GPIO_PDDR_UART_PDDR_UART7	       (0x80)

/* Bit definitions and macros for MCF_GPIO_PDDR_QSPI */
#define MCF_GPIO_PDDR_QSPI_PDDR_QSPI0	       (0x01)
#define MCF_GPIO_PDDR_QSPI_PDDR_QSPI1	       (0x02)
#define MCF_GPIO_PDDR_QSPI_PDDR_QSPI2	       (0x04)
#define MCF_GPIO_PDDR_QSPI_PDDR_QSPI3	       (0x08)
#define MCF_GPIO_PDDR_QSPI_PDDR_QSPI4	       (0x10)
#define MCF_GPIO_PDDR_QSPI_PDDR_QSPI5	       (0x20)

/* Bit definitions and macros for MCF_GPIO_PDDR_TIMER */
#define MCF_GPIO_PDDR_TIMER_PDDR_TIMER0	     (0x01)
#define MCF_GPIO_PDDR_TIMER_PDDR_TIMER1	     (0x02)
#define MCF_GPIO_PDDR_TIMER_PDDR_TIMER2	     (0x04)
#define MCF_GPIO_PDDR_TIMER_PDDR_TIMER3	     (0x08)

/* Bit definitions and macros for MCF_GPIO_PDDR_LCDDATAH */
#define MCF_GPIO_PDDR_LCDDATAH_PDDR_LCDDATAH0	     (0x01)
#define MCF_GPIO_PDDR_LCDDATAH_PDDR_LCDDATAH1	     (0x02)

/* Bit definitions and macros for MCF_GPIO_PDDR_LCDDATAM */
#define MCF_GPIO_PDDR_LCDDATAM_PDDR_LCDDATAM0	     (0x01)
#define MCF_GPIO_PDDR_LCDDATAM_PDDR_LCDDATAM1	     (0x02)
#define MCF_GPIO_PDDR_LCDDATAM_PDDR_LCDDATAM2	     (0x04)
#define MCF_GPIO_PDDR_LCDDATAM_PDDR_LCDDATAM3	     (0x08)
#define MCF_GPIO_PDDR_LCDDATAM_PDDR_LCDDATAM4	     (0x10)
#define MCF_GPIO_PDDR_LCDDATAM_PDDR_LCDDATAM5	     (0x20)
#define MCF_GPIO_PDDR_LCDDATAM_PDDR_LCDDATAM6	     (0x40)
#define MCF_GPIO_PDDR_LCDDATAM_PDDR_LCDDATAM7	     (0x80)

/* Bit definitions and macros for MCF_GPIO_PDDR_LCDDATAL */
#define MCF_GPIO_PDDR_LCDDATAL_PDDR_LCDDATAL0	     (0x01)
#define MCF_GPIO_PDDR_LCDDATAL_PDDR_LCDDATAL1	     (0x02)
#define MCF_GPIO_PDDR_LCDDATAL_PDDR_LCDDATAL2	     (0x04)
#define MCF_GPIO_PDDR_LCDDATAL_PDDR_LCDDATAL3	     (0x08)
#define MCF_GPIO_PDDR_LCDDATAL_PDDR_LCDDATAL4	     (0x10)
#define MCF_GPIO_PDDR_LCDDATAL_PDDR_LCDDATAL5	     (0x20)
#define MCF_GPIO_PDDR_LCDDATAL_PDDR_LCDDATAL6	     (0x40)
#define MCF_GPIO_PDDR_LCDDATAL_PDDR_LCDDATAL7	     (0x80)

/* Bit definitions and macros for MCF_GPIO_PDDR_LCDCTLH */
#define MCF_GPIO_PDDR_LCDCTLH_PDDR_LCDCTLH0	     (0x01)

/* Bit definitions and macros for MCF_GPIO_PDDR_LCDCTLL */
#define MCF_GPIO_PDDR_LCDCTLL_PDDR_LCDCTLL0	     (0x01)
#define MCF_GPIO_PDDR_LCDCTLL_PDDR_LCDCTLL1	     (0x02)
#define MCF_GPIO_PDDR_LCDCTLL_PDDR_LCDCTLL2	     (0x04)
#define MCF_GPIO_PDDR_LCDCTLL_PDDR_LCDCTLL3	     (0x08)
#define MCF_GPIO_PDDR_LCDCTLL_PDDR_LCDCTLL4	     (0x10)
#define MCF_GPIO_PDDR_LCDCTLL_PDDR_LCDCTLL5	     (0x20)
#define MCF_GPIO_PDDR_LCDCTLL_PDDR_LCDCTLL6	     (0x40)
#define MCF_GPIO_PDDR_LCDCTLL_PDDR_LCDCTLL7	     (0x80)

/* Bit definitions and macros for MCF_GPIO_PPDSDR_FECH */
#define MCF_GPIO_PPDSDR_FECH_PPDSDR_FECH0    (0x01)
#define MCF_GPIO_PPDSDR_FECH_PPDSDR_FECH1    (0x02)
#define MCF_GPIO_PPDSDR_FECH_PPDSDR_FECH2    (0x04)
#define MCF_GPIO_PPDSDR_FECH_PPDSDR_FECH3    (0x08)
#define MCF_GPIO_PPDSDR_FECH_PPDSDR_FECH4    (0x10)
#define MCF_GPIO_PPDSDR_FECH_PPDSDR_FECH5    (0x20)
#define MCF_GPIO_PPDSDR_FECH_PPDSDR_FECH6    (0x40)
#define MCF_GPIO_PPDSDR_FECH_PPDSDR_FECH7    (0x80)

/* Bit definitions and macros for MCF_GPIO_PPDSDR_FECL */
#define MCF_GPIO_PPDSDR_FECL_PPDSDR_FECL0    (0x01)
#define MCF_GPIO_PPDSDR_FECL_PPDSDR_FECL1    (0x02)
#define MCF_GPIO_PPDSDR_FECL_PPDSDR_FECL2    (0x04)
#define MCF_GPIO_PPDSDR_FECL_PPDSDR_FECL3    (0x08)
#define MCF_GPIO_PPDSDR_FECL_PPDSDR_FECL4    (0x10)
#define MCF_GPIO_PPDSDR_FECL_PPDSDR_FECL5    (0x20)
#define MCF_GPIO_PPDSDR_FECL_PPDSDR_FECL6    (0x40)
#define MCF_GPIO_PPDSDR_FECL_PPDSDR_FECL7    (0x80)

/* Bit definitions and macros for MCF_GPIO_PPDSDR_SSI */
#define MCF_GPIO_PPDSDR_SSI_PPDSDR_SSI0	     (0x01)
#define MCF_GPIO_PPDSDR_SSI_PPDSDR_SSI1	     (0x02)
#define MCF_GPIO_PPDSDR_SSI_PPDSDR_SSI2	     (0x04)
#define MCF_GPIO_PPDSDR_SSI_PPDSDR_SSI3	     (0x08)
#define MCF_GPIO_PPDSDR_SSI_PPDSDR_SSI4	     (0x10)

/* Bit definitions and macros for MCF_GPIO_PPDSDR_BUSCTL */
#define MCF_GPIO_PPDSDR_BUSCTL_PPDSDR_BUSCTL0	     (0x01)
#define MCF_GPIO_PPDSDR_BUSCTL_PPDSDR_BUSCTL1	     (0x02)
#define MCF_GPIO_PPDSDR_BUSCTL_PPDSDR_BUSCTL2	     (0x04)
#define MCF_GPIO_PPDSDR_BUSCTL_PPDSDR_BUSCTL3	     (0x08)

/* Bit definitions and macros for MCF_GPIO_PPDSDR_BE */
#define MCF_GPIO_PPDSDR_BE_PPDSDR_BE0	       (0x01)
#define MCF_GPIO_PPDSDR_BE_PPDSDR_BE1	       (0x02)
#define MCF_GPIO_PPDSDR_BE_PPDSDR_BE2	       (0x04)
#define MCF_GPIO_PPDSDR_BE_PPDSDR_BE3	       (0x08)

/* Bit definitions and macros for MCF_GPIO_PPDSDR_CS */
#define MCF_GPIO_PPDSDR_CS_PPDSDR_CS1	       (0x02)
#define MCF_GPIO_PPDSDR_CS_PPDSDR_CS2	       (0x04)
#define MCF_GPIO_PPDSDR_CS_PPDSDR_CS3	       (0x08)
#define MCF_GPIO_PPDSDR_CS_PPDSDR_CS4	       (0x10)
#define MCF_GPIO_PPDSDR_CS_PPDSDR_CS5	       (0x20)

/* Bit definitions and macros for MCF_GPIO_PPDSDR_PWM */
#define MCF_GPIO_PPDSDR_PWM_PPDSDR_PWM2	     (0x04)
#define MCF_GPIO_PPDSDR_PWM_PPDSDR_PWM3	     (0x08)
#define MCF_GPIO_PPDSDR_PWM_PPDSDR_PWM4	     (0x10)
#define MCF_GPIO_PPDSDR_PWM_PPDSDR_PWM5	     (0x20)

/* Bit definitions and macros for MCF_GPIO_PPDSDR_FECI2C */
#define MCF_GPIO_PPDSDR_FECI2C_PPDSDR_FECI2C0	     (0x01)
#define MCF_GPIO_PPDSDR_FECI2C_PPDSDR_FECI2C1	     (0x02)
#define MCF_GPIO_PPDSDR_FECI2C_PPDSDR_FECI2C2	     (0x04)
#define MCF_GPIO_PPDSDR_FECI2C_PPDSDR_FECI2C3	     (0x08)

/* Bit definitions and macros for MCF_GPIO_PPDSDR_UART */
#define MCF_GPIO_PPDSDR_UART_PPDSDR_UART0    (0x01)
#define MCF_GPIO_PPDSDR_UART_PPDSDR_UART1    (0x02)
#define MCF_GPIO_PPDSDR_UART_PPDSDR_UART2    (0x04)
#define MCF_GPIO_PPDSDR_UART_PPDSDR_UART3    (0x08)
#define MCF_GPIO_PPDSDR_UART_PPDSDR_UART4    (0x10)
#define MCF_GPIO_PPDSDR_UART_PPDSDR_UART5    (0x20)
#define MCF_GPIO_PPDSDR_UART_PPDSDR_UART6    (0x40)
#define MCF_GPIO_PPDSDR_UART_PPDSDR_UART7    (0x80)

/* Bit definitions and macros for MCF_GPIO_PPDSDR_QSPI */
#define MCF_GPIO_PPDSDR_QSPI_PPDSDR_QSPI0    (0x01)
#define MCF_GPIO_PPDSDR_QSPI_PPDSDR_QSPI1    (0x02)
#define MCF_GPIO_PPDSDR_QSPI_PPDSDR_QSPI2    (0x04)
#define MCF_GPIO_PPDSDR_QSPI_PPDSDR_QSPI3    (0x08)
#define MCF_GPIO_PPDSDR_QSPI_PPDSDR_QSPI4    (0x10)
#define MCF_GPIO_PPDSDR_QSPI_PPDSDR_QSPI5    (0x20)

/* Bit definitions and macros for MCF_GPIO_PPDSDR_TIMER */
#define MCF_GPIO_PPDSDR_TIMER_PPDSDR_TIMER0	     (0x01)
#define MCF_GPIO_PPDSDR_TIMER_PPDSDR_TIMER1	     (0x02)
#define MCF_GPIO_PPDSDR_TIMER_PPDSDR_TIMER2	     (0x04)
#define MCF_GPIO_PPDSDR_TIMER_PPDSDR_TIMER3	     (0x08)

/* Bit definitions and macros for MCF_GPIO_PPDSDR_LCDDATAH */
#define MCF_GPIO_PPDSDR_LCDDATAH_PPDSDR_LCDDATAH0  (0x01)
#define MCF_GPIO_PPDSDR_LCDDATAH_PPDSDR_LCDDATAH1  (0x02)

/* Bit definitions and macros for MCF_GPIO_PPDSDR_LCDDATAM */
#define MCF_GPIO_PPDSDR_LCDDATAM_PPDSDR_LCDDATAM0  (0x01)
#define MCF_GPIO_PPDSDR_LCDDATAM_PPDSDR_LCDDATAM1  (0x02)
#define MCF_GPIO_PPDSDR_LCDDATAM_PPDSDR_LCDDATAM2  (0x04)
#define MCF_GPIO_PPDSDR_LCDDATAM_PPDSDR_LCDDATAM3  (0x08)
#define MCF_GPIO_PPDSDR_LCDDATAM_PPDSDR_LCDDATAM4  (0x10)
#define MCF_GPIO_PPDSDR_LCDDATAM_PPDSDR_LCDDATAM5  (0x20)
#define MCF_GPIO_PPDSDR_LCDDATAM_PPDSDR_LCDDATAM6  (0x40)
#define MCF_GPIO_PPDSDR_LCDDATAM_PPDSDR_LCDDATAM7  (0x80)

/* Bit definitions and macros for MCF_GPIO_PPDSDR_LCDDATAL */
#define MCF_GPIO_PPDSDR_LCDDATAL_PPDSDR_LCDDATAL0  (0x01)
#define MCF_GPIO_PPDSDR_LCDDATAL_PPDSDR_LCDDATAL1  (0x02)
#define MCF_GPIO_PPDSDR_LCDDATAL_PPDSDR_LCDDATAL2  (0x04)
#define MCF_GPIO_PPDSDR_LCDDATAL_PPDSDR_LCDDATAL3  (0x08)
#define MCF_GPIO_PPDSDR_LCDDATAL_PPDSDR_LCDDATAL4  (0x10)
#define MCF_GPIO_PPDSDR_LCDDATAL_PPDSDR_LCDDATAL5  (0x20)
#define MCF_GPIO_PPDSDR_LCDDATAL_PPDSDR_LCDDATAL6  (0x40)
#define MCF_GPIO_PPDSDR_LCDDATAL_PPDSDR_LCDDATAL7  (0x80)

/* Bit definitions and macros for MCF_GPIO_PPDSDR_LCDCTLH */
#define MCF_GPIO_PPDSDR_LCDCTLH_PPDSDR_LCDCTLH0	   (0x01)

/* Bit definitions and macros for MCF_GPIO_PPDSDR_LCDCTLL */
#define MCF_GPIO_PPDSDR_LCDCTLL_PPDSDR_LCDCTLL0	   (0x01)
#define MCF_GPIO_PPDSDR_LCDCTLL_PPDSDR_LCDCTLL1	   (0x02)
#define MCF_GPIO_PPDSDR_LCDCTLL_PPDSDR_LCDCTLL2	   (0x04)
#define MCF_GPIO_PPDSDR_LCDCTLL_PPDSDR_LCDCTLL3	   (0x08)
#define MCF_GPIO_PPDSDR_LCDCTLL_PPDSDR_LCDCTLL4	   (0x10)
#define MCF_GPIO_PPDSDR_LCDCTLL_PPDSDR_LCDCTLL5	   (0x20)
#define MCF_GPIO_PPDSDR_LCDCTLL_PPDSDR_LCDCTLL6	   (0x40)
#define MCF_GPIO_PPDSDR_LCDCTLL_PPDSDR_LCDCTLL7	   (0x80)

/* Bit definitions and macros for MCF_GPIO_PCLRR_FECH */
#define MCF_GPIO_PCLRR_FECH_PCLRR_FECH0	     (0x01)
#define MCF_GPIO_PCLRR_FECH_PCLRR_FECH1	     (0x02)
#define MCF_GPIO_PCLRR_FECH_PCLRR_FECH2	     (0x04)
#define MCF_GPIO_PCLRR_FECH_PCLRR_FECH3	     (0x08)
#define MCF_GPIO_PCLRR_FECH_PCLRR_FECH4	     (0x10)
#define MCF_GPIO_PCLRR_FECH_PCLRR_FECH5	     (0x20)
#define MCF_GPIO_PCLRR_FECH_PCLRR_FECH6	     (0x40)
#define MCF_GPIO_PCLRR_FECH_PCLRR_FECH7	     (0x80)

/* Bit definitions and macros for MCF_GPIO_PCLRR_FECL */
#define MCF_GPIO_PCLRR_FECL_PCLRR_FECL0	     (0x01)
#define MCF_GPIO_PCLRR_FECL_PCLRR_FECL1	     (0x02)
#define MCF_GPIO_PCLRR_FECL_PCLRR_FECL2	     (0x04)
#define MCF_GPIO_PCLRR_FECL_PCLRR_FECL3	     (0x08)
#define MCF_GPIO_PCLRR_FECL_PCLRR_FECL4	     (0x10)
#define MCF_GPIO_PCLRR_FECL_PCLRR_FECL5	     (0x20)
#define MCF_GPIO_PCLRR_FECL_PCLRR_FECL6	     (0x40)
#define MCF_GPIO_PCLRR_FECL_PCLRR_FECL7	     (0x80)

/* Bit definitions and macros for MCF_GPIO_PCLRR_SSI */
#define MCF_GPIO_PCLRR_SSI_PCLRR_SSI0	       (0x01)
#define MCF_GPIO_PCLRR_SSI_PCLRR_SSI1	       (0x02)
#define MCF_GPIO_PCLRR_SSI_PCLRR_SSI2	       (0x04)
#define MCF_GPIO_PCLRR_SSI_PCLRR_SSI3	       (0x08)
#define MCF_GPIO_PCLRR_SSI_PCLRR_SSI4	       (0x10)

/* Bit definitions and macros for MCF_GPIO_PCLRR_BUSCTL */
#define MCF_GPIO_PCLRR_BUSCTL_PCLRR_BUSCTL0	     (0x01)
#define MCF_GPIO_PCLRR_BUSCTL_PCLRR_BUSCTL1	     (0x02)
#define MCF_GPIO_PCLRR_BUSCTL_PCLRR_BUSCTL2	     (0x04)
#define MCF_GPIO_PCLRR_BUSCTL_PCLRR_BUSCTL3	     (0x08)

/* Bit definitions and macros for MCF_GPIO_PCLRR_BE */
#define MCF_GPIO_PCLRR_BE_PCLRR_BE0	       (0x01)
#define MCF_GPIO_PCLRR_BE_PCLRR_BE1	       (0x02)
#define MCF_GPIO_PCLRR_BE_PCLRR_BE2	       (0x04)
#define MCF_GPIO_PCLRR_BE_PCLRR_BE3	       (0x08)

/* Bit definitions and macros for MCF_GPIO_PCLRR_CS */
#define MCF_GPIO_PCLRR_CS_PCLRR_CS1	       (0x02)
#define MCF_GPIO_PCLRR_CS_PCLRR_CS2	       (0x04)
#define MCF_GPIO_PCLRR_CS_PCLRR_CS3	       (0x08)
#define MCF_GPIO_PCLRR_CS_PCLRR_CS4	       (0x10)
#define MCF_GPIO_PCLRR_CS_PCLRR_CS5	       (0x20)

/* Bit definitions and macros for MCF_GPIO_PCLRR_PWM */
#define MCF_GPIO_PCLRR_PWM_PCLRR_PWM2	       (0x04)
#define MCF_GPIO_PCLRR_PWM_PCLRR_PWM3	       (0x08)
#define MCF_GPIO_PCLRR_PWM_PCLRR_PWM4	       (0x10)
#define MCF_GPIO_PCLRR_PWM_PCLRR_PWM5	       (0x20)

/* Bit definitions and macros for MCF_GPIO_PCLRR_FECI2C */
#define MCF_GPIO_PCLRR_FECI2C_PCLRR_FECI2C0	     (0x01)
#define MCF_GPIO_PCLRR_FECI2C_PCLRR_FECI2C1	     (0x02)
#define MCF_GPIO_PCLRR_FECI2C_PCLRR_FECI2C2	     (0x04)
#define MCF_GPIO_PCLRR_FECI2C_PCLRR_FECI2C3	     (0x08)

/* Bit definitions and macros for MCF_GPIO_PCLRR_UART */
#define MCF_GPIO_PCLRR_UART_PCLRR_UART0	     (0x01)
#define MCF_GPIO_PCLRR_UART_PCLRR_UART1	     (0x02)
#define MCF_GPIO_PCLRR_UART_PCLRR_UART2	     (0x04)
#define MCF_GPIO_PCLRR_UART_PCLRR_UART3	     (0x08)
#define MCF_GPIO_PCLRR_UART_PCLRR_UART4	     (0x10)
#define MCF_GPIO_PCLRR_UART_PCLRR_UART5	     (0x20)
#define MCF_GPIO_PCLRR_UART_PCLRR_UART6	     (0x40)
#define MCF_GPIO_PCLRR_UART_PCLRR_UART7	     (0x80)

/* Bit definitions and macros for MCF_GPIO_PCLRR_QSPI */
#define MCF_GPIO_PCLRR_QSPI_PCLRR_QSPI0	     (0x01)
#define MCF_GPIO_PCLRR_QSPI_PCLRR_QSPI1	     (0x02)
#define MCF_GPIO_PCLRR_QSPI_PCLRR_QSPI2	     (0x04)
#define MCF_GPIO_PCLRR_QSPI_PCLRR_QSPI3	     (0x08)
#define MCF_GPIO_PCLRR_QSPI_PCLRR_QSPI4	     (0x10)
#define MCF_GPIO_PCLRR_QSPI_PCLRR_QSPI5	     (0x20)

/* Bit definitions and macros for MCF_GPIO_PCLRR_TIMER */
#define MCF_GPIO_PCLRR_TIMER_PCLRR_TIMER0    (0x01)
#define MCF_GPIO_PCLRR_TIMER_PCLRR_TIMER1    (0x02)
#define MCF_GPIO_PCLRR_TIMER_PCLRR_TIMER2    (0x04)
#define MCF_GPIO_PCLRR_TIMER_PCLRR_TIMER3    (0x08)

/* Bit definitions and macros for MCF_GPIO_PCLRR_LCDDATAH */
#define MCF_GPIO_PCLRR_LCDDATAH_PCLRR_LCDDATAH0	   (0x01)
#define MCF_GPIO_PCLRR_LCDDATAH_PCLRR_LCDDATAH1	   (0x02)

/* Bit definitions and macros for MCF_GPIO_PCLRR_LCDDATAM */
#define MCF_GPIO_PCLRR_LCDDATAM_PCLRR_LCDDATAM0	   (0x01)
#define MCF_GPIO_PCLRR_LCDDATAM_PCLRR_LCDDATAM1	   (0x02)
#define MCF_GPIO_PCLRR_LCDDATAM_PCLRR_LCDDATAM2	   (0x04)
#define MCF_GPIO_PCLRR_LCDDATAM_PCLRR_LCDDATAM3	   (0x08)
#define MCF_GPIO_PCLRR_LCDDATAM_PCLRR_LCDDATAM4	   (0x10)
#define MCF_GPIO_PCLRR_LCDDATAM_PCLRR_LCDDATAM5	   (0x20)
#define MCF_GPIO_PCLRR_LCDDATAM_PCLRR_LCDDATAM6	   (0x40)
#define MCF_GPIO_PCLRR_LCDDATAM_PCLRR_LCDDATAM7	   (0x80)

/* Bit definitions and macros for MCF_GPIO_PCLRR_LCDDATAL */
#define MCF_GPIO_PCLRR_LCDDATAL_PCLRR_LCDDATAL0	   (0x01)
#define MCF_GPIO_PCLRR_LCDDATAL_PCLRR_LCDDATAL1	   (0x02)
#define MCF_GPIO_PCLRR_LCDDATAL_PCLRR_LCDDATAL2	   (0x04)
#define MCF_GPIO_PCLRR_LCDDATAL_PCLRR_LCDDATAL3	   (0x08)
#define MCF_GPIO_PCLRR_LCDDATAL_PCLRR_LCDDATAL4	   (0x10)
#define MCF_GPIO_PCLRR_LCDDATAL_PCLRR_LCDDATAL5	   (0x20)
#define MCF_GPIO_PCLRR_LCDDATAL_PCLRR_LCDDATAL6	   (0x40)
#define MCF_GPIO_PCLRR_LCDDATAL_PCLRR_LCDDATAL7	   (0x80)

/* Bit definitions and macros for MCF_GPIO_PCLRR_LCDCTLH */
#define MCF_GPIO_PCLRR_LCDCTLH_PCLRR_LCDCTLH0	     (0x01)

/* Bit definitions and macros for MCF_GPIO_PCLRR_LCDCTLL */
#define MCF_GPIO_PCLRR_LCDCTLL_PCLRR_LCDCTLL0	     (0x01)
#define MCF_GPIO_PCLRR_LCDCTLL_PCLRR_LCDCTLL1	     (0x02)
#define MCF_GPIO_PCLRR_LCDCTLL_PCLRR_LCDCTLL2	     (0x04)
#define MCF_GPIO_PCLRR_LCDCTLL_PCLRR_LCDCTLL3	     (0x08)
#define MCF_GPIO_PCLRR_LCDCTLL_PCLRR_LCDCTLL4	     (0x10)
#define MCF_GPIO_PCLRR_LCDCTLL_PCLRR_LCDCTLL5	     (0x20)
#define MCF_GPIO_PCLRR_LCDCTLL_PCLRR_LCDCTLL6	     (0x40)
#define MCF_GPIO_PCLRR_LCDCTLL_PCLRR_LCDCTLL7	     (0x80)

/* Bit definitions and macros for MCF_GPIO_PAR_FEC */
#define MCF_GPIO_PAR_FEC_PAR_FEC_MII(x)	     (((x)&0x03)<<0)
#define MCF_GPIO_PAR_FEC_PAR_FEC_7W(x)	     (((x)&0x03)<<2)
#define MCF_GPIO_PAR_FEC_PAR_FEC_7W_GPIO     (0x00)
#define MCF_GPIO_PAR_FEC_PAR_FEC_7W_URTS1    (0x04)
#define MCF_GPIO_PAR_FEC_PAR_FEC_7W_FEC	     (0x0C)
#define MCF_GPIO_PAR_FEC_PAR_FEC_MII_GPIO    (0x00)
#define MCF_GPIO_PAR_FEC_PAR_FEC_MII_UART    (0x01)
#define MCF_GPIO_PAR_FEC_PAR_FEC_MII_FEC     (0x03)

/* Bit definitions and macros for MCF_GPIO_PAR_PWM */
#define MCF_GPIO_PAR_PWM_PAR_PWM1(x)	       (((x)&0x03)<<0)
#define MCF_GPIO_PAR_PWM_PAR_PWM3(x)	       (((x)&0x03)<<2)
#define MCF_GPIO_PAR_PWM_PAR_PWM5	       (0x10)
#define MCF_GPIO_PAR_PWM_PAR_PWM7	       (0x20)

/* Bit definitions and macros for MCF_GPIO_PAR_BUSCTL */
#define MCF_GPIO_PAR_BUSCTL_PAR_TS(x)	       (((x)&0x03)<<3)
#define MCF_GPIO_PAR_BUSCTL_PAR_RWB	       (0x20)
#define MCF_GPIO_PAR_BUSCTL_PAR_TA	       (0x40)
#define MCF_GPIO_PAR_BUSCTL_PAR_OE	       (0x80)
#define MCF_GPIO_PAR_BUSCTL_PAR_OE_GPIO	       (0x00)
#define MCF_GPIO_PAR_BUSCTL_PAR_OE_OE	       (0x80)
#define MCF_GPIO_PAR_BUSCTL_PAR_TA_GPIO	       (0x00)
#define MCF_GPIO_PAR_BUSCTL_PAR_TA_TA	       (0x40)
#define MCF_GPIO_PAR_BUSCTL_PAR_RWB_GPIO       (0x00)
#define MCF_GPIO_PAR_BUSCTL_PAR_RWB_RWB	       (0x20)
#define MCF_GPIO_PAR_BUSCTL_PAR_TS_GPIO	       (0x00)
#define MCF_GPIO_PAR_BUSCTL_PAR_TS_DACK0       (0x10)
#define MCF_GPIO_PAR_BUSCTL_PAR_TS_TS	       (0x18)

/* Bit definitions and macros for MCF_GPIO_PAR_FECI2C */
#define MCF_GPIO_PAR_FECI2C_PAR_SDA(x)	     (((x)&0x03)<<0)
#define MCF_GPIO_PAR_FECI2C_PAR_SCL(x)	     (((x)&0x03)<<2)
#define MCF_GPIO_PAR_FECI2C_PAR_MDIO(x)	     (((x)&0x03)<<4)
#define MCF_GPIO_PAR_FECI2C_PAR_MDC(x)	     (((x)&0x03)<<6)
#define MCF_GPIO_PAR_FECI2C_PAR_MDC_GPIO     (0x00)
#define MCF_GPIO_PAR_FECI2C_PAR_MDC_UTXD2    (0x40)
#define MCF_GPIO_PAR_FECI2C_PAR_MDC_SCL	     (0x80)
#define MCF_GPIO_PAR_FECI2C_PAR_MDC_EMDC     (0xC0)
#define MCF_GPIO_PAR_FECI2C_PAR_MDIO_GPIO    (0x00)
#define MCF_GPIO_PAR_FECI2C_PAR_MDIO_URXD2   (0x10)
#define MCF_GPIO_PAR_FECI2C_PAR_MDIO_SDA     (0x20)
#define MCF_GPIO_PAR_FECI2C_PAR_MDIO_EMDIO   (0x30)
#define MCF_GPIO_PAR_FECI2C_PAR_SCL_GPIO     (0x00)
#define MCF_GPIO_PAR_FECI2C_PAR_SCL_UTXD2    (0x04)
#define MCF_GPIO_PAR_FECI2C_PAR_SCL_SCL	     (0x0C)
#define MCF_GPIO_PAR_FECI2C_PAR_SDA_GPIO     (0x00)
#define MCF_GPIO_PAR_FECI2C_PAR_SDA_URXD2    (0x01)
#define MCF_GPIO_PAR_FECI2C_PAR_SDA_SDA	     (0x03)

/* Bit definitions and macros for MCF_GPIO_PAR_BE */
#define MCF_GPIO_PAR_BE_PAR_BE0	 (0x01)
#define MCF_GPIO_PAR_BE_PAR_BE1	 (0x02)
#define MCF_GPIO_PAR_BE_PAR_BE2	 (0x04)
#define MCF_GPIO_PAR_BE_PAR_BE3	 (0x08)

/* Bit definitions and macros for MCF_GPIO_PAR_CS */
#define MCF_GPIO_PAR_CS_PAR_CS1	 (0x02)
#define MCF_GPIO_PAR_CS_PAR_CS2	 (0x04)
#define MCF_GPIO_PAR_CS_PAR_CS3	 (0x08)
#define MCF_GPIO_PAR_CS_PAR_CS4	 (0x10)
#define MCF_GPIO_PAR_CS_PAR_CS5	 (0x20)
#define MCF_GPIO_PAR_CS_PAR_CS_CS1_GPIO	     (0x00)
#define MCF_GPIO_PAR_CS_PAR_CS_CS1_SDCS1     (0x01)
#define MCF_GPIO_PAR_CS_PAR_CS_CS1_CS1	     (0x03)

/* Bit definitions and macros for MCF_GPIO_PAR_SSI */
#define MCF_GPIO_PAR_SSI_PAR_MCLK	       (0x0080)
#define MCF_GPIO_PAR_SSI_PAR_TXD(x)	       (((x)&0x0003)<<8)
#define MCF_GPIO_PAR_SSI_PAR_RXD(x)	       (((x)&0x0003)<<10)
#define MCF_GPIO_PAR_SSI_PAR_FS(x)	       (((x)&0x0003)<<12)
#define MCF_GPIO_PAR_SSI_PAR_BCLK(x)	       (((x)&0x0003)<<14)

/* Bit definitions and macros for MCF_GPIO_PAR_UART */
#define MCF_GPIO_PAR_UART_PAR_UTXD0		(0x0001)
#define MCF_GPIO_PAR_UART_PAR_URXD0		(0x0002)
#define MCF_GPIO_PAR_UART_PAR_URTS0		(0x0004)
#define MCF_GPIO_PAR_UART_PAR_UCTS0		(0x0008)
#define MCF_GPIO_PAR_UART_PAR_UTXD1(x)		(((x)&0x0003)<<4)
#define MCF_GPIO_PAR_UART_PAR_URXD1(x)		(((x)&0x0003)<<6)
#define MCF_GPIO_PAR_UART_PAR_URTS1(x)		(((x)&0x0003)<<8)
#define MCF_GPIO_PAR_UART_PAR_UCTS1(x)		(((x)&0x0003)<<10)
#define MCF_GPIO_PAR_UART_PAR_UCTS1_GPIO	(0x0000)
#define MCF_GPIO_PAR_UART_PAR_UCTS1_SSI_BCLK	(0x0800)
#define MCF_GPIO_PAR_UART_PAR_UCTS1_ULPI_D7	(0x0400)
#define MCF_GPIO_PAR_UART_PAR_UCTS1_UCTS1	(0x0C00)
#define MCF_GPIO_PAR_UART_PAR_URTS1_GPIO	(0x0000)
#define MCF_GPIO_PAR_UART_PAR_URTS1_SSI_FS	(0x0200)
#define MCF_GPIO_PAR_UART_PAR_URTS1_ULPI_D6	(0x0100)
#define MCF_GPIO_PAR_UART_PAR_URTS1_URTS1	(0x0300)
#define MCF_GPIO_PAR_UART_PAR_URXD1_GPIO	(0x0000)
#define MCF_GPIO_PAR_UART_PAR_URXD1_SSI_RXD	(0x0080)
#define MCF_GPIO_PAR_UART_PAR_URXD1_ULPI_D5	(0x0040)
#define MCF_GPIO_PAR_UART_PAR_URXD1_URXD1	(0x00C0)
#define MCF_GPIO_PAR_UART_PAR_UTXD1_GPIO	(0x0000)
#define MCF_GPIO_PAR_UART_PAR_UTXD1_SSI_TXD	(0x0020)
#define MCF_GPIO_PAR_UART_PAR_UTXD1_ULPI_D4	(0x0010)
#define MCF_GPIO_PAR_UART_PAR_UTXD1_UTXD1	(0x0030)

/* Bit definitions and macros for MCF_GPIO_PAR_QSPI */
#define MCF_GPIO_PAR_QSPI_PAR_SCK(x)	       (((x)&0x0003)<<4)
#define MCF_GPIO_PAR_QSPI_PAR_DOUT(x)	       (((x)&0x0003)<<6)
#define MCF_GPIO_PAR_QSPI_PAR_DIN(x)	       (((x)&0x0003)<<8)
#define MCF_GPIO_PAR_QSPI_PAR_PCS0(x)	       (((x)&0x0003)<<10)
#define MCF_GPIO_PAR_QSPI_PAR_PCS1(x)	       (((x)&0x0003)<<12)
#define MCF_GPIO_PAR_QSPI_PAR_PCS2(x)	       (((x)&0x0003)<<14)

/* Bit definitions and macros for MCF_GPIO_PAR_TIMER */
#define MCF_GPIO_PAR_TIMER_PAR_TIN0(x)	     (((x)&0x03)<<0)
#define MCF_GPIO_PAR_TIMER_PAR_TIN1(x)	     (((x)&0x03)<<2)
#define MCF_GPIO_PAR_TIMER_PAR_TIN2(x)	     (((x)&0x03)<<4)
#define MCF_GPIO_PAR_TIMER_PAR_TIN3(x)	     (((x)&0x03)<<6)
#define MCF_GPIO_PAR_TIMER_PAR_TIN3_GPIO     (0x00)
#define MCF_GPIO_PAR_TIMER_PAR_TIN3_TOUT3    (0x80)
#define MCF_GPIO_PAR_TIMER_PAR_TIN3_URXD2    (0x40)
#define MCF_GPIO_PAR_TIMER_PAR_TIN3_TIN3     (0xC0)
#define MCF_GPIO_PAR_TIMER_PAR_TIN2_GPIO     (0x00)
#define MCF_GPIO_PAR_TIMER_PAR_TIN2_TOUT2    (0x20)
#define MCF_GPIO_PAR_TIMER_PAR_TIN2_UTXD2    (0x10)
#define MCF_GPIO_PAR_TIMER_PAR_TIN2_TIN2     (0x30)
#define MCF_GPIO_PAR_TIMER_PAR_TIN1_GPIO     (0x00)
#define MCF_GPIO_PAR_TIMER_PAR_TIN1_TOUT1    (0x08)
#define MCF_GPIO_PAR_TIMER_PAR_TIN1_DACK1    (0x04)
#define MCF_GPIO_PAR_TIMER_PAR_TIN1_TIN1     (0x0C)
#define MCF_GPIO_PAR_TIMER_PAR_TIN0_GPIO     (0x00)
#define MCF_GPIO_PAR_TIMER_PAR_TIN0_TOUT0    (0x02)
#define MCF_GPIO_PAR_TIMER_PAR_TIN0_DREQ0    (0x01)
#define MCF_GPIO_PAR_TIMER_PAR_TIN0_TIN0     (0x03)

/* Bit definitions and macros for MCF_GPIO_PAR_LCDDATA */
#define MCF_GPIO_PAR_LCDDATA_PAR_LD7_0(x)    (((x)&0x03)<<0)
#define MCF_GPIO_PAR_LCDDATA_PAR_LD15_8(x)   (((x)&0x03)<<2)
#define MCF_GPIO_PAR_LCDDATA_PAR_LD16(x)     (((x)&0x03)<<4)
#define MCF_GPIO_PAR_LCDDATA_PAR_LD17(x)     (((x)&0x03)<<6)

/* Bit definitions and macros for MCF_GPIO_PAR_LCDCTL */
#define MCF_GPIO_PAR_LCDCTL_PAR_CLS	       (0x0001)
#define MCF_GPIO_PAR_LCDCTL_PAR_PS	       (0x0002)
#define MCF_GPIO_PAR_LCDCTL_PAR_REV	       (0x0004)
#define MCF_GPIO_PAR_LCDCTL_PAR_SPL_SPR	       (0x0008)
#define MCF_GPIO_PAR_LCDCTL_PAR_CONTRAST       (0x0010)
#define MCF_GPIO_PAR_LCDCTL_PAR_LSCLK	       (0x0020)
#define MCF_GPIO_PAR_LCDCTL_PAR_LP_HSYNC       (0x0040)
#define MCF_GPIO_PAR_LCDCTL_PAR_FLM_VSYNC      (0x0080)
#define MCF_GPIO_PAR_LCDCTL_PAR_ACD_OE	       (0x0100)

/* Bit definitions and macros for MCF_GPIO_PAR_IRQ */
#define MCF_GPIO_PAR_IRQ_PAR_IRQ1(x)	       (((x)&0x0003)<<4)
#define MCF_GPIO_PAR_IRQ_PAR_IRQ2(x)	       (((x)&0x0003)<<6)
#define MCF_GPIO_PAR_IRQ_PAR_IRQ4(x)	       (((x)&0x0003)<<8)
#define MCF_GPIO_PAR_IRQ_PAR_IRQ5(x)	       (((x)&0x0003)<<10)
#define MCF_GPIO_PAR_IRQ_PAR_IRQ6(x)	       (((x)&0x0003)<<12)

/* Bit definitions and macros for MCF_GPIO_MSCR_FLEXBUS */
#define MCF_GPIO_MSCR_FLEXBUS_MSCR_ADDRCTL(x)	     (((x)&0x03)<<0)
#define MCF_GPIO_MSCR_FLEXBUS_MSCR_DLOWER(x)	     (((x)&0x03)<<2)
#define MCF_GPIO_MSCR_FLEXBUS_MSCR_DUPPER(x)	     (((x)&0x03)<<4)

/* Bit definitions and macros for MCF_GPIO_MSCR_SDRAM */
#define MCF_GPIO_MSCR_SDRAM_MSCR_SDRAM(x)    (((x)&0x03)<<0)
#define MCF_GPIO_MSCR_SDRAM_MSCR_SDCLK(x)    (((x)&0x03)<<2)
#define MCF_GPIO_MSCR_SDRAM_MSCR_SDCLKB(x)   (((x)&0x03)<<4)

/* Bit definitions and macros for MCF_GPIO_DSCR_I2C */
#define MCF_GPIO_DSCR_I2C_I2C_DSE(x)	       (((x)&0x03)<<0)

/* Bit definitions and macros for MCF_GPIO_DSCR_PWM */
#define MCF_GPIO_DSCR_PWM_PWM_DSE(x)	       (((x)&0x03)<<0)

/* Bit definitions and macros for MCF_GPIO_DSCR_FEC */
#define MCF_GPIO_DSCR_FEC_FEC_DSE(x)	       (((x)&0x03)<<0)

/* Bit definitions and macros for MCF_GPIO_DSCR_UART */
#define MCF_GPIO_DSCR_UART_UART0_DSE(x)	     (((x)&0x03)<<0)
#define MCF_GPIO_DSCR_UART_UART1_DSE(x)	     (((x)&0x03)<<2)

/* Bit definitions and macros for MCF_GPIO_DSCR_QSPI */
#define MCF_GPIO_DSCR_QSPI_QSPI_DSE(x)	     (((x)&0x03)<<0)

/* Bit definitions and macros for MCF_GPIO_DSCR_TIMER */
#define MCF_GPIO_DSCR_TIMER_TIMER_DSE(x)     (((x)&0x03)<<0)

/* Bit definitions and macros for MCF_GPIO_DSCR_SSI */
#define MCF_GPIO_DSCR_SSI_SSI_DSE(x)	       (((x)&0x03)<<0)

/* Bit definitions and macros for MCF_GPIO_DSCR_LCD */
#define MCF_GPIO_DSCR_LCD_LCD_DSE(x)	       (((x)&0x03)<<0)

/* Bit definitions and macros for MCF_GPIO_DSCR_DEBUG */
#define MCF_GPIO_DSCR_DEBUG_DEBUG_DSE(x)       (((x)&0x03)<<0)

/* Bit definitions and macros for MCF_GPIO_DSCR_CLKRST */
#define MCF_GPIO_DSCR_CLKRST_MSCR_FBCLK(x)	     (((x)&0x03)<<0)
#define MCF_GPIO_DSCR_CLKRST_RSTOUT_DSE(x)	     (((x)&0x03)<<2)

/* Bit definitions and macros for MCF_GPIO_DSCR_IRQ */
#define MCF_GPIO_DSCR_IRQ_IRQ_DSE(x)	       (((x)&0x03)<<0)

/*
 *
 * Interrupt Controller (INTC) - Chapter 14
 *
 */

#define MCF_INTC_BASE (0xFC048000)
#define MCF_INTC0_IMRH	     ((volatile UINT32*)(0xFC048008))
#define MCF_INTC0_IMRL	     ((volatile UINT32*)(0xFC04800C))
#define MCF_INTC1_IMRH	     ((volatile UINT32*)(0xFC04C008))
#define MCF_INTC1_IMRL	     ((volatile UINT32*)(0xFC04C00C))
#define MCF_INTC0_ICR(x)     ((volatile UINT8 *)(0xFC048040+((x)*0x001)))
#define MCF_INTC1_ICR(x)     ((volatile UINT8 *)(0xFC04C040+((x)*0x001)))

#include <hwif/intCtlr/mcfIntc.h>

/*
 *
 * Edge Port Module (EPORT) - Chapter 15
 *
 */

/* Register read/write macros */
#define MCF_EPORT_EPPAR	   (*(volatile UINT16*)(0xFC094000))
#define MCF_EPORT_EPDDR	   (*(volatile UINT8 *)(0xFC094002))
#define MCF_EPORT_EPIER	   (*(volatile UINT8 *)(0xFC094003))
#define MCF_EPORT_EPDR	   (*(volatile UINT8 *)(0xFC094004))
#define MCF_EPORT_EPPDR	   (*(volatile UINT8 *)(0xFC094005))
#define MCF_EPORT_EPFR	   (*(volatile UINT8 *)(0xFC094006))

/* Bit definitions and macros for MCF_EPORT_EPPAR */
#define MCF_EPORT_EPPAR_EPPA1(x)	 (((x)&0x0003)<<2)
#define MCF_EPORT_EPPAR_EPPA2(x)	 (((x)&0x0003)<<4)
#define MCF_EPORT_EPPAR_EPPA3(x)	 (((x)&0x0003)<<6)
#define MCF_EPORT_EPPAR_EPPA4(x)	 (((x)&0x0003)<<8)
#define MCF_EPORT_EPPAR_EPPA5(x)	 (((x)&0x0003)<<10)
#define MCF_EPORT_EPPAR_EPPA6(x)	 (((x)&0x0003)<<12)
#define MCF_EPORT_EPPAR_EPPA7(x)	 (((x)&0x0003)<<14)
#define MCF_EPORT_EPPAR_LEVEL		 (0)
#define MCF_EPORT_EPPAR_RISING		 (1)
#define MCF_EPORT_EPPAR_FALLING		 (2)
#define MCF_EPORT_EPPAR_BOTH		 (3)
#define MCF_EPORT_EPPAR_EPPA7_LEVEL	 (0x0000)
#define MCF_EPORT_EPPAR_EPPA7_RISING	 (0x4000)
#define MCF_EPORT_EPPAR_EPPA7_FALLING	 (0x8000)
#define MCF_EPORT_EPPAR_EPPA7_BOTH	 (0xC000)
#define MCF_EPORT_EPPAR_EPPA6_LEVEL	 (0x0000)
#define MCF_EPORT_EPPAR_EPPA6_RISING	 (0x1000)
#define MCF_EPORT_EPPAR_EPPA6_FALLING	 (0x2000)
#define MCF_EPORT_EPPAR_EPPA6_BOTH	 (0x3000)
#define MCF_EPORT_EPPAR_EPPA5_LEVEL	 (0x0000)
#define MCF_EPORT_EPPAR_EPPA5_RISING	 (0x0400)
#define MCF_EPORT_EPPAR_EPPA5_FALLING	 (0x0800)
#define MCF_EPORT_EPPAR_EPPA5_BOTH	 (0x0C00)
#define MCF_EPORT_EPPAR_EPPA4_LEVEL	 (0x0000)
#define MCF_EPORT_EPPAR_EPPA4_RISING	 (0x0100)
#define MCF_EPORT_EPPAR_EPPA4_FALLING	 (0x0200)
#define MCF_EPORT_EPPAR_EPPA4_BOTH	 (0x0300)
#define MCF_EPORT_EPPAR_EPPA3_LEVEL	 (0x0000)
#define MCF_EPORT_EPPAR_EPPA3_RISING	 (0x0040)
#define MCF_EPORT_EPPAR_EPPA3_FALLING	 (0x0080)
#define MCF_EPORT_EPPAR_EPPA3_BOTH	 (0x00C0)
#define MCF_EPORT_EPPAR_EPPA2_LEVEL	 (0x0000)
#define MCF_EPORT_EPPAR_EPPA2_RISING	 (0x0010)
#define MCF_EPORT_EPPAR_EPPA2_FALLING	 (0x0020)
#define MCF_EPORT_EPPAR_EPPA2_BOTH	 (0x0030)
#define MCF_EPORT_EPPAR_EPPA1_LEVEL	 (0x0000)
#define MCF_EPORT_EPPAR_EPPA1_RISING	 (0x0004)
#define MCF_EPORT_EPPAR_EPPA1_FALLING	 (0x0008)
#define MCF_EPORT_EPPAR_EPPA1_BOTH	 (0x000C)

/* Bit definitions and macros for MCF_EPORT_EPDDR */
#define MCF_EPORT_EPDDR_EPDD1	   (0x02)
#define MCF_EPORT_EPDDR_EPDD2	   (0x04)
#define MCF_EPORT_EPDDR_EPDD3	   (0x08)
#define MCF_EPORT_EPDDR_EPDD4	   (0x10)
#define MCF_EPORT_EPDDR_EPDD5	   (0x20)
#define MCF_EPORT_EPDDR_EPDD6	   (0x40)
#define MCF_EPORT_EPDDR_EPDD7	   (0x80)

/* Bit definitions and macros for MCF_EPORT_EPIER */
#define MCF_EPORT_EPIER_EPIE1	   (0x02)
#define MCF_EPORT_EPIER_EPIE2	   (0x04)
#define MCF_EPORT_EPIER_EPIE3	   (0x08)
#define MCF_EPORT_EPIER_EPIE4	   (0x10)
#define MCF_EPORT_EPIER_EPIE5	   (0x20)
#define MCF_EPORT_EPIER_EPIE6	   (0x40)
#define MCF_EPORT_EPIER_EPIE7	   (0x80)

/* Bit definitions and macros for MCF_EPORT_EPDR */
#define MCF_EPORT_EPDR_EPD1	   (0x02)
#define MCF_EPORT_EPDR_EPD2	   (0x04)
#define MCF_EPORT_EPDR_EPD3	   (0x08)
#define MCF_EPORT_EPDR_EPD4	   (0x10)
#define MCF_EPORT_EPDR_EPD5	   (0x20)
#define MCF_EPORT_EPDR_EPD6	   (0x40)
#define MCF_EPORT_EPDR_EPD7	   (0x80)

/* Bit definitions and macros for MCF_EPORT_EPPDR */
#define MCF_EPORT_EPPDR_EPPD1	   (0x02)
#define MCF_EPORT_EPPDR_EPPD2	   (0x04)
#define MCF_EPORT_EPPDR_EPPD3	   (0x08)
#define MCF_EPORT_EPPDR_EPPD4	   (0x10)
#define MCF_EPORT_EPPDR_EPPD5	   (0x20)
#define MCF_EPORT_EPPDR_EPPD6	   (0x40)
#define MCF_EPORT_EPPDR_EPPD7	   (0x80)

/* Bit definitions and macros for MCF_EPORT_EPFR */
#define MCF_EPORT_EPFR_EPF1	   (0x02)
#define MCF_EPORT_EPFR_EPF2	   (0x04)
#define MCF_EPORT_EPFR_EPF3	   (0x08)
#define MCF_EPORT_EPFR_EPF4	   (0x10)
#define MCF_EPORT_EPFR_EPF5	   (0x20)
#define MCF_EPORT_EPFR_EPF6	   (0x40)
#define MCF_EPORT_EPFR_EPF7	   (0x80)

/*
 *
 * Enhanced DMA (EDMA) - Chapter 16
 *
 */

#define MCF_EDMA_BASE           (0xFC044000)

#define MCF_EDMA_NUM_CHANNELS	   15

#include <hwif/dmaCtlr/mcfEdma.h>

/*
 *
 * FlexBus Chip Selects (FBCS) - Chapter 17
 *
 */

/* Register read/write macros */
#define MCF_FBCS0_CSAR	   0xFC008000
#define MCF_FBCS0_CSMR	   0xFC008004
#define MCF_FBCS0_CSCR	   0xFC008008
#define MCF_FBCS1_CSAR	   ((volatile UINT32*)(0xFC00800C))
#define MCF_FBCS1_CSMR	   ((volatile UINT32*)(0xFC008010))
#define MCF_FBCS1_CSCR	   ((volatile UINT32*)(0xFC008014))
#define MCF_FBCS2_CSAR	   ((volatile UINT32*)(0xFC008018))
#define MCF_FBCS2_CSMR	   ((volatile UINT32*)(0xFC00801C))
#define MCF_FBCS2_CSCR	   ((volatile UINT32*)(0xFC008020))
#define MCF_FBCS3_CSAR	   ((volatile UINT32*)(0xFC008024))
#define MCF_FBCS3_CSMR	   ((volatile UINT32*)(0xFC008028))
#define MCF_FBCS3_CSCR	   ((volatile UINT32*)(0xFC00802C))
#define MCF_FBCS4_CSAR	   ((volatile UINT32*)(0xFC008030))
#define MCF_FBCS4_CSMR	   ((volatile UINT32*)(0xFC008034))
#define MCF_FBCS4_CSCR	   ((volatile UINT32*)(0xFC008038))
#define MCF_FBCS5_CSAR	   ((volatile UINT32*)(0xFC00803C))
#define MCF_FBCS5_CSMR	   ((volatile UINT32*)(0xFC008040))
#define MCF_FBCS5_CSCR	   ((volatile UINT32*)(0xFC008044))
#define MCF_FBCS_CSAR(x)   ((volatile UINT32*)(0xFC008000+((x)*0x00C)))
#define MCF_FBCS_CSMR(x)   ((volatile UINT32*)(0xFC008004+((x)*0x00C)))
#define MCF_FBCS_CSCR(x)   ((volatile UINT32*)(0xFC008008+((x)*0x00C)))

/* Bit definitions and macros for MCF_FBCS_CSAR */
#define MCF_FBCS_CSAR_BA(x)	   ((x)&0xFFFF0000)

/* Bit definitions and macros for MCF_FBCS_CSMR */
#define MCF_FBCS_CSMR_V	           (0x00000001)
#define MCF_FBCS_CSMR_WP	   (0x00000100)
#define MCF_FBCS_CSMR_BAM(x)	   (((x)&0x0000FFFF)<<16)
#define MCF_FBCS_CSMR_BAM_4G	   (0xFFFF0000)
#define MCF_FBCS_CSMR_BAM_2G	   (0x7FFF0000)
#define MCF_FBCS_CSMR_BAM_1G	   (0x3FFF0000)
#define MCF_FBCS_CSMR_BAM_1024M	   (0x3FFF0000)
#define MCF_FBCS_CSMR_BAM_512M	   (0x1FFF0000)
#define MCF_FBCS_CSMR_BAM_256M	   (0x0FFF0000)
#define MCF_FBCS_CSMR_BAM_128M	   (0x07FF0000)
#define MCF_FBCS_CSMR_BAM_64M	   (0x03FF0000)
#define MCF_FBCS_CSMR_BAM_32M	   (0x01FF0000)
#define MCF_FBCS_CSMR_BAM_16M	   (0x00FF0000)
#define MCF_FBCS_CSMR_BAM_8M	   (0x007F0000)
#define MCF_FBCS_CSMR_BAM_4M	   (0x003F0000)
#define MCF_FBCS_CSMR_BAM_2M	   (0x001F0000)
#define MCF_FBCS_CSMR_BAM_1M	   (0x000F0000)
#define MCF_FBCS_CSMR_BAM_1024K	   (0x000F0000)
#define MCF_FBCS_CSMR_BAM_512K	   (0x00070000)
#define MCF_FBCS_CSMR_BAM_256K	   (0x00030000)
#define MCF_FBCS_CSMR_BAM_128K	   (0x00010000)
#define MCF_FBCS_CSMR_BAM_64K	   (0x00000000)

/* Bit definitions and macros for MCF_FBCS_CSCR */
#define MCF_FBCS_CSCR_BSTW	   (0x00000008)
#define MCF_FBCS_CSCR_BSTR	   (0x00000010)
#define MCF_FBCS_CSCR_BEM	   (0x00000020)
#define MCF_FBCS_CSCR_PS(x)	   (((x)&0x00000003)<<6)
#define MCF_FBCS_CSCR_AA	   (0x00000100)
#define MCF_FBCS_CSCR_SBM	   (0x00000200)
#define MCF_FBCS_CSCR_WS(x)	   (((x)&0x0000003F)<<10)
#define MCF_FBCS_CSCR_WRAH(x)	   (((x)&0x00000003)<<16)
#define MCF_FBCS_CSCR_RDAH(x)	   (((x)&0x00000003)<<18)
#define MCF_FBCS_CSCR_ASET(x)	   (((x)&0x00000003)<<20)
#define MCF_FBCS_CSCR_SWSEN	   (0x00800000)
#define MCF_FBCS_CSCR_SWS(x)	   (((x)&0x0000003F)<<26)
#define MCF_FBCS_CSCR_PS_8	   (0x00000040)
#define MCF_FBCS_CSCR_PS_16	   (0x00000080)
#define MCF_FBCS_CSCR_PS_32	   (0x00000000)

/*
 *
 * SDRAM Controller (SDRAMC) - Chapter 18
 *
 */

/* Register read/write macros */
#define MCF_SDRAMC_SDMR	           0xFC0B8000
#define MCF_SDRAMC_SDCR	           0xFC0B8004
#define MCF_SDRAMC_SDCFG1	   0xFC0B8008
#define MCF_SDRAMC_SDCFG2	   0xFC0B800C
#define MCF_SDRAMC_SDDS	           0xFC0B8100
#define MCF_SDRAMC_SDCS0	   0xFC0B8110
#define MCF_SDRAMC_SDCS1	   0xFC0B8114
#define MCF_SDRAMC_SDCS2	   0xFC0B8118
#define MCF_SDRAMC_SDCS3	   0xFC0B811C
#define MCF_SDRAMC_SDCS(x)	   (0xFC0B8110+((x)*0x004)))

/* Bit definitions and macros for MCF_SDRAMC_SDMR */
#define MCF_SDRAMC_SDMR_CMD	         (0x00010000)
#define MCF_SDRAMC_SDMR_AD(x)	         (((x)&0x00000FFF)<<18)
#define MCF_SDRAMC_SDMR_BNKAD(x)	 (((x)&0x00000003)<<30)
#define MCF_SDRAMC_SDMR_BNKAD_LMR	 (0x00000000)
#define MCF_SDRAMC_SDMR_BNKAD_LEMR	 (0x40000000)

/* Bit definitions and macros for MCF_SDRAMC_SDCR */
#define MCF_SDRAMC_SDCR_IPALL	   (0x00000002)
#define MCF_SDRAMC_SDCR_IREF	   (0x00000004)
#define MCF_SDRAMC_SDCR_DQS_OE(x)  (((x)&0x0000000F)<<8)
#define MCF_SDRAMC_SDCR_PS(x)	   (((x)&0x00000003)<<12)
#define MCF_SDRAMC_SDCR_RCNT(x)	   (((x)&0x0000003F)<<16)
#define MCF_SDRAMC_SDCR_MUX(x)	   (((x)&0x00000003)<<24)
#define MCF_SDRAMC_SDCR_REF	   (0x10000000)
#define MCF_SDRAMC_SDCR_DDR	   (0x20000000)
#define MCF_SDRAMC_SDCR_CKE	   (0x40000000)
#define MCF_SDRAMC_SDCR_MODE_EN	   (0x80000000)
#define MCF_SDRAMC_SDCR_PS_16	   (0x00002000)
#define MCF_SDRAMC_SDCR_PS_32	   (0x00000000)

/* Bit definitions and macros for MCF_SDRAMC_SDCFG1 */
#define MCF_SDRAMC_SDCFG1_WTLAT(x)	 (((x)&0x00000007)<<4)
#define MCF_SDRAMC_SDCFG1_REF2ACT(x)	 (((x)&0x0000000F)<<8)
#define MCF_SDRAMC_SDCFG1_PRE2ACT(x)	 (((x)&0x00000007)<<12)
#define MCF_SDRAMC_SDCFG1_ACT2RW(x)	 (((x)&0x00000007)<<16)
#define MCF_SDRAMC_SDCFG1_RDLAT(x)	 (((x)&0x0000000F)<<20)
#define MCF_SDRAMC_SDCFG1_SWT2RD(x)	 (((x)&0x00000007)<<24)
#define MCF_SDRAMC_SDCFG1_SRD2RW(x)	 (((x)&0x0000000F)<<28)

/* Bit definitions and macros for MCF_SDRAMC_SDCFG2 */
#define MCF_SDRAMC_SDCFG2_BL(x)	 (((x)&0x0000000F)<<16)
#define MCF_SDRAMC_SDCFG2_BRD2WT(x)	 (((x)&0x0000000F)<<20)
#define MCF_SDRAMC_SDCFG2_BWT2RW(x)	 (((x)&0x0000000F)<<24)
#define MCF_SDRAMC_SDCFG2_BRD2PRE(x)	 (((x)&0x0000000F)<<28)

/* Bit definitions and macros for MCF_SDRAMC_SDDS */
#define MCF_SDRAMC_SDDS_SB_D(x)	 (((x)&0x00000003)<<0)
#define MCF_SDRAMC_SDDS_SB_S(x)	 (((x)&0x00000003)<<2)
#define MCF_SDRAMC_SDDS_SB_A(x)	 (((x)&0x00000003)<<4)
#define MCF_SDRAMC_SDDS_SB_C(x)	 (((x)&0x00000003)<<6)
#define MCF_SDRAMC_SDDS_SB_E(x)	 (((x)&0x00000003)<<8)

/* Bit definitions and macros for MCF_SDRAMC_SDCS */
#define MCF_SDRAMC_SDCS_CSSZ(x)	         (((x)&0x0000001F)<<0)
#define MCF_SDRAMC_SDCS_BASE(x)	         (((x)&0x00000FFF)<<20)
#define MCF_SDRAMC_SDCS_BA(x)	         ((x)&0xFFF00000)
#define MCF_SDRAMC_SDCS_CSSZ_DIABLE	 (0x00000000)
#define MCF_SDRAMC_SDCS_CSSZ_1MBYTE	 (0x00000013)
#define MCF_SDRAMC_SDCS_CSSZ_2MBYTE	 (0x00000014)
#define MCF_SDRAMC_SDCS_CSSZ_4MBYTE	 (0x00000015)
#define MCF_SDRAMC_SDCS_CSSZ_8MBYTE	 (0x00000016)
#define MCF_SDRAMC_SDCS_CSSZ_16MBYTE	 (0x00000017)
#define MCF_SDRAMC_SDCS_CSSZ_32MBYTE	 (0x00000018)
#define MCF_SDRAMC_SDCS_CSSZ_64MBYTE	 (0x00000019)
#define MCF_SDRAMC_SDCS_CSSZ_128MBYTE	 (0x0000001A)
#define MCF_SDRAMC_SDCS_CSSZ_256MBYTE	 (0x0000001B)
#define MCF_SDRAMC_SDCS_CSSZ_512MBYTE	 (0x0000001C)
#define MCF_SDRAMC_SDCS_CSSZ_1GBYTE	 (0x0000001D)
#define MCF_SDRAMC_SDCS_CSSZ_2GBYTE	 (0x0000001E)
#define MCF_SDRAMC_SDCS_CSSZ_4GBYTE	 (0x0000001F)

/*
 *
 * Fast Ethernet Controller (FEC) - Chapter 19
 *
 */

#define MCF_FEC_BASE    (0xFC030000)

#include <hwif/end/mcfFec.h>

/*
 *
 * USB Controller (USB) - Chapter 20
 *
 */

/* Register read/write macros */
#define MCF_USB0_ID		       (*(volatile UINT32*)(0xFC0B0000))
#define MCF_USB0_HWGENERAL	       (*(volatile UINT32*)(0xFC0B0004))
#define MCF_USB0_HWHOST	               (*(volatile UINT32*)(0xFC0B0008))
#define MCF_USB0_HWDEVICE	       (*(volatile UINT32*)(0xFC0B000C))
#define MCF_USB0_HWTXBUF	       (*(volatile UINT32*)(0xFC0B0010))
#define MCF_USB0_HWRXBUF	       (*(volatile UINT32*)(0xFC0B0014))
#define MCF_USB0_CAPLENGTH	       (*(volatile UINT8 *)(0xFC0B0100))
#define MCF_USB0_HCIVERSION	       (*(volatile UINT16*)(0xFC0B0102))
#define MCF_USB0_HCSPARAMS	       (*(volatile UINT32*)(0xFC0B0104))
#define MCF_USB0_HCCPARAMS	       (*(volatile UINT32*)(0xFC0B0108))
#define MCF_USB0_DCIVERSION	       (*(volatile UINT16*)(0xFC0B0120))
#define MCF_USB0_DCCPARAMS	       (*(volatile UINT32*)(0xFC0B0124))
#define MCF_USB0_USBCMD	               (*(volatile UINT32*)(0xFC0B0140))
#define MCF_USB0_USBSTS	               (*(volatile UINT32*)(0xFC0B0144))
#define MCF_USB0_USBINTR	       (*(volatile UINT32*)(0xFC0B0148))
#define MCF_USB0_FRINDEX	       (*(volatile UINT32*)(0xFC0B014C))
#define MCF_USB0_PERIODICLISTBASE      (*(volatile UINT32*)(0xFC0B0154))
#define MCF_USB0_DEVICEADDR	       (*(volatile UINT32*)(0xFC0B0154))
#define MCF_USB0_ASYNCLISTADDR	       (*(volatile UINT32*)(0xFC0B0158))
#define MCF_USB0_EPLISTADDR	       (*(volatile UINT32*)(0xFC0B0158))
#define MCF_USB0_ASYNCTTSTS	       (*(volatile UINT32*)(0xFC0B015C))
#define MCF_USB0_BURSTSIZE	       (*(volatile UINT32*)(0xFC0B0160))
#define MCF_USB0_TXFILLTUNING	       (*(volatile UINT32*)(0xFC0B0164))
#define MCF_USB0_TXTTFILLTUNING	       (*(volatile UINT32*)(0xFC0B0168))
#define MCF_USB_ULPI0_VIEWPORT	       (*(volatile UINT32*)(0xFC0B0170))
#define MCF_USB0_CONFIGFLAG	       (*(volatile UINT32*)(0xFC0B0180))
#define MCF_USB0_PORTSC	               (*(volatile UINT32*)(0xFC0B0184))
#define MCF_USB0_OTGSC	               (*(volatile UINT32*)(0xFC0B01A4))
#define MCF_USB0_USBMODE	       (*(volatile UINT32*)(0xFC0B01A8))
#define MCF_USB0_EPSETUPSR	       (*(volatile UINT32*)(0xFC0B01AC))
#define MCF_USB0_EPPRIME	       (*(volatile UINT32*)(0xFC0B01B0))
#define MCF_USB0_EPFLUSH	       (*(volatile UINT32*)(0xFC0B01B4))
#define MCF_USB0_EPSR		       (*(volatile UINT32*)(0xFC0B01B8))
#define MCF_USB0_EPCOMPLETE	       (*(volatile UINT32*)(0xFC0B01BC))
#define MCF_USB0_EPCR0	               (*(volatile UINT32*)(0xFC0B01C0))
#define MCF_USB0_EPCR1	               (*(volatile UINT32*)(0xFC0B01C4))
#define MCF_USB0_EPCR2	               (*(volatile UINT32*)(0xFC0B01C8))
#define MCF_USB0_EPCR3	               (*(volatile UINT32*)(0xFC0B01CC))
#define MCF_USB0_EPCR(x)    (*(volatile UINT32*)(0xFC0B01C4+((x-1)*0x004)))
#define MCF_USB1_ID		       (*(volatile UINT32*)(0xFC0B4000))
#define MCF_USB1_HWGENERAL	       (*(volatile UINT32*)(0xFC0B4004))
#define MCF_USB1_HWHOST	               (*(volatile UINT32*)(0xFC0B4008))
#define MCF_USB1_HWDEVICE	       (*(volatile UINT32*)(0xFC0B400C))
#define MCF_USB1_HWTXBUF	       (*(volatile UINT32*)(0xFC0B4010))
#define MCF_USB1_HWRXBUF	       (*(volatile UINT32*)(0xFC0B4014))
#define MCF_USB1_CAPLENGTH	       (*(volatile UINT8 *)(0xFC0B4100))
#define MCF_USB1_HCIVERSION	       (*(volatile UINT16*)(0xFC0B4102))
#define MCF_USB1_HCSPARAMS	       (*(volatile UINT32*)(0xFC0B4104))
#define MCF_USB1_HCCPARAMS	       (*(volatile UINT32*)(0xFC0B4108))
#define MCF_USB1_DCIVERSION	       (*(volatile UINT16*)(0xFC0B4120))
#define MCF_USB1_DCCPARAMS	       (*(volatile UINT32*)(0xFC0B4124))
#define MCF_USB1_USBCMD	               (*(volatile UINT32*)(0xFC0B4140))
#define MCF_USB1_USBSTS	               (*(volatile UINT32*)(0xFC0B4144))
#define MCF_USB1_USBINTR	       (*(volatile UINT32*)(0xFC0B4148))
#define MCF_USB1_FRINDEX	       (*(volatile UINT32*)(0xFC0B414C))
#define MCF_USB1_PERIODICLISTBASE      (*(volatile UINT32*)(0xFC0B4154))
#define MCF_USB1_DEVICEADDR	       (*(volatile UINT32*)(0xFC0B4154))
#define MCF_USB1_ASYNCLISTADDR	       (*(volatile UINT32*)(0xFC0B4158))
#define MCF_USB1_EPLISTADDR	       (*(volatile UINT32*)(0xFC0B4158))
#define MCF_USB1_ASYNCTTSTS	       (*(volatile UINT32*)(0xFC0B415C))
#define MCF_USB1_BURSTSIZE	       (*(volatile UINT32*)(0xFC0B4160))
#define MCF_USB1_TXFILLTUNING	       (*(volatile UINT32*)(0xFC0B4164))
#define MCF_USB1_TXTTFILLTUNING	       (*(volatile UINT32*)(0xFC0B4168))
#define MCF_USB_ULPI1_VIEWPORT	       (*(volatile UINT32*)(0xFC0B4170))
#define MCF_USB1_CONFIGFLAG	       (*(volatile UINT32*)(0xFC0B4180))
#define MCF_USB1_PORTSC	               (*(volatile UINT32*)(0xFC0B4184))
#define MCF_USB1_OTGSC	               (*(volatile UINT32*)(0xFC0B41A4))
#define MCF_USB1_USBMODE	       (*(volatile UINT32*)(0xFC0B41A8))
#define MCF_USB1_EPSETUPSR	       (*(volatile UINT32*)(0xFC0B41AC))
#define MCF_USB1_EPPRIME	       (*(volatile UINT32*)(0xFC0B41B0))
#define MCF_USB1_EPFLUSH	       (*(volatile UINT32*)(0xFC0B41B4))
#define MCF_USB1_EPSR		       (*(volatile UINT32*)(0xFC0B41B8))
#define MCF_USB1_EPCOMPLETE	       (*(volatile UINT32*)(0xFC0B41BC))
#define MCF_USB1_EPCR0	               (*(volatile UINT32*)(0xFC0B41C0))
#define MCF_USB1_EPCR1	               (*(volatile UINT32*)(0xFC0B41C4))
#define MCF_USB1_EPCR2	               (*(volatile UINT32*)(0xFC0B41C8))
#define MCF_USB1_EPCR3	               (*(volatile UINT32*)(0xFC0B41CC))
#define MCF_USB1_EPCR(x)	       (*(volatile UINT32*)(0xFC0B41C4+((x-1)*0x004)))
#define MCF_USB_ID(x)		       (*(volatile UINT32*)(0xFC0B0000+((x)*0x4000)))
#define MCF_USB_HWGENERAL(x)	       (*(volatile UINT32*)(0xFC0B0004+((x)*0x4000)))
#define MCF_USB_HWHOST(x)	       (*(volatile UINT32*)(0xFC0B0008+((x)*0x4000)))
#define MCF_USB_HWDEVICE(x)	       (*(volatile UINT32*)(0xFC0B000C+((x)*0x4000)))
#define MCF_USB_HWTXBUF(x)	       (*(volatile UINT32*)(0xFC0B0010+((x)*0x4000)))
#define MCF_USB_HWRXBUF(x)	       (*(volatile UINT32*)(0xFC0B0014+((x)*0x4000)))
#define MCF_USB_CAPLENGTH(x)	       (*(volatile UINT8 *)(0xFC0B0100+((x)*0x4000)))
#define MCF_USB_HCIVERSION(x)	       (*(volatile UINT16*)(0xFC0B0102+((x)*0x4000)))
#define MCF_USB_HCSPARAMS(x)	       (*(volatile UINT32*)(0xFC0B0104+((x)*0x4000)))
#define MCF_USB_HCCPARAMS(x)	       (*(volatile UINT32*)(0xFC0B0108+((x)*0x4000)))
#define MCF_USB_DCIVERSION(x)	       (*(volatile UINT16*)(0xFC0B0120+((x)*0x4000)))
#define MCF_USB_DCCPARAMS(x)	       (*(volatile UINT32*)(0xFC0B0124+((x)*0x4000)))
#define MCF_USB_USBCMD(x)	       (*(volatile UINT32*)(0xFC0B0140+((x)*0x4000)))
#define MCF_USB_USBSTS(x)	       (*(volatile UINT32*)(0xFC0B0144+((x)*0x4000)))
#define MCF_USB_USBINTR(x)	       (*(volatile UINT32*)(0xFC0B0148+((x)*0x4000)))
#define MCF_USB_FRINDEX(x)	       (*(volatile UINT32*)(0xFC0B014C+((x)*0x4000)))
#define MCF_USB_PERIODICLISTBASE(x)    (*(volatile UINT32*)(0xFC0B0154+((x)*0x4000)))
#define MCF_USB_DEVICEADDR(x)	       (*(volatile UINT32*)(0xFC0B0154+((x)*0x4000)))
#define MCF_USB_ASYNCLISTADDR(x)       (*(volatile UINT32*)(0xFC0B0158+((x)*0x4000)))
#define MCF_USB_EPLISTADDR(x)	       (*(volatile UINT32*)(0xFC0B0158+((x)*0x4000)))
#define MCF_USB_ASYNCTTSTS(x)	       (*(volatile UINT32*)(0xFC0B015C+((x)*0x4000)))
#define MCF_USB_BURSTSIZE(x)	       (*(volatile UINT32*)(0xFC0B0160+((x)*0x4000)))
#define MCF_USB_TXFILLTUNING(x)	       (*(volatile UINT32*)(0xFC0B0164+((x)*0x4000)))
#define MCF_USB_TXTTFILLTUNING(x)      (*(volatile UINT32*)(0xFC0B0168+((x)*0x4000)))
#define MCF_USB_ULPI_VIEWPORT(x)       (*(volatile UINT32*)(0xFC0B0170+((x)*0x4000)))
#define MCF_USB_CONFIGFLAG(x)	       (*(volatile UINT32*)(0xFC0B0180+((x)*0x4000)))
#define MCF_USB_PORTSC(x)	       (*(volatile UINT32*)(0xFC0B0184+((x)*0x4000)))
#define MCF_USB_OTGSC(x)	       (*(volatile UINT32*)(0xFC0B01A4+((x)*0x4000)))
#define MCF_USB_USBMODE(x)	       (*(volatile UINT32*)(0xFC0B01A8+((x)*0x4000)))
#define MCF_USB_EPSETUPSR(x)	       (*(volatile UINT32*)(0xFC0B01AC+((x)*0x4000)))
#define MCF_USB_EPPRIME(x)	       (*(volatile UINT32*)(0xFC0B01B0+((x)*0x4000)))
#define MCF_USB_EPFLUSH(x)	       (*(volatile UINT32*)(0xFC0B01B4+((x)*0x4000)))
#define MCF_USB_EPSR(x)	               (*(volatile UINT32*)(0xFC0B01B8+((x)*0x4000)))
#define MCF_USB_EPCOMPLETE(x)	       (*(volatile UINT32*)(0xFC0B01BC+((x)*0x4000)))
#define MCF_USB_EPCR0(x)	       (*(volatile UINT32*)(0xFC0B01C0+((x)*0x4000)))
#define MCF_USB_EPCR1(x)	       (*(volatile UINT32*)(0xFC0B01C4+((x)*0x4000)))
#define MCF_USB_EPCR2(x)	       (*(volatile UINT32*)(0xFC0B01C8+((x)*0x4000)))
#define MCF_USB_EPCR3(x)	       (*(volatile UINT32*)(0xFC0B01CC+((x)*0x4000)))

/* Bit definitions and macros for MCF_USB_ID */
#define MCF_USB_ID_RESERVED	       (0x0000C000)
#define MCF_USB_ID_ID(x)	       (((x)&0x0000003F)<<0|0x0000C000)
#define MCF_USB_ID_NID(x)	       (((x)&0x0000003F)<<8|0x0000C000)
#define MCF_USB_ID_REVISION(x)	       (((x)&0x000000FF)<<16|0x0000C000)

/* Bit definitions and macros for MCF_USB_HWGENERAL */
#define MCF_USB_HWGENERAL_RT	       (0x00000001)
#define MCF_USB_HWGENERAL_CLKC(x)      (((x)&0x00000003)<<1)
#define MCF_USB_HWGENERAL_BWT	       (0x00000008)
#define MCF_USB_HWGENERAL_PHYW(x)      (((x)&0x00000003)<<4)
#define MCF_USB_HWGENERAL_PHYM(x)      (((x)&0x00000007)<<6)
#define MCF_USB_HWGENERAL_SM(x)	       (((x)&0x00000003)<<9)

/* Bit definitions and macros for MCF_USB_HWHOST */
#define MCF_USB_HWHOST_HC	       (0x00000001)
#define MCF_USB_HWHOST_NPORT(x)	       (((x)&0x00000007)<<1)
#define MCF_USB_HWHOST_TTASY(x)	       (((x)&0x000000FF)<<16)
#define MCF_USB_HWHOST_TTPER(x)	       (((x)&0x000000FF)<<24)

/* Bit definitions and macros for MCF_USB_HWDEVICE */
#define MCF_USB_HWDEVICE_DC	       (0x00000001)
#define MCF_USB_HWDEVICE_DEVEP(x)      (((x)&0x0000001F)<<1)

/* Bit definitions and macros for MCF_USB_HWTXBUF */
#define MCF_USB_HWTXBUF_TXBURST(x)     (((x)&0x000000FF)<<0)
#define MCF_USB_HWTXBUF_TXADD(x)       (((x)&0x000000FF)<<8)
#define MCF_USB_HWTXBUF_TXCHANADD(x)   (((x)&0x000000FF)<<16)
#define MCF_USB_HWTXBUF_TXLC	       (0x80000000)

/* Bit definitions and macros for MCF_USB_HWRXBUF */
#define MCF_USB_HWRXBUF_RXBURST(x)	     (((x)&0x000000FF)<<0)
#define MCF_USB_HWRXBUF_RXADD(x)	     (((x)&0x000000FF)<<8)

/* Bit definitions and macros for MCF_USB_CAPLENGTH */
#define MCF_USB_CAPLENGTH_CAPLENGTH(x)	   (((x)&0xFF)<<0)

/* Bit definitions and macros for MCF_USB_HCIVERSION */
#define MCF_USB_HCIVERSION_HCIVERSION(x)	   (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF_USB_HCSPARAMS */
#define MCF_USB_HCSPARAMS_N_PORTS(x)	     (((x)&0x0000000F)<<0)
#define MCF_USB_HCSPARAMS_PPC	             (0x00000010)
#define MCF_USB_HCSPARAMS_N_PCC(x)	     (((x)&0x0000000F)<<8)
#define MCF_USB_HCSPARAMS_N_CC(x)	     (((x)&0x0000000F)<<12)
#define MCF_USB_HCSPARAMS_PI	             (0x00010000)
#define MCF_USB_HCSPARAMS_N_PTT(x)	     (((x)&0x0000000F)<<20)
#define MCF_USB_HCSPARAMS_N_TT(x)	     (((x)&0x0000000F)<<24)

/* Bit definitions and macros for MCF_USB_HCCPARAMS */
#define MCF_USB_HCCPARAMS_ADC	       (0x00000001)
#define MCF_USB_HCCPARAMS_PFL	       (0x00000002)
#define MCF_USB_HCCPARAMS_ASP	       (0x00000004)
#define MCF_USB_HCCPARAMS_IST(x)       (((x)&0x0000000F)<<4)
#define MCF_USB_HCCPARAMS_EECP(x)      (((x)&0x000000FF)<<8)

/* Bit definitions and macros for MCF_USB_DCIVERSION */
#define MCF_USB_DCIVERSION_DCIVERSION(x)	   (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF_USB_DCCPARAMS */
#define MCF_USB_DCCPARAMS_DEN(x)       (((x)&0x0000001F)<<0)
#define MCF_USB_DCCPARAMS_DC	       (0x00000080)
#define MCF_USB_DCCPARAMS_HC	       (0x00000100)

/* Bit definitions and macros for MCF_USB_USBCMD */
#define MCF_USB_USBCMD_RS	       (0x00000001)
#define MCF_USB_USBCMD_RST	       (0x00000002)
#define MCF_USB_USBCMD_FS0	       (0x00000004)
#define MCF_USB_USBCMD_FS1	       (0x00000008)
#define MCF_USB_USBCMD_PSE	       (0x00000010)
#define MCF_USB_USBCMD_ASE	       (0x00000020)
#define MCF_USB_USBCMD_IAA	       (0x00000040)
#define MCF_USB_USBCMD_LR	       (0x00000080)
#define MCF_USB_USBCMD_ASP(x)	       (((x)&0x00000003)<<8)
#define MCF_USB_USBCMD_ASPE	       (0x00000800)
#define MCF_USB_USBCMD_SUTW	       (0x00002000)
#define MCF_USB_USBCMD_ATDTW	       (0x00004000)
#define MCF_USB_USBCMD_FS2	       (0x00008000)
#define MCF_USB_USBCMD_ITC(x)	       (((x)&0x000000FF)<<16)
#define MCF_USB_USBCMD_ITC_IMM	       (0x00000000)
#define MCF_USB_USBCMD_ITC_1	       (0x00010000)
#define MCF_USB_USBCMD_ITC_2	       (0x00020000)
#define MCF_USB_USBCMD_ITC_4	       (0x00040000)
#define MCF_USB_USBCMD_ITC_8	       (0x00080000)
#define MCF_USB_USBCMD_ITC_16	       (0x00100000)
#define MCF_USB_USBCMD_ITC_32	       (0x00200000)
#define MCF_USB_USBCMD_ITC_40	       (0x00400000)
#define MCF_USB_USBCMD_FS_1024	       (0x00000000)
#define MCF_USB_USBCMD_FS_512	       (0x00000004)
#define MCF_USB_USBCMD_FS_256	       (0x00000008)
#define MCF_USB_USBCMD_FS_128	       (0x0000000C)
#define MCF_USB_USBCMD_FS_64	       (0x00008000)
#define MCF_USB_USBCMD_FS_32	       (0x00008004)
#define MCF_USB_USBCMD_FS_16	       (0x00008008)
#define MCF_USB_USBCMD_FS_8	       (0x0000800C)

/* Bit definitions and macros for MCF_USB_USBSTS */
#define MCF_USB_USBSTS_UI	       (0x00000001)
#define MCF_USB_USBSTS_UEI	       (0x00000002)
#define MCF_USB_USBSTS_PCI	       (0x00000004)
#define MCF_USB_USBSTS_FRI	       (0x00000008)
#define MCF_USB_USBSTS_SEI	       (0x00000010)
#define MCF_USB_USBSTS_AAI	       (0x00000020)
#define MCF_USB_USBSTS_URI	       (0x00000040)
#define MCF_USB_USBSTS_SRI	       (0x00000080)
#define MCF_USB_USBSTS_SLI	       (0x00000100)
#define MCF_USB_USBSTS_HCH	       (0x00001000)
#define MCF_USB_USBSTS_RCL	       (0x00002000)
#define MCF_USB_USBSTS_PS	       (0x00004000)
#define MCF_USB_USBSTS_AS	       (0x00008000)

/* Bit definitions and macros for MCF_USB_USBINTR */
#define MCF_USB_USBINTR_UE	       (0x00000001)
#define MCF_USB_USBINTR_UEE	       (0x00000002)
#define MCF_USB_USBINTR_PCE	       (0x00000004)
#define MCF_USB_USBINTR_FRE	       (0x00000008)
#define MCF_USB_USBINTR_SEE	       (0x00000010)
#define MCF_USB_USBINTR_AAE	       (0x00000020)
#define MCF_USB_USBINTR_URE	       (0x00000040)
#define MCF_USB_USBINTR_SRE	       (0x00000080)
#define MCF_USB_USBINTR_SLE	       (0x00000100)

/* Bit definitions and macros for MCF_USB_FRINDEX */
#define MCF_USB_FRINDEX_FRINDEX(x)	     (((x)&0x00003FFF)<<0)

/* Bit definitions and macros for MCF_USB_PERIODICLISTBASE */
#define MCF_USB_PERIODICLISTBASE_PERBASE(x)	   (((x)&0x000FFFFF)<<12)

/* Bit definitions and macros for MCF_USB_DEVICEADDR */
#define MCF_USB_DEVICEADDR_USBADR(x)	     (((x)&0x0000007F)<<25)

/* Bit definitions and macros for MCF_USB_ASYNCLISTADDR */
#define MCF_USB_ASYNCLISTADDR_ASYBASE(x)	   (((x)&0x07FFFFFF)<<5)

/* Bit definitions and macros for MCF_USB_EPLISTADDR */
#define MCF_USB_EPLISTADDR_EPBASE(x)	     (((x)&0x001FFFFF)<<11)

/* Bit definitions and macros for MCF_USB_ASYNCTTSTS */
#define MCF_USB_ASYNCTTSTS_TTAS	     (0x00000001)
#define MCF_USB_ASYNCTTSTS_TTAC	     (0x00000002)

/* Bit definitions and macros for MCF_USB_BURSTSIZE */
#define MCF_USB_BURSTSIZE_RXPBURST(x)	     (((x)&0x000000FF)<<0)
#define MCF_USB_BURSTSIZE_TXPBURST(x)	     (((x)&0x000000FF)<<8)

/* Bit definitions and macros for MCF_USB_TXFILLTUNING */
#define MCF_USB_TXFILLTUNING_TXSCHOH(x)	   (((x)&0x000000FF)<<0)
#define MCF_USB_TXFILLTUNING_TXSCHHEALTH(x)	   (((x)&0x0000001F)<<8)
#define MCF_USB_TXFILLTUNING_TXFIFOTHRES(x)	   (((x)&0x0000003F)<<16)

/* Bit definitions and macros for MCF_USB_TXTTFILLTUNING */
#define MCF_USB_TXTTFILLTUNING_TXTTSCHOH(x)	   (((x)&0x0000001F)<<0)
#define MCF_USB_TXTTFILLTUNING_TXTTSCHHEALTH(x)	 (((x)&0x0000001F)<<8)

/* Bit definitions and macros for MCF_USB_CONFIGFLAG */
#define MCF_USB_CONFIGFLAG_CONFIGFLAG(x)	   (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF_USB_PORTSC */
#define MCF_USB_PORTSC_CCS	       (0x00000001)
#define MCF_USB_PORTSC_CSC	       (0x00000002)
#define MCF_USB_PORTSC_PE	       (0x00000004)
#define MCF_USB_PORTSC_PEC	       (0x00000008)
#define MCF_USB_PORTSC_OCA	       (0x00000010)
#define MCF_USB_PORTSC_OCC	       (0x00000020)
#define MCF_USB_PORTSC_FPR	       (0x00000040)
#define MCF_USB_PORTSC_SUSP	       (0x00000080)
#define MCF_USB_PORTSC_PR	       (0x00000100)
#define MCF_USB_PORTSC_LS(x)	       (((x)&0x00000003)<<10)
#define MCF_USB_PORTSC_PP	       (0x00001000)
#define MCF_USB_PORTSC_PO	       (0x00002000)
#define MCF_USB_PORTSC_PIC(x)	       (((x)&0x00000003)<<14)
#define MCF_USB_PORTSC_PTC(x)	       (((x)&0x0000000F)<<16)
#define MCF_USB_PORTSC_WLCN	       (0x00100000)
#define MCF_USB_PORTSC_WKDS	       (0x00200000)
#define MCF_USB_PORTSC_WKOC	       (0x00400000)
#define MCF_USB_PORTSC_PHCD	       (0x00800000)
#define MCF_USB_PORTSC_PFSC	       (0x01000000)
#define MCF_USB_PORTSC_PSPD(x)	       (((x)&0x00000003)<<26)
#define MCF_USB_PORTSC_PTS(x)	       (((x)&0x00000003)<<30)
#define MCF_USB_PORTSC_PTS_ULPI	       (0x80000000)
#define MCF_USB_PORTSC_PTS_FS_LS       (0xC0000000)
#define MCF_USB_PORTSC_PSPD_FULL       (0x00000000)
#define MCF_USB_PORTSC_PSPD_LOW	       (0x04000000)
#define MCF_USB_PORTSC_PSPD_HIGH       (0x08000000)
#define MCF_USB_PORTSC_PTC_DISBALE     (0x00000000)
#define MCF_USB_PORTSC_PTC_JSTATE      (0x00010000)
#define MCF_USB_PORTSC_PTC_KSTATE      (0x00020000)
#define MCF_USB_PORTSC_PTC_SEQ_NAK     (0x00030000)
#define MCF_USB_PORTSC_PTC_PACKET      (0x00040000)
#define MCF_USB_PORTSC_PTC_FORCE_ENABLE	   (0x00050000)
#define MCF_USB_PORTSC_PIC_OFF	       (0x00000000)
#define MCF_USB_PORTSC_PIC_AMBER       (0x00004000)
#define MCF_USB_PORTSC_PIC_GREEN       (0x00008000)
#define MCF_USB_PORTSC_LS_SE0	       (0x00000000)
#define MCF_USB_PORTSC_LS_JSTATE       (0x00000400)
#define MCF_USB_PORTSC_LS_KSTATE       (0x00000800)

/* Bit definitions and macros for MCF_USB_OTGSC */
#define MCF_USB_OTGSC_VD	       (0x00000001)
#define MCF_USB_OTGSC_VC	       (0x00000002)
#define MCF_USB_OTGSC_OT	       (0x00000008)
#define MCF_USB_OTGSC_DP	       (0x00000010)
#define MCF_USB_OTGSC_ID	       (0x00000100)
#define MCF_USB_OTGSC_AVV	       (0x00000200)
#define MCF_USB_OTGSC_ASV	       (0x00000400)
#define MCF_USB_OTGSC_BSV	       (0x00000800)
#define MCF_USB_OTGSC_BSE	       (0x00001000)
#define MCF_USB_OTGSC_1MST	       (0x00002000)
#define MCF_USB_OTGSC_DPS	       (0x00004000)
#define MCF_USB_OTGSC_IDIS	       (0x00010000)
#define MCF_USB_OTGSC_AVVIS	       (0x00020000)
#define MCF_USB_OTGSC_ASVIS	       (0x00040000)
#define MCF_USB_OTGSC_BSVIS	       (0x00080000)
#define MCF_USB_OTGSC_BSEIS	       (0x00100000)
#define MCF_USB_OTGSC_1MSS	       (0x00200000)
#define MCF_USB_OTGSC_DPIS	       (0x00400000)
#define MCF_USB_OTGSC_IDIE	       (0x01000000)
#define MCF_USB_OTGSC_AVVIE	       (0x02000000)
#define MCF_USB_OTGSC_ADVIE	       (0x04000000)
#define MCF_USB_OTGSC_BSVIE	       (0x08000000)
#define MCF_USB_OTGSC_BSEIE	       (0x10000000)
#define MCF_USB_OTGSC_1MSE	       (0x20000000)
#define MCF_USB_OTGSC_DPIE	       (0x40000000)
#define MCF_USB_OTGSC_CLEAR	       (0x007F0000)
#define MCF_USB_OTGSC_ENABLE_ALL       (0x7F000000)

/* Bit definitions and macros for MCF_USB_USBMODE */
#define MCF_USB_USBMODE_CM(x)	       (((x)&0x00000003)<<0)
#define MCF_USB_USBMODE_ES	       (0x00000004)
#define MCF_USB_USBMODE_SLOM	       (0x00000008)
#define MCF_USB_USBMODE_SDIS	       (0x00000010)
#define MCF_USB_USBMODE_CM_IDLE	       (0x00000000)
#define MCF_USB_USBMODE_CM_DEVICE      (0x00000002)
#define MCF_USB_USBMODE_CM_HOST	       (0x00000003)

/* Bit definitions and macros for MCF_USB_EPSETUPSR */
#define MCF_USB_EPSETUPSR_EPSETUPSTAT(x)	   (((x)&0x0000003F)<<0)

/* Bit definitions and macros for MCF_USB_EPPRIME */
#define MCF_USB_EPPRIME_PERB(x)	       (((x)&0x0000003F)<<0)
#define MCF_USB_EPPRIME_PETB(x)	       (((x)&0x0000003F)<<16)
#define MCF_USB_EPPRIME_PETB0	       (0x00010000)
#define MCF_USB_EPPRIME_PETB1	       (0x00020000)
#define MCF_USB_EPPRIME_PETB2	       (0x00040000)
#define MCF_USB_EPPRIME_PETB3	       (0x00080000)
#define MCF_USB_EPPRIME_PETB4	       (0x00100000)
#define MCF_USB_EPPRIME_PETB5	       (0x00200000)
#define MCF_USB_EPPRIME_PERB0	       (0x00000001)
#define MCF_USB_EPPRIME_PERB1	       (0x00000002)
#define MCF_USB_EPPRIME_PERB2	       (0x00000004)
#define MCF_USB_EPPRIME_PERB3	       (0x00000008)
#define MCF_USB_EPPRIME_PERB4	       (0x00000010)
#define MCF_USB_EPPRIME_PERB5	       (0x00000020)

/* Bit definitions and macros for MCF_USB_EPFLUSH */
#define MCF_USB_EPFLUSH_FERB(x)	       (((x)&0x0000003F)<<0)
#define MCF_USB_EPFLUSH_FETB(x)	       (((x)&0x0000003F)<<16)
#define MCF_USB_EPFLUSH_FETB0	       (0x00010000)
#define MCF_USB_EPFLUSH_FETB1	       (0x00020000)
#define MCF_USB_EPFLUSH_FETB2	       (0x00040000)
#define MCF_USB_EPFLUSH_FETB3	       (0x00080000)
#define MCF_USB_EPFLUSH_FETB4	       (0x00100000)
#define MCF_USB_EPFLUSH_FETB5	       (0x00200000)
#define MCF_USB_EPFLUSH_FERB0	       (0x00000001)
#define MCF_USB_EPFLUSH_FERB1	       (0x00000002)
#define MCF_USB_EPFLUSH_FERB2	       (0x00000004)
#define MCF_USB_EPFLUSH_FERB3	       (0x00000008)
#define MCF_USB_EPFLUSH_FERB4	       (0x00000010)
#define MCF_USB_EPFLUSH_FERB5	       (0x00000020)

/* Bit definitions and macros for MCF_USB_EPSR */
#define MCF_USB_EPSR_ERBR(x)	       (((x)&0x0000003F)<<0)
#define MCF_USB_EPSR_ETBR(x)	       (((x)&0x0000003F)<<16)
#define MCF_USB_EPSR_ETBR0	       (0x00010000)
#define MCF_USB_EPSR_ETBR1	       (0x00020000)
#define MCF_USB_EPSR_ETBR2	       (0x00040000)
#define MCF_USB_EPSR_ETBR3	       (0x00080000)
#define MCF_USB_EPSR_ETBR4	       (0x00100000)
#define MCF_USB_EPSR_ETBR5	       (0x00200000)
#define MCF_USB_EPSR_ERBR0	       (0x00000001)
#define MCF_USB_EPSR_ERBR1	       (0x00000002)
#define MCF_USB_EPSR_ERBR2	       (0x00000004)
#define MCF_USB_EPSR_ERBR3	       (0x00000008)
#define MCF_USB_EPSR_ERBR4	       (0x00000010)
#define MCF_USB_EPSR_ERBR5	       (0x00000020)

/* Bit definitions and macros for MCF_USB_EPCOMPLETE */
#define MCF_USB_EPCOMPLETE_ERCE(x)	     (((x)&0x0000003F)<<0)
#define MCF_USB_EPCOMPLETE_ETCE(x)	     (((x)&0x0000003F)<<16)
#define MCF_USB_EPCOMPLETE_ETCE0	     (0x00010000)
#define MCF_USB_EPCOMPLETE_ETCE1	     (0x00020000)
#define MCF_USB_EPCOMPLETE_ETCE2	     (0x00040000)
#define MCF_USB_EPCOMPLETE_ETCE3	     (0x00080000)
#define MCF_USB_EPCOMPLETE_ETCE4	     (0x00100000)
#define MCF_USB_EPCOMPLETE_ETCE5	     (0x00200000)
#define MCF_USB_EPCOMPLETE_ERCE0	     (0x00000001)
#define MCF_USB_EPCOMPLETE_ERCE1	     (0x00000002)
#define MCF_USB_EPCOMPLETE_ERCE2	     (0x00000004)
#define MCF_USB_EPCOMPLETE_ERCE3	     (0x00000008)
#define MCF_USB_EPCOMPLETE_ERCE4	     (0x00000010)
#define MCF_USB_EPCOMPLETE_ERCE5	     (0x00000020)

/* Bit definitions and macros for MCF_USB_EPCR0 */
#define MCF_USB_EPCR0_RXS	       (0x00000001)
#define MCF_USB_EPCR0_RXT(x)	       (((x)&0x00000003)<<2)
#define MCF_USB_EPCR0_RXE	       (0x00000080)
#define MCF_USB_EPCR0_TXS	       (0x00010000)
#define MCF_USB_EPCR0_TXT(x)	       (((x)&0x00000003)<<18)
#define MCF_USB_EPCR0_TXE	       (0x00800000)

/* Bit definitions and macros for MCF_USB_EPCR */
#define MCF_USB_EPCR_RXS	       (0x00000001)
#define MCF_USB_EPCR_RXD	       (0x00000002)
#define MCF_USB_EPCR_RXT(x)	       (((x)&0x00000003)<<2)
#define MCF_USB_EPCR_RXI	       (0x00000020)
#define MCF_USB_EPCR_RXR	       (0x00000040)
#define MCF_USB_EPCR_RXE	       (0x00000080)
#define MCF_USB_EPCR_TXS	       (0x00010000)
#define MCF_USB_EPCR_TXD	       (0x00020000)
#define MCF_USB_EPCR_TXT(x)	       (((x)&0x00000003)<<18)
#define MCF_USB_EPCR_TXI	       (0x00200000)
#define MCF_USB_EPCR_TXR	       (0x00400000)
#define MCF_USB_EPCR_TXE	       (0x00800000)
#define MCF_USB_EPCR_TXT_CONTROL       (0x00000000)
#define MCF_USB_EPCR_TXT_ISO	       (0x00040000)
#define MCF_USB_EPCR_TXT_BULK	       (0x00080000)
#define MCF_USB_EPCR_TXT_INT	       (0x000C0000)
#define MCF_USB_EPCR_RXT_CONTROL       (0x00000000)
#define MCF_USB_EPCR_RXT_ISO	       (0x00000004)
#define MCF_USB_EPCR_RXT_BULK	       (0x00000008)
#define MCF_USB_EPCR_RXT_INT	       (0x0000000C)

/*
 *
 * LCD Controller (LCDC) - Chapter 22
 *
 */

/* Register read/write macros */
#define MCF_LCDC_LSSAR	                (*(volatile UINT32*)(0xFC0AC000))
#define MCF_LCDC_LSR	                (*(volatile UINT32*)(0xFC0AC004))
#define MCF_LCDC_LVPWR	                (*(volatile UINT32*)(0xFC0AC008))
#define MCF_LCDC_LCPR		        (*(volatile UINT32*)(0xFC0AC00C))
#define MCF_LCDC_LCWHBR	                (*(volatile UINT32*)(0xFC0AC010))
#define MCF_LCDC_LCCMR	                (*(volatile UINT32*)(0xFC0AC014))
#define MCF_LCDC_LPCR		        (*(volatile UINT32*)(0xFC0AC018))
#define MCF_LCDC_LHCR		        (*(volatile UINT32*)(0xFC0AC01C))
#define MCF_LCDC_LVCR		        (*(volatile UINT32*)(0xFC0AC020))
#define MCF_LCDC_LPOR		        (*(volatile UINT32*)(0xFC0AC024))
#define MCF_LCDC_LSCR		        (*(volatile UINT32*)(0xFC0AC028))
#define MCF_LCDC_LPCCR	                (*(volatile UINT32*)(0xFC0AC02C))
#define MCF_LCDC_LDCR		        (*(volatile UINT32*)(0xFC0AC030))
#define MCF_LCDC_LRMCR	                (*(volatile UINT32*)(0xFC0AC034))
#define MCF_LCDC_LICR		        (*(volatile UINT32*)(0xFC0AC038))
#define MCF_LCDC_LIER		        (*(volatile UINT32*)(0xFC0AC03C))
#define MCF_LCDC_LISR		        (*(volatile UINT32*)(0xFC0AC040))
#define MCF_LCDC_LGWSAR	                (*(volatile UINT32*)(0xFC0AC050))
#define MCF_LCDC_LGWSR	                (*(volatile UINT32*)(0xFC0AC054))
#define MCF_LCDC_LGWVPWR	        (*(volatile UINT32*)(0xFC0AC058))
#define MCF_LCDC_LGWPOR	                (*(volatile UINT32*)(0xFC0AC05C))
#define MCF_LCDC_LGWPR	                (*(volatile UINT32*)(0xFC0AC060))
#define MCF_LCDC_LGWCR	                (*(volatile UINT32*)(0xFC0AC064))
#define MCF_LCDC_LGWDCR	                (*(volatile UINT32*)(0xFC0AC068))
#define MCF_LCDC_BPLUT_BASE	        (*(volatile UINT32*)(0xFC0AC800))
#define MCF_LCDC_GWLUT_BASE	        (*(volatile UINT32*)(0xFC0ACC00))

/* Bit definitions and macros for MCF_LCDC_LSSAR */
#define MCF_LCDC_LSSAR_SSA(x)	    (((x)&0x3FFFFFFF)<<2)

/* Bit definitions and macros for MCF_LCDC_LSR */
#define MCF_LCDC_LSR_YMAX(x)	    (((x)&0x000003FF)<<0)
#define MCF_LCDC_LSR_XMAX(x)	    (((x)&0x0000003F)<<20)

/* Bit definitions and macros for MCF_LCDC_LVPWR */
#define MCF_LCDC_LVPWR_VPW(x)	    (((x)&0x000003FF)<<0)

/* Bit definitions and macros for MCF_LCDC_LCPR */
#define MCF_LCDC_LCPR_CYP(x)	    (((x)&0x000003FF)<<0)
#define MCF_LCDC_LCPR_CXP(x)	    (((x)&0x000003FF)<<16)
#define MCF_LCDC_LCPR_OP	    (0x10000000)
#define MCF_LCDC_LCPR_CC(x)	    (((x)&0x00000003)<<30)
#define MCF_LCDC_LCPR_CC_TRANSPARENT	  (0x00000000)
#define MCF_LCDC_LCPR_CC_OR	    (0x40000000)
#define MCF_LCDC_LCPR_CC_XOR	    (0x80000000)
#define MCF_LCDC_LCPR_CC_AND	    (0xC0000000)
#define MCF_LCDC_LCPR_OP_ON	    (0x10000000)
#define MCF_LCDC_LCPR_OP_OFF	    (0x00000000)

/* Bit definitions and macros for MCF_LCDC_LCWHBR */
#define MCF_LCDC_LCWHBR_BD(x)	    (((x)&0x000000FF)<<0)
#define MCF_LCDC_LCWHBR_CH(x)	    (((x)&0x0000001F)<<16)
#define MCF_LCDC_LCWHBR_CW(x)	    (((x)&0x0000001F)<<24)
#define MCF_LCDC_LCWHBR_BK_EN	    (0x80000000)
#define MCF_LCDC_LCWHBR_BK_EN_ON    (0x80000000)
#define MCF_LCDC_LCWHBR_BK_EN_OFF   (0x00000000)

/* Bit definitions and macros for MCF_LCDC_LCCMR */
#define MCF_LCDC_LCCMR_CUR_COL_B(x)	  (((x)&0x0000003F)<<0)
#define MCF_LCDC_LCCMR_CUR_COL_G(x)	  (((x)&0x0000003F)<<6)
#define MCF_LCDC_LCCMR_CUR_COL_R(x)	  (((x)&0x0000003F)<<12)

/* Bit definitions and macros for MCF_LCDC_LPCR */
#define MCF_LCDC_LPCR_PCD(x)	    (((x)&0x0000003F)<<0)
#define MCF_LCDC_LPCR_SHARP	    (0x00000040)
#define MCF_LCDC_LPCR_SCLKSEL	    (0x00000080)
#define MCF_LCDC_LPCR_ACD(x)	    (((x)&0x0000007F)<<8)
#define MCF_LCDC_LPCR_ACDSEL	    (0x00008000)
#define MCF_LCDC_LPCR_REV_VS	    (0x00010000)
#define MCF_LCDC_LPCR_SWAP_SEL	    (0x00020000)
#define MCF_LCDC_LPCR_ENDSEL	    (0x00040000)
#define MCF_LCDC_LPCR_SCLKIDLE	    (0x00080000)
#define MCF_LCDC_LPCR_OEPOL	    (0x00100000)
#define MCF_LCDC_LPCR_CLKPOL	    (0x00200000)
#define MCF_LCDC_LPCR_LPPOL	    (0x00400000)
#define MCF_LCDC_LPCR_FLM	    (0x00800000)
#define MCF_LCDC_LPCR_PIXPOL	    (0x01000000)
#define MCF_LCDC_LPCR_BPIX(x)	    (((x)&0x00000007)<<25)
#define MCF_LCDC_LPCR_PBSIZ(x)	    (((x)&0x00000003)<<28)
#define MCF_LCDC_LPCR_COLOR	    (0x40000000)
#define MCF_LCDC_LPCR_TFT	    (0x80000000)
#define MCF_LCDC_LPCR_MODE_MONOCHROME	  (0x00000000)
#define MCF_LCDC_LPCR_MODE_CSTN	    (0x40000000)
#define MCF_LCDC_LPCR_MODE_TFT	    (0xC0000000)
#define MCF_LCDC_LPCR_PBSIZ_1	    (0x00000000)
#define MCF_LCDC_LPCR_PBSIZ_2	    (0x10000000)
#define MCF_LCDC_LPCR_PBSIZ_4	    (0x20000000)
#define MCF_LCDC_LPCR_PBSIZ_8	    (0x30000000)
#define MCF_LCDC_LPCR_BPIX_1bpp	    (0x00000000)
#define MCF_LCDC_LPCR_BPIX_2bpp	    (0x02000000)
#define MCF_LCDC_LPCR_BPIX_4bpp	    (0x04000000)
#define MCF_LCDC_LPCR_BPIX_8bpp	    (0x06000000)
#define MCF_LCDC_LPCR_BPIX_12bpp	  (0x08000000)
#define MCF_LCDC_LPCR_BPIX_16bpp	  (0x0A000000)
#define MCF_LCDC_LPCR_BPIX_18bpp	  (0x0C000000)

/* Bit definitions and macros for MCF_LCDC_LHCR */
#define MCF_LCDC_LHCR_H_WAIT_2(x)	  (((x)&0x000000FF)<<0)
#define MCF_LCDC_LHCR_H_WAIT_1(x)	  (((x)&0x000000FF)<<8)
#define MCF_LCDC_LHCR_H_WIDTH(x)	  (((x)&0x0000003F)<<26)

/* Bit definitions and macros for MCF_LCDC_LVCR */
#define MCF_LCDC_LVCR_V_WAIT_2(x)	  (((x)&0x000000FF)<<0)
#define MCF_LCDC_LVCR_V_WAIT_1(x)	  (((x)&0x000000FF)<<8)
#define MCF_LCDC_LVCR_V_WIDTH(x)	  (((x)&0x0000003F)<<26)

/* Bit definitions and macros for MCF_LCDC_LPOR */
#define MCF_LCDC_LPOR_POS(x)	    (((x)&0x0000001F)<<0)

/* Bit definitions and macros for MCF_LCDC_LPCCR */
#define MCF_LCDC_LPCCR_PW(x)	    (((x)&0x000000FF)<<0)
#define MCF_LCDC_LPCCR_CC_EN	    (0x00000100)
#define MCF_LCDC_LPCCR_SCR(x)	    (((x)&0x00000003)<<9)
#define MCF_LCDC_LPCCR_LDMSK	    (0x00008000)
#define MCF_LCDC_LPCCR_CLS_HI_WIDTH(x)	(((x)&0x000001FF)<<16)
#define MCF_LCDC_LPCCR_SCR_LINEPULSE	  (0x00000000)
#define MCF_LCDC_LPCCR_SCR_PIXELCLK	  (0x00002000)
#define MCF_LCDC_LPCCR_SCR_LCDCLOCK	  (0x00004000)

/* Bit definitions and macros for MCF_LCDC_LDCR */
#define MCF_LCDC_LDCR_TM(x)	    (((x)&0x0000001F)<<0)
#define MCF_LCDC_LDCR_HM(x)	    (((x)&0x0000001F)<<16)
#define MCF_LCDC_LDCR_BURST	    (0x80000000)

/* Bit definitions and macros for MCF_LCDC_LRMCR */
#define MCF_LCDC_LRMCR_SEL_REF	  (0x00000001)

/* Bit definitions and macros for MCF_LCDC_LICR */
#define MCF_LCDC_LICR_INTCON	    (0x00000001)
#define MCF_LCDC_LICR_INTSYN	    (0x00000004)
#define MCF_LCDC_LICR_GW_INT_CON    (0x00000010)

/* Bit definitions and macros for MCF_LCDC_LIER */
#define MCF_LCDC_LIER_BOF_EN	    (0x00000001)
#define MCF_LCDC_LIER_EOF_EN	    (0x00000002)
#define MCF_LCDC_LIER_ERR_RES_EN    (0x00000004)
#define MCF_LCDC_LIER_UDR_ERR_EN    (0x00000008)
#define MCF_LCDC_LIER_GW_BOF_EN	    (0x00000010)
#define MCF_LCDC_LIER_GW_EOF_EN	    (0x00000020)
#define MCF_LCDC_LIER_GW_ERR_RES_EN (0x00000040)
#define MCF_LCDC_LIER_GW_UDR_ERR_EN (0x00000080)

/* Bit definitions and macros for MCF_LCDC_LISR */
#define MCF_LCDC_LISR_BOF	    (0x00000001)
#define MCF_LCDC_LISR_EOF	    (0x00000002)
#define MCF_LCDC_LISR_ERR_RES	    (0x00000004)
#define MCF_LCDC_LISR_UDR_ERR	    (0x00000008)
#define MCF_LCDC_LISR_GW_BOF	    (0x00000010)
#define MCF_LCDC_LISR_GW_EOF	    (0x00000020)
#define MCF_LCDC_LISR_GW_ERR_RES    (0x00000040)
#define MCF_LCDC_LISR_GW_UDR_ERR    (0x00000080)

/* Bit definitions and macros for MCF_LCDC_LGWSAR */
#define MCF_LCDC_LGWSAR_GWSA(x)	  (((x)&0x3FFFFFFF)<<2)

/* Bit definitions and macros for MCF_LCDC_LGWSR */
#define MCF_LCDC_LGWSR_GWH(x)	    (((x)&0x000003FF)<<0)
#define MCF_LCDC_LGWSR_GWW(x)	    (((x)&0x0000003F)<<20)

/* Bit definitions and macros for MCF_LCDC_LGWVPWR */
#define MCF_LCDC_LGWVPWR_GWVPW(x)   (((x)&0x000003FF)<<0)

/* Bit definitions and macros for MCF_LCDC_LGWPOR */
#define MCF_LCDC_LGWPOR_GWPO(x)	    (((x)&0x0000001F)<<0)

/* Bit definitions and macros for MCF_LCDC_LGWPR */
#define MCF_LCDC_LGWPR_GWYP(x)	    (((x)&0x000003FF)<<0)
#define MCF_LCDC_LGWPR_GWXP(x)	    (((x)&0x000003FF)<<16)

/* Bit definitions and macros for MCF_LCDC_LGWCR */
#define MCF_LCDC_LGWCR_GWCKB(x)	    (((x)&0x0000003F)<<0)
#define MCF_LCDC_LGWCR_GWCKG(x)	    (((x)&0x0000003F)<<6)
#define MCF_LCDC_LGWCR_GWCKR(x)	    (((x)&0x0000003F)<<12)
#define MCF_LCDC_LGWCR_GW_RVS	    (0x00200000)
#define MCF_LCDC_LGWCR_GWE	    (0x00400000)
#define MCF_LCDC_LGWCR_GWCKE	    (0x00800000)
#define MCF_LCDC_LGWCR_GWAV(x)	    (((x)&0x000000FF)<<24)

/* Bit definitions and macros for MCF_LCDC_LGWDCR */
#define MCF_LCDC_LGWDCR_GWTM(x)	    (((x)&0x0000001F)<<0)
#define MCF_LCDC_LGWDCR_GWHM(x)	    (((x)&0x0000001F)<<16)
#define MCF_LCDC_LGWDCR_GWBT	    (0x80000000)

/* Bit definitions and macros for MCF_LCDC_BPLUT_BASE */
#define MCF_LCDC_BPLUT_BASE_BASE(x)	  (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF_LCDC_GWLUT_BASE */
#define MCF_LCDC_GWLUT_BASE_BASE(x)	  (((x)&0xFFFFFFFF)<<0)

/*
 *
 * FlexCAN Module (CAN) - Chapter 23
 *
 */

/* Register read/write macros */
#define MCF_CAN_CANMCR	            (*(volatile UINT32*)(0xFC020000))
#define MCF_CAN_CANCTRL	            (*(volatile UINT32*)(0xFC020004))
#define MCF_CAN_TIMER	            (*(volatile UINT32*)(0xFC020008))
#define MCF_CAN_RXGMASK	            (*(volatile UINT32*)(0xFC020010))
#define MCF_CAN_RX14MASK	    (*(volatile UINT32*)(0xFC020014))
#define MCF_CAN_RX15MASK	    (*(volatile UINT32*)(0xFC020018))
#define MCF_CAN_ERRCNT	            (*(volatile UINT32*)(0xFC02001C))
#define MCF_CAN_ERRSTAT	            (*(volatile UINT32*)(0xFC020020))
#define MCF_CAN_IMASK	            (*(volatile UINT32*)(0xFC020028))
#define MCF_CAN_IFLAG	            (*(volatile UINT32*)(0xFC020030))

/* Bit definitions and macros for MCF_CAN_CANMCR */
#define MCF_CAN_CANMCR_MAXMB(x)	     (((x)&0x0000000F)<<0)
#define MCF_CAN_CANMCR_LPMACK	     (0x00100000)
#define MCF_CAN_CANMCR_SUPV	     (0x00800000)
#define MCF_CAN_CANMCR_FRZACK	     (0x01000000)
#define MCF_CAN_CANMCR_SOFTRST	     (0x02000000)
#define MCF_CAN_CANMCR_NOTRDY	     (0x08000000)
#define MCF_CAN_CANMCR_HALT	     (0x10000000)
#define MCF_CAN_CANMCR_FRZ	     (0x40000000)
#define MCF_CAN_CANMCR_MDIS	     (0x80000000)

/* Bit definitions and macros for MCF_CAN_CANCTRL */
#define MCF_CAN_CANCTRL_PROPSEG(x)   (((x)&0x00000007)<<0)
#define MCF_CAN_CANCTRL_LOM	     (0x00000008)
#define MCF_CAN_CANCTRL_LBUF	     (0x00000010)
#define MCF_CAN_CANCTRL_TSYNC	     (0x00000020)
#define MCF_CAN_CANCTRL_BOFFREC	     (0x00000040)
#define MCF_CAN_CANCTRL_SAMP	     (0x00000080)
#define MCF_CAN_CANCTRL_LPB	     (0x00001000)
#define MCF_CAN_CANCTRL_CLKSRC	     (0x00002000)
#define MCF_CAN_CANCTRL_ERRMSK	     (0x00004000)
#define MCF_CAN_CANCTRL_BOFFMSK	     (0x00008000)
#define MCF_CAN_CANCTRL_PSEG2(x)     (((x)&0x00000007)<<16)
#define MCF_CAN_CANCTRL_PSEG1(x)     (((x)&0x00000007)<<19)
#define MCF_CAN_CANCTRL_RJW(x)	     (((x)&0x00000003)<<22)
#define MCF_CAN_CANCTRL_PRESDIV(x)   (((x)&0x000000FF)<<24)

/* Bit definitions and macros for MCF_CAN_TIMER */
#define MCF_CAN_TIMER_TIMER(x)	   (((x)&0x0000FFFF)<<0)

/* Bit definitions and macros for MCF_CAN_RXGMASK */
#define MCF_CAN_RXGMASK_MI(x)	     (((x)&0x1FFFFFFF)<<0)

/* Bit definitions and macros for MCF_CAN_RX14MASK */
#define MCF_CAN_RX14MASK_MI(x)	   (((x)&0x1FFFFFFF)<<0)

/* Bit definitions and macros for MCF_CAN_RX15MASK */
#define MCF_CAN_RX15MASK_MI(x)	   (((x)&0x1FFFFFFF)<<0)

/* Bit definitions and macros for MCF_CAN_ERRCNT */
#define MCF_CAN_ERRCNT_TXECTR(x)	   (((x)&0x000000FF)<<0)
#define MCF_CAN_ERRCNT_RXECTR(x)	   (((x)&0x000000FF)<<8)

/* Bit definitions and macros for MCF_CAN_ERRSTAT */
#define MCF_CAN_ERRSTAT_WAKINT	            (0x00000001)
#define MCF_CAN_ERRSTAT_ERRINT	            (0x00000002)
#define MCF_CAN_ERRSTAT_BOFFINT	            (0x00000004)
#define MCF_CAN_ERRSTAT_FLTCONF(x)	    (((x)&0x00000003)<<4)
#define MCF_CAN_ERRSTAT_TXRX	            (0x00000040)
#define MCF_CAN_ERRSTAT_IDLE	            (0x00000080)
#define MCF_CAN_ERRSTAT_RXWRN	            (0x00000100)
#define MCF_CAN_ERRSTAT_TXWRN	            (0x00000200)
#define MCF_CAN_ERRSTAT_STFERR	            (0x00000400)
#define MCF_CAN_ERRSTAT_FRMERR	            (0x00000800)
#define MCF_CAN_ERRSTAT_CRCERR	            (0x00001000)
#define MCF_CAN_ERRSTAT_ACKERR	            (0x00002000)
#define MCF_CAN_ERRSTAT_BITERR(x)	    (((x)&0x00000003)<<14)
#define MCF_CAN_ERRSTAT_FLTCONF_ACTIVE	    (0x00000000)
#define MCF_CAN_ERRSTAT_FLTCONF_PASSIVE	    (0x00000010)
#define MCF_CAN_ERRSTAT_FLTCONF_BUSOFF	    (0x00000020)

/* Bit definitions and macros for MCF_CAN_IMASK */
#define MCF_CAN_IMASK_BUF0M	     (0x00000001)
#define MCF_CAN_IMASK_BUF1M	     (0x00000002)
#define MCF_CAN_IMASK_BUF2M	     (0x00000004)
#define MCF_CAN_IMASK_BUF3M	     (0x00000008)
#define MCF_CAN_IMASK_BUF4M	     (0x00000010)
#define MCF_CAN_IMASK_BUF5M	     (0x00000020)
#define MCF_CAN_IMASK_BUF6M	     (0x00000040)
#define MCF_CAN_IMASK_BUF7M	     (0x00000080)
#define MCF_CAN_IMASK_BUF8M	     (0x00000100)
#define MCF_CAN_IMASK_BUF9M	     (0x00000200)
#define MCF_CAN_IMASK_BUF10M	     (0x00000400)
#define MCF_CAN_IMASK_BUF11M	     (0x00000800)
#define MCF_CAN_IMASK_BUF12M	     (0x00001000)
#define MCF_CAN_IMASK_BUF13M	     (0x00002000)
#define MCF_CAN_IMASK_BUF14M	     (0x00004000)
#define MCF_CAN_IMASK_BUF15M	     (0x00008000)
#define MCF_CAN_IMASK_BUF(x)	     (1<<x)

/* Bit definitions and macros for MCF_CAN_IFLAG */
#define MCF_CAN_IFLAG_BUF0I	     (0x00000001)
#define MCF_CAN_IFLAG_BUF1I	     (0x00000002)
#define MCF_CAN_IFLAG_BUF2I	     (0x00000004)
#define MCF_CAN_IFLAG_BUF3I	     (0x00000008)
#define MCF_CAN_IFLAG_BUF4I	     (0x00000010)
#define MCF_CAN_IFLAG_BUF5I	     (0x00000020)
#define MCF_CAN_IFLAG_BUF6I	     (0x00000040)
#define MCF_CAN_IFLAG_BUF7I	     (0x00000080)
#define MCF_CAN_IFLAG_BUF8I	     (0x00000100)
#define MCF_CAN_IFLAG_BUF9I	     (0x00000200)
#define MCF_CAN_IFLAG_BUF10I	     (0x00000400)
#define MCF_CAN_IFLAG_BUF11I	     (0x00000800)
#define MCF_CAN_IFLAG_BUF12I	     (0x00001000)
#define MCF_CAN_IFLAG_BUF13I	     (0x00002000)
#define MCF_CAN_IFLAG_BUF14I	     (0x00004000)
#define MCF_CAN_IFLAG_BUF15I	     (0x00008000)
#define MCF_CAN_IFLAG_BUF(x)	     (1<<x)

/*
 *
 * Synchronous Serial Interface (SSI) - Chapter 24
 *
 */

/* Register read/write macros */
#define MCF_SSI_TX0		(*(volatile UINT32*)(0xFC0BC000))
#define MCF_SSI_TX1		(*(volatile UINT32*)(0xFC0BC004))
#define MCF_SSI_RX0		(*(volatile UINT32*)(0xFC0BC008))
#define MCF_SSI_RX1		(*(volatile UINT32*)(0xFC0BC00C))
#define MCF_SSI_CR		(*(volatile UINT32*)(0xFC0BC010))
#define MCF_SSI_ISR		(*(volatile UINT32*)(0xFC0BC014))
#define MCF_SSI_IER		(*(volatile UINT32*)(0xFC0BC018))
#define MCF_SSI_TCR		(*(volatile UINT32*)(0xFC0BC01C))
#define MCF_SSI_RCR		(*(volatile UINT32*)(0xFC0BC020))
#define MCF_SSI_CCR		(*(volatile UINT32*)(0xFC0BC024))
#define MCF_SSI_FCSR		(*(volatile UINT32*)(0xFC0BC02C))
#define MCF_SSI_ACR		(*(volatile UINT32*)(0xFC0BC038))
#define MCF_SSI_ACADD		(*(volatile UINT32*)(0xFC0BC03C))
#define MCF_SSI_ACDAT		(*(volatile UINT32*)(0xFC0BC040))
#define MCF_SSI_ATAG		(*(volatile UINT32*)(0xFC0BC044))
#define MCF_SSI_TMASK		(*(volatile UINT32*)(0xFC0BC048))
#define MCF_SSI_RMASK		(*(volatile UINT32*)(0xFC0BC04C))

/* Bit definitions and macros for MCF_SSI_TX */
#define MCF_SSI_TX_SSI_TX(x)	      (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF_SSI_RX */
#define MCF_SSI_RX_SSI_RX(x)	      (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF_SSI_CR */
#define MCF_SSI_CR_SSI_EN	(0x00000001)
#define MCF_SSI_CR_TE		(0x00000002)
#define MCF_SSI_CR_RE		(0x00000004)
#define MCF_SSI_CR_NET	        (0x00000008)
#define MCF_SSI_CR_SYN	        (0x00000010)
#define MCF_SSI_CR_I2S(x)	(((x)&0x00000003)<<5)
#define MCF_SSI_CR_MCE	        (0x00000080)
#define MCF_SSI_CR_TCH	        (0x00000100)
#define MCF_SSI_CR_CIS	        (0x00000200)
#define MCF_SSI_CR_I2S_NORMAL	(0x00000000)
#define MCF_SSI_CR_I2S_MASTER	(0x00000020)
#define MCF_SSI_CR_I2S_SLAVE	(0x00000040)

/* Bit definitions and macros for MCF_SSI_ISR */
#define MCF_SSI_ISR_TFE0	(0x00000001)
#define MCF_SSI_ISR_TFE1	(0x00000002)
#define MCF_SSI_ISR_RFF0	(0x00000004)
#define MCF_SSI_ISR_RFF1	(0x00000008)
#define MCF_SSI_ISR_RLS         (0x00000010)
#define MCF_SSI_ISR_TLS         (0x00000020)
#define MCF_SSI_ISR_RFS         (0x00000040)
#define MCF_SSI_ISR_TFS         (0x00000080)
#define MCF_SSI_ISR_TUE0	(0x00000100)
#define MCF_SSI_ISR_TUE1	(0x00000200)
#define MCF_SSI_ISR_ROE0	(0x00000400)
#define MCF_SSI_ISR_ROE1	(0x00000800)
#define MCF_SSI_ISR_TDE0	(0x00001000)
#define MCF_SSI_ISR_TDE1	(0x00002000)
#define MCF_SSI_ISR_RDR0	(0x00004000)
#define MCF_SSI_ISR_RDR1	(0x00008000)
#define MCF_SSI_ISR_RXT         (0x00010000)
#define MCF_SSI_ISR_CMDDU	(0x00020000)
#define MCF_SSI_ISR_CMDAU	(0x00040000)

/* Bit definitions and macros for MCF_SSI_IER */
#define MCF_SSI_IER_TFE0	(0x00000001)
#define MCF_SSI_IER_TFE1	(0x00000002)
#define MCF_SSI_IER_RFF0	(0x00000004)
#define MCF_SSI_IER_RFF1	(0x00000008)
#define MCF_SSI_IER_RLS         (0x00000010)
#define MCF_SSI_IER_TLS         (0x00000020)
#define MCF_SSI_IER_RFS         (0x00000040)
#define MCF_SSI_IER_TFS         (0x00000080)
#define MCF_SSI_IER_TUE0	(0x00000100)
#define MCF_SSI_IER_TUE1	(0x00000200)
#define MCF_SSI_IER_ROE0	(0x00000400)
#define MCF_SSI_IER_ROE1	(0x00000800)
#define MCF_SSI_IER_TDE0	(0x00001000)
#define MCF_SSI_IER_TDE1	(0x00002000)
#define MCF_SSI_IER_RDR0	(0x00004000)
#define MCF_SSI_IER_RDR1	(0x00008000)
#define MCF_SSI_IER_RXT         (0x00010000)
#define MCF_SSI_IER_CMDU	(0x00020000)
#define MCF_SSI_IER_CMDAU	(0x00040000)
#define MCF_SSI_IER_TIE         (0x00080000)
#define MCF_SSI_IER_TDMAE	(0x00100000)
#define MCF_SSI_IER_RIE         (0x00200000)
#define MCF_SSI_IER_RDMAE	(0x00400000)

/* Bit definitions and macros for MCF_SSI_TCR */
#define MCF_SSI_TCR_TEFS	(0x00000001)
#define MCF_SSI_TCR_TFSL	(0x00000002)
#define MCF_SSI_TCR_TFSI	(0x00000004)
#define MCF_SSI_TCR_TSCKP	(0x00000008)
#define MCF_SSI_TCR_TSHFD	(0x00000010)
#define MCF_SSI_TCR_TXDIR	(0x00000020)
#define MCF_SSI_TCR_TFDIR	(0x00000040)
#define MCF_SSI_TCR_TFEN0	(0x00000080)
#define MCF_SSI_TCR_TFEN1	(0x00000100)
#define MCF_SSI_TCR_TXBIT0	(0x00000200)

/* Bit definitions and macros for MCF_SSI_RCR */
#define MCF_SSI_RCR_REFS	(0x00000001)
#define MCF_SSI_RCR_RFSL	(0x00000002)
#define MCF_SSI_RCR_RFSI	(0x00000004)
#define MCF_SSI_RCR_RSCKP	(0x00000008)
#define MCF_SSI_RCR_RSHFD	(0x00000010)
#define MCF_SSI_RCR_RFEN0	(0x00000080)
#define MCF_SSI_RCR_RFEN1	(0x00000100)
#define MCF_SSI_RCR_RXBIT0	(0x00000200)
#define MCF_SSI_RCR_RXEXT	(0x00000400)

/* Bit definitions and macros for MCF_SSI_CCR */
#define MCF_SSI_CCR_PM(x)	(((x)&0x000000FF)<<0)
#define MCF_SSI_CCR_DC(x)	(((x)&0x0000001F)<<8)
#define MCF_SSI_CCR_WL(x)	(((x)&0x0000000F)<<13)
#define MCF_SSI_CCR_PSR         (0x00020000)
#define MCF_SSI_CCR_DIV2	(0x00040000)

/* Bit definitions and macros for MCF_SSI_FCSR */
#define MCF_SSI_FCSR_TFWM0(x)	    (((x)&0x0000000F)<<0)
#define MCF_SSI_FCSR_RFWM0(x)	    (((x)&0x0000000F)<<4)
#define MCF_SSI_FCSR_TFCNT0(x)	    (((x)&0x0000000F)<<8)
#define MCF_SSI_FCSR_RFCNT0(x)	    (((x)&0x0000000F)<<12)
#define MCF_SSI_FCSR_TFWM1(x)	    (((x)&0x0000000F)<<16)
#define MCF_SSI_FCSR_RFWM1(x)	    (((x)&0x0000000F)<<20)
#define MCF_SSI_FCSR_TFCNT1(x)	    (((x)&0x0000000F)<<24)
#define MCF_SSI_FCSR_RFCNT1(x)	    (((x)&0x0000000F)<<28)

/* Bit definitions and macros for MCF_SSI_ACR */
#define MCF_SSI_ACR_AC97EN	(0x00000001)
#define MCF_SSI_ACR_FV	        (0x00000002)
#define MCF_SSI_ACR_TIF         (0x00000004)
#define MCF_SSI_ACR_RD	        (0x00000008)
#define MCF_SSI_ACR_WR	        (0x00000010)
#define MCF_SSI_ACR_FRDIV(x)	(((x)&0x0000003F)<<5)

/* Bit definitions and macros for MCF_SSI_ACADD */
#define MCF_SSI_ACADD_SSI_ACADD(x)  (((x)&0x0007FFFF)<<0)

/* Bit definitions and macros for MCF_SSI_ACDAT */
#define MCF_SSI_ACDAT_SSI_ACDAT(x)  (((x)&0x0007FFFF)<<0)

/* Bit definitions and macros for MCF_SSI_ATAG */
#define MCF_SSI_ATAG_DDI_ATAG(x)    (((x)&0x0000FFFF)<<0)

/* Bit definitions and macros for MCF_SSI_TMASK */
#define MCF_SSI_TMASK_SSI_TMASK(x)  (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF_SSI_RMASK */
#define MCF_SSI_RMASK_SSI_RMASK(x)  (((x)&0xFFFFFFFF)<<0)

/*
 *
 * Real-time Clock (RTC) - Chapter 25
 *
 */

/* Register read/write macros */
#define MCF_RTC_HOURMIN	 (*(volatile UINT32*)(0xFC0A8000))
#define MCF_RTC_SECONDS	 (*(volatile UINT32*)(0xFC0A8004))
#define MCF_RTC_ALRM_HM	 (*(volatile UINT32*)(0xFC0A8008))
#define MCF_RTC_ALRM_SEC (*(volatile UINT32*)(0xFC0A800C))
#define MCF_RTC_CR	 (*(volatile UINT32*)(0xFC0A8010))
#define MCF_RTC_ISR	 (*(volatile UINT32*)(0xFC0A8014))
#define MCF_RTC_IER	 (*(volatile UINT32*)(0xFC0A8018))
#define MCF_RTC_STPWCH	 (*(volatile UINT32*)(0xFC0A801C))
#define MCF_RTC_DAYS	 (*(volatile UINT32*)(0xFC0A8020))
#define MCF_RTC_ALRM_DAY (*(volatile UINT32*)(0xFC0A8024))

/* Bit definitions and macros for MCF_RTC_HOURMIN */
#define MCF_RTC_HOURMIN_MINUTES(x)   (((x)&0x0000003F)<<0)
#define MCF_RTC_HOURMIN_HOURS(x)     (((x)&0x0000001F)<<8)

/* Bit definitions and macros for MCF_RTC_SECONDS */
#define MCF_RTC_SECONDS_SECONDS(x)   (((x)&0x0000003F)<<0)

/* Bit definitions and macros for MCF_RTC_ALRM_HM */
#define MCF_RTC_ALRM_HM_MINUTES(x)   (((x)&0x0000003F)<<0)
#define MCF_RTC_ALRM_HM_HOURS(x)     (((x)&0x0000001F)<<8)

/* Bit definitions and macros for MCF_RTC_ALRM_SEC */
#define MCF_RTC_ALRM_SEC_SECONDS(x)  (((x)&0x0000003F)<<0)

/* Bit definitions and macros for MCF_RTC_CR */
#define MCF_RTC_CR_SWR	 (0x00000001)
#define MCF_RTC_CR_XTL(x)	 (((x)&0x00000003)<<5)
#define MCF_RTC_CR_EN		 (0x00000080)
#define MCF_RTC_CR_32768	 (0x0)
#define MCF_RTC_CR_32000	 (0x1)
#define MCF_RTC_CR_38400	 (0x2)

/* Bit definitions and macros for MCF_RTC_ISR */
#define MCF_RTC_ISR_SW	         (0x00000001)
#define MCF_RTC_ISR_MIN	         (0x00000002)
#define MCF_RTC_ISR_ALM	         (0x00000004)
#define MCF_RTC_ISR_DAY	         (0x00000008)
#define MCF_RTC_ISR_1HZ	         (0x00000010)
#define MCF_RTC_ISR_HR	         (0x00000020)
#define MCF_RTC_ISR_2HZ	         (0x00000080)
#define MCF_RTC_ISR_SAM0	 (0x00000100)
#define MCF_RTC_ISR_SAM1	 (0x00000200)
#define MCF_RTC_ISR_SAM2	 (0x00000400)
#define MCF_RTC_ISR_SAM3	 (0x00000800)
#define MCF_RTC_ISR_SAM4	 (0x00001000)
#define MCF_RTC_ISR_SAM5	 (0x00002000)
#define MCF_RTC_ISR_SAM6	 (0x00004000)
#define MCF_RTC_ISR_SAM7	 (0x00008000)

/* Bit definitions and macros for MCF_RTC_IER */
#define MCF_RTC_IER_SW	         (0x00000001)
#define MCF_RTC_IER_MIN	         (0x00000002)
#define MCF_RTC_IER_ALM	         (0x00000004)
#define MCF_RTC_IER_DAY	         (0x00000008)
#define MCF_RTC_IER_1HZ	         (0x00000010)
#define MCF_RTC_IER_HR	         (0x00000020)
#define MCF_RTC_IER_2HZ	         (0x00000080)
#define MCF_RTC_IER_SAM0	 (0x00000100)
#define MCF_RTC_IER_SAM1	 (0x00000200)
#define MCF_RTC_IER_SAM2	 (0x00000400)
#define MCF_RTC_IER_SAM3	 (0x00000800)
#define MCF_RTC_IER_SAM4	 (0x00001000)
#define MCF_RTC_IER_SAM5	 (0x00002000)
#define MCF_RTC_IER_SAM6	 (0x00004000)
#define MCF_RTC_IER_SAM7	 (0x00008000)

/* Bit definitions and macros for MCF_RTC_STPWCH */
#define MCF_RTC_STPWCH_CNT(x)	       (((x)&0x0000003F)<<0)

/* Bit definitions and macros for MCF_RTC_DAYS */
#define MCF_RTC_DAYS_DAYS(x)	       (((x)&0x0000FFFF)<<0)

/* Bit definitions and macros for MCF_RTC_ALRM_DAY */
#define MCF_RTC_ALRM_DAY_DAYS(x)     (((x)&0x0000FFFF)<<0)

/*
 *
 * Pulse Width Modulation (PWM) - Chapter 26
 *
 */

/* Register read/write macros */
#define MCF_PWM_PWME	     (*(volatile UINT8 *)(0xFC090020))
#define MCF_PWM_PWMPOL	     (*(volatile UINT8 *)(0xFC090021))
#define MCF_PWM_PWMCLK	     (*(volatile UINT8 *)(0xFC090022))
#define MCF_PWM_PWMPRCLK     (*(volatile UINT8 *)(0xFC090023))
#define MCF_PWM_PWMCAE	     (*(volatile UINT8 *)(0xFC090024))
#define MCF_PWM_PWMCTL	     (*(volatile UINT8 *)(0xFC090025))
#define MCF_PWM_PWMSCLA	     (*(volatile UINT8 *)(0xFC090028))
#define MCF_PWM_PWMSCLB	     (*(volatile UINT8 *)(0xFC090029))
#define MCF_PWM_PWMCNT0	     (*(volatile UINT8 *)(0xFC09002C))
#define MCF_PWM_PWMCNT1	     (*(volatile UINT8 *)(0xFC09002D))
#define MCF_PWM_PWMCNT2	     (*(volatile UINT8 *)(0xFC09002E))
#define MCF_PWM_PWMCNT3	     (*(volatile UINT8 *)(0xFC09002F))
#define MCF_PWM_PWMCNT4	     (*(volatile UINT8 *)(0xFC090030))
#define MCF_PWM_PWMCNT5	     (*(volatile UINT8 *)(0xFC090031))
#define MCF_PWM_PWMCNT6	     (*(volatile UINT8 *)(0xFC090032))
#define MCF_PWM_PWMCNT7	     (*(volatile UINT8 *)(0xFC090033))
#define MCF_PWM_PWMCNT(x)    (*(volatile UINT8 *)(0xFC09002C+((x)*0x001)))
#define MCF_PWM_PWMPER0	     (*(volatile UINT8 *)(0xFC090034))
#define MCF_PWM_PWMPER1	     (*(volatile UINT8 *)(0xFC090035))
#define MCF_PWM_PWMPER2	     (*(volatile UINT8 *)(0xFC090036))
#define MCF_PWM_PWMPER3	     (*(volatile UINT8 *)(0xFC090037))
#define MCF_PWM_PWMPER4	     (*(volatile UINT8 *)(0xFC090038))
#define MCF_PWM_PWMPER5	     (*(volatile UINT8 *)(0xFC090039))
#define MCF_PWM_PWMPER6	     (*(volatile UINT8 *)(0xFC09003A))
#define MCF_PWM_PWMPER7	     (*(volatile UINT8 *)(0xFC09003B))
#define MCF_PWM_PWMPER(x)    (*(volatile UINT8 *)(0xFC090034+((x)*0x001)))
#define MCF_PWM_PWMDTY0	     (*(volatile UINT8 *)(0xFC09003C))
#define MCF_PWM_PWMDTY1	     (*(volatile UINT8 *)(0xFC09003D))
#define MCF_PWM_PWMDTY2	     (*(volatile UINT8 *)(0xFC09003E))
#define MCF_PWM_PWMDTY3	     (*(volatile UINT8 *)(0xFC09003F))
#define MCF_PWM_PWMDTY4	     (*(volatile UINT8 *)(0xFC090040))
#define MCF_PWM_PWMDTY5	     (*(volatile UINT8 *)(0xFC090041))
#define MCF_PWM_PWMDTY6	     (*(volatile UINT8 *)(0xFC090042))
#define MCF_PWM_PWMDTY7	     (*(volatile UINT8 *)(0xFC090043))
#define MCF_PWM_PWMDTY(x)    (*(volatile UINT8 *)(0xFC09003C+((x)*0x001)))
#define MCF_PWM_PWMSDN	     (*(volatile UINT8 *)(0xFC090044))

/* Bit definitions and macros for MCF_PWM_PWME */
#define MCF_PWM_PWME_PWME0	     (0x01)
#define MCF_PWM_PWME_PWME1	     (0x02)
#define MCF_PWM_PWME_PWME2	     (0x04)
#define MCF_PWM_PWME_PWME3	     (0x08)
#define MCF_PWM_PWME_PWME4	     (0x10)
#define MCF_PWM_PWME_PWME5	     (0x20)
#define MCF_PWM_PWME_PWME6	     (0x40)
#define MCF_PWM_PWME_PWME7	     (0x80)

/* Bit definitions and macros for MCF_PWM_PWMPOL */
#define MCF_PWM_PWMPOL_PPOL0	     (0x01)
#define MCF_PWM_PWMPOL_PPOL1	     (0x02)
#define MCF_PWM_PWMPOL_PPOL2	     (0x04)
#define MCF_PWM_PWMPOL_PPOL3	     (0x08)
#define MCF_PWM_PWMPOL_PPOL4	     (0x10)
#define MCF_PWM_PWMPOL_PPOL5	     (0x20)
#define MCF_PWM_PWMPOL_PPOL6	     (0x40)
#define MCF_PWM_PWMPOL_PPOL7	     (0x80)

/* Bit definitions and macros for MCF_PWM_PWMCLK */
#define MCF_PWM_PWMCLK_PCLK0	     (0x01)
#define MCF_PWM_PWMCLK_PCLK1	     (0x02)
#define MCF_PWM_PWMCLK_PCLK2	     (0x04)
#define MCF_PWM_PWMCLK_PCLK3	     (0x08)
#define MCF_PWM_PWMCLK_PCLK4	     (0x10)
#define MCF_PWM_PWMCLK_PCLK5	     (0x20)
#define MCF_PWM_PWMCLK_PCLK6	     (0x40)
#define MCF_PWM_PWMCLK_PCLK7	     (0x80)

/* Bit definitions and macros for MCF_PWM_PWMPRCLK */
#define MCF_PWM_PWMPRCLK_PCKA(x)   (((x)&0x07)<<0)
#define MCF_PWM_PWMPRCLK_PCKB(x)   (((x)&0x07)<<4)

/* Bit definitions and macros for MCF_PWM_PWMCAE */
#define MCF_PWM_PWMCAE_CAE0	     (0x01)
#define MCF_PWM_PWMCAE_CAE1	     (0x02)
#define MCF_PWM_PWMCAE_CAE2	     (0x04)
#define MCF_PWM_PWMCAE_CAE3	     (0x08)
#define MCF_PWM_PWMCAE_CAE4	     (0x10)
#define MCF_PWM_PWMCAE_CAE5	     (0x20)
#define MCF_PWM_PWMCAE_CAE6	     (0x40)
#define MCF_PWM_PWMCAE_CAE7	     (0x80)

/* Bit definitions and macros for MCF_PWM_PWMCTL */
#define MCF_PWM_PWMCTL_PFRZ	     (0x04)
#define MCF_PWM_PWMCTL_PSWAI	     (0x08)
#define MCF_PWM_PWMCTL_CON01	     (0x10)
#define MCF_PWM_PWMCTL_CON23	     (0x20)
#define MCF_PWM_PWMCTL_CON45	     (0x40)
#define MCF_PWM_PWMCTL_CON67	     (0x80)

/* Bit definitions and macros for MCF_PWM_PWMSCLA */
#define MCF_PWM_PWMSCLA_SCALEA(x)  (((x)&0xFF)<<0)

/* Bit definitions and macros for MCF_PWM_PWMSCLB */
#define MCF_PWM_PWMSCLB_SCALEB(x)  (((x)&0xFF)<<0)

/* Bit definitions and macros for MCF_PWM_PWMCNT */
#define MCF_PWM_PWMCNT_COUNT(x)	   (((x)&0xFF)<<0)

/* Bit definitions and macros for MCF_PWM_PWMPER */
#define MCF_PWM_PWMPER_PERIOD(x)   (((x)&0xFF)<<0)

/* Bit definitions and macros for MCF_PWM_PWMDTY */
#define MCF_PWM_PWMDTY_DUTY(x)	   (((x)&0xFF)<<0)

/* Bit definitions and macros for MCF_PWM_PWMSDN */
#define MCF_PWM_PWMSDN_SDNEN	     (0x01)
#define MCF_PWM_PWMSDN_PWM7IL	     (0x02)
#define MCF_PWM_PWMSDN_PWM7IN	     (0x04)
#define MCF_PWM_PWMSDN_LVL	     (0x10)
#define MCF_PWM_PWMSDN_RESTART	   (0x20)
#define MCF_PWM_PWMSDN_IE    (0x40)
#define MCF_PWM_PWMSDN_IF    (0x80)

/*
 *
 * Watchdog Timer Modules (WTM) - Chapter 27
 *
 */

/* Register read/write macros */
#define MCF_WTM_WCR	 ((volatile UINT16*)(0xFC098000))
#define MCF_WTM_WMR	 ((volatile UINT16*)(0xFC098002))
#define MCF_WTM_WCNTR	 ((volatile UINT16*)(0xFC098004))
#define MCF_WTM_WSR	 ((volatile UINT16*)(0xFC098006))
#define MCF_WTM_WCREG	 0xFC098000

/* Bit definitions and macros for MCF_WTM_WCR */
#define MCF_WTM_WCR_EN	     (0x0001)
#define MCF_WTM_WCR_HALTED   (0x0002)
#define MCF_WTM_WCR_DOZE     (0x0004)
#define MCF_WTM_WCR_WAIT     (0x0008)

/* Bit definitions and macros for MCF_WTM_WMR */
#define MCF_WTM_WMR_WM(x)    (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF_WTM_WCNTR */
#define MCF_WTM_WCNTR_WC(x)  (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF_WTM_WSR */
#define MCF_WTM_WSR_WS(x)    (((x)&0xFFFF)<<0)

/*
 *
 * Programmable Interrupt Timer Modules (PIT) - Chapter 28
 *
 */

#define MCF_PIT0_BASE   (0xFC080000)
#define MCF_PIT1_BASE   (0xFC084000)
#define MCF_PIT2_BASE   (0xFC088000)
#define MCF_PIT3_BASE   (0xFC08C000)
    
#include <hwif/timer/mcfPit.h>

/*
 *
 * DMA Timers (DTIM) - Chapter 29
 *
 */

/* Register read/write macros */
#define MCF_DTIM0_DTMR	   (*(volatile UINT16*)(0xFC070000))
#define MCF_DTIM0_DTXMR	   (*(volatile UINT8 *)(0xFC070002))
#define MCF_DTIM0_DTER	   (*(volatile UINT8 *)(0xFC070003))
#define MCF_DTIM0_DTRR	   (*(volatile UINT32*)(0xFC070004))
#define MCF_DTIM0_DTCR	   (*(volatile UINT32*)(0xFC070008))
#define MCF_DTIM0_DTCN	   (*(volatile UINT32*)(0xFC07000C))
#define MCF_DTIM1_DTMR	   (*(volatile UINT16*)(0xFC074000))
#define MCF_DTIM1_DTXMR	   (*(volatile UINT8 *)(0xFC074002))
#define MCF_DTIM1_DTER	   (*(volatile UINT8 *)(0xFC074003))
#define MCF_DTIM1_DTRR	   (*(volatile UINT32*)(0xFC074004))
#define MCF_DTIM1_DTCR	   (*(volatile UINT32*)(0xFC074008))
#define MCF_DTIM1_DTCN	   (*(volatile UINT32*)(0xFC07400C))
#define MCF_DTIM2_DTMR	   (*(volatile UINT16*)(0xFC078000))
#define MCF_DTIM2_DTXMR	   (*(volatile UINT8 *)(0xFC078002))
#define MCF_DTIM2_DTER	   (*(volatile UINT8 *)(0xFC078003))
#define MCF_DTIM2_DTRR	   (*(volatile UINT32*)(0xFC078004))
#define MCF_DTIM2_DTCR	   (*(volatile UINT32*)(0xFC078008))
#define MCF_DTIM2_DTCN	   (*(volatile UINT32*)(0xFC07800C))
#define MCF_DTIM3_DTMR	   (*(volatile UINT16*)(0xFC07C000))
#define MCF_DTIM3_DTXMR	   (*(volatile UINT8 *)(0xFC07C002))
#define MCF_DTIM3_DTER	   (*(volatile UINT8 *)(0xFC07C003))
#define MCF_DTIM3_DTRR	   (*(volatile UINT32*)(0xFC07C004))
#define MCF_DTIM3_DTCR	   (*(volatile UINT32*)(0xFC07C008))
#define MCF_DTIM3_DTCN	   (*(volatile UINT32*)(0xFC07C00C))
#define MCF_DTIM_DTMR(x)   (*(volatile UINT16*)(0xFC070000+((x)*0x4000)))
#define MCF_DTIM_DTXMR(x)  (*(volatile UINT8 *)(0xFC070002+((x)*0x4000)))
#define MCF_DTIM_DTER(x)   (*(volatile UINT8 *)(0xFC070003+((x)*0x4000)))
#define MCF_DTIM_DTRR(x)   (*(volatile UINT32*)(0xFC070004+((x)*0x4000)))
#define MCF_DTIM_DTCR(x)   (*(volatile UINT32*)(0xFC070008+((x)*0x4000)))
#define MCF_DTIM_DTCN(x)   (*(volatile UINT32*)(0xFC07000C+((x)*0x4000)))

/* Bit definitions and macros for MCF_DTIM_DTMR */
#define MCF_DTIM_DTMR_RST	   (0x0001)
#define MCF_DTIM_DTMR_CLK(x)	   (((x)&0x0003)<<1)
#define MCF_DTIM_DTMR_FRR	   (0x0008)
#define MCF_DTIM_DTMR_ORRI	   (0x0010)
#define MCF_DTIM_DTMR_OM	   (0x0020)
#define MCF_DTIM_DTMR_CE(x)	   (((x)&0x0003)<<6)
#define MCF_DTIM_DTMR_PS(x)	   (((x)&0x00FF)<<8)
#define MCF_DTIM_DTMR_CE_ANY	   (0x00C0)
#define MCF_DTIM_DTMR_CE_FALL	   (0x0080)
#define MCF_DTIM_DTMR_CE_RISE	   (0x0040)
#define MCF_DTIM_DTMR_CE_NONE	   (0x0000)
#define MCF_DTIM_DTMR_CLK_DTIN	   (0x0006)
#define MCF_DTIM_DTMR_CLK_DIV16	   (0x0004)
#define MCF_DTIM_DTMR_CLK_DIV1	   (0x0002)
#define MCF_DTIM_DTMR_CLK_STOP	   (0x0000)

/* Bit definitions and macros for MCF_DTIM_DTXMR */
#define MCF_DTIM_DTXMR_MODE16	   (0x01)
#define MCF_DTIM_DTXMR_DMAEN	   (0x80)

/* Bit definitions and macros for MCF_DTIM_DTER */
#define MCF_DTIM_DTER_CAP	   (0x01)
#define MCF_DTIM_DTER_REF	   (0x02)

/* Bit definitions and macros for MCF_DTIM_DTRR */
#define MCF_DTIM_DTRR_REF(x)	   (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF_DTIM_DTCR */
#define MCF_DTIM_DTCR_CAP(x)	   (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF_DTIM_DTCN */
#define MCF_DTIM_DTCN_CNT(x)	   (((x)&0xFFFFFFFF)<<0)

/*
 *
 * Queued Serial Peripheral Interface (QSPI) - Chapter 30
 *
 */

#define MCF_QSPI_BASE (0xFC05C000)

#include <hwif/spi/mcfQspi.h>

/*
 *
 * Universal Asynchronous Receiver Transmitter (UART) - Chapter 31
 *
 */

#define MCF_UART_BASE0      0xFC060000
#define MCF_UART_BASE1      0xFC064000
#define MCF_UART_BASE2      0xFC068000

#include <hwif/sio/mcfUart.h>

/*
 *
 * I2C Module (I2C) - Chapter 32
 *
 */

#define MCF_I2C_BASE      (0xFC058000)
  
#include <hwif/i2c/mcfI2c.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 *
 * Message Digest Hardware Accelerator (MDHA) - Chapter 33
 *
 */

/* Register read/write macros */
#define MCF_MDHA_MDMR		(*(volatile UINT32*)(0xEC080000))
#define MCF_MDHA_MDCR		(*(volatile UINT32*)(0xEC080004))
#define MCF_MDHA_MDCMR	        (*(volatile UINT32*)(0xEC080008))
#define MCF_MDHA_MDSR		(*(volatile UINT32*)(0xEC08000C))
#define MCF_MDHA_MDISR	        (*(volatile UINT32*)(0xEC080010))
#define MCF_MDHA_MDIMR	        (*(volatile UINT32*)(0xEC080014))
#define MCF_MDHA_MDDSR	        (*(volatile UINT32*)(0xEC08001C))
#define MCF_MDHA_MDIN		(*(volatile UINT32*)(0xEC080020))
#define MCF_MDHA_MDA0		(*(volatile UINT32*)(0xEC080030))
#define MCF_MDHA_MDB0		(*(volatile UINT32*)(0xEC080034))
#define MCF_MDHA_MDC0		(*(volatile UINT32*)(0xEC080038))
#define MCF_MDHA_MDD0		(*(volatile UINT32*)(0xEC08003C))
#define MCF_MDHA_MDE0		(*(volatile UINT32*)(0xEC080040))
#define MCF_MDHA_MDMDS	        (*(volatile UINT32*)(0xEC080044))
#define MCF_MDHA_MDA1		(*(volatile UINT32*)(0xEC080070))
#define MCF_MDHA_MDB1		(*(volatile UINT32*)(0xEC080074))
#define MCF_MDHA_MDC1		(*(volatile UINT32*)(0xEC080078))
#define MCF_MDHA_MDD1		(*(volatile UINT32*)(0xEC08007C))
#define MCF_MDHA_MDE1		(*(volatile UINT32*)(0xEC080080))

/* Bit definitions and macros for MCF_MDHA_MDMR */
#define MCF_MDHA_MDMR_ALG	(0x00000001)
#define MCF_MDHA_MDMR_PDATA     (0x00000004)
#define MCF_MDHA_MDMR_MAC(x)    (((x)&0x00000003)<<3)
#define MCF_MDHA_MDMR_INIT	(0x00000020)
#define MCF_MDHA_MDMR_IPAD	(0x00000040)
#define MCF_MDHA_MDMR_OPAD	(0x00000080)
#define MCF_MDHA_MDMR_SWAP	(0x00000100)
#define MCF_MDHA_MDMR_MACFULL	(0x00000200)
#define MCF_MDHA_MDMR_SSL	(0x00000400)

/* Bit definitions and macros for MCF_MDHA_MDCR */
#define MCF_MDHA_MDCR_IE	(0x00000001)
#define MCF_MDHA_MDCR_DMA	(0x00000002)
#define MCF_MDHA_MDCR_ENDIAN	(0x00000004)
#define MCF_MDHA_MDCR_DMAL(x)	(((x)&0x0000001F)<<16)

/* Bit definitions and macros for MCF_MDHA_MDCMR */
#define MCF_MDHA_MDCMR_SWR	(0x00000001)
#define MCF_MDHA_MDCMR_RI	(0x00000002)
#define MCF_MDHA_MDCMR_CI	(0x00000004)
#define MCF_MDHA_MDCMR_GO	(0x00000008)

/* Bit definitions and macros for MCF_MDHA_MDSR */
#define MCF_MDHA_MDSR_INT	(0x00000001)
#define MCF_MDHA_MDSR_DONE	(0x00000002)
#define MCF_MDHA_MDSR_ERR	(0x00000004)
#define MCF_MDHA_MDSR_RD	(0x00000008)
#define MCF_MDHA_MDSR_BUSY	(0x00000010)
#define MCF_MDHA_MDSR_END	(0x00000020)
#define MCF_MDHA_MDSR_HSH	(0x00000040)
#define MCF_MDHA_MDSR_GNW	(0x00000080)
#define MCF_MDHA_MDSR_FS(x)	(((x)&0x00000007)<<8)
#define MCF_MDHA_MDSR_APD(x)	(((x)&0x00000007)<<13)
#define MCF_MDHA_MDSR_IFL(x)	(((x)&0x000000FF)<<16)

/* Bit definitions and macros for MCF_MDHA_MDISR */
#define MCF_MDHA_MDISR_IFO	(0x00000001)
#define MCF_MDHA_MDISR_NON	(0x00000004)
#define MCF_MDHA_MDISR_IME	(0x00000010)
#define MCF_MDHA_MDISR_IDS	(0x00000020)
#define MCF_MDHA_MDISR_RMDP	(0x00000080)
#define MCF_MDHA_MDISR_ERE	(0x00000100)
#define MCF_MDHA_MDISR_GTDS	(0x00000200)

/* Bit definitions and macros for MCF_MDHA_MDIMR */
#define MCF_MDHA_MDIMR_IFO	(0x00000001)
#define MCF_MDHA_MDIMR_NON	(0x00000004)
#define MCF_MDHA_MDIMR_IME	(0x00000010)
#define MCF_MDHA_MDIMR_IDS	(0x00000020)
#define MCF_MDHA_MDIMR_RMDP	(0x00000080)
#define MCF_MDHA_MDIMR_ERE	(0x00000100)
#define MCF_MDHA_MDIMR_GTDS	(0x00000200)

/* Bit definitions and macros for MCF_MDHA_MDDSR */
#define MCF_MDHA_MDDSR_DATASIZE(x)  (((x)&0x1FFFFFFF)<<0)

/* Bit definitions and macros for MCF_MDHA_MDIN */
#define MCF_MDHA_MDIN_DATAIN(x)	    (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF_MDHA_MDA0 */
#define MCF_MDHA_MDA0_DATA(x)	      (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF_MDHA_MDB0 */
#define MCF_MDHA_MDB0_DATA(x)	      (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF_MDHA_MDC0 */
#define MCF_MDHA_MDC0_DATA(x)	      (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF_MDHA_MDD0 */
#define MCF_MDHA_MDD0_DATA(x)	      (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF_MDHA_MDE0 */
#define MCF_MDHA_MDE0_DATA(x)	      (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF_MDHA_MDMDS */
#define MCF_MDHA_MDMDS_DATASIZE(x)  (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF_MDHA_MDA1 */
#define MCF_MDHA_MDA1_DATA(x)	      (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF_MDHA_MDB1 */
#define MCF_MDHA_MDB1_DATA(x)	      (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF_MDHA_MDC1 */
#define MCF_MDHA_MDC1_DATA(x)	      (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF_MDHA_MDD1 */
#define MCF_MDHA_MDD1_DATA(x)	      (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF_MDHA_MDE1 */
#define MCF_MDHA_MDE1_DATA(x)	      (((x)&0xFFFFFFFF)<<0)

/*
 *
 * Random Number Generator (RNG) - Chapter 34
 *
 */

/* Register read/write macros */
#define MCF_RNG_RNGCR	      (*(volatile UINT32*)(0xEC088000))
#define MCF_RNG_RNGSR	      (*(volatile UINT32*)(0xEC088004))
#define MCF_RNG_RNGER	      (*(volatile UINT32*)(0xEC088008))
#define MCF_RNG_RNGOUT	    (*(volatile UINT32*)(0xEC08800C))

/* Bit definitions and macros for MCF_RNG_RNGCR */
#define MCF_RNG_RNGCR_GO    (0x00000001)
#define MCF_RNG_RNGCR_HA    (0x00000002)
#define MCF_RNG_RNGCR_IM    (0x00000004)
#define MCF_RNG_RNGCR_CI    (0x00000008)

/* Bit definitions and macros for MCF_RNG_RNGSR */
#define MCF_RNG_RNGSR_SV            (0x00000001)
#define MCF_RNG_RNGSR_LRS	    (0x00000002)
#define MCF_RNG_RNGSR_FUF	    (0x00000004)
#define MCF_RNG_RNGSR_EI            (0x00000008)
#define MCF_RNG_RNGSR_OFL(x)	    (((x)&0x000000FF)<<8)
#define MCF_RNG_RNGSR_OFS(x)	    (((x)&0x000000FF)<<16)

/* Bit definitions and macros for MCF_RNG_RNGER */
#define MCF_RNG_RNGER_ENTROPY(x)  (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF_RNG_RNGOUT */
#define MCF_RNG_RNGOUT_OUTPUT(x)  (((x)&0xFFFFFFFF)<<0)

/*
 *
 * Symmetric Key Hardware Accelerator (SKHA) - Chapter 35
 *
 */

/* Register read/write macros */
#define MCF_SKHA_SKMR		(*(volatile UINT32*)(0xEC084000))
#define MCF_SKHA_SKCR		(*(volatile UINT32*)(0xEC084004))
#define MCF_SKHA_SKCMR	        (*(volatile UINT32*)(0xEC084008))
#define MCF_SKHA_SKSR		(*(volatile UINT32*)(0xEC08400C))
#define MCF_SKHA_SKISR	        (*(volatile UINT32*)(0xEC084010))
#define MCF_SKHA_SKIMR	        (*(volatile UINT32*)(0xEC084014))
#define MCF_SKHA_SKKSR	        (*(volatile UINT32*)(0xEC084018))
#define MCF_SKHA_SKDSR	        (*(volatile UINT32*)(0xEC08401C))
#define MCF_SKHA_SKIN		(*(volatile UINT32*)(0xEC084020))
#define MCF_SKHA_SKOUT	        (*(volatile UINT32*)(0xEC084024))
#define MCF_SKHA_SKK0		(*(volatile UINT32*)(0xEC084030))
#define MCF_SKHA_SKK1		(*(volatile UINT32*)(0xEC084034))
#define MCF_SKHA_SKK2		(*(volatile UINT32*)(0xEC084038))
#define MCF_SKHA_SKK3		(*(volatile UINT32*)(0xEC08403C))
#define MCF_SKHA_SKK4		(*(volatile UINT32*)(0xEC084040))
#define MCF_SKHA_SKK5		(*(volatile UINT32*)(0xEC084044))
#define MCF_SKHA_SKK(x)         (*(volatile UINT32*)(0xEC084030+((x)*0x004)))
#define MCF_SKHA_SKC0		(*(volatile UINT32*)(0xEC084070))
#define MCF_SKHA_SKC1		(*(volatile UINT32*)(0xEC084074))
#define MCF_SKHA_SKC2		(*(volatile UINT32*)(0xEC084078))
#define MCF_SKHA_SKC3		(*(volatile UINT32*)(0xEC08407C))
#define MCF_SKHA_SKC4		(*(volatile UINT32*)(0xEC084080))
#define MCF_SKHA_SKC5		(*(volatile UINT32*)(0xEC084084))
#define MCF_SKHA_SKC6		(*(volatile UINT32*)(0xEC084088))
#define MCF_SKHA_SKC7		(*(volatile UINT32*)(0xEC08408C))
#define MCF_SKHA_SKC8		(*(volatile UINT32*)(0xEC084090))
#define MCF_SKHA_SKC9		(*(volatile UINT32*)(0xEC084094))
#define MCF_SKHA_SKC10	        (*(volatile UINT32*)(0xEC084098))
#define MCF_SKHA_SKC11	        (*(volatile UINT32*)(0xEC08409C))
#define MCF_SKHA_SKC(x)         (*(volatile UINT32*)(0xEC084070+((x)*0x004)))

/* Bit definitions and macros for MCF_SKHA_SKMR */
#define MCF_SKHA_SKMR_ALG(x)	      (((x)&0x00000003)<<0)
#define MCF_SKHA_SKMR_DIR	      (0x00000004)
#define MCF_SKHA_SKMR_CM(x)	      (((x)&0x00000003)<<3)
#define MCF_SKHA_SKMR_DKP	      (0x00000100)
#define MCF_SKHA_SKMR_CTRM(x)	      (((x)&0x0000000F)<<9)
#define MCF_SKHA_SKMR_CM_ECB	      (0x00000000)
#define MCF_SKHA_SKMR_CM_CBC	      (0x00000008)
#define MCF_SKHA_SKMR_CM_CTR	      (0x00000018)
#define MCF_SKHA_SKMR_DIR_DEC	      (0x00000000)
#define MCF_SKHA_SKMR_DIR_ENC	      (0x00000004)
#define MCF_SKHA_SKMR_ALG_AES	      (0x00000000)
#define MCF_SKHA_SKMR_ALG_DES	      (0x00000001)
#define MCF_SKHA_SKMR_ALG_TDES	      (0x00000002)

/* Bit definitions and macros for MCF_SKHA_SKCR */
#define MCF_SKHA_SKCR_IE	    (0x00000001)
#define MCF_SKHA_SKCR_IDMA	    (0x00000002)
#define MCF_SKHA_SKCR_ODMA	    (0x00000004)
#define MCF_SKHA_SKCR_ENDIAN	    (0x00000008)
#define MCF_SKHA_SKCR_IDMAL(x)	    (((x)&0x0000003F)<<16)
#define MCF_SKHA_SKCR_ODMAL(x)	    (((x)&0x0000003F)<<24)

/* Bit definitions and macros for MCF_SKHA_SKCMR */
#define MCF_SKHA_SKCMR_SWR	(0x00000001)
#define MCF_SKHA_SKCMR_RI	(0x00000002)
#define MCF_SKHA_SKCMR_CI	(0x00000004)
#define MCF_SKHA_SKCMR_GO	(0x00000008)

/* Bit definitions and macros for MCF_SKHA_SKSR */
#define MCF_SKHA_SKSR_INT	(0x00000001)
#define MCF_SKHA_SKSR_DONE	(0x00000002)
#define MCF_SKHA_SKSR_ERR	(0x00000004)
#define MCF_SKHA_SKSR_RD	(0x00000008)
#define MCF_SKHA_SKSR_BUSY	(0x00000010)
#define MCF_SKHA_SKSR_IFL(x)	(((x)&0x000000FF)<<16)
#define MCF_SKHA_SKSR_OFL(x)	(((x)&0x000000FF)<<24)

/* Bit definitions and macros for MCF_SKHA_SKISR */
#define MCF_SKHA_SKISR_IFO	(0x00000001)
#define MCF_SKHA_SKISR_OFU	(0x00000002)
#define MCF_SKHA_SKISR_NEIF	(0x00000004)
#define MCF_SKHA_SKISR_NEOF	(0x00000008)
#define MCF_SKHA_SKISR_IME	(0x00000010)
#define MCF_SKHA_SKISR_DSE	(0x00000020)
#define MCF_SKHA_SKISR_KSE	(0x00000040)
#define MCF_SKHA_SKISR_RMDP	(0x00000080)
#define MCF_SKHA_SKISR_ERE	(0x00000100)
#define MCF_SKHA_SKISR_KPE	(0x00000200)
#define MCF_SKHA_SKISR_KRE	(0x00000400)
#define MCF_SKHA_SKISR_DRL	(0x00000800)

/* Bit definitions and macros for MCF_SKHA_SKIMR */
#define MCF_SKHA_SKIMR_IFO	(0x00000001)
#define MCF_SKHA_SKIMR_OFU	(0x00000002)
#define MCF_SKHA_SKIMR_NEIF	(0x00000004)
#define MCF_SKHA_SKIMR_NEOF	(0x00000008)
#define MCF_SKHA_SKIMR_IME	(0x00000010)
#define MCF_SKHA_SKIMR_DSE	(0x00000020)
#define MCF_SKHA_SKIMR_KSE	(0x00000040)
#define MCF_SKHA_SKIMR_RMDP	(0x00000080)
#define MCF_SKHA_SKIMR_ERE	(0x00000100)
#define MCF_SKHA_SKIMR_KPE	(0x00000200)
#define MCF_SKHA_SKIMR_KRE	(0x00000400)
#define MCF_SKHA_SKIMR_DRL	(0x00000800)

/* Bit definitions and macros for MCF_SKHA_SKKSR */
#define MCF_SKHA_SKKSR_KEYSIZE(x)   (((x)&0x0000003F)<<0)

/* Bit definitions and macros for MCF_SKHA_SKDSR */
#define MCF_SKHA_SKDSR_DATASIZE(x)  (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF_SKHA_SKIN */
#define MCF_SKHA_SKIN_DATAIN(x)	    (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF_SKHA_SKOUT */
#define MCF_SKHA_SKOUT_DATAOUT(x)   (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF_SKHA_SKK */
#define MCF_SKHA_SKK_KEY(x)	      (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF_SKHA_SKC */
#define MCF_SKHA_SKC_CONTEXT(x)	    (((x)&0xFFFFFFFF)<<0)


#ifdef __cplusplus
}
#endif

#endif /* __INCMCF5329h */

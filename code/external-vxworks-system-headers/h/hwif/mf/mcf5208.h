/* mcf5208.h - Freescale MCF5208 CPU control registers */

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
01f,29apr10,pad  Moved extern C statement after include statements.
01e,12mar08,rec  move multifunction header files to h/hwif/..
01d,06feb08,rec  change CAST_M5208 macros to more generic type
01c,10dec07,rec  vxBus support
01b,20sep07,rec  Created for vxWorks 6.6
01a,19jun07,rec	 initial version created for vxWorks 6.4
*/

/*
 * This file contains I/O addresses and related constants for the M5208.
 * Each section is referenced to the appropriate chapter in "MCF5208 Reference
 * Manual".
 */

#ifndef __INCMCF5208h
#define __INCMCF5208h

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
#define M5208_SRAM_SIZE		16384		/* size of SRAM */

/*
 *
 * Cache - Chapter 5
 *
 */
 
/* register definitions for CACR */

#define	MCF_CACR_ENABLE	    0x80000000	/* enable cache */
#define MCF_CACR_CPDI	    0x10000000	/* disable CPUSHL invalidation (instr)*/
#define MCF_CACR_CFRZ	    0x08000000	/* cache freeze */
#define MCF_CACR_CINV	    0x01000000	/* cache invalidate all */
#define MCF_CACR_DISI	    0x00800000	/* disable instruction caching */
#define MCF_CACR_DISD	    0x00400000	/* disable data caching */
#define MCF_CACR_INVI	    0x00200000	/* CINV instruction cache only */
#define MCF_CACR_INVD	    0x00100000	/* CINV data cache only */
#define MCF_CACR_CEIB	    0x00000400	/* Cache enable noncache instr burst */
#define MCF_CACR_DCM	    0x00000200	/* default cache mode disabled */
#define MCF_CACR_DBWE	    0x00000100	/* default buffer write enabled */
#define MCF_CACR_DBP	    0x00000020	/* default write protect */
#define MCF_CACR_EUSP	    0x00000010	/* enable user stack pointer */
#define MCF_CACR_CLNF1	    0x00000002	/* noncache instruction bursting -1 */
#define MCF_CACR_CLNF0	    0x00000001	/* noncache instruction bursting -2 */

/* register definitions for ACR (that differ from cacheColdfireLib.h) */

#define MCF_ACR_CM_DIS  0x00000040	/* Cache disabled */
#define MCF_ACR_CM_BWE	0x00000020	/* Buffer write enable */

#define MCF_DATA_CACHE_SIZE		0x1000  /* 4k */
#define MCF_INSTRUCTION_CACHE_SIZE	0x1000  /* 4k */
#define MCF_LINE_COUNT                  256

/*
 *
 * Phase Locked Loop (PLL) - Chapter 7
 *
 */

/* Register read/write macros */
#define MCF_PLL_PODR	      (CAST_MCF_VOL(UINT8)(0xFC090000))
#define MCF_PLL_PLLCR	      (CAST_MCF_VOL(UINT8)(0xFC090002))
#define MCF_PLL_PMDR	      (CAST_MCF_VOL(UINT8)(0xFC090004))
#define MCF_PLL_PFDR	      0xFC090006

/* Bit definitions and macros for MCF_PLL_PODR */
#define MCF_PLL_PODR_BUSDIV(x)    (((x)&0x0F)<<0)
#define MCF_PLL_PODR_CPUDIV(x)    (((x)&0x0F)<<4)

/* Bit definitions and macros for MCF_PLL_PLLCR */
#define MCF_PLL_PLLCR_DITHDEV(x)  (((x)&0x07)<<0)
#define MCF_PLL_PLLCR_DITHEN	    (0x80)

/* Bit definitions and macros for MCF_PLL_PMDR */
#define MCF_PLL_PMDR_MODDIV(x)    (((x)&0xFF)<<0)

/* Bit definitions and macros for MCF_PLL_PFDR */
#define MCF_PLL_PFDR_MFD(x)	    (((x)&0xFF)<<0)

/*
 *
 * Power Management Module (PMM) - Chapter 8
 *
 */

/* Register read/write macros */
#define MCF_PMM_WCR	      (CAST_MCF_VOLPTR( UINT8 )(0xFC040013))
#define MCF_PMM_PPMSR0	      (CAST_MCF_VOLPTR( UINT8 )(0xFC04002C))
#define MCF_PMM_PPMSR1	      (CAST_MCF_VOLPTR( UINT8 )(0xFC04002E))
#define MCF_PMM_PPMCR0	      (CAST_MCF_VOLPTR( UINT8 )(0xFC04002D))
#define MCF_PMM_PPMCR1	      (CAST_MCF_VOLPTR( UINT8 )(0xFC04002F))
#define MCF_PMM_PPMHR0	      (CAST_MCF_VOLPTR( UINT32 )(0xFC040030))
#define MCF_PMM_PPMHR1	      (CAST_MCF_VOLPTR( UINT32 )(0xFC040038))
#define MCF_PMM_LPCR	      (CAST_MCF_VOLPTR( UINT8 )(0xFC0A0007))
#define MCF_PMM_MISCCR        (CAST_MCF_VOLPTR( UINT8 )(0xFC0A0010))

/* Bit definitions and macros for MCF_PMM_WCR */
#define MCF_PMM_WCR_PRILVL(x)		    (((x)&0x07)<<0)
#define MCF_PMM_WCR_ENBWCR	      (0x80)

/* Bit definitions and macros for MCF_PMM_PPMSR */
#define MCF_PMM_PPMSR_SMCD(x)       (((x)&0x3F)<<0)
#define MCF_PMM_PPMSR_SAMCD	      (0x40)

/* Bit definitions and macros for MCF_PMM_PPMCR */
#define MCF_PMM_PPMCR_CMCD(x)	      (((x)&0x3F)<<0)
#define MCF_PMM_PPMCR_CAMCD	      (0x40)

/* Bit definitions and macros for MCF_PMM_PPMHR0 */
#define MCF_PMM_PPMHR0_CD32	      (0x00000001)
#define MCF_PMM_PPMHR0_CD33	      (0x00000002)
#define MCF_PMM_PPMHR0_CD34	      (0x00000004)
#define MCF_PMM_PPMHR0_CD35	      (0x00000008)
#define MCF_PMM_PPMHR0_CD36	      (0x00000010)
#define MCF_PMM_PPMHR0_CD40	      (0x00000100)
#define MCF_PMM_PPMHR0_CD41	      (0x00000200)
#define MCF_PMM_PPMHR0_CD42	      (0x00000400)

/* Bit definitions and macros for MCF_PMM_PPMLR0 */
#define MCF_PMM_PPMLR0_CD2	      (0x00000004)
#define MCF_PMM_PPMLR0_CD12	      (0x00001000)
#define MCF_PMM_PPMLR0_CD17	      (0x00020000)
#define MCF_PMM_PPMLR0_CD18	      (0x00040000)
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
#define MCF_PMM_LPCR_STPMD_SYS_DISABLED	        (0x00)
#define MCF_PMM_LPCR_STPMD_SYS_BUSCLK_DISABLED  (0x04)
#define MCF_PMM_LPCR_STPMD_ONLY_OSC_ENABLED	(0x08)
#define MCF_PMM_LPCR_STPMD_ALL_DISABLED	        (0x0C)

/* Bit definitions and macros for MCF_PMM_MISCCR */
#define MCF_PMM_MISCCR_LPDDIV(x)                (((x)&0x000F)<<0)
#define MCF_PMM_MISCCR_LIMP                     (0x1000)
#define MCF_PMM_MISCCR_PLL_LOCK                 (0x2000)

/*
 *
 * Chip Configuration Module (CCM) - Chapter 9
 *
 */

/* Register read/write macros */
#define MCF_CCM_CCR	      (CAST_MCF_VOL(UINT16)(0xFC0A0004))
#define MCF_CCM_RCON	      (CAST_MCF_VOL(UINT16)(0xFC0A0008))
#define MCF_CCM_CIR	      (CAST_MCF_VOL(UINT16)(0xFC0A000A))

/* Bit definitions and macros for MCF_CCM_CCR */
#define MCF_CCM_CCR_RESERVED	    (0x0001)
#define MCF_CCM_CCR_PLL_MODE	    (0x0003)
#define MCF_CCM_CCR_OSC_MODE	    (0x0005)
#define MCF_CCM_CCR_BOOTPS(x)	    (((x)&0x0003)<<3|0x0001)
#define MCF_CCM_CCR_LOAD            (0x0021)
#define MCF_CCM_CCR_LIMP            (0x0041)
#define MCF_CCM_CCR_OSC_FREQ        (0x0081)
#define MCF_CCM_CCR_CSC   	    (0x0201)

/* Bit definitions and macros for MCF_CCM_RCON */
#define MCF_CCM_RCON_RESERVED	    (0x0001)
#define MCF_CCM_RCON_PLL_MODE	    (0x0003)
#define MCF_CCM_RCON_OSC_MODE	    (0x0005)
#define MCF_CCM_RCON_BOOTPS(x)      (((x)&0x0003)<<3|0x0001)
#define MCF_CCM_RCON_LOAD	    (0x0021)
#define MCF_CCM_RCON_LIMP	    (0x0041)
#define MCF_CCM_RCON_OSC_FREQ       (0x0081)
#define MCF_CCM_RCON_CSC   	    (0x0201)

/* Bit definitions and macros for MCF_CCM_CIR */
#define MCF_CCM_CIR_PRN(x)	    (((x)&0x003F)<<0)
#define MCF_CCM_CIR_PIN(x)	    (((x)&0x03FF)<<6)

/*
 *
 * Reset Controller Module (RCM) - Chapter 10
 *
 */

/* Register read/write macros */
#define MCF_RCM_RCR	   (CAST_MCF_VOLPTR( UINT8 )(0xFC0A0000))
#define MCF_RCM_RSR	   (CAST_MCF_VOLPTR( UINT8 )(0xFC0A0001))

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
#define MCF_SCM_MPR		(CAST_MCF_VOLPTR( UINT32 )(0xFC000000))
#define MCF_SCM_PACRA		(CAST_MCF_VOLPTR( UINT32 )(0xFC000020))
#define MCF_SCM_PACRB		(CAST_MCF_VOLPTR( UINT32 )(0xFC000024))
#define MCF_SCM_PACRC		(CAST_MCF_VOLPTR( UINT32 )(0xFC000028))
#define MCF_SCM_PACRD		(CAST_MCF_VOLPTR( UINT32 )(0xFC00002C))
#define MCF_SCM_PACRE		(CAST_MCF_VOLPTR( UINT32 )(0xFC000040))
#define MCF_SCM_PACRF		(CAST_MCF_VOLPTR( UINT32 )(0xFC000044))
#define MCF_SCM_CWCR		(CAST_MCF_VOLPTR( UINT16 )(0xFC040016))
#define MCF_SCM_CWSR		(CAST_MCF_VOLPTR( UINT8 )(0xFC04001B))
#define MCF_SCM_CWIR		(CAST_MCF_VOLPTR( UINT8 )(0xFC04001F))
#define MCF_SCM_CFADR		(CAST_MCF_VOLPTR( UINT32 )(0xFC040070))
#define MCF_SCM_CFIER		(CAST_MCF_VOLPTR( UINT8 )(0xFC040075))
#define MCF_SCM_CFLOC		(CAST_MCF_VOLPTR( UINT8 )(0xFC040076))
#define MCF_SCM_CFATR           (CAST_MCF_VOLPTR( UINT8 )(0xFC040077))
#define MCF_SCM_CFDTRH	        (CAST_MCF_VOLPTR( UINT32 )(0xFC04007C))
#define MCF_SCM_CFDTRL	        (CAST_MCF_VOLPTR( UINT32 )(0xFC04007C))

/* Bit definitions and macros for MCF_SCM_MPR */
#define MCF_SCM_MPR_MPROT2(x)	      (((x)&0x0000000F)<<20)
#define MCF_SCM_MPR_MPROT1(x)	      (((x)&0x0000000F)<<24)
#define MCF_SCM_MPR_MPROT0(x)	      (((x)&0x0000000F)<<28)
#define MCF_SCM_MPR_MPROT_MTR	      (0x4)
#define MCF_SCM_MPR_MPROT_MTW	      (0x2)
#define MCF_SCM_MPR_MPROT_MPL	      (0x1)

/* Bit definitions and macros for MCF_SCM_PACRA */
#define MCF_SCM_PACRA_PACR2(x)      (((x)&0x0000000F)<<20)
#define MCF_SCM_PACRA_PACR1(x)      (((x)&0x0000000F)<<24)
#define MCF_SCM_PACRA_PACR0(x)      (((x)&0x0000000F)<<28)
#define MCF_SCM_PACRA_PACR_SP	      (0x4)
#define MCF_SCM_PACRA_PACR_WP	      (0x2)
#define MCF_SCM_PACRA_PACR_TP	      (0x1)

/* Bit definitions and macros for MCF_SCM_PACRB */
#define MCF_SCM_PACRB_PACR12(x)     (((x)&0x0000000F)<<12)

/* Bit definitions and macros for MCF_SCM_PACRC */
#define MCF_SCM_PACRC_PACR23(x)     (((x)&0x0000000F)<<0)
#define MCF_SCM_PACRC_PACR22(x)     (((x)&0x0000000F)<<4)
#define MCF_SCM_PACRC_PACR21(x)     (((x)&0x0000000F)<<8)
#define MCF_SCM_PACRC_PACR18(x)     (((x)&0x0000000F)<<20)
#define MCF_SCM_PACRC_PACR17(x)     (((x)&0x0000000F)<<24)
#define MCF_SCM_PACRC_PACR16(x)     (((x)&0x0000000F)<<28)

/* Bit definitions and macros for MCF_SCM_PACRD */
#define MCF_SCM_PACRD_PACR31(x)     (((x)&0x0000000F)<<0)
#define MCF_SCM_PACRD_PACR30(x)     (((x)&0x0000000F)<<4)
#define MCF_SCM_PACRD_PACR29(x)     (((x)&0x0000000F)<<8)
#define MCF_SCM_PACRD_PACR28(x)     (((x)&0x0000000F)<<12)
#define MCF_SCM_PACRD_PACR26(x)     (((x)&0x0000000F)<<20)
#define MCF_SCM_PACRD_PACR25(x)     (((x)&0x0000000F)<<24)
#define MCF_SCM_PACRD_PACR24(x)     (((x)&0x0000000F)<<28)

/* Bit definitions and macros for MCF_SCM_PACRE */
#define MCF_SCM_PACRE_PACR36(x)     (((x)&0x0000000F)<<12)
#define MCF_SCM_PACRE_PACR35(x)     (((x)&0x0000000F)<<16)
#define MCF_SCM_PACRE_PACR34(x)     (((x)&0x0000000F)<<20)
#define MCF_SCM_PACRE_PACR33(x)     (((x)&0x0000000F)<<24)
#define MCF_SCM_PACRE_PACR32(x)     (((x)&0x0000000F)<<28)

/* Bit definitions and macros for MCF_SCM_PACRF */
#define MCF_SCM_PACRF_PACR42(x)     (((x)&0x0000000F)<<20)
#define MCF_SCM_PACRF_PACR41(x)     (((x)&0x0000000F)<<24)
#define MCF_SCM_PACRF_PACR40(x)     (((x)&0x0000000F)<<28)

/* Bit definitions and macros for MCF_SCM_CWCR */
#define MCF_SCM_CWCR_CWT(x)	      (((x)&0x001F)<<0)
#define MCF_SCM_CWCR_CWRI(x)	      (((x)&0x0003)<<5)
#define MCF_SCM_CWCR_CWE	      (0x0080)
#define MCF_SCM_CWCR_CWR_WH	      (0x0100)
#define MCF_SCM_CWCR_RO	              (0x8000)
#define MCF_SCM_CWCR_CWRI_INT	      (0x0000)
#define MCF_SCM_CWCR_CWRI_INT_THEN_RESET  (0x0020)
#define MCF_SCM_CWCR_CWRI_RESET     (0x0040)
#define MCF_SCM_CWCR_CWRI_WINDOW    (0x0060)

/* Bit definitions and macros for MCF_SCM_CWSR */
#define MCF_SCM_CWSR_CWSR(x)	      (((x)&0xFF)<<0)

/* Bit definitions and macros for MCF_SCM_CWIR */
#define MCF_SCM_CWIR_CWIC	      (0x01)
#define MCF_SCM_CWIR_CFEI	      (0x02)

/* Bit definitions and macros for MCF_SCM_BCR */
#define MCF_SCM_BCR_S1	        (0x00000002)
#define MCF_SCM_BCR_S4	        (0x00000010)
#define MCF_SCM_BCR_S6	        (0x00000040)
#define MCF_SCM_BCR_S7	        (0x00000080)
#define MCF_SCM_BCR_GBW	        (0x00000100)
#define MCF_SCM_BCR_GBR	        (0x00000200)

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

/* Bit definitions and macros for MCF_SCM_CFDTRH */
#define MCF_SCM_CFDTRH_CFDTR(x)      (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF_SCM_CFDTRL */
#define MCF_SCM_CFDTRL_CFDTR(x)      (((x)&0xFFFFFFFF)<<0)
/*
 *
 * Cross-bar switch (XBS) - Chapter 12
 *
 */

/* Register read/write macros */
#define MCF_XBS_PRS1	       (CAST_MCF_VOLPTR( UINT32 )(0xFC004100))
#define MCF_XBS_PRS2	       (CAST_MCF_VOLPTR( UINT32 )(0xFC004200))
#define MCF_XBS_PRS3	       (CAST_MCF_VOLPTR( UINT32 )(0xFC004300))
#define MCF_XBS_PRS4	       (CAST_MCF_VOLPTR( UINT32 )(0xFC004400))
#define MCF_XBS_PRS5	       (CAST_MCF_VOLPTR( UINT32 )(0xFC004500))
#define MCF_XBS_PRS6	       (CAST_MCF_VOLPTR( UINT32 )(0xFC004600))
#define MCF_XBS_PRS7	       (CAST_MCF_VOLPTR( UINT32 )(0xFC004700))
#define MCF_XBS_PRS(x)         (CAST_MCF_VOLPTR( UINT32 )(0xFC004100+((x-1)*0x100)))
#define MCF_XBS_CRS1	       (CAST_MCF_VOLPTR( UINT32 )(0xFC004110))
#define MCF_XBS_CRS2	       (CAST_MCF_VOLPTR( UINT32 )(0xFC004210))
#define MCF_XBS_CRS3	       (CAST_MCF_VOLPTR( UINT32 )(0xFC004310))
#define MCF_XBS_CRS4	       (CAST_MCF_VOLPTR( UINT32 )(0xFC004410))
#define MCF_XBS_CRS5	       (CAST_MCF_VOLPTR( UINT32 )(0xFC004510))
#define MCF_XBS_CRS6	       (CAST_MCF_VOLPTR( UINT32 )(0xFC004610))
#define MCF_XBS_CRS7	       (CAST_MCF_VOLPTR( UINT32 )(0xFC004710))
#define MCF_XBS_CRS(x)         (CAST_MCF_VOLPTR( UINT32 )(0xFC004110+((x-1)*0x100)))

/* Bit definitions and macros for MCF_XBS_PRS */
#define MCF_XBS_PRS_M0(x)	     (((x)&0x00000007)<<0)
#define MCF_XBS_PRS_M1(x)	     (((x)&0x00000007)<<4)
#define MCF_XBS_PRS_M2(x)	     (((x)&0x00000007)<<8)

/* Bit definitions and macros for MCF_XBS_CRS */
#define MCF_XBS_CRS_PARK(x)	           (((x)&0x00000007)<<0)
#define MCF_XBS_CRS_PCTL(x)	           (((x)&0x00000003)<<4)
#define MCF_XBS_CRS_ARB	                   (0x00000100)
#define MCF_XBS_CRS_RO	                   (0x80000000)
#define MCF_XBS_CRS_PCTL_PARK_FIELD	   (0x00000000)
#define MCF_XBS_CRS_PCTL_PARK_ON_LAST	   (0x00000010)
#define MCF_XBS_CRS_PCTL_PARK_NO_MASTER    (0x00000020)
#define MCF_XBS_CRS_PCTL_PARK_CORE	   (0x00000000)
#define MCF_XBS_CRS_PCTL_PARK_EDMA	   (0x00000001)
#define MCF_XBS_CRS_PCTL_PARK_FEC	   (0x00000002)

/*
 *
 * General Purpose I/O (GPIO) - Chapter 13
 *
 */

/* Register read/write macros */
#define MCF_GPIO_PODR_BUSCTL             (CAST_MCF_VOL(UINT8)(0xFC0A4000))
#define MCF_GPIO_PODR_BE                 (CAST_MCF_VOL(UINT8)(0xFC0A4001))
#define MCF_GPIO_PODR_CS                 (CAST_MCF_VOL(UINT8)(0xFC0A4002))
#define MCF_GPIO_PODR_FECI2C             (CAST_MCF_VOL(UINT8)(0xFC0A4003))
#define MCF_GPIO_PODR_QSPI               (CAST_MCF_VOL(UINT8)(0xFC0A4004))
#define MCF_GPIO_PODR_TIMER              (CAST_MCF_VOL(UINT8)(0xFC0A4005))
#define MCF_GPIO_PODR_UART               (CAST_MCF_VOL(UINT8)(0xFC0A4006))
#define MCF_GPIO_PODR_FECH               (CAST_MCF_VOL(UINT8)(0xFC0A4007))
#define MCF_GPIO_PODR_FECL               (CAST_MCF_VOL(UINT8)(0xFC0A4008))
#define MCF_GPIO_PDDR_BUSCTL             (CAST_MCF_VOL(UINT8)(0xFC0A400C))
#define MCF_GPIO_PDDR_BE                 (CAST_MCF_VOL(UINT8)(0xFC0A400D))
#define MCF_GPIO_PDDR_CS                 (CAST_MCF_VOL(UINT8)(0xFC0A400E))
#define MCF_GPIO_PDDR_FECI2C             (CAST_MCF_VOL(UINT8)(0xFC0A400F))
#define MCF_GPIO_PDDR_QSPI               (CAST_MCF_VOL(UINT8)(0xFC0A4010))
#define MCF_GPIO_PDDR_TIMER              (CAST_MCF_VOL(UINT8)(0xFC0A4011))
#define MCF_GPIO_PDDR_UART               (CAST_MCF_VOL(UINT8)(0xFC0A4012))
#define MCF_GPIO_PDDR_FECH               (CAST_MCF_VOL(UINT8)(0xFC0A4013))
#define MCF_GPIO_PDDR_FECL               (CAST_MCF_VOL(UINT8)(0xFC0A4014))
#define MCF_GPIO_PPDSDR_BUSCTL           (CAST_MCF_VOL(UINT8)(0xFC0A4018))
#define MCF_GPIO_PPDSDR_BE               (CAST_MCF_VOL(UINT8)(0xFC0A4019))
#define MCF_GPIO_PPDSDR_CS               (CAST_MCF_VOL(UINT8)(0xFC0A401A))
#define MCF_GPIO_PPDSDR_FECI2C           (CAST_MCF_VOL(UINT8)(0xFC0A401B))
#define MCF_GPIO_PPDSDR_QSPI             (CAST_MCF_VOL(UINT8)(0xFC0A401C))
#define MCF_GPIO_PPDSDR_TIMER            (CAST_MCF_VOL(UINT8)(0xFC0A401D))
#define MCF_GPIO_PPDSDR_UART             (CAST_MCF_VOL(UINT8)(0xFC0A401E))
#define MCF_GPIO_PPDSDR_FECH             (CAST_MCF_VOL(UINT8)(0xFC0A401F))
#define MCF_GPIO_PPDSDR_FECL             (CAST_MCF_VOL(UINT8)(0xFC0A4020))
#define MCF_GPIO_PCLRR_BUSCTL            (CAST_MCF_VOL(UINT8)(0xFC0A4024))
#define MCF_GPIO_PCLRR_BE                (CAST_MCF_VOL(UINT8)(0xFC0A4025))
#define MCF_GPIO_PCLRR_CS                (CAST_MCF_VOL(UINT8)(0xFC0A4026))
#define MCF_GPIO_PCLRR_FECI2C            (CAST_MCF_VOL(UINT8)(0xFC0A4027))
#define MCF_GPIO_PCLRR_QSPI              (CAST_MCF_VOL(UINT8)(0xFC0A4028))
#define MCF_GPIO_PCLRR_TIMER             (CAST_MCF_VOL(UINT8)(0xFC0A4029))
#define MCF_GPIO_PCLRR_UART              (CAST_MCF_VOL(UINT8)(0xFC0A402A))
#define MCF_GPIO_PCLRR_FECH              (CAST_MCF_VOL(UINT8)(0xFC0A402B))
#define MCF_GPIO_PCLRR_FECL              (CAST_MCF_VOL(UINT8)(0xFC0A402C))
#define MCF_GPIO_PAR_BUSCTL              (CAST_MCF_VOL(UINT8)(0xFC0A4030))
#define MCF_GPIO_PAR_BE                  (CAST_MCF_VOL(UINT8)(0xFC0A4031))
#define MCF_GPIO_PAR_CS                  (CAST_MCF_VOL(UINT8)(0xFC0A4032))
#define MCF_GPIO_PAR_FECI2C              (CAST_MCF_VOL(UINT8)(0xFC0A4033))
#define MCF_GPIO_PAR_QSPI                (CAST_MCF_VOL(UINT8)(0xFC0A4034))
#define MCF_GPIO_PAR_TIMER               (CAST_MCF_VOL(UINT8)(0xFC0A4035))
#define MCF_GPIO_PAR_UART                (CAST_MCF_VOL(UINT16)(0xFC0A4036))
#define MCF_GPIO_PAR_FEC                 (CAST_MCF_VOL(UINT8)(0xFC0A4038))
#define MCF_GPIO_PAR_IRQ                 (CAST_MCF_VOL(UINT8)(0xFC0A4039))
#define MCF_GPIO_MSCR_FLEXBUS            (CAST_MCF_VOL(UINT8)(0xFC0A403A))
#define MCF_GPIO_MSCR_SDRAM              (CAST_MCF_VOL(UINT8)(0xFC0A403B))
#define MCF_GPIO_DSCR_I2C                (CAST_MCF_VOL(UINT8)(0xFC0A403C))
#define MCF_GPIO_DSCR_MISC               (CAST_MCF_VOL(UINT8)(0xFC0A403D))
#define MCF_GPIO_DSCR_FEC                (CAST_MCF_VOL(UINT8)(0xFC0A403E))
#define MCF_GPIO_DSCR_UART               (CAST_MCF_VOL(UINT8)(0xFC0A403F))
#define MCF_GPIO_DSCR_QSPI               (CAST_MCF_VOL(UINT8)(0xFC0A4040))

/* Bit definitions and macros for MCF_GPIO_PODR_BUSCTL */
#define MCF_GPIO_PODR_BUSCTL_POSDR_BUSCTL0     (0x01)
#define MCF_GPIO_PODR_BUSCTL_PODR_BUSCTL1      (0x02)
#define MCF_GPIO_PODR_BUSCTL_PODR_BUSCTL2      (0x04)
#define MCF_GPIO_PODR_BUSCTL_PODR_BUSCTL3      (0x08)

/* Bit definitions and macros for MCF_GPIO_PODR_BE */
#define MCF_GPIO_PODR_BE_PODR_BE0              (0x01)
#define MCF_GPIO_PODR_BE_PODR_BE1              (0x02)
#define MCF_GPIO_PODR_BE_PODR_BE2              (0x04)
#define MCF_GPIO_PODR_BE_PODR_BE3              (0x08)

/* Bit definitions and macros for MCF_GPIO_PODR_CS */
#define MCF_GPIO_PODR_CS_PODR_CS1              (0x02)
#define MCF_GPIO_PODR_CS_PODR_CS2              (0x04)
#define MCF_GPIO_PODR_CS_PODR_CS3              (0x08)

/* Bit definitions and macros for MCF_GPIO_PODR_FECI2C */
#define MCF_GPIO_PODR_FECI2C_PODR_FECI2C0      (0x01)
#define MCF_GPIO_PODR_FECI2C_PODR_FECI2C1      (0x02)
#define MCF_GPIO_PODR_FECI2C_PODR_FECI2C2      (0x04)
#define MCF_GPIO_PODR_FECI2C_PODR_FECI2C3      (0x08)

/* Bit definitions and macros for MCF_GPIO_PODR_QSPI */
#define MCF_GPIO_PODR_QSPI_PODR_QSPI0          (0x01)
#define MCF_GPIO_PODR_QSPI_PODR_QSPI1          (0x02)
#define MCF_GPIO_PODR_QSPI_PODR_QSPI2          (0x04)
#define MCF_GPIO_PODR_QSPI_PODR_QSPI3          (0x08)

/* Bit definitions and macros for MCF_GPIO_PODR_TIMER */
#define MCF_GPIO_PODR_TIMER_PODR_TIMER0        (0x01)
#define MCF_GPIO_PODR_TIMER_PODR_TIMER1        (0x02)
#define MCF_GPIO_PODR_TIMER_PODR_TIMER2        (0x04)
#define MCF_GPIO_PODR_TIMER_PODR_TIMER3        (0x08)

/* Bit definitions and macros for MCF_GPIO_PODR_UART */
#define MCF_GPIO_PODR_UART_PODR_UART0          (0x01)
#define MCF_GPIO_PODR_UART_PODR_UART1          (0x02)
#define MCF_GPIO_PODR_UART_PODR_UART2          (0x04)
#define MCF_GPIO_PODR_UART_PODR_UART3          (0x08)
#define MCF_GPIO_PODR_UART_PODR_UART4          (0x10)
#define MCF_GPIO_PODR_UART_PODR_UART5          (0x20)
#define MCF_GPIO_PODR_UART_PODR_UART6          (0x40)
#define MCF_GPIO_PODR_UART_PODR_UART7          (0x80)

/* Bit definitions and macros for MCF_GPIO_PODR_FECH */
#define MCF_GPIO_PODR_FECH_PODR_FECH0          (0x01)
#define MCF_GPIO_PODR_FECH_PODR_FECH1          (0x02)
#define MCF_GPIO_PODR_FECH_PODR_FECH2          (0x04)
#define MCF_GPIO_PODR_FECH_PODR_FECH3          (0x08)
#define MCF_GPIO_PODR_FECH_PODR_FECH4          (0x10)
#define MCF_GPIO_PODR_FECH_PODR_FECH5          (0x20)
#define MCF_GPIO_PODR_FECH_PODR_FECH6          (0x40)
#define MCF_GPIO_PODR_FECH_PODR_FECH7          (0x80)

/* Bit definitions and macros for MCF_GPIO_PODR_FECL */
#define MCF_GPIO_PODR_FECL_PODR_FECL0          (0x01)
#define MCF_GPIO_PODR_FECL_PODR_FECL1          (0x02)
#define MCF_GPIO_PODR_FECL_PODR_FECL2          (0x04)
#define MCF_GPIO_PODR_FECL_PODR_FECL3          (0x08)
#define MCF_GPIO_PODR_FECL_PODR_FECL4          (0x10)
#define MCF_GPIO_PODR_FECL_PODR_FECL5          (0x20)
#define MCF_GPIO_PODR_FECL_PODR_FECL6          (0x40)
#define MCF_GPIO_PODR_FECL_PODR_FECL7          (0x80)

/* Bit definitions and macros for MCF_GPIO_PDDR_BUSCTL */
#define MCF_GPIO_PDDR_BUSCTL_PDDR_BUSCTL0      (0x01)
#define MCF_GPIO_PDDR_BUSCTL_PDDR_BUSCTL1      (0x02)
#define MCF_GPIO_PDDR_BUSCTL_PDDR_BUSCTL2      (0x04)
#define MCF_GPIO_PDDR_BUSCTL_PDDR_BUSCTL3      (0x08)

/* Bit definitions and macros for MCF_GPIO_PDDR_BE */
#define MCF_GPIO_PDDR_BE_PDDR_BE0              (0x01)
#define MCF_GPIO_PDDR_BE_PDDR_BE1              (0x02)
#define MCF_GPIO_PDDR_BE_PDDR_BE2              (0x04)
#define MCF_GPIO_PDDR_BE_PDDR_BE3              (0x08)

/* Bit definitions and macros for MCF_GPIO_PDDR_CS */
#define MCF_GPIO_PDDR_CS_PDDR_CS1              (0x02)
#define MCF_GPIO_PDDR_CS_PDDR_CS2              (0x04)
#define MCF_GPIO_PDDR_CS_PDDR_CS3              (0x08)

/* Bit definitions and macros for MCF_GPIO_PDDR_FECI2C */
#define MCF_GPIO_PDDR_FECI2C_PDDR_FECI2C0      (0x01)
#define MCF_GPIO_PDDR_FECI2C_PDDR_FECI2C1      (0x02)
#define MCF_GPIO_PDDR_FECI2C_PDDR_FECI2C2      (0x04)
#define MCF_GPIO_PDDR_FECI2C_PDDR_FECI2C3      (0x08)

/* Bit definitions and macros for MCF_GPIO_PDDR_QSPI */
#define MCF_GPIO_PDDR_QSPI_PDDR_QSPI0          (0x01)
#define MCF_GPIO_PDDR_QSPI_PDDR_QSPI1          (0x02)
#define MCF_GPIO_PDDR_QSPI_PDDR_QSPI2          (0x04)
#define MCF_GPIO_PDDR_QSPI_PDDR_QSPI3          (0x08)

/* Bit definitions and macros for MCF_GPIO_PDDR_TIMER */
#define MCF_GPIO_PDDR_TIMER_PDDR_TIMER0        (0x01)
#define MCF_GPIO_PDDR_TIMER_PDDR_TIMER1        (0x02)
#define MCF_GPIO_PDDR_TIMER_PDDR_TIMER2        (0x04)
#define MCF_GPIO_PDDR_TIMER_PDDR_TIMER3        (0x08)

/* Bit definitions and macros for MCF_GPIO_PDDR_UART */
#define MCF_GPIO_PDDR_UART_PDDR_UART0          (0x01)
#define MCF_GPIO_PDDR_UART_PDDR_UART1          (0x02)
#define MCF_GPIO_PDDR_UART_PDDR_UART2          (0x04)
#define MCF_GPIO_PDDR_UART_PDDR_UART3          (0x08)
#define MCF_GPIO_PDDR_UART_PDDR_UART4          (0x10)
#define MCF_GPIO_PDDR_UART_PDDR_UART5          (0x20)
#define MCF_GPIO_PDDR_UART_PDDR_UART6          (0x40)
#define MCF_GPIO_PDDR_UART_PDDR_UART7          (0x80)

/* Bit definitions and macros for MCF_GPIO_PDDR_FECH */
#define MCF_GPIO_PDDR_FECH_PDDR_FECH0          (0x01)
#define MCF_GPIO_PDDR_FECH_PDDR_FECH1          (0x02)
#define MCF_GPIO_PDDR_FECH_PDDR_FECH2          (0x04)
#define MCF_GPIO_PDDR_FECH_PDDR_FECH3          (0x08)
#define MCF_GPIO_PDDR_FECH_PDDR_FECH4          (0x10)
#define MCF_GPIO_PDDR_FECH_PDDR_FECH5          (0x20)
#define MCF_GPIO_PDDR_FECH_PDDR_FECH6          (0x40)
#define MCF_GPIO_PDDR_FECH_PDDR_FECH7          (0x80)

/* Bit definitions and macros for MCF_GPIO_PDDR_FECL */
#define MCF_GPIO_PDDR_FECL_PDDR_FECL0          (0x01)
#define MCF_GPIO_PDDR_FECL_PDDR_FECL1          (0x02)
#define MCF_GPIO_PDDR_FECL_PDDR_FECL2          (0x04)
#define MCF_GPIO_PDDR_FECL_PDDR_FECL3          (0x08)
#define MCF_GPIO_PDDR_FECL_PDDR_FECL4          (0x10)
#define MCF_GPIO_PDDR_FECL_PDDR_FECL5          (0x20)
#define MCF_GPIO_PDDR_FECL_PDDR_FECL6          (0x40)
#define MCF_GPIO_PDDR_FECL_PDDR_FECL7          (0x80)

/* Bit definitions and macros for MCF_GPIO_PPDSDR_BUSCTL */
#define MCF_GPIO_PPDSDR_BUSCTL_PPDSDR_BUSCTL0  (0x01)
#define MCF_GPIO_PPDSDR_BUSCTL_PPDSDR_BUSCTL1  (0x02)
#define MCF_GPIO_PPDSDR_BUSCTL_PPDSDR_BUSCTL2  (0x04)
#define MCF_GPIO_PPDSDR_BUSCTL_PPDSDR_BUSCTL3  (0x08)

/* Bit definitions and macros for MCF_GPIO_PPDSDR_BE */
#define MCF_GPIO_PPDSDR_BE_PPDSDR_BE0          (0x01)
#define MCF_GPIO_PPDSDR_BE_PPDSDR_BE1          (0x02)
#define MCF_GPIO_PPDSDR_BE_PPDSDR_BE2          (0x04)
#define MCF_GPIO_PPDSDR_BE_PPDSDR_BE3          (0x08)

/* Bit definitions and macros for MCF_GPIO_PPDSDR_CS */
#define MCF_GPIO_PPDSDR_CS_PPDSDR_CS1          (0x02)
#define MCF_GPIO_PPDSDR_CS_PPDSDR_CS2          (0x04)
#define MCF_GPIO_PPDSDR_CS_PPDSDR_CS3          (0x08)

/* Bit definitions and macros for MCF_GPIO_PPDSDR_FECI2C */
#define MCF_GPIO_PPDSDR_FECI2C_PPDSDR_FECI2C0  (0x01)
#define MCF_GPIO_PPDSDR_FECI2C_PPDSDR_FECI2C1  (0x02)
#define MCF_GPIO_PPDSDR_FECI2C_PPDSDR_FECI2C2  (0x04)
#define MCF_GPIO_PPDSDR_FECI2C_PPDSDR_FECI2C3  (0x08)

/* Bit definitions and macros for MCF_GPIO_PPDSDR_QSPI */
#define MCF_GPIO_PPDSDR_QSPI_PPDSDR_QSPI0      (0x01)
#define MCF_GPIO_PPDSDR_QSPI_PPDSDR_QSPI1      (0x02)
#define MCF_GPIO_PPDSDR_QSPI_PPDSDR_QSPI2      (0x04)
#define MCF_GPIO_PPDSDR_QSPI_PPDSDR_QSPI3      (0x08)

/* Bit definitions and macros for MCF_GPIO_PPDSDR_TIMER */
#define MCF_GPIO_PPDSDR_TIMER_PPDSDR_TIMER0    (0x01)
#define MCF_GPIO_PPDSDR_TIMER_PPDSDR_TIMER1    (0x02)
#define MCF_GPIO_PPDSDR_TIMER_PPDSDR_TIMER2    (0x04)
#define MCF_GPIO_PPDSDR_TIMER_PPDSDR_TIMER3    (0x08)

/* Bit definitions and macros for MCF_GPIO_PPDSDR_UART */
#define MCF_GPIO_PPDSDR_UART_PPDSDR_UART0      (0x01)
#define MCF_GPIO_PPDSDR_UART_PPDSDR_UART1      (0x02)
#define MCF_GPIO_PPDSDR_UART_PPDSDR_UART2      (0x04)
#define MCF_GPIO_PPDSDR_UART_PPDSDR_UART3      (0x08)
#define MCF_GPIO_PPDSDR_UART_PPDSDR_UART4      (0x10)
#define MCF_GPIO_PPDSDR_UART_PPDSDR_UART5      (0x20)
#define MCF_GPIO_PPDSDR_UART_PPDSDR_UART6      (0x40)
#define MCF_GPIO_PPDSDR_UART_PPDSDR_UART7      (0x80)

/* Bit definitions and macros for MCF_GPIO_PPDSDR_FECH */
#define MCF_GPIO_PPDSDR_FECH_PPDSDR_FECH0      (0x01)
#define MCF_GPIO_PPDSDR_FECH_PPDSDR_FECH1      (0x02)
#define MCF_GPIO_PPDSDR_FECH_PPDSDR_FECH2      (0x04)
#define MCF_GPIO_PPDSDR_FECH_PPDSDR_FECH3      (0x08)
#define MCF_GPIO_PPDSDR_FECH_PPDSDR_FECH4      (0x10)
#define MCF_GPIO_PPDSDR_FECH_PPDSDR_FECH5      (0x20)
#define MCF_GPIO_PPDSDR_FECH_PPDSDR_FECH6      (0x40)
#define MCF_GPIO_PPDSDR_FECH_PPDSDR_FECH7      (0x80)

/* Bit definitions and macros for MCF_GPIO_PPDSDR_FECL */
#define MCF_GPIO_PPDSDR_FECL_PPDSDR_FECL0      (0x01)
#define MCF_GPIO_PPDSDR_FECL_PPDSDR_FECL1      (0x02)
#define MCF_GPIO_PPDSDR_FECL_PPDSDR_FECL2      (0x04)
#define MCF_GPIO_PPDSDR_FECL_PPDSDR_FECL3      (0x08)
#define MCF_GPIO_PPDSDR_FECL_PPDSDR_FECL4      (0x10)
#define MCF_GPIO_PPDSDR_FECL_PPDSDR_FECL5      (0x20)
#define MCF_GPIO_PPDSDR_FECL_PPDSDR_FECL6      (0x40)
#define MCF_GPIO_PPDSDR_FECL_PPDSDR_FECL7      (0x80)

/* Bit definitions and macros for MCF_GPIO_PCLRR_BUSCTL */
#define MCF_GPIO_PCLRR_BUSCTL_PCLRR_BUSCTL0    (0x01)
#define MCF_GPIO_PCLRR_BUSCTL_PCLRR_BUSCTL1    (0x02)
#define MCF_GPIO_PCLRR_BUSCTL_PCLRR_BUSCTL2    (0x04)
#define MCF_GPIO_PCLRR_BUSCTL_PCLRR_BUSCTL3    (0x08)

/* Bit definitions and macros for MCF_GPIO_PCLRR_BE */
#define MCF_GPIO_PCLRR_BE_PCLRR_BE0            (0x01)
#define MCF_GPIO_PCLRR_BE_PCLRR_BE1            (0x02)
#define MCF_GPIO_PCLRR_BE_PCLRR_BE2            (0x04)
#define MCF_GPIO_PCLRR_BE_PCLRR_BE3            (0x08)

/* Bit definitions and macros for MCF_GPIO_PCLRR_CS */
#define MCF_GPIO_PCLRR_CS_PCLRR_CS1            (0x02)
#define MCF_GPIO_PCLRR_CS_PCLRR_CS2            (0x04)
#define MCF_GPIO_PCLRR_CS_PCLRR_CS3            (0x08)

/* Bit definitions and macros for MCF_GPIO_PCLRR_FECI2C */
#define MCF_GPIO_PCLRR_FECI2C_PCLRR_FECI2C0    (0x01)
#define MCF_GPIO_PCLRR_FECI2C_PCLRR_FECI2C1    (0x02)
#define MCF_GPIO_PCLRR_FECI2C_PCLRR_FECI2C2    (0x04)
#define MCF_GPIO_PCLRR_FECI2C_PCLRR_FECI2C3    (0x08)

/* Bit definitions and macros for MCF_GPIO_PCLRR_QSPI */
#define MCF_GPIO_PCLRR_QSPI_PCLRR_QSPI0        (0x01)
#define MCF_GPIO_PCLRR_QSPI_PCLRR_QSPI1        (0x02)
#define MCF_GPIO_PCLRR_QSPI_PCLRR_QSPI2        (0x04)
#define MCF_GPIO_PCLRR_QSPI_PCLRR_QSPI3        (0x08)

/* Bit definitions and macros for MCF_GPIO_PCLRR_TIMER */
#define MCF_GPIO_PCLRR_TIMER_PCLRR_TIMER0      (0x01)
#define MCF_GPIO_PCLRR_TIMER_PCLRR_TIMER1      (0x02)
#define MCF_GPIO_PCLRR_TIMER_PCLRR_TIMER2      (0x04)
#define MCF_GPIO_PCLRR_TIMER_PCLRR_TIMER3      (0x08)

/* Bit definitions and macros for MCF_GPIO_PCLRR_UART */
#define MCF_GPIO_PCLRR_UART_PCLRR_UART0        (0x01)
#define MCF_GPIO_PCLRR_UART_PCLRR_UART1        (0x02)
#define MCF_GPIO_PCLRR_UART_PCLRR_UART2        (0x04)
#define MCF_GPIO_PCLRR_UART_PCLRR_UART3        (0x08)
#define MCF_GPIO_PCLRR_UART_PCLRR_UART4        (0x10)
#define MCF_GPIO_PCLRR_UART_PCLRR_UART5        (0x20)
#define MCF_GPIO_PCLRR_UART_PCLRR_UART6        (0x40)
#define MCF_GPIO_PCLRR_UART_PCLRR_UART7        (0x80)

/* Bit definitions and macros for MCF_GPIO_PCLRR_FECH */
#define MCF_GPIO_PCLRR_FECH_PCLRR_FECH0        (0x01)
#define MCF_GPIO_PCLRR_FECH_PCLRR_FECH1        (0x02)
#define MCF_GPIO_PCLRR_FECH_PCLRR_FECH2        (0x04)
#define MCF_GPIO_PCLRR_FECH_PCLRR_FECH3        (0x08)
#define MCF_GPIO_PCLRR_FECH_PCLRR_FECH4        (0x10)
#define MCF_GPIO_PCLRR_FECH_PCLRR_FECH5        (0x20)
#define MCF_GPIO_PCLRR_FECH_PCLRR_FECH6        (0x40)
#define MCF_GPIO_PCLRR_FECH_PCLRR_FECH7        (0x80)

/* Bit definitions and macros for MCF_GPIO_PCLRR_FECL */
#define MCF_GPIO_PCLRR_FECL_PCLRR_FECL0        (0x01)
#define MCF_GPIO_PCLRR_FECL_PCLRR_FECL1        (0x02)
#define MCF_GPIO_PCLRR_FECL_PCLRR_FECL2        (0x04)
#define MCF_GPIO_PCLRR_FECL_PCLRR_FECL3        (0x08)
#define MCF_GPIO_PCLRR_FECL_PCLRR_FECL4        (0x10)
#define MCF_GPIO_PCLRR_FECL_PCLRR_FECL5        (0x20)
#define MCF_GPIO_PCLRR_FECL_PCLRR_FECL6        (0x40)
#define MCF_GPIO_PCLRR_FECL_PCLRR_FECL7        (0x80)

/* Bit definitions and macros for MCF_GPIO_PAR_BUSCTL */
#define MCF_GPIO_PAR_BUSCTL_PAR_TS(x)          (((x)&0x03)<<0)
#define MCF_GPIO_PAR_BUSCTL_PAR_RWB            (0x04)
#define MCF_GPIO_PAR_BUSCTL_PAR_TA             (0x08)
#define MCF_GPIO_PAR_BUSCTL_PAR_OE             (0x10)
#define MCF_GPIO_PAR_BUSCTL_PAR_TS_GPIO        (0x00)
#define MCF_GPIO_PAR_BUSCTL_PAR_TS_DACK0       (0x02)
#define MCF_GPIO_PAR_BUSCTL_PAR_TS_TS          (0x03)

/* Bit definitions and macros for MCF_GPIO_PAR_BE */
#define MCF_GPIO_PAR_BE_PAR_BE0                (0x01)
#define MCF_GPIO_PAR_BE_PAR_BE1                (0x02)
#define MCF_GPIO_PAR_BE_PAR_BE2                (0x04)
#define MCF_GPIO_PAR_BE_PAR_BE3                (0x08)

/* Bit definitions and macros for MCF_GPIO_PAR_CS */
#define MCF_GPIO_PAR_CS_PAR_CS1(x)             (((x)&0x03)<<0)
#define MCF_GPIO_PAR_CS_PAR_CS2                (0x04)
#define MCF_GPIO_PAR_CS_PAR_CS3                (0x08)
#define MCF_GPIO_PAR_CS_PAR_CS1_GPIO           (0x00)
#define MCF_GPIO_PAR_CS_PAR_CS1_SDCS1          (0x02)
#define MCF_GPIO_PAR_CS_PAR_CS1_CS1            (0x03)

/* Bit definitions and macros for MCF_GPIO_PAR_FECI2C */
#define MCF_GPIO_PAR_FECI2C_PAR_SDA(x)         (((x)&0x03)<<0)
#define MCF_GPIO_PAR_FECI2C_PAR_SCL(x)         (((x)&0x03)<<2)
#define MCF_GPIO_PAR_FECI2C_PAR_MDIO(x)        (((x)&0x03)<<4)
#define MCF_GPIO_PAR_FECI2C_PAR_MDC(x)         (((x)&0x03)<<6)
#define MCF_GPIO_PAR_FECI2C_PAR_MDC_GPIO       (0x00)
#define MCF_GPIO_PAR_FECI2C_PAR_MDC_UTXD2      (0x40)
#define MCF_GPIO_PAR_FECI2C_PAR_MDC_SCL        (0x80)
#define MCF_GPIO_PAR_FECI2C_PAR_MDC_EMDC       (0xC0)
#define MCF_GPIO_PAR_FECI2C_PAR_MDIO_GPIO      (0x00)
#define MCF_GPIO_PAR_FECI2C_PAR_MDIO_URXD2     (0x10)
#define MCF_GPIO_PAR_FECI2C_PAR_MDIO_SDA       (0x20)
#define MCF_GPIO_PAR_FECI2C_PAR_MDIO_EMDIO     (0x30)
#define MCF_GPIO_PAR_FECI2C_PAR_SCL_GPIO       (0x00)
#define MCF_GPIO_PAR_FECI2C_PAR_SCL_UTXD2      (0x04)
#define MCF_GPIO_PAR_FECI2C_PAR_SCL_SCL        (0x0C)
#define MCF_GPIO_PAR_FECI2C_PAR_SDA_GPIO       (0x00)
#define MCF_GPIO_PAR_FECI2C_PAR_SDA_URXD2      (0x02)
#define MCF_GPIO_PAR_FECI2C_PAR_SDA_SDA        (0x03)

/* Bit definitions and macros for MCF_GPIO_PAR_QSPI */
#define MCF_GPIO_PAR_QSPI_PAR_SCK(x)           (((x)&0x03)<<0)
#define MCF_GPIO_PAR_QSPI_PAR_DOUT(x)          (((x)&0x03)<<2)
#define MCF_GPIO_PAR_QSPI_PAR_DIN(x)           (((x)&0x03)<<4)
#define MCF_GPIO_PAR_QSPI_PAR_PCS2(x)          (((x)&0x03)<<6)
#define MCF_GPIO_PAR_QSPI_PAR_PCS2_GPIO        (0x00)
#define MCF_GPIO_PAR_QSPI_PAR_PCS2_URTS2       (0x40)
#define MCF_GPIO_PAR_QSPI_PAR_PCS2_DACK0       (0x80)
#define MCF_GPIO_PAR_QSPI_PAR_PCS2_PCS2        (0xC0)
#define MCF_GPIO_PAR_QSPI_PAR_DIN_GPIO         (0x00)
#define MCF_GPIO_PAR_QSPI_PAR_DIN_UCTS2        (0x10)
#define MCF_GPIO_PAR_QSPI_PAR_DIN_DREQ0        (0x20)
#define MCF_GPIO_PAR_QSPI_PAR_DIN_DIN          (0x30)
#define MCF_GPIO_PAR_QSPI_PAR_DOUT_GPIO        (0x00)
#define MCF_GPIO_PAR_QSPI_PAR_DOUT_SDA         (0x08)
#define MCF_GPIO_PAR_QSPI_PAR_DOUT_DOUT        (0x0C)
#define MCF_GPIO_PAR_QSPI_PAR_SCK_GPIO         (0x00)
#define MCF_GPIO_PAR_QSPI_PAR_SCK_SCL          (0x02)
#define MCF_GPIO_PAR_QSPI_PAR_SCK_SCK          (0x03)

/* Bit definitions and macros for MCF_GPIO_PAR_TIMER */
#define MCF_GPIO_PAR_TIMER_PAR_TIN0(x)         (((x)&0x03)<<0)
#define MCF_GPIO_PAR_TIMER_PAR_TIN1(x)         (((x)&0x03)<<2)
#define MCF_GPIO_PAR_TIMER_PAR_TIN2(x)         (((x)&0x03)<<4)
#define MCF_GPIO_PAR_TIMER_PAR_TIN3(x)         (((x)&0x03)<<6)
#define MCF_GPIO_PAR_TIMER_PAR_TIN3_GPIO       (0x00)
#define MCF_GPIO_PAR_TIMER_PAR_TIN3_UCTS2      (0x40)
#define MCF_GPIO_PAR_TIMER_PAR_TIN3_TOUT3      (0x80)
#define MCF_GPIO_PAR_TIMER_PAR_TIN3_TIN3       (0xC0)
#define MCF_GPIO_PAR_TIMER_PAR_TIN2_GPIO       (0x00)
#define MCF_GPIO_PAR_TIMER_PAR_TIN2_URTS2      (0x10)
#define MCF_GPIO_PAR_TIMER_PAR_TIN2_TOUT2      (0x20)
#define MCF_GPIO_PAR_TIMER_PAR_TIN2_TIN2       (0x30)
#define MCF_GPIO_PAR_TIMER_PAR_TIN1_GPIO       (0x00)
#define MCF_GPIO_PAR_TIMER_PAR_TIN1_URXD2      (0x04)
#define MCF_GPIO_PAR_TIMER_PAR_TIN1_TOUT1      (0x08)
#define MCF_GPIO_PAR_TIMER_PAR_TIN1_TIN1       (0x0C)
#define MCF_GPIO_PAR_TIMER_PAR_TIN0_GPIO       (0x00)
#define MCF_GPIO_PAR_TIMER_PAR_TIN0_UTXD2      (0x01)
#define MCF_GPIO_PAR_TIMER_PAR_TIN0_TOUT0      (0x02)
#define MCF_GPIO_PAR_TIMER_PAR_TIN0_TIN0       (0x03)

/* Bit definitions and macros for MCF_GPIO_PAR_UART */
#define MCF_GPIO_PAR_UART_PAR_URXD0            (0x0001)
#define MCF_GPIO_PAR_UART_PAR_UTXD0            (0x0002)
#define MCF_GPIO_PAR_UART_PAR_URTS0(x)         (((x)&0x0003)<<2)
#define MCF_GPIO_PAR_UART_PAR_UCTS0(x)         (((x)&0x0003)<<4)
#define MCF_GPIO_PAR_UART_PAR_URXD1            (0x0040)
#define MCF_GPIO_PAR_UART_PAR_UTXD1            (0x0080)
#define MCF_GPIO_PAR_UART_PAR_URTS1(x)         (((x)&0x0003)<<8)
#define MCF_GPIO_PAR_UART_PAR_UCTS1(x)         (((x)&0x0003)<<10)
#define MCF_GPIO_PAR_UART_PAR_UCTS1_GPIO       (0x0000)
#define MCF_GPIO_PAR_UART_PAR_UCTS1_PCS1       (0x0400)
#define MCF_GPIO_PAR_UART_PAR_UCTS1_TIN1       (0x0800)
#define MCF_GPIO_PAR_UART_PAR_UCTS1_UCTS1      (0x0C00)
#define MCF_GPIO_PAR_UART_PAR_URTS1_GPIO       (0x0000)
#define MCF_GPIO_PAR_UART_PAR_URTS1_PCS1       (0x0100)
#define MCF_GPIO_PAR_UART_PAR_URTS1_TOUT1      (0x0200)
#define MCF_GPIO_PAR_UART_PAR_URTS1_URTS1      (0x0300)
#define MCF_GPIO_PAR_UART_PAR_UCTS0_GPIO       (0x0000)
#define MCF_GPIO_PAR_UART_PAR_UCTS0_PCS0       (0x0010)
#define MCF_GPIO_PAR_UART_PAR_UCTS0_TIN0       (0x0020)
#define MCF_GPIO_PAR_UART_PAR_UCTS0_UCTS0      (0x0030)
#define MCF_GPIO_PAR_UART_PAR_URTS0_GPIO       (0x0000)
#define MCF_GPIO_PAR_UART_PAR_URTS0_PCS0       (0x0004)
#define MCF_GPIO_PAR_UART_PAR_URTS0_TOUT0      (0x0008)
#define MCF_GPIO_PAR_UART_PAR_URTS0_URTS0      (0x000C)

/* Bit definitions and macros for MCF_GPIO_PAR_FEC */
#define MCF_GPIO_PAR_FEC_PAR_FEC_MII(x)        (((x)&0x03)<<0)
#define MCF_GPIO_PAR_FEC_PAR_FEC_7W(x)         (((x)&0x03)<<2)
#define MCF_GPIO_PAR_FEC_PAR_FEC_7W_GPIO       (0x00)
#define MCF_GPIO_PAR_FEC_PAR_FEC_7W_URTS1      (0x04)
#define MCF_GPIO_PAR_FEC_PAR_FEC_7W_FEC        (0x0C)
#define MCF_GPIO_PAR_FEC_PAR_FEC_MII_GPIO      (0x00)
#define MCF_GPIO_PAR_FEC_PAR_FEC_MII_UART      (0x01)
#define MCF_GPIO_PAR_FEC_PAR_FEC_MII_FEC       (0x03)

/* Bit definitions and macros for MCF_GPIO_PAR_IRQ */
#define MCF_GPIO_PAR_IRQ_PAR_IRQ4              (0x01)

/* Bit definitions and macros for MCF_GPIO_MSCR_FLEXBUS */
#define MCF_GPIO_MSCR_FLEXBUS_MSCR_ADDRCTL(x)  (((x)&0x03)<<0)
#define MCF_GPIO_MSCR_FLEXBUS_MSCR_DLOWER(x)   (((x)&0x03)<<2)
#define MCF_GPIO_MSCR_FLEXBUS_MSCR_DUPPER(x)   (((x)&0x03)<<4)
#define MCF_GPIO_MSCR_FLEXBUS_MSCR_FBCLK(x)    (((x)&0x03)<<6)
#define MCF_GPIO_MSCR_FLEXBUS_HALF_DRIVE_1_8   (0x00)
#define MCF_GPIO_MSCR_FLEXBUS_OPEN_DRAIN       (0x01)
#define MCF_GPIO_MSCR_FLEXBUS_FULL_DRIVE_1_8   (0x02)
#define MCF_GPIO_MSCR_FLEXBUS_CMOS_OR_2_5      (0x03)

/* Bit definitions and macros for MCF_GPIO_MSCR_SDRAM */
#define MCF_GPIO_MSCR_SDRAM_MSCR_SDRAM(x)      (((x)&0x03)<<0)
#define MCF_GPIO_MSCR_SDRAM_MSCR_SDCLK(x)      (((x)&0x03)<<2)
#define MCF_GPIO_MSCR_SDRAM_MSCR_SDCLKB(x)     (((x)&0x03)<<4)
#define MCF_GPIO_MSCR_SDRAM_HALF_DRIVE_1_8     (0x00)
#define MCF_GPIO_MSCR_SDRAM_OPEN_DRAIN         (0x01)
#define MCF_GPIO_MSCR_SDRAM_FULL_DRIVE_1_8     (0x02)
#define MCF_GPIO_MSCR_SDRAM_CMOS_OR_2_5        (0x03)

/* Bit definitions and macros for MCF_GPIO_DSCR_I2C */
#define MCF_GPIO_DSCR_I2C_I2C_DSE(x)           (((x)&0x03)<<0)
#define MCF_GPIO_DSCR_I2C_DSE_10_pF            (0x00)
#define MCF_GPIO_DSCR_I2C_DSE_20_pF            (0x01)
#define MCF_GPIO_DSCR_I2C_DSE_30_pF            (0x02)
#define MCF_GPIO_DSCR_I2C_DSE_50_pF            (0x03)

/* Bit definitions and macros for MCF_GPIO_DSCR_MISC */
#define MCF_GPIO_DSCR_MISC_TIMER_DSE(x)        (((x)&0x03)<<0)
#define MCF_GPIO_DSCR_MISC_RSTOUT_DSE(x)       (((x)&0x03)<<2)
#define MCF_GPIO_DSCR_MISC_DEBUG_DSE(x)        (((x)&0x03)<<4)
#define MCF_GPIO_DSCR_MISC_DSE_10_pF           (0x00)
#define MCF_GPIO_DSCR_MISC_DSE_20_pF           (0x01)
#define MCF_GPIO_DSCR_MISC_DSE_30_pF           (0x02)
#define MCF_GPIO_DSCR_MISC_DSE_50_pF           (0x03)

/* Bit definitions and macros for MCF_GPIO_DSCR_FEC */
#define MCF_GPIO_DSCR_FEC_FEC_DSE(x)           (((x)&0x03)<<0)
#define MCF_GPIO_DSCR_FEC_DSE_10_pF            (0x00)
#define MCF_GPIO_DSCR_FEC_DSE_20_pF            (0x01)
#define MCF_GPIO_DSCR_FEC_DSE_30_pF            (0x02)
#define MCF_GPIO_DSCR_FEC_DSE_50_pF            (0x03)

/* Bit definitions and macros for MCF_GPIO_DSCR_UART */
#define MCF_GPIO_DSCR_UART_IRQ_DSE(x)          (((x)&0x03)<<0)
#define MCF_GPIO_DSCR_UART_UART0_DSE(x)        (((x)&0x03)<<2)
#define MCF_GPIO_DSCR_UART_UART1_DSE(x)        (((x)&0x03)<<4)
#define MCF_GPIO_DSCR_UART_DSE_10_pF           (0x00)
#define MCF_GPIO_DSCR_UART_DSE_20_pF           (0x01)
#define MCF_GPIO_DSCR_UART_DSE_30_pF           (0x02)
#define MCF_GPIO_DSCR_UART_DSE_50_pF           (0x03)

/* Bit definitions and macros for MCF_GPIO_DSCR_QSPI */
#define MCF_GPIO_DSCR_QSPI_QSPI_DSE(x)         (((x)&0x03)<<0)
#define MCF_GPIO_DSCR_QSPI_DSE_10_pF           (0x00)
#define MCF_GPIO_DSCR_QSPI_DSE_20_pF           (0x01)
#define MCF_GPIO_DSCR_QSPI_DSE_30_pF           (0x02)
#define MCF_GPIO_DSCR_QSPI_DSE_50_pF           (0x03)

/*
 *
 * Interrupt Controller (INTC) - Chapter 14
 *
 */

#define MCF_INTC_BASE (0xFC048000)

#include <hwif/intCtlr/mcfIntc.h>

/********************************************************************/

/*
 *
 * Edge Port Module (EPORT) - Chapter 15
 *
 */

/* Register read/write macros */
#define MCF_EPORT_EPPAR          (CAST_MCF_VOLPTR( UINT16 )(0xFC088000))
#define MCF_EPORT_EPDDR          (CAST_MCF_VOLPTR( UINT8 )(0xFC088002))
#define MCF_EPORT_EPIER          (CAST_MCF_VOLPTR( UINT8 )(0xFC088003))
#define MCF_EPORT_EPDR           (CAST_MCF_VOLPTR( UINT8 )(0xFC088004))
#define MCF_EPORT_EPPDR          (CAST_MCF_VOLPTR( UINT8 )(0xFC088005))
#define MCF_EPORT_EPFR           (CAST_MCF_VOLPTR( UINT8 )(0xFC088006))

/* Bit definitions and macros for MCF_EPORT_EPPAR */
#define MCF_EPORT_EPPAR_EPPA1(x)       (((x)&0x0003)<<2)
#define MCF_EPORT_EPPAR_EPPA2(x)       (((x)&0x0003)<<4)
#define MCF_EPORT_EPPAR_EPPA3(x)       (((x)&0x0003)<<6)
#define MCF_EPORT_EPPAR_EPPA4(x)       (((x)&0x0003)<<8)
#define MCF_EPORT_EPPAR_EPPA5(x)       (((x)&0x0003)<<10)
#define MCF_EPORT_EPPAR_EPPA6(x)       (((x)&0x0003)<<12)
#define MCF_EPORT_EPPAR_EPPA7(x)       (((x)&0x0003)<<14)
#define MCF_EPORT_EPPAR_LEVEL          (0)
#define MCF_EPORT_EPPAR_RISING         (1)
#define MCF_EPORT_EPPAR_FALLING        (2)
#define MCF_EPORT_EPPAR_BOTH           (3)
#define MCF_EPORT_EPPAR_EPPA7_LEVEL    (0x0000)
#define MCF_EPORT_EPPAR_EPPA7_RISING   (0x4000)
#define MCF_EPORT_EPPAR_EPPA7_FALLING  (0x8000)
#define MCF_EPORT_EPPAR_EPPA7_BOTH     (0xC000)
#define MCF_EPORT_EPPAR_EPPA6_LEVEL    (0x0000)
#define MCF_EPORT_EPPAR_EPPA6_RISING   (0x1000)
#define MCF_EPORT_EPPAR_EPPA6_FALLING  (0x2000)
#define MCF_EPORT_EPPAR_EPPA6_BOTH     (0x3000)
#define MCF_EPORT_EPPAR_EPPA5_LEVEL    (0x0000)
#define MCF_EPORT_EPPAR_EPPA5_RISING   (0x0400)
#define MCF_EPORT_EPPAR_EPPA5_FALLING  (0x0800)
#define MCF_EPORT_EPPAR_EPPA5_BOTH     (0x0C00)
#define MCF_EPORT_EPPAR_EPPA4_LEVEL    (0x0000)
#define MCF_EPORT_EPPAR_EPPA4_RISING   (0x0100)
#define MCF_EPORT_EPPAR_EPPA4_FALLING  (0x0200)
#define MCF_EPORT_EPPAR_EPPA4_BOTH     (0x0300)
#define MCF_EPORT_EPPAR_EPPA3_LEVEL    (0x0000)
#define MCF_EPORT_EPPAR_EPPA3_RISING   (0x0040)
#define MCF_EPORT_EPPAR_EPPA3_FALLING  (0x0080)
#define MCF_EPORT_EPPAR_EPPA3_BOTH     (0x00C0)
#define MCF_EPORT_EPPAR_EPPA2_LEVEL    (0x0000)
#define MCF_EPORT_EPPAR_EPPA2_RISING   (0x0010)
#define MCF_EPORT_EPPAR_EPPA2_FALLING  (0x0020)
#define MCF_EPORT_EPPAR_EPPA2_BOTH     (0x0030)
#define MCF_EPORT_EPPAR_EPPA1_LEVEL    (0x0000)
#define MCF_EPORT_EPPAR_EPPA1_RISING   (0x0004)
#define MCF_EPORT_EPPAR_EPPA1_FALLING  (0x0008)
#define MCF_EPORT_EPPAR_EPPA1_BOTH     (0x000C)

/* Bit definitions and macros for MCF_EPORT_EPDDR */
#define MCF_EPORT_EPDDR_EPDD1          (0x02)
#define MCF_EPORT_EPDDR_EPDD2          (0x04)
#define MCF_EPORT_EPDDR_EPDD3          (0x08)
#define MCF_EPORT_EPDDR_EPDD4          (0x10)
#define MCF_EPORT_EPDDR_EPDD5          (0x20)
#define MCF_EPORT_EPDDR_EPDD6          (0x40)
#define MCF_EPORT_EPDDR_EPDD7          (0x80)

/* Bit definitions and macros for MCF_EPORT_EPIER */
#define MCF_EPORT_EPIER_EPIE1          (0x02)
#define MCF_EPORT_EPIER_EPIE2          (0x04)
#define MCF_EPORT_EPIER_EPIE3          (0x08)
#define MCF_EPORT_EPIER_EPIE4          (0x10)
#define MCF_EPORT_EPIER_EPIE5          (0x20)
#define MCF_EPORT_EPIER_EPIE6          (0x40)
#define MCF_EPORT_EPIER_EPIE7          (0x80)

/* Bit definitions and macros for MCF_EPORT_EPDR */
#define MCF_EPORT_EPDR_EPD1            (0x02)
#define MCF_EPORT_EPDR_EPD2            (0x04)
#define MCF_EPORT_EPDR_EPD3            (0x08)
#define MCF_EPORT_EPDR_EPD4            (0x10)
#define MCF_EPORT_EPDR_EPD5            (0x20)
#define MCF_EPORT_EPDR_EPD6            (0x40)
#define MCF_EPORT_EPDR_EPD7            (0x80)

/* Bit definitions and macros for MCF_EPORT_EPPDR */
#define MCF_EPORT_EPPDR_EPPD1          (0x02)
#define MCF_EPORT_EPPDR_EPPD2          (0x04)
#define MCF_EPORT_EPPDR_EPPD3          (0x08)
#define MCF_EPORT_EPPDR_EPPD4          (0x10)
#define MCF_EPORT_EPPDR_EPPD5          (0x20)
#define MCF_EPORT_EPPDR_EPPD6          (0x40)
#define MCF_EPORT_EPPDR_EPPD7          (0x80)

/* Bit definitions and macros for MCF_EPORT_EPFR */
#define MCF_EPORT_EPFR_EPF1            (0x02)
#define MCF_EPORT_EPFR_EPF2            (0x04)
#define MCF_EPORT_EPFR_EPF3            (0x08)
#define MCF_EPORT_EPFR_EPF4            (0x10)
#define MCF_EPORT_EPFR_EPF5            (0x20)
#define MCF_EPORT_EPFR_EPF6            (0x40)
#define MCF_EPORT_EPFR_EPF7            (0x80)

/*
 *
 * Enhanced DMA (EDMA) - Chapter 16
 *
 */
 
#define MCF_EDMA_BASE           (0xFC044000)
#define MCF_EDMA_NUM_CHANNELS	   1

#include <hwif/dmaCtlr/mcfEdma.h>


/*
 *
 * FlexBus Chip Selects (FBCS) - Chapter 17
 *
 */

/* Register read/write macros */
#define MCF_FBCS0_CSAR     0xFC008000
#define MCF_FBCS0_CSMR     0xFC008004
#define MCF_FBCS0_CSCR     0xFC008008
#define MCF_FBCS1_CSAR     (CAST_MCF_VOL(UINT32)(0xFC00800C))
#define MCF_FBCS1_CSMR     (CAST_MCF_VOL(UINT32)(0xFC008010))
#define MCF_FBCS1_CSCR     (CAST_MCF_VOL(UINT32)(0xFC008014))
#define MCF_FBCS2_CSAR     (CAST_MCF_VOL(UINT32)(0xFC008018))
#define MCF_FBCS2_CSMR     (CAST_MCF_VOL(UINT32)(0xFC00801C))
#define MCF_FBCS2_CSCR     (CAST_MCF_VOL(UINT32)(0xFC008020))
#define MCF_FBCS3_CSAR     (CAST_MCF_VOL(UINT32)(0xFC008024))
#define MCF_FBCS3_CSMR     (CAST_MCF_VOL(UINT32)(0xFC008028))
#define MCF_FBCS3_CSCR     (CAST_MCF_VOL(UINT32)(0xFC00802C))
#define MCF_FBCS4_CSAR     (CAST_MCF_VOL(UINT32)(0xFC008030))
#define MCF_FBCS4_CSMR     (CAST_MCF_VOL(UINT32)(0xFC008034))
#define MCF_FBCS4_CSCR     (CAST_MCF_VOL(UINT32)(0xFC008038))
#define MCF_FBCS5_CSAR     (CAST_MCF_VOL(UINT32)(0xFC00803C))
#define MCF_FBCS5_CSMR     (CAST_MCF_VOL(UINT32)(0xFC008040))
#define MCF_FBCS5_CSCR     (CAST_MCF_VOL(UINT32)(0xFC008044))
#define MCF_FBCS_CSAR(x)   (CAST_MCF_VOL(UINT32)(0xFC008000+((x)*0x00C)))
#define MCF_FBCS_CSMR(x)   (CAST_MCF_VOL(UINT32)(0xFC008004+((x)*0x00C)))
#define MCF_FBCS_CSCR(x)   (CAST_MCF_VOL(UINT32)(0xFC008008+((x)*0x00C)))

/* Bit definitions and macros for MCF_FBCS_CSAR */
#define MCF_FBCS_CSAR_BA(x)	   ((x)&0xFFFF0000)

/* Bit definitions and macros for MCF_FBCS_CSMR */
#define MCF_FBCS_CSMR_V             (0x00000001)
#define MCF_FBCS_CSMR_WP	    (0x00000100)
#define MCF_FBCS_CSMR_BAM(x)	    (((x)&0x0000FFFF)<<16)
#define MCF_FBCS_CSMR_BAM_4G	    (0xFFFF0000)
#define MCF_FBCS_CSMR_BAM_2G	    (0x7FFF0000)
#define MCF_FBCS_CSMR_BAM_1G	    (0x3FFF0000)
#define MCF_FBCS_CSMR_BAM_1024M     (0x3FFF0000)
#define MCF_FBCS_CSMR_BAM_512M      (0x1FFF0000)
#define MCF_FBCS_CSMR_BAM_256M      (0x0FFF0000)
#define MCF_FBCS_CSMR_BAM_128M      (0x07FF0000)
#define MCF_FBCS_CSMR_BAM_64M	    (0x03FF0000)
#define MCF_FBCS_CSMR_BAM_32M	    (0x01FF0000)
#define MCF_FBCS_CSMR_BAM_16M	    (0x00FF0000)
#define MCF_FBCS_CSMR_BAM_8M	    (0x007F0000)
#define MCF_FBCS_CSMR_BAM_4M	    (0x003F0000)
#define MCF_FBCS_CSMR_BAM_2M	    (0x001F0000)
#define MCF_FBCS_CSMR_BAM_1M	    (0x000F0000)
#define MCF_FBCS_CSMR_BAM_1024K     (0x000F0000)
#define MCF_FBCS_CSMR_BAM_512K      (0x00070000)
#define MCF_FBCS_CSMR_BAM_256K      (0x00030000)
#define MCF_FBCS_CSMR_BAM_128K      (0x00010000)
#define MCF_FBCS_CSMR_BAM_64K	    (0x00000000)

/* Bit definitions and macros for MCF_FBCS_CSCR */
#define MCF_FBCS_CSCR_BSTW	    (0x00000008)
#define MCF_FBCS_CSCR_BSTR	    (0x00000010)
#define MCF_FBCS_CSCR_BEM	    (0x00000020)
#define MCF_FBCS_CSCR_PS(x)	    (((x)&0x00000003)<<6)
#define MCF_FBCS_CSCR_AA	    (0x00000100)
#define MCF_FBCS_CSCR_SBM	    (0x00000200)
#define MCF_FBCS_CSCR_WS(x)	    (((x)&0x0000003F)<<10)
#define MCF_FBCS_CSCR_WRAH(x)	    (((x)&0x00000003)<<16)
#define MCF_FBCS_CSCR_RDAH(x)	    (((x)&0x00000003)<<18)
#define MCF_FBCS_CSCR_ASET(x)	    (((x)&0x00000003)<<20)
#define MCF_FBCS_CSCR_SWSEN	    (0x00800000)
#define MCF_FBCS_CSCR_SWS(x)	    (((x)&0x0000003F)<<26)
#define MCF_FBCS_CSCR_PS_8	    (0x00000040)
#define MCF_FBCS_CSCR_PS_16	    (0x00000080)
#define MCF_FBCS_CSCR_PS_32	    (0x00000000)

/*
 *
 * SDRAM Controller (SDRAMC) - Chapter 18
 *
 */

/* Register read/write macros */
#define MCF_SDRAMC_SDMR	            0xFC0A8000
#define MCF_SDRAMC_SDCR	            0xFC0A8004
#define MCF_SDRAMC_SDCFG1	    0xFC0A8008
#define MCF_SDRAMC_SDCFG2	    0xFC0A800C
#define MCF_SDRAMC_SDDS	            0xFC0A8100
#define MCF_SDRAMC_SDCS0	    0xFC0A8110
#define MCF_SDRAMC_SDCS1	    0xFC0A8114
#define MCF_SDRAMC_SDCS2	    0xFC0A8118
#define MCF_SDRAMC_SDCS3	    0xFC0A811C
#define MCF_SDRAMC_SDCS(x)	    (0xFC0A8110+((x)*0x004)))

/* Bit definitions and macros for MCF_SDRAMC_SDMR */
#define MCF_SDRAMC_SDMR_CMD	    (0x00010000)
#define MCF_SDRAMC_SDMR_AD(x)	    (((x)&0x00000FFF)<<18)
#define MCF_SDRAMC_SDMR_BNKAD(x)    (((x)&0x00000003)<<30)
#define MCF_SDRAMC_SDMR_BNKAD_LMR   (0x00000000)
#define MCF_SDRAMC_SDMR_BNKAD_LEMR  (0x40000000)

/* Bit definitions and macros for MCF_SDRAMC_SDCR */
#define MCF_SDRAMC_SDCR_IPALL	    (0x00000002)
#define MCF_SDRAMC_SDCR_IREF	    (0x00000004)
#define MCF_SDRAMC_SDCR_DQS_OE(x)   (((x)&0x0000000F)<<8)
#define MCF_SDRAMC_SDCR_PS	    (0x00002000)
#define MCF_SDRAMC_SDCR_RCNT(x)	    (((x)&0x0000003F)<<16)
#define MCF_SDRAMC_SDCR_OE_RULE     (0x00400000)
#define MCF_SDRAMC_SDCR_MUX(x)	    (((x)&0x00000003)<<24)
#define MCF_SDRAMC_SDCR_REF	    (0x10000000)
#define MCF_SDRAMC_SDCR_DDR	    (0x20000000)
#define MCF_SDRAMC_SDCR_CKE	    (0x40000000)
#define MCF_SDRAMC_SDCR_MODE_EN	    (0x80000000)
#define MCF_SDRAMC_SDCR_PS_16	    (0x00002000)
#define MCF_SDRAMC_SDCR_PS_32	    (0x00000000)

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
 * Watchdog Timer Modules (WTM) - Chapter 20
 *
 */

/* Register read/write macros */
#define MCF_WTM_WCR	 (CAST_MCF_VOL(UINT16)(0xFC08C000))
#define MCF_WTM_WMR	 (CAST_MCF_VOL(UINT16)(0xFC08C002))
#define MCF_WTM_WCNTR	 (CAST_MCF_VOL(UINT16)(0xFC08C004))
#define MCF_WTM_WSR	 (CAST_MCF_VOL(UINT16)(0xFC08C006))

/* Bit definitions and macros for MCF_WTM_WCR */
#define MCF_WTM_WCR_EN       (0x0001)
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
 * Programmable Interrupt Timer Modules (PIT) - Chapter 21
 *
 */
 
#define MCF_PIT0_BASE   (0xFC080000)
#define MCF_PIT1_BASE   (0xFC084000)
    
#include <hwif/timer/mcfPit.h>

/*
 *
 * DMA Timers (DTIM) - Chapter 22
 *
 */

/* Register read/write macros */
#define MCF_DTIM0_DTMR     (CAST_MCF_VOLPTR( UINT16 )(0xFC070000))
#define MCF_DTIM0_DTXMR    (CAST_MCF_VOLPTR( UINT8 )(0xFC070002))
#define MCF_DTIM0_DTER     (CAST_MCF_VOLPTR( UINT8 )(0xFC070003))
#define MCF_DTIM0_DTRR     (CAST_MCF_VOLPTR( UINT32 )(0xFC070004))
#define MCF_DTIM0_DTCR     (CAST_MCF_VOLPTR( UINT32 )(0xFC070008))
#define MCF_DTIM0_DTCN     (CAST_MCF_VOLPTR( UINT32 )(0xFC07000C))
#define MCF_DTIM1_DTMR     (CAST_MCF_VOLPTR( UINT16 )(0xFC074000))
#define MCF_DTIM1_DTXMR    (CAST_MCF_VOLPTR( UINT8 )(0xFC074002))
#define MCF_DTIM1_DTER     (CAST_MCF_VOLPTR( UINT8 )(0xFC074003))
#define MCF_DTIM1_DTRR     (CAST_MCF_VOLPTR( UINT32 )(0xFC074004))
#define MCF_DTIM1_DTCR     (CAST_MCF_VOLPTR( UINT32 )(0xFC074008))
#define MCF_DTIM1_DTCN     (CAST_MCF_VOLPTR( UINT32 )(0xFC07400C))
#define MCF_DTIM2_DTMR     (CAST_MCF_VOLPTR( UINT16 )(0xFC078000))
#define MCF_DTIM2_DTXMR    (CAST_MCF_VOLPTR( UINT8 )(0xFC078002))
#define MCF_DTIM2_DTER     (CAST_MCF_VOLPTR( UINT8 )(0xFC078003))
#define MCF_DTIM2_DTRR     (CAST_MCF_VOLPTR( UINT32 )(0xFC078004))
#define MCF_DTIM2_DTCR     (CAST_MCF_VOLPTR( UINT32 )(0xFC078008))
#define MCF_DTIM2_DTCN     (CAST_MCF_VOLPTR( UINT32 )(0xFC07800C))
#define MCF_DTIM3_DTMR     (CAST_MCF_VOLPTR( UINT16 )(0xFC07C000))
#define MCF_DTIM3_DTXMR    (CAST_MCF_VOLPTR( UINT8 )(0xFC07C002))
#define MCF_DTIM3_DTER     (CAST_MCF_VOLPTR( UINT8 )(0xFC07C003))
#define MCF_DTIM3_DTRR     (CAST_MCF_VOLPTR( UINT32 )(0xFC07C004))
#define MCF_DTIM3_DTCR     (CAST_MCF_VOLPTR( UINT32 )(0xFC07C008))
#define MCF_DTIM3_DTCN     (CAST_MCF_VOLPTR( UINT32 )(0xFC07C00C))
#define MCF_DTIM_DTMR(x)   (CAST_MCF_VOLPTR( UINT16 )(0xFC070000+((x)*0x4000)))
#define MCF_DTIM_DTXMR(x)  (CAST_MCF_VOLPTR( UINT8 )(0xFC070002+((x)*0x4000)))
#define MCF_DTIM_DTER(x)   (CAST_MCF_VOLPTR( UINT8 )(0xFC070003+((x)*0x4000)))
#define MCF_DTIM_DTRR(x)   (CAST_MCF_VOLPTR( UINT32 )(0xFC070004+((x)*0x4000)))
#define MCF_DTIM_DTCR(x)   (CAST_MCF_VOLPTR( UINT32 )(0xFC070008+((x)*0x4000)))
#define MCF_DTIM_DTCN(x)   (CAST_MCF_VOLPTR( UINT32 )(0xFC07000C+((x)*0x4000)))

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
#define MCF_DTIM_DTMR_CLK_DTIN     (0x0006)
#define MCF_DTIM_DTMR_CLK_DIV16    (0x0004)
#define MCF_DTIM_DTMR_CLK_DIV1     (0x0002)
#define MCF_DTIM_DTMR_CLK_STOP     (0x0000)

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
 * Queued Serial Peripheral Interface (QSPI) - Chapter 23
 *
 */

#define MCF_QSPI_BASE (0xFC05C000)

#include <hwif/spi/mcfQspi.h>

/*
 *
 * Universal Asynchronous Receiver Transmitter (UART) - Chapter 24
 *
 */
#define MCF_UART_BASE0      0xFC060000
#define MCF_UART_BASE1      0xFC064000

#include <hwif/sio/mcfUart.h>

/*
 *
 * I2C Module (I2C) - Chapter 25
 *
 */

#define MCF_I2C_BASE      (0xFC058000)
  
#include <hwif/i2c/mcfI2c.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif /* __INCMCF5208h */

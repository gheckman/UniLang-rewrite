/* fsl_KinetisMem.h - Freescale Kinetis memory subsystem header file */

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
01a,30jul13,yjw  Created
*/

/*
DESCRIPTION
This file contains register definitions specifc to the freescale Kinetis
flash and SDRAM memory interface registers.

SEE ALSO:
\tb K70 Sub-Family Reference Manual
*/

#ifndef __INCfsl_KinetisMemh
#define __INCfsl_KinetisMemh

#ifdef __cplusplus
extern "C" {
#endif

/* Flash Memory Module (FTFE) register map */

struct kinetis_ftfe_regs {
	UINT8 fstat;	/* Flash Status Register */
	UINT8 fcnfg;	/* Flash Configuration Register */
	UINT8 fsec;	/* Flash Security Register */
	UINT8 fopt;	/* Flash Option Register */

	/* Flash Common Command Object Registers (3:0) */
	UINT8 fccob3;
	UINT8 fccob2;
	UINT8 fccob1;
	UINT8 fccob0;

	/* Flash Common Command Object Registers (7:4) */
	UINT8 fccob7;
	UINT8 fccob6;
	UINT8 fccob5;
	UINT8 fccob4;

	/* Flash Common Command Object Registers (0xB:8) */
	UINT8 fccobB;
	UINT8 fccobA;
	UINT8 fccob9;
	UINT8 fccob8;
};

/* FTFE registers base */

#define KINETIS_AIPS0PERIPH_BASE 0x40000000
#define KINETIS_FTFE_BASE		(KINETIS_AIPS0PERIPH_BASE + 0x00020000)
#define KINETIS_FTFE			((volatile struct kinetis_ftfe_regs *)KINETIS_FTFE_BASE)

/* Flash Status Register (FSTAT)*/

#define KINETIS_FTFE_FSTAT_CCIF             0x80
#define KINETIS_FTFE_FSTAT_RDCOLERR         0x40
#define KINETIS_FTFE_FSTAT_ACCERR           0x20
#define KINETIS_FTFE_FSTAT_FPVIOL           0x10
#define KINETIS_FTFE_FSTAT_MGSTAT0          0x01

/* Flash configuration register (FCNFG)*/

#define KINETIS_FTFE_FCNFG_CCIE             0x80
#define KINETIS_FTFE_FCNFG_RDCOLLIE         0x40
#define KINETIS_FTFE_FCNFG_ERSAREQ          0x20
#define KINETIS_FTFE_FCNFG_ERSSUSP          0x10
#define KINETIS_FTFE_FCNFG_RAMRDY           0x02
#define KINETIS_FTFE_FCNFG_EEERDY           0x01

/* Flash security register (FSEC) */

#define KINETIS_FTFE_FSEC_KEYEN             0xC0
#define KINETIS_FTFE_FSEC_FSLACC            0x0C
#define KINETIS_FTFE_FSEC_SEC               0x03

/* Flash operation commands */

#define KINETIS_FTFE_VERIFY_BLOCK               0x00
#define KINETIS_FTFE_VERIFY_SECTION             0x01
#define KINETIS_FTFE_PROGRAM_CHECK              0x02
#define KINETIS_FTFE_READ_RESOURCE              0x03
#define KINETIS_FTFE_PROGRAM_LONGWORD           0x06
#define KINETIS_FTFE_PROGRAM_PHRASE             0x07
#define KINETIS_FTFE_ERASE_BLOCK                0x08
#define KINETIS_FTFE_ERASE_SECTOR               0x09
#define KINETIS_FTFE_PROGRAM_SECTION            0x0B
#define KINETIS_FTFE_VERIFY_ALL_BLOCK           0x40
#define KINETIS_FTFE_READ_ONCE                  0x41
#define KINETIS_FTFE_PROGRAM_ONCE               0x43
#define KINETIS_FTFE_ERASE_ALL_BLOCK            0x44
#define KINETIS_FTFE_SECURITY_BY_PASS           0x45
#define KINETIS_FTFE_PFLASH_SWAP                0x46
#define KINETIS_FTFE_PROGRAM_PARTITION          0x80
#define KINETIS_FTFE_SET_EERAM                  0x81

/* Flash Memory Controller (FMC) register map */

struct kinetis_fmc_regs {
	UINT32 pfapr;	/* Flash Access Protection Register */
	UINT32 pfb01cr;	/* Flash Bank 01 Control Register */
	UINT32 pfb23cr;	/* Flash Bank 23 Control Register */
};

/* FMC registers base */
#define KINETIS_FMC_BASE	(KINETIS_AIPS0PERIPH_BASE + 0x0001F000)
#define KINETIS_FMC			((volatile struct kinetis_fmc_regs *)KINETIS_FMC_BASE)

/* PFAPR Bit Fields */

#define FMC_PFAPR_M0AP_MASK                      0x00000003
#define FMC_PFAPR_M1AP_MASK                      0x0000000C
#define FMC_PFAPR_M2AP_MASK                      0x00000030
#define FMC_PFAPR_M3AP_MASK                      0x000000C0
#define FMC_PFAPR_M4AP_MASK                      0x00000300
#define FMC_PFAPR_M5AP_MASK                      0x00000C00
#define FMC_PFAPR_M6AP_MASK                      0x00003000
#define FMC_PFAPR_M0PFD_MASK                     0x00010000
#define FMC_PFAPR_M1PFD_MASK                     0x00020000
#define FMC_PFAPR_M2PFD_MASK                     0x00040000
#define FMC_PFAPR_M3PFD_MASK                     0x00080000
#define FMC_PFAPR_M4PFD_MASK                     0x00100000
#define FMC_PFAPR_M5PFD_MASK                     0x00200000
#define FMC_PFAPR_M6PFD_MASK                     0x00400000
#define FMC_PFAPR_M7PFD_MASK                     0x00800000

/* PFB01CR Bit Fields */

#define FMC_PFB01CR_B01SEBE_MASK                 0x00000001
#define FMC_PFB01CR_B01IPE_MASK                  0x00000002
#define FMC_PFB01CR_B01DPE_MASK                  0x00000004
#define FMC_PFB01CR_B01ICE_MASK                  0x00000008
#define FMC_PFB01CR_B01DCE_MASK                  0x00000010
#define FMC_PFB01CR_CRC_MASK                     0x000000E0
#define FMC_PFB01CR_B01MW_MASK                   0x00060000
#define FMC_PFB01CR_S_B_INV_MASK                 0x00080000
#define FMC_PFB01CR_CINV_WAY_MASK                0x00F00000
#define FMC_PFB01CR_CLCK_WAY_MASK                0x0F000000
#define FMC_PFB01CR_B01RWSC_MASK                 0xF0000000

/* PFB23CR Bit Fields */

#define FMC_PFB23CR_B23SEBE_MASK                 0x00000001
#define FMC_PFB23CR_B23IPE_MASK                  0x00000002
#define FMC_PFB23CR_B23DPE_MASK                  0x00000004
#define FMC_PFB23CR_B23ICE_MASK                  0x00000008
#define FMC_PFB23CR_B23DCE_MASK                  0x00000010
#define FMC_PFB23CR_B23MW_MASK                   0x00060000
#define FMC_PFB23CR_B23RWSC_MASK                 0xF0000000

/* TAGVD Bit Fields */

#define FMC_TAGVD_valid_MASK                     0x00000001
#define FMC_TAGVD_tag_MASK                       0x000FFFC0

/* DATA_UM Bit Fields */

#define FMC_DATA_UM_data_MASK                    0xFFFFFFFF

/* DATA_MU Bit Fields */

#define FMC_DATA_MU_data_MASK                    0xFFFFFFFF

/* DATA_ML Bit Fields */

#define FMC_DATA_ML_data_MASK                    0xFFFFFFFF

/* DATA_LM Bit Fields */

#define FMC_DATA_LM_data_MASK                    0xFFFFFFFF

/* Pointer to the beginning of flash */

#define KINETIS_NVM_PTR	((UINT8 *)0x0)

/* Address of the flash programming acceleration RAM */

#define FLASH_PROG_ACCEL_BASE	0x14000000
#define FLASH_PROG_ACCEL_PTR	((UINT8 *)FLASH_PROG_ACCEL_BASE)

/*
 * Size in bytes of the flash programming acceleration RAM
 */

#define FLASH_PROG_ACCEL_SIZE	(16 * 1024)

/*
 * Size of the bottom half of the flash programming acceleration RAM
 * that may be used for flash programming.
 */
 
#define FLASH_PROG_ACCEL_HALF	(FLASH_PROG_ACCEL_SIZE / 2)

/* Size of a sector in the MCU internal flash is 4 Kbytes (K70) */

#define FLASH_SECTOR_SIZE	(4 * 1024)

/*
 * Offset of the byte in flash that loads into the FSEC register on reset
 */
#define KINETIS_FLASH_FSEC_OFFSET	0x40C

#define CONFIG_KINETIS_DDR
#define CONFIG_KINETIS_DDR_SYNC		/* DDR synchronous mode */

/*
 * DDR1/2/LP SDRAM Memory Controller (DDRMC) register map
 */
struct kinetis_ddr_regs {
	UINT32 cr[64];	/* Control Registers */
	UINT32 rsv0[32];	/* Reserved */
	UINT32 rcr;	/* RCR Control Register */
	UINT32 rsv1[10];	/* Reserved */
	UINT32 pad_ctrl;	/* I/O Pad Control Register */
};

/*
 * DDRMC registers base
 */
#define KINETIS_DDR_BASE		(KINETIS_AIPS1PERIPH_BASE + 0x0002E000)
#define KINETIS_DDR			((volatile struct kinetis_ddr_regs *) \
					KINETIS_DDR_BASE)

/* DDR size is 128 Mbytes */
#define KINETIS_MCM_CR_DDRSIZE_128MB	(1 << 20)

/*
 * DRAM Port 0 configuration
 */
#define KINETIS_DDR_RP0		1
#define KINETIS_DDR_WP0		1
#define KINETIS_DDR_P0RDCNT	32
#define KINETIS_DDR_P0WRCNT	32
#define KINETIS_DDR_P0ORD	1
#define KINETIS_DDR_P0PRI0	3
#define KINETIS_DDR_P0PRI1	3
#define KINETIS_DDR_P0PRI2	3
#define KINETIS_DDR_P0PRI3	3
#define KINETIS_DDR_P0PRIRLX	100

/*
 * DRAM Port 1 configuration
 */
#define KINETIS_DDR_RP1		1
#define KINETIS_DDR_WP1		1
#define KINETIS_DDR_P1RDCNT	32
#define KINETIS_DDR_P1WRCNT	32
#define KINETIS_DDR_P1ORD	1
#define KINETIS_DDR_P1PRI0	2
#define KINETIS_DDR_P1PRI1	2
#define KINETIS_DDR_P1PRI2	2
#define KINETIS_DDR_P1PRI3	2
#define KINETIS_DDR_P1PRIRLX	100

/*
 * DRAM Port 2 configuration
 */
#define KINETIS_DDR_RP2		1
#define KINETIS_DDR_WP2		1
#define KINETIS_DDR_P2RDCNT	32
#define KINETIS_DDR_P2WRCNT	32
#define KINETIS_DDR_P2ORD	2
#define KINETIS_DDR_P2PRI0	1
#define KINETIS_DDR_P2PRI1	1
#define KINETIS_DDR_P2PRI3	1
#define KINETIS_DDR_P2PRI2	1
#define KINETIS_DDR_P2PRIRLX	100

/*
 * Port types: synchronous, asynchronous.
 * See DDR registers bit fields: CR40[P0TYP], CR42[P1TYP], CR44[P2TYP].
 */
#define KINETIS_DDR_PORT_ASYNC	0
#define KINETIS_DDR_PORT_SYNC	3

/*
 * Actual port types
 */
#ifdef CONFIG_KINETIS_DDR_SYNC
#define KINETIS_DDR_P0TYP	KINETIS_DDR_PORT_SYNC
#define KINETIS_DDR_P1TYP	KINETIS_DDR_PORT_SYNC
#define KINETIS_DDR_P2TYP	KINETIS_DDR_PORT_SYNC
#else
#define KINETIS_DDR_P0TYP	KINETIS_DDR_PORT_ASYNC
#define KINETIS_DDR_P1TYP	KINETIS_DDR_PORT_ASYNC
#define KINETIS_DDR_P2TYP	KINETIS_DDR_PORT_ASYNC
#endif /* CONFIG_KINETIS_DDR_SYNC */

/*
 * Other SDRAM configuration options
 */
#define KINETIS_DDR_INITAREF		2
#define KINETIS_DDR_TINIT		49
#define KINETIS_DDR_TCCD		2
#define KINETIS_DDR_WRLAT		2
#define KINETIS_DDR_LATGATE	        5
#define KINETIS_DDR_LATLIN		6
#define KINETIS_DDR_TRASMIN	        6
#define KINETIS_DDR_TRC			9
#define KINETIS_DDR_TRRD		2
#define KINETIS_DDR_TBINT		2
#define KINETIS_DDR_TMRD		2
#define KINETIS_DDR_TRTP		2
#define KINETIS_DDR_TRP			3
#define KINETIS_DDR_TWTR		2
#define KINETIS_DDR_TRASMAX		10500	/* 70000 ns */
#define KINETIS_DDR_TMOD		2
#define KINETIS_DDR_TCKESR		3
#define KINETIS_DDR_CLKPW		3
#define KINETIS_DDR_TDAL		5
#define KINETIS_DDR_TWR			3
#define KINETIS_DDR_TRASDI		2
#define KINETIS_DDR_TDLL		200
#define KINETIS_DDR_TRPAB		3
#define KINETIS_DDR_TCPD		50
#define KINETIS_DDR_TFAW		7
#define KINETIS_DDR_TREF		1170	/* 7.8 us */
#define KINETIS_DDR_TRFC		50
#define KINETIS_DDR_TXSR		200
#define KINETIS_DDR_TPDEX		2
#define KINETIS_DDR_TXSNR		50
#define KINETIS_DDR_CKSRX		3
#define KINETIS_DDR_CKSRE		3
#define KINETIS_DDR_APREBIT		10
#define KINETIS_DDR_COLSIZ		1
#define KINETIS_DDR_ADDPINS		2
#define KINETIS_DDR_CMDAGE		255
#define KINETIS_DDR_AGECNT		255
#define KINETIS_DDR_R2WSAME		2
#define KINETIS_DDR_RDDTENBAS		2
#define KINETIS_DDR_PHYRDLAT		6
#define KINETIS_DDR_PYWRLTBS		2
#define KINETIS_DDR_CTRLUPDMX		968
#define KINETIS_DDR_PHYUPDTY1		968
#define KINETIS_DDR_PHYUPDTY0		968
#define KINETIS_DDR_PHYUPDTY3		968
#define KINETIS_DDR_PHYUPDTY2		968
#define KINETIS_DDR_WRLATADJ		2
#define KINETIS_DDR_RDLATADJ		3
#define KINETIS_DDR_PHYUPDRESP		968
#define KINETIS_DDR_CLKENDLY		1
#define KINETIS_DDR_CMDDLY		2

/*
 * Micron MT47H[...] DDR2 SDRAM memory chip configuration registers
 */
/*
 * Mode Register (MR)
 */
#define MT47H_MR_WR_BITS	9
/* CAS Latency (CL) */
#define MT47H_MR_CL_BITS	4
/* Burst Length */
#define MT47H_MR_BL_BITS	0
/* Burst Length = 4 */
#define MT47H_MR_BL_4		(2 << MT47H_MR_BL_BITS)
/*
 * Extended Mode Register
 */
/* Enables the 75 Ohms resistor */
#define MT47H_EMR_RTT_75_MSK	(1 << 2)
/* Enables the 150 Ohms resistor */
#define MT47H_EMR_RTT_150_MSK	(1 << 6)

/*
 * SDRAM configuration options
 */
/* Write Recovery (WR) = 2 */
#define SDRAM_MR_WR	2
/* CAS Latency (CL) */
#define SDRAM_MR_CL	3
/* Burst Length */
#define SDRAM_MR_BL	MT47H_MR_BL_4

/*
 * DDR2 memory chip 16-bit registers
 */
/* Mode Register (MR) */
#define KINETIS_DDR_MR0DAT0 \
	(((SDRAM_MR_WR - 1) << MT47H_MR_WR_BITS) | \
	(SDRAM_MR_CL << MT47H_MR_CL_BITS) | \
	SDRAM_MR_BL)
/* Extended Mode Register (EMR) */
#define KINETIS_DDR_MR1DAT0		MT47H_EMR_RTT_75_MSK
/* Extended Mode Register 2 (EMR2) */
#define KINETIS_DDR_MR2DAT0		0
/* Extended Mode Register 3 (EMR3) */
#define KINETIS_DDR_MR3DAT0		0

/*
 * DDR Control Register 0 (DDR_CR00)
 */

/* DDR2 */
#define KINETIS_DDR_CR00_DDRCLS_DDR2	(4 << 8)
#define KINETIS_DDR_CR00_START_MSK	(1 << 0)
/*
 * DDR Control Register 2 (DDR_CR02)
 */
#define KINETIS_DDR_CR02_INITAREF_BITS	24
#define KINETIS_DDR_CR02_TINIT_BITS	0
/*
 * DDR Control Register 3 (DDR_CR03)
 */
#define KINETIS_DDR_CR03_TCCD_BITS	24
#define KINETIS_DDR_CR03_WRLAT_BITS	16
#define KINETIS_DDR_CR03_LATGATE_BITS	8
#define KINETIS_DDR_CR03_LATLIN_BITS	0
/*
 * DDR Control Register 4 (DDR_CR04)
 */
#define KINETIS_DDR_CR04_TRASMIN_BITS	24
#define KINETIS_DDR_CR04_TRC_BITS	16
#define KINETIS_DDR_CR04_TRRD_BITS	8
#define KINETIS_DDR_CR04_TBINT_BITS	0
/*
 * DDR Control Register 5 (DDR_CR05)
 */
#define KINETIS_DDR_CR05_TMRD_BITS	24
#define KINETIS_DDR_CR05_TRTP_BITS	16
#define KINETIS_DDR_CR05_TRP_BITS	8
#define KINETIS_DDR_CR05_TWTR_BITS	0
/*
 * DDR Control Register 6 (DDR_CR06)
 */
#define KINETIS_DDR_CR06_TRASMAX_BITS	8
#define KINETIS_DDR_CR06_TMOD_BITS	0
/*
 * DDR Control Register 7 (DDR_CR07)
 */
#define KINETIS_DDR_CR07_CCAPEN_MSK	(1 << 24)
#define KINETIS_DDR_CR07_TCKESR_BITS	8
#define KINETIS_DDR_CR07_CLKPW_BITS	0
/*
 * DDR Control Register 8 (DDR_CR08)
 */
#define KINETIS_DDR_CR08_TDAL_BITS	24
#define KINETIS_DDR_CR08_TWR_BITS	16
#define KINETIS_DDR_CR08_TRASDI_BITS	8
#define KINETIS_DDR_CR08_TRAS_MSK	(1 << 0)
/*
 * DDR Control Register 9 (DDR_CR09)
 */
#define KINETIS_DDR_CR09_BSTLEN_BITS	24
#define KINETIS_DDR_CR09_BSTLEN_4W	(2 << KINETIS_DDR_CR09_BSTLEN_BITS)
#define KINETIS_DDR_CR09_TDLL_BITS	0
/*
 * DDR Control Register 10 (DDR_CR10)
 */
#define KINETIS_DDR_CR10_TRPAB_BITS	24
#define KINETIS_DDR_CR10_TCPD_BITS	8
#define KINETIS_DDR_CR10_TFAW_BITS	0
/*
 * DDR Control Register 11 (DDR_CR11)
 */
#define KINETIS_DDR_CR11_TREFEN_MSK	(1 << 24)
/*
 * DDR Control Register 12 (DDR_CR12)
 */
#define KINETIS_DDR_CR12_TREF_BITS	16
#define KINETIS_DDR_CR12_TRFC_BITS	0
/*
 * DDR Control Register 14 (DDR_CR14)
 */
#define KINETIS_DDR_CR14_TXSR_BITS	16
#define KINETIS_DDR_CR14_TPDEX_BITS	0
/*
 * DDR Control Register 15 (DDR_CR15)
 */
#define KINETIS_DDR_CR15_TXSNR_BITS	0
/*
 * DDR Control Register 16 (DDR_CR16)
 */
#define KINETIS_DDR_CR16_QKREF_MSK	(1 << 0)
/*
 * DDR Control Register 20 (DDR_CR20)
 */
#define KINETIS_DDR_CR20_CKSRX_BITS	16
#define KINETIS_DDR_CR20_CKSRE_BITS	8
/*
 * DDR Control Register 21 (DDR_CR21)
 */
#define KINETIS_DDR_CR21_MR1DAT0_BITS	16
#define KINETIS_DDR_CR21_MR0DAT0_BITS	0
/*
 * DDR Control Register 22 (DDR_CR22)
 */
#define KINETIS_DDR_CR22_MR3DAT0_BITS	16
#define KINETIS_DDR_CR22_MR2DAT0_BITS	0
/*
 * DDR Control Register 25 (DDR_CR25)
 */
#define KINETIS_DDR_CR25_APREBIT_BITS	24
#define KINETIS_DDR_CR25_COLSIZ_BITS	16
#define KINETIS_DDR_CR25_ADDPINS_BITS	8
#define KINETIS_DDR_CR25_BNK8_MSK	(1 << 0)
/*
 * DDR Control Register 26 (DDR_CR26)
 */
#define KINETIS_DDR_CR26_BNKSPT_MSK	(1 << 24)
#define KINETIS_DDR_CR26_ADDCOL_MSK	(1 << 16)
#define KINETIS_DDR_CR26_CMDAGE_BITS	8
#define KINETIS_DDR_CR26_AGECNT_BITS	0
/*
 * DDR Control Register 27 (DDR_CR27)
 */
#define KINETIS_DDR_CR27_SWPEN_MSK	(1 << 24)
#define KINETIS_DDR_CR27_RWEN_MSK	(1 << 16)
#define KINETIS_DDR_CR27_PRIEN_MSK	(1 << 8)
#define KINETIS_DDR_CR27_PLEN_MSK	(1 << 0)
/*
 * DDR Control Register 28 (DDR_CR28)
 */
#define KINETIS_DDR_CR28_CSMAP_MSK	(1 << 0)
/*
 * DDR Control Register 30 (DDR_CR30)
 */
#define KINETIS_DDR_CR30_INTSTAT_DRAMINIT_MSK	(1 << 10)
#define KINETIS_DDR_CR30_RSYNCRF_MSK		(1 << 0)
/*
 * DDR Control Register 34 (DDR_CR34)
 */
#define KINETIS_DDR_CR34_ODTWRCS_MSK	(1 << 8)
#define KINETIS_DDR_CR34_ODTRDC_MSK	(1 << 0)
/*
 * DDR Control Register 37 (DDR_CR37)
 */
#define KINETIS_DDR_CR37_R2WSAME_BITS	8
/*
 * DDR Control Register 38 (DDR_CR38)
 */
#define KINETIS_DDR_CR38_P0WRCNT_BITS	16
/*
 * DDR Control Register 39 (DDR_CR39)
 */
#define KINETIS_DDR_CR39_WP0_BITS	24
#define KINETIS_DDR_CR39_RP0_BITS	16
#define KINETIS_DDR_CR39_P0RDCNT_BITS	0
/*
 * DDR Control Register 40 (DDR_CR40)
 */
#define KINETIS_DDR_CR40_P1WRCNT_BITS	8
#define KINETIS_DDR_CR40_P0TYP_BITS	0
/*
 * DDR Control Register 41 (DDR_CR41)
 */
#define KINETIS_DDR_CR41_WP1_BITS	24
#define KINETIS_DDR_CR41_RP1_BITS	16
#define KINETIS_DDR_CR41_P1RDCNT_BITS	0
/*
 * DDR Control Register 42 (DDR_CR42)
 */
#define KINETIS_DDR_CR42_P2WRCNT_BITS	8
#define KINETIS_DDR_CR42_P1TYP_BITS	0
/*
 * DDR Control Register 43 (DDR_CR43)
 */
#define KINETIS_DDR_CR43_WP2_BITS	24
#define KINETIS_DDR_CR43_RP2_BITS	16
#define KINETIS_DDR_CR43_P2RDCNT_BITS	0
/*
 * DDR Control Register 44 (DDR_CR44)
 */
#define KINETIS_DDR_CR44_P2TYP_BITS	0
/*
 * DDR Control Register 45 (DDR_CR45)
 */
#define KINETIS_DDR_CR45_P0PRI3_BITS	24
#define KINETIS_DDR_CR45_P0PRI2_BITS	16
#define KINETIS_DDR_CR45_P0PRI1_BITS	8
#define KINETIS_DDR_CR45_P0PRI0_BITS	0
/*
 * DDR Control Register 46 (DDR_CR46)
 */
#define KINETIS_DDR_CR46_P1PRI0_BITS	24
#define KINETIS_DDR_CR46_P0PRIRLX_BITS	8
#define KINETIS_DDR_CR46_P0ORD_BITS	0
/*
 * DDR Control Register 47 (DDR_CR47)
 */
#define KINETIS_DDR_CR47_P1ORD_BITS	24
#define KINETIS_DDR_CR47_P1PRI3_BITS	16
#define KINETIS_DDR_CR47_P1PRI2_BITS	8
#define KINETIS_DDR_CR47_P1PRI1_BITS	0
/*
 * DDR Control Register 48 (DDR_CR48)
 */
#define KINETIS_DDR_CR48_P2PRI1_BITS	24
#define KINETIS_DDR_CR48_P2PRI0_BITS	16
#define KINETIS_DDR_CR48_P1PRIRLX_BITS	0
/*
 * DDR Control Register 49 (DDR_CR49)
 */
#define KINETIS_DDR_CR49_P2ORD_BITS	16
#define KINETIS_DDR_CR49_P2PRI3_BITS	8
#define KINETIS_DDR_CR49_P2PRI2_BITS	0
/*
 * DDR Control Register 50 (DDR_CR50)
 */
#define KINETIS_DDR_CR50_P2PRIRLX_BITS		0
/*
 * DDR Control Register 52 (DDR_CR52)
 */
#define KINETIS_DDR_CR52_RDDTENBAS_BITS		24
#define KINETIS_DDR_CR52_PHYRDLAT_BITS		8
#define KINETIS_DDR_CR52_PYWRLTBS_BITS		0
/*
 * DDR Control Register 53 (DDR_CR53)
 */
#define KINETIS_DDR_CR53_CTRLUPDMX_BITS		16
/*
 * DDR Control Register 54 (DDR_CR54)
 */
#define KINETIS_DDR_CR54_PHYUPDTY1_BITS		16
#define KINETIS_DDR_CR54_PHYUPDTY0_BITS		0
/*
 * DDR Control Register 55 (DDR_CR55)
 */
#define KINETIS_DDR_CR55_PHYUPDTY3_BITS		16
#define KINETIS_DDR_CR55_PHYUPDTY2_BITS		0
/*
 * DDR Control Register 56 (DDR_CR56)
 */
#define KINETIS_DDR_CR56_WRLATADJ_BITS		24
#define KINETIS_DDR_CR56_RDLATADJ_BITS		16
#define KINETIS_DDR_CR56_PHYUPDRESP_BITS	0
/*
 * DDR Control Register 57 (DDR_CR57)
 */
#define KINETIS_DDR_CR57_ODTALTEN_MSK		(1 << 24)
#define KINETIS_DDR_CR57_CLKENDLY_BITS		16
#define KINETIS_DDR_CR57_CMDDLY_BITS		0
/*
 * RCR Control Register (DDR_RCR)
 */
#define KINETIS_DDR_RCR_RST_MSK		(1 << 30)
/*
 * I/O Pad Control Register (DDR_PAD_CTRL)
 */
/* Required to enable ODT and configure ODT resistor value in the pad */
#define KINETIS_DDR_PAD_CTRL_PAD_ODT_CS0_BITS	24
/* 75 Ohms */
#define KINETIS_DDR_PAD_CTRL_CS0_75 \
	(1 << KINETIS_DDR_PAD_CTRL_PAD_ODT_CS0_BITS)
/* SPARE_DLY_CTRL[1:0] is used to control the delay chain #0 */
#define KINETIS_DDR_PAD_CTRL_SPARE_DLY_CTRL_BITS	0
/* 10 buffers */
#define KINETIS_DDR_PAD_CTRL_DELAY_10BUF \
	(3 << KINETIS_DDR_PAD_CTRL_SPARE_DLY_CTRL_BITS)
/* This bit should always be written into PAD_CTRL (undocumented feature) */
#define KINETIS_DDR_PAD_CTRL_FIXED_MSK		(1 << 9)

#ifdef __cplusplus
}
#endif

#endif  /* __INCfsl_KinetisMemh */

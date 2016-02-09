/* xlxLib.h -  Netlogic Support Routines */

/*
 * Copyright 2007-2008, 2010-2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01l,12jul11,l_z  add xlxRead/Write declaration
01k,25apr11,slk  rename to xlxLib.h and add XLP defines for pagewalker support
01j,29apr10,pad  Moved extern C statement after include statements.
01i,02feb10,pgh  Fix warnings.
01h,07apr08,h_k  added S_XLR_NUM_THREADS_PER_CORE.
01g,19dec07,wap  Add definitions for L1D_CFG0 register
01f,04dec07,l_z  Rename cpuNUM to cpuIndex and cpuID to cpuId
01e,01dec07,l_z  Add XLR_NUM_THREADS_PER_CORE macro
01d,19oct07,wap  Add routines to access processor control registers
01c,25sep07,d_c  Add extended interrupts for RMI _xlr variant
01b,31aug08,l_z  Declare xlr CP2 access interface.
*/

/*
DESCRIPTION

This file declares the Netlogic family support routines. All the functions are 
defined in src/arch/mips/xlxALib.s.

These function access the follow CP2 register:
	Bucket register
	Config register
	Status register
	Credit register
	Bucket size register.

For more details, see src/arch/mips/xlrALib.s.

*/

#ifndef __INCxlxlibh
#define __INCxlxlibh


#include "vxWorks.h"

#ifdef __cplusplus
extern "C" {
#endif


#define EIMR_SR_IMASK      0xff  /* Bits in EIMR corresponding to SR[15:8] */
#define EIMR_SR_SHIFT      8     /* Shift between SR and EIMR */

#define XLR_PCR_THREADEN	0x0000
#define XLR_PCR_SOFTSLEEP	0x0001
#define XLR_PCR_SCHEDULING	0x0002
#define XLR_PCR_SCHEDCOUNT	0x0003
#define XLR_PCR_BHRPM		0x0004 /* Branch history register prog. mask */
#define XLR_PCR_IFU_DEFEATURE	0x0006
#define XLR_PCR_ICU_DEFEATURE	0x0100
#define XLR_PCR_ICU_ERRLOG	0x0101
#define XLR_PCR_ICU_DBGADDR	0x0102
#define XLR_PCR_ICU_DBGDATA_LO	0x0103
#define XLR_PCR_ICU_DBGDATA_HI	0x0104
#define XLR_PCR_ICU_SAMP_LFSR	0x0105
#define XLR_PCR_ICU_SAMP_PC	0x0106
#define XLR_PCR_ICU_SAMP_SETUP	0x0107
#define XLR_PCR_ICU_SAMP_TIMER	0x0108
#define XLR_PCR_ICU_SAMP_PC_HI	0x0109
#define XLR_PCR_IEU_DEFEATURE	0x0200
#define XLR_PCR_TGT_PC		0x0207
#define XLR_PCR_L1D_CFG0	0x0300
#define XLR_PCR_L1D_CFG1	0x0301
#define XLR_PCR_L1D_CFG2	0x0302
#define XLR_PCR_L1D_CFG3	0x0303
#define XLR_PCR_L1D_CFG4	0x0304
#define XLR_PCR_L1D_STATUS	0x0305
#define XLR_PCR_L1D_DEFEATURE	0x0306
#define XLR_PCR_L1D_DEBUG0	0x0307
#define XLR_PCR_L1D_DEBUG1	0x0308
#define XLR_PCR_L1D_ERRLOG	0x0309
#define XLR_PCR_L1D_OVF_LO	0x030A
#define XLR_PCR_L1D_INTR	0x030B
#define XLR_PCR_MMU_SETUP	0x0400
#define XLR_PCR_PRF_SMP_EVENT	0x0500
#define XLR_PCR_PRF_SMP_RPLYBUF	0x0501

/* L1 Data cache config register 0 */

#define XLR_L1DCFG0_L1D_LP_DIS	0x00002000	/* L1D low power disable */
#define XLR_L1DCFG0_ERL_FORCEM	0x00001000	/* enable virtualizing of ERL */
#define XLR_L1DCFG0_MEM_ORDER	0x00000F00	/* memory ordering mode */
#define XLR_L1DCFG0_UTLB_PART	0x00000080	/* uTLP partitioned by threads */
#define XLR_L1DCFG0_D_FORCEM	0x00000040	/* force mapped data */
#define XLR_L1DCFG0_CACHEER_ENB 0x00000020	/* cache error log and report */
#define XLR_L1DCFG0_L2ALLOC_ENB	0x00000010	/* L2 line allocation enable */
#define XLR_L1DCFG0_DATAECC_ENB	0x00000008	/* Data ECC enable */
#define XLR_L1DCFG0_SNPPAR_ENB	0x00000004	/* Snoop tag parity enable */
#define XLR_L1DCFG0_TAGPAR_ENB	0x00000002	/* Tag parity enable */
#define XLR_L1DCFG0_L1DCA_ENB	0x00000001	/* L1 data cache enable */

#define XLR_MEMORDER_ST_ST	0x00000100
#define XLR_MEMORDER_LD_ST	0x00000200
#define XLR_MEMORDER_ST_LD	0x00000400
#define XLR_MEMORDER_LD_LD	0x00000800

/* XLP defines for pagewalker support */
#define XLP_MMU_SETUP             0x0400 /* MMU setup  */
#define XLP_LFSRSEED              0x0401 /* LFSR seed  */
#define XLP_HPW_NUM_PAGE_LVL      0x0410 /* Pagewalker Number Page Level */
#define XLP_PGWKR_PGDBASE         0x0411 /* Pagewalker PGD Base */
#define XLP_PGWKR_PGDSHFT         0x0412 /* Pagewalker PGD Shift Register */
#define XLP_PGWKR_PGDMASK         0x0413 /* Pagewalker PGD Mask Register */
#define XLP_PGWKR_PUDSHFT         0x0414 /* Pagewalker PUD Shift Register */
#define XLP_PGWKR_PUDMASK         0x0415 /* Pagewalker PUD Mask Register */
#define XLP_PGWKR_PMDSHFT         0x0416 /* Pagewalker PMD Shift Register */
#define XLP_PGWKR_PMDMASK         0x0417 /* Pagewalker PMD Mask Register */
#define XLP_PGWKR_PTESHFT         0x0418 /* Pagewalker PTE Shift Register */
#define XLP_PGWKR_PTEMASK         0x0419 /* Pagewalker PTE Mask Register */

#define MMU_SETUP_THREAD_MODE     0x00000003 /* Four thread per core */
#define MMU_SETUP_GLOBAL_MODE     0x00000001 /* MMU thread global mode */
#define HFP_NUM_PAGE_LVL_VALUE    ((6 <<4 ) || 0x00000009) /* Enable PGD and PTE,
                                                            * and set the EntryHiLoShift with 6
                                                            */

#define XLP_EXTENDED_TLB_ENTRYS   512 /* 2048/4 */
#define CONFIG6_ELVT              0x00000020 /* Enable large memory variable TLB */
#define CONFIG6_EGT               0x00000010 /* Enable global TLB */
#define CONFIG6_EPW               0x00000008 /* Enable page walker */
#define CONFIG6_EFT               0x00000004 /* Enable fixed TLB */
#define CONFIG6_PWI               0x00000002 /* Page walker implemented */
#define CONFIG6_FTI               0x00000001 /* Fixed TLB implemented */

/* This macro show the offset of sp and gp in struct CPU_ARGS */
#define CPU_ARGS_SP_OFFSET         8
#define CPU_ARGS_GP_OFFSET         12

/* Max cores for all of XLR CPU */
#define XLR_NUM_CORES              8

/* Thread number per core */
#define S_XLR_NUM_THREADS_PER_CORE 2
#define XLR_NUM_THREADS_PER_CORE   (1 << S_XLR_NUM_THREADS_PER_CORE)

/* Bucket number per core */
#define XLR_NUM_BUCKETS_PER_CORE   8

#ifndef _ASMLANGUAGE

/* struct is for pass paramater to slave CPU */
typedef struct
    {
    UINT32 cpuIndex;
    UINT32 cpuId;
    UINT32 sp;
    UINT32 gp;
    } CPU_ARGS;

IMPORT UINT64 xlrEirrGet(void);
IMPORT void xlrEirrSet(UINT64);
IMPORT UINT64 xlrEimrGet(void);
IMPORT void xlrEimrSet(UINT64);
IMPORT void xlrCp2MsgSend(UINT32);
IMPORT void xlrCp2MsgRecv(UINT32);
IMPORT UINT64 xlrPcrGet (UINT32);
IMPORT void xlrPcrSet (UINT32, UINT64);

/* extern CP2 64bit transmit buffer register access function */
extern UINT64 xlrCp2Rd64Reg0Sel0 (void); \
extern  void  xlrCp2Wr64Reg0Sel0 (UINT64);
extern UINT64 xlrCp2Rd64Reg0Sel1 (void); \
extern  void  xlrCp2Wr64Reg0Sel1 (UINT64);
extern UINT64 xlrCp2Rd64Reg0Sel2 (void); \
extern  void  xlrCp2Wr64Reg0Sel2 (UINT64);
extern UINT64 xlrCp2Rd64Reg0Sel3 (void); \
extern  void  xlrCp2Wr64Reg0Sel3 (UINT64);

/* extern CP2 64bit receive buffer register access function*/
extern UINT64 xlrCp2Rd64Reg1Sel0 (void); \
extern  void  xlrCp2Wr64Reg1Sel0 (UINT64);
extern UINT64 xlrCp2Rd64Reg1Sel1 (void); \
extern  void  xlrCp2Wr64Reg1Sel1 (UINT64);
extern UINT64 xlrCp2Rd64Reg1Sel2 (void); \
extern  void  xlrCp2Wr64Reg1Sel2 (UINT64);
extern UINT64 xlrCp2Rd64Reg1Sel3 (void); \
extern  void  xlrCp2Wr64Reg1Sel3 (UINT64);

/* extern CP2 32bit status register access function */
extern UINT32 xlrCp2Rd32Reg2Sel0 (void); \
extern  void  xlrCp2Wr32Reg2Sel0 (UINT32);
extern UINT32 xlrCp2Rd32Reg2Sel1 (void); \
extern  void  xlrCp2Wr32Reg2Sel1 (UINT32);

/* extern CP2 32bit config register access function */
extern UINT32 xlrCp2Rd32Reg3Sel0 (void); \
extern  void  xlrCp2Wr32Reg3Sel0 (UINT32);
extern UINT32 xlrCp2Rd32Reg3Sel1 (void); \
extern  void  xlrCp2Wr32Reg3Sel1 (UINT32);

/* extern CP2 32bit bucket size register access function */
extern UINT32 xlrCp2Rd32Reg4Sel0 (void); \
extern  void  xlrCp2Wr32Reg4Sel0 (UINT32);
extern UINT32 xlrCp2Rd32Reg4Sel1 (void); \
extern  void  xlrCp2Wr32Reg4Sel1 (UINT32);
extern UINT32 xlrCp2Rd32Reg4Sel2 (void); \
extern  void  xlrCp2Wr32Reg4Sel2 (UINT32);
extern UINT32 xlrCp2Rd32Reg4Sel3 (void); \
extern  void  xlrCp2Wr32Reg4Sel3 (UINT32);
extern UINT32 xlrCp2Rd32Reg4Sel4 (void); \
extern  void  xlrCp2Wr32Reg4Sel4 (UINT32);
extern UINT32 xlrCp2Rd32Reg4Sel5 (void); \
extern  void  xlrCp2Wr32Reg4Sel5 (UINT32);
extern UINT32 xlrCp2Rd32Reg4Sel6 (void); \
extern  void  xlrCp2Wr32Reg4Sel6 (UINT32);
extern UINT32 xlrCp2Rd32Reg4Sel7 (void); \
extern  void  xlrCp2Wr32Reg4Sel7 (UINT32);

extern UINT32 xlrCp2Rd32Reg5Sel0 (void); \
extern  void  xlrCp2Wr32Reg5Sel0 (UINT32);

extern UINT32 xlrCp2Rd32Reg6Sel0 (void); \
extern  void  xlrCp2Wr32Reg6Sel0 (UINT32);
extern UINT32 xlrCp2Rd32Reg6Sel1 (void); \
extern  void  xlrCp2Wr32Reg6Sel1 (UINT32);
extern UINT32 xlrCp2Rd32Reg6Sel2 (void); \
extern  void  xlrCp2Wr32Reg6Sel2 (UINT32);
extern UINT32 xlrCp2Rd32Reg6Sel3 (void); \
extern  void  xlrCp2Wr32Reg6Sel3 (UINT32);
extern UINT32 xlrCp2Rd32Reg6Sel4 (void); \
extern  void  xlrCp2Wr32Reg6Sel4 (UINT32);

/* extern CP2 32bit credit register access function */
extern UINT32 xlrCp2Rd32Reg16Sel0 (void); \
extern  void  xlrCp2Wr32Reg16Sel0 (UINT32);
extern UINT32 xlrCp2Rd32Reg16Sel1 (void); \
extern  void  xlrCp2Wr32Reg16Sel1 (UINT32);
extern UINT32 xlrCp2Rd32Reg16Sel2 (void); \
extern  void  xlrCp2Wr32Reg16Sel2 (UINT32);
extern UINT32 xlrCp2Rd32Reg16Sel3 (void); \
extern  void  xlrCp2Wr32Reg16Sel3 (UINT32);
extern UINT32 xlrCp2Rd32Reg16Sel4 (void); \
extern  void  xlrCp2Wr32Reg16Sel4 (UINT32);
extern UINT32 xlrCp2Rd32Reg16Sel5 (void); \
extern  void  xlrCp2Wr32Reg16Sel5 (UINT32);
extern UINT32 xlrCp2Rd32Reg16Sel6 (void); \
extern  void  xlrCp2Wr32Reg16Sel6 (UINT32);
extern UINT32 xlrCp2Rd32Reg16Sel7 (void); \
extern  void  xlrCp2Wr32Reg16Sel7 (UINT32);

extern UINT32 xlrCp2Rd32Reg17Sel0 (void); \
extern  void  xlrCp2Wr32Reg17Sel0 (UINT32);
extern UINT32 xlrCp2Rd32Reg17Sel1 (void); \
extern  void  xlrCp2Wr32Reg17Sel1 (UINT32);
extern UINT32 xlrCp2Rd32Reg17Sel2 (void); \
extern  void  xlrCp2Wr32Reg17Sel2 (UINT32);
extern UINT32 xlrCp2Rd32Reg17Sel3 (void); \
extern  void  xlrCp2Wr32Reg17Sel3 (UINT32);
extern UINT32 xlrCp2Rd32Reg17Sel4 (void); \
extern  void  xlrCp2Wr32Reg17Sel4 (UINT32);
extern UINT32 xlrCp2Rd32Reg17Sel5 (void); \
extern  void  xlrCp2Wr32Reg17Sel5 (UINT32);
extern UINT32 xlrCp2Rd32Reg17Sel6 (void); \
extern  void  xlrCp2Wr32Reg17Sel6 (UINT32);
extern UINT32 xlrCp2Rd32Reg17Sel7 (void); \
extern  void  xlrCp2Wr32Reg17Sel7 (UINT32);

extern UINT32 xlrCp2Rd32Reg18Sel0 (void); \
extern  void  xlrCp2Wr32Reg18Sel0 (UINT32);
extern UINT32 xlrCp2Rd32Reg18Sel1 (void); \
extern  void  xlrCp2Wr32Reg18Sel1 (UINT32);
extern UINT32 xlrCp2Rd32Reg18Sel2 (void); \
extern  void  xlrCp2Wr32Reg18Sel2 (UINT32);
extern UINT32 xlrCp2Rd32Reg18Sel3 (void); \
extern  void  xlrCp2Wr32Reg18Sel3 (UINT32);
extern UINT32 xlrCp2Rd32Reg18Sel4 (void); \
extern  void  xlrCp2Wr32Reg18Sel4 (UINT32);
extern UINT32 xlrCp2Rd32Reg18Sel5 (void); \
extern  void  xlrCp2Wr32Reg18Sel5 (UINT32);
extern UINT32 xlrCp2Rd32Reg18Sel6 (void); \
extern  void  xlrCp2Wr32Reg18Sel6 (UINT32);
extern UINT32 xlrCp2Rd32Reg18Sel7 (void); \
extern  void  xlrCp2Wr32Reg18Sel7 (UINT32);

extern UINT32 xlrCp2Rd32Reg19Sel0 (void); \
extern  void  xlrCp2Wr32Reg19Sel0 (UINT32);
extern UINT32 xlrCp2Rd32Reg19Sel1 (void); \
extern  void  xlrCp2Wr32Reg19Sel1 (UINT32);
extern UINT32 xlrCp2Rd32Reg19Sel2 (void); \
extern  void  xlrCp2Wr32Reg19Sel2 (UINT32);
extern UINT32 xlrCp2Rd32Reg19Sel3 (void); \
extern  void  xlrCp2Wr32Reg19Sel3 (UINT32);
extern UINT32 xlrCp2Rd32Reg19Sel4 (void); \
extern  void  xlrCp2Wr32Reg19Sel4 (UINT32);
extern UINT32 xlrCp2Rd32Reg19Sel5 (void); \
extern  void  xlrCp2Wr32Reg19Sel5 (UINT32);
extern UINT32 xlrCp2Rd32Reg19Sel6 (void); \
extern  void  xlrCp2Wr32Reg19Sel6 (UINT32);
extern UINT32 xlrCp2Rd32Reg19Sel7 (void); \
extern  void  xlrCp2Wr32Reg19Sel7 (UINT32);

extern UINT32 xlrCp2Rd32Reg20Sel0 (void); \
extern  void  xlrCp2Wr32Reg20Sel0 (UINT32);
extern UINT32 xlrCp2Rd32Reg20Sel1 (void); \
extern  void  xlrCp2Wr32Reg20Sel1 (UINT32);
extern UINT32 xlrCp2Rd32Reg20Sel2 (void); \
extern  void  xlrCp2Wr32Reg20Sel2 (UINT32);
extern UINT32 xlrCp2Rd32Reg20Sel3 (void); \
extern  void  xlrCp2Wr32Reg20Sel3 (UINT32);
extern UINT32 xlrCp2Rd32Reg20Sel4 (void); \
extern  void  xlrCp2Wr32Reg20Sel4 (UINT32);
extern UINT32 xlrCp2Rd32Reg20Sel5 (void); \
extern  void  xlrCp2Wr32Reg20Sel5 (UINT32);
extern UINT32 xlrCp2Rd32Reg20Sel6 (void); \
extern  void  xlrCp2Wr32Reg20Sel6 (UINT32);
extern UINT32 xlrCp2Rd32Reg20Sel7 (void); \
extern  void  xlrCp2Wr32Reg20Sel7 (UINT32);

extern UINT32 xlrCp2Rd32Reg21Sel0 (void); \
extern  void  xlrCp2Wr32Reg21Sel0 (UINT32);
extern UINT32 xlrCp2Rd32Reg21Sel1 (void); \
extern  void  xlrCp2Wr32Reg21Sel1 (UINT32);
extern UINT32 xlrCp2Rd32Reg21Sel2 (void); \
extern  void  xlrCp2Wr32Reg21Sel2 (UINT32);
extern UINT32 xlrCp2Rd32Reg21Sel3 (void); \
extern  void  xlrCp2Wr32Reg21Sel3 (UINT32);
extern UINT32 xlrCp2Rd32Reg21Sel4 (void); \
extern  void  xlrCp2Wr32Reg21Sel4 (UINT32);
extern UINT32 xlrCp2Rd32Reg21Sel5 (void); \
extern  void  xlrCp2Wr32Reg21Sel5 (UINT32);
extern UINT32 xlrCp2Rd32Reg21Sel6 (void); \
extern  void  xlrCp2Wr32Reg21Sel6 (UINT32);
extern UINT32 xlrCp2Rd32Reg21Sel7 (void); \
extern  void  xlrCp2Wr32Reg21Sel7 (UINT32);

extern UINT32 xlrCp2Rd32Reg22Sel0 (void); \
extern  void  xlrCp2Wr32Reg22Sel0 (UINT32);
extern UINT32 xlrCp2Rd32Reg22Sel1 (void); \
extern  void  xlrCp2Wr32Reg22Sel1 (UINT32);
extern UINT32 xlrCp2Rd32Reg22Sel2 (void); \
extern  void  xlrCp2Wr32Reg22Sel2 (UINT32);
extern UINT32 xlrCp2Rd32Reg22Sel3 (void); \
extern  void  xlrCp2Wr32Reg22Sel3 (UINT32);
extern UINT32 xlrCp2Rd32Reg22Sel4 (void); \
extern  void  xlrCp2Wr32Reg22Sel4 (UINT32);
extern UINT32 xlrCp2Rd32Reg22Sel5 (void); \
extern  void  xlrCp2Wr32Reg22Sel5 (UINT32);
extern UINT32 xlrCp2Rd32Reg22Sel6 (void); \
extern  void  xlrCp2Wr32Reg22Sel6 (UINT32);
extern UINT32 xlrCp2Rd32Reg22Sel7 (void); \
extern  void  xlrCp2Wr32Reg22Sel7 (UINT32);

extern UINT32 xlrCp2Rd32Reg23Sel0 (void); \
extern  void  xlrCp2Wr32Reg23Sel0 (UINT32);
extern UINT32 xlrCp2Rd32Reg23Sel1 (void); \
extern  void  xlrCp2Wr32Reg23Sel1 (UINT32);
extern UINT32 xlrCp2Rd32Reg23Sel2 (void); \
extern  void  xlrCp2Wr32Reg23Sel2 (UINT32);
extern UINT32 xlrCp2Rd32Reg23Sel3 (void); \
extern  void  xlrCp2Wr32Reg23Sel3 (UINT32);
extern UINT32 xlrCp2Rd32Reg23Sel4 (void); \
extern  void  xlrCp2Wr32Reg23Sel4 (UINT32);
extern UINT32 xlrCp2Rd32Reg23Sel5 (void); \
extern  void  xlrCp2Wr32Reg23Sel5 (UINT32);
extern UINT32 xlrCp2Rd32Reg23Sel6 (void); \
extern  void  xlrCp2Wr32Reg23Sel6 (UINT32);
extern UINT32 xlrCp2Rd32Reg23Sel7 (void); \
extern  void  xlrCp2Wr32Reg23Sel7 (UINT32);

extern UINT32 xlrCp2Rd32Reg24Sel0 (void); \
extern  void  xlrCp2Wr32Reg24Sel0 (UINT32);
extern UINT32 xlrCp2Rd32Reg24Sel1 (void); \
extern  void  xlrCp2Wr32Reg24Sel1 (UINT32);
extern UINT32 xlrCp2Rd32Reg24Sel2 (void); \
extern  void  xlrCp2Wr32Reg24Sel2 (UINT32);
extern UINT32 xlrCp2Rd32Reg24Sel3 (void); \
extern  void  xlrCp2Wr32Reg24Sel3 (UINT32);
extern UINT32 xlrCp2Rd32Reg24Sel4 (void); \
extern  void  xlrCp2Wr32Reg24Sel4 (UINT32);
extern UINT32 xlrCp2Rd32Reg24Sel5 (void); \
extern  void  xlrCp2Wr32Reg24Sel5 (UINT32);
extern UINT32 xlrCp2Rd32Reg24Sel6 (void); \
extern  void  xlrCp2Wr32Reg24Sel6 (UINT32);
extern UINT32 xlrCp2Rd32Reg24Sel7 (void); \
extern  void  xlrCp2Wr32Reg24Sel7 (UINT32);

extern UINT32 xlrCp2Rd32Reg25Sel0 (void); \
extern  void  xlrCp2Wr32Reg25Sel0 (UINT32);
extern UINT32 xlrCp2Rd32Reg25Sel1 (void); \
extern  void  xlrCp2Wr32Reg25Sel1 (UINT32);
extern UINT32 xlrCp2Rd32Reg25Sel2 (void); \
extern  void  xlrCp2Wr32Reg25Sel2 (UINT32);
extern UINT32 xlrCp2Rd32Reg25Sel3 (void); \
extern  void  xlrCp2Wr32Reg25Sel3 (UINT32);
extern UINT32 xlrCp2Rd32Reg25Sel4 (void); \
extern  void  xlrCp2Wr32Reg25Sel4 (UINT32);
extern UINT32 xlrCp2Rd32Reg25Sel5 (void); \
extern  void  xlrCp2Wr32Reg25Sel5 (UINT32);
extern UINT32 xlrCp2Rd32Reg25Sel6 (void); \
extern  void  xlrCp2Wr32Reg25Sel6 (UINT32);
extern UINT32 xlrCp2Rd32Reg25Sel7 (void); \
extern  void  xlrCp2Wr32Reg25Sel7 (UINT32);

extern UINT32 xlrCp2Rd32Reg26Sel0 (void); \
extern  void  xlrCp2Wr32Reg26Sel0 (UINT32);
extern UINT32 xlrCp2Rd32Reg26Sel1 (void); \
extern  void  xlrCp2Wr32Reg26Sel1 (UINT32);
extern UINT32 xlrCp2Rd32Reg26Sel2 (void); \
extern  void  xlrCp2Wr32Reg26Sel2 (UINT32);
extern UINT32 xlrCp2Rd32Reg26Sel3 (void); \
extern  void  xlrCp2Wr32Reg26Sel3 (UINT32);
extern UINT32 xlrCp2Rd32Reg26Sel4 (void); \
extern  void  xlrCp2Wr32Reg26Sel4 (UINT32);
extern UINT32 xlrCp2Rd32Reg26Sel5 (void); \
extern  void  xlrCp2Wr32Reg26Sel5 (UINT32);
extern UINT32 xlrCp2Rd32Reg26Sel6 (void); \
extern  void  xlrCp2Wr32Reg26Sel6 (UINT32);
extern UINT32 xlrCp2Rd32Reg26Sel7 (void); \
extern  void  xlrCp2Wr32Reg26Sel7 (UINT32);

extern UINT32 xlrCp2Rd32Reg27Sel0 (void); \
extern  void  xlrCp2Wr32Reg27Sel0 (UINT32);
extern UINT32 xlrCp2Rd32Reg27Sel1 (void); \
extern  void  xlrCp2Wr32Reg27Sel1 (UINT32);
extern UINT32 xlrCp2Rd32Reg27Sel2 (void); \
extern  void  xlrCp2Wr32Reg27Sel2 (UINT32);
extern UINT32 xlrCp2Rd32Reg27Sel3 (void); \
extern  void  xlrCp2Wr32Reg27Sel3 (UINT32);
extern UINT32 xlrCp2Rd32Reg27Sel4 (void); \
extern  void  xlrCp2Wr32Reg27Sel4 (UINT32);
extern UINT32 xlrCp2Rd32Reg27Sel5 (void); \
extern  void  xlrCp2Wr32Reg27Sel5 (UINT32);
extern UINT32 xlrCp2Rd32Reg27Sel6 (void); \
extern  void  xlrCp2Wr32Reg27Sel6 (UINT32);
extern UINT32 xlrCp2Rd32Reg27Sel7 (void); \
extern  void  xlrCp2Wr32Reg27Sel7 (UINT32);

extern UINT32 xlrCp2Rd32Reg28Sel0 (void); \
extern  void  xlrCp2Wr32Reg28Sel0 (UINT32);
extern UINT32 xlrCp2Rd32Reg28Sel1 (void); \
extern  void  xlrCp2Wr32Reg28Sel1 (UINT32);
extern UINT32 xlrCp2Rd32Reg28Sel2 (void); \
extern  void  xlrCp2Wr32Reg28Sel2 (UINT32);
extern UINT32 xlrCp2Rd32Reg28Sel3 (void); \
extern  void  xlrCp2Wr32Reg28Sel3 (UINT32);
extern UINT32 xlrCp2Rd32Reg28Sel4 (void); \
extern  void  xlrCp2Wr32Reg28Sel4 (UINT32);
extern UINT32 xlrCp2Rd32Reg28Sel5 (void); \
extern  void  xlrCp2Wr32Reg28Sel5 (UINT32);
extern UINT32 xlrCp2Rd32Reg28Sel6 (void); \
extern  void  xlrCp2Wr32Reg28Sel6 (UINT32);
extern UINT32 xlrCp2Rd32Reg28Sel7 (void); \
extern  void  xlrCp2Wr32Reg28Sel7 (UINT32);

extern UINT32 xlrCp2Rd32Reg29Sel0 (void); \
extern  void  xlrCp2Wr32Reg29Sel0 (UINT32);
extern UINT32 xlrCp2Rd32Reg29Sel1 (void); \
extern  void  xlrCp2Wr32Reg29Sel1 (UINT32);
extern UINT32 xlrCp2Rd32Reg29Sel2 (void); \
extern  void  xlrCp2Wr32Reg29Sel2 (UINT32);
extern UINT32 xlrCp2Rd32Reg29Sel3 (void); \
extern  void  xlrCp2Wr32Reg29Sel3 (UINT32);
extern UINT32 xlrCp2Rd32Reg29Sel4 (void); \
extern  void  xlrCp2Wr32Reg29Sel4 (UINT32);
extern UINT32 xlrCp2Rd32Reg29Sel5 (void); \
extern  void  xlrCp2Wr32Reg29Sel5 (UINT32);
extern UINT32 xlrCp2Rd32Reg29Sel6 (void); \
extern  void  xlrCp2Wr32Reg29Sel6 (UINT32);
extern UINT32 xlrCp2Rd32Reg29Sel7 (void); \
extern  void  xlrCp2Wr32Reg29Sel7 (UINT32);

extern UINT32 xlrCp2Rd32Reg30Sel0 (void); \
extern  void  xlrCp2Wr32Reg30Sel0 (UINT32);
extern UINT32 xlrCp2Rd32Reg30Sel1 (void); \
extern  void  xlrCp2Wr32Reg30Sel1 (UINT32);
extern UINT32 xlrCp2Rd32Reg30Sel2 (void); \
extern  void  xlrCp2Wr32Reg30Sel2 (UINT32);
extern UINT32 xlrCp2Rd32Reg30Sel3 (void); \
extern  void  xlrCp2Wr32Reg30Sel3 (UINT32);
extern UINT32 xlrCp2Rd32Reg30Sel4 (void); \
extern  void  xlrCp2Wr32Reg30Sel4 (UINT32);
extern UINT32 xlrCp2Rd32Reg30Sel5 (void); \
extern  void  xlrCp2Wr32Reg30Sel5 (UINT32);
extern UINT32 xlrCp2Rd32Reg30Sel6 (void); \
extern  void  xlrCp2Wr32Reg30Sel6 (UINT32);
extern UINT32 xlrCp2Rd32Reg30Sel7 (void); \
extern  void  xlrCp2Wr32Reg30Sel7 (UINT32);

extern UINT32 xlrCp2Rd32Reg31Sel0 (void); \
extern  void  xlrCp2Wr32Reg31Sel0 (UINT32);
extern UINT32 xlrCp2Rd32Reg31Sel1 (void); \
extern  void  xlrCp2Wr32Reg31Sel1 (UINT32);
extern UINT32 xlrCp2Rd32Reg31Sel2 (void); \
extern  void  xlrCp2Wr32Reg31Sel2 (UINT32);
extern UINT32 xlrCp2Rd32Reg31Sel3 (void); \
extern  void  xlrCp2Wr32Reg31Sel3 (UINT32);
extern UINT32 xlrCp2Rd32Reg31Sel4 (void); \
extern  void  xlrCp2Wr32Reg31Sel4 (UINT32);
extern UINT32 xlrCp2Rd32Reg31Sel5 (void); \
extern  void  xlrCp2Wr32Reg31Sel5 (UINT32);
extern UINT32 xlrCp2Rd32Reg31Sel6 (void); \
extern  void  xlrCp2Wr32Reg31Sel6 (UINT32);
extern UINT32 xlrCp2Rd32Reg31Sel7 (void); \
extern  void  xlrCp2Wr32Reg31Sel7 (UINT32);

IMPORT void xlxWrite64(UINT64 addr, UINT64 val);
IMPORT UINT64 xlxRead64(UINT64 addr);
IMPORT void xlxWrite32(UINT64 addr, UINT32 val);
IMPORT UINT32 xlxRead32(UINT64 addr);
IMPORT void xlxWrite16(UINT64 addr, UINT16 val);
IMPORT UINT16 xlxRead16(UINT64 addr);
IMPORT void xlxWrite8(UINT64 addr, UINT8 val);
IMPORT UINT8 xlxRead8(UINT64 addr);

#endif /* ! _ASMLANGUAGE */
      
#ifdef __cplusplus
}
#endif
#endif /* __INCxlxlibh */


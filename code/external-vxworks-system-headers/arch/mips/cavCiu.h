/* cavCiu.h - Cavium interrupt controller types and defines */

/*
 * Copyright (c) 2010-2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01k,09dec11,x_f  add CIU2 defines for OcteonII CN68xx
01j,18jul11,rlg  adding the type def for ciu_soft_rst - needed for uboot
                 control x mods
01i,10jun11,d_c  Restore Cavium headers to original form, before splitting
                 struct defs to separate headers
01h,26oct10,rlg  add CAV_CIU_QLM2_T
01g,20oct10,d_c  Include SDK data types directly from SDK
01f,05oct10,d_c  Change ull to ULL to be Diab compatible
01e,28sep10,d_c  change name to be consistent
01d,19aug10,d_c  Revert back original SDK names for copied data types
01c,13aug10,rlg  SDK REMOVAL - add another data struct
01b,26jul10,rlg  additional CIU registers addressing
01a,15jul10,rlg  created.
*/

#ifndef __INCvxbMipsCavIntCtlrh
#define __INCvxbMipsCavIntCtlrh

#include <arch/mips/private/cavSdkDrvInclude.h>
#define CAV_INCLUDE_TYPEDEFS_ONLY
#include CAV_SDK_DRV_INCLUDE(cvmx-ciu-defs.h)

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

/*
 *    ADDRESS DEFINES 
 */

#define CAV_CIU_BASE_ADDR 	0x8001070000000000ULL
#define CAV_CIU_QLM2_ADDR       0x8001070000000790ULL

/* INTERRUPT SUMMERY 34 registers  chapter 12 of 63xx pdf */
#define CAV_CIU_INTX_SUM0_OFF	0x0	/* start offset 33 int summery regs */
#define CAV_CIU_INTX_SUM0_SP    0x8     /* one per core spacing = 0x8 */
#define CAV_CIU_INT_SUM1_OFF	0x108	/* int summery of device   */
#define CAV_CIU_INT33_SUM0_OFF	0x110   /* extra sum0 reg #34 ??? */

/* INTERRUPT ENABLE 
 * cavium ugly here en0 regs are immediately followed by the 
 * en1 regs - hence the addrs will jump by 0x10 
 * 
 * int0_en0 = ip2 for core 0 	0x200
 * int0_en1 = ip2 for core 0 	0x208
 * int1_en0 = ip3 for core 0	0x210
 * int1_en1 = ip3 for core 0 	0x218
 * ......
 *
 * note maybe want read/write operations to access both registers 
 * this way do away with confusing addressing
 */
#define CAV_CIU_INTX_EN0_OFF	0x200	/* start offset 34 int enable regs */
#define CAV_CIU_INTX_EN0_SP     0x10    /* one per core spaceing = 0x10 */
#define CAV_CIU_INTX_EN1_OFF	0x208	/* start offset 34 int enable regs */
#define CAV_CIU_INTX_EN1_SP     0x10    /* one per core spaceing = 0x10 */

/* MAIL BOX REGISTERS */

#define CAV_CIU_MBOX_SETX_OFF	0x600   /* 16 registers spacing = 0x8 */
#define CAV_CIU_MBOX_SETX_SP	0x8   
#define CAV_CIU_MBOX_CLRX_OFF	0x680	/* 16 registers spacing = 0x8 */
#define CAV_CIU_MBOX_CLRX_SP	0x8


/* Fuse Register Definition */
#define CAV_CIU_FUSE_OFF	0x728                 /* 1 register per box */
#define CAV_CIU_FUSE_MASK	0x00000000ffffffffULL /* lower 32 bits only */
                                                      /* each bit set implies */
                                                      /* active cpu */
#define CAV_CIU_FUSE \
    (CAV_CIU_BASE_ADDR + (CAV_CIU_FUSE_OFF))

/* Core Reset Register  - 1 register per device */
#define CAV_CIU_PP_RST_OFF      0x700
#define CAV_CUI_PP_RST_MASK     0x00000000ffffffffULL
#define CAV_CIU_PP_RST \
    (CAV_CIU_BASE_ADDR + (CAV_CIU_PP_RST_OFF))

/* Core Soft Reset Register  - 1 register per device */
#define CAV_CIU_SOFT_RST_OFF      0x740
#define CAV_CUI_SOFT_RST_MASK     0x00000000ffffffffULL
#define CAV_CIU_SOFT_RST \
    (CAV_CIU_BASE_ADDR + (CAV_CIU_SOFT_RST_OFF))

/* REGISTER Addressing Macros  */

/* INTERRUPT SUMMERY REGISTERS 
 * NOTE for all summery registers pass in core number 
 * however it is not really required for sum1 or int33_sum0
 * done for consistancy
 */
#define CAV_CIU_INTX_SUM0(corenum ) \
    (CAV_CIU_BASE_ADDR + (CAV_CIU_INTX_SUM0_OFF + \
    ((corenum) * CAV_CIU_INTX_SUM0_SP)))
#define CAV_CIU_INT_SUM1 \
    (CAV_CIU_BASE_ADDR + CAV_CIU_INT_SUM1_OFF )
#define CAV_CIU_INT33_SUM0 \
    (CAV_CIU_BASE_ADDR + CAV_CIU_INT33_SUM0_OFF )

/* INTERRUPT ENABLE REGISTERS  */
#define CAV_CIU_INTX_EN0(corenum ) \
    (CAV_CIU_BASE_ADDR + (CAV_CIU_INTX_EN0_OFF + \
    ((corenum) * CAV_CIU_INTX_EN0_SP)))

#define CAV_CIU_INTX_EN1(corenum ) \
    (CAV_CIU_BASE_ADDR + (CAV_CIU_INTX_EN1_OFF + \
    ((corenum) * CAV_CIU_INTX_EN1_SP)))

/* MAILBOX REGISTERS */
#define CAV_CIU_MBOX_SETX(regnum) \
    (CAV_CIU_BASE_ADDR + (CAV_CIU_MBOX_SETX_OFF + \
    ((regnum) * CAV_CIU_MBOX_SETX_SP)))
#define CAV_CIU_MBOX_CLRX(regnum) \
    (CAV_CIU_BASE_ADDR + (CAV_CIU_MBOX_CLRX_OFF + \
    ((regnum) * CAV_CIU_MBOX_CLRX_SP)))


/* BIT MASK AND SHIFT FOR REGISTERS */
/* INTERRUPT SUMMERY 0 */

#define CAV_CIU_INTX_SUM0_BOOTDMA_BIT 		63
#define CAV_CIU_INTX_SUM0_BOOTDMA_MASK 		0x0000000000000001ULL
#define CAV_CIU_INTX_SUM0_MII_BIT  		62
#define CAV_CIU_INTX_SUM0_MII_MASK 		0x0000000000000001ULL
#define CAV_CIU_INTX_SUM0_IPD_BIT 		61
#define CAV_CIU_INTX_SUM0_IPD_MASK 		0x0000000000000001ULL
#define CAV_CIU_INTX_SUM0_POWIQ_BIT 		60
#define CAV_CIU_INTX_SUM0_POWIQ_MASK 		0x0000000000000001ULL
#define CAV_CIU_INTX_SUM0_TWSI2_BIT  		59
#define CAV_CIU_INTX_SUM0_TWSI2_MASK 		0x0000000000000001ULL
#define CAV_CIU_INTX_SUM0_USB_BIT  		56
#define CAV_CIU_INTX_SUM0_USB_MASK 		0x0000000000000001ULL
#define CAV_CIU_INTX_SUM0_TIMER_BIT  		52
#define CAV_CIU_INTX_SUM0_TIMER_MASK 		0x000000000000000FULL
#define CAV_CIU_INTX_SUM0_IPDDRP_BIT  		50
#define CAV_CIU_INTX_SUM0_IPDDRP_MASK 		0x0000000000000001ULL
#define CAV_CIU_INTX_SUM0_GMSDRP_BIT  		48
#define CAV_CIU_INTX_SUM0_GMSDRP_MASK 		0x0000000000000001ULL
#define CAV_CIU_INTX_SUM0_TRACE_BIT  		47
#define CAV_CIU_INTX_SUM0_TRACE_MASK 		0x0000000000000001ULL
#define CAV_CIU_INTX_SUM0_RML_BIT  		46
#define CAV_CIU_INTX_SUM0_RML_MASK 		0x0000000000000001ULL
#define CAV_CIU_INTX_SUM0_TWSI_BIT  		45
#define CAV_CIU_INTX_SUM0_TWSI_MASK 		0x0000000000000001ULL
#define CAV_CIU_INTX_SUM0_WDOG_BIT  		44
#define CAV_CIU_INTX_SUM0_WDOG_MASK 		0x0000000000000001ULL
#define CAV_CIU_INTX_SUM0_PCIMSI_BIT  		40
#define CAV_CIU_INTX_SUM0_PCIMSI_MASK 		0x000000000000000FULL
#define CAV_CIU_INTX_SUM0_PCIINT_BIT  		36
#define CAV_CIU_INTX_SUM0_PCIINT_MASK 		0x000000000000000FULL
#define CAV_CIU_INTX_SUM0_UART_BIT  		34
#define CAV_CIU_INTX_SUM0_UART_MASK 		0x0000000000000003ULL
#define CAV_CIU_INTX_SUM0_MBOX_BIT  		32
#define CAV_CIU_INTX_SUM0_MBOX_MASK 		0x0000000000000003ULL
#define CAV_CIU_INTX_SUM0_GPIO_BIT  		16
#define CAV_CIU_INTX_SUM0_GPIO_MASK 		0x000000000000FFFFULL
#define CAV_CIU_INTX_SUM0_WORKQ_BIT  		0
#define CAV_CIU_INTX_SUM0_WORKQ_MASK 		0x000000000000FFFFULL

/* INTERRUPT SUMMERY 1 */

#define CAV_CIU_INT_SUM1_RST_BIT  		63
#define CAV_CIU_INT_SUM1_RST_MASK 		0x0000000000000001ULL
#define CAV_CIU_INT_SUM1_DFM_BIT  		56
#define CAV_CIU_INT_SUM1_DFM_MASK 		0x0000000000000001ULL
#define CAV_CIU_INT_SUM1_LMC0_BIT  		52
#define CAV_CIU_INT_SUM1_LMC0_MASK 		0x0000000000000001ULL
#define CAV_CIU_INT_SUM1_SRIO1_BIT  		51
#define CAV_CIU_INT_SUM1_SRIO1_MASK 		0x0000000000000001ULL
#define CAV_CIU_INT_SUM1_SRIO0_BIT  		50
#define CAV_CIU_INT_SUM1_SRIO0_MASK 		0x0000000000000001ULL
#define CAV_CIU_INT_SUM1_PEM1_BIT  		49
#define CAV_CIU_INT_SUM1_PEM1_MASK 		0x0000000000000001ULL
#define CAV_CIU_INT_SUM1_PEM0_BIT  		48
#define CAV_CIU_INT_SUM1_PEM0_MASK 		0x0000000000000001ULL
#define CAV_CIU_INT_SUM1_PTP_BIT  		47
#define CAV_CIU_INT_SUM1_PTP_MASK 		0x0000000000000001ULL
#define CAV_CIU_INT_SUM1_AGL_BIT  		46
#define CAV_CIU_INT_SUM1_AGL_MASK 		0x0000000000000001ULL
#define CAV_CIU_INT_SUM1_AGX0_BIT  		36
#define CAV_CIU_INT_SUM1_AGX0_MASK 		0x0000000000000001ULL
#define CAV_CIU_INT_SUM1_DPI_BIT  		35
#define CAV_CIU_INT_SUM1_DPI_MASK 		0x0000000000000001ULL
#define CAV_CIU_INT_SUM1_SLI_BIT  		34
#define CAV_CIU_INT_SUM1_SLI_MASK 		0x0000000000000001ULL
#define CAV_CIU_INT_SUM1_USB_BIT  		33
#define CAV_CIU_INT_SUM1_USB_MASK 		0x0000000000000001ULL
#define CAV_CIU_INT_SUM1_DFA_BIT  		32
#define CAV_CIU_INT_SUM1_DFA_MASK 		0x0000000000000001ULL
#define CAV_CIU_INT_SUM1_KEY_BIT  		31
#define CAV_CIU_INT_SUM1_KEY_MASK 		0x0000000000000001ULL
#define CAV_CIU_INT_SUM1_RAD_BIT  		30
#define CAV_CIU_INT_SUM1_RAD_MASK 		0x0000000000000001ULL
#define CAV_CIU_INT_SUM1_TIM_BIT  		29
#define CAV_CIU_INT_SUM1_TIM_MASK 		0x0000000000000001ULL
#define CAV_CIU_INT_SUM1_ZIP_BIT  		28
#define CAV_CIU_INT_SUM1_ZIP_MASK 		0x0000000000000001ULL
#define CAV_CIU_INT_SUM1_PKO_BIT  		27
#define CAV_CIU_INT_SUM1_PKO_MASK 		0x0000000000000001ULL
#define CAV_CIU_INT_SUM1_PIP_BIT  		26
#define CAV_CIU_INT_SUM1_PIP_MASK 		0x0000000000000001ULL
#define CAV_CIU_INT_SUM1_IPD_BIT  		25
#define CAV_CIU_INT_SUM1_IPD_MASK 		0x0000000000000001ULL
#define CAV_CIU_INT_SUM1_L2C_BIT  		24
#define CAV_CIU_INT_SUM1_L2C_MASK 		0x0000000000000001ULL
#define CAV_CIU_INT_SUM1_POW_BIT  		23
#define CAV_CIU_INT_SUM1_POW_MASK 		0x0000000000000001ULL
#define CAV_CIU_INT_SUM1_FPA_BIT  		22
#define CAV_CIU_INT_SUM1_FPA_MASK 		0x0000000000000001ULL
#define CAV_CIU_INT_SUM1_IOB_BIT  		21
#define CAV_CIU_INT_SUM1_IOB_MASK 		0x0000000000000001ULL
#define CAV_CIU_INT_SUM1_MIO_BIT  		20
#define CAV_CIU_INT_SUM1_MIO_MASK 		0x0000000000000001ULL
#define CAV_CIU_INT_SUM1_NAND_BIT  		19
#define CAV_CIU_INT_SUM1_NAND_MASK 		0x0000000000000001ULL
#define CAV_CIU_INT_SUM1_MII1_BIT  		18
#define CAV_CIU_INT_SUM1_MII1_MASK 		0x0000000000000001ULL
#define CAV_CIU_INT_SUM1_WDOG_BIT  		0
#define CAV_CIU_INT_SUM1_WDOG_MASK 		0x000000000000003FULL

/* INTERRUPT ENABLE 0 REGISTER */

#define CAV_CIU_INTX_EN0_BOOTDMA_BIT 		63
#define CAV_CIU_INTX_EN0_MII_BIT  		62
#define CAV_CIU_INTX_EN0_IPD_BIT 		61
#define CAV_CIU_INTX_EN0_POWIQ_BIT 		60
#define CAV_CIU_INTX_EN0_TWSI2_BIT  		59
#define CAV_CIU_INTX_EN0_USB_BIT  		56
#define CAV_CIU_INTX_EN0_TIMER_BIT  		52
#define CAV_CIU_INTX_EN0_IPDDRP_BIT  		50
#define CAV_CIU_INTX_EN0_GMSDRP_BIT  		48
#define CAV_CIU_INTX_EN0_TRACE_BIT  		47
#define CAV_CIU_INTX_EN0_RML_BIT  		46
#define CAV_CIU_INTX_EN0_TWSI_BIT  		45
#define CAV_CIU_INTX_EN_WDOG_BIT  		44
#define CAV_CIU_INTX_EN0_PCIMSI_BIT  		40
#define CAV_CIU_INTX_EN0_PCIINT_BIT  		36
#define CAV_CIU_INTX_EN0_UART_BIT  		34
#define CAV_CIU_INTX_EN0_MBOX_BIT  		32
#define CAV_CIU_INTX_EN0_GPIO_BIT  		16
#define CAV_CIU_INTX_EN0_WORKQ_BIT  		0

/* INTERRUPT ENABLE 1 REGISTER */

#define CAV_CIU_INT_EN1_RST_BIT  		63
#define CAV_CIU_INT_EN1_DFM_BIT  		56
#define CAV_CIU_INT_EN1_LMC0_BIT  		52
#define CAV_CIU_INT_EN1_SRIO1_BIT  		51
#define CAV_CIU_INT_EN1_SRIO0_BIT  		50
#define CAV_CIU_INT_EN1_PEM1_BIT  		49
#define CAV_CIU_INT_EN1_PEM0_BIT  		48
#define CAV_CIU_INT_EN1_PTP_BIT  		47
#define CAV_CIU_INT_EN1_AGL_BIT  		46
#define CAV_CIU_INT_EN1_AGX0_BIT  		36
#define CAV_CIU_INT_EN1_DPI_BIT  		35
#define CAV_CIU_INT_EN1_SLI_BIT  		34
#define CAV_CIU_INT_EN1_USB_BIT  		33
#define CAV_CIU_INT_EN1_DFA_BIT  		32
#define CAV_CIU_INT_EN1_KEY_BIT  		31
#define CAV_CIU_INT_EN1_RAD_BIT  		30
#define CAV_CIU_INT_EN1_TIM_BIT  		29
#define CAV_CIU_INT_EN1_ZIP_BIT  		28
#define CAV_CIU_INT_EN1_PKO_BIT  		27
#define CAV_CIU_INT_EN1_PIP_BIT  		26
#define CAV_CIU_INT_EN1_IPD_BIT  		25
#define CAV_CIU_INT_EN1_L2C_BIT  		24
#define CAV_CIU_INT_EN1_POW_BIT  		23
#define CAV_CIU_INT_EN1_FPA_BIT  		22
#define CAV_CIU_INT_EN1_IOB_BIT  		21
#define CAV_CIU_INT_EN1_MIO_BIT  		20
#define CAV_CIU_INT_EN1_NAND_BIT  		19
#define CAV_CIU_INT_EN1_MII1_BIT  		18
#define CAV_CIU_INT_EN1_WDOG_BIT  		0

/* Here are Octeon II CIU2 defines */

#define CAV_CIU2_SUM(core, intLine)                   \
    (0x8001070100000000ULL + 0x200 * (intLine - 2) + 0x8 * (core))

#define CAV_CIU2_RAW_PPX_IPX(core, intLine, type)     \
    (0x8001070100040000ULL + 0x200000 * (core) + 0x200 * (intLine - 2) + 0x1000 * (type))

#define CAV_CIU2_SRC_PPX_IPX(core, intLine, type)     \
    (0x8001070100080000ULL + 0x200000 * (core) + 0x200 * (intLine - 2) + 0x1000 * (type))

#define CAV_CIU2_EN_PPX_IPX(core, intLine, type)      \
    (0x8001070100090000ULL + 0x200000 * (core) + 0x200 * (intLine - 2) + 0x1000 * (type))

#define CAV_CIU2_EN_PPX_IPX_W1S(core, intLine, type)  \
    (0x80010701000A0000ULL + 0x200000 * (core) + 0x200 * (intLine - 2) + 0x1000 * (type))

#define CAV_CIU2_EN_PPX_IPX_W1C(core, intLine, type)  \
    (0x80010701000B0000ULL + 0x200000 * (core) + 0x200 * (intLine - 2) + 0x1000 * (type))

#define CAV_CIU2_ACK(core, intLine)                   \
    (0x80010701000C0000ULL + 0x200000 * (core) + 0x200 * (intLine - 2))

#define CAV_CIU2_MBOX_SETX(regnum)                    \
    (0x8001070100100400ull + (((regnum) & 0x1F) * CAV_CIU_MBOX_SETX_SP))

#define CAV_CIU2_MBOX_CLRX(regnum)                    \
    (0x8001070100100600ull + (((regnum) & 0x1F) * CAV_CIU_MBOX_CLRX_SP))

#define CAV_CIU2_INTR_CIU_READY (0x8001070100102008ull)

#define CAV_CIU2_NUM_INT_PER_TYPE       64
#define CAV_CIU2_NUM_INT_TYPES          9

#define CAV_CIU2_TYPE_WRKQ              0
#define CAV_CIU2_TYPE_WDOG              1
#define CAV_CIU2_TYPE_RML               2
#define CAV_CIU2_TYPE_MIO               3
#define CAV_CIU2_TYPE_IO                4
#define CAV_CIU2_TYPE_MEM               5
#define CAV_CIU2_TYPE_PKT               6
#define CAV_CIU2_TYPE_GPIO              7
#define CAV_CIU2_TYPE_MBOX              8

#define CAV_CIU2_IP2                    2
#define CAV_CIU2_IP3                    3
#define CAV_CIU2_IP4                    4

#define CAV_CIU2_SUM_MBOX0              60
#define CAV_CIU2_SUM_MBOX1              61
#define CAV_CIU2_SUM_MBOX2              62
#define CAV_CIU2_SUM_MBOX3              63

/* typedefs */

typedef cvmx_ciu_pp_rst_t CAV_CIU_PP_RST_T;
typedef cvmx_ciu_mbox_setx_t CAV_CIU_MBOX_T;
typedef cvmx_ciu_qlm2_t CAV_CIU_QLM2_T; 
typedef cvmx_ciu_soft_rst_t CAV_CIU_SOFT_RST_T;
#ifdef __cplusplus
}
#endif


#endif	/* __INCvxbMipsIntCtlrSPh */

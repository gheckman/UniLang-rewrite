/* rm9000.h - PMC-Sierra RM9000 CPU header */

/* Copyright 2005, 2010 Wind River Systems, Inc. */

/*
 * This file has been developed or significantly modified by the
 * MIPS Center of Excellence Dedicated Engineering Staff.
 * This notice is as per the MIPS Center of Excellence Master Partner
 * Agreement, do not remove this notice without checking first with
 * WR/Platforms MIPS Center of Excellence engineering management.
 */

/*
modification history
--------------------
01b,29apr10,pad  Moved extern C statement after include statements.
01a,14apr05,rlg  created for yosemite bsp based off of yosemite 5.5 bsp
*/

/*
This file contains I/O addresses and related constants for the
PMC-Sierra RM9000 CPU core. 
*/

#ifndef	__INCrm9000h
#define	__INCrm9000h

#include "vxWorks.h"

#ifdef __cplusplus
extern "C" {
#endif


/* Config Register Defines */

#define RM9000_CFG_K0_CACHE_WRITETHROUGH         0x00000001
#define RM9000_CFG_K0_CACHE_UNCACHE_BLOCK        0x00000002
#define RM9000_CFG_K0_CACHE_WRITEBACK            0x00000003
#define RM9000_CFG_K0_CACHE_COH_WRITEBACK_EXC    0x00000004
#define RM9000_CFG_K0_CACHE_COH_WRITEBACK        0x00000005
#define RM9000_CFG_K0_CACHE_UNCACHE_NONBLOCK     0x00000006
#define RM9000_CFG_K0_CACHE_FAST_PACKET          0x00000007
#define RM9000_CFG_SEC_CACHE_ENABLE              0x00000008

/* On Chip Device (OCD) Registers - Base Address */

#ifndef RM9000x2_OCD_BASE_ADDR
#define RM9000x2_OCD_BASE_ADDR             0xBB000000
#endif

#define RM9000_REG_ADDR(x) (RM9000x2_OCD_BASE_ADDR + x)

#ifndef _ASMLANGUAGE

/* rm9000x2 register read and write macros */

#define RM9000_REG_READ(offset)                             \
           *(volatile UINT32 *)(RM9000_REG_ADDR(offset))
#define RM9000_REG_WRITE(offset,regdata)                            \
           *(volatile UINT32 *)(RM9000_REG_ADDR(offset)) = regdata

#define RM9K_REG_READ32(offset)                             \
           *(volatile UINT32 *)(RM9000_REG_ADDR(offset))
#define RM9K_REG_WRITE32(offset,regdata)                            \
           *(volatile UINT32 *)(RM9000_REG_ADDR(offset)) = regdata

#define RM9K_REG_READ16(offset)                             \
           *(volatile UINT16 *)(RM9000_REG_ADDR(offset))
#define RM9K_REG_WRITE16(offset,regdata)                            \
           *(volatile UINT16 *)(RM9000_REG_ADDR(offset)) = regdata

#define RM9K_REG_READ8(offset)                             \
           *(volatile UINT8 *)(RM9000_REG_ADDR(offset))
#define RM9K_REG_WRITE8(offset,regdata)                            \
           *(volatile UINT8 *)(RM9000_REG_ADDR(offset)) = regdata

#define RM9K_REG_SET32(offset,regdata)                            \
           *(volatile UINT32 *)(RM9000_REG_ADDR(offset)) = (*(volatile UINT32 *)(RM9000_REG_ADDR(offset))) | regdata

#define RM9K_REG_CLEAR32(offset,regdata)                            \
	*(volatile UINT32 *)(RM9000_REG_ADDR(offset)) = (*(volatile UINT32 *)(RM9000_REG_ADDR(offset))) & ~regdata


#endif /* _ASMLANGUAGE */

/* Memory defines */

#define DRAM_CACHE_VIRT_BASE               K0BASE
#define DRAM_NONCACHE_VIRT_BASE            K1BASE
#define KSU_MASK     0xE0000000      /* Memory window selection bits */

/* On Chip Device (OCD) Registers */

#define RM9000x2_OCD_OCDINFO               0x0000
#define RM9000x2_OCD_XCAUFL                0x0010

#define RM9000x2_OCD_UPENR                 0x00f0   /* Micro Periph Enable */
#define RM9000x2_OCD_CPURSLMT              0x00f8   /* CPU Resource Limit */

#define RM9000x2_OCD_LKB0                  0x0100   /* Bank 0 Base Addr */
#define RM9000x2_OCD_LKM0                  0x0104   /* Bank 0 Addr Mask */
#define RM9000x2_OCD_LKB1                  0x0108   /* Bank 1 Base Addr */
#define RM9000x2_OCD_LKM1                  0x010C   /* Bank 1 Addr Mask */
#define RM9000x2_OCD_LKB2                  0x0110   /* Bank 2 Base Addr */
#define RM9000x2_OCD_LKM2                  0x0114   /* Bank 2 Addr Mask */
#define RM9000x2_OCD_LKB3                  0x0118   /* Bank 3 Base Addr */
#define RM9000x2_OCD_LKM3                  0x011C   /* Bank 3 Addr Mask */
#define RM9000x2_OCD_LKB4                  0x0120   /* Bank 4 Base Addr */
#define RM9000x2_OCD_LKM4                  0x0124   /* Bank 4 Addr Mask */
#define RM9000x2_OCD_LKB5                  0x0128   /* Bank 5 Base Addr */
#define RM9000x2_OCD_LKM5                  0x012C   /* Bank 5 Addr Mask */
#define RM9000x2_OCD_LKB6                  0x0130   /* Bank 6 Base Addr */
#define RM9000x2_OCD_LKM6                  0x0134   /* Bank 6 Addr Mask */
#define RM9000x2_OCD_LKB7                  0x0138   /* Bank 7 Base Addr */
#define RM9000x2_OCD_LKM7                  0x013C   /* Bank 7 Addr Mask */
#define RM9000x2_OCD_LKB8                  0x0140   /* Bank 8 Base Addr */
#define RM9000x2_OCD_LKM8                  0x0144   /* Bank 8 Addr Mask */
#define RM9000x2_OCD_LKB9                  0x0148   /* Bank 9 Base Addr */
#define RM9000x2_OCD_LKM9                  0x014C   /* Bank 9 Addr Mask */
#define RM9000x2_OCD_LKB10                 0x0150   /* Bank 10 Base Addr */
#define RM9000x2_OCD_LKM10                 0x0154   /* Bank 10 Addr Mask */
#define RM9000x2_OCD_LKB11                 0x0158   /* Bank 11 Base Addr */
#define RM9000x2_OCD_LKM11                 0x015C   /* Bank 11 Addr Mask */
#define RM9000x2_OCD_LKB12                 0x0160   /* Bank 12 Base Addr */
#define RM9000x2_OCD_LKM12                 0x0164   /* Bank 12 Addr Mask */
#define RM9000x2_OCD_LKB13                 0x0168   /* Bank 13 Base Addr */
#define RM9000x2_OCD_LKM13                 0x016C   /* Bank 13 Addr Mask */

#define RM9000x2_OCD_LDP0                  0x0200   
#define RM9000x2_OCD_LDP1                  0x0210   
#define RM9000x2_OCD_LDP2                  0x0220   
#define RM9000x2_OCD_LDP3                  0x0230   

#define RM9000x2_OCD_RSTSTATUS             0x0A20   /* Reset Status */
#define RM9000x2_OCD_RSTSET                0x0A24   /* Reset Set */
#define RM9000x2_OCD_RSTCLEAR              0x0A28   /* Reset Clear */

#define RM9000x2_OCD_SEM                   0x0A60   /* Semaphore Register */
#define RM9000x2_OCD_SEMSET                0x0A64   /* Semaphore Set */
#define RM9000x2_OCD_SEMCLR                0x0A68   /* Semaphore Clear */

/* 
 *  MAC subsytem registers
 */

/* MAC Subsystem */
#define RM9000_GE_DEVICE_ID_REG  		0x0000
#define RM9000_GE_RESET				0x0004
#define RM9000_GE_DLL_STATUS			0x0008
#define RM9000_TSB_CONTROL_0			0x000c
#define RM9000_TSB_CONTROL_1			0x0010
#define RM9000_PRIORITY_CHECKSUM_PORT_0		0x1038
#define RM9000_PRIORITY_CHECKSUM_PORT_1		0x2038
#define RM9000_PRIORITY_CHECKSUM_PORT_2		0x3038

/*
 *  SCMB subsystem
 */
#define RM9000_SCMB_0_CONTROL                	0x0180  /* SCMB 0 Control */
#define RM9000_SCMB_0_CLKA                   	0x0184  /* SCMB 0 Clock A */
#define RM9000_SCMB_0_CLKB                   	0x0188  /* SCMB 0 Clock B */
#define RM9000_MDIO_0_COMMAND                	0x0190  /* MDIO 0 Command */
#define RM9000_MDIO_0_DEVICE_PORT_ADDRESS    	0x0194  /* MDIO 0 Device and Port addrs */
#define RM9000_MDIO_0_DATA                   	0x0198  /* MDIO 0 Data */
#define RM9000_MDIO_0_INTERRUPTS             	0x019c  /* MDIO 0 Interrupts */

#define RM9000_2BI_0_CONFIG			0x01a0	/* 2BI 0 Configuration */
#define RM9000_2BI_0_COMMAND			0x01a4	/* 2BI 0 Command */
#define RM9000_2BI_0_ADDRESS			0x01a8	/* 2BI 0 Address */
#define RM9000_2BI_0_DATA0			0x01ac	/* 2BI 0 Data bits 15:0 */
#define RM9000_2BI_0_DATA1			0x01b0	/* 2BI 0 Data bits 31:16 */
#define RM9000_2BI_0_DATA2			0x01b4	/* 2BI 0 Data bits 47:32 */
#define RM9000_2BI_0_DATA3			0x01b8	/* 2BI 0 Data bits 63:48 */
#define RM9000_2BI_0_INTERRUPTS			0x01bc	/* 2BI 0 Interrupts */

/* RM9000 SDRAM Register Defines */

#define RM9000_SDRAM_GEN_CONFIG_REG        0x0300
#define RM9000_SDRAM_MODE_REG              0x0304
#define RM9000_SDRAM_BANK0_CONFIG_REG      0x0340
#define RM9000_SDRAM_BANK1_CONFIG_REG      0x0350
#define RM9000_SDRAM_BANK2_CONFIG_REG      0x0360
#define RM9000_SDRAM_BANK3_CONFIG_REG      0x0370
#define RM9000_SDRAM_BANK0_TIMING_REG      0x0344
#define RM9000_SDRAM_BANK1_TIMING_REG      0x0354
#define RM9000_SDRAM_BANK2_TIMING_REG      0x0364
#define RM9000_SDRAM_BANK3_TIMING_REG      0x0374

/* (PRId) Processor Revision Identifier Register definitions */

#define RM9000x2_IMP_NUM                   0x34	        /* RM9000x2 */
#define RM9000x2_PRID_REV_MASK             0x000000FF
#define RM9000x2_PRID_REV_SHIFT            0
#define RM9000x2_PRID_IMP_NUM_MASK         0x0000FF00
#define RM9000x2_PRID_IMP_NUM_SHIFT        8
#define RM9000x2_PRID_CPU_NUM_MASK         0x07000000
#define RM9000x2_PRID_CPU_NUM_SHIFT        24

/* (UPENR) Microprocessor Peripherals Enable definitions */

#define RM9000x2_RESET_CONTROL_ENABLE      0x01
#define RM9000x2_RESET_CONTROL_DISABLE     0x00

/* (RSTSTATUS, RSTSET, RSTCLEAR) Reset Register definitions */

#define RM9000x2_RESET_PROC_0              0x01
#define RM9000x2_RESET_PROC_1              0x02
#define RM9000x2_RESET_SEC_PROC            0x02   /* reset Secondary Procs */

/* (SEM, SEMSET, SEMCLR) Semaphore Register definitions */

#define RM9000_ROM_SEM_BIT  0x00000001     /* sem bit to use by rm9000Init.s */

/* Cache Defines */

#define RM9000x2_L2_CACHE_SIZE         0x00040000      /* 256 KBytes */
#define RM9000x2_L3_CACHE_SIZE         0x00000000      /* No L3 cache */
#define RM9000x2_CACHE_LINE_SIZE       32

/* Interrupt Priority Control Register bit defines */

#define RM9000x2_IPC_VEC_SPACING_MASK  0x0000001F
#define RM9000x2_IPC_IM15              0x00008000      /* MASK OCD Fault int */
#define RM9000x2_IPC_IM14              0x00004000      /* MASK OCD Flag int */
#define RM9000x2_IPC_IM13              0x00002000      /* MASK Perf counter */
#define RM9000x2_IPC_IM12              0x00001000      /* MASK alt timer int */
#define RM9000x2_IPC_IM11              0x00000800      /* MASK level 9 int */
#define RM9000x2_IPC_IM10              0x00000400      /* MASK level 8 int */
#define RM9000x2_IPC_IM9               0x00000200      /* MASK level 7 int */
#define RM9000x2_IPC_IM8               0x00000100      /* MASK level 6 int */
#define RM9000x2_IPC_TIMER_EXCL_IPL12  0x00000080      /* timer on int 12 */
#define RM9000x2_IPC_IM_MASK           0x0000FF00      /* extended int mask */

/* External Interrupt Pin (n) Configuration registers */

#define RM9000x2_EXT_INTPIN0_CONFIG        0x0A40
#define RM9000x2_EXT_INTPIN1_CONFIG        0x0A44
#define RM9000x2_EXT_INTPIN2_CONFIG        0x0A48
#define RM9000x2_EXT_INTPIN3_CONFIG        0x0A4C
#define RM9000x2_EXT_INTPIN4_CONFIG        0x0A50
#define RM9000x2_EXT_INTPIN5_CONFIG        0x0A54
#define RM9000x2_EXT_INTPIN6_CONFIG        0x0A58
#define RM9000x2_EXT_INTPIN7_CONFIG        0x0A5C

/* External Interrupt Pin (n) register defines */

#define RM9000x2_VECTOR_MASK               0x00FF0000  /* level & status bit */
#define RM9000x2_VECTOR_SHIFT              16
#define RM9000x2_PROC_INT_MASK             0x00E00000  /* int level */
#define RM9000x2_PROC_INT_SHIFT            21
#define RM9000x2_INT_STATUS_BIT_MASK       0x001F0000  /* bit in status reg */
#define RM9000x2_INT_STATUS_BIT_SHIFT      16
#define RM9000x2_MESSAGE_TYPE_MASK         0x00000700  /* msg type */
#define RM9000x2_MESSAGE_TYPE_SHIFT        8
#define RM9000x2_INTERRUPT_DEST_MASK       0x00000003  /* proc 0 or 1 */
#define RM9000x2_INTERRUPT_DEST_PROC0      1           /* proc 0 select */
#define RM9000x2_INTERRUPT_DEST_PROC1      2           /* proc 1 select */

/* Processor 0 Interrupt Status, Mask, Set and Clear registers */

#define RM9000x2_INTP0_STATUS_0            0x1B00
#define RM9000x2_INTP0_MASK_0              0x1B04
#define RM9000x2_INTP0_SET_0               0x1B08
#define RM9000x2_INTP0_CLEAR_0             0x1B0C
#define RM9000x2_INTP0_STATUS_1            0x1B10
#define RM9000x2_INTP0_MASK_1              0x1B14
#define RM9000x2_INTP0_SET_1               0x1B18
#define RM9000x2_INTP0_CLEAR_1             0x1B1C
#define RM9000x2_INTP0_STATUS_2            0x1B20
#define RM9000x2_INTP0_MASK_2              0x1B24
#define RM9000x2_INTP0_SET_2               0x1B28
#define RM9000x2_INTP0_CLEAR_2             0x1B2C
#define RM9000x2_INTP0_STATUS_3            0x1B30
#define RM9000x2_INTP0_MASK_3              0x1B34
#define RM9000x2_INTP0_SET_3               0x1B38
#define RM9000x2_INTP0_CLEAR_3             0x1B3C
#define RM9000x2_INTP0_STATUS_4            0x1B40
#define RM9000x2_INTP0_MASK_4              0x1B44
#define RM9000x2_INTP0_SET_4               0x1B48
#define RM9000x2_INTP0_CLEAR_4             0x1B4C
#define RM9000x2_INTP0_STATUS_5            0x1B50
#define RM9000x2_INTP0_MASK_5              0x1B54
#define RM9000x2_INTP0_SET_5               0x1B58
#define RM9000x2_INTP0_CLEAR_5             0x1B5C
#define RM9000x2_INTP0_STATUS_6            0x1B60
#define RM9000x2_INTP0_MASK_6              0x1B64
#define RM9000x2_INTP0_SET_6               0x1B68
#define RM9000x2_INTP0_CLEAR_6             0x1B6C
#define RM9000x2_INTP0_STATUS_7            0x1B70
#define RM9000x2_INTP0_MASK_7              0x1B74
#define RM9000x2_INTP0_SET_7               0x1B78
#define RM9000x2_INTP0_CLEAR_7             0x1B7C

/* Processor 1 Interrupt Status, Mask, Set and Clear registers */

#define RM9000x2_INTP1_STATUS_0            0x2B00
#define RM9000x2_INTP1_MASK_0              0x2B04
#define RM9000x2_INTP1_SET_0               0x2B08
#define RM9000x2_INTP1_CLEAR_0             0x2B0C
#define RM9000x2_INTP1_STATUS_1            0x2B10
#define RM9000x2_INTP1_MASK_1              0x2B14
#define RM9000x2_INTP1_SET_1               0x2B18
#define RM9000x2_INTP1_CLEAR_1             0x2B1C
#define RM9000x2_INTP1_STATUS_2            0x2B20
#define RM9000x2_INTP1_MASK_2              0x2B24
#define RM9000x2_INTP1_SET_2               0x2B28
#define RM9000x2_INTP1_CLEAR_2             0x2B2C
#define RM9000x2_INTP1_STATUS_3            0x2B30
#define RM9000x2_INTP1_MASK_3              0x2B34
#define RM9000x2_INTP1_SET_3               0x2B38
#define RM9000x2_INTP1_CLEAR_3             0x2B3C
#define RM9000x2_INTP1_STATUS_4            0x2B40
#define RM9000x2_INTP1_MASK_4              0x2B44
#define RM9000x2_INTP1_SET_4               0x2B48
#define RM9000x2_INTP1_CLEAR_4             0x2B4C
#define RM9000x2_INTP1_STATUS_5            0x2B50
#define RM9000x2_INTP1_MASK_5              0x2B54
#define RM9000x2_INTP1_SET_5               0x2B58
#define RM9000x2_INTP1_CLEAR_5             0x2B5C
#define RM9000x2_INTP1_STATUS_6            0x2B60
#define RM9000x2_INTP1_MASK_6              0x2B64
#define RM9000x2_INTP1_SET_6               0x2B68
#define RM9000x2_INTP1_CLEAR_6             0x2B6C
#define RM9000x2_INTP1_STATUS_7            0x2B70
#define RM9000x2_INTP1_MASK_7              0x2B74
#define RM9000x2_INTP1_SET_7               0x2B78
#define RM9000x2_INTP1_CLEAR_7             0x2B7C

/* base vector number for user programmable vectors */

/* TLB Defines */

#undef TLB_ENTRIES
#define TLB_ENTRIES                    64
#define TLB_4K_PAGE_SIZE_MASK          0x00000000
#define TLB_16K_PAGE_SIZE_MASK         0x00006000
#define TLB_64K_PAGE_SIZE_MASK         0x0001E000
#define TLB_256K_PAGE_SIZE_MASK        0x0007E000
#define TLB_1M_PAGE_SIZE_MASK          0x001FE000
#define TLB_4M_PAGE_SIZE_MASK          0x007FE000
#define TLB_16M_PAGE_SIZE_MASK         0x01FFE000
#define TLB_64M_PAGE_SIZE_MASK         0x07FFE000
#define TLB_256M_PAGE_SIZE_MASK        0x1FFFE000
#define TLB_PG_SVPN                    0xfffff000      /* SW page no mask */
#define TLB_PG_SHIFT                   6
#define TLB_PG_FRAME                   0x3fffffc0
#define TLB_P_ENTRY_SHIFT              12     /* convert VM pagenum to VA */

#define TLB_PG_G                       0x00000001      /* HW */
#define TLB_PG_V                       0x00000002
#define TLB_PG_NV                      0x00000000
#define TLB_PG_M                       0x00000004
#define TLB_PG_ATTR                    0x0000003f
#define TLB_PG_UNCACHED                0x00000010
#define TLB_PG_CACHED                  0x00000018
#define TLB_PG_CACHEMODE               0x00000038
#define TLB_PG_IOPAGE    (TLB_PG_G | TLB_PG_V | TLB_PG_M | TLB_PG_UNCACHED)

#define TLBLO_MODE                     TLB_PG_IOPAGE
#define TLBLO_PFNMASK                  TLB_PG_FRAME
#define TLBHI_VPN2MASK                 0xffffe000
#define TLBLO_PAGEMASK		       TLB_256M_PAGE_SIZE_MASK
#define TLBLO_PAGEMASK_SIZE	(TLBLO_PAGEMASK | TLB_PG_IOPAGE | 0x1000)
#define TLBLO_LO1_OFFSET               0x2000

/* Interrupt Level bit defines to their respective register */

/* interrupt priority control register */

#define INT_LVL_OCD_FAULT       SR_IBIT8        /* OCD Fault */
#define INT_LVL_OCD_FLAG        SR_IBIT7        /* OCD Flag (DMA complete) */
#define INT_LVL_PERF            SR_IBIT6        /* Performance Counter */
#define INT_LVL_ALT_TIMER       SR_IBIT5        /* alt timer interrupt */
#define INT_LVL_EXT_INT_9       SR_IBIT4        /* ext interrupt 9 */
#define INT_LVL_EXT_INT_8       SR_IBIT3        /* ext interrupt 8 */
#define INT_LVL_EXT_INT_7       SR_IBIT2        /* ext interrupt 7 */
#define INT_LVL_EXT_INT_6       SR_IBIT1        /* ext interrupt 6 */

/* status register bit definitions */

#define INT_LVL_EXT_INT_5       0x00008000      /* ext interrupt 5 */
#define INT_LVL_EXT_INT_4       0x00004000      /* ext interrupt 4 */
#define INT_LVL_EXT_INT_3       0x00002000      /* ext interrupt 3 */
#define INT_LVL_EXT_INT_2       0x00001000      /* ext interrupt 2 */
#define INT_LVL_EXT_INT_1       0x00000800      /* ext interrupt 1 */
#define INT_LVL_EXT_INT_0       0x00000400      /* ext interrupt 0 */
#define INT_LVL_SW1             0x00000200      /* sw interrupt 1 (fixed) */
#define INT_LVL_SW0             0x00000100      /* sw interrupt 0 (fixed) */

/* Exception Vector Table offset values */

#define RM9000_CPU1_VEC_OFFSET	0x08000000  /* offset for CPU1 Exc Vec Tbl */

/* 
 * RM9000 Interrupt Controller Notes
 * There are 32 interrupt sources for each of the 8 interrupt levels (0-7) 
 * SW Interrupts are generated via the set register for the level
 * SW Interrupts are cleared via the clear register for the level
 * (processor 0 registers 0x1B00 - 0x1B7C
 * and Processor 1 registers 0x2B00 - 0x2B7C).  
 * One external interrupt can be mapped per interrupt level for the externally
 * generated h/w interrupt.
 */

/* and 8 levels internal to rm9000x2 it can set and clear */

#define RM9000x2_INT_LVLS_INTERNAL  8
#define RM9000x2_INT_SRCS_INTERNAL  32

/* Exception Table Defines 
*
*	moved from yosemiteRm9k.h to here
*	this will also work for the jaguuar
*
*/

#define RM9K_CPU1_TLB_EXC_ADDR       0x88000000
#define RM9K_CPU1_XTLB_EXC_ADDR      0x88000080
#define RM9K_CPU1_CACHE_EXC_ADDR     0x88000100
#define RM9K_CPU1_NORM_EXC_ADDR      0x88000180

/*
*	defines for romInit.s
*	when building bootroms
*/

#define RM9K_CONF000    0x00d0
#define RM9K_CONF032    0x00d4
#define RM9K_CONF064    0x00d8
#define RM9K_CONF096    0x00dc
#define RM9K_CONF128    0x00e0
#define RM9K_CONF160    0x00e4
#define RM9K_CONF192    0x00e8
#define RM9K_CONF224    0x00ec

#ifdef __cplusplus
}
#endif
#endif /* __INCrm9000h */

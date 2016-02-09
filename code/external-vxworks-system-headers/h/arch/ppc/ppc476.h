/* ppc476.h - PowerPC 476 specific header */

/*
 * Copyright (c) 2009-2012, 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
03jan14,p_x  add _PPC_MSR_BIT_FP macro (WIND00444989)
01m,26jun12,pad  use common ESR definitions.
01l,19jun12,x_s  added PPC476 PVR value definitions.
01k,15may12,x_s  removed PPC476_REV2_FIX definition for PPC476 Rev2.1.
01j,13mar12,x_s  removed erroneous macro definitions. (WIND00312647)
01i,22mar11,x_z  added workaround for PPC476 REV2.
01h,17dec10,x_z  added L1 Cache definitions.
01g,15dec10,x_z  added bit definition for _DBCR0_EDM; remove some incorrect
                 macros to support hard float point.
01f,20oct10,x_z  added bit definitions for DBCR and DBSR;
                 removed workaround for DCBX instructions for REV2 core.
01e,08oct10,x_z  removed CPU_VARIANT; fixed definitions for TSR;
                 used _WRS_HARDWARE_FP to disable FP support;
                 updated definition for MCSR
01d,08sep10,x_z  removed _PPC_PVR_CACHE_SIZE_FIELD and _WRS_I_CACHE_TAG_VIRTUAL;
                 fixd cache line size; removed FP support
01c,25aug10,x_z  corrected some register definitions.
01b,25aug10,x_z  removed _DBCR0_EDM until WDB is supported.
01a,28dec09,x_s  created.
*/

#ifndef __INCppc476h
#define __INCppc476h

#ifdef __cplusplus
extern "C" {
#endif

/* 
 * PPC476 REV2 has some errata, so the workaround for them must be applied. 
 * PPC476 REV2.1 has corrected these errata, the workaround would not be done 
 * for REV2.1 silicon revision by dynamic distinguish silicon version. 
 */

#define PPC476_REV2_FIX

/* 
 * PVR:
 * For PPC476, PVR value should be 0xZZZ52RRZ. 
 * Where Z represents digits chosen by SOC owner and all Z digits are 
 * application specific. 
 * The 52 represents a ppc476 and RR digits represent core revision levels, 
 * and all four (52RR) of these digits are assigned by IBM. 
 */

#define PPC476_PVR_CORE_REV_MSB 20
#define PPC476_PVR_CORE_REV_LSB 27
#define PPC476_PVR_CORE_REV_0   0x08
#define PPC476_PVR_CORE_REV_1   0x0c

/* MMU supports software TLB miss handler */

#define _WRS_TLB_MISS_CLASS_SW  1
#undef  _WRS_TLB_MISS_CLASS_HW

/* MMU uses PID register to extend virtual address tag */

#define _WRS_MMU_CLASS_PID_REG  1
#undef  _WRS_MMU_CLASS_SR_REGS
#undef  _WRS_MMU_CLASS_NONE

/* MMU ASID context register name for _WRS_MMU_CLASS_PID_REG */

#define _PPC_PID_REG            PID

/*
 * The L1 cache line size is 32 bytes, and the L2 cache size is 128 bytes.
 * Therefore, all cache operations are handled in a way that the L1 cache
 * operates on its four cache lines independently from the L2 cache. In other
 * words, all cache instrcutions will work with 128-byte cache line size after
 * CCR0[ICS] is set to make that icbi request size is set to 128 bytes.
 */

#define _CPU_CACHE_ALIGN_SHIFT  7   /* 128-byte lines */
#define _CPU_CACHE_ALIGN_SIZE   128

/* L1 Cache defines */

#define L1ICACHE_WAYS           4
#define L1ICACHE_SETS           256
#define L1ICACHE_LINE_SIZE      32
#define L1ICACHE_LINES          (L1ICACHE_SETS * L1ICACHE_WAYS)
#define L1ICACHE_SIZE           (L1ICACHE_LINE_SIZE * L1ICACHE_LINES)
#define L1DCACHE_WAYS           4
#define L1DCACHE_SETS           256
#define L1DCACHE_LINE_SIZE      32
#define L1DCACHE_LINES          (L1DCACHE_SETS * L1DCACHE_WAYS)
#define L1DCACHE_SIZE           (L1DCACHE_LINE_SIZE * L1DCACHE_LINES)

#define _CACHE_LINE_MASK        0x7F

#define _PPC_CACHE_UNIFIED      FALSE

#define PPC_NO_REAL_MODE

/* Processor control */

#define CCR0    0x3B3   /* Core Configuration Register 0 */
#define CCR1    0x378   /* Core Configuration Register 1 */
#define CCR2    0x379   /* Core configuration Register 2 */
#define PIR     0x11E   /* Processor ID Register */
#define SPRG4   0x104   /* Special Purpose Register General 4 */
#define SPRG4_R SPRG4   /* read */
#define SPRG4_W 0x114   /* write */
#define SPRG5   0x105   /* Special Purpose Register General 5 */
#define SPRG5_R SPRG5   /* read */
#define SPRG5_W 0x115   /* write */
#define SPRG6   0x106   /* Special Purpose Register General 6 */
#define SPRG6_R SPRG6   /* read */
#define SPRG6_W 0x116   /* write */
#define SPRG7   0x107   /* Special Purpose Register General 7 */
#define SPRG7_R SPRG7   /* read */
#define SPRG7_W 0x117   /* write */
#define SPRG8   0x25c   /* Special Purpose Register General 8 */
#define USPRG0  0x100   /* User Special Purpose Register General 0 */
#define DCRIPR  0x37B   /* DCR Immediate Prefix Register */

/*
 * Don't define DEC -- asmPpc.h has the correct value, and defining it
 * here breaks C and C++ code (in target/src/zinc/common/z_int.cpp and
 * target/src/os/fioLib.c) that uses DEC with OCT and HEX as members of
 * an enum.
 * #define      DEC     0x016   /@ Decrementer @/
 *
 * The following are also defined correctly in asmPpc.h.  They are
 * omitted here to prevent compiler warnings about redefinition.
 * #define      CTR     0x009   /@ Count Register @/
 * #define      LR      0x008   /@ Link Register @/
 * #define      PVR     0x11F   /@ Processor Version Register @/
 * #define      SPRG0   0x110   /@ Special Purpose Register General 0 @/
 * #define      SPRG1   0x111   /@ Special Purpose Register General 1 @/
 * #define      SPRG2   0x112   /@ Special Purpose Register General 2 @/
 * #define      SPRG3   0x113   /@ Special Purpose Register General 3 @/
 * #define      SPRG3_R 0x103   /@ ????? /
 * #define      SRR0    0x01A   /@ Save/Restore Register 0 @/
 * #define      SRR1    0x01B   /@ Save/Restore Register 1 @/
 * #define      XER     0x001   /@ Integer Exception Register @/
 */

/* Interrupt and exceptions */

#define CSRR0   0x03A   /* Critical Save/Restore Register 0 */
#define CSRR1   0x03B   /* Critical Save/Restore Register 1 */
#define DEAR    0x03D   /* Data Exception Address Register */
#define ESR     0x03E   /* Exception Syndrome Register */

#define IVOR0   0x190   /* Critical Input */
#define IVOR1   0x191   /* Machine Check */
#define IVOR2   0x192   /* Data Storage */
#define IVOR3   0x193   /* Instruction Storage */
#define IVOR4   0x194   /* External Input */
#define IVOR5   0x195   /* Alignment */
#define IVOR6   0x196   /* Program */
#define IVOR7   0x197   /* Floating Point Unavailable */
#define IVOR8   0x198   /* System Call */
#define IVOR9   0x199   /* Auxiliary Processor Unavailable */
#define IVOR10  0x19A   /* Decrementer */
#define IVOR11  0x19B   /* Fixed Interval Timer */
#define IVOR12  0x19C   /* Watchdog Timer */
#define IVOR13  0x19D   /* Data TLB Error */
#define IVOR14  0x19E   /* Instruction TLB Error */
#define IVOR15  0x19F   /* Debug */
#define IVPR    0x03F   /* Interrupt Vector Prefix Register */
#define MCSRR0  0x23A   /* Machine Check Save/Restore Register 0 */
#define MCSRR1  0x23B   /* Machine Check Save/Restore Register 1 */
#define MCSR    0x23C   /* Machine Check Status Register */
#define MCSRC   0x33C   /* Machine Check Status Register for clean */

/* Cache */

#define DCDBTRH 0x39D   /* Data Cache Debug Tag Register High */
#define DCDBTRL 0x39C   /* Data Cache Debug Tag Register Low */
#define DCESR   0x352   /* Data Cache Exception Syndrome Register */
#define ICDBDR0 0x3D3   /* Instruction Cache Debug Data Register 0 */
#define ICDBDR1 0x3D4   /* Instruction Cache Debug Data Register 1 */
#define ICDBTRH 0x39F   /* Instruction Cache Debug Tag Register High */
#define ICDBTRL 0x39E   /* Instruction Cache Debug Tag Register Low */
#define ICESR   0x353   /* Instruction Cache Exception Syndrome Register */
#define IOCCR   0x35C   /* Instruction Opcode Compare Control Register */
#define IOCR1   0x35D   /* Instruction Opcode Compare Register 1 */
#define IOCR2   0x35E   /* Instruction Opcode Compare Register 2 */

/* Debug */

#define DAC1    0x13C   /* Data Cache Address Compare 1 Register */
#define DAC2    0x13D   /* Data Cache Address Compare 2 Register */
#define DVC1    0x13E   /* Data Value Compare 1 */
#define DVC2    0x13F   /* Data Value Compare 2 */
#define DBCR0   0x134   /* Debug Control Register 0 */
#define DBCR1   0x135   /* Debug Control Register 1 */
#define DBCR2   0x136   /* Debug Control Register 2 */
#define DBDR    0x3F3   /* Debug Data Register */
#define DBSR    0x130   /* Debug Status Register */
#define IAC1    0x138   /* Instruction Address Compare 1 */
#define IAC2    0x139   /* Instruction Address Compare 2 */
#define IAC3    0x13A   /* Instruction Address Compare 3 */
#define IAC4    0x13B   /* Instruction Address Compare 4 */
                        /* Xer is 0x001 has been defined */

/* MMU SPR Summary */

#define PID     0x030   /* Process ID */
#define RMPD    0x339   /* Real Mode Page Description Register */
#define MMUBE0  0x334   /* MMU Bolted Entries 0 Register */
#define MMUBE1  0x335   /* MMU Bolted Entries 1 Register */
#define SSPCR   0x33E   /* Supervisor Search Priority Configuration Register */
#define USPCR   0x33F   /* User Search Priority Configuration Register */
#define ISPCR   0x33D   /* Invalidate/Search Priority Configuration Register */
#define RSTCFG  0x39B   /* Reset Configuration */
#define MMUCR   0x3B2   /* Memory Management Unit Control Register */

/* Timers */

#define DECAR   0x036   /* Decrementer Auto-Reload */
#define TBL_R   0x10C   /* Time Base Lower, read */
#define TBL_W   0x11C   /* Time Base Lower, write */
#define TBU_R   0x10D   /* Time Base Upper, read */
#define TBU_W   0x11D   /* Time Base Upper, write */
#define TCR     0x154   /* Timer Control Register */
#define TSR     0x150   /* Timer Status Register (R/C) */
#define TSR_W   0x350   /* Timer Status Register (Write) */

/* MSR (upper half) definitions */

/* archPpc.h defines a generic MSR.  Here we define changes from that base */

#undef  _PPC_MSR_SF_U           /* 64 bit mode not implemented */
#undef  _PPC_MSR_POW_U          /* power management not supported */
#undef  _PPC_MSR_ILE_U          /* little endian mode not supported */

#define _PPC_MSR_WE_U   0x0004          /* wait state enable */
#define _PPC_MSR_CE_U   0x0002          /* critical interrupt enable */
#define _PPC_MSR_WE     0x00040000      /* wait state enable */
#define _PPC_MSR_CE     0x00020000      /* critical interrupt enable */

/* MSR (lower half) definitions */

#undef  _PPC_MSR_IR             /* insn address translation (always on) */
#undef  _PPC_MSR_DR             /* data address translation (always on) */
#undef  _PPC_MSR_SE             /* single step unsupported */
#undef  _PPC_MSR_BE             /* branch trace not supported */
#undef  _PPC_MSR_IP             /* exception prefix bit not supported */
#undef  _PPC_MSR_RI             /* recoverable interrupt unsupported */
#undef  _PPC_MSR_LE             /* little endian mode unsupported */
#undef  _PPC_MSR_BIT_LE         /* little endian mode unsupported */

#define _PPC_MSR_DWE    0x0400  /* debug wait enable */
#define _PPC_MSR_DE     0x0200  /* debug exception enable */
#define _PPC_MSR_IS     0x0020  /* insn address space selector */
#define _PPC_MSR_DS     0x0010  /* data address space selector */
#define _PPC_MSR_PMM    0x0004  /* Enable gathering statistics for marked processes */

/* MSR bit fields */

#define _PPC_MSR_BIT_WE     13
#define _PPC_MSR_BIT_CE     14
#define	_PPC_MSR_BIT_FP		18
#define _PPC_MSR_BIT_DWE    21
#define _PPC_MSR_BIT_DE     22
#define _PPC_MSR_BIT_IS     26      /* MSR Inst Translation bit - IS */
#define _PPC_MSR_BIT_DS     27      /* MSR Data Translation bit - DS */
#define _PPC_MSR_BIT_PMM    19      /* Performance monitor mark */

/* INT_MASK definition (mask EE & CE bits) : overwrite the one in asmPpc.h */

#undef  INT_MASK
#define INT_MASK(src, des) \
    rlwinm  des, src, 0, _PPC_MSR_BIT_EE+1, _PPC_MSR_BIT_EE-1; \
    rlwinm  des, des, 0, _PPC_MSR_BIT_CE+1, _PPC_MSR_BIT_CE-1

/*
 * PPC476 has FPU always.
 *
 * Note: This is ultimately controlled by the TOOL setting used to compile the
 * architecture code:  TOOL=gnu or TOOL=diab with CPU=PPC476 will set
 * _WRS_HARDWARE_FP; TOOL=sfdiab or TOOL=sfgnu will not.
 */

#ifndef _WRS_HARDWARE_FP
#   undef  _PPC_MSR_FP         /* floating point unsupported */
#   undef  _PPC_MSR_FE1        /* floating point not supported */
#   undef  _PPC_MSR_FE0        /* floating point not supported */
#endif /* _WRS_HARDWARE_FP */

/* MSR MMU Bit extraction */

#define _PPC_MSR_MMU_RI_EXTRACT(src, dst) \
    rlwinm  dst, src, 0, _PPC_MSR_BIT_IS, _PPC_MSR_BIT_DS

#ifndef _PPC_MSR_FP

/* No FP, so _PPC_MSR_MMU_RI_FP_EXTRACT is the same */

#define _PPC_MSR_MMU_RI_FP_EXTRACT  _PPC_MSR_MMU_RI_EXTRACT

#else   /* _PPC_MSR_FP */

#define _PPC_MSR_MMU_RI_FP_EXTRACT(src, dst) \
    li  dst, _PPC_MSR_IS | _PPC_MSR_DS | _PPC_MSR_FP ; \
    and dst, dst, src

#endif  /* _PPC_MSR_FP */

/* The setting in archPpc.h is wrong for the PPC476 */

#undef  _PPC_MSR_POWERUP
#define _PPC_MSR_POWERUP        0x0000  /* state of MSR at powerup */

/* Bits in the upper half of CCR0 */

#define _PPC_CCR0_PRE_U         0x4000  /* dcache Parity Recoverability Enab */
#define _PPC_CCR0_FDCI_U        0x1000  /* force L1 D-Cache inhibited */
#define _PPC_CCR0_CRPE_U        0x0800  /* Cache Read Parity Enable */
#define _PPC_CCR0_DLMQ_U        0x0040  /* disable D-Cache load miss queue */
#define _PPC_CCR0_ICS_U         0x0020  /* 128-byte icbi request */
#define _PPC_CCR0_DAPUIB_U      0x0010  /* Disable APU Instruction Broadcast */
#define _PPC_CCR0_BIT_DAPUIB_U  11      /* Disable APU Instruction Broadcast */

/* Bits in the lower half of CCR0 */

#define _PPC_CCR0_DTB           0x8000  /* Disable Trace Broadcast */
#define _PPC_CCR0_FLSTA         0x0100  /* Force Load/Store Alignment Excptn */
#define _PPC_CCR0_DBTAC         0x0040  /* Disable branch target address content
                                         * (BTAC) addressable memory */
#define _PPC_CCR0_DQWPM         0x000C  /* Data cache quadword prediction mode */
#define _PPC_CCR0_IQWPM         0x0002  /* Instruction cache quadword prediction mode */

/* Bits in the upper half of CCR1 */

#define _PPC_CCR1_GPRPEI_U      0xC000  /* GPR parity error insert */
#define _PPC_CCR1_FPRPEI_U      0x3000  /* Floating-Point Register (FPR) parity error insert */
#define _PPC_CCR1_ICDPEI_U      0x0C00  /* Instruction cache data parity error insert */
#define _PPC_CCR1_ICLPEI_U      0x0300  /* Instruction cache LRU parity error insert. */

#define _PPC_CCR1_ICTPEI_U      0x00C0  /* Instruction cache tag parity error insert */
#define _PPC_CCR1_DCDPEI_U      0x0030  /* Data cache data parity error insert */

#define _PPC_CCR1_DCLPEI_U      0x000C  /* I-cache Data Parity Error Ins wd 4 */
#define _PPC_CCR1_DCTPEI_U      0x0003  /* I-cache Data Parity Error Ins wd 5 */

/* Bits in the lower half of CCR1 */

#define _PPC_CCR1_MMUTPEI       0x8000  /* Memory management unit tag parity error insert */
#define _PPC_CCR1_MMUDPEI       0x4000  /* Memory management unit data parity error insert */
#define _PPC_CCR1_TCS           0x0300  /* Timer clock select, watchdog timer select */

/* Bits in the upper half of MCSR */

#define _PPC_MCSR_MCS_U         0x8000  /* Machine Check Summary */
#define _PPC_MCSR_TLBE_U        0x0800  /* TLB Error */
#define _PPC_MCSR_ICAE_U        0x0400  /* I-cache Asynchronous Error */
#define _PPC_MCSR_DCE_U         0x0200  /* D-Cache Error */
#define _PPC_MCSR_GPRE_U        0x0100  /* GPR parity Error */
#define _PPC_MCSR_FPRE_U        0x0080  /* FPR parity Error */
#define _PPC_MCSR_IMPE_U        0x0040  /* Imprecise Machine Check Error */
#define _PPC_MCSR_L2CE_U        0x0020  /* Error or System Error reported */
                                        /* through the L2 cache */
#define _PPC_MCSR_DCRE_U        0x0010  /* DCR timeout Error */

/* Bits in the upper half of TCR */

#define _PPC_TCR_WP_U   0xc000  /* Watchdog Timer Period */
#define _PPC_TCR_WRC_U  0x3000  /* Watchdog Timer Reset Control */
#define _PPC_TCR_WIE_U  0x0800  /* Watchdog Timer Interrupt Enable */
#define _PPC_TCR_DIE_U  0x0400  /* Decrementer Interrupt Enable */
#define _PPC_TCR_FP_U   0x0300  /* Fixed Interval Timer Period */
#define _PPC_TCR_FIE_U  0x0080  /* Fixed Interval Timer Interrupt Enable */
#define _PPC_TCR_ARE_U  0x0040  /* Decrementer Auto-Reload Enable */

/* Bits in the upper half of TSR */

#define _PPC_TSR_ENW_U  0x8000  /* Enable Next Watchdog Timer Exception */
#define _PPC_TSR_WIS_U  0x4000  /* Watchdog Timer Interrupt Status */
#define _PPC_TSR_WRS_U  0x3000  /* Watchdog Timer Reset Status */
#define _PPC_TSR_DIS_U  0x0800  /* Decrementer Interrupt Status */
#define _PPC_TSR_FIS_U  0x0400  /* Fixed Interval Timer Interrupt Status */

/* versions of the aligned for 32-bit TCR/TSR register access */

#define _PPC476_TCR_DIE (_PPC_TCR_DIE_U << 16)
#define _PPC476_TSR_DIS (_PPC_TSR_DIS_U << 16)

/* debug control register 0 */

#define _DBCR0_EDM_U        0x8000 /* external debug mode */
#define _DBCR0_IDM_U        0x4000 /* internal debug mode */
#define _DBCR0_RST_SYS_U    0x3000 /* system reset */
#define _DBCR0_RST_SOC_U    0x2000 /* chip reset */
#define _DBCR0_RST_CORE_U   0x1000 /* core reset */
#define _DBCR0_RST_MASK_U   0x3000 /* mask for reset bit */
#define _DBCR0_ICMP_U       0x0800 /* instruction completion debug event */
#define _DBCR0_BRT_U        0x0400 /* branch taken debug event */
#define _DBCR0_IRPT_U       0x0200 /* interrupt debug event */
#define _DBCR0_TRAP_U       0x0100 /* trap debug event */
#define _DBCR0_IAC1_U       0x0080 /* instruction address compare 1 */
#define _DBCR0_IAC2_U       0x0040 /* instruction address compare 2 */
#define _DBCR0_IAC3_U       0x0020 /* instruction address compare 3 */
#define _DBCR0_IAC4_U       0x0010 /* instruction address compare 4 */
#define _DBCR0_DAC1R_U      0x0008 /* data address compare 1 Read */
#define _DBCR0_DAC1W_U      0x0004 /* data address compare 1 Write */
#define _DBCR0_DAC2R_U      0x0002 /* data address compare 2 Read */
#define _DBCR0_DAC2W_U      0x0001 /* data address compare 2 Write */
#define _DBCR0_EDM          0x80000000 /* external debug mode */
#define _DBCR0_IDM          0x40000000 /* internal debug mode */
#define _DBCR0_RST          0x30000000 /* reset */
#define _DBCR0_ICMP         0x08000000 /* instruction completion debug event */
#define _DBCR0_BRT          0x04000000 /* branch taken */
#define _DBCR0_IRPT         0x02000000 /* exception debug event */
#define _DBCR0_TRAP         0x01000000 /* trap debug event */
#define _DBCR0_IAC1         0x00800000 /* instruction address compare 1 */
#define _DBCR0_IAC2         0x00400000 /* instruction address compare 2 */
#define _DBCR0_IAC3         0x00200000 /* instruction address compare 3 */
#define _DBCR0_IAC4         0x00100000 /* instruction address compare 4 */
#define _DBCR0_DAC1R        0x00080000 /* data address compare 1 Read */
#define _DBCR0_DAC1W        0x00040000 /* data address compare 1 Write */
#define _DBCR0_DAC2R        0x00020000 /* data address compare 2 Read */
#define _DBCR0_DAC2W        0x00010000 /* data address compare 2 Write */
#define _DBCR0_RET          0x00008000 /* return debug event */
#define _DBCR0_FT           0x00000001 /* freeze timers on debug */

/* debug control register 1 */

#define _DBCR1_IAC1US_U   0xc000        /* IAC 1 User/Supervisor */
#define _DBCR1_IAC1ER_U   0x3000        /* IAC 1 Effective/Real */
#define _DBCR1_IAC2US_U   0x0c00        /* IAC 2 User/Supervisor */
#define _DBCR1_IAC2ER_U   0x0300        /* IAC 2 Effective/Real */
#define _DBCR1_IAC12M_U   0x00c0        /* IAC 1/2 Mode */
#define _DBCR1_IAC12AT_U  0x0001        /* IAC 1/2 Auto-Toggle Enable */
#define _DBCR1_IAC1US     0xc0000000    /* IAC 1 User/Supervisor */
#define _DBCR1_IAC1ER     0x30000000    /* IAC 1 Effective/Real */
#define _DBCR1_IAC2US     0x0c000000    /* IAC 2 User/Supervisor */
#define _DBCR1_IAC2ER     0x03000000    /* IAC 2 Effective/Real */
#define _DBCR1_IAC12M     0x00c00000    /* IAC 1/2 Mode */
#define _DBCR1_IAC12AT    0x00010000    /* IAC 1/2 Auto-Toggle Enable */
#define _DBCR1_IAC3US     0x0000c000    /* IAC 3 User/Supervisor */
#define _DBCR1_IAC3ER     0x00003000    /* IAC 3 Effective/Real */
#define _DBCR1_IAC4US     0x00000c00    /* IAC 4 User/Supervisor */
#define _DBCR1_IAC4ER     0x00000300    /* IAC 4 Effective/Real */
#define _DBCR1_IAC34M     0x000000c0    /* IAC 3/4 Mode */
#define _DBCR1_IAC34AT    0x00000001    /* IAC 3/4 Auto-Toggle Enable */

/* debug control register 2 */

#define _DBCR2_DAC1US_U   0xc000        /* DAC 1 User/Supervisor */
#define _DBCR2_DAC1ER_U   0x3000        /* DAC 1 Effective/Real */
#define _DBCR2_DAC2US_U   0x0c00        /* DAC 2 User/Supervisor */
#define _DBCR2_DAC2ER_U   0x0300        /* DAC 2 Effective/Real */
#define _DBCR2_DAC12M_U   0x00c0        /* DAC 1/2 Mode */
#define _DBCR2_DAC12A_U   0x0020        /* DAC 1/2 Asynchronous */
#define _DBCR2_DVC1M_U    0x000c        /* DVC 1 Mode */
#define _DBCR2_DVC2M_U    0x0003        /* DVC 2 Mode */
#define _DBCR2_DAC1US     0xc0000000    /* DAC 1 User/Supervisor */
#define _DBCR2_DAC1ER     0x30000000    /* DAC 1 Effective/Real */
#define _DBCR2_DAC2US     0x0c000000    /* DAC 2 User/Supervisor */
#define _DBCR2_DAC2ER     0x03000000    /* DAC 2 Effective/Real */
#define _DBCR2_DAC12M     0x00c00000    /* DAC 1/2 Mode */
#define _DBCR2_DAC12A     0x00200000    /* DAC 1/2 Asynchronous */
#define _DBCR2_DVC1M      0x000c0000    /* DVC 1 Mode */
#define _DBCR2_DVC2M      0x00030000    /* DVC 2 Mode */
#define _DBCR2_DVC1BE     0x0000000c    /* DVC 1 Byte Enables 0:3 */
#define _DBCR2_DVC2BE     0x00000003    /* DVC 2 Byte Enables 0:3 */

/* debug status register */

#define _DBSR_IDE_U     0x8000          /* Imprecise Debug Event */
#define _DBSR_UDE_U     0x4000          /* Unconditional Debug Event */
#define _DBSR_MRR_U     0x3000          /* Most Recent Reset */
#define _DBSR_ICMP_U    0x0800          /* Instruction Completion Debug Event */
#define _DBSR_BRT_U     0x0400          /* Branch Taken Debug Event */
#define _DBSR_IRPT_U    0x0200          /* Interrupt Debug Event */
#define _DBSR_TRAP_U    0x0100          /* Trap Debug Event */
#define _DBSR_IAC1_U    0x0080          /* IAC 1 Debug Event */
#define _DBSR_IAC2_U    0x0040          /* IAC 2 Debug Event */
#define _DBSR_IAC3_U    0x0020          /* IAC 3 Debug Event */
#define _DBSR_IAC4_U    0x0010          /* IAC 4 Debug Event */
#define _DBSR_DAC1R_U   0x0008          /* DAC/DVC 1 Read Debug Event */
#define _DBSR_DAC1W_U   0x0004          /* DAC/DVC 1 Write Debug Event */
#define _DBSR_DAC2R_U   0x0002          /* DAC/DVC 2 Read Debug Event */
#define _DBSR_DAC2W_U   0x0001          /* DAC/DVC 2 Write Debug Event */
#define _DBSR_IDE       0x80000000      /* Imprecise Debug Event */
#define _DBSR_UDE       0x40000000      /* Unconditional Debug Event */
#define _DBSR_MRR       0x30000000      /* Most Recent Reset */
#define _DBSR_MRR_SYS   0x30000000      /* system reset */
#define _DBSR_MRR_SOC   0x20000000      /* chip reset */
#define _DBSR_MRR_CORE  0x10000000      /* core reset */
#define _DBSR_ICMP      0x08000000      /* Instruction Completion Debug Event */
#define _DBSR_BRT       0x04000000      /* Branch Taken Debug Event */
#define _DBSR_IRPT      0x02000000      /* Interrupt Debug Event */
#define _DBSR_TRAP      0x01000000      /* Trap Debug Event */
#define _DBSR_IAC1      0x00800000      /* IAC 1 Debug Event */
#define _DBSR_IAC2      0x00400000      /* IAC 2 Debug Event */
#define _DBSR_IAC3      0x00200000      /* IAC 3 Debug Event */
#define _DBSR_IAC4      0x00100000      /* IAC 4 Debug Event */
#define _DBSR_DAC1R     0x00080000      /* DAC/DVC 1 Read Debug Event */
#define _DBSR_DAC1W     0x00040000      /* DAC/DVC 1 Write Debug Event */
#define _DBSR_DAC2R     0x00020000      /* DAC/DVC 2 Read Debug Event */
#define _DBSR_DAC2W     0x00010000      /* DAC/DVC 2 Write Debug Event */
#define _DBSR_RET       0x00008000      /* Return Debug Event */
#define _DBSR_IAC12ATS  0x00000002      /* IAC 1/2 Auto-Toggle Status */
#define _DBSR_IAC34ATS  0x00000001      /* IAC 3/4 Auto-Toggle Status */

/* mask for hardware breakpoints */

#define _DBSR_HWBP_MSK  ( _DBSR_IAC1 | _DBSR_IAC2 | \
              _DBSR_IAC3 | _DBSR_IAC4 | \
              _DBSR_DAC1R | _DBSR_DAC1W | \
              _DBSR_DAC2R | _DBSR_DAC2W )

/* Data Cache Debug Tag Register High */

/*
 * _DCDBTRH_TRA (Tag Real Address) is bits 0:23.  Due to the limitations
 * of PPC immediate operands, a corresponding mask is not all that useful.
 * Use rlwinm instead.
 */

#define _DCDBTRH_V      0x00000080      /* Cache Line Valid */
#define _DCDBTRH_TERA   0x0000000f      /* Tag Extended Real Address */

/* Data Cache Debug Tag Register Low */

#define _DCDBTRL_UPAR_U 0x0004          /* U-field Parity */
#define _DCDBTRL_TPAR_U 0x0003          /* Tag Parity */
#define _DCDBTRL_DPAR   0x0000f000      /* Data Parity */
#define _DCDBTRL_MPAR   0x00000f00      /* Modified (dirty) Parity */
#define _DCDBTRL_D      0x000000f0      /* Dirty Indicators */
#define _DCDBTRL_U0     0x00000008      /* U0 Storage Attribute */
#define _DCDBTRL_U1     0x00000004      /* U1 Storage Attribute */
#define _DCDBTRL_U2     0x00000002      /* U2 Storage Attribute */
#define _DCDBTRL_U3     0x00000001      /* U3 Storage Attribute */

/* Instruction Cache Debug Tag Register High */

/*
 * _ICDBTRH_TRA (Tag Real Address) is bits 0:23.  Due to the limitations
 * of PPC immediate operands, a corresponding mask is not all that useful.
 * Use rlwinm instead.
 */

#define _ICDBTRH_V      0x00000080      /* Cache Line Valid */
#define _ICDBTRH_TPAR   0x00000060      /* Tag Parity */
#define _ICDBTRH_DAPAR  0x00000010      /* Instruction Data Parity */

/* Instruction Cache Debug Tag Register Low */

#define _ICDBTRL_TS     0x00000200      /* Translation Space */
#define _ICDBTRL_TD     0x00000100      /* TID Disable */
#define _ICDBTRL_TID    0x000000ff      /* Translation ID */

/* Reset Configuration Register */

#define _RSTCFG_U0        0x00008000    /* U0 Storage Attribute */
#define _RSTCFG_U1        0x00004000    /* U1 Storage Attribute */
#define _RSTCFG_U2        0x00002000    /* U2 Storage Attribute */
#define _RSTCFG_U3        0x00001000    /* U3 Storage Attribute */
#define _RSTCFG_E         0x00000080    /* E Storage Attribute */
#define _RSTCFG_ERPN      0x0000000f    /* Extended Real Page Number */

/* Integer Exception Register */

#define _XER_SO_U         0x8000        /* Summary Overflow */
#define _XER_OV_U         0x4000        /* Overflow */
#define _XER_CA_U         0x2000        /* Carry */
#define _XER_SO           0x80000000    /* Summary Overflow */
#define _XER_OV           0x40000000    /* Overflow */
#define _XER_CA           0x20000000    /* Carry */
#define _XER_TBC          0x0000007f    /* Transfer Byte Count */

/*
 * exception syndrome register mask bits:
 * 0 - error not occured 1 - error occured
 */

#define _PPC476_ESR_MCI_U 0x8000      /* Machine Check -- Insn Fetch */
#define _PPC476_ESR_PIL_U 0x0800      /* Pgm Interrupt -- Illegal Insn */
#define _PPC476_ESR_PPR_U 0x0400      /* Pgm Interrupt -- Previleged Insn */
#define _PPC476_ESR_PTR_U 0x0200      /* Pgm Interrupt -- Trap */
#define _PPC476_ESR_FP_U  0x0100      /* Floating Point Operation */
#define _PPC476_ESR_ST_U  0x0080      /* Store Operation */
#define _PPC476_ESR_DLK_U 0x0030      /* Data Storage Interrupt -- Locking */
#define _PPC476_ESR_AP_U  0x0008      /* AP Operation */
#define _PPC476_ESR_PUO_U 0x0004      /* Pgm Interrupt -- Unimplemented */
#define _PPC476_ESR_BO_U  0x0002      /* Byte Ordering Exception */
#define _PPC476_ESR_PIE_U 0x0001      /* Pgm Interrupt -- Imprecise */
#define _PPC476_ESR_MCI   0x80000000  /* Machine Check -- Insn Fetch */
#define _PPC476_ESR_PIL   0x08000000  /* Pgm Interrupt -- Illegal Insn */
#define _PPC476_ESR_PPR   0x04000000  /* Pgm Interrupt -- Previleged Insn */
#define _PPC476_ESR_PTR   0x02000000  /* Pgm Interrupt -- Trap */
#define _PPC476_ESR_FP    0x01000000  /* Floating Point Operation */
#define _PPC476_ESR_ST    0x00800000  /* Store Operation */
#define _PPC476_ESR_DLK   0x00300000  /* Data Storage Interrupt -- Locking */
#define _PPC476_ESR_AP    0x00080000  /* AP Operation */
#define _PPC476_ESR_PUO   0x00040000  /* Pgm Interrupt -- Unimplemented Opn */
#define _PPC476_ESR_BO    0x00020000  /* Byte Ordering Exception */
#define _PPC476_ESR_PIE   0x00010000  /* Pgm Interrupt -- Imprecise */
#define _PPC476_ESR_PCRE  0x00000010  /* Pgm Interrupt -- Condition Reg Enab */
#define _PPC476_ESR_PCMP  0x00000008  /* Pgm Interrupt -- Compare */
#define _PPC476_ESR_PCRF  0x00000007  /* Pgm Interrupt -- Condition Reg Field */

/* common ESR macros */

#define _PPC_ESR_MCI    _PPC476_ESR_MCI
#define _PPC_ESR_PIL    _PPC476_ESR_PIL
#define _PPC_ESR_PPR    _PPC476_ESR_PPR
#define _PPC_ESR_PTR    _PPC476_ESR_PTR
#define _PPC_ESR_FP     _PPC476_ESR_FP
#define _PPC_ESR_ST     _PPC476_ESR_ST
#define _PPC_ESR_DLK    _PPC476_ESR_DLK
#define _PPC_ESR_AP     _PPC476_ESR_AP
#define _PPC_ESR_PUO    _PPC476_ESR_PUO
#define _PPC_ESR_BO     _PPC476_ESR_BO
#define _PPC_ESR_PIE    _PPC476_ESR_PIE
#define _PPC_ESR_PCRE   _PPC476_ESR_PCRE
#define _PPC_ESR_PCMP   _PPC476_ESR_PCMP
#define _PPC_ESR_PCRF   _PPC476_ESR_PCRF

#ifdef __cplusplus
}
#endif

#endif /* __INCppc476h */

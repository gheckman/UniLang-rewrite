/* asmMips.h - assembler definitions header file */

/*
 * Copyright (c) 1991-1993, 1996-1997, 1999, 2001-2002, 2004, 2006-2011
 * Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

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
02n,01sep11,slk  add register size selectable subu and addu
02m,02mar11,d_c  Add FUNC_EXPORT() macro.
02m,03mar11,slk  add xlp variant support
02l,28sep10,d_c  remove warning about .word values
02k,23jul10,rlg  addition of some cavium specific defines part of SDK removal
02m,27may10,d_c  Rename CAVIUM_CNMIPS_* to _WRS_CAVIUM_CNMIPS_* and define in
                 arch Makefile
02l,28apr10,d_c  LPA and execute inhibit support
02k,31mar10,d_c  Add cav_cn5xxx and cav_cn6xxx variants
02j,27jul09,pch  CQ154839: add _WRS_MIPS_ERET24K_ERRATA
02i,08jul09,slk  add FUNC_BEGIN and FUNC_END
02h,20apr09,pch  Import PARAM_OFFSET from rtpALib.s
02g,26feb09,pgh  Remove _WRS_MIPS_SDA_SUPPORTED #if
02f,08feb09,pch  add HAZARD_NULL
02e,08aug08,slk  add _WRS_MIPS_SDA_OFFSET macro for gnu and diab SDA
                 region accesses
02d,26sep07,d_c  Add extended interrupts for RMI _xlr variant
02c,16aug07,agf  Define empty hazard set for fully interlocked cores
02b,10aug07,rlg  MIPS library restructure changes
02a,29jul07,pes  Addition of more registers for Cavium save/restore
01z,15may07,sru  N32 stack alignment set to 16-byte aligned
01y,28mar07,rlg  updates to allow for full 64 bit register access on li
                 instructions
01y,29mar07,pes  Adjust stack frame macros for n32 use.
01x,18jul06,pes  Move SMP macros to private header.
01y,28aug06,pes  Enclose macro definitions in #ifdef _ASMLANGUAGE/#endif
                 to prevent namespace collision if this file is included
                 in a "C" file. (WIND00035912)
01x,21jun06,rlg  removal of SMP macros
01w,24may06,pes  Remove macros dealing with _mipsSrImask and _mipsEsfTail.
01v,11may06,pes  Add macros for SMP support.
01u,24apr06,pes  Add SMP support.
01t,17jun04,pes  Add definition of _RTypeSize.
01s,05may04,pes  Correct build failures caused by 01r.
01r,28apr04,pes  Adjusting hazard include file mechanism.
01q,23oct02,jmt  Modified to handle Arch Specific hazards
01p,01aug01,mem  Changes to support diab.
01o,16jul01,ros  add CofE comment
01n,20apr01,roz  Added SWC1/LWC1
01m,09apr01,mem  Correct stack frame macros for MIPS64
01l,09feb01,tlc  Introduce HAZARD macro definitions.
01k,03jan01,pes  Added GTEXT and GDATA for declaring functions and data
01j,19jan99,dra  added CW4000, CW4011, VR4100, VR5000 and VR5400 support.
                 fixed SETFRAME macro to keep stack 8-byte aligned.
01i,18apr97,kkk  added C0_PRID for R3000. (SPR# 8321)
01h,22nov96,kkk  add back C0_TLBHI for R3000.
01g,21nov96,kkk  enabled SW/LW for R4650.
01g,14oct96,kkk  added R4650 support.
01f,15oct93,cd   added R4000 support; defined frame macros.
01e,22sep92,rrr  added support for c++
01d,03jun92,ajm  updated file name referenced to match real name
01c,26may92,rrr  the tree shuffle
01b,04oct91,rrr  passed through the ansification filter
                  -changed copyright notice
01a,21feb91,ajm  written.
*/

#ifndef __INCasmMipsh
#define __INCasmMipsh

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _ASMLANGUAGE
/*
 * The LEADING_UNDERSCORE macro should be defined to TRUE for toolchains
 * that do NOT prefix a leading underscore character, i.e. "_", to
 * symbols.  Define the macro to FALSE when using a toolchain that
 * does add a leading underscore character to symbols.
 */

#define LEADING_UNDERSCORE FALSE 

#if (LEADING_UNDERSCORE == TRUE)
#define FUNC_EXPORT(func)   .globl _##func
#define FUNC(func)          _##func
#define FUNC_LABEL(func)    _##func:
#else
#define FUNC_EXPORT(func)   .globl func
#define FUNC(func)          func
#define FUNC_LABEL(func)    func:
#endif

/* Introduced to abstract assembler idiosyncrasies */

#define FUNC_BEGIN(func)        FUNC_LABEL(func)
#define FUNC_END(func)          .size   FUNC(func), . - FUNC(func)

#define FUNC_DECL(range,func)
#define VAR_DECL(var)   var
#define VAR(var)        var(r0)

/*
 * These macros are used to declare assembly language symbols that need
 * to be typed properly(func or data) to be visible to the OMF tool.  
 * So that the build tool could mark them as an entry point to be linked
 * by another PD.
 */

#define GTEXT(sym) FUNC(sym) ;  .type   FUNC(sym),@function
#define GDATA(sym) FUNC(sym) ;  .type   FUNC(sym),@object

#define FUNCREF(func)   func


/*
*  MIPS register definitions
*/

#define zero    $0      /* wired zero */
#define AT      $at     /* assembler temp */
#define v0      $2      /* return reg 0 */
#define v1      $3      /* return reg 1 */
#define a0      $4      /* arg reg 0 */
#define a1      $5      /* arg reg 1 */
#define a2      $6      /* arg reg 2 */
#define a3      $7      /* arg reg 3 */
#define t0      $8      /* caller saved 0 */
#define t1      $9      /* caller saved 1 */
#define t2      $10     /* caller saved 2 */
#define t3      $11     /* caller saved 3 */
#define t4      $12     /* caller saved 4 */
#define t5      $13     /* caller saved 5 */
#define t6      $14     /* caller saved 6 */
#define t7      $15     /* caller saved 7 */
#define s0      $16     /* callee saved 0 */
#define s1      $17     /* callee saved 1 */
#define s2      $18     /* callee saved 2 */
#define s3      $19     /* callee saved 3 */
#define s4      $20     /* callee saved 4 */
#define s5      $21     /* callee saved 5 */
#define s6      $22     /* callee saved 6 */
#define s7      $23     /* callee saved 7 */
#define t8      $24     /* caller saved 8 */
#define t9      $25     /* caller saved 9 */
#define k0      $26     /* kernel temp 0 */
#define k1      $27     /* kernel temp 1 */
#define gp      $28     /* global pointer */
#define sp      $29     /* stack pointer */
#define s8      $30     /* callee saved 8 */
#define ra      $31     /* return address */


#ifdef _WRS_MIPS_N32_ABI

#define a4      $8      /* arg register 4 (== t0 in OABI) */
#define a5      $9      /* arg register 5 (== t1 in OABI)*/
#define a6      $10     /* arg register 6 (== t2 in OABI) */
#define a7      $11     /* arg register 7 (== t3 in OABI) */

#endif /* _wRS_MIPS_N32_ABI */

/*
* MIPS Coprocessor 0 regs
*/
#define C0_IBASE        $0      /* R4650: instruction base xlate address */
#define C0_IBOUND       $1      /* R4650: instruction xlate address bound */
#define C0_DBASE        $2      /* R4650: data base xlate address */
#define C0_DBOUND       $3      /* R4650: data xlate address bound */
#define C0_INX          $0      /* tlb index */
#define C0_RAND         $1      /* tlb random */

/* Begin CPUs: R3000, CW4000, CW4011 */
#define C0_TLBLO        $2      /* tlb entry low */
/* End R3000, CW4000, CW4011 */

/* Begin CPUs: R4000, VR5000, VR5400, VR4100 */
#define C0_TLBLO0       $2      /* tlb entry low 0 */
#define C0_TLBLO1       $3      /* tlb entry low 1 */
/* End R4000, VR5000, VR5400, VR4100 */

#define C0_CTXT         $4      /* tlb context */

/* Begin CPUs: R4000, VR5000, VR5400, VR4100 */
#define C0_PAGEMASK     $5      /* page mask */
#define C0_WIRED        $6      /* lb wired entries */
/* End R4000, VR5000, VR5400, VR4100 */
#if defined(_WRS_CAVIUM_CNMIPS_CORE) || defined(_WRS_CAVIUM_CNMIPS_II_CORE)
#define C0_HWRENA       $7
#endif /* _WRS_CAVIUM_CNMIPS_CORE || _WRS_CAVIUM_CNMIPS_II_CORE */

#define C0_BADVADDR     $8              /* bad virtual address */

/* Begin CPUs: R4000, R4650, VR5000, VR5400, CW4011, VR4100 */
#define C0_COUNT        $9      /* count */
/* End R4000, R4650, VR5000, VR5400, CW4011, VR4100 */
#if defined(_WRS_CAVIUM_CNMIPS_CORE) || defined(_WRS_CAVIUM_CNMIPS_II_CORE)
#define C0_CAVCNTL      $9,7
#define C0_PAGE_GRAIN   $5,1
#endif /* _WRS_CAVIUM_CNMIPS_CORE || _WRS_CAVIUM_CNMIPS_II_CORE */

/* Begin CPUs: R4000, VR5000, VR5400, R3000, CW4000, CW4011, VR4100 */
#define C0_TLBHI        $10     /* tlb entry hi */
/* End R4000, VR5000, VR5400, R3000, CW4000, CW4011, VR4100 */

/* Begin CPUs: R4000, VR5000, VR5400, R4650, CW4011, VR4100 */
#define C0_COMPARE      $11     /* compare */
#if defined(_WRS_CAVIUM_CNMIPS_CORE) || defined(_WRS_CAVIUM_CNMIPS_II_CORE)
#define C0_CAV_MEMCTL   $11,7
#endif /* _WRS_CAVIUM_CNMIPS_CORE || _WRS_CAVIUM_CNMIPS_II_CORE */

/* End R4000, VR5000, VR5400, R4650, CW4011, VR4100*/

#define C0_SR           $12     /* status register */
#define C0_CAUSE        $13     /* exception cause */
#define C0_EPC          $14     /* exception pc */

#define C0_PRID         $15
#if defined(_WRS_CAVIUM_CNMIPS_CORE) || defined(_WRS_CAVIUM_CNMIPS_II_CORE)
#define C0_EBASE        $15,1
#endif /* _WRS_CAVIUM_CNMIPS_CORE || _WRS_CAVIUM_CNMIPS_II_CORE */

/* Begin CPUs: R4000, R4650, VR5000, VR5400, VR4100, CW4011 */
#define C0_CONFIG       $16

#define C0_CALG         $17     /* R4650: cache algorithm register */
#define C0_LLADDR       $17

#define C0_IWATCH       $18     /* R4650: instruction virt addr for watch */
#define C0_WATCHLO      $18

#define C0_DWATCH       $19     /* R4650: data virt addr for watch */
#define C0_WATCHHI      $19

#define C0_ECC          $26
#define C0_CACHEERR     $27
#define C0_TAGLO        $28

/* Begin CPUs: R4000, VR5000, VR5400, VR4100 */
#define C0_TAGHI        $29
/* End R4000, VR5000, VR5400, VR4100 */

#define C0_ERRPC        $30
/* End R4000, R4650, VR5000, VR5400, VR4100, CW4011 */

/*
*  MIPS floating point coprocessor register definitions
*/

#define fp0     $f0     /* return reg 0 */
#define fp1     $f1     /* return reg 1 */
#define fp2     $f2     /* return reg 2 */
#define fp3     $f3     /* return reg 3 */
#define fp4     $f4     /* caller saved 0 */
#define fp5     $f5     /* caller saved 1 */
#define fp6     $f6     /* caller saved 2 */
#define fp7     $f7     /* caller saved 3 */
#define fp8     $f8     /* caller saved 4 */
#define fp9     $f9     /* caller saved 5 */
#define fp10    $f10    /* caller saved 6 */
#define fp11    $f11    /* caller saved 7 */
#define fp12    $f12    /* arg reg 0 */
#define fp13    $f13    /* arg reg 1 */
#define fp14    $f14    /* arg reg 2 */
#define fp15    $f15    /* arg reg 3 */
#define fp16    $f16    /* caller saved 8 */
#define fp17    $f17    /* caller saved 9 */
#define fp18    $f18    /* caller saved 10 */
#define fp19    $f19    /* caller saved 11 */
#define fp20    $f20    /* callee saved 0 */
#define fp21    $f21    /* callee saved 1 */
#define fp22    $f22    /* callee saved 2 */
#define fp23    $f23    /* callee saved 3 */
#define fp24    $f24    /* callee saved 4 */
#define fp25    $f25    /* callee saved 5 */
#define fp26    $f26    /* callee saved 6 */
#define fp27    $f27    /* callee saved 7 */
#define fp28    $f28    /* callee saved 8 */
#define fp29    $f29    /* callee saved 9 */
#define fp30    $f30    /* callee saved 10 */
#define fp31    $f31    /* callee saved 11 */

#define C1_IR $0        /* implementation/revision reg */
#define C1_SR $31       /* control/status reg */

/*
* define aliases for operations that are different in 64bit mode
*/
#if (_WRS_INT_REGISTER_SIZE == 4)
#define SW      sw
#define LW      lw
#define MFC0    mfc0
#define MTC0    mtc0
#define LI      li
#define SUBU	subu
#define ADDU	addu
#define SRL	srl
#define SLL	sll

#ifdef _WRS_MIPS_ENABLE_LPA
#error LPA not supported on processors with 4-byte internal registers.
#endif
#define SW_LPA   sw
#define LW_LPA   lw
#define MFC0_LPA mfc0
#define MTC0_LPA mtc0

#elif (_WRS_INT_REGISTER_SIZE == 8)
#define SW      sd              /* storing machine registers */
#define LW      ld              /* loading machine registers */
#define MFC0    dmfc0           /* reading wide cop0 register */
#define MTC0    dmtc0           /* writing wide cop0 register */
#define LI      dli
#define SUBU	dsubu
#define ADDU	daddu
#define SRL	dsrl
#define SLL	dsll

#if defined (_WRS_MIPS_ENABLE_LPA)

/* The variants which have 8 byte regs, but 4 byte TLB entryLo regs
 * can not support LPA. Check for them here.
 */

#if defined (MIPSXX_mti5kx)
#error This variant can not support LPA because it has 32 bit TLB entryLo regs.
#endif

#define SW_LPA   sd
#define LW_LPA   ld
#define MFC0_LPA dmfc0
#define MTC0_LPA dmtc0

#else /* ! _WRS_MIPS_ENABLE_LPA */

#define SW_LPA   sw
#define LW_LPA   lw
#define MFC0_LPA mfc0
#define MTC0_LPA mtc0

#endif /* defined (_WRS_MIPS_ENABLE_LPA) */

#else   /* _WRS_INT_REGISTER_SIZE */
#error "invalid _WRS_INT_REGISTER_SIZE value"
#endif  /* _WRS_INT_REGISTER_SIZE */

#define _RTypeSize _WRS_INT_REGISTER_SIZE

#if (_WRS_FP_REGISTER_SIZE == 4)
#define SWC1    swc1
#define LWC1    lwc1
#define MFC1    mfc1
#define MTC1    mtc1
#elif (_WRS_FP_REGISTER_SIZE == 8)
#define SWC1    sdc1
#define LWC1    ldc1
#define MFC1    dmfc1           /* reading wide fp register */
#define MTC1    dmtc1           /* writing wide fp register */
#elif /* _WRS_FP_REGISTER_SIZE */
#error "invalid _WRS_FP_REGISTER_SIZE value"
#endif /* _WRS_FP_REGISTER_SIZE */

/* Hazard definitions */

/*
 * A MIPS Hazard is defined as any combination of instructions which
 * would cause unpredictable behavior in terms of pipeline delays,
 * cache misses, and exceptions.  Hazards are defined by the number
 * of CPU cycles that must pass between certain combinations of
 * instructions.  Because some MIPS CPUs single-issue nop instructions
 * while others dual-issue, the CPU cycles defined below are done so
 * according to the instruction issue mechanism available.
 */
#define SINGLE_ISSUE 0  
#define DUAL_ISSUE   1 
#define CPU_CYCLES              DUAL_ISSUE

/*
 * Using the issue mechanism definitions above, the MIPS CPU cycles
 * are defined below.
 */

#define ssnop           .word 0x00000040

#if (CPU_CYCLES == SINGLE_ISSUE)
#define CPU_CYCLES_ONE          ssnop
#define CPU_CYCLES_TWO          ssnop; ssnop
#elif (CPU_CYCLES == DUAL_ISSUE)
#define CPU_CYCLES_ONE          ssnop; ssnop
#define CPU_CYCLES_TWO          ssnop; ssnop; ssnop; ssnop
#endif

/*
 * Sixteen instructions are required to handle the VR5432 errata in
 * order to fill its instruction prefetch.  See HAZARD_VR5400 macro
 * for details.
 */
#define CPU_CYCLES_SIXTEEN      ssnop; ssnop; ssnop; ssnop; \
                                ssnop; ssnop; ssnop; ssnop; \
                                ssnop; ssnop; ssnop; ssnop; \
                                ssnop; ssnop; ssnop; ssnop                                  

/*
 * To assist with handling MIPS hazards, a number of categories of
 * hazards have been defined here.  
 *
 * HAZARD_TLB        After modifying tlb CP0 registers, do not use the
 *                   TLB for two CPU cycles.
 * HAZARD_ERET       After modifying the SR, do not return from an
 *                   exception for two CPU cycles.
 * HAZARD_INTERRUPT  After modifying the SR, interrupts do not lock
 *                   for two CPU cycles.
 * HAZARD_CP_READ    After a read from a Coprocessor register, the
 *                   result is not available for one CPU cycle.
 * HAZARD_CP_WRITE   After a write to a Coprocessor register, the
 *                   result is not effective for two CPU cycles.
 * HAZARD_CACHE_TAG  Cache TAG load and store instructions should
 *                   not be used withing one CPU cycle of modifying
 *                   the TAG registers.
 * HAZARD_CACHE      Cache instructions should not be used within 2
 *                   CPU cycles of each other.
 * HAZARD_VR5400     For the VR5432 CPU only.  Serialized instructions
 *                   (mtc0, ctc0, mfc0, cfc0, etc) must not appear within
 *                   16 instructions after a conditional branch or label.
 *
 * These hazard macros are intended for use with MIPS architecture-
 * dependent assembly files which require handling hazards.  For example,
 * suppose interrupts are being locked, to address the hazard, please
 * do the following:
 *
 * mtc0     t0, C0_SR
 * HAZARD_INTERRUPT
 * lw       t0, 0(a0)
 *
 * Similarly, when reading from a coprocessor register, please do the
 * following:
 *
 * mfc0     t0, C0_SR
 * HAZARD_CP_READ
 * and      t0, t0, t1
 * mtc0     t0, C0_SR
 * HAZARD_CP_WRITE
 *
 *
 * For more details on these categories, please refer to MIPS hazard
 * documentation.
 */

/* Hazard macros */

/*
 * The following is a do-nothing that results in no binary code. It is
 * a placeholder req'd for proper macro expansion in some situations.
 */
#define HAZARD_NULL     . = .

/*
 * If this arch requires non-standard Hazard defs, include the hazard file
 * defined for this arch.  Otherwise, use the defaults.
 */

#define HAZARD_STRINGIFY(x)     #x
#define HAZARD_HDR(file)        HAZARD_STRINGIFY(arch/mips/file)
#define HAZARD_INCLUDE(file)    HAZARD_HDR(HAZARD_FILE)

#ifdef HAZARD_FILE
#include HAZARD_INCLUDE(file)
#else
#ifdef _WRS_MIPS_FULL_HW_INTERLOCK
#define HAZARD_TLB
#define HAZARD_ERET
#define HAZARD_CP_READ          HAZARD_NULL
#define HAZARD_CP_WRITE         HAZARD_NULL
#define HAZARD_CACHE_TAG
#define HAZARD_CACHE            HAZARD_NULL
#define HAZARD_INTERRUPT        HAZARD_NULL
#else
#define HAZARD_TLB       CPU_CYCLES_TWO
#define HAZARD_ERET      CPU_CYCLES_TWO
#define HAZARD_CP_READ   CPU_CYCLES_ONE
#define HAZARD_CP_WRITE  CPU_CYCLES_TWO
#define HAZARD_CACHE_TAG CPU_CYCLES_ONE
#define HAZARD_CACHE     CPU_CYCLES_TWO
#define HAZARD_INTERRUPT CPU_CYCLES_TWO
#endif  /* _WRS_MIPS_FULL_HW_INTERLOCK */
#endif  /*  HAZARD_FILE */

#ifdef _WRS_MIPS_VR5400_ERRATA
#define HAZARD_VR5400    CPU_CYCLES_SIXTEEN
#else   /* _WRS_MIPS_VR5400_ERRATA */
#define HAZARD_VR5400
#endif  /* _WRS_MIPS_VR5400_ERRATA */

#ifdef _WRS_MIPS_ERET24K_ERRATA
#define ERET    eret ; nop
#else   /* _WRS_MIPS_ERET24K_ERRATA */
#define ERET    eret
#endif  /* _WRS_MIPS_ERET24K_ERRATA */

#if defined(_WRS_CAVIUM_CNMIPS_CORE) || defined(_WRS_CAVIUM_CNMIPS_II_CORE)

/* Macros to generate instructions */

/* must use register numbers here, not names or with $ prefix. */
/* defines for register numbers */

#define ZERO    0       /* zero register */
#define V0      2       /* return reg 0 */
#define V1      3       /* return reg 1 */
#define A0      4       /* arg reg 0 */
#define A1      5       /* arg reg 1 */
#define A2      6       /* arg reg 2 */
#define A3      7       /* arg reg 3 */
#define T0      8       /* caller saved 0 */
#define T1      9       /* caller saved 1 */
#define T2      10      /* caller saved 2 */
#define T3      11      /* caller saved 3 */
#define T4      12      /* caller saved 4 */
#define T5      13      /* caller saved 5 */
#define T6      14      /* caller saved 6 */
#define T7      15      /* caller saved 7 */
#define S0      16      /* callee saved 0 */
#define S1      17      /* callee saved 1 */
#define S2      18      /* callee saved 2 */
#define S3      19      /* callee saved 3 */
#define S4      20      /* callee saved 4 */
#define S5      21      /* callee saved 5 */
#define S6      22      /* callee saved 6 */
#define S7      23      /* callee saved 7 */
#define T8      24      /* caller saved 8 */
#define T9      25      /* caller saved 9 */

/* 192-bit * 64-bit Unsigned Multiply and Add: v3mulu */
#define CAV_V3MULU(rd,rs,rt)    .word   (0x70000011 |   \
                                 ((rd) << 11) | \
                                 ((rs) << 21) | \
                                 ((rt) << 16))
/* Move to multiplier registers */
#define CAV_MTM0(rs)            .word   (0x70000008 |   \
                                 ((rs) << 21))
#define CAV_MTM1(rs)            .word   (0x7000000c |   \
                                 ((rs) << 21))
#define CAV_MTM2(rs)            .word   (0x7000000d |   \
                                 ((rs) << 21))
#define CAV_MTP0(rs)            .word   (0x70000009 |   \
                                 ((rs) << 21))
#define CAV_MTP1(rs)            .word   (0x7000000a |   \
                                 ((rs) << 21))
#define CAV_MTP2(rs)            .word   (0x7000000b |   \
                                 ((rs) << 21))
#endif /* defined(_WRS_CAVIUM_CNMIPS_CORE) || defined(_WRS_CAVIUM_CNMIPS_II_CORE) */

#if defined(MIPSXX_xlr) || defined(MIPSXX_xlp)
#define C0_EIRR    $9,6
#define C0_EIMR    $9,7
#endif  /* MIPSXX_xlr || MIPSXX_xlp */

/*
 * Stack frame allocation.
 * These macros are used in assembly language routines to automate the
 * allocation and use of stack frames. They create a stack frame that
 * looks like this:
 *
#ifdef _WRS_MIPS_N32_ABI
 *
 *      +-------+<---   Original SP (16-byte aligned)
 *      |  RA   |       Storage for return address (8 bytes for alignment)
 *      +-------+
 *      | extra |       Optional additional storage requested by SETFRAME_EXTRA
 *      +-------+
 *      | r0-rN |       Storage for up to 4 additional local registers
 *      +-------+
 *      | a0-aN |       Storage for up to 8 argument regs
 *      +-------+<---   Adjusted SP (16-byte aligned)
 *
#else /@ _WRS_MIPS_N32_ABI @/
 *
 *      +-------+
 *      | a0-a3 |       Storage provided by ABI contract from calling function
 *      +-------+<---   Original SP
 *      |  RA   |       Storage for return address (8 bytes for alignment)
 *      +-------+
 *      | extra |       Optional additional storage requested by SETFRAME_EXTRA
 *      +-------+
 *      | r0-rN |       Storage for up to 4 additional local registers
 *      +-------+
 *      |(a0-a3)|       Storage provided by ABI contract to called function
 *      +-------+<---   Adjusted SP     
 *
#endif /@ _WRS_MIPS_N32_ABI @/
 *
 *
 */

/* Return the size of the frame for the named routine */
#define FRAMESZ(routine)        _##routine##Fsize
#ifdef _WRS_MIPS_N32_ABI
#define FRAMEASZ(routine)       _##routine##ARsize
#endif

#ifdef _WRS_MIPS_N32_ABI
/*
 * Calculate the frame size for the named routine
 * up to 8 register slots allocated for subroutines to store argument registers
 * 8 bytes are allocated for saving RA (independent of register size).
 * nregs register locations are reserved for storing locally used registers.
 * stack is kept 16-byte aligned.
 */
#define SETFRAME_EXTRA(routine,naregs,nregs,extra) \
   FRAMEASZ(routine) = ((_RTypeSize)*(naregs)); \
   FRAMESZ(routine) = ((((_RTypeSize)*((naregs)+(nregs)))+8+(extra)+15) & ~0x0f)  
#else /*  _WRS_MIPS_N32_ABI */
/*
 * Calculate the frame size for the named routine
 * 4 register slots allocated for subroutines to store argument registers
 * 8 bytes are allocated for saving RA (independent of register size).
 * nregs register locations are reserved for storing locally used registers.
 * stack is kept 8-byte aligned.
 */
#define SETFRAME_EXTRA(routine,naregs,nregs,extra) \
        FRAMESZ(routine) = ((((_RTypeSize)*(4+(nregs)))+8+(extra)+7) & ~0x07)
#endif /*  _WRS_MIPS_N32_ABI */

#define SETFRAME(routine,naregs,nregs) \
        SETFRAME_EXTRA(routine,naregs,nregs,0)

/* The location at which to store the return address */
#define FRAMERA(routine)        (FRAMESZ(routine)-8)

/* Locations at which to store locally used registers */

#ifdef _WRS_MIPS_N32_ABI
#define FRAMER(routine,regn)    (FRAMEASZ(routine)+(_RTypeSize)*(regn))
#else /* _WRS_MIPS_N32_ABI */
#define FRAMER(routine,regn)    ((_RTypeSize)*(4+(regn)))
#endif /* _WRS_MIPS_N32_ABI */

#define FRAMER0(routine) FRAMER(routine,0)
#define FRAMER1(routine) FRAMER(routine,1)
#define FRAMER2(routine) FRAMER(routine,2)
#define FRAMER3(routine) FRAMER(routine,3)

/* Locations at which to store argument registers */
#ifdef _WRS_MIPS_N32_ABI
#define FRAMEA(routine, regn) (                 (_RTypeSize)*(regn))
#else   /* _WRS_MIPS_N32_ABI */
#define FRAMEA(routine, regn) (FRAMESZ(routine)+(_RTypeSize)*(regn))
#endif  /* _WRS_MIPS_N32_ABI */

#define FRAMEA0(routine) FRAMEA(routine,0)
#define FRAMEA1(routine) FRAMEA(routine,1)
#define FRAMEA2(routine) FRAMEA(routine,2)
#define FRAMEA3(routine) FRAMEA(routine,3)

#ifdef _WRS_MIPS_N32_ABI
#define FRAMEA4(routine) FRAMEA(routine,4)
#define FRAMEA5(routine) FRAMEA(routine,5)
#define FRAMEA6(routine) FRAMEA(routine,6)
#define FRAMEA7(routine) FRAMEA(routine,7)
#endif /* _WRS_MIPS_N32_ABI */

/*
 * _NABI() and _OABI() are used as wrappers for assembly instructions
 * that should only be emited under the N32 or non-N32 ABI.
 */

#ifdef _WRS_MIPS_N32_ABI
#    define _NABI(...)  __VA_ARGS__
#    define _OABI(...)
#else
#    define _NABI(...)
#    define _OABI(...)  __VA_ARGS__
#endif

/*
 * Offset to locate the correct word when loading
 * a 32-bit parameter value from a stack frame
 */

#if (_WRS_INT_REGISTER_SIZE == 8) && (_BYTE_ORDER == _BIG_ENDIAN)
#define PARAM32_OFFSET    4
#else /* (_WRS_INT_REGISTER_SIZE == 8) && (_BYTE_ORDER == _BIG_ENDIAN) */
#define PARAM32_OFFSET    0
#endif /* (_WRS_INT_REGISTER_SIZE == 8) && (_BYTE_ORDER == _BIG_ENDIAN) */

/*
 * SDA support for assembly loads and stores using the gp register
 * to index into the sdata or sbss area
 */

#if defined(__GNUC__)
#define _WRS_MIPS_SDA_OFFSET(symbol)    %gp_rel(symbol)(gp)
#else /* diab */
#define _WRS_MIPS_SDA_OFFSET(symbol)    %sdaoff(symbol)(gp)
#endif /* defined(__GNUC__) */

#endif /* _ASMLANGUAGE */
#ifdef __cplusplus
}
#endif

#endif /* __INCasmMipsh */

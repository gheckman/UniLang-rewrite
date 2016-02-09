/* mipsExcPage.h - exception page (-1 page) definitions */

/* Copyright  2009-2010 Wind River Systems, Inc. */

/*
modification history
--------------------
01e,04aug10,slk  updates for OSM support
01d,24jun10,slk  add stack area for LMM images
01c,13nov09,slk  add location for CPU logical index
01b,09jun09,pch  Allocate space in exc page for use by TLB optimization
01a,16feb09,slk  Created from mmuMipsLib.h
*/


#ifndef __INCmipsExcPageh
#define __INCmipsExcPageh

/* Exc page virtual base addrs */

#define EXCPAGE_VIRT_BASE_ADRS          0xFFFFE000

/*
 * TLB scratch area when an Exc page is mapped in the TLB,
 * used exclusively in mmuMipsALib.s
 */

#define TLB_EXCPAGE_AT          (-0x08)
#define TLB_EXCPAGE_K0          (-0x10)
#define TLB_EXCPAGE_K1          (-0x18)
#define TLB_EXCPAGE_T0          (-0x20)
#define TLB_EXCPAGE_T1          (-0x28)
#define TLB_EXCPAGE_T2          (-0x30)
#define TLB_EXCPAGE_T3          (-0x38)
#define TLB_EXCPAGE_T4          (-0x40)
#define TLB_EXCPAGE_T5          (-0x48)
#define TLB_EXCPAGE_T6          (-0x50)
#define TLB_EXCPAGE_T7          (-0x58)
#define TLB_EXCPAGE_T8          (-0x60)

/*
 * remaining space between (-0x60) and (-0x100)
 * reserved for future use in mmuMipsALib.s
 */

/*
 * Exc scratch area when an Exc page is mapped in the TLB,
 * used in excALib.s, sigCtxALib.s, wdbDbgALib.s, windALib.s
 */

#define EXCPAGE_EXCSTUB_BASE            (-0x100)
#define EXCPAGE_EXCSTUB_AT              (EXCPAGE_EXCSTUB_BASE-0x08)
#define EXCPAGE_EXCSTUB_K0              (EXCPAGE_EXCSTUB_BASE-0x10)
#define EXCPAGE_EXCSTUB_K1              (EXCPAGE_EXCSTUB_BASE-0x18)
#define EXCPAGE_EXCSTUB_T0              (EXCPAGE_EXCSTUB_BASE-0x20)
#define EXCPAGE_EXCSTUB_T1              (EXCPAGE_EXCSTUB_BASE-0x28)
#define EXCPAGE_EXCSTUB_T2              (EXCPAGE_EXCSTUB_BASE-0x30)
#define EXCPAGE_EXCSTUB_T3              (EXCPAGE_EXCSTUB_BASE-0x38)
#define EXCPAGE_EXCSTUB_T4              (EXCPAGE_EXCSTUB_BASE-0x40)
#define EXCPAGE_EXCSTUB_T5              (EXCPAGE_EXCSTUB_BASE-0x48)
#define EXCPAGE_EXCSTUB_T6              (EXCPAGE_EXCSTUB_BASE-0x50)
#define EXCPAGE_EXCSTUB_T7              (EXCPAGE_EXCSTUB_BASE-0x58)
#define EXCPAGE_EXCSTUB_T8              (EXCPAGE_EXCSTUB_BASE-0x60)
#define EXCPAGE_EXCSTUB_T9              (EXCPAGE_EXCSTUB_BASE-0x68)
#define EXCPAGE_EXCSTUB_BVA             (EXCPAGE_EXCSTUB_BASE-0x70)
#define EXCPAGE_EXCSTUB_PC              (EXCPAGE_EXCSTUB_BASE-0x78)
#define EXCPAGE_EXCSTUB_TLBHI           (EXCPAGE_EXCSTUB_BASE-0x80)
#define EXCPAGE_EXCSTUB_CR              (EXCPAGE_EXCSTUB_BASE-0x88)
#define EXCPAGE_EXCSTUB_SR              (EXCPAGE_EXCSTUB_BASE-0x90)
#define EXCPAGE_EXCSTUB_SP              (EXCPAGE_EXCSTUB_BASE-0x98)

/*
 * remaining space between (-0x198) and (-0x200) reserved
 * for future use in connection with exception handling
 */

/* sigCtx scratch area when an Exc page is mapped in the TLB */

#define EXCPAGE_SIGCTX_BASE             (-0x200)
#define EXCPAGE_SIGCTX_T1               (EXCPAGE_SIGCTX_BASE-0x08)
#define EXCPAGE_SIGCTX_SR               (EXCPAGE_SIGCTX_BASE-0x10)
#define EXCPAGE_SIGCTX_PC               (EXCPAGE_SIGCTX_BASE-0x18)

/*
 * MMU Miss handling scratch area when an Exc page is mapped in the TLB,
 * used exclusively in mmuMipsALib.s
 */

#define EXCPAGE_MMU_BASE                (-0x300)
#define EXCPAGE_MMU_HANDLER             (EXCPAGE_MMU_BASE-0x08)
#define EXCPAGE_MMU_CNTXT_TBL           (EXCPAGE_MMU_BASE-0x10)
#define EXCPAGE_MMU_VADDR_MASK          (EXCPAGE_MMU_BASE-0x18)
#define EXCPAGE_MMU_VADDR_SHIFT         (EXCPAGE_MMU_BASE-0x20)
#define EXCPAGE_MMU_MISS_COUNT          (EXCPAGE_MMU_BASE-0x28)
#define EXCPAGE_MMU_MISS_COUNT_INS      (EXCPAGE_MMU_BASE-0x30)

/* MIPS per CPU archVars (moved from WIND_VARS_ARCH structure) */

#define EXCPAGE_ARCHVARS_BASE           (-0x400)
#define EXCPAGE_ARCHVARSareWeNested     (EXCPAGE_ARCHVARS_BASE)
#define EXCPAGE_ARCHVARS_mipsEsfTail    (EXCPAGE_ARCHVARS_BASE-0x08)
#define EXCPAGE_ARCHVARS_mipsSrImask    (EXCPAGE_ARCHVARS_BASE-0x10)
#define EXCPAGE_ARCHVARS_mipsIpiMailbox (EXCPAGE_ARCHVARS_BASE-0x18)

/* TLB optimization work area, used exclusively in mmuMipsALib.s */

#define EXCPAGE_OPT_BASE                (-0x500)
#define EXCPAGE_OPT_EntryLo0            (EXCPAGE_OPT_BASE-0x08)
#define EXCPAGE_OPT_EntryLo1OrValue     (EXCPAGE_OPT_BASE-0x10)
#define EXCPAGE_OPT_EntryHi             (EXCPAGE_OPT_BASE-0x18)
#define EXCPAGE_OPT_PageMask            (EXCPAGE_OPT_BASE-0x20)
#define EXCPAGE_OPT_lockSet             (EXCPAGE_OPT_BASE-0x28)
#define EXCPAGE_OPT_nTlbEntries         (EXCPAGE_OPT_BASE-0x30)
#define EXCPAGE_OPT_SavedEntryHi        (EXCPAGE_OPT_BASE-0x38)
#define EXCPAGE_OPT_key                 (EXCPAGE_OPT_BASE-0x40)

/* CPU specific storage */

#define EXCPAGE_CPU_BASE                (-0x580)
#define EXCPAGE_CPU_LOGICAL_INDEX       (EXCPAGE_CPU_BASE-0x08)

/* LMM stack area */

#define EXCPAGE_TMP_STACK_OFFSET        (-0x600)

#endif /* __INCmipsExcPageh */

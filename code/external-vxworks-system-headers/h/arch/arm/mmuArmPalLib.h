/* mmuArmPalLib.h - ARM MMU library header file */

/*
 * Copyright (c) 1996-2007, 2009-2010, 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
02i,02mar12,rec  WIND00318272 - POSIX signals conformance
02h,09jan12,rec  WIND00196578 - remove unused reference _func_armPageSource
02g,29apr10,pad  Moved extern C statement after include statements.
02f,03nov09,j_b  add INCLUDE_MMU_SUBPAGE_SUPPORT, undef INCLUDE_MMU_TEX_SUPPORT
02e,23oct07,to   added lockCnt and lockOwner to MMU_TRANS_TBL
02d,21sep07,to   define MMU_PAGE_SIZE_SHIFT
02c,21sep07,j_b  add _func_mmuFaultAddrGet prototype
02b,09feb07,j_b  add mmuFarGet prototype
02a,20sep06,j_b  add page optimization support
01z,12sep06,m_h  fix vert-to-phys translation problem in upper bits
                 WIND00059266
01y,28mar06,m_h  Coherancy Support (s-bit)
01x,01mar06,m_h  Section Support in non-XScale ARM
01w,03jan06,m_h  Manzano Support
01v,24jun05,scm  correct PAGE_DESC_FIELD for missing BE pad3 field, (SPR 110348)
01u,08feb05,rec  use VIRT_ADDR and PHYS_ADDR instead of void
01t,31jan05,jb   Adding OTHER_SECT_DESC to resolve bsp reference
01s,09dec04,jb   Palifying mmu, extracted from mmuArmLib.h, 01r
*/

/*
 History from mmuArmLib.h
01r,10aug04,scm  adjust for removal of MPU support, add 926E...
01q,18sep03,scm  BASE 6 port...
01p,04oct01,scm  add extended small page table support for XScale...
01o,23jul01,scm  change XScale name to conform to coding standards...
01n,11jul01,scm  add support for XScale...
01m,29mar01,jpd  removed externs for mmyPhysToVirt & mmuVirtToPhys (SPR #63512).
01l,19mar01,jpd  redefine MMU_ATTR_BUFFERABLE and MMU_ATTR_CACHE_MINICACHE
         (SPR #64788).
01k,16aug00,jpd  no longer clear MMUCR Reserved/Should Be Zero bits (SPR #33608)
01j,14jun00,jpd  reworked MMU_STATE_WRITETHROUGH definition.
01i,17feb00,jpd  T3: prefixed defs with MMU_; added new defs; changed SR to 10.
01h,07sep99,jpd  added ARM740T, ARM920T support.
01g,20jan99,cdp  removed support for old ARM libraries;
         add prefix to MMU_IDs.
01f,24nov98,jpd  added ARM940T support, added other CPU ids; removed
         mmuIntLock/Unlock as intIFLock/Unlock to be used instead;
            cdp  restructured for multiple cache/MMU libraries; big-endian.
01e,09mar98,jpd  added MMUCTR_ definitions for ARM810 and extra cache states.
01d,20jan98,jpd  added _func_armPhysToVirt() etc. function pointers.
01c,17sep97,jpd  added MMU_INIT_VALUE and mmuIntLock/Unlock definitions.
01b,24jan97,jpd  modified mmuAEnable definition.
01a,09may96,cdp  created.
*/

#ifndef __INCmmuArmPalLibh
#define __INCmmuArmPalLibh


#ifndef _ASMLANGUAGE

#include <memLib.h>
#include <semLib.h>

#ifdef __cplusplus
extern "C" {
#endif

#endif /* _ASMLANGUAGE */

/*
 * MMUs are not fitted to all processors, and so the definitions below
 * should not need to be included for processors without MMUs.
 */

#if (ARMMMU != ARMMMU_NONE)

/*
 * The page size we will use. Ignore the sub-page, Large Page and Tiny
 * Page features.
 */

#define MMU_PAGE_SIZE 4096
#define MMU_PAGE_SIZE_SHIFT 12

#undef INCLUDE_MMU_SUBPAGE_SUPPORT
#define INCLUDE_MMU_SUBPAGE_SUPPORT
	
#undef INCLUDE_MMU_TEX_SUPPORT

/*
 * The amount described by a Level 1 Descriptor, which equals the smallest
 * amount of VM allocatable in VxWorks.
 */

#define MMU_PAGE_BLOCK_SIZE 0x100000    /* 1 MByte */

#define MMU_ADRS_TO_L1D_INDEX_SHIFT 20

#define MMU_PTE_INDEX_MASK  0x000FF000  /* extract PTE index from Virt Addr */
#define MMU_PTE_INDEX_SHIFT 12          /* shift to make that into PTE index */

#define MMU_L1D_TO_BASE_SHIFT 10        /* to turn L1D to PT base addr */
#define MMU_L1DSECTION_TO_BASE_SHIFT 20 /* L1D section to PT base addr */
#define MMU_L1DSECTION_BA_MASK  0xFFF00000 /* phys bits 20-31 */

#define MMU_L1DSSECTIONLO_TO_BASE_SHIFT 24 /* bits 24-31 of supersection */
#define MMU_L1DSSECTIONHI_TO_BASE_SHIFT 32 /* bits 32-35 of supersection */
#define MMU_L1DSSECTIONLO_BA_MASK  0xFF000000 /* phys bits 24-31 */
#define MMU_L1DSSECTIONHI_BA_MASK  0x00F00000 /* phys bits 32-35 */

#define MMU_ADDR_PI_MASK     0x00000FFF /* extract page index from Virt Addr */
#define MMU_PTE_BA_MASK      0xFFFFF000 /* extract phys base address from PTE */

#define MMU_ADDR_SI_MASK     0x000FFFFF /* extr section index from Virt Addr */
#define MMU_PTE_SECA_MASK    0xFFF00000 /* extract section base from L1 desc */

#define MMU_ADDR_SSI_MASK    0x00FFFFFF /* supersection index from virt */
#define MMU_PTE_SSECA_MASK   0xFF000000 /* supersection base from L1 desc */
#define MMU_PTE_SSECAX_MASK  0x00F00000 /* supersection extended bits L1 */
#define MMU_PTE_SSECAX_SHIFT 12         /* supersection extended bits L1 */

#define MMU_PTE_TYPE_MASK       0x00000003 /* bits [0:1] */
#define MMU_L1PD_PTE_MASK       0xFFFFFC00 /* extract phys PTE addr from L1PD */
#define MMU_L1PD_TYPE_MASK      0x00000003 /* type bits [0:1] */
#define MMU_L1PD_CB_MASK        0x0000000C /* CB bits [3:2] */
#define MMU_L1PD_AP_MASK        0x00000C00 /* AP bits [10:11] */
#define MMU_L1PD_P_MASK         0x00000200 /* P bit [9] */
#define MMU_L1PD_TEX_MASK       0x00007000 /* TEX bits [14:12] */
#define MMU_L1PD_S_MASK         0x00010000 /* S bit (coherancy) [16] */

#define MMU_PTE_SECT_CB_MASK    0x0000000C /* CB bits [3:2] */
#define MMU_PTE_SECT_AP_MASK    0x00000030 /* AP bits [5:4] */
#define MMU_PTE_SECT_TEX_MASK   0x000001C0 /* TEX bits [8:6] */
#define MMU_PTE_SECT_S_MASK     0x00000200 /* S-bit (coherancy) [9] */

#define MMU_L1L2_SECT_CB_SHIFT   0  /* CB shift convert L1 to L2 */
#define MMU_L1L2_SECT_AP_SHIFT   6  /* AP shift convert L1 to L2 */
#define MMU_L1L2_SECT_TEX_SHIFT  6  /* TEX shift convert L1 to L2 */
#define MMU_L1L2_SECT_S_SHIFT    7  /* S-bit shift convert L1 to L2 */

#define MMU_PTE_SSECT_TYPE      0x00040000 /* supersection bit [18] */
#define MMU_PTE_SECT_TYPE_MASK  0x00040000 /* which type of section? */

#define MMU_NUM_VM_PAGES_IN_A_SECT  0x100
#define MMU_NUM_VM_PAGES_IN_A_SSECT 0x1000
#define MMU_NUM_SECTS_IN_A_SSECT    0x10        /* 16 sections/supersection */
#define MMU_SECT_SIZE               0x100000    /* section = 1MB */
#define MMU_SSECT_SIZE              0x1000000   /* supersection = 16MB */

#define MMU_L1PD_AP_SHIFT   10
#define MMU_L1PD_CB_SHIFT   2
#define MMU_L1PD_P_SHIFT    9
#define MMU_L1PD_S_SHIFT    16

#define MMU_L1PD_DOMAIN_MASK        0x000001E0      /* domain bits 5-8 */
#define MMU_L1PD_DOMAIN_SHIFT   5   /* shift to make domain field in L1PD */

/*
 * The Domain Access Control Register specifies the way in which access
 * rights are treated for each of sixteen domains. For each domain the
 * current state can be:
 *
 *   00 no access: all accesses generate aborts
 *   01 client:    access rights specified in page tables are checked.
 *   10 reserved
 *   11 manager:  accesses not checked against page tables: all access allowed.
 */

#define MMU_DACR_VAL_NORMAL             1       /* client of 0 */
#define MMU_DACR_VAL_UNPROTECT          0x03    /* manager of 0 */

/* Level 1 Descriptor types */

#define MMU_DESC_TYPE_FAULT   0         /* any access will cause a fault */
#define MMU_DESC_TYPE_PAGE    1
#define MMU_DESC_TYPE_SECTION 2

#define MMU_DEF_L1_PAGE 0x00000011      /* domain zero, Page descriptor */

/*
 * Section descriptors, such as might be used to set up an intermediate
 * set of page tables on processors such as SA-1100/SA-1500 where this
 * needs to be done from BSP initialization, before vm(Base)Lib sets up
 * a proper set of page tables.
 */

#define MMU_RAM_SECT_DESC       0xC1E   /* R/W cacheable bufferable domain 0 */
#define MMU_MINICACHE_SECT_DESC 0xC1A   /* R/W C+ B- domain 0 */
#define MMU_OTHER_SECT_DESC 0xC12       /* R/W C- B- domain 0 */

/* Level 2 Descriptor or Page Table Entry (PTE) types */

#define MMU_PTE_TYPE_FAULT   0          /* any access will cause a fault */
#define MMU_PTE_TYPE_LG_PAGE 1          /* Large page descriptor */
#define MMU_PTE_TYPE_SM_PAGE 2          /* Small page descriptor */
#define MMU_PTE_TYPE_EX_PAGE 3          /* Extended page descriptor */

/*
 * The Translation Table Base register (TTBR) points to a table of Level 1
 * Descriptors. these are either Invalid Section descriptors, Section
 * Descriptors, or Page Table Descriptors. If Page Table Descriptors, they
 * each point to a table of Level 2 Page Descriptors, or Page Table Entries
 * (PTEs).
 * The 32-bit (virtual) address space allows for 4096 M. Each Level 1
 * Descriptor describes a 1 M area of memory. There are therefore 4096 Level
 * 1 Descriptors, and each table of 256 Level 2 Page Descriptors (PTEs)
 * describes 256 4 kbyte pages.
 */

#define MMU_NUM_L1_DESCS 4096
#define MMU_NUM_L2_DESCS 256
#define MMU_L1_TABLE_SIZE (MMU_NUM_L1_DESCS * sizeof(MMU_LEVEL_1_DESC))

/* No. of pages a Level 1 Descriptor table takes up */

#define MMU_L1_DESC_PAGES (MMU_L1_TABLE_SIZE / MMU_PAGE_SIZE)

/* Size of a Page Table */

#define MMU_PAGE_TABLE_SIZE (MMU_NUM_L2_DESCS * sizeof(PTE))

/* Section and supersection L1 definitions follow */

#undef MMU_DEF_L1_SECTION_PAGE
#define MMU_DEF_L1_SECTION_PAGE 0x00000002  /* Section page descriptor */

#undef MMU_DEF_L1_SUPERSECTION_PAGE
#define MMU_DEF_L1_SUPERSECTION_PAGE 0x00040002  /* supersection */

#undef MMU_DEF_L1_SECTION_PAGE_MASK
#define MMU_DEF_L1_SECTION_PAGE_MASK 0x00040003  /* mask */

#undef MMU_STATE_SECTION_MASK_WRITABLE
#define MMU_STATE_SECTION_MASK_WRITABLE 0x00000030      /* All APn bits */

/*
 * Architecture-dependent MMU states. These are states settable for pages and
 * here they correspond to settings in the Page Table Entries (PTEs).
 *
 * We set Valid/Invalid by setting a Fault second-level descriptor rather
 * than by using the Access Permissions within a small page second-level
 * descriptor. This is because we will want to use the Access Permissions to
 * control supervisor mode access and we cannot then use the AP bits
 * to disallow access as the SR bits in the MMU Control register must be set
 * to 10 in order to control read/write access from Supervisor mode.
 */

#define MMU_STATE_INVALID_STATE 0xFFFFFFFF

#define MMU_STATE_MASK_VALID            0x03        /* 2nd level desc type */

#define MMU_STATE_MASK_WRITABLE         0x00000FF0  /* All APn bits */

#define MMU_STATE_MASK_CACHEABLE        0x0000000C  /* CB bits */
#define MMU_STATE_MASK_BUFFERABLE       0x00000004

#define MMU_STATE_MASK_MEM_COHERENCY    0x00000200  /* Manzano S-bit */
#define MMU_STATE_MEM_COHERENCY         0x00000200  /* Manzano S-bit */

#ifdef INCLUDE_MMU_SBIT_SUPPORT
  #define MMU_STATE_MASK_CACHEABLE_S    0x0000020C  /* CB&S bits */
#else /*INCLUDE_MMU_SBIT_SUPPORT*/
  #define MMU_STATE_MASK_CACHEABLE_S    0x0000000C  /* CB bits */
#endif /*INCLUDE_MMU_SBIT_SUPPORT*/

#define MMU_STATE_VALID         MMU_PTE_TYPE_SM_PAGE    /* set to page type */
#define MMU_STATE_VALID_NOT     MMU_PTE_TYPE_FAULT      /* set to type fault */

#define MMU_STATE_WRITABLE              0x00000FF0      /* APn bits to 11 */

#define MMU_STATE_WRITABLE_NOT          0x0             /* APn bits to 00 */

#define MMU_STATE_MASK_PROTECTION       0x00000FF0      /* APn bits */

#define MMU_STATE_SUP_RO                0x00000000      /* AP: 00 */
#define MMU_STATE_SUP_RW                0x00000550      /* AP: 01 */
#define MMU_STATE_USR_RO_SUP_RW         0x00000AA0      /* AP: 10 */
#define MMU_STATE_USR_RW_SUP_RW         0x00000FF0      /* AP: 11 */

#define MMU_STATE_AP_SUP_RO        0x0      /* AP field: 00 */
#define MMU_STATE_AP_SUP_RW        0x1      /* AP field: 01 */
#define MMU_STATE_AP_USR_RO_SUP_RW 0x2      /* AP field: 10 */
#define MMU_STATE_AP_USR_RW_SUP_RW 0x3      /* AP field: 11 */

/* Write-through mode is only available on some CPUs */

#define MMU_STATE_CACHEABLE_WRITETHROUGH    0x8

#define MMU_STATE_CACHEABLE_COPYBACK        0xC  /* write back */

/*
 * Set the default state to be copyback. CACHEABLE_WRITETHROUGH can also be
 * selected on those cache designs that permit it.
 */

#define MMU_STATE_CACHEABLE     MMU_STATE_CACHEABLE_COPYBACK

#define MMU_STATE_CACHEABLE_NOT     0x0

#define MMU_STATE_BUFFERABLE        0x4 /* bufferable, not cacheable */
#define MMU_STATE_BUFFERABLE_NOT    0x0 /* will also set not cacheable*/

/*
 * Under VxWorks AE 1.1, when setting either of the attributes SPL_0 or SPL_1,
 * using vmPgAttrSet(), it is necessary to:
 *
 * 1. specify MMU_ATTR_SPL_MSK ORred with MMU_ATTR_CACHE_MSK in the mask
 *    argument to the routine, and:
 * 2. specify the appropriate cache state ORred in to the state argument
 *    to the routine.
 *
 * So, to set a page as bufferable not cacheable, it is necessary to
 * specify both MMU_ATTR_SPL_0 and specify MMU_ATTR_CACHE_OFF in the
 * state argument. To mark a page as cacheable in the minicache,
 * MMU_ATTR_SPL_1 and MMU_ATTR_CACHE_COPYBACK must be specified in the
 * state argument. In both cases, specify MMU_ATTR_SPL_MSK ORred with
 * MMU_ATTR_CACHE_MSK in the mask argument.
 *
 * These restrictions were not present in VxWorks AE 1.0.
 *
 * To "unset" the special attibutes SPL_0 or SPL_1, specify
 * MMU_ATTR_CACHE_MSK in the mask parameter (without MMU_ATTR_SPL_MSK),
 * and specify the cacheability required in the state argument.
 *
 * We provide the following aliases on ARM, to make life easier.
 */

#define MMU_ATTR_BUFFERABLE     (MMU_ATTR_SPL_0)

/* MMU Control Register bit allocations */

#define MMUCR_M_ENABLE   (1<<0)  /* MMU enable */
#define MMUCR_A_ENABLE   (1<<1)  /* Address alignment fault enable */
#define MMUCR_C_ENABLE   (1<<2)  /* (data) cache enable */
#define MMUCR_W_ENABLE   (1<<3)  /* write buffer enable */
#define MMUCR_PROG32     (1<<4)  /* PROG32 */
#define MMUCR_DATA32     (1<<5)  /* DATA32 */
#define MMUCR_L_ENABLE   (1<<6)  /* Late abort on earlier CPUs */
#define MMUCR_BIGEND     (1<<7)  /* Big-endian (=1), little-endian (=0) */
#define MMUCR_SYSTEM     (1<<8)  /* System bit, modifies MMU protections */
#define MMUCR_ROM    (1<<9)      /* ROM bit, modifies MMU protections */
#define MMUCR_F      (1<<10)     /* Should Be Zero */
#define MMUCR_Z_ENABLE   (1<<11) /* Branch prediction enable on 810 */
#define MMUCR_I_ENABLE   (1<<12) /* Instruction cache enable */
#define MMUCR_V_ENABLE   (1<<13) /* Exception vectors remap to 0xFFFF0000 */
#define MMUCR_ALTVECT    MMUCR_V_ENABLE /* alternate vector select */
#define MMUCR_RR_ENABLE  (1<<14) /* Round robin cache replacement enable */
#define MMUCR_ROUND_ROBIN MMUCR_RR_ENABLE  /* round-robin placement */
#define MMUCR_DISABLE_TBIT   (1<<15) /* disable TBIT */

/* The following definitions are now deprecated and may be withdrawn */

#ifdef MMU_ARM_ALLOW_DEPRECATED

#define LEVEL_1_DESC        MMU_LEVEL_1_DESC
#define PAGE_SIZE           MMU_PAGE_SIZE
#define PAGE_BLOCK_SIZE     MMU_PAGE_BLOCK_SIZE
#define PTE_INDEX_MASK      MMU_PTE_INDEX_MASK
#define PTE_INDEX_SHIFT     MMU_PTE_INDEX_SHIFT
#define L1D_TO_BASE_SHIFT   MMU_L1D_TO_BASE_SHIFT
#define ADDR_PI_MASK        MMU_ADDR_PI_MASK
#define NUM_L1_DESCS        MMU_NUM_L1_DESCS
#define NUM_L2_DESCS        MMU_NUM_L2_DESCS
#define L1_TABLE_SIZE       MMU_L1_TABLE_SIZE
#define L1_DESC_PAGES       MMU_L1_DESC_PAGES
#define PAGE_TABLE_SIZE     MMU_PAGE_TABLE_SIZE
#define DESC_TYPE_PAGE      MMU_DESC_TYPE_PAGE
#define DEF_L1_PAGE         MMU_DEF_L1_PAGE
#define PTE_TYPE_FAULT      MMU_PTE_TYPE_FAULT
#define PTE_TYPE_SM_PAGE    MMU_PTE_TYPE_SM_PAGE
#define RAM_SECT_DESC       MMU_RAM_SECT_DESC
#define MINICACHE_SECT_DESC MMU_MINICACHE_SECT_DESC
#define OTHER_SECT_DESC     MMU_OTHER_SECT_DESC

#else /* MMU_ARM_ALLOW_DEPRECATED */

    /* Some BSPs still reference PAGE_SIZE */

#define PAGE_SIZE           MMU_PAGE_SIZE

    /* Some BSPs still reference OTHER_SECT_DESC */

#define OTHER_SECT_DESC     MMU_OTHER_SECT_DESC

#endif /* MMU_ARM_ALLOW_DEPRECATED */

#define ADDR_TO_PAGE 12     /* shift phys address to PTE page base address */

#ifndef _ASMLANGUAGE

/* If using standard ARM MMU structures */
#ifndef MMU_ARCHITECTURE_DEFINES_STRUCTURES

/* Default ARMARCH4/5 ARM MMU Structures */

#if (_BYTE_ORDER == _LITTLE_ENDIAN)

/* little-endian */

/* First level page descriptors */

typedef struct
    {
    UINT type   : 2;        /* descriptor type, 1 => page */
    UINT pad1   : 2;        /* SBZ */
    UINT pad2   : 1;        /* SBO */
    UINT domain : 4;        /* domain number */
    UINT pad3   : 1;        /* SBZ */
    UINT addr   : 22;       /* base address of page table */
    } PAGE_DESC_FIELD;

/* First level "section" descriptor */
typedef struct
    {
    UINT type   : 2;        /* descriptor type, 2 => section */
    UINT bbit   : 1;        /* bufferable-bit */
    UINT cbit   : 1;        /* cacheable-bit */
    UINT pad1   : 1;        /* SBO */
    UINT domain : 4;        /* domain number */
    UINT pbit   : 1;        /* XSCALE 'P' bit */
    UINT ap : 2;            /* AP */
    UINT tex    : 3;        /* AP */
    UINT pad2   : 1;        /* SBO */
    UINT sbit   : 1;        /* S-bit */
    UINT pad3   : 1;        /* SBO */
    UINT super  : 1;        /* 1 => supersection */
    UINT pad4   : 1;        /* SBO */
    UINT addr   : 12;       /* base address of page table */
    } SECTION_DESC_FIELD;

/* First level "supersection" descriptor */
typedef struct
    {
    UINT type   : 2;        /* descriptor type, 2 => section */
    UINT bbit   : 1;        /* bufferable-bit */
    UINT cbit   : 1;        /* cacheable-bit */
    UINT pad1   : 1;        /* SBO */
    UINT addrHi2: 4;        /* phys address 39:36 */
    UINT pbit   : 1;        /* XSCALE 'P' bit */
    UINT ap : 2;            /* AP */
    UINT tex    : 3;        /* TEX */
    UINT pad2   : 1;        /* SBO */
    UINT sbit   : 1;        /* S-bit */
    UINT pad3   : 1;        /* SBO */
    UINT super  : 1;        /* 1 => supersection */
    UINT pad4   : 1;        /* SBO */
    UINT addrHi : 4;        /* phys address 35:32 */
    UINT addrLo : 8;        /* phys address 31:24 */
    } SUPERSECTION_DESC_FIELD;

/* Layout of Page Table Entries (PTEs), actually small page descriptors */

typedef struct
    {
    UINT type   : 2;        /* page type, 2 => small page */
    UINT cb     : 2;        /* cacheable/bufferable bits */
    UINT ap0    : 2;        /* access permission, sub-page 0 */
    UINT ap1    : 2;        /* access permission, sub-page 1 */
    UINT ap2    : 2;        /* access permission, sub-page 2 */
    UINT ap3    : 2;        /* access permission, sub-page 3 */
    UINT addr   : 20;       /* page base address */
    } PTE_FIELD;

#else /* (_BYTE_ORDER == _LITTLE_ENDIAN) */

/* big-endian */

/* First level descriptors */

typedef struct
    {
    UINT addr   : 22;       /* descriptor type, 1 => page */
    UINT pad3   : 1;        /* SBZ */
    UINT domain : 4;        /* domain number */
    UINT pad2   : 1;        /* SBO */
    UINT pad1   : 2;        /* SBZ */
    UINT type   : 2;        /* base address of page table */
    } PAGE_DESC_FIELD;

/* First level "section" descriptor */
typedef struct
    {
    UINT addr   : 12;       /* base address of page table */
    UINT pad4   : 1;        /* SBO */
    UINT super  : 1;        /* 1 => supersection */
    UINT pad3   : 1;        /* SBO */
    UINT sbit   : 1;        /* S-bit */
    UINT pad2   : 1;        /* SBO */
    UINT tex    : 3;        /* AP */
    UINT ap : 2;            /* AP */
    UINT pbit   : 1;        /* XSCALE 'P' bit */
    UINT domain : 4;        /* domain number */
    UINT pad1   : 1;        /* SBO */
    UINT c  : 1;            /* c-bit */
    UINT b  : 1;            /* b-bit */
    UINT type   : 2;        /* descriptor type, 2 => section */
    } SECTION_DESC_FIELD;

/* First level "supersection" descriptor */
typedef struct
    {
    UINT addrLo : 8;        /* phys address 31:24 */
    UINT addrHi : 4;        /* phys address 35:32 */
    UINT pad4   : 1;        /* SBO */
    UINT super  : 1;        /* 1 => supersection */
    UINT pad3   : 1;        /* SBO */
    UINT sbit   : 1;        /* S-bit */
    UINT pad2   : 1;        /* SBO */
    UINT tex    : 3;        /* AP */
    UINT ap : 2;            /* AP */
    UINT pbit   : 1;        /* XSCALE 'P' bit */
    UINT addrHi2: 4;        /* phys address 39:36 */
    UINT pad1   : 1;        /* SBO */
    UINT c  : 1;            /* c-bit */
    UINT b  : 1;            /* b-bit */
    UINT type   : 2;        /* descriptor type, 2 => section */
    } SUPERSECTION_DESC_FIELD;

/* Layout of Page Table Entries (PTEs), actually small page descriptors */

typedef struct
    {
    UINT addr   : 20;       /* page base address */
    UINT ap3    : 2;        /* access permission, sub-page 3 */
    UINT ap2    : 2;        /* access permission, sub-page 2 */
    UINT ap1    : 2;        /* access permission, sub-page 1 */
    UINT ap0    : 2;        /* access permission, sub-page 0 */
    UINT cb     : 2;        /* cacheable/bufferable bits */
    UINT type   : 2;        /* page type, 2 => small page */
    } PTE_FIELD;

#endif /* (_BYTE_ORDER == _LITTLE_ENDIAN) */

/* First level descriptor access */

typedef union
    {
    PAGE_DESC_FIELD         fields;
    SECTION_DESC_FIELD      sectionFields;
    SUPERSECTION_DESC_FIELD supersectionFields;
    UINT32                  bits;
    } MMU_LEVEL_1_DESC;

/* Second level descriptor access */

typedef union
    {
    PTE_FIELD fields;
    UINT32 bits;
    } PTE;

/*
 * Structure for MMU translation table access - normally used to get a pointer
 * to the first-level translation table.
 * To support page table optimization, a second first-level table and a
 * semaphore are needed.
 * The initial, unoptimized set of page tables will be set as the active
 * translation tables (via pLevel1Table) while optimization or deoptimization
 * is in progress using the inactive second translation table (pAltLevel1Table).
 * After each page table optimization or deoptimization operation has
 * completed, the second translation table will be set as the active
 * translation table.  The initial set of page tables retain their
 * links to level 2 pages, which may otherwise be lost after optimization.
 * Any non-optimization changes to the active first-level table will also be
 * made to the inactive first-level table.
 * The semaphore is used to prevent corruption of the tables.
 */

typedef struct mmuTransTblStruct
    {
    MMU_LEVEL_1_DESC *pLevel1Table;     /* active MMU table */
    MMU_LEVEL_1_DESC *pAltLevel1Table;  /* inactive MMU table */
    VX_MUTEX_SEMAPHORE(mmuTransTblSem); /* MMU tables' semaphore */
    UINT32      lockCnt;                /* lock count */
    atomic_t    lockOwner;              /* lock owner */
    } MMU_TRANS_TBL;

#endif /* MMU_ARCHITECTURE_DEFINES_STRUCTURES */

/* Externally visible mmuLib, mmuMapLib and mmuALib2 routines */

IMPORT UINT32 mmuReadId (void);
IMPORT PHYS_ADDR mmuVirtToPhys (VIRT_ADDR addr);
IMPORT VIRT_ADDR mmuPhysToVirt (PHYS_ADDR addr);
IMPORT UINT32   (* mmuCrGet) (void);
IMPORT void (* mmuModifyCr) (UINT32 value, UINT32 mask);
IMPORT UINT32   mmuHardCrGet (void);
IMPORT UINT32   mmuSoftCrGet (void);
IMPORT void mmuModifyHardCr (UINT32 value, UINT32 mask);
IMPORT void mmuModifySoftCr (UINT32 value, UINT32 mask);

IMPORT UINT32   (* _func_mmuFaultAddrGet) (void);
IMPORT UINT32   (* _func_mmuFaultStatusGet) (void);

IMPORT UINT32   mmuFarGet (void);	/* CP15_FAR only available with MMUs */
IMPORT UINT32   mmuFsrGet (void);	/* CP15_FSR only available with MMUs */

#endif  /* _ASMLANGUAGE */

#endif /* (ARMMMU != ARMMMU_NONE) */

#ifdef __cplusplus
}
#endif

#endif  /* __INCmmuArmPalLibh */

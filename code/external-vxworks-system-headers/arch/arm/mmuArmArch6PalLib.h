/* mmuArmArch6PalLib.h - ARM MMU library header file */

/*
 * Copyright (c) 2005-2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
17apr14,c_l  Fix TTBR & PTE attribute macros for enabled
             ENABLE_CACHED_PAGE_TBL. (VXW6-73478)
02p,18sep13,zgl  Add TTBR & PTE attribute macros for ARM A15 (WIND00434990)
02o,11jun12,jdw  Fix TTBR & PTE attribute macros for ARM A9,
                 WIND00342202, WIND00342756
02n,02mar12,rec  WIND00318272 - POSIX signals conformance
02m,09jan12,rec  WIND00196578 - remove unused reference _func_armPageSource
02l,28sep11,jdw  Add shared attribute to cached page tables (WIND00298486)
02k,13may11,jdw  Clear TTBR0 bits during MMU init (WIND00258897)
02j,20apr11,jdw  Add support for cached page tables
02i,25aug10,my_  add MMUCR_EE bit definition (WIND00229795)
02h,17jun10,m_h  Thumb-2 Support
02g,29apr10,pad  Moved extern C statement after include statements.
02f,02feb10,j_b  add not-global PTE bit (nG), ASID support
02e,03nov09,j_b  add INCLUDE_MMU_TEX_SUPPORT, undef INCLUDE_MMU_SUBPAGE_SUPPORT
02d,02nov09,j_b  fix translation bug due to XN bit support (WIND00189001)
02c,07feb08,j_b  Change MMU_DEF_L1_PAGE so bit 4 is 0 per VMSAv6
02b,23oct07,to   added lockCnt and lockOwner to MMU_TRANS_TBL
02a,21sep07,to   define MMU_PAGE_SIZE_SHIFT
01z,21sep07,j_b  add _func_mmuFaultAddrGet prototype
01y,08aug07,j_b  modify MMU_STATE_MASK_CACHEABLE for ARMv6 extended types;
                 add INCLUDE_MMU_EXTD_TYPE_SUPPORT
01x,30jul07,j_b  fix special purpose attributes' masks
01w,03jul07,j_b  add special purpose attributes for added ARMv6 extended types
                 (w/ TEX)
01v,20sep06,j_b  add page optimization support
01u,11sep06,m_h  fix vert-to-phys translation problem in upper bits
                 WIND00059266
01t,01mar06,m_h  Manzano supersection support
01s,30mar05,jb   Extracted from mmuArmArch6PalLib.h, 01u
*/

#ifndef __INCmmuArmArch6PalLibh
#define __INCmmuArmArch6PalLibh

#ifndef _ASMLANGUAGE

#include <memLib.h>
#include <semLib.h>

#ifdef __cplusplus
extern "C" {
#endif

#endif /* _ASMLANGUAGE */

/*
 * The page size we will use. Ignore the sub-page, Large Page and Tiny
 * Page features.
 */

#define MMU_PAGE_SIZE 4096
#define MMU_PAGE_SIZE_SHIFT 12

/*
 * See the Virtual Memory System Architecture for ARMv6 (VMSAv6) section
 * in the ARM Architecture Reference Manual (ARM DDI 0100) for MMU details.
 */

#define PAGE_SIZE            MMU_PAGE_SIZE

#undef INCLUDE_MMU_APXBIT_SUPPORT
#define INCLUDE_MMU_APXBIT_SUPPORT

#undef INCLUDE_MMU_XNBIT_SUPPORT
#define INCLUDE_MMU_XNBIT_SUPPORT

#undef INCLUDE_MMU_EXTD_TYPE_SUPPORT
#define INCLUDE_MMU_EXTD_TYPE_SUPPORT

#undef INCLUDE_MMU_SBIT_SUPPORT
#define INCLUDE_MMU_SBIT_SUPPORT

#undef INCLUDE_MMU_TEX_SUPPORT
#define INCLUDE_MMU_TEX_SUPPORT

#undef INCLUDE_MMU_SUBPAGE_SUPPORT

/*
 * The amount described by a Level 1 Descriptor, which equals the smallest
 * amount of VM allocatable in VxWorks.
 */

#define MMU_PAGE_BLOCK_SIZE 0x100000	/* 1 MByte */

#define MMU_ADRS_TO_L1D_INDEX_SHIFT 20

#define MMU_PTE_INDEX_MASK  0x000FF000  /* extract PTE index from Virt Addr */
#define MMU_PTE_INDEX_SHIFT 12          /* shift to make that into PTE index */

#define MMU_L1D_TO_BASE_SHIFT 10            /* to turn L1D to PT base addr */
#define MMU_L1DSECTION_TO_BASE_SHIFT 20     /* L1D section to PT base addr */
#define MMU_L1DSECTION_BA_MASK  0xFFF00000  /* phys bits 20-31 */

#define MMU_L1DSSECTIONLO_TO_BASE_SHIFT 24  /* bits 24-31 of supersection */
#define MMU_L1DSSECTIONHI_TO_BASE_SHIFT 32  /* bits 32-35 of supersection */
#define MMU_L1DSSECTIONHI2_TO_BASE_SHIFT 5  /* bits 36-39 of supersection */
#define MMU_L1DSSECTIONLO_BA_MASK  0xFF000000 /* phys bits 24-31 */
#define MMU_L1DSSECTIONHI_BA_MASK  0x00F00000 /* phys bits 32-35 */
#define MMU_L1DSSECTIONHI2_BA_MASK 0x000001E0 /* phys bits 36-39 */

/* optional extended physical address bit fields */

#define MMU_L1DSSECTION_EXTD_BA_MASK  \
            (MMU_L1DSSECTIONHI_BA_MASK | MMU_L1DSSECTIONHI2_BA_MASK)

/* supersection base address packing */

#define MMU_L1DSSECTION_BA_SET(physAddr, L1desc) \
            (L1desc = (L1desc & ~MMU_L1DSSECTION_EXTD_BA_MASK) | \
              ( (((unsigned long long)(physAddr)) & MMU_L1DSSECTIONLO_BA_MASK) | \
                ((((unsigned long long)(physAddr)) >> 12) & \
                        MMU_L1DSSECTIONHI_BA_MASK) | \
                ((((unsigned long long)(physAddr)) >> 31) & \
                        MMU_L1DSSECTIONHI2_BA_MASK) ))

/* supersection base address unpacking */

#define MMU_L1DSSECTION_BA_GET(ssectDesc) \
            ((unsigned long long) \
             ( (unsigned long long)(ssectDesc & MMU_L1DSSECTIONLO_BA_MASK) | \
                ((unsigned long long)(ssectDesc & MMU_L1DSSECTIONHI_BA_MASK) \
                            << 12) | \
                ((unsigned long long)(ssectDesc & MMU_L1DSSECTIONHI2_BA_MASK) \
                            << 31) ))

/* Address translation masks */

#define MMU_ADDR_PI_MASK     0x00000FFF /* extract page index from Virt Addr */
#define MMU_PTE_BA_MASK      0xFFFFF000 /* extract phys base address from PTE */
#define MMU_ADDR_SI_MASK     0x000FFFFF /* extr section index from Virt Addr */
#define MMU_PTE_SECA_MASK    0xFFF00000 /* extract section base from L1 desc */

#define MMU_ADDR_SSI_MASK    0x00FFFFFF /* supersection index from virt */
#define MMU_PTE_SSECA_MASK   0xFF000000 /* supersection base from L1 desc */
#define MMU_PTE_SSECAX_MASK  0x00F00000 /* supersection extended bits L1 */
#define MMU_PTE_SSECAX_SHIFT 12         /* supersection extended bits shift */

/* Level 1 descriptor bit fields */

#define MMU_L1PD_TYPE_MASK   0x00000003 /* type bits [0:1] */
#define MMU_L1PD_CB_MASK     0x0000000C /* CB bits [3:2] */
#define MMU_L1PD_XN_MASK     0x00000010 /* eXecute Never bit [4] */
#define MMU_L1PD_DOMAIN_MASK 0x000001E0	/* domain bits [8:5] */
#define MMU_L1PD_P_MASK      0x00000200 /* P bit [9] */
#define MMU_L1PD_AP_MASK     0x00000C00 /* AP bits [10:11] */
#define MMU_L1PD_TEX_MASK    0x00007000 /* TEX bits [14:12] */
#define MMU_L1PD_APX_MASK    0x00008000 /* APX bit [15] */
#define MMU_L1PD_S_MASK      0x00010000 /* Shared bit [16] */
#define MMU_L1PD_NG_MASK     0x00020000 /* not-Global bit [17] */
#define MMU_L1PD_PTE_MASK    0xFFFFFC00 /* extract phys L2 PTE addr from L1PD */

/* # of shifts (right) to get fields in Level 1 descriptor */

#define MMU_L1PD_CB_SHIFT      2
#define MMU_L1PD_XN_SHIFT      4
#define MMU_L1PD_DOMAIN_SHIFT  5
#define MMU_L1PD_P_SHIFT       9
#define MMU_L1PD_AP_SHIFT      10
#define MMU_L1PD_TEX_SHIFT     12
#define MMU_L1PD_APX_SHIFT     15
#define MMU_L1PD_S_SHIFT       16
#define MMU_L1PD_NG_SHIFT      17

/* Level 2 descriptor bit fields */

#define MMU_PTE_TYPE_MASK       0x00000003 /* PTE type bits [0:1] */
#define MMU_PTE_SECT_XN_MASK    0x00000001 /* eXecute Never bit [0] */
#define MMU_PTE_SECT_CB_MASK    0x0000000C /* CB bits [3:2] */
#define MMU_PTE_SECT_AP_MASK    0x00000030 /* AP bits [5:4] */
#define MMU_PTE_SECT_TEX_MASK   0x000001C0 /* TEX bits [8:6] */
#define MMU_PTE_SECT_APX_MASK   0x00000200 /* APX bit [9] */
#define MMU_PTE_SECT_S_MASK     0x00000400 /* Shared bit [10] */
#define MMU_PTE_SECT_NG_MASK    0x00000800 /* not-Global bit [11] */

/* adjustment to translate fields: Level 1 <-> Level 2 descriptors */

#define MMU_L1L2_SECT_NG_SHIFT   6 /* nG-bit shift convert L1 to L2 */
#define MMU_L1L2_SECT_S_SHIFT    6 /* S-bit shift convert L1 to L2 */
#define MMU_L1L2_SECT_TEX_SHIFT  6 /* TEX shift convert L1 to L2 */
#define MMU_L1L2_SECT_AP_SHIFT   6 /* AP, APX shift convert L1 to L2 */
#define MMU_L1L2_SECT_XN_SHIFT   4 /* XN-bit shift convert L1 to L2 */
#define MMU_L1L2_SECT_CB_SHIFT   0 /* CB shift convert L1 to L2 */

/* Section and Supersection type and size macros */

#define MMU_PTE_SSECT_TYPE          0x00040000 /* supersection bit [18] */
#define MMU_PTE_SECT_TYPE_MASK      0x00040000 /* which type of section? */

#define MMU_SECT_SIZE               0x100000    /* section = 1MB */
#define MMU_SSECT_SIZE              0x1000000   /* supersection = 16MB */

#define MMU_NUM_VM_PAGES_IN_A_SECT  0x100       /* 1MB = 256 * 4KB pages */
#define MMU_NUM_VM_PAGES_IN_A_SSECT 0x1000      /* 16MB = 4096 * 4KB pages */
#define MMU_NUM_SECTS_IN_A_SSECT    0x10        /* 16 sections/supersection */

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

#define MMU_DACR_VAL_NORMAL         1       /* client of 0 */
#define MMU_DACR_VAL_UNPROTECT      0x03    /* manager of 0 */

/* Level 1 Descriptor types */

#define MMU_DESC_TYPE_FAULT         0       /* any access will cause a fault */
#define MMU_DESC_TYPE_PAGE          1
#define MMU_DESC_TYPE_SECTION       2

#define MMU_DEF_L1_PAGE     0x00000001      /* domain zero, Page descriptor */

/*
 * Section descriptors, such as might be used to set up an intermediate
 * set of page tables on processors such as SA-1100/SA-1500 where this
 * needs to be done from BSP initialization, before vm(Base)Lib sets up
 * a proper set of page tables.
 */

#define MMU_RAM_SECT_DESC       0xC1E   /* R/W cacheable bufferable domain 0 */
#define MMU_MINICACHE_SECT_DESC 0xC1A   /* R/W C+ B- domain 0 */
#define MMU_OTHER_SECT_DESC 0xC12   /* R/W C- B- domain 0 */

/* Level 2 Descriptor or Page Table Entry (PTE) types */

#define MMU_PTE_TYPE_FAULT   0              /* any access will cause a fault */
#define MMU_PTE_TYPE_LG_PAGE 1              /* Large page descriptor */
#define MMU_PTE_TYPE_SM_PAGE 2              /* Small page descriptor */
#define MMU_PTE_TYPE_EX_PAGE 3              /* Extended page descriptor */

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

/* Number of possible ASIDs */

#define MMU_NUM_ASIDS        256
#define VXWORKS_KERNEL_ASID  0    /* reserved ASID for VxWorks kernel */

/* Section and supersection L1 definitions follow */

#undef INCLUDE_MMU_SUPERSECTION_SUPPORT  /* support supersection descriptors */
#define INCLUDE_MMU_SUPERSECTION_SUPPORT

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

#define MMU_STATE_INVALID_STATE     0xFFFFFFFF

#define MMU_STATE_MASK_VALID        0x00000002  /* 2nd lvl desc bit 1 only */

#define MMU_STATE_MASK_WRITABLE     0x00000230  /* All APn bits */

#define MMU_STATE_MASK_CACHEABLE    0x000005CC	/* S, TEX[0:2] + CB bits */

#define MMU_STATE_VALID             MMU_PTE_TYPE_SM_PAGE /* set to page type */
#define MMU_STATE_VALID_NOT         MMU_PTE_TYPE_FAULT  /* set to type fault */

#define MMU_STATE_MASK_PROTECTION   0x00000231      /* APX + APn + XN bits */

#define MMU_STATE_SUP_RO            0x00000210      /* APX: 1 AP: 01 */
#define MMU_STATE_SUP_RW            0x00000010      /* APX: 0 AP: 01 */
#define MMU_STATE_SUP_RO_USR_RO     0x00000220      /* APX: 1 AP: 10 */
#define MMU_STATE_SUP_RW_USR_RO     0x00000020      /* APX: 0 AP: 10 */
#define MMU_STATE_SUP_RW_USR_RW     0x00000030      /* APX: 0 AP: 11 */

#define MMU_STATE_WRITABLE          MMU_STATE_SUP_RW

#define MMU_STATE_WRITABLE_NOT      MMU_STATE_SUP_RO

#define MMU_STATE_AP_SUP_RO         0x1      /* AP field: 01 */
#define MMU_STATE_AP_SUP_RW         0x1      /* AP field: 01 */
#define MMU_STATE_AP_SUP_RO_USR_RO  0x2      /* AP field: 10 */
#define MMU_STATE_AP_SUP_RW_USR_RO  0x2      /* AP field: 10 */
#define MMU_STATE_AP_SUP_RW_USR_RW  0x3      /* AP field: 11 */

#define MMU_STATE_AP_USR_RO_SUP_RO  MMU_STATE_AP_SUP_RO_USR_RO
#define MMU_STATE_AP_USR_RO_SUP_RW  MMU_STATE_AP_SUP_RW_USR_RO
#define MMU_STATE_AP_USR_RW_SUP_RW  MMU_STATE_AP_SUP_RW_USR_RW

/* The Execute-Never bit is an extra permission check on readable addresses */

#define MMU_STATE_EXE_NOT           0x00000001	/* Execute-Never, XN bit */

#define MMU_STATE_SUP_RO_XN	   (MMU_STATE_SUP_RO | MMU_STATE_EXE_NOT)
#define MMU_STATE_SUP_RW_XN	   (MMU_STATE_SUP_RW | MMU_STATE_EXE_NOT)
#define MMU_STATE_SUP_RO_USR_RO_XN (MMU_STATE_SUP_RO_USR_RO | MMU_STATE_EXE_NOT)
#define MMU_STATE_SUP_RW_USR_RO_XN (MMU_STATE_SUP_RW_USR_RO | MMU_STATE_EXE_NOT)
#define MMU_STATE_SUP_RW_USR_RW_XN (MMU_STATE_SUP_RW_USR_RW | MMU_STATE_EXE_NOT)

/*
 * Memory Region Attributes -
 * cache access, write buffer access, coherency control
 */

#define MMU_STATE_STRONGLY_ORDERED  0x0         /* strongly ordered, shared */
#define MMU_STATE_CACHEABLE_NOT     0x0         /* backward compatible */

#define MMU_STATE_DEVICE_SHARED     0x00000004 /* device type, shared */
                                               /* (bufferable, not cacheable) */

/* outer & inner write-thru cachable, no write alloc */

#define MMU_STATE_NORMAL_WRITETHROUGH     0x00000008
#define MMU_STATE_CACHEABLE_WRITETHROUGH  0x00000008  /* backward compatible */

#define MMU_STATE_NORMAL_WRITEBACK        0x0000000C  /* write-back, no alloc */
#define MMU_STATE_CACHEABLE_COPYBACK      0x0000000C  /* backward compatible */

#define MMU_STATE_NORMAL_NONCACHEABLE     0x00000040  /* non-cached, sharable */

#define MMU_STATE_DEVICE_NONSHARED        0x00000080  /* device, non-shared */

#define MMU_STATE_COPYBACK_ALLOC          0x0000004C  /* write-back, sharable */

/* Define the flags used by Cached Page Tables for the PTEs */

/*
 *  - For MPCore(Cortex-A9 and ARM11), inner and outer write-back
 *    write-allocate cacheable.
 *  - For UPCore(Cortex-A9 and ARM11), inner and outer write-back
 *    no write-allocate cacheable.
 */

#ifdef _WRS_CONFIG_SMP

/* s=1,tex=001,c,b=11 */

#define MMU_STATE_CACHE_PTE_A9_FLAGS          (MMU_STATE_COPYBACK_ALLOC   | \
                                               MMU_STATE_SHARED)
#else

/* s=0,tex=000,c,b=11 */

#define MMU_STATE_CACHE_PTE_A9_FLAGS          (MMU_STATE_NORMAL_WRITEBACK)
#endif /* _WRS_CONFIG_SMP */

/*  - For Cortex-A15 MPCore, inner and outer write-back, no write-allocate. */

#define MMU_STATE_WRITEBACK_PTE_A15_MPCORE    (MMU_STATE_NORMAL_WRITEBACK)

/*  - For others use the standard settings. */

#define MMU_STATE_WRITETHROUGH_PTE_GENERIC    (MMU_STATE_NORMAL_WRITETHROUGH)

/*
 * The following outer/inner noncacheable policy is also used as
 * the basis for the rest of the outer/inner cache policies.
 * (See the MMU_ATTR_OUT_x_IN_x macros for SPL_4 below.)
 */

#define MMU_STATE_OUT_OFF_IN_OFF          0x00000100  /* out/inner non-cached */

/* outer cache policy (TEX[1:0]) >> shift, relative to MMU_ATTR_OUT_x_IN_x */

#define MMU_STATE_OUTER_CACHE_POLICY_SHIFT  24

/* inner cache policy (CB) >> shift, relative to MMU_ATTR_OUT_x_IN_x */

#define MMU_STATE_INNER_CACHE_POLICY_SHIFT  26

/*
 * Set the default state to be copyback. CACHEABLE_WRITETHROUGH can also be
 * selected on those cache designs that permit it.
 */

#define MMU_STATE_CACHEABLE         MMU_STATE_CACHEABLE_COPYBACK

/*
 * Shared memory attribute -
 * accessible by multiple processors or bus masters and must be kept coherent
 */

#define MMU_STATE_SHARED            0x00000400      /* Shared bit */

#define MMU_STATE_WRITETHROUGH_SHARED  \
                          (MMU_STATE_CACHEABLE_WRITETHROUGH | MMU_STATE_SHARED)
#define MMU_STATE_COPYBACK_SHARED  \
                          (MMU_STATE_CACHEABLE_COPYBACK | MMU_STATE_SHARED)
#define MMU_STATE_NONCACHEABLE_SHARED  \
                          (MMU_STATE_NORMAL_NONCACHEABLE | MMU_STATE_SHARED)

/*
 * Global memory attribute -
 * not-Global causes ASID to be associated with address translation
 */

#define MMU_STATE_NOT_GLOBAL        0x00000800      /* not-Global bit */

/*
 * Architecture-specific attributes
 *
 * The following ARMv6-specific aliases are provided for ease of use.
 *
 * NOTE: MMU_ATTR_CACHE_GUARDED is used as MMU_ATTR_CACHE_IO (its former name).
 */

/* Strongly Ordered - same as MMU_ATTR_CACHE_OFF for backward compatibility */

#define MMU_ATTR_STRONGLY_ORDERED  (MMU_ATTR_CACHE_OFF)

/* Shared Device */

#define MMU_ATTR_DEVICE_SHARED_MSK  (MMU_ATTR_CACHE_MSK)
#define MMU_ATTR_DEVICE_SHARED	(MMU_ATTR_CACHE_GUARDED | MMU_ATTR_CACHE_OFF | \
				 MMU_ATTR_CACHE_COHERENCY)
#define MMU_ATTR_BUFFERABLE     MMU_ATTR_DEVICE_SHARED /* backward compatible */

/* Non-Shared Device */

#define MMU_ATTR_DEVICE_NONSHARED_MSK	MMU_ATTR_DEVICE_SHARED_MSK
#define MMU_ATTR_DEVICE_NONSHARED	(MMU_ATTR_CACHE_GUARDED | \
					 MMU_ATTR_CACHE_OFF)

/*
 * Special Purpose Attributes:
 * When setting any of these attributes, it is necessary to:
 *
 * 1. specify MMU_ATTR_SPL_MSK ORred with MMU_ATTR_CACHE_MSK in the mask
 *    argument to the routine, and:
 * 2. specify the appropriate cache state ORed in to the state argument
 *    to the routine, unless the cache state is implied.
 *
 * So, to set a page as normal, noncacheable memory, it is necessary to
 * specify both MMU_ATTR_SPL_0 and specify MMU_ATTR_CACHE_OFF in the
 * state argument.
 *
 * To "unset" the special attributes, specify MMU_ATTR_CACHE_MSK in
 * the mask parameter (without MMU_ATTR_SPL_MSK) and specify the
 * cacheability required in the state argument.
 */

/* Normal, Noncacheable memory */

#define MMU_ATTR_NORMAL_NONCACHEABLE_MSK (MMU_ATTR_SPL_MSK | MMU_ATTR_CACHE_MSK)
#define MMU_ATTR_NORMAL_NONCACHEABLE     (MMU_ATTR_SPL_0 | MMU_ATTR_CACHE_OFF)
#define MMU_ATTR_NORMAL_NONCACHEABLE_SHARED (MMU_ATTR_NORMAL_NONCACHEABLE | \
				             MMU_ATTR_CACHE_COHERENCY)

/*
 * Outer and Inner Cache Write-Back, Write Allocate (same as XScale)
 * -- this can also be ORed with MMU_ATTR_CACHE_COHERENCY to set as Shared
 */

#define MMU_ATTR_WRITEALLOCATE_MSK    (MMU_ATTR_SPL_MSK | MMU_ATTR_CACHE_MSK)
#define MMU_ATTR_WRITEALLOCATE        (MMU_ATTR_SPL_3 | MMU_ATTR_CACHE_COPYBACK)
#define MMU_ATTR_WRITEALLOCATE_SHARED (MMU_ATTR_WRITEALLOCATE | \
				       MMU_ATTR_CACHE_COHERENCY)

/*
 * Individually Specified Outer and Inner Cache Policies
 *  -- ORed with TEX[1:0] and CB encodings for each, shifted to prevent
 *     conflicts with common MMU_ATTR_ protection, cache, valid and SPL bits:
 *  OFF - Noncacheable, Unbuffered
 *  WBWA - Write-Back cached, Write Allocate, Buffered
 *  WTNA - Write-Through cached, No Allocate on Write, Buffered
 *  WBNA - Write-Back cached, No Allocate on Write, Buffered
 *
 * -- these can also be ORed with MMU_ATTR_CACHE_COHERENCY to set as Shared,
 *    but since MMU_ATTR_CACHE_COHERENCY is invalid by itself
 *    MMU_ATTR_CACHE_OFF is added to all of them (and will be disregarded)
 */

#define MMU_ATTR_CACHE_POLICY_SHIFT	28  /* cache policy encoding << shift */
#define MMU_ATTR_CACHE_OUTER_POLICY_MSK	0xC0000000  /* outer policy code bits */
#define MMU_ATTR_CACHE_INNER_POLICY_MSK	0x30000000  /* inner policy code bits */

#define MMU_ATTR_OUT_X_IN_Y_MSK         (MMU_ATTR_SPL_MSK | MMU_ATTR_CACHE_MSK)
#define MMU_ATTR_OUT_OFF_IN_OFF		(MMU_ATTR_SPL_4 | MMU_ATTR_CACHE_OFF)
#define MMU_ATTR_OUT_OFF_IN_WBWA	(MMU_ATTR_OUT_OFF_IN_OFF | \
					  (0x1 << MMU_ATTR_CACHE_POLICY_SHIFT))
#define MMU_ATTR_OUT_OFF_IN_WTNA	(MMU_ATTR_OUT_OFF_IN_OFF | \
					  (0x2 << MMU_ATTR_CACHE_POLICY_SHIFT))
#define MMU_ATTR_OUT_OFF_IN_WBNA	(MMU_ATTR_OUT_OFF_IN_OFF | \
					  (0x3 << MMU_ATTR_CACHE_POLICY_SHIFT))

#define MMU_ATTR_OUT_WBWA_IN_OFF	(MMU_ATTR_OUT_OFF_IN_OFF | \
					  (0x4 << MMU_ATTR_CACHE_POLICY_SHIFT))
#define MMU_ATTR_OUT_WBWA_IN_WBWA	(MMU_ATTR_OUT_OFF_IN_OFF | \
					  (0x5 << MMU_ATTR_CACHE_POLICY_SHIFT))
#define MMU_ATTR_OUT_WBWA_IN_WTNA	(MMU_ATTR_OUT_OFF_IN_OFF | \
					  (0x6 << MMU_ATTR_CACHE_POLICY_SHIFT))
#define MMU_ATTR_OUT_WBWA_IN_WBNA	(MMU_ATTR_OUT_OFF_IN_OFF | \
					  (0x7 << MMU_ATTR_CACHE_POLICY_SHIFT))

#define MMU_ATTR_OUT_WTNA_IN_OFF	(MMU_ATTR_OUT_OFF_IN_OFF | \
					  (0x8 << MMU_ATTR_CACHE_POLICY_SHIFT))
#define MMU_ATTR_OUT_WTNA_IN_WBWA	(MMU_ATTR_OUT_OFF_IN_OFF | \
					  (0x9 << MMU_ATTR_CACHE_POLICY_SHIFT))
#define MMU_ATTR_OUT_WTNA_IN_WTNA	(MMU_ATTR_OUT_OFF_IN_OFF | \
					  (0xA << MMU_ATTR_CACHE_POLICY_SHIFT))
#define MMU_ATTR_OUT_WTNA_IN_WBNA	(MMU_ATTR_OUT_OFF_IN_OFF | \
					  (0xB << MMU_ATTR_CACHE_POLICY_SHIFT))

#define MMU_ATTR_OUT_WBNA_IN_OFF	(MMU_ATTR_OUT_OFF_IN_OFF | \
					  (0xC << MMU_ATTR_CACHE_POLICY_SHIFT))
#define MMU_ATTR_OUT_WBNA_IN_WBWA	(MMU_ATTR_OUT_OFF_IN_OFF | \
					  (0xD << MMU_ATTR_CACHE_POLICY_SHIFT))
#define MMU_ATTR_OUT_WBNA_IN_WTNA	(MMU_ATTR_OUT_OFF_IN_OFF | \
					  (0xE << MMU_ATTR_CACHE_POLICY_SHIFT))
#define MMU_ATTR_OUT_WBNA_IN_WBNA	(MMU_ATTR_OUT_OFF_IN_OFF | \
					  (0xF << MMU_ATTR_CACHE_POLICY_SHIFT))

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
#define MMUCR_ROM        (1<<9)  /* ROM bit, modifies MMU protections */
#define MMUCR_F          (1<<10) /* Should Be Zero */
#define MMUCR_Z_ENABLE   (1<<11) /* Branch prediction enable on 810 */
#define MMUCR_I_ENABLE   (1<<12) /* Instruction cache enable */
#define MMUCR_V_ENABLE   (1<<13) /* Exception vectors remap to 0xFFFF0000 */
#define MMUCR_ALTVECT    MMUCR_V_ENABLE /* alternate vector select */
#define MMUCR_RR_ENABLE  (1<<14) /* Round robin cache replacement enable */
#define MMUCR_ROUND_ROBIN MMUCR_RR_ENABLE  /* round-robin placement */
#define MMUCR_DISABLE_TBIT   (1<<15) /* disable TBIT */
#define MMUCR_ENABLE_DTCM    (1<<16) /* Enable Data TCM */
#define MMUCR_ENABLE_ITCM    (1<<18) /* Enable Instruction TCM */
#define MMUCR_UNALIGNED_ENABLE (1<<22) /* Enable unaligned access */
#define MMUCR_EXTENDED_PAGE (1<<23)  /* Use extended PTE format */
#define MMUCR_VECTORED_INTERRUPT (1<<24) /* Enable VIC Interface */
#define MMUCR_EE                 (1<<25) /* Exception Endianness bit */
#define MMUCR_THUMB_EXCEPTIONS (1<<30) /* Exceptions are Thumb */

#define ADDR_TO_PAGE 12     /* shift phys address to PTE page base address*/

/* MMU TTBR register fields for v6 and v7a */

#define MMU_TTBR_BASE_ADDR_MASK 0xFFFFC000
#define MMU_TTBR_C_MASK         0x00000001
#define MMU_TTBR_RGN_MASK       0x00000018
#define MMU_TTBR_IRGN_MASK      0x00000041
#define MMU_TTBR_NOS_MASK       0x00000020
#define MMU_TTBR_S_MASK         0x00000002
#define MMU_TTBR_IMP_MASK       0x00000004

/* RGN field bits */

#define MMU_TTBR_RGN_NML_NC     0x00000000 /* Normal, outer not cached        */
#define MMU_TTBR_RGN_NML_WB_WA  0x00000008 /* Normal, outer write-back,
                                              write-allocate cached           */
#define MMU_TTBR_RGN_NML_WT     0x00000010 /* Normal, outer write-thru cached */
#define MMU_TTBR_RGN_NML_WB     0x00000018 /* Normal, outer write-back,       */
                                           /* no write-allocate cached        */

/* IRGN field bits */

#define MMU_TTBR_IRGN_NML_NC    0x00000000 /* Normal, inner not cached        */
#define MMU_TTBR_IRGN_NML_WT    0x00000001 /* Normal, inner write-thru cached */
#define MMU_TTBR_IRGN_NML_WB_WA 0x00000040 /* Normal, inner write-back,
                                              write-allocate cached           */
#define MMU_TTBR_IRGN_NML_WB    0x00000041 /* Normal, inner write-back,       */
                                           /* no write-allocate cached        */

/* C Bit fields */

#define MMU_TTBR_C_NML_NC       0x00000000 /* Normal, not cached */
#define MMU_TTBR_C_NML_C        0x00000001 /* Normal, cached     */

/* S & NOS fields */

#define MMU_TTBR_S              0x00000002 /* Inner Shared     */
#define MMU_TTBR_NOS            0x00000020 /* Not Outer Shared */

#ifdef _WRS_CONFIG_SMP

/*
 * ARM Cortex-A9 MPCore and ARM11 MPCore do not support inner write-through
 * cached page tables. Cortex-A9 MPCore L2 can support write-through cached page
 * tables. Setup TTBR for normal memory, inner and outer write-back
 * write-allocate cacheable.
 */

/* IRGN[0]=1,NOS=1,RGN=0b01,S=1 */

#define MMU_TTBR_CACHE_PTE_A9_FLAGS          (MMU_TTBR_RGN_NML_WB_WA     | \
                                              MMU_TTBR_IRGN_NML_WB_WA    | \
                                              MMU_TTBR_S                 | \
                                              MMU_TTBR_NOS)

#else

/*
 * ARM Cortex-A9 UPCore and ARM11 UPCore.
 * Setup TTBR for normal memory, inner and outer write-back
 * no write-allocate cacheable.
 */

/* IRGN[0]=1,NOS=0,RGN=0b11,S=0,C=1 */

#define MMU_TTBR_CACHE_PTE_A9_FLAGS          (MMU_TTBR_RGN_NML_WB        | \
                                              MMU_TTBR_IRGN_NML_WB)

#endif /* _WRS_CONFIG_SMP */

/*
 * ARM Cortex-A15 MPCore does not support write-through for L1 and L2 cache.
 * Here, setup TTBR for inner and outer write-back, no write-allocate cached.
 */

#define MMU_TTBR_CACHE_PTE_A15_MPCORE ( MMU_TTBR_IRGN_NML_WB | \
                                        MMU_TTBR_RGN_NML_WB )

/*
 * For ARM Cortex-A8, or generic ARMv7 & ARMv6 cores:
 *
 * Select the mask for the single core or MPCore format for the TTBR. By
 * default we support the MPCore format because it is compatible with the UP
 * format and it is safer to zero out all the bits which are unused. Select
 * inner and outer write-through cached page tables.
 */

#ifdef _WRS_CONFIG_USE_MC_TTBR_FMT
#define MMU_TTBR_CACHE_PTE_GENERIC \
    ( MMU_TTBR_IRGN_NML_WT | MMU_TTBR_RGN_NML_WT )
#else  /* _WRS_CONFIG_USE_MC_TTBR_FMT */
#define MMU_TTBR_CACHE_PTE_GENERIC \
    ( MMU_TTBR_C_NML_C | MMU_TTBR_RGN_NML_WT )
#endif /* _WRS_CONFIG_USE_MC_TTBR_FMT */

#ifndef _ASMLANGUAGE

#if (_BYTE_ORDER == _LITTLE_ENDIAN)

/* little-endian */

/* First level page descriptors */

typedef struct
    {
    UINT type   : 2;        /* descriptor type, 1 => page */
    UINT pad1   : 2;        /* SBZ */
    UINT pad2   : 1;        /* SBO */
    UINT domain : 4;        /* domain number */
    UINT pbit   : 1;        /* 'P' bit */
    UINT addr   : 22;       /* base address of page table */
    } PAGE_DESC_FIELD;

/* First level "section" descriptor */
typedef struct
    {
    UINT type   : 2;        /* descriptor type, 2 => section */
    UINT bbit   : 1;        /* bufferable-bit */
    UINT cbit   : 1;        /* cacheable-bit */
    UINT xnbit  : 1;        /* XN-bit */
    UINT domain : 4;        /* domain number */
    UINT pbit   : 1;        /* XSCALE 'P' bit */
    UINT ap 	: 2;        /* AP */
    UINT tex    : 3;        /* TEX */
    UINT apx    : 1;        /* APX */
    UINT sbit   : 1;        /* S-bit */
    UINT nG     : 1;        /* nG-bit */
    UINT super  : 1;        /* 1 => supersection */
    UINT pad1   : 1;        /* SBZ */
    UINT addr   : 12;       /* base address of page table */
    } SECTION_DESC_FIELD;

/* First level "supersection" descriptor */
typedef struct
    {
    UINT type   : 2;        /* descriptor type, 2 => section */
    UINT bbit   : 1;        /* bufferable-bit */
    UINT cbit   : 1;        /* cacheable-bit */
    UINT xnbit  : 1;        /* XN-bit */
    UINT addrHi2: 4;        /* phys address 39:36 */
    UINT pbit   : 1;        /* XSCALE 'P' bit */
    UINT ap 	: 2;        /* AP */
    UINT tex    : 3;        /* TEX */
    UINT apx    : 1;        /* APX */
    UINT sbit   : 1;        /* S-bit */
    UINT nG     : 1;        /* nG-bit */
    UINT super  : 1;        /* 1 => supersection */
    UINT pad1   : 1;        /* SBZ */
    UINT addrHi : 4;        /* phys address 35:32 */
    UINT addrLo : 8;        /* phys address 31:24 */
    } SUPERSECTION_DESC_FIELD;

/* Layout of Page Table Entries (PTEs), actually small page descriptors */

typedef struct
    {
    UINT type   : 2;            /* page type, 3 => extended small page */
    UINT cb     : 2;            /* cacheable/bufferable bits */
    UINT ap     : 2;            /* access permission */
    UINT tex    : 3;            /* type extension field */
    UINT apx    : 1;        	/* access permission extension field */
    UINT sbz    : 2;            /* should be zero */
    UINT addr   : 20;           /* page base address */
    } PTE_FIELD;

#else /* (_BYTE_ORDER == _LITTLE_ENDIAN) */

/* big-endian */

/* First level page descriptors */

typedef struct
    {
    UINT addr   : 22;       /* base address of page table */
    UINT pbit   : 1;        /* XSCALE 'P' bit */
    UINT domain : 4;        /* domain number */
    UINT pad2   : 1;        /* SBO */
    UINT pad1   : 2;        /* SBZ */
    UINT type   : 2;        /* descriptor type, 1 => page */
    } PAGE_DESC_FIELD;

/* First level "section" descriptor */
typedef struct
    {
    UINT addr   : 12;       /* base address of page table */
    UINT pad1   : 1;        /* SBZ */
    UINT super  : 1;        /* 1 => supersection */
    UINT nG     : 1;        /* nG-bit */
    UINT sbit   : 1;        /* S-bit */
    UINT apx    : 1;        /* APX */
    UINT tex    : 3;        /* AP */
    UINT ap 	: 2;        /* AP */
    UINT pbit   : 1;        /* XSCALE 'P' bit */
    UINT domain : 4;        /* domain number */
    UINT xnbit  : 1;        /* XN-bit */
    UINT cbit  	: 1;        /* C-bit */
    UINT bbit  	: 1;        /* B-bit */
    UINT type   : 2;        /* descriptor type, 2 => section */
    } SECTION_DESC_FIELD;

/* First level "supersection" descriptor */
typedef struct
    {
    UINT addrLo : 8;        /* phys address 31:24 */
    UINT addrHi : 4;        /* phys address 35:32 */
    UINT pad1   : 1;        /* SBZ */
    UINT super  : 1;        /* 1 => supersection */
    UINT nG     : 1;        /* nG-bit */
    UINT sbit   : 1;        /* S-bit */
    UINT apx    : 1;        /* APX */
    UINT tex    : 3;        /* AP */
    UINT ap 	: 2;        /* AP */
    UINT pbit   : 1;        /* XSCALE 'P' bit */
    UINT addrHi2: 4;        /* phys address 39:36 */
    UINT xnbit  : 1;        /* XN-bit */
    UINT cbit  	: 1;        /* C-bit */
    UINT bbit  	: 1;        /* B-bit */
    UINT type   : 2;        /* descriptor type, 2 => section */
    } SUPERSECTION_DESC_FIELD;

/* Layout of Page Table Entries (PTEs), actually small page descriptors */

typedef struct
    {
    UINT addr   : 20;           /* page base address */
    UINT sbz    : 2;            /* should be zero */
    UINT apx    : 1;        	/* access permission extension field */
    UINT tex    : 3;            /* type extension field */
    UINT ap     : 2;            /* access permission */
    UINT cb     : 2;            /* cacheable/bufferable bits */
    UINT type   : 2;            /* page type, 3 => extended small page */
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
    UINT8       asid;                   /* ASID/context id */
    } MMU_TRANS_TBL;

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
IMPORT UINT32   (* _func_mmuIFaultStatusGet) (void);
IMPORT UINT32   mmuIFsrGet (void);	/* CP15_IFSR only available with MMUs */
IMPORT UINT32   mmuFarGet (void);	/* CP15_FAR only available with MMUs */
IMPORT UINT32   mmuFsrGet (void);	/* CP15_FSR only available with MMUs */

#endif  /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif  /* __INCmmuArmArch6PalLibh */

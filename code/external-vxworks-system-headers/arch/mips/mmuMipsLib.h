/* mmuMipsLib.h - Memory Management Unit Library for MIPS */

/*
 * Copyright (c) 1999-2000, 2003-2005, 2007, 2009-2012
 * Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. No license to Wind River intellectual property rights
 * is granted herein. All rights not licensed by Wind River are reserved
 * by Wind River.
 */

/*
modification history
--------------------
02h,08mar12,l_z  check MMU maxWired when locking the page. (WIND00317377)
02g,31mar11,slk  updates for xlp hardware table walk
02f,09mar11,slk  add support for XLP variant
02e,08dec10,slk  fix MAPPED_TO_PHYS - defect 237748
02d,27may10,d_c  Rename CAVIUM_CNMIPS_* to _WRS_CAVIUM_CNMIPS_* and define in
                 arch Makefile
02f,29jul10,slk  add defines for LMM support
02e,20jul10,slk  add defines for AIM MMU memory pool allocation
02d,09jul10,slk  add defines for 256M byte MMU pagesize
02c,29apr10,pad  Moved extern C statement after include statements.
02c,08apr10,d_c  LPA and execute inhibit support
02b,02apr09,pch  add 128M & 512M page sizes
02a,14feb09,slk  move exc page (-1) defines to mipsExcPage.h
01z,01feb07,pes  Remove OSM exception page entries. The variables involved
                 have been moved to .kseg0data.
01y,23feb05,d_c  SPR 103891: Add bit to arch-dependent state word to
                 indicate user has access. Add bit to PTE to indicate
		 page is in kuseg. Corrected copyright.
01x,09dec04,pes  Remove setting the 8K page size bit in MMU_PTE_INIT_STATE.
                 This is an artifact of old code that encoded entryLo1 instead
		 of entryLo0.
01w,01nov04,slk  Add define for OSM error stack pointer
01v,22oct04,slk  SPR 92598: Add support for OSM handler and guard page size
                 storage in the exception page scratch area
01u,21sep04,sru  Added comment describing rationale for 8K MMU page size.
01t,15sep04,sru  Made MMU_PAGE_SIZE a simple constant, so that it can be
                 used as a parameter to the _WRS_DATA_ALIGN_BYTES directive.
01s,06aug04,sru  Add bitfields to pageMask portion of TLB.  Create TLB
                 structure for reading TLB hardware; update page masks.
01r,24mar04,slk  Modify definition of MMU_VA_TO_PFN_MASK for 16M rather than
                 4K page size.  Also rename MMU_VA_TO_PFN_MASK to
                 MMU_VA_TO_PFN_16M_MASK.
01q,02mar04,pes  Correct conditional expression for determining definition of
                 MMU_PTE_TLBLO0_OFFSET.
01p,17feb04,pes  Adjust offset to tlblo0 in PTE to deal with big-endian 32-bit
                 hosts.
01o,11dec03,jmt  Code Review changes
01n,08dec03,jmt  Incorporate Code Review changes
01m,02dec03,jmt  Continued Testing of MIPS AIM AD-MMU code
01l,19nov03,jmt  Continue development of MIPS AD-MMU code
01k,30oct03,jmt  rewrite as architecture-dependent portion of AIM MMU library
01j,16sep03,jmt  Modify TLB Handling for Base 6
01i,10sep03,jmt  Merge code from AE to Base 6
01h,12sep00,dra  Cleanup.
01g,30aug00,dra  Updated ASID fields.
01f,14jun00,dra  generalize the mmuMipsUnMap flush of virtual page address to
                 all Mips archs
01e,19apr00,dra  Expand MMU_MIPS_CONFIG to allow write protection of page
                 tables.  Add support for page unmap address flush.
01d,13apr00,dra  Added support for xTLB vector.
01c,24jan00,dra  Added pointer to mmuMipsConfig struct for
                 mmuMipsContextSet routine.
01b,15sep99,dra  Updated MMU_STATE macros.
01a,30jul99,dra  Created.
*/

/*
DESCRIPTION:

The MIPS family of devices range from the Toshiba TX3907 to the NEC VR4100
resulting in a wide range of implementations of memory management units.
This library contains the constant declarations, structures, and globals
that are generic to all of these devices.

The MIPS mmu library is a two-part library made from the generic library
module and a device-specific module; mmuMipsLib and mmuMipsxxxLib respectively.
This header file contains the data structure MMU_MIPS_CONFIG used to
interface the generic module to the device-specific one.  It also contains
declarations of all of the device-specific library initialization functions
as well as the generic one.

*/

#ifndef __INCmmuMipsLibh
#define __INCmmuMipsLibh

#ifndef _ASMLANGUAGE
#include "aimMmuLib.h"
#endif
#include <arch/mips/mipsExcPage.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Defines */

/*
 * Table Entry Definitions
 * These are definitions for the indexes for the cache, protection
 * and mask tables defined for every device-dependent library
 */

/* Protection Table Indexes */

#define MMU_READWRITE   3
#define MMU_NO_WRITE	2
#define MMU_WRITE	32

/* Cache Table Indexes */

#define MMU_INVALID	0
#define MMU_CACHEOFF	1
#define MMU_CPYBACK	2
#define MMU_WRTHRU	3
#define MMU_COHRNT	4

/* Mask Table Indexes */

#define MMU_PMASK	1
#define MMU_VMASK	2
#define MMU_PVMASK	3
#define MMU_CMASK	4
#define MMU_PCMASK	5
#define MMU_VCMASK	6
#define MMU_PVCMASK	7

/*
 * The MIPS MMU supports a hardware page size of 4K.  However, the MMU 
 * library treats each TLB register group as an entity for a single 
 * virtual->physical mapping.  So, the EntryLo0 and EntryLo1 registers
 * are always configured to map adjacent physical pages.  For this reason,
 * the de facto hardware page size is 2 * 4k, or 8K.
 */

#define MMU_PAGE_SIZE           0x2000  /* used in _WRS_ALIGN... directive */

/* MIPS common masks */ 

#define MIPS_R_ENTRY_MASK 0xFFC00000 /* Mask off top-10 bits in BVaddr */
#define MIPS_R_ENTRY_SHIFT	 22
#define MIPS_P_ENTRY_MASK 0x003FE000 /* Mask off middle-9 bits in BVaddr */

/* Context table information */

#define MMU_GLOBAL_CONTEXT	0
#define MMU_FIRST_LOCAL_CONTEXT 1
#define MMU_LAST_LOCAL_CONTEXT	255

/* Page size support information */

/*
 * MMU_PAGE_SIZES_STANDARD are the page sizes defined by the MIPS32 hardware
 * architecture.  This is used in palDescInit(), together with probing the
 * pagemask register, to determine the sizes supported by a particular
 * implementation.
 */

#define MMU_PAGE_SIZES_STANDARD (MMU_PAGE_MASK_8K   | \
				 MMU_PAGE_MASK_32K  | \
				 MMU_PAGE_MASK_128K | \
				 MMU_PAGE_MASK_512K | \
				 MMU_PAGE_MASK_2M   | \
				 MMU_PAGE_MASK_8M   | \
				 MMU_PAGE_MASK_32M  | \
				 MMU_PAGE_MASK_128M | \
				 MMU_PAGE_MASK_512M)

/*
 * MMU_PAGE_SIZES_ALLOWED are page sizes supported by the MIPS AD-MMU code.
 * The AIM page table design restricts the allowed page size to a minimum of
 * 4KB and a maximum of 4MB.
 */

#define MMU_PAGE_SIZES_ALLOWED	(MMU_PAGE_MASK_8K   | \
				 MMU_PAGE_MASK_32K  | \
				 MMU_PAGE_MASK_128K | \
				 MMU_PAGE_MASK_512K | \
				 MMU_PAGE_MASK_2M)

#define MMU_MAX_PAGE_SIZES	5

/***********************************************************************
 * Hardware TLB definitions
 */

#define TLB_4K_PAGE_SIZE        0x00001000
#define TLB_16K_PAGE_SIZE       0x00004000
#define TLB_64K_PAGE_SIZE       0x00010000
#define TLB_256K_PAGE_SIZE      0x00040000
#define TLB_1M_PAGE_SIZE        0x00100000
#define TLB_4M_PAGE_SIZE        0x00400000
#define TLB_16M_PAGE_SIZE       0x01000000
#define TLB_64M_PAGE_SIZE       0x04000000
#define TLB_256M_PAGE_SIZE      0x10000000

#define TLB_4K_PAGE_SIZE_MASK   0x00000000 
#define TLB_16K_PAGE_SIZE_MASK  0x00006000 
#define TLB_64K_PAGE_SIZE_MASK  0x0001E000 
#define TLB_256K_PAGE_SIZE_MASK 0x0007E000 
#define TLB_1M_PAGE_SIZE_MASK   0x001FE000 
#define TLB_4M_PAGE_SIZE_MASK   0x007FE000 
#define TLB_16M_PAGE_SIZE_MASK  0x01FFE000 
#define TLB_64M_PAGE_SIZE_MASK  0x07FFE000 
#define TLB_256M_PAGE_SIZE_MASK 0x1FFFE000 

#define TLB_PAGE_MASK_SHIFT             13  /* lower 13 bits must be 0 */

/* R4K TLB definitions
 * - does not match hardware definitions
 * The software will use page sizes twice the Hardware TLB page size
 * The page size mask does not change.
 */

#define TLB_8K_PAGE_SIZE        (2*TLB_4K_PAGE_SIZE)
#define TLB_32K_PAGE_SIZE       (2*TLB_16K_PAGE_SIZE)
#define TLB_128K_PAGE_SIZE      (2*TLB_64K_PAGE_SIZE)
#define TLB_512K_PAGE_SIZE      (2*TLB_256K_PAGE_SIZE)
#define TLB_2M_PAGE_SIZE        (2*TLB_1M_PAGE_SIZE)
#define TLB_8M_PAGE_SIZE        (2*TLB_4M_PAGE_SIZE)
#define TLB_32M_PAGE_SIZE       (2*TLB_16M_PAGE_SIZE)
#define TLB_128M_PAGE_SIZE      (2*TLB_64M_PAGE_SIZE)
#define TLB_512M_PAGE_SIZE      (2*TLB_256M_PAGE_SIZE)

#define TLB_8K_PAGE_SIZE_MASK   TLB_4K_PAGE_SIZE_MASK
#define TLB_32K_PAGE_SIZE_MASK  TLB_16K_PAGE_SIZE_MASK
#define TLB_128K_PAGE_SIZE_MASK TLB_64K_PAGE_SIZE_MASK
#define TLB_512K_PAGE_SIZE_MASK TLB_256K_PAGE_SIZE_MASK
#define TLB_2M_PAGE_SIZE_MASK   TLB_1M_PAGE_SIZE_MASK
#define TLB_8M_PAGE_SIZE_MASK   TLB_4M_PAGE_SIZE_MASK
#define TLB_32M_PAGE_SIZE_MASK  TLB_16M_PAGE_SIZE_MASK
#define TLB_128M_PAGE_SIZE_MASK TLB_64M_PAGE_SIZE_MASK
#define TLB_512M_PAGE_SIZE_MASK TLB_256M_PAGE_SIZE_MASK


/* TLB EntryLo PFN defines */

#ifdef _WRS_MIPS_ENABLE_LPA

#if defined (MIPSXX_cav_cn3xxx)

/* Bits 36 through 39 (30 and 33 of the PFN) are reserved/0 in
 * Cavium 38xx physical addresses
 */
#define TLB_4K_PFN_MASK         0x000007FC3FFFFFC0
#define TLB_8K_PFN_MASK         0x000007FC3FFFFF80
#define TLB_32K_PFN_MASK        0x000007FC3FFFFE00
#define TLB_128K_PFN_MASK       0x000007FC3FFFF800
#define TLB_512K_PFN_MASK       0x000007FC3FFFE000
#define TLB_2M_PFN_MASK         0x000007FC3FFF8000
#define TLB_8M_PFN_MASK         0x000007FC3FFE0000
#define TLB_32M_PFN_MASK        0x000007FC3FF80000
#define TLB_128M_PFN_MASK       0x000007FC3FE00000
#define TLB_512M_PFN_MASK       0x000007FC3F800000

#elif defined (MIPSXX_cav_cn5xxx) || defined (MIPSXX_cav_cn6xxx)

/* Bits 38 through 39 (32 and 33 of the PFN) are reserved/0 in
 * Cavium 58xx and 6xxx physical addresses
 */
#define TLB_4K_PFN_MASK         0x000007FCFFFFFFC0
#define TLB_8K_PFN_MASK         0x000007FCFFFFFF80
#define TLB_32K_PFN_MASK        0x000007FCFFFFFE00
#define TLB_128K_PFN_MASK       0x000007FCFFFFF800
#define TLB_512K_PFN_MASK       0x000007FCFFFFE000
#define TLB_2M_PFN_MASK         0x000007FCFFFF8000
#define TLB_8M_PFN_MASK         0x000007FCFFFE0000
#define TLB_32M_PFN_MASK        0x000007FCFFF80000
#define TLB_128M_PFN_MASK       0x000007FCFFE00000
#define TLB_512M_PFN_MASK       0x000007FCFF800000

#elif defined (_WRS_MIPS_NETLOGIC_CPU)

#define TLB_4K_PFN_MASK         0x00000003FFFFFFC0
#define TLB_8K_PFN_MASK         0x00000003FFFFFF80
#define TLB_32K_PFN_MASK        0x00000003FFFFFE00
#define TLB_128K_PFN_MASK       0x00000003FFFFF800
#define TLB_512K_PFN_MASK       0x00000003FFFFE000
#define TLB_2M_PFN_MASK         0x00000003FFFF8000
#define TLB_8M_PFN_MASK         0x00000003FFFE0000
#define TLB_32M_PFN_MASK        0x00000003FFF80000
#define TLB_128M_PFN_MASK       0x00000003FFE00000
#define TLB_512M_PFN_MASK       0x00000003FF800000

#else
#error LPA support not implemented for selected variant
#endif /* defined (_WRS_MIPS_NETLOGIC_CPU) */

#else /* not _WRS_MIPS_ENABLE_LPA */

#define TLB_4K_PFN_MASK         0x3FFFFFC0
#define TLB_8K_PFN_MASK         0x3FFFFF80
#define TLB_32K_PFN_MASK        0x3FFFFE00
#define TLB_128K_PFN_MASK       0x3FFFF800
#define TLB_512K_PFN_MASK       0x3FFFE000
#define TLB_2M_PFN_MASK         0x3FFF8000
#define TLB_8M_PFN_MASK         0x3FFE0000
#define TLB_32M_PFN_MASK        0x3FF80000
#define TLB_128M_PFN_MASK       0x3FE00000
#define TLB_512M_PFN_MASK       0x3F800000

#endif /* _WRS_MIPS_ENABLE_LPA */

/* Physical address defines */

#if defined (_WRS_CAVIUM_CNMIPS_CORE) || defined (_WRS_CAVIUM_CNMIPS_II_CORE)

#define PHYS_ADDR_CAVIUM_CNMIPS_IO_WINDOW_MIN  0x0000000010000000ULL
#define PHYS_ADDR_CAVIUM_CNMIPS_IO_WINDOW_MAX  0x000000001FFFFFFFULL
#define PHYS_ADDR_CAVIUM_CNMIPS_IO_BIT         0x0001000000000000ULL

#endif /* defined (_WRS_CAVIUM_CNMIPS_CORE) || defined (_WRS_CAVIUM_CNMIPS_II_CORE) */

/* virtual address masks */

#define TLB_2M_VADDR_MASK       0x00200000
#define TLB_512K_VADDR_MASK     0x00380000
#define TLB_128K_VADDR_MASK     0x003E0000
#define TLB_32K_VADDR_MASK      0x003F8000
#define TLB_8K_VADDR_MASK       0x003FE000

#define TLB_2M_VADDR_SHIFT      (21 - MMU_PTE_SIZE_SHIFT)
#define TLB_512K_VADDR_SHIFT    (19 - MMU_PTE_SIZE_SHIFT)
#define TLB_128K_VADDR_SHIFT    (17 - MMU_PTE_SIZE_SHIFT)
#define TLB_32K_VADDR_SHIFT     (15 - MMU_PTE_SIZE_SHIFT)
#define TLB_8K_VADDR_SHIFT      (13 - MMU_PTE_SIZE_SHIFT)

/* Page Table Size defines
 * These define the page table size for each of the page sizes.
 * Use the smallest page size supported
 */
#define TLB_2M_TABLE_SIZE       2
#define TLB_512K_TABLE_SIZE     (4 * TLB_2M_TABLE_SIZE)
#define TLB_128K_TABLE_SIZE     (4 * TLB_512K_TABLE_SIZE)
#define TLB_32K_TABLE_SIZE      (4 * TLB_128K_TABLE_SIZE)
#define TLB_8K_TABLE_SIZE       (4 * TLB_32K_TABLE_SIZE)

/* available TLB sizes */

#define TLB_PAGE_SIZE_STANDARD	(TLB_8K_PAGE_SIZE    | \
                                 TLB_32K_PAGE_SIZE   | \
                                 TLB_128K_PAGE_SIZE  | \
                                 TLB_512K_PAGE_SIZE  | \
                                 TLB_2M_PAGE_SIZE    | \
                                 TLB_8M_PAGE_SIZE    | \
                                 TLB_32M_PAGE_SIZE   | \
                                 TLB_128M_PAGE_SIZE  | \
                                 TLB_512M_PAGE_SIZE)

/* Page Grain register defines */

#if defined (_WRS_CAVIUM_CNMIPS_CORE) || defined (_WRS_CAVIUM_CNMIPS_II_CORE)

#define PAGE_GRAIN_ELPA  0x20000000 /* enable LPA mode */
#define PAGE_GRAIN_XIE   0x40000000 /* enable execute inhibit attribute */
#define PAGE_GRAIN_RIE   0x80000000 /* enable read inhibit attribute */

#endif /* defined (_WRS_CAVIUM_CNMIPS_CORE) || defined (_WRS_CAVIUM_CNMIPS_II_CORE) */

#define MMU_R4K_VPN2_SHIFT          13		/* right shift justify VPN of
						 * address
						 */
#define MMU_R4K_PFN_SHIFT           6		/* left shift for PFN loc */

/* EntryLo state bits */

#define MMU_R4K_STATE_VALID	    0x00000002  /* V flag set      */
#define MMU_R4K_STATE_VALID_NOT	    0x00000000  /* V flag reset    */
#define MMU_R4K_STATE_WRITABLE	    0x00000004  /* D flag set      */
#define MMU_R4K_STATE_GLOBAL	    0x00000001  /* G flag set      */
#define MMU_R4K_UNCACHED            0x00000010
#define MMU_R4K_CACHED              0x00000018
#define MMU_R4K_CACHEABLE           0x00000038

/* TLB entryLo0 bit definitions for execute inhibit */

#ifdef _WRS_MIPS_ENABLE_EXE_INH
#if defined (_WRS_CAVIUM_CNMIPS_CORE) || defined (_WRS_CAVIUM_CNMIPS_II_CORE)

#ifdef _WRS_MIPS_ENABLE_LPA
#define MMU_R4K_EXE_INH            0x4000000000000000ULL
#else
#define MMU_R4K_EXE_INH            0x40000000
#endif

#else /* ! (defined (_WRS_CAVIUM_CNMIPS_CORE) || defined (_WRS_CAVIUM_CNMIPS_II_CORE)) */
#error Execute inhibit is not supported on this variant
#endif /* defined (_WRS_CAVIUM_CNMIPS_CORE) || defined (_WRS_CAVIUM_CNMIPS_II_CORE) */
#endif /* _WRS_MIPS_ENABLE_EXE_INH */

/* TLB entryLo0 attribute bit offsets */

#define MMU_R4K_GLOBAL_START     0           /* Start point of global bit */
#define MMU_R4K_VALID_START      1           /* Start point of valid bit  */
#define MMU_R4K_DIRTY_START      2           /* Start point of dirty bit  */
#define MMU_R4K_CACHE_START      3           /* Start point of cache field*/

/***********************************************************************
 * Arch-dependent MMU state word defines
 */

/* Arch-dependent state bits: Valid, Writable, and cache
 * correspond to the bits in TLB entryLo. But the others are purely
 * logical, and do not correlate to hardware. These must be
 * interpreted and translated in code.
 */

#define MMU_BASE_STATE                  0x00000000
#define MMU_STATE_READABLE              0x00000000
#define MMU_STATE_VALID                 MMU_R4K_STATE_VALID
#define MMU_STATE_VALID_NOT             MMU_R4K_STATE_VALID_NOT	
#define MMU_STATE_WRITABLE              MMU_R4K_STATE_WRITABLE
#define MMU_STATE_CACHED                MMU_R4K_CACHED
#define MMU_STATE_UNCACHED              MMU_R4K_UNCACHED
#define MMU_STATE_CACHEABLE             MMU_R4K_CACHEABLE
#define MMU_STATE_LOCKED		0x00000100
#define MMU_STATE_ISR_CALLABLE		0x00000200
#define MMU_STATE_USER_ACCESS           0x00000400
#define MMU_STATE_EXECUTABLE            0x00000800
#define MMU_STATE_INVALID               0xC0000000  /* Invalid State */

/* MMU State bits that coorespond directly to entryLo0 in hardware.
 * On Cavium Octeon, the TLBLo cache bits have no effect on caching mode.
 * and are not part of the MMU arch-dependent state word.
 */
#if defined (_WRS_CAVIUM_CNMIPS_CORE) || defined (_WRS_CAVIUM_CNMIPS_II_CORE)
#define MMU_STATE_ENTRYLO_MASK         (MMU_R4K_STATE_VALID \
					| MMU_R4K_STATE_WRITABLE)
#else
#define MMU_STATE_ENTRYLO_MASK          (MMU_R4K_STATE_VALID	  \
					 | MMU_R4K_STATE_WRITABLE \
					 | MMU_R4K_CACHEABLE)
#endif /* defined (_WRS_CAVIUM_CNMIPS_CORE) || defined (_WRS_CAVIUM_CNMIPS_II_CORE) */
					
/* Arch-dependent state masks: Used in MMU state mask variables and
 * data structures. These coorespond to the three basic types of
 * types of information stored in MMU state variables.
 */
#define MMU_STATE_MASK_VALID            MMU_STATE_VALID
#define MMU_STATE_MASK_CACHEABLE        MMU_STATE_CACHEABLE
#define MMU_STATE_MASK_PROT             (MMU_STATE_WRITABLE \
					 | MMU_STATE_EXECUTABLE \
					 | MMU_STATE_USER_ACCESS)

/* "Special" arch-dependent state masks. Used for unique
 * arch-dependent attributes.
 */
#define MMU_STATE_MASK_LOCKED		MMU_STATE_LOCKED
#define MMU_STATE_MASK_ISR_CALLABLE	MMU_STATE_ISR_CALLABLE


/***********************************************************************
 * Other TLB/PTE definitions
 */

/* Wired defines */

#define MMU_MAX_WIRED_REGS          63

/* Entry Hi defines */
   
#define MMU_R4K_VPN2_MASK           0xffffe000      /* page no mask */
#define MMU_R4K_ASID_MASK           0x000000ff
#define MMU_VA_TO_PFN_16M_MASK      0x1e000000      /* 16M page mask */
#define MMU_NUM_ASID                256
#define MMU_R4K_PAGE_SHIFT          12     /* convert VM pagenum to VA */

/*
 * Table Entry Definitions
 * These are definitions for the indexes for the cache, protection
 * and mask tables defined for every device-dependent library
 */

/* Protection Table Indexes */

#define MMU_READWRITE   3
#define MMU_NO_WRITE	2
#define MMU_WRITE	32

/* Cache Table Indexes */

#define MMU_INVALID	0
#define MMU_CACHEOFF	1
#define MMU_CPYBACK	2
#define MMU_WRTHRU	3
#define MMU_COHRNT	4

/* Mask Table Indexes */

#define MMU_PMASK	1
#define MMU_VMASK	2
#define MMU_PVMASK	3
#define MMU_CMASK	4
#define MMU_PCMASK	5
#define MMU_VCMASK	6
#define MMU_PVCMASK	7

/* TLB Miss Setup Structure offsets */

#define MMU_SETUP_VADDR_MASK_OFFSET  0x0
#define MMU_SETUP_PAGE_MASK_OFFSET   0x4
#define MMU_SETUP_ENTRYLO0_OR_OFFSET 0x8
#define MMU_SETUP_TABLE_SIZE_OFFSET  0xc
#define MMU_SETUP_VADDR_SHIFT_OFFSET 0x10

/* PTE Defines */

#define MMU_BYTES_PER_ENTRY	   16	/* Num bytes per page table entry */
#define MMU_PTE_SIZE_SHIFT         4
#define MMU_PTE_PAGE_MASK_OFFSET   0x00

#ifndef _WRS_MIPS_HW_PG_WALKER
#define MMU_PTE_ENTRYLO1_OR_OFFSET 0x04
#if defined (_WRS_PHYS_ADDR_IS_64_BITS) && (_BYTE_ORDER == _BIG_ENDIAN)  && (_WRS_INT_REGISTER_SIZE == 4)
#define MMU_PTE_TLBLO0_OFFSET      0x0c
#else /* _WRS_PHYS_ADDR_IS_64_BITS) && (_BYTE_ORDER == _BIG_ENDIAN) */
#define MMU_PTE_TLBLO0_OFFSET      0x08
#endif /* _WRS_PHYS_ADDR_IS_64_BITS) && (_BYTE_ORDER == _BIG_ENDIAN) */
#else  /* _WRS_MIPS_HW_PG_WALKER */
#define MMU_PTE_TLBLO0_OFFSET      0x00
#define MMU_PTE_TLBLO1_OFFSET      0x08
#define MMU_PTE_DISCARD_STATE_BITS_SHIFT	5
#endif /* _WRS_MIPS_HW_PG_WALKER */

#define MMU_PTE_TBLPTR_MASK      0xFFFFFFFE
#define MMU_PTE_TERM_MASK        0x00000001
#define MMU_PTE_NOT_TERM         0x00000000
#define MMU_PTE_TERM             0x00000001

#define MMU_TEMP_TLB_STATE (MMU_R4K_STATE_VALID | MMU_R4K_CACHED | \
			    MMU_R4K_STATE_WRITABLE | MMU_R4K_STATE_GLOBAL)
#define MMU_PTE_INIT_STATE (MMU_R4K_UNCACHED | MMU_R4K_STATE_WRITABLE)

/* dynamic MMU page size not supported if h/w page walker is enabled */

#ifndef _WRS_MIPS_HW_PG_WALKER
#define ENABLE_DYNAMIC_SIZE
#else  /* _WRS_MIPS_HW_PG_WALKER */
#undef ENABLE_DYNAMIC_SIZE
#endif /* _WRS_MIPS_HW_PG_WALKER */

/* translation from virtual and physical address space to a pointer
 * LMM mode does not translate addresses to KSEG0.  A virtual address
 * is returned without modification while a physical address has the 
 * virtual to physical offset added to it (lmmMipsVirtToPhysOffset)
 */

#ifndef _ASMLANGUAGE
extern _WRS_SECTION_KSEG0BSS int  lmmMipsModeEnabled;
extern _WRS_SECTION_KSEG0BSS UINT64 lmmMipsVirtToPhysOffset;
#define KM_TO_PTR(x)                    \
                ((lmmMipsModeEnabled == 0) ? KM_TO_K0(x) : (x))
#define PHYS_TO_PTR(x)                  \
                ((lmmMipsModeEnabled == 0) ? PHYS_TO_K0(x) : \
                (x + lmmMipsVirtToPhysOffset))

/* identity mapped images still simply translate KSEG0 to physical.
 * large memory model images can be passed a KSEG2 mapped address or
 * a KSEG0/KSEG1 address.  if its KSEG2 we simply subtract our virtual
 * to physical translation offset from the mapped address (making sure its
 * signed extended so the upper 32 bits are 1's) else
 * the mapped address must be KSEG0 or KSEG1 and we do the simple translation
 * to get the correct address
 */

#define MAPPED_TO_PHYS(x)               \
                ((lmmMipsModeEnabled == 0) ? KM_TO_PHYS(x) : \
                (IS_KSEG2(x) ? ((INT64)((INT32)x) - lmmMipsVirtToPhysOffset) :\
                KM_TO_PHYS(x)))
#define IS_LMM_MAPPED   (lmmMipsModeEnabled != 0)
#endif /* _ASMLANGUAGE */


/* MIPS_TLB_ENTRY structure offsets */

#define MIPS_TLB_ENTRY_OFS_HI            0
#define MIPS_TLB_ENTRY_OFS_LO0           8

#ifdef _WRS_MIPS_ENABLE_LPA
#define MIPS_TLB_ENTRY_OFS_LO1           16
#define MIPS_TLB_ENTRY_OFS_PAGEMASK      24
#define MIPS_TLB_ENTRY_SIZE              32
#else
#define MIPS_TLB_ENTRY_OFS_LO1           12
#define MIPS_TLB_ENTRY_OFS_PAGEMASK      16
#define MIPS_TLB_ENTRY_SIZE              24
#endif

#ifndef _ASMLANGUAGE

/* The Page-Table Entry (PTE) Structure */

typedef struct
#ifndef _WRS_MIPS_HW_PG_WALKER
    {
#if (_BYTE_ORDER == _BIG_ENDIAN)
    UINT32      pageMask:19;
    UINT32  reserved:10;
    UINT32      isKuseg:1;
    UINT32  isr:1;
    UINT32  locked:1;   /* LSB */
#else   /* _BYTE_ORDER == _BIG_ENDIAN */
    UINT32  locked:1;   /* LSB */
    UINT32  isr:1;
    UINT32      isKuseg:1;
    UINT32  reserved:10;
    UINT32      pageMask:19;
#endif  /* _BYTE_ORDER == _BIG_ENDIAN */
    UINT32      entryLo1OrValue;
    PHYS_ADDR   entryLo0;
#else /* _WRS_MIPS_HW_PG_WALKER */
    {
#if (_BYTE_ORDER == _BIG_ENDIAN)
    UINT64      readInhibit0:1;
    UINT64      excInhibit0:1;
    UINT64      isKuseg:1;
    UINT64      isr:1;
    UINT64      locked:1;
    UINT64      pageMask:19;
    UINT64      reserved0:6;
    UINT64      entryLo0:34; /* LSB */
    UINT64      readInhibit1:1;
    UINT64      excInhibit1:1;
    UINT64      reserved1:28;
    UINT64      entryLo1:34; /* LSB */
#else   /* _BYTE_ORDER == _BIG_ENDIAN */
    UINT64      entryLo0:34; /* SLB */
    UINT64      reserved0:6;
    UINT64      pageMask:19;
    UINT64      locked:1;
    UINT64      isr:1;
    UINT64      isKuseg:1;
    UINT64      excInhibit0:1;
    UINT64      readInhibit0:1;
    UINT64      entryLo1:34; /* LSB */
    UINT64      reserved1:28;
    UINT64      excInhibit1:1;
    UINT64      readInhibit1:1;
#endif  /* _BYTE_ORDER == _BIG_ENDIAN */
#endif /* _WRS_MIPS_HW_PG_WALKER */
    } PTE;

/* Define the TLB Structure. */

typedef struct
    {
#if (_WRS_INT_REGISTER_SIZE == 8)
    UINT64	entryHi;
#else  /* (_WRS_INT_REGISTER_SIZE != 8) */
    UINT32	entryHi;
    UINT32      pad1;
#endif /* (_WRS_INT_REGISTER_SIZE != 8) */
    
#ifdef _WRS_MIPS_ENABLE_LPA
    UINT64      entryLo0;
    UINT64	entryLo1;
#else    
    UINT32      entryLo0;
    UINT32	entryLo1;
#endif /* _WRS_MIPS_ENABLE_LPA */
    
    UINT32	pageMask;
    UINT32      pad2;
    } MIPS_TLB_ENTRY;

typedef void      (*MMUMIPSTLBCLRFUNC)(UINT, UINT, VIRT_ADDR);
typedef void      (*MMUMIPSTLBCLRALLFUNC)(UINT);
typedef void      (*MMUMIPSTLBWIREDENTRYSETFUNC)(UINT32, PTE *);
typedef void      (*MMUMIPSTLBENABLEFUNC)(UINT,UINT,UINT,FUNCPTR);
typedef void      (*MMUMIPSTLBVECFUNC)(void);

/* 
 * TLB Setup structure for Miss handler
 *
 * This structure holds the information needed by the TLB Miss Handler
 * to setup the TLB entry.
 */

typedef struct
    {
    UINT32   vAddrMask;
    UINT32   pageMask;
    UINT32   entryLo0OrValue;
    UINT32   tableSize;
    UINT32   vAddrShift;
    } MIPS_TLB_SETUP_STRUCT;

/* Prototypes external MIPS MMU routines */

IMPORT STATUS mmuMipsLibInit (VIRT_ADDR, size_t);
IMPORT STATUS mmuMipsLpaEnable (void);
IMPORT BOOL mmuMipsLpaIsEnabled (void);
IMPORT STATUS mmuMipsExeInhEnable (void);
IMPORT BOOL mmuMipsExeInhIsEnabled (void);

#endif  /* ifndef _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif  /* __INCmmuMipsLibh */

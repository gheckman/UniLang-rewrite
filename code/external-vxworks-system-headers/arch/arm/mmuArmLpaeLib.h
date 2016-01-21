/* mmuArmLpaeLib.h - ARM LPAE MMU library header file */

/*
 * Copyright (c) 2013-2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
17apr14,c_l  add the write protection of L2 page table. (VXW6-73478)
01a,01jun13,zgl  written
*/

#ifndef __INCmmuArmLpaeLibh
#define __INCmmuArmLpaeLibh

#ifndef _ASMLANGUAGE

/* includes */

#include <memLib.h>
#include <semLib.h>

#ifdef __cplusplus
extern "C" {
#endif

#endif /* _ASMLANGUAGE */

/* defines */

/* make mask, h = end bit, l = start bit */

#define MAKE_MASK_64(h,l) (((1ULL << (h + 1)) - 1) & ~((1ULL << l) - 1))
#define MAKE_MASK_32(h,l) (((1UL << (h + 1)) - 1) & ~((1UL << l) - 1))

/*
 * The page size we will use. Ignore the sub-page, Large Page and Tiny
 * Page features.
 */

#define MMU_PAGE_SIZE   4096
#define PAGE_SIZE       MMU_PAGE_SIZE

#define MMU_ADRS_TO_L1D_INDEX_SHIFT 30
#define MMU_ADRS_TO_L2D_INDEX_SHIFT 21
#define MMU_PAGE_SIZE_SHIFT 12

#define MMU_LPAE_NO_BITS_PHYS_ADDR 40


/* get Level 2 index */

#define MMU_L2PD_INDEX_GET(vaddr) \
        ((vaddr >> MMU_ADRS_TO_L2D_INDEX_SHIFT) & (MMU_NUM_L2_DESCS - 1))

#define MMU_PTE_INDEX_MASK  MAKE_MASK_32(20,12)  /* extract PTE index from */
                                                 /* Virt Addr */
#define MMU_PTE_BA_MASK     MAKE_MASK_64(39,12)  /* extract phys base address */
#define MMU_PTE_INDEX_SHIFT 12          /* shift to make that into PTE index */

#define MMU_ADDR_PI_MASK    0x00000FFF  /* extract page offset from Virt Addr */

/* extract phys L2 page table base addr from L1PD */

#define MMU_L1PD_L2TBL_MASK  MAKE_MASK_64(39,12)

/* extract phys L3 page table base addr from L2PD */

#define MMU_L2PD_L3TBL_MASK  MMU_L1PD_L2TBL_MASK

/* Level 1/2 Descriptor types */

#define MMU_DESC_TYPE_FAULT         0x0   /* any access will cause a fault */
#define MMU_DESC_TYPE_BLOCK         0x1   /* block descriptor */
#define MMU_DESC_TYPE_TABLE         0x3   /* page table descriptor */

/* defalt Descriptor types for Level 1/2 */

#define MMU_DEF_L1_PAGE             MMU_DESC_TYPE_TABLE   
#define MMU_DEF_L2_PAGE             MMU_DEF_L1_PAGE

/* Level 3 Descriptor or Page Table Entry (PTE) types */

#define MMU_PTE_TYPE_FAULT   0x0        /* any access will cause a fault */
#define MMU_PTE_TYPE_PAGE    0x3        /* page descriptor */

#define MMU_PTE_AF      (1 << 10)       /* access flag bit */

/* No. of Descriptor for each page table level */

#define MMU_NUM_L1_DESCS 4
#define MMU_NUM_L2_DESCS 512
#define MMU_NUM_L3_DESCS 512

#define MMU_L1_TABLE_SIZE MMU_PAGE_SIZE

/* No. of pages a Level 1 Descriptor table takes up */

#define MMU_L1_DESC_PAGES (MMU_L1_TABLE_SIZE / MMU_PAGE_SIZE)

/* The amount described by a L1 Descriptor */

#define MMU_L1_DESC_RANGE (MMU_NUM_L2_DESCS * MMU_NUM_L3_DESCS * MMU_PAGE_SIZE)

/* Size of a Page Table */

#define MMU_PAGE_TABLE_SIZE MMU_PAGE_SIZE

/*
 * The amount described by a L2 Descriptor, which equals the smallest
 * amount of VM allocatable in VxWorks.
 */

#define MMU_L2_DESC_RANGE (MMU_NUM_L3_DESCS * MMU_PAGE_SIZE) /* 2 MBytes */

#define MMU_PAGE_BLOCK_SIZE MMU_L2_DESC_RANGE
        

/* Number of possible ASIDs */

#define MMU_NUM_ASIDS        256
#define VXWORKS_KERNEL_ASID  0    /* reserved ASID for VxWorks kernel */

/*
 * Architecture-dependent MMU states. These are states settable for pages and
 * here they correspond to settings in the Page Table Entries (PTEs).
 */

#define MMU_STATE_INVALID_STATE     0xFFFFFFFF

#define MMU_STATE_MASK_VALID        0x00000003  /* bits[1:0] for PTE state */

#define MMU_STATE_MASK_WRITABLE     0x000000C0  /* AP[2:1], bits[7:6] */

#define MMU_STATE_MASK_CACHEABLE    0x0000031C	/* SH[1:0], AttrIndex[2:0], */
                                                /* bits[9:8] and bits[4:2] */

#define MMU_STATE_VALID             0x3         /* 0b11 means valid */
#define MMU_STATE_VALID_NOT         0x0         /* 0b00 means NOT valid */

#define MMU_STATE_MASK_PROTECTION   0x000000C0      /* AP[2:1], bits[7:6] */

#define MMU_STATE_SUP_RO            0x00000080      /* AP: 10 */
#define MMU_STATE_SUP_RW            0x00000000      /* AP: 00 */
#define MMU_STATE_SUP_RO_USR_RO     0x000000C0      /* AP: 11 */
#define MMU_STATE_SUP_RW_USR_RO     0x00000040      /* AP: 01, not support, */
                                                    /* here we set same as RW */
#define MMU_STATE_SUP_RW_USR_RW     0x00000040      /* AP: 01 */

/* XN not support */

#define MMU_STATE_SUP_RO_XN         MMU_STATE_SUP_RO
#define MMU_STATE_SUP_RW_XN         MMU_STATE_SUP_RW
#define MMU_STATE_SUP_RO_USR_RO_XN  MMU_STATE_SUP_RO_USR_RO
#define MMU_STATE_SUP_RW_USR_RO_XN  MMU_STATE_SUP_RW_USR_RO
#define MMU_STATE_SUP_RW_USR_RW_XN  MMU_STATE_SUP_RW_USR_RW

#define MMU_STATE_WRITABLE          MMU_STATE_SUP_RW

#define MMU_STATE_WRITABLE_NOT      MMU_STATE_SUP_RO

#define MMU_STATE_AP_SUP_RO         0x2      /* AP field: 10 */
#define MMU_STATE_AP_SUP_RW         0x0      /* AP field: 00 */
#define MMU_STATE_AP_SUP_RO_USR_RO  0x3      /* AP field: 11 */
#define MMU_STATE_AP_SUP_RW_USR_RO  0x1      /* AP field: 01, arm not support */
#define MMU_STATE_AP_SUP_RW_USR_RW  0x1      /* AP field: 01 */

#define MMU_STATE_AP_USR_RO_SUP_RO  MMU_STATE_AP_SUP_RO_USR_RO
#define MMU_STATE_AP_USR_RO_SUP_RW  MMU_STATE_AP_SUP_RW_USR_RO
#define MMU_STATE_AP_USR_RW_SUP_RW  MMU_STATE_AP_SUP_RW_USR_RW

/* 
 * Memory Region Attributes -
 * cache access, write buffer access, coherency control
 */

/*
 * Memory Region Attributes - for LPAE
 *
 *  n = AttrIndex[2:0]
 *
 *  n	MAIR
 *  000	00000000        Strongly-ordered
 *  001	01000100        Normal memory, Inner & Outer Non-cacheable
 *  010	10101010        Normal memory, Write-Through, Read-Allocate
 *  011	11101110        Normal memory, Write-Back, Read-Allocate
 *  100	00000100        Device memory
 */

#define MMU_MAIR0_VALUE	    0xEEAA4400
#define MMU_MAIR1_VALUE	    0x00000004

#define MMU_STATE_AI_STRONGLY_ORDERED  0x0  /* n = 0b000, strongly ordered */
#define MMU_STATE_STRONGLY_ORDERED  ((MMU_STATE_AI_STRONGLY_ORDERED << 2) | \
                                     MMU_STATE_SHARED_OUTER)
#define MMU_STATE_CACHEABLE_NOT  MMU_STATE_STRONGLY_ORDERED

#define MMU_STATE_AI_DEVICE  0x4  /* n = 0b100 */
#define MMU_STATE_DEVICE_SHARED  ((MMU_STATE_AI_DEVICE << 2) | \
                                  MMU_STATE_SHARED_OUTER)

/* device always shared in LPAE */

#define MMU_STATE_DEVICE_NONSHARED MMU_STATE_DEVICE_SHARED

/* outer & inner write-thru cachable, write alloc */

#define MMU_STATE_AI_NORMAL_WRITETHROUGH  0x2  /* n = 0b010, Write-Through */
#define MMU_STATE_NORMAL_WRITETHROUGH   (MMU_STATE_AI_NORMAL_WRITETHROUGH << 2)
#define MMU_STATE_CACHEABLE_WRITETHROUGH  MMU_STATE_NORMAL_WRITETHROUGH

/* outer & inner write-back cachable, write alloc */

#define MMU_STATE_AI_NORMAL_WRITEBACK  0x3  /* n = 0b011, Write-Back */
#define MMU_STATE_NORMAL_WRITEBACK  (MMU_STATE_AI_NORMAL_WRITEBACK << 2)
#define MMU_STATE_CACHEABLE_COPYBACK  MMU_STATE_NORMAL_WRITEBACK
#define MMU_STATE_COPYBACK_ALLOC  MMU_STATE_NORMAL_WRITEBACK

/* outer & inner Non-cachable */

#define MMU_STATE_AI_NORMAL_NONCACHEABLE  0x1  /* n = 0b001, Non-cacheable */
#define MMU_STATE_NORMAL_NONCACHEABLE  (MMU_STATE_AI_NORMAL_NONCACHEABLE << 2)

/*
 * Set the default state to be copyback.
 */

#define MMU_STATE_CACHEABLE         MMU_STATE_CACHEABLE_COPYBACK

/* 
 * Shared memory attribute -
 * accessible by multiple processors or bus masters and must be kept coherent
 */

#define MMU_STATE_SHARED_OUTER            (0x2 << 8)     /* Outer Shareable */
#define MMU_STATE_SHARED_INNER            (0x3 << 8)     /* Inner Shareable */

#define MMU_STATE_SHARED  MMU_STATE_SHARED_INNER

#define MMU_STATE_WRITETHROUGH_SHARED  \
                          (MMU_STATE_CACHEABLE_WRITETHROUGH | MMU_STATE_SHARED)
#define MMU_STATE_COPYBACK_SHARED  \
                          (MMU_STATE_CACHEABLE_COPYBACK | MMU_STATE_SHARED)

/*
 * A memory region with a resultant memory type attribute of Normal, and a
 * resultant cacheability attribute of Inner Non-cacheable, Outer Non-cacheable,
 * must have a resultant shareability attribute of Outer Shareable, otherwise
 * shareability is UNPREDICTABLE.
 */
                           
#define MMU_STATE_NONCACHEABLE_SHARED  \
                          (MMU_STATE_NORMAL_NONCACHEABLE | \
                           MMU_STATE_SHARED_OUTER)

/* 
 * Global memory attribute -
 * not-Global causes ASID to be associated with address translation
 */

#define MMU_STATE_NOT_GLOBAL        0x00000800      /* not-Global, bit[11] */

/* 
 * Architecture-specific attributes
 *
 * The following ARMv7-specific aliases are provided for ease of use.
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

/* Normal, Noncacheable memory */

#define MMU_ATTR_NORMAL_NONCACHEABLE_MSK (MMU_ATTR_CACHE_MSK)
#define MMU_ATTR_NORMAL_NONCACHEABLE     (MMU_ATTR_CACHE_OFF)
#define MMU_ATTR_NORMAL_NONCACHEABLE_SHARED (MMU_ATTR_NORMAL_NONCACHEABLE | \
				             MMU_ATTR_CACHE_COHERENCY)

/* Normal, Inner Cache Write-Back, Write Allocate */

#define MMU_ATTR_WRITEALLOCATE_MSK    MMU_ATTR_CACHE_MSK
#define MMU_ATTR_WRITEALLOCATE        MMU_ATTR_CACHE_COPYBACK
#define MMU_ATTR_WRITEALLOCATE_SHARED (MMU_ATTR_WRITEALLOCATE | \
				       MMU_ATTR_CACHE_COHERENCY)

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
#define MMUCR_HA_ENABLE    (1<<17) /* Hardware Access flag enable */
#define MMUCR_ENABLE_ITCM    (1<<18) /* Enable Instruction TCM */
#define MMUCR_UNALIGNED_ENABLE (1<<22) /* Enable unaligned access */
#define MMUCR_EXTENDED_PAGE (1<<23)  /* Use extended PTE format */
#define MMUCR_VECTORED_INTERRUPT (1<<24) /* Enable VIC Interface */
#define MMUCR_EE                 (1<<25) /* Exception Endianness bit */
#define MMUCR_THUMB_EXCEPTIONS (1<<30) /* Exceptions are Thumb */

/* MMU TTBR 64 bit register fields for LPAE */

#define MMU_TTBR64_BA_MASK      MAKE_MASK_64(39, 12)
#define MMU_TTBR64_ASID_SHIFT   48

/* MMU TTBCR register fields for LPAE */

#define MMU_TTBCR_IRGN_NC	(0 << 8)
#define MMU_TTBCR_IRGN_WBWA	(1 << 8)
#define MMU_TTBCR_IRGN_WT	(2 << 8)
#define MMU_TTBCR_IRGN_WB	(3 << 8)
#define MMU_TTBCR_ORGN_NC	(0 << 10)
#define MMU_TTBCR_ORGN_OC_WBWA	(1 << 10)
#define MMU_TTBCR_ORGN_OC_WT	(2 << 10)
#define MMU_TTBCR_ORGN_OC_WB	(3 << 10)
#define MMU_TTBCR_S		(3 << 12)
#define MMU_TTBCR_S_OUTER	(2 << 12)
#define MMU_TTBCR_EAE		(1 << 31)

#ifdef _WRS_CONFIG_ENABLE_CACHED_PAGE_TBL
/* PTWs cacheable, inner WBWA not shareable, outer WBWA not shareable */

#define MMU_TTBCR_FLAGS_UP	(MMU_TTBCR_IRGN_WBWA | MMU_TTBCR_ORGN_OC_WBWA)

/* PTWs cacheable, inner WBWA shareable, outer WBWA not shareable */

#define MMU_TTBCR_FLAGS_SMP	(MMU_TTBCR_IRGN_WBWA | MMU_TTBCR_S | \
                                 MMU_TTBCR_ORGN_OC_WBWA)
#else /* !_WRS_CONFIG_ENABLE_CACHED_PAGE_TBL */
/* PTWs not cacheable, inner not shareable, outer not shareable */

#define MMU_TTBCR_FLAGS_UP	(MMU_TTBCR_IRGN_NC | MMU_TTBCR_ORGN_NC)

/* PTWs not cacheable, inner shareable, outer not shareable */

#define MMU_TTBCR_FLAGS_SMP	(MMU_TTBCR_ORGN_NC | MMU_TTBCR_S | \
                                 MMU_TTBCR_ORGN_NC)
#endif /* _WRS_CONFIG_ENABLE_CACHED_PAGE_TBL */

/* typedefs */

#ifndef _ASMLANGUAGE

#if (_BYTE_ORDER == _LITTLE_ENDIAN)

/* little-endian */

/* Level 1/2 page descriptors */

typedef struct
    {
    UINT type   : 2;          /* descriptor type, 0b11 => page table */
    UINT pad1   : 10;         /* Ignored */
    UINT addr   : 20;         /* base address of page table */
    UINT addr40 : 8;          /* base address of page table */
    UINT pad2   : 12;         /* UNK/SBZP */
    UINT pad3   : 7;          /* Ignored */
    UINT pxn    : 1;          /* PXNTable */
    UINT xn     : 1;          /* XNTable */
    UINT ap     : 2;          /* APTable */
    UINT ns     : 1;          /* NSTable */
    } PAGE_DESC_FIELD;

/* Layout of Page Table Entries (PTEs) */

typedef struct
    {
    UINT type   : 2;          /* page type, 0b11 => page */
    UINT ai     : 3;          /* AttrIndx[2:0] */
    UINT ns     : 1;          /* non-secure bit */
    UINT ap     : 2;          /* AP[2:1], access permission */
    UINT sh     : 2;          /* SH[1:0], shareability field */
    UINT af     : 1;          /* access flag */
    UINT ng     : 1;          /* not global bit */
    UINT addr   : 20;         /* phys address */
    UINT addr40 : 8;          /* phys address */
    UINT pad1   : 12;         /* UNK/SBZP */
    UINT ch     : 1;          /* contiguous hint */
    UINT pxn    : 1;          /* privileged execute-never bit */
    UINT xn     : 1;          /* execute-never bit */
    UINT pad2   : 9;          /* ignored */
    } PTE_FIELD;

#else /* (_BYTE_ORDER == _LITTLE_ENDIAN) */

/* big-endian */

#error "LPAE for big-endian not support yet."

#endif /* (_BYTE_ORDER == _LITTLE_ENDIAN) */

/* First/second level descriptor access */

typedef union
    {
    PAGE_DESC_FIELD         fields;
    UINT                    bits[2];
    UINT64                  bits64;
    } MMU_LEVEL_1_DESC, MMU_LEVEL_2_DESC;

/* Third level descriptor access */

typedef union
    {
    PTE_FIELD fields;
    UINT bits[2];
    UINT64 bits64;
    } PTE;

/*
 * Structure for MMU translation table access - normally used to get a pointer
 * to the first-level translation table.
 */

typedef struct mmuTransTblStruct
    {
    MMU_LEVEL_1_DESC *pLevel1Table;     /* active MMU table */
    VX_MUTEX_SEMAPHORE(mmuTransTblSem); /* MMU tables' semaphore */
    UINT32      lockCnt;                /* lock count */
    atomic_t    lockOwner;              /* lock owner */
    UINT8       asid;                   /* ASID/context id */
    } MMU_TRANS_TBL;

/* function declarations */

/* Externally visible mmuLib, mmuMapLib and mmuALib2 routines */

IMPORT UINT32 mmuReadId (void);
IMPORT PHYS_ADDR mmuVirtToPhys (VIRT_ADDR addr);
IMPORT VIRT_ADDR mmuPhysToVirt (PHYS_ADDR addr);

IMPORT UINT32   (* mmuCrGet) (void);
IMPORT void (* mmuModifyCr) (UINT32 value, UINT32 mask);
IMPORT UINT32   mmuHardCrGet (void);
IMPORT void mmuModifyHardCr (UINT32 value, UINT32 mask);

IMPORT UINT32   (* _func_mmuFaultAddrGet) (void);
IMPORT UINT32   (* _func_mmuFaultStatusGet) (void);
IMPORT UINT32   (* _func_mmuIFaultStatusGet) (void);
IMPORT UINT32   mmuIFsrGet (void);
IMPORT UINT32   mmuFarGet (void);
IMPORT UINT32   mmuFsrGet (void);

#endif  /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif  /* __INCmmuArmLpaeLibh */

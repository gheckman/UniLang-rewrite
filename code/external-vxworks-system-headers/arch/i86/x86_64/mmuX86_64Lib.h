/* mmuX86_64Lib.h - mmuX86_64Lib header for x86_64. */

/*
 * Copyright 2009-2010, 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01l,02may14,jb   VXW6-24753 - add Intel Write Combining Option
01k,23dec10,jlv  WIND00241261 - set default WP state for GuestOs
01j,24jun10,scm  WIND00217705 - check for correct physical address size...
01i,29apr10,pad  Moved extern C statement after include statements.
01h,22mar10,j_l  Modify MMU_CVT_VIRT_SYS to consider both direct mapped and
                 kernel system mapped regions
01g,03feb10,scm  update to exploit dllLib macros...
01f,19oct09,jb   Phase2 Update
01e,15oct09,jb   Fix mmuPteGet bug
01d,27aug09,jb   First phase of direct mapped design
01c,25aug09,jb   Add non-canonical address defs, remove Page0 Unmap
01b,03aug09,jb   Enable Page0 Unmap
01a,28may09,jb   written.
*/

#ifndef __INCmmuX86_64Libh
#define __INCmmuX86_64Libh

#include <dllLib.h>

#include <arch/i86/pentiumLib.h>
#include <arch/i86/x86_64/private/adrSpaceArchLibP.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MMU_CVT_VIRT_SYS(virtAddr)                                      \
    ((virtAddr & ~(KERNEL_DIRECT_MAP_RGN_BASE | (~KERNEL_SYS_MEM_RGN_BASE))) ? \
     ((VIRT_ADDR)(virtAddr & ~KERNEL_DIRECT_MAP_RGN_BASE) | KERNEL_DIRECT_MAP_RGN_BASE) : \
     ((VIRT_ADDR)(virtAddr & ~KERNEL_SYS_MEM_RGN_BASE) | KERNEL_SYS_MEM_RGN_BASE))
#define MMU_CVT_PHYS_SYS(physAddr) ((PHYS_ADDR)physAddr | KERNEL_SYS_MEM_RGN_BASE)
#define MMU_CVT_PHYS_DIR(physAddr) ((PHYS_ADDR)physAddr | KERNEL_DIRECT_MAP_RGN_BASE)

/*
 * Enable Temp optimized mmuTableZero
 */

#define MMU_OPTIMIZED_INIT                  /* Optimized table init */
#define MMU_ENABLE_INSTRUMENTATION          /* Table use instrumentation */

#define  MMU_OPTIMIZE_TABLE_ALLOC_ENABLE     /* Page Table allocation optimization */
#define MMU_ENABLE_PAGE_TABLE_OPTIMIZATION  /* Page Table size optimization (TLB) */

/*
 * Canonical address definitions
 */

#define CANONICAL_BITS          0xffff800000000000
#define NON_CANONICAL_PAGES     0xffff000000000
#define CANONICAL_UPPER         CANONICAL_BITS
#define ADDR_IS_CANONICAL(va)   ((((va) & CANONICAL_BITS) == 0) || \
                                         (((va) & CANONICAL_BITS) == CANONICAL_BITS))

/*
 * Private definitions for use in the avail
 * slots of PDE and PT records. bit 9 (0x1)
 * is reserved for NOBLOCK
 */

/*
 * TABLE_ALLOC_OPT indicates table was allocated
 * as part of a block alocation. Free at the top.
 */

#define TABLE_ALLOC_OPT         0x4             /* bit in Avail0 */
#define MMU_TABLE_ALLOC_OPT     0x800L          /* Absolute bit */

/*
 * Table size definitions
 */

#ifndef PAGE_SIZE_4KB
#define PAGE_SIZE_4KB		0x1000
#endif
#ifndef PAGE_SIZE_2MB
#define PAGE_SIZE_2MB		0x200000
#endif

#define PAGE_BLOCK_SIZE		0x200000        /* 2MB */
#define PAGES_PER_BLOCK         512

#define PDE_BLOCK_SIZE          0x40000000      /* 1GB */
#define PAGES_PER_PDE           262144

#define PDP_BLOCK_SIZE          0x8000000000    /* 512GB */
#define PAGES_PER_PDP           134217728

#define N_PML4                  512
#define N_PDPTE                 512
#define N_PDE                   512
#define N_PTE                   512

/*
 * Bits used to mask and shift virtual addresses
 * when calculating indices into the tables
 */

#define PML4_PTR_BITS           0x0000ff8000000000L
#define DIR_PTR_BITS		0x0000007fc0000000L
#define DIR_BITS		0x000000003fe00000L
#define TBL_BITS		0x00000000001ff000L

#define PML4_PTR_INDEX          39
#define DIR_PTR_INDEX		30
#define DIR_INDEX		21
#define TBL_INDEX		12

/* Mask for extracting addresses from PDEs */

#define OFFSET_BITS_4KB		0x0000000000000fffL
#define ASM_OFFSET_BITS_4KB	0x0000000000000fff
#define OFFSET_BITS_2MB		0x00000000001fffffL

#define PTE_TO_BITFIELD_4KB     0x0fffffff
#define PTE_TO_ADDR_4KB		0x000000fffffff000L
#define PTE_TO_BITFIELD_2MB     0x000fffff
#define PTE_TO_ADDR_2MB		0x000000ffffe00000L
#define PTP_TO_ADDR		0x000000fffffff000L
#define PDE_TO_ADDR		0x000000fffffff000L
#define PDP_TO_ADDR		0x000000fffffff000L
#define PML4_TO_ADDR            0x000000fffffff000L
#define ASM_PML4_TO_ADDR        0xfffffff000

/* Value used to indicate an unmapped page */

#define MMU_ENTRY_UNMAPPED      0x7ff000fffffff000

#define ADDR_TO_PAGE		12
#define ADDR_TO_PAGE_MASK       0xfffffff

#ifndef	_ASMLANGUAGE

/*
 * Page-Map-Level-4-Table Entry
 */

typedef struct
    {
    ULONG present:1;         /* Entry is valid */
    ULONG rw:1;              /* Read/Write when set, R/O when clear */
    ULONG us:1;              /* User/Supervisor, User when set,
                                Supervisor when clear */
    ULONG pwt:1;             /* Page-level write through, wt when set,
                                copy back when clear */
    ULONG pcd:1;             /* Page-level cache disable, disabled when set */
    ULONG access:1;          /* Page or Page Table has been accessed */
    ULONG rsvd0:3;           /* Reserved, must be zero */
    ULONG avail0:3;          /* Available to system programmers */
    ULONG page:28;           /* Bits 39 - 12, points to PDPTE or PDE if used
                                as PDPE_FIELD */
    ULONG rsvd1:12;          /* Reserved, must be zero */
    ULONG avail1:11;         /* Available to system programmers */
    ULONG exd:1;             /* Execute Disable Bit */
    } PML4_FIELD;

typedef union pml4
    {
    PML4_FIELD field;
    ULONG      bits;
    }PML4;

/*
 * Page-Directory-Pointer-Table Entry
 * Same at PLM4
 */

typedef PML4_FIELD PDPE_FIELD;

typedef union pdpt
    {
    PDPE_FIELD field;
    ULONG      bits;
    }PDPT;

/*
 * Page-Directory Entry 4k Page Table
 */

typedef struct
    {
    ULONG present:1;         /* Entry is valid */
    ULONG rw:1;              /* Read/Write when set, R/O when clear */
    ULONG us:1;              /* User/Supervisor, User when set,
                                Supervisor when clear */
    ULONG pwt:1;             /* Page-level write through, wt when set,
                                copy back when clear */
    ULONG pcd:1;             /* Page-level cache disable, disabled when set */
    ULONG access:1;          /* Page or Page Table has been accessed */
    ULONG mbz:3;             /* Must be zero, includes bit 7, page size as 0 */
    ULONG avail0:3;          /* Available to system programmers */
    ULONG page:28;           /* Bits 39 - 12, physical address of PTEs */
    ULONG rsvd1:12;          /* Reserved, must be zero */
    ULONG avail1:11;         /* Available to system programmers */
    ULONG exd:1;             /* Execute Disable Bit, disabled when set */
    } PDE4K_FIELD;

typedef union pde
    {
    PDE4K_FIELD field;
    ULONG       bits;
    }PDE4K;

/*
 * Page-Directory Entry 2m Page Table
 */

typedef struct
    {
    ULONG present:1;         /* Entry is valid */
    ULONG rw:1;              /* Read/Write when set, R/O when clear */
    ULONG us:1;              /* User/Supervisor, User when set,
                                Supervisor when clear */
    ULONG pwt:1;             /* Page-level write through, wt when set,
                                copy back when clear */
    ULONG pcd:1;             /* Page-level cache disable, disabled when set */
    ULONG access:1;          /* Page or Page Table has been accessed */
    ULONG dirty:1;           /* Page has been written */
    ULONG pagesize:1;        /* Page Size, 2mb when set, 4k ptr when clear */
    ULONG global:1;          /* Global bit, Global page when set */
    ULONG avail0:3;          /* Available to system programmers */
    ULONG pat:1;             /* Page attribute table index */
    ULONG rsvd1:8;           /* Reserved, must be zero */
    ULONG page:19;           /* Bits 39 - 21, physical address of 2m page */
    ULONG rsvd2:12;          /* Reserved, must be zero */
    ULONG avail1:11;         /* Available to system programmers */
    ULONG exd:1;             /* Execute Disable Bit, disabled when set */
    } PDE2M_FIELD;

typedef union pde2m
    {
    PDE2M_FIELD field;
    ULONG       bits;
    }PDE2M;

/*
 * NOTE: Generic Page-Directory Entry is same as 2MB entry.
 * This is for type determination.
 */

typedef PDE2M PDET;

/*
 * Page-Table Entry 4k Page
 */

typedef struct
    {
    ULONG present:1;         /* Entry is valid */
    ULONG rw:1;              /* Read/Write when set, R/O when clear */
    ULONG us:1;              /* User/Supervisor, User when set,
                                Supervisor when clear */
    ULONG pwt:1;             /* Page-level write through, wt when set,
                                copy back when clear */
    ULONG pcd:1;             /* Page-level cache disable, disabled when set */
    ULONG access:1;          /* Page or Page Table has been accessed */
    ULONG dirty:1;           /* Page has been written */
    ULONG pat:1;             /* Page attribute table index */
    ULONG global:1;          /* Global bit, Global page when set */
    ULONG avail0:3;          /* Available to system programmers */
    ULONG page:28;           /* Bits 39 - 12, physical address of 4k page */
    ULONG rsvd1:12;          /* Reserved, must be zero */
    ULONG avail1:11;         /* Available to system programmers */
    ULONG exd:1;             /* Execute Disable Bit, disabled when set */
    } PTE_FIELD;

typedef union pte
    {
    PTE_FIELD field;
    ULONG     bits;
    } PTE;

/*
 * Page Table Allocation Info. Enables efficient
 * allocation/de-allocation of page table resources.
 */

typedef struct mmuPageAllocInfo
    {
    struct mmuPageAllocInfo * next;  /* Pointer to next alloc struct */
    VIRT_ADDR                 vAddr; /* Virtual Address of allocated buffer */
    size_t                    pages; /* Number of pages for this allocation */
    } PGALLOCINFO;

#ifdef MMU_ENABLE_PAGE_TABLE_OPTIMIZATION

/*
 * Each Page Table Backing Store has up to 64 pages
 */

typedef struct mmuPgTblStore
    {
    DL_NODE		   node;
    short                  flags;       /* Indicates type, 0 = auto, 1 = manual */
    short                  resvd;       /* reserved */
    short                  pgCnt;       /* Number of pages in this store */
    short                  freeCnt;     /* Free pages in this store */
    ULONG                  freeField;   /* Bit field  indicating free blocks */
    ULONG  *               storage;     /* The storage itself */
    } PGTBLSTORE;

/* Backing store defs */

#define MMU_BACKING_PAGE_PER_NODE       64
#define MMU_BACKING_L_PER_PAGE          512
#define MMU_BACKING_ALL_BITS            0xFFFFFFFFFFFFFFFFL
#define MMU_STORE_AUTO 0
#define MMU_STORE_MANUAL 1
#endif /* MMU_ENABLE_PAGE_TABLE_OPTIMIZATION */

typedef struct mmuTransTblStruct
    {
    PML4 *        pPml4;        /* pointer to PML4 ptr tbl */

    PGALLOCINFO * pAlloc;       /* Page resource alloc info */
    PGALLOCINFO * pAllocLast;   /* Quick access to last structure */
#ifdef MMU_ENABLE_INSTRUMENTATION
    ULONG         totAllocPages;
#endif /* MMU_ENABLE_INSTRUMENTATION */

#ifdef MMU_ENABLE_PAGE_TABLE_OPTIMIZATION
    DL_LIST	  pgTblStore;
#ifdef MMU_ENABLE_INSTRUMENTATION
    int           storeCnt;     /* Number of backing store nodes */
#endif /* MMU_ENABLE_INSTRUMENTATION */
#endif /* MMU_ENABLE_PAGE_TABLE_OPTIMIZATION */

#ifdef MMU_ENABLE_INSTRUMENTATION
    PGALLOCINFO * pMapped;      /* mmuPageMap calls */
    PGALLOCINFO * pMappedLast;
    int           mappedPages;
    int           pdptCnt;
    int           pdeCnt;
    int           ptCnt;
#ifdef MMU_OPTIMIZE_TABLE_ALLOC_ENABLE
    int           orphanCnt;
#endif /* MMU_OPTIMIZE_TABLE_ALLOC_ENABLE */
#ifdef MMU_ENABLE_PAGE_TABLE_OPTIMIZATION
    int           optCnt;
#endif /* MMU_ENABLE_PAGE_TABLE_OPTIMIZATION */
    int           stateChg;
#endif /* MMU_ENABLE_INSTRUMENTATION */
    } MMU_TRANS_TBL;

/*
 * For Write Combining setup
 */

typedef union mmuPatReg
    {
    UINT64 mmuFullPat;
    UINT32 mmuHalfPat[2];
    UCHAR  mmuCharPat[8];
    } MMU_PAT_REG;

#define IA32_PAT_MSR                    0x277
#define IA32_PAT_WC_IDX                 0x02
#define IA32_PAT_WC                     0x01

/*
 * Private MACRO to convert Physical addresses from tables to
 * Virtual addresses useable by the mmu code.
 * This relationship must exist for the current 64-bit mmu
 * library to work.
 */

#define MMU_CVT_PHYS_VIRT(physAddr) ((PHYS_ADDR)physAddr | mmuX86_64PToVC)

#define MMU_STATE_MASK_VALID            0x001
#define MMU_STATE_MASK_WRITABLE         0x002
#define MMU_STATE_MASK_USER             0x004
#define MMU_STATE_MASK_EXEC_DIS         0x8000000000000000L

#define MMU_STATE_MASK_PROTECTION       0x8000000000000006L

#define MMU_STATE_MASK_WRITETHROUGH     0x008
#define MMU_STATE_MASK_WBACK            0x008
#define MMU_STATE_MASK_CACHEABLE        0x018
#define MMU_STATE_MASK_WCOMBINE         MMU_STATE_MASK_CACHEABLE

#define MMU_STATE_MASK_GLOBAL           0x100

#define MMU_STATE_MASK_NO_BLOCK         0x200

#define MMU_STATE_MASK_STATE            0x800000000000031FL

#define MMU_STATE_VALID                 0x001
#define MMU_STATE_VALID_NOT             0x000
#define MMU_STATE_WRITABLE              0x002
#define MMU_STATE_WRITABLE_NOT          0x000
#define MMU_STATE_USER                  0x004
#define MMU_STATE_USER_NOT              0x000
#define MMU_STATE_EXEC_DIS              0x8000000000000000L
#define MMU_STATE_EXEC_DIS_NOT          0x0000000000000000L
#define MMU_STATE_WRITETHROUGH          0x008
#define MMU_STATE_WBACK                 0x000
#define MMU_STATE_WCOMBINE              0x010 /* This requires mod to default PAT Table */

#define MMU_STATE_COPYBACK              0x000
#define MMU_STATE_CACHEABLE_NOT         0x018
#define MMU_STATE_WBACK_NOT     MMU_STATE_CACHEABLE_NOT
#define MMU_STATE_WCOMBINE_NOT          0

#define MMU_STATE_CACHEABLE             0x000
#define MMU_STATE_GLOBAL                0x100
#define MMU_STATE_GLOBAL_NOT            0x000

#define MMU_STATE_NO_BLOCK              0x200
#define MMU_STATE_NO_BLOCK_NOT          0x000

#define MMU_STATE_INVALID               0xffffffffffffffffL

#ifndef _WRS_CONFIG_WRHV_GUEST

#define MMU_STATE_SUP_RO        (MMU_STATE_EXEC_DIS | MMU_STATE_USER_NOT | \
                                 MMU_STATE_WRITABLE_NOT)
#define MMU_STATE_SUP_ROX       (MMU_STATE_USER_NOT | MMU_STATE_WRITABLE_NOT)
#define MMU_STATE_USR_RO        (MMU_STATE_EXEC_DIS | MMU_STATE_USER     | \
                                 MMU_STATE_WRITABLE_NOT)
#define MMU_STATE_USR_ROX       (MMU_STATE_USER     | MMU_STATE_WRITABLE_NOT)
#define MMU_STATE_SUP_RW        (MMU_STATE_EXEC_DIS | MMU_STATE_USER_NOT | \
                                 MMU_STATE_WRITABLE)
#define MMU_STATE_SUP_RWX       (MMU_STATE_USER_NOT | MMU_STATE_WRITABLE)
#define MMU_STATE_USR_RW        (MMU_STATE_EXEC_DIS | MMU_STATE_USER     | \
                                 MMU_STATE_WRITABLE)
#define MMU_STATE_USR_RWX       (MMU_STATE_USER     | MMU_STATE_WRITABLE)

#else

#define MMU_STATE_SUP_RO        (MMU_STATE_USER_NOT | MMU_STATE_WRITABLE_NOT)
#define MMU_STATE_SUP_ROX       (MMU_STATE_USER_NOT | MMU_STATE_WRITABLE_NOT)
#define MMU_STATE_USR_RO        (MMU_STATE_USER     | MMU_STATE_WRITABLE_NOT)
#define MMU_STATE_USR_ROX       (MMU_STATE_USER     | MMU_STATE_WRITABLE_NOT)
#define MMU_STATE_SUP_RW        (MMU_STATE_USER_NOT | MMU_STATE_WRITABLE)
#define MMU_STATE_SUP_RWX       (MMU_STATE_USER_NOT | MMU_STATE_WRITABLE)
#define MMU_STATE_USR_RW        (MMU_STATE_USER     | MMU_STATE_WRITABLE)
#define MMU_STATE_USR_RWX       (MMU_STATE_USER     | MMU_STATE_WRITABLE)

#endif /* _WRS_CONFIG_WRHV_GUEST */

/* wpOff is used to temporarily override supervisor write-protection.
 * When using wpOff, interrupts should
 * be locked because this disables write-protection system wide!
 * Before unlocking interrupts, be sure to do a wpOn().
 */

#define wpOff()    vxCr0Set (vxCr0Get() & 0xfffeffff)
#define wpOn()     vxCr0Set (vxCr0Get() | 0x00010000)

/* function declarations */

#if defined(__STDC__) || defined(__cplusplus)

extern STATUS	mmuX86_64LibInit (int pageSize);
extern STATUS	mmuX86_64Enable (BOOL enable);

extern void	mmuX86_64On ();
extern void	mmuX86_64Off ();
extern void	mmuX86_64TLBFlush ();
extern void	mmuX86_64Pml4Set (MMU_TRANS_TBL *transTbl);
extern STATUS   mmuX86_64Show (MMU_TRANS_TBL *transTbl,
                               VIRT_ADDR vaddr, size_t numPages, int flag);

extern PML4 *   mmuX86_64Pml4Get ();

extern unsigned int mmuX86_64GetPhysAddrSize ();

#else   /* __STDC__ */

extern STATUS	mmuX86_64LibInit ();
extern STATUS	mmuX86_64Enable ();

extern void	mmuX86_64On ();
extern void	mmuX86_64Off ();
extern void	mmuX86_64TLBFlush ();
extern void	mmuX86_64Pml4Set ();
extern void     mmuX86_64Show ();

extern MMU_TRANS_TBL *mmuX86_64Pml4Get ();

extern unsigned int mmuX86_64GetPhysAddrSize ();

#endif  /* __STDC__ */

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCmmuX86_64Libh */

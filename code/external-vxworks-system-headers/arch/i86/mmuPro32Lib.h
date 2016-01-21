/* mmuPro32Lib.h - mmuPpro32Lib header for i86. */

/*
 * Copyright (c) 1984-2003,2009, 2011, 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/*
modification history
--------------------
01j,02may14,jb   VXW6-81787 - add Intel Write Combining Option
01i,19jan11,jb   Fix for WIND00185635 - mmu deoptimize locks do not work
01h,08sep09,rbc  WIND00177961 - vmStateSet() can no longer been called from an
                 ISR
01g,21apr09,rbc  Page Table Optimization.
01f,09dec03,zmm  Ported to Base6 from AE version of mmuPro32Lib.h 01f,30nov99
01e,12jun02,hdn  added arch specific VM library APIs' prototype
01d,23may02,hdn  replaced PAGE_SIZE with PD_SIZE and PT_SIZE
01c,22aug01,hdn  moved GDT and GDT_ENTRIES to regsI86.h
01b,13may98,hdn  added _ASMLANGUAGE macro.
01a,11apr97,hdn  written.
*/

#ifndef __INCmmuPro32Libh
#define __INCmmuPro32Libh

#ifdef __cplusplus
extern "C" {
#endif


#define PAGE_SIZE           0x1000
#define PAGE_BLOCK_SIZE	    0x400000
#define PAGE_SIZE_4KB	    0x1000
#define PAGE_SIZE_4MB	    0x400000
#define N_PTES              1024
#define N_PDES              1024

#define DIRECTORY_BITS	    0xffc00000
#define TABLE_BITS          0x003ff000
#define OFFSET_BITS_4KB	    0x00000fff
#define OFFSET_BITS_4MB	    0x003fffff
#define DIRECTORY_INDEX	    22
#define TABLE_INDEX         12
#define PTE_TO_ADDR_4KB	    0xfffff000
#define PTE_TO_ADDR_4MB	    0xffc00000
#define PTE_INVALID         PTE_TO_ADDR_4KB
#define PDE_INVALID         PTE_TO_ADDR_4MB

#define PAGES_PER_BLOCK     0x400
#define ADDR_TO_PAGE	    12
#define ADDR_TO_PAGEBASE    22

#ifndef	_ASMLANGUAGE

#define PAGE_TABLE_PRESENT  1
#define PAGE_TABLE_RW       1
#define PAGE_TABLE_US       1
#define PAGE_TABLE_PWT      1
#define PAGE_TABLE_PCD      1
#define PAGE_TABLE_ACCESS   1
#define PAGE_TABLE_DIRTY    1
#define PAGE_TABLE_4KB      0
#define PAGE_TABLE_4MB      1
#define PAGE_TABLE_GLOBAL   1

/* Define use of hardware available bits */

#define PAGE_TABLE_AVAIL_MASK 0x7
#define PAGE_TABLE_MASK_NO_BLOCK 0x1
#define PAGE_TABLE_NO_BLOCK 0x1

typedef struct
    {
    unsigned present:1;
    unsigned rw:1;
    unsigned us:1;
    unsigned pwt:1;
    unsigned pcd:1;
    unsigned access:1;
    unsigned dirty:1;
    unsigned pagesize:1;
    unsigned global:1;
    unsigned avail:3;
    unsigned page:20;
    } PTE_FIELD;

typedef union pte
    {
    PTE_FIELD field;
    unsigned int bits;
    } PTE;

typedef struct mmuTransTblStruct
    {
    PTE *pDirectoryTable;
    PTE *pAltDirectoryTable;
    VX_SEMAPHORE(mmuTransTblSem);
    } MMU_TRANS_TBL;

#if (_VX_CPU != _VX_PENTIUM)
typedef union mmuPatReg
    {
    UINT64 mmuFullPat;
    UINT32 mmuHalfPat[2];
    UCHAR  mmuCharPat[8];
    } MMU_PAT_REG;

#define IA32_PAT_MSR                    0x277
#define IA32_PAT_WC_IDX                 0x02
#define IA32_PAT_WC                     0x01
#endif /* (_VX_CPU != _VX_PENTIUM) */

#define MMU_STATE_MASK_VALID		0x001
#define MMU_STATE_MASK_WRITABLE		0x002
#define MMU_STATE_MASK_USER		0x004
#define MMU_STATE_MASK_PROTECTION       0x006

#define MMU_STATE_MASK_WRITETHROUGH     0x008
#define MMU_STATE_MASK_WBACK		0x008
#define MMU_STATE_MASK_CACHEABLE	0x018  /* 0x018 was 0x10 in AE version */

#define MMU_STATE_MASK_GLOBAL		0x100

#define MMU_STATE_MASK_NO_BLOCK		0x200
#define MMU_STATE_MASK_STATE            0x31f

#define MMU_STATE_VALID			0x001
#define MMU_STATE_VALID_NOT		0x000
#define MMU_STATE_WRITABLE		0x002
#define MMU_STATE_WRITABLE_NOT		0x000
#define MMU_STATE_USER                  0x004
#define MMU_STATE_USER_NOT              0x000
#define MMU_STATE_WRITETHROUGH		0x008
#define MMU_STATE_WBACK			0x000

#define MMU_STATE_COPYBACK		0x000
#define MMU_STATE_CACHEABLE_NOT		0x018  /* 0x18 was 0x10 in AE version */
#define MMU_STATE_WBACK_NOT	MMU_STATE_CACHEABLE_NOT

#if (_VX_CPU != _VX_PENTIUM)
#define MMU_STATE_MASK_WCOMBINE         MMU_STATE_MASK_CACHEABLE
#define MMU_STATE_WCOMBINE              0x010 /* This requires mod to default PAT Table */
#define MMU_STATE_WCOMBINE_NOT          0x000
#endif /* (_VX_CPU != _VX_PENTIUM) */

#define MMU_STATE_CACHEABLE		0x000
#define MMU_STATE_GLOBAL		0x100
#define MMU_STATE_GLOBAL_NOT    0x000

#define MMU_STATE_NO_BLOCK		0x200
#define MMU_STATE_NO_BLOCK_NOT  0x000

#define MMU_STATE_SUP_RO        (MMU_STATE_USER_NOT | MMU_STATE_WRITABLE_NOT) /* 0x0 */
#define MMU_STATE_USR_RO        (MMU_STATE_USER     | MMU_STATE_WRITABLE_NOT) /* 0x4 */
#define MMU_STATE_SUP_RW        (MMU_STATE_USER_NOT | MMU_STATE_WRITABLE)     /* 0x2 */
#define MMU_STATE_USR_RW        (MMU_STATE_USER     | MMU_STATE_WRITABLE)     /* 0x6 */

/* wpOff is used to temporarily override supervisor write-protection.
 * When using wpOff, interrupts should
 * be locked because this disables write-protection system wide!
 * Before unlocking interrupts, be sure to do a wpOn().
 */

#define wpOff()    vxCr0Set (vxCr0Get() & 0xfffeffff)
#define wpOn()     vxCr0Set (vxCr0Get() | 0x00010000)

/* function declarations */

#if defined(__STDC__) || defined(__cplusplus)

extern STATUS	mmuPro32LibInit (int pageSize);
extern STATUS	mmuPro32Enable (BOOL enable);
extern void	mmuPro32On ();
extern void	mmuPro32Off ();
extern void	mmuPro32TLBFlush ();
extern void	mmuPro32PdbrSet (MMU_TRANS_TBL *transTbl);
extern void	mmuPro32Show (MMU_TRANS_TBL *transTbl, void * vaddr);
extern MMU_TRANS_TBL *mmuPro32PdbrGet ();

#else   /* __STDC__ */

extern STATUS	mmuPro32LibInit ();
extern STATUS	mmuPro32Enable ();
extern void	mmuPro32On ();
extern void	mmuPro32Off ();
extern void	mmuPro32TLBFlush ();
extern void	mmuPro32PdbrSet ();
extern void	mmuPro32Show ();
extern MMU_TRANS_TBL *mmuPro32PdbrGet ();

#endif  /* __STDC__ */

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCmmuPro32Libh */

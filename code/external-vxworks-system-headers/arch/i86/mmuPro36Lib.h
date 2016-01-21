/* mmuPro36Lib.h - mmuPro36Lib header for i86. */

/* Copyright 1984-2002, 2010 Wind River Systems, Inc. */

/*
modification history
--------------------
01g,29apr10,pad  Moved extern C statement after include statements.
01f,07apr04,scm  Ported to Base6 ...
01e,12jun02,hdn  added arch specific VM library APIs' prototype
01d,06jun02,hdn  replaced PAGE_SIZE with PD_SIZE and PT_SIZE
01c,22aug01,hdn  moved GDT and GDT_ENTRIES to regsI86.h
01b,13may98,hdn  added _ASMLANGUAGE macro. 
01a,11apr97,hdn  written.
*/

#ifndef __INCmmuPro36Libh
#define __INCmmuPro36Libh

#include "arch/i86/pentiumLib.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PAGE_SIZE_4KB		0x1000
#define PAGE_SIZE_2MB		0x200000

#define PAGE_BLOCK_SIZE		0x200000

#define N_PTPTRS                4 
#define N_PTES                  512 
#define N_PDES                  512 

#define DIR_PTR_BITS		0xc0000000
#define DIR_BITS		0x3fe00000
#define TBL_BITS		0x001ff000

#define OFFSET_BITS_4KB		0x00000fff
#define OFFSET_BITS_2MB		0x001fffff

#define DIR_PTR_BITS		0xc0000000
#define DIR_BITS		0x3fe00000
#define TBL_BITS		0x001ff000

#define DIR_PTR_INDEX		30
#define DIR_INDEX		21
#define TBL_INDEX		12

#define PTE_TO_ADDR_4KB		0xfffff000
#define PTE_TO_ADDR_2MB		0xffe00000
#define PDP_TO_ADDR		0xfffff000

#define PTE_INVALID             PTE_TO_ADDR_4KB
#define PDE_INVALID             PTE_INVALID

#define ADDR_TO_PAGE		12
#define ADDR_TO_PAGEBASE	0xffe00000

#ifndef	_ASMLANGUAGE

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
    unsigned page36:4;
    unsigned reserved:28;
    } PTE_FIELD;

typedef union pte
    {
    PTE_FIELD field;
    UINT bits[2];
    } PTE;

typedef struct mmuTransTblStruct
    {
    PTE * pDirectoryPtrTable;	/* pointer to dir ptr tbl */
    INT32 pageSize;             /* 4K, 2M */
    } MMU_TRANS_TBL;

#define MMU_STATE_MASK_VALID            0x001
#define MMU_STATE_MASK_WRITABLE         0x002
#define MMU_STATE_MASK_USER             0x004
#define MMU_STATE_MASK_PROTECTION       0x006

#define MMU_STATE_MASK_WRITETHROUGH     0x008
#define MMU_STATE_MASK_WBACK            0x008
#define MMU_STATE_MASK_CACHEABLE        0x018  /* 0x018 was 0x10 in AE version */

#define MMU_STATE_MASK_GLOBAL           0x100
#define MMU_STATE_MASK_STATE            0x11f

#define MMU_STATE_VALID                 0x001
#define MMU_STATE_VALID_NOT             0x000
#define MMU_STATE_WRITABLE              0x002
#define MMU_STATE_WRITABLE_NOT          0x000
#define MMU_STATE_USER                  0x004
#define MMU_STATE_USER_NOT              0x000
#define MMU_STATE_WRITETHROUGH          0x008
#define MMU_STATE_WBACK                 0x000

#define MMU_STATE_COPYBACK              0x000
#define MMU_STATE_CACHEABLE_NOT         0x018  /* 0x18 was 0x10 in AE version */
#define MMU_STATE_WBACK_NOT     MMU_STATE_CACHEABLE_NOT         

#define MMU_STATE_CACHEABLE             0x000
#define MMU_STATE_GLOBAL                0x100
#define MMU_STATE_GLOBAL_NOT            0x000

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

extern STATUS	mmuPro36LibInit (int pageSize);
extern STATUS	mmuPro36Enable (BOOL enable);

extern void	mmuPro36On ();
extern void	mmuPro36Off ();
extern void	mmuPro36TLBFlush ();
extern void	mmuPro36PdbrSet (MMU_TRANS_TBL *transTbl);
extern void     mmuPro36Show (MMU_TRANS_TBL *transTbl, VIRT_ADDR vaddr);

extern MMU_TRANS_TBL *mmuPro36PdbrGet ();

#else   /* __STDC__ */

extern STATUS	mmuPro36LibInit ();
extern STATUS	mmuPro36Enable ();

extern void	mmuPro36On ();
extern void	mmuPro36Off ();
extern void	mmuPro36TLBFlush ();
extern void	mmuPro36PdbrSet ();
extern void     mmuPro36Show ();

extern MMU_TRANS_TBL *mmuPro36PdbrGet ();

#endif  /* __STDC__ */

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCmmuPro36Libh */

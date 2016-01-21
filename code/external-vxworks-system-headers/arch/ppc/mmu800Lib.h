/* mmuPpc800Lib.h - mmu library for PowerPc 800 series */

/* Copyright 1984-2005 Wind River Systems, Inc. */

/*
modification history
--------------------
01i,03feb05,mig  Code review changes.
01h,19jan05,mig  Cleanup
01g,05jan05,mig  Fix protection states
01f,22dec04,mig  Fix protection states
01e,24nov04,mig  Support AIM MMU in VxWorks 6.0 
01d,29nov04,dtr  Fix for AIM transition.
01c,13nov03,jtp  Support configAll.h change requiring MMU_PAGE_SIZE
                 definition.
01b,05feb97,tpr  removed reserved macro (SPR 7783).
01a,27apr96,tpr	 written.
*/

#ifndef __INCmmuPpc800Libh
#define __INCmmuPpc800Libh

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Number of TLB Entry registers, expressed both as a power of two
 * as well as an integer.
 */

#define N_TLB_ENTRIES_BITS			6
#define N_TLB_ENTRIES				(1 << N_TLB_ENTRIES_BITS)

#define MMU_I_ADDR_TRANS			0
#define MMU_D_ADDR_TRANS			1

#define MMU_INST				0x01
#define MMU_DATA				0x02

#define MMU_ASID_MIN				0
#define MMU_ASID_MAX				15

#define MMU_PAGE_SIZE_4K			0x00001000
#define MMU_PAGE_SIZE_16K			0x00004000
#define MMU_PAGE_SIZE_512K			0x00080000
#define MMU_PAGE_SIZE_8M			0x00800000
#define MMU_TLB_PAGE_SIZE_4K			0
#define MMU_TLB_PAGE_SIZE_16K			0
#define MMU_TLB_PAGE_SIZE_512K			1
#define MMU_TLB_PAGE_SIZE_8M			3

#define MMU_PAGE_SIZE				MMU_PAGE_SIZE_4K
#define MMU_PAGE_SIZE_8XX_MIN			MMU_PAGE_SIZE

#define MMU_STATE_VALID				0x00000001
#define MMU_STATE_VALID_NOT			0x00000000
#define MMU_STATE_WRITABLE			0x00000002
#define MMU_STATE_WRITABLE_NOT			0x00000000
#define MMU_STATE_CACHEABLE			0x00000000
#define MMU_STATE_CACHEABLE_NOT			0x00000004
#define MMU_STATE_CACHEABLE_WRITETHROUGH	0x00000008
#define MMU_STATE_CACHEABLE_COPYBACK		0x00000000
#define MMU_STATE_GUARDED			0x00000010
#define MMU_STATE_GUARDED_NOT			0x00000000

#define MMU_STATE_MASK_VALID			0x00000001
#define MMU_STATE_MASK_WRITABLE			0x00000002
#define MMU_STATE_MASK_CACHEABLE		0x0000000c
#define MMU_STATE_MASK_GUARDED			0x00000010
#define MMU_STATE_MASK_PROTECTION		0x00000700
#define MMU_STATE_MASK_WRITEABLE_NOT            0x00000400
#define MMU_RPN_SHIFT				0x0000000c
#define MMU_PROT_SHIFT				0x00000008
#define MMU_PP_MASK				0x00000003

#define MMU_STATE_SUP_RWX   			0x00000000
#define MMU_STATE_SUP_RWX_USR_RX		0x00000100
#define MMU_STATE_SUP_RWX_USR_RWX		0x00000200
#define MMU_STATE_SUP_RX_USR_RX			0x00000300
#define MMU_STATE_SUP_RX   			0x00000400

/*
 * Each context's MMU pages are mapped using a two-level page table
 * scheme. The level 1 table is called the REGION table and the level
 * 2 table is called a PAGE table.
 *
 * The most significant MMU_REGION_INDEX_BITS bits of the virtual
 * address are used as an index into the Region Table. Each entry is of
 * size 2 ^ MMU_REGION_ENTRY_BITS, typically a pointer to a PAGE table.
 */

#define MMU_REGION_INDEX_BITS	10	/* number of bits in index */
#define MMU_REGION_TBL_ENTRIES	(0x1 << MMU_REGION_INDEX_BITS)
					/* number of regions in table */
#define MMU_REGION_ENTRY_BITS	2	/* size in bytes as pwr of 2 */
#define MMU_REGION_INDEX_MASK	0xFFC00000
#define MMU_REGION_INDEX_SHIFT	22

/*
 * The next most significant MMU_PAGE_INDEX_BITS bits of the virtual
 * address are used as an index into the Page Table.
 */

#define MMU_PAGE_INDEX_BITS	10	/* number of bits in index */

/* max number of page table entries */

#define MMU_PAGE_TBL_ENTRIES 	(0x1 << MMU_PAGE_INDEX_BITS)

#ifndef _ASMLANGUAGE

/* Effective Address Definition */

typedef union effectiveAddr		/* effective Address structure */
    {
    struct
	{
	u_int l1index:10;		/* Level 1 Index */
	u_int l2index:10;		/* Level 2 Index */
	u_int po:12;			/* Page Offset */
	} field;
   
    void * effAddr;

    } EFFECTIVE_ADDR;

/* Real Address Definition */

typedef union	realAddress	/* Real Address Structure */
    {
    struct			/* Bit field description */
	{
	u_int rpn:20;		/* Real Page Number */
	u_int po:12;		/* Page Offset */
	}field;

    void * realAddr;		/* Real Address */

    } REAL_ADDRESS;	

/* Level 1 Descriptor Definition */

typedef union level_1_desc	/* Level 1 descriptor format */
    {
    struct			/* Bit field desciption */
	{
	u_int l2ba:20;		/* Level 2 table Base Address */
	u_int reserved:3;	/* Reserved */
	u_int apg:4;		/* Access Protection Group */
	u_int g:1;		/* Guarded storage attribute for entry */
	u_int ps:2;		/* Page Size level one */
	u_int wt:1;		/* Write Through attribute for entry */
	u_int v:1;		/* Segment Valid bit */
	} field;

    u_int l1desc;		/* Level 1 descriptor */

    } LEVEL_1_DESC;

/* Level 1 Table pointer definition */

typedef union	level_1_tbl_ptr	/* Level 1 Table pointer structure */
    {
    struct			/* Bit field description */
	{
	u_int l1tb:20;		/* Level 1 table Base */
	u_int l1index:10;	/* Level 1 table Index */
	u_int reserved:2;	/* Reserved */
	} field;		

    LEVEL_1_DESC * pL1Desc;	/* Level 1 descriptor table pointer */

    } LEVEL_1_TBL_PTR;

/* Level 2 descriptor definition */

typedef union level_2_desc	/* Level 2 descriptor format */
    {
    struct			/* Bit field desciption */
	{
	u_int rpn:20;		/* Real Page Number */
	u_int pp:2;		/* Page Protection */
	u_int ppe:1;		/* Page Protection encoding */
	u_int c:1;		/* Change bit */
	u_int spv:4;		/* Sub Page Valid  */
	u_int sps:1;		/* Small Page Size */
	u_int sh:1;		/* Shared Page */
	u_int ci:1;		/* Cache Inhibit */
	u_int v:1;		/* Page Valid bit */
	} field;

    u_int l2desc;		/* Level 2 descriptor */

    } LEVEL_2_DESC;

/* Level 2 Table pointer definition */

typedef union	level_2_tbl_ptr	/* Level 2 Table pointer structure */
    {
    struct			/* Bit field description */
	{
	u_int l2tb:20;		/* Level 2 Table Base */
	u_int l2index:10;	/* Level 2 table Index */
	u_int reserved:2;	/* Reserved */
	} field;		

    LEVEL_2_DESC * pL2Desc;	/* Level 2 descriptor table pointer */ 

    } LEVEL_2_TBL_PTR;

#define MMU8XX_PTE	LEVEL_2_DESC

#if defined(__STDC__) || defined(__cplusplus)

extern STATUS mmu800LibInit (int mmuType);

#else   /* __STDC__ */

extern STATUS mmu800LibInit ();

#endif  /* __STDC__ */

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCmmuPpc800Libh */

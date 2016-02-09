/* mmu405Lib.h - mmu library for PowerPc 405 series */

/* Copyright 1984-2003  Wind River Systems, Inc. */

/*
modification history
--------------------
01g,19may04,dtr  Add additional support for AIM.
01f,09dec03,jtp  Code inspection modifications
01e,01dec03,jtp  Identify range of valid ASIDs
01d,14nov03,jtp  Support variable minimum page size in miss handler & page
		 tables
01c,12nov03,jtp  Parameterize REGION and PAGE table size and offset;
                 move miss handler parameter support here.
01b,28oct03,jtp  Support Base 6 AIM MMU
01a,18jul00,sm	 written.
*/

/*
DESCRIPTION

This header contains the public interface to the PowerPC 405 Core Memory
Management Library. It also defines private (internal) structures and
macros used to manipulate the 405 MMU.

Theory: the vmBaseLib and vmLib provide an application programmer
interface to the memory management and protection features of the 405
MMU. With the help of the aimMmuLib and mmu405Lib layers, a data
structure is maintained which stores per-page attributes: validity,
protection, cacheability, and address translation. This data structure
represents each page as a page table entry (PTE).

The 405 MMU hardware maintains a cache of 64 Unified Translation
Lookaside Buffer (TLB) Entry registers.  When the processor accesses a
memory location and fails to find matching TLB entry, it calls an
interrupt handler to establish a mapping. That miss handler walks the
data structure and copies a PTE into a TLB Entry register.

This file provides data needed to coordinate the mmu405Lib layer with
the aimMmuLib and vmLib/vmBaseLib layers.

See also:
    VxWorks PowerPC Architecture Supplement, WindRiver
    IBM PowerPC 405GP User's Manual, IBM
    IBM PowerPC 405CR User's Manual, IBM
    IBM PowerPC Npe405H/L User's Manual, IBM

*/

#ifndef __INCmmuPpc405Libh
#define __INCmmuPpc405Libh

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

/*
 * Number of TLB Entry registers, expressed both as a power of two
 * as well as an integer.
 */

#define N_TLB_ENTRIES_BITS	6
#define N_TLB_ENTRIES		(1 << N_TLB_ENTRIES_BITS)

/*
 * MMU_I_ADDR_TRANS and MMU_D_ADDR_TRANS are used in the mmu405Lib /
 * mmuPpcALib & cacheALib call interface. They are not useful at the
 * application programming level.
 */

#define MMU_I_ADDR_TRANS	0
#define MMU_D_ADDR_TRANS	1

/*
 * MMU_INST and MMU_DATA are used at the usrMmuInit / mmu405Lib call
 * interface.  They are not useful at the application programming
 * level.
 */

#define MMU_INST		0x01
#define MMU_DATA		0x02

/*
 * MMU_STATE attributes cover, at a minumum, validity, cacheability, and
 * protection.  In PowerPC the attributes also include guarded (forbids
 * speculative access) and memory coherency tagging.
 *
 * The PowerPC 405GP does not support memory coherency, so setting this
 * bit is irrelevant. However, other versions of the 405 core may choose
 * to add support. The 405 hardware also supports U0 and E bits but the
 * 405 MMU library does not utilize them.
 *
 * Note: the GLOBAL bit is used for the miss handler and is not used by the
 * hardware.
 */

#define MMU_STATE_VALID				0x00000400
#define MMU_STATE_VALID_NOT			0x00000000
#define MMU_STATE_GLOBAL			0x00000800
#define MMU_STATE_GLOBAL_NOT			0x00000000
#define MMU_STATE_CACHEABLE			0x00000000
#define MMU_STATE_CACHEABLE_NOT			0x00000004
#define MMU_STATE_CACHEABLE_WRITETHROUGH	0x00000008
#define MMU_STATE_CACHEABLE_COPYBACK		0x00000000
#define MMU_STATE_MEM_COHERENCY			0x00000002
#define MMU_STATE_MEM_COHERENCY_NOT		0x00000000
#define MMU_STATE_GUARDED			0x00000001
#define MMU_STATE_GUARDED_NOT			0x00000000
#define MMU_STATE_ENDIAN_LITTLE			0x00001000
#define MMU_STATE_ISR_CALLABLE                  0x00080000

#define MMU_STATE_MASK_VALID			0x00000400
#define MMU_STATE_MASK_GLOBAL			0x00000800
#define MMU_STATE_MASK_CACHEABLE    		0x0000000c
#define MMU_STATE_MASK_MEM_COHERENCY   		0x00000002
#define MMU_STATE_MASK_GUARDED			0x00000001
#define MMU_STATE_MASK_PROTECTION		0x000003f0
#define MMU_STATE_MASK_ISR_CALLABLE             0x00080000

/*
 * Protection Bits
 *
 * Each TLB entry controls access to one page of memory. The
 * protection mode is controlled by 6 bits in the TLB word, split
 * into 3 fields. These fields are:
 *
 * EX	- Executable. 1 bit. if 1, page may be executable
 * WR	- Writable. 1 bit. if 1, page is writable
 * ZSEL - Zone Select. 4 bits. Indexes into the Zone Protection Regsiter
 *
 * The Zone Protection Register (ZPR) is a 32 bit register consisting of
 * 16 2-bit fields. It is indexed by a TLB entry's ZSEL field. The value
 * of each 2-bit field may be:
 *
 *   0 - access is Supervisor only, controlled by the EX and WR bits.
 *   1 - access is both Supervisor and User, controlled by the EX and WR
 *       bits.
 *   2 - acess is Supervisor RWX, and User controlled by the EX and WR
 *       bits.
 *   3 - access is Supervisor RWX, User RWX. The EX and WR bits are
 *	 ignored.
 *
 * The 405 MMU also allows any valid page to be read in supervisor mode.
 *
 * The VxWorks mmu405Lib implementation applies the above TLB entry
 * fields and the ZPR register to support page protection.
 *
 * The ZPR is initialized to have four valid zones, indexed by ZSEL
 * values 0, 1, 2, and 3, and containing values of 0, 1, 2, and 3.
 *
 * The Selected Zone Protection Register bitfields (looked up via the
 * TLB ZSEL field) in cooperation with the TLB EX and WR bits,
 * implement the following (and only the following) page protections:
 *
 *   EX WR ZPR SupUsr
 *    0  0  00 r-----
 *    0  1  00 rw----
 *    1  0  00 r-x---
 *    1  1  00 rwx---
 *    0  0  01 r--r--
 *    0  1  01 rw-rw-
 *    1  0  01 r-xr-x
 *    1  1  01 rwxrwx
 *    0  0  10 rwxr--
 *    0  1  10 rwxrw-
 *    1  0  10 rwxr-x
 *    1  1  10 rwxrwx
 *    -  -  11 rwxrwx
 *
 * Note that some page protection settings cannot be supported with the
 * 405 MMU, in general, the supervisor mode always has more access
 * rights than the user mode.
 *
 * These protection bits (EX, WR, ZSEL 0-3 mapping to ZPR fields 0-3)
 * are mapped directly into MMU_STATE_* macros, defined below:
 */

/* MMU_STATE_* protection mode sub-fields, mapping 1:1 with hardware */

#define _MMU_EX		0x00000200	/* executable, modified by ZSEL */
#define _MMU_WR		0x00000100	/* writable, modified by ZSEL */
#define _MMU_ZSEL_0	0x00000000	/* SUP (only) R + EX + WR */
#define _MMU_ZSEL_1	0x00000010	/* SUP & USR both R + EX + WR */
#define _MMU_ZSEL_2	0x00000020	/* SUP RWX. USR R + EX + WR */
#define _MMU_ZSEL_3	0x00000030	/* SUP RWX. USR RWX. */

#define _MMU_ZSEL_MASK	0x000000f0	/* mask for ZSEL field */

/* MMU_STATE_* protection modes macros */

#define    MMU_STATE_SUP_R	     (_MMU_ZSEL_0                    )
#define    MMU_STATE_SUP_RW	     (_MMU_ZSEL_0 | _MMU_WR          )
#define    MMU_STATE_SUP_RX	     (_MMU_ZSEL_0           | _MMU_EX)
#define    MMU_STATE_SUP_RWX	     (_MMU_ZSEL_0 | _MMU_WR | _MMU_EX)

#define    MMU_STATE_SUP_R_USR_R     (_MMU_ZSEL_1                    )
/* #define MMU_STATE_SUP_RW_USR_R    /@ mode not supported */
/* #define MMU_STATE_SUP_RX_USR_R    /@ mode not supported */
#define    MMU_STATE_SUP_RWX_USR_R   (_MMU_ZSEL_2                    )

/* #define MMU_STATE_SUP_R_USR_W     /@ mode not supported */
/* #define MMU_STATE_SUP_RW_USR_W    /@ mode not supported */
/* #define MMU_STATE_SUP_RX_USR_W    /@ mode not supported */
/* #define MMU_STATE_SUP_RWX_USR_W   /@ mode not supported */

/* #define MMU_STATE_SUP_R_USR_RW    /@ mode not supported */
#define    MMU_STATE_SUP_RW_USR_RW   (_MMU_ZSEL_1 | _MMU_WR          )
/* #define MMU_STATE_SUP_RX_USR_RW   /@ mode not supported */
#define    MMU_STATE_SUP_RWX_USR_RW  (_MMU_ZSEL_2 | _MMU_WR          )

/* #define MMU_STATE_SUP_R_USR_X     /@ mode not supported */
/* #define MMU_STATE_SUP_RW_USR_X    /@ mode not supported */
/* #define MMU_STATE_SUP_RX_USR_X    /@ mode not supported */
/* #define MMU_STATE_SUP_RWX_USR_X   /@ mode not supported */

/* #define MMU_STATE_SUP_R_USR_RX    /@ mode not supported */
/* #define MMU_STATE_SUP_RW_USR_RX   /@ mode not supported */
#define    MMU_STATE_SUP_RX_USR_RX   (_MMU_ZSEL_1           | _MMU_EX)
#define    MMU_STATE_SUP_RWX_USR_RX  (_MMU_ZSEL_2           | _MMU_EX)

/* #define MMU_STATE_SUP_R_USR_WX    /@ mode not supported */
/* #define MMU_STATE_SUP_RW_USR_WX   /@ mode not supported */
/* #define MMU_STATE_SUP_RX_USR_WX   /@ mode not supported */
/* #define MMU_STATE_SUP_RWX_USR_WX  /@ mode not supported */

/* #define MMU_STATE_SUP_R_USR_RWX   /@ mode not supported */
/* #define MMU_STATE_SUP_RW_USR_RWX  /@ mode not supported */
/* #define MMU_STATE_SUP_RX_USR_RWX  /@ mode not supported */
#define    MMU_STATE_SUP_RWX_USR_RWX (_MMU_ZSEL_3                    )

/* 
 * Initial value of the ZPR.
 *
 * The ZPR, in collusion with the EX and WR bits, is used to set
 * MMU page protection attributes.
 *
 *   - Zone 0 is SUP only, controlled by the EX and WR bits.
 *   - Zone 1 is SUP and USR, controlled by the EX and WR bits.
 *   - Zone 2 is SUP RWX, and USR controlled by the EX and WR bits.
 *   - Zone 3 is SUP RWX, USR RWX.
 *   - Zone 4..15 is SUP only, controlled by the EX and WR bits.
 */

#define MMU_ZPR_INIT_VAL \
    (0 << 30) | (1 << 28) | (2 << 26) | (3 << 24) | \
    (0 << 22) | (0 << 20) | (0 << 18) | (0 << 16) | \
    (0 << 14) | (0 << 12) | (0 << 10) | (0 <<  8) | \
    (0 <<  6) | (0 <<  4) | (0 <<  2) | (0 <<  0)

/*
 * MMU_RPN_SHIFT.  The 405 TLB entry contains Real Page Number (RPN) and
 * Effective Page Number (EPN) fields which store the physical and
 * virtual page bits.  These fields always begin at the most significant
 * bit of the TLB word they are stored in, and the number of significant
 * bits depends on the TLB Page Size field. The 405 MMU code only
 * supports page sizes that are a multiple of MMU_PAGE_SIZE_4XX_MIN
 * bytes. The bit offset to convert a Real or Effective Page Number
 * field into a page base address is MMU_RPN_SHIFT. It must also match
 * the size of the rpn and epn bitfields in the MMU405_PTE structure,
 * below.
 */

#define MMU_RPN_SHIFT		MMU_PAGE_BITS_MIN


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

/*
 * The next most significant bits of the virtual address are used as an
 * index into the Page Table.  Note that MMU_PAGE_INDEX_BITS_MAX
 * describes the maximum number of bits to be used as a index to look up
 * an entry in the page table.  Fewer bits may be used if the
 * mmu405PageSizeMin is set to a larger hardware-TLB-supported page
 * size.
 *
 * Each entry is of size 2 ^ MMU_PAGE_ENTRY_BITS, which is the size of
 * an MMU405_PTE.
 */

#define MMU_PAGE_INDEX_BITS_MAX	10	/* number of bits in index */
#define MMU_PAGE_TBL_ENTRIES_MAX (0x1 << MMU_PAGE_INDEX_BITS_MAX)
					/* max number of page table entries */
#define MMU_PAGE_ENTRY_BITS	3    /* MMU405_PTE size in bytes as pwr of 2 */

/*
 * The remaining bits are the "offset" portion of a virtual address. All
 * the most significant bits have been translated as part of the
 * virtual->real page number lookup.
 *
 * The page size is at least MMU_PAGE_SIZE_4XX_MIN, but may be larger if
 * mmu405PageSizeMin is set to a larger hardware-TLB-supported page
 * size.
 */

#define MMU_PAGE_BITS_MIN	(32 - (MMU_REGION_INDEX_BITS + \
				       MMU_PAGE_INDEX_BITS_MAX ))
#define MMU_PAGE_SIZE_4XX_MIN	(0x1 << MMU_PAGE_BITS_MIN)

/* Range of hardware context numbers (PID register & TLB TID field) */

#define MMU_ASID_MIN		1
#define MMU_ASID_MAX		255
#define MMU_ASID_GLOBAL		MMU_ASID_MIN

/* TLB Miss Handler information */

/* Support for miss handler */

#define TLB_V_BIT	25	/* valid bit is at bit 25 of word 0 */
#define TLB_GLOBAL_BIT	28	/* global page map bit is at bit 28 of word 0 */
#define TLB_LOCK_BIT	29	/* lock page map bit is at bit 29 of word 0 */
#define TLB_ISR_CALL_BIT  30	/* isr callable bit is at bit 30 of word 0 */
#define TLB_N_WORDS	2	/* two TLB words, hi (0) and lo (1) */

#define	TLB_MIN_SUPPORT		/* use TLB indexes from 0 to max */
#undef	CACHE_STATE_VAR		/* no mod to W, I bits in miss handler */
#define TID_SOURCE	PID	/* PID is source of TLB Entry TID field */
#define MMU405_NUM_LOCKED_ENTRIES  0x6

/* page sizes */

#define _MMU_TLB_SZ_1K		0x00000000	/* 1KB page size */
#define _MMU_TLB_SZ_4K		0x00000080	/* 4KB page size */
#define _MMU_TLB_SZ_16K		0x00000100	/* 16KB page size */
#define _MMU_TLB_SZ_64K		0x00000180	/* 64KB page size */
#define _MMU_TLB_SZ_256K	0x00000200	/* 256KB page size */
#define _MMU_TLB_SZ_1M		0x00000280	/* 1MB page size */
#define _MMU_TLB_SZ_4M		0x00000300	/* 4MB page size */
#define _MMU_TLB_SZ_16M		0x00000380	/* 16MB page size */
#define _MMU_TLB_SZ_MASK	0x00000380	/* mask for page size field */
#define _MMU_TLB_SZ_SHIFT	7		/* offset of page size field */

/******************************************************************************
*
* Page Table Entry descriptor definition 
*
* This PTE stores most of the fields needed to update a TLB entry. Note
* that we store only the 20 most significant bits of the EPN and RPN,
* since we support a minimum page size of 4K.
*
* TLB fields are from ch. 6. PPC405GP Embedded Processor User's Manual,
* Sixth Preliminary Edition (June 2000)
*
* TLB Word 0 (aka TLBHI):
*
*  0               8              16        21    24  26  28    31
* +---------------.---------------.-----------+---.-+-+-+-+-+-----+
* |                    EPN                    |SIZE |V|E|U|G|-----|
* |                                           |     | | |0|L|-----|
* +---------------'---------------'-----------+---'-+-+-+-+-+-----+
*
* EPN  - Effective (Virtual) address Page Number
* SIZE - Page Size - mmu405Lib maps pages of size MMU_PAGE_SIZE. Larger
*	 sized pages are set up in static TLB mappings in the BSP,
*        or may be automatically managed by the AIM MMU for optimized
*        mappings.
* V    - Valid page bit
* E,U0	- Unused by mmu405Lib and set to zero
* GL    - global bit, set to 1 in a page table entry to inform the TLB
*	  Miss handler that this page is global; i.e. mapped in all
*	  contexts, that is, a TID=0. This bit is set to 0 before
*	  writing to the hardware TLB Entry
*
* TLB Word 1 (aka TLBLO):
*
*  0               8              16        21    24      28    31
* +---------------.---------------.-----------+-+-+-------+-+-+-+-+
* |                    RPN                    |E|W| ZSEL  |W|I|M|G|
* |                                           |X|R|       | | | | |
* +---------------'---------------'-----------+-+-+-------+-+-+-+-+
*
* RPN   - Real (Physical) address Page Number
* EX    - EXecutable, unless altered by zone protection
* WR    - WRitable bit, unless altered by zone protection
* ZSEL	- Zone SELect - select protection zone bit pairs from ZPR register
* W    	- Write-Through
* I    	- Caching Inhibited
* M    	- Unused by mmu405Lib and 405 hardware, and set to zero
* G    	- Guarded (Avoid speculative access)
*
*/

#ifndef _ASMLANGUAGE

typedef union mmu405_pte	/* Page Table Entry format */
    {
    struct			/* Bit field desciption */
	{
	/* hi word */
	UINT32 epn:20;		/* effective page number */
	UINT32 rsvd1:2;		/* reserved */
	UINT32 size:3;		/* page size (min 4k) */
	UINT32 v:1;		/* valid bit */
	UINT32 e:1;		/* little endian bit */
	UINT32 u0:1;		/* user attribute */
	UINT32 global:1;	/* miss hdlr will map page in all contexts */
	UINT32 lock:1;
	UINT32 isr:1;
	UINT32 rsvd2:1;		/* reserved */

	/* lo word */
	UINT32 rpn:20;		/* real page number */
	UINT32 rsvd3:2;		/* reserved */
	UINT32 ex:1;		/* execute protection */
	UINT32 wr:1;		/* write protection */
	UINT32 zsel:4;		/* zone protection */
	UINT32 w:1;		/* write thru/back */
	UINT32 i:1;		/* cache inhibited */
	UINT32 m:1;		/* memory coherent */
	UINT32 g:1;		/* memory guarded  */

	} field;

    struct 
	{
	UINT32 word0;		/* hi word */
	UINT32 word1;		/* lo word */
	} words;

    } MMU405_PTE;



#if defined(__STDC__) || defined(__cplusplus)

extern STATUS mmu405LibInit (int mmuType, UINT minPageSize);

#else   /* __STDC__ */

extern STATUS mmu405LibInit ();

#endif  /* __STDC__ */

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCmmuPpc405Libh */












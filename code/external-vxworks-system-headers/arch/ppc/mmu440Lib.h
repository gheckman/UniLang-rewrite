/* mmu440Lib.h - mmu library for PowerPc 440 series */

/*
 * Copyright (c) 2001-2003, 2011, 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01n,04jan12,x_s  Correct PPC465 erroneous translation of MMU attributes. (WIND00318349)
01m,07jul11,syt  Add support for PPC465.
01l,09feb05,mdo  Documentation fix for apigen
01k,11nov04,dtr  Add user permission flags for static TLBs.
01j,19may04,dtr  Add support for ISR_CALLABLE state.
01i,09apr04,dtr  Add in MMU_LOCK mask and bit field in Pte.
01h,09dec03,jtp  Code inspection modifications
01g,01dec03,jtp  Identify range of valid ASIDs
01f,17nov03,jtp  Support variable minimum page size in miss handler & page
                 tables
01e,12nov03,jtp  Parameterize REGION and PAGE table size and offset;
                 move miss handler parameter support here.
01d,04nov03,jtp  Incorporate review feedback
01c,17oct03,sru  Updates for Base 6 AIM MMU
01b,06jan03,pch  Add support for 440x5 core (PPC440GX)
01a,17apr02,jtp	 written, based on mmu405Lib.h
*/

/*
DESCRIPTION

This header contains the public interface to the PowerPC 440 Core Memory
Management Library. It also defines private (internal) structures and
macros used to manipulate the 440 MMU.

Theory: the vmBaseLib and vmLib provide an application programmer
interface to the memory management and protection features of the 440
MMU. With the help of the aimMmuLib and mmu440Lib layers, a data
structure is maintained which stores per-page attributes: validity,
protection, cacheability, and address translation. This data structure
represents each page as a page table entry (PTE).

The 440 MMU hardware maintains a cache of 64 Unified Translation
Lookaside Buffer (TLB) Entry registers.  When the processor accesses a
memory location and fails to find matching TLB entry, it calls an
interrupt handler to establish a mapping. That miss handler walks the
data structure and copies a PTE into a TLB Entry register.

The 440 MMU cannot be disabled, but several TLB Entry registers are
reserved at boot time to establish a static memory mapping that supports
low-level interrupt, exception, and MMU page management activities. This
is configured in applications via the sysStaticTlbDesc[] memory array.
The remainder of the TLB Entry registers are available to the
vmLib/vmBaseLib mapping, established via sysPhysMemDesc[].

This file provides data needed to coordinate the mmu440Lib layer with
the aimMmuLib and vmLib/vmBaseLib layers, as well as definitions needed
to configure the sysStaticTlbDesc[] array.

See also:
    VxWorks PowerPC Architecture Supplement, WindRiver
    IBM PowerPC 440GP User's Manual, IBM
    IBM PowerPC 440GX User's Manual, IBM

*/

#ifndef __INCmmuPpc440Libh
#define __INCmmuPpc440Libh

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
 * MMU_I_ADDR_TRANS and MMU_D_ADDR_TRANS are used in the mmu440Lib /
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
 * MMU_STATE attributes cover, at a minimum, validity, cacheability, and
 * protection.  In PowerPC the attributes also include guarded (forbids
 * speculative access) and memory coherency tagging.
 *
 * The PowerPC 440 does not support memory coherency, so setting these
 * bits is irrelevant. The 440 hardware also supports U0, U1, U2, U3, and
 * E bits but the 440 MMU library does not utilize them.
 *
 * Note that all of the bits map 1-1 with actual bit offsets in TLB Word
 * 2, with the exception of VALIDity bits -- which in the actual
 * hardware is stored in TLB Word 0 at a different bit position (see
 * MMU_STATE_VALID_SHIFT below).  Also note the GLOBAL bit is used for
 * the miss handler and is not used by the hardware.
 */

#define MMU_STATE_VALID				0x00000040
#define MMU_STATE_VALID_NOT			0x00000000
#define MMU_STATE_GLOBAL			0x80000000
#define MMU_STATE_GLOBAL_NOT			0x00000000
#define MMU_STATE_LOCK				0x00800000
#define MMU_STATE_UNLOCK			0x00000000
#define MMU_STATE_CACHEABLE			0x00000000
#define MMU_STATE_CACHEABLE_NOT			0x00000400
#define MMU_STATE_CACHEABLE_WRITETHROUGH	0x00000800
#define MMU_STATE_CACHEABLE_COPYBACK		0x00000000
#define MMU_STATE_MEM_COHERENCY			0x00000200
#define MMU_STATE_MEM_COHERENCY_NOT		0x00000000
#define MMU_STATE_GUARDED			0x00000100
#define MMU_STATE_GUARDED_NOT			0x00000000
#define MMU_STATE_ENDIAN_LITTLE			0x00000080
#define MMU_STATE_ISR_CALLABLE                  0x00080000

#define MMU_STATE_MASK_VALID			0x00000040
#define MMU_STATE_MASK_GLOBAL    		0x80000000
#define MMU_STATE_MASK_CACHEABLE    		0x00000c00
#if (CPU == PPC465)
#define MMU_STATE_MASK_CACHEABLE_EXT		0x001f0000
#endif /* PPC465 */
#define MMU_STATE_MASK_GUARDED			0x00000100
#define MMU_STATE_MASK_MEM_COHERENCY		0x00000200
#define MMU_STATE_MASK_PROTECTION		0x0000003f
#define MMU_STATE_MASK_ISR_CALLABLE             0x00080000
/* Valid bit in mmu_state is in different bit position and in TLB Word 0 */

#define MMU_STATE_VALID_SHIFT			3


/*
 * Protection Bits
 *
 * Each TLB entry controls access to one page of memory. The protection
 * mode is controlled by 6 bits in the TLB word, one for each of Read,
 * Write, Execute for Supervisor and User.
 *
 * These protection bits are mapped directly into MMU_STATE_* macros,
 * defined below:
 */

/* MMU_STATE_* protection mode sub-fields, mapping 1:1 with hardware */

#define _MMU_UX			0x00000020
#define _MMU_UW			0x00000010
#define _MMU_UR			0x00000008
#define _MMU_SX			0x00000004
#define _MMU_SW			0x00000002
#define _MMU_SR			0x00000001

#define _MMU_URWX	 	   (_MMU_UR | _MMU_UW | _MMU_UX)

/* MMU_STATE_* protection modes macros */

#define MMU_STATE_SUP_R		   (_MMU_SR)
#define MMU_STATE_SUP_RW	   (_MMU_SR|_MMU_SW)
#define MMU_STATE_SUP_RX	   (_MMU_SR|        _MMU_SX)
#define MMU_STATE_SUP_RWX	   (_MMU_SR|_MMU_SW|_MMU_SX)

#define MMU_STATE_SUP_R_USR_R	   (MMU_STATE_SUP_R   | _MMU_UR)
#define MMU_STATE_SUP_RW_USR_R     (MMU_STATE_SUP_RW  | _MMU_UR)
#define MMU_STATE_SUP_RX_USR_R     (MMU_STATE_SUP_RX  | _MMU_UR)
#define MMU_STATE_SUP_RWX_USR_R    (MMU_STATE_SUP_RWX | _MMU_UR)

#define MMU_STATE_SUP_R_USR_W	   (MMU_STATE_SUP_R   | _MMU_UW)
#define MMU_STATE_SUP_RW_USR_W     (MMU_STATE_SUP_RW  | _MMU_UW)
#define MMU_STATE_SUP_RX_USR_W     (MMU_STATE_SUP_RX  | _MMU_UW)
#define MMU_STATE_SUP_RWX_USR_W    (MMU_STATE_SUP_RWX | _MMU_UW)

#define MMU_STATE_SUP_R_USR_RW	   (MMU_STATE_SUP_R   | _MMU_UR | _MMU_UW)
#define MMU_STATE_SUP_RW_USR_RW    (MMU_STATE_SUP_RW  | _MMU_UR | _MMU_UW)
#define MMU_STATE_SUP_RX_USR_RW    (MMU_STATE_SUP_RX  | _MMU_UR | _MMU_UW)
#define MMU_STATE_SUP_RWX_USR_RW   (MMU_STATE_SUP_RWX | _MMU_UR | _MMU_UW)

#define MMU_STATE_SUP_R_USR_X	   (MMU_STATE_SUP_R   | _MMU_UX)
#define MMU_STATE_SUP_RW_USR_X     (MMU_STATE_SUP_RW  | _MMU_UX)
#define MMU_STATE_SUP_RX_USR_X     (MMU_STATE_SUP_RX  | _MMU_UX)
#define MMU_STATE_SUP_RWX_USR_X    (MMU_STATE_SUP_RWX | _MMU_UX)

#define MMU_STATE_SUP_R_USR_RX	   (MMU_STATE_SUP_R   | _MMU_UR | _MMU_UX)
#define MMU_STATE_SUP_RW_USR_RX    (MMU_STATE_SUP_RW  | _MMU_UR | _MMU_UX)
#define MMU_STATE_SUP_RX_USR_RX    (MMU_STATE_SUP_RX  | _MMU_UR | _MMU_UX)
#define MMU_STATE_SUP_RWX_USR_RX   (MMU_STATE_SUP_RWX | _MMU_UR | _MMU_UX)

#define MMU_STATE_SUP_R_USR_WX	   (MMU_STATE_SUP_R   | _MMU_UW | _MMU_UX)
#define MMU_STATE_SUP_RW_USR_WX    (MMU_STATE_SUP_RW  | _MMU_UW | _MMU_UX)
#define MMU_STATE_SUP_RX_USR_WX    (MMU_STATE_SUP_RX  | _MMU_UW | _MMU_UX)
#define MMU_STATE_SUP_RWX_USR_WX   (MMU_STATE_SUP_RWX | _MMU_UW | _MMU_UX)

#define MMU_STATE_SUP_R_USR_RWX	   (MMU_STATE_SUP_R   | _MMU_URWX)
#define MMU_STATE_SUP_RW_USR_RWX   (MMU_STATE_SUP_RW  | _MMU_URWX)
#define MMU_STATE_SUP_RX_USR_RWX   (MMU_STATE_SUP_RX  | _MMU_URWX)
#define MMU_STATE_SUP_RWX_USR_RWX  (MMU_STATE_SUP_RWX | _MMU_URWX)


/*
 * MMU_RPN_SHIFT.  The 440 TLB entry contains Real Page Number (RPN) and
 * Effective Page Number (EPN) fields which store the physical and
 * virtual page bits.  These fields always begin at the most significant
 * bit of the TLB word they are stored in, and the number of significant
 * bits depends on the TLB Page Size field. The 440 MMU code only
 * supports page sizes that are a multiple of MMU_PAGE_SIZE_4XX_MIN
 * bytes. The bit offset to convert a Real or Effective Page Number
 * field into a page base address is MMU_RPN_SHIFT. It must also match
 * the size of the rpn and epn bitfields in the MMU440_PTE structure,
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
 * The next most significant MMU_PAGE_INDEX_BITS bits of the virtual
 * address are used as an index into the Page Table.
 *
 * The next most significant bits of the virtual address are used as an
 * index into the Page Table.  Note that MMU_PAGE_INDEX_BITS_MAX
 * describes the maximum number of bits to be used as a index to look up
 * an entry in the page table.  Fewer bits may be used if the
 * mmu440PageSizeMin is set to a larger hardware-TLB-supported page
 * size.
 *
 * Each entry is of size 2 ^ MMU_PAGE_ENTRY_BITS, which is the size of
 * an MMU440_PTE.
 */

#define MMU_PAGE_INDEX_BITS_MAX	10	/* number of bits in index */

/* max number of page table entries */

#define MMU_PAGE_TBL_ENTRIES_MAX (0x1 << MMU_PAGE_INDEX_BITS_MAX)

/* MMU440_PTE size in bytes as pwr of 2 */

#define MMU_PAGE_ENTRY_BITS	4    

#define MMU440_NO_BITS_PHYS_ADDR 36 /* VM layer needs to know size of 
				       physical address primarily for 
				       contextShow routines */

/* Must be at least one for Optimization */ 

#define MMU440_NUM_LOCKED_ENTRIES 0x6 

/* intLock max size for write */
#define MAX_PAGE_WRITE_BYTES 0x100
/*
 * The remaining bits are the "offset" portion of a virtual address. All
 * the most significant bits have been translated as part of the
 * virtual->real page number lookup.
 *
 * The page size is at least MMU_PAGE_SIZE_4XX_MIN, but may be larger if
 * mmu440PageSizeMin is set to a larger hardware-TLB-supported page
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

#define TLB_V_BIT	22	/* valid bit is at bit 22 of word 0 */
#define TLB_TS_BIT	23	/* TS bit is at bit 23 of word 0 */
#define TLB_SIZE_BIT	24	/* SIZE start bit is at bit 24 of word 0 */
#define TLB_ERPN_BIT	28	/* ERPN start bit is at bit 28 of word 0 */
#define TLB_GLOBAL_BIT	0	/* global page map bit is at bit 0 of word 2 */
#define TLB_LOCK_BIT	1	/* lock page map bit is at bit 1 of word 2 */
#define TLB_ISR_BIT	2	/* isr bit is at bit 2 of word 2 */
#if (CPU == PPC465)
#define TLB_FAR_BIT	10	/* fixed address region is at bit 10 of word 2 */
#define TLB_WL1_BIT	11	/* L1 cache write through is at bit 11 of word 2 */
#define TLB_IL1I_BIT	12	/* L1 instruction cache inhibited is at bit 12 of word 2 */
#define TLB_IL1D_BIT	13	/* L1 data cache inhibited is at bit 13 of word 2 */
#define TLB_IL2I_BIT	14	/* L2 instruction cache inhibited is at bit 14 of word 2 */
#define TLB_IL2D_BIT	15	/* L2 data cache inhibited is at bit 15 of word 2 */
#endif /* PPC465 */
#define TLB_W_BIT	20	/* writethru bit is at bit 20 of word 2 */
#define TLB_I_BIT	21	/* cache inhibit bit is at bit 21 of word 2 */
#define TLB_M_BIT	22	/* memory coherence bit is at bit 22 of word 2 */
#define TLB_G_BIT	23	/* guarded bit is at bit 23 of word 2 */
#define TLB_E_BIT	24	/* endian bit is at bit 24 of word 2 */
#define TLB_UX_BIT	26	/* user state execute Enable bit is at bit 26 of word 2 */
#define TLB_UW_BIT	27	/* user state write Enable bit is at bit 27 of word 2 */
#define TLB_UR_BIT	28	/* user state read Enable bit is at bit 28 of word 2 */
#define TLB_SX_BIT	29	/* supervisor state Execute Enable bit is at bit 29 of word 2 */
#define TLB_SW_BIT	30	/* supervisor state Write Enable bit is at bit 30 of word 2 */
#define TLB_SR_BIT	31	/* supervisor state Read Enable bit is at bit 31 of word 2 */

#define MMUCR_STID_BIT0		0
#define MMUCR_STID_BIT7		7

#define TLB_N_WORDS	3	/* three TLB words, 0, 1, and 2 */

#define TLB_MIN_SUPPORT		/* use TLB indexes from mmuPpcTlbMin to max */
#define CACHE_STATE_VAR cache440Enabled        /* if TRUE cache is enabled */
#define TID_SOURCE	MMUCR	/* MMUCR is source of TLB Entry TID field */

#define MMUCR_STS_BIT		15	/* search translation space at bit 15 of MMUCR */
#define MMUCR_STID_MSB		24	/* STID starts at bit 24 of MMUCR */
#define MMUCR_STID_LSB		31	/* STID ends   at bit 31 of MMUCR */
#define MMUCR_STID_OFFSET	0	/* STID needs no offset to match PID */


/* TLB_ENTRY_DESC page attributes */

#define _MMU_TLB_TS_0		0x00000000	/* Translation Space 0 */
#define _MMU_TLB_TS_1		0x00010000	/* Translation Space 1 */
#define _MMU_TLB_V		0x00000200	/* Valid */

#define _MMU_TLB_SZ_1K		0x00000000	/* 1KB page size */
#define _MMU_TLB_SZ_4K		0x00000010	/* 4KB page size */
#define _MMU_TLB_SZ_16K		0x00000020	/* 16KB page size */
#define _MMU_TLB_SZ_64K		0x00000030	/* 64KB page size */
#define _MMU_TLB_SZ_256K	0x00000040	/* 256KB page size */
#define _MMU_TLB_SZ_1M		0x00000050	/* 1MB page size */
#define _MMU_TLB_SZ_16M		0x00000070	/* 16MB page size */
#define _MMU_TLB_SZ_256M	0x00000090	/* 256MB page size */
#define _MMU_TLB_SZ_1G		0x000000a0	/* 1GB page size, only PPC465 support */
#define _MMU_TLB_SZ_MASK	0x000000f0	/* mask for page size field */
#define _MMU_TLB_SZ_SHIFT	4		/* offset of page size field */

#define _MMU_TLB_ATTR_W		0x00000800	/* writethrough */
#define _MMU_TLB_ATTR_I		0x00000400	/* inhibit caching */
#define _MMU_TLB_ATTR_G		0x00000100	/* guarded */

#if (CPU == PPC465)
#define _MMU_TLB_ATTR_WL1	0x00100000	/* write through L1 cache */
#define _MMU_TLB_ATTR_IL1I	0x00080000	/* inhibited L1 instruction caching */
#define _MMU_TLB_ATTR_IL1D	0x00040000	/* inhibited L1 data caching */
#define _MMU_TLB_ATTR_IL2I	0x00020000	/* inhibited L2 instruction caching */
#define _MMU_TLB_ATTR_IL2D	0x00010000	/* inhibited L2 data caching */
#define _MMU_TLB_ATTR_M		0x00008000	/* memory coherence virtual bit */
#define _MMU_TLB_ATTR_PHY_M 0x00000200  /* memory coherence phsical bit */
#endif /* PPC465 */

#define _MMU_TLB_PERM_X		0x00000004	/* executable */
#define _MMU_TLB_PERM_W		0x00000002	/* writable */
#define _MMU_TLB_PERM_UR       	0x00001000	/* user read */
#define _MMU_TLB_PERM_UW       	0x00002000	/* user writable */
#define _MMU_TLB_PERM_UX       	0x00004000	/* user executable */

#ifndef	_ASMLANGUAGE

/*
*
* Page Table Entry descriptor definition
*
* The PTE stores most of the fields needed to update a TLB entry. Note
* that we store only the 20 most significant bits of the EPN and RPN (*),
* since we support a minimum page size of 4K.
*
*     (*) - the ERPN stores the Extended Real Page Number, which are
*	    the most significant 4 bits of the 36-bit physical address.
*           The RPN contains the most significant 20 bits of the lower
*           32 bits of the 36-bit physical address.
*
* The structure is padded to 16 bytes to simplify calculating the PTE
* offset in the miss handler; it also cache-aligns the loaded PTE which
* may simplify the hardware's access.
*
* TLB fields are from ch. 6. PPC440GP User's Manual, version 7, March
* 2002
*
* TLB Word 0:
*
*  0               8              16        21    24            31
* +---------------.---------------.-----------+-+-+-------+-------+
* |                    EPN                    |V|T| SIZE  |-------|
* |                                           | |S|       |-------|
* +---------------'---------------'-----------+-+-+-------+-------+
*
* EPN  - Effective (Virtual) address Page Number
* V    - Valid page bit
* TS   - Translation address Space - vmLib/vmBaseLib only manages
* 	 values of '1' -- that is, dynamic mmu page mapping only
*	 uses MSR[IS,DS] values of 1. TS values of zero are
*	 only set up in a static TLB mapping in the BSP.  TS values
*        of 1 may also be set up in static TLB mapping in the BSP,
*        or may be set up using the sysPhysMemDesc array.
* SIZE - Page Size - mmu440Lib maps pages of size MMU_PAGE_SIZE. Larger
*	 sized pages are set up in static TLB mappings in the BSP,
*        or may be automatically managed by the AIM MMU for optimized
*        mappings.
*
* TLB Word 1:
*
*  0               8              16        21    24            31
* +---------------.---------------.-----------+---.-------+-------+
* |                    RPN                    |-----------| ERPN  |
* |                                           |-----------|       |
* +---------------'---------------'-----------+---'-------+-------+
*
* RPN  - Real (Physical) address Page Number
* ERPN - Extended Real Page Number
*
* TLB Word 2:
*
*  0               8              16              24            31
* +-+-------------.---------------+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
* |G|             0               |U|U|U|U|W|I|M|G|E|-|U|U|U|S|S|S|
* |L|                             |0|1|2|3| | | | | |-|X|W|R|X|W|R|
* +-+-------------'---------------+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
*
* GL    - global bit, set to 1 in a page table entry to inform the TLB
*	  Miss handler that this page is global; i.e. mapped in all
*	  contexts, that is, a TID=0. This bit is set to 0 before
*	  writing to the hardware TLB Entry
* 0     - Field of zeroes
* WL1   - Write Through L1 (PPC465 only)
* IL1I  - Caching Inhibited L1 Instruction Cache (PPC465 only)
* IL1D  - Caching Inhibited L1 Data Cache (PPC465 only)
* IL2I  - Caching Inhibited L2 Instruction Cache (PPC465 only)
* IL2D  - Caching Inhibited L2 Data Cache (PPC465 only)
* U0-U3	- Unused by mmu440Lib and set to zero
* W    	- Write-Through
* I    	- Caching Inhibited
* M    	- Unused by mmu440Lib and 440 hardware, and set to zero
* G    	- Guarded (Avoid speculative access)
* E	- Unused by mmu440Lib and set to zero
* UX    - User eXecute
* UW    - User Write
* UR    - User Read
* SX    - Supervisor eXecute
* SW    - Supervisor Write
* SR    - Supervisor Read
*/

typedef union mmu440_pte	/* Page Table Entry format */
    {
    struct			/* Bit field description */
	{
	/* word 0 */
	UINT32 epn:20;		/* effective page number */
	UINT32 rsvd1:2;		/* reserved */
	UINT32 v:1;		/* valid bit */
	UINT32 ts:1;		/* translation space bit */
	UINT32 size:4;		/* page size */
	UINT32 rsvd2:4;		/* reserved */

	/* word 1 */
	UINT32 rpn:20;		/* real page number */
	UINT32 rsvd3:8;		/* reserved */
	UINT32 erpn:4;		/* extended real page number */

	/* word 2 */
	UINT32 global:1;	/* miss hdlr will map page in all contexts */
	UINT32 lock:1;          /* lock bit label indicating static TLB 
				   used */
	UINT32 isr:1;           /* isr bit set indicating no large page 
				   allowed */
#if (CPU == PPC465)
	UINT32 rsvd4:8;		/* reserved */
	UINT32 wl1:1;		/* write thru/back L1 */
	UINT32 il1i:1;		/* L1 i-cache inhibited */
	UINT32 il1d:1;		/* L1 d-cache inhibited */
	UINT32 il2i:1;		/* L2 i-cache inhibited */
	UINT32 il2d:1;		/* L2 d-cache inhibited */
#else /* !PPC465 */
	UINT32 rsvd4:13;	/* reserved */
#endif /* !PPC465 */
	UINT32 u0:1;		/* user attribute 0 */
	UINT32 u1:1;		/* user attribute 1 */
	UINT32 u2:1;		/* user attribute 2 */
	UINT32 u3:1;		/* user attribute 3 */
	UINT32 w:1;		/* write thru/back */
	UINT32 i:1;		/* cache inhibited */
	UINT32 m:1;		/* memory coherent */
	UINT32 g:1;		/* memory guarded  */
	UINT32 e:1;		/* little endian bit */
	UINT32 rsvd5:1;		/* reserved */
	UINT32 ux:1;		/* user execute protection */
	UINT32 uw:1;		/* user write protection */
	UINT32 ur:1;		/* user read protection */
	UINT32 sx:1;		/* supervisor execute protection */
	UINT32 sw:1;		/* supervisor write protection */
	UINT32 sr:1;		/* supervisor read protection */

	UINT32 rsvd6:32;	/* pad descriptor table to power of 2 */

	} field;

    struct 
	{
	UINT32 word0;		/* word 0 */
	UINT32 word1;		/* word 1 */
	UINT32 word2;		/* word 2 */
	UINT32 pad0;		/* pad word */
	} words;

    } MMU440_PTE;

/* Translation Table Definition */

/* TLB Entry description, used for mmu initialization */

typedef struct
    {
    UINT32	effAddr;	/* Effective address of base of page */
    UINT32	realAddrExt;	/*  4 MSB of 36-bit real address */
    UINT32	realAddr;	/* 32 LSB of 36-bit real address */
    UINT32	attr;		/* page attributes */
    } TLB_ENTRY_DESC;


#if defined(__STDC__) || defined(__cplusplus)

extern STATUS mmu440LibInit (int mmuType, int staticTlbNum,
			     TLB_ENTRY_DESC * pStaticTlbDesc, UINT minPageSize);

#else	/* __STDC__ */

extern STATUS mmu440LibInit ();

#endif	/* __STDC__ */

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCmmuPpc440Libh */

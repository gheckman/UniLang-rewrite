/* mmu476Lib.h - mmu library for PowerPc 476 series */

/*
 * Copyright (c) 2009-2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01k,22mar12,x_s  changed MMU_ASID_MAX to 1023. (WIND00340725)
01j,07mar12,h_k  removed _WRS_ARCH_REQUIRES_TLB_SYNC_CPC definition that is
                 left over by mistake. (WIND00320752)
01i,25feb11,x_s  added SMP support.
01h,10feb11,x_z  changed MMU_ASID_MIN to 0 to fix RTP issue.
01g,10feb11,x_z  added _MMU_TLB_DESC_ENTRY_SIZE.
01f,16dec10,x_z  fixed comment issues.
01e,14dec10,x_z  added MMUCR_STS_U.
01d,20oct10,x_z  fixed comment issues.
01c,15oct10,x_z  added support for Real Mode Page Description Register and fixed
                 some little issue.
01b,26may10,x_z  added TLB entry macros and fix TLB bit filed definitions.
01a,28dec09,x_s  created.
*/

/*
DESCRIPTION

This header contains the public interface to the PowerPC 476 Core Memory
Management Library. It also defines private (internal) structures and macros
used to manipulate the 476 MMU.

Theory: the vmBaseLib and vmLib provide an application programmer interface to
the memory management and protection features of the 476 MMU.  With the help of
the aimMmuLib and mmu476Lib layers, a data structure is maintained which stores
per-page attributes: validity, protection, cacheability, coherence and address
translation. This data structure represents each page as a page table entry
(PTE).

The 476 MMU hardware maintains a cache of 1024 Unified Translation Lookaside
Buffer (TLB) Entry registers.  When the processor accesses a memory location and
fails to find matching TLB entry, it calls an interrupt handler to establish a
mapping. That miss handler walks the data structure and copies a PTE into a TLB
Entry register.

The 476 MMU can be disabled to use real address mode, but it has no good
usability, so it is unused in mmu476Lib. the bolted TLB Entries are used at boot
time to establish a static memory mapping that supports low-level interrupt,
exception, and MMU page management activities. This is configured in
applications via the sysStaticTlbDesc[] memory array. The remainder of the TLB
Entry registers are available to the vmLib/vmBaseLib mapping, established via
sysPhysMemDesc[].

This file provides data needed to coordinate the mmu476Lib layer with the
aimMmuLib and vmLib/vmBaseLib layers, as well as definitions needed to configure
the sysStaticTlbDesc[] array.

SEE ALSO:
\tb "PowerPC 476FP Embedded Processor Core User's Manual"
*/

#ifndef __INCmmuPpc476Libh
#define __INCmmuPpc476Libh

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

/*
 * Number of TLB Entry registers, expressed both as a power of two
 * as well as an integer.
 */

#define N_TLB_ENTRIES_BITS  8
#define N_TLB_WAY_NUMBER    4
#define N_TLB_INDEX_NUMBER  (1 << N_TLB_ENTRIES_BITS)
#define N_TLB_ENTRIES       (N_TLB_INDEX_NUMBER * N_TLB_WAY_NUMBER)

/*
 * Tlb entry size is 1024 includes index size (256) and way size (4), convert
 * tlb entry to index and way.
 */

#define MMU_I_ADDR_TRANS    0
#define MMU_D_ADDR_TRANS    1

/*
 * MMU_INST and MMU_DATA are used at the usrMmuInit / mmu476Lib call
 * interface.  They are not useful at the application programming
 * level.
 */

#define MMU_INST            0x01
#define MMU_DATA            0x02

/*
 * MMU_STATE attributes cover, at a minimum, validity, cacheability, and
 * protection.  In PowerPC the attributes also include guarded (forbids
 * speculative access) and memory coherency tagging.
 *
 * The PPC476 hardware also supports U0, U1, U2, U3, and
 * E bits but the 476 MMU library does not utilize them.
 *
 * Note that all of the bits map 1-1 with actual bit offsets in TLB Word
 * 2, with the exception of VALIDity bits -- which in the actual
 * hardware is stored in TLB Word 0 at a different bit position (see
 * MMU_STATE_VALID_SHIFT below).  Also note the GLOBAL and LOCK bit are used for
 * the miss handler and is not used by the hardware.
 */

#define MMU_STATE_VALID                     0x00000040
#define MMU_STATE_VALID_NOT                 0x00000000
#define MMU_STATE_GLOBAL                    0x80000000
#define MMU_STATE_GLOBAL_NOT                0x00000000
#define MMU_STATE_LOCK                      0x00800000
#define MMU_STATE_UNLOCK                    0x00000000

#define MMU_STATE_CACHEABLE                 0x00000000
#define MMU_STATE_CACHEABLE_NOT             _MMU_TLB_ATTR_I

#define MMU_STATE_CACHEABLE_WRITETHROUGH    _MMU_TLB_ATTR_W
#define MMU_STATE_CACHEABLE_COPYBACK        0x00000000

#define MMU_STATE_MEM_COHERENCY             _MMU_TLB_ATTR_M
#define MMU_STATE_MEM_COHERENCY_NOT         0x00000000

#define MMU_STATE_GUARDED                   _MMU_TLB_ATTR_G
#define MMU_STATE_GUARDED_NOT               0x00000000

#define MMU_STATE_ENDIAN_LITTLE             _MMU_TLB_ATTR_E
#define MMU_STATE_ISR_CALLABLE              0x00080000

#define MMU_STATE_MASK_VALID                MMU_STATE_VALID
#define MMU_STATE_MASK_GLOBAL               MMU_STATE_GLOBAL
#define MMU_STATE_MASK_CACHEABLE            (MMU_STATE_CACHEABLE_NOT |  \
                                            MMU_STATE_CACHEABLE_WRITETHROUGH)
#define MMU_STATE_MASK_GUARDED              MMU_STATE_GUARDED
#define MMU_STATE_MASK_MEM_COHERENCY        MMU_STATE_MEM_COHERENCY
#define MMU_STATE_MASK_PROTECTION           0x0000003f
#define MMU_STATE_MASK_ISR_CALLABLE         MMU_STATE_ISR_CALLABLE

/* Valid bit in mmu_state is in different bit position and in TLB Word 0 */

#define MMU_STATE_VALID_SHIFT               3
#define MMU_PAGE_SIZE                       0x1000  /* pages are 4K bytes */

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

#define _MMU_UX                     _MMU_TLB_PERM_UX
#define _MMU_UW                     _MMU_TLB_PERM_UW
#define _MMU_UR                     _MMU_TLB_PERM_UR
#define _MMU_SX                     _MMU_TLB_PERM_X
#define _MMU_SW                     _MMU_TLB_PERM_W
#define _MMU_SR                     _MMU_TLB_PERM_R

#define _MMU_URWX                   (_MMU_UR | _MMU_UW | _MMU_UX)

/* MMU_STATE_* protection modes macros */

#define MMU_STATE_SUP_R             (_MMU_SR)
#define MMU_STATE_SUP_RW            (_MMU_SR | _MMU_SW)
#define MMU_STATE_SUP_RX            (_MMU_SR | _MMU_SX)
#define MMU_STATE_SUP_RWX           (_MMU_SR | _MMU_SW | _MMU_SX)

#define MMU_STATE_SUP_R_USR_R       (MMU_STATE_SUP_R   | _MMU_UR)
#define MMU_STATE_SUP_RW_USR_R      (MMU_STATE_SUP_RW  | _MMU_UR)
#define MMU_STATE_SUP_RX_USR_R      (MMU_STATE_SUP_RX  | _MMU_UR)
#define MMU_STATE_SUP_RWX_USR_R     (MMU_STATE_SUP_RWX | _MMU_UR)

#define MMU_STATE_SUP_R_USR_W       (MMU_STATE_SUP_R   | _MMU_UW)
#define MMU_STATE_SUP_RW_USR_W      (MMU_STATE_SUP_RW  | _MMU_UW)
#define MMU_STATE_SUP_RX_USR_W      (MMU_STATE_SUP_RX  | _MMU_UW)
#define MMU_STATE_SUP_RWX_USR_W     (MMU_STATE_SUP_RWX | _MMU_UW)

#define MMU_STATE_SUP_R_USR_RW      (MMU_STATE_SUP_R   | _MMU_UR | _MMU_UW)
#define MMU_STATE_SUP_RW_USR_RW     (MMU_STATE_SUP_RW  | _MMU_UR | _MMU_UW)
#define MMU_STATE_SUP_RX_USR_RW     (MMU_STATE_SUP_RX  | _MMU_UR | _MMU_UW)
#define MMU_STATE_SUP_RWX_USR_RW    (MMU_STATE_SUP_RWX | _MMU_UR | _MMU_UW)

#define MMU_STATE_SUP_R_USR_X       (MMU_STATE_SUP_R   | _MMU_UX)
#define MMU_STATE_SUP_RW_USR_X      (MMU_STATE_SUP_RW  | _MMU_UX)
#define MMU_STATE_SUP_RX_USR_X      (MMU_STATE_SUP_RX  | _MMU_UX)
#define MMU_STATE_SUP_RWX_USR_X     (MMU_STATE_SUP_RWX | _MMU_UX)

#define MMU_STATE_SUP_R_USR_RX      (MMU_STATE_SUP_R   | _MMU_UR | _MMU_UX)
#define MMU_STATE_SUP_RW_USR_RX     (MMU_STATE_SUP_RW  | _MMU_UR | _MMU_UX)
#define MMU_STATE_SUP_RX_USR_RX     (MMU_STATE_SUP_RX  | _MMU_UR | _MMU_UX)
#define MMU_STATE_SUP_RWX_USR_RX    (MMU_STATE_SUP_RWX | _MMU_UR | _MMU_UX)

#define MMU_STATE_SUP_R_USR_WX      (MMU_STATE_SUP_R   | _MMU_UW | _MMU_UX)
#define MMU_STATE_SUP_RW_USR_WX     (MMU_STATE_SUP_RW  | _MMU_UW | _MMU_UX)
#define MMU_STATE_SUP_RX_USR_WX     (MMU_STATE_SUP_RX  | _MMU_UW | _MMU_UX)
#define MMU_STATE_SUP_RWX_USR_WX    (MMU_STATE_SUP_RWX | _MMU_UW | _MMU_UX)

#define MMU_STATE_SUP_R_USR_RWX     (MMU_STATE_SUP_R   | _MMU_URWX)
#define MMU_STATE_SUP_RW_USR_RWX    (MMU_STATE_SUP_RW  | _MMU_URWX)
#define MMU_STATE_SUP_RX_USR_RWX    (MMU_STATE_SUP_RX  | _MMU_URWX)
#define MMU_STATE_SUP_RWX_USR_RWX   (MMU_STATE_SUP_RWX | _MMU_URWX)


/*
 * MMU_RPN_SHIFT.  The 476 TLB entry contains Real Page Number (RPN) and
 * Effective Page Number (EPN) fields which store the physical and
 * virtual page bits.  These fields always begin at the most significant
 * bit of the TLB word they are stored in, and the number of significant
 * bits depends on the TLB Page Size field. The 476 MMU code only
 * supports page sizes that are a multiple of MMU_PAGE_SIZE_4XX_MIN
 * bytes. The bit offset to convert a Real or Effective Page Number
 * field into a page base address is MMU_RPN_SHIFT. It must also match
 * the size of the rpn and epn bitfields in the MMU476_PTE structure,
 * below.
 */

#define MMU_RPN_SHIFT               MMU_PAGE_BITS_MIN

/*
 * Each context's MMU pages are mapped using a two-level page table
 * scheme. The level 1 table is called the REGION table and the level
 * 2 table is called a PAGE table.
 *
 * The most significant MMU_REGION_INDEX_BITS bits of the virtual
 * address are used as an index into the Region Table. Each entry is of
 * size 2 ^ MMU_REGION_ENTRY_BITS, typically a pointer to a PAGE table.
 */

#define MMU_REGION_INDEX_BITS       10  /* number of bits in index */

/* number of regions in table */

#define MMU_REGION_TBL_ENTRIES      (1 << MMU_REGION_INDEX_BITS)

/* size in bytes as pwr of 2 */

#define MMU_REGION_ENTRY_BITS       2

/*
 * The next most significant MMU_PAGE_INDEX_BITS bits of the virtual address are
 * used as an index into the Page Table.  Note that MMU_PAGE_INDEX_BITS_MAX
 * describes the maximum number of bits to be used as a index to look up
 * an entry in the page table.  Fewer bits may be used if the
 * mmu476PageSizeMin is set to a larger hardware-TLB-supported page
 * size.
 *
 * Each entry is of size 2 ^ MMU_PAGE_ENTRY_BITS, which is the size of
 * an MMU476_PTE.
 */

#define MMU_PAGE_INDEX_BITS_MAX     10  /* number of bits in index */

/* max number of page table entries */

#define MMU_PAGE_TBL_ENTRIES_MAX    (1 << MMU_PAGE_INDEX_BITS_MAX)

/* MMU476_PTE size in bytes as pwr of 2 */

#define MMU_PAGE_ENTRY_BITS         4

#define MMU476_NO_BITS_PHYS_ADDR    42  /* VM layer needs to know size of */
                                        /* physical address primarily for */
                                        /* contextShow routines */

/* Must be at least one for Optimization */

#define MMU476_NUM_LOCKED_ENTRIES   6

/* intLock max size for write */

#define MAX_PAGE_WRITE_BYTES        0x100

/*
 * The remaining bits are the "offset" portion of a virtual address. All
 * the most significant bits have been translated as part of the
 * virtual->real page number lookup.
 *
 * The page size is at least MMU_PAGE_SIZE_4XX_MIN, but may be larger if
 * mmu476PageSizeMin is set to a larger hardware-TLB-supported page
 * size.
 */

#define MMU_PAGE_BITS_MIN           (32 - (MMU_REGION_INDEX_BITS + \
                                    MMU_PAGE_INDEX_BITS_MAX ))
#define MMU_PAGE_SIZE_4XX_MIN       (1 << MMU_PAGE_BITS_MIN)

/* Range of hardware context numbers (PID register & TLB TID field) */

#define MMU_ASID_MIN                0

/*
 * Based on the user manual of PPC 476, ASID occupies 16 bits and the max value
 * should be 65535. While VxWorks does not support so many context for 32 bit 
 * architecture, only supports 1024 contexts at most. So here changes the max value 
 * of ASID to 1023.
 */

#define MMU_ASID_MAX                (1024 - 1)
#define MMU_ASID_GLOBAL             MMU_ASID_MIN

/* TLB Miss Handler information */

#define TLB_V_BIT                   20  /* valid bit is at bit 20 of word 0 */
#define TLB_GLOBAL_BIT              0   /* global page map bit is at bit 0 of */
                                        /* word 2 */
#define TLB_LOCK_BIT                1   /* lock page map bit is at bit 1 of */
                                        /* word 2 */
#define TLB_ISR_BIT                 2   /* isr bit is at bit 2 of word 2 */
#define TLB_LI_BIT                  14  /* Inhibit L1 instruction cache bit */
                                        /* is at bit 14 of  word 2 */
#define TLB_LD_BIT                  15  /* Inhibit L1 data cache bit is at */
                                        /* bit 15 of  word 2 */
#define TLB_W_BIT                   20  /* writethru bit is at bit 20 of */
                                        /* word 2 */
#define TLB_I_BIT                   21  /* cache inhibit bit is at bit 21 */
                                        /* of word 2 */
#define TLB_M_BIT                   22  /* memory coherent bit is at bit 22 */
                                        /* of word 2 */
#define TLB_G_BIT                   23  /* memory guarded bit is at bit 23 */
                                        /* of word 2 */
#define TLB_E_BIT                   24  /* little endian bit is at bit 24 */
                                        /* of word 2 */
#define TLB_N_WORDS                 3   /* three TLB words, 0, 1, and 2 */

#define CACHE_STATE_VAR             cache476Enabled /* Cache enabled flag */
#define TID_SOURCE                  MMUCR   /* obtain TLB Entry TID fromm */

/* use hardware assist mode for tlbwe */

#define TLB_INDEX_ADDR_HASH
#define MMUTLB_WRITE_RA_VALUE       0x00000000

/* TLB_ENTRY_DESC page attributes */

/* word 0 */

#define _MMU_TLB_DESC_ENTRY_SIZE    16  /* sizeof(TLB_ENTRY_DESC) */
#define _MMU_TLB_WORD0_SHIFT        16  /* avoid overlap with word2 */

#define _MMU_TLB_V                  0x00000800  /* Valid */

#define _MMU_TLB_TS_0               0x00000000  /* Translation Space 0 */
#define _MMU_TLB_TS_1               0x00000400  /* Translation Space 1 */

#define _MMU_TLB_SZ_4K              0x00000000  /* 4KB page size */
#define _MMU_TLB_SZ_16K             0x00000010  /* 16KB page size */
#define _MMU_TLB_SZ_64K             0x00000030  /* 64KB page size */
#define _MMU_TLB_SZ_1M              0x00000070  /* 1MB page size */
#define _MMU_TLB_SZ_16M             0x000000F0  /* 16MB page size */
#define _MMU_TLB_SZ_256M            0x000001F0  /* 256MB page size */
#define _MMU_TLB_SZ_1G              0x000003F0  /* 1GB page size */
#define _MMU_TLB_SZ_MASK            0x000003F0  /* mask for page size field */
#define _MMU_TLB_SZ_SHIFT           4

#define _MMU_TLB_BOLTED_R           0x00000008  /* bolted flag (tlbre only) */

#define _MMU_TLB_RPN_MASK           0xfffff000  /* Real Page Number */
#define _MMU_TLB_ERPN_MASK          0x000003ff  /* Extended Real Page Number */
#define _MMU_TLB_ERPN_BIT0          22

#define _MMU_TLB_ATTR_MASK          0x0003ffbf
#define _MMU_TLB_ATTR_IL1I          0x00020000  /* inhibit L1 instruction */
#define _MMU_TLB_ATTR_IL1D          0x00010000  /* inhibit L1 data */
#define _MMU_TLB_ATTR_W             0x00000800  /* writethrough */
#define _MMU_TLB_ATTR_I             0x00000400  /* inhibit caching */
#define _MMU_TLB_ATTR_M             0x00000200  /* memory coherent */
#define _MMU_TLB_ATTR_G             0x00000100  /* guarded */
#define _MMU_TLB_ATTR_E             0x00000080  /* Little Endian */

#define _MMU_TLB_PERM_UX            0x00000020  /* user executable */
#define _MMU_TLB_PERM_UW            0x00000010  /* user writable */
#define _MMU_TLB_PERM_UR            0x00000008  /* user read */
#define _MMU_TLB_PERM_X             0x00000004  /* executable */
#define _MMU_TLB_PERM_W             0x00000002  /* writable */
#define _MMU_TLB_PERM_R             0x00000001  /* read */

#define MMU_BOLTED_ENTRY_MAX_VALUE  6

/* for tlbwe */

#define MMUTLB_WRITE_RA_SWAY    0x80000000
#define MMUTLB_WRITE_RA_WAY0    0x00000000
#define MMUTLB_WRITE_RA_WAY1    0x20000000
#define MMUTLB_WRITE_RA_WAY2    0x40000000
#define MMUTLB_WRITE_RA_WAY3    0x60000000

#define MMUTLB_WRITE_RA_BOLT    0x08000000
#define MMUTLB_WRITE_RA_BOLT_0  0x00000000
#define MMUTLB_WRITE_RA_BOLT_1  0x01000000
#define MMUTLB_WRITE_RA_BOLT_2  0x02000000
#define MMUTLB_WRITE_RA_BOLT_3  0x03000000
#define MMUTLB_WRITE_RA_BOLT_4  0x04000000
#define MMUTLB_WRITE_RA_BOLT_5  0x05000000

#define MMUTLB_BOLT_FLAG        (MMUTLB_WRITE_RA_SWAY | MMUTLB_WRITE_RA_BOLT)
#define MMUTLB_BOLT_FLAG_SHIFT  24
#define MMUTLB_BOLT_FLAG_MSB    0x88
#define MMUTLB_BOLT_ENTRYn(n)   (MMUTLB_BOLT_FLAG | MMUTLB_WRITE_RA_BOLT_##n)

/* for tlbre */

#define MMUTLB_READ_RA_WAY_MASK     0x60000000
#define MMUTLB_READ_RA_WAY_SHIFT    29
#define MMUTLB_READ_RA_INDEX_MASK   0x00FF0000
#define MMUTLB_READ_RA_INDEX_SHIFT  16

/* MMUCR */

#define MMUCR_REALE_U               0x8000 /* Real mode enable */
#define MMUCR_REALE_BIT             0
#define MMUCR_STS_U                 0x0001 /* TS for tlbivax and tlbsx */
#define MMUCR_STS_BIT               15
#define MMUCR_STID_MSB              16  /* STID starts at bit 16 of MMUCR */
#define MMUCR_STID_LSB              31  /* STID ends   at bit 31 of MMUCR */
#define MMUCR_STID_OFFSET           0   /* STID needs no offset to match PID */

/* MMUBEn */

#define MMUBE0_IBE0_MASK        0xff000000
#define MMUBE0_IBE1_MASK        0x00ff0000
#define MMUBE0_IBE2_MASK        0x0000ff00
#define MMUBE0_IBE_MASK         0xffffff00

#define MMUBE0_VBE_0            0x00000004
#define MMUBE0_VBE_1            0x00000002
#define MMUBE0_VBE_2            0x00000001
#define MMUBE0_VBE_MASK         0x00000007

#define MMUBE1_IBE3_MASK        0xff000000
#define MMUBE1_IBE4_MASK        0x00ff0000
#define MMUBE1_IBE5_MASK        0x0000ff00
#define MMUBE1_IBE_MASK         0xffffff00

#define MMUBE1_VBE_3            0x00000004
#define MMUBE1_VBE_4            0x00000002
#define MMUBE1_VBE_5            0x00000001
#define MMUBE1_VBE_MASK         0x00000007

#define MMUBE_IBEn(x, n)       (((x) >> ((3 - n) * 8)) & 0xFF)

#define MMUBE_IBEn_WORDn(n)     ((n) >> 5)
#define MMUBE_IBEn_BITn(n)      ((n) & 31)

/* Real Mode Page Description Register */

#define RMPD_ERPN_MASK          0x3FF       /* Extended real page number */
#define RMPD_ERPN_SHIFT         20
#define RMPD_ATTR_W             0x00040000  /* Write through */
#define RMPD_ATTR_I             0x00020000  /* Cache inhibited */
#define RMPD_ATTR_M             0x00010000  /* Memory coherency required */
#define RMPD_ATTR_G             0x00008000  /* Guarded */
#define RMPD_ATTR_E             0x00004000  /* Endian */
#define RMPD_ATTR_IL1I          0x00002000  /* L1 instruction cache inhibit */
#define RMPD_ATTR_IL1D          0x00001000  /* L1 data cache inhibit */
#define RMPD_PERM_SX            0x00000200  /* Supervisor execute permission */
#define RMPD_PERM_SR            0x00000100  /* Supervisor read permission */
#define RMPD_PERM_SW            0x00000080  /* Supervisor write permission */
#define RMPD_PERM_UX            0x00000040  /* User execute permission */
#define RMPD_PERM_UR            0x00000020  /* User read permission */
#define RMPD_PERM_UW            0x00000010  /* User write permission */

#ifndef _ASMLANGUAGE

/*
*
* Page Table Entry descriptor definition
*
* The PTE stores most of the fields needed to update a TLB entry. Note
* that we store only the 20 most significant bits of the EPN and RPN (*),
* since we support a minimum page size of 4K.
*
*   (*) -   The ERPN stores the Extended Real Page Number, which are
*           the most significant 10 bits of the 42-bit physical address.
*           The RPN contains the most significant 20 bits of the lower
*           32 bits of the 42-bit physical address.
*
*   (*) -   The TID is stored in the tag of every UTLB entry. It can be
*           accessed only by MMUCR[STID].
*
* The structure is padded to 16 bytes to simplify calculating the PTE
* offset in the miss handler; it also cache-aligns the loaded PTE which
* may simplify the hardware's access.
*
* TLB fields are from PowerPC 476FP Embedded Processor Core User's Manual
* Version 1.0
*
* TLB Word 0:
*                                  1       1 2 2 2 2        2 2 3 3
*  0               8               6       9 0 1 2 4        8 9 0 1
* +---------------.---------------.---------+-+-+--.-------+-+-+-+-+
* |                    EPN                  |V|T|   DSIZ   |B|E|D|T|
* |                                         | |S|          | |P|P|P|
* +---------------'---------------'---------+-+-+--'-------+-+-+-+-+
*
* EPN  - Effective (Virtual) address Page Number
* V    - Valid page bit
* TS   - Translation address Space - vmLib/vmBaseLib only manages
*        values of '1' -- that is, dynamic mmu page mapping only
*        uses MSR[IS,DS] values of 1. TS values of zero are
*        only set up in a static TLB mapping in the BSP.  TS values
*        of 1 may also be set up in static TLB mapping in the BSP,
*        or may be set up using the sysPhysMemDesc array.
* DSIZ - This field describes the page size for this entry. Supported page sizes
*        are 4 KB (minimum size),16 KB, 64 KB, 1 MB, 16 MB, 256 MB, and 1 GB.
*
* EP   - The parity bit that covers the EPN
* DP   - The parity bit that covers the Valid, TS, and DSIZ fields.
* TP   - The parity bit that covers the TID. TID is located in the UTLB entry
*        tag field, but it can only be accessed by tlbre/tlbwe.
* B    - The bolted entry flag (available for tlbre).
*
* TLB Word 1:
*                                  1       1 2 2 2 2              3
*  0               8               6       9 0 1 2 4              1
* +---------------.---------------.---------+-+-+--.---------------+
* |                    RPN                  |R|E|      ERPN        |
* |                                         |P|P|                  |
* +---------------'---------------'---------+-+-+--'---------------+
*
* RPN  - Real (Physical) address Page Number (20 bit)
* RP   - The parity bit that covers the RPN
* EP   - The parity bit that covers the ERPN
* ERPN - Extended Real Page Number (10 bit)
*
* TLB Word 2:
*                              1 1 1       2       2   2         3
*  0       4       8           4 5 6       0       4   6         1
* +-+-+-+-+-------.-----------+-+-+-+-+-+-+-+-+---+-+-+-+-+-+-+-+-+
* |G|L|I| |                   |I|I|U|U|U|U|W|I|M|G|E| |U|U|U|S|S|S|
* |L|O|S| |                   |L|L| | | | | | | | | | | | | | | | |
* |B|C|R| |                   |1|1| | | | | | | | | | | | | | | | |
* | |K| | |                   |I|D|0|1|2|3| | | | | | |X|W|R|X|W|R|
* +-+-+-+-+-------'-----------+-+-+-+-+-+-+-+-+---+-+-+-+-+-+-+-+-+
*
* GLB   - miss hdlr will map page in all contexts(when reading from hardware, it
*         is the parity bit that covers storage attributes and permissions)
* LOCK  - lock bit label indicating static TLB used
* ISR   - isr bit set indicating no large page allowed
* IL1I  - Inhibit L1 instruction
* IL1D  - Inhibit L1 data
* U     - User defined bits
* W     - Write-Through
* I     - Caching Inhibited
* M     - Memory Coherence Required
* G     - Guarded (Avoid speculative access)
* E     - Little Endian
* UX    - User eXecute
* UW    - User Write
* UR    - User Read
* SX    - Supervisor eXecute
* SW    - Supervisor Write
* SR    - Supervisor Read
*/

typedef union mmu476_pte    /* Page Table Entry format */
    {
    struct          /* Bit field description */
    {
    /* word 0 */

    UINT32 epn:20;      /* effective page number */
    UINT32 v:1;         /* valid bit */
    UINT32 ts:1;        /* translation space bit */
    UINT32 dsize:6;     /* page size */
    UINT32 bolted:1;    /* bolted entry flag (available for tlbre) */
    UINT32 ep1:1;       /* the parity bit that covers the EPN */
    UINT32 dp:1;        /* parity bit for Valid, TS, and DSIZ fields */
    UINT32 tp:1;        /* the parity bit that covers the TID */

    /* word 1 */

    UINT32 rpn:20;      /* real page number */
    UINT32 rp:1;        /* The parity bit that covers the RPN */
    UINT32 ep2:1;       /* The parity bit that covers the ERPN */
    UINT32 erpn:10;     /* extended real page number */

    /* word 2 */

    UINT32 global:1;    /* miss hdlr will map page in all contexts or the */
                        /* parity bit that covers storage attributes and */
                        /* when read from hardware */
    UINT32 lock:1;      /* lock bit label indicating static TLB used */
    UINT32 isr:1;       /* isr bit set indicating no large page allowed */
    UINT32 rsvd2:11;    /* reserved */

    UINT32 li:1;        /* Inhibit L1 instruction cache */
    UINT32 ld:1;        /* Inhibit L1 data cache */
    UINT32 u0:1;        /* User defined bit 0 */
    UINT32 u1:1;        /* User defined bit 1 */
    UINT32 u2:1;        /* User defined bit 2 */
    UINT32 u3:1;        /* User defined bit 3 */

    UINT32 w:1;         /* write thru/back */
    UINT32 i:1;         /* cache inhibited */
    UINT32 m:1;         /* memory coherent */
    UINT32 g:1;         /* memory guarded  */
    UINT32 e:1;         /* little endian */

    UINT32 rsvd3:1;
    UINT32 ux:1;        /* user execute protection */
    UINT32 uw:1;        /* user write protection */
    UINT32 ur:1;        /* user read protection */
    UINT32 sx:1;        /* supervisor execute protection */
    UINT32 sw:1;        /* supervisor write protection */
    UINT32 sr:1;        /* supervisor read protection */

    UINT32 rsvd4:32;    /* pad descriptor table to power of 2 */
    } field;

    struct
    {
    UINT32 word0;       /* word 0 */
    UINT32 word1;       /* word 1 */
    UINT32 word2;       /* word 2 */
    UINT32 pad0;        /* pad word */
    } words;

    } MMU476_PTE;

/*
 * The MMUCR register is important for TLB entry search, read and write:
 *
 *   Search: sts and stid fields are used by tlbsx instruction.
 *   Read: stid field is set by a tlbre 0 instruction
 *   Write: stid field is used by tlbwe 0 instruction
 */

typedef union
   {
   struct
   {
   UINT32  reale:1;     /* Real mode enable */
   UINT32  lway:2;      /* Latched way */
   UINT32  lvalid:1;    /* Latched valid */
   UINT32  dulxe:1;     /* Data-side user locked line exception enable */
   UINT32  iulxe:1;     /* Instruction-side user locked line exception enable */
   UINT32  rsvd:1;
   UINT32  lindex:8;    /* Latched index address */
   UINT32  sts:1;       /* Set translation space */
   UINT32  stid:16;     /* Set translation ID */
   } field;

   UINT32 word;

   } MMUCR_REG;

/* Translation Table Definition */

/* TLB Entry description, used for mmu initialization */

typedef struct
    {
    UINT32  effAddr;        /* Effective address of base of page */
    UINT32  realAddrExt;    /* 10 MSB of 42-bit real address */
    UINT32  realAddr;       /* 32 LSB of 42-bit real address */
    UINT32  attr;           /* page attributes */
    } TLB_ENTRY_DESC;

typedef union
    {
    struct
    {
    UINT32  sway:1;     /* software Specified mode vs. hardware assist mode */
    UINT32  way:2;      /* way number */
    UINT32  rsvd1:1;
    UINT32  bolt:1;     /* bolted */
    UINT32  entry:3;    /* index of bolted entry in MMUBE0/1 */
    UINT32  rsvd2:24;
    } write;

    struct
    {
    UINT32  rsvd1:1;
    UINT32  way:2;      /* way number */
    UINT32  rsvd2:5;
    UINT32  index:8;    /* index number */
    UINT32  rsvd3:16;
    } read;

    UINT32 word;
    } MMUTLB_RA;

extern STATUS mmu476LibInit (int mmuType, int staticTlbNum,
                 TLB_ENTRY_DESC * pStaticTlbDesc, UINT minPageSize);

#endif  /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCmmuPpc476Libh */

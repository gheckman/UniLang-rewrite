/* mmuE500Lib.h - mmu library for PowerPC E500 series */

/*
 * Copyright (c) 2001-2005,2007,2009,2011-2013  Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01o,30jan13,pcs  cleanup for code review.
01n,10sep12,pcs  Add support for e6500
01m,11nov11,ers  Fix for vmPageLock/Unlock. (WIND00297094)
                 N_TLB_ENTRIES for e500mc.  (WIND00322280)
01l,29jun09,pmr  e500mc 36-bit addressing
01k,10jun09,pmr  e500mc static TLB num.
01j,19apr07,dtr  Add support for e200 VLE.
01i,19jul05,dtr  Implement 36bit rpn.
01h,11nov04,dtr  Add user permission flags for static TLBs.
01g,07oct04,mdo  Documentation fixes for apigen.
01f,09apr04,dtr  Add in MMU_LOCK mask and bit field in Pte.
01e,18mar04,dtr  Mods fixes after formal inspection.
01d,09feb04,dtr  Fix protection bits.
01c,30jan04,mil  Updated for Base6.
01b,13jun03,mil  Added TLB sizes.
01a,07jan03,dtr  Adding support for static TLB entries.
*/

/*
DESCRIPTION

This header contains the public interface to the PowerPC E500 Core Memory
Management Library. It also defines private (internal) structures and
macros used to manipulate the E500 MMU.

Theory: the vmBaseLib and vmLib provide an application programmer
interface to the memory management and protection features of the E500
MMU. With the help of the aimMmuLib and mmuE500Lib layers, a data
structure is maintained which stores per-page attributes: validity,
protection, cacheability, and address translation. This data structure
represents each page as a page table entry (PTE).

The E500 MMU has two levels.  In level 1, instruction and data are
split, while they are unified in level 2.  Level 1 is maintained by
the hardware and level 2 is maintained by the OS.  The number of entries
are as follows:

Name      Level   Type No of pg sizes Assoc     #entries     filled by
I-L1VSP     L1    Instr     9         Full         4         TLB1 hit
I-L1TLB4K   L1    Instr   1(4k)       4-way        64         TLB0 hit
D-L1VSP     L1    Data      9         Full         4         TLB1 hit
D-L1TLB4K   L1    Data    1(4k)       4-way        64         TLB0 hit
TLB1        L2    I/D       9         Full        16         s/w tlbwe
TLB0        L2    I/D     1(4k)       2-way       256         s/w tlbwe

The VSP (variable sized page) are used as static entries like the BATs,
while the 4k page are dynamic entries that gets loaded with the PTEs.
When a TLB miss occur in TLB0, an exception occurs and the OS walks the
data structure and copies a PTE into a TLB0 entry.  Hence, TLB1 is 
filled with mapping from the sysStaticTlbDesc[] array, and TLB0 is 
filled with mapping from the sysPhysMemDesc[] array.

Note that the E500 MMU cannot be turned off.  Translation occurs at
all time, which it uses also the IS and DS bits while deciding a hit.
Real mode is simulated with both IS and DS bits set to zero.

This file provides data needed to coordinate the mmuE500Lib layer with
the aimMmuLib and vmLib/vmBaseLib layers, as well as definitions needed
to configure the sysStaticTlbDesc[] array.
*/

#ifndef __INCmmuE500Libh
#define __INCmmuE500Libh

#include <arch/ppc/ppc85xx.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#if defined (PPC_e6500)
#undef E6500MMU_HW_TLB_WALK
#endif

#define MMU_PAGE_SIZE           0x1000          /* pages are 4K bytes */

/*
 * MMU_I_ADDR_TRANS and MMU_D_ADDR_TRANS are used in the mmuE500Lib /
 * mmuPpcALib & cacheALib call interface. They are not useful at the
 * application programming level.
 */

#define MMU_I_ADDR_TRANS        0
#define MMU_D_ADDR_TRANS        1

/*
 * MMU_INST and MMU_DATA are used at the usrMmuInit
 * interface.  They are not useful at the application programming
 * level.
 */

#define MMU_INST                0x01
#define MMU_DATA                0x02

/*
 * MMU_STATE attributes
 *
 */

#if defined (PPC_e6500)

/* offsets to the entries to the TLB1ESEL structure. */

#define TLB1ESEL_NEXT_OFFSET	0
#define TLB1ESEL_START_OFFSET	1
#define TLB1ESEL_MAX_OFFSET	2
#define TLB1ESEL_LOCK_OFFSET	3


/* V, WIMGE bits */
#define MMU_STATE_VALID                         0x00000001
#define MMU_STATE_VALID_NOT                     0x00000000
#define MMU_STATE_LOCK                          0x00002000
#define MMU_STATE_UNLOCK                        0x00000000
#define MMU_STATE_CACHEABLE_WRITETHROUGH        0x00800000
#define MMU_STATE_CACHEABLE_COPYBACK            0x00000000
#define MMU_STATE_CACHEABLE                     0x00000000
#define MMU_STATE_CACHEABLE_NOT                 0x00400000
#define MMU_STATE_MEM_COHERENCY                 0x00200000
#define MMU_STATE_MEM_COHERENCY_NOT             0x00000000
#define MMU_STATE_GUARDED                       0x00100000
#define MMU_STATE_GUARDED_NOT                   0x00000000
#define MMU_STATE_ENDIAN_BIG                    0x00000000
#define MMU_STATE_ENDIAN_LITTLE                 0x00080000

#define MMU_STATE_MASK_VALID                    0x00000001
#define MMU_STATE_MASK_LOCK                     0x00002000
#define MMU_STATE_MASK_WIMG                     0x00F80000
#define MMU_STATE_MASK_WRITETHROUGH             0x00800000
#define MMU_STATE_MASK_CACHEABLE                0x00C00000
#define MMU_STATE_MASK_MEM_COHERENCY            0x00200000
#define MMU_STATE_MASK_GUARDED                  0x00100000
#define MMU_STATE_MASK_ENDIAN                   0x00080000

/* UX/SX, UW/SW, UR/SR bits */

#define MMU_STATE_EXECUTE                       0x000000C0
#define MMU_STATE_EXECUTE_NOT                   0x00000000
#define MMU_STATE_WRITABLE                      0x00000030
#define MMU_STATE_WRITABLE_NOT                  0x00000000
#define MMU_STATE_MASK_EXECUTE                  0x000000C0
#define MMU_STATE_MASK_WRITABLE                 0x00000030
#define MMU_STATE_MASK_WRITABLE_EXECUTE         0x000000F0
#define MMU_STATE_MASK_WIMG_WRITABLE_EXECUTE    0x00000000 
#define MMU_STATE_MASK_PROTECTION               0x000000FC
#define MMU_STATE_PROTECTION_BIT_SHIFT          0

#else

/* V, WIMGE bits */
#define MMU_STATE_VALID                         0x80000000
#define MMU_STATE_VALID_NOT                     0x00000000
#define MMU_STATE_LOCK                          0x00800000
#define MMU_STATE_UNLOCK                        0x00000000
#define MMU_STATE_CACHEABLE_WRITETHROUGH        0x00000010
#define MMU_STATE_CACHEABLE_COPYBACK            0x00000000
#define MMU_STATE_CACHEABLE                     0x00000000
#define MMU_STATE_CACHEABLE_NOT                 0x00000008
#define MMU_STATE_MEM_COHERENCY                 0x00000004
#define MMU_STATE_MEM_COHERENCY_NOT             0x00000000
#define MMU_STATE_GUARDED                       0x00000002
#define MMU_STATE_GUARDED_NOT                   0x00000000
#define MMU_STATE_ENDIAN_BIG                    0x00000000
#define MMU_STATE_ENDIAN_LITTLE                 0x00000001

#define MMU_STATE_MASK_VALID                    0x80000000
#define MMU_STATE_MASK_LOCK                     0x00800000
#define MMU_STATE_MASK_WIMG                     0x0000001F
#define MMU_STATE_MASK_WRITETHROUGH             0x00000010
#define MMU_STATE_MASK_CACHEABLE                0x00000018
#define MMU_STATE_MASK_MEM_COHERENCY            0x00000004
#define MMU_STATE_MASK_GUARDED                  0x00000002
#define MMU_STATE_MASK_ENDIAN                   0x00000001

/* UX/SX, UW/SW, UR/SR bits */

  /* drice - need to look at these values */
#define MMU_STATE_EXECUTE                       0x00003000
#define MMU_STATE_EXECUTE_NOT                   0x00000000
#define MMU_STATE_WRITABLE                      0x00000c00
#define MMU_STATE_WRITABLE_NOT                  0x00000000
#define MMU_STATE_MASK_EXECUTE                  0x00003000
#define MMU_STATE_MASK_WRITABLE                 0x00000c00
#define MMU_STATE_MASK_WRITABLE_EXECUTE         0x00003c00
#define MMU_STATE_MASK_WIMG_WRITABLE_EXECUTE    0x00000000 
#define MMU_STATE_MASK_PROTECTION               0x00003f00
#define MMU_STATE_PROTECTION_BIT_SHIFT          8

#endif /* PPC_e6500 */

/*
 * The next most significant MMU_PAGE_INDEX_BITS bits of the virtual
 * address are used as an index into the Page Table.
 *
 * The next most significant bits of the virtual address are used as an
 * index into the Page Table.  Note that MMU_PAGE_INDEX_BITS_MAX
 * describes the maximum number of bits to be used as a index to look up
 * an entry in the page table. 
 *
 * Each entry is of size 2 ^ MMU_PAGE_ENTRY_BITS, which is the size of
 * an MMUE500_PTE.
 */

#define MMU_PAGE_INDEX_BITS_MAX 10      /* number of bits in index */
#define MMU_PAGE_TBL_ENTRIES_MAX (0x1 << MMU_PAGE_INDEX_BITS_MAX)
                                        /* max number of page table entries */
#if defined(PPC_e6500)
#define MMU_PAGE_ENTRY_BITS     3    /* MMUE500_PTE size in bytes as pwr of 2 */
#else
#define MMU_PAGE_ENTRY_BITS     4    /* MMUE500_PTE size in bytes as pwr of 2 */
#endif

/*
 * Each context's MMU pages are mapped using a two-level page table
 * scheme. The level 1 table is called the REGION table and the level
 * 2 table is called a PAGE table.
 *
 * The most significant MMU_REGION_INDEX_BITS bits of the virtual
 * address are used as an index into the Region Table. Each entry is of
 * size 2 ^ MMU_REGION_ENTRY_BITS, typically a pointer to a PAGE table.
 */

#define MMU_REGION_INDEX_BITS   10      /* number of bits in index */
#define MMU_REGION_TBL_ENTRIES  (0x1 << MMU_REGION_INDEX_BITS)
                                        /* number of regions in table */
#define MMU_REGION_ENTRY_BITS   2       /* size in bytes as pwr of 2 */

#if defined (PPC_e6500)
#define MMUE500_NO_BITS_PHYS_ADDR       40
#elif defined(PPC_e500v2) || defined(PPC_e500mc)
#define MMUE500_NO_BITS_PHYS_ADDR       36
#endif

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

/* MMU_STATE_* protection mode sub-fields, mapping <<8 with hardware */

#if defined (PPC_e6500)

#define _MMU_UX                 0x00000080
#define _MMU_SX                 0x00000040
#define _MMU_UW                 0x00000020
#define _MMU_SW                 0x00000010
#define _MMU_UR                 0x00000008
#define _MMU_SR                 0x00000004

#else

#define _MMU_UX                 0x00002000
#define _MMU_SX                 0x00001000
#define _MMU_UW                 0x00000800
#define _MMU_SW                 0x00000400
#define _MMU_UR                 0x00000200
#define _MMU_SR                 0x00000100

#endif

#define _MMU_URWX                  (_MMU_UR | _MMU_UW | _MMU_UX)

/* MMU_STATE_* protection modes macros */

#define MMU_STATE_SUP_R            (_MMU_SR)
#define MMU_STATE_SUP_RW           (_MMU_SR|_MMU_SW)
#define MMU_STATE_SUP_RX           (_MMU_SR|        _MMU_SX)
#define MMU_STATE_SUP_RWX          (_MMU_SR|_MMU_SW|_MMU_SX)

#define MMU_STATE_SUP_R_USR_R      (MMU_STATE_SUP_R   | _MMU_UR)
#define MMU_STATE_SUP_RW_USR_R     (MMU_STATE_SUP_RW  | _MMU_UR)
#define MMU_STATE_SUP_RX_USR_R     (MMU_STATE_SUP_RX  | _MMU_UR)
#define MMU_STATE_SUP_RWX_USR_R    (MMU_STATE_SUP_RWX | _MMU_UR)

#define MMU_STATE_SUP_R_USR_W      (MMU_STATE_SUP_R   | _MMU_UW)
#define MMU_STATE_SUP_RW_USR_W     (MMU_STATE_SUP_RW  | _MMU_UW)
#define MMU_STATE_SUP_RX_USR_W     (MMU_STATE_SUP_RX  | _MMU_UW)
#define MMU_STATE_SUP_RWX_USR_W    (MMU_STATE_SUP_RWX | _MMU_UW)

#define MMU_STATE_SUP_R_USR_RW     (MMU_STATE_SUP_R   | _MMU_UR | _MMU_UW)
#define MMU_STATE_SUP_RW_USR_RW    (MMU_STATE_SUP_RW  | _MMU_UR | _MMU_UW)
#define MMU_STATE_SUP_RX_USR_RW    (MMU_STATE_SUP_RX  | _MMU_UR | _MMU_UW)
#define MMU_STATE_SUP_RWX_USR_RW   (MMU_STATE_SUP_RWX | _MMU_UR | _MMU_UW)

#define MMU_STATE_SUP_R_USR_X      (MMU_STATE_SUP_R   | _MMU_UX)
#define MMU_STATE_SUP_RW_USR_X     (MMU_STATE_SUP_RW  | _MMU_UX)
#define MMU_STATE_SUP_RX_USR_X     (MMU_STATE_SUP_RX  | _MMU_UX)
#define MMU_STATE_SUP_RWX_USR_X    (MMU_STATE_SUP_RWX | _MMU_UX)

#define MMU_STATE_SUP_R_USR_RX     (MMU_STATE_SUP_R   | _MMU_UR | _MMU_UX)
#define MMU_STATE_SUP_RW_USR_RX    (MMU_STATE_SUP_RW  | _MMU_UR | _MMU_UX)
#define MMU_STATE_SUP_RX_USR_RX    (MMU_STATE_SUP_RX  | _MMU_UR | _MMU_UX)
#define MMU_STATE_SUP_RWX_USR_RX   (MMU_STATE_SUP_RWX | _MMU_UR | _MMU_UX)

#define MMU_STATE_SUP_R_USR_WX     (MMU_STATE_SUP_R   | _MMU_UW | _MMU_UX)
#define MMU_STATE_SUP_RW_USR_WX    (MMU_STATE_SUP_RW  | _MMU_UW | _MMU_UX)
#define MMU_STATE_SUP_RX_USR_WX    (MMU_STATE_SUP_RX  | _MMU_UW | _MMU_UX)
#define MMU_STATE_SUP_RWX_USR_WX   (MMU_STATE_SUP_RWX | _MMU_UW | _MMU_UX)

#define MMU_STATE_SUP_R_USR_RWX    (MMU_STATE_SUP_R   | _MMU_URWX)
#define MMU_STATE_SUP_RW_USR_RWX   (MMU_STATE_SUP_RW  | _MMU_URWX)
#define MMU_STATE_SUP_RX_USR_RWX   (MMU_STATE_SUP_RX  | _MMU_URWX)
#define MMU_STATE_SUP_RWX_USR_RWX  (MMU_STATE_SUP_RWX | _MMU_URWX)

/* RPN field offset in TLB Word 0 (left shift this number of bits) */

#define MMU_RPN_SHIFT                           12

/* TLB_ENTRY_DESC page attributes */


#ifdef PPC_e6500

#define _MMU_TLB_TS_0           0x00000000      /* Translation Space 0 */
#define _MMU_TLB_TS_1           0x00002000      /* Translation Space 1 */

#define TLB_GLOBAL_BIT  30      /* global page map bit is at bit 30 of word 1 */
#define TLB_LOCK_BIT    18      /* lock page map bit is at bit 18 of word 1 */

#define _MMU_TLB_SZ_4K          0x00000100      /* 4KB page size */
#define _MMU_TLB_SZ_8K          0x00000180      /* 8KB page size */
#define _MMU_TLB_SZ_16K         0x00000200      /* 16KB page size */
#define _MMU_TLB_SZ_32K         0x00000280      /* 32KB page size */
#define _MMU_TLB_SZ_64K         0x00000300      /* 64KB page size */
#define _MMU_TLB_SZ_128K        0x00000380      /* 128KB page size */
#define _MMU_TLB_SZ_256K        0x00000400      /* 256KB page size */
#define _MMU_TLB_SZ_512K        0x00000480      /* 512KB page size */
#define _MMU_TLB_SZ_1M          0x00000500      /* 1MB page size */
#define _MMU_TLB_SZ_2M          0x00000580      /* 2MB page size */
#define _MMU_TLB_SZ_4M          0x00000600      /* 4MB page size */
#define _MMU_TLB_SZ_8M          0x00000680      /* 8MB page size */
#define _MMU_TLB_SZ_16M         0x00000700      /* 16MB page size */
#define _MMU_TLB_SZ_32M         0x00000780      /* 32MB page size */
#define _MMU_TLB_SZ_64M         0x00000800      /* 64MB page size */
#define _MMU_TLB_SZ_128M        0x00000880      /* 128MB page size */
#define _MMU_TLB_SZ_256M        0x00000900      /* 256MB page size */
#define _MMU_TLB_SZ_512M        0x00000980      /* 512MB page size */
#define _MMU_TLB_SZ_1G          0x00000a00      /* 1GB page size */
#define _MMU_TLB_SZ_2G          0x00000a80      /* 2GB page size */
#define _MMU_TLB_SZ_4G          0x00000b00      /* 4GB page size */
#define _MMU_TLB_SZ_8G          0x00000b80      /* 8GB page size */
#define _MMU_TLB_SZ_16G         0x00000c00      /* 16GB page size */
#define _MMU_TLB_SZ_32G         0x00000c80      /* 32GB page size */
#define _MMU_TLB_SZ_64G         0x00000d00      /* 64GB page size */
#define _MMU_TLB_SZ_128G        0x00000d80      /* 128GB page size */
#define _MMU_TLB_SZ_256G        0x00000e00      /* 256GB page size */
#define _MMU_TLB_SZ_512G        0x00000e80      /* 512GB page size */
#define _MMU_TLB_SZ_1TB         0x00000f00      /* 1TB page size */
#define _MMU_TLB_SZ_MASK        0x00000f80      /* mask for page size field */
#define _MMU_TLB_SZ_SHIFT       7               /* offset of page size field */
#define _MMU_TLB_VALID          0x80000000      /* TLB is valid bit */
#define _MMU_TLB_IPROT          0x40000000      /* invalidate protection */

#define _MMU_TLB_ATTR_W         0x00000010      /* writethrough */
#define _MMU_TLB_ATTR_I         0x00000008      /* inhibit caching */
#define _MMU_TLB_ATTR_M         0x00000004      /* memory coherency */
#define _MMU_TLB_ATTR_G         0x00000002      /* guarded */
#define _MMU_TLB_ATTR_E         0x00000001      /* endianess */


#define _MMU_TLB_PERM_X         0x00000020      /* executable */
#define _MMU_TLB_PERM_W         0x00000040      /* writable */
#define _MMU_TLB_PERM_UR        0x00010000      /* user read */
#define _MMU_TLB_PERM_UW        0x00020000      /* user write */
#define _MMU_TLB_PERM_UX        0x00040000      /* user execute */

#else

#define _MMU_TLB_TS_0           0x00000000      /* Translation Space 0 */
#define _MMU_TLB_TS_1           0x00001000      /* Translation Space 1 */

#define TLB_GLOBAL_BIT  25      /* global page map bit is at bit 0 of word 2 */
#define TLB_LOCK_BIT    26      /* lock page map bit is at bit 1 of word 2 */

#define _MMU_TLB_SZ_4K          0x00000100      /* 4KB page size */
#define _MMU_TLB_SZ_16K         0x00000200      /* 16KB page size */
#define _MMU_TLB_SZ_64K         0x00000300      /* 64KB page size */
#define _MMU_TLB_SZ_256K        0x00000400      /* 256KB page size */
#define _MMU_TLB_SZ_1M          0x00000500      /* 1MB page size */
#define _MMU_TLB_SZ_4M          0x00000600      /* 4MB page size */
#define _MMU_TLB_SZ_16M         0x00000700      /* 16MB page size */
#define _MMU_TLB_SZ_64M         0x00000800      /* 64MB page size */
#define _MMU_TLB_SZ_256M        0x00000900      /* 256MB page size */
#define _MMU_TLB_SZ_1G          0x00000a00      /* 1GB page size */
#define _MMU_TLB_SZ_MASK        0x00000f00      /* mask for page size field */
#define _MMU_TLB_SZ_SHIFT       8               /* offset of page size field */
#define _MMU_TLB_IPROT          0x00000080      /* invalidate protection */

#define _MMU_TLB_ATTR_W         0x00000010      /* writethrough */
#define _MMU_TLB_ATTR_I         0x00000008      /* inhibit caching */
#define _MMU_TLB_ATTR_M         0x00000004      /* memory coherency */
#define _MMU_TLB_ATTR_G         0x00000002      /* guarded */
#define _MMU_TLB_ATTR_E         0x00000001      /* endianess */


#define _MMU_TLB_PERM_X         0x00000020      /* executable */
#define _MMU_TLB_PERM_W         0x00000040      /* writable */
#define _MMU_TLB_PERM_UR        0x00010000      /* user read */
#define _MMU_TLB_PERM_UW        0x00020000      /* user write */
#define _MMU_TLB_PERM_UX        0x00040000      /* user execute */

#ifdef PPC_e200
#define _MMU_TLB_ATTR_VLE       0x00080000      /* variable length encoding */
#endif
#endif /* PPC_e6500 */


#ifdef PPC_e500mc
#define N_TLB_ENTRIES_BITS             9        /* # TLB0: read TLB0CFG */
#define N_TLB_ENTRIES                  512      /* # TLB0: read TLB0CFG */
#define MMUE500_NUM_STATIC_TLB_ENTIRES 0x40
#elif defined PPC_e6500
#define N_TLB_ENTRIES_BITS             10       /* # TLB0: read TLB0CFG */
#define N_TLB_ENTRIES                  1024     /* # TLB0: read TLB0CFG */
#define N_TLB1_ENTRIES                 64       /* # TLB1: read TLB1CFG */
#define MMUE500_NUM_STATIC_TLB_ENTIRES 0x40
#else
#define N_TLB_ENTRIES_BITS             8        /* # TLB0: read TLB0CFG */
#define N_TLB_ENTRIES                  256      /* # TLB0: read TLB0CFG */
#define MMUE500_NUM_STATIC_TLB_ENTIRES 0x10
#endif

#ifndef _ASMLANGUAGE

typedef union   /* e500 pte format */
    {
    UINT32 tlb1cfg;
    struct                      /* Bit field description */
        {
        UINT32 assoc:8;
        UINT32 minsize:4;
        UINT32 mazsize:4;
        UINT32 iprot:1;
        UINT32 avail:1;
        UINT32 :2;
        UINT32 nentry:12;
        } field;
    } E200_TLB1CFG;

#ifdef PPC_e6500
/*
* (PTE)
*
* | 0                                                             |28       31|
* |32                                                             |50       63|
* +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+--+--+--+--+--+--+--+--+
* |                                                               |           |
* |                              ARPN(0-28)                       |ARPN(29-31)|
* |                                                               |           |
* +---------------------------------------------------------------+-----------+
* |                               28                              |     4     |
*
* | 0       | 8| 9|10|11|12|13|14|15|16 |18 |19|20   |24|25|26|27|28|29|30 |31|
* |32       |40|41|42|43|44|45|46|47|48 |50 |51|52   |56|57|58|59|60|61|62 |63|
* +-+-+-+-+-+--+--+--+--+--+--+--+--+-+-+---+--+-----+--+--+--+--+--+---+--+--+
* |         |  |  |  |  |  |  |  |  |   |   |  |     |  |  |  |  |  |  |   |  |
* |  ARPN   |W |I |M |G |E |R |U0|U1| - |SW0|C |  PS |UX|SX|UW|SW|UR|SR|SW1|V |
* | (32-39) |  |  |  |  |  |  |  |  |   | L |  |     |  |  |  |  |  |  | G |  |
* +---------+--+--+--+--+--+--+--+--+---+---+--+-----+--+--+--+--+--+--+---+--+
* |    8    |1 |1 |1 |1 |1 |1 |1 |1 | 2 | 1 |1 |  4  |1 |1 | 1 |1 |1 |1 |1 | 1|
*
*
* ARPN  - Bbbreviated real page number
* WIMGE - Storage control attributes
* R     - Referenced bit
* U0    - User defined storage control bit 0
* U1    - User defined storage control bit 1
* SW0   - Available for SW use
* C     - Changed bit.
* PS    - Page size
* BAP   - Base access permissions
* SW1   - Available for SW use
* V     - Valid
*
*
* TLB Word 0:  (MAS1)
*
*
* | 0| 1   | 2                         |16  |18 |19|20       |25           31|
* |32|33   |34                         |48  |50 |51|52       |57           63|
* +--+-----+-+-+-+-+-+-+-+-+-+-+-+-+-+-'-+--+---+--+-+-+-+-+-+-+-+-+-+-+-+-+-+
* |  |     |                           |    |   |  |         |               |
* | V|IPROT|           TID             |    |IND|TS| TSIZE   |       -       |
* |  |     |                           |    |   |  |         |               |
* +_-+-----+---------------------------+----+---+--+---------+---------------+
* |1 |  1  |            14             | 2  | 1 |1 |   5     |     7         |
*
* V     - TLB Valid bit
* IPROT - Invalidate protect
* TID   - Translation ID
* IND   - Indirect
* TS    - Translation space
* TSIZE - Translation size
*
* TLB Word 1:  (MAS2)
*
* | 0                                     |20         |25|26|27|28|29|30|31|
* |32                                     |52         |57|58|59|60|61|62|63|
* +-+-+-+-+-+-+-+-'-+-+-+-+-+-+-+-'-+-+-+-+-+-+---+-'-+--+--+--+--+--+--+--+
* |                                                   |  |  |  |  |  |  |  |
* |                    EPN                |     -     |X0|X1|W |I |M |G |E |
* |                                       |           |  |  |  |  |  |  |  |
* +---------------'---------------'-------+-----------+--+--+--+--+--+--+--+
* |                   20                  |     5     |1 |1 |1 |1 |1 |1 |1 |
*
* EPN    - Effective (Virtual) address Page Number
* X0-X1  - Implementation dependant page attribute
* W     - Write-Through
* I     - Caching Inhibited
* M     - Memory Coherency required
* G     - Guarded
* E     - Endianess (Unused and set to zero.)
*
* TLB Word 2:  (MAS3)
*
* | 0                                   |20   |22     |26|27|28|29|30|31|
* |32                                   |52   |54     |58|59|60|61|62|63|
* +-+-+-+-+-+-+-+-'-+-+-+-+-+-+-+-'-+-+-+-+-+-+-+-'-+-+--+--+--+--+--+--+
* |                                     |     |       |  |  |  |  |  |  |
* |                    RPN              |  -  | U0-U3 |UX|SX|UW|SW|UR|SR|
* |                                     |     |       |  |  |  |  |  |  |
* +-------------------------------------+-----+-------+--------------+--+
* |                    RPN              |  -  | U0-U3 |    SPSIZE    |- |
* +-------------------------------------+-----+-------+--+--+--+--+--+--+
* |                   20                |  2  |   4   |       5      |1 |
*
* RPN    - Real (Physical) address Page Number
* U0-U3  - User bits
* UX     - User execute permission
* SX     - Supervisor execute permission
* UW     - User write permission
* SW     - Supervisor write permission
* UR     - User read permission
* SR     - Supervisor read permission
* SPSIZE - Sub-page size (4Kb for e6500)
*
*
* TLB Word 3:  (MAS7)
*
* | 0                                                    |24          31|
* |32                                                    |56          63|
* +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+--+--+--+--+--+--+
* |                                                      |              |
* |                          -                           |     RPN      |
* |                                                      |              |
* +------------------------------------------------------+--------------+
* |                         24                           |      8       |
*
* RPN    - Real (Physical) address Page Number 8 high order bits
*
*/
#else
/*
*
* E500 PTE descriptor definition 
* This stores most of the fields needed to update a TLB entry. Note that
* we store only 20 bits of the epn, since we support a minimum page size
* of 4K only. ERPN and variable page sizes are currently unimplemented.
*
* TLB fields are from ch. 6. PPCE500GP User's Manual, version 7, March
* 2002
*
* TLB Word 0:
*
* | 0|  1  | 2         | 8             |16   |19|20     |24           31|
* |32| 33  |34         |40             |48   |51|52     |56           63|
* +--+-----+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+--+-+-+-+-+-+-+-+-+-+-+-+-+
* |  |     |           |               |     |  |       |               |
* | V|IPROT|           |   TID         |     | T| TSIZE |               |
* |  |     |           |               |     | S|       |               |
* +--+-----+-----------+---------------+-----+--+-------+-+-+-+-+-+-+-+-+
* | 1|  1  |     6     |      8        |  3  | 1|   4   |       8       |    
*
* V     - TLB Valid bit
* IPROT - Invalidate protect 
* TID   - Translation ID
* TS    - Translation space
* TSIZE - Translation size 
*
*
* TLB Word 1:
*
* | 0                                     |20 |22 |23 |25         31|
* |32                                     |52 |54 |55 |57         63|
* +-+-+-+-+-+-+-+-'-+-+-+-+-+-+-+-'-+-+-+-+-+-+---+-'-+-+-+-+-+-+-+-+
* |                                       |   |   |   | | | | | | | |
* |                    EPN                |   |SHA|   |X|X|W|I|M|G|E|
* |                                       |   |REN|   |1|0| | | | | |
* +---------------'---------------'-------+-+-+---+-'-+-+-+-+-+-+-+-+
* |                 20                    | 2 | 1 | 2 |      7      |
*
* EPN    - Effective (Virtual) address Page Number
* SHAREN - Enable cache fills to use shared cache state
* X0-X1  - Implementation dependant page attribute 
* W     - Write-Through
* I     - Caching Inhibited
* M     - Memory Coherency required 
* G     - Guarded
* E     - Endianess (Unused and set to zero.)
*
*
* TLB Word 2:
*
* | 0                                     |20 |22     |26       31|
* |32                                     |52 |54     |58       63|
* +-+-+-+-+-+-+-+-'-+-+-+-+-+-+-+-'-+-+-+-+---+-------+-+-+-+-+-+-+
* |                                       |   |       | | | | | | |
* |                    RPN                |   | U0-U3 |U|S|U|S|U|S|
* |                                       |   |       |X|X|W|W|R|R|
* +---------------'---------------'-------+---+-+---+-+-+-+-+-+-+-+
* |                  20                   | 2 |   4   |1|1|1|1|1|1|
*
* RPN    - Real (Physical) address Page Number
* U0-U3  - User bits
* UX     - User execute permission
* SX     - Supervisor execute permission
* UW     - User write permission
* SW     - Supervisor write permission
* UR     - User read permission
* SR     - Supervisor read permission
*
*
*/
#endif /* PPC_e6500 */

typedef union e500_pte  /* pte format for e6500/e500mc/e500v2/e200 */
    {
    struct                      /* Bit field description */
        {
#if defined(PPC_e6500)
        /* pte format for e6500 */

        /* word 0 */

        UINT32 arpnHigh32:32;     /* real page number */

        /* word 1 */

        UINT32 arpnLow8:8;
        UINT32 w:1;             /* write thru/back */
        UINT32 i:1;             /* cache inhibited */
        UINT32 m:1;             /* memory coherent */
        UINT32 g:1;             /* memory guarded  */
        UINT32 e:1;             /* little endian bit */
        UINT32 r:1;
        UINT32 u0:1;            /* user attribute 0 */
        UINT32 u1:1;            /* user attribute 1 */
        UINT32 rsvd2:2;
        UINT32 lock:1;          /* lock bit label indicating static TLB used */
        UINT32 c:1;
        UINT32 psize:4;         /* translation size */
        UINT32 ux:1;            /* user execute protection */
        UINT32 sx:1;            /* supervisor execute protection */
        UINT32 uw:1;            /* user write protection */
        UINT32 sw:1;            /* supervisor write protection */
        UINT32 ur:1;            /* user read protection */
        UINT32 sr:1;            /* supervisor read protection */
        UINT32 global:1;        /* global bit for internal use */
        UINT32 v:1;             /* valid bit */

#else
        /* pte format for e500mc/e500v2/e200 */

        /* word 0 */

        UINT32 v:1;             /* valid bit */
        UINT32 iprot:1;         /* invalidate protect bit */
        UINT32 rsvd1:6;         /* reserved */
        UINT32 tid:8;           /* translation ID */
        UINT32 rsvd2:3;         /* reserved */
        UINT32 ts:1;            /* translation space */
        UINT32 tsize:4;         /* translation size */
        UINT32 rsvd3:8;         /* reserved */

        /* word 1 */

        UINT32 epn:20;          /* effective page number */
        UINT32 rsvd4:2;         /* reserved */
        UINT32 sharen:1;        /* enables cache fills to use shared cache state */
        UINT32 rsvd5:2;         /* reserved */
        UINT32 global:1;        /* global bit for internal use */

#ifdef PPC_e200 /* TLB0 not available on e200 so no lock bit reqd */
        UINT32 vle:1;           /* variable length encoding */
#else
        UINT32 lock:1;         /* lock bit label indicating static TLB used */
#endif
        UINT32 w:1;             /* write thru/back */
        UINT32 i:1;             /* cache inhibited */
        UINT32 m:1;             /* memory coherent */
        UINT32 g:1;             /* memory guarded  */
        UINT32 e:1;             /* little endian bit */

        /* word 2 */

        UINT32 rpn:20;          /* real page number */
        UINT32 rsvd6:2;         /* reserved */
        UINT32 u0:1;            /* user attribute 0 */
        UINT32 u1:1;            /* user attribute 1 */
        UINT32 u2:1;            /* user attribute 2 */
        UINT32 u3:1;            /* user attribute 3 */
        UINT32 ux:1;            /* user execute protection */
        UINT32 sx:1;            /* supervisor execute protection */
        UINT32 uw:1;            /* user write protection */
        UINT32 sw:1;            /* supervisor write protection */
        UINT32 ur:1;            /* user read protection */
        UINT32 sr:1;            /* supervisor read protection */

        /* word3 */

#if defined(PPC_e500v2) || defined(PPC_e500mc)
        UINT32 rsvd7:28;        /* reserved*/
        UINT32 erpn:4;          /* extended real page number*/
#else
        UINT32 rsvd7:32;        /* pad descriptor table to power of 2 */
#endif
#endif /* PPC_e6500 */

        } field;

    struct 
        {
        UINT32 word0;           /* word 0 */
        UINT32 word1;           /* word 1 */
#if !defined(PPC_e6500)
        UINT32 word2;           /* word 2 */
#if defined(PPC_e500v2) || defined(PPC_e500mc)
        UINT32 word3;           /* word3 */
#else
        UINT32 pad0;            /* pad word */
#endif
#endif /* !PPC_e6500 */
        } words;

    } MMUE500_PTE;

/* TLB Entry description, used for mmu initialization */

typedef struct
    {
    UINT32      effAddr;        /* Effective address of base of page */
    UINT32      realAddrExt;    /* top 4 bits of real address */
    UINT32      realAddr;       /* rest of real address */
    UINT32      attr;           /* page attributes */
    } TLB_ENTRY_DESC;

#if defined(PPC_e6500)
typedef union e6500_pte  /* e6500 pte format */
    {
    struct                      /* Bit field description */
        {
        /* word 0 */
        UINT32 v:1;             /* valid bit */
        UINT32 iprot:1;         /* invalidate protect bit */
        UINT32 tid:14;           /* translation ID */
        UINT32 rsvd1:2;         /* reserved */
        UINT32 ind:1;            /* translation space */
        UINT32 ts:1;            /* translation space */
        UINT32 tsize:5;         /* translation size */
        UINT32 rsvd3:7;         /* reserved */

        /* word 1 */
        UINT32 epn:20;          /* effective page number */
        UINT32 rsvd4:5;         /* reserved */
        UINT32 global:1;        /* global bit for internal use */
        UINT32 lock:1;         /* lock bit label indicating static TLB used */
        UINT32 w:1;             /* write thru/back */
        UINT32 i:1;             /* cache inhibited */
        UINT32 m:1;             /* memory coherent */
        UINT32 g:1;             /* memory guarded  */
        UINT32 e:1;             /* little endian bit */

        /* word 2 */
        UINT32 rpn:20;          /* real page number */
        UINT32 rsvd6:2;         /* reserved */
        UINT32 u0:1;            /* user attribute 0 */
        UINT32 u1:1;            /* user attribute 1 */
        UINT32 u2:1;            /* user attribute 2 */
        UINT32 u3:1;            /* user attribute 3 */
        UINT32 ux:1;            /* user execute protection */
        UINT32 sx:1;            /* supervisor execute protection */
        UINT32 uw:1;            /* user write protection */
        UINT32 sw:1;            /* supervisor write protection */
        UINT32 ur:1;            /* user read protection */
        UINT32 sr:1;            /* supervisor read protection */

        /* word3 */
        UINT32 rsvd7:24;        /* reserved*/
        UINT32 erpn:8;          /* extended real page number*/
        } field;

    struct 
        {
        UINT32 word0;           /* word 0 */
        UINT32 word1;           /* word 1 */
        UINT32 word2;           /* word 2 */
        UINT32 word3;           /* word 3 */

        } words;

    } MMUE6500_PTE;

#endif /* PPC_e6500 */

/*
 * Reserved atomics provides storage for spin locks used to protect
 * resources from simultaneous access by multiple CPUs.  pReservedAtomics,
 * a pointer to this atomics storage, is set to a "well known" address:
 * RESERVED_ATOMICS_ADRS.  It's area is initialized in mmuE500LibInit().
 * The BSP must "allocate" this storage by having it MMU mapped but not used.
 * The storage must be at a "well known" address.
 * 
 * Spin locks fail if any part of the variable's cache line is accessed.
 * The lock fields are aligned to a cache line with the remainder of the
 * line unreferenced by aligning the subsequent field on a cache line.
 * The page containing reserved atomics must be accessible by all CPUs.
 * WARNING: a spin lock is not a sempahore, the caller does NOT block as a
 * result of using a spin lock.
 * 
 * An enumerated index is used rather than an xxCreate because callers on
 * different CPUs need some way to ID the item created.  Intended usage:
 * atomic32Cas(MMU_SYNC,0,1); ... atomic32Cas(MMU_SYNC,1,0);
 */

typedef long atomicM_t _WRS_DATA_ALIGN_BYTES(_CPU_CACHE_ALIGN_SIZE);


typedef struct
{
atomicM_t  arch1;
long       isInitialized;   /* unused atomic area */
atomicM_t  arch2;
atomicM_t  arch3;
atomicM_t  arch4;
atomicM_t  bsp1;
atomicM_t  bsp2;
atomicM_t  cust1;
atomicM_t  cust2;
atomicM_t  pad;  /* ensures cust2 gets an entire line. Do NOT use pad. */
} reservedAtomics_t;

IMPORT reservedAtomics_t  * pReservedAtomics; /* pointer defined in mmuE500Lib.c */

#ifndef RESERVED_ATOMICS_ADRS
#define RESERVED_ATOMICS_ADRS 0x5000
#endif

#define MMU_SYNC &(pReservedAtomics->arch1)
#define L3_SYNC  &(pReservedAtomics->arch2)

#define RA_INITIALIZED_VALUE  0x61746f6d /* ASCII for "atom", atomics cleared */

#if defined(__STDC__) || defined(__cplusplus)

extern STATUS mmuE500LibInit (int mmuType, int staticTlbNum, 
                              TLB_ENTRY_DESC * pStaticTlbDesc);

#else   /* __STDC__ */

extern STATUS mmuE500LibInit ();

#endif  /* __STDC__ */

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCmmuPpcE500Libh */

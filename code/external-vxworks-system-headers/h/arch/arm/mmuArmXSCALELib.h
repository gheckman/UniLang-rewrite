/* mmuArmXSCALELib.h - XScale MMU library header file */

/*
 * Copyright (c) 2000, 2001, 2003-2007, 2009-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01l,29jul10,pad  Moved extern C statement after include statements.
01k,03nov09,j_b  add INCLUDE_MMU_TEX_SUPPORT, undef INCLUDE_MMU_SUBPAGE_SUPPORT
01j,23oct07,to   added lockCnt and lockOwner to MMU_TRANS_TBL
01i,13sep06,j_b  add page optimization support
01h,29mar06,m_h  Coherancy (S-bit) support
01g,03jan06,m_h  Manzano Support
01f,08feb05,rec  use VIRT_ADDR and PHYS_ADDR instead of void
01e,10feb05,jb   Reverting to ROM mode for shared data/libraries
01d,09dec04,jb   Palify Arm MMU
01c,08sep03,scm  add P-bit support...
01b,23jul01,scm  change XScale name to conform to coding standards...
01a,31aug00,scm  created.
*/

#ifndef __INCmmuArmXSCALELibh
#define __INCmmuArmXSCALELibh

#include <memLib.h>
#include <semLib.h>

#define MMU_ID_XSCALE           0x052000

/* Enable support for section descriptors */
#undef INCLUDE_MMU_SECTION_SUPPORT
#define INCLUDE_MMU_SECTION_SUPPORT

/* Let the Pal code know Xscale has unique structures */

#define MMU_ARCHITECTURE_DEFINES_STRUCTURES

#include "mmuArmPalLib.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Xscale specific definitions follow */

#undef INCLUDE_MMU_SUBPAGE_SUPPORT
	
#undef INCLUDE_MMU_TEX_SUPPORT
#define INCLUDE_MMU_TEX_SUPPORT

#undef MMU_DEF_L1_PAGE
#define MMU_DEF_L1_PAGE 0x00000001          /* domain zero, Page descriptor */

#undef MMU_STATE_MASK_WRITABLE
#define MMU_STATE_MASK_WRITABLE         0x00000030      /* All APn bits */

#define MMU_STATE_X_BIT                 0x00000040
#define MMU_STATE_S_BIT                 0x00000200      /* S-bit coherancy */

#define MMU_STATE_MASK_EX_BUFFERABLE    (MMU_STATE_X_BIT | MMU_STATE_MASK_BUFFERABLE)
#define MMU_STATE_MASK_EX_CACHEABLE     (MMU_STATE_X_BIT | MMU_STATE_MASK_CACHEABLE)

#undef MMU_STATE_VALID
#define MMU_STATE_VALID                 MMU_PTE_TYPE_EX_PAGE /* set to page type */

#undef MMU_STATE_WRITABLE
#define MMU_STATE_WRITABLE              0x00000030      /* APn bits to 11 */

#undef MMU_STATE_MASK_PROTECTION
#define MMU_STATE_MASK_PROTECTION       0x00000030      /* APn bits */

#undef MMU_STATE_SUP_RO
#define MMU_STATE_SUP_RO                0x00000000      /* AP: 00 */

#undef MMU_STATE_SUP_RW
#define MMU_STATE_SUP_RW                0x00000010      /* AP: 01 */

#undef MMU_STATE_USR_RO_SUP_RW
#define MMU_STATE_USR_RO_SUP_RW         0x00000020      /* AP: 10 */

#undef MMU_STATE_USR_RW_SUP_RW
#define MMU_STATE_USR_RW_SUP_RW         0x00000030      /* AP: 11 */

    /* only AP bits valid on extended small page tables are AP0 */

#ifdef INCLUDE_MMU_SBIT_SUPPORT
#define MMU_MSK_UNUSED_AP               0xfffff23f
#else /*INCLUDE_MMU_SBIT_SUPPORT*/
#define MMU_MSK_UNUSED_AP               0xfffff03f
#endif /*INCLUDE_MMU_SBIT_SUPPORT*/

#define MMU_MSK_CHK_APS                 0x00000fc0
#define MMU_MSK_X_BIT                   0x00000040

/* Section and supersection L1 definitions follow */

#undef MMU_DEF_L1_SECTION_PAGE
#define MMU_DEF_L1_SECTION_PAGE 0x00000002  /* Section page descriptor */

#undef MMU_DEF_L1_SUPERSECTION_PAGE
#define MMU_DEF_L1_SUPERSECTION_PAGE 0x00040002  /* supersection */

#undef MMU_DEF_L1_SECTION_PAGE_MASK
#define MMU_DEF_L1_SECTION_PAGE_MASK 0x00040003  /* mask */

#undef MMU_STATE_SECTION_MASK_WRITABLE
#define MMU_STATE_SECTION_MASK_WRITABLE 0x00000030      /* All APn bits */

/* optional extended physical address bit fields */
#define MMU_L1DSSECTION_EXTD_BA_MASK  MMU_L1DSSECTIONHI_BA_MASK

/* Supersection base address packing */
#define MMU_L1DSSECTION_BA_SET(physAddr, ssectDesc) \
            (ssectDesc = (ssectDesc & ~MMU_L1DSSECTION_EXTD_BA_MASK) | \
              ( (((unsigned long long)(physAddr)) & MMU_L1DSSECTIONLO_BA_MASK) | \
                ((((unsigned long long)(physAddr)) >> 12) & \
                        MMU_L1DSSECTIONHI_BA_MASK) ))
/* Supersection base address unpacking */
#define MMU_L1DSSECTION_BA_GET(ssectDesc) \
            ((unsigned long long) \
              ( (unsigned long long)(ssectDesc & MMU_L1DSSECTIONLO_BA_MASK) | \
                ((unsigned long long)(ssectDesc & MMU_L1DSSECTIONHI_BA_MASK) \
                        << 12) ))

/* The X-bit is the LSB of TEX: bit-12 of the section or supersection L1 */
#define MMU_STATE_SECTION_X_BIT         0x00001000

#define MMU_STATE_MASK_SECTION_EX_BUFFERABLE  \
                 (MMU_STATE_SECTION_X_BIT | MMU_STATE_MASK_BUFFERABLE)
#define MMU_STATE_MASK_SECTION_EX_CACHEABLE \
                 (MMU_STATE_SECTION_X_BIT | MMU_STATE_MASK_CACHEABLE)

#define MMU_SECTION_MSK_X_BIT           0x00001000

#define MMU_STATE_CACHEABLE_MINICACHE    0x48 /* allocate in minicache, X=1, CB=10  */

    /* the mini data cache attributes to the Auxiliary Control Reg */
    /* used by mmuSetMDBits...                                     */

#define MD_COPYBACK        0x00000000
#define MD_WRITEALLOCATE   0x00000010
#define MD_WRITETHRU       0x00000020

#define MMU_STATE_CACHEABLE_EX_COPYBACK  (MMU_STATE_X_BIT | MMU_STATE_CACHEABLE_COPYBACK)

#define MMU_STATE_EX_CACHEABLE          MMU_STATE_CACHEABLE_EX_COPYBACK

#define MMU_STATE_EX_CACHEABLE_NOT      0x0

    /* bufferable, not cacheable, no coalesce */

#define MMU_STATE_EX_BUFFERABLE         (MMU_STATE_X_BIT | MMU_STATE_BUFFERABLE)
#define MMU_STATE_EX_BUFFERABLE_NOT     0x0     /* will also set not cacheable, no coalesce */

#define MMU_ATTR_CACHE_MINICACHE        (MMU_ATTR_SPL_1 | MMU_ATTR_CACHE_COPYBACK)

    /*
     * two new states with extended small page tables, bufferable no coalesce, and
     * write back with read/write allocate...
     */

#define MMU_ATTR_NO_COALESCE (MMU_ATTR_SPL_2 | MMU_ATTR_CACHE_OFF) /* Cache -- no coalesce into buffers */
#define MMU_ATTR_WRITEALLOCATE (MMU_ATTR_SPL_3 | MMU_ATTR_CACHE_COPYBACK) /* Cache -- write allocate */

    /* cache states determined by MD-bits of Auxilliary Control Register */

#define MMU_ATTR_CACHE_MINICACHE_CB  (MMU_ATTR_SPL_1 | MMU_ATTR_CACHE_COPYBACK)
#define MMU_ATTR_CACHE_MINICACHE_WA  (MMU_ATTR_SPL_1 | MMU_ATTR_WRITEALLOCATE)
#define MMU_ATTR_CACHE_MINICACHE_WT  (MMU_ATTR_SPL_1 | MMU_ATTR_CACHE_WRITETHRU)

    /* Write-through mode is only available on some CPUs */

#define MMU_STATE_CACHEABLE_WRITETHROUGH        0x8

/*
 * Values to be used when mmuEnable() is called. This will be after the MMU has
 * been initialised by sysInit()/romInit() and after cacheLib has set whatever
 * cache enable settings have been chosen.
 *
 * M 1 Enable MMU
 * A 0 Disable address alignment fault
 * C X ((D-)Cache Enable) Controlled by cacheLib
 * W X (Write Buffer) Controlled by cacheLib
 * P 1 (PROG32) should be set before this
 * D 1 (DATA32) should be set before this
 * L 1 (Late abort on earlier CPUs) ignore
 * B X (Big/Little-endian) should be set before this
 * S 1 (System)
 * R 0 (ROM)
 * F 0 Should be Zero
 * Z X (Branch prediction enable on 810) Controlled by cacheLib
 * I X (I-cache enable) Controlled by cacheLib
 *
 * For time being, do not enable the address alignment fault, as GCC
 * currently generates unaligned accesses in its code, and switching this
 * on will cause immediate faults. So, do not put it into the enable
 * mask.
 *
 * We used to clear all the Reserved/Should Be Zero bits when the
 * MMU/MPU was enabled, by including one bits for them in the definition
 * of MMU_ENABLE_MASK. We no longer do this, as CPU designers may extend
 * the definitions of the bits within the MMU Control Register. The MMU
 * Control register is initialised within romInit()/sysInit(), as the BSP
 * is the only place where the particular details of the CPU/MMU are
 * actually known. In general, it will be appropriate for the BSP to
 * initialise the MMUCR Reserved/Should Be Zero bits to zero. When the
 * MMU is enabled, we will only change the bits we are particularly
 * concerned about, by using a Read-Modify-Write strategy.
 */

 /* This defines the operating mode MMUCR_ROM, MMUCR_SYSTEM, or neither */

#define MMUCR_MODE MMUCR_ROM            /* This MUST remain as ROM for shared libraries */

#define MMU_ENABLE_MASK  (MMUCR_M_ENABLE | MMUCR_SYSTEM | MMUCR_ROM)

#define MMU_ENABLE_VALUE (MMUCR_M_ENABLE | MMUCR_MODE)

#if (_BYTE_ORDER == _LITTLE_ENDIAN)
#define MMU_INIT_VALUE (MMUCR_PROG32 | MMUCR_DATA32 | MMUCR_L_ENABLE | \
                            MMUCR_MODE)
#else
#define MMU_INIT_VALUE (MMUCR_PROG32 | MMUCR_DATA32 | MMUCR_L_ENABLE | \
                            MMUCR_BIGEND | MMUCR_MODE)
#endif

#ifndef _ASMLANGUAGE

#if (_BYTE_ORDER == _LITTLE_ENDIAN)

/* little-endian */

/* First level page descriptors */

typedef struct
    {
    UINT type   : 2;        /* descriptor type, 1 => page */
    UINT pad1   : 2;        /* SBZ */
    UINT pad2   : 1;        /* SBO */
    UINT domain : 4;        /* domain number */
    UINT pbit   : 1;        /* XSCALE 'P' bit */
    UINT addr   : 22;       /* base address of page table */
    } PAGE_DESC_FIELD;

/* First level "section" descriptor */
typedef struct
    {
    UINT type   : 2;        /* descriptor type, 2 => section */
    UINT bbit   : 1;        /* bufferable-bit */
    UINT cbit   : 1;        /* cacheable-bit */
    UINT pad1   : 1;        /* SBO */
    UINT domain : 4;        /* domain number */
    UINT pbit   : 1;        /* XSCALE 'P' bit */
    UINT ap 	: 2;        /* AP */
    UINT tex    : 3;        /* TEX */
    UINT pad2   : 1;        /* SBO */
    UINT sbit   : 1;        /* S-bit */
    UINT pad3   : 1;        /* SBO */
    UINT super  : 1;        /* 1 => supersection */
    UINT pad4   : 1;        /* SBO */
    UINT addr   : 12;       /* base address of page table */
    } SECTION_DESC_FIELD;

/* First level "supersection" descriptor */
typedef struct
    {
    UINT type   : 2;        /* descriptor type, 2 => section */
    UINT bbit   : 1;        /* bufferable-bit */
    UINT cbit   : 1;        /* cacheable-bit */
    UINT pad1   : 1;        /* SBO */
    UINT addrHi2: 4;        /* SBZ [phys address 39:36] */
    UINT pbit   : 1;        /* XSCALE 'P' bit */
    UINT ap 	: 2;        /* AP */
    UINT tex    : 3;        /* TEX */
    UINT pad2   : 1;        /* SBO */
    UINT sbit   : 1;        /* S-bit */
    UINT pad3   : 1;        /* SBO */
    UINT super  : 1;        /* 1 => supersection */
    UINT pad4   : 1;        /* SBO */
    UINT addrHi : 4;        /* phys address 35:32 */
    UINT addrLo : 8;        /* phys address 31:24 */
    } SUPERSECTION_DESC_FIELD;



/* Layout of Page Table Entries (PTEs), actually small page descriptors */

typedef struct
    {
    UINT type   : 2;        /* page type, 3 => extended small page */
    UINT cb     : 2;        /* cacheable/bufferable bits */
    UINT ap     : 2;        /* access permission */
    UINT tex    : 4;        /* type extension field */
    UINT sbz    : 2;        /* should be zero */
    UINT addr   : 20;       /* page base address */
    } PTE_FIELD;

#else /* (_BYTE_ORDER == _LITTLE_ENDIAN) */

/* big-endian */

/* First level page descriptors */

typedef struct
    {
    UINT addr   : 22;       /* base address of page table */
    UINT pbit   : 1;        /* XSCALE 'P' bit */
    UINT domain : 4;        /* domain number */
    UINT pad2   : 1;        /* SBO */
    UINT pad1   : 2;        /* SBZ */
    UINT type   : 2;        /* descriptor type, 1 => page */
    } PAGE_DESC_FIELD;

/* First level "section" descriptor */
typedef struct
    {
    UINT addr   : 12;       /* base address of page table */
    UINT pad4   : 1;        /* SBO */
    UINT super  : 1;        /* 1 => supersection */
    UINT pad3   : 1;        /* SBO */
    UINT sbit   : 1;        /* S-bit */
    UINT pad2   : 1;        /* SBO */
    UINT tex    : 3;        /* AP */
    UINT ap 	: 2;        /* AP */
    UINT pbit   : 1;        /* XSCALE 'P' bit */
    UINT domain : 4;        /* domain number */
    UINT pad1   : 1;        /* SBO */
    UINT c  	: 1;        /* c-bit */
    UINT b  	: 1;        /* b-bit */
    UINT type   : 2;        /* descriptor type, 2 => section */
    } SECTION_DESC_FIELD;

/* First level "supersection" descriptor */
typedef struct
    {
    UINT addrLo : 8;        /* phys address 31:24 */
    UINT addrHi : 4;        /* phys address 35:32 */
    UINT pad4   : 1;        /* SBO */
    UINT super  : 1;        /* 1 => supersection */
    UINT pad3   : 1;        /* SBO */
    UINT sbit   : 1;        /* S-bit */
    UINT pad2   : 1;        /* SBO */
    UINT tex    : 3;        /* AP */
    UINT ap 	: 2;        /* AP */
    UINT pbit   : 1;        /* XSCALE 'P' bit */
    UINT addrHi2: 4;        /* SBZ [phys address 39:36] */
    UINT pad1   : 1;        /* SBO */
    UINT c  	: 1;        /* c-bit */
    UINT b  	: 1;        /* b-bit */
    UINT type   : 2;        /* descriptor type, 2 => section */
    } SUPERSECTION_DESC_FIELD;

/* Layout of Page Table Entries (PTEs), actually small page descriptors */

typedef struct
    {
    UINT addr   : 20;       /* page base address */
    UINT sbz    : 2;        /* should be zero */
    UINT tex    : 4;        /* type extension field */
    UINT ap     : 2;        /* access permission */
    UINT cb     : 2;        /* cacheable/bufferable bits */
    UINT type   : 2;        /* page type, 3 => extended small page */
    } PTE_FIELD;

#endif /* (_BYTE_ORDER == _LITTLE_ENDIAN) */

/* First level descriptor access */

typedef union
    {
    PAGE_DESC_FIELD fields;
    SECTION_DESC_FIELD sectionFields;
    SUPERSECTION_DESC_FIELD supersectionFields;
    UINT32 bits;
    } MMU_LEVEL_1_DESC;

/* Second level descriptor access */

typedef union
    {
    PTE_FIELD fields;
    UINT32 bits;
    } PTE;

/*
 * Structure for MMU translation table access - normally used to get a pointer
 * to the first-level translation table.
 * To support page table optimization, a second first-level table and a
 * semaphore are needed.
 * The initial, unoptimized set of page tables will be set as the active
 * translation tables (via pLevel1Table) while optimization or deoptimization
 * is in progress using the inactive second translation table (pAltLevel1Table).
 * After each page table optimization or deoptimization operation has
 * completed, the second translation table will be set as the active
 * translation table.  The initial set of page tables retain their
 * links to level 2 pages, which may otherwise be lost after optimization.
 * Any non-optimization changes to the active first-level table will also be
 * made to the inactive first-level table.
 * The semaphore is used to prevent corruption of the tables.
 */

typedef struct mmuTransTblStruct
    {
    MMU_LEVEL_1_DESC *pLevel1Table;     /* active MMU table */
    MMU_LEVEL_1_DESC *pAltLevel1Table;  /* inactive MMU table */
    VX_MUTEX_SEMAPHORE(mmuTransTblSem); /* MMU tables' semaphore */
    UINT32      lockCnt;                /* lock count */
    atomic_t    lockOwner;              /* lock owner */
    } MMU_TRANS_TBL;

#if defined(__STDC__) || defined(__cplusplus)


IMPORT  void    mmuArmXSCALELibInstall (VIRT_ADDR(physToVirt) (PHYS_ADDR),
                                        PHYS_ADDR(virtToPhys) (VIRT_ADDR));
IMPORT  void    mmuArmXSCALETtbrSet (MMU_LEVEL_1_DESC *);
IMPORT  MMU_LEVEL_1_DESC *  mmuArmXSCALETtbrGet ( void);
IMPORT  void    mmuArmXSCALEDacrSet (UINT32 dacrVal);
IMPORT  void    mmuArmXSCALETLBIDFlushEntry (void *addr);
IMPORT  void    mmuArmXSCALETLBIDFlushAll (void);
IMPORT  void    mmuArmXSCALEAEnable (UINT32 cacheState);
IMPORT  void    mmuArmXSCALEADisable (void);
IMPORT  STATUS  mmuArmXSCALEPBitSet ( void * virtAddr, UINT32 size);
IMPORT  STATUS  mmuArmXSCALEPBitClear ( void * virtAddr, UINT32 size);
IMPORT  STATUS  mmuArmXSCALEPBitGet ( void * virtAddr );
IMPORT  STATUS  mmuArmXSCALEAcrGet (void );
IMPORT  void    mmuArmXSCALEAcrSet (UINT32 acrVal);

#else   /* __STDC__ */

IMPORT  void    mmuArmXSCALELibInstall ();
IMPORT  void    mmuArmXSCALETtbrSet ();
IMPORT  MMU_LEVEL_1_DESC *  mmuArmXSCALETtbrGet ();
IMPORT  void    mmuArmXSCALEDacrSet ();
IMPORT  void    mmuArmXSCALETLBIDFlushEntry ();
IMPORT  void    mmuArmXSCALETLBIDFlushAll ();
IMPORT  void    mmuArmXSCALEAEnable ();
IMPORT  void    mmuArmXSCALEADisable ();
IMPORT  STATUS  mmuArmXSCALEPBitSet ();
IMPORT  STATUS  mmuArmXSCALEPBitClear ();
IMPORT  STATUS  mmuArmXSCALEPBitGet ();
IMPORT  STATUS  mmuArmXSCALEAcrGet ();
IMPORT  void    mmuArmXSCALEAcrSet ();

#endif  /* __STDC__ */

#endif  /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif  /* __INCmmuArmXSCALELibh */

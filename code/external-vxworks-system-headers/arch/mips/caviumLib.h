/* caviumLib.h -  Cavium Support Routines */

/*
 * Copyright (c) 2010-2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01n,11may12,l_z  replace OCTEON_MODEL with CAV_PRID for CAVIUM_MAX_CORES
01m,09dec11,x_f  update for Octeon rev2 CN68xx board
01l,13apr11,rlg  update for Octeon rev2 boards
01k,17jan11,pgh  Add macro to get number of TLBs.
01j,09nov10,d_c  Define CAV_CACHE_LINE_SIZE in terms of CVMX_CACHE_LINE_SIZE
                 Remove unused definition of CVMX_CACHE_LINE_ALIGNED.
01i,15oct10,d_c  add CAV_SYNCWS
01h,29sep10,pgh  Remove assembly externs
01h,05oct10,d_c  Change ull to ULL to be Diab compatible
01g,28sep10,d_c  remove warning about assembler support
01f,24aug10,pgh  Add prototype for cavHwInit()
01e,16aug10,rlg  addition of more prototypes
01e,13aug10,d_c  Add interface elements to support vxbOcteonEnd.c
01d,02aug10,rlg  addition of more function prototypes and few defines
01c,21jul10,d_c  Add capability to get Cavium processor ID at runtime
01b,15jul10,d_c  Add cavCyclesGet()
01a,14jul10,d_c  Written
*/

/*
DESCRIPTION

This file declares macros, typedefs, and prototypes for general,
non-device-specific access routines for Cavium hardware.

*/

#ifndef __INCcaviumlibh
#define __INCcaviumlibh

#include <vsbConfig.h>
#include <vxWorks.h>
#ifdef _ASMLANGUAGE
#include <arch/mips/asmMips.h>
#endif
#include <arch/mips/private/octeonMips64.h>

#ifdef __cplusplus
extern "C" {
#endif


/* defines */

/* Cache line size */

#define CAV_CACHE_LINE_SIZE      CVMX_CACHE_LINE_SIZE

/*
 * Masks and shifts used to extract fields out of PRId register.
 * Private. Used by caviumLib.c and caviumALib.s. Not needed
 * for caviumLib API below.
 */

#define CAV_PRID_REV_MASK   0x000000ff
#define CAV_PRID_ID_MASK    0x0000ff00
#define CAV_PRID_ID_SHIFT   8

/*
 * PrId register defines for processor ID field and returned by
 * cavPridGet().. See PRId reg (CP0 15,0) definition in Cavium Octeon
 * HRM.
 */

#define CAV_PRID_CN36XX 0x00
#define CAV_PRID_CN38XX 0x00
#define CAV_PRID_CN3020 0x01
#define CAV_PRID_CN31XX 0x01
#define CAV_PRID_CN3005 0x02
#define CAV_PRID_CN3010 0x02
#define CAV_PRID_CN58XX 0x03
#define CAV_PRID_CN54XX 0x04
#define CAV_PRID_CN55XX 0x04
#define CAV_PRID_CN56XX 0x04
#define CAV_PRID_CN57XX 0x04
#define CAV_PRID_CN50XX 0x06
#define CAV_PRID_CN52XX 0x07
#define CAV_PRID_CN63XX 0x90
#define CAV_PRID_CN68XX 0x91

/*
 * OCTEON II define 
 * the prid for pass 2 units is defined by cavium to be
 * 0xd900?
 * d = manufactor - cavium
 * 9 = board - cn63xx
 *   0 = revision - pass 1.0
 *   1 = revision - pass 1.1
 *   2 = revision - pass 1.2
 *   8 = revision - pass 2.0
 *   9 = revision - pass 2.1
 *   A = revision - pass 2.2
 * NOTE: at this time only need the revision in initddr3 
 * low 8 bits of register - also this value doesn't match what the docs
 * say - definition taken from the u-boot code provided by cavium
 */
#define CAV_PRID_CN63XX_PASS10	0x00
#define CAV_PRID_CN63XX_PASS11	0x01
#define CAV_PRID_CN63XX_PASS12	0x02
#define CAV_PRID_CN63XX_PASS20	0x08
#define CAV_PRID_CN63XX_PASS21	0x09
#define CAV_PRID_CN63XX_PASS22	0x0A

/*
 * Cavium Processor Family Masks
 *
 * The CAV_PROC_FAMILY_GET() macro function returns one of these masks.
 * They also may or'ed together and passed to CAV_PROC_FAMILY_IN().
 */

#define CAV_PROC_FAMILY_CN3XXX 0x00000001
#define CAV_PROC_FAMILY_CN5XXX 0x00000002
#define CAV_PROC_FAMILY_CN6XXX 0x00000004

/*
 * Cavium Processor ID Masks.
 *
 * The CAV_PROC_ID_GET() macro function returns one of these values.
 * They also may or'ed together and passed to CAV_PROC_ID_IN().
 */

#define CAV_PROC_ID_CN36XX 0x00000001
#define CAV_PROC_ID_CN38XX 0x00000001
#define CAV_PROC_ID_CN3020 0x00000002
#define CAV_PROC_ID_CN31XX 0x00000002
#define CAV_PROC_ID_CN3005 0x00000004
#define CAV_PROC_ID_CN3010 0x00000004
#define CAV_PROC_ID_CN58XX 0x00000008
#define CAV_PROC_ID_CN54XX 0x00000010
#define CAV_PROC_ID_CN55XX 0x00000010
#define CAV_PROC_ID_CN56XX 0x00000010
#define CAV_PROC_ID_CN57XX 0x00000010
#define CAV_PROC_ID_CN50XX 0x00000020
#define CAV_PROC_ID_CN52XX 0x00000040
#define CAV_PROC_ID_CN63XX 0x00000080
#define CAV_PROC_ID_CN68XX 0x00000100

/* address for the leds */
#ifdef _ASMLANGUAGE
#define CAV_LED_ADDR 0x800000001d0200f8
#else /* _ASMLANGUAGE */
#define CAV_LED_ADDR 0x800000001d0200f8ULL
#endif /* _ASMLANGUAGE */

/* instruction define */
#define CAVSYNCIOBDMA _WRS_ASM (".word 0x0000008f")
#define CAVSYNCW      _WRS_ASM (".word 0x0000010f")

/* SYNCWS is defined SYNCW in SDK support for vxWorks. See cvmx-asm.h */

#define CAVSYNCWS     CAVSYNCW

/* generic define */

#if (CAV_PRID == CAV_PRID_CN68XX)
#define CAVIUM_MAX_CORES          32
#else /* !(CAV_PRID == CAV_PRID_CN68XX) */
#define CAVIUM_MAX_CORES          16 
#endif /* (CAV_PRID == CAV_PRID_CN68XX) */

/* globals */

/* Cavium processor family, processor ID, and processor revision
 *
 * *** PLEASE USE FUNCTION MACROS BELOW TO ACCESS THESE VARIABLES  ***
 */

#ifndef _ASMLANGUAGE

IMPORT unsigned int cavProcFamily;	/* Processor Family */
IMPORT unsigned int cavProcId;          /* Processor Id */
IMPORT unsigned int cavProcRev;		/* Processor revision */
	
#endif /* _ASMLANGUAGE */


/* functions */


#ifndef _ASMLANGUAGE
IMPORT void cavLibInit(void); /* Initialize module */
#endif /* ! _ASMLANGUAGE */

/***********************************************************************
* Functions that may be used prior to sysHwInit()
*/
	
/*
* The cavPridGet() and cavRevGet() functions access the hardware-based
* Cavium processor ID, and revision, They use only register accesses,
* and hence can be called even prior to .data, .bss, and GP
* initialization. However, they are less efficient than the cavProc*
* functions defined below, and should only be used prior to
* sysHwInit().
*/

/* These won't work for C code that runs in non-resident
 * command line bootroms, which are linked to RAM_LOW, but run from
 * ROM_TEXT_ADRS and RAM_HIGH_ADRS. These need to be
 * inlined. Specifically, octeonBootInit.c can't use these.
 */

#ifndef _ASMLANGUAGE

IMPORT unsigned int cavPridGet(void);
IMPORT unsigned int cavRevGet(void);

IMPORT UINT64 cavRead64
    (
    UINT64 addr
    );
IMPORT void cavWrite64
    (
    UINT64 addr,
    UINT64 val
    );
IMPORT UINT64 cavCsrRead
    (
    UINT64 addr
    );
IMPORT void cavCsrWrite
    (
    UINT64 addr,
    UINT64 val
    );
IMPORT UINT64 cavCyclesGet
    (
    void
    );

IMPORT void cavWrite32
    (
    UINT64 addr,
    UINT32 val
    );

IMPORT UINT32 cavRead32
    (
    UINT64 addr
    );


IMPORT void cavWrite16
    (
    UINT64 addr,
    UINT16 val
    );

IMPORT UINT16 cavRead16
    (
    UINT64 addr
    );

IMPORT void cavWrite8
    (
    UINT64 addr,   
    UINT8 val    
    );

IMPORT UINT8 cavRead8
    (
    UINT64 addr
    );

IMPORT void cavLedDisplay
    (
    const char *
    );


IMPORT void cavCvmmenctlSet
    (
    UINT64 value
    );

IMPORT UINT64 cavCvmmenctlGet
    (
    void
    );

IMPORT void *cavPhysToPtr
    (
    uint64_t physical_address
    );

IMPORT uint64_t cavPtrToPhys
    (
    void *ptr
    );

IMPORT unsigned int cavCoreNumGet (void);

IMPORT void cavHwInit(void);

#endif /* ! _ASMLANGUAGE */

    
/***********************************************************************
* Do not use the following macro functions prior to entering sysHwInit().
*/

#ifndef _ASMLANGUAGE

#define CAV_PROC_FAMILY_GET()            cavProcFamily
#define CAV_PROC_FAMILY_IN(familyMask)   (cavProcFamily & (familyMask))

#define CAV_PROC_ID_GET()                cavProcId
#define CAV_PROC_ID_IN(idMask)           (cavProcId & (idMask))

#define CAV_PROC_REV_GET()               cavProcRev

#else /* _ASMLANGUAGE */

#define CAV_PROC_FAMILY_GET(reg) \
  lw      reg, _WRS_MIPS_SDA_OFFSET(cavProcFamily)

#define CAV_PROC_FAMILY_IN(familyMask,reg) \
  lw      reg, _WRS_MIPS_SDA_OFFSET(cavProcFamily) ;\
  and     reg, familyMask

#define CAV_PROC_ID_GET(reg) \
  lw      reg, _WRS_MIPS_SDA_OFFSET(cavProcId)

#define CAV_PROC_ID_IN(idMask,reg) \
  lw      reg, _WRS_MIPS_SDA_OFFSET(cavProcId) ;\
  and     reg, idMask

#define CAV_PROC_REV_GET(reg) \
  lw      reg, _WRS_MIPS_SDA_OFFSET(cavProcRev)


/******************************************************************************
* CAV_NUM_TLBS_GET() - Get the number of TLBs.
*
* This macro returns the number of TLBs available.  The cn63xx uses the config 
* 4 register to store the upper bits for the total number of TLBs
*/

#if ((CAV_PRID == CAV_PRID_CN63XX) || (CAV_PRID == CAV_PRID_CN68XX))
#define CAV_NUM_TLBS_GET(val,tmp)           \
    mfc0    val, C0_CONFIG1;                \
    HAZARD_CP_READ;                         \
    and     val, CFG1_MMUMASK;              \
    srl     val, CFG1_MMUSHIFT;             \
    mfc0    tmp, C0_CONFIG4;                \
    HAZARD_CP_READ;                         \
    and     tmp, CFG4_MMUSIZEEXT_MASK;      \
    sll     tmp, CFG4_MMUSIZEEXT_OR_SHIFT;  \
    or      val, tmp;                       \
    addu    val, 1
#else /* (CAV_PRID == CAV_PRID_CN63XX) */
#define CAV_NUM_TLBS_GET(val,tmp)           \
    mfc0    val, C0_CONFIG1;                \
    HAZARD_CP_READ;                         \
    and     val, CFG1_MMUMASK;              \
    srl     val, CFG1_MMUSHIFT;             \
    addu    val, 1
#endif /* (CAV_PRID == CAV_PRID_CN63XX) || (CAV_PRID == CAV_PRID_CN68XX) */

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif
#endif /* __INCcaviumlibh */


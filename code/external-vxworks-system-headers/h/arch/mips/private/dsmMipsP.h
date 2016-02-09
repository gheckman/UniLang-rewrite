/* dsmMipP.h - private assembler definitions header file for disassembler */

/*
 * Copyright (c) 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01a,28apr10,rlg  written.
*/

#ifndef __INCdsmMipsPh
#define __INCdsmMipsPh

#ifdef __cplusplus
extern "C" {
#endif

#include <vsbConfig.h>
#include <arch/mips/archMips.h>
#include <arch/mips/regsMips.h>
#include <arch/mips/mipsExcPage.h>
#include <private/kernelLockLibP.h>
#ifdef _ASMLANGUAGE
#include <private/windLibP.h>
#endif /* _ASMLANGUAGE */

/*

The CPU bits defined below can be used to identify instructions which
are only valid on a particular set of CPU types.  At some point in the
future it might be valuable to add bits which identify CPU groups such
as ISA, ISA2, etc.  If you add any entry to this list, a corresponding
entry needs to be made to the CPUMASK, defined in /target/src/arch/mips
dsmLib.c.

*/
#define dsmANY          (0)
#define dsmMIPS1        (1 << 0)
#define dsmMIPS2        (1 << 1)	/* MIPSI2 */
#define dsmMIPS3        (1 << 2)	/* MIPSI3 */
#define dsmMIPS4        (1 << 3)	
#define dsmMIPS32       (1 << 4)	/* MIPSI32 */
#define dsmMIPS64       (1 << 5)	/* MIPSI64 */
#define dsmMIPS32R2    (1 << 6)		/* MIPSI32R2 */
#define dsmMIPS64R2    (1 << 7)		/* MIPSI64R2 */

#define dsmCW4011       (1 << 8)
#define dsmR4650        (1 << 9)
#define dsmVR5400       (1 << 10)
#define dsmRMI_XLX     (1 << 11)
#define dsmOCTEON      (1 << 12)
#define dsmOCTEONII    (1 << 13)

#define dsmUNKNOWN    (1 << 31)

UINT dsmMipsSupportISAs (void );

#ifdef __cplusplus
}
#endif


#endif /* __INCdsmMipsPh */

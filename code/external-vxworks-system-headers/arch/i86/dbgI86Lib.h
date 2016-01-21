/* dbgI86Lib.h - header file for arch dependent portion of debugger */

/* 
 * Copyright (c) 1991,1993,1997-1998,2002-2005,2009-2010,2012 
 * Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
01u,16oct12,scm  WIND00376020 - fast system call support...
01t,22oct10,jmp  Removed obsolete DSM() macro - Replaced by VXDBG_INSTR_CMP().
01s,29jul10,pad  Moved extern C statement after include statements.
01r,19jun09,mze  replacing PAD64
01q,20mar09,jmp  removed DBG_INST_ALIGN definition (Use the default one).
01p,10feb09,jb   Adding 64-bit Support
01p,31mar09,dbt  Disable hardware breakpoint support for Hypervisor
		 Guest OS (CQ:WIND00161733).
01o,16feb05,aeg  changed wdbDbgCtxXXX() prototypes (SPR #106381).
01n,14oct04,elg  Rename wdbDbgCtxXXX() in wdbCtxXXX().
01m,01sep04,elg  Define context load/save for WDB.
01l,19aug04,jb   Fix for SPRs 100660, 100729, and 100748
01k,25jun04,elg  Undefine WDB_CTX_LOAD() to use standard definition
		 (SPR #98730).
01j,27apr04,jmp  adapted to share trcArchLib between VxSim/i86 and i86 arches.
01i,02mar04,jb   Adding StepOverSyscall support
01h,17jul03,c_c  Fixed build.
01g,16sep02,pai  Updated with commonly used manifest constants.
01f,30may02,hdn  added WDB_CTX_LOAD() define (spr 75694)
01e,11mar98,dbt  corrected problems introduced by the SENS merge
                 added Copyright.
01d,13feb98,hdn  fixed BRK_DATAxx macros.
01d,30dec97,dbt  modified and added some defines for new breakpoint scheme.
01c,29nov93,hdn  added a definition EDI - EFLAGS.
01b,27aug93,hdn  added support for c++
01a,11sep91,hdn  written based on TRON version.
*/

#ifndef __INCI86dbgh
#define __INCI86dbgh

#ifdef _WRS_CONFIG_LP64
#include "arch/i86/x86_64/dbgX86_64Lib.h"
#else
/* includes */

#include "arch/i86/esfI86.h"
#include "arch/i86/regsI86.h"
#include "arch/i86/instrI86.h"
#include <vsbConfig.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#define BRK_INST            (0x00)    /* instruction hardware breakpoint   */
#define BRK_DATAW1          (0x01)    /* data write 1 byte breakpoint      */
#define BRK_DATAW2          (0x05)    /* data write 2 byte breakpoint      */
#define BRK_DATAW4          (0x0d)    /* data write 4 byte breakpoint      */
#define BRK_DATARW1         (0x03)    /* data read-write 1 byte breakpoint */
#define BRK_DATARW2         (0x07)    /* data read-write 2 byte breakpoint */
#define BRK_DATARW4         (0x0f)    /* data read-write 4 byte breakpoint */

#define DEFAULT_HW_BP       (BRK_DATARW1)   /* default hardware breakpoint */

#define BRK_HARDWARE        (0x10)    /* hardware breakpoint bit */
#define BRK_HARDMASK        (0x0f)    /* hardware breakpoint mask */

#define SAVED_DBGREGS       (0x18)    /* 6 debug registers */
#define SAVED_REGS          (0x38)    /* 8 + 6 registers */

#define TRACE_FLAG          (0x0100)  /* TF in EFLAGS */
#define INT_FLAG            (0x0200)  /* IF in EFLAGS */

#define DBG_HARDWARE_BP     1       /* hardware breakpoint support */

#ifdef	_WRS_CONFIG_WRHV_GUEST

/* No hardware breakpoint support in Hypervisor Guest OS for now */

#undef	DBG_HARDWARE_BP
#define	DBG_HARDWARE_BP	0
#endif	/* _WRS_CONFIG_WRHV_GUEST */

#ifndef _ASMLANGUAGE

#define DBG_BREAK_INST      (0xcc)    /* int 3 */

#if (CPU != PENTIUM)
#define DBG_SYSCALL_SIZE      2
#define DBG_SYSCALL_INST      0x5a5d340f
#define DBG_SYSCALL_INST_MASK 0xffffffff
#else
#define DBG_SYSCALL_SIZE    7
#define DBG_SYSCALL_INST    0x0000009A
#endif /* (CPU != PENTIUM) */

/* offsets to register fields in type REG_SET */

#define EDI                 (0)
#define ESI                 (1)
#define EBP                 (2)
#define ESP                 (3)
#define EBX                 (4)
#define EDX                 (5)
#define ECX                 (6)
#define EAX                 (7)
#define EFLAGS              (8)

/* context save/load for WDB */

#define	WDB_CTX_SAVE(pRegs)	(_wdbCtxSave (pRegs))
#define	WDB_CTX_LOAD(pRegs)	(_wdbCtxLoad (pRegs))

/* typedefs */

/* aliases for type <ESF0> */

typedef ESF0                BREAK_ESF;
typedef ESF0                TRACE_ESF;

/* hardware breakpoint registers */

typedef struct              /* DBG_REGS */
    {
    unsigned int    db0;    /* debug register 0 */
    unsigned int    db1;    /* debug register 1 */
    unsigned int    db2;    /* debug register 2 */
    unsigned int    db3;    /* debug register 3 */
    unsigned int    db6;    /* debug register 6 */
    unsigned int    db7;    /* debug register 7 */

    } DBG_REGS;


/* function declarations */

extern void	_wdbCtxLoad (const REG_SET *);
extern int	_wdbCtxSave (const REG_SET *);

#endif    /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* _WRS_CONFIG_LP64 */

#endif /* __INCI86dbgh */

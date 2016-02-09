/* dbgX86_64Lib.h - header file for arch dependent portion of debugger */

/* 
 * Copyright (c) 2009-2010, 2012 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
01k,24jul12,scm  WIND00225976 - syscall/sysret support...
01j,08nov10,scm  adjust constants for 64 bit syscalls...
01i,22oct10,jmp  Removed obsolete DSM() macro - Replaced by VXDBG_INSTR_CMP().
01h,23sep10,scm  WIND00234092 -correctly manage "FS" during rtp breakpoint handling.
01g,17sep10,scm  WIND00233372 -correct system call detection in
                 wdbDbgSysCallCheck.
01f,29apr10,pad  Moved extern C statement after include statements.
01e,18may09,jmp  Added missing prototypes for registers routines.
01d,13may09,rlp  Added Hardware breakpoint support for LP64 model.
01c,20apr09,jb   Update SAVED_DBGREGS for 64-bit
01b,20mar09,jmp  removed DBG_INST_ALIGN definition (Use the default one).
01a,26jan09,jb   Created from 32-bit version
*/

#ifndef __INCX86_64dbgh
#define __INCX86_64dbgh


/* includes */

#include <esf.h>
#include <regs.h>
#include <arch/i86/x86_64/instrX86_64.h>

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

#define SAVED_DBGREGS       (0x30)    /* 6 debug registers */
#define SAVED_REGS          (0xC8)    /* 19 + 6 registers */

#define TRACE_FLAG          (0x0100)  /* TF in EFLAGS */
#define INT_FLAG            (0x0200)  /* IF in EFLAGS */

#define DBG_HARDWARE_BP     1       /* hardware breakpoint support */

#ifndef _ASMLANGUAGE

#define DBG_BREAK_INST      (0xcc)    /* int 3 */

#define DBG_SYSCALL_SIZE    2      /* size of 'syscall' instruction */

/* instruction sequence of syscall */

#define DBG_SYSCALL_INST       0xfff883595b41050f 
#define DBG_SYSCALL_INST_MASK  0xffffffffffffffff /* validate syscall matches */

/*
 *
 * Intel® 64 and IA-32 Architectures Software Developer's Manual Volume 3B;
 * System Programming Guide, Part 2 states:
 *
 * In 64-bit mode, the upper 32 bits of DR7 are reserved and must be written
 * with zeros. Writing 1 to any of the upper 32 bits results in a #GP(0)
 * exception.
 */

#define	DR7_VALUE_SET(x)    ((x) & 0xffffffff)

/* offsets to register fields in type REG_SET */

#define R15                 (0)
#define R14                 (1)
#define R13                 (2)
#define R12                 (3)
#define R11                 (4)
#define R10                 (5)
#define R9                  (6)
#define R8                  (7)
#define RDI                 (8)
#define RSI                 (9)
#define RBP                 (10)
#define RSP                 (11)
#define RBX                 (12)
#define RDX                 (13)
#define RCX                 (14)
#define RAX                 (15)
#define EFLAGS              (16)
#define FS                  (19)

/* context save/load for WDB */

#define	WDB_CTX_SAVE(pRegs)	(_wdbCtxSave (pRegs))
#define	WDB_CTX_LOAD(pRegs)	(_wdbCtxLoad (pRegs))

/* typedefs */

/* aliases for type <ESF2> */

typedef ESF2                BREAK_ESF;
typedef ESF2                TRACE_ESF;

/* hardware breakpoint registers */

typedef struct              /* DBG_REGS */
    {
    ULONG    db0;    /* debug register 0 */
    ULONG    db1;    /* debug register 1 */
    ULONG    db2;    /* debug register 2 */
    ULONG    db3;    /* debug register 3 */
    ULONG    db6;    /* debug register 6 */
    ULONG    db7;    /* debug register 7 */

    } DBG_REGS;

/* function declarations (XXX Following lines should be in a private file) */

extern void     _wdbCtxLoad             (const REG_SET *);
extern int      _wdbCtxSave             (const REG_SET *);
extern long     rdi                     (long taskId);
extern long     rsi                     (long taskId);
extern long     rbp                     (long taskId);
extern long     rsp                     (long taskId);
extern long     rbx                     (long taskId);
extern long     rdx                     (long taskId);
extern long     rcx                     (long taskId);
extern long     rax                     (long taskId);
extern long     rflags                  (long taskId);
extern long     r8			(long taskId);
extern long     r9			(long taskId);
extern long     r10			(long taskId);
extern long     r11			(long taskId);
extern long     r12			(long taskId);
extern long     r13			(long taskId);
extern long     r14			(long taskId);
extern long     r15			(long taskId);

#endif    /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCX86_64dbgh */

/* dbgSimntLib.h - header file for arch dependent portion of debugger */

/*
 * Copyright (c) 1998,2004,2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this
 * software may be licensed only pursuant to the terms of an applicable
 * Wind River license agreement.
 */

/*
modification history
--------------------
01g,22oct10,jmp  Removed obsolete DSM() macro - Replaced by VXDBG_INSTR_CMP().
01f,19may10,elp  64 bits support.
01f,29apr10,pad  Moved extern C statement after include statements.
01e,18may04,jmp  fixed instrI86.h reference.
01d,07apr04,jmp  adapted to share trcArchLib between VxSim/i86 and i86 arches.
01c,11feb04,elg  Add syscall instruction size macro.
01b,09feb04,jeg  added DSM() macro definition
01a,29apr98,cym  written based on x86 version.
*/

#ifndef __INCdbgSimntLibh
#define __INCdbgSimntLibh

/* includes */

#include <vsbConfig.h>

#if (CPU==SIMNT)
#include <arch/simnt/instrSimpentium.h>
#elif (CPU==SIMLINUX)
#include <arch/simlinux/instrSimpentium.h>
#endif /* CPU == SIMNT */

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#define BRK_INST	0x1000		/* instruction hardware breakpoint */
#define BRK_DATAW1	0x1400		/* data write 1 byte breakpoint */
#define BRK_DATAW2	0x1500		/* data write 2 byte breakpoint */
#define BRK_DATAW4	0x1700		/* data write 4 byte breakpoint */
#define BRK_DATARW1	0x1c00		/* data read-write 1 byte breakpoint */
#define BRK_DATARW2	0x1d00		/* data read-write 2 byte breakpoint */
#define BRK_DATARW4	0x1f00		/* data read-write 4 byte breakpoint */

#define BRK_HARDWARE	0x1000		/* hardware breakpoint bit */
#define BRK_HARDMASK	0x1f00		/* hardware breakpoint mask */

#define TRACE_FLAG	(0x0100)	/* TF in EFLAGS */
#define INT_FLAG	(0x0200)	/* IF in EFLAGS */

#define DBG_INST_ALIGN	(1)

#ifndef _ASMLANGUAGE

#define BREAK_INST		0xcc	/* int 3 */
#define DBG_BREAK_INST		0xcc	/* int 3 */
#define	DBG_SYSCALL_SIZE	2
#define BREAK_ESF EXC_INFO
#define TRACE_ESF EXC_INFO

/* register indexes */

#ifdef _WRS_CONFIG_LP64
#define R15			(0)
#define R14			(1)
#define R13			(2)
#define R12			(3)
#define R11			(4)
#define R10			(5)
#define R9			(6)
#define R8			(7)
#define RDI			(8)
#define RSI			(9)
#define RBP			(10)
#define RSP			(11)
#define RBX			(12)
#define RDX			(13)
#define RCX			(14)
#define RAX			(15)
#define RFLAGS			(16)
#else /* _WRS_CONFIG_LP64 */
#define EDI			(0)
#define ESI			(1)
#define EBP			(2)
#define ESP			(3)
#define EBX			(4)
#define EDX			(5)
#define ECX			(6)
#define EAX			(7)
#define EFLAGS			(8)
#endif /* _WRS_CONFIG_LP64 */

#define _WRS_TRC_ARGS_COUNT	5       /* number of arguments to print in */
                                        /* stack trace */

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

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* INCdbgSimntLibh */

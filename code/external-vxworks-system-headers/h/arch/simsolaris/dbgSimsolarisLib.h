/* dbgSimsolarisLib.h - simsolaris debugger header */

/*
 * Copyright (c) 1995-2007, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
-------------------
01k,29apr10,pad  Moved extern C statement after include statements.
01j,08mar07,dbt  No longer include instrSparc.h file.
01i,24nov06,dbt  Cleaned up header files inclusion
01h,11feb04,elg  Add syscall instruction size macro.
01g,24jun03,jmp  code cleanup.
01f,24jan03,jeg  add Destination Register definition
01e,20jan03,jeg  Merged T22-CP1 : INST_SAV and INST_SAV_MASK Macros value
		 updated
01d,13sep00,mlg  added INST_SAV
01c,03mar00,elg  Add _wdbDbgCtxSetup() to support system mode.
01b,29dec97,dbt  modified for new breakpoint scheme
01a,07jun95,ism  derived from simsparc
*/

#ifndef __INCdbgSimsolarisLibh
#define __INCdbgSimsolarisLibh

/* includes */

#include <arch/simsolaris/regsSimsolaris.h>
#include <arch/simsolaris/archSimsolaris.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#define DBG_NO_SINGLE_STEP	1
#define DBG_BREAK_INST		0x91d02001

#define	DBG_SYSCALL_SIZE	((2 * sizeof (INSTR)) / sizeof (INSTR))

#define INST_SAV		0x9de3b000
#define INST_SAV_MASK		0xfffff000

#define INST_CALL		OP_1
#define INST_CALL_MASK		OP
#define JMPL_o7			(OP_2 + RD_o7 + OP3_38)
#define JMPL_o7_MASK		(OP + DR + OP3)

#define I7_OFFSET		0x0f    /* offset from base of stack, in ints */
#define I7_CONTENTS(sp)		((INSTR *)*(sp + I7_OFFSET))
#ifdef __cplusplus
}
#endif

#endif /* __INCdbgSimsolarisLibh */

/* esfSimsparc.h - vxSim for Windows exception stack frame */

/* Copyright 1993-1995, 2010 Wind River Systems, Inc. */

/*
modification history
--------------------
01b,29apr10,pad  Moved extern C statement after include statements.
01a,29apr98,cym  derived from simsolaris
*/

#ifndef __INCesfSimnth
#define __INCesfSimnth

#include "regs.h"
#include "excLib.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ESF             EXC_INFO

/* Overflow/Underflow Stack Frame */

#define STACK_FRAME      0x00                  /* Stack Frame */
#define SF_LOCALS        (STACK_FRAME + 0x00)  /* Local Registers */
#define SF_INS           (STACK_FRAME + 0x20)  /* In Registers */
#define SF_SPARE         (STACK_FRAME + 0x5C)  /* Spare Slot */
#define STACK_FRAME_SIZE 0x60

#define	INIT_STACK_FRAME	STACK_ROUND_UP ((((MAX_TASK_ARGS - 6) \
				* sizeof (int)) + (STACK_FRAME_SIZE - 4)))

#ifdef __cplusplus
}
#endif

#endif /* __INCesfSimnth */

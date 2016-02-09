/* taskDefs.h - Constants and other definitions required by taskLib */

/*
 * Copyright (c) 2005-2006,2008-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01e,29apr10,pad  Moved extern C statement after include statements.
01d,19mar09,to   WIND00158413: increase KERNEL_TASK_EXC_STACK_SIZE for x86
01c,07jan08,slk  defect 112288: fix CPU_FAMILY define for MIPS
                 KERNEL_TASK_EXC_STACK_SIZE
01b,16may06,pes  Increase KERNEL_TASK_EXC_STACK_SIZE for MIPS builds.
01b,16may06,slk  modified to increase exception stack size for MIPS times 2
01a,15aug05,yvp  written by extracting definitions from taskLib.h & taskLibP.h
*/

#ifndef __INCtaskDefsh
#define __INCtaskDefsh

/* includes */

#include "vxWorks.h"

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#define VX_USER_MODE		0x0000	 /* INTERNAL: tasks in user mode */
#define VX_SUPERVISOR_MODE	0x0001	 /* INTERNAL: tasks in sup mode */
#define VX_DEALLOC_STACK	0x0004	 /* INTERNAL: deallocate stack */
#define VX_TASK_OBJ_OWNER	0x0800	 /* INTERNAL: task owns objs directly */
#define VX_DEALLOC_EXC_STACK	0x1000	 /* INTERNAL: deallocate the exc stack */
#define VX_DEALLOC_TCB		0x8000	 /* INTERNAL: deallocate the task TCB */

#ifndef	_WRS_ARCH_IS_SIMULATOR
#if (CPU_FAMILY==MIPS) || (CPU_FAMILY==I80X86)
#define KERNEL_TASK_EXC_STACK_SIZE (4096*2)
#else /* (CPU_FAMILY==MIPS) || (CPU_FAMILY==I80X86) */
#define KERNEL_TASK_EXC_STACK_SIZE (4096)
#endif /* (CPU_FAMILY==MIPS) || (CPU_FAMILY==I80X86) */
#else /* _WRS_ARCH_IS_SIMULATOR */
#define KERNEL_TASK_EXC_STACK_SIZE (4096*3)
#endif /* _WRS_ARCH_IS_SIMULATOR */


#ifdef __cplusplus
}
#endif

#endif /* __INCtaskDefsh */

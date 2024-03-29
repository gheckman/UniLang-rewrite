/* kernelLib.h - header file for kernelLib.c */

/*
 * Copyright (c) 1990-1992, 2005-2007, 2009 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01o,21oct09,cww  Removed TICK_HOOK typedef
01n,12feb09,cww  add LP64 support
01m,06feb09,pcs  Updated to add support for the LP64 data model.
01l,11feb09,zl   removed WIND_SCHED_DESC
01k,04sep07,pch  CQ102745: resizeable idle-task exception stacks
01j,24nov06,cjj  added kernelCpuEnable(), fixed typo from
		 previous mod.
01i,23oct06,lei  added kernelIsCpuIdle & kernelIsSystemIdle;
		 changed "unsigned" to "unsigned int"
01h,31aug05,jln  added kernelRoundRobinInstall() 
01g,16aug05,jln  remove roundRobinLib.h
01f,02aug05,jln  Added WIND_SCHED_DESC struct
01e,22sep92,rrr  added support for c++
01d,04jul92,jcf  cleaned up.
01c,26may92,rrr  the tree shuffle
01b,04oct91,rrr  passed through the ansification filter
		  -fixed #else and #endif
		  -changed VOID to void
		  -changed copyright notice
01a,05oct90,shl created.
*/

#ifndef __INCkernelLibh
#define __INCkernelLibh

#ifdef __cplusplus
extern "C" {
#endif

/* typedefs */

/*
 * Parameters passed to kernelInit().
 *
 * Always change the version number when changing the structure.
 *
 * This helps kernelInit() to detect a mismatch between its caller and itself,
 * e.g. if they were compiled using different versions of kernelLib.h.
 */

#define	_KERNEL_INIT_PARAMS_VERSION	0x6600	/* sanity check */

typedef struct kernelInit_params
    {
    FUNCPTR rootRtn;			/* function to run as tRootTask */
    size_t rootMemSize;			/* memory for TCB and root stack */
    char   *pMemPoolStart;		/* beginning of memory pool */
    char   *pMemPoolEnd;		/* end of memory pool */
    size_t intStackSize;		/* interrupt stack size */
    size_t vmPageSize;			/* configuration's VM_PAGE_SIZE */
    size_t intStackOverflowSize;	/* int stack overflow region size */
    size_t intStackUnderflowSize;	/* int stack underflow region size */
    size_t idleTaskExcepStkSize;	/* SMP idle task exc. stack size */
    size_t idleTaskExcepStkOverflowSize;	/* ... overflow region size */
    size_t idleTaskExcepStkUnderflowSize;	/* ... underflow region size */
    int    lockOutLevel;		/* interrupt lock-out level (1-7) */
    } _KERNEL_INIT_PARAMS;

#define	_KERNEL_INIT_PARAMS_VN_AND_SIZE	\
	((_KERNEL_INIT_PARAMS_VERSION << 16) + sizeof(_KERNEL_INIT_PARAMS))

/* extern */

extern BOOL roundRobinHookInstalled;	  /* flag shows round robin hooked */

/* pointer to kernelRoundRobinHook */

extern void (*_func_kernelRoundRobinHook)(TASK_ID);

/* function declarations */

extern char *	kernelVersion (void);
extern STATUS 	kernelTimeSlice (int ticks);
extern void 	kernelInit (UINT32 sanity, _KERNEL_INIT_PARAMS *pParams);
extern STATUS 	kernelRoundRobinInstall (void);
extern STATUS	kernelCpuEnable (unsigned int cpuToEnable);
extern BOOL 	kernelIsCpuIdle (unsigned int cpu);
extern BOOL	kernelIsSystemIdle (void);

#ifdef __cplusplus
}
#endif

#endif /* __INCkernelLibh */

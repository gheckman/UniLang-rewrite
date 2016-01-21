/* intX86_64Lib.h - X86_64-specific interrupt library header file */

/*
 * Copyright (c) 2009-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01e,24mar10,scm  add support for 64 bit inlines...
01d,12jan10,scm  adjust proto typing...
01c,08sep09,scm  FUNCPTR update...
01b,20may09,jb   Change to kernel model
01a,12mar09,jb   Adding 64-bit support, created from 32 bit version 01g
*/

#ifndef __INCintX86_64Libh
#define __INCintX86_64Libh

#ifdef __cplusplus
extern "C" {
#endif

/* offset macro for stuff in the intConnect code */
#ifdef _WRS_ARCH_KERNEL_MODEL
#define ICC_ADDR_SIZE           4

#define ICC_INT_BASE            0
#define	ICC_INT_ENT		ICC_INT_BASE + 0x2	/* intConnectCode[2] */
#define	ICC_BOI_PUSH		ICC_INT_BASE + 0x13     /* intConnectCode[0x13] */
#define ICC_BOI_SIZE            16                      /* Size of BOI arg and call */
#define	ICC_BOI_PARAM		ICC_INT_BASE + 0x15	/* intConnectCode[0x15] */
#define	ICC_BOI_ROUTN		ICC_INT_BASE + 0x1F	/* intConnectCode[0x1F] */
#define	ICC_INT_PARAM		ICC_INT_BASE + 0x25	/* intConnectCode[0x25] */
#define	ICC_INT_ROUTN		ICC_INT_BASE + 0x2F	/* intConnectCode[0x2F] */
#define	ICC_EOI_PARAM		ICC_INT_BASE + 0x35	/* intConnectCode[0x35] */
#define	ICC_EOI_CALL		ICC_INT_BASE + 0x3E	/* intConnectCode[0x3E] */
#define ICC_EOI_SIZE            6
#define	ICC_EOI_ROUTN		ICC_INT_BASE + 0x40	/* intConnectCode[0x40] */
#define	ICC_INT_EXIT		ICC_INT_BASE + 0x53     /* intConnectCode[0x53] */
#else
#define ICC_ADDR_SIZE           8
#error _WRS_ARCH_KERNEL_MODEL is only supported model
#endif /* _WRS_ARCH_KERNEL_MODEL */

#ifndef _ASMLANGUAGE

typedef STATUS (*SYS_INT_LVL_ENABLE_RTN_PTR)(int);
typedef STATUS (*SYS_INT_LVL_DISABLE_RTN_PTR)(int);

#if defined (__GNUC__)

static __inline__ int _inline_intCpuLock (void)
    {
    long key;

    __asm__ volatile ("pushf; cli; pop %0; " \
		      : "=g" (key) : : "memory");

    return (int) key;
    }

static __inline__ void _inline_intCpuUnlock 
    (
    int key
    )
    {
    __asm__ volatile ("testl $0x200,%0; jz 0f; sti; 0: " \
		      : : "g" (key) : "cc", "memory");
    }

#else

#define _inline_intCpuLock()		intCpuLock()
#define _inline_intCpuUnlock(key)	intCpuUnlock(key)

#endif /* _VX_TOOL_FAMILY */

#define _inline_intCpuMicroLock() _inline_intCpuLock()
#define _inline_intCpuMicroUnlock(key) _inline_intCpuUnlock(key)

/* function declarations */

extern FUNCPTR 	intHandlerCreateX86_64 (FUNCPTR routine, _Vx_usr_arg_t parameter,
				     FUNCPTR routineBoi, _Vx_usr_arg_t parameterBoi,
				     FUNCPTR routineEoi, _Vx_usr_arg_t parameterEoi);
extern void 	intVecSet2 (FUNCPTR * vector, FUNCPTR function,
			    int idtGate, int idtSelector);
extern void	intVecGet2 (FUNCPTR * vector, FUNCPTR * pFunction, 
			    int * pIdtGate, int * pIdtSelector);

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INCintX86_64Libh */

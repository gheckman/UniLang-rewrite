/* intI86Lib.h - I86-specific interrupt library header file */

/*
 * Copyright (c) 2001,2003-2004,2007-2009 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01j,10jun09,sem  Update intCpuMicroLock inline defines
01i,15apr09,sem  Add new intCpuMicroLock API
01h,24mar09,sem  Removed andl instruction from inline intCpuLock().
01g,21apr08,scm  WIND00121559 - modified gnu versions of inline.
01f,19jun07,zl   added _inline_intCpuLock() and _inline_intCpuUnlock()
01e,12oct04,jb  Add interrupt lockout for automatic stack switch
01d,04dec03,jb  Removing info message
01c,22aug03,to   added inline intLock()/intUnlock().
		 deleted K&R style prototypes.
01b,09nov01,hdn  added intConnectCode offset macros
01a,29aug01,hdn  taken from T31 ver 01b.
*/

#ifndef __INCintI86Libh
#define __INCintI86Libh

#ifdef __cplusplus
extern "C" {
#endif


/* offset macro for stuff in the intConnect code */

#define ICC_INT_BASE            1
#define	ICC_INT_ENT		ICC_INT_BASE + 1	/* intConnectCode[1] */
#define	ICC_BOI_PUSH		ICC_INT_ENT + 7	        /* intConnectCode[8] */
#define	ICC_BOI_PARAM		ICC_BOI_PUSH + 1	/* intConnectCode[9] */
#define	ICC_BOI_ROUTN		ICC_BOI_PARAM + 5	/* intConnectCode[14] */
#define	ICC_INT_PARAM		ICC_BOI_ROUTN + 5	/* intConnectCode[19] */
#define	ICC_INT_ROUTN		ICC_INT_PARAM + 5	/* intConnectCode[24] */
#define	ICC_EOI_PARAM		ICC_INT_ROUTN + 5	/* intConnectCode[29] */
#define	ICC_EOI_CALL		ICC_EOI_PARAM + 4	/* intConnectCode[33] */
#define	ICC_EOI_ROUTN		ICC_EOI_CALL + 1	/* intConnectCode[34] */
#define	ICC_ADD_N		ICC_EOI_ROUTN + 6	/* intConnectCode[40] */
#define	ICC_INT_EXIT		ICC_ADD_N + 5	        /* intConnectCode[45] */

#ifndef _ASMLANGUAGE

#if defined (__DCC__)

__asm volatile int _inline_intCpuLock (void)
{
! "ax"						/* ax is clobbered */
	pushf					/* push EFLAGS on stack */
	cli					/* clear interrupts */
	popl %eax				/* get EFLAGS in EAX */
}

__asm volatile void _inline_intCpuUnlock (int key)
{
!
% mem key; lab skip_sti				/* input: key; declare label */
	testl	$0x200,key			/* test EFLAGS_IF */
	jz	skip_sti			/* if not set, skip sti */
	sti					/* else enable interrupts */
skip_sti:
}

#elif defined (__GNUC__)

static __inline__ int _inline_intCpuLock (void)
    {
    int key;

    __asm__ volatile ("pushf; cli; popl %0; " \
		      : "=g" (key) : : "memory");

    return key;
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

extern FUNCPTR 	intHandlerCreateI86 (FUNCPTR routine, int parameter,
				     FUNCPTR routineBoi, int parameterBoi,
				     FUNCPTR routineEoi, int parameterEoi);
extern void 	intVecSet2 (FUNCPTR * vector, FUNCPTR function,
			    int idtGate, int idtSelector);
extern void	intVecGet2 (FUNCPTR * vector, FUNCPTR * pFunction, 
			    int * pIdtGate, int * pIdtSelector);

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INCintI86Libh */

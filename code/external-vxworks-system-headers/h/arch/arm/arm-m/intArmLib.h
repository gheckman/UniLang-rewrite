/* intArmLib.h - ARM-specific interrupt library header file */

/*
 * Copyright (c) 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01a,12apr12,jdw  created.
*/

#ifndef __INCintArmLibh
#define __INCintArmLibh

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WRS_ENABLE_IRQ_TRACING
/* 
 * For tracing we can define some "no-op" instructions which can be
 * inserted and identified in the ICE trace buffer. 
 */
#define WRS_ICE_TRACE_IRQ_LOCK   orr     r5,r5,r5
#define WRS_ICE_TRACE_IRQ_UNLOCK orr     r6,r6,r6
#else  /* _WRS_ENABLE_IRQ_TRACING */
#define WRS_ICE_TRACE_IRQ_LOCK   
#define WRS_ICE_TRACE_IRQ_UNLOCK 
#endif /* _WRS_ENABLE_IRQ_TRACING */        
                
#ifndef _ASMLANGUAGE

/* inline intCpuLock()/intCpuUnlock() and intCpuMicroLock/Unlock() */

#if	defined (__DCC__)

__asm volatile int _inline_intCpuLock ()
{
! "r0"
        mrs     r0, BASEPRI            /* get current status */
        mov     r1, #0x10
		mrs     BASEPRI, r1
        WRS_ICE_TRACE_IRQ_LOCK 
}

__asm volatile void _inline_intCpuUnlock (int key)
{ 
% reg key; lab label ! "r0"             /* input: key in r0 */

        mrs     BASEPRI, r0
        WRS_ICE_TRACE_IRQ_UNLOCK 
}

#elif	defined (__GNUC__)

static __inline__ int _inline_intCpuLock (void)
    {
    int key;
    __asm__ volatile
	(
	"mrs	r0, BASEPRI;		"	/* get current status */
	"mov    r1, #0x10			"	/* set new status */
	"mrs    BASEPRI, r1			"
	: "=&r" (key)				/* output: key is %0 */
	:					/* no input */
	: "r0", "r1"
	);
    return key;
    }

static __inline__ void _inline_intCpuUnlock (int key)
    {
    __asm__ volatile
	(
	"mrs	BASEPRI, r0		"	/* set new status */
	: "r" (key)				/* input: key is %0 */
	: "r0" 					/* r0, r1 clobbered; memory */
						    /* clobber for code barrier */
	);	
    }

#endif	/* __DCC__ */

/*
 * For ARM-M these functions are identical
 */

#define _inline_intCpuMicroLock() _inline_intCpuLock()
#define _inline_intCpuMicroUnlock(key) _inline_intCpuUnlock(key)

/* functions in intArchLib.c and intALib.s */

extern STATUS intArchConnect (VOIDFUNCPTR * vector, 
                              VOIDFUNCPTR routine, int argument);
extern STATUS intArchDisconnect (VOIDFUNCPTR * vector, 
                                 VOIDFUNCPTR  routine, int argument);
extern int intLevelSet (int level);

extern STATUS intEnable (int level);
extern STATUS intDisable (int level);

extern unsigned int getBasePri( void );
extern unsigned int setBasePri( unsigned int level );     	  	 
                
#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
        }
#endif

#endif /* __INCintArmLibh */

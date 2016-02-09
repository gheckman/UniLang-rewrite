/* ivArm.h - ARM interrupt vectors */

/* Copyright 1996-1997 Wind River Systems, Inc. */

/*
modification history
--------------------
01a,09may96,cdp  created
*/

#ifndef	__INCivArmh
#define	__INCivArmh

#ifdef __cplusplus
extern "C" {
#endif


/* macros to convert interrupt vectors <-> interrupt numbers */

#define IVEC_TO_INUM(intVec)    ((int) (intVec))
#define INUM_TO_IVEC(intNum)    ((VOIDFUNCPTR *) (intNum))


/* interrupt vector definitions are in the BSP header files */


#ifdef __cplusplus
}
#endif

#endif	/* __INCivArmh */

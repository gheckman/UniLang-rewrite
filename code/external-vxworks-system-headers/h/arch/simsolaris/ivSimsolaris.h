/* ivSimsolaris.h - Solaris VxSim interrupt vectors */

/*
 * Copyright (c) 1993-2003,2007 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this
 * software may be licensed only pursuant to the terms of an applicable
 * Wind River license agreement.
 */


/*
modification history
--------------------
01j,05oct07,elp  added IPI_INTR_ID_DEBUG
01i,04mar07,elp  added multiples IPIs
01h,07feb07,elp  added IV_IPI0 definition.
01g,16sep03,jmp  cleanup interrupt vector definitions.
01f,21may03,jmp  moved IV_MAX from intArchLib.c.
01e,18mar03,dbt  Added missing interrupt vectors.
01d,05mar03,jeg  cleanup code .
01c,21feb03,jeg  added test to avoid multiple definitions of FD_TO_IVEC.
01b,13feb97,pr   changed the iv number which were different from the sparc.
01a,07jun95,ism  derived from simsparc
*/

#ifndef __INCivSimsolarisLibh
#define __INCivSimsolarisLibh

#ifdef __cplusplus
extern "C" {
#endif

/* maximun number of interrupt vectors */

#define	IV_MAX	(256 + 40)	/* 256 correspond to MAX_FD defined on host */
				/* side, see vxsimLib.h */

/* macros to convert interrupt vectors <-> interrupt numbers */

#define IVEC_TO_INUM(intVec)    ((int) (intVec))
#define INUM_TO_IVEC(intNum)    ((VOIDFUNCPTR *) (intNum))

#define IVEC_TO_FD(intVec)      (IVEC_TO_INUM(intVec) - 40)
#ifndef FD_TO_IVEC
#define FD_TO_IVEC(fd)          (INUM_TO_IVEC((fd) + 40))
#endif

/* interrupt vector definitions */

#define	IV_HUP          1
#define	IV_INT          2
#define	IV_ILL		4
#define	IV_TRAP		5
#define	IV_FPE		8
#define	IV_BUS          10
#define	IV_SEGV         11
#define	IV_CLOCK1       14
#define	IV_USR1         16
#define	IV_USR2         17
#define	IV_IO           22
#define	IV_CLOCK2       28
#define	IV_CLOCK3       29
#define IV_IPI0		32	/* aka IPI_INTR_ID_CPC */
#define IV_IPI1		33	/* aka IPI_INTR_ID_DEBUG */
#define IV_IPI2		34
#define IV_IPI3		35

#ifdef __cplusplus
}
#endif

#endif /* __INCivSimsolarisLibh */

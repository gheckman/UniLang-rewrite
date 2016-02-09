/* ivSimlinux.h - simlinux interrupt vectors */

/*
 * Copyright (c) 1993-2007 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this
 * software may be licensed only pursuant to the terms of an applicable
 * Wind River license agreement.
 */

/*
modification history
--------------------
01e,04mar07,elp  added multiples IPIs
01d,07feb07,elp  added IV_IPI.
01c,16sep03,jmp  cleanup interrupt vector definitions.
01b,21may03,jmp  moved IV_MAX from intArchLib.c.
01a,05sep00,hbh  derived from simsolaris
*/

#ifndef __INCivSimlinuxh
#define __INCivSimlinuxh

#ifdef __cplusplus
extern "C" {
#endif

/* maximun number of interrupt vectors */

#define IV_MAX  (256 + 40)      /* 256 correspond to MAX_FD defined on host */
                                /* side, see vxsimLib.h */

/* macros to convert interrupt vectors <-> interrupt numbers */

#define IVEC_TO_INUM(intVec)    ((int) (intVec))
#define INUM_TO_IVEC(intNum)    ((VOIDFUNCPTR *) (intNum))

#define IVEC_TO_FD(intVec)      (IVEC_TO_INUM(intVec) - 40)
#define FD_TO_IVEC(fd)          (INUM_TO_IVEC((fd) + 40))

/* interrupt vector definitions */

#define	IV_HUP          1
#define	IV_INT          2
#define	IV_ILL		4
#define	IV_TRAP		5
#define	IV_BUS          7
#define	IV_FPE		8
#define	IV_SEGV         11
#define	IV_CLOCK1       14
#define	IV_USR1         10
#define	IV_USR2         12
#define	IV_IO           29
#define	IV_CLOCK2       26
#define	IV_CLOCK3       27
#define IV_IPI0		32
#define IV_IPI1		33
#define IV_IPI2		34
#define IV_IPI3		35


#ifdef __cplusplus
}
#endif

#endif /* __INCivSimlinux */

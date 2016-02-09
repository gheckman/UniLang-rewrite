/* vxX86_64Lib.h - header for arch/board dependent routines for x86_64 */


/*
 * Copyright 2009, 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01c,09may12,j_l  WIND00337546 - Add vxGdtrSet() and vxLdtrSet() prototypes.
                                Modify vxLdtrGet() prototype.
                 Adhere to coding standards more closely
01b,24feb09,jb   Update to 64-bits
01a,26jan09,jb   Created from 32-bit version 01h
*/

#ifndef __INCvxX86_64Libh
#define __INCvxX86_64Libh

#ifdef __cplusplus
extern "C" {
#endif


/* power management mode definitions - used by vxPowerModeSet/Get */

#define VX_POWER_MODE_DISABLE      (0x1) /* power mgt disable: loop when idle*/
#define VX_POWER_MODE_AUTOHALT     (0x4) /* AutoHalt power management mode */

/* function declarations */

#ifndef	_ASMLANGUAGE

extern void	vxMemProbeTrap		(void);
extern STATUS	vxMemProbeSup		(int length, char * adrs, char * pVal);
extern long	vxCr0Get		(void);
extern void	vxCr0Set		(long cr0);
extern long	vxCr2Get		(void);
extern void	vxCr2Set		(long cr2);
extern long	vxCr3Get		(void);
extern void	vxCr3Set		(long cr3);
extern long	vxCr4Get		(void);
extern void	vxCr4Set		(long cr4);
extern int 	vxCsGet 		(void);
extern int	vxDsGet			(void);
extern int 	vxSsGet 		(void);
extern long	vxEflagsGet		(void);
extern void	vxEflagsSet		(long rflags);
extern void	vxDrGet			(long * pDr0, long * pDr1, long * pDr2,
					 long * pDr3, long * pDr4, long * pDr5,
					 long * pDr6, long * pDr7);
extern void	vxDrSet			(long dr0, long dr1, long dr2, long dr3,
					 long dr4, long dr5, long dr6, long dr7);
extern int	vxTssGet		(void);
extern void	vxTssSet		(long value);
extern void	vxGdtrGet		(long long int * pGdtr);
extern void	vxGdtrSet		(long long int * pGdtr);
extern void	vxIdtrGet		(long long int * pIdtr);
extern void	vxLdtrGet		(UINT16 * pLdtr);
extern void	vxLdtrSet		(UINT16 ldtr);
IMPORT STATUS	vxPowerModeSet		(UINT32 mode);
IMPORT UINT32	vxPowerModeGet		(void);
extern STATUS	vxIdleHookAdd		(FUNCPTR entHook, FUNCPTR exitHook);
extern VOID	vxIdleEntHookRtn	(void);
extern VOID	vxIdleExtHookRtn	(void);
extern UINT32	vxIdleUtilGet		(void);

extern void	vxShowInit		(void);
extern void	vxCpuShow		(void);
extern void	vxDrShow		(void);
extern void	vxSseShow		(long);
extern void	vxIdleShow		(BOOL debug);

#endif  /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCvxX86_64Libh */

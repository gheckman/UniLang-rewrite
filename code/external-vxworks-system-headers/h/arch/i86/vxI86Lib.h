/* vxI86Lib.h - header for arch/board dependent routines for the I80X86 */

/*
 * Copyright (c) 2001-2003, 2005, 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */


/*
modification history
--------------------
01i,09may12,j_l  WIND00337546 - Add vxGdtrSet() and vxLdtrSet() prototypes.
                                Modify vxLdtrGet() prototype.
                 Adhere to coding standards more closely
01h,16feb05,aeg  added various function prototypes (SPR #106381).
01g,24dec03,jb  Adding prototype for vxDsGet
01f,04sep02,hdn  added vxIdleHookAdd(), vxIdleShow() prototype.
01e,11apr02,pai  Added vxCpuShow(), vxDrShow(), and vxSseShow() prototypes.
01d,26mar02,pai  Added vxShowInit() prototype (SPR 74103).
01c,13nov01,ahm  Added rudimentary support for power management (SPR#32599)
01b,26oct01,hdn  added vxDr[SG]et(), vxTss[GS]et() prototype.
01a,22aug01,hdn  written.
*/

#ifndef __INCvxI86Libh
#define __INCvxI86Libh

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
extern int	vxCr0Get		(void);
extern void	vxCr0Set		(int cr0);
extern int	vxCr2Get		(void);
extern void	vxCr2Set		(int cr2);
extern int	vxCr3Get		(void);
extern void	vxCr3Set		(int cr3);
extern int	vxCr4Get		(void);
extern void	vxCr4Set		(int cr4);
extern int 	vxCsGet 		(void);
extern int	vxDsGet			(void);
extern int 	vxSsGet 		(void);
extern int	vxEflagsGet		(void);
extern void	vxEflagsSet		(int eflags);
extern void	vxDrGet			(int * pDr0, int * pDr1, int * pDr2,
					 int * pDr3, int * pDr4, int * pDr5,
					 int * pDr6, int * pDr7);
extern void	vxDrSet			(int dr0, int dr1, int dr2, int dr3,
					 int dr4, int dr5, int dr6, int dr7);
extern int	vxTssGet		(void);
extern void	vxTssSet		(int value);
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
extern void	vxSseShow		(int);
extern void	vxIdleShow		(BOOL debug);

#endif  /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCvxI86Libh */

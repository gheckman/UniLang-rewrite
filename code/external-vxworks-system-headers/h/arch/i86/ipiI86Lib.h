/* ipiI86Lib.h - I80X86 IPI library header */

/*
 * Copyright (c) 2002,2006-2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */


/*
modification history
--------------------
01m,03feb11,rbc  WIND00253734 - Disable _WRS_VX_IA_IPI_INSTRUMENTATION for 32
                 Bit.
01l,03jun10,scm  disable _WRS_VX_IA_IPI_INSTRUMENTATION for 64 bit...
01k,01jun10,jb   Adding ipi instrumentation for AMP/SMP M-N debugging
01j,29apr10,pad  Moved extern C statement after include statements.
01i,14jan09,scm  Clean up old SMP restrictions.
01h,27aug08,jpb  Renamed VSB header file
01g,24jun08,jpb  Added include path for kernel configurations options set in
                 vsb.  Renamed _WRS_VX_SMP to _WRS_CONFIG_SMP.
01f,01jun07,tor  add DEBUG IPI num
01e,06apr07,scm  clarify CPC "self" as meaning boot strap processor...
01d,08dec06,scm  add additional SMP ipi support routines...
01c,28feb02,hdn  took IPI_MAX_XXX macros from ipiArchLib.c
01b,27feb02,hdn  renamed ipiStubShutdown() to ipiShutdownSup()
01a,20feb02,hdn  written
*/

#ifndef __INCipiI86Libh
#define __INCipiI86Libh

	
#include <vsbConfig.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#define	IPI_MAX_HANDLERS	8	/* max number of handlers */
#define	IPI_MAX_RETRIES		3	/* max number of retries */

#define CPC_IPI_INUM        0xEF /* Must be highest possible int IPI */
#define DEBUG_IPI_INUM      0xEE /* second-highest possible IPI */
#define BEGIN_IPI_INUM      0xE8 /* First IPI Interrupt Number */

#define CPC_TO_ALL_BUT_SELF 0x0  /* special case for broadcasts */
#define CPC_TO_BSP          0x1
#define CPC_TO_AP_1         0x2
#define CPC_TO_AP_2         0x4
#define CPC_TO_AP_3         0x8
#define CPC_TO_ALL_CPUS     0xF

#ifndef	_ASMLANGUAGE

/* variable declarations */

IMPORT char	ipiCallTbl [];		/* table of IPI stub calls */

#ifdef _WRS_CONFIG_LP64
#undef _WRS_VX_IA_IPI_INSTRUMENTATION
#else
#undef _WRS_VX_IA_IPI_INSTRUMENTATION
#endif /* _WRS_CONFIG_LP64 */

#ifdef _WRS_VX_IA_IPI_INSTRUMENTATION
struct ipiCounters
    {
    UINT32 ipiEmit[IPI_MAX_HANDLERS];
    UINT32 ipiSent[IPI_MAX_HANDLERS];
    UINT32 ipiRecv[IPI_MAX_HANDLERS];
    };
extern struct ipiCounters *ipiCounters[VX_MAX_SMP_CPUS];
#endif /* _WRS_VX_IA_IPI_INSTRUMENTATION */

/* function declarations */

#if defined(__STDC__) || defined(__cplusplus)

extern void	ipiVecInit (UINT32 intNum);
extern void	ipiHandler (UINT32 index);
extern STATUS	ipiConnect (UINT32 intNum, VOIDFUNCPTR routine);
extern STATUS	ipiStartup (UINT32 apicId, UINT32 vector, UINT32 nTimes);
extern STATUS	ipiShutdown (UINT32 apicId, UINT32 vector);
extern STATUS	ipiReset (UINT32 apicId);
extern void	ipiStub (void);
extern void	ipiShutdownSup (void);
extern void	ipiHandlerTlbFlush (void);
extern void	ipiHandlerTscReset (void);
extern void	ipiHandlerShutdown (void);

/* CPC support routines... */
STATUS cpcIpiEmit (cpuset_t processor);
STATUS cpcIpiIntConnect (VOIDFUNCPTR * vector, VOIDFUNCPTR handler, int param);
STATUS cpcIpiIntEnable (int vector);
STATUS cpcIpiIntDisable (int vector);

#else	/* __STDC__ */

extern void	ipiVecInit ();
extern void	ipiHandler ();
extern STATUS	ipiConnect ();
extern STATUS	ipiStartup ();
extern STATUS	ipiShutdown ();
extern STATUS	ipiReset ();
extern void	ipiStub ();
extern void	ipiShutdownSup ();
extern void	ipiHandlerTlbFlush ();
extern void	ipiHandlerTscReset ();
extern void	ipiHandlerShutdown ();

/* CPC support routines... */
STATUS cpcIpiEmit ();
STATUS cpcIpiIntConnect ();
STATUS cpcIpiIntEnable ();
STATUS cpcIpiIntDisable ();

#endif	/* __STDC__ */

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCipiI86Libh */

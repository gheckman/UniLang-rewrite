/* mmuArchLib.h - mmu library header for VxSim */

/*
 * Copyright (c) 1999-2004,2007 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this
 * software may be licensed only pursuant to the terms of an applicable
 * Wind River license agreement.
 */

/*
modification history
--------------------
01g,23jul07,elp  moved type definition to mmuArchLibSP.h..
01f,03may07,elp  added SMP support.
01e,19aug04,dbt  Removed obsolote mmuArchCurrentSet() prototype.
01d,03dec03,jmp  added mmuArchLibInit().
01c,26nov03,jmp  added mmuArchCurrentSet().
01c,30dec03,kab  Update for VIRT_ADDR type
01b,07oct03,jmp  added MMU_STATE_VALID_NOT.
		 added MMU cache simulation.
01a,17jul03,jmp  imported from VxWorksAE.
*/

#ifndef __INCmmuArchLibh
#define __INCmmuArchLibh

#ifdef __cplusplus
extern "C" {
#endif

/* MMU Page Size */

#ifdef  HOST
#ifndef WIN32
#define MMU_PAGE_SIZE	0x2000		/* pages are 8 kbytes */
#else	/* !WIN32 */
#define MMU_PAGE_SIZE	0x10000		/* pages are 64 kbytes */
#endif	/* WIN32 */

#else

#if  CPU != SIMNT
#define MMU_PAGE_SIZE		0x2000		/* pages are 8 kbytes */
#else	/* CPU != SIMNT */
#define MMU_PAGE_SIZE		0x10000		/* pages are 64 kbytes */
#endif /* CPU != SIMNT */
#endif	/* HOST */

#if MMU_PAGE_SIZE == 0x10000
#define MMU_PAGE_TBL_SIZE	0x200000	/* page table is 2Mbytes */
#else
#define MMU_PAGE_TBL_SIZE	0x100000	/* page table is 1Mbytes */
#endif /* MMU_PAGE_SIZE == 0x10000 */

#ifndef  HOST
extern	STATUS	mmuArchLibInit		(UINT pageSize);
#endif	/* HOST */

#ifdef __cplusplus
}
#endif

#endif /* __INCmmuArchLibh */

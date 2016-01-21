/* wdbMemLib.h - WDB memory services header file */

/*
 * Copyright (c) 2003-2005 Wind River Systems, Inc.  
 *
 * The right to copy, distribute, modify or otherwise make use  of this 
 * software may be licensed only pursuant to the terms of an applicable Wind 
 * River license agreement.
 */

/*
modification history
--------------------
01b,18nov05,dbt  Removed wdbMemTest() prototype.
01a,14nov05,dbt  Updated wdbMemTest prototype.
		 Removed useless function pointers.
01d,30sep03.elg  Fix build warnings.
01c,29sep03,tbu  Changed wdbMemScan usage (now returns a status)
01b,16sep03,tbu  Added _wdbMemCksum
01a,06jan03,elg  Written.
*/

#ifndef __INCwdbMemLibh
#define	__INCwdbMemLibh

#ifdef	__cplusplus
extern "C" {
#endif	/* __cplusplus */

/* externs */

extern UINT32	wdbCksum	(UINT16 * pData, UINT32 nBytes, UINT32 init,
				 BOOL moreData);

#ifdef	__cplusplus
}
#endif	/* __cplusplus */

#endif	/* __INCwdbMemLibh */

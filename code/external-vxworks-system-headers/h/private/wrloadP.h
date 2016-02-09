/* wrloadP.h - private header file for wrload core */

/*
 * Copyright (c) 2008-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software may be
 * licensed only pursuant to the terms of an applicable Wind River license
 * agreement.
 */

/*
modification history
--------------------
01h,01mar10,v_r  Moved contents to wrloadSP.h.
01g,27nov09,v_r  Merged latest changes from wrlinux multicore layer:
		 + entry point now using WRLOAD_ADDR_T
		 + added wrloadSubComponentVersionPrint(). 
01f,24nov09,v_r  Mods for P4080 36bits support (CQ:WIND00174166):
		 + added support for 64-bit load bias and physical addresses.
		 + added CPU-specific routines support.
		 + added custom version of strtoll().
01e,23oct08,kab  Update sysAmpCpuPrep to new sig per design mod
01d,16oct08,kab  Add wrloadTgtCpuPrep,
                 modify wrloadTgtSymbolsRegister to distinguish internal use
01c,08aug08,mak  Ci updates
01b,24jul08,mak  tree re-org
01a,08feb08,mak  written.
*/

#ifndef	__INCwrloadPh
#define	__INCwrloadPh

#endif	/* __INCwrloadPh */

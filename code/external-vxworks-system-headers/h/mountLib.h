/* mountLib.h - Mount protocol library header */

/*
 * Copyright (c) 1994, 1999-2001, 2004, 2006 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
01h,19sep06,mwv  update nfs include path (WIND00065965)
01g,01jul04,dlk  Made this file include "mountd.h", and removed other contents.
01f,06nov01,vvv  made max. path length configurable (SPR #63551)
01e,10oct01,rae  update copyright
01d,21jun00,rsh  upgrade to dosFs 2.0
01d,21sep99,jkf  changed nameToInode for nfsHash approach.
01c,25apr94,jmm  added S_mountLib_ILLEGAL_MODE; changed mode to readOnly 
01b,21apr94,jmm  added MOUNTD_ARGUMENT; prototype cleanup
01a,31mar94,jmm  written.
*/

#ifndef __INCmountLibh
#define __INCmountLibh

#if 0
#error mountLib.h is obsolete, use mountd.h instead
#endif

#include <nfs/mountd.h>

#endif /* __INCmountLibh */

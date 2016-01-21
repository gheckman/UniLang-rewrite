/* dcr4xxALib.h - DCR access assembly routines				      */

/*
*******************************************************************************
   This source and object code has been made available to you by IBM on an
   AS-IS basis.

   IT IS PROVIDED WITHOUT WARRANTY OF ANY KIND, INCLUDING THE WARRANTIES OF
   MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE OR OF NONINFRINGEMENT
   OF THIRD PARTY RIGHTS.  IN NO EVENT SHALL IBM OR ITS LICENSORS BE LIABLE
   FOR INCIDENTAL, CONSEQUENTIAL OR PUNITIVE DAMAGES.  IBM'S OR ITS LICENSOR'S
   DAMAGES FOR ANY CAUSE OF ACTION, WHETHER IN CONTRACT OR IN TORT, AT LAW OR
   AT EQUITY, SHALL BE LIMITED TO A MAXIMUM OF $1,000 PER LICENSE.  No license
   under IBM patents or patent applications is to be implied by the copyright
   license.

   Any user of this software should understand that neither IBM nor its
   licensors will be responsible for any consequences resulting from the use
   of this software.

   Any person who transfers this source code or any derivative work must
   include the IBM copyright notice, this paragraph, and the preceding two
   paragraphs in the transferred software.

   Any person who transfers this object code or any derivative work must
   include the IBM copyright notice in the transferred software.

   COPYRIGHT   I B M   CORPORATION 2000
   LICENSED MATERIAL  -  PROGRAM PROPERTY OF  I B M

****************************************************************************
\NOMANUAL
*/

/*
 * Copyright (c) 2007-2008 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01b,20mar08,b_m  rename to dcr4xxALib.h
01a,27feb07,rcs  ported from amcc440ep BSP 
*/

/*
This file contains the definitions of input and output functions for
accessing Device Control Registers.
*/

#ifndef INCdcr4xxh
#define INCdcr4xxh

#ifdef __cplusplus
    extern "C" {
#endif

#ifndef _ASMLANGUAGE

UINT32	dcrInLong(UINT32);
void	dcrOutLong(UINT32,UINT32);

/* TEMPORARY HACK for msync/mbar in PPC440gnu */
/*
 * Done here because this .h file (and only this .h file) is shared
 * among all PPC440 BSP's, hence the change can be made -- and later
 * removed -- in just one place to cover all of them.
 */
#ifdef	EIEIO_SYNC
#undef	EIEIO_SYNC
#define	EIEIO_SYNC _WRS_ASM(" eieio; sync")
#endif	/* EIEIO_SYNC */
#ifdef	EIEIO
#undef	EIEIO
#define	EIEIO _WRS_ASM(" eieio")
#endif	/* EIEIO */
#ifdef	SYNC
#undef	SYNC
#define	SYNC _WRS_ASM(" sync")
#endif	/* SYNC */
/* end of TEMPORARY HACK */

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
    }
#endif

#endif	/* INCdcr4xxh */

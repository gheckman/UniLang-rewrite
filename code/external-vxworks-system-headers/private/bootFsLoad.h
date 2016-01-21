/* bootFsLoad.h - Bootrom Application Filesystem Load Support */

/* 
*  Copyright (c) 2005,2007-2009 Wind River Systems, Inc.
* 
* The right to copy, distribute, modify or otherwise make use
* of this software may be licensed only pursuant to the terms
* of an applicable Wind River license agreement.
*/

/*
modification history
--------------------
01d,16dec09,pgh  64-bit conversion
01c,02dec08,pgh  Add prototype for bootFsLoad().
01b,06feb07,jmt  Add default file load routine
01a,12may05,jmt   written
*/

/*
DESCRIPTION
This module holds the vxWorks Bootrom Application Filesystem Load Support routines.

INCLUDE FILES: 
*/ 

#ifndef INCbootFsLoadh
#define INCbootFsLoadh

/* defines */

/* typedefs */

/* global function declarations */

void devSplit (FAST char *fullFileName, FAST char *devName);
STATUS bootFsFileLoad (char *fileName, void **pEntry);
STATUS bootFsLoad (char *, void **);

#endif /* INCbootFsLoadh */

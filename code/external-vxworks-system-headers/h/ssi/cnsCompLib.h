/* cnsCompLib.h - Media type comp library header file */

/* Copyright 2005 Wind River Systems, Inc. */

/* 
Modification History
--------------------
01c,06jan06,tkf Removed all cnsComp* function prototypes.
01b,19dec05,xli Added the cnsCompIoctl API
01a,25nov05,xli  Written.
*/

/*
DESCRIPTION

This file contains the definitions for the cnsCompLib library (cnsCompLib). 
across memory boundaries on a single node.    
*/

#ifndef __INCcnsCompLibh
#define __INCcnsCompLibh

#ifdef  __cplusplus
extern "C" {
#endif /* __cplusplus */

IMPORT STATUS cnsCompLibInit ();

#ifdef  __cplusplus
}
#endif /* __cplusplus */

#endif  /* __INCcnsCompLibh */
  

/* unLib.h - AF_LOCAL domain initialization header file */

/* Copyright 2003-2005, 2010 Wind River Systems, Inc. */

/*
modification history
--------------------
01e,29apr10,pad  Moved extern C statement after include statements.
01d,04jan05,bwa  removed 'Inst' part of init routine names (SPR#103232).
01c,24feb04,bwa  added PROTOCOL_SWITCH_FULL definition
01b,26nov03,bwa  moved protos/unCompLib.h errno definitions here
01a,10oct03,bwa  written
*/

#ifndef __INCunLibh
#define __INCunLibh

#include <vwModNum.h>

#ifdef __cplusplus
extern "C" {
#endif

     
/* errnos */

#define S_unLib_ALREADY_INITIALIZED          (M_unLib | 0x0001)
#define S_unLib_COMP_ALREADY_INITIALIZED     (M_unLib | 0x0002)
#define S_unLib_PROTOCOL_SWITCH_FULL         (M_unLib | 0x0003)

/* function prototypes */

STATUS unInit (void * pInitValues);

#ifdef __cplusplus
}
#endif
    
#endif  /* __INCunLibh */


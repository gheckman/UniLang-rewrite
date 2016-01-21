/* unCompLib.h - AF_LOCAL/COMP protocol initialization header file */

/* Copyright 2003-2005 Wind River Systems, Inc. */

/*
modification history
--------------------
01c,04jan05,bwa  removed 'Inst' part of init routine names (SPR#103232).
01b,26nov03,bwa  moved errno definitions to netinet/unLib.h
01a,05nov03,bwa  written
*/

#ifndef __INCunCompLibh
#define __INCunCompLibh

#ifdef __cplusplus
extern "C" {
#endif

/* function prototypes */

STATUS unCompInit (void * pInitValues);

#ifdef __cplusplus
}
#endif
    
#endif  /* __INCunCompLibh */


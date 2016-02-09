/* wdbDynPrintfLib.h - WDB dynamic printf support library */

/*
 * Copyright (c) 2008 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01a,18jul08,dbt	 created
*/

#ifndef __INCwdbDynPrintfLibh
#define __INCwdbDynPrintfLibh

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

/* dynamic printf output option */

#define	WDB_DPRINTF_VERBOSE	1

/* function declarations */

extern STATUS wdbDynPrintfBpValidate (long arg);
extern STATUS wdbDynPrintfExprEval (long arg, char * buffer, size_t size,
					void * pRegisters,
					long pid, int * pOptions); 

#ifdef __cplusplus
}
#endif

#endif /* __INCwdbDynPrintfLibh */

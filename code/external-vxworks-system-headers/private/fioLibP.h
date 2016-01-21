/* fioLibP.h - header for formatted i/o library */

/*
 * Copyright (c) 2005, 2009-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01e,16sep10,mcm  Updated prototype of fioBufPrint to use size_t instead of int
01d,29apr10,pad  Moved extern C statement after include statements.
01c,15sep09,mcm  Fixing up printExc's arguments
01b,26mar09,mcm  Updates for the LP64 data model
01a,27Jul05,rhe  written
*/

#ifndef __INCfioLibPh
#define __INCfioLibPh

/* includes */
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif


/* defines */
#define FIO_HEX_X_SUPPORT	    /* fioFormatv support for %X */
#define FIO_OCT_SUPPORT             /* fioFormatv support for %o */

#define NSIZE 16

#define FIO_HEX 16
#define FIO_OCT 8
#define FIO_DEC 10

/*
 * Choose PADSIZE to trade efficiency vs size.  If larger printf fields occur
 * frequently, increase PADSIZE (and make the initialisers below longer).
 */
  
#define	PADSIZE		16		/* pad chunk size */
 
#ifndef _ASMLANGUAGE
 
/* typedefs */

typedef struct snputbuf_arg     /* used by snprintf(), snputbuf() snprintf() */
    { 
    char *pBuf;                 /* running pointer to the next char */
    char *pBufEnd;              /* pointer to buffer end */
    } SNPUTBUF_ARG;
		
/* function declarations */

typedef enum fio_state
    {
    FIO_STATE_COLLECT =  0,     /* Collect text rfrom the format string */
    FIO_STATE_TYPE_BASIC        /*     c d             i   o p s u X x % support */
    } FIO_STATE;

extern STATUS fioBufPut (char *inbuf, int length, char ** outptr);
extern STATUS fioBufPrint (char *buf, size_t nbytes, int fd);
extern STATUS fioSnBufPut (char *pInBuf, int length, SNPUTBUF_ARG *pArg);
extern void   printExc (char* fmt, _Vx_usr_arg_t arg1, _Vx_usr_arg_t arg2, 
                        _Vx_usr_arg_t arg3, _Vx_usr_arg_t arg4, 
                        _Vx_usr_arg_t arg5);
#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCfioLibh */


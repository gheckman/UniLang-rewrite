/* excLibP.h - private exception handling subsystem header file */

/* 
 * Copyright (c) 1984-2006, 2009-2010 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
01i,20sep10,jpb  Added exception handling function pointers.
01h,08apr10,jpb  Added func binding prototypes.
01g,26mar09,zl   updated for LP64 build. Moved jobAdd() to jobLibP.h,
                 removed jobExcAdd().
01f,17oct06,gls  made maxIsrJobs argument a UINT (Defect #00059580)
01e,07jun05,yvp  Added prototype for jobAdd(). Updated copyright.
01d,09mar05,yvp  Added ISR_JOB definition.
01c,20jan05,yvp  Reverted prototype for excInit().
01b,25aug04,ans  updated declaration of excInit()
01a,13nov01,yvp  created.
*/

#ifndef __INCexcLibPh
#define __INCexcLibPh

#ifdef __cplusplus
extern "C" {
#endif

#ifndef	_ASMLANGUAGE

/* defines */

#define ISR_JOB_MAX_ARGS     6

/* typedefs */

/* Structure describing ISR-level job deferral */

typedef struct
    {
    VOIDFUNCPTR	  func;                   /* pointer to function to invoke */
    _Vx_usr_arg_t arg [ISR_JOB_MAX_ARGS]; /* args for function */
    } ISR_JOB;

/* Select extended (32-bit) calls from the vector table to handlers */

extern BOOL excExtendedVectors;

/* function declarations */

extern STATUS 	excVecInit (void);
extern STATUS 	excInit    (UINT maxIsrJobs);

/* function pointer prototypes */

extern STATUS  (*_func_excJobAdd)(VOIDFUNCPTR func,
				  _Vx_usr_arg_t arg1, _Vx_usr_arg_t arg2,
				  _Vx_usr_arg_t arg3, _Vx_usr_arg_t arg4, 
				  _Vx_usr_arg_t arg5, _Vx_usr_arg_t arg6);

/* TODO: Keep these as 'FUNCPTR' for now but they should be made fully typed */

extern FUNCPTR     _func_excInfoShow;
extern FUNCPTR     _func_excPanicHook;
extern FUNCPTR     _func_excBaseHook;
extern FUNCPTR     _func_excIntHook;
extern FUNCPTR     excExcepHook;

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCexcLibPh */

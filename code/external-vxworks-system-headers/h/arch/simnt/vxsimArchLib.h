/* vxsimArchLib.h - header for VxSim architecture library */

/* Copyright 2003 Wind River Systems, Inc. */
#include "copyright_wrs.h"

/*
modification history
--------------------
01b,28mar03,jmp  added vxsimExceptionDispatch.
01a,30jan03,jmp  written.
*/

#ifndef __INCvxsimArchLibh
#define __INCvxsimArchLibh

extern void	vxsimExceptionDispatch	(EXC_INFO * pExcInfo, REG_SET * pRegs);

#endif	/* __INCvxsimArchLibh */

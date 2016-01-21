/* excSimsolaris.h - simsolaris exception library header */

/* Copyright 1993-2004 Wind River Systems, Inc. */

/*
modification history
--------------------
01d,10mar04,dbt  Fixed _WRS_IS_SUP_EXC() macro.
01c,09feb04,jmp  added _WRS_IS_SUPV_EXC() macro.
01b,21oct03,jmp  file cleanup.
01a,07jun95,ism  derived from simsparc
*/

#ifndef __INCexcSimsolarisLibh
#define __INCexcSimsolarisLibh

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ASMLANGUAGE

/* defines */

#define _WRS_IS_SUPV_EXC()	VXSIM_SUP_MODE_GET(pRegs->reg_status)

/* variable declarations */

extern FUNCPTR  excExcepHook;   /* add'l rtn to call when exceptions occur */

/* typedefs */

typedef struct
    {
    UINT32	valid;		/* Indicators that following fields are valid */
    UINT32	pc;		/* Program counter                            */
    UINT32	npc;		/* Next program counter			      */
    UINT32	ps;		/* Processor status			      */
    UINT32	sig;		/* signal number			      */
    UINT32	code;		/* Signal code				      */
    UINT32	addr;		/* Memory location which caused fault         */
    UINT32	ptcb;
    } EXC_INFO;

#endif  /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCexcSimsolarisLibh */

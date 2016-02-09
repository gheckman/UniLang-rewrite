/* excSimlinuxLib.h - simlinux exception library header */

/* Copyright 1993-2004 Wind River Systems, Inc. */

/*
modification history
--------------------
01f,21may10,elp  64bits support.
01e,10mar04,dbt  Fixed _WRS_IS_SUP_EXC() macro.
01d,09feb04,jmp  added _WRS_IS_SUPV_EXC() macro.
01c,21oct03,jmp  renamed some fields of EXC_INFO to share code with
                 simsolaris.
01b,17apr03,dbt  Adapted for VxWorks 5.x
01a,05sep00,hbh  derived from simsolaris
	   +jmp
*/

#ifndef __INCexcSimlinuxLibh
#define __INCexcSimlinuxLibh

#ifndef HOST
#include <arch/simlinux/archSimlinux.h>
#endif	/* !HOST */

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
    UINT32	valid;		/* indicators that following fields are valid */
    UINT32	sig;		/* signal number			      */
    UINT32	code;		/* Signal code				      */
    VXSIM_ULONG	addr;		/* Memory location which caused fault	      */
    UCHAR *	pc;		/* program counter			      */
    } EXC_INFO;

#endif  /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCexcSimlinuxLibh */

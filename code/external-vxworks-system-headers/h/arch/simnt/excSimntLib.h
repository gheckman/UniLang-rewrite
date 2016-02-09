/* excSimntLib.h - exception library header */

/*
 * Copyright (c) 1998,2000,2003,2004,2006,2007,2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this
 * software may be licensed only pursuant to the terms of an applicable
 * Wind River license agreement.
 */

/*
modification history
--------------------
01i,21may10,elp  64bits support.
01h,19jun07,elp  added access violation type macros.
01g,08nov06,elp  can be included in assembly file
01f,10mar04,dbt  Fixed _WRS_IS_SUP_EXC() macro.
01e,09feb04,jmp  added _WRS_IS_SUPV_EXC() macro.
01d,21oct03,jmp  replaced padding field of EXC_INFO by access type.
01c,28mar03,jmp  added exception numbers.
		 replaced INSTR by UCHAR to use this file from host side.
01b,30may00,elp  renamed errCode in accessAddr.
01a,29apr98,cym  written based x86 version.
*/

#ifndef __INCexcSimntLibh
#define __INCexcSimntLibh

#ifndef HOST
#include <arch/simnt/archSimnt.h>
#endif /* !HOST */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ASMLANGUAGE
/* typedefs */

typedef struct
    {
    UINT16	valid;		/* indicators that following fields are valid */
    UINT16	vecNum;		/* vector number */
    VXSIM_ULONG	accessAddr;	/* access address */
    UCHAR *	pc;		/* program counter */
    UINT32	statusReg;	/* status register */
    UINT16	csReg;		/* code segment register */
    UINT16	accessType;	/* type of access (read or write) */
    } EXC_INFO;
#endif /* _ASMLANGUAGE */

/* defines */

#define _WRS_IS_SUPV_EXC()	VXSIM_SUP_MODE_GET(pRegs->reg_status)

#define LOW_VEC		0		/* lowest initialized vector */
#define HIGH_VEC	0xff		/* highest initialized vector */

/* exception info valid bits */

#define EXC_VEC_NUM		0x01	/* vector number valid */
#define EXC_ACCESS_READ		0x02	/* accessAddr is valid (READ access) */
#define EXC_ACCESS_WRITE	0x04	/* accessAddr is valid (WRITE access) */
#define EXC_PC			0x08	/* pc valid */
#define EXC_STATUS_REG		0x10	/* status register valid */
#define EXC_CS_REG		0x20	/* code segment register valid */
#define EXC_INVALID_TYPE	0x80	/* special indicator: ESF type was bad;
					 * type is in funcCode field */

/* access violation type */

#define EXC_READ_ACCESS		0	/* read access violation */
#define EXC_WRITE_ACCESS	1	/* write access violation */
#define EXC_EXEC_ACCESS		8	/* execute access violation */

/* exception numbers */

#define EXC_INT_DIVIDE_BY_ZERO		0
#define EXC_SINGLE_STEP			1
#define EXC_DATATYPE_MISALIGNMENT	2
#define EXC_BREAKPOINT			3
#define EXC_IN_PAGE_ERROR		4
#define EXC_ILLEGAL_INSTRUCTION		5
#define EXC_INVALID_DISPOSITION		6
#define EXC_ARRAY_BOUNDS_EXCEEDED	7
#define EXC_FLT_DENORMAL_OPERAND	8
#define EXC_FLT_DIVIDE_BY_ZERO		9
#define EXC_FLT_INEXACT_RESULT		10
#define EXC_FLT_INVALID_OPERATION	11
#define EXC_FLT_OVERFLOW		12
#define EXC_ACCESS_VIOLATION		13
#define EXC_FLT_STACK_CHECK		14
#define EXC_FLT_UNDERFLOW		15
#define EXC_INT_OVERFLOW		16
#define EXC_PRIV_INSTRUCTION		17
#define EXC_STACK_OVERFLOW		18
#define EXC_UNKNOWN			19

#ifndef _ASMLANGUAGE
/* variable declarations */

extern FUNCPTR  excExcepHook;   /* add'l rtn to call when exceptions occur */

/* function declarations */

extern void	excStub (void);
extern void	excIntStub (void);

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCexcSimntLibh */

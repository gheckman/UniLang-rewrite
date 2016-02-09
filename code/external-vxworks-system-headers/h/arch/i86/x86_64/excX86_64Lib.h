/* excX86_64Lib.h - exception library header */

/*
 * Copyright 2009, 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01c,25jun12,pad  Added missing exception macro definitions (part of fix for
                 defect #353696).
01b,23feb09,jb   Initial port to 64-bits
01a,26jan09,jb   Created from 32-bit version
*/

#ifndef __INCexcX86_64Libh
#define __INCexcX86_64Libh

#ifdef __cplusplus
extern "C" {
#endif

/* lowest and highest vector number to initialize */

#define LOW_VEC		0		/* lowest initialized vector */
#define HIGH_VEC	0xff		/* highest initialized vector */

/* ESF Pointer for exception handler */

#define ESF_EXCBASE            0x90


#ifndef	_ASMLANGUAGE

typedef struct
    {
    UINT16 valid;	/* indicators that following fields are valid */
    UINT16 vecNum;	/* vector number */
    ULONG errCode;	/* error code */
    INSTR * pc;		/* program counter */
    ULONG rflags;	/* rflags register */
    UINT16 cs;		/* code segment register */
    UINT16 pad;		/* pad to four byte boundary */
    ULONG esp;		/* stack pointer in the ESF */
    ULONG ss;		/* stack segment in the ESF */
    ULONG esp0;		/* supervisor (PL0) stack pointer */
    ULONG cr2;		/* CR2 */
    ULONG cr3;		/* CR3 */
    ULONG esp00;	/* content of the stack *(esp0 + 0) */
    ULONG esp01;	/* content of the stack *(esp0 + 1) */
    ULONG esp02;	/* content of the stack *(esp0 + 2) */
    ULONG esp03;	/* content of the stack *(esp0 + 3) */
    ULONG esp04;	/* content of the stack *(esp0 + 4) */
    ULONG esp05;	/* content of the stack *(esp0 + 5) */
    ULONG esp06;	/* content of the stack *(esp0 + 6) */
    ULONG esp07;	/* content of the stack *(esp0 + 7) */
    ULONG reserved0;	/* reserved 0 */
    ULONG reserved1;	/* reserved 1 */
    ULONG reserved2;	/* reserved 2 */
    ULONG reserved3;	/* reserved 3 */
    } EXC_INFO;

#define _WRS_IS_SUPV_EXC() (((excInfo.cs & 0x3) == 0) ? TRUE : FALSE)

/* exception info valid bits */

#define EXC_VEC_NUM		0x01	/* vector number valid */
#define EXC_ERROR_CODE		0x02	/* error code valid */
#define EXC_ESP_SS		0x04	/* ESP and SS valid */
#define EXC_CR2			0x08	/* CR2 valid */
#define EXC_FP_CONTEXT		0x10	/* FP_CONTEXT valid */
#define EXC_INVALID_TYPE	0x80	/* special indicator: ESF type was bad;
					 * type is in funcCode field */

/* exception vector number */

#define EXC_DIVIDE_ERROR              0x00      /* divide error */
#define EXC_DEBUG                     0x01      /* debug */
#define EXC_NMI                       0x02      /* NMI */
#define EXC_INT3                      0x03      /* breakpoint */
#define EXC_OVERFLOW                  0x04      /* overflow */
#define EXC_BOUNDS_CHECK              0x05      /* bounds check */
#define EXC_INVALID_OPCODE            0x06      /* invalid opcode */
#define EXC_DEVICE_NOT_AVAILABLE      0x07      /* device not available */
#define EXC_DOUBLE_FAULT              0x08      /* double fault */
#define EXC_COPROC_OVERRUN            0x09      /* coprocessor segment overrun */
#define EXC_INVALID_TSS               0x0a      /* invalid TSS */
#define EXC_SEGMENT_NOT_PRESENT       0x0b      /* segment not present */
#define EXC_STACK_SEGMENT_FAULT       0x0c      /* stack segment fault */
#define EXC_GENERAL_PROTECTION        0x0d      /* general protection */
#define EXC_PAGE_FAULT                0x0e      /* page fault */
#define EXC_RESERVED                  0x0f      /* Intel-reserved */
#define EXC_FP_ERROR                  0x10      /* Floating-point error */
#define EXC_ALIGNMENT_CHECK           0x11      /* alignment check */
#define EXC_MACHINE_CHECK             0x12      /* machine check */
#define EXC_SIMD_ERROR                0x13      /* SIMD Float exception */

/* variable declarations */

extern FUNCPTR  excExcepHook;   /* add'l rtn to call when exceptions occur */

/* function declarations */

#if defined(__STDC__) || defined(__cplusplus)

extern void	excStub (void);
extern void	excStub0 (void);
extern void	excStub1 (void);
extern void	excIntStub (void);

#else	/* __STDC__ */

extern void	excStub ();
extern void	excStub0 ();
extern void	excStub1 ();
extern void	excIntStub ();

#endif	/* __STDC__ */

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCexcX86_64Libh */

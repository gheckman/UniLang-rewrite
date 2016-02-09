/* asmArm.h - ARM assembler definitions header file */

/*
 * Copyright (c) 1996, 2004, 2010, 2012, 2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01g,20feb13,yjw  add macros to support Thumb-2
01f,16oct12,jdw  Add SPSR set macro (WIND00259770)
01e,18jan12,rec  WIND00329076 - add FUNC_END, cleanup macros to be consistent
                 with other arch defines.  Remove THUMB support.
01d,09jan12,jdw  Add macro definitions for pld instructions
01c,21may10,m_h  Thumb-2 Support
01b,06jul04,md   added function definition macros
01a,09may96,cdp  created
*/

#ifndef	__INCasmArmh
#define	__INCasmArmh

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _ASMLANGUAGE

#ifdef __GNUC__
	.syntax unified
#endif

/* Build for Gnu elf or Diab compiler */
/* useful, assembly-language macros */
#define FUNC(a) a
#define VAR(name) name

/*
 * These macros are used to declare assembly language symbols that need
 * to be typed properly(func or data) to be visible to the OMF tool.  
 * So that the build tool could mark them as an entry point to be linked
 * correctly.  
 */

#ifdef __DCC__
 #if ARM_THUMB2
 #define GTEXT(sym) FUNC(sym) ;  .type   FUNC(sym),@tfunc
 #else /* ARM_THUMB2 */
 #define GTEXT(sym) FUNC(sym) ;  .type   FUNC(sym),@function
 #endif /* ARM_THUMB2 */
 #define GDATA(sym) VAR(sym) ;  .type   VAR(sym),@object
#elif (defined __GNUC__) /* GNU macros */
 #define GTEXT(sym) FUNC(sym) ;  .type   FUNC(sym),STT_FUNC
 #define GDATA(sym) VAR(sym) ;  .type   VAR(sym),STT_OBJECT
#else /* neither __DCC__ nor __GNUC__ */
 #error "error!!! unsupported compiler!!!"
#endif /* __DCC__ */

/* abstract assembler idiosyncrasies */

#define FUNC_LABEL(func)        func:
#define VAR_LABEL(name)         name:

#define	FUNC_EXPORT(func)	.globl	GTEXT(func)
#define	DATA_EXPORT(var)	.globl	GDATA(var)
#define	FUNC_IMPORT(func)	.extern	FUNC(func)
#define	DATA_IMPORT(var)	.extern	VAR(var)
#define	FUNC_END(func)		.size	FUNC(func), . - FUNC(func)


#if ((!defined __GNUC__) && (!defined __DCC__))
 #error "error!!! unsupported assembler!!!"
#endif /* (defined __GNUC__) && (!defined __DCC__) */

/* 
 * The DCC assembler has problems with spaces before the function label.
 * To avoid assembler parse problems, the FUNC_LABEL macros below are 
 * not indented.
 */
 
#if ARM_THUMB2
#if (defined __GNUC__)
 #define	FUNC_BEGIN(func) \
    .thumb;\
    .thumb_func;\
    .balign 4;\
FUNC_LABEL(func)
#else /* !__GNUC__ */
 #define	FUNC_BEGIN(func) \
    .thumb;\
    .balign 4;\
FUNC_LABEL(func)
#endif /* __GNUC__ */
#else /* !ARM_THUMB2 */
 #define	FUNC_BEGIN(func) \
     .code 32;\
     .balign	4;\
FUNC_LABEL(func)
#endif /* ARM_THUMB2 */

/*
 * The following two macros are deprecated. Definitions are provided for
 * backward compatibility.
 */ 
 
#define _ARM_FUNCTION_CALLED_FROM_C FUNC_BEGIN
#define _ARM_FUNCTION FUNC_BEGIN

/* Define macros to use the PLD instruction on ARM v7 processors */        
#if (CPU == ARMARCH7 || CPU == ARMARCH7_T2)
#define PLD(...)  pld     __VA_ARGS__
#else
/* if not ARM v7, do nothing */
#define PLD(...)
#endif         

#if (CPU == ARMARCH7M)
/*
 * Macro to perform a 32-bit MOV operation, using the ARMv7-M encoding of the
 * MOV and MOVT instructions to copy the lower and upper 16-bits of a 32-bit
 * constant to a register.
 */ 

#define _ARM_M_MOV32(reg, val) \
        LDR reg, =val
		
/* External interrupt toggle */		
		
#define INT_LOCK          \
        PUSH {r0};        \
	MOV  r0, #0x10;   \
        MSR  basepri, r0; \
	POP  {r0}
	
#define INT_UNLOCK        \
        PUSH {r0};        \
	MOV  r0, #0x00;   \
        MSR  basepri, r0; \
	POP  {r0}
		
#endif /* CPU == ARMARCH7M */

#define TEMP_STACK_ADR 0x20000800	

/*
 * The SPSR has changed and additional bits have been added as newer ARM
 * architecture versions have been released. The new bit definitions are
 * marked as RAZ/SBZP in older architecture revisions and shouldn't be
 * modified. Newer versions of the Diab compiler have changed the behavior of
 * the 'MSR spsr, <reg>' operation and no longer assumes modification of only
 * spsr_cf fields when specific mask fields are not specified. GCC translates
 * 'MSR spsr, <reg>' to only modify spsr_cf fields by default, if specific
 * fields are not specified. See the ARM Architecture Reference Manual for
 * definitions of the SPSR fields and MSR instruction behavior. 
 * 
 * The _ARM_SPSR_SET() macro abstracts arch and compiler issues from common
 * code.
 */
#if (CPU != ARMARCH7M)
#if ((_VX_CPU == _VX_ARMARCH7) || (_VX_CPU == _VX_ARMARCH7_T2))

/* 
 * For ARMv7 (ARM & Thumb2) SPSR <23:20> are RAZ/SBZP, all others are
 * defined... Write all bits.
 */

#define _ARM_SPSR_SET(reg) \
	MSR	spsr_cxsf, reg

#else /* ((_VX_CPU == _VX_ARMARCH7) || (_VX_CPU == _VX_ARMARCH7_T2)) */

/* 
 * For ARMv4, ARMv5, & ARMv6 architectures only the 'c' (bits <7:0>) and 'f'
 * (bits <31:24>) fields are restored in order to remain consistent with
 * earlier versions of VxWorks and older Diab compiler revisions.
 *
 *   NOTES: 
 *         1) The IMX31 may crash if reserved SPSR bits are modified,
 *            see WIND00253307 for details
 *         2) For ARMARCH6 the GE[3:0] bits (SPSR <19:16>) are not preserved
 *            because VxWorks does not support SIMD instructions
 */

#define _ARM_SPSR_SET(reg) \
	MSR	spsr_cf, reg

#endif /* ((_VX_CPU == _VX_ARMARCH7) || (_VX_CPU == _VX_ARMARCH7_T2)) */

#endif /* CPU != ARMARCH7M */

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif	/* __INCasmArmh */

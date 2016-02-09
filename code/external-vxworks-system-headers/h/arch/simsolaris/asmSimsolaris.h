/* asmSimsolaris.h - VxSim/Solaris assembler definitions header */

/*
 * Copyright (c) 1995,1999,2000,2003,2008 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01f,26mar08,dbt  Added FUNC_BEGIN & FUNC_END macros (Defect WIND00066731).
01e,05mar03,jeg  Updated __INC macro
01d,23feb00,bwa  put back TRUE and FALSE. for them to be initialized, 
                 _ASMLANGUAGE has to be defined in the file were this file
                 is included 
01c,01feb00,bwa  replaced TRUE and FALSE by 1 and 0 since they are not defined
		 here
01b,01dec99,aeg  added FUNC, FUNC_LABEL, GTEXT, and GDATA macros.
01a,07jun95,ism  derived from simsparc
*/

#ifndef __INCasmSimsolaris
#define __INCasmSimsolaris


/*
 * The LEADING_UNDERSCORE macro should be defined to TRUE for toolchains
 * that do NOT prefix a leading underscore character, i.e. "_", to
 * symbols.  Define the macro to FALSE when using a toolchain that
 * does add a leading underscore character to symbols.
 */

#define LEADING_UNDERSCORE FALSE 

#if (LEADING_UNDERSCORE == TRUE)
#define FUNC(func)          _##func
#define FUNC_LABEL(func)    _##func:
#else
#define FUNC(func)          func
#define FUNC_LABEL(func)    func:
#endif
 

/*
 * The GTEXT and GDATA macros should be used to ensure the proper
 * symbol type is associated with a function or data label.  This
 * is an ELFism.
 */

#define GTEXT(sym) FUNC(sym) ;  .type   FUNC(sym),@function
#define GDATA(sym) FUNC(sym) ;  .type   FUNC(sym),@object

/* Introduced to abstract assembler idiosyncrasies */

#define	FUNC_BEGIN(func)	FUNC_LABEL(func)
#define	FUNC_END(func)		.size	FUNC(func), . - FUNC(func)

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif /* __INCasmSimsolaris*/

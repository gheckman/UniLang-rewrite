/* archMipsCommon.h - common Mips architecture specific header */

/*
 * Copyright (c) 2003-2004, 2006-2007, 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
 * This file has been developed or significantly modified by the
 * MIPS Center of Excellence Dedicated Engineering Staff.
 * This notice is as per the MIPS Center of Excellence Master Partner
 * Agreement, do not remove this notice without checking first with
 * WR/Platforms MIPS Center of Excellence engineering management.
 */

/*
modification history
--------------------
01o,21mar12,jpb  Updated for POSIX namespace isolation conformance (part of 
                 defect Defect WIND000307800).
01n,09aug07,pad  _VX_CPU_MIPS_64BIT and _VX_CPU_MIPS_32BIT were not defined
                 when _POSIX_C_SOURCE was defined by the applications. This is
                 now fixed.
01m,11jul07,zl   added _WRS_CPU_HAS_CLZ_INSTR.
01l,04may07,zl   updated portable library build configuration.
01k,21feb07,pes  Add support for new MIPS lib structure.
01j,26jun06,jpb  Updated for POSIX namespace conformance.
		 Changed C preprocessor macro CPU to _VX_CPU.
01i,02feb06,mil  Updated for POSIX namespace conformance.
01h,30sep04,pes  added define of _WRS_NO_BITS_PHYS_ADDR
01g,01oct04,tam  moved definition of _TYPE_PHYS_ADDR to the kernel
                 architecture scpecific header
01f,17sep04,pes  moved _TYPE_PHYS_ADDDR and _WRS_PHYS_ADDR_IS_64_BITS here
                 from archMips.h
01e,22mar04,zl   moved trcLib_PORTABLE, _RType and INSTR definitions here.
01d,17mar04,pes  Enable Coprocessor Abstraction
01c,25nov03,pes  Moved definition of _BYTE_ORDER to archMipsCommon.h.
01b,12nov03,job  Moved some blib stuff from archMips.h
01a,11nov03,pes  written.
*/

#ifndef __INCarchMipsCommonh
#define __INCarchMipsCommonh

#ifdef __cplusplus
extern "C" {
#endif

#if defined(MIPSEB) || defined(__MIPSEB__)
#undef _BYTE_ORDER
#define	_BYTE_ORDER             _BIG_ENDIAN
#elif defined(MIPSEL) || defined(__MIPSEL__)
#undef _BYTE_ORDER
#define	_BYTE_ORDER		_LITTLE_ENDIAN
#else
#warning "One of MIPSEL or MIPSEB must be defined"
#endif

#define _WRS_PAL_COPROC_LIB		/* enable coprocessor abstraction */

/* from bLib.c */

#define _WRS_BLIB_ALIGNMENT     3       /* quad byte alignment mask */

/* 
 * CLZ instruction (used for ffsMsb and ffsLsb) not supported 
 * by MIPSI2 and MIPSI3 
 *
 * IMPORTANT: this must be conditional on ISA level, and not variant level
 */

#if (_VX_CPU != _VX_MIPSI2) && (_VX_CPU != _VX_MIPSI3)
#define _WRS_CPU_HAS_CLZ_INSTR
#endif /* !_VX_MIPSI2 && !_VX_MIPSI3 */

/* 32/64 bit */

#define _VX_CPU_MIPS_32BIT ((_VX_CPU==_VX_MIPS32) || \
			    (_VX_CPU==_VX_MIPSI2) || \
			    (_VX_CPU==_VX_MIPSI32) || \
			    (_VX_CPU==_VX_MIPSI32R2))

#define _VX_CPU_MIPS_64BIT ((_VX_CPU==_VX_MIPS64) || \
			    (_VX_CPU==_VX_MIPSI3) || \
			    (_VX_CPU==_VX_MIPSI64) || \
			    (_VX_CPU==_VX_MIPSI64R2))

#ifndef _ASMLANGUAGE

typedef unsigned long _Vx_INSTR;        /* 32 bit word-aligned instructions */

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
typedef _Vx_INSTR	INSTR;	
#endif  /* !_POSIX_xxx_SOURCE */

#if	(_VX_CPU_MIPS_32BIT)
typedef unsigned long _RType;		/* registers are 32 bits */
#elif	(_VX_CPU_MIPS_64BIT)
typedef unsigned long long _RType;	/* registers are 64 bits */
#else	/* _VX_CPU_MIPSxxBIT */
#error "Invalid CPU value"
#endif	/* _VX_CPU */

#endif	/* !_ASMLANGUAGE */

#define _WRS_NO_BITS_PHYS_ADDR	64


#ifdef __cplusplus
}
#endif

#endif /* __INCarchMipsCommonh */


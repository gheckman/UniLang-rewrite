/* vxArch.h - architecture header */

/*
Copyright (c) 1992-1998,2000,2001,2003-2006,2009-2010 Wind River Systems, Inc.

The right to copy, distribute, modify or otherwise make use
of this software may be licensed only pursuant to the terms
of an applicable Wind River license agreement.
*/

/*
modification history
--------------------
02p,28sep10,sem  Update IA arch includes
02o,16sep10,gls  moved VX_OBJ_ALIGN_SIZE to architecture header file
02n,18may10,pad  Moved extern C statement after include statements.
02m,11dec09,pad  Replaced CORE2 and X86_64 with _VX_CORE2 and _VX_X86_64 in
                 order to support the POSIX namespace isolation.
02l,23jul09,mze  remove PAD64
02k,19jun09,mze  replacing PAD64
02j,24feb09,pcs  Resolve build error. Change CPU to _VX_CPU.
02i,18feb09,jb  Adding 64-bit support
02h,02jun08,jpb  Removed #defines of _WRS_CONFIG_SV_INSTRUMENTATION.
02g,12may08,jpb  Modifications for source build.  Renamed 
                 WV_INSTRUMENTATION to _WRS_CONFIG_SV_INSTRUMENTATION.
02f,08aug06,pch  move VX_MAX_SMP_CPUS to private/vxSmpP.h
02e,17jul06,mmi  Added VX_MAX_SMP_CPUS
02e,18may06,jpb  Updated for POSIX namespace conformance.  
		 Changed C preprocessor macro CPU to _VX_CPU.
02d,05feb06,mil  Updated for POSIX namespace conformance.
02c,07jan06,rec	 add _WRS_SUPV_STACK_ADJUST
02b,01jul05,rec	 coldfire review comments
02a,23jun05,rec	 add coldfire support
01z,07oct05,yvp	 Defined VX_OBJ_ALIGN_SIZE (SPR 113405).
01y,07jun05,yvp	 Updated copyright. #include now with angle-brackets.
01x,26apr05,yvp	 Transferred previous 2 changes into vxLayerConfig.h
01w,16mar05,yvp	 Undef'ed WV_INSTRUMENTATION and EDR_ERROR_INJECT_STUBS.
		 Defined MINIMAL_KERNAL and _FREE_VERSION for now.
01v,04apr05,scm	 re-enable WV_INSTRUMENTATION for ARM/XScale...
01u,22mar05,scm	 disable WV_INSTRUMENTATION until windview work complete for ARM...
01t,17dec04,scm	 add WV_INSTRUMENTATION for arm/xscale...
01s,15nov04,h_k	 enabled WV_INSTRUMENTATION for SH.
01r,04may04,tcr	 add WV_INSTRUMENTATION to MIPS
01q,06apr04,dbt	 Enabled WindView support for VxSim.
01p,13mar04,dlk	 disable WV_INSTRUMENTATION if _FREE_VERSION defined.
01o,25mar04,dbt	 Added SIMPENTIUM support.
01n,19nov04,job	 Combined user & kernel mode versions. Moved kernel mode
		 STACK, ALLOC & CACHE_ALIGN_SIZE macros here so that they
		 are set correctly.
01m,16dec03,kk	 re-enable WV_INSTRUMENTATION
01l,14dec03,kk	 temporarily disable WV_INSTRUMENTATION until network builds
01k,11nov03,tcr	 enable WindView on selected archs
01j,15jul03,kam	 rebased to Base6 integration branch
01i,26jun03,dcc	 temporarily comment out the definition of WV_INSTRUMENTATION
01h,17apr03,dbt	 Added SIMLINUX support. Removed SIMHPPA & SIMSPARCSUNOS
01g,16nov01,dee	 add COLDFIRE architecture
01f,14nov01,tcr	 Undo previous change
01e,29oct01,tcr	 add INCLUDE_WVNET for instrumented network stack
01d,25feb00,frf	 Add SH support for T2
01c,06Aug98,ms	 added WV_INSTRUMENTATION.
02b,15aug97,cym	 added SIMNT support.
02b,28nov96,cdp	 added ARM support.
02a,26may94,yao	 added PPC support.
01n,30oct95,ism	 added SIMSOLARIS support.
01m,19mar95,dvs	 removed #ifdef TRON - tron no longer supported.
01l,02dec93,pme	 added Am29K family support.
01k,11aug93,gae	 vxsim hppa.
01j,12jun93,rrr	 vxsim.
01i,09jun93,hdn	 added support for I80X86
01h,22sep92,rrr	 added support for c++
01g,07sep92,smb	 added documentation
01f,07jul92,rrr	 added defines for BIG & LITTLE ENDIAN and STACK direction
01e,07jul92,ajm	 added _ARCH_MULTIPLE_CACHELIB for cache init
01d,03jul92,smb	 changed name from arch.h.
01c,06jun92,ajm	 corrected definition of mips CPU_FAMILY
01b,26may92,rrr	 the tree shuffle
		  -changed includes to have absolute path from h/
01a,22apr92,yao	 written.
*/

/*
DESCRIPTION
This header file includes a architecture specific header file depending
on the value of CPU_FAMILY defined in vxCpu.h. The header file contains
definitions specific to this CPU family. This header file must be
preceded by an include of vxCpu.h
*/

#ifndef __INCvxArchh
#define __INCvxArchh

#ifdef _BIG_ENDIAN
#undef _BIG_ENDIAN
#endif /* _BIG_ENDIAN */
#define _BIG_ENDIAN		1234

#ifdef _LITTLE_ENDIAN
#undef _LITTLE_ENDIAN
#endif /* _LITTLE_ENDIAN */
#define _LITTLE_ENDIAN		4321

#define _STACK_GROWS_DOWN	(-1)
#define _STACK_GROWS_UP		1

#ifdef _WRS_KERNEL

#if (_VX_CPU_FAMILY==_VX_MC680X0)
#include <arch/mc68k/archMc68k.h>
#endif /* (_VX_CPU_FAMILY== _VX_MC680X0) */

#if (_VX_CPU_FAMILY==_VX_SPARC)
#include <arch/sparc/archSparc.h>
#endif /* (_VX_CPU_FAMILY== _VX_SPARC) */

#if (_VX_CPU_FAMILY==_VX_I960)
#include <arch/i960/archI960.h>
#endif /* (_VX_CPU_FAMILY== _VX_I960) */

#if (_VX_CPU_FAMILY==_VX_AM29XXX)
#include <arch/am29k/archAm29k.h>
#endif /* (_VX_CPU_FAMILY==_VX_AM29XXX) */

#else /* _WRS_KERNEL */

#if (_VX_CPU_FAMILY==_VX_SIMPENTIUM)
#include <arch/simpentium/archSimpentium.h>
#endif /* (_VX_CPU_FAMILY== _VX_SIMPENTIUM) */

#endif /* _WRS_KERNEL */

#if (_VX_CPU_FAMILY==_VX_SIMSPARCSOLARIS)
#include <arch/simsolaris/archSimsolaris.h>
#endif /* (_VX_CPU_FAMILY== _VX_SIMSPARCSOLARIS) */

#if (_VX_CPU_FAMILY==_VX_SIMLINUX)
#include <arch/simlinux/archSimlinux.h>
#endif /* (_VX_CPU_FAMILY== _VX_SIMLINUX) */

#if (_VX_CPU_FAMILY==_VX_SIMNT)
#include <arch/simnt/archSimnt.h>
#endif /* (_VX_CPU_FAMILY== _VX_SIMNT) */

#if (_VX_CPU_FAMILY==_VX_MIPS)
#include <arch/mips/archMips.h>
#endif /* (_VX_CPU_FAMILY==_VX_MIPS) */

#if (_VX_CPU_FAMILY==_VX_PPC)
#include <arch/ppc/archPpc.h>
#endif /* (_VX_CPU_FAMILY==_VX_PPC) */

#if (_VX_CPU_FAMILY==_VX_I80X86)
#include <vsbConfig.h>
#ifndef _WRS_CONFIG_LP64
#include <arch/i86/archI86.h>
#else
#include <arch/i86/x86_64/archX86_64.h>
#endif  /* _WRS_CONFIG_LP64 */
#endif /* (_VX_CPU_FAMILY==_VX_I80X86) */

#if (_VX_CPU_FAMILY==_VX_SH)
#include <arch/sh/archSh.h>
#endif /* (_VX_CPU_FAMILY==_VX_SH) */

#if (_VX_CPU_FAMILY==_VX_ARM)
#include <arch/arm/archArm.h>
#endif /* (_VX_CPU_FAMILY==_VX_ARM) */

#if (_VX_CPU_FAMILY==_VX_COLDFIRE)
#include <arch/coldfire/archColdfire.h>
#endif /* (_VX_CPU_FAMILY== _VX_COLDFIRE) */

#ifndef _WRS_SUP_STACK_RELOC

/* in case the architecture needs to relocate supervisor stacks */

#define _WRS_SUP_STACK_RELOC(p) p
#define _WRS_SUP_STACK_UNRELOC(p) p
#endif /* !_WRS_SUP_STACK_RELOC */

#ifndef _BYTE_ORDER
#define _BYTE_ORDER		_BIG_ENDIAN
#endif /* _BYTE_ORDER */

#ifndef _STACK_DIR
#define _STACK_DIR		_STACK_GROWS_DOWN
#endif	/* _STACK_DIR */

#ifndef _ALLOC_ALIGN_SIZE
#define _ALLOC_ALIGN_SIZE	4	/* 4 byte boundary */
#endif	/* _ALLOC_ALIGN_SIZE */

/* Note: for architectures not reguiring stack alignment, enforcing 4 byte
 * alignment is recommended for better efficiency.
 */

#ifndef _STACK_ALIGN_SIZE
#define _STACK_ALIGN_SIZE	4	/* 4 byte boundary */
#endif	/* _STACK_ALIGN_SIZE */

#ifndef _CACHE_ALIGN_SIZE
#define _CACHE_ALIGN_SIZE	16
#endif	/* _CACHE_ALIGN_SIZE */

#ifndef _ARCH_MULTIPLE_CACHELIB
#define _ARCH_MULTIPLE_CACHELIB FALSE
#endif	/* _ARCH_MULTIPLE_CACHELIB */

/* alignment requirement when accessing bus */

#ifndef _DYNAMIC_BUS_SIZING
#define _DYNAMIC_BUS_SIZING	TRUE	/* dynamic bus sizing */
#endif	/* _DYNAMIC_BUS_SIZING */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* This is were any symbol with C linkage should be added */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INCvxArchh */

/* archMips.h - MIPS architecture specific header */

/*
 * Copyright (c) 1992-1993, 1995-1997, 1999-2011 Wind River Systems, Inc.
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
05c,02aug11,slk  add rom entry text section
05b,08jun11,d_c  Add interrupt vector code offsets
05b,16jun11,l_z  update for XLP SMP
05a,01feb11,slk  add _WRS_ENABLE_TLB_POOL_CREATE_HOOK hook to enable AIM
                 MMU pool creation in MIPS arch
04z,27jan11,slk  add defines for extra LMM kernel segment below KSEG0
04y,20jan11,slk  add wired text and data macros for arch source builds
04x,12jan11,d_c  Defect WIND00249800 Fix WIND00249802 - update
                 vmPageProtectTest for MIPS processors that support executable
                 page attributes
04w,17dec10,d_c  Defect WIND00237752. Add PRID definitions for company field
04v,08dec10,slk  add IS_KSEG2
04u,12nov10,slk  add configuration 4 register
04t,07oct10,slk  add ARCH_NEEDS_PADDR_TRANSLATION requirement for wrload
04s,23sep10,rlg  fix for WIND00232811 defect/escalation kernel to rtp signal
                 crash
04v,16sep10,gls  added VX_OBJ_ALIGN_SIZE
04u,08jul10,slk  fix PHYS_TO_PTR and PTR_TO_PHYS
04t,15jun10,slk  add defines for large memory model
04t,05may10,pch  small footprint
04u,27may10,d_c  Rename CAVIUM_CNMIPS_* to _WRS_CAVIUM_CNMIPS_* and define in
                 arch Makefile
04s,29apr10,pad  Moved extern C statement after include statements.
04t,26apr10,d_c  fix #endif comment
04s,31mar10,d_c  Add cav_cn5xxx and cav_cn6xxx variants
04r,15oct09,slk  add KX_TO_K0 and KX_TO_K1 addr conversions for mapped ROM
04q,23sep09,kab  Add wrload map/unmap macros
04p,20jul09,slk  add define for MIPS32 or MIPS64 compatible variants
04o,29may09,slk  add bitfield macros for R2 cpus
04n,20mar09,pch  add R2 support in SR_IE macros
04m,26feb09,pgh  Remove _WRS_MIPS_SDA_SUPPORTED
04l,05feb09,pch  macros for SR_IE manipulation
04k,27aug08,slk  add _WRS_MIPS_SDA_SUPPORTED macro to enable SDA
04j,13mar08,rlp  Removed obsolete _WRS_ARCH_HAS_DBG_IPI macro.
04i,12feb08,rlp  Properly handle Branch Delay Slot (CQ:WIND00116790).
04h,28nov07,l_z  Increase the value of VX_MAX_SMP_CPUS to 32.
04g,08nov07,slk  add _WRS_ARCH_NO_LEGACY_INT_ENABLE_DISABLE_SUPPORT
04f,24oct07,pes  Correct stack alignment boundary for n32
04e,12oct07,pes  WIND00107843: fix aimMmuBufferWrite issues for BCM1480
04d,10aug07,rlg  MIPS library restructure changes
04c,07aug07,pes  Define _WRS_MMU_HAS_MAP_STATE_API.
04b,29jul07,pes  Addition of define for Cavium multiplier presence bit.
04a,17jul07,pes  Undefine 'mips' to resolve gnu build issues when -ansi is not
		 specified.
03z,13jul07,rlp  Added the _WRS_ARCH_HAS_DBG_IPI support.
03y,29jun07,jmp  Defined _WRS_ARCH_HAS_VXDBG_CPU_CTRL_SUPPORT for MIPS.
03x,18jun07,pes  Move references to _WRS_VX_SMP out of public header file.
03w,15may07,jmt  Updated max SMP CPUs to 16
03v,04may07,zl   updated portable library build configuration.
03u,17apr07,kk   move VX_MAX_SMP_CPUS to here
03t,20apr07,pes  Correct detection logic for R2 instructions.
03s,28mar07,slk  Add 128 byte cacheline size for cavium
03r,21feb07,jmg  Added include vxPortablLibP.h
03q,16feb07,pes  Add #undef for _WRS_MMU_HAS_MAP_STATE_API, to be
		 #define'd when appropriate. Add defines to enable CPCs
		 for cacheTextUpdate and TLB flush operations.
03p,07feb07,pes  Make this file "assembler friendly".
03o,21feb07,pes  Add support for new MIPS lib structure.
03n,11dec06,kk   removed references to _WRS_BASE6_SCHEDULER and
		 _WRS_ARCH_HAS_RESCHEDULE_STACK, no longer needed
03m,02nov06,pes  #define _WRS_ARCH_HAS_IDLE_TASK and #undef
		 _WRS_ARCH_HAS_RESCHEDULE_STACK to enable use of idle task
		 for SMP.
03l,28sep06,pes  Add definition of _WRS_ARCH_HAS_NEW_KERNEL_LOCK
03k,20sep06,pes  Move definition of VX_KERNEL_VARS to private/smpMipsP.h.
03j,14sep06,gls  added define of VX_KERNEL_VARS
03i,15aug06,pes  Add definition _WRS_VX_NO_GLOBAL_ERRNO
03h,31may06,pes  Add definition of _WRS_ARCH_HAS_RESCHEDULE_STACK
03g,13jan06,pes  Document changes made to definition of _CACHE_ALIGN_SIZE
03f,10jan06,pes  Enable MIPS R2 ISA support. Add support for non-standard
		 cache line sizes.
03e,29aug05,h_k  added _WRS_SUPPORT_CACHE_XLATE and _WRS_SUPPORT_CACHE_LOCK.
03d,12aug05,pes  Add SR_MX bit, define _WRS_DSP_SUPPORT.
03c,12apr05,kk   remove _WRS_OBJLIB_SUPPORT_VERIFY_TRAP macro (SPR# 106486)
03b,24feb05,slk  SPR 102772: add _ARCH_SUPPORTS_PROTECT_INTERRUPT_STACK
		 and _WRS_STACK_PROTECT_REQUIRES_MMU macros.
03a,10dec04,slk  SPR 104530.  Add define for PM_MMULESS_PAGE_SIZE used by
		 pmLib.c.  This needs to be changed for MIPS to 8192 so the
		 ED&R area is created on an 8K boundary.
02z,09dec04,pes  SPR 103585 et.al.: Added _WRS_NONGLOBAL_NULL_PAGE define.
		 Triggers conditional code in aimMmuLib.c.
02y,01nov04,slk  SPR 92598: Add support for OSM event handling
02x,15oct04,pes  Corrected copyright notice. Add definition of BEV_VEC
02w,01oct04,tam  moved definition of _TYPE_PHYS_ADDR from shared file to
		 kernel header
02v,17sep04,pes  Move _TYPE_PHYS_ADDDR and _WRS_PHYS_ADDR_IS_64_BITS to
		 archMipsCommon.h.
02u,02sep04,pes  Add definition of _WRS_LINKER_DATA_SEG_ALIGN
02t,18may04,mem  Remove R3k.
02s,28apr04,pes  Switch to portable scheduler.
02r,27apr04,cjj  Defined workQLib_PORTABLE
02q,22mar04,zl   moved trcLib_PORTABLE, _RType and INSTR to archMipsCommon.h;
		 added _WRS_FRAMEP_FROM_JMP_BUF and _WRS_RET_PC_FROM_JMP_BUF.
02p,26mar04,slk  Add configuration 1 register definitions
02o,10mar04,pes  *Really* finish implementation of 02h.
02n,10mar04,pes  Finish implementation of 02h.
02m,10mar04,pes  Change _STACK_ALIGN_SIZE to 8 to match compiler behavior.
02l,13feb04,pes  Add typedef override for _TYPE_PHYS_ADDR. Define
		 trcLib_PORTABLE.
02k,07dec03,pes  Removed definitions of _ARCH_LONG_MIN and _ARCH_INT_MIN in
		 favor of those in vxTypesBase.h
02j,25nov03,pes  Moved definition of _BYTE_ORDER to archMipsCommon.h.
02i,14nov03,job  Moved some blib stuff to archMipsCommon.h
02h,13nov03,pes  Add include of archMipsCommon.h
02g,29oct03,pes  Adjust Address mapping macros for greater flexibility.
02f,28oct03,pcm  enabled base 6 scheduler
02e,27aug03,to   added defines for semLib.
02d,07may03,pes  More conditional compilation cleanup.
02c,29apr03,pes  PAL conditional compilation cleanup.
02b,03oct02,jmt  Allow for override of _CACHE_ALIGN_SIZE
02a,13mar01,sn   SPR 73723 - define supported toolchains
01z,09jan02,tlc  Remove inappropriate TLB definitions.
01y,04oct01,agf  add TLB definitions and constants
01x,16jul01,ros  add CofE comment
01w,07jun01,mem  Re-introduce optimized kernel.
01v,13feb01,pes  Add support for RM7000 extended interrupts
01u,05jan01,mem  Remove decl of _wdbDbgCtx routines.
01t,04jan01,agf  Adding TLB_ENTRIES define
01s,03jan01,pes  Remove definition of IS_KSEGM. This is not supported in
		 Tornado 2.
01r,20dec00,pes  Merge some definitions from target/h/arch/r4000.h.
01q,12oct99,yvp  Merge from .../tor2_0_0.coretools-baseline branch to make
		 Tor2 code work with T3 main/LATEST compiler
01p,07sep99,myz  added CW4000_16 compiler switch
01o,22jan97,alp  added  CW4000 and CW4010 support.
01n,11nov99,dra  Updated for T3 toolchain.
01m,18oct99,dra  added CW4000, CW4011, VR4100, VR5000 and VR5400 support.
		 added test for both MIPSEB and MIPSEL defined.
01l,00oct00,sn   removed varargs/typedefs for GNUC
01k,14oct96,kkk  added R4650 support.
01j,05aug96,kkk  Changed _ALLOC_ALIGN_SIZE & _STACK_ALIGN_SIZE to 16.
01i,27jun96,kkk  undo 01h.
01h,30apr96,mem  fixed varargs support for R4000, use 64 bit stack slots.
01g,27may95,cd	 switched from MIPSE[BL] to _BYTE_ORDER for ansi compliance
01f,15oct93,cd   added support for R4000, SDE compiler and 64 bit kernel.
01e,22sep92,rrr  added support for c++
01d,07jun92,ajm  added _ARCH_MULTIPLE_CACHES for cache init
01c,03jun92,ajm  updated file name referenced to match real name
01b,26may92,rrr  the tree shuffle
01a,22apr92,yao  written.
*/

#ifndef __INCarchMipsh
#define __INCarchMipsh

#define _ARCH_SUPPORTS_GCC
#define _ARCH_SUPPORTS_DCC

/*
 * The gnu compiler has a pre-defined value of '1' for the macro 'mips'
 * this interferes with use of 'mips' in _VX_ARCH_DIR (as expanded in in
 * vxInline.h). #undef'ing it here resolves that issue.
 */

#ifdef mips
#undef mips
#endif /* mips */

/* temporary macro to trigger VM subsystem updates */

#define _WRS_MMU_HAS_MAP_STATE_API

/* temporary macro to indicate MIPS uses the new errno design */
   
#define _WRS_VX_NO_GLOBAL_ERRNO

/* temporary macro to indicate MIPS uses the type II kernel lock */

#define _WRS_ARCH_HAS_NEW_KERNEL_LOCK

/* temporary macro to indicate MIPS has idle task */

#define _WRS_ARCH_HAS_IDLE_TASK

/* indicates that MIPS has VxDBG CPU control support */

#define _WRS_ARCH_HAS_VXDBG_CPU_CTRL_SUPPORT

/* for legacy interrupt API support, flag MIPS doesn't support 
 * separate intEnable/intDisable to control int controller 
 * configuration
 */

#define _WRS_ARCH_NO_LEGACY_INT_ENABLE_DISABLE_SUPPORT

/* Enable MMU Post State Set Hook in aimMmuLib */

#define _WRS_ENABLE_MMU_POST_STATE_SET_HOOK

/* Enable creating memory pools for AIM MMU (region and page tables)  */

#define _WRS_ENABLE_TLB_POOL_CREATE_HOOK

/* indicate to wrload library we need to translate symbol addresses */

#define ARCH_NEEDS_PADDR_TRANSLATION

/* End PAL */

#undef VX_MAX_SMP_CPUS
#define VX_MAX_SMP_CPUS         32

#define	_ARCH_MULTIPLE_CACHELIB		TRUE

#include <vsbConfig.h>		/* ensure _WRS_CONFIG_* are set properly */

#ifdef	_WRS_CONFIG_NORMAL_MIPS_CACHE_SUPPORT
#define _WRS_SUPPORT_CACHE_XLATE		/* cache virt-phys translate */
#define _WRS_SUPPORT_CACHE_LOCK			/* cache lock feature */
#endif	/* _WRS_CONFIG_NORMAL_MIPS_CACHE_SUPPORT */

#define _DYNAMIC_BUS_SIZING		FALSE	/* no dynamic bus sizing */
#define	_ALLOC_ALIGN_SIZE		16

/*
 * VX_OBJ_ALIGN_SIZE is the default allocation boundary for kernel objects.  
 * This is used for both statically and dynamically allocated objects.
 */

#define VX_OBJ_ALIGN_SIZE		16

#ifdef _WRS_MIPS_N32_ABI
#define _STACK_ALIGN_SIZE		16
/* no extra stack size needed  by n32 abi */
#define FRAMEBASESZ			0	
#else /* _WRS_MIPS_N32_ABI */
#define _STACK_ALIGN_SIZE		8
/* o32 abi needs to have an extra 16 bytes added to the stack  */
#define FRAMEBASESZ			16
#endif /* _WRS_MIPS_N32_ABI */

/*
 * This file is included in both arch-dependent and arch-independent builds.
 * Since _CACHE_ALIGN_SIZE is accessed by files in both categories,
 * the following strategy is used to ensure the correct value is used.
 *
 * For builds of arch independent code, CPU_VARIANT will NOT be defined,
 * so _CPU_CACHE_ALIGN_SIZE will be undefined. In this case, we define
 * _CACHE_ALIGN_SIZE to refer to the global variable _mipsCacheLineSize,
 * which is initialized at boot time to be the size appropriate for the
 * processor in use. Arch independent code will then read the variable
 * to get the correct alignment boundary.
 * 
 * For builds of BSPs and the kernel libraries, the value of CPU_VARIANT
 * will be defined, and the macro MIPSXX_<CPU_VARIANT> will be defined.
 * When we see that CPU_VARIANT is defined, we check to see whether
 * the MIPSXX_<CPU_VARIANT> definition is one that requires a 64-byte
 * alignment. If so, we set _CPU_CACHE_ALIGN_SIZE to 64, otherwise it is
 * set to the default of 32 bytes. Once this is done, we assign
 * _CACHE_ALIGN_SIZE to the value we selected for _CPU_CACHE_ALIGN_SIZE.
 * To add another CPU_VARIANT that requires 64-byte cache alignment, or
 * a different alignment boundary, simply add a test for definition of
 * the MIPSXX_<CPU_VARIANT> corresponding to that variant and (if necessary)
 * the new alignment boundary for that variant.
 *
 */

#if defined (CPU_VARIANT)
#  if defined (MIPSXX_tx79xx) || defined (MIPSXX_xlp)
#    define _CPU_CACHE_ALIGN_SIZE	64
#  elif defined(_WRS_CAVIUM_CNMIPS_CORE) || defined(_WRS_CAVIUM_CNMIPS_II_CORE)
#    define _CPU_CACHE_ALIGN_SIZE	128
#  else /* CPU_CACHE_ALIGN_SIZE */
#    define _CPU_CACHE_ALIGN_SIZE	32
#  endif /* _CPU_CACHE_ALIGN_SIZE */
#endif /* CPU_VARIANT */

/*
 * Use constant size if known (when building for a specific CPU type)
 * else fetch from a global variable (when building for generic)
 */
#undef  _CACHE_ALIGN_SIZE
#ifdef  _CPU_CACHE_ALIGN_SIZE
#define _CACHE_ALIGN_SIZE	_CPU_CACHE_ALIGN_SIZE
#else /* _CPU_CACHE_ALIGN_SIZE */
# ifndef _ASMLANGUAGE
# define _CACHE_ALIGN_SIZE	_mipsCacheLineSize
  extern int _mipsCacheLineSize;
# endif /* _ASMLANGUAGE */
#endif /* _CPU_CACHE_ALIGN_SIZE */

#define _WRS_MIPS_32BIT_CPU ((CPU==MIPS32)||(CPU==MIPSI2)||\
			     (CPU==MIPSI32)||(CPU==MIPSI32R2))

#define _WRS_MIPS_64BIT_CPU ((CPU==MIPS64)||(CPU==MIPSI3)||\
			     (CPU==MIPSI64)||(CPU==MIPSI64R2))

#if (CPU==MIPSI32R2) || (CPU==MIPSI64R2)
#define _WRS_MIPS_ENABLE_R2_ISA
#endif /* CPU==MIPSI32R2 || CPU==MIPSI64R2 */

/* ISA is compatible with MIPS32 or MIPS64 */
#if (CPU!=MIPSI2) && (CPU!=MIPSI3)
#define _WRS_MIPS_MIPS32_OR_MIPS64_ISA_COMPATIBLE
#else /* (CPU!=MIPSI2) && (CPU!=MIPSI3) */
#undef _WRS_MIPS_MIPS32_OR_MIPS64_ISA_COMPATIBLE
#endif /* (CPU!=MIPSI2) && (CPU!=MIPSI3) */

#if	_WRS_MIPS_32BIT_CPU

#define _WRS_INT_REGISTER_SIZE		4
#define _WRS_INT_REGISTER_SHIFT		2
#define _WRS_FP_REGISTER_SIZE		4
#define _WRS_FP_REGISTER_SHIFT		2

#elif	_WRS_MIPS_64BIT_CPU

#define _WRS_INT_REGISTER_SIZE		8
#define _WRS_INT_REGISTER_SHIFT		3
#define _WRS_FP_REGISTER_SIZE		8
#define _WRS_FP_REGISTER_SHIFT		3

#else	/* CPU */
#error "Invalid CPU value"
#endif	/* CPU */

#define _WRS_DSP_SUPPORT

#define RTP_SPAWN_MEMORY_LEAK_FIX	/* remove when temp code is removed */

#define _RTypeSize			_WRS_INT_REGISTER_SIZE

#define SR_INT_ENABLE			SR_IE	/* interrupt enable bit */

#define POP_SR(p) ((p) & ~SR_EXL)

/*
 * Segment base addresses and sizes
 */

#define	K0BASE		0x80000000
#define	K0SIZE		0x20000000
#define	K1BASE		0xA0000000
#define	K1SIZE		0x20000000

#define KMBASE		"Do not use" /* 0xC0000000 *//* mapped kernel space */
#define	KMSIZE		"Do not use" /* 0x40000000 */

#define	KSBASE		"Do not use" /* 0xC0000000 */
#define	KSSIZE		"Do not use" /* 0x20000000 */
#define	K2BASE		0xC0000000
#define	K2SIZE		0x20000000
#define	K3BASE		0xE0000000
#define	K3SIZE		0x20000000

/* the following defines are used my mmuMipsLib.c to define the 
 * sizes and start and end addresses of the memory regions defined
 * by virtualSegmentInfo[].
 */

/* need to start the user segment at an offset from 0x00000000 */

#define _WRS_MIPS_USER_SEGMENT_BASE_ADRS_OFFSET	0x00400000

/* LMM extra kernel segment size. this segment ends at K0BASE.  the size is
 * used in the table virtualSegmentInfo in mmuMipsLib.c to define the
 * end of the user segment and the start address and size of an extra
 * kernel segment.  this segment is used for creating a wired-TLB entry
 * virtual region that gives access to the MMU context, region and page
 * tables that is guaranteed to not have a TLB miss.  It is also used as
 * needed by the BSP for mapping regions like PCIE space.  The wired-TLB
 * used for MMU tables uses the virtual address
 * AIM_MMU_INIT_MEM_POOL_VIRT_ADRS to define its base address.  this is
 * typcially set to the top of this kernel segment.
 */

#ifdef _WRS_MIPS_LMM_SUPPORTED
#define _WRS_MIPS_EXTRA_KERNEL_SEGMENT_SIZE    0x20000000  /* set to 512MB */

#define _WRS_MIPS_USER_SEGMENT_END_ADRS    (K0BASE - \
					   _WRS_MIPS_EXTRA_KERNEL_SEGMENT_SIZE)
#define _WRS_MIPS_EXTRA_KERNEL_SEGMENT_BASE_ADRS \
                                               _WRS_MIPS_USER_SEGMENT_END_ADRS
#else  /* _WRS_MIPS_LMM_SUPPORTED */

/* non LMM variants get all of the memory for user space below K0BASE */

#define _WRS_MIPS_USER_SEGMENT_END_ADRS    K0BASE

#endif /* _WRS_MIPS_LMM_SUPPORTED */

/* define the user segment size based on the size of the 
 * _WRS_MIPS_EXTRA_KERNEL_SEGMENT_SIZE.
 */

#define _WRS_MIPS_USER_SEGMENT_SIZE    (_WRS_MIPS_USER_SEGMENT_END_ADRS -\
                                       _WRS_MIPS_USER_SEGMENT_BASE_ADRS_OFFSET)

/*
 * Address conversion macros
 */

#ifdef _ASMLANGUAGE
#define	K0_TO_K1(x)	((x)|0xA0000000)	/* kseg0 to kseg1 */
#define	K1_TO_K0(x)	((x)&0x9FFFFFFF)	/* kseg1 to kseg0 */

#define	K0_TO_PHYS(x)	((x)&0x1FFFFFFF)	/* kseg0 to physical */
#define	K1_TO_PHYS(x)	((x)&0x1FFFFFFF)	/* kseg1 to physical */

#define	PHYS_TO_K0(x)	((x)|0x80000000)	/* physical to kseg0 */
#define	PHYS_TO_K1(x)	((x)|0xA0000000)	/* physical to kseg1 */

/* any kseg to phys, kseg0, kseg1 or kseg2 */
#define KX_TO_PHYS(x)   ((x)&0x1FFFFFFF)
#define KX_TO_K0(x)     (((x) & ADDRESS_SPACE_MASK) | K0BASE)
#define KX_TO_K1(x)     (((x) & ADDRESS_SPACE_MASK) | K1BASE)
#define KX_TO_K2(x)     (((x) & ADDRESS_SPACE_MASK) | K2BASE)
#else /* _ASMLANGUAGE */
#define	K0_TO_K1(x)	((unsigned)(x)|0xA0000000)	/* kseg0 to kseg1 */
#define	K1_TO_K0(x)	((unsigned)(x)&0x9FFFFFFF)	/* kseg1 to kseg0 */

#define	K0_TO_PHYS(x)	((unsigned)(x)&0x1FFFFFFF)	/* kseg0 to physical */
#define	K1_TO_PHYS(x)	((unsigned)(x)&0x1FFFFFFF)	/* kseg1 to physical */

#define	PHYS_TO_K0(x)	((unsigned)(x)|0x80000000)	/* physical to kseg0 */
#define	PHYS_TO_K1(x)	((unsigned)(x)|0xA0000000)	/* physical to kseg1 */

/* any kseg to phys, kseg0, kseg1 or kseg2 */
#define KX_TO_PHYS(x)   ((unsigned)(x)&0x1FFFFFFF)
#define KX_TO_K0(x)     (((unsigned)(x) & ADDRESS_SPACE_MASK) | K0BASE)
#define KX_TO_K1(x)     (((unsigned)(x) & ADDRESS_SPACE_MASK) | K1BASE)
#define KX_TO_K2(x)     (((unsigned)(x) & ADDRESS_SPACE_MASK) | K2BASE)
#endif /* _ASMLANGUAGE */

/*
 * The "KM" conversion macros only work for limited sections of the
 * mapped kernel space.
 * 
 */

#define ADDRESS_SPACE_MASK	(~(7<<29))
#ifdef _ASMLANGUAGE
#define	KM_TO_K0(x)	(((x) & ADDRESS_SPACE_MASK) | K0BASE)
#define	KM_TO_K1(x)	(((x) & ADDRESS_SPACE_MASK) | K1BASE)
#define	KM_TO_PHYS(x)	((x)&0x1FFFFFFF)
#define	PHYS_TO_KM(x)	((x) | K2BASE)

#else /* _ASMLANGUAGE */
#define	KM_TO_K0(x)	(((unsigned)(x) & ADDRESS_SPACE_MASK) | K0BASE)
#define	KM_TO_K1(x)	(((unsigned)(x) & ADDRESS_SPACE_MASK) | K1BASE)

#define	KM_TO_PHYS(x)	((unsigned)(x)&0x1FFFFFFF)
#define	PHYS_TO_KM(x)	((unsigned)(x) | K2BASE)
#define K0_TO_KM(x)	PHYS_TO_KM(K0_TO_PHYS(x))


/*
 * Address predicates
 */

#define	IS_KSEG0(x)	((unsigned)(x) >= K0BASE && (unsigned)(x) < K1BASE)
#define	IS_KSEG1(x)	((unsigned)(x) >= K1BASE && (unsigned)(x) < K2BASE)
#define	IS_KSEG2(x)	((unsigned)(x) >= K2BASE)
#define	IS_KUSEG(x)	((unsigned)(x) < K0BASE)

#define IS_UNMAPPED(x)	(((unsigned)(x) & 0xc0000000) == 0x80000000)
#define IS_KSEGM(x)     (!(IS_UNMAPPED(x)))

#endif /* _ASMLANGUAGE */


#ifndef _ASMLANGUAGE
/* unique section defines for assembly and 'C' used mostly for large
 * meory model support
 */
#define _WRS_SECTION_KSEG0BSS            \
                    __attribute__ ((__section__ (".kseg0bss")))
#define _WRS_SECTION_TEXT_UNMAPPED        \
                    __attribute__ ((__section__ (".unmapped.text")))
#define _WRS_SECTION_TEXT_WIRED           \
                    __attribute__ ((__section__ (".text.wired")))
#define _WRS_SECTION_DATA_UNMAPPED        \
                    __attribute__ ((__section__ (".unmapped.data")))
#else  /* _ASMLANGUAGE */
#if (TOOL_FAMILY != GNU)
#define _WRS_SECTION_KSEG0BSS		.section .kseg0bss,b
#define _WRS_SECTION_TEXT_UNMAPPED	.section .unmapped.text
#define _WRS_SECTION_TEXT_VECTORS	.section .vectors.text
#define _WRS_SECTION_TEXT_WIRED		.section .text.wired
#define _WRS_SECTION_TEXT_ROMENTRY      .section .text.romentry
#define _WRS_SECTION_DATA_UNMAPPED	.section .unmapped.data
#else  /* (TOOL_FAMILY == GNU) */
#define _WRS_SECTION_KSEG0BSS		.section .kseg0bss,"w"
#define _WRS_SECTION_TEXT_UNMAPPED	.section .unmapped.text,"x"
#define _WRS_SECTION_TEXT_VECTORS	.section .vectors.text,"x"
#define _WRS_SECTION_TEXT_WIRED		.section .text.wired,"x"
#define _WRS_SECTION_TEXT_ROMENTRY      .section .text.romentry,"x"
#define _WRS_SECTION_DATA_UNMAPPED	.section .unmapped.data,"w"
#endif /* (TOOL_FAMILY != GNU) */
#endif /* _ASMLANGUAGE */

/* control text section assignment based on the variant supporting
 * large memory model.  this define is done for src/arch/mips builds 
 * only so these defines must be limited to that scope
 */

#ifdef _WRS_MIPS_LMM_SUPPORTED
#define _WRS_ARCH_WIRED_OR_STD_TEXT_SECT	_WRS_SECTION_TEXT_WIRED
#else  /* _WRS_MIPS_LMM_SUPPORTED */
#ifndef _ASMLANGUAGE
#define _WRS_ARCH_WIRED_OR_STD_TEXT_SECT
#else  /* _ASMLANGUAGE */
#define _WRS_ARCH_WIRED_OR_STD_TEXT_SECT	.text
#endif /* _ASMLANGUAGE */
#endif /* _WRS_MIPS_LMM_SUPPORTED */

/* PAL additions */
#define FLOAT_NORM			/* xdr */

#define STK_PAGE_GUARD_ATTR		PAGE_MGR_OPTS_SUP_DATA_RO
#define _WRS_ARCH_BLIB
#define	LOGICAL_TO_VIRT(X)		PHYS_TO_KM(K0_TO_PHYS(X))
#define _WRS_DUAL_MAPPED_SYS_PAGE
#define _WRS_VIRTUALLY_INDEXED_CACHES
#define _WRS_CACHE_PAL			/* cache library has been PAL-ified */

/* vxwTaskLib.h */
#define _WRS_NEED_SRSET			/* target/h/vxwTaskLib.h */
#ifndef _WRS_SRSET_ARG_TYPE
#define _WRS_SRSET_ARG_TYPE	UINT32		/* argument to SRSet */
#endif /* _WRS_SRSET_ARG_TYPE */

/* wdbDbgLib.h */
#ifndef _ASMLANGUAGE
#define WDB_CTX_LOAD(pRegs) _wdbDbgCtxLoad (pRegs)
#define WDB_CTX_SAVE(pRegs) _wdbDbgCtxSave (pRegs)
#endif /* _ASMLANGUAGE */

#ifndef _WRS_SPY_TASK_SIZE
#define _WRS_SPY_TASK_SIZE	10000			/* spyLib.c */
#endif /* _WRS_SPY_TASK_SIZE */

#define _WRS_ARCH_LOADELF	LOADELF_MIPS_MODEL	/* loadElf.c */

#define _WRS_CHECK_REGISTER_WIDTH	/* for register display */

/* Target shell support */
#define _WRS_SHELL_DATA_TYPES		SHELL_ALL_DATA_SUPPORT

#ifndef _ASMLANGUAGE
/* wrload 1.x access to secondary image space */
#define _WRS_WRLOAD_MEM_MAP(cpu, paddr, nbytes)     (IS_KSEGM(paddr) ? \
                                                      (VIRT_ADDR) KM_TO_K0(paddr) : \
                                                      (VIRT_ADDR) (paddr))
#define _WRS_WRLOAD_MEM_UNMAP(cpu, paddr, nbytes)
#endif /* _ASMLANGUAGE */

/*
 * Exception vectors
 */

#define T_VEC_OFFSET	0x000
#define X_VEC_OFFSET	0x080
#define C_VEC_OFFSET	0x100
#define E_VEC_OFFSET	0x180

#define	T_VEC		(K0BASE+T_VEC_OFFSET)   /* tlbmiss vector */
#define	X_VEC		(K0BASE+X_VEC_OFFSET)	/* xtlbmiss vector */
#define	C_VEC		(K1BASE+C_VEC_OFFSET)	/* cache exception vector */
#define	E_VEC		(K0BASE+E_VEC_OFFSET)	/* exception vector */
#define	R_VEC		(K1BASE+0x1fc00000)	/* reset vector */
#define BEV_VEC		(K1BASE+0x1fc00380)	/* boot exception vector */

/*
 * Cache alignment macros
 *
 * NOTE: These definitions may migrate to vxWorks.h in a future release.
 */
#define	CACHE_ROUND_UP(x)	ROUND_UP(x, _CACHE_ALIGN_SIZE)
#define	CACHE_ROUND_DOWN(x)	ROUND_DOWN(x, _CACHE_ALIGN_SIZE)

/*
* Cache size constants
*/

#define	R4KMINCACHE	+(1*1024)	/* leading plus for mas's benefit */
#define	R4KMAXCACHE	+(256*1024)	/* leading plus for mas's benefit */

/*
 * Cause bit definitions
 */
#define	CAUSE_BD	0x80000000	/* Branch delay slot */
#define	CAUSE_CEMASK	0x30000000	/* coprocessor error */
#define	CAUSE_CESHIFT	28

#define	CAUSE_IP8	0x00008000	/* External level 8 pending */
#define	CAUSE_IP7	0x00004000	/* External level 7 pending */
#define	CAUSE_IP6	0x00002000	/* External level 6 pending */
#define	CAUSE_IP5	0x00001000	/* External level 5 pending */
#define	CAUSE_IP4	0x00000800	/* External level 4 pending */
#define	CAUSE_IP3	0x00000400	/* External level 3 pending */
#define	CAUSE_SW2	0x00000200	/* Software level 2 pending */
#define	CAUSE_SW1	0x00000100	/* Software level 1 pending */

/* extended interrupt cause bits (e.g., RM7000) */
#define CAUSE_IP16	0x00800000	/* RESERVED */
#define CAUSE_IP15	0x00400000	/* RESERVED */
#define CAUSE_IP14	0x00200000	/* Perf counter */
#define CAUSE_IP13	0x00100000	/* Alt Timer */
#define CAUSE_IP12	0x00080000	/* External level 12 pending */
#define CAUSE_IP11	0x00040000	/* External level 11 pending */
#define CAUSE_IP10	0x00020000	/* External level 10 pending */
#define CAUSE_IP9	0x00010000	/* External level 9 pending */

/* Note: mask includes extended interrupt bit positions */
#define	CAUSE_IPMASK	0x00FFFF00	/* Pending interrupt mask */
#define	CAUSE_IPSHIFT	8

#define	CAUSE_EXCMASK	0x0000007C	/* Cause code bits */
#define	CAUSE_EXCSHIFT	2

/*
 * Status definition bits
 */
#define	SR_CUMASK	0xf0000000	/* coproc usable bits */
#define	SR_CU3		0x80000000	/* Coprocessor 3 usable */
#define	SR_CU2		0x40000000	/* Coprocessor 2 usable */
#define	SR_CU1		0x20000000	/* Coprocessor 1 usable */
#define	SR_CU0		0x10000000	/* Coprocessor 0 usable */
#define SR_RP		0x08000000      /* Use reduced power mode */
#define SR_FR		0x04000000      /* Enable extra floating point regs */
#define SR_RE		0x02000000      /* Reverse endian in user mode */
#define SR_MX		0x01000000      /* Enable DSP/MX extensions */
#define	SR_BEV		0x00400000	/* use boot exception vectors */
#define	SR_TS		0x00200000	/* TLB shutdown */
#define SR_SR		0x00100000	/* soft reset occurred */
#define	SR_CH		0x00040000	/* cache hit */
#define	SR_CE		0x00020000	/* use ECC reg */
#define	SR_DE		0x00010000	/* disable cache errors */
#define	SR_IMASK	0x0000ff00	/* Interrupt mask */
#define	SR_IMASK8	0x00000000	/* mask level 8 */
#define	SR_IMASK7	0x00008000	/* mask level 7 */
#define	SR_IMASK6	0x0000c000	/* mask level 6 */
#define	SR_IMASK5	0x0000e000	/* mask level 5 */
#define	SR_IMASK4	0x0000f000	/* mask level 4 */
#define	SR_IMASK3	0x0000f800	/* mask level 3 */
#define	SR_IMASK2	0x0000fc00	/* mask level 2 */
#define	SR_IMASK1	0x0000fe00	/* mask level 1 */
#define	SR_IMASK0	0x0000ff00	/* mask level 0 */
#define	SR_IBIT8	0x00008000	/* bit level 8 */
#define	SR_IBIT7	0x00004000	/* bit level 7 */
#define	SR_IBIT6	0x00002000	/* bit level 6 */
#define	SR_IBIT5	0x00001000	/* bit level 5 */
#define	SR_IBIT4	0x00000800	/* bit level 4 */
#define	SR_IBIT3	0x00000400	/* bit level 3 */
#define	SR_IBIT2	0x00000200	/* bit level 2 */
#define	SR_IBIT1	0x00000100	/* bit level 1 */

#define	SR_IMASKSHIFT	8

/* starting bit and number of bits in SR_IMASK. defines needed for bitfield
 * macros (_WRS_MIPS_BITFIELD_XXXX)
 */
#define	SR_IMASK_LSB	8
#define	SR_IMASK_SIZE	8

/* R4K specific */
#define	SR_KX		0x00000080	/* enable kernel 64bit addresses */
#define	SR_SX		0x00000040	/* enable supervisor 64bit addresses */
#define	SR_UX		0x00000020	/* enable user 64bit addresses */
#define	SR_KSUMASK	0x00000018	/* mode mask */
#define SR_KSU_K	0x00000000	/* kernel mode */
#define SR_KSU_S	0x00000008	/* supervisor mode */
#define SR_KSU_U	0x00000010	/* user mode */
#define	SR_ERL		0x00000004	/* Error Level */
#define	SR_EXL		0x00000002	/* Exception Level */
#define	SR_IE		0x00000001	/* interrupt enable, 1 => enable */

/* Assembly macros to adjust (only) SR_IE */

#ifdef _ASMLANGUAGE
/******************************************************************************
*
* _MIPS_INT_DISABLE - disable interrupts by masking off SR_IE
*
* When built for R1, this performs the read/modify/write of C0_SR to turn off
* the SR_IE bit.  The mask is usually specified as an immediate operand, but
* may instead be specified as a register (which must already contain ~SR_IE).
*
* When built for R2 it generates a di instruction and uses only the first
* and last parameters.
*
* _MIPS_INT_DISABLE(oldSR, scratch, mask, hazard)
*
* oldSR    Destination register for "mfc0  <oldSR>, C0_SR"
* scratch  Register used to construct and write the new SR value, may be
*          the same as oldSR if the caller does not need the old value.
* mask     Usually the immediate value ~SR_IE, but may
*          instead be a register containing that value.
* hazard   Hazard macro to emit following "mtc0  <scratch>, C0_SR",
*          usually HAZARD_CP_WRITE but occasionally HAZARD_INTERRUPT.
*          May be HAZARD_NULL if the caller handles the hazard.
*/

# ifdef	_WRS_MIPS_ENABLE_R2_ISA
#define	_MIPS_INT_DISABLE(oldSR, scratch, mask, hazard)  \
	.set	noreorder				;\
	di	oldSR					;\
	hazard						;\
	.set	reorder
# else	/* _WRS_MIPS_ENABLE_R2_ISA */
#define	_MIPS_INT_DISABLE(oldSR, scratch, mask, hazard)  \
	.set	noreorder				;\
	mfc0	oldSR, C0_SR				;\
	HAZARD_CP_READ					;\
	and	scratch, oldSR, mask			;\
	mtc0	scratch, C0_SR				;\
	hazard						;\
	.set	reorder
# endif	/* _WRS_MIPS_ENABLE_R2_ISA */

/******************************************************************************
*
* _MIPS_INT_ENABLE - enable interrupts by turning on SR_IE
*
* When built for R1, this performs the read/modify/write of C0_SR to turn on
* the SR_IE bit.  The mask is usually specified as an immediate operand, but
* may instead be specified as a register (which must already contain SR_IE).
*
* When built for R2 it generates an ei instruction and uses only the first
* and last parameters.
*
* _MIPS_INT_ENABLE(oldSR, scratch, mask, hazard)
*
* oldSR    Destination register for "mfc0  <oldSR>, C0_SR"
* scratch  Register used to construct and write the new SR value, may be
*          the same as oldSR if the caller does not need the old value.
* mask     Usually the immediate value SR_IE, but may
*          instead be a register containing that value.
* hazard   Hazard macro to emit following "mtc0  <scratch>, C0_SR",
*          usually HAZARD_CP_WRITE but occasionally HAZARD_INTERRUPT.
*          May be HAZARD_NULL if the caller handles the hazard.
*/

# ifdef	_WRS_MIPS_ENABLE_R2_ISA
#define	_MIPS_INT_ENABLE(oldSR, scratch, mask, hazard)  \
	.set	noreorder				;\
	ei	oldSR					;\
	hazard						;\
	.set	reorder
# else	/* _WRS_MIPS_ENABLE_R2_ISA */
#define	_MIPS_INT_ENABLE(oldSR, scratch, mask, hazard)   \
	.set	noreorder				;\
	mfc0	oldSR, C0_SR				;\
	HAZARD_CP_READ					;\
	or	scratch, oldSR, mask			;\
	mtc0	scratch, C0_SR				;\
	hazard						;\
	.set	reorder
# endif	/* _WRS_MIPS_ENABLE_R2_ISA */

#endif /* _ASMLANGUAGE */

/*
 * fpa definitions
 */

#define FP_ROUND	0x3		/* r4010 round mode mask */
#define FP_STICKY 	0x7c		/* r4010 sticky bits mask */
#define FP_ENABLE 	0xf80		/* r4010 enable mode mask */
#define FP_EXC		0x3f000		/* r4010 exception mask */

#define FP_ROUND_N	0x0		/* round to nearest */
#define FP_ROUND_Z 	0x1		/* round to zero */
#define FP_ROUND_P 	0x2		/* round to + infinity */
#define FP_ROUND_M 	0x3		/* round to - infinity */

#define FP_STICKY_I	0x4		/* sticky inexact operation */
#define FP_STICKY_U	0x8		/* sticky underflow */
#define FP_STICKY_O	0x10		/* sticky overflow */
#define FP_STICKY_Z	0x20		/* sticky divide by zero */
#define FP_STICKY_V	0x40		/* sticky invalid operation */

#define FP_ENABLE_I	0x80		/* enable inexact operation */
#define FP_ENABLE_U	0x100		/* enable underflow exc  */
#define FP_ENABLE_O	0x200		/* enable overflow exc  */
#define FP_ENABLE_Z	0x400		/* enable divide by zero exc  */
#define FP_ENABLE_V	0x800		/* enable invalid operation exc  */

#define FP_EXC_I	0x1000		/* inexact operation */
#define FP_EXC_U	0x2000		/* underflow */
#define FP_EXC_O	0x4000		/* overflow */
#define FP_EXC_Z	0x8000		/* divide by zero */
#define FP_EXC_V	0x10000		/* invalid operation */
#define FP_EXC_E	0x20000		/* unimplemented operation */

#define FP_COND		0x800000	/* condition bit */
#define FP_FS		0x1000000	/* flush denormalised results to zero */

#define FP_EXC_SHIFT	12
#define FP_ENABLE_SHIFT	7
#define FP_EXC_MASK	(FP_EXC_I|FP_EXC_U|FP_EXC_O|FP_EXC_Z|FP_EXC_V|FP_EXC_E)
#define FP_ENABLE_MASK	(FP_ENABLE_I|FP_ENABLE_U|FP_ENABLE_O|FP_ENABLE_Z| \
			 FP_ENABLE_V)
#define FP_TASK_STATUS	(FP_FS) 	/* all FP exceptions are disabled
					   we only attempt to hide denormalised
					   results for signals (see fppALib.s
					   and spr #7665) */

#if defined(_WRS_CAVIUM_CNMIPS_CORE) || defined(_WRS_CAVIUM_CNMIPS_II_CORE)
#define C0_CAVCTL_NOMUL 0x08000000	/* multiplier presence bit (1=no)  */
#endif /* defined(_WRS_CAVIUM_CNMIPS_CORE) || defined(_WRS_CAVIUM_CNMIPS_II_CORE) */

/*
 * R4000 Config Register
 */
#define CFG_CM		0x80000000	/* Master-Checker mode */
#define CFG_ECMASK	0x70000000	/* System Clock Ratio */
#define CFG_ECBY2	0x00000000 	/* divide by 2 */
#define CFG_ECBY3	0x00000000 	/* divide by 3 */
#define CFG_ECBY4	0x00000000 	/* divide by 4 */
#define CFG_EPMASK	0x0f000000	/* Transmit data pattern */
#define CFG_EPD		0x00000000	/* D */
#define CFG_EPDDX	0x01000000	/* DDX */
#define CFG_EPDDXX	0x02000000	/* DDXX */
#define CFG_EPDXDX	0x03000000	/* DXDX */
#define CFG_EPDDXXX	0x04000000	/* DDXXX */
#define CFG_EPDDXXXX	0x05000000	/* DDXXXX */
#define CFG_EPDXXDXX	0x06000000	/* DXXDXX */
#define CFG_EPDDXXXXX	0x07000000	/* DDXXXXX */
#define CFG_EPDXXXDXXX	0x08000000	/* DXXXDXXX */
#define CFG_SBMASK	0x00c00000	/* Secondary cache block size */
#define CFG_SBSHIFT	22
#define CFG_SB4		0x00000000	/* 4 words */
#define CFG_SB8		0x00400000	/* 8 words */
#define CFG_SB16	0x00800000	/* 16 words */
#define CFG_SB32	0x00c00000	/* 32 words */
#define CFG_SS		0x00200000	/* Split secondary cache */
#define CFG_SW		0x00100000	/* Secondary cache port width */
#define CFG_EWMASK	0x000c0000	/* System port width */
#define CFG_EWSHIFT	18
#define CFG_EW64	0x00000000	/* 64 bit */
#define CFG_EW32	0x00010000	/* 32 bit */
#define CFG_SC		0x00020000	/* Secondary cache absent */
#define CFG_SM		0x00010000	/* Dirty Shared mode disabled */
#define CFG_BE		0x00008000	/* Big Endian */
#define CFG_EM		0x00004000	/* ECC mode enable */
#define CFG_EB		0x00002000	/* Block ordering */
#define CFG_ICMASK	0x00000e00	/* Instruction cache size */
#define CFG_ICSHIFT	9
#define CFG_DCMASK	0x000001c0	/* Data cache size */
#define CFG_DCSHIFT	6
#define CFG_IB		0x00000020	/* Instruction cache block size */
#define CFG_DB		0x00000010	/* Data cache block size */
#define CFG_CU		0x00000008	/* Update on Store Conditional */
#define CFG_K0MASK	0x00000007	/* KSEG0 coherency algorithm */

/*
 * Primary cache mode
 */
#define CFG_C_UNCACHED		2
#define CFG_C_NONCOHERENT	3
#define CFG_C_COHERENTXCL	4
#define CFG_C_COHERENTXCLW	5
#define CFG_C_COHERENTUPD	6

/* 
 * Primary Cache TagLo 
 */
#define TAG_PTAG_MASK           0xffffff00      /* Primary Tag */
#define TAG_PTAG_SHIFT          0x00000008
#define TAG_PSTATE_MASK         0x000000c0      /* Primary Cache State */
#define TAG_PSTATE_SHIFT        0x00000006
#define TAG_PARITY_MASK         0x0000000f      /* Primary Tag Parity */
#define TAG_PARITY_SHIFT        0x00000000

/* 
 * Secondary Cache TagLo 
 */
#define TAG_STAG_MASK           0xffffe000      /* Secondary Tag */
#define TAG_STAG_SHIFT          0x0000000d
#define TAG_SSTATE_MASK         0x00001c00      /* Secondary Cache State */
#define TAG_SSTATE_SHIFT        0x0000000a
#define TAG_VINDEX_MASK         0x00000380      /* Secondary Virtual Index */
#define TAG_VINDEX_SHIFT        0x00000007
#define TAG_ECC_MASK            0x0000007f      /* Secondary Tag ECC */
#define TAG_ECC_SHIFT           0x00000000
#define TAG_STAG_SIZE			19	/* Secondary Tag Width */

/* MIPS32/MIPS64 CP0 Register 16 Select 1 defines */

#define CFG1_MMUMASK        0x7e000000   /* MMU size field */
#define CFG1_MMUSHIFT       25
#define CFG1_ISMASK         0x01c00000   /* icache sets per way */
#define CFG1_ISSHIFT        22
#define CFG1_ILMASK         0x00380000   /* icache line size */
#define CFG1_ILSHIFT        19
#define CFG1_IAMASK         0x00070000   /* icache associativity */
#define CFG1_IASHIFT        16
#define CFG1_DSMASK         0x0000e000   /* dcache sets per way */
#define CFG1_DSSHIFT        13
#define CFG1_DLMASK         0x00001c00   /* dcache line size */
#define CFG1_DLSHIFT        10
#define CFG1_DAMASK         0x00000380   /* dcache associativity */
#define CFG1_DASHIFT        7
#define CFG1_PC             0x00000010   /* perf counter implemented */
#define CFG1_WR             0x00000008   /* watch reg implemented */
#define CFG1_CA             0x00000004   /* code compression implemented */
#define CFG1_EP             0x00000002   /* EJTAG implemented */
#define CFG1_FP             0x00000001   /* FPU implemented */
#define CFG1_CACHE_SETS_PER_WAY     64   /* base size for sets per way shifted
					  * left by the value in the CFG1
					  * sets per way field
					  */

#define CFG1_CACHE_LINE_SIZE         2   /* base cache size shifted left by
					  * the value in the CFG1 cache line
					  * size field
					  */

/* MIPS64 CP0 Register 16 Select 4 defines */

#define CFG4_MMUSIZEEXT_MASK        0x000000ff
#define CFG4_MMUSIZEEXT_OR_SHIFT    6    /* shift left to OR with config 1
                                          * MMU Size value for total size
                                          */

/* MIPS64 CP0 Register 16 Select 6 defines */
#define CFG6_CTLB_SIZE_MASK        0xffff0000 /* Number of Combined TLB entries mask */
#define CFG6_CTLB_SIZE_SHIFT       16         /* Number of Combined TLB entries shift */

/*
 * CacheErr register
 */
#define CACHEERR_TYPE		0x80000000	/* reference type: 
						   0=Instr, 1=Data */
#define CACHEERR_LEVEL		0x40000000	/* cache level:
						   0=Primary, 1=Secondary */
#define CACHEERR_DATA		0x20000000	/* data field:
						   0=No error, 1=Error */
#define CACHEERR_TAG		0x10000000	/* tag field:
						   0=No error, 1=Error */
#define CACHEERR_REQ		0x08000000	/* request type:
						   0=Internal, 1=External */
#define CACHEERR_BUS		0x04000000	/* error on bus:
						   0=No, 1=Yes */
#define CACHEERR_BOTH		0x02000000	/* Data & Instruction error:
						   0=No, 1=Yes */
#define CACHEERR_ECC		0x01000000	/* ECC error :
						   0=No, 1=Yes */
#define CACHEERR_SIDX_MASK	0x003ffff8	/* PADDR(21..3) */
#define CACHEERR_SIDX_SHIFT		 3
#define CACHEERR_PIDX_MASK	0x00000007	/* VADDR(14..12) */
#define CACHEERR_PIDX_SHIFT		12

/*
 * Cache operations
 */
#define Index_Invalidate_I               0x0         /* 0       0 */
#define Index_Writeback_Inv_D            0x1         /* 0       1 */
#define Index_Invalidate_SI              0x2         /* 0       2 */
#define Index_Writeback_Inv_SD           0x3         /* 0       3 */
#define Index_Load_Tag_I                 0x4         /* 1       0 */
#define Index_Load_Tag_D                 0x5         /* 1       1 */
#define Index_Load_Tag_SI                0x6         /* 1       2 */
#define Index_Load_Tag_SD                0x7         /* 1       3 */
#define Index_Store_Tag_I                0x8         /* 2       0 */
#define Index_Store_Tag_D                0x9         /* 2       1 */
#define Index_Store_Tag_SI               0xA         /* 2       2 */
#define Index_Store_Tag_SD               0xB         /* 2       3 */
#define Create_Dirty_Exc_D               0xD         /* 3       1 */
#define Create_Dirty_Exc_SD              0xF         /* 3       3 */
#define Hit_Invalidate_I                 0x10        /* 4       0 */
#define Hit_Invalidate_D                 0x11        /* 4       1 */
#define Hit_Invalidate_SI                0x12        /* 4       2 */
#define Hit_Invalidate_SD                0x13        /* 4       3 */
#define Hit_Writeback_Inv_D              0x15        /* 5       1 */
#define Hit_Writeback_Inv_SD             0x17        /* 5       3 */
#define Fill_I                           0x14        /* 5       0 */
#define Hit_Writeback_D                  0x19        /* 6       1 */
#define Hit_Writeback_SD                 0x1B        /* 6       3 */
#define Hit_Writeback_I                  0x18        /* 6       0 */
#define Lock_I				 0x1C	     /* 7	0 */
#define Lock_D				 0x1D	     /* 7	1 */
#define Hit_Set_Virtual_SI               0x1E        /* 7       2 */
#define Hit_Set_Virtual_SD               0x1F        /* 7       3 */

/*
 * Coprocessor 0 operations
 */
#define	C0_READI  0x1		/* read ITLB entry addressed by C0_INDEX */
#define	C0_WRITEI 0x2		/* write ITLB entry addressed by C0_INDEX */
#define	C0_WRITER 0x6		/* write ITLB entry addressed by C0_RAND */
#define	C0_PROBE  0x8		/* probe for ITLB entry addressed by TLBHI */
#define	C0_ERET	  0x18		/* restore for exception */

/*
 * TLB definitions
 */
#define TLB_ENTRIES   64        /* set to size of largest supported core */

/*
 * macros used in fppShow.c to word swap the 32 bit FP reg pair before printing
 * double value if _WRS_FP_REGISTER_SIZE == 4 (e.g., MIPS32 hardware float).
 */
#if (_WRS_FP_REGISTER_SIZE == 4)
#define _WRS_NEED_DOUBLE_TMP

#ifndef _ASMLANGUAGE
/* word swap the 32 bits FP Reg. pair before printing double value. */
#define _WRS_FP_REG_TEMP(ix) { \
	*(UINT32 *) fpDoubleTmp = \
	  *(UINT32 *) (((UINT32)&fpRegSet + fpRegName[ix].regOff + sizeof(UINT32))); \
	*(UINT32 *) ((UINT32) fpDoubleTmp + sizeof(UINT32)) = \
	  *(UINT32 *) (((UINT32)&fpRegSet + fpRegName[ix].regOff)); \
	fpTmp = fpDoubleTmp; \
	}
#endif	/* _WRS_FP_REGISTER_SIZE == 4 */
#endif /* _ASMLANGUAGE */

/* moved here from h/private/javaLibP.h */

#define JAVA_C_SYM_PREFIX	""

/* moved here from h/private/loadElfLibP.h */
   
/* Check whether the value fits in n bits */

#ifndef _ASMLANGUAGE
#define CHECK_FITS(val,nBits) (((val) & ~(MASK(nBits))) == 0)
#endif /* _ASMLANGUAGE */

/* moved here from h/types/vxtypesOld.h */

#define _WRS_PHYS_ADDR_IS_64_BITS

#ifndef _ASMLANGUAGE
/* physical addresses are represented on 64-bit for all MIPS CPUs */

#define _TYPE_PHYS_ADDR	typedef UINT64 PHYS_ADDR

#define CHAR_FROM_CONST(x)	(char *)(x)
#define VOID_FROM_CONST(x)	(void *)(x)
#endif	/* _ASMLANGUAGE */

/* trigger generation of regWidth field of the REG_INDEX struct in h/regs.h. */

#define _WRS_REG_INDEX_REGWIDTH

/* from vmBaseLib.c */

/* #define _WRS_DISABLE_BASEVM */

/* from dbgTaskLib.c and wdbBpLib.c */

    /*
     * On MIPS CPUs, when a breakpoint exception occurs in a branch delay slot,
     * the PC has been changed in the breakpoint handler to match with the
     * breakpoint address.
     * Once the matching has been made, the PC is modified to have its normal
     * value (the preceding jump instruction).
     */

#ifndef _ASMLANGUAGE
#define _WRS_ADJUST_PC_FOR_BRANCH_DELAY(p) \
    {if ((p)->cause & CAUSE_BD) \
	(p)->reg_pc--;}

#define _WRS_GET_PC_FOR_BRANCH_DELAY(pc, p) \
    {				\
    if ((p)->cause & CAUSE_BD)	\
	pc = (p)->reg_pc + 1;	\
    else			\
	pc = (p)->reg_pc;	\
    }

#endif /* _ASMLANGUAGE */

/* Bitfield INS(insert) and EXT(extract) operations defined for assembly and 
 * R2 and non R2 cores.
 *
 * note: these macros use the AT register
 */

#ifdef _ASMLANGUAGE
#ifdef _WRS_MIPS_ENABLE_R2_ISA
#define _WRS_MIPS_BITFIELD_INS(dstReg,srcReg,bitPos,numBits)      \
        .set noat ;                                               \
        srl    AT,srcReg,bitPos ;                                 \
        ins    dstReg,AT,bitPos,numBits ;                         \
        .set at ;
#define _WRS_MIPS_BITFIELD_INS_JUSTIFIED(dstReg,srcReg,bitPos,numBits)  \
        ins    dstReg,srcReg,bitPos,numBits ;
#define _WRS_MIPS_BITFIELD_EXT(dstReg,srcReg,bitPos,numBits)      \
        ext    dstReg,srcReg,bitPos,numBits ;                     \
        sll    dstReg,bitPos ;
#define _WRS_MIPS_BITFIELD_EXT_JUSTIFIED(dstReg,srcReg,bitPos,numBits)  \
        ext    dstReg,srcReg,bitPos,numBits ;
#define _WRS_MIPS_BITFIELD_INS_OFFSET(dstReg,dstBitPos,srcReg,srcBitPos,\
                                          numBits)  \
	.set noat ;                                               \
        ext    AT,srcReg,srcBitPos,numBits ;                      \
        ins    dstReg,AT,dstBitPos,numBits ;                      \
        .set at
#define _WRS_MIPS_BITFIELD_INS_SRC_MASKED(dstReg,srcReg,bitPos,numBits) \
        _WRS_MIPS_BITFIELD_INS(dstReg,srcReg,bitPos,numBits)
#else /* _WRS_MIPS_ENABLE_R2_ISA */
#define _WRS_MIPS_BITFIELD_INS(dstReg,srcReg,bitPos,numBits)      \
        .set noat ;                                               \
        lui    AT, ~(((1 << numBits) - 1) << bitPos)@h;           \
        ori    AT, ~(((1 << numBits) - 1) << bitPos)@l;           \
        and    dstReg, AT ;                                       \
	not    AT ;                                               \
        and    AT, srcReg ;                                       \
        or     dstReg, AT ;                                       \
        .set at ;
#define _WRS_MIPS_BITFIELD_INS_JUSTIFIED(dstReg,srcReg,bitPos,numBits) \
        .set noat ;                                               \
        lui    AT, ~(((1 << numBits) - 1) << bitPos)@h;           \
        ori    AT, ~(((1 << numBits) - 1) << bitPos)@l;           \
        and    dstReg, AT;                                        \
        lui    AT, ((1 << numBits) - 1)@h;                        \
        ori    AT, ((1 << numBits) - 1)@l;                        \
        and    AT,srcReg;                                         \
        sll    AT,bitPos ;                                        \
        or     dstReg,AT;                                         \
        .set at ;
#define _WRS_MIPS_BITFIELD_EXT(dstReg,srcReg,bitPos,numBits)      \
        .set noat ;                                               \
        lui    AT, (((1 << numBits) - 1) << bitPos)@h;            \
        ori    AT, (((1 << numBits) - 1) << bitPos)@l;            \
        and    dstReg,srcReg,AT ;                                 \
        .set at
#define _WRS_MIPS_BITFIELD_EXT_JUSTIFIED(dstReg,srcReg,bitPos,numBits) \
        .set noat ;                                               \
        srl    dstReg,srcReg,bitPos ;                             \
        lui    AT, ((1 << numBits) - 1)@h;                        \
        ori    AT, ((1 << numBits) - 1)@l;                        \
        and    dstReg,AT ;                                        \
        .set at
#define _WRS_MIPS_BITFIELD_INS_OFFSET(dstReg,dstBitPos,srcReg,srcBitPos,\
                                          numBits)  \
        .set noat ;                                               \
        lui    AT, ~(((1 << numBits) - 1) << dstBitPos)@h;        \
        ori    AT, ~(((1 << numBits) - 1) << dstBitPos)@l;        \
        and    dstReg,AT ;                                        \
        lui    AT, (((1 << numBits) - 1) << srcBitPos)@h;         \
        ori    AT, (((1 << numBits) - 1) << srcBitPos)@l;         \
        and    AT, srcReg ;                                       \
	srl    AT, srcBitPos ;                                    \
	sll    AT, dstBitPos ;                                    \
        or     dstReg, AT ;                                       \
        .set at
#define _WRS_MIPS_BITFIELD_INS_SRC_MASKED(dstReg,srcReg,bitPos,numBits) \
        .set noat ;                                               \
        lui    AT, ~(((1 << numBits) - 1) << bitPos)@h;           \
        ori    AT, ~(((1 << numBits) - 1) << bitPos)@l;           \
        and    dstReg, AT ;                                       \
        or     dstReg, srcReg ;                                   \
        .set at ;
#endif /* _WRS_MIPS_ENABLE_R2_ISA */
#endif /* _ASMLANGUAGE */

/* add macros for MIPS32 or MIPS64 ISA compatible */
#if defined(_WRS_MIPS_MIPS32_OR_MIPS64_ISA_COMPATIBLE) && defined(_ASMLANGUAGE)

#define CLO(tmpReg,dstReg,srcReg)                       \
        clo     dstReg,srcReg;
#define CLZ(tmpReg0,tmpReg1,dstReg,srcReg)              \
        clz     dstReg,srcReg;
#define MOVN(dstReg, srcReg, testReg)                   \
        movn    dstReg, srcReg, testReg;
#define MOVZ(dstReg, srcReg, testReg)                   \
        movz    dstReg, srcReg, testReg;

#elif defined(_ASMLANGUAGE)

/* emulate clz and clo */
#define CLO(tmpReg,dstReg,srcReg)                       \
	.set noat;                                      \
        li      AT,0x80000000;                          \
        li      tmpReg,-1;                              \
99:;                                                    \
        addiu   tmpReg,1;                               \
        and     AT,srcReg;                              \
        .set noreorder;                                 \
        bnez    AT,99b;                                 \
        srl     AT,1;                                   \
        .set reorder;                                   \
	.set at;                                        \
        move    dstReg,tmpReg;

#define CLZ(tmpReg0,tmpReg1,dstReg,srcReg)              \
	.set noat;                                      \
        li      AT,0x80000000;                          \
        li      tmpReg0,-1;                             \
99:;                                                    \
        addiu   tmpReg0,1;                              \
        and     tmpReg1,srcReg,AT;                      \
        .set noreorder;                                 \
        bne     tmpReg1,AT,99b;                         \
        srl     AT,1;                                   \
        .set reorder;                                   \
	.set at;                                        \
        move    dstReg,tmpReg0;

#define MOVN(dstReg, srcReg, testReg)                   \
        .set noreorder;                                 \
        beqz    testReg, 99f;                           \
        nop;                                            \
        move    dstReg, srcReg;                         \
        .set reorder;                                   \
99:;

#define MOVZ(dstReg, srcReg, testReg)                   \
        .set noreorder;                                 \
        bnez    testReg, 99f;                           \
        nop;                                            \
        move    dstReg, srcReg;                         \
        .set reorder;                                   \
99:;

#endif /* _WRS_MIPS_MIPS32_OR_MIPS64_ISA_COMPATIBLE && _ASMLANGUAGE */

/* from loadElfLib.c */

#define _WRS_USE_ELF_LOAD_FORMAT

/* from spyLib.c */

#define _WRS_SPY_TASK_SIZE	10000	/* MIPS specific spy task size */

/* from usrLib.c */

#ifdef _ASMLANGUAGE
#define _WRS_TASK_REG_WIDTH taskRegName[ix].regWidth
#define _WRS_FPCTL_REG_WIDTH fpCtlRegName[ix].regWidth
#endif /* _ASMLANGUAGE */

/* from xdr_float.c */

#define FLOAT_NORM

/* from vmShow.c */

/* #define _WRS_DISABLE_VM */

/* from taskShow.c */

#define _WRS_CUSTOM_TASK_ARCH_REGS_SHOW

/* from schedLib.c */

/*
 * Let the idle loop look like a real task by turning all ints on.
 * Without this if a task locks interrupts and suspends itself, and
 * there are no ready tasks, we will lockup.
 */

#ifndef _ASMLANGUAGE
#define _WRS_ENABLE_IDLE_INTS	{intSRSet (taskSrDefault);}
#endif /* _ASMLANGUAGE */

/* macros for getting frame and return PC from a jmp_buf */

#ifndef _ASMLANGUAGE
#define _WRS_FRAMEP_FROM_JMP_BUF(env)	((char *) (env)[0].reg.spReg)
#define _WRS_RET_PC_FROM_JMP_BUF(env)	((INSTR *) (env)[0].reg.raReg)
#endif /* _ASMLANGUAGE */

/*
 * specify that MIPS architecture uses the linker to achieve data
 * segment alignment.
 */
#define _WRS_LINKER_DATA_SEG_ALIGN

/* Enable possibility of including OSM detection if mapped kernel */

#if	defined(INCLUDE_MAPPED_KERNEL)
#define _WRS_OSM_INIT
#endif /* defined(INCLUDE_MAPPED_KERNEL) */

/* Trigger use of non-global null page. For an explanation, see the 
 * description in aimMmuLib.c in the function header for aimMmuLibInit.
 */

#define _WRS_NONGLOBAL_NULL_PAGE

/* Add define for PM_MMULESS_PAGE_SIZE.  needed by pmLib.c so
 * the ED&R area is created on a 8K boundary in all cases.  the 8k
 * boundary size specifies for MIPS the minimum page size.
 */

#define PM_MMULESS_PAGE_SIZE 8192

/* define _ARCH_SUPPORTS_PROTECT_INTERRUPT_STACK indicating support
 * for guard pages on the interrupt stack
 */

#define _ARCH_SUPPORTS_PROTECT_INTERRUPT_STACK

/* define _WRS_STACK_PROTECT_REQUIRES_MMU to indicate all stack
 * protection support features require MMU support on MIPS
 */

#define _WRS_STACK_PROTECT_REQUIRES_MMU

/* PRID definitions */

#define MIPS_PRID_COMPANY_MASK    0x00ff0000
#define MIPS_PRID_COMPANY_SHIFT   16
#define MIPS_PRID_COMPANY_CAVIUM  13

#define MIPS_PRID_ID_MASK            0x0000ff00
#define MIPS_PRID_ID_SHIFT           8
#define MIPS_PRID_ID_CAVIUM_CN50XX   0x06
#define MIPS_PRID_ID_CAVIUM_CN52XX   0x07
#define MIPS_PRID_ID_CAVIUM_CN56XX   0x04
#define MIPS_PRID_ID_CAVIUM_CN58XX   0x03
#define MIPS_PRID_ID_CAVIUM_CN63XX   0x90


#include <arch/mips/archMipsCommon.h>

#ifdef __cplusplus
extern "C" {
#endif

/* END PAL */

#ifdef __cplusplus
}
#endif

#endif /* __INCarchMipsh */

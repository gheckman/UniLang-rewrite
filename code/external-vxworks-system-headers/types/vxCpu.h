/* vxCpu.h - VxWorks CPU definitions header */

/*
 * Copyright (c) 1984-2006, 2009-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
 * vxCpu.h is now generated -- DO NOT EDIT
 *
 * To change the boilerplate, edit vxCpu.in
 *
 * To add CPU types or otherwise change the substance,
 * edit $WIND_BASE/host/resource/target/architecturedb
 */

/*
modification history
--------------------
02m,03nov10,mze  IA CPU tag work
02l,27feb09,m_h  Typo in path in architecturedb comment
02k,20jul06,jpb  Fixed _VX_CPU and _VX_TOOL macros not being defined
02j,12jun06,jpb  Updated for POSIX namespace conformance.
                 Changed C preprocessor macro CPU to _VX_CPU.
02i,10aug01,pch  Rename to vxCpu.in, revise for use in generating vxCpu.h
                 from host/src/target/architecturedb
02m,23jul01,scm  change XScale name to conform to coding standards...
02h,07may01,kab  Fix PPC enum clashes
02l,04may01,scm  add STRONGARM support...
02g,25oct00,s_m  renamed PPC405 cpu types
02f,14jun00,alp  Added PPC405 support
02k,11dec00,scm  replace references to ARMSA2 with XScale
02j,31aug00,scm  add sa2 support under arm
02i,20jan99,cdp  marked old ARM CPU numbers 'obsoleted'.
02h,13nov98,cdp  added ARMARCH3, ARMARCH4, ARMARCH4_T.
02n,28mar01,mem  Update SH cpu numbers.
02m,14dec00,pes  Remove more obsolete MIPS CPU designations.
02m,01dec00,???  Update ARM block
02l,06oct00,ish  fix MCF5400
02k,07jul00,dh   rationalised mcf family to 2 cpus.
02j,23nov99,yvp  adding CPU_FAMILY FRV and CPU type FR500 for Fujitsu FR-V
                 (a.k.a Venus) family processors
02i,27mar00,ish  Fixed CPU identifiers in ColdFire support
02h,15mar00,dra  Added ColdFire support.
02g,12oct99,yvp  Merge from .../tor2_0_0.coretools-baseline branch to make
                 Tor2 code work with T3 main/LATEST compiler
02f,09sep99,myz  added CW4000_16 support
02f,22jul99,jld  Regularize CPU=MCOREx tags.
02e,17dec97,ur   added MCORE support.
02f,05nov97,mem  added SPARCV9 support.
02n,18oct99,dra  added CW4000, CW4011, VR4100, VR5000 and VR5400 support.
02m,13jul99,bc   Added SH7718 <-> sh3e
02l,02jul98,st   added SH7750 support (SH4).
02k,05may98,jmc  added SH-DSP and SH3-DSP support.
02j,23apr97,hk   added SH support.
02i,17aug97,tpr  added PowerPC EC 603 support.
02h,15aug97,cym  added SIMNT support.
02g,09apr98,hdn  added support for Pentium, PentiumPro.
02f,26mar97,cdp  added Thumb (ARM7TDMI_T) support.
02e,28nov96,cdp  added ARM support.
02d,12jul96,kkk  added CW4000 & R4650 support.
02c,08feb96,tpr  added PPC505 and PPC860 support.
02b,23feb96,tpr  undefined the PPC macro defined by the PowerPC Gnu.
02a,26may94,yao  added PPC support.
01k,24jul95,ism  added SIMSOLARIS support.
01j,27dec95,myz  added I960HX stuff.
01i,20mar95,kvk  added I960JX specific stuff.
01h,31oct94,kdl  removed comment-within-comment.
01f,27sep93,cd   added R4000 support.
01g,26oct94,tmk  added new cpu type MC68LC040
01f,21jul94,tpr  added MC68060 cpu.
01f,09jun93,hdn  added support for I80X86
01g,02dec93,tpr  added definition for the AMD 29200 microcontroller
	    pad  added definitions for the AMD 29030 cpu
01g,11aug93,gae  vxsim hppa.
01f,22jun93,gae  vxsim: added SIMSPARCSUNOS.
01e,13nov92,dnw  added test for correct definition of CPU
01d,22sep92,rrr  added support for c++
01c,07sep92,smb  added documentation
01b,23jul92,jwt  restored SPARClite reference omitted in file creation.
01a,11jul92,smb  CPU definitions moved from vxWorks.h.
*/

/*
DESCRIPTION
Depending on the value of CPU passed to the system by the compiler command
line, the CPU_FAMILY is defined.  This must be the first header file
included by vxWorks.h.
*/

#ifndef __INCvxCpuh
#define __INCvxCpuh

#ifdef __cplusplus
extern "C" {
#endif

/* CPU types */

/* Turn off stuff that some compilers pre-define ... */
#ifdef MC68000
#undef MC68000
#endif
#ifdef I960
#undef I960
#endif
#ifdef PPC
#undef PPC
#endif


/* Ensure CPU_FAMILY undefined initially */
#ifdef CPU_FAMILY
#undef CPU_FAMILY
#endif

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
	!defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
#ifndef CPU /* Do not want to override POSIX application if CPU already set */
#define CPU _VX_CPU /* Non-posix source files need CPU defined */
#elif !defined(_VX_CPU)
#define _VX_CPU    CPU /* backward compatibility */
#endif /* CPU */
#endif /* _POSIX_xxx_SOURCE */



/*
 *  Source information :
 *
 *  Input file                vxCpu.in, size       6588, modified Wed Dec 29 02:06:50 2010
 *  Database file       architecturedb, size      26659, modified Thu Nov 14 04:57:22 2013
 *
 */


#define _VX_MC68000	1	/* _VX_CPU */
#define _VX_MC68010	2	/* _VX_CPU */
#define _VX_MC68020	3	/* _VX_CPU */
#define _VX_MC68030	4	/* _VX_CPU */
#define _VX_MC68040	5	/* _VX_CPU */
#define _VX_MC68LC040	6	/* _VX_CPU */
#define _VX_MC68060	7	/* _VX_CPU */
#define _VX_CPU32	8	/* _VX_CPU */
#define _VX_MC680X0	9	/* _VX_CPU_FAMILY */
#define _VX_SPARC	10	/* _VX_CPU & _VX_CPU_FAMILY */
#define _VX_SPARClite	11	/* _VX_CPU */
#define _VX_I960	20	/* _VX_CPU_FAMILY */
#define _VX_I960CA	21	/* _VX_CPU */
#define _VX_I960KA	22	/* _VX_CPU */
#define _VX_I960KB	23	/* _VX_CPU */
#define _VX_I960JX	24	/* _VX_CPU */
#define _VX_I960HX	25	/* _VX_CPU */
#define _VX_TRON	30	/* _VX_CPU_FAMILY */
#define _VX_G100	31	/* _VX_CPU */
#define _VX_G200	32	/* _VX_CPU */
#define _VX_MIPS	40	/* _VX_CPU_FAMILY */
#define _VX_MIPS32	41	/* _VX_CPU */
#define _VX_MIPS64	42	/* _VX_CPU */
#define _VX_MIPSI2	43	/* _VX_CPU */
#define _VX_MIPSI3	44	/* _VX_CPU */
#define _VX_MIPSI32	45	/* _VX_CPU */
#define _VX_MIPSI32R2	46	/* _VX_CPU */
#define _VX_MIPSI64	47	/* _VX_CPU */
#define _VX_MIPSI64R2	48	/* _VX_CPU */
#define _VX_MIPS64_64	49	/* _VX_CPU */
#define _VX_AM29XXX	50	/* _VX_CPU_FAMILY */
#define _VX_AM29030	51	/* _VX_CPU */
#define _VX_AM29200	52	/* _VX_CPU */
#define _VX_AM29035	53	/* _VX_CPU */
#define _VX_SIMSPARCSUNOS	60	/* _VX_CPU & _VX_CPU_FAMILY */
#define _VX_SIMSPARCSOLARIS	61	/* _VX_CPU & _VX_CPU_FAMILY */
#define _VX_SIMHPPA	70	/* _VX_CPU & _VX_CPU_FAMILY */
#define _VX_I80X86	80	/* _VX_CPU_FAMILY */
#define _VX_I80386	81	/* _VX_CPU */
#define _VX_I80486	82	/* _VX_CPU */
#define _VX_PENTIUM	83	/* _VX_CPU */
#define _VX_PENTIUM2	84	/* _VX_CPU */
#define _VX_PENTIUM3	85	/* _VX_CPU */
#define _VX_PENTIUM4	86	/* _VX_CPU */
#define _VX_PENTIUM64	87	/* _VX_CPU */
#define _VX_CORE2	88	/* _VX_CPU */
#define _VX_X86_64	89	/* _VX_CPU */
#define _VX_PPC32	90	/* _VX_CPU & _VX_CPU_FAMILY */
#define _VX_PPC	90	/* _VX_CPU_FAMILY */
#define _VX_PPC601	91	/* _VX_CPU */
#define _VX_PPC602	92	/* _VX_CPU */
#define _VX_PPC603	93	/* _VX_CPU */
#define _VX_PPC604	94	/* _VX_CPU */
#define _VX_PPC403	95	/* _VX_CPU */
#define _VX_PPC505	96	/* _VX_CPU */
#define _VX_PPC860	97	/* _VX_CPU */
#define _VX_PPCEC603	98	/* _VX_CPU */
#define _VX_PPC555	99	/* _VX_CPU */
#define _VX_SIMNT	100	/* _VX_CPU & _VX_CPU_FAMILY */
#define _VX_SPARCV9	110	/* _VX_CPU_FAMILY */
#define _VX_ULTRASPARC	111	/* _VX_CPU */
#define _VX_ATOM	112	/* _VX_CPU */
#define _VX_CORE	113	/* _VX_CPU */
#define _VX_NEHALEM	114	/* _VX_CPU */
#define _VX_ARM	120	/* _VX_CPU_FAMILY */
#define _VX_ARM710A	121	/* _VX_CPU */
#define _VX_ARM7TDMI	122	/* _VX_CPU */
#define _VX_ARM810	123	/* _VX_CPU */
#define _VX_ARMSA110	124	/* _VX_CPU */
#define _VX_ARM7TDMI_T	125	/* _VX_CPU */
#define _VX_ARMARCH3	126	/* _VX_CPU */
#define _VX_ARMARCH4	127	/* _VX_CPU */
#define _VX_ARMARCH4_T	128	/* _VX_CPU */
#define _VX_STRONGARM	129	/* _VX_CPU */
#define _VX_SH32	130	/* _VX_CPU & _VX_CPU_FAMILY */
#define _VX_SH	130	/* _VX_CPU_FAMILY */
#define _VX_SH7000	131	/* _VX_CPU */
#define _VX_SH7600	132	/* _VX_CPU */
#define _VX_SH7040	133	/* _VX_CPU */
#define _VX_SH7700	134	/* _VX_CPU */
#define _VX_SH7410	135	/* _VX_CPU */
#define _VX_SH7729	136	/* _VX_CPU */
#define _VX_SH7750	137	/* _VX_CPU */
#define _VX_MCORE	150	/* _VX_CPU_FAMILY */
#define _VX_MCORE10	151	/* _VX_CPU */
#define _VX_MCORE15	152	/* _VX_CPU */
#define _VX_MCORE200	153	/* _VX_CPU */
#define _VX_MCORE300	154	/* _VX_CPU */
#define _VX_COLDFIRE	160	/* _VX_CPU_FAMILY */
#define _VX_MCF5200	161	/* _VX_CPU */
#define _VX_MCF5400	162	/* _VX_CPU */
#define _VX_FRV	170	/* _VX_CPU_FAMILY */
#define _VX_FR500	171	/* _VX_CPU */
#define _VX_MAP1000	180	/* _VX_CPU & _VX_CPU_FAMILY */
#define _VX_MAP	180	/* _VX_CPU_FAMILY */
#define _VX_MAP1000A	181	/* _VX_CPU */
#define _VX_MAPCA	182	/* _VX_CPU */
#define _VX_SIMLINUX	190	/* _VX_CPU & _VX_CPU_FAMILY */
#define _VX_SIMPENTIUM	191	/* _VX_CPU & _VX_CPU_FAMILY */
#define _VX_XSCALE	1120	/* _VX_CPU */
#define _VX_ARMARCH5	1121	/* _VX_CPU */
#define _VX_ARMARCH5_T	1122	/* _VX_CPU */
#define _VX_ARMARCH6	1123	/* _VX_CPU */
#define _VX_ARMARCH6_T	1124	/* _VX_CPU */
#define _VX_ARMARCH7	1125	/* _VX_CPU */
#define _VX_ARMARCH7_T2	1126	/* _VX_CPU */
#define _VX_ARMARCH7M	1127	/* _VX_CPU */
#define _VX_PPC509	2000	/* _VX_CPU */
#define _VX_PPC405	2001	/* _VX_CPU */
#define _VX_PPC405F	2002	/* _VX_CPU */
#define _VX_PPC440	2003	/* _VX_CPU */
#define _VX_PPC85XX	2004	/* _VX_CPU */
#define _VX_PPC970	2005	/* _VX_CPU */
#define _VX_PPC476	2006	/* _VX_CPU */
#define _VX_PPCE500MC	2007	/* _VX_CPU */
#define _VX_PPC465	2008	/* _VX_CPU */
#define _VX_PPC750	2010	/* _VX_CPU */
#define _VX_PPC7400	2011	/* _VX_CPU */
#define _VX_PPC8260	2012	/* _VX_CPU */
#define _VX_PPC8560	2013	/* _VX_CPU */
#define _VX_PPC64	2014	/* _VX_CPU */

#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define MC68000	_VX_MC68000	/* _VX_CPU */
#define MC68010	_VX_MC68010	/* _VX_CPU */
#define MC68020	_VX_MC68020	/* _VX_CPU */
#define MC68030	_VX_MC68030	/* _VX_CPU */
#define MC68040	_VX_MC68040	/* _VX_CPU */
#define MC68LC040	_VX_MC68LC040	/* _VX_CPU */
#define MC68060	_VX_MC68060	/* _VX_CPU */
#define CPU32	_VX_CPU32	/* _VX_CPU */
#define MC680X0	_VX_MC680X0	/* _VX_CPU_FAMILY */
#define SPARC	_VX_SPARC	/* _VX_CPU & _VX_CPU_FAMILY */
#define SPARClite	_VX_SPARClite	/* _VX_CPU */
#define I960	_VX_I960	/* _VX_CPU_FAMILY */
#define I960CA	_VX_I960CA	/* _VX_CPU */
#define I960KA	_VX_I960KA	/* _VX_CPU */
#define I960KB	_VX_I960KB	/* _VX_CPU */
#define I960JX	_VX_I960JX	/* _VX_CPU */
#define I960HX	_VX_I960HX	/* _VX_CPU */
#define TRON	_VX_TRON	/* _VX_CPU_FAMILY */
#define G100	_VX_G100	/* _VX_CPU */
#define G200	_VX_G200	/* _VX_CPU */
#define MIPS	_VX_MIPS	/* _VX_CPU_FAMILY */
#define MIPS32	_VX_MIPS32	/* _VX_CPU */
#define MIPS64	_VX_MIPS64	/* _VX_CPU */
#define MIPSI2	_VX_MIPSI2	/* _VX_CPU */
#define MIPSI3	_VX_MIPSI3	/* _VX_CPU */
#define MIPSI32	_VX_MIPSI32	/* _VX_CPU */
#define MIPSI32R2	_VX_MIPSI32R2	/* _VX_CPU */
#define MIPSI64	_VX_MIPSI64	/* _VX_CPU */
#define MIPSI64R2	_VX_MIPSI64R2	/* _VX_CPU */
#define MIPS64_64	_VX_MIPS64_64	/* _VX_CPU */
#define AM29XXX	_VX_AM29XXX	/* _VX_CPU_FAMILY */
#define AM29030	_VX_AM29030	/* _VX_CPU */
#define AM29200	_VX_AM29200	/* _VX_CPU */
#define AM29035	_VX_AM29035	/* _VX_CPU */
#define SIMSPARCSUNOS	_VX_SIMSPARCSUNOS	/* _VX_CPU & _VX_CPU_FAMILY */
#define SIMSPARCSOLARIS	_VX_SIMSPARCSOLARIS	/* _VX_CPU & _VX_CPU_FAMILY */
#define SIMHPPA	_VX_SIMHPPA	/* _VX_CPU & _VX_CPU_FAMILY */
#define I80X86	_VX_I80X86	/* _VX_CPU_FAMILY */
#define I80386	_VX_I80386	/* _VX_CPU */
#define I80486	_VX_I80486	/* _VX_CPU */
#define PENTIUM	_VX_PENTIUM	/* _VX_CPU */
#define PENTIUM2	_VX_PENTIUM2	/* _VX_CPU */
#define PENTIUM3	_VX_PENTIUM3	/* _VX_CPU */
#define PENTIUM4	_VX_PENTIUM4	/* _VX_CPU */
#define PENTIUM64	_VX_PENTIUM64	/* _VX_CPU */
#define CORE2	_VX_CORE2	/* _VX_CPU */
#define X86_64	_VX_X86_64	/* _VX_CPU */
#define PPC32	_VX_PPC32	/* _VX_CPU & _VX_CPU_FAMILY */
#define PPC	_VX_PPC	/* _VX_CPU_FAMILY */
#define PPC601	_VX_PPC601	/* _VX_CPU */
#define PPC602	_VX_PPC602	/* _VX_CPU */
#define PPC603	_VX_PPC603	/* _VX_CPU */
#define PPC604	_VX_PPC604	/* _VX_CPU */
#define PPC403	_VX_PPC403	/* _VX_CPU */
#define PPC505	_VX_PPC505	/* _VX_CPU */
#define PPC860	_VX_PPC860	/* _VX_CPU */
#define PPCEC603	_VX_PPCEC603	/* _VX_CPU */
#define PPC555	_VX_PPC555	/* _VX_CPU */
#define SIMNT	_VX_SIMNT	/* _VX_CPU & _VX_CPU_FAMILY */
#define SPARCV9	_VX_SPARCV9	/* _VX_CPU_FAMILY */
#define ULTRASPARC	_VX_ULTRASPARC	/* _VX_CPU */
#define ARM	_VX_ARM	/* _VX_CPU_FAMILY */
#define ARM710A	_VX_ARM710A	/* _VX_CPU */
#define ARM7TDMI	_VX_ARM7TDMI	/* _VX_CPU */
#define ARM810	_VX_ARM810	/* _VX_CPU */
#define ARMSA110	_VX_ARMSA110	/* _VX_CPU */
#define ARM7TDMI_T	_VX_ARM7TDMI_T	/* _VX_CPU */
#define ARMARCH3	_VX_ARMARCH3	/* _VX_CPU */
#define ARMARCH4	_VX_ARMARCH4	/* _VX_CPU */
#define ARMARCH4_T	_VX_ARMARCH4_T	/* _VX_CPU */
#define STRONGARM	_VX_STRONGARM	/* _VX_CPU */
#define SH32	_VX_SH32	/* _VX_CPU & _VX_CPU_FAMILY */
#define SH	_VX_SH	/* _VX_CPU_FAMILY */
#define SH7000	_VX_SH7000	/* _VX_CPU */
#define SH7600	_VX_SH7600	/* _VX_CPU */
#define SH7040	_VX_SH7040	/* _VX_CPU */
#define SH7700	_VX_SH7700	/* _VX_CPU */
#define SH7410	_VX_SH7410	/* _VX_CPU */
#define SH7729	_VX_SH7729	/* _VX_CPU */
#define SH7750	_VX_SH7750	/* _VX_CPU */
#define MCORE	_VX_MCORE	/* _VX_CPU_FAMILY */
#define MCORE10	_VX_MCORE10	/* _VX_CPU */
#define MCORE15	_VX_MCORE15	/* _VX_CPU */
#define MCORE200	_VX_MCORE200	/* _VX_CPU */
#define MCORE300	_VX_MCORE300	/* _VX_CPU */
#define COLDFIRE	_VX_COLDFIRE	/* _VX_CPU_FAMILY */
#define MCF5200	_VX_MCF5200	/* _VX_CPU */
#define MCF5400	_VX_MCF5400	/* _VX_CPU */
#define FRV	_VX_FRV	/* _VX_CPU_FAMILY */
#define FR500	_VX_FR500	/* _VX_CPU */
#define MAP1000	_VX_MAP1000	/* _VX_CPU & _VX_CPU_FAMILY */
#define MAP	_VX_MAP	/* _VX_CPU_FAMILY */
#define MAP1000A	_VX_MAP1000A	/* _VX_CPU */
#define MAPCA	_VX_MAPCA	/* _VX_CPU */
#define SIMLINUX	_VX_SIMLINUX	/* _VX_CPU & _VX_CPU_FAMILY */
#define SIMPENTIUM	_VX_SIMPENTIUM	/* _VX_CPU & _VX_CPU_FAMILY */
#define XSCALE	_VX_XSCALE	/* _VX_CPU */
#define ARMARCH5	_VX_ARMARCH5	/* _VX_CPU */
#define ARMARCH5_T	_VX_ARMARCH5_T	/* _VX_CPU */
#define ARMARCH6	_VX_ARMARCH6	/* _VX_CPU */
#define ARMARCH6_T	_VX_ARMARCH6_T	/* _VX_CPU */
#define ARMARCH7	_VX_ARMARCH7	/* _VX_CPU */
#define ARMARCH7_T2	_VX_ARMARCH7_T2	/* _VX_CPU */
#define ARMARCH7M	_VX_ARMARCH7M	/* _VX_CPU */
#define PPC509	_VX_PPC509	/* _VX_CPU */
#define PPC405	_VX_PPC405	/* _VX_CPU */
#define PPC405F	_VX_PPC405F	/* _VX_CPU */
#define PPC440	_VX_PPC440	/* _VX_CPU */
#define PPC85XX	_VX_PPC85XX	/* _VX_CPU */
#define PPC970	_VX_PPC970	/* _VX_CPU */
#define PPC476	_VX_PPC476	/* _VX_CPU */
#define PPCE500MC	_VX_PPCE500MC	/* _VX_CPU */
#define PPC465	_VX_PPC465	/* _VX_CPU */
#define PPC750	_VX_PPC750	/* _VX_CPU */
#define PPC7400	_VX_PPC7400	/* _VX_CPU */
#define PPC8260	_VX_PPC8260	/* _VX_CPU */
#define PPC8560	_VX_PPC8560	/* _VX_CPU */
#define PPC64	_VX_PPC64	/* _VX_CPU */
#endif /* _WRS_KERNEL */

#if	(_VX_CPU==_VX_MC68000 || \
	 _VX_CPU==_VX_MC68010 || \
	 _VX_CPU==_VX_MC68020 || \
	 _VX_CPU==_VX_MC68030 || \
	 _VX_CPU==_VX_MC68040 || \
	 _VX_CPU==_VX_MC68LC040 || \
	 _VX_CPU==_VX_MC68060 || \
	 _VX_CPU==_VX_CPU32)
#define	_VX_CPU_FAMILY	_VX_MC680X0
#define _WRS_CPU_FAMILY_PREPENDS_UNDERSCORE	TRUE
#define _VX_ARCH_DIR	mc68k
#endif	/* _VX_CPU_FAMILY==_VX_MC680X0 */

#if	(_VX_CPU==_VX_SPARC || \
	 _VX_CPU==_VX_SPARClite)
#define	_VX_CPU_FAMILY	_VX_SPARC
#define _WRS_CPU_FAMILY_PREPENDS_UNDERSCORE	TRUE
#define _VX_ARCH_DIR	sparc
#endif	/* _VX_CPU_FAMILY==_VX_SPARC */

#if	(_VX_CPU==_VX_I960CA || \
	 _VX_CPU==_VX_I960KA || \
	 _VX_CPU==_VX_I960KB || \
	 _VX_CPU==_VX_I960JX || \
	 _VX_CPU==_VX_I960HX)
#define	_VX_CPU_FAMILY	_VX_I960
#define _WRS_CPU_FAMILY_PREPENDS_UNDERSCORE	TRUE
#define _VX_ARCH_DIR	i960
#endif	/* _VX_CPU_FAMILY==_VX_I960 */

#if	(_VX_CPU==_VX_G100 || \
	 _VX_CPU==_VX_G200)
#define	_VX_CPU_FAMILY	_VX_TRON
#define _WRS_CPU_FAMILY_PREPENDS_UNDERSCORE	FALSE
#endif	/* _VX_CPU_FAMILY==_VX_TRON */

#if	(_VX_CPU==_VX_MIPS32 || \
	 _VX_CPU==_VX_MIPS64 || \
	 _VX_CPU==_VX_MIPSI2 || \
	 _VX_CPU==_VX_MIPSI3 || \
	 _VX_CPU==_VX_MIPSI32 || \
	 _VX_CPU==_VX_MIPSI32R2 || \
	 _VX_CPU==_VX_MIPSI64 || \
	 _VX_CPU==_VX_MIPSI64R2 || \
	 _VX_CPU==_VX_MIPS64_64)
#define	_VX_CPU_FAMILY	_VX_MIPS
#define _WRS_CPU_FAMILY_PREPENDS_UNDERSCORE	FALSE
#define _VX_ARCH_DIR	mips
#endif	/* _VX_CPU_FAMILY==_VX_MIPS */

#if	(_VX_CPU==_VX_AM29030 || \
	 _VX_CPU==_VX_AM29200 || \
	 _VX_CPU==_VX_AM29035)
#define	_VX_CPU_FAMILY	_VX_AM29XXX
#define _WRS_CPU_FAMILY_PREPENDS_UNDERSCORE	FALSE
#define _VX_ARCH_DIR	am29k
#endif	/* _VX_CPU_FAMILY==_VX_AM29XXX */

#if	(_VX_CPU==_VX_SIMSPARCSUNOS)
#define	_VX_CPU_FAMILY	_VX_SIMSPARCSUNOS
#define _WRS_CPU_FAMILY_PREPENDS_UNDERSCORE	TRUE
#define _VX_ARCH_DIR	simsparc
#endif	/* _VX_CPU_FAMILY==_VX_SIMSPARCSUNOS */

#if	(_VX_CPU==_VX_SIMSPARCSOLARIS)
#define	_VX_CPU_FAMILY	_VX_SIMSPARCSOLARIS
#define _WRS_CPU_FAMILY_PREPENDS_UNDERSCORE	FALSE
#define _VX_ARCH_DIR	simsolaris
#endif	/* _VX_CPU_FAMILY==_VX_SIMSPARCSOLARIS */

#if	(_VX_CPU==_VX_SIMHPPA)
#define	_VX_CPU_FAMILY	_VX_SIMHPPA
#define _WRS_CPU_FAMILY_PREPENDS_UNDERSCORE	FALSE
#define _VX_ARCH_DIR	simhppa
#endif	/* _VX_CPU_FAMILY==_VX_SIMHPPA */

#if	(_VX_CPU==_VX_I80386 || \
	 _VX_CPU==_VX_I80486 || \
	 _VX_CPU==_VX_PENTIUM || \
	 _VX_CPU==_VX_PENTIUM2 || \
	 _VX_CPU==_VX_PENTIUM3 || \
	 _VX_CPU==_VX_PENTIUM4 || \
	 _VX_CPU==_VX_PENTIUM64 || \
	 _VX_CPU==_VX_CORE2 || \
	 _VX_CPU==_VX_X86_64 || \
	 _VX_CPU==_VX_ATOM || \
	 _VX_CPU==_VX_CORE || \
	 _VX_CPU==_VX_NEHALEM)
#define	_VX_CPU_FAMILY	_VX_I80X86
#define _WRS_CPU_FAMILY_PREPENDS_UNDERSCORE	FALSE
#define _VX_ARCH_DIR	i86
#endif	/* _VX_CPU_FAMILY==_VX_I80X86 */

#if	(_VX_CPU==_VX_PPC32 || \
	 _VX_CPU==_VX_PPC601 || \
	 _VX_CPU==_VX_PPC602 || \
	 _VX_CPU==_VX_PPC603 || \
	 _VX_CPU==_VX_PPC604 || \
	 _VX_CPU==_VX_PPC403 || \
	 _VX_CPU==_VX_PPC505 || \
	 _VX_CPU==_VX_PPC860 || \
	 _VX_CPU==_VX_PPCEC603 || \
	 _VX_CPU==_VX_PPC555 || \
	 _VX_CPU==_VX_PPC509 || \
	 _VX_CPU==_VX_PPC405 || \
	 _VX_CPU==_VX_PPC405F || \
	 _VX_CPU==_VX_PPC440 || \
	 _VX_CPU==_VX_PPC85XX || \
	 _VX_CPU==_VX_PPC970 || \
	 _VX_CPU==_VX_PPC476 || \
	 _VX_CPU==_VX_PPCE500MC || \
	 _VX_CPU==_VX_PPC465 || \
	 _VX_CPU==_VX_PPC750 || \
	 _VX_CPU==_VX_PPC7400 || \
	 _VX_CPU==_VX_PPC8260 || \
	 _VX_CPU==_VX_PPC8560 || \
	 _VX_CPU==_VX_PPC64)
#define	_VX_CPU_FAMILY	_VX_PPC
#define _WRS_CPU_FAMILY_PREPENDS_UNDERSCORE	FALSE
#define _VX_ARCH_DIR	ppc
#endif	/* _VX_CPU_FAMILY==_VX_PPC */

#if	(_VX_CPU==_VX_SIMNT)
#define	_VX_CPU_FAMILY	_VX_SIMNT
#define _WRS_CPU_FAMILY_PREPENDS_UNDERSCORE	FALSE
#define _VX_ARCH_DIR	simnt
#endif	/* _VX_CPU_FAMILY==_VX_SIMNT */

#if	(_VX_CPU==_VX_ULTRASPARC)
#define	_VX_CPU_FAMILY	_VX_SPARCV9
#define _WRS_CPU_FAMILY_PREPENDS_UNDERSCORE	FALSE
#define _VX_ARCH_DIR	sparcv9
#endif	/* _VX_CPU_FAMILY==_VX_SPARCV9 */

#if	(_VX_CPU==_VX_ARM710A || \
	 _VX_CPU==_VX_ARM7TDMI || \
	 _VX_CPU==_VX_ARM810 || \
	 _VX_CPU==_VX_ARMSA110 || \
	 _VX_CPU==_VX_ARM7TDMI_T || \
	 _VX_CPU==_VX_ARMARCH3 || \
	 _VX_CPU==_VX_ARMARCH4 || \
	 _VX_CPU==_VX_ARMARCH4_T || \
	 _VX_CPU==_VX_STRONGARM || \
	 _VX_CPU==_VX_XSCALE || \
	 _VX_CPU==_VX_ARMARCH5 || \
	 _VX_CPU==_VX_ARMARCH5_T || \
	 _VX_CPU==_VX_ARMARCH6 || \
	 _VX_CPU==_VX_ARMARCH6_T || \
	 _VX_CPU==_VX_ARMARCH7 || \
	 _VX_CPU==_VX_ARMARCH7_T2 || \
	 _VX_CPU==_VX_ARMARCH7M)
#define	_VX_CPU_FAMILY	_VX_ARM
#define _WRS_CPU_FAMILY_PREPENDS_UNDERSCORE	FALSE
#define _VX_ARCH_DIR	arm
#endif	/* _VX_CPU_FAMILY==_VX_ARM */

#if	(_VX_CPU==_VX_SH32 || \
	 _VX_CPU==_VX_SH7000 || \
	 _VX_CPU==_VX_SH7600 || \
	 _VX_CPU==_VX_SH7040 || \
	 _VX_CPU==_VX_SH7700 || \
	 _VX_CPU==_VX_SH7410 || \
	 _VX_CPU==_VX_SH7729 || \
	 _VX_CPU==_VX_SH7750)
#define	_VX_CPU_FAMILY	_VX_SH
#define _WRS_CPU_FAMILY_PREPENDS_UNDERSCORE	TRUE
#define _VX_ARCH_DIR	sh
#endif	/* _VX_CPU_FAMILY==_VX_SH */

#if	(_VX_CPU==_VX_MCORE10 || \
	 _VX_CPU==_VX_MCORE15 || \
	 _VX_CPU==_VX_MCORE200 || \
	 _VX_CPU==_VX_MCORE300)
#define	_VX_CPU_FAMILY	_VX_MCORE
#define _WRS_CPU_FAMILY_PREPENDS_UNDERSCORE	FALSE
#define _VX_ARCH_DIR	mcore
#endif	/* _VX_CPU_FAMILY==_VX_MCORE */

#if	(_VX_CPU==_VX_MCF5200 || \
	 _VX_CPU==_VX_MCF5400)
#define	_VX_CPU_FAMILY	_VX_COLDFIRE
#define _WRS_CPU_FAMILY_PREPENDS_UNDERSCORE	TRUE
#define _VX_ARCH_DIR	coldfire
#endif	/* _VX_CPU_FAMILY==_VX_COLDFIRE */

#if	(_VX_CPU==_VX_FR500)
#define	_VX_CPU_FAMILY	_VX_FRV
#define _WRS_CPU_FAMILY_PREPENDS_UNDERSCORE	TRUE
#define _VX_ARCH_DIR	frv
#endif	/* _VX_CPU_FAMILY==_VX_FRV */

#if	(_VX_CPU==_VX_MAP1000 || \
	 _VX_CPU==_VX_MAP1000A || \
	 _VX_CPU==_VX_MAPCA)
#define	_VX_CPU_FAMILY	_VX_MAP
#define _WRS_CPU_FAMILY_PREPENDS_UNDERSCORE	TRUE
#define _VX_ARCH_DIR	map
#endif	/* _VX_CPU_FAMILY==_VX_MAP */

#if	(_VX_CPU==_VX_SIMLINUX)
#define	_VX_CPU_FAMILY	_VX_SIMLINUX
#define _WRS_CPU_FAMILY_PREPENDS_UNDERSCORE	FALSE
#define _VX_ARCH_DIR	simlinux
#endif	/* _VX_CPU_FAMILY==_VX_SIMLINUX */

#if	(_VX_CPU==_VX_SIMPENTIUM)
#define	_VX_CPU_FAMILY	_VX_SIMPENTIUM
#define _WRS_CPU_FAMILY_PREPENDS_UNDERSCORE	FALSE
#define _VX_ARCH_DIR	simpentium
#endif	/* _VX_CPU_FAMILY==_VX_SIMPENTIUM */

/*
 * CPU_FAMILY is needed for shared files in kernel so now we need to define
 * CPU_FAMILY based on the above setting of _VX_CPU_FAMILY.
 * Also, _VX_TOOL and _VX_TOOL_FAMILY is needed by shared header files
 * used in kernel builds so those need to be set as well
 */
#if defined(_WRS_KERNEL)
#define CPU_FAMILY _VX_CPU_FAMILY
#if defined(TOOL_FAMILY) && defined(TOOL)
#define _VX_TOOL_FAMILY TOOL_FAMILY
#define _VX_TOOL TOOL
#endif /* TOOL_FAMILY && TOOL */
#endif /* _WRS_KERNEL */

/* Non-posix source files need CPU_FAMILY, TOOL_FAMILY and TOOL to be set.
 * CPU_FAMILY is set on the above setting of _VX_CPU_FAMILY
 */

#if !defined(_WRS_KERNEL) && \
    (!defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))

#if !defined(_VX_TOOL_FAMILY) && defined(TOOL_FAMILY)
#define _VX_TOOL_FAMILY    TOOL_FAMILY
#elif defined(_VX_TOOL_FAMILY)
#define TOOL_FAMILY    _VX_TOOL_FAMILY
#endif /* !defined(_VX_TOOL_FAMILY) && defined(TOOL_FAMILY) */

#if !defined(_VX_TOOL) && defined (TOOL)
#define _VX_TOOL    TOOL
#elif defined(_VX_TOOL)
#define TOOL    _VX_TOOL
#endif /* !defined(_VX_TOOL) && defined(TOOL) */

#if !defined(_VX_CPU_FAMILY) && defined(CPU_FAMILY)
#define _VX_CPU_FAMILY CPU_FAMILY
#elif defined(_VX_CPU_FAMILY)
#define CPU_FAMILY    _VX_CPU_FAMILY
#endif /*!defined(_VX_CPU_FAMILY) && defined(CPU_FAMILY) */

#endif /* !_WRS_KERNEL && !POSIX_xxx_SOURCE */

/*
 * Check that _VX_CPU and _VX_CPU_FAMILY are now defined correctly.
 * If _VX_CPU is defined to be one of the above valid values then
 * the _VX_CPU_FAMILY will have been properly selected.
 * This is required in order to select the right headers
 * and definitions for that CPU in subsequent headers.
 * If _VX_CPU or _VX_CPU_FAMILY is not defined at this point,
 * we generate an error and abort the compilation.
 */

#if !defined(_VX_CPU) || !defined(_VX_CPU_FAMILY)
#error _VX_CPU is not defined correctly
#endif

#ifdef __cplusplus
}
#endif

#endif /* __INCvxCpuh */

/* version.h - VxWorks version information */

/* 
 * Copyright (c) 1994-1996, 1998, 2000-2001, 2003-2014 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */

/*
modification history
--------------------
04q,27mar15,jam  change version to 6.9.4.5
04p,04feb15,jam  change version to 6.9.4.4
04o,02sep14,jam  change version to 6.9.4.3
04n,09jun14,jam  change version to 6.9.4.2
04m,26feb14,jam  change version to 6.9.4.1
04l,15nov13,jam  change version to 6.9.4
04k,26jul13,jam  change version to 6.9.3.3
04j,02may13,jam  change version to 6.9.3.2
04i,12mar12,pad  Displayed digits of the version number are now handled on
		 their own (defect 273861). Full version number now presents
		 four digits if applicable.
04h,02sep11,mdk  change MAINT_VERSION to 2
04g,19may11,mdk  add minor number for 6.9.1
04f,24nov10,pad  Removed EAR string from version info.
04e,27jul10,pad  Bumped EAR number from 2 to 3. Moved this information into a
		 third qualifier.
04d,05may10,pad  Cleaned-up now that both VxWorks 32-bit and 64-bit use the
                 same minor version number.
04c,28apr10,pad  Moved extern C statement after include statements.
04b,31mar10,pad  Bumped 64-bit version name from EAR-1 to EAR-2.
04a,24feb10,mdk  6.9 version update
03z,01oct09,pad  Fixed a bug (missing space) in the definition of
                 VXWORKS_VERSION. Also reverted to release number 6.8 for the
                 32-bit VxWorks build until the host tools are ready for the
                 release 6.9.
03y,24sep09,pad  Replaced #ifndef HOST/#endif with #ifdef _WRS_KERNEL to also
                 prevent the inclusion of vsbConfig.h when used on the
		 user-side.
03x,24sep09,pad  Added #ifndef HOST/#endif around the inclusion of
                 vsbConfig.h.
03w,18sep09,pad  Introduced RUNTIME_VERSION_EXTENDED to hold the complete
		 release string.
03w,06jul09,kkz  Updating version number for VxWorks 6.8
03v,29apr08,kkz  Updating version number to 6.7
03u,05mar07,kk   update version number to 6.6
03u,15nov06,cjj  Added definition for SMP
03t,07sep06,kkz  Version number 6.5
03s,16aug06,mmg  Update version string to 6.4
03r,12may06,kkz  Changed RUNTIME_VERSION to 6.3
03q,16dec05,tam  update version to 6.3 - Beta Release
03p,28sep05,tam  removed RDR from version string
03o,01sep05,pad  Moved #ifdef _WRS_KERNEL pragma lower in the file so as to
                 allow for the build of the host-side part of vxsim.
03n,24aug05,pad  this file is now shared between kernel and user sides
		 (SPR #105066) but only the _WRS_VXWORKS_xxx macros are visible
		 on the user side.
03m,11aug05,kkz  Updating version strings for 6.2
03l,12may05,tam  changed RUNTIME_VERSION to 6.1
03k,22apr05,tam  changed RUNTIME_VERSION to 6.1 - Reference Design Release
03j,17feb05,tam  changed RUNTIME_VERSION to 6.1 - Early Access Release
03i,18oct04,dbt  change RUNTIME_VERSION to 6.0.
03h,11may04,md   add global variables for VxWorks version numbers
03g,05may04,dat  move version number macros from vxWorks.c to version.h,
		 change version to 'Beta'
03f,16mar04,rhe  Change RUNTIME_VERSION to 6.0 - Technology Access Release 2
03e,12dec03,dat  change release to 6.0, TAR version 1, added a space to
		 VXWORKS_VERSION between the name and the version.
03d,05oct03,kk   change release to 5.5 (BASE 6 - Iter 2)
03c,02jul03,job  change release to 5.5 (BASE 6 - Iter 1)
03c,25mar03,sfp  update for CP-1 release: VxWorks 5.5.1
03b,12sep01,fmk  change release to 5.5
03a,17jan01,sn   simplify job of host val  
03a,08dec00,cmf  changed release to 5.4.2
02z,08jul98,ms   changed release to 5.4.
02y,02oct96,p_m  changed release to 5.3.1.
                 removed pre 02r history.
02x,15mar96,p_m  changed release to 5.3 for everything except 960 K.
02w,06mar96,dat  removed length macros, no longer needed
02v,23jan96,tpr  changed release to 5.3-PowerPC-beta
02t,06jun95,caf  changed release to 5.2-PowerPC-beta.
02u,25oct95,ms	 changed release to 5.3
02t,21jun95,ms	 changed release to 5.3-beta
02s,29mar95,kdl  changed release to 5.2.
02r,12nov94,dvs  changed release to 5.2-beta
*/

#ifndef __INCversionh
#define __INCversionh

/*
 * CAVEAT: this file is quite sensitive and is involved in more than the build
 * of the kernel and user sides of VxWorks. It is also involved in the build
 * the VxSim executable on the host side... Therefore the inclusion of
 * vsbConfig.h is applied to target builds (and kernel environment) only.
 */

#ifdef _WRS_KERNEL
#include <vsbConfig.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Release identification, major, minor, and maintenance numbers.
 * 
 * IMPORTANT NOTE: changing any of the release identification numbers requires
 * 		   coordination with the host tools so that the PAM (Product
 * 		   Activation Matrix) files are properly updated.
 */

#define _WRS_VXWORKS_MAJOR 6
#define _WRS_VXWORKS_MINOR 9
#define _WRS_VXWORKS_MAINT 4
#define _WRS_VXWORKS_SVCPK 5

/*
 * Macro controlling what version's digits are displayed in all banners using
 * the 'vxWorksVersion' and 'runtimeVersion' global variables. The possible
 * values are:
 *  - 4: the four digits of the version number are displayed.
 *  - 3: only the three highest digits of the version number are displayed.
 *  - 2: only the two highest digits of the version number are displayed.
 *
 * When asked to display more than 2 digits, only the useful digits are
 * actually displayed. For instance even if all digits are requested the full
 * version will have two digits only if the maintenance and service pack
 * numbers are equal to zero, or will have three digits only if only the
 * service pack number is equal to zero. A null minor version number is
 * always displayed.
 */

#define ALL_VERSION_DIGITS			4
#define MAJ_MIN_AND_MAINT_VERSION_DIGITS	3
#define MAJ_AND_MIN_VERSION_DIGITS		2

#define NUM_VERSION_DIGITS_TO_DISPLAY	MAJ_AND_MIN_VERSION_DIGITS
 
/*
 ****************************************************************************
			NO VERSION SETTINGS BELOW THIS POINT
 ****************************************************************************
 */

/*
 * Some "stringification" magic to automatically set RUNTIME_VERSION with the
 * proper major and minor release numbers.
 */

#define strLvl1(s)	#s
#define strLvl2(m)	strLvl1(m)

/*
 * Backward compatibility constraint: the RUNTIME_NAME and RUNTIME_VERSION
 * macros should always hold, respectively the simple string "VxWorks" and a
 * string composed of the major release number and minor release number
 * separated by a dot.
 */

#define RUNTIME_NAME		"VxWorks"
#define RUNTIME_VERSION		strLvl2(_WRS_VXWORKS_MAJOR) "." \
				strLvl2(_WRS_VXWORKS_MINOR)

/*
 * Prepare the runtime's display and full version macros. 
 * We use only the digits that are to be displayed and are useful, per
 * the rules laid out above. For the full version macro, used by version(),
 * we use all the digits.
 */

#if (NUM_VERSION_DIGITS_TO_DISPLAY == ALL_VERSION_DIGITS && \
     _WRS_VXWORKS_SVCPK != 0)
#define RUNTIME_VERSION_BANNER	strLvl2(_WRS_VXWORKS_MAJOR) "." \
				strLvl2(_WRS_VXWORKS_MINOR) "." \
				strLvl2(_WRS_VXWORKS_MAINT) "." \
				strLvl2(_WRS_VXWORKS_SVCPK)
#elif (NUM_VERSION_DIGITS_TO_DISPLAY == MAJ_MIN_AND_MAINT_VERSION_DIGITS && \
       _WRS_VXWORKS_MAINT != 0)
#define RUNTIME_VERSION_BANNER	strLvl2(_WRS_VXWORKS_MAJOR) "." \
				strLvl2(_WRS_VXWORKS_MINOR) "." \
				strLvl2(_WRS_VXWORKS_MAINT)
#else
#define RUNTIME_VERSION_BANNER	strLvl2(_WRS_VXWORKS_MAJOR) "." \
				strLvl2(_WRS_VXWORKS_MINOR)
#endif

#if (_WRS_VXWORKS_SVCPK != 0)
#define RUNTIME_VERSION_FULL	strLvl2(_WRS_VXWORKS_MAJOR) "." \
				strLvl2(_WRS_VXWORKS_MINOR) "." \
				strLvl2(_WRS_VXWORKS_MAINT) "." \
				strLvl2(_WRS_VXWORKS_SVCPK)
#elif (_WRS_VXWORKS_MAINT != 0)
#define RUNTIME_VERSION_FULL	strLvl2(_WRS_VXWORKS_MAJOR) "." \
				strLvl2(_WRS_VXWORKS_MINOR) "." \
				strLvl2(_WRS_VXWORKS_MAINT)
#else
#define RUNTIME_VERSION_FULL	strLvl2(_WRS_VXWORKS_MAJOR) "." \
				strLvl2(_WRS_VXWORKS_MINOR)
#endif

/*
 * Additional macros used to set the qualifiers properly for all variants of
 * VxWorks.
 */

#define RUNTIME_SMP_NAME	"SMP"
#define RUNTIME_64BIT_NAME	"64-bit"

#ifdef _WRS_CONFIG_SMP
#define RUNTIME_QUALIFIER_1	" " RUNTIME_SMP_NAME
#else
#define RUNTIME_QUALIFIER_1	""
#endif

#ifdef _WRS_CONFIG_LP64
#define RUNTIME_QUALIFIER_2	" " RUNTIME_64BIT_NAME
#else
#define RUNTIME_QUALIFIER_2	""
#endif

#define RUNTIME_QUALIFIER_3	""	/* EAR version, etc. */

/*
 * The extended runtime version is the concatenation of the displayed release
 * number followed by qualifiers (currently three), possibly empty, covering the
 * variants of VxWorks.
 * For instance:
 *   RUNTIME_VERSION_EXTENDED | VERSION  QUALIFIER_1  QUALIFIER_2 QUALIFIER_3
 *   6.9                      |   6.9
 *   6.9 SMP                  |   6.9       SMP
 *   6.9 64-bit               |   6.9                   64-bit
 *   6.9 SMP 64-bit           |   6.9       SMP         64-bit
 *   6.9 64-bit EAR-1         |   6.9                   64-bit      EAR-1
 *   6.9 SMP 64-bit EAR-1     |   6.9       SMP         64-bit      EAR-1
 *
 * Note: for printLogo(), the max combined length is 44 characters.
 *
 * The extended full runtime version is essentially the same but uses all the
 * useful version digits.
 */

#define RUNTIME_VERSION_EXTENDED RUNTIME_VERSION_BANNER RUNTIME_QUALIFIER_1 \
				 RUNTIME_QUALIFIER_2 RUNTIME_QUALIFIER_3

#define RUNTIME_VERSION_FULL_EXTENDED RUNTIME_VERSION_FULL RUNTIME_QUALIFIER_1 \
				      RUNTIME_QUALIFIER_2 RUNTIME_QUALIFIER_3

/*
 * The VxWorks version is simply the concatenation of the runtime name,
 * "VxWorks", followed by a space followed by the extended runtime version
 * (as defined above).
 *
 * IMPORTANT NOTE: the order of the tokens in the VXWORKS_VERSION macro must
 *                 not be changed without coordination with the host tools.
 */

#define VXWORKS_VERSION RUNTIME_NAME " " RUNTIME_VERSION_EXTENDED

#ifdef _WRS_KERNEL 
#ifndef _ASMLANGUAGE
IMPORT char * creationDate;
IMPORT char * runtimeVersion;
IMPORT char * runtimeVersionFull;
IMPORT char * runtimeName;
IMPORT char * vxWorksVersion;

IMPORT const unsigned int vxWorksVersionMajor;
IMPORT const unsigned int vxWorksVersionMinor;
IMPORT const unsigned int vxWorksVersionMaint;
IMPORT const unsigned int vxWorksVersionSvcpk;
#endif
#endif /* _WRS_KERNEL */

#ifdef __cplusplus
}
#endif

#endif /* __INCversionh */

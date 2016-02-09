/* gtf_util.h - general timer facility - utility */

/*
 * Copyright 1984-2005, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01k,10nov10,dlk  Move extern "C" after last header file include. WIND00240828.
01j,31jan05,sar  Fix defects found in GTF code inspection of 10/26/2004
                 as described in SPRs 106685 - 105688
01i,23aug04,rp   merged from COMP_WN_IPV6_BASE6_ITER5_TO_UNIFIED_PRE_MERGE
01h,28may04,niq  Merging from base6 label POST_ITER5_FRZ16_REBASE (ver
                 /main/vdt/base6_itn5_networking-int/1)
01g,20nov03,niq  Remove copyright_wrs.h file inclusion
01f,05nov03,cdw  Removal of unnecessary _KERNEL guards.
01e,04nov03,rlm  Ran batch header path update for header re-org.
01d,03nov03,rlm  Removed wrn/coreip/ prefix from #includes for header re-org.
01c,10jun03,vvv  include netVersion.h
01b,15jan02,pas  GTF_REQUIRE[_2] should test the condition even if
                 it's not logging the errors
01a,06jun01,deg  written.
*/

#ifndef __INCgtf_utilh
#define __INCgtf_utilh

#include <netVersion.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#ifdef GTF_WITH_DEBUG
#define GTF_PRINT(s1,s2) PRINTF("**** %s : %10ld\n",s1, (unsigned long) s2) 
#else
#define GTF_PRINT(s1,s2)
#endif

#if ! defined (_FREE_VERSION)

#ifdef GTF_WITH_REQUIRE
#define GTF_REQUIRE(cond, func, diag, retVal) if(!(cond)) \
                              { \
		              GTF_ERROR_LOG(func, diag); \
		              return (retVal); \
		              }	
#define GTF_REQUIRE_2(cond, func, diag) if(!(cond)) \
                              { \
		              GTF_ERROR_LOG(func, diag); \
		              return; \
		              }	
#else /* GTF_WITH_REQUIRE */
#define GTF_REQUIRE(cond, func, diag, retVal) if(!(cond)) \
                              { \
		              return (retVal); \
		              }	
#define GTF_REQUIRE_2(cond, func, diag) if(!(cond)) \
                              { \
		              return; \
		              }	
#endif /* GTF_WITH_REQUIRE */

#else  /* defined (_FREE_VERSION) */

#define GTF_REQUIRE(cond, func, diag, retVal) do {} while (0)
#define GTF_REQUIRE_2(cond, func, diag) do {} while (0)

#endif /* defined (_FREE_VERSION) */

#define GTF_ERROR_LOG(func, diag) gtfErrorLog(__FILE__, func,__LINE__, diag);



extern void gtfErrorLog(char *file, 
			char *function, 
			int line, 
			char *diagnose
			);

#ifdef __cplusplus
}
#endif

#endif /* __INCgtf_utilh */

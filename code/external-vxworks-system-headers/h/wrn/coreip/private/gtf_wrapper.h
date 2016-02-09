/* gtf_wrapper.h - general timer facility - wrapper */

/* Copyright 2001-2003, 2005, 2010 Wind River Systems, Inc. */

/*
modification history
--------------------
01i,10nov10,dlk  Move extern "C" after last header file include. WIND00240828.
01h,31jan05,sar  Fix defects found in GTF code inspection of 10/26/2004
                 as described in SPRs 106685 - 105688
01g,20nov03,niq  Remove copyright_wrs.h file inclusion
01f,04nov03,rlm  Ran batch header path update for header re-org.
01e,03nov03,rlm  Removed wrn/coreip/ prefix from #includes for header re-org.
01d,23oct03,rlm  updated #includes for header re-org
01c,08sep03,vvv  merged from ACCORDION_BASE6_MERGE_BASELINE
01b,02feb02,ham  changed for tornado build
01a,06jun01,deg  written.
*/

#ifndef __INCgtf_wrapperh
#define __INCgtf_wrapperh

#include <private/gtf_core.h>

#ifdef __cplusplus
extern "C" {
#endif

extern GTF_TIMER *gtfTimeout(GTF_TIMER_HANDLER th,
			    void* arg,
			    unsigned int toTicks,
			    GTF_TIMER_MANAGER *tm
			    );
  
extern void gtfUntimeout(GTF_TIMER_HANDLER th,
			 void* arg,
			 GTF_TIMER *t,
			 GTF_TIMER_MANAGER *tm
			 );

extern void gtfCalloutReset(GTF_TIMER *t,
			    unsigned int toTicks,
			    GTF_TIMER_HANDLER th,
			    void* arg,
			    GTF_TIMER_MANAGER *tm
			    );
 
extern void gtfCalloutStop(GTF_TIMER *t,
			   GTF_TIMER_MANAGER *tm
			   );
  
extern void gtfCalloutInit(GTF_TIMER *t);

#ifdef __cplusplus
}
#endif

#endif /* __INCgtf_wrapperh */

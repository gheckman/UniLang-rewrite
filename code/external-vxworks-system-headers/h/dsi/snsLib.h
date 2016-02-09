/* snsLib.h - Socket Name Service library header file */

/*
 * Copyright (c) 2003-2005, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01k,28apr10,pad  Moved extern C statement after include statements.
01j,10may05,ebh  parameterize SNS server type and instance for DSAL
01i,18apr05,ebh  added parameter to snsServer declaration
                 added truncated scopy strings for snsShow command
01h,05jan05,bwa  made listen socket's backlog configurable (SPR#102955).
01g,19may04,ymz  changed for coding convention alignment.
01f,13apr04,ymz  code review changes.
01e,30mar04,ymz  changed scope expression syntax.
01d,01mar04,ymz  code review changes.
01c,09feb04,ymz  added URL support.
01b,03dec03,als  snsLib error codes now part of salLib.
01a,26nov03,als  created.
*/

#ifndef __INCsnsLibh
#define __INCsnsLibh

/* includes */

#include "vwModNum.h"
#include "dsi/salCommon.h"

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

/* define service scope string used in the URL, must be in lower case */

#define SNS_SCOPE_URL_DELIMITER         '@'

#define SNS_SCOPE_PRIVATE_STR          "private"
#define SNS_SCOPE_UPTO_PRIVATE_STR     "upto_private"
#define SNS_SCOPE_NODE_STR             "node"
#define SNS_SCOPE_UPTO_NODE_STR        "upto_node"
#define SNS_SCOPE_CLUSTER_STR          "cluster"
#define SNS_SCOPE_UPTO_CLUSTER_STR     "upto_cluster"
#define SNS_SCOPE_SYSTEM_STR           "system"
#define SNS_SCOPE_UPTO_SYSTEM_STR      "upto_system"
/* !! MAKE SURE THE NEXT ENTRY IS THE LONGEST SCOPE ENTRY - used internally !!*/
#define SNS_SCOPE_LONGEST_ENTRY_STR    "longest_scope"

#define SNS_SCOPE_SHOW_PRIVATE_STR     "priv"
#define SNS_SCOPE_SHOW_NODE_STR        "node"
#define SNS_SCOPE_SHOW_CLUSTER_STR     "clust"
#define SNS_SCOPE_SHOW_SYSTEM_STR      "systm"

#define SNS_URL_SCHEME              "sns:"

#define SNS_NUM_SCOPES  4           /* number of SNS scopes supported */

/* typedefs */

enum sns_scopes_value           /* SNS service scope */
    {
    /* define in the increasing scale and value */

    SNS_SCOPE_NONE      = -1,   /* unassigned value (used by overrideScope) */
    SNS_SCOPE_PRIVATE   = 1,    /* address space (kernel/rtp) scope */
    SNS_SCOPE_NODE      = 3,    /* local processor scope */
    SNS_SCOPE_CLUSTER   = 5,    /* multiprocessor support using TIPC */
    SNS_SCOPE_SYSTEM    = 7     /* multiprocessor support not yet available */
    };

typedef void * snsServDesc;     /* SNS service descriptor */

/* function declarations */

extern STATUS snsServer   (const int backlog, const int distributedFlag,
		          const int snsServerType, const int snsServerInstance);
extern void snsShow       (const char * name);
extern STATUS dsalMonitor (const unsigned int dsalSnsServerType,
			   const unsigned int dsalSnsServerInstance);

#ifdef __cplusplus
}
#endif

#endif /* __INCsnsLibh */

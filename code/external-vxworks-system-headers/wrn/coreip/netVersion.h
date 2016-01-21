/* netVersion.h - Network stack version information */

/* Copyright 2003 - 2006 Wind River Systems, Inc. */

/*
modification history
--------------------
01h,15aug06,spw  updated to version 3.1.2
01g,28mar06,dlk  updated to version 3.1
01f,13jul05,vvv  updated version to 3.0
01e,24jun05,vvv  updated version to 2.2
01d,07apr05,vvv  updated version
01c,23aug04,rp   merged from COMP_WN_IPV6_BASE6_ITER5_TO_UNIFIED_PRE_MERGE
01b,28may04,niq  Merging from base6 label POST_ITER5_FRZ16_REBASE (ver
                 /main/IPV6_alameda/base6_itn5_networking-int/1)
01a,11jun03,vvv  written
*/

#ifndef __INCnetVersionh
#define __INCnetVersionh

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#define STACK_NAME_V4    1       /* Classic IPv4 only stack */
#define STACK_NAME_V4_V6 2       /* Dual IPv4, IPv6 stack */

#define STACK_NAME       STACK_NAME_V4_V6

#define STACK_VERSION_MAJOR 3
#define STACK_VERSION_MINOR 1
#define STACK_VERSION_PATCH 2 
#define STACK_VERSION_PATCH_MINOR 0

#ifdef __cplusplus
}
#endif

#endif /* __INCnetVersionh */

/* intrinsics.h - map INCLUDE_INTRINSICS to toolchain specific intrinsics */

/* Copyright 2010 Wind River Systems, Inc. */

/*
modification history
--------------------
01b,02mar10,gvm  icc requires gnu
01a,25feb10,mze  created from gnu version
*/

/*
DESCRIPTION
Map INCLUDE_INTRINSICS to INCLUDE_ICC_INTRINSICS. Included when TOOL_FAMILY=icc.
 
NOMANUAL
*/

#ifdef INCLUDE_INTRINSICS
#ifndef INCLUDE_ICC_INTRINSICS
#define INCLUDE_ICC_INTRINSICS
#ifndef	INCLUDE_GNU_INTRINSICS
#define INCLUDE_GNU_INTRINSICS
#endif
#endif
#endif

/*	Copyright (c) 2011 Wind River Systems, Inc.				*/
/*	All Rights Reserved							*/
/*	Implementation module : tcasm.h						*/
/*										*/
/*	Description :								*/
/*	This module provides access to the target assembly instructions		*/
/*	through intrinsic function prototypes.					*/


#ifndef	SUPPRESS_INTRINSIC_FUNCTIONS

extern int _abs( int) __attribute__((intrinsic_pseudo(1, "abs") ));
extern int _absdif( int,  int) __attribute__((intrinsic_pseudo(1, "absdif") ));
extern int _absdifs( int,  int) __attribute__((intrinsic_pseudo(1, "absdifs") ));
extern int _abss( int) __attribute__((intrinsic_pseudo(1, "abss") ));
extern int _adds( int,  int) __attribute__((intrinsic_pseudo(1, "adds") ));
extern void _bisr( const unsigned int) __attribute__((intrinsic_function(0x100, 0, "bisr") ));
extern int _bmerge( int,  int) __attribute__((intrinsic_pseudo(1, "bmerge") ));
extern int _clo( int) __attribute__((intrinsic_pseudo(1, "clo") ));
extern int _cls( int) __attribute__((intrinsic_pseudo(1, "cls") ));
extern int _clz( int) __attribute__((intrinsic_pseudo(1, "clz") ));
extern void _debug( void) __attribute__((intrinsic_function(0x103, 0, "debug") ));
extern void _disable( void) __attribute__((intrinsic_function(0x103, 0, "disable") ));
extern void _dsync( void) __attribute__((intrinsic_function(0x103, 0, "dsync") ));
extern void _enable( void) __attribute__((intrinsic_function(0x103, 0, "enable") ));
extern void _isync( void) __attribute__((intrinsic_function(0x103, 0, "isync") ));
extern int _max( int,  int) __attribute__((intrinsic_pseudo(3, "max") ));
extern int _mfcr( const unsigned int) __attribute__((intrinsic_function(0x101, 0, "mfcr") ));
extern int _min( int,  int) __attribute__((intrinsic_pseudo(3, "min") ));
extern void _mtcr( const unsigned int,  int) __attribute__((intrinsic_function(0x102, 0, "mtcr") ));
extern void _nop( void) __attribute__((intrinsic_function(0x103, 0, "nop") ));
extern void _restore( int) __attribute__((intrinsic_function(0x104, 0, "restore") ));
extern void _rslcx( void) __attribute__((intrinsic_function(0x103, 0, "rslcx") ));
extern void _rstv( void) __attribute__((intrinsic_function(0x103, 0, "rstv") ));
extern void _svlcx( void) __attribute__((intrinsic_function(0x103, 0, "svlcx") ));
extern void _syscall( const unsigned int) __attribute__((intrinsic_function(0x100, 0, "syscall") ));
extern void _trapsv( void) __attribute__((intrinsic_function(0x103, 0, "trapsv") ));
extern void _trapv( void) __attribute__((intrinsic_function(0x103, 0, "trapv") ));

#endif	/* SUPPRESS_INTRINSIC_FUNCTIONS */

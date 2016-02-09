/*	Copyright (c) 2010 Wind River Systems, Inc.				*/
/*	All Rights Reserved							*/
/*	Implementation module : mipsasm.h					*/
/*										*/
/*	Description :								*/
/*	This module provides access to the target assembly instructions		*/
/*	through intrinsic function prototypes.					*/


#ifndef	SUPPRESS_INTRINSIC_FUNCTIONS

extern int __cfc2( const unsigned int) __attribute__((intrinsic_function(1, 0, "cfc2") ));
extern int __cfc3( const unsigned int) __attribute__((intrinsic_function(1, 0, "cfc3") ));
extern int __clo( int) __attribute__((intrinsic_function(7, 0, "clo") ));
extern int __clz( int) __attribute__((intrinsic_function(7, 0, "clz") ));
extern void __ctc2( const unsigned int,  int) __attribute__((intrinsic_function(2, 0, "ctc2") ));
extern void __ctc3( const unsigned int,  int) __attribute__((intrinsic_function(2, 0, "ctc3") ));
extern int __di( void) __attribute__((intrinsic_function(3, 0, "di") ));
extern void __ei( int) __attribute__((intrinsic_function(4, 0, "ei") ));
extern int __mfc0( const unsigned int) __attribute__((intrinsic_function(1, 0, "mfc0") ));
extern int __mfc3( const unsigned int) __attribute__((intrinsic_function(1, 0, "mfc3") ));
extern void __mtc0( const unsigned int,  int) __attribute__((intrinsic_function(2, 0, "mtc0") ));
extern void __mtc2( const unsigned int,  int) __attribute__((intrinsic_function(2, 0, "mtc2") ));
extern void __mtc3( const unsigned int,  int) __attribute__((intrinsic_function(2, 0, "mtc3") ));
extern void __nop( void) __attribute__((intrinsic_function(8, 0, "nop") ));
extern void __ssnop( void) __attribute__((intrinsic_function(8, 0, "ssnop") ));
extern void __teq( int,  int) __attribute__((intrinsic_function(5, 0, "teq") ));
extern void __teqi( int,  const signed int) __attribute__((intrinsic_function(6, 0, "teqi") ));
extern void __tge( int,  int) __attribute__((intrinsic_function(5, 0, "tge") ));
extern void __tgei( int,  const signed int) __attribute__((intrinsic_function(6, 0, "tgei") ));
extern void __tgeiu( unsigned int,  const unsigned int) __attribute__((intrinsic_function(6, 0, "tgeiu") ));
extern void __tgeu( unsigned int,  unsigned int) __attribute__((intrinsic_function(5, 0, "tgeu") ));
extern void __tlt( int,  int) __attribute__((intrinsic_function(5, 0, "tlt") ));
extern void __tlti( int,  const signed int) __attribute__((intrinsic_function(6, 0, "tlti") ));
extern void __tltiu( unsigned int,  const unsigned int) __attribute__((intrinsic_function(6, 0, "tltiu") ));
extern void __tltu( unsigned int,  unsigned int) __attribute__((intrinsic_function(5, 0, "tltu") ));
extern void __tne( int,  int) __attribute__((intrinsic_function(5, 0, "tne") ));
extern void __tnei( int,  const signed int) __attribute__((intrinsic_function(6, 0, "tnei") ));

#endif	/* SUPPRESS_INTRINSIC_FUNCTIONS */

/* mathP.h - private definitions for math functions */

/*
 * Copyright 1990-1992, 1997, 2001, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 *
 */

/*
modification history
--------------------
01j,16apr10,mcm  Fixed WIND00192604 - the structure DOUBLE had not been
                 adapted to LP64. The members l1 and l2 should be 32-bit
                 integers not long.
01i,03oct01,to   use IEEE little endian for ARM
01h,23jan97,cdp  reverse words in double for ARM.
01g,22sep92,rrr  added support for c++
01f,04sep92,wmd  modified definition of DOUBLE for BIG/LITTLE ENDIAN architectures.
01e,30jul92,kdl  added fp type test macros; deleted declarations of unused
		 routines (isnan(), etc.); changed _d_type() to fpTypeGet();
		 deleted prototypes for _dNormalize, _finite, _upscale.
01d,30jul92,kdl  added DOUBLE union definition, from floatLib.c.
01c,08jul92,smb  added to clib library.
01b,04oct91,rrr  passed through the ansification filter
		  -fixed #else and #endif
		    -changed copyright notice
01a,14sep90,mcl  adapted from Berkeley.
*/

#ifndef __INCmathPh
#define __INCmathPh

#ifdef __cplusplus
extern "C" {
#endif

#define ZERO 	0
#define REAL 	1
#define INTEGER 2
#define INF 	3
#define NAN 	4

#define isNan(num) 	((fpTypeGet (num, 0)) == NAN)
#define isZero(num) 	((fpTypeGet (num, 0)) == ZERO)
#define isInf(num) 	((fpTypeGet (num, 0)) == INF)

typedef union
    {
    unsigned p_mant[2];
    double p_double;
    } __cv_type;

#define p_mantlow p_mant[0]
#define p_manthigh p_mant[1]


typedef union	/* DOUBLE */
    {
    double ddat;
#if (_BYTE_ORDER == _BIG_ENDIAN)
    struct
        {
        int l1;
        int l2;
        } ldat;
#else
    struct
        {
        int l2;
        int l1;
        } ldat;
#endif /* _BYTE_ORDER == _BIG_ENDIAN */
    } DOUBLE;

/* function declarations */

#if defined(__STDC__) || defined(__cplusplus)

extern int fpTypeGet (double v, double *r);

#else	/* __STDC__ */

extern int fpTypeGet();

#endif	/* __STDC__ */

#ifdef __cplusplus
}
#endif

#endif /* __INCmathPh */

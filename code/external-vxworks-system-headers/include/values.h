#ifndef __Ivalues
#define __Ivalues

#include <limits.h>
#include <float.h>

#define BITSPERBYTE	CHAR_BIT
#define BITS(t)		((int)(CHAR_BIT * sizeof(t)))

#define _HIBIT(t)	((t)(1L << BITS(t)-1))
#define HIBITS		_HIBIT(short)
#define HIBITI		_HIBIT(int)
#define HIBITL		_HIBIT(long)

#define MAXSHORT	SHRT_MAX
#define MAXINT		INT_MAX
#define MAXLONG		LONG_MAX

#define MAXDOUBLE	DBL_MAX
#define MAXFLOAT	FLT_MAX
#define MINDOUBLE	DBL_MIN
#define MINFLOAT	FLT_MIN

#define DMAXEXP		DBL_MAX_EXP
#define DMINEXP		DBL_MIN_EXP
#define FMAXEXP		FLT_MAX_EXP
#define FMINEXP		FLT_MIN_EXP

#define DSIGNIF		DBL_MANT_DIG
#define FSIGNIF		FLT_MANT_DIG

#define M_PI		3.1415926535897932384626
#define M_LN2		0.6931471805599453094172
#define M_SQRT2		1.4142135623730950488016

#define DMAXPOWTWO	((double)(1L << BITS(long)-2) * (1L << DBL_MANT_DIG-BITS(long)+1))
#define FMAXPOWTWO	((float)(1L << FLT_MANT_DIG-1))
#define LN_MAXDOUBLE	(M_LN2*(double)DBL_MAX_EXP)
#define LN_MINDOUBLE	(M_LN2*(double)(DBL_MIN_EXP-1))
#define LN_DENDOUBLE	(M_LN2*(double)(DBL_MIN_EXP-1-DBL_MANT_DIG))
#define H_PREC		(DBL_MANT_DIG&1 ? M_SQRT2*(double)(1L<<(DBL_MANT_DIG/2)) : (double)(1L<<(DBL_MANT_DIG/2)))
#define X_EPS		(1.0/H_PREC)
#define X_PLOSS		((double)(long)(M_PI * H_PREC))
#define X_TLOSS		(M_PI * DMAXPOWTWO)

#endif

#ifndef __Idiab_float
#define __Idiab_float

#define _IEEE		1

#define FLT_RADIX	2
#define FLT_ROUNDS	-1
#define FLT_MANT_DIG	24
#define FLT_EPSILON	1.19209290E-07F
#ifndef FLT_DIG
#define FLT_DIG		6
#endif
#define FLT_MIN_EXP	(-125)
#ifndef FLT_MIN
#define FLT_MIN		1.17549435E-38F
#endif
#define FLT_MIN_10_EXP	(-37)
#define FLT_MAX_EXP	128
#ifndef FLT_MAX
#define FLT_MAX		3.40282347E38F
#endif
#define FLT_MAX_10_EXP	38

#define DBL_MANT_DIG	53
#define DBL_EPSILON	2.2204460492503131E-16
#ifndef DBL_DIG
#define DBL_DIG		15
#endif
#define DBL_MIN_EXP	(-1021)
#ifndef DBL_MIN
#define DBL_MIN		2.2250738585072016E-308
#endif
#define DBL_MIN_10_EXP	(-307)
#define DBL_MAX_EXP	1024
#ifndef DBL_MAX
#define DBL_MAX		1.7976931348623157E308
#endif
#define DBL_MAX_10_EXP	308

#ifdef __LDBL__

#define LDBL_MANT_DIG	63
#define LDBL_EPSILON	2.168404345E-19L
#define LDBL_DIG	18
#define LDBL_MIN_EXP	(-16381)
#define LDBL_MIN	8E-4933L
#define LDBL_MIN_10_EXP	(-4932)
#define LDBL_MAX_EXP	16384
#define LDBL_MAX	6E4931L
#define LDBL_MAX_10_EXP	4931

#else

#define LDBL_MANT_DIG	DBL_MANT_DIG
#define LDBL_EPSILON	DBL_EPSILON
#define LDBL_DIG	DBL_DIG
#define LDBL_MIN_EXP	DBL_MIN_EXP
#define LDBL_MIN	DBL_MIN
#define LDBL_MIN_10_EXP	DBL_MIN_10_EXP
#define LDBL_MAX_EXP	DBL_MAX_EXP
#define LDBL_MAX	DBL_MAX
#define LDBL_MAX_10_EXP	DBL_MAX_10_EXP

#endif
#endif

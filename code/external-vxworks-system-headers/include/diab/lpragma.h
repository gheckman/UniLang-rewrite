/*	lpragma.h
 *
 *	This file contains pragmas describing the ANSI C libraries
 *	so the compiler can do more optimizations.
 *
 *	It is included before all other files.
 */

/*	internal functions	*/

#pragma pure_function __DIAB_rd_pk, __DIAB_rd_sw, __DIAB_rd_pk_sw
#pragma nodebug_function __DIAB_rd_pk, __DIAB_rd_sw, __DIAB_rd_pk_sw

#ifndef __RTP__
#ifndef __cplusplus

/*	errno.h		*/

#pragma pure_function __errno_fn

/*	math.h		*/

#pragma pure_function acos(errno), asin(errno), atan(errno), atan2(errno)
#pragma pure_function cos(errno), sin(errno), tan(errno), cosh(errno)
#pragma pure_function sinh(errno), tanh(errno), exp(errno)
#pragma pure_function ldexp(errno), log(errno), log10(errno)
#pragma pure_function pow(errno), sqrt(errno), ceil, fabs
#pragma pure_function floor, fmod(errno)

#pragma no_side_effects atanf, ceilf, fabsf

/*	setjmp.h	*/

#pragma no_return longjmp

/*	stdlib.h	*/

#pragma no_side_effects atof, atoi, atol
#pragma no_side_effects strtod(2,errno), strtol(2,errno), strtoul(2,errno)
#pragma no_side_effects rand, srand
#pragma no_side_effects calloc, free(1), malloc, realloc(1)
#pragma no_return abort, exit, _exit
#pragma no_side_effects getenv
#pragma pure_function abs, div, labs, ldiv

/*	stdio.h		*/

#pragma no_side_effects __flsbuf(2,errno), __filbuf(1,errno)
#pragma no_side_effects _flsbuf(2,errno), _filbuf(1,errno)
#pragma no_side_effects fprintf(1,errno)


/*	string.h	*/

#pragma no_side_effects memcpy(1), memmove(1), strcpy(1), strncpy(1)
#pragma no_side_effects strcat(1), strncat(1), memset(1)

#pragma no_side_effects memcmp, strcmp, strncmp, memchr, strchr, strrchr
#pragma no_side_effects strstr, strlen

/*	time.h		*/

#pragma no_side_effects clock, time

/*	ctype.h		*/

#pragma no_side_effects isalnum, isalpha, isascii, iscntrl, isdigit
#pragma no_side_effects isgraph, islower, isupper, isprint, ispunct
#pragma no_side_effects isspace, isxdigit

#else
#ifdef __ETOA__
/*
 *	C++ specific information is less precise to
 *	avoid scoping problems.
 */

#include <xmacros.h>

#if __STRICT_ANSI__
#define _ATTRIBUTE(x)
#else
#define _ATTRIBUTE(x) __attribute__((x))
#endif

/*	errno.h		*/

_C_LIB_DECL
extern _ATTRIBUTE(pure_function) int *__errno_fn(void);
_END_C_LIB_DECL


/*	math.h		*/

_C_LIB_DECL
extern double _ATTRIBUTE(pure_function) ceil(double);
extern double _ATTRIBUTE(pure_function) fabs(double);
extern double _ATTRIBUTE(pure_function) floor(double);
_END_C_LIB_DECL


/*	stdlib.h	*/

_C_STD_BEGIN
_C_LIB_DECL

extern double _ATTRIBUTE(no_side_effects) atof(const char *);
extern int    _ATTRIBUTE(no_side_effects) atoi(const char *);
extern long   _ATTRIBUTE(no_side_effects) atol(const char *);
extern int    _ATTRIBUTE(no_side_effects) rand(void);
extern char   _ATTRIBUTE(no_side_effects) *getenv(const char *);

extern int    _ATTRIBUTE(pure_function) abs(int);
extern long   _ATTRIBUTE(pure_function) labs(long);

extern void   _ATTRIBUTE(no_return) abort(void);
extern void   _ATTRIBUTE(no_return) exit(int);
extern void   _ATTRIBUTE(no_return) _exit(int);

_END_C_LIB_DECL
_C_STD_END


/*	string.h	*/

_C_STD_BEGIN
_C_LIB_DECL

extern int   _ATTRIBUTE(no_side_effects) strcmp(const char *, const char *);
extern char  _ATTRIBUTE(no_side_effects) *strchr(const char *, int);
extern char  _ATTRIBUTE(no_side_effects) *strrchr(const char *, int);
extern char  _ATTRIBUTE(no_side_effects) *strstr(const char *, const char *);

_END_C_LIB_DECL
_C_STD_END

#endif /* __ETOA__    */
#endif /* __cplusplus */

/* Put ANSI functions here so compiler will know if varargs functions called */

#ifndef __skip_ansi_vararg_prototypes
#ifndef __cplusplus
extern int printf(const char *, ...);
extern int scanf(const char *, ...);
extern int sprintf(char *, const char *, ...);
extern int sscanf(const char *, const char *, ...);
#endif
#endif

#endif /* __RTP__ */

#ifdef _RTC_ENABLED
#ifdef __cplusplus
extern "C" {
#endif
void __rtc_incl_mem(void *, unsigned int);
void __rtc_excl_mem(void *, unsigned int);
void __rtc_incl_auto0(void **, void *, unsigned int);
void __rtc_incl_auto(void **, void *, unsigned int, unsigned int);
void __rtc_excl_auto0(void **);
void __rtc_excl_auto(void **, unsigned int);
void __rtc_init(void);
void *__rtc_chk(void *, int, unsigned int);
void *__rtc_chk_at(void *, int, void *, int, unsigned int);
void *__rtc_inc_op_at(void *, int, void **, int);
void *__rtc_op_inc_at(void *, int, void **, int);
#ifdef __cplusplus
}
#endif
#endif

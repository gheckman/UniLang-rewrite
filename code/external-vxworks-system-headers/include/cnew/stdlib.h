/* stdlib.h standard header */
#ifndef _STDLIB
#define _STDLIB
#ifndef _YVALS
 #include <yvals.h>
#endif /* _YVALS */

_C_STD_BEGIN

		/* MACROS */
#ifndef NULL
 #define NULL	_NULL
#endif /* NULL */

#define EXIT_FAILURE	_EXFAIL
#define EXIT_SUCCESS	0

#define MB_CUR_MAX	_CSTD _Getmbcurmax()

 #if _ILONG
  #define RAND_MAX	0x3fffffff

 #else /* _ILONG */
  #define RAND_MAX	0x7fff
 #endif /* _ILONG */

 #ifndef _NO_RETURN
  #define _NO_RETURN(fun)	void fun
 #endif /* _NO_RETURN */

		/* TYPE DEFINITIONS */

 #if !defined(_SIZE_T) && !defined(_SIZET) && !defined(_SIZE_T_DEFINED) \
	&& !defined(_BSD_SIZE_T_DEFINED_)
  #define _SIZE_T
  #define _SIZET
  #define _BSD_SIZE_T_DEFINED_
  #define _SIZE_T_DEFINED
  #define _STD_USING_SIZE_T
typedef _Sizet size_t;
 #endif /* !defined(_SIZE_T) etc. */

 #if !defined(_WCHART) && !defined(_WCHAR_T_DEFINED)
  #define _WCHART
  #define _WCHAR_T_DEFINED
typedef _Wchart wchar_t;
 #endif /* _WCHART etc. */

typedef struct
	{	/* result of int divide */
	int quot;
	int rem;
	} div_t;

typedef struct
	{	/* result of long divide */
	long quot;
	long rem;
	} ldiv_t;

 #ifndef _LLDIV_T
typedef struct
	{	/* result of long long divide */
	_Longlong quot;
	_Longlong rem;
	} _Lldiv_t;
 #endif /* _LLDIV_T */

 #if _HAS_C9X
typedef _Lldiv_t lldiv_t;
 #endif /* _IS_C9X */

		/* DECLARATIONS */
_EXTERN_C /* low-level functions */
_NO_RETURN(exit(int));

_NO_RETURN(_Exit(int));	/* added with C99 */
char *getenv(const char *);
int system(const char *);
_END_EXTERN_C

_C_LIB_DECL
int abs(int);
long labs(long);
_NO_RETURN(abort(void));
void *calloc(size_t, size_t);
div_t div(int, int);
void free(void *);
ldiv_t ldiv(long, long);
void *malloc(size_t);
int mblen(const char *, size_t);
size_t mbstowcs(wchar_t *_Restrict,
	const char *_Restrict, size_t);
int mbtowc(wchar_t *_Restrict, const char *_Restrict, size_t);
int rand(void);
void srand(unsigned int);
void *realloc(void *, size_t);
long strtol(const char *_Restrict, char **_Restrict, int);
size_t wcstombs(char *_Restrict,
	const wchar_t *_Restrict, size_t);
int wctomb(char *, wchar_t);

 #if _ADDED_C_LIB
  #if (defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE != 200112L)) || defined(_XOPEN_SOURCE) || \
	defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)  /* XSI options */
char *mktemp(char *);
int putenv(char *);
  #endif  /* _POSIX_xxx_SOURCE */

int rand_r(unsigned *);

  #if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
	!defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
int getopt(int, char *const *, const char *);
char *tempnam(const char *, const char *);

extern char *optarg;
extern int optind, opterr, optopt;
  #endif  /* _POSIX_xxx_SOURCE */
 #endif /* _ADDED_C_LIB */

 #ifndef _NO_WINDRIVER_MODIFICATIONS
  #ifndef _AVOID_NON_ANSI
int rand_r(unsigned *);
int setenv(const char *, const char *, int);
int unsetenv(const char *);
  #endif

  #if !defined(__STRICT_ANSI__)
   #define __USE_POSIX
  #endif 

  #ifdef __USE_POSIX
   #if (_POSIX_C_SOURCE != 200112L) || defined(_XOPEN_SOURCE) || \
	defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)  /* XSI options */
long a64l(const char *);
char *l64a(long);
double drand48(void);
double erand48(unsigned short *);
long jrand48(unsigned short *);
void lcong48(unsigned short *);
long lrand48(void);
long mrand48(void);
long nrand48(unsigned short *);
void srand48(long);
unsigned short *seed48(unsigned short *);
   #endif  /* _POSIX_xxx_SOURCE */
   #if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
		!defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
long irand48(unsigned short);
long krand48(unsigned short *, unsigned short);
   #endif  /* _POSIX_xxx_SOURCE */
  #endif
 #endif /* !_NO_WINDRIVER_MODIFICATIONS */

unsigned long _Stoul(const char *, char **, int);
float _Stof(const char *, char **, long);
double _Stod(const char *, char **, long);
long double _Stold(const char *, char **, long);
_Longlong _Stoll(const char *, char **, int);
_ULonglong _Stoull(const char *, char **, int);

float _Stofx(const char *, char **, long, int *);
double _Stodx(const char *, char **, long, int *);
long double _Stoldx(const char *, char **, long, int *);
long _Stolx(const char *, char **, int, int *);
unsigned long _Stoulx(const char *, char **, int, int *);

size_t _Getmbcurmax(void);

 #if _HAS_C9X
_Longlong llabs(_Longlong);
lldiv_t lldiv(_Longlong, _Longlong);
 #endif /* _IS_C9X */

_END_C_LIB_DECL

 #if defined(__cplusplus) && !defined(_NO_CPP_INLINES)
_EXTERN_C
typedef void _Atexfun(void);
typedef int _Cmpfun(const void *, const void *);

int atexit(void (*)(void));
void *bsearch(const void *, const void *,
	size_t, size_t, _Cmpfun *);
void qsort(void *, size_t, size_t, _Cmpfun *);
_END_EXTERN_C

  #if _HAS_STRICT_LINKAGE
typedef int _Cmpfun2(const void *, const void *);

inline int atexit(void (*_Pfn)(void))
	{	// register a function to call at exit
	return (atexit((_Atexfun *)_Pfn));
	}

inline void *bsearch(const void *_Key, const void *_Base,
	size_t _Nelem, size_t _Size, _Cmpfun2 *_Cmp)
	{	// search by binary chop
	return (bsearch(_Key, _Base, _Nelem, _Size, (_Cmpfun *)_Cmp));
	}

inline void qsort(void *_Base,
	size_t _Nelem, size_t _Size, _Cmpfun2 *_Cmp)
	{	// sort
	qsort(_Base, _Nelem, _Size, (_Cmpfun *)_Cmp);
	}
  #endif /* _HAS_STRICT_LINKAGE */

		// INLINES, FOR C++
_C_LIB_DECL
inline double atof(const char *_Str)
	{	// convert string to double
	return (_Stod(_Str, 0, 0));
	}

inline int atoi(const char *_Str)
	{	// convert string to int
	return ((int)_Stoul(_Str, 0, 10));
	}

inline long atol(const char *_Str)
	{	// convert string to long
	return ((long)_Stoul(_Str, 0, 10));
	}

 #if defined(__APPLE__) && 3 <= __GNUC__	/* compiler test */
double strtod(const char *_Restrict,
	char **_Restrict);
unsigned long strtoul(const char *_Restrict,
	char **_Restrict, int);

 #else /* defined(__APPLE__) && 3 <= __GNUC__ */
inline double strtod(const char *_Restrict _Str,
	char **_Restrict _Endptr)
	{	// convert string to double, with checking
	return (_Stod(_Str, _Endptr, 0));
	}

inline unsigned long strtoul(const char *_Restrict _Str,
	char **_Restrict _Endptr, int _Base)
	{	// convert string to unsigned long, with checking
	return (_Stoul(_Str, _Endptr, _Base));
	}
 #endif /* defined(__APPLE__) && 3 <= __GNUC__ */

 #if _HAS_C9X
inline _Longlong atoll(const char *_Str)
	{	// convert string to long long
	return ((_Longlong)_Stoull(_Str, 0, 10));
	}

inline float strtof(const char *_Restrict _Str,
	char **_Restrict _Endptr)
	{	// convert string to float, with checking
	return (_Stof(_Str, _Endptr, 0));
	}

inline long double strtold(const char *_Restrict _Str,
	char **_Restrict _Endptr)
	{	// convert string to long double, with checking
	return (_Stold(_Str, _Endptr, 0));
	}

inline _Longlong strtoll(const char *_Restrict _Str,
	char **_Restrict _Endptr, int _Base)
	{	// convert string to long long, with checking
	return (_Stoll(_Str, _Endptr, _Base));
	}

inline _ULonglong strtoull(const char *_Restrict _Str,
	char **_Restrict _Endptr, int _Base)
	{	// convert string to unsigned long long, with checking
	return (_Stoull(_Str, _Endptr, _Base));
	}
 #endif /* _IS_C9X */

_END_C_LIB_DECL

		// OVERLOADS, FOR C++

  #if !defined(_LLDIV_T) || defined(_LONGLONG)
   #ifndef _NO_WINDRIVER_MODIFICATIONS
extern "C++" {
   #endif /* !_NO_WINDRIVER_MODIFICATIONS */
inline long abs(long _Left)
	{	// compute abs
	return (labs(_Left));
	}

inline ldiv_t div(long _Left, long _Right)
	{	// compute quotient and remainder
	return (ldiv(_Left, _Right));
	}
   #ifndef _NO_WINDRIVER_MODIFICATIONS
}
   #endif /* !_NO_WINDRIVER_MODIFICATIONS */
  #endif /* !defined(_LLDIV_T) || defined(_LONGLONG) */

 #ifndef _NO_WINDRIVER_MODIFICATIONS
extern "C++" {
 #endif /* !_NO_WINDRIVER_MODIFICATIONS */

 #if _HAS_C9X

  #if !defined(_LLDIV_T) && defined(_LONGLONG)
inline _Longlong abs(_Longlong _Left)
	{	// compute abs
	return (llabs(_Left));
	}

inline _Lldiv_t div(_Longlong _Left, _Longlong _Right)
	{	// compute quotient and remainder
	return (lldiv(_Left, _Right));
	}
  #endif /* !defined(_LLDIV_T) && defined(_LONGLONG) */

 #endif /* _IS_C9X */

 #ifndef _NO_WINDRIVER_MODIFICATIONS
}
 #endif /* !_NO_WINDRIVER_MODIFICATIONS */

 #else /* defined(__cplusplus) && !defined(_NO_CPP_INLINES) */
_C_LIB_DECL
		/* DECLARATIONS AND MACRO OVERRIDES, FOR C */
typedef int _Cmpfun(const void *, const void *);

/* */ int atexit(void (*)(void));
void *bsearch(const void *, const void *,
	size_t, size_t, _Cmpfun *);
void qsort(void *, size_t, size_t, _Cmpfun *);

double atof(const char *);
int atoi(const char *);
long atol(const char *);
double strtod(const char *_Restrict, char **_Restrict);
unsigned long strtoul(const char *_Restrict,
	char **_Restrict, int);

#define atof(str)	_Stod(str, 0, 0)
#define atoi(str)	(int)_Stoul(str, 0, 10)
#define atol(str)	(long)_Stoul(str, 0, 10)
#define strtod(str, endptr)	_Stod(str, endptr, 0)
#define strtoul(str, endptr, base)	_Stoul(str, endptr, base)

 #if _HAS_C9X
_Longlong atoll(const char *);
float strtof(const char *_Restrict,
	char **_Restrict);
long double strtold(const char *_Restrict,
	char **_Restrict);
_Longlong strtoll(const char *_Restrict,
	char **_Restrict, int);
_ULonglong strtoull(const char *_Restrict,
	char **_Restrict, int);

#define atoll(str)	(_Longlong)_Stoull(str, 0, 10)
#define strtof(str, endptr)	_Stof(str, endptr, 0)
#define strtold(str, endptr)	_Stold(str, endptr, 0)
#define strtoll(str, endptr, base)	_Stoll(str, endptr, base)
#define strtoull(str, endptr, base)	_Stoull(str, endptr, base)
 #endif /* _IS_C9X */

_END_C_LIB_DECL
 #endif /* defined(__cplusplus) && !defined(_NO_CPP_INLINES) */

 #ifndef _LLDIV_T
  #define _LLDIV_T
 #endif /* _LLDIV_T */

_C_STD_END
#endif /* _STDLIB */

 #if defined(_STD_USING)

  #ifdef _STD_USING_SIZE_T
using _CSTD size_t;
  #endif /* _STD_USING_SIZE_T */

using _CSTD div_t; using _CSTD ldiv_t;

using _CSTD abort; using _CSTD abs; using _CSTD atexit;
using _CSTD atof; using _CSTD atoi; using _CSTD atol;
using _CSTD bsearch; using _CSTD calloc; using _CSTD div;
using _CSTD exit; using _CSTD free; using _CSTD getenv;
using _CSTD labs; using _CSTD ldiv; using _CSTD malloc;
using _CSTD mblen; using _CSTD mbstowcs; using _CSTD mbtowc;
using _CSTD qsort; using _CSTD rand; using _CSTD realloc;
using _CSTD srand; using _CSTD strtod; using _CSTD strtol;
using _CSTD strtoul; using _CSTD system;
using _CSTD wcstombs; using _CSTD wctomb;

 #if _HAS_C9X
using _CSTD lldiv_t;

using _CSTD atoll; using _CSTD llabs; using _CSTD lldiv;
using _CSTD strtof; using _CSTD strtold;
using _CSTD strtoll; using _CSTD strtoull;
using _CSTD _Exit;
 #endif /* _IS_C9X */

 #endif /* defined(_STD_USING) */

/*
 * Copyright (c) 1992-2006 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V5.01:1278 */

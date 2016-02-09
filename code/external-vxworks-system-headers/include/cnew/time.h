/* time.h standard header */
#ifndef _TIME
#define _TIME
#ifndef _YVALS
 #include <yvals.h>
#endif /* _YVALS */

_C_STD_BEGIN

		/* macros */

#ifdef _NO_WINDRIVER_MODIFICATIONS
 #define CLOCKS_PER_SEC	_CPS
#else

 #ifndef NULL
  #define NULL	_NULL
 #endif /* NULL */

/* Used to convert the value returned by the clock() function into seconds. */
 #if defined(__RTP__)
  #define CLOCKS_PER_SEC	sysClkRateGet()
 #else
  #define CLOCKS_PER_SEC	_CPS
 #endif

 #if defined(__RTP__) && _HAS_POSIX_C_LIB
/* The identifier of the system-wide realtime clock. */
  #define CLOCK_REALTIME		0x0

/* The identifier for the system-wide monotonic clock. */
  #define CLOCK_MONOTONIC		0x1

/* The identifier of the CPU-time clock associated with the process making a clock() or timer*() function call. */ 
  #define CLOCK_PROCESS_CPUTIME_ID	0x2

/* The identifier of the CPU-time clock associated with the thread making a clock() or timer*() function call. */
  #define CLOCK_THREAD_CPUTIME_ID	0x3

/* Flag indicating time is absolute. */
  #define TIMER_ABSTIME			0x1

/* Flag indicating time is relative */
  #define TIMER_RELTIME   (~TIMER_ABSTIME)
 #endif /* __RTP__ && _HAS_POSIX_C_LIB */
#endif /* !_NO_WINDRIVER_MODIFICATIONS */

		/* type definitions */

 #if !defined(_SIZE_T) && !defined(_SIZET) && !defined(_SIZE_T_DEFINED) \
	&& !defined(_BSD_SIZE_T_DEFINED_) && !defined(__size_t)
  #define _SIZE_T
  #define _SIZET
  #define _BSD_SIZE_T_DEFINED_
  #define _SIZE_T_DEFINED
  #define _STD_USING_SIZE_T
typedef _Sizet size_t;
 #endif /* !defined(_SIZE_T) etc. */

 #if !defined(_CLOCK_T) && !defined(__clock_t_defined) \
	&& !defined(_BSD_CLOCK_T_DEFINED_) && !defined(__clock_t)
  #define _CLOCK_T
  #define __clock_t_defined
  #define _BSD_CLOCK_T_DEFINED_
  #define _STD_USING_CLOCK_T
typedef long clock_t;
 #endif /* !defined(_CLOCK_T) etc. */

 #if !defined(_TIME_T) && !defined(__time_t_defined) && !defined(__time_t) \
	&& !defined(_BSD_TIME_T_DEFINED_) && !defined(_TIME_T_DEFINED) 
  #define _TIME_T
  #define __time_t_defined
  #define _BSD_TIME_T_DEFINED_
  #define _TIME_T_DEFINED
  #define _STD_USING_TIME_T
typedef long time_t;
 #endif /* !defined(_TIME_T) etc. */

 #ifndef _TM_DEFINED
  #define _TM_DEFINED
struct tm
	{	/* date and time components */
	int tm_sec;
	int tm_min;
	int tm_hour;
	int tm_mday;
	int tm_mon;
	int tm_year;
	int tm_wday;
	int tm_yday;
	int tm_isdst;
	};
 #endif /* _TM_DEFINED */

 #if _HAS_POSIX_C_LIB

  #ifndef _NO_WINDRIVER_MODIFICATIONS
   #if defined(__RTP__)
    #ifndef _TIMESPEC_DEFINED
     #define _TIMESPEC_DEFINED
struct timespec
	{
	time_t tv_sec;
	long tv_nsec;
};
    #endif /* _TIMESPEC_DEFINED */

    #ifndef _ITIMERSPEC_DEFINED
     #define _ITIMERSPEC_DEFINED
struct itimerspec
	{
	struct timespec  it_interval;
	struct timespec  it_value;
};
    #endif /* _ITIMERSPEC_DEFINED */
   #endif /* __RTP__ */ 
 #else
   #if defined(__linux) || defined(__linux__)	/* compiler test */ \
	|| !defined(__APPLE__) && (0x570 < __SUNPRO_CC)
struct timespec
	{	/* POSIX.4, needed for pthread_cond_timedwait */
	time_t tv_sec;
	long tv_nsec;
	};
   #endif /* defined(__linux) etc. */
  #endif /* !_NO_WINDRIVER_MODIFICATIONS */

  #if !defined(_CLOCKID_T) && !defined(__clockid_t_defined)
   #define _CLOCKID_T
   #define __clockid_t_defined
   #define _STD_USING_CLOCKID_T
typedef int clockid_t;
  #endif /* !defined(_CLOCKID_T) && !defined(__clockid_t_defined) */

  #ifndef _NO_WINDRIVER_MODIFICATIONS
   #if defined(__RTP__) || defined(__DCC__)
    #if !defined(_TIMER_T)
     #define _TIMER_T
struct __timer;
typedef struct __timer *timer_t;
    #endif /* !defined(_TIMER_T) */

    #if (_POSIX_C_SOURCE != 200112L) || defined(_XOPEN_SOURCE) || \
	defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)  /* XSI options */
extern int   getdate_err;
extern int   daylight;
extern long  timezone;
    #endif  /* _POSIX_xxx_SOURCE */
extern char  *tzname[];
   #endif /* __RTP__ || __DCC__ */
  #endif /* !_NO_WINDRIVER_MODIFICATIONS */

 #endif /* _HAS_POSIX_C_LIB */

_EXTERN_C	/* low-level functions */
time_t time(time_t *);
_END_EXTERN_C

_C_LIB_DECL	/* declarations */
char *asctime(const struct tm *);
clock_t clock(void);
char *ctime(const time_t *);
double difftime(time_t, time_t);
struct tm *gmtime(const time_t *);
struct tm *localtime(const time_t *);
time_t mktime(struct tm *);
size_t strftime(char *_Restrict, size_t,
	const char *_Restrict, const struct tm *_Restrict);
 #ifndef _NO_WINDRIVER_MODIFICATIONS
  #if (__RTP__ || __DCC__) && _HAS_POSIX_C_LIB
/* These functions have a different signature in VxWorks and POSIX. The "_"
 * versions of the functions will be taken from VxWorks and then used to
 * implement the VxWorks or POSIX functionality depending on the setting of
 * _VXWORKS_COMPATIBILITY_MODE */
/* POSIX definitions - default */
char *asctime_r(const struct tm *, char *);		
char *ctime_r(const time_t *, char *);
struct tm *gmtime_r(const time_t *, struct tm *);
struct tm *localtime_r(const time_t *, struct tm *);
/* VxWorks definitions */
size_t _vxworks_asctime_r(const struct tm *, char *, size_t *);
char *_vxworks_ctime_r(const time_t *, char *, size_t *);
int _vxworks_gmtime_r(const time_t *, struct tm *);
int _vxworks_localtime_r(const time_t *, struct tm *);

   #ifdef _VXWORKS_COMPATIBILITY_MODE
    #define asctime_r(tm, buf, buflen)      _vxworks_asctime_r((tm), (buf), (buflen))
    #define ctime_r(tm, buf, buflen)        _vxworks_ctime_r((tm), (buf), (buflen))
    #define gmtime_r(tm, tmStruct)          _vxworks_gmtime_r((tm), (tmStruct))
    #define localtime_r(tm, tmStruct)       _vxworks_localtime_r((tm), (tmStruct))
   #endif /* _VXWORKS_COMPATIBILITY_MODE */

struct sigevent;
int timer_create(clockid_t, struct sigevent *_Restrict, timer_t *_Restrict);
int timer_delete(timer_t);
int timer_gettime(timer_t, struct itimerspec *);
int timer_getoverrun(timer_t);
int timer_settime(timer_t, int, const struct itimerspec *_Restrict,
				               struct itimerspec *_Restrict);

int clock_getres(clockid_t, struct timespec *);
int clock_gettime(clockid_t, struct timespec *);
int clock_settime(clockid_t, const struct timespec *);
int nanosleep(const struct timespec *, struct timespec *);
int clock_nanosleep(clockid_t, int, const struct timespec *, struct timespec *);
void tzset(void);

   #if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
	 !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)

    #ifndef _VOIDFUNCPTR_DEFINED
     #define _VOIDFUNCPTR_DEFINED
     #ifdef __cplusplus
typedef void    (*VOIDFUNCPTR) (...);  /* ptr to function returning void */
     #else
typedef void    (*VOIDFUNCPTR) ();     /* ptr to function returning void */
     #endif /* __cplusplus */
    #endif /* _VOIDFUNCPTR_DEFINED */

    #ifndef _STATUS_DEFINED
     #define _STATUS_DEFINED
typedef int	STATUS;
    #endif /* _STATUS_DEFINED */

extern int      timer_connect (timer_t timerid, VOIDFUNCPTR routine, int arg);
extern int      timer_cancel (timer_t timerid);
extern timer_t  timer_open (const char * name, int mode, clockid_t clockId, 
                            struct sigevent * evp, void * context);
extern STATUS   timer_close (timer_t timerId);
extern STATUS   timer_unlink (const char * name);
   #endif  /* _POSIX_xxx_SOURCE */
  #endif /* (__RTP__ || __DCC__) && _HAS_POSIX_C_LIB */
 #endif /* !_NO_WINDRIVER_MODIFICATIONS */

_END_C_LIB_DECL
_C_STD_END
#endif /* _TIME */

 #if defined(_STD_USING)

  #ifdef _STD_USING_CLOCK_T
using _CSTD clock_t;
  #endif /* _STD_USING_CLOCK_T */

  #ifdef _STD_USING_SIZE_T
using _CSTD size_t;
  #endif /* _STD_USING_SIZE_T */

  #ifdef _STD_USING_TIME_T
using _CSTD time_t;
  #endif /* _STD_USING_TIME_T */

  #ifdef _STD_USING_CLOCKID_T
using _CSTD clockid_t;
  #endif /* _STD_USING_CLOCKID_T */

using _CSTD tm;
using _CSTD asctime; using _CSTD clock; using _CSTD ctime;
using _CSTD difftime; using _CSTD gmtime; using _CSTD localtime;
using _CSTD mktime; using _CSTD strftime; using _CSTD time;
 #endif /* defined(_STD_USING) */

/*
 * Copyright (c) 1992-2006 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V5.01:1278 */

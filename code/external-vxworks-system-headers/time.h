/* time.h - POSIX time header */

/*
 * Copyright (c) 1992-2006, 2009-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01y,27may10,pad  Moved extern C statement after include statements.
01x,04mar10,jpb  Changed type of clockid_t from signed to unsigned.  Added
                 LP64 conditional.
01w,19jan10,pad  Removed usage of _WRS_KEEP_USING_FUNCPTR.
01v,26aug09,jpb  Added fully-qualified function pointer TIMER_CONNECT_FUNC.
                 Added declarations of init functions.
01u,18may09,xia  updated for LP64 data model
01t,31oct06,jmg  Added verbose mode to timer_show as part of defect
                 #WIND00039293
01s,01mar06,pes  Move typedefs to base type files.
01r,21feb06,pes  Move typedef of time_t and struct timespec.
01q,27jan06,jln  added CLOCK_PROCESS_CPUTIME_ID and CLOCK_THREAD_CPUTIME_ID
01q,31jan06,yvp  Added clock_nanosleep().
                 Updated copyright + #include now with angle brackets.
01p,09nov05,to   added CLOCK_MONOTONIC.
01o,18aug05,mcm  Merging contents of timeCommon.h with time.h.
01n,01mar05,gls  moved _POSIX macro definitions to limits.h (SPR #105358)
                 removed _POSIX_INTERVAL_MAX definition
01m,04dec03,pad  Further re-arrangement of content with share/timeCommon.h
01l,02dec03,ans  removed ANSI C definition.
01k,01oct03,ans  Rearranged contents with share/h/timeCommon.h.
01j,00oct00,sn   Removed defns of size_t etc.
01i,17feb99,mrs  Add C++ support for NULL, (SPR #25079).
01h,13aug96,dbt  modifed comment for tm_sec (SPR #4436).
		 Updated copyright.
01g,02jul96,dbt  added #include "vxWorks.h" (SPR #4370).
01f,14jul94,dvs  changed def of CLOCKS_PER_SEC to sysClkRateGet() (SPR# 2486).
01f,29nov93,dvs  folded in timers.h, made draft 14 POSIX compliant
01e,15oct92,rrr  silenced warnings.
01d,22sep92,rrr  added support for c++
01c,31jul92,gae  added undef of _TYPE_timer_t.
01b,27jul92,gae  added _TYPE_timer_t, CLOCK_REALTIME, TIMER_ABSTIME.
01a,22jul92,smb  written
           +rrr
*/

#ifndef __INCtimeh
#define __INCtimeh

#include <vxWorks.h>
#include <vsbConfig.h>
#include <types/vxANSI.h>
#include <objLib.h>
#include <limits.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NULL
#if defined __GNUG__
#define NULL (__null)
#else
#if !defined(__cplusplus) && 0
#define NULL ((void*)0)
#else
#define NULL (0)
#endif
#endif
#endif

/* forward declaration of sigevent (eliminates need to include sigevent.h). */
struct sigevent;

#ifdef __cplusplus
}
#endif

/* typedef timer_t */
#include <base/b_timer_t.h>

/* typedef clock_t */
#include <base/b_clock_t.h>

/* typedef time_t */
#include <base/b_time_t.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WRS_CONFIG_LP64
typedef unsigned long clockid_t;
#else
typedef unsigned int clockid_t;
#endif /* _WRS_CONFIG_LP64 */

#define CLOCKS_PER_SEC	sysClkRateGet()

#define CLOCK_REALTIME			0x0 /* system wide realtime clock */
#define CLOCK_MONOTONIC			0x1 /* system wide monotonic clock */
#define CLOCK_PROCESS_CPUTIME_ID  	0x2 /* process CPU-time clock */ 
#define CLOCK_THREAD_CPUTIME_ID   	0x3 /* thread CPU-time clock */

#define TIMER_ABSTIME	0x1		    /* absolute time */
#define TIMER_RELTIME   (~TIMER_ABSTIME)    /* relative time */

#ifdef __cplusplus
}
#endif

/* typedef struct timespec */
#include <base/b_struct_timespec.h>

#ifdef __cplusplus
extern "C" {
#endif

struct itimerspec
    {
    struct timespec it_interval;	/* timer period (reload value) */
    struct timespec it_value;		/* timer expiration */
    };

struct tm
    {
    int tm_sec;		/* seconds after the minute     - [0, 59] */
    int tm_min;		/* minutes after the hour       - [0, 59] */
    int tm_hour;	/* hours after midnight         - [0, 23] */
    int tm_mday;	/* day of the month             - [1, 31] */
    int tm_mon;		/* months since January         - [0, 11] */
    int tm_year;	/* years since 1900     */
    int tm_wday;	/* days since Sunday            - [0, 6] */
    int tm_yday;	/* days since January 1         - [0, 365] */
    int tm_isdst;	/* Daylight Saving Time flag */
    };

typedef void (*TIMER_CONNECT_FUNC) (timer_t timerId, _Vx_usr_arg_t arg);

/* function declarations */

extern uint_t      _clocks_per_sec(void);
extern char *	   asctime (const struct tm *_tptr);
extern clock_t	   clock (void);
extern char *	   ctime (const time_t *_cal);
extern double	   difftime (time_t _t1, time_t _t0);
extern struct tm * gmtime (const time_t *_tod);
extern struct tm * localtime (const time_t *_tod);

extern int 	timer_create (clockid_t clock_id, struct sigevent *evp,
			      timer_t *ptimer);
extern int 	timer_delete (timer_t timerid);
extern int 	timer_gettime (timer_t timerid, struct itimerspec *value);
extern int 	timer_settime (timer_t timerid, int flags,
		               const struct itimerspec *value,
			       struct itimerspec *ovalue);
extern int 	timer_getoverrun (timer_t timerid);
extern int      timer_connect (timer_t timerid, TIMER_CONNECT_FUNC routine,
                               _Vx_usr_arg_t arg);
extern int      timer_cancel (timer_t timerid);
extern int      nanosleep (const struct timespec *rqtp, struct timespec *rmtp);
extern timer_t  timer_open (const char * name, int mode, clockid_t clockId, 
                            struct sigevent * evp, void * context);
extern STATUS   timer_close (timer_t timerId);
extern STATUS   timer_unlink (const char * name);
extern void     timerWdHandler (timer_t timerid);

extern int	clock_gettime (clockid_t clock_id, struct timespec *tp);
extern int	clock_settime (clockid_t clock_id, const struct timespec *tp);
extern int	clock_getres (clockid_t clock_id, struct timespec *res);
extern int	clock_nanosleep (clockid_t clock_id, int flags, 
				 const struct timespec * rqtp, 
				 struct timespec * rmtp);

extern time_t	   mktime (struct tm *_tptr);
extern size_t	   strftime (char *_s, size_t _n, const char *_format,
		   	      const struct tm *_tptr);
extern time_t	   time (time_t *_tod);

extern int      timer_show (timer_t timerid, int verbose);
extern STATUS   timer_modify (timer_t timerId, struct sigevent * pSigev);

#if _EXTENSION_POSIX_REENTRANT		/* undef this for ANSI */
/* These functions have a different signature in VxWorks and POSIX. The "_"
 * versions of the functions will be taken from VxWorks and then used to
 * implement the VxWorks or POSIX functionality depending on the setting of
 * _VXWORKS_COMPATIBILITY_MODE */
/* POSIX definitions - default */
extern char   *    asctime_r(const struct tm *_tm, char *_buffer);
extern char   *    ctime_r(const time_t *_cal, char *_buffer);
extern struct tm * gmtime_r(const time_t *_tod,  struct tm *_result);
extern struct tm * localtime_r(const time_t *_tod, struct tm *_result);

/* VxWorks definitions */
extern int       _vxworks_asctime_r(const struct tm *_tm, char *_buffer, size_t *_buflen);
extern char *    _vxworks_ctime_r(const time_t *_cal, char *_buffer, size_t *_buflen);
extern int       _vxworks_gmtime_r(const time_t *_tod, struct tm *_result);
extern int       _vxworks_localtime_r(const time_t *_tod, struct tm *_result);

  #ifdef _VXWORKS_COMPATIBILITY_MODE
   #define asctime_r(tm, buf, buflen)      _vxworks_asctime_r((tm), (buf), (buflen))
   #define ctime_r(tm, buf, buflen)        _vxworks_ctime_r((tm), (buf), (buflen))
   #define gmtime_r(tm, tmStruct)          _vxworks_gmtime_r((tm), (tmStruct))
   #define localtime_r(tm, tmStruct)       _vxworks_localtime_r((tm), (tmStruct))
  #endif /* _VXWORKS_COMPATIBILITY_MODE */

#endif	/*  _EXTENSION_POSIX_REENTRANT */

#ifdef __cplusplus
}
#endif

#endif /* __INCtimeh */

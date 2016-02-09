#ifndef __Itime
#define __Itime

#include <xmacros.h>
#include <sys/types.h>

_C_LIB_DECL

#ifndef NULL
#define NULL 0
#endif

#ifndef __size_t
#define	__size_t
_TYPE_size_t;
#endif

#ifndef __clock_t
#define	__clock_t
typedef size_t clock_t;
#endif

#ifndef __INCtypesh
#ifndef __time_t
#define __time_t 
typedef size_t time_t;
#endif
#endif /* __INCtypesh */

struct	tm {
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

#define CLOCKS_PER_SEC 1000000

/* CLK_TCK is not defined in ANSI, but it was in an ANSI DRAFT and
 * since some test suites still looks for it, we keep inside
 * __STRICT_ANSI__ for the time being
 */
#ifdef	__mot68
#define CLK_TCK	60
#else
#include <unistd.h>
#define CLK_TCK	(sysconf(3))
#endif

extern clock_t clock(void);
extern double difftime(time_t, time_t);
extern time_t mktime(struct tm *);
extern time_t time(time_t *);
extern char *asctime(const struct tm *);
extern char *asctime_r(const struct tm *, char *);
extern char *ctime(const time_t *);
extern char *ctime_r(const time_t *, char *);
extern struct tm *gmtime(const time_t *);
extern struct tm *gmtime_r(const time_t *, struct tm *);
extern struct tm *localtime(const time_t *);
extern struct tm *localtime_r(const time_t *, struct tm *);
extern size_t strftime(char *, size_t, const char *, const struct tm *);

#if !defined(__STRICT_ANSI__) || defined(__cplusplus)

#include <sys/time.h>

extern void tzset(void);

extern long timezone;
extern int daylight;
extern char *tzname[];

extern int getitimer(int, struct itimerval *);
extern int setitimer(int, struct itimerval *, struct itimerval *);

#ifndef __clock_id_t
#define __clock_id_t
typedef int clockid_t;
#endif

#ifndef __timer_t
#define __timer_t
typedef void * timer_t;
#endif

struct timespec {
	time_t tv_sec;
	long int tv_nsec;
};

struct itimerspec {
	struct timespec it_interval;
	struct timespec it_value;
};

#define CLOCK_REALTIME		0
#define CLOCK_MONOTONIC		1
#define CLOCK_PROCESS_CPUTIME_ID	2
#define CLOCK_THREAD_CPUTIME_ID	3

struct sigevent;

extern int timer_create (clockid_t, struct sigevent *, timer_t *);
extern int timer_settime (timer_t, int, const struct itimerspec *, struct itimerspec *);
extern int timer_gettime (timer_t, struct itimerspec *);
extern int timer_getoverrun (timer_t);
extern int timer_delete (timer_t);

extern int clock_settime (clockid_t, const struct timespec *);
extern int clock_gettime (clockid_t, struct timespec *);
extern int clock_getres (clockid_t, struct timespec *);
extern int clock_nanosleep (clockid_t, int, const struct timespec, struct timespec *);

extern int nanosleep(const struct timespec*, struct timespec*);



#endif	/* __STRICT_ANSI__ */

_END_C_LIB_DECL

#endif

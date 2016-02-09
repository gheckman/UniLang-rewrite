#ifndef __Istime
#define __Istime

#ifdef	__cplusplus
extern "C" {
#endif

#if !defined(__STRICT_ANSI__) || defined(__cplusplus)

struct timeval {
	time_t		tv_sec;
	unsigned long	tv_usec;
};

struct itimerval {
	struct timeval	it_interval;
	struct timeval	it_value;
};

#define ITIMER_REAL	0
#define ITIMER_VIRTUAL	1
#define ITIMER_PROF	2

#define CLOCKS_PER_SECOND	1000000

extern int getitimer(int, struct itimerval *);
extern int setitimer(int, struct itimerval *, struct itimerval *);

#endif	/* __STRICT_ANSI__ */
#ifdef	__cplusplus
}
#endif
#endif

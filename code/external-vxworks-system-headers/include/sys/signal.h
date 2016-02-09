#define	SIGHUP	1
#define	SIGINT	2
#define	SIGQUIT	3
#define	SIGILL	4
#define	SIGTRAP	5
#define	SIGIOT	6
#define SIGABRT	6
#define	SIGEMT	7
#define	SIGFPE	8
#define	SIGKILL	9
#define	SIGBUS	10
#define	SIGSEGV	11
#define	SIGSYS	12
#define	SIGPIPE	13
#define	SIGALRM	14
#define	SIGTERM	15
#define	SIGUSR1	16
#define	SIGUSR2	17
#define	SIGCLD	18
#define	SIGCHLD	18
#define	SIGPWR	19

#define SIG_BLOCK 0
#define SIG_UNBLOCK 1
#define SIG_SETMASK 2

#define	SIG_ERR	(__sighandler_t)-1
#define	SIG_DFL	(__sighandler_t)0
#define	SIG_IGN	(__sighandler_t)1
#define	SIG_HOLD (__sighandler_t)2

#ifdef	__mot68
#define SIGURG	20
#define SIGPOLL	22
#define SIGIO	24
#define SIGVTALRM 25
#define SIGPROF 26

#if !defined(__STRICT_ANSI__)
#define SA_NOCLDSTOP 1

#define	NSIG	27
#define MAXSIG	32
#endif	/* __STRICT_ANSI__ */
#else
#define SIGWINCH 20
#define SIGPOLL	22
#define SIGSTOP	23
#define SIGTSTP	24
#define SIGCONT	25
#define SIGTTIN 26
#define SIGTTOU	27
#define SIGURG	33
#define SIGIO	34
#define SIGXCPU	35
#define SIGXFSZ	36
#define SIGVTALRM 37
#define SIGPROF	38
#define SIGLOST	40

#if !defined(__STRICT_ANSI__)
#define SA_NOCLDSTOP 1

#define	NSIG	65
#define MAXSIG	64
#endif	/* __STRICT_ANSI__ */
#endif

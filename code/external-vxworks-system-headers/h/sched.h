/* sched.h - POSIX scheduler header file */

/*
 * Copyright (c) 1984-1994, 2006, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/*
modification history
--------------------
01e,29apr10,pad  Moved extern C statement after include statements.
01d,21feb06,pes  Correct multiple definition protection for sched_param
                 struct by using base/b_struct_sched_param.h.
01c,11jan06,gls  added check that sched_param not already defined
01b,05jan94,kdl	 removed include of private/schedP.h.
01a,04nov93,dvs  written
*/

#ifndef __INCschedh
#define __INCschedh

#include "time.h"
#include "timers.h"

/* scheduling policies */

#define SCHED_FIFO	0x1	/* FIFO per priority scheduling policy */
#define SCHED_RR	0x2	/* round robin scheduling policy */
#define SCHED_OTHER	0x4	/* implementation defined; not currently used */

/* high/low priority values per scheduling policy POSIX numbering */

#define SCHED_FIFO_HIGH_PRI	255	/* POSIX highest priority for FIFO */
#define SCHED_FIFO_LOW_PRI	0	/* POSIX lowest priority for FIFO */
#define SCHED_RR_HIGH_PRI	255	/* POSIX highest priority for RR */
#define SCHED_RR_LOW_PRI	0	/* POSIX lowest priority for RR */

#include <base/b_struct_sched_param.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function declarations */

#if defined(__STDC__) || defined(__cplusplus)

extern int sched_setparam (pid_t pid, const struct sched_param * param);
extern int sched_getparam (pid_t pid, struct sched_param * param);
extern int sched_setscheduler (pid_t pid, int policy, 
			       const struct sched_param * param);
extern int sched_getscheduler (pid_t pid);
extern int sched_yield (void);
extern int sched_get_priority_max (int policy);
extern int sched_get_priority_min (int policy);
extern int sched_rr_get_interval (pid_t pid, struct timespec * interval);

#else   /* __STDC__ */

extern int sched_setparam ();
extern int sched_getparam ();
extern int sched_setscheduler ();
extern int sched_getscheduler ();
extern int sched_yield ();
extern int sched_get_priority_max ();
extern int sched_get_priority_min ();
extern int sched_rr_get_interval ();

#endif  /* __STDC__ */

#ifdef __cplusplus
}
#endif

#endif /* __INCschedh */

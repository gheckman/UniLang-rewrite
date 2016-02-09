/*	Implementation module : proflib.c

	Copyright 1990-2002 Wind River Systems, Inc. USA

	Description :
	Library module for compiler profiling.
*/

#ifndef D_proflib
#define D_proflib

#include <stdio.h>	/* need FILE* declaration */

/**************	Imports to declare exports **********************/

#undef EXTERN
#ifdef M_proflib
#define EXTERN
#else
#define EXTERN extern
#endif /* M_proflib */

/*
 * constants
 */
#define PROF_DEFAULT_NSUBS 1	/* default #of sub-functions per function*/
#define PROF_MIN_NPAIRS    50	/* minimum #of pairs allocated each time */
#define PROF_MAX_NPAIRS    250	/* maximum #of pairs allocated each time */
#define PROF_ARRAY_SIZE    50	/* size of each __PROF_INFO_ARRAY part */
#define PROF_TID_MAX_SIZE  50	/* max task-id string length */


#ifndef	M_profutil	/* for target... */

/*
 *	Profile data structure used by target.
 */
typedef void (*prof_func_ptr)();
typedef unsigned long prof_count;
typedef unsigned long prof_time;
typedef unsigned long prof_val;

struct prof_info {
	struct prof_memory	*pi_mhead;
	struct prof_memory	*pi_mtail;
	struct prof_func	*pi_funcbase;	/* function list (prof_func) */
	struct prof_stack	*pi_stack;	/* stack list (prof_stack) */
	struct prof_pair	*pi_pairfree;
	struct prof_pair	*pi_pairlast;
	prof_val		pi_nfunc;	/* number of functions */
	prof_val		*pi_bcnt;	/* block count array */
	prof_val		pi_nbcnt;	/* block count array size */
	prof_val		pi_timebase;	/* timebase in nS */
	prof_val		pi_version;	/* version number */
	char			*pi_tidname;	/* task-id string	(v2) */
	prof_val		pi_tidlen;	/* length of task-id	(v2) */
	prof_val		pi_tidnum;	/* task-id # [reserved]	(v2) */
	int			pi_magic;	/* (v3) */
};

struct prof_memory {
	struct prof_memory	*pm_next;
	prof_val		pm_size;
	int			pm_magic;
};

struct prof_data {
	prof_count		pd_recur;
	prof_count		pd_count;
	prof_time		pd_functime;
	prof_time		pd_totaltime;
};

struct prof_func {
	struct prof_data	pf_data;
	struct prof_pair	*pf_pair;
	struct prof_pair	*pf_last;
};

struct prof_pair {
	struct prof_data	pp_data;
	struct prof_pair	*pp_next;
	struct prof_func	*pp_caller;
	struct prof_func	*pp_callee;
};

struct prof_stack {
	struct prof_stack	*ps_prev;
	struct prof_func	*ps_func;
	struct prof_pair	*ps_pair;
	volatile prof_time	ps_toptime;
	volatile prof_time	ps_subtime;
	volatile prof_time	ps_padding;
};

struct prof_array_elem {
	struct prof_info	*pae_pip;
	prof_val		pae_instance;
};

struct prof_array {
	struct prof_array	*pa_next;
	prof_val		pa_size;
	struct prof_array_elem	pa_array[PROF_ARRAY_SIZE];
};

/*
 * RTAlib globals
 */
EXTERN void* __PROF_INFO_PTR;
EXTERN void* __PROF_INFO_ARRAY;
extern char __prof_tid_name[];

extern void __prof_print(void);
extern void __prof_fprint(FILE*);
extern void __prof_xprint(FILE *, size_t (*)(const void*,size_t,size_t,FILE*), 
			  struct prof_info*);
extern void __prof_reset(void);
extern void __prof_init(int, int);
extern void __prof_finish(void);
extern void __prof_finish_pip(void**);
extern void __prof_finish_print(void);
extern void __prof_clock(void);

extern void (*__prof_drop_stack)(void *);

extern prof_val* __prof_bcnt(void);
extern prof_val* __prof_enter_pair(prof_func_ptr*, struct prof_stack*);
extern prof_val* __prof_enter_fast(prof_func_ptr*, struct prof_stack*);
extern void __prof_exit_pair(void);
extern void __prof_exit_fast(void);

/*
 * RTAlib callouts
 */
extern void __rta_drop_stack(void *);

#else  /* M_profutil */

/*
 *	Profile data structure used by host.  Must be identical
 *	to the above in size and order.
 */

struct prof_info {
	prof_addr		pi_mhead;
	prof_addr		pi_mtail;
	prof_addr		pi_funcbase;	/* function list (prof_func) */
	prof_addr		pi_stack;	/* stack list (prof_stack) */
	prof_addr		pi_pairfree;
	prof_addr		pi_pairlast;
	prof_val		pi_nfunc;	/* number of functions */
	prof_addr		pi_bcnt;	/* block count array */
	prof_val		pi_nbcnt;	/* block count array size */
	prof_val		pi_timebase;	/* timebase in nS */
	prof_val		pi_version;	/* version number */
	prof_addr		pi_tidname;	/* task-id string 	(v2) */
	prof_val		pi_tidlen;	/* length of task-id	(v2) */
	prof_val		pi_tidnum;	/* task-id # [reserved] (v2) */
};

struct prof_memory {
	prof_addr		pm_next;
	prof_val		pm_size;
};

struct prof_data {
	prof_count		pd_recur;
	prof_count		pd_count;
	prof_time		pd_functime;
	prof_time		pd_totaltime;
};

struct prof_func {
	struct prof_data	pf_data;
	prof_addr		pf_pair;
	prof_addr		pf_last;
};

struct prof_pair {
	struct prof_data	pp_data;
	prof_addr		pp_next;
	prof_addr		pp_caller;
	prof_addr		pp_callee;
};

struct prof_stack {
	prof_addr		ps_prev;
	prof_addr		ps_func;
	prof_addr		ps_pair;
	prof_time		ps_toptime;
	prof_time		ps_subtime;
	prof_time		ps_padding;
};

struct prof_array_elem {
	prof_addr		pae_pip;
	prof_val		pae_instance;
};

struct prof_array {
	prof_addr		pa_next;
	prof_val		pa_size;
	struct prof_array_elem	pa_array[PROF_ARRAY_SIZE];
};

#endif /* M_profutil */
#endif /* D_proflib */

/* Local variables:	*/
/* Mode: c-mode		*/
/* c-basic-offset: 8	*/
/* c-indent-level: 8	*/
/* c-argdecl-indent:0	*/
/* c-label-offset: -8	*/
/* comment-column: 40	*/
/* End:			*/

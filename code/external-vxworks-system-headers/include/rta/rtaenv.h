/*	Definition module : rtaenv.h

	Copyright 1990-2002 Wind River Systems, Inc. USA

	Description :
	This module declares helper functions for RTA;
	profiler and run-time error checker (RTC)
*/


#ifndef _RTAENV_H
#define _RTAENV_H

#include <stdlib.h>

#ifdef	__cplusplus
extern "C" {
#endif

/******************** RTC definitions ********************/

/*
 * __rtc_abort is called by run-time checker when it detects severe error
 * and system must be stopped
 */
void __rtc_abort(void);

/*
 * __rtc_abort is called by run-time checker when it detects severe error
 * and task execution must be aborted
 */
void __rtc_abort_task(void);

/*
 * default function for RTC error printing.
 * __rtc_error is initialized by pointer to this function
 */
void __rtc_error_default(void * ptr, char * msg);

/*
 * __rtc_print is used by RTC to print reports other than error message,
 * e.g. memory leaks report
 */
void __rtc_print(char * msg);

/*
 * print stack tarce for current task
 */
void __rtc_print_stack_trace(void);

/*
 * __rtc_heap_walk must iterate system memory blocks which are used by heap.
 * Usually a program has only one such block created by sbrk
 * To start iteration __rtc_heap_walk will be called with 'addr' == NULL,
 * last call to __rtc_heap_walk must return NULL in 'addr'.
 */
struct __rtc_heap_walk_struct {
	void * addr;	/* memory block address */
	size_t size;	/* memory block size */
	void * ref;	/* this field is reserved for __rtc_heap_walk function implementation */
};
void __rtc_heap_walk(struct __rtc_heap_walk_struct * p);

/*
 * __rtc_heap_type returns:
 * 0 - heap does not support multiple threads (single threading), one stack per thread
 * 1 - each thread has own heap, more than one stack per thread
 * 2 - one heap for all threads, more than one stack per thread
 * 3 - each thread has own heap, one stack per thread
 * 4 - one heap for all threads, one stack per thread
 */
int __rtc_heap_type(void);

/*
 * returns stack limit of current thread or NULL if stack limit is unknown
 */
void * __rtc_sp_limit(void);

/*
 * __rtc_sp_grow change stack limit to 'need' if possible
 */
void __rtc_sp_grow(void * need);


/*
 * should return 1 if checking and profiling must be temporally disabled,
 * like in interrupt handler
 */
int __rta_is_interrupted(void);


/*
 * Pointers to memory manager functions.
 * RTC initializes these to internal functions used to register
 * a newly allocated block, or when a block is about to be freed.
 * Keep in DATA so we know we can reach them (pSOS)
 */
#if defined(__ppc) || defined(__mips) || defined(__nec)
#  pragma use_section DATA __rtc_alloc_ptr, __rtc_free_ptr, _rtc_blkinfo_ptr
#endif
extern void* (*__rtc_alloc_ptr)(void*, size_t);
extern void* (*__rtc_free_ptr)(void*, void*, void (*)(void*, void*));
extern void* (*__rtc_blkinfo_ptr)(void*, int);



/******************** Profiler definitions ********************/

/*
 * Profiler user init callout
 * should start the profile timer (if start_timer == 1). 
 * returns the time interval in nano-seconds
 * return 0xffffffff if no timer is present, or could not be started
 */
extern unsigned long __prof_user_init(int start_timer);

/*
 * Profiler user finish callout
 * should stop the profile timer (if stop_timer == 1) and
 * and no one else is using the timer
 */
extern void __prof_user_finish(int stop_timer);


/*
 * get current task ID
 * Called from __prof_init to get the ID of the current task.
 *
 * Should return -1 if used in single tasking system.
 * In a multi tasking system the task ID string should be
 * copied into the buffer pointed to by *tid. max is the maximum
 * number of characters that can be copied to the buffer. The
 * string must be terminated using a NUL character. 
 *	
 * If the RTOS uses numbers for task-ID's the number must be 
 * converted to a string by this ruotine.
 */
extern void __prof_get_current_tid(char * tid, int max);


/******************** RTA definitions ********************/

/*
 * allocate/free memory for RTA
 */
extern void* __rta_alloc(size_t size);
extern void __rta_free(void *ptr);

/*
 * __rta_longjmp: pointer to longjmp callback function
 * the profiler and RTC defines this pointer to a common function
 * when initialized. longjmp() must call this functions if pointer is non NULL
 * Keep in DATA so we know we can reach it (pSOS)
 */
#if defined(__ppc) || defined(__mips) || defined(__nec)
#  pragma use_section DATA __rta_longjmp
#endif
extern void (*__rta_longjmp)(void *);


#ifdef	__cplusplus
}
#endif
#endif

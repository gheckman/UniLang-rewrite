/*	Definition module : rtc.h

	Copyright 1990-2002 Wind River Systems, Inc. USA

	Description :
	This module declares interface to
	run-time error checker.
*/

#ifndef __Irtc
#define __Irtc

#include <xmacros.h>

_C_LIB_DECL

#ifndef __size_t
#define	__size_t
_TYPE_size_t;
#endif

/* RTC mode */

#define _RTC_MD_ATEXIT_REPORT	0x01	/* enable memory leaks and stack usage report at exit */
#define _RTC_MD_ABORT		0x02	/* enable system abort on error */
#define _RTC_MD_ABORT_TASK	0x04	/* enable task abort on error */

extern void (*__rtc_error)(void *, char *);
extern void (*__rtc_drop_stack)(void *);
extern void __rta_drop_stack(void*);	/* function for stack drop (profiler & rtc) */

/* pointers below needs to be per task (if multi-threading) */
extern void* __RTC_INFO_PTR;
extern void* __RTC_SP_LIMIT;

extern unsigned __rtc_num_threads;

#ifndef _RTC_ENABLED
void __rtc_init(void);
void __rtc_clear(void);
void __rtc_incl_mem(void * ptr, size_t sz);
void __rtc_incl_auto0(void ** list, void * ptr, size_t sz);
void __rtc_excl_auto0(void ** list);
void __rtc_incl_auto(void ** list, void * ptr, size_t sz, unsigned int level);
void __rtc_excl_auto(void ** list, unsigned int level);
void * __rtc_chk(void * ptr, int offset, size_t sz);
void * __rtc_chk_at(char * file, int line, void * ptr, int offset, size_t sz);
void * __rtc_inc_op_at(char * file, int line, void ** ptr, int offset);
void * __rtc_op_inc_at(char * file, int line, void ** ptr, int offset);
#endif

int __rtc_mem_leaks(void);
int __rtc_new_leaks(void);
int __rtc_clear_leaks(void);
void __rtc_set_leaks_report_limit(int);
void __rtc_clear(void);
int __rtc_is_free(void *);
void __rtc_set_mode(int);
int __rtc_get_mode(void);
void __rtc_set_free_delay(int count);
void __rtc_exit(void);
void __rtc_finish(void);
void __rtc_finish_rip(void **p);
void __rtc_disable(char * file_name, int line); /* disable error message at given location,
						   if line==0 then disable messages for whole file.
						 */

_END_C_LIB_DECL

#endif

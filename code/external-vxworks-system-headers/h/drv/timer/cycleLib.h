/* cycleLib.h - clock cycle level event library header */

/* Copyright 2005 Wind River Systems, Inc. */
#include "copyright_wrs.h"

/*
modification history
--------------------
01a,06dec05,prb	written.
*/

#ifndef	__INCcycleLibh
#define	__INCcycleLibh

#include <sys/cdefs.h>

#define	SET_RELOAD(x)
#undef	SET_RELOAD

typedef unsigned int CYCLE_TICK;
typedef unsigned long long int CYCLE_CLOCK;

typedef struct cycleLibEvent_t cycleLibEvent_t;
typedef cycleLibEvent_t *CEVENT_ID;

/*
 * The event queue is a double linked delta queue.
 *
 * The next pointer points to the next element, or NULL if it is
 * the last event in the queue.
 *
 * The prev pointer points t the previous element.  It's value is unspecified
 * for the first element in the queue.
 *
 * The tick value is the number of ticks between the previous event
 * and this event.
 *
 * The rate is the frequency, in ticks, of this event.  A value of 0
 * implies this is not a repeating event.
 *
 * The base is only used for repeating events.  This is the absolute cycle
 * value for the next event.
 */
struct cycleLibEvent_t {
	CEVENT_ID	next;			/* Next event to fire */
	CEVENT_ID	prev;			/* doubly linked list */
	CYCLE_TICK	tick;			/* delta until event fires */
	void		(*callback)(void *);	/* callback function */
	void		*arg;			/* argument to callback */
	CYCLE_TICK	rate;			/* rate if repeating event */
	CYCLE_CLOCK	base;			/* time base if repeating */
};

__BEGIN_DECLS

extern void		cycleLibInit __P((void));
extern int		cycleLibPoolAlloc __P((int, CEVENT_ID));
extern void		cycleLibEventFree __P((CEVENT_ID));
extern void		cycleLibEventHandler __P((void));
extern CEVENT_ID	cycleLibEventAdd __P((CYCLE_TICK, void(*)(void *),
				void *));
extern CEVENT_ID	cycleLibEventAddRepeating __P((CYCLE_TICK, CYCLE_TICK,
				void(*)(void *), void *));
extern CEVENT_ID	cycleLibEventAddAbsolute __P((CYCLE_CLOCK,
				void(*)(void *), void *, CEVENT_ID));
extern void		cycleLibEventDelete __P((CEVENT_ID, void(*)(void *),
				void *));
__END_DECLS

/*
 * The values below should be set in a architecture specific location.
 */

#define	SET_TIMER(x)		vxDecSet(x)
#define	GET_CYCLE_CLOCK()	gettb()

__BEGIN_DECLS
extern CYCLE_CLOCK		gettb __P((void));
extern void			vxDecSet __P((unsigned));
__END_DECLS

#endif	/* __INCcycleLibh */

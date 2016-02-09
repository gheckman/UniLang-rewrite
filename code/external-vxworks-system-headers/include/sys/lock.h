#ifndef __Ilock
#define __Ilock

#ifdef	__cplusplus
extern "C" {
#endif

#define	UNLOCK	 0
#define	PROCLOCK 1
#define	TXTLOCK	 2
#define	DATLOCK	 4

extern int plock(int);

#ifdef	__cplusplus
}
#endif
#endif

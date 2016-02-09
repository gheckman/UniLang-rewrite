/* selectLibP.h - private select library header */

/* Copyright 2001-2004, 2006, 2010 Wind River Systems, Inc. */

/*
modification history
--------------------
01g,06sep10,jxu  Moved select related function pointers from funcBindP.h, 
                 included selectLib.h, tyLib.h and ptyLib.h.
                 moved typedef selWkNode and SEL_WAKEUP_LIST to selectLib.h.
01f,29apr10,pad  Moved extern C statement after include statements.
01e,18apr06,dlk  Address SPRs #118764, #119855, and #119926.
01d,03jun04,dat  Track maxFd for saved fd_set's, 97881
01c,18dec03,dat  replace memCtx with ready and returnSet.
01b,09dec03,dat  chg taskId to be a real WIND_TCB ptr, added ctx sw flag,
		 added exception fd_set.
01a,18sep01,aeg  extracted from version 02c of selectLib.h; added selContext.
*/

#ifndef __INCselectLibP
#define __INCselectLibP

#ifndef _ASMLANGUAGE
#include <selectLib.h>   /* SELECT_TYPE */
#include <tyLib.h>
#include <ptyDrv.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct selContext
    {
    SEMAPHORE	wakeupSem;		/* wakeup semaphore */
    BOOL     	pendedOnSelect;		/* task pended on select? */

    fd_set     *pReadFds;		/* select'ed task's read fd_set */
    fd_set     *pWriteFds;		/* select'ed task's write fd_set */
    fd_set     *pExcFds;		/* select'ed task's exc fd_set */

    /* the following are needed for safe task deletion */

    fd_set     *pOrigReadFds;		/* task's original read fd_set */
    fd_set     *pOrigWriteFds;		/* task's original write fd_set */
    fd_set     *pOrigExcFds;		/* task's original exc fd_set */
    int		maxFd;			/* maxFd for saved sets above */
    int		width;			/* width parm passed to select() */
	
	BOOL badfd;

    /* 
     * The remaining memory in the SEL_CONTEXT dynamically allocated by
     * the select task create hook is used to store the various fd_set's
     * referenced in the above fd_set pointers.  Note that these structures
     * are not really fd_set's since their size is based on maxFiles (iosLib) 
     * instead of FD_SETSIZE.
     *
     * fd_set  origReadFds;	/@ memory for task's original read fd_set @/
     * fd_set  origWriteFds;	/@ memory for task's original write fd_set @/
     * fd_set  origExcFds;	/@ memory for task's original write fd_set @/
     */

    } SEL_CONTEXT;

/* function declarations */

IMPORT void	selectInit		(int numFiles);
IMPORT void	selTaskDeleteHookAdd 	(void);

/* variable declarations */

/* select-related function pointers, moving from funcBindP.h */

extern void (*_func_selTyAdd)           (TY_DEV *pTyDev, _Vx_ioctl_arg_t arg);

extern void (*_func_selTyDelete)        (TY_DEV *pTyDev, _Vx_ioctl_arg_t arg);

extern void (*_func_selPtyAdd)          (PSEUDO_DEV *pPtyDev, 
                                         _Vx_ioctl_arg_t arg);

extern void (*_func_selPtyDelete)       (PSEUDO_DEV *pPtyDev, 
                                         _Vx_ioctl_arg_t arg);

extern void (*_func_selPtySlaveAdd)     (PSEUDO_DEV *pPtyDev,
                                         _Vx_ioctl_arg_t arg);

extern void (*_func_selPtySlaveDelete)  (PSEUDO_DEV *pPtyDev,
                                         _Vx_ioctl_arg_t arg);

extern void (*_func_selWakeupAll)       (SEL_WAKEUP_LIST *pWakeupList,
                                         FAST SELECT_TYPE type);

extern void (*_func_selWakeupListInit)  (SEL_WAKEUP_LIST *pWakeupList);

extern void (*_func_selWakeupListTerm)  (SEL_WAKEUP_LIST *pWakeupList);

extern void (*_func_selWakeup)          (SEL_WAKEUP_NODE *pWakeupNode);

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCselectLibP */

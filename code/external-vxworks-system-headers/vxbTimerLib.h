/* vxbTimerLib.h - vxbus timer interfaces header file */

/*
 * Copyright (c) 2006, 2007, 2009-2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01o,17jul12,sye  Removed duplicate method declaration. (WIND00359032)
01n,17aug11,dee  Defect WIND00278138 - add 64-bit timestamp support
01m,29apr10,pad  Moved extern C statement after include statements.
01l,20aug09,my_  Fix a possible memory overflow (WIND00176116)
01l,25feb09,h_k  updated for LP64 support.
01k,05mar07,ami  Added new macro
01j,24feb07,pdg  flag added for timer not supporting all frequencies within
                 the range
01i,02feb07,pdg  updated design review comments
01h,13dec06,sup  updated timer selection algorithm
01g,20sep06,pdg  Fix WIND00066007(up counter to be used instead of down
                 counter)
01f,19sep06,pdg  replaced method constant with an address
01e,15sep06,h_k  added missing vxBusLib.h inclusion.
01d,25aug06,pdg  changed 'sys' to 'vxb'
01c,16jul06,sup  Typo in comment of structure variable *timerCountGet. Changed up to down.
01b,21jun06,pdg  new design incorporated
01a,06Mar06,pdg  written
*/

/*
DESCRIPTION

This library provides the timer specific interfaces

*/

#ifndef _INC_vxbTimerLibH
#define _INC_vxbTimerLibH

#include <hwif/vxbus/vxBus.h>
#include <vxBusLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* features provided by the timer */

/* the timer can interrupt */

#define VXB_TIMER_CAN_INTERRUPT			0x00000001

/* the timer provides interface to read intermediate count values */

#define VXB_TIMER_INTERMEDIATE_COUNT		0x00000002

/* the timer size is 16 bits */

#define VXB_TIMER_SIZE_16			0x00000004

/* the timer size is 32 bits */

#define VXB_TIMER_SIZE_32			0x00000008

/* the timer size is 64 bits */

#define VXB_TIMER_SIZE_64			0x00000010

/* the timer cannot be disabled */

#define VXB_TIMER_CANNOT_DISABLE        	0x00000020

/* the timer stops couting while the current count value is read */

#define VXB_TIMER_STOP_WHILE_READ		0x00000040

/* the timer can automatically reload the maximum counter after an interrupt */

#define VXB_TIMER_AUTO_RELOAD			0x00000080

/* counter is a free-running counter, rollover value cannot be modified */

#define VXB_TIMER_CANNOT_MODIFY_ROLLOVER	0x00000100

/* 
 * the timer cannot support all frequencies between the maximum
 * and minimum frequency ranges. It supports only some frequencies
 * within the range. 
 */

#define VXB_TIMER_CANNOT_SUPPORT_ALL_FREQS	0x00000200

#define VXB_TIMER_SIZE_23      0x00000400      
/* frequency values to be used during system clock selection */

#define SYSCLK_OPTIMUM_MINFRQ		10
#define SYSCLK_OPTIMUM_MAXFRQ		5000
#define SYSCLK_MINFRQ_LIMIT         60
#define SYSCLK_MAXFRQ_LIMIT         300

/* frequency values to be used during the auxiliary clock selection */

#define AUXCLK_OPTIMUM_MINFRQ		10
#define AUXCLK_OPTIMUM_MAXFRQ		50000
#define AUXCLK_MINFRQ_LIMIT         60
#define AUXCLK_MAXFRQ_LIMIT         1000

/* freuency value to be used by the timestamp timer */

#define TS_OPTIMUM_MAXFRQ	        50000

/* maximum value of integer - used during timer selection */

#define MAXINT				0x7FFFFFFF

/* typedefs */

typedef struct vxbTimerFunctionality*	 timerHandle_t;

struct vxbTimerFunctionality
    {
    BOOL	allocated;	/* flag used to denote timer allocation */
    UINT32	clkFrequency;	/* clock frequency */
    UINT32	minFrequency;	/* min period timer can provide */
    UINT32	maxFrequency;	/* max period timer can provide */
    UINT32	features;	/* features of timer */
    UINT32	ticksPerSecond;	/* ticks per second */
    char	timerName[MAX_DRV_NAME_LEN + 1] ; /* timer Name */
    UINT32	rolloverPeriod; /* rollover period of the timer in seconds */

    /* allocate dedicated timer */
    STATUS (*timerAllocate)
        (
        VXB_DEVICE_ID	pInst,	 /* IN */
        UINT32		flags,	 /* IN */
        void **		pCookie, /* OUT */
        UINT32		timerNo  /* IN */
        );
 
    /* release dedicated timer */
    STATUS (*timerRelease)
        (
        VXB_DEVICE_ID	pInst,	 /* IN */
        void *		pCookie	 /* IN */
        );
    
    /* get count between rollover/ISR events */
    STATUS (*timerRolloverGet)
        (
        void *	pCookie,	/* IN */
        UINT32 *  count		/* OUT */
        );
 
    /* 
     * get current timestamp timer count value.
     * The driver should ensure returning the count as that of 
     * an up counter. 
     */
    STATUS (*timerCountGet)
        (
        void *		pCookie,	/* IN */
        UINT32 *		count		/* OUT */
        );

    /* disable the timer */
 
    STATUS (*timerDisable)
        (
        void *	pCookie		/* IN */
        ); 

    /* enable the timer */

    STATUS (*timerEnable)
        (
        void *	pCookie,	/* IN */
        UINT32	maxTimerCount	/* IN */
        ); 

    /* set the function to be called on every interrupt */

    STATUS (*timerISRSet)
        (
        void *	pCookie,		/* IN */
        void   (*pIsr)(_Vx_usr_arg_t),	/* IN */
        _Vx_usr_arg_t	arg		/* IN */
        );
 
    /* enable the timer */

    STATUS (*timerEnable64)
        (
        void *	pCookie,	/* IN */
        UINT64	maxTimerCount	/* OUT */
        ); 

    /* get count between rollover/ISR events */

    STATUS (*timerRolloverGet64)
        (
        void *	pCookie,	/* IN */
        UINT64 *count		/* IN */
        );

    /* 
     * get current timestamp timer count value.
     * The driver should ensure returning the count as that of 
     * an up counter. 
     */
    STATUS (*timerCountGet64)
        (
        void *		pCookie,	/* IN */
        UINT64 *	count		/* OUT */
        );
    };

/* structure to be used and updated during timer selection */

struct selectedTimerDetails
    {
    VXB_DEVICE_ID	pInst;
    UINT32		timerNo;
    }; 

/* globals */

extern char *	pSysClkName;
extern UINT32	sysClkDevUnitNo;
extern UINT32	sysClkTimerNo;
extern char *	pAuxClkName;
extern UINT32	auxClkDevUnitNo;
extern UINT32	auxClkTimerNo;
extern char *	pTimestampTimerName;
extern UINT32	timestampDevUnitNo;
extern UINT32	timestampTimerNo;

extern STATUS (*_vxb_clkConnectRtn)
    (
    FUNCPTR routine,    
    _Vx_usr_arg_t arg             
    );

extern void (*_vxb_clkDisableRtn) (void);
extern void (*_vxb_clkEnableRtn) (void);
extern int (*_vxb_clkRateGetRtn) (void);

extern STATUS (*_vxb_clkRateSetRtn)
    (
    int ticksPerSecond
    );

extern STATUS (*_vxb_auxClkConnectRtn)
    (
    FUNCPTR routine,   
    _Vx_usr_arg_t arg          
    );

extern void (*_vxb_auxClkDisableRtn) (void);
extern void (*_vxb_auxClkEnableRtn) (void);
extern int (*_vxb_auxClkRateGetRtn) (void);

extern STATUS (*_vxb_auxClkRateSetRtn)
    (
    int ticksPerSecond
    );

extern STATUS (*_vxb_timestampConnectRtn)
    (
    FUNCPTR routine,
    _Vx_usr_arg_t arg         
    );

/*
 * The follow 10 function pointers may be used by the bsp to
 * override any or all of the standard VxBus timestamp driver timestamp functions 
 */

/* bsp provided overrides of timestamp enable/disable routines */

extern STATUS (*_vxb_timestampEnableRtn) (void);
extern STATUS (*_vxb_timestampDisableRtn) (void); 

/* 32-bit bsp provided overrides of timestamp access routines */

extern UINT32 (*_vxb_timestampPeriodRtn) (void);
extern UINT32 (*_vxb_timestampFreqRtn) (void);
extern UINT32 (*_vxb_timestampRtn) (void);
extern UINT32 (*_vxb_timestampLockRtn) (void);

/* 64-bit bsp provided overrides of timestamp access routines */

extern UINT64 (*_vxb_timestamp64PeriodRtn) (void);
extern UINT64 (*_vxb_timestamp64FreqRtn) (void);

extern STATUS (*_vxb_timestamp64Rtn)
    (
    UINT64 *  countVal  /* pointer to return 64-bit counter value */
    );

extern STATUS (*_vxb_timestamp64LockRtn)
    (
    UINT64 *  countVal  /* pointer to return 64-bit counter value */
    );

extern void (*_vxb_delayRtn) ();

extern void (*_vxb_msDelayRtn)
    (
    int	delayTime
    );

extern void (*_vxb_usDelayRtn)
    (
    int	delayTime
    );

extern void vxbDelay (void);

extern void vxbMsDelay
    (
    int	delayTime
    );

extern void vxbUsDelay
    (
    int	delayTime
    );

extern timerHandle_t sysClkHandleGet (void);
extern timerHandle_t sysAuxClkHandleGet (void);
extern timerHandle_t sysTimestampHandleGet (void);

extern STATUS vxbTimerFeaturesGet
    (
    timerHandle_t	timer,
    UINT32 *		pMinFreq,
    UINT32 *		pMaxFreq,
    UINT32 *		pFeatures
    );

extern timerHandle_t vxbTimerAlloc
    (
    UINT32	freq,		/* requested frequency */
    UINT32	minFreq,	/* max acceptable min freq */ 
    UINT32	maxFreq,	/* min acceptable max freq */ 
    UINT32	features,	/* timer features */
    UINT32	featureMask,	/* timer features specified */
    void (*pIsr)(_Vx_usr_arg_t arg),	/* ISR */
    _Vx_usr_arg_t	arg	/* argument to ISR */
    );

extern void vxbTimerRelease
    (
    timerHandle_t	timer
    );

extern void vxbSysClkShow (void);
extern void vxbAuxClkShow (void);
extern void vxbTimestampShow (void);
extern void vxbDelayClkShow (void);

extern STATUS vxbDelayLibInit (void);
extern void vxbTimerStubInit (void);

extern STATUS vxbSysClkLibInit (void);

extern STATUS vxbSysClkConnect
    (
    FUNCPTR     routine,   /* routine called at each system clock interrupt */
    _Vx_usr_arg_t arg       /* argument with which to call routine        */
    );

extern void vxbSysClkEnable (void);
extern void vxbSysClkDisable (void);
extern int vxbSysClkRateGet (void);

extern STATUS vxbSysClkRateSet
    (
    int ticksPerSecond      /* number of clock interrupts per second */
    );

extern void vxbSysClkShowInit (void);
extern STATUS vxbAuxClkLibInit (void);

extern STATUS vxbAuxClkConnect
    (
    FUNCPTR routine,    /* routine called at each aux clock interrupt    */
    _Vx_usr_arg_t arg   /* argument to auxiliary clock interrupt routine */
    );

extern void vxbAuxClkDisable (void);
extern void vxbAuxClkEnable (void);
extern int vxbAuxClkRateGet (void);

extern STATUS vxbAuxClkRateSet
    (
    int ticksPerSecond  /* number of clock interrupts per second */
    );

extern void vxbAuxClkShowInit (void);

extern STATUS vxbTimestampLibInit (void);

extern STATUS vxbTimestampConnect
    (
    FUNCPTR     routine,
    _Vx_usr_arg_t arg
    );

/* 
 * The following 10 functions are defined in src/hwif/util/vxbTimeStampLib.c
 * They call a vxBus timestamp driver unless the driver function is overriden
 * by the overrides above.
 */

/* timestamp enable/disable functions */

extern STATUS vxbTimestampEnable (void);
extern STATUS vxbTimestampDisable (void);

/* 32-bit timestamp access functions */

extern UINT32 vxbTimestampPeriod (void);
extern UINT32 vxbTimestampFreq (void);
extern UINT32 vxbTimestamp (void);
extern UINT32 vxbTimestampLock (void);

/* 64-bit timestamp access functions */

extern UINT64 vxbTimestamp64Period (void);
extern UINT64 vxbTimestamp64Freq (void);

extern STATUS vxbTimestamp64
    (
    UINT64 *  countVal  /* pointer to return 64-bit counter value */
    ); 

extern STATUS vxbTimestamp64Lock
    (
    UINT64 *  countVal  /* pointer to return 64-bit counter value */
    ); 

extern void vxbTimestampShowInit (void);

#ifdef __cplusplus
}
#endif

#endif /* _INC_vxbTimerLibH */


/* ivSimnt.h - simnt interrupt vectors */

/*
 * Copyright (c) 1997,2003,2004,2007 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this
 * software may be licensed only pursuant to the terms of an applicable
 * Wind River license agreement.
 */

/*
modification history
--------------------
01d,05oct07,elp  moved interrupt vector definitions.
01c,09feb04,dat  Diab lint fix, chg INUM_TO_IVEC
01b,21may03,jmp  moved IV_MAX from intArchLib.c.
01a,06oct97,cym  written
*/

#ifndef __INCivSimnth
#define __INCivSimnth

#ifdef __cplusplus
extern "C" {
#endif

/* maximun number of interrupt vectors */

#define IV_MAX	0x0300		/* This value must be coherent with	*/
				/* VXSIM_MAX_INTS defined on host side.	*/
				/* See vxsimwin32.h .			*/

/* macros to convert interrupt vectors <-> interrupt numbers */

#define IVEC_TO_INUM(intVec)    	(intVec)
#define INUM_TO_IVEC(intNum)    	((VOIDFUNCPTR *)intNum)

#define IVEC_TO_MESSAGE(intVec) 	(intVec)
#define MESSAGE_TO_IVEC(message)        (message)

/* interrupt vector definitions */

#define TIMER_SYS_CLK_INT       0x0000  /* System clock interrupt       */
#define TIMER_AUX_CLK_INT       0x0001  /* Auxiliary clock interrupt    */
#define TIMER_TS_ROLL_OVER_INT  0x0002  /* Timestamp rollover interrupt */
#define MAILSLOT_INT            0x0003  /* Backend pipe interrupt       */
#define CONSOLE_SIO_INT         0x0004  /* SIO driver interrupt         */
#define BUS_INT                 0x0005  /* BUS interrupt                */

/* level0 IPI interrupt aka  IPI_INTR_ID_CPC */

#define IV_IPI0                 0x0006  

/* level1 IPI interrupt aka IPI_INTR_ID_DEBUG */

#define IV_IPI1                 0x0007  

#define IV_IPI2                 0x0008  /* level2 IPI interrupt         */
#define IV_IPI3                 0x0009  /* level3 IPI interrupt         */
#define WINDML_INT_RANGE_BASE   0x00f0  /* WindML interrupts range base */
#define WINDML_INT_RANGE_END    0x00ff  /* WindML interrupts range end  */
#define USER_INT_RANGE_BASE     0x0200  /* User interrupts range base   */
#define USER_INT_RANGE_END      0x02ff  /* User interrupts range end    */

#ifdef __cplusplus
}
#endif

#endif /* __INCivSimnth */

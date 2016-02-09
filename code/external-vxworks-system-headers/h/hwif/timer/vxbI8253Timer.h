/* vxbI8253Timer.h - i8253 timer device header */

/*
 * Copyright (c) 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01b,25aug10,j_l	 Change default i8253 counter mode to mode 2 (WIND00221408).
01a,02feb10,cwl	 created. (WIND00196333)
*/

#ifndef __INCvxbI8253Timerh
#define __INCvxbI8253Timerh

#ifdef __cplusplus
extern "C" {
#endif

/* operation modes for timer I8253 */

#define VXB_I8253_COUNTER_MODE0          0x0
#define VXB_I8253_COUNTER_MODE1	         0x02
#define VXB_I8253_COUNTER_MODE2	         0x04
#define VXB_I8253_COUNTER_MODE3          0x06
#define VXB_I8253_COUNTER_MODE4          0x08
#define VXB_I8253_COUNTER_MODE5          0x0A
#define VXB_I8253_COUNTER_MODE_DEFAULT   VXB_I8253_COUNTER_MODE2

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* __INCvxbI8253Timerh */


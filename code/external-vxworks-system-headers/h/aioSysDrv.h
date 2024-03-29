/* aioSysDrv.h - AIO system driver header file */

/* Copyright 1984-2005, 2010 Wind River Systems, Inc. */

/*
modification history
--------------------
01g,24jun10,jxu  LP64: changed API  STATUS aioSysInit (int, int, int) to
                 STATUS aioSysInit (int, int, size_t);
01f,28apr10,pad  Moved extern C statement after include statements.
01e,07feb05,hya  added missing prototype
01d,30jan04,dat  Rework for RTP compatibility
01c,12jan94,kdl  changed name from aioSysPxLib to aioSysDrv; general cleanup.
01b,06dec93,dvs  removed S_aioSysPxLib_NO_PIPES
01a,04apr93,elh  written.
*/

#ifndef __INCaioSysDrvh
#define __INCaioSysDrvh

/* includes */

#include "aio.h"

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

/* project configurable AIO task parameters */

#define AIO_IO_TASKS_DFLT       2               /* number of I/O tasks */
#define AIO_IO_STACK_DFLT       0x7000          /* I/O task stack size */
#define AIO_IO_PRIO_DFLT        50              /* I/O task priority */

/* hardcoded parameters */

#define AIO_TASK_OPT            0               /* task options */
#define AIO_WAIT_STACK          0x7000          /* wait task stack size */

/* forward declarations */

extern STATUS aioSysInit (int numTasks, int taskPrio, size_t taskStackSize);
extern STATUS aioSysInsert (struct aiocb *pAiocb, int prio);

#ifdef __cplusplus
}
#endif

#endif /* __INCaioSysDrvh */

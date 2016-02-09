/* hwdefs.h - DSHM adaptation layer: HW definitions */

/*
 * Copyright (c) 2006-2007, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01g,29apr10,pad  Moved extern C statement after include statements.
01f,14jun07,bwa  added HandshakeSend method.
01e,09apr07,bwa  moved PLB method data structure to its own file.
01d,06apr07,bwa  added NodeReady and BeatGetChild methods.
01c,15mar07,bwa  updated busctlr methods.
01b,21dec06,bwa  changed static method numbers to a character string;
		 added bus controller method data structure;
                 removed FUNCPTR usage.
01a,05jul06,bwa  written.
*/

#ifndef __INCdshmAdaptHwdefsh
#define __INCdshmAdaptHwdefsh

#include <hwif/vxbus/vxBus.h>
#include <vxBusLib.h>

#ifdef __cplusplus
extern "C" {
#endif

METHOD_DECL(dshmBusCtlrMethodId);
METHOD_DECL(dshmBusCtlrMethodChildTxId);
METHOD_DECL(dshmBusCtlrMethodChildRemoveId);
METHOD_DECL(dshmBusCtlrMethodChildPingId);
METHOD_DECL(dshmBusCtlrMethodNodeReadyId);
METHOD_DECL(dshmBusCtlrMethodChildBeatGetId);
METHOD_DECL(dshmBusCtlrMethodHandshakeSendId);

#ifdef __cplusplus
}
#endif

#endif /* __INCdshmAdaptHwdefsh */


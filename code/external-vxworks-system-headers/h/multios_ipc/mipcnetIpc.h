/* mipcnetIpc.h - private Multi-OS IPC API for MND net driver */

/********************************************************************
The following file is dual licensed and is available under either 
the GPL version 2 or a Wind River commercial license.

*********************************************************************
Copyright (c) 2008-2011 Wind River Systems, Inc.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License version 2 as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

*********************************************************************
Copyright (c) 2008-2011 Wind River Systems, Inc.

The right to copy, distribute, modify, or otherwise make use
of this software may be licensed pursuant to the terms
of an applicable Wind River license agreement.

*********************************************************************/

/*
modification history
--------------------
01i,07jan11,jlk  Update license header
01h,17dec10,h_w  Add the API mipcnetUnitTxBufAvail and other type defines
01g,23jun10,h_w  upgrade to MND 2.1
01f,29apr10,h_w  fix WIND00162940, add an api mipcnetBusCtrlTxActive to
                 active bus control tx task mipcnetBusCtrlTxTask
01e,10mar10,wy1  fix WIND00188999, add api mipcnetUnitPktDiscard for buffer
                 free
01d,25sep09,spw  Add tx, rx buffer configuration to mipcnetUnitConfig
01c,20sep09,spw  Add mipcnetBusRxCallback
01b,02jul09,spw  linux compatibility
01a,13nov08,mak  written
*/

#ifndef __INCmipcnetIpch
#define __INCmipcnetIpch

#include <multios_ipc/mipc.h>
#include <multios_ipc/multios_adapt.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MND_IF_NAME				"mnd"
#define MND_IF_NAME_MAX_LEN		64

#define MIPCNET_BUS_MAX			4		/* mipcnet busses per OS, max value is 1024 */
#define MIPCNET_NODE_MAX		1024	/* mipcnet nodes per bus, max value is 1024 */
#define MIPCNET_UNIT_MAX		256		/* mipcnet i/f units supported, max value 256 */

#define MIPCNET_INT_RX			1
#define MIPCNET_INT_TX_AVAIL		2

/* typedefs */

typedef void (*INTFUNCPTR) (void *, unsigned char);

struct mipcnetUnitConfig {
    void *pBus;                  	/* the bus handle from mipcnetBusCreate() */
    int unit;                   	/* the mipcnet unit number on this node */
    int segment;                	/* the mipcnet eth segment number */
    int dataPort;               	/* the data port used for this segment */
    int mtu;						/* the size of the MND frame payload */
    int txBufs;                     /* transmit buffers on the data socket */
    int rxBufs;                     /* receive buffers on the data socket */
    char busName[MIPC_BUS_NAME_MAX_LEN];/* the MIPC bus on which the MND unit resides */
};

void *mipcnetBusCreate
(
    char *busName,
    int txBufs,
    int rxBufs,
    int ctrlPort
);

void * mipcnetUnitCreate
(
    struct mipcnetUnitConfig * config
);

void mipcnetUnitDelete
(
    void *	pUnit
);

void mipcnetUnitStart
(
    void *	pUnit
);

void mipcnetUnitIntEnable
(
    void *	pUnit
);

void mipcnetUnitIntDisable
(
    void *	pUnit
);

void mipcnetUnitPhysAddrGet
(
    void *			pUnit,
    unsigned char *	enetAddr
);

int mipcnetUnitPhysAddrIsValid
(
    void *			pUnit,
    unsigned char *	enetAddr
);

MIPC_ZBUFFER mipcnetUnitPktAlloc
(
    void *	pUnit,
    char **	ppBuffer
);

int mipcnetUnitPktSend
(
    void *			pUnit,
    void *			pPkt,
    unsigned char *	pBuffer,
    size_t			bufSize
);

void mipcnetUnitIntConnect
(
    void *	pUnit,
    INTFUNCPTR	intRtn,
    void *	intArg
);

void mipcnetUnitIntDisconnect
(
    void *	pUnit
);

int mipcnetUnitMtuGet
(
    void *	pUnit,
    int *	pMtu
);

int mipcnetUnitTxBufAvail
(
    void *	pUnit
);

int mipcnetUnitPktZReceive
(
    void *			pUnit,
    void **			buffer,
    MIPC_ZBUFFER *	zbuf
);

int mipcnetUnitPktZFree
(
    void *			pUnit,
    MIPC_ZBUFFER	zbuf
);

void mipcnetUnitSendNodeJoinMsgAll
(
    void *pUnit
);

void mipcnetUnitSendSegDetachMsgAll
(
    void *pUnit
);

void mipcnetUnitPollEnable
(
    void *pUnit
);

void mipcnetUnitPollDisable
(
    void *pUnit
);

int mipcnetUnitParser
(
    char * start,
    char * end,
    struct mipcnetUnitConfig* cfg
);

#ifdef __cplusplus
}
#endif

#endif /* __INCmipcnetIpch */


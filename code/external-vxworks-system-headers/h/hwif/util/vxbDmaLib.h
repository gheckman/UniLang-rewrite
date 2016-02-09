/* vxbDmaLib.h - vxBus DMA interfaces header file */

/*
 * Copyright (c) 2006-2007, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/* 
modification history
--------------------
01g,29apr10,pad  Moved extern C statement after include statements.
01f,25mar09,h_k  updated for LP64 support.
01e,26jul07,h_k  added includes for vxBusLib.h & vxBus.h
01d,13jun07,tor  remove VIRT_ADDR
01c,06feb07,wap  Cleanup
01b,05oct06,pdg  updated review comments
01a,22Jun06,pdg  written
*/

/*
DESCRIPTION

This file defines the macros, structures and interfaces which can be used
by the device drivers for performing DMA tramsfers.

*/

#ifndef __INCvxbDmaLibh
#define __INCvxbDmaLibh 

/* includes */

#include <vxBusLib.h>
#include <hwif/vxbus/vxBus.h>

#ifdef __cplusplus
extern "C" {
#endif

/* mask values used */

#define DMA_INITIATOR_INDEX_MASK	0x000000FF /* index mask */
#define DMA_COPY_MODE_MASK		0x00000300 /* copy mode mask */
#define DMA_TRANSFER_TYPE_MASK		0x00003000 /* transfer type mask */	

/* 'flags' values in dmaChanAlloc () */

#define DMA_COPY_MODE_DEVBUF	0x00000000
#define DMA_COPY_MODE_FIFO	0x00000100
#define DMA_COPY_MODE_NO_SOFT	0x00000200
#define DMA_COPY_MODE_NO_HW	0x00000300
#define DMA_TRANSFER_TYPE_RD	0x00001000
#define DMA_TRANSFER_TYPE_WR	0x00002000

/* flag value used during dedicated DMA channel allocation */

#define DMA_CHAN_ALLOCATED	0x01000000

#define DMA_CHAINED_BUFFERS	0x01000000 /* the dma engine supports */
                                                   /* chained buffers */
#define DMA_INDEX_MASK		0x000000FF
#define DMA_CRC_MASK		0x0000FF00 /* crc mask value */
#define DMA_CONVERSION_MASK	0x00FF0000 /* features & flags mask */

/* DMA transfer status values */

#define DMA_STATUS_OK			0
#define DMA_STATUS_ERROR		1
#define DMA_STATUS_CANCELLED		2

/* channel status values */

#define DMA_NOT_USED	1 /* DMA channel is not in use */	
#define DMA_IDLE	2 /* DMA channel is inactive */
#define DMA_RUNNING	3 /* DMA engine is running */
#define DMA_PAUSED	4 /* DMA is currently paused */

typedef void (* pVXB_DMA_COMPLETE_FN)
    (
    void *	pArg,
    UINT32	actualTransferSize,
    UINT32	transferStatus
    );

typedef struct vxbDmaResource VXB_DMA_RESOURCE, * VXB_DMA_RESOURCE_ID;

/*
 * This structure holds the function pointers which can be used by IO
 * device driver instances to perform read and write operations 
 * through the DMA engine, pause, resume dma operations and retrieve 
 * the status of dma operations.
 */
struct vxbDmaFuncs
    {
    STATUS (*dmaRead)	/* read from device */
        (
        VXB_DMA_RESOURCE_ID	dmaChan,
        char *   		src,
        char *   		dest,
        int			transferSize,
        int			unitSize,
        UINT32			flags,
        pVXB_DMA_COMPLETE_FN	pDmaComplete,
        void *			pArg
        );

    STATUS (*dmaReadAndWait) /* read from device and wait for completion */
        (
        VXB_DMA_RESOURCE_ID	dmaChan,
        char *   		src,
        char *   		dest,
        int *			pTransferSize,
        int			unitSize,
        UINT32			flags
        );

    STATUS (*dmaWrite)	/* write to device */
        (
        VXB_DMA_RESOURCE_ID	dmaChan,
        char *   		src,
        char *   		dest,
        int			transferSize,
        int			unitSize,
        UINT32			flags,
        pVXB_DMA_COMPLETE_FN	pDmaComplete,
        void *			pArg
        );

    STATUS (*dmaWriteAndWait)	/* write to device and wait for completion */
        (
        VXB_DMA_RESOURCE_ID	dmaChan,
        char *   		src,
        char *   		dest,
        int *			pTransferSize,
        int			unitSize,
        UINT32			flags
        );

    STATUS (*dmaCancel)	/* cancel a dma transfer */
        (
        VXB_DMA_RESOURCE_ID	dmaChan 
        );	

    STATUS (*dmaPause) /* pause a dma transfer */
        (
        VXB_DMA_RESOURCE_ID	dmaChan 
        );	

    STATUS (*dmaResume)	/* resume a dma transfer */
        (
        VXB_DMA_RESOURCE_ID	dmaChan 
        );	

    int (*dmaStatus)	/* get the status of DMA channel */
        (
        VXB_DMA_RESOURCE_ID	dmaChan
        );
    };

#define vxbDmaRead(a,b,c,d,e,f,g,h)	(a)->dmaFuncs.dmaRead(a,b,c,d,e,f,g,h)
#define vxbDmaWrite(a,b,c,d,e,f,g,h)	(a)->dmaFuncs.dmaWrite(a,b,c,d,e,f,g,h)
#define vxbDmaReadAndWait(a,b,c,d,e,f)	\
	(a)->dmaFuncs.dmaReadAndWait(a,b,c,d,e,f)
#define vxbDmaWriteAndWait(a,b,c,d,e,f)	\
	(a)->dmaFuncs.dmaWriteAndWait(a,b,c,d,e,f)
#define vxbDmaCancel(x)			(x)->dmaFuncs.dmaCancel(x)
#define vxbDmaPause(x)			(x)->dmaFuncs.dmaPause(x)
#define vxbDmaResume(x)			(x)->dmaFuncs.dmaResume(x)
#define vxbDmaStatus(x)			(x)->dmaFuncs.dmaStatus(x)

/* 
 * Pointer to struct vxbDmaResource is returned by dmaChanAlloc ().
 * This has to be used for communication with the DMA engine.
 */

struct vxbDmaResource
    {
    struct vxbDmaFuncs	dmaFuncs;/* structure holding dma function pointers */	
    void *		pDmaChan;/* channel specific data-used by DMA driver */
    VXB_DEVICE_ID	dmaInst; /* dma engine instance ID */
    };

/*
 * if multiple buffers are used during a transfer,
 * 'src' should point to a list of the following structures. In the case
 * of multiple buffers, 'destn' need not be used.
 */
struct vxbDmaBufferDesc
    {
    char *   			srcAddr;	/* source address */
    char *   			destAddr;	/* destination address */
    int				transferSize;	/* size of transfer */	
    UINT32			transferStatus;	/* status of dma transfer */
    struct vxbDmaBufferDesc *	pNextDesc;	/* pointer to the next desc */
    void		*	pDmaChanData;	/* pointer to the driver data */			
    };

IMPORT VXB_DMA_RESOURCE_ID vxbDmaChanAlloc (VXB_DEVICE_ID pDev,
                                            UINT32 minQueueDepth, UINT32 flags,
                                            void * pDedicatedChanInfo);    
IMPORT void vxbDmaChanFree (VXB_DMA_RESOURCE_ID dmaChan);

IMPORT void vxbDmaLibInit (void);

/* Backwards compatibility. */

#define dmaChanAlloc vxbDmaChanAlloc
#define dmaChanFree vxbDmaChanFree

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INCvxbDmaLibh */ 

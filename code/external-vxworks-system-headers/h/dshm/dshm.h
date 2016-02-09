/* dshm.h - core dSHM definitions */

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
01j,15jul10,gjj  deprecated the DSHM technology and added deprecation macros. 
01h,29apr10,pad  Moved extern C statement after include statements.
01g,23aug07,bwa  changed 'type' field in DSHM_SVC_OBJ to 'svc'.
01f,22mar07,bwa  moved DSHM_BUS_INT_INFO to bus controller;   
		 changed message size to 64 .
01e,07mar07,bwa  modified some network commands layout.
01d,02mar07,bwa  changed message size from 40 to 32 (cache aligned).
01c,02feb07,bwa  added DSHM_ADDR_INVALID.
01b,21dec06,bwa  major overhaul.
01a,05jul06,bwa  written.
*/

#ifndef __INCdshmh
#define __INCdshmh
 

#include <dshm/adapt/types.h>
#include <dshm/adapt/errno.h>

#ifdef __cplusplus
extern "C" {
#endif

#define DSHM_VERSION	1

/* messages layout
 * 
 *   +---> service
 *   |       +---> destination
 *   |       |                  +---> payload
 *   |       |                  |
 * +---+---+---+---+---------//-------------+
 * | 2 | 2 | 2 | 2 |           var          |
 * +---+---+---+---+---------//-------------+
 *       |       |
 *       |       +----> type (action)
 *       +---> source
 */

#define DSHM_OFFSET_SVC		0
#define DSHM_OFFSET_SRC		2
#define DSHM_OFFSET_DST		4
#define DSHM_OFFSET_TYP		6
#define DSHM_OFFSET_DAT		8
#define DSHM_SIZE_DAT		56
/* total message size should always be a multiple of 32 (cache aligned) */
#define DSHM_SIZE		(DSHM_SIZE_DAT + DSHM_OFFSET_DAT)

/* the message type
 */

#define DSHM(name)	char name [DSHM_SIZE]	/* use to define a variable */
#define DSHM_PTR(name)	char *name		/* use to define a pointer */
#define DSHM_CAST(name)	((char *)name)		/* use to cast a pointer */
#define DSHM_TYPE()	char [DSHM_SIZE]	/* used for function args */

/* byte-order macros so that we don't include in.h
 */

#if	_BYTE_ORDER ==_BIG_ENDIAN
#define	ntohl(x)	(x)
#define	ntohs(x)	(x)
#define	htonl(x)	(x)
#define	htons(x)	(x)
#endif	/* _BYTE_ORDER==_BIG_ENDIAN */

#if	_BYTE_ORDER ==_LITTLE_ENDIAN
#define ntohl(x)	((((x) & 0x000000ff) << 24) | \
			 (((x) & 0x0000ff00) <<  8) | \
			 (((x) & 0x00ff0000) >>  8) | \
			 (((x) & 0xff000000) >> 24))

#define htonl(x)	((((x) & 0x000000ff) << 24) | \
			 (((x) & 0x0000ff00) <<  8) | \
			 (((x) & 0x00ff0000) >>  8) | \
			 (((x) & 0xff000000) >> 24))

#define ntohs(x)	((((x) & 0x00ff) << 8) | \
			 (((x) & 0xff00) >> 8))

#define htons(x)	((((x) & 0x00ff) << 8) | \
			 (((x) & 0xff00) >> 8))
#endif	/* _BYTE_ORDER==_LITTLE_ENDIAN */

/* message access macros
 */

/* used to build the message */

#define DSHM_BUILD(msg, svc, src, dst, typ) \
    do \
	{ \
	*((uint16_t*)(msg+DSHM_OFFSET_SVC))  = htons(svc); \
	*((uint16_t*)(msg+DSHM_OFFSET_SRC))  = htons(src); \
	*((uint16_t*)(msg+DSHM_OFFSET_DST))  = htons(dst); \
	*((uint16_t*)(msg+DSHM_OFFSET_TYP))  = htons(typ); \
	} \
    while ((0))
    
#define DSHM_SRC_SET(msg, src) \
    do \
	{ \
	*((uint16_t*)(msg+DSHM_OFFSET_SRC)) = htons (src); \
	} \
    while ((0))

#define DSHM_DST_SET(msg, dst) \
    do \
	{ \
	*((uint16_t*)(msg+DSHM_OFFSET_DST)) = htons (dst); \
	} \
    while ((0))

/* build data portion represented as an array of N-bit parameters */

#define DSHM_DAT8_SET(msg,index,value) \
    do \
	{ \
	(((uint8_t*)(msg+DSHM_OFFSET_DAT))[index]) = (value); \
	} \
    while ((0))
    
#define DSHM_DAT16_SET(msg,index,value) \
    do \
	{ \
	(((uint16_t*)(msg+DSHM_OFFSET_DAT))[index]) = htons(value); \
	} \
    while ((0))
    
#define DSHM_DAT32_SET(msg,index,value) \
    do \
	{ \
	(((uint32_t*)(msg+DSHM_OFFSET_DAT))[index]) = htonl(value); \
	} \
    while ((0))

/* access each section of the message */

#define DSHM_SVC_GET(msg) (ntohs(*(uint16_t*)(msg+DSHM_OFFSET_SVC)))
#define DSHM_SRC_GET(msg) (ntohs(*(uint16_t*)(msg+DSHM_OFFSET_SRC)))
#define DSHM_DST_GET(msg) (ntohs(*(uint16_t*)(msg+DSHM_OFFSET_DST)))
#define DSHM_TYP_GET(msg) (ntohs(*(uint16_t*)(msg+DSHM_OFFSET_TYP)))
#define DSHM_DAT_GET(msg) (msg+DSHM_OFFSET_DAT)

/* access to data portion as an array of N-bit parameters */

#define DSHM_DAT8_GET(msg,index) \
    (((uint8_t*)(msg+DSHM_OFFSET_DAT))[index])
    
#define DSHM_DAT16_GET(msg,index) \
    (ntohs(((uint16_t*)(msg+DSHM_OFFSET_DAT))[index]))
    
#define DSHM_DAT32_GET(msg,index) \
    (ntohl(((uint32_t*)(msg+DSHM_OFFSET_DAT))[index]))

/* service types
 * 
 * users of the dSHM messaging system
 */

#define DSHM_SVC_MNG		0	/* node management service: needed */

#define DSHM_SVC_TIPC		1	/* TIPC bearers: */
#define DSHM_SVC_TIPC_SEC	4	/* same as inet, up to two bearers */

#define DSHM_SVC_VNIC		2	/* virtual network interfaces: */
#define DSHM_SVC_VNIC_SEC	5	/* up to four (4) of them can be */
#define DSHM_SVC_VNIC_3RD	6	/* configured as services without */
#define DSHM_SVC_VNIC_4TH	7	/* using up a generic service number. */

#define DSHM_SVC_VXMP		3	/* VxMP Deux */

#define DSHM_SVC_TEST		9	/* test application service */
 
/* messages types
 * 
 * these are passed as the 'type' part of the message, which can be viewed as
 * 'actions' either requested or performed by the sender; the following groups
 * of action are currently supported and thus reserved:
 * 
 * - management, type @ offsets 0x0000, 0x0010
 * - network communication, types @ offset 0x0020
 * - VxMP2 commands, types @ offset 0x0030
 */

/* node management messages */
 
#define DSHM_TYP_MNG_OFF	0x0000
#define DSHM_MNG(typ)		(typ + DSHM_TYP_MNG_OFF)
#define DSHM_TYP_MNG_JOIN	DSHM_MNG(0) /* node is joining system */
#define DSHM_TYP_MNG_QUIT	DSHM_MNG(1) /* node is quitting system */
#define DSHM_TYP_MNG_EJECT	DSHM_MNG(2) /* node is ejecting rogue peer */
#define DSHM_TYP_MNG_SYNC	DSHM_MNG(3) /* synchronize backup with manager*/
#define DSHM_TYP_MNG_ACCEPT	DSHM_MNG(4) /* node is joining system */

/* manager/backup election messages */

#define DSHM_TYP_ELECT_OFF	0x0010
#define DSHM_ELECT(typ)		(typ + DSHM_TYP_ELECT_OFF)
#define DSHM_TYP_ELECT_AM_MNGR	DSHM_ELECT(0)	/* 'I am the manager' */
#define DSHM_TYP_ELECT_YOU_MNGR	DSHM_ELECT(1)	/* 'You are the manager' */
#define DSHM_TYP_ELECT_AM_BCKP	DSHM_ELECT(2)	/* 'I am the backup' */
#define DSHM_TYP_ELECT_YOU_BCKP	DSHM_ELECT(3)	/* 'You are the backup' */
#define DSHM_TYP_ELECT_TOO_LATE	DSHM_ELECT(4)	/* 'Too late! can't be mngr' */

/* network communication messages */

#define DSHM_TYP_NET_OFF	0x0020
#define DSHM_NET(typ)		(typ + DSHM_TYP_NET_OFF)
#define DSHM_NET_INDEX(cmd)	(cmd - DSHM_TYP_NET_OFF)
#define DSHM_TYP_NET_JOIN	DSHM_NET(0) /* 'hey! here I am!' */
#define DSHM_TYP_NET_REQ     	DSHM_NET(1) /* 'I want buffers' */
#define DSHM_TYP_NET_ALLOC   	DSHM_NET(2) /* 'here are your buffers' */
#define DSHM_TYP_NET_SEND    	DSHM_NET(3) /* 'you can read these buffers' */
#define DSHM_TYP_NET_FREE    	DSHM_NET(4) /* 'I don't want these buffers!' */
#define DSHM_TYP_NET_BCAST   	DSHM_NET(5) /* 'come read a bcast buf from me'*/
#define DSHM_TYP_NET_QUIT	DSHM_NET(6) /* 'dropping off...!' */
#define DSHM_TYP_NET_QUIT_ACK	DSHM_NET(7) /* 'you quitting acknowledged' */
#define DSHM_TYP_NET_MAX	DSHM_NET(8)

/* VxMP2 commands */

#define DSHM_TYP_VXMP_	/* unknown for now */

/* addresses
 */

/* broadcast address */

#define DSHM_ADDR_BCAST	0xffff

/* invalid unicast address */

#define DSHM_ADDR_INVALID 0xffff

/* networking message payload
 * 
 * arguments passed for each type of networking message
 */

#define DSHM_TYP_NET_JOIN_RING_SET(msg, ring) \
    DSHM_DAT32_SET(msg, 0, ring)
#define DSHM_TYP_NET_JOIN_RING_GET(msg) \
    DSHM_DAT32_GET(msg, 0)
    
/* request asks for a number of clusters (QuanTitY) and size */
#define DSHM_TYP_NET_REQ_QTY_SET(msg, qty) \
    DSHM_DAT8_SET(msg, 0, qty)
#define DSHM_TYP_NET_REQ_SIZE_SET(msg, size) \
    DSHM_DAT16_SET(msg, 1, size)
#define DSHM_TYP_NET_REQ_QTY_GET(msg) \
    DSHM_DAT8_GET(msg, 0)
#define DSHM_TYP_NET_REQ_SIZE_GET(msg) \
    DSHM_DAT16_GET(msg, 1)
    
/* alloc sends a number of clusters (QuanTitY), their size and the buffer
 * offsets */
/* calculate where the first buffer is, after all the tags */
/* explanation: we have a replies with the following format:
 * 2 bytes: quantity of buffers allocated
 * 2 bytes: size of buffers (all equal size)
 * n * 2bytes: tag for each buffer allocated -> n is a fixed amount dependant
 *             on the maximum number of buffers that can be allocated. That
 *             number is based on the size of DSHM messages, DSHM_SIZE_DAT.
 * n * 4bytes: buffers offset into shared memory. n is the same as for the tags
 * 
 * This is broken up in the #if 0 below.
 */
#define _DSHM_ALLOC_BUF_OFFSET \
    ((ROUND_UP ((((DSHM_SIZE_DAT - 4)) / 6 * 2) , 4) / 4) + 1)
#if 0
    ( \
	( \ /* find out first buffer location */
	    ROUND_UP ( \ /* tags before bufs are 16bit, round-up to 32bit */
		( \
		    ( \ /* calculate number of tags-bufs pairs */
			(DSHM_SIZE_DAT - 4) \	/* remove the qty and size */
			    / 6 \ /* each tag + buf pair is 6 bytes */
		    ) \
		    * 2 /* tags before bufs are 2bytes */
		), 4 \ /* round-up to 32bits */
	    ) / 4 \ /* we have an offset in bytes, put it in 4byte quantities */
	) + 1 \	/* finally, add the qty/size pair (2bytes each) */
    )
#endif
    
#define DSHM_TYP_NET_ALLOC_QTY_SET(msg, qty) \
    DSHM_DAT16_SET(msg, 0, qty)
#define DSHM_TYP_NET_ALLOC_SIZE_SET(msg, size) \
    DSHM_DAT16_SET(msg, 1, size)
#define DSHM_TYP_NET_ALLOC_TAG_SET(msg, tag, tagValue) \
    DSHM_DAT16_SET(msg, (2 + (tag)), (tagValue))
#define DSHM_TYP_NET_ALLOC_BUF_SET(msg, buf, pBuf) \
    DSHM_DAT32_SET(msg, (_DSHM_ALLOC_BUF_OFFSET + buf), pBuf)

#define DSHM_TYP_NET_ALLOC_QTY_GET(msg) \
    DSHM_DAT16_GET(msg, 0)
#define DSHM_TYP_NET_ALLOC_SIZE_GET(msg) \
    DSHM_DAT16_GET(msg, 1)
#define DSHM_TYP_NET_ALLOC_TAG_GET(msg, tag) \
    DSHM_DAT16_GET(msg, (2 + (tag)))
#define DSHM_TYP_NET_ALLOC_BUF_GET(msg, buf) \
    DSHM_DAT32_GET(msg, (_DSHM_ALLOC_BUF_OFFSET + buf))
    
/* send requests a number of clusters (QuanTitY) and size and sends a buffer */
#define DSHM_TYP_NET_SEND_QTY_SET(msg, qty) \
    DSHM_DAT8_SET(msg, 0, qty)
#define DSHM_TYP_NET_SEND_REP_SET(msg, condition) \
    DSHM_DAT8_SET(msg, 1, condition)	/* condition can only be TRUE/FALSE */
#define DSHM_TYP_NET_SEND_SIZE_SET(msg, buf, size) \
    DSHM_DAT16_SET(msg, (1 + buf), size)
#define DSHM_TYP_NET_SEND_TAG_SET(msg, tag, tagValue) \
    DSHM_DAT16_SET(msg, (2 + (tag)), (tagValue))

#define DSHM_TYP_NET_SEND_QTY_GET(msg) \
    DSHM_DAT8_GET(msg, 0)
#define DSHM_TYP_NET_SEND_REP_GET(msg) \
    DSHM_DAT8_GET(msg, 1)
#define DSHM_TYP_NET_SEND_SIZE_GET(msg, buf) \
    DSHM_DAT16_GET(msg, (1 + buf))
#define DSHM_TYP_NET_SEND_TAG_GET(msg, tag) \
    DSHM_DAT16_GET(msg, (2 + (tag)))
    
/* bcast sends a bcast read tag */
#define DSHM_TYP_NET_BCAST_TAG_SET(msg, tag) \
    DSHM_DAT32_SET(msg, 0, tag)
#define DSHM_TYP_NET_BCAST_TAG_GET(msg) \
    DSHM_DAT32_GET(msg, 0)
    
void dshmMsgDump (DSHM(msg), const int align, const int level) 
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");

typedef struct _DSHM_SVC_OBJ
    {
    int svc;		/* unique service number */
    int hw;		/* hardware reference number */
    } DSHM_SVC_OBJ;

void dshmInit (const int debugLevel) 
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");

/* This macro is useful for quickly verifying success of data initialization,
 * outputting an error message if not, and jumping to a 'cleanup:' tag in the
 * routine.
 */
#define DSHM_INIT_VERIFY(test, fmt, args...) \
    do { \
	if (!(test)) \
	    { \
	    DSHM_PRINT ("!!FAILED!![%s:%d] " fmt, __FILE__, __LINE__, ##args); \
	    goto cleanup; \
	    } \
    } while ((0))

#ifdef __cplusplus
}
#endif

#endif	/* __INCdshmh */


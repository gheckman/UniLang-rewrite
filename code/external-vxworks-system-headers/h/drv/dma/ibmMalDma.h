/* ibmMalDma.h - IBM Memory Access Layer (MAL) library header */

/*
*******************************************************************************
   This source and object code has been made available to you by IBM on an
   AS-IS basis.

   IT IS PROVIDED WITHOUT WARRANTY OF ANY KIND, INCLUDING THE WARRANTIES OF
   MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE OR OF NONINFRINGEMENT
   OF THIRD PARTY RIGHTS.  IN NO EVENT SHALL IBM OR ITS LICENSORS BE LIABLE
   FOR INCIDENTAL, CONSEQUENTIAL OR PUNITIVE DAMAGES.  IBM'S OR ITS LICENSOR'S
   DAMAGES FOR ANY CAUSE OF ACTION, WHETHER IN CONTRACT OR IN TORT, AT LAW OR
   AT EQUITY, SHALL BE LIMITED TO A MAXIMUM OF $1,000 PER LICENSE.  No license
   under IBM patents or patent applications is to be implied by the copyright
   license.

   Any user of this software should understand that neither IBM nor its
   licensors will be responsible for any consequences resulting from the use
   of this software.

   Any person who transfers this source code or any derivative work must
   include the IBM copyright notice, this paragraph, and the preceding two
   paragraphs in the transferred software.

   Any person who transfers this object code or any derivative work must
   include the IBM copyright notice in the transferred software.

   COPYRIGHT   I B M   CORPORATION 2000
   LICENSED MATERIAL  -  PROGRAM PROPERTY OF  I B M

********************************************************************************
\NOMANUAL
*/

/* Copyright 1984-2004 Wind River Systems, Inc. */

/*
modification history
--------------------
01h,03sep04,mdo  Documentation fixes for apigen
01g,28may04,jln  add MAL_RX_GROUP_HANDLER_RUNING
01f,26aug03,jln  change malLib.c to ibmMalDma.h; 
                 change ibmMalRxGroupHandlerEnable() API
01e,07jul03,jln  rename EMAC_RXCHAN_GROUP to MAL_RXCHAN_GROUP
01d,11jun03,jln  modified MAL_DATA structure, more comments.
01c,16may01,mcg  common driver for walnut (405GP), cedar (NPe405x)
01b,15jan00,mcg  added alignment requirement for buffer descriptor rings
01a,18oct99,mcg  created
*/

/*
This file contains constants for the IBM Memory Access Layer core.
The emacEnd driver is tightly coupling with this header file, if any change 
in the MAL data structure and APIs, the emacEnd.c should be recompiled.
*/

#ifndef INCibmMalDmah
#define INCibmMalDmah

#ifdef __cplusplus
extern "C" {
#endif

#define MAL_NUM_TYPES  2
#define MAL_TX_TYPE    0
#define MAL_RX_TYPE    1
#define MAL_MAX_CHANNELS 32    /* 32 for receive, 32 for transmit */

/*
 * Reduced configurations of MAL are used for chips with fewer communication
 * cores inside.
 */

#define MAL_NO_INTS       0x00000000
#define MAL_EOB_INT_EN    0x00000001
#define MAL_DE_INT_EN     0x00000002
#define MAL_SERR_INT_EN   0x00000004

#define MAL_MAX_DESC            256            /* max descriptors per channel */
#define MAL_MAX_DESC_TBL_SIZE  (MAL_MAX_DESC * sizeof(MAL_BD))
#define MAL_DESC_REQ_ALIGN     (512*1024)      /* 512KB                       */

/* MAX RX channels in a board */

#ifndef MAX_MAL_RX_CHANS
#define MAX_MAL_RX_CHANS      4
#endif

/* MAL flags */

#define MAL_RX_GROUP_ENABLE                0x0001
#define MAL_RX_GROUP_POLL_ENABLE           0x0002
#define MAL_RX_GROUP_HANDLER_RUNING        0x0004

/* MAL Channel structure */

typedef struct
    {
    UINT         channelType;       /* TX_TYPE or RX_TYPE                     */
    UINT         channelNum;        /* channel number (0 through 31)          */
    UINT         bufferSizeRX;      /* receive buffer size if an RX channel   */
    UINT         channelIntMask;    /* interrupt mask for this channel        */
    VOIDFUNCPTR  functionEOB;       /* function for EOB int on this channel   */
    UINT         parmEOB;           /* parameter for the above function       */
    VOIDFUNCPTR  functionDescErr;   /* function for DE int on this channel    */
    UINT         parmDescErr;       /* parameter for the above function       */
    VOIDFUNCPTR  functionSERR;      /* function for MAL SERR int for this chn */
    UINT         parmSERR;          /* parameter for the above function       */
    } MAL_CHANNEL;

/*
 * MAL initialization structure.  This information is passed to the MAL driver
 * in malInit().
 */

typedef struct
    {
    UINT dcrBaseReg;
    UINT validChannels[MAL_NUM_TYPES];
    UINT intLvlTxeob;
    UINT intVecTxeob;
    UINT intLvlRxeob;
    UINT intVecRxeob;
    UINT intLvlTxde;
    UINT intVecTxde;
    UINT intLvlRxde;
    UINT intVecRxde;
    UINT intLvlSerr;
    UINT intVecSerr;
    } MAL_INIT;

/* Structure to group all EMAC_RX channels */

typedef struct
    {
    int             rotateIndex [MAX_MAL_RX_CHANS]; /* channel order to search */
    UINT            rotateRx [MAX_MAL_RX_CHANS];    /* RX channels index in order */
    UINT            chanNum;                        /* number of RX channels in group */
    UINT            maxRxPktsPerInterrupt;          /* Max RX packets in a interrupt */ 
    } MAL_RXCHAN_GROUP;

/*
 *  MAL driver control structure.
 */

typedef struct
    {
    MAL_INIT         malInit;
    char            *descTablesAlloc;
    char            *descTables;
    UINT             reserved1;
    MAL_CHANNEL      malChannelArray[MAL_NUM_TYPES][MAL_MAX_CHANNELS];
    UINT             malInitializedChannels[MAL_NUM_TYPES];
    UINT             malFlags;
    UINT             reserved2;
    MAL_RXCHAN_GROUP malRxChanGrp;
    UINT             reserved3;
    UINT             reserved4;
    } MAL_DATA;

/*
 * MAL Buffer Descriptor Structure.  The same structure is used for both
 * Transmit and Receive channels.
 */
typedef struct
    {
    USHORT   statusControl;              /* Shared between MAL and comm core */
    USHORT   dataLen;                    /* Buffer byte count                */
    char   * bufferAdrs;                 /* Buffer address                   */
    } MAL_BD;


/*
 * The status/control bits in the MAL buffer descriptor structure have different
 * meaning if the descriptor is used by a TX channel versus an RX channel.
 * Bits 0:5 are used to convey MAL control/status.  Bits 6:15 are
 * used to convey the communication core's (EMAC for example) control/status.
 */

/* MAL TX Descriptor Control/Status bits */
#define MAL_TX_CTRL_READY     0x8000           /* Packet ready to transmit    */
#define MAL_TX_CTRL_WRAP      0x4000           /* Last descriptor in the ring */
#define MAL_TX_CTRL_CM        0x2000
#define MAL_TX_CTRL_LAST      0x1000           /* Last buffer for this packet */
#define MAL_TX_CTRL_INTR      0x0400           /* Intr when packet TX complete*/

/* MAL RX Descriptor Control/Status bits */
#define MAL_RX_CTRL_EMPTY     0x8000           /* Buffer empty, ready to RX   */
#define MAL_RX_CTRL_WRAP      0x4000           /* Last descriptor in the ring */
#define MAL_RX_CTRL_CM        0x2000
#define MAL_RX_CTRL_LAST      0x1000           /* Last buffer for this packet */
#define MAL_RX_CTRL_FIRST     0x0800           /* 1st buffer for this packet  */
#define MAL_RX_CTRL_INTR      0x0400           /* Intr when packet RX complete*/

/* Masks */
#define MAL_MAL_CTRL_BITS     0xFC00           /* All descriptor bits for MAL */
#define MAL_COMMAC_CTRL_BITS  0x03FF           /* All descriptor bits for the */
                                               /* communications core         */

#define MAL_RX_ONE_BUFFER     (MAL_RX_CTRL_FIRST | MAL_RX_CTRL_LAST)


/* External functions */
#if defined(__STDC__) || defined(__cplusplus)

void   ibmMalReset             (UINT dcrBaseReg);
MAL_DATA * ibmMalInit          (MAL_INIT *pMalInit);
STATUS ibmMalChannelInit       (MAL_DATA *pMalData, MAL_CHANNEL *pChannel);
STATUS ibmMalChannelDelete     (MAL_DATA *pMalData, UINT channelType, UINT channelNum);
STATUS ibmMalChannelActivate   (MAL_DATA *pMalData, UINT channelType, UINT channelNum);
STATUS ibmMalChannelStop       (MAL_DATA *pMalData, UINT channelType, UINT channelNum);
STATUS ibmMalChannelIntMaskGet (MAL_DATA *pMalData, UINT channelType, UINT channelNum, UINT * intMask);
STATUS ibmMalChannelIntMaskSet (MAL_DATA *pMalData, UINT channelType, UINT channelNum, UINT intMask);
STATUS ibmMalChannelDescTblPtrGet (MAL_DATA *pMalData, UINT channelType, UINT channelNum,
                                   MAL_BD ** descTblAdrs);
STATUS ibmMalShutDown             (MAL_DATA * pMalData);
void   ibmMalRxGroupHandlerEnable (MAL_DATA *, BOOL, BOOL);
#else
void   ibmMalReset             ();
MAL_DATA * ibmMalInit          ();
STATUS ibmMalChannelInit       ();
STATUS ibmMalChannelDelete     ();
STATUS ibmMalChannelActivate   ();
STATUS ibmMalChannelStop       ();
STATUS ibmMalChannelIntMaskGet ();
STATUS ibmMalChannelIntMaskSet ();
STATUS ibmMalChannelDescTblPtrGet (); 
STATUS ibmMalShutDown             ();
void   ibmMalRxGroupHandlerEnable ();
#endif /* defined(__STDC__) || defined(__cplusplus) */

#ifdef __cplusplus
}
#endif

#endif  /* INCibmMalDmah */

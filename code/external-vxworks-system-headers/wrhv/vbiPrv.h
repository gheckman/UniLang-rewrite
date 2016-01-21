/* vbiPrv.h - virtual board interface private definitions */

/*
 * Copyright (c) 2009-2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01g,18apr11,wqi  VBI subset for CERT hypervisor.
01f,08feb11,jlv  Sync with HV 1.3 04-Feb-11 DVD
01e,24may10,jl   Sync with HV 1.2 25-May-10
01d,03mar10,rgo  Add vbiVbRemote prototype
01c,22sep09,d_c  Defect WIND00183017 Fix WIND00183019 - sync with 18-Sep HV
                 DVD
01b,13jul09,to   changes from v01b for HV 1.1
01a,03jul09,mmi  written
*/

#ifndef __INCvbiPrvh
#define __INCvbiPrvh

#include <vxWorks.h>
#include <vsbConfig.h>
#include <wrhv/vbiVersion.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifndef _ASMLANGUAGE

_WRS_INLINE vbiStatus_t _vbiStrncmp 
    (
    const char * s1, 
    const char * s2, 
    size_t n
    )
    {                                        
    if (n == 0)
	return (0);
 
    while (*s1++ == *s2++)
	{
 	if ((s1 [-1] == EOS) || (--n == 0))
 	    return (0);
        }
 
    return ((s1 [-1]) - (s2 [-1]));
    }

/* private ioapic operator */

extern vbiStatus_t vbiIoapicOp (uint32_t ioctl, vbiIrq_t irq, uint32_t filter,
				vbiVb_t vbId);

/* private interrupt redirection operator */

extern vbiStatus_t vbiVcoreIntRed_op (vbiIrq_t irq, vbiCore_t CoreId);

/* Name service private operator */

extern vbiStatus_t  vbiNsOp (uint32_t op, char* name, uint32_t rev, 
			     VBI_NS_HANDLE *handle, uint32_t timeout,
			     uint32_t options);

#if !defined(_WRS_CONFIG_WRHV_GUEST_CERT) && !defined(_WRS_CONFIG_WRHV_GUEST_CERT_DEBUG) 

/* Message receive private operator */

extern vbiStatus_t vbiReceiveOp
    (
    void		*rmsg, /* pointer to message to receive  */
    uint32_t		rlen,  /* length of message to receive   */
    VBI_MSG_INFO	*info, /* status info structure pointer  */
    VBI_MSG_CTL     	*ctl   /* control data structure pointer */
    );                                   

/* Remote VB private operator */

extern vbiStatus_t vbiVbRemote
    (
    uint32_t    	 op,          /* VB Remote operation */
    vbiVb_t     	 boardID,     /* Board ID */
    vbiCore_t   	 coreID,      /* Core ID */
    vbiGuestPhysAddr_t * out 	      /* Pointer to store return value */
    );
#endif /* !_WRS_CONFIG_WRHV_GUEST_CERT && !_WRS_CONFIG_WRHV_GUEST_CERT_DEBUG */

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INCvbiPrvh */

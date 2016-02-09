/* vbiDynamicVb.h - Dynamic VB VBI interface */

/*
 * Copyright (c) 2010-2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01d,11nov11,c_t  sync with HV2.0 23-sept-11 DVD.
01c,21sep11,c_t  mod for VBI subset for Cert Profile.
01b,08feb11,jlv  Sync with HV 1.3 04-Feb-11
01a,12nov10,dtr  written
*/

#ifndef __INCvbiDynamicVbh
#define __INCvbiDynamicVbh

#include <wrhv/vbiTypes.h>

#ifdef __cplusplus
extern "C" {
#endif


#ifndef	_ASMLANGUAGE

/* Cert Profile does not support dynamic VB. */

#if !defined(_WRS_CONFIG_WRHV_GUEST_CERT) &&\
    !defined(_WRS_CONFIG_WRHV_GUEST_CERT_DEBUG)

#ifndef VB_ALIGN_FIELD_64
#if defined(_WRS_CONFIG_LP64)
# define VB_ALIGN_FIELD_64(decl_var, pad_var)	\
			   __attribute__(( aligned(8) )) \
			   decl_var
#else
# if (__VBI_BYTE_ORDER == __VBI_LITTLE_ENDIAN)
#  define VB_ALIGN_FIELD_64(decl_var, pad_var)	\
			    __attribute__(( aligned(8) )) \
			    decl_var; \
			    uint32_t pad_var
# else
#  define VB_ALIGN_FIELD_64(decl_var, pad_var)	\
			    __attribute__(( aligned(8) )) \
			    uint32_t pad_var; \
			    decl_var
# endif
#endif
#endif

typedef uint64_t virtAddr_t;
typedef vbPciDevice_t vbiPciDevice_t;

/* This returns only the simple contiguous data */
vbiStatus_t vbiBoardSimpleConfigGet (vbiVb_t vbId, 
				     vbSimpleInformation_t *pVbInfo);

/* this returns also the complex data that has variable sixe e.g.device list */
vbiStatus_t vbiBoardConfigGet (vbiVb_t vbId, 
			       vbInformation_t *pVbInfo); 

vbiVb_t vbiVbCreate(vbInformation_t *pVbInfo, uint32_t options);
vbiStatus_t vbiVbDelete(vbiVb_t vbId);

/* Additive/Subtractive - i.e. not in zombie configuration */
vbiStatus_t vbiVbSharedMemoryAlloc(vbiVb_t vbId, vbiName_t smRegionName, 
				   virtAddr_t *va, size_t size);
vbiStatus_t vbiVbSharedMemoryFree(vbiVb_t vbId, vbiName_t smRegionName, 
				  virtAddr_t va);
vbiStatus_t vbiVbRamAlloc(vbiVb_t vbId, virtAddr_t *va, size_t size);
vbiStatus_t vbiVbRamFree(vbiVb_t vbId, virtAddr_t va);

/* Vb Core Migration */

/* Information can be optained for the Virtual boards such as prio and 
 * present Cpu using vbiBoardConfigGet() */
vbiStatus_t vbiVbMove(vbiVb_t vbId, uint32_t *pCpuList, 
		      uint32_t options);

#define VBIMOVE_OPTION_RESUME    0
#define VBIMOVE_OPTION_NO_RESUME 1

vbiStatus_t vbiVbPrioritySet(vbiVb_t vbId, uint32_t *pCpuPriorityList,
			     uint32_t options);

#define VBIPRIOSET_OPTION_RESUME    0
#define VBIPRIOSET_OPTION_NO_RESUME 1

#endif /* _WRS_CONFIG_WRHV_GUEST_CERT & DEBUG */
#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif

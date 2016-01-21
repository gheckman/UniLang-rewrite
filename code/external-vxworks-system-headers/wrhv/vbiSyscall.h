/* vbiSyscall.h - hypervisor system calls */

/*
 * Copyright (c) 2007-2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
02z,17feb12,c_t  sync with HV 2.0 27-jan-12 DVD
02y,18sep11,wqi  VBI subset for CERT hypervisor.
02x,07sep11,m_h  Sync with HV 1.3.1.1 02-Sept-11 DVD
02w,04apr11,jlv  Sync with HV 1.3 01-Apr-11 (WIND00265419)
02v,08feb11,jlv  Sync with HV 1.3 04-Feb-11 DVD
02u,27jan11,jlv  Fix apigen issues
02t,03nov10,rab  workaround 6.9 compiler alignment issue
02s,24may10,jl   Sync with HV 1.2 25-May-10
02r,29apr10,pad  Moved extern C statement after include statements.
02q,22mar10,wap  Add vbiDirectInterruptEOI() for direct interrupt support
02p,03mar10,rgo  Sync-up with hv1.2 view on 3/3/10.
02o,30nov09,jl   Sync with HV 1.1 04-Dec-09 DVD
02n,23oct09,jl   Sync with HV 1.1 30-Oct-09 DVD
02m,22sep09,d_c  Defect WIND00183017 Fix WIND00183019 - sync with 18-Sep HV
                 DVD
02l,18aug09,d_c  Sync with HV 1.1 14-Aug-09 DVD
                 HV vbiSyscall.h version  02p,12aug09,dtr
		 Update vbiHyIoctl API to add additional argument.
02k,02aug09,jl   support vbi register read, write
02k,22jul09,d_c  Add prototype for vbiKputc
02j,13jul09,to   changes from v02n for HV 1.1
02i,01jul09,to   VBI 2.0 APIs from vbiSyscall.h, v02m for HV 1.1
02h,25feb09,mmi  keep hypervisor definitions in a separate header file
02g,05feb09,to   vbiMgmt to vbiVbMgmt
02f,29jan09,rec  add MDIO macro definitions
02e,17dec08,to   modified for vxWorks
02d,12dec08,md   rename header files
02c,05dec08,mes  Removed shelf macros, added vbMgmt macros
02b,01dec08,md   add VBI_IOAPICIOCTL_SEND options
02a,21nov08,md   remove port and ED&R syscalls
01z,20nov08,mmi  adtopt new naming convention
01y,31oct08,dbt  Added vdkVtlbMmuOp hypercall.
01x,16jun08,mmi  fix vdkBspIoctl prototype
01w,19may08,gws  add vIoapicIoctl
01v,18apr08,md   add extra arg to vdkHyioctl
01u,11apr08,md   add EOI ioctl
01t,06mar08,md   add debug shell ioctl
01s,06dec07,foo  update hw ints
01r,23nov07,foo  fix prototype, use basic types
01q,25oct07,foo  updated with new vdk functions
01p,27sep07,md   added exception profiling fields
01o,26sep07,md   added profiling statistics and stats ioctl
01n,10sep07,md   re-number hypervisor system calls
01m,21aug07,md   added VDK_SYS_ctx_load_vmmu
01l,05jul07,foo  added bspIoctl calls and defines
01k,04jun07,md   added ctxctl and mmu system calls
01j,17may07,ymz  added port syscall.
01i,28may07,foo  update vdkInt prototype
01h,18may07,md   add hypervisor ioctl
01g,20apr07,md   add vmmu system calls
01f,18apr07,md   renamed to vdk
01e,10apr07,md   replace kprintf syscall with kputs and kputc
01d,19mar07,foo  fix macro
01c,17mar07,foo  modify definitions to all start with HY
01b,15mar07,md   added interrupt system calls
01a,09mar07,md   written
*/

#ifndef __INCvbiSyscallh
#define __INCvbiSyscallh

#include <vxWorks.h>
#include <vsbConfig.h>
#include <wrhv/vbiVersion.h>
#include <wrhv/vbiTypes.h>
#include <wrhv/wrhvHypercalls.h>
#include <wrhv/vbiArch.h>
#include <wrhv/vbInterface.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#ifndef	_ASMLANGUAGE

typedef void * VOID_PTR;

/* Forward declaration */
struct vmmuConfig;
#ifndef __cplusplus
struct VB_ARCH_CONTROL_REGS; 
#endif /* __cplusplus */

/* information about incoming message */

typedef struct vbiMsgInfo {
    vbiCtx_t id;			   /* context id of sender	      */
    uint32_t type;			   /* message type (msg/event)	      */
    uint64_t slen;			   /* length of sent buffer	      */
    uint64_t rlen;			   /* length of received buffer	      */
    uint16_t status;			   /* message status information      */
    uint16_t error;			   /* extended error status	      */
    uint64_t timestamp;			   /* time message was sent	      */
    uint32_t nmsg;			   /* number of queued msgs remaining */
} __attribute__((packed)) VBI_MSG_INFO;

/* message status bits as reported in the "status" field */

#define	VBI_MSG_STATUS_OK		0 /* message was transferred ok */
#define	VBI_MSG_STATUS_TRUNCATED	1 /* message was truncated */
#define	VBI_MSG_STATUS_COPY_ERROR	2 /* message wasn't able to be copied */

/* extended error codes reported in "error" field */

#define	VBI_MSG_ERROR_INTLEVEL          1 /* operation not allowed at int lvl */
#define	VBI_MSG_ERROR_BAD_ID            2 /* bad context id specified	      */
#define	VBI_MSG_ERROR_ABORTED           3 /* operation aborted		      */
#define	VBI_MSG_ERROR_TIMEOUT           4 /* operation timed out	      */
#define	VBI_MSG_ERROR_XCALL             5 /* cross call to remote cpu failed  */
#define	VBI_MSG_ERROR_UNSUPPORTED       6 /* the operation not allowed        */

/* message types as reported in the "type" field */

#define	VBI_MSG_TYPE_REGULAR  1	/* regular message */
#define	VBI_MSG_TYPE_EVENT    2	/* event message */
#define	VBI_MSG_TYPE_REPLY    3	/* reply message */

/* modifiers for message processing */

typedef struct vbiMsgCtl {
    uint32_t flags;	/* operation flags */
    uint32_t ordering;	/* order to receive messages */
    uint64_t timeout;	/* receive timeout		*/
} __attribute__((packed)) VBI_MSG_CTL;

/* message control flags */
#define VBI_MSG_CTL_FLAG_RETRY 1

/* memory read/write control structure */

typedef struct vbiMemCtl
    {
    VB_ALIGN_FIELD_64 (VOID_PTR pBuffer, pad1); /* address of target context */
    VB_ALIGN_FIELD_64 (VOID_PTR pAddress, pad2);/* address of calling context */
    uint64_t	sizeIn;		    /* number of bytes to be read	    */
    uint64_t	sizeOut;	    /* number of bytes successfully read    */
    uint32_t	flags;	    	    /* data/instruction flush option	    */
  } VBI_MEM_CTL;

#define VBI_DCACHE_FLUSH 	0x0001
#define VBI_ICACHE_INV 		0x0002

#if !defined(_WRS_CONFIG_WRHV_GUEST_CERT) && \
    !defined(_WRS_CONFIG_WRHV_GUEST_CERT_DEBUG)
/* system call prototypes for use within a context */

extern int  vbiHyIoctl (unsigned ioctl, void *arg1, void *arg2, void *arg3,
			void *arg4);
extern int  vbiIoapicIoctl (unsigned ioctl, unsigned arg1, unsigned arg2);
extern int  vbiCtxctl (unsigned operation, unsigned arg1, unsigned arg2);
extern int32_t vbiVbMgmt (uint32_t cmd, uint32_t boardId, int32_t *outError,
			  uint32_t flags, void * ctl);
extern int  vbiVtlbOp (unsigned int op, unsigned long arg1,
			  unsigned long arg2, unsigned long arg3);
#endif /* !_WRS_CONFIG_WRHV_GUEST_CERT && !_WRS_CONFIG_WRHV_GUEST_CERT_DEBUG */

/* name server options and timeouts */

#define VBI_NS_NOVERSION	  0xffffffff /* no specific service version */
#define VBI_NS_ANYVERSION	  0xffffffff /* match any service version   */
#define VBI_NS_OPTION_NONE	  0x0000     /* no options		    */
#define VBI_NS_OPTION_LOOKUP_WAIT 0x0001     /* wait for name registration  */
#define VBI_NS_NO_TIMEOUT	  0x0000     /* wait forever */

/*
 * Modified APIs for VBI 2.0 
 */

/* Message send	    */

extern vbiStatus_t vbiSend (vbiCtx_t	    id, 
			    void	    *smsg, 
			    size_t	    slen, 
			    void	    *rmsg,
			    size_t	    rlen, 
			    VBI_MSG_INFO    *info, 
			    VBI_MSG_CTL    *ctl);
/* message receive  */

#if !defined(_WRS_CONFIG_WRHV_GUEST_CERT) && \
    !defined(_WRS_CONFIG_WRHV_GUEST_CERT_DEBUG)


extern vbiStatus_t vbiReceive (void		*rmsg, 
			       uint32_t		rlen, 
			       VBI_MSG_INFO	*info,
			       VBI_MSG_CTL     *ctl);                                   
/* message reply */

extern int32_t vbiReply (vbiCtx_t	    id, 
			 void		    *smsg, 
			 size_t		    slen, 
			 VBI_MSG_CTL	    *ctl);

#endif /* !_WRS_CONFIG_WRHV_GUEST_CERT && !_WRS_CONFIG_WRHV_GUEST_CERT_DEBUG */
extern vbiStatus_t vbiPanic (const char *msg);
extern vbiStatus_t vbiDcacheFlush (void *saddr, size_t size);
extern vbiStatus_t vbiIcacheFlush (void *saddr, size_t size);

#ifndef _WRS_CONFIG_WRHV_GUEST_CERT
extern vbiStatus_t vbiKputs (const char *s);
extern vbiStatus_t vbiKputc (int c);

extern vbiStatus_t vbiVmmuConfig (struct vmmuConfig * config);
extern vbiStatus_t vbiVmmuCreate (struct vmmuConfig * config);
extern vbiStatus_t vbiVmmuDelete (struct vmmuConfig * config);
extern vbiStatus_t vbiVmmuEnable (uint32_t  vmmu_num);
extern vbiStatus_t vbiVmmuDisable (uint32_t vmmu_num);
extern vbiStatus_t vbiVmmuTlbFlush (struct vmmuConfig * config, void *addr, size_t len);
#endif /* !_WRS_CONFIG_WRHV_GUEST_CERT */
extern vbiStatus_t vbiNsRegister (char  *name, uint32_t  revision);
extern vbiStatus_t vbiNsUnregister (char *name, uint32_t  revision);
extern vbiStatus_t vbiNsLookupOld (char *name, uint32_t  rev,
				   VBI_NS_HANDLE *pHandle);
extern vbiStatus_t vbiNsLookup (char *name, uint32_t  rev,
				VBI_NS_HANDLE *pHandle, uint32_t timeout,
				uint32_t options);

/* Prior to vbi 2.0 these api were vbiMmuAttrSet/Get */

#if !defined(_WRS_CONFIG_WRHV_GUEST_CERT) &&\
    !defined(_WRS_CONFIG_WRHV_GUEST_CERT_DEBUG)

extern vbiStatus_t  vbiMemAttrSet (void *vaddr, size_t len, vbiMemAttr_t attr);
extern vbiStatus_t  vbiMemAttrGet (void *vaddr, vbiMemAttr_t * attr);

#endif /* !_WRS_CONFIG_WRHV_GUEST_CERT && !_WRS_CONFIG_WRHV_GUEST_CERT_DEBUG */

/*
 * START: New APIs introduced for vbi 2.0  
 */

extern void vbiIntVCoreUnlock (void);
extern vbiIntState_t vbiIntVCoreLock (void);
extern vbiStatus_t vbiCacheTextUpdate (void *saddr, size_t size);
extern vbiStatus_t  vbiExcBaseSet (void * excTblBase);

/* interrupt handling APIs */

extern void vbiDirectInterruptEOI (void);

/* virtual board management APIs */

extern vbiStatus_t vbiVbReset (vbiVb_t id, vbiCore_t core, uint32_t options);
#if !defined(_WRS_CONFIG_WRHV_GUEST_CERT) && \
    !defined(_WRS_CONFIG_WRHV_GUEST_CERT_DEBUG)

extern vbiStatus_t vbiVbSuspend (vbiVb_t id, vbiCore_t core);
extern vbiStatus_t vbiVbRestart (vbiVb_t id, vbiCore_t core);
extern vbiStatus_t vbiVbResume (vbiVb_t id, vbiCore_t core);

/* read remote vb's memory */

extern vbiStatus_t vbiVbMemoryRead (VBI_MEM_CTL *memCtl, vbiVb_t targetBoard);
extern vbiStatus_t vbiVbMemoryWrite (VBI_MEM_CTL *memCtl, vbiVb_t targetBoard);

#endif /* !_WRS_CONFIG_WRHV_GUEST_CERT && !_WRS_CONFIG_WRHV_GUEST_CERT_DEBUG */
#ifndef _WRS_CONFIG_WRHV_GUEST_CERT
extern void vbiDebugShellStart (uint32_t  flags);
#endif /* !_WRS_CONFIG_WRHV_GUEST_CERT */

/* read/write remote vb's registers */

#if !defined(_WRS_CONFIG_WRHV_GUEST_CERT) &&\
    !defined(_WRS_CONFIG_WRHV_GUEST_CERT_DEBUG)

extern vbiStatus_t vbiVbRegisterRead (VBI_HREG_SET_CMPLX_QUALIFIED *regSet, 
					vbiVb_t targetBoard,
					vbiCore_t core);
extern vbiStatus_t vbiVbRegisterWrite (VBI_HREG_SET_CMPLX_QUALIFIED *regSet, 
					vbiVb_t targetBoard,
					vbiCore_t core);

#endif /* !_WRS_CONFIG_WRHV_GUEST_CERT && !_WRS_CONFIG_WRHV_GUEST_CERT_DEBUG */

extern vbiStatus_t vbiBspIoctl(unsigned, int, int, int, int, int, int, int);

/*
 * END: New APIs introduced for vbi 2.0  
 */


#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif  /* __INCvbiSyscallh */

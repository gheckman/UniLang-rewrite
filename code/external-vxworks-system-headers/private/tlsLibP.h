/* tlsLibP.h - TLS private interface header */

/*
 * Copyright (c) 2006-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01g,10sep10,jpb  Added function pointer _func_tlsSizeGet.
01f,23jul10,gvm  updates for 64-bit user side TLS ABI 
01f,12jul10,gvm  ICC implements __tls_varp
01e,14oct09,gvm  Fix for defect WIND00104917
01e,23sep09,gvm  adapted to LP64
01d,12apr08,mcm  Using the same definition of TLS_VAR_ADDR for both compilers
01c,14jun07,jpb  Changed definition of TLS_VAR_ADDR based on compiler
01b,25apr07,gls  ported to user side
01a,19oct06,dbt  written
*/


#ifndef __INCtlsLibPh
#define __INCtlsLibPh

#ifdef __cplusplus
extern "C" {
#endif

/* type declaration */

struct __tls__var;

/* variable declarations */

#ifdef _WRS_KERNEL
IMPORT UCHAR	wrs_kernel_tls_data_start [];
IMPORT UCHAR	wrs_kernel_tls_data_size [];
IMPORT UCHAR	wrs_kernel_tls_vars_start [];
IMPORT UCHAR	wrs_kernel_tls_vars_size [];
IMPORT UCHAR	wrs_kernel_tls_data_align [];
#else
IMPORT UCHAR	__wrs_rtp_tls_data_start [];
IMPORT UCHAR	__wrs_rtp_tls_data_size [];
IMPORT UCHAR	__wrs_rtp_tls_vars_start [];
IMPORT UCHAR	__wrs_rtp_tls_vars_size [];
IMPORT UCHAR	__wrs_rtp_tls_data_align [];
#endif

/* defines */

/* Get the pointer on a __thread variable structure given its name */

#if	defined(__RTP__) && defined(_WRS_CONFIG_LP64)
#define	TLS_VAR_ADDR(x)		(&(x))
#else
#define TLS_VAR_ADDR(x)		__tls_varp(&(x))
#if defined(__GNUC__) && !defined(__INTEL_COMPILER)
#define	__tls_varp		__builtin___tls_varp
#endif	/* __GNUC__ && !__INTEL_COMPILER */
#endif	/* __RTP__ && _WRS_CONFIG_LP64 */

/* function declarations */

#if	defined(__RTP__) && defined(_WRS_CONFIG_LP64)
extern void *	tlsByTaskLookup		(void * pTlsVar, TASK_ID tid);
#else
extern void *	tlsByTaskLookup		(struct __tls__var * pTlsVar,
					 TASK_ID tid);
#endif	/* __RTP__ && _WRS_CONFIG_LP64 */

#ifdef	_WRS_KERNEL
extern void	tlsLibInit		(void * tlsVarsAddr,
					 UINT32 tlsVarsSize,
					 void * tlsDataAddr,
					 UINT32 tlsDataSize,
					 UINT32 tlsDataAlignment);

extern void	tlsLoadLibInit		(void);
#endif	/* _WRS_KERNEL */

/* function pointers */

#ifndef _WRS_KERNEL
extern int     (*_func_tlsSizeGet)(void); 
#endif /* !_WRS_KERNEL */

#ifdef __cplusplus
}
#endif

#endif /* __INCtlsLibPh */

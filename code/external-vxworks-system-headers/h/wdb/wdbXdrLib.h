/* wdbXdrLib.h - External Data Representation Serialization Routines for WDB */

/*
 * Copyright (c) 2005-2007 Wind River Systems, Inc.  
 *
 * The right to copy, distribute, modify or otherwise make use of this 
 * software may be licensed only pursuant to the terms of an applicable Wind 
 * River license agreement.
 */

/*
modification history
--------------------
01c,10jul07,tbu  Fixed for 64 bits big endian, some cleanup
01b,06jul07,p_b  Added 64 bits support
01a,06dec05,dbt	 written based on xdr.h
*/

#ifndef __INCwdbXdrLibh
#define __INCwdbXdrLibh

#ifdef __cplusplus
extern "C" {
#endif

/*
DESCRIPTION

Header file for WDB XDR implementation. This header file is mean to be used
only when building runtime XDRs, it should not be used when building 
Target Server. The main reason for this WDB XDR implementation is to provide
a fully standalone WDB agent that does not depend on the runtime Operating
System source and header files.
*/

/* defines */

#define	WDB_XDR_SETPOS		wdbXdrSetpos
#define	WDB_XDR_GETPOS		wdbXdrGetpos
#define	WDB_XDR_INLINE		wdbXdrInline
#define	WDB_XDR_PUTBYTES	wdbXdrPutbytes

#define	WDB_XDR_GETLONG(xdrs,lp)	\
    wdbXdrGetVal((xdrs),(lp),sizeof(long))
#define	WDB_XDR_PUTLONG(xdrs,lp)	\
    wdbXdrPutVal((xdrs),(lp),sizeof(long))
#define	WDB_XDR_GETUINT32(xdrs,lp)	\
    wdbXdrGetVal((xdrs),(lp),sizeof(UINT32))
#define	WDB_XDR_PUTUINT32(xdrs,lp)	\
    wdbXdrPutVal((xdrs),(lp),sizeof(UINT32))
#define WDB_XDR_GETADDR(xdrs,lp)	\
    wdbXdrGetVal((xdrs),(lp),sizeof(TGT_ADDR_T))
#define WDB_XDR_PUTADDR(xdrs,lp)	\
    wdbXdrPutVal((xdrs),(lp),sizeof(TGT_ADDR_T))

/* XDR type definitions (target only) */

typedef enum wdb_xdr_op
    {
    WDB_XDR_ENCODE	= 0,
    WDB_XDR_DECODE	= 1,
    WDB_XDR_FREE	= 2
    } WDB_XDR_OP;

typedef struct wdb_xdr
    {
    WDB_XDR_OP	x_op;		/* operation; fast additional param */
    char *	x_private;	/* pointer to private data */
    char * 	x_base;		/* private used for position info */
    UINT32	x_handy;	/* extra private word */
    } WDB_XDR;

typedef	BOOL (*wdbXdrProc_t)();

/* function declarations */

extern void	wdbXdrCreate	(WDB_XDR * xdrs, char * addr,
				 UINT32 size, WDB_XDR_OP op);
extern BOOL	wdbXdrSetpos	(WDB_XDR * xdrs, UINT32 pos);
extern UINT32	wdbXdrGetpos	(WDB_XDR * xdrs);

extern UINT32 * wdbXdrInline	(WDB_XDR * xdrs, size_t len);
extern BOOL	wdbXdrPutbytes	(WDB_XDR * xdrs, char * addr,
				 size_t len); 

extern BOOL wdbXdrGetVal 	(WDB_XDR * xdrs,void * lp,
				 size_t    size);
extern BOOL wdbXdrPutVal 	(WDB_XDR * xdrs,void * lp,
				 size_t    size);

#ifdef __cplusplus
}
#endif

#endif /* __INCwdbXdrLibh */

/* wdbGopherLib.h - info gathering interpreter header for the agent */

/*
 * Copyright (c) 2003-2007 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this
 * software may be licensed only pursuant to the terms of an applicable Wind
 * River license agreement.
 */

/*
modification history
--------------------
01i,26jun07,tbu  Added 64 bit support
          + p_b  completed support
01h,24jan06,tbu  Added the OS-specific hook for special commands
01g,04jan06,dbt  Made several routines private. Added
                 gopherWriteChar() prototype.
01f,08dec05,dbt  Replaced IMPORT with extern.
01e,22nov05,dbt  Updated gopher function prototypes.
01d,16jun05,jmp  moved to share/src/agents/wdb.
01c,28may04,elg  Fix compiler warning.
01b,29mar04,elg  Add information to reorder numbers following endianness if
                 necessary.
01a,19feb03,elg  Written from wdbGopherLib.c.
*/

/*
DESCRIPTION
*/

#ifndef	__INCwdbGopherLibh
#define	__INCwdbGopherLibh

#ifdef	__cplusplus
extern "C" {
#endif	/* __cplusplus */

/* typedef */

enum byte_reorder
    {
    NO_REORDER,		/* no byte reordering */
    NTOH_REORDER,	/* perform a hton() before writing to tape */
    HTON_REORDER	/* perform a ntoh() before writing to tape */
    };

typedef struct
    {
    char *		program;	/* where to start executing */
    TGT_ADDR_T 		p;		/* initial value of pointer */
    WDB_POINTER_SIZE    pointerSize;	/* actual size of pointer */
    char *		pTape;		/* tape array */
    int			tapeIx;		/* index in tape to write next cell */
    int			tapeLen;	/* total length of tape */
    int			execute;	/* whether to execute, or just parse */
    unsigned int	status;		/* error code */
    enum byte_reorder	byteReorder;	/* do we have to reorder numbers ? */
    } wdbGopherCtx_t;

/* externals */

extern UINT32 gopherWriteChar	(wdbGopherCtx_t * gc, char value);
extern UINT32 gopherWriteScalar	(wdbGopherCtx_t * gc, UINT8 * src, int type);
extern void gopherHookAdd       (UINT32 (*gopherHook) (wdbGopherCtx_t * gc));

#ifdef	__cplusplus
}
#endif	/* __cplusplus */

#endif	/* __INCwdbGopherLibh */

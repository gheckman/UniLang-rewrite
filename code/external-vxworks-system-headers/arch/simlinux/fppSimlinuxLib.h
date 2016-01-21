/* fppLib.h - floating-point coprocessor support library header */

/*
 * Copyright (c) 1998,2002-2003,2010,2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this
 * software may be licensed only pursuant to the terms of an applicable
 * Wind River license agreement.
 */

/*
modification history
--------------------
01j,05sep11,elp  Added xmm registers to host regset (CQID: WIND00286339)
01i,06apr11,elp  added xmm8-xmm15
01h,30sep10,elp  fixed FPXREG_FPX() macro.
01g,14sep10,elp  Added SSE support (64-bits).
01f,14jan10,elp  64bits support.
01e,19aug03,dbt  Added PAL support.
01d,17jun03,jmp  code cleanup.
01c,27mar03,jmp  rewrote from i86.
01b,03may02,jmp  added fppDtoDx() & fppDxtoD().
01a,29apr98,cym  derived from i86
*/

#ifndef	__INCfppSimntLibh
#define	__INCfppSimntLibh

#ifdef __cplusplus
extern "C" {
#endif

/* number of fp registers on coprocessor */

#define FP_NUM_REGS	8	/* number of FP registers	*/
#define XSAVE_HEADER	64 	/* number of bytes in the XSAVE header */

#ifdef _WRS_CONFIG_LP64
#define XMM_NUM_REGS	16	/* number of XMM registers */
#define FP_NUM_RESERVED	6	/* reserved area in FPX_CONTEXT */

/* FPREG_SET structure offsets */

#define	FPREG_FPCR	0x00	/* offset to FPCR in FPREG_SET */
#define	FPREG_FPSR	0x04	/* offset to FPSR in FPREG_SET */
#define	FPREG_FPTAG	0x08	/* offset to FPTAG in FPREG_SET */
#define	FPREG_OP	0x0c	/* offset to OP in FPREG_SET */
#define	FPREG_IP	0x10	/* offset to IP in FPREG_SET */
#define	FPREG_CS	0x14	/* offset to CS in FPREG_SET */
#define	FPREG_DP	0x18	/* offset to DP in FPREG_SET */
#define	FPREG_DS	0x1c	/* offset to DS in FPREG_SET */
#define FPREG_FPX(n)	(0x20 + (n)*sizeof(DOUBLEX)) /* offset to FPX(n) */

#else /* _WRS_CONFIG_LP64 */

#define XMM_NUM_REGS	8	/* number of XMM registers */
#define FP_NUM_RESERVED	14	/* reserved area in FPX_CONTEXT */

/* FPREG_SET structure offsets */

#define	FPREG_FPCR	0x00	/* offset to FPCR in FPREG_SET */
#define	FPREG_FPSR	0x04	/* offset to FPSR in FPREG_SET */
#define	FPREG_FPTAG	0x08	/* offset to FPTAG in FPREG_SET */
#define	FPREG_OP	0x0c	/* offset to OP in FPREG_SET */
#define	FPREG_IP	0x10	/* offset to IP in FPREG_SET */
#define	FPREG_CS	0x12	/* offset to CS in FPREG_SET */
#define	FPREG_DP	0x14	/* offset to DP in FPREG_SET */
#define	FPREG_DS	0x18	/* offset to DS in FPREG_SET */
#define FPREG_FPX(n)	(0x1c + (n)*sizeof(DOUBLEX)) /* offset to FPX(n) */

#endif /* _WRS_CONFIG_LP64 */

/* FPO_CONTEXT structure offsets */

#define FPO_CONTEXT_FPCR	0x00	/* offset to FPCR in FPO_CONTEXT */
#define FPO_CONTEXT_FPSR	0x04	/* offset to FPSR in FPO_CONTEXT */
#define FPO_CONTEXT_FPTAG	0x08	/* offset to FPTAG in FPO_CONTEXT */
#define FPO_CONTEXT_IP		0x0c	/* offset to IP in FPO_CONTEXT	*/
#define FPO_CONTEXT_CS		0x10	/* offset to CS in FPO_CONTEXT	*/
#define FPO_CONTEXT_OP		0x12	/* offset to OP in FPO_CONTEXT	*/
#define FPO_CONTEXT_DP		0x14	/* offset to DP in FPO_CONTEXT	*/
#define FPO_CONTEXT_DS		0x18	/* offset to DS in FPO_CONTEXT	*/
#define FPO_CONTEXT_FPX(n)	(0x1c + (n)*sizeof(DOUBLEX))

/* FPX_CONTEXT - structure offsets for New FP context */

#define	FPX_CONTEXT_FPCR	0x00	/* offset to FPCR in FPX_CONTEXT */
#define	FPX_CONTEXT_FPSR	0x02	/* offset to FPSR in FPX_CONTEXT */
#define	FPX_CONTEXT_FPTAG	0x04	/* offset to FPTAG in FPX_CONTEXT */
#define	FPX_CONTEXT_OP		0x06	/* offset to OP in FPX_CONTEXT */
#define	FPX_CONTEXT_IP		0x08	/* offset to IP in FPX_CONTEXT */
#define	FPX_CONTEXT_CS		0x0c	/* offset to CS in FPX_CONTEXT */
#define	FPX_CONTEXT_DP		0x10	/* offset to DP in FPX_CONTEXT */
#define	FPX_CONTEXT_DS		0x14	/* offset to DS in FPX_CONTEXT */
#define	FPX_CONTEXT_RSVD0	0x18    /* offset to RESERVED0 in FPX_CONTEXT */
#define	FPX_CONTEXT_RSVD1	0x1c    /* offset to RESERVED1 in FPX_CONTEXT */
#define FPX_CONTEXT_FPX(n)	(0x20 + (n)*sizeof(DOUBLEX_SSE)) /* FPX(n) */

/* FPU Control Word register */
#define FPCR_PC_MASK    0xfcff      /* Precision Control Field mask */
#define FPCR_PC_DOUBLE  0x0200          /* Double precision */

#ifndef _ASMLANGUAGE

/* DOUBLEX - double extended precision */

typedef struct
    {
    unsigned char f[10];
    } DOUBLEX;

typedef struct 
    {
    UCHAR f[10];	/* ST[0-7] or MM[0-7] */
    UCHAR r[6];		/* reserved */
    } DOUBLEX_SSE;

/* FPO_CONTEXT - Old FP context used by fsave/frstor instruction */

typedef struct fpOcontext
    {
    int		fpcr;			/* 0x00: 4 control word */
    int		fpsr;			/* 0x04: 4 status word */
    int		fptag;			/* 0x08: 4 tag word */
    int		ip;			/* 0x0c: 4 instruction pointer */
    short	cs;			/* 0x10: 2 instr pointer selector */
    short	op;			/* 0x12: 2 last FP instr op code */
    int		dp;			/* 0x14: 4 data pointer */
    int		ds;			/* 0x18: 4 data pointer selector */
    DOUBLEX	fpx[FP_NUM_REGS];	/* 0x1c: 8*10 FR[0-7] non-TOS rel. order */
    } FPO_CONTEXT;			/* 108  bytes total */

/* FPX_CONTEXT - New FP context used by fxsave/fxrstor instruction */

typedef struct fpXcontext
    {
    short	fpcr;			/* 0x00: 2 control word */
    short	fpsr;			/* 0x02: 2 status word */
    short	fptag;			/* 0x04: 2 tag word */
    short	op;			/* 0x06: 2 last FP instr op code */
    int		ip;			/* 0x08: 4 instruction pointer */
    int		cs;			/* 0x0c: 4 instr pointer selector */
    int		dp;			/* 0x10: 4 data pointer */
    int		ds;			/* 0x14: 4 data pointer selector */
    int		reserved0;		/* 0x18: 4 reserved */
    int		reserved1;		/* 0x1c: 4 reserved */
    DOUBLEX_SSE	fpx[FP_NUM_REGS];	/* 0x20: 8*16  FR[0-7] non-TOS rel. order */
    DOUBLEX_SSE	xmm[XMM_NUM_REGS];	/* 8*16  XMM[0-7] */
    DOUBLEX_SSE	res2[FP_NUM_RESERVED];	/* 14*16 reserved */
    } FPX_CONTEXT;			/* 512   bytes total */

/* FPX_EXT_CONTEXT - Extended FP context used by xsave/xrstor instruction */

typedef struct fpXExtContext
    {
    short	    fpcr;		/* 0x00: 2 control word */
    short	    fpsr;		/* 0x02: 2 status word */
    short	    fptag;		/* 0x04: 2 tag word */
    short	    op;		        /* 0x06: 2 last FP instr op code */
    int		    ip;		        /* 0x08: 4 instr pointer */
    int		    cs;		        /* 0x0c: 4 instr pointer selector */
    int		    dp;		        /* 0x10: 4 data pointer */
    int		    ds;		        /* 0x14: 4 data pointer selector */
    int		    reserved0;	        /* 0x18: 4 reserved */
    int		    reserved1;	        /* 0x20: 4 reserved */
    DOUBLEX_SSE	    fpx[FP_NUM_REGS];   /* 0x24: 8*16 FR[0-7]  */
    DOUBLEX_SSE	    xmm[XMM_NUM_REGS];  /* 8*16  XMM[0-7] */
    DOUBLEX_SSE	    res2[FP_NUM_RESERVED];	/* 14*16 reserved */
    UCHAR           xSaveHeader[XSAVE_HEADER];  /* 64    XSave header */   
    DOUBLEX_SSE     ymm[XMM_NUM_REGS];  /* 8*16  higher 128 bits of YMM[0-7] */
    } FPX_EXT_CONTEXT;			/* 704   bytes total */

/* FP_CONTEXT - Common FP context */

typedef struct fpContext
    {
    union u
	{
	FPO_CONTEXT o;			/* old FPO_CONTEXT for fsave/frstor */
	FPX_CONTEXT x;			/* new FPX_CONTEXT for fxsave/fxrstor */
	FPX_EXT_CONTEXT	x_ext;		/* FPX_EXT_CONTEXT xsave/xrestore */
	} u;
    } FP_CONTEXT;

#ifdef _WRS_CONFIG_LP64
/* FPREG_SET - FP register set that is different from FP_CONTEXT */

typedef struct fpregOSet
    {
    int		fpcr;			/* 0x00: control word */
    int		fpsr;			/* 0x04: status word */
    int		fptag;			/* 0x08: tag word */
    int		op;			/* 0x0c: last FP instruction op code */
    int		ip;			/* 0x10: instruction pointer */
    int		cs;			/* 0x14: instruction pointer selector */
    int		dp;			/* 0x18: data pointer */
    int		ds;			/* 0x1c: data pointer selector */
    DOUBLEX	fpx[FP_NUM_REGS];	/* 0x20: FR[0-7] non-TOS rel. order */
    } FPREGO_SET;

#else /* _WRS_CONFIG_LP64 */

typedef FPO_CONTEXT FPREGO_SET;

#endif /* _WRS_CONFIG_LP64 */

typedef struct fpregXSet
    {
    int		fpcr;			/* 0x00: control word */
    int		fpsr;			/* 0x04: status word */
    int		fptag;			/* 0x08: tag word */
    int		op;			/* 0x0c: last FP instruction op code */
    int		ip;			/* 0x10: instruction pointer */
    int		cs;			/* 0x14: instruction pointer selector */
    int		dp;			/* 0x18: data pointer */
    int		ds;			/* 0x1c: data pointer selector */
    DOUBLEX	fpx[FP_NUM_REGS];	/* 0x20: FR[0-7] non-TOS rel. order */
    DOUBLEX_SSE	xmm[XMM_NUM_REGS];	/* [8|16]*16 XMM[0-[7|15]] */
    } FPREGX_SET;

typedef struct fpregXExtSet
    {
    int		fpcr;			/* 0x00: control word */
    int		fpsr;			/* 0x04: status word */
    int		fptag;			/* 0x08: tag word */
    int		op;			/* 0x0c: last FP instruction op code */
    int		ip;			/* 0x10: instruction pointer */
    int		cs;			/* 0x14: instruction pointer selector */
    int		dp;			/* 0x18: data pointer */
    int		ds;			/* 0x1c: data pointer selector */
    DOUBLEX	fpx[FP_NUM_REGS];	/* 0x20: FR[0-7] non-TOS rel. order */
    DOUBLEX_SSE	xmm[XMM_NUM_REGS];	/* [8|16]*16 XMM[0-[7|15]] */
    DOUBLEX_SSE	ymm[XMM_NUM_REGS];	/* [8|16]*16 higher 128 bits of YMM */
    } FPREGXEXT_SET;

typedef struct fpregSet
    {
    union n
    	{
	FPREGO_SET	o;
	FPREGX_SET	x;
	FPREGXEXT_SET	x_ext;
	} n;
    } FPREG_SET;

/* variable declarations */

extern REG_INDEX fpRegName[];           /* f-point data register table */
extern REG_INDEX fpCtlRegName[];        /* f-point control register table */
extern FUNCPTR   fppCreateHookRtn;      /* arch dependent create hook routine */
extern FUNCPTR   fppDisplayHookRtn;     /* arch dependent display routine */

/* func ptr to fppSave/fppXsave */

extern void (* _func_fppSaveRtn) (FP_CONTEXT *);

/* func ptr to fppRestore/fppXrestore */

extern void (* _func_fppRestoreRtn) (FP_CONTEXT *);

/* function declarations */

extern	void	fppArchInit (void);
extern	STATUS	fppProbe (void);
extern	void	fppDtoDx (DOUBLEX * pDx, double * pDouble);
extern	void	fppDxtoD (double * pDouble, DOUBLEX * pDx);

extern  void	fppRegsToCtx (FPREG_SET * pFpRegSet, FP_CONTEXT * pFpContext);
extern  void	fppCtxToRegs (FP_CONTEXT * pFpContext, FPREG_SET * pFpRegSet);
#ifdef _WRS_CONFIG_LP64
extern void	fppXregsToCtx (FPREG_SET * pFpRegSet, FP_CONTEXT * pFpContext);
extern  void    fppXctxToRegs (FP_CONTEXT * pFpContext, FPREG_SET * pFpRegSet);
#endif /* _WRS_CONFIG_LP64 */

extern FP_CONTEXT *	fppCtxCreate (TASK_ID tid);
extern STATUS		fppCtxDelete (FP_CONTEXT * pCtx);
extern void		fppCtxShow (FP_CONTEXT * pFpContext);
extern STATUS		fppEnable (void);
extern STATUS		fppDisable (void);

#endif  /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCfppSimntLibh */

/* fppX86_64Lib.h - floating-point coprocessor support library header */

/* Copyright 2009-2011 Wind River Systems, Inc. */

/*
modification history
--------------------
01h,22dec11,jjk  WIND00313302 - Fix display of FP/MMX registers
01g,27jul11,g_x  add xmm[] and ymm[] to FPREG_SET (WIND00285122)
01f,22mar11,ggm  WIND00262870 - Added fppArchCpuInit.
01e,19jan11,ggm  XSave / XRestore implementation for extended state context
                 switch.
01d,29sep10,scm  adjust offset for FPXREG_FPX for DOUBLEX_SSE structs...
01c,23sep10,scm  adjust 64 bit structures...
01b,08jul09,scm  FUNCPTR conversion...
01a,26jan09,jb   Create 64-bit version from 32-bit version 01h
*/

#ifndef	__INCfppX86_64Libh
#define	__INCfppX86_64Libh

#ifdef __cplusplus
extern "C" {
#endif

/* control register: defines for control word */

#define	FPCR_IM			0x0001	/* IM exc-mask invalid operation */
#define	FPCR_DM			0x0002	/* DM exc-mask denormalized operand */
#define	FPCR_ZM			0x0004	/* ZM exc-mask zero divide */
#define	FPCR_OM			0x0008	/* OM exc-mask overflow */
#define	FPCR_UM			0x0010	/* UM exc-mask underflow */
#define	FPCR_PM			0x0020	/* PM exc-mask precision */
#define	FPCR_PC_SINGLE		0x0000	/* PC single precision(24 bits) */
#define	FPCR_PC_DOUBLE		0x0200	/* PC double precision(53 bits) */
#define	FPCR_PC_EXTENDED	0x0300	/* PC extended precision(64 bits) */
#define	FPCR_PC_MASK		0xfcff	/* PC extended precision(64 bits) */
#define	FPCR_RC_NEAREST		0x0000	/* RC round to nearest */
#define	FPCR_RC_DOWN		0x0400	/* RC round down */
#define	FPCR_RC_UP		0x0800	/* RC round up */
#define	FPCR_RC_ZERO		0x0c00	/* RC round to zero */
#define	FPCR_RC_MASK		0xf3ff	/* RC round bits mask */
#define	FPCR_X			0x1000	/* X infinity control */

/* status register: defines for status word */

#define FPSR_IE			0x0001	/* IE exc-flag invalid operation */
#define FPSR_DE			0x0002	/* DE exc-flag denormalized operand */
#define FPSR_ZE			0x0004	/* ZE exc-flag zero divide */
#define FPSR_OE			0x0008	/* OE exc-flag overflow */
#define FPSR_UE			0x0010	/* UE exc-flag underflow */
#define FPSR_PE			0x0020	/* PE exc-flag precision */
#define FPSR_SF			0x0040	/* SF stack fault */
#define FPSR_ES			0x0080	/* ES error summary status */
#define FPSR_C0			0x0100	/* C0 condition code */
#define FPSR_C1			0x0200	/* C1 condition code */
#define FPSR_C2			0x0400	/* C2 condition code */
#define FPSR_TOP		0x3800	/* TOP top of stack pointer */
#define FPSR_C3			0x4000	/* C3 condition code */
#define FPSR_B			0x8000	/* FPU busy */

/* number of FP/MM and XMM registers on coprocessor */

#define	FP_NUM_REGS		8	/* number of FP/MM registers */
#define	XMM_NUM_REGS		16	/* number of XMM registers */
#define	FP_NUM_RESERVED		6	/* reserved area in FPX_CONTEXT */
#define XSAVE_HEADER            64      /* number of bytes for the XSAVE header */

/* maximum size of floating-point coprocessor state frame */

#define FPO_STATE_FRAME_SIZE	108	/* nBytes of FPO_CONTEXT */
#define FPX_STATE_FRAME_SIZE	512	/* nBytes of FPX_CONTEXT */

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

/* FPX_CONTEXT REG_SET - structure offsets for New FP context */

#define	FPXREG_FPCR	0x00	/* offset to FPCR in FPREG_SET */
#define	FPXREG_FPSR	0x02	/* offset to FPSR in FPREG_SET */
#define	FPXREG_FPTAG	0x04	/* offset to FPTAG in FPREG_SET */
#define	FPXREG_OP	0x06	/* offset to OP in FPREG_SET */
#define	FPXREG_IP	0x08	/* offset to IP in FPREG_SET */
#define	FPXREG_CS	0x0c	/* offset to CS in FPREG_SET */
#define	FPXREG_DP	0x10	/* offset to DP in FPREG_SET */
#define	FPXREG_DS	0x14	/* offset to DS in FPREG_SET */
#define	FPXREG_RSVD0    0x18    /* offset to RESERVED0 in FPREG_SET */
#define	FPXREG_RSVD1    0x1c    /* offset to RESERVED1 in FPREG_SET */
#define FPXREG_FPX(n)	(0x20 + (n)*sizeof(DOUBLEX_SSE)) /* offset to FPX(n) */

#ifndef	_ASMLANGUAGE

/* DOUBLEX - double extended precision */

typedef struct
    {
    UCHAR f[10];			/* ST[0-7] or MM[0-7] */
    } DOUBLEX;

/* DOUBLEX_SSE - double extended precision used in FPX_CONTEXT for SSE */

typedef struct
    {
    UCHAR xmm[16];			/* for 128 bits XMM registers */
    } DOUBLEX_SSE;

/* FPREGO_SET - FP register set that is different from FPO_CONTEXT */

typedef struct fpregOSet
    {
    int		fpcr;			/* control word */
    int		fpsr;			/* status word */
    int		fptag;			/* tag word */
    int		op;			/* last FP instruction op code */
    int 	ip;			/* instruction pointer */
    int		cs;			/* instruction pointer selector */
    int 	dp;			/* data pointer */
    int		ds;			/* data pointer selector */
    DOUBLEX	fpx[FP_NUM_REGS];	/* FR[0-7] non-TOS rel. order */
    } FPREGO_SET;

/* FPREGX_SET - FP register set that is corresponding to FPX_CONTEXT */

typedef struct fpregXSet
    {
    int		fpcr;			/* control word */
    int		fpsr;			/* status word */
    int		fptag;			/* tag word */
    int		op;			/* last FP instruction op code */
    int 	ip;			/* instruction pointer */
    int		cs;			/* instruction pointer selector */
    int 	dp;			/* data pointer */
    int		ds;			/* data pointer selector */
    DOUBLEX	fpx[FP_NUM_REGS];	/* FR[0-7] non-TOS rel. order */
    DOUBLEX_SSE	xmm[XMM_NUM_REGS];	/* 16*16 XMM[0-15] */
    } FPREGX_SET;

/* FPREGX_EXT_SET - FP register set that is corresponding to FPX_EXT_CONTEXT */

typedef struct fpregX_ExtSet
    {
    int		fpcr;			/* control word */
    int		fpsr;			/* status word */
    int		fptag;			/* tag word */
    int		op;			/* last FP instruction op code */
    int 	ip;			/* instruction pointer */
    int		cs;			/* instruction pointer selector */
    int 	dp;			/* data pointer */
    int		ds;			/* data pointer selector */
    DOUBLEX	fpx[FP_NUM_REGS];	/* FR[0-7] non-TOS rel. order */
    DOUBLEX_SSE	xmm[XMM_NUM_REGS];	/* 16*16 XMM[0-15] */
    DOUBLEX_SSE     ymm[XMM_NUM_REGS];          /* 16*16 higher 128 bits of YMM[0-15] */
    } FPREGX_EXT_SET;

/* FPREG_SET - Common FP register set */

typedef struct fpregSet
    {
    union n
	{
	FPREGO_SET o;			/* old FPREGO_SET for fsave/frstor */
	FPREGX_SET x;			/* new FPREGX_SET for fxsave/fxrstor */
	FPREGX_EXT_SET  x_ext;         /* FPREGX_EXT_SET for xsave/xrstor  */ 
	} n;
    } FPREG_SET;

/* FPO_CONTEXT - Old FP context used by fsave/frstor instruction */

typedef struct fpOcontext
    {
    int		fpcr;			/* 4    control word */
    int		fpsr;			/* 4    status word */
    int		fptag;			/* 4    tag word */
    int 	ip;			/* 4    instruction pointer */
    short	cs;			/* 2    instruction pointer selector */
    short	op;			/* 2    last FP instruction op code */
    int 	dp;			/* 4    data pointer */
    int		ds;			/* 4    data pointer selector */
    DOUBLEX	fpx[FP_NUM_REGS];	/* 8*10 FR[0-7] non-TOS rel. order */
    } FPO_CONTEXT;			/* 108  bytes total */

/* FPX_CONTEXT - New FP context used by fxsave/fxrstor instruction */

typedef struct fpXcontext
    {
    short	fpcr;			/* 2     control word */
    short	fpsr;			/* 2     status word */
    short	fptag;			/* 2     tag word */
    short	op;			/* 2     last FP instruction op code */
    int 	ip;			/* 4     instruction pointer */
    int		cs;			/* 4     instruction pointer selector */
    int 	dp;			/* 4     data pointer */
    int		ds;			/* 4     data pointer selector */
    int		reserved0;		/* 4     reserved */
    int		reserved1;		/* 4     reserved */
    DOUBLEX_SSE	fpx[FP_NUM_REGS];	/* 8*16  FR[0-7] non-TOS rel. order */
    DOUBLEX_SSE	xmm[XMM_NUM_REGS];	/* 16*16 XMM[0-15] */
    DOUBLEX_SSE	res2[FP_NUM_RESERVED];	/* 8*16  reserved */
    } FPX_CONTEXT;			/* 512   bytes total */


/* FPX_EXT_CONTEXT - Extended FP context used by xsave/xrstor instruction */

typedef struct fpX_ExtContext
    {
    short	    fpcr;			/* 2     control word */
    short	    fpsr;			/* 2     status word */
    short	    fptag;			/* 2     tag word */
    short	    op;			        /* 2     last FP instruction op code */
    int		    ip;			        /* 4     instruction pointer */
    int		    cs;			        /* 4     instruction pointer selector */
    int		    dp;			        /* 4     data pointer */
    int		    ds;			        /* 4     data pointer selector */
    int		    reserved0;		        /* 4     reserved */
    int		    reserved1;		        /* 4     reserved */
    DOUBLEX_SSE	    fpx[FP_NUM_REGS];	        /* 8*16  FR[0-7] non-TOS rel. order */
    DOUBLEX_SSE	    xmm[XMM_NUM_REGS];	        /* 16*16 XMM[0-15] */
    DOUBLEX_SSE	    res2[FP_NUM_RESERVED];	/* 6*16  reserved */
    UCHAR           xSaveHeader[XSAVE_HEADER];  /* 64    XSave header */   
    DOUBLEX_SSE     ymm[XMM_NUM_REGS];          /* 16*16 higher 128 bits of YMM[0-15] */
    } FPX_EXT_CONTEXT;			        /* 832   bytes total */


/* FP_CONTEXT - Common FP context */

typedef struct fpContext
    {
    union u
	{
	FPO_CONTEXT o;			/* old FPO_CONTEXT for fsave/frstor */
	FPX_CONTEXT x;			/* new FPX_CONTEXT for fxsave/fxrstor */
	FPX_EXT_CONTEXT  x_ext;         /* FPX_EXT_CONTEXT for xsave/xrstor  */ 
	} u;
    } FP_CONTEXT;

/* variable declarations */

extern REG_INDEX   fpRegName[];		/* f-point data register table */
extern REG_INDEX   fpXregName[];	/* f-point data register table for FPX and FPX_EXT */
extern REG_INDEX   fpCtlRegName[];	/* f-point control register table */
extern REG_INDEX   fpXctlRegName[];	/* new f-point control register table */
extern WIND_TCB    *pFppTaskIdPrevious;	/* task id for deferred exceptions */

#if !defined (_WRS_PAL_COPROC_LIB)
extern FUNCPTR	   fppCreateHookRtn;	/* arch dependent create hook routine */
#endif  /* !_WRS_PAL_COPROC_LIB */

/* func ptr to fppSave/fppXsave */

extern void (* _func_fppSaveRtn) (FP_CONTEXT *);

/* func ptr to fppRestore/fppXrestore */

extern void (* _func_fppRestoreRtn) (FP_CONTEXT *);

/* function declarations */

#if defined(__STDC__) || defined(__cplusplus)

extern  void    fppArchCpuInit(void);
extern	void	fppArchInit (void);
extern	void	fppArchTaskCreateInit (FP_CONTEXT *pFpContext);
extern	STATUS  fppProbeSup (void);
extern	void	fppProbeTrap (void);
extern	void	fppDtoDx (DOUBLEX *pDx, double *pDouble);
extern	void	fppDxtoD (double *pDouble, DOUBLEX *pDx);
extern	void	fppXrestore (FP_CONTEXT *pFpContext);
extern	void 	fppXsave (FP_CONTEXT *pFpContext);
extern	void	fppXregsToCtx (FPREG_SET *pFpRegSet, FP_CONTEXT *pFpContext);
extern	void	fppExtXregsToCtx (FPREG_SET *pFpRegSet, FP_CONTEXT *pFpContext);
extern	void	fppXctxToRegs (FP_CONTEXT *pFpContext, FPREG_SET *pFpRegSet);
extern	void	fppExtXctxToRegs (FP_CONTEXT *pFpContext, FPREG_SET *pFpRegSet);
extern	void	fppArchSwitchHook (WIND_TCB * pOldTcb, WIND_TCB * pNewTcb);
extern	STATUS	fppArchSwitchHookEnable (BOOL enable);

#else

extern  void    fppArchCpuInit();
extern	void	fppArchInit ();
extern	void	fppArchTaskCreateInit ();
extern	STATUS	fppProbeSup ();
extern	void	fppProbeTrap ();
extern	void	fppDtoDx ();
extern	void	fppDxtoD ();
extern	void	fppXrestore ();
extern	void 	fppXsave ();
extern	void	fppXregsToCtx ();
extern	void	fppExtXregsToCtx ();
extern	void	fppXctxToRegs ();
extern	void	fppExtXctxToRegs ();
extern	void	fppArchSwitchHook ();
extern	STATUS	fppArchSwitchHookEnable ();

#endif	/* __STDC__ */

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCfppX86_64Libh */

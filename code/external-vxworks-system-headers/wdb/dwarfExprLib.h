/* dwarfExprLib.h - dwarf expressions evaluator */

/* 
 * Copyright (c) 2008-2010 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
01i,24feb10,rlp  Added the DWARF_ERR_STACK_TOO_SMALL error code.
01h,16sep09,bpn  Added comments. Reviewed piece type management.
01g,18jun09,bpn  Fixed build error on solaris host.
01f,11jun09,bpn  Fixed piece max size definition.
01e,28may09,bpn  Added support of pieces. Added new errors.
01d,07may08,bpn  Moved type defines from dwarExprLib.c.
01c,18apr07,dbt  Updated APIs + cleanup
01b,02apr08,bpn  Fixed target and host build.
           +cad
01a,16jan08,tbu  created
*/

#ifndef __INCdwarfExprLibh
#define __INCdwarfExprLibh

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* defines */

/* dwarf program header offsets */

#define	DWARF_HDR_PROG_VERSION	0	/* program version */
#define	DWARF_HDR_PROG_ENDIAN	1	/* program endianness (1 = BE) */
#define	DWARF_HDR_PROG_HDR_SIZE	2	/* progam header size */
#define DWARF_HDR_PROG_PTR_SIZE	3	/* pointer size */
#define	DWARF_HDR_PROG_SIZE_HI	4	/* high order byte of program size */
#define	DWARF_HDR_PROG_SIZE_LO	5	/* low order byte of program size */

/* dwarf types */

#define	DWARF_U_CHAR_TYPE		unsigned char
#define	DWARF_U_SHORT_TYPE		unsigned short
#define	DWARF_U_INT_TYPE		unsigned int
#define	DWARF_U_LONG_TYPE		unsigned long
#ifdef WIN32
#define DWARF_U_LLONG_TYPE		unsigned __int64
#else	/* !WIN32 */
#define	DWARF_U_LLONG_TYPE		unsigned long long
#endif	/*  WIN32 */
#define	DWARF_U_FLOAT_TYPE		float
#define	DWARF_U_DOUBLE_TYPE		double

#define	DWARF_S_CHAR_TYPE		char
#define	DWARF_S_SHORT_TYPE		short
#define	DWARF_S_INT_TYPE		int
#define	DWARF_S_LONG_TYPE		long
#ifdef WIN32
#define DWARF_S_LLONG_TYPE		__int64
#else	/* !WIN32 */
#define	DWARF_S_LLONG_TYPE		long long
#endif
#define	DWARF_S_FLOAT_TYPE		float
#define	DWARF_S_DOUBLE_TYPE		double

#ifndef DWARF_PIECE_MAX_SIZE	/* Max size of a reconstructed piece value */
#define DWARF_PIECE_MAX_SIZE		(sizeof (DWARF_U_LLONG_TYPE))
#endif

#ifndef DWARF_BYTE_ORDER
/*
 * Define the byte order of the machine that runs the evaluator. We can't use
 * _BYTE_ORDER, _BIG_ENDIAN and _LITTLE_ENDIAN directly because SPARC machine 
 * defines differently _BIG_ENDIAN and _LITTLE_ENDIAN macros, without a value.
 * So use a specific way to specify byte ordering for internal use of the
 * DWARF evaluator
 */
#define DWARF_BYTE_ORDER	_BYTE_ORDER
#define DWARF_BIG_ENDIAN	_BIG_ENDIAN
#define DWARF_LITTLE_ENDIAN	_LITTLE_ENDIAN
#endif

/* dwarf element types */

typedef enum
    {
    DWARF_UNKNOWN_VAL	= 0,
    DWARF_CHAR_VAL	= 1,
    DWARF_SHORT_VAL	= 2,
    DWARF_INT_VAL	= 3,
    DWARF_LONG_VAL	= 4,
    DWARF_LLONG_VAL	= 5,
    DWARF_FLOAT_VAL 	= 6,
    DWARF_DOUBLE_VAL	= 7,
    DWARF_PIECE_VAL	= 8
    } DWARF_ELT_TYPE;

/* dwarf evaluator status values */

typedef enum dwarf_status
    {
    DWARF_OK				= 0,	/* OK status */
    DWARF_ERR_INVALID_PARAMS		= 1,	/* params invalid */
    DWARF_ERR_INVALID_MEM_ACCESS	= 2,	/* memory fault */
    DWARF_ERR_INVALID_CTX		= 3,	/* bad context */
    DWARF_ERR_INVALID_REG		= 4,	/* invalid register */
    DWARF_ERR_INVALID_OPCODE		= 5,	/* invalid opcode */
    DWARF_ERR_TLS_NOT_SUPPORTED		= 6,	/* no TLS support */
    DWARF_ERR_INVALID_PROG		= 7,	/* invalid dwarf program */
    DWARF_ERR_UNSUPPORTED_PIECE_SIZE	= 8,	/* generated piece value size */
						/* is not supported */
    DWARF_ERR_PIECE_SIZE_TO_BIG		= 9,	/* piece value size if greater */
						/* than piece buffer size */
    DWARF_ERR_STACK_TOO_SMALL		= 10	/* DWARF stack too small */
    } DWARF_STATUS;

/* an element of the stack */

typedef struct 			/* dwarf element */
    {
    DWARF_ELT_TYPE	type;		/* element type */
    BOOL	   	signedVal;	/* TRUE=signed, FALSE=unsigned */
    UINT32		pieceBitSize;	/* current piece bit size */
    union 
    	{
	DWARF_S_CHAR_TYPE	charVal;
	DWARF_U_CHAR_TYPE	u_charVal;
	DWARF_S_SHORT_TYPE	shortVal;
	DWARF_U_SHORT_TYPE	u_shortVal;
	DWARF_S_INT_TYPE	intVal;
	DWARF_U_INT_TYPE	u_intVal;
	DWARF_S_LONG_TYPE	longVal;
	DWARF_U_LONG_TYPE	u_longVal;
	DWARF_S_LLONG_TYPE	llongVal;
	DWARF_U_LLONG_TYPE	u_llongVal;
#ifdef	DWARF_FLOAT_SUPPORT
	DWARF_S_FLOAT_TYPE	floatVal;
	DWARF_S_DOUBLE_TYPE	doubleVal;
#endif	/* DWARF_FLOAT_SUPPORT */
	DWARF_U_CHAR_TYPE	pieceVal[DWARF_PIECE_MAX_SIZE];
	} val;			/* element value */
    } DWARF_ELT;

/* extern declarations */

extern DWARF_STATUS	dwarfExprEval (const void * dwarfProg,
				void * ctxId, void * pRegs,
				BOOL dryRun, int * pExitVal,
				DWARF_ELT * pValue);
extern DWARF_STATUS	dwarfExprOpSearch (const void * dwarfProg,
				UCHAR opcode, char * pattern,
				size_t patternSize, void ** pPos);
extern UINT32		dwarfExprSizeGet (DWARF_ELT * pElement);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INCdwarfExprLibh */

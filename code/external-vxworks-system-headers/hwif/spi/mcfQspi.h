/* mcfQspi.h - coldfire Queued SPI device header */

/*
 * Copyright 2007,2008 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01b,06feb08,rec  change CAST_M5208 macros to more generic type
01a,14dec07,rec	 created
*/

#ifndef __INCmcfQspih
#define __INCmcfQspih


/* register offsets */

#define MCF_QSPI_QMR_OFF    0x00
#define MCF_QSPI_QDLYR_OFF  0x04
#define MCF_QSPI_QWR_OFF    0x08
#define MCF_QSPI_QIR_OFF    0x0C
#define MCF_QSPI_QAR_OFF    0x10
#define MCF_QSPI_QDR_OFF    0x14

/* Register read/write macros */

#define MCF_QSPI_QMR	   (CAST_MCF_VOLPTR( UINT16 )(MCF_QSPI_BASE + \
                                        MCF_QSPI_QMR_OFF))
#define MCF_QSPI_QDLYR	   (CAST_MCF_VOLPTR( UINT16 )(MCF_QSPI_BASE + \
                                        MCF_QSPI_QDLYR_OFF))
#define MCF_QSPI_QWR	   (CAST_MCF_VOLPTR( UINT16 )(MCF_QSPI_BASE + \
                                        MCF_QSPI_QWR_OFF))
#define MCF_QSPI_QIR	   (CAST_MCF_VOLPTR( UINT16 )(MCF_QSPI_BASE + \
                                        MCF_QSPI_QIR_OFF))
#define MCF_QSPI_QAR	   (CAST_MCF_VOLPTR( UINT16 )(MCF_QSPI_BASE + \
                                        MCF_QSPI_QAR_OFF))
#define MCF_QSPI_QDR	   (CAST_MCF_VOLPTR( UINT16 )(MCF_QSPI_BASE + \
                                        MCF_QSPI_QDR_OFF))

/* Bit definitions and macros for MCF_QSPI_QMR */
#define MCF_QSPI_QMR_BAUD(x)	 (((x)&0x00FF)<<0)
#define MCF_QSPI_QMR_CPHA	 (0x0100)
#define MCF_QSPI_QMR_CPOL	 (0x0200)
#define MCF_QSPI_QMR_BITS(x)	 (((x)&0x000F)<<10)
#define MCF_QSPI_QMR_DOHIE	 (0x4000)
#define MCF_QSPI_QMR_MSTR	 (0x8000)

/* Bit definitions and macros for MCF_QSPI_QDLYR */
#define MCF_QSPI_QDLYR_DTL(x)	 (((x)&0x00FF)<<0)
#define MCF_QSPI_QDLYR_QCD(x)	 (((x)&0x007F)<<8)
#define MCF_QSPI_QDLYR_SPE	 (0x8000)

/* Bit definitions and macros for MCF_QSPI_QWR */
#define MCF_QSPI_QWR_NEWQP(x)	 (((x)&0x000F)<<0)
#define MCF_QSPI_QWR_ENDQP(x)	 (((x)&0x000F)<<8)
#define MCF_QSPI_QWR_CSIV	 (0x1000)
#define MCF_QSPI_QWR_WRTO	 (0x2000)
#define MCF_QSPI_QWR_WREN	 (0x4000)
#define MCF_QSPI_QWR_HALT	 (0x8000)

/* Bit definitions and macros for MCF_QSPI_QIR */
#define MCF_QSPI_QIR_SPIF	 (0x0001)
#define MCF_QSPI_QIR_ABRT	 (0x0004)
#define MCF_QSPI_QIR_WCEF	 (0x0008)
#define MCF_QSPI_QIR_SPIFE	 (0x0100)
#define MCF_QSPI_QIR_ABRTE	 (0x0400)
#define MCF_QSPI_QIR_WCEFE	 (0x0800)
#define MCF_QSPI_QIR_ABRTL	 (0x1000)
#define MCF_QSPI_QIR_ABRTB	 (0x4000)
#define MCF_QSPI_QIR_WCEFB	 (0x8000)

/* Bit definitions and macros for MCF_QSPI_QAR */
#define MCF_QSPI_QAR_ADDR(x)	 (((x)&0x003F)<<0)
#define MCF_QSPI_QAR_TRANS	 (0x0000)
#define MCF_QSPI_QAR_RECV	 (0x0010)
#define MCF_QSPI_QAR_CMD	 (0x0020)

/* Bit definitions and macros for MCF_QSPI_QDR */
#define MCF_QSPI_QDR_DATA(x)	 (((x)&0xFFFF)<<0)
#define MCF_QSPI_QDR_CONT	 (0x8000)
#define MCF_QSPI_QDR_BITSE	 (0x4000)
#define MCF_QSPI_QDR_DT	 (0x2000)
#define MCF_QSPI_QDR_DSCK	 (0x1000)
#define MCF_QSPI_QDR_QSPI_CS3	 (0x0800)
#define MCF_QSPI_QDR_QSPI_CS2	 (0x0400)
#define MCF_QSPI_QDR_QSPI_CS1	 (0x0200)
#define MCF_QSPI_QDR_QSPI_CS0	 (0x0100)



#endif


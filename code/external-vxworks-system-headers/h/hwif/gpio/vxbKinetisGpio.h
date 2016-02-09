/* vxbKinetisGpio.h - interrupt controller for freescale Kinetis */

/*
 * Copyright (c) 2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01a,17aug13,yjw   created
*/

#ifndef	__INCvxbKinetisGpioh
#define	__INCvxbKinetisGpioh

#ifdef __cplusplus
extern "C" {
#endif

#define BITBAND_ALIAS_ADDRESS(addr, bit) \
     ((((UINT32)(addr) & 0xF0000000) + 0x02000000) \
	 +((((UINT32)(addr)&0xFFFFF)<<5) \
	 +((UINT32)(bit)<<2)))
	 
#define PCR_READ_4(pCtrl, addr)                                \
    vxbRead32 ((pCtrl->pcrHandle),                             \
               (UINT32 *)((char *)(pCtrl->pInst->pRegBase[0]) + (addr)))

#define PCR_WRITE_4(pCtrl, addr, data)                         \
    vxbWrite32 ((pCtrl->pcrHandle),                            \
                (UINT32 *)((char *)(pCtrl->pInst->pRegBase[0]) + (addr)), data)
				
#define GPIO_READ_4(pCtrl, addr)                                \
    vxbRead32 ((pCtrl->gpioHandle),                             \
               (UINT32 *)((char *)(pCtrl->pInst->pRegBase[1]) + (addr)))

#define GPIO_WRITE_4(pCtrl, addr, data)                         \
    vxbWrite32 ((pCtrl->gpioHandle),                            \
                (UINT32 *)((char *)(pCtrl->pInst->pRegBase[1]) + (addr)), data)
				
#define KINETIS_GPIO_BANK_WIDTH  32

#define PORT_PCR            0x00
#define PORT_GPCLR          0x80
#define PORT_GPCHR          0x84
#define PORT_ISFR           0xa0
#define PORT_DFER           0xc0
#define PORT_DFCR           0xc4
#define PORT_DFWR           0xc8

#define PCR_IRQC_MASK       0x000f0000
#define PCR_MUX_MASK        0x00000700
#define PCR_PULL_MASK       0x00000003

#define KINETIS_GPIO_INPUT               0x0
#define KINETIS_GPIO_OUTPUT              0x1

#define KINETIS_GPIO_PULL_DISABLE        0x0
#define KINETIS_GPIO_PULL_DOWN           0x2
#define KINETIS_GPIO_PULL_UP             0x3

#define KINETIS_GPIO_INT_DMA_DISABLE     0x0
#define KINETIS_GPIO_DMA_RISING          0x1
#define KINETIS_GPIO_DMA_FAILING         0x2
#define KINETIS_GPIO_DMA_EITHER          0x3
#define KINETIS_GPIO_INT_LEVEL_LOW       0x8
#define KINETIS_GPIO_INT_RISING          0x9
#define KINETIS_GPIO_INT_FAILING         0xa
#define KINETIS_GPIO_INT_EITHER          0xb
#define KINETIS_GPIO_INT_LEVEL_HIGH      0xc

#define PDOR_ALIAS_OFFSET   0
#define PSOR_ALIAS_OFFSET   (0x04 << 5)
#define PCOR_ALIAS_OFFSET   (0x08 << 5)
#define PTOR_ALIAS_OFFSET   (0x0c << 5)
#define PDIR_ALIAS_OFFSET   (0x10 << 5)
#define PDDR_ALIAS_OFFSET   (0x14 << 5)

/* Private context structure */

typedef struct kinetisIsrEntry 
    {
    VOIDFUNCPTR     pIsr;       /* ISR */
    void *          pArg;        /* parameter */
    } KINETIS_ISR_ENTRY;

typedef struct kinetisGpioDrvCtrl
    {
    VXB_DEVICE_ID           pInst;       /* pointer to the controller instance */
    UINT32                  validBmp;  /* this is a valid bitmap for this controller.
                                            bit 0 means free, 1 means used. */
    void *                  pcrHandle;      /* handle of PCR vxbRead/vxbWrite */
	void *                  gpioHandle;      /* handle of GPIO vxbRead/vxbWrite */
	KINETIS_ISR_ENTRY       isrTable[KINETIS_GPIO_BANK_WIDTH];         /* ISR handler table */
	
    /* allocate a pin. */
    STATUS (*gpioAlloc) 
        (
        VXB_DEVICE_ID pDev, 
        UINT32 pin                   
        );
    /* release a pin */
	STATUS (*gpioRelease)  
        (
        VXB_DEVICE_ID pDev, 
        UINT32 pin                   
        );	
    /* get input value of a pin */
	UINT32 (*gpioInput)
        (
        VXB_DEVICE_ID pDev, 
        UINT32 pin
        );
    /* output value to a pin */
	STATUS (*gpioOutput)
        (
        VXB_DEVICE_ID pDev, 
        UINT32 pin,
        UINT32 value
        );
    /* config Gpio pin */
    STATUS (*gpioConfig)
        (
        VXB_DEVICE_ID pDev, 
        UINT32 pin,
        UINT32 trigger,  /* trigger mode */
		UINT32 pull,     /* internal pull down or up */
		UINT32 dir       /* input or output */
		);
    /* set ISR for a pin */
	STATUS (*gpioISRSet)
        (
        VXB_DEVICE_ID pDev, 
        UINT32          pin,
        VOIDFUNCPTR     pIsr,       /* ISR */
        void *          pArg        /* parameter */
        );
    } KINETIS_GPIO_DRVCTRL;			

#ifdef __cplusplus
}
#endif

#endif	/* __INCvxbKinetisGpioh */

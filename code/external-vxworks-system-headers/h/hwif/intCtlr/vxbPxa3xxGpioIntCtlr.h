/* vxbPxa3xxGpioIntCtlr.h - Gpio interrupt controller for PXA3XX */

/*
 * Copyright (c) 2009 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01a,03mar09,d_l  created.
*/

#ifndef __INCvxbPxa3xxGpioIntCtlrh
#define __INCvxbPxa3xxGpioIntCtlrh

#include <vxWorks.h>
#include <vxBusLib.h>
#include <hwif/vxbus/vxBus.h>

/* defines */

#define GPIO_EDGE_NONE              0
#define GPIO_EDGE_RISE              1
#define GPIO_EDGE_FALL              2
#define GPIO_EDGE_BOTH              3

#define GPIO_DIR_IN                 0
#define GPIO_DIR_OUT                1

#define GPIO_LEVEL_LOW              0
#define GPIO_LEVEL_HIGH             1

#define GPIO_NORMAL                 0
#define GPIO_INTERRUPT              1

/* default definitions */

#ifndef GPIO_BIT
#   define GPIO_BIT(_bitNumber)     (1 << (_bitNumber))
#endif /* GPIO_BIT */

#ifndef PXA3XX_GPIO_BASE
#   define PXA3XX_GPIO_BASE         (PXA3XX_PERIPHERAL_BASE + 0x00E00000)
#endif /* PXA3XX_GPIO_BASE */

#define PXA3XX_GPIO_REG_COUNT       3
#define BULVERDE_GPIO_REG_COUNT     4
#define PXA3XX_GPIO_PIN_MAX         80
#define BULVERDE_GPIO_PIN_MAX       120
#define PXA3XX_GPIO_PIN_MIN         0
#define BULVERDE_GPIO_PIN_MIN       PXA3XX_GPIO_PIN_MIN
#define PXA3XX_GPIO_INT_NUM         78      /* number of gpio interrupts */
#define GPIO_INT_LEVEL_MIN          0
#define GPIO_INT_LEVEL_MAX          (BULVERDE_GPIO_PIN_MAX - 2)
#define PXA3XX_GPIO_INT_2TO80       78      /* number of 2nd lvl gpio interrupts */
#define PXA3XX_GPIO_INT_80          PXA3XX_GPIO_PIN_MAX
#define BULVERDE_GPIO_INT_120       BULVERDE_GPIO_PIN_MAX
#define PXA3XX_GPIO_INT_2           2
#define PXA3XX_GPIO_INT_1           1
#define BULVERDE_GPIO_INT_1         1
#define PXA3XX_GPIO_INT_2TO80MASK   0x0ffff800

/* GPIO pin level register */

#define PXA3XX_GPIO_GPLR_HI         1       /* pin level high */
#define PXA3XX_GPIO_GPLR_LO         0       /* pin level low */

/* GPIO pin Direction  register */

#define PXA3XX_GPIO_GPDR_OUT        1       /* pin direction as output */
#define PXA3XX_GPIO_GPDR_IN         0       /* pin direction as input */

/* GPIO pin output set register */

#define PXA3XX_GPIO_GPSR_SET        1       /* set pin level to high */

/* GPIO pin output clear register */

#define PXA3XX_GPIO_GPCR_SET        1       /* clear pin level to zero */

/* GPIO pin rising edge register */

#define PXA3XX_GPIO_GRER_RISING     1       /* set gpio to rising edge */

/* GPIO pin falling edge register */

#define PXA3XX_GPIO_GFER_FALLING    1       /* set gpio to falling edge */

#define PXA3XX_GPIO_INT_RISING      0x01    /* software GPIO_BIT flag */
#define PXA3XX_GPIO_INT_FALLING     0x02    /* software GPIO_BIT flag */

/* GPIO pin edge detect register */

#define PXA3XX_GPIO_GEDR_DETECT     1       /* edge detect has occured */
#define PXA3XX_GPIO_GEDR_RESET      0x0fffffff

/* registers definition */

/* General Purpose I/O Registers */

#define PXA3XX_GPIO_GPLR            0x40E00000  /* GPIO Pin Level (31-0) */
#define PXA3XX_GPIO_GPLR_x          0x40E00000  /* GPIO Pin Level (31-0) */
#define PXA3XX_GPIO_GPLR_y          0x40E00004  /* GPIO Pin Level (63-32) */
#define PXA3XX_GPIO_GPLR_z          0x40E00008  /* GPIO Pin Level (84-64) */
#define PXA3XX_GPIO_GPDR            0x40E0000C  /* GPIO Pin Direction (31-0) */
#define PXA3XX_GPIO_GPDR_x          0x40E0000C  /* GPIO Pin Direction (31-0) */
#define PXA3XX_GPIO_GPDR_y          0x40E00010  /* GPIO Pin Direction (63-32) */
#define PXA3XX_GPIO_GPDR_z          0x40E00014  /* GPIO Pin Direction (84-64) */
#define PXA3XX_GPIO_GPSR            0x40E00018  /* GPIO Output Set (31-0) */
#define PXA3XX_GPIO_GPSR_x          0x40E00018  /* GPIO Output Set (31-0) */
#define PXA3XX_GPIO_GPSR_y          0x40E0001C  /* GPIO Output Set (63-32) */
#define PXA3XX_GPIO_GPSR_z          0x40E00020  /* GPIO Output Set (84-64) */
#define PXA3XX_GPIO_GPCR            0x40E00024  /* GPIO Output Clear (31-0) */
#define PXA3XX_GPIO_GPCR_x          0x40E00024  /* GPIO Output Clear (31-0) */
#define PXA3XX_GPIO_GPCR_y          0x40E00028  /* GPIO Output Clear (63-32) */
#define PXA3XX_GPIO_GPCR_z          0x40E0002C  /* GPIO Output Clear (84-64) */
#define PXA3XX_GPIO_GRER            0x40E00030  /* GPIO Rising Edge Detect Enable (31-0) */
#define PXA3XX_GPIO_GRER_x          0x40E00030  /* GPIO Rising Edge Detect Enable (31-0) */
#define PXA3XX_GPIO_GRER_y          0x40E00034  /* GPIO Rising Edge Detect Enable (63-32) */
#define PXA3XX_GPIO_GRER_z          0x40E00038  /* GPIO Rising Edge Detect Enable (84-64) */
#define PXA3XX_GPIO_GFER            0x40E0003C  /* GPIO Falling Edge Detect Enable (31-0) */
#define PXA3XX_GPIO_GFER_x          0x40E0003C  /* GPIO Falling Edge Detect Enable (31-0) */
#define PXA3XX_GPIO_GFER_y          0x40E00040  /* GPIO Falling Edge Detect Enable (63-32) */
#define PXA3XX_GPIO_GFER_z          0x40E00044  /* GPIO Falling Edge Detect Enable (84-64) */
#define PXA3XX_GPIO_GEDR            0x40E00048  /* GPIO Edge Detect Status (31-0) */
#define PXA3XX_GPIO_GEDR_x          0x40E00048  /* GPIO Edge Detect Status (31-0) */
#define PXA3XX_GPIO_GEDR_y          0x40E0004C  /* GPIO Edge Detect Status (63-32) */
#define PXA3XX_GPIO_GEDR_z          0x40E00050  /* GPIO Edge Detect Status (84-64) */
#define PXA3XX_GPIO_GAFR0_x         0x40E00054  /* GPIO Alternate Function Select (31-0) */
#define PXA3XX_GPIO_GAFR1_x         0x40E00058  /* GPIO Alternate Function Select (31-0) */
#define PXA3XX_GPIO_GAFR0_y         0x40E0005C  /* GPIO Alternate Function Select (63-32) */
#define PXA3XX_GPIO_GAFR1_y         0x40E00060  /* GPIO Alternate Function Select (63-32) */
#define PXA3XX_GPIO_GAFR0_z         0x40E00064  /* GPIO Alternate Function Select (84-64) */
#define PXA3XX_GPIO_GAFR1_z         0x40E00068  /* GPIO Alternate Function Select (84-64) */

/* Index */

#define PXA3XX_GPIO_GPLR_x_IDX      0x00000000  /* GPIO Pin Level (31-0) */
#define PXA3XX_GPIO_GPLR_y_IDX      0x00000004  /* GPIO Pin Level (63-32) */
#define PXA3XX_GPIO_GPLR_z_IDX      0x00000008  /* GPIO Pin Level (95-64) */
#define PXA3XX_GPIO_GPDR_x_IDX      0x0000000C  /* GPIO Pin Direction (31-0) */
#define PXA3XX_GPIO_GPDR_y_IDX      0x00000010  /* GPIO Pin Direction (63-32) */
#define PXA3XX_GPIO_GPDR_z_IDX      0x00000014  /* GPIO Pin Direction (95-64) */
#define PXA3XX_GPIO_GPDR_3_IDX      0x0000010C  /* GPIO Pin Direction (127-96) */
#define PXA3XX_GPIO_GPSR_x_IDX      0x00000018  /* GPIO Output Set (31-0) */
#define PXA3XX_GPIO_GPSR_y_IDX      0x0000001C  /* GPIO Output Set (63-32) */
#define PXA3XX_GPIO_GPSR_z_IDX      0x00000020  /* GPIO Output Set (95-64) */
#define PXA3XX_GPIO_GPSR_3_IDX      0x00000118  /* GPIO Output Set (127-96) */
#define PXA3XX_GPIO_GPCR_x_IDX      0x00000024  /* GPIO Output Clear (31-0) */
#define PXA3XX_GPIO_GPCR_y_IDX      0x00000028  /* GPIO Output Clear (63-32) */
#define PXA3XX_GPIO_GPCR_z_IDX      0x0000002C  /* GPIO Output Clear (95-64) */
#define PXA3XX_GPIO_GPCR_3_IDX      0x00000124  /* GPIO Output Clear (127-96) */
#define PXA3XX_GPIO_GRER_x_IDX      0x00000030  /* GPIO Rising Edge Detect Enable (31-0) */
#define PXA3XX_GPIO_GRER_y_IDX      0x00000034  /* GPIO Rising Edge Detect Enable (63-32) */
#define PXA3XX_GPIO_GRER_z_IDX      0x00000038  /* GPIO Rising Edge Detect Enable (95-64) */
#define PXA3XX_GPIO_GRER_3_IDX      0x00000130  /* GPIO Rising Edge Detect Enable (127-96) */
#define PXA3XX_GPIO_GFER_x_IDX      0x0000003C  /* GPIO Falling Edge Detect Enable (31-0) */
#define PXA3XX_GPIO_GFER_y_IDX      0x00000040  /* GPIO Falling Edge Detect Enable (63-32) */
#define PXA3XX_GPIO_GFER_z_IDX      0x00000044  /* GPIO Falling Edge Detect Enable (95-64) */
#define PXA3XX_GPIO_GFER_3_IDX      0x0000013C  /* GPIO Falling Edge Detect Enable (127-96) */
#define PXA3XX_GPIO_GEDR_x_IDX      0x00000048  /* GPIO Edge Detect Status (31-0) */
#define PXA3XX_GPIO_GEDR_y_IDX      0x0000004C  /* GPIO Edge Detect Status (63-32) */
#define PXA3XX_GPIO_GEDR_z_IDX      0x00000050  /* GPIO Edge Detect Status (95-64) */
#define PXA3XX_GPIO_GEDR_3_IDX      0x00000138  /* GPIO Edge Detect Status (127-96) */
#define PXA3XX_GPIO_GAFR0_x_IDX     0x00000054  /* GPIO Alternate Function Select (31-0) */
#define PXA3XX_GPIO_GAFR1_x_IDX     0x00000058  /* GPIO Alternate Function Select (31-0) */
#define PXA3XX_GPIO_GAFR0_y_IDX     0x0000005C  /* GPIO Alternate Function Select (63-32) */
#define PXA3XX_GPIO_GAFR1_y_IDX     0x00000060  /* GPIO Alternate Function Select (63-32) */
#define PXA3XX_GPIO_GAFR0_z_IDX     0x00000064  /* GPIO Alternate Function Select (95-64) */
#define PXA3XX_GPIO_GAFR1_z_IDX     0x00000068  /* GPIO Alternate Function Select (95-64) */
#define PXA3XX_GPIO_GAFR0_3_IDX     0x0000006C  /* GPIO Alternate Function Select (127-96) */
#define PXA3XX_GPIO_GAFR1_3_IDX     0x00000070  /* GPIO Alternate Function Select (127-96) */

typedef struct pxa3xxGpioIntCtlrInput
    {
    int             pin;
    char *          pName;
    char            edge;
    char            dir;
    char            defaultLevel;
    char            usage;
    } PXA3XX_GPIO_INTCTLR_INPUT;

/*
 * PXA3XX GPIO Register Setup Structure
 *
 * Filled in by the bsp in sysLib.c and parsed  by
 * pxa3xxGpioHwInit. It must be NULL terminated.
 */

typedef struct pxa3xxGpioRegInit
    {
    UINT32  regAddr;
    UINT32  regVal;
    } PXA3XX_GPIO_REG_INIT;

#endif  /* __INCvxbPxa3xxGpioIntCtlrh */

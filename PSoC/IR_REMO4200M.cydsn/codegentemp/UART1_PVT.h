/***************************************************************************//**
* \file .h
* \version 4.0
*
* \brief
*  This private file provides constants and parameter values for the
*  SCB Component.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PVT_UART1_H)
#define CY_SCB_PVT_UART1_H

#include "UART1.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define UART1_SetI2CExtClkInterruptMode(interruptMask) UART1_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define UART1_ClearI2CExtClkInterruptSource(interruptMask) UART1_CLEAR_INTR_I2C_EC(interruptMask)
#define UART1_GetI2CExtClkInterruptSource()                (UART1_INTR_I2C_EC_REG)
#define UART1_GetI2CExtClkInterruptMode()                  (UART1_INTR_I2C_EC_MASK_REG)
#define UART1_GetI2CExtClkInterruptSourceMasked()          (UART1_INTR_I2C_EC_MASKED_REG)

#if (!UART1_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define UART1_SetSpiExtClkInterruptMode(interruptMask) \
                                                                UART1_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define UART1_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                UART1_CLEAR_INTR_SPI_EC(interruptMask)
    #define UART1_GetExtSpiClkInterruptSource()                 (UART1_INTR_SPI_EC_REG)
    #define UART1_GetExtSpiClkInterruptMode()                   (UART1_INTR_SPI_EC_MASK_REG)
    #define UART1_GetExtSpiClkInterruptSourceMasked()           (UART1_INTR_SPI_EC_MASKED_REG)
#endif /* (!UART1_CY_SCBIP_V1) */

#if(UART1_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void UART1_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (UART1_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (UART1_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_UART1_CUSTOM_INTR_HANDLER)
    extern cyisraddress UART1_customIntrHandler;
#endif /* !defined (CY_REMOVE_UART1_CUSTOM_INTR_HANDLER) */
#endif /* (UART1_SCB_IRQ_INTERNAL) */

extern UART1_BACKUP_STRUCT UART1_backup;

#if(UART1_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 UART1_scbMode;
    extern uint8 UART1_scbEnableWake;
    extern uint8 UART1_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 UART1_mode;
    extern uint8 UART1_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * UART1_rxBuffer;
    extern uint8   UART1_rxDataBits;
    extern uint32  UART1_rxBufferSize;

    extern volatile uint8 * UART1_txBuffer;
    extern uint8   UART1_txDataBits;
    extern uint32  UART1_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 UART1_numberOfAddr;
    extern uint8 UART1_subAddrSize;
#endif /* (UART1_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (! (UART1_SCB_MODE_I2C_CONST_CFG || \
        UART1_SCB_MODE_EZI2C_CONST_CFG))
    extern uint16 UART1_IntrTxMask;
#endif /* (! (UART1_SCB_MODE_I2C_CONST_CFG || \
              UART1_SCB_MODE_EZI2C_CONST_CFG)) */


/***************************************
*        Conditional Macro
****************************************/

#if(UART1_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define UART1_SCB_MODE_I2C_RUNTM_CFG     (UART1_SCB_MODE_I2C      == UART1_scbMode)
    #define UART1_SCB_MODE_SPI_RUNTM_CFG     (UART1_SCB_MODE_SPI      == UART1_scbMode)
    #define UART1_SCB_MODE_UART_RUNTM_CFG    (UART1_SCB_MODE_UART     == UART1_scbMode)
    #define UART1_SCB_MODE_EZI2C_RUNTM_CFG   (UART1_SCB_MODE_EZI2C    == UART1_scbMode)
    #define UART1_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (UART1_SCB_MODE_UNCONFIG == UART1_scbMode)

    /* Defines wakeup enable */
    #define UART1_SCB_WAKE_ENABLE_CHECK       (0u != UART1_scbEnableWake)
#endif /* (UART1_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!UART1_CY_SCBIP_V1)
    #define UART1_SCB_PINS_NUMBER    (7u)
#else
    #define UART1_SCB_PINS_NUMBER    (2u)
#endif /* (!UART1_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_UART1_H) */


/* [] END OF FILE */

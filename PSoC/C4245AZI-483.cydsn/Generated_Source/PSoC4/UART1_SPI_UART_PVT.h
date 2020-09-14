/***************************************************************************//**
* \file UART1_SPI_UART_PVT.h
* \version 4.0
*
* \brief
*  This private file provides constants and parameter values for the
*  SCB Component in SPI and UART modes.
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

#if !defined(CY_SCB_SPI_UART_PVT_UART1_H)
#define CY_SCB_SPI_UART_PVT_UART1_H

#include "UART1_SPI_UART.h"


/***************************************
*     Internal Global Vars
***************************************/

#if (UART1_INTERNAL_RX_SW_BUFFER_CONST)
    extern volatile uint32  UART1_rxBufferHead;
    extern volatile uint32  UART1_rxBufferTail;
    
    /**
    * \addtogroup group_globals
    * @{
    */
    
    /** Sets when internal software receive buffer overflow
     *  was occurred.
    */  
    extern volatile uint8   UART1_rxBufferOverflow;
    /** @} globals */
#endif /* (UART1_INTERNAL_RX_SW_BUFFER_CONST) */

#if (UART1_INTERNAL_TX_SW_BUFFER_CONST)
    extern volatile uint32  UART1_txBufferHead;
    extern volatile uint32  UART1_txBufferTail;
#endif /* (UART1_INTERNAL_TX_SW_BUFFER_CONST) */

#if (UART1_INTERNAL_RX_SW_BUFFER)
    extern volatile uint8 UART1_rxBufferInternal[UART1_INTERNAL_RX_BUFFER_SIZE];
#endif /* (UART1_INTERNAL_RX_SW_BUFFER) */

#if (UART1_INTERNAL_TX_SW_BUFFER)
    extern volatile uint8 UART1_txBufferInternal[UART1_TX_BUFFER_SIZE];
#endif /* (UART1_INTERNAL_TX_SW_BUFFER) */


/***************************************
*     Private Function Prototypes
***************************************/

void UART1_SpiPostEnable(void);
void UART1_SpiStop(void);

#if (UART1_SCB_MODE_SPI_CONST_CFG)
    void UART1_SpiInit(void);
#endif /* (UART1_SCB_MODE_SPI_CONST_CFG) */

#if (UART1_SPI_WAKE_ENABLE_CONST)
    void UART1_SpiSaveConfig(void);
    void UART1_SpiRestoreConfig(void);
#endif /* (UART1_SPI_WAKE_ENABLE_CONST) */

void UART1_UartPostEnable(void);
void UART1_UartStop(void);

#if (UART1_SCB_MODE_UART_CONST_CFG)
    void UART1_UartInit(void);
#endif /* (UART1_SCB_MODE_UART_CONST_CFG) */

#if (UART1_UART_WAKE_ENABLE_CONST)
    void UART1_UartSaveConfig(void);
    void UART1_UartRestoreConfig(void);
#endif /* (UART1_UART_WAKE_ENABLE_CONST) */


/***************************************
*         UART API Constants
***************************************/

/* UART RX and TX position to be used in UART1_SetPins() */
#define UART1_UART_RX_PIN_ENABLE    (UART1_UART_RX)
#define UART1_UART_TX_PIN_ENABLE    (UART1_UART_TX)

/* UART RTS and CTS position to be used in  UART1_SetPins() */
#define UART1_UART_RTS_PIN_ENABLE    (0x10u)
#define UART1_UART_CTS_PIN_ENABLE    (0x20u)


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Interrupt processing */
#define UART1_SpiUartEnableIntRx(intSourceMask)  UART1_SetRxInterruptMode(intSourceMask)
#define UART1_SpiUartEnableIntTx(intSourceMask)  UART1_SetTxInterruptMode(intSourceMask)
uint32  UART1_SpiUartDisableIntRx(void);
uint32  UART1_SpiUartDisableIntTx(void);


#endif /* (CY_SCB_SPI_UART_PVT_UART1_H) */


/* [] END OF FILE */

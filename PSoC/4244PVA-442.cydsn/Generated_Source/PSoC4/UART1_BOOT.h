/***************************************************************************//**
* \file UART1_BOOT.h
* \version 4.0
*
* \brief
*  This file provides constants and parameter values of the bootloader
*  communication APIs for the SCB Component.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2014-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_BOOT_UART1_H)
#define CY_SCB_BOOT_UART1_H

#include "UART1_PVT.h"

#if (UART1_SCB_MODE_I2C_INC)
    #include "UART1_I2C.h"
#endif /* (UART1_SCB_MODE_I2C_INC) */

#if (UART1_SCB_MODE_EZI2C_INC)
    #include "UART1_EZI2C.h"
#endif /* (UART1_SCB_MODE_EZI2C_INC) */

#if (UART1_SCB_MODE_SPI_INC || UART1_SCB_MODE_UART_INC)
    #include "UART1_SPI_UART.h"
#endif /* (UART1_SCB_MODE_SPI_INC || UART1_SCB_MODE_UART_INC) */


/***************************************
*  Conditional Compilation Parameters
****************************************/

/* Bootloader communication interface enable */
#define UART1_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART1) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

/* Enable I2C bootloader communication */
#if (UART1_SCB_MODE_I2C_INC)
    #define UART1_I2C_BTLDR_COMM_ENABLED     (UART1_BTLDR_COMM_ENABLED && \
                                                            (UART1_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             UART1_I2C_SLAVE_CONST))
#else
     #define UART1_I2C_BTLDR_COMM_ENABLED    (0u)
#endif /* (UART1_SCB_MODE_I2C_INC) */

/* EZI2C does not support bootloader communication. Provide empty APIs */
#if (UART1_SCB_MODE_EZI2C_INC)
    #define UART1_EZI2C_BTLDR_COMM_ENABLED   (UART1_BTLDR_COMM_ENABLED && \
                                                         UART1_SCB_MODE_UNCONFIG_CONST_CFG)
#else
    #define UART1_EZI2C_BTLDR_COMM_ENABLED   (0u)
#endif /* (UART1_EZI2C_BTLDR_COMM_ENABLED) */

/* Enable SPI bootloader communication */
#if (UART1_SCB_MODE_SPI_INC)
    #define UART1_SPI_BTLDR_COMM_ENABLED     (UART1_BTLDR_COMM_ENABLED && \
                                                            (UART1_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             UART1_SPI_SLAVE_CONST))
#else
        #define UART1_SPI_BTLDR_COMM_ENABLED (0u)
#endif /* (UART1_SPI_BTLDR_COMM_ENABLED) */

/* Enable UART bootloader communication */
#if (UART1_SCB_MODE_UART_INC)
       #define UART1_UART_BTLDR_COMM_ENABLED    (UART1_BTLDR_COMM_ENABLED && \
                                                            (UART1_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             (UART1_UART_RX_DIRECTION && \
                                                              UART1_UART_TX_DIRECTION)))
#else
     #define UART1_UART_BTLDR_COMM_ENABLED   (0u)
#endif /* (UART1_UART_BTLDR_COMM_ENABLED) */

/* Enable bootloader communication */
#define UART1_BTLDR_COMM_MODE_ENABLED    (UART1_I2C_BTLDR_COMM_ENABLED   || \
                                                     UART1_SPI_BTLDR_COMM_ENABLED   || \
                                                     UART1_EZI2C_BTLDR_COMM_ENABLED || \
                                                     UART1_UART_BTLDR_COMM_ENABLED)


/***************************************
*        Function Prototypes
***************************************/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (UART1_I2C_BTLDR_COMM_ENABLED)
    /* I2C Bootloader physical layer functions */
    void UART1_I2CCyBtldrCommStart(void);
    void UART1_I2CCyBtldrCommStop (void);
    void UART1_I2CCyBtldrCommReset(void);
    cystatus UART1_I2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus UART1_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map I2C specific bootloader communication APIs to SCB specific APIs */
    #if (UART1_SCB_MODE_I2C_CONST_CFG)
        #define UART1_CyBtldrCommStart   UART1_I2CCyBtldrCommStart
        #define UART1_CyBtldrCommStop    UART1_I2CCyBtldrCommStop
        #define UART1_CyBtldrCommReset   UART1_I2CCyBtldrCommReset
        #define UART1_CyBtldrCommRead    UART1_I2CCyBtldrCommRead
        #define UART1_CyBtldrCommWrite   UART1_I2CCyBtldrCommWrite
    #endif /* (UART1_SCB_MODE_I2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (UART1_I2C_BTLDR_COMM_ENABLED) */


#if defined(CYDEV_BOOTLOADER_IO_COMP) && (UART1_EZI2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void UART1_EzI2CCyBtldrCommStart(void);
    void UART1_EzI2CCyBtldrCommStop (void);
    void UART1_EzI2CCyBtldrCommReset(void);
    cystatus UART1_EzI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus UART1_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map EZI2C specific bootloader communication APIs to SCB specific APIs */
    #if (UART1_SCB_MODE_EZI2C_CONST_CFG)
        #define UART1_CyBtldrCommStart   UART1_EzI2CCyBtldrCommStart
        #define UART1_CyBtldrCommStop    UART1_EzI2CCyBtldrCommStop
        #define UART1_CyBtldrCommReset   UART1_EzI2CCyBtldrCommReset
        #define UART1_CyBtldrCommRead    UART1_EzI2CCyBtldrCommRead
        #define UART1_CyBtldrCommWrite   UART1_EzI2CCyBtldrCommWrite
    #endif /* (UART1_SCB_MODE_EZI2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (UART1_EZI2C_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (UART1_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void UART1_SpiCyBtldrCommStart(void);
    void UART1_SpiCyBtldrCommStop (void);
    void UART1_SpiCyBtldrCommReset(void);
    cystatus UART1_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus UART1_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map SPI specific bootloader communication APIs to SCB specific APIs */
    #if (UART1_SCB_MODE_SPI_CONST_CFG)
        #define UART1_CyBtldrCommStart   UART1_SpiCyBtldrCommStart
        #define UART1_CyBtldrCommStop    UART1_SpiCyBtldrCommStop
        #define UART1_CyBtldrCommReset   UART1_SpiCyBtldrCommReset
        #define UART1_CyBtldrCommRead    UART1_SpiCyBtldrCommRead
        #define UART1_CyBtldrCommWrite   UART1_SpiCyBtldrCommWrite
    #endif /* (UART1_SCB_MODE_SPI_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (UART1_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (UART1_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void UART1_UartCyBtldrCommStart(void);
    void UART1_UartCyBtldrCommStop (void);
    void UART1_UartCyBtldrCommReset(void);
    cystatus UART1_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus UART1_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map UART specific bootloader communication APIs to SCB specific APIs */
    #if (UART1_SCB_MODE_UART_CONST_CFG)
        #define UART1_CyBtldrCommStart   UART1_UartCyBtldrCommStart
        #define UART1_CyBtldrCommStop    UART1_UartCyBtldrCommStop
        #define UART1_CyBtldrCommReset   UART1_UartCyBtldrCommReset
        #define UART1_CyBtldrCommRead    UART1_UartCyBtldrCommRead
        #define UART1_CyBtldrCommWrite   UART1_UartCyBtldrCommWrite
    #endif /* (UART1_SCB_MODE_UART_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (UART1_UART_BTLDR_COMM_ENABLED) */

/**
* \addtogroup group_bootloader
* @{
*/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (UART1_BTLDR_COMM_ENABLED)
    #if (UART1_SCB_MODE_UNCONFIG_CONST_CFG)
        /* Bootloader physical layer functions */
        void UART1_CyBtldrCommStart(void);
        void UART1_CyBtldrCommStop (void);
        void UART1_CyBtldrCommReset(void);
        cystatus UART1_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
        cystatus UART1_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    #endif /* (UART1_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Map SCB specific bootloader communication APIs to common APIs */
    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART1)
        #define CyBtldrCommStart    UART1_CyBtldrCommStart
        #define CyBtldrCommStop     UART1_CyBtldrCommStop
        #define CyBtldrCommReset    UART1_CyBtldrCommReset
        #define CyBtldrCommWrite    UART1_CyBtldrCommWrite
        #define CyBtldrCommRead     UART1_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART1) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (UART1_BTLDR_COMM_ENABLED) */

/** @} group_bootloader */

/***************************************
*           API Constants
***************************************/

/* Timeout unit in milliseconds */
#define UART1_WAIT_1_MS  (1u)

/* Return number of bytes to copy into bootloader buffer */
#define UART1_BYTES_TO_COPY(actBufSize, bufSize) \
                            ( ((uint32)(actBufSize) < (uint32)(bufSize)) ? \
                                ((uint32) (actBufSize)) : ((uint32) (bufSize)) )

/* Size of Read/Write buffers for I2C bootloader  */
#define UART1_I2C_BTLDR_SIZEOF_READ_BUFFER   (64u)
#define UART1_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (64u)

/* Byte to byte time interval: calculated basing on current component
* data rate configuration, can be defined in project if required.
*/
#ifndef UART1_SPI_BYTE_TO_BYTE
    #define UART1_SPI_BYTE_TO_BYTE   (160u)
#endif

/* Byte to byte time interval: calculated basing on current component
* baud rate configuration, can be defined in the project if required.
*/
#ifndef UART1_UART_BYTE_TO_BYTE
    #define UART1_UART_BYTE_TO_BYTE  (193u)
#endif /* UART1_UART_BYTE_TO_BYTE */

#endif /* (CY_SCB_BOOT_UART1_H) */


/* [] END OF FILE */

/***************************************************************************//**
* \file UART1_PINS.h
* \version 4.0
*
* \brief
*  This file provides constants and parameter values for the pin components
*  buried into SCB Component.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PINS_UART1_H)
#define CY_SCB_PINS_UART1_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/

/* Unconfigured pins */
#define UART1_REMOVE_RX_WAKE_SCL_MOSI_PIN  (1u)
#define UART1_REMOVE_RX_SCL_MOSI_PIN      (1u)
#define UART1_REMOVE_TX_SDA_MISO_PIN      (1u)
#define UART1_REMOVE_SCLK_PIN      (1u)
#define UART1_REMOVE_SS0_PIN      (1u)
#define UART1_REMOVE_SS1_PIN                 (1u)
#define UART1_REMOVE_SS2_PIN                 (1u)
#define UART1_REMOVE_SS3_PIN                 (1u)

/* Mode defined pins */
#define UART1_REMOVE_I2C_PINS                (1u)
#define UART1_REMOVE_SPI_MASTER_PINS         (1u)
#define UART1_REMOVE_SPI_MASTER_SCLK_PIN     (1u)
#define UART1_REMOVE_SPI_MASTER_MOSI_PIN     (1u)
#define UART1_REMOVE_SPI_MASTER_MISO_PIN     (1u)
#define UART1_REMOVE_SPI_MASTER_SS0_PIN      (1u)
#define UART1_REMOVE_SPI_MASTER_SS1_PIN      (1u)
#define UART1_REMOVE_SPI_MASTER_SS2_PIN      (1u)
#define UART1_REMOVE_SPI_MASTER_SS3_PIN      (1u)
#define UART1_REMOVE_SPI_SLAVE_PINS          (1u)
#define UART1_REMOVE_SPI_SLAVE_MOSI_PIN      (1u)
#define UART1_REMOVE_SPI_SLAVE_MISO_PIN      (1u)
#define UART1_REMOVE_UART_TX_PIN             (0u)
#define UART1_REMOVE_UART_RX_TX_PIN          (1u)
#define UART1_REMOVE_UART_RX_PIN             (0u)
#define UART1_REMOVE_UART_RX_WAKE_PIN        (1u)
#define UART1_REMOVE_UART_RTS_PIN            (1u)
#define UART1_REMOVE_UART_CTS_PIN            (1u)

/* Unconfigured pins */
#define UART1_RX_WAKE_SCL_MOSI_PIN (0u == UART1_REMOVE_RX_WAKE_SCL_MOSI_PIN)
#define UART1_RX_SCL_MOSI_PIN     (0u == UART1_REMOVE_RX_SCL_MOSI_PIN)
#define UART1_TX_SDA_MISO_PIN     (0u == UART1_REMOVE_TX_SDA_MISO_PIN)
#define UART1_SCLK_PIN     (0u == UART1_REMOVE_SCLK_PIN)
#define UART1_SS0_PIN     (0u == UART1_REMOVE_SS0_PIN)
#define UART1_SS1_PIN                (0u == UART1_REMOVE_SS1_PIN)
#define UART1_SS2_PIN                (0u == UART1_REMOVE_SS2_PIN)
#define UART1_SS3_PIN                (0u == UART1_REMOVE_SS3_PIN)

/* Mode defined pins */
#define UART1_I2C_PINS               (0u == UART1_REMOVE_I2C_PINS)
#define UART1_SPI_MASTER_PINS        (0u == UART1_REMOVE_SPI_MASTER_PINS)
#define UART1_SPI_MASTER_SCLK_PIN    (0u == UART1_REMOVE_SPI_MASTER_SCLK_PIN)
#define UART1_SPI_MASTER_MOSI_PIN    (0u == UART1_REMOVE_SPI_MASTER_MOSI_PIN)
#define UART1_SPI_MASTER_MISO_PIN    (0u == UART1_REMOVE_SPI_MASTER_MISO_PIN)
#define UART1_SPI_MASTER_SS0_PIN     (0u == UART1_REMOVE_SPI_MASTER_SS0_PIN)
#define UART1_SPI_MASTER_SS1_PIN     (0u == UART1_REMOVE_SPI_MASTER_SS1_PIN)
#define UART1_SPI_MASTER_SS2_PIN     (0u == UART1_REMOVE_SPI_MASTER_SS2_PIN)
#define UART1_SPI_MASTER_SS3_PIN     (0u == UART1_REMOVE_SPI_MASTER_SS3_PIN)
#define UART1_SPI_SLAVE_PINS         (0u == UART1_REMOVE_SPI_SLAVE_PINS)
#define UART1_SPI_SLAVE_MOSI_PIN     (0u == UART1_REMOVE_SPI_SLAVE_MOSI_PIN)
#define UART1_SPI_SLAVE_MISO_PIN     (0u == UART1_REMOVE_SPI_SLAVE_MISO_PIN)
#define UART1_UART_TX_PIN            (0u == UART1_REMOVE_UART_TX_PIN)
#define UART1_UART_RX_TX_PIN         (0u == UART1_REMOVE_UART_RX_TX_PIN)
#define UART1_UART_RX_PIN            (0u == UART1_REMOVE_UART_RX_PIN)
#define UART1_UART_RX_WAKE_PIN       (0u == UART1_REMOVE_UART_RX_WAKE_PIN)
#define UART1_UART_RTS_PIN           (0u == UART1_REMOVE_UART_RTS_PIN)
#define UART1_UART_CTS_PIN           (0u == UART1_REMOVE_UART_CTS_PIN)


/***************************************
*             Includes
****************************************/

#if (UART1_RX_WAKE_SCL_MOSI_PIN)
    #include "UART1_uart_rx_wake_i2c_scl_spi_mosi.h"
#endif /* (UART1_RX_SCL_MOSI) */

#if (UART1_RX_SCL_MOSI_PIN)
    #include "UART1_uart_rx_i2c_scl_spi_mosi.h"
#endif /* (UART1_RX_SCL_MOSI) */

#if (UART1_TX_SDA_MISO_PIN)
    #include "UART1_uart_tx_i2c_sda_spi_miso.h"
#endif /* (UART1_TX_SDA_MISO) */

#if (UART1_SCLK_PIN)
    #include "UART1_spi_sclk.h"
#endif /* (UART1_SCLK) */

#if (UART1_SS0_PIN)
    #include "UART1_spi_ss0.h"
#endif /* (UART1_SS0_PIN) */

#if (UART1_SS1_PIN)
    #include "UART1_spi_ss1.h"
#endif /* (UART1_SS1_PIN) */

#if (UART1_SS2_PIN)
    #include "UART1_spi_ss2.h"
#endif /* (UART1_SS2_PIN) */

#if (UART1_SS3_PIN)
    #include "UART1_spi_ss3.h"
#endif /* (UART1_SS3_PIN) */

#if (UART1_I2C_PINS)
    #include "UART1_scl.h"
    #include "UART1_sda.h"
#endif /* (UART1_I2C_PINS) */

#if (UART1_SPI_MASTER_PINS)
#if (UART1_SPI_MASTER_SCLK_PIN)
    #include "UART1_sclk_m.h"
#endif /* (UART1_SPI_MASTER_SCLK_PIN) */

#if (UART1_SPI_MASTER_MOSI_PIN)
    #include "UART1_mosi_m.h"
#endif /* (UART1_SPI_MASTER_MOSI_PIN) */

#if (UART1_SPI_MASTER_MISO_PIN)
    #include "UART1_miso_m.h"
#endif /*(UART1_SPI_MASTER_MISO_PIN) */
#endif /* (UART1_SPI_MASTER_PINS) */

#if (UART1_SPI_SLAVE_PINS)
    #include "UART1_sclk_s.h"
    #include "UART1_ss_s.h"

#if (UART1_SPI_SLAVE_MOSI_PIN)
    #include "UART1_mosi_s.h"
#endif /* (UART1_SPI_SLAVE_MOSI_PIN) */

#if (UART1_SPI_SLAVE_MISO_PIN)
    #include "UART1_miso_s.h"
#endif /*(UART1_SPI_SLAVE_MISO_PIN) */
#endif /* (UART1_SPI_SLAVE_PINS) */

#if (UART1_SPI_MASTER_SS0_PIN)
    #include "UART1_ss0_m.h"
#endif /* (UART1_SPI_MASTER_SS0_PIN) */

#if (UART1_SPI_MASTER_SS1_PIN)
    #include "UART1_ss1_m.h"
#endif /* (UART1_SPI_MASTER_SS1_PIN) */

#if (UART1_SPI_MASTER_SS2_PIN)
    #include "UART1_ss2_m.h"
#endif /* (UART1_SPI_MASTER_SS2_PIN) */

#if (UART1_SPI_MASTER_SS3_PIN)
    #include "UART1_ss3_m.h"
#endif /* (UART1_SPI_MASTER_SS3_PIN) */

#if (UART1_UART_TX_PIN)
    #include "UART1_tx.h"
#endif /* (UART1_UART_TX_PIN) */

#if (UART1_UART_RX_TX_PIN)
    #include "UART1_rx_tx.h"
#endif /* (UART1_UART_RX_TX_PIN) */

#if (UART1_UART_RX_PIN)
    #include "UART1_rx.h"
#endif /* (UART1_UART_RX_PIN) */

#if (UART1_UART_RX_WAKE_PIN)
    #include "UART1_rx_wake.h"
#endif /* (UART1_UART_RX_WAKE_PIN) */

#if (UART1_UART_RTS_PIN)
    #include "UART1_rts.h"
#endif /* (UART1_UART_RTS_PIN) */

#if (UART1_UART_CTS_PIN)
    #include "UART1_cts.h"
#endif /* (UART1_UART_CTS_PIN) */


/***************************************
*              Registers
***************************************/

#if (UART1_RX_SCL_MOSI_PIN)
    #define UART1_RX_SCL_MOSI_HSIOM_REG   (*(reg32 *) UART1_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    #define UART1_RX_SCL_MOSI_HSIOM_PTR   ( (reg32 *) UART1_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    
    #define UART1_RX_SCL_MOSI_HSIOM_MASK      (UART1_uart_rx_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define UART1_RX_SCL_MOSI_HSIOM_POS       (UART1_uart_rx_i2c_scl_spi_mosi__0__HSIOM_SHIFT)
    #define UART1_RX_SCL_MOSI_HSIOM_SEL_GPIO  (UART1_uart_rx_i2c_scl_spi_mosi__0__HSIOM_GPIO)
    #define UART1_RX_SCL_MOSI_HSIOM_SEL_I2C   (UART1_uart_rx_i2c_scl_spi_mosi__0__HSIOM_I2C)
    #define UART1_RX_SCL_MOSI_HSIOM_SEL_SPI   (UART1_uart_rx_i2c_scl_spi_mosi__0__HSIOM_SPI)
    #define UART1_RX_SCL_MOSI_HSIOM_SEL_UART  (UART1_uart_rx_i2c_scl_spi_mosi__0__HSIOM_UART)
    
#elif (UART1_RX_WAKE_SCL_MOSI_PIN)
    #define UART1_RX_WAKE_SCL_MOSI_HSIOM_REG   (*(reg32 *) UART1_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    #define UART1_RX_WAKE_SCL_MOSI_HSIOM_PTR   ( (reg32 *) UART1_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    
    #define UART1_RX_WAKE_SCL_MOSI_HSIOM_MASK      (UART1_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define UART1_RX_WAKE_SCL_MOSI_HSIOM_POS       (UART1_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_SHIFT)
    #define UART1_RX_WAKE_SCL_MOSI_HSIOM_SEL_GPIO  (UART1_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_GPIO)
    #define UART1_RX_WAKE_SCL_MOSI_HSIOM_SEL_I2C   (UART1_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_I2C)
    #define UART1_RX_WAKE_SCL_MOSI_HSIOM_SEL_SPI   (UART1_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_SPI)
    #define UART1_RX_WAKE_SCL_MOSI_HSIOM_SEL_UART  (UART1_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_UART)    
   
    #define UART1_RX_WAKE_SCL_MOSI_INTCFG_REG (*(reg32 *) UART1_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define UART1_RX_WAKE_SCL_MOSI_INTCFG_PTR ( (reg32 *) UART1_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define UART1_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS  (UART1_uart_rx_wake_i2c_scl_spi_mosi__SHIFT)
    #define UART1_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK ((uint32) UART1_INTCFG_TYPE_MASK << \
                                                                           UART1_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS)
#else
    /* None of pins UART1_RX_SCL_MOSI_PIN or UART1_RX_WAKE_SCL_MOSI_PIN present.*/
#endif /* (UART1_RX_SCL_MOSI_PIN) */

#if (UART1_TX_SDA_MISO_PIN)
    #define UART1_TX_SDA_MISO_HSIOM_REG   (*(reg32 *) UART1_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    #define UART1_TX_SDA_MISO_HSIOM_PTR   ( (reg32 *) UART1_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    
    #define UART1_TX_SDA_MISO_HSIOM_MASK      (UART1_uart_tx_i2c_sda_spi_miso__0__HSIOM_MASK)
    #define UART1_TX_SDA_MISO_HSIOM_POS       (UART1_uart_tx_i2c_sda_spi_miso__0__HSIOM_SHIFT)
    #define UART1_TX_SDA_MISO_HSIOM_SEL_GPIO  (UART1_uart_tx_i2c_sda_spi_miso__0__HSIOM_GPIO)
    #define UART1_TX_SDA_MISO_HSIOM_SEL_I2C   (UART1_uart_tx_i2c_sda_spi_miso__0__HSIOM_I2C)
    #define UART1_TX_SDA_MISO_HSIOM_SEL_SPI   (UART1_uart_tx_i2c_sda_spi_miso__0__HSIOM_SPI)
    #define UART1_TX_SDA_MISO_HSIOM_SEL_UART  (UART1_uart_tx_i2c_sda_spi_miso__0__HSIOM_UART)
#endif /* (UART1_TX_SDA_MISO_PIN) */

#if (UART1_SCLK_PIN)
    #define UART1_SCLK_HSIOM_REG   (*(reg32 *) UART1_spi_sclk__0__HSIOM)
    #define UART1_SCLK_HSIOM_PTR   ( (reg32 *) UART1_spi_sclk__0__HSIOM)
    
    #define UART1_SCLK_HSIOM_MASK      (UART1_spi_sclk__0__HSIOM_MASK)
    #define UART1_SCLK_HSIOM_POS       (UART1_spi_sclk__0__HSIOM_SHIFT)
    #define UART1_SCLK_HSIOM_SEL_GPIO  (UART1_spi_sclk__0__HSIOM_GPIO)
    #define UART1_SCLK_HSIOM_SEL_I2C   (UART1_spi_sclk__0__HSIOM_I2C)
    #define UART1_SCLK_HSIOM_SEL_SPI   (UART1_spi_sclk__0__HSIOM_SPI)
    #define UART1_SCLK_HSIOM_SEL_UART  (UART1_spi_sclk__0__HSIOM_UART)
#endif /* (UART1_SCLK_PIN) */

#if (UART1_SS0_PIN)
    #define UART1_SS0_HSIOM_REG   (*(reg32 *) UART1_spi_ss0__0__HSIOM)
    #define UART1_SS0_HSIOM_PTR   ( (reg32 *) UART1_spi_ss0__0__HSIOM)
    
    #define UART1_SS0_HSIOM_MASK      (UART1_spi_ss0__0__HSIOM_MASK)
    #define UART1_SS0_HSIOM_POS       (UART1_spi_ss0__0__HSIOM_SHIFT)
    #define UART1_SS0_HSIOM_SEL_GPIO  (UART1_spi_ss0__0__HSIOM_GPIO)
    #define UART1_SS0_HSIOM_SEL_I2C   (UART1_spi_ss0__0__HSIOM_I2C)
    #define UART1_SS0_HSIOM_SEL_SPI   (UART1_spi_ss0__0__HSIOM_SPI)
#if !(UART1_CY_SCBIP_V0 || UART1_CY_SCBIP_V1)
    #define UART1_SS0_HSIOM_SEL_UART  (UART1_spi_ss0__0__HSIOM_UART)
#endif /* !(UART1_CY_SCBIP_V0 || UART1_CY_SCBIP_V1) */
#endif /* (UART1_SS0_PIN) */

#if (UART1_SS1_PIN)
    #define UART1_SS1_HSIOM_REG  (*(reg32 *) UART1_spi_ss1__0__HSIOM)
    #define UART1_SS1_HSIOM_PTR  ( (reg32 *) UART1_spi_ss1__0__HSIOM)
    
    #define UART1_SS1_HSIOM_MASK     (UART1_spi_ss1__0__HSIOM_MASK)
    #define UART1_SS1_HSIOM_POS      (UART1_spi_ss1__0__HSIOM_SHIFT)
    #define UART1_SS1_HSIOM_SEL_GPIO (UART1_spi_ss1__0__HSIOM_GPIO)
    #define UART1_SS1_HSIOM_SEL_I2C  (UART1_spi_ss1__0__HSIOM_I2C)
    #define UART1_SS1_HSIOM_SEL_SPI  (UART1_spi_ss1__0__HSIOM_SPI)
#endif /* (UART1_SS1_PIN) */

#if (UART1_SS2_PIN)
    #define UART1_SS2_HSIOM_REG     (*(reg32 *) UART1_spi_ss2__0__HSIOM)
    #define UART1_SS2_HSIOM_PTR     ( (reg32 *) UART1_spi_ss2__0__HSIOM)
    
    #define UART1_SS2_HSIOM_MASK     (UART1_spi_ss2__0__HSIOM_MASK)
    #define UART1_SS2_HSIOM_POS      (UART1_spi_ss2__0__HSIOM_SHIFT)
    #define UART1_SS2_HSIOM_SEL_GPIO (UART1_spi_ss2__0__HSIOM_GPIO)
    #define UART1_SS2_HSIOM_SEL_I2C  (UART1_spi_ss2__0__HSIOM_I2C)
    #define UART1_SS2_HSIOM_SEL_SPI  (UART1_spi_ss2__0__HSIOM_SPI)
#endif /* (UART1_SS2_PIN) */

#if (UART1_SS3_PIN)
    #define UART1_SS3_HSIOM_REG     (*(reg32 *) UART1_spi_ss3__0__HSIOM)
    #define UART1_SS3_HSIOM_PTR     ( (reg32 *) UART1_spi_ss3__0__HSIOM)
    
    #define UART1_SS3_HSIOM_MASK     (UART1_spi_ss3__0__HSIOM_MASK)
    #define UART1_SS3_HSIOM_POS      (UART1_spi_ss3__0__HSIOM_SHIFT)
    #define UART1_SS3_HSIOM_SEL_GPIO (UART1_spi_ss3__0__HSIOM_GPIO)
    #define UART1_SS3_HSIOM_SEL_I2C  (UART1_spi_ss3__0__HSIOM_I2C)
    #define UART1_SS3_HSIOM_SEL_SPI  (UART1_spi_ss3__0__HSIOM_SPI)
#endif /* (UART1_SS3_PIN) */

#if (UART1_I2C_PINS)
    #define UART1_SCL_HSIOM_REG  (*(reg32 *) UART1_scl__0__HSIOM)
    #define UART1_SCL_HSIOM_PTR  ( (reg32 *) UART1_scl__0__HSIOM)
    
    #define UART1_SCL_HSIOM_MASK     (UART1_scl__0__HSIOM_MASK)
    #define UART1_SCL_HSIOM_POS      (UART1_scl__0__HSIOM_SHIFT)
    #define UART1_SCL_HSIOM_SEL_GPIO (UART1_sda__0__HSIOM_GPIO)
    #define UART1_SCL_HSIOM_SEL_I2C  (UART1_sda__0__HSIOM_I2C)
    
    #define UART1_SDA_HSIOM_REG  (*(reg32 *) UART1_sda__0__HSIOM)
    #define UART1_SDA_HSIOM_PTR  ( (reg32 *) UART1_sda__0__HSIOM)
    
    #define UART1_SDA_HSIOM_MASK     (UART1_sda__0__HSIOM_MASK)
    #define UART1_SDA_HSIOM_POS      (UART1_sda__0__HSIOM_SHIFT)
    #define UART1_SDA_HSIOM_SEL_GPIO (UART1_sda__0__HSIOM_GPIO)
    #define UART1_SDA_HSIOM_SEL_I2C  (UART1_sda__0__HSIOM_I2C)
#endif /* (UART1_I2C_PINS) */

#if (UART1_SPI_SLAVE_PINS)
    #define UART1_SCLK_S_HSIOM_REG   (*(reg32 *) UART1_sclk_s__0__HSIOM)
    #define UART1_SCLK_S_HSIOM_PTR   ( (reg32 *) UART1_sclk_s__0__HSIOM)
    
    #define UART1_SCLK_S_HSIOM_MASK      (UART1_sclk_s__0__HSIOM_MASK)
    #define UART1_SCLK_S_HSIOM_POS       (UART1_sclk_s__0__HSIOM_SHIFT)
    #define UART1_SCLK_S_HSIOM_SEL_GPIO  (UART1_sclk_s__0__HSIOM_GPIO)
    #define UART1_SCLK_S_HSIOM_SEL_SPI   (UART1_sclk_s__0__HSIOM_SPI)
    
    #define UART1_SS0_S_HSIOM_REG    (*(reg32 *) UART1_ss0_s__0__HSIOM)
    #define UART1_SS0_S_HSIOM_PTR    ( (reg32 *) UART1_ss0_s__0__HSIOM)
    
    #define UART1_SS0_S_HSIOM_MASK       (UART1_ss0_s__0__HSIOM_MASK)
    #define UART1_SS0_S_HSIOM_POS        (UART1_ss0_s__0__HSIOM_SHIFT)
    #define UART1_SS0_S_HSIOM_SEL_GPIO   (UART1_ss0_s__0__HSIOM_GPIO)  
    #define UART1_SS0_S_HSIOM_SEL_SPI    (UART1_ss0_s__0__HSIOM_SPI)
#endif /* (UART1_SPI_SLAVE_PINS) */

#if (UART1_SPI_SLAVE_MOSI_PIN)
    #define UART1_MOSI_S_HSIOM_REG   (*(reg32 *) UART1_mosi_s__0__HSIOM)
    #define UART1_MOSI_S_HSIOM_PTR   ( (reg32 *) UART1_mosi_s__0__HSIOM)
    
    #define UART1_MOSI_S_HSIOM_MASK      (UART1_mosi_s__0__HSIOM_MASK)
    #define UART1_MOSI_S_HSIOM_POS       (UART1_mosi_s__0__HSIOM_SHIFT)
    #define UART1_MOSI_S_HSIOM_SEL_GPIO  (UART1_mosi_s__0__HSIOM_GPIO)
    #define UART1_MOSI_S_HSIOM_SEL_SPI   (UART1_mosi_s__0__HSIOM_SPI)
#endif /* (UART1_SPI_SLAVE_MOSI_PIN) */

#if (UART1_SPI_SLAVE_MISO_PIN)
    #define UART1_MISO_S_HSIOM_REG   (*(reg32 *) UART1_miso_s__0__HSIOM)
    #define UART1_MISO_S_HSIOM_PTR   ( (reg32 *) UART1_miso_s__0__HSIOM)
    
    #define UART1_MISO_S_HSIOM_MASK      (UART1_miso_s__0__HSIOM_MASK)
    #define UART1_MISO_S_HSIOM_POS       (UART1_miso_s__0__HSIOM_SHIFT)
    #define UART1_MISO_S_HSIOM_SEL_GPIO  (UART1_miso_s__0__HSIOM_GPIO)
    #define UART1_MISO_S_HSIOM_SEL_SPI   (UART1_miso_s__0__HSIOM_SPI)
#endif /* (UART1_SPI_SLAVE_MISO_PIN) */

#if (UART1_SPI_MASTER_MISO_PIN)
    #define UART1_MISO_M_HSIOM_REG   (*(reg32 *) UART1_miso_m__0__HSIOM)
    #define UART1_MISO_M_HSIOM_PTR   ( (reg32 *) UART1_miso_m__0__HSIOM)
    
    #define UART1_MISO_M_HSIOM_MASK      (UART1_miso_m__0__HSIOM_MASK)
    #define UART1_MISO_M_HSIOM_POS       (UART1_miso_m__0__HSIOM_SHIFT)
    #define UART1_MISO_M_HSIOM_SEL_GPIO  (UART1_miso_m__0__HSIOM_GPIO)
    #define UART1_MISO_M_HSIOM_SEL_SPI   (UART1_miso_m__0__HSIOM_SPI)
#endif /* (UART1_SPI_MASTER_MISO_PIN) */

#if (UART1_SPI_MASTER_MOSI_PIN)
    #define UART1_MOSI_M_HSIOM_REG   (*(reg32 *) UART1_mosi_m__0__HSIOM)
    #define UART1_MOSI_M_HSIOM_PTR   ( (reg32 *) UART1_mosi_m__0__HSIOM)
    
    #define UART1_MOSI_M_HSIOM_MASK      (UART1_mosi_m__0__HSIOM_MASK)
    #define UART1_MOSI_M_HSIOM_POS       (UART1_mosi_m__0__HSIOM_SHIFT)
    #define UART1_MOSI_M_HSIOM_SEL_GPIO  (UART1_mosi_m__0__HSIOM_GPIO)
    #define UART1_MOSI_M_HSIOM_SEL_SPI   (UART1_mosi_m__0__HSIOM_SPI)
#endif /* (UART1_SPI_MASTER_MOSI_PIN) */

#if (UART1_SPI_MASTER_SCLK_PIN)
    #define UART1_SCLK_M_HSIOM_REG   (*(reg32 *) UART1_sclk_m__0__HSIOM)
    #define UART1_SCLK_M_HSIOM_PTR   ( (reg32 *) UART1_sclk_m__0__HSIOM)
    
    #define UART1_SCLK_M_HSIOM_MASK      (UART1_sclk_m__0__HSIOM_MASK)
    #define UART1_SCLK_M_HSIOM_POS       (UART1_sclk_m__0__HSIOM_SHIFT)
    #define UART1_SCLK_M_HSIOM_SEL_GPIO  (UART1_sclk_m__0__HSIOM_GPIO)
    #define UART1_SCLK_M_HSIOM_SEL_SPI   (UART1_sclk_m__0__HSIOM_SPI)
#endif /* (UART1_SPI_MASTER_SCLK_PIN) */

#if (UART1_SPI_MASTER_SS0_PIN)
    #define UART1_SS0_M_HSIOM_REG    (*(reg32 *) UART1_ss0_m__0__HSIOM)
    #define UART1_SS0_M_HSIOM_PTR    ( (reg32 *) UART1_ss0_m__0__HSIOM)
    
    #define UART1_SS0_M_HSIOM_MASK       (UART1_ss0_m__0__HSIOM_MASK)
    #define UART1_SS0_M_HSIOM_POS        (UART1_ss0_m__0__HSIOM_SHIFT)
    #define UART1_SS0_M_HSIOM_SEL_GPIO   (UART1_ss0_m__0__HSIOM_GPIO)
    #define UART1_SS0_M_HSIOM_SEL_SPI    (UART1_ss0_m__0__HSIOM_SPI)
#endif /* (UART1_SPI_MASTER_SS0_PIN) */

#if (UART1_SPI_MASTER_SS1_PIN)
    #define UART1_SS1_M_HSIOM_REG    (*(reg32 *) UART1_ss1_m__0__HSIOM)
    #define UART1_SS1_M_HSIOM_PTR    ( (reg32 *) UART1_ss1_m__0__HSIOM)
    
    #define UART1_SS1_M_HSIOM_MASK       (UART1_ss1_m__0__HSIOM_MASK)
    #define UART1_SS1_M_HSIOM_POS        (UART1_ss1_m__0__HSIOM_SHIFT)
    #define UART1_SS1_M_HSIOM_SEL_GPIO   (UART1_ss1_m__0__HSIOM_GPIO)
    #define UART1_SS1_M_HSIOM_SEL_SPI    (UART1_ss1_m__0__HSIOM_SPI)
#endif /* (UART1_SPI_MASTER_SS1_PIN) */

#if (UART1_SPI_MASTER_SS2_PIN)
    #define UART1_SS2_M_HSIOM_REG    (*(reg32 *) UART1_ss2_m__0__HSIOM)
    #define UART1_SS2_M_HSIOM_PTR    ( (reg32 *) UART1_ss2_m__0__HSIOM)
    
    #define UART1_SS2_M_HSIOM_MASK       (UART1_ss2_m__0__HSIOM_MASK)
    #define UART1_SS2_M_HSIOM_POS        (UART1_ss2_m__0__HSIOM_SHIFT)
    #define UART1_SS2_M_HSIOM_SEL_GPIO   (UART1_ss2_m__0__HSIOM_GPIO)
    #define UART1_SS2_M_HSIOM_SEL_SPI    (UART1_ss2_m__0__HSIOM_SPI)
#endif /* (UART1_SPI_MASTER_SS2_PIN) */

#if (UART1_SPI_MASTER_SS3_PIN)
    #define UART1_SS3_M_HSIOM_REG    (*(reg32 *) UART1_ss3_m__0__HSIOM)
    #define UART1_SS3_M_HSIOM_PTR    ( (reg32 *) UART1_ss3_m__0__HSIOM)
    
    #define UART1_SS3_M_HSIOM_MASK      (UART1_ss3_m__0__HSIOM_MASK)
    #define UART1_SS3_M_HSIOM_POS       (UART1_ss3_m__0__HSIOM_SHIFT)
    #define UART1_SS3_M_HSIOM_SEL_GPIO  (UART1_ss3_m__0__HSIOM_GPIO)
    #define UART1_SS3_M_HSIOM_SEL_SPI   (UART1_ss3_m__0__HSIOM_SPI)
#endif /* (UART1_SPI_MASTER_SS3_PIN) */

#if (UART1_UART_RX_PIN)
    #define UART1_RX_HSIOM_REG   (*(reg32 *) UART1_rx__0__HSIOM)
    #define UART1_RX_HSIOM_PTR   ( (reg32 *) UART1_rx__0__HSIOM)
    
    #define UART1_RX_HSIOM_MASK      (UART1_rx__0__HSIOM_MASK)
    #define UART1_RX_HSIOM_POS       (UART1_rx__0__HSIOM_SHIFT)
    #define UART1_RX_HSIOM_SEL_GPIO  (UART1_rx__0__HSIOM_GPIO)
    #define UART1_RX_HSIOM_SEL_UART  (UART1_rx__0__HSIOM_UART)
#endif /* (UART1_UART_RX_PIN) */

#if (UART1_UART_RX_WAKE_PIN)
    #define UART1_RX_WAKE_HSIOM_REG   (*(reg32 *) UART1_rx_wake__0__HSIOM)
    #define UART1_RX_WAKE_HSIOM_PTR   ( (reg32 *) UART1_rx_wake__0__HSIOM)
    
    #define UART1_RX_WAKE_HSIOM_MASK      (UART1_rx_wake__0__HSIOM_MASK)
    #define UART1_RX_WAKE_HSIOM_POS       (UART1_rx_wake__0__HSIOM_SHIFT)
    #define UART1_RX_WAKE_HSIOM_SEL_GPIO  (UART1_rx_wake__0__HSIOM_GPIO)
    #define UART1_RX_WAKE_HSIOM_SEL_UART  (UART1_rx_wake__0__HSIOM_UART)
#endif /* (UART1_UART_WAKE_RX_PIN) */

#if (UART1_UART_CTS_PIN)
    #define UART1_CTS_HSIOM_REG   (*(reg32 *) UART1_cts__0__HSIOM)
    #define UART1_CTS_HSIOM_PTR   ( (reg32 *) UART1_cts__0__HSIOM)
    
    #define UART1_CTS_HSIOM_MASK      (UART1_cts__0__HSIOM_MASK)
    #define UART1_CTS_HSIOM_POS       (UART1_cts__0__HSIOM_SHIFT)
    #define UART1_CTS_HSIOM_SEL_GPIO  (UART1_cts__0__HSIOM_GPIO)
    #define UART1_CTS_HSIOM_SEL_UART  (UART1_cts__0__HSIOM_UART)
#endif /* (UART1_UART_CTS_PIN) */

#if (UART1_UART_TX_PIN)
    #define UART1_TX_HSIOM_REG   (*(reg32 *) UART1_tx__0__HSIOM)
    #define UART1_TX_HSIOM_PTR   ( (reg32 *) UART1_tx__0__HSIOM)
    
    #define UART1_TX_HSIOM_MASK      (UART1_tx__0__HSIOM_MASK)
    #define UART1_TX_HSIOM_POS       (UART1_tx__0__HSIOM_SHIFT)
    #define UART1_TX_HSIOM_SEL_GPIO  (UART1_tx__0__HSIOM_GPIO)
    #define UART1_TX_HSIOM_SEL_UART  (UART1_tx__0__HSIOM_UART)
#endif /* (UART1_UART_TX_PIN) */

#if (UART1_UART_RX_TX_PIN)
    #define UART1_RX_TX_HSIOM_REG   (*(reg32 *) UART1_rx_tx__0__HSIOM)
    #define UART1_RX_TX_HSIOM_PTR   ( (reg32 *) UART1_rx_tx__0__HSIOM)
    
    #define UART1_RX_TX_HSIOM_MASK      (UART1_rx_tx__0__HSIOM_MASK)
    #define UART1_RX_TX_HSIOM_POS       (UART1_rx_tx__0__HSIOM_SHIFT)
    #define UART1_RX_TX_HSIOM_SEL_GPIO  (UART1_rx_tx__0__HSIOM_GPIO)
    #define UART1_RX_TX_HSIOM_SEL_UART  (UART1_rx_tx__0__HSIOM_UART)
#endif /* (UART1_UART_RX_TX_PIN) */

#if (UART1_UART_RTS_PIN)
    #define UART1_RTS_HSIOM_REG      (*(reg32 *) UART1_rts__0__HSIOM)
    #define UART1_RTS_HSIOM_PTR      ( (reg32 *) UART1_rts__0__HSIOM)
    
    #define UART1_RTS_HSIOM_MASK     (UART1_rts__0__HSIOM_MASK)
    #define UART1_RTS_HSIOM_POS      (UART1_rts__0__HSIOM_SHIFT)    
    #define UART1_RTS_HSIOM_SEL_GPIO (UART1_rts__0__HSIOM_GPIO)
    #define UART1_RTS_HSIOM_SEL_UART (UART1_rts__0__HSIOM_UART)    
#endif /* (UART1_UART_RTS_PIN) */


/***************************************
*        Registers Constants
***************************************/

/* HSIOM switch values. */ 
#define UART1_HSIOM_DEF_SEL      (0x00u)
#define UART1_HSIOM_GPIO_SEL     (0x00u)
/* The HSIOM values provided below are valid only for UART1_CY_SCBIP_V0 
* and UART1_CY_SCBIP_V1. It is not recommended to use them for 
* UART1_CY_SCBIP_V2. Use pin name specific HSIOM constants provided 
* above instead for any SCB IP block version.
*/
#define UART1_HSIOM_UART_SEL     (0x09u)
#define UART1_HSIOM_I2C_SEL      (0x0Eu)
#define UART1_HSIOM_SPI_SEL      (0x0Fu)

/* Pins settings index. */
#define UART1_RX_WAKE_SCL_MOSI_PIN_INDEX   (0u)
#define UART1_RX_SCL_MOSI_PIN_INDEX       (0u)
#define UART1_TX_SDA_MISO_PIN_INDEX       (1u)
#define UART1_SCLK_PIN_INDEX       (2u)
#define UART1_SS0_PIN_INDEX       (3u)
#define UART1_SS1_PIN_INDEX                  (4u)
#define UART1_SS2_PIN_INDEX                  (5u)
#define UART1_SS3_PIN_INDEX                  (6u)

/* Pins settings mask. */
#define UART1_RX_WAKE_SCL_MOSI_PIN_MASK ((uint32) 0x01u << UART1_RX_WAKE_SCL_MOSI_PIN_INDEX)
#define UART1_RX_SCL_MOSI_PIN_MASK     ((uint32) 0x01u << UART1_RX_SCL_MOSI_PIN_INDEX)
#define UART1_TX_SDA_MISO_PIN_MASK     ((uint32) 0x01u << UART1_TX_SDA_MISO_PIN_INDEX)
#define UART1_SCLK_PIN_MASK     ((uint32) 0x01u << UART1_SCLK_PIN_INDEX)
#define UART1_SS0_PIN_MASK     ((uint32) 0x01u << UART1_SS0_PIN_INDEX)
#define UART1_SS1_PIN_MASK                ((uint32) 0x01u << UART1_SS1_PIN_INDEX)
#define UART1_SS2_PIN_MASK                ((uint32) 0x01u << UART1_SS2_PIN_INDEX)
#define UART1_SS3_PIN_MASK                ((uint32) 0x01u << UART1_SS3_PIN_INDEX)

/* Pin interrupt constants. */
#define UART1_INTCFG_TYPE_MASK           (0x03u)
#define UART1_INTCFG_TYPE_FALLING_EDGE   (0x02u)

/* Pin Drive Mode constants. */
#define UART1_PIN_DM_ALG_HIZ  (0u)
#define UART1_PIN_DM_DIG_HIZ  (1u)
#define UART1_PIN_DM_OD_LO    (4u)
#define UART1_PIN_DM_STRONG   (6u)


/***************************************
*          Macro Definitions
***************************************/

/* Return drive mode of the pin */
#define UART1_DM_MASK    (0x7u)
#define UART1_DM_SIZE    (3u)
#define UART1_GET_P4_PIN_DM(reg, pos) \
    ( ((reg) & (uint32) ((uint32) UART1_DM_MASK << (UART1_DM_SIZE * (pos)))) >> \
                                                              (UART1_DM_SIZE * (pos)) )

#if (UART1_TX_SDA_MISO_PIN)
    #define UART1_CHECK_TX_SDA_MISO_PIN_USED \
                (UART1_PIN_DM_ALG_HIZ != \
                    UART1_GET_P4_PIN_DM(UART1_uart_tx_i2c_sda_spi_miso_PC, \
                                                   UART1_uart_tx_i2c_sda_spi_miso_SHIFT))
#endif /* (UART1_TX_SDA_MISO_PIN) */

#if (UART1_SS0_PIN)
    #define UART1_CHECK_SS0_PIN_USED \
                (UART1_PIN_DM_ALG_HIZ != \
                    UART1_GET_P4_PIN_DM(UART1_spi_ss0_PC, \
                                                   UART1_spi_ss0_SHIFT))
#endif /* (UART1_SS0_PIN) */

/* Set bits-mask in register */
#define UART1_SET_REGISTER_BITS(reg, mask, pos, mode) \
                    do                                           \
                    {                                            \
                        (reg) = (((reg) & ((uint32) ~(uint32) (mask))) | ((uint32) ((uint32) (mode) << (pos)))); \
                    }while(0)

/* Set bit in the register */
#define UART1_SET_REGISTER_BIT(reg, mask, val) \
                    ((val) ? ((reg) |= (mask)) : ((reg) &= ((uint32) ~((uint32) (mask)))))

#define UART1_SET_HSIOM_SEL(reg, mask, pos, sel) UART1_SET_REGISTER_BITS(reg, mask, pos, sel)
#define UART1_SET_INCFG_TYPE(reg, mask, pos, intType) \
                                                        UART1_SET_REGISTER_BITS(reg, mask, pos, intType)
#define UART1_SET_INP_DIS(reg, mask, val) UART1_SET_REGISTER_BIT(reg, mask, val)

/* UART1_SET_I2C_SCL_DR(val) - Sets I2C SCL DR register.
*  UART1_SET_I2C_SCL_HSIOM_SEL(sel) - Sets I2C SCL HSIOM settings.
*/
/* SCB I2C: scl signal */
#if (UART1_CY_SCBIP_V0)
#if (UART1_I2C_PINS)
    #define UART1_SET_I2C_SCL_DR(val) UART1_scl_Write(val)

    #define UART1_SET_I2C_SCL_HSIOM_SEL(sel) \
                          UART1_SET_HSIOM_SEL(UART1_SCL_HSIOM_REG,  \
                                                         UART1_SCL_HSIOM_MASK, \
                                                         UART1_SCL_HSIOM_POS,  \
                                                         (sel))
    #define UART1_WAIT_SCL_SET_HIGH  (0u == UART1_scl_Read())

/* Unconfigured SCB: scl signal */
#elif (UART1_RX_WAKE_SCL_MOSI_PIN)
    #define UART1_SET_I2C_SCL_DR(val) \
                            UART1_uart_rx_wake_i2c_scl_spi_mosi_Write(val)

    #define UART1_SET_I2C_SCL_HSIOM_SEL(sel) \
                    UART1_SET_HSIOM_SEL(UART1_RX_WAKE_SCL_MOSI_HSIOM_REG,  \
                                                   UART1_RX_WAKE_SCL_MOSI_HSIOM_MASK, \
                                                   UART1_RX_WAKE_SCL_MOSI_HSIOM_POS,  \
                                                   (sel))

    #define UART1_WAIT_SCL_SET_HIGH  (0u == UART1_uart_rx_wake_i2c_scl_spi_mosi_Read())

#elif (UART1_RX_SCL_MOSI_PIN)
    #define UART1_SET_I2C_SCL_DR(val) \
                            UART1_uart_rx_i2c_scl_spi_mosi_Write(val)


    #define UART1_SET_I2C_SCL_HSIOM_SEL(sel) \
                            UART1_SET_HSIOM_SEL(UART1_RX_SCL_MOSI_HSIOM_REG,  \
                                                           UART1_RX_SCL_MOSI_HSIOM_MASK, \
                                                           UART1_RX_SCL_MOSI_HSIOM_POS,  \
                                                           (sel))

    #define UART1_WAIT_SCL_SET_HIGH  (0u == UART1_uart_rx_i2c_scl_spi_mosi_Read())

#else
    #define UART1_SET_I2C_SCL_DR(val)        do{ /* Does nothing */ }while(0)
    #define UART1_SET_I2C_SCL_HSIOM_SEL(sel) do{ /* Does nothing */ }while(0)

    #define UART1_WAIT_SCL_SET_HIGH  (0u)
#endif /* (UART1_I2C_PINS) */

/* SCB I2C: sda signal */
#if (UART1_I2C_PINS)
    #define UART1_WAIT_SDA_SET_HIGH  (0u == UART1_sda_Read())
/* Unconfigured SCB: sda signal */
#elif (UART1_TX_SDA_MISO_PIN)
    #define UART1_WAIT_SDA_SET_HIGH  (0u == UART1_uart_tx_i2c_sda_spi_miso_Read())
#else
    #define UART1_WAIT_SDA_SET_HIGH  (0u)
#endif /* (UART1_MOSI_SCL_RX_PIN) */
#endif /* (UART1_CY_SCBIP_V0) */

/* Clear UART wakeup source */
#if (UART1_RX_SCL_MOSI_PIN)
    #define UART1_CLEAR_UART_RX_WAKE_INTR        do{ /* Does nothing */ }while(0)
    
#elif (UART1_RX_WAKE_SCL_MOSI_PIN)
    #define UART1_CLEAR_UART_RX_WAKE_INTR \
            do{                                      \
                (void) UART1_uart_rx_wake_i2c_scl_spi_mosi_ClearInterrupt(); \
            }while(0)

#elif(UART1_UART_RX_WAKE_PIN)
    #define UART1_CLEAR_UART_RX_WAKE_INTR \
            do{                                      \
                (void) UART1_rx_wake_ClearInterrupt(); \
            }while(0)
#else
#endif /* (UART1_RX_SCL_MOSI_PIN) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Unconfigured pins */
#define UART1_REMOVE_MOSI_SCL_RX_WAKE_PIN    UART1_REMOVE_RX_WAKE_SCL_MOSI_PIN
#define UART1_REMOVE_MOSI_SCL_RX_PIN         UART1_REMOVE_RX_SCL_MOSI_PIN
#define UART1_REMOVE_MISO_SDA_TX_PIN         UART1_REMOVE_TX_SDA_MISO_PIN
#ifndef UART1_REMOVE_SCLK_PIN
#define UART1_REMOVE_SCLK_PIN                UART1_REMOVE_SCLK_PIN
#endif /* UART1_REMOVE_SCLK_PIN */
#ifndef UART1_REMOVE_SS0_PIN
#define UART1_REMOVE_SS0_PIN                 UART1_REMOVE_SS0_PIN
#endif /* UART1_REMOVE_SS0_PIN */

/* Unconfigured pins */
#define UART1_MOSI_SCL_RX_WAKE_PIN   UART1_RX_WAKE_SCL_MOSI_PIN
#define UART1_MOSI_SCL_RX_PIN        UART1_RX_SCL_MOSI_PIN
#define UART1_MISO_SDA_TX_PIN        UART1_TX_SDA_MISO_PIN
#ifndef UART1_SCLK_PIN
#define UART1_SCLK_PIN               UART1_SCLK_PIN
#endif /* UART1_SCLK_PIN */
#ifndef UART1_SS0_PIN
#define UART1_SS0_PIN                UART1_SS0_PIN
#endif /* UART1_SS0_PIN */

#if (UART1_MOSI_SCL_RX_WAKE_PIN)
    #define UART1_MOSI_SCL_RX_WAKE_HSIOM_REG     UART1_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define UART1_MOSI_SCL_RX_WAKE_HSIOM_PTR     UART1_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define UART1_MOSI_SCL_RX_WAKE_HSIOM_MASK    UART1_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define UART1_MOSI_SCL_RX_WAKE_HSIOM_POS     UART1_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define UART1_MOSI_SCL_RX_WAKE_INTCFG_REG    UART1_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define UART1_MOSI_SCL_RX_WAKE_INTCFG_PTR    UART1_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define UART1_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS   UART1_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define UART1_MOSI_SCL_RX_WAKE_INTCFG_TYPE_MASK  UART1_RX_WAKE_SCL_MOSI_HSIOM_REG
#endif /* (UART1_RX_WAKE_SCL_MOSI_PIN) */

#if (UART1_MOSI_SCL_RX_PIN)
    #define UART1_MOSI_SCL_RX_HSIOM_REG      UART1_RX_SCL_MOSI_HSIOM_REG
    #define UART1_MOSI_SCL_RX_HSIOM_PTR      UART1_RX_SCL_MOSI_HSIOM_PTR
    #define UART1_MOSI_SCL_RX_HSIOM_MASK     UART1_RX_SCL_MOSI_HSIOM_MASK
    #define UART1_MOSI_SCL_RX_HSIOM_POS      UART1_RX_SCL_MOSI_HSIOM_POS
#endif /* (UART1_MOSI_SCL_RX_PIN) */

#if (UART1_MISO_SDA_TX_PIN)
    #define UART1_MISO_SDA_TX_HSIOM_REG      UART1_TX_SDA_MISO_HSIOM_REG
    #define UART1_MISO_SDA_TX_HSIOM_PTR      UART1_TX_SDA_MISO_HSIOM_REG
    #define UART1_MISO_SDA_TX_HSIOM_MASK     UART1_TX_SDA_MISO_HSIOM_REG
    #define UART1_MISO_SDA_TX_HSIOM_POS      UART1_TX_SDA_MISO_HSIOM_REG
#endif /* (UART1_MISO_SDA_TX_PIN_PIN) */

#if (UART1_SCLK_PIN)
    #ifndef UART1_SCLK_HSIOM_REG
    #define UART1_SCLK_HSIOM_REG     UART1_SCLK_HSIOM_REG
    #define UART1_SCLK_HSIOM_PTR     UART1_SCLK_HSIOM_PTR
    #define UART1_SCLK_HSIOM_MASK    UART1_SCLK_HSIOM_MASK
    #define UART1_SCLK_HSIOM_POS     UART1_SCLK_HSIOM_POS
    #endif /* UART1_SCLK_HSIOM_REG */
#endif /* (UART1_SCLK_PIN) */

#if (UART1_SS0_PIN)
    #ifndef UART1_SS0_HSIOM_REG
    #define UART1_SS0_HSIOM_REG      UART1_SS0_HSIOM_REG
    #define UART1_SS0_HSIOM_PTR      UART1_SS0_HSIOM_PTR
    #define UART1_SS0_HSIOM_MASK     UART1_SS0_HSIOM_MASK
    #define UART1_SS0_HSIOM_POS      UART1_SS0_HSIOM_POS
    #endif /* UART1_SS0_HSIOM_REG */
#endif /* (UART1_SS0_PIN) */

#define UART1_MOSI_SCL_RX_WAKE_PIN_INDEX UART1_RX_WAKE_SCL_MOSI_PIN_INDEX
#define UART1_MOSI_SCL_RX_PIN_INDEX      UART1_RX_SCL_MOSI_PIN_INDEX
#define UART1_MISO_SDA_TX_PIN_INDEX      UART1_TX_SDA_MISO_PIN_INDEX
#ifndef UART1_SCLK_PIN_INDEX
#define UART1_SCLK_PIN_INDEX             UART1_SCLK_PIN_INDEX
#endif /* UART1_SCLK_PIN_INDEX */
#ifndef UART1_SS0_PIN_INDEX
#define UART1_SS0_PIN_INDEX              UART1_SS0_PIN_INDEX
#endif /* UART1_SS0_PIN_INDEX */

#define UART1_MOSI_SCL_RX_WAKE_PIN_MASK UART1_RX_WAKE_SCL_MOSI_PIN_MASK
#define UART1_MOSI_SCL_RX_PIN_MASK      UART1_RX_SCL_MOSI_PIN_MASK
#define UART1_MISO_SDA_TX_PIN_MASK      UART1_TX_SDA_MISO_PIN_MASK
#ifndef UART1_SCLK_PIN_MASK
#define UART1_SCLK_PIN_MASK             UART1_SCLK_PIN_MASK
#endif /* UART1_SCLK_PIN_MASK */
#ifndef UART1_SS0_PIN_MASK
#define UART1_SS0_PIN_MASK              UART1_SS0_PIN_MASK
#endif /* UART1_SS0_PIN_MASK */

#endif /* (CY_SCB_PINS_UART1_H) */


/* [] END OF FILE */

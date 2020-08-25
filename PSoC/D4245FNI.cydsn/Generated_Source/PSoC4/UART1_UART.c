/***************************************************************************//**
* \file UART1_UART.c
* \version 4.0
*
* \brief
*  This file provides the source code to the API for the SCB Component in
*  UART mode.
*
* Note:
*
*******************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "UART1_PVT.h"
#include "UART1_SPI_UART_PVT.h"
#include "cyapicallbacks.h"

#if (UART1_UART_WAKE_ENABLE_CONST && UART1_UART_RX_WAKEUP_IRQ)
    /**
    * \addtogroup group_globals
    * \{
    */
    /** This global variable determines whether to enable Skip Start
    * functionality when UART1_Sleep() function is called:
    * 0 – disable, other values – enable. Default value is 1.
    * It is only available when Enable wakeup from Deep Sleep Mode is enabled.
    */
    uint8 UART1_skipStart = 1u;
    /** \} globals */
#endif /* (UART1_UART_WAKE_ENABLE_CONST && UART1_UART_RX_WAKEUP_IRQ) */

#if(UART1_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    const UART1_UART_INIT_STRUCT UART1_configUart =
    {
        UART1_UART_SUB_MODE,
        UART1_UART_DIRECTION,
        UART1_UART_DATA_BITS_NUM,
        UART1_UART_PARITY_TYPE,
        UART1_UART_STOP_BITS_NUM,
        UART1_UART_OVS_FACTOR,
        UART1_UART_IRDA_LOW_POWER,
        UART1_UART_MEDIAN_FILTER_ENABLE,
        UART1_UART_RETRY_ON_NACK,
        UART1_UART_IRDA_POLARITY,
        UART1_UART_DROP_ON_PARITY_ERR,
        UART1_UART_DROP_ON_FRAME_ERR,
        UART1_UART_WAKE_ENABLE,
        0u,
        NULL,
        0u,
        NULL,
        UART1_UART_MP_MODE_ENABLE,
        UART1_UART_MP_ACCEPT_ADDRESS,
        UART1_UART_MP_RX_ADDRESS,
        UART1_UART_MP_RX_ADDRESS_MASK,
        (uint32) UART1_SCB_IRQ_INTERNAL,
        UART1_UART_INTR_RX_MASK,
        UART1_UART_RX_TRIGGER_LEVEL,
        UART1_UART_INTR_TX_MASK,
        UART1_UART_TX_TRIGGER_LEVEL,
        (uint8) UART1_UART_BYTE_MODE_ENABLE,
        (uint8) UART1_UART_CTS_ENABLE,
        (uint8) UART1_UART_CTS_POLARITY,
        (uint8) UART1_UART_RTS_POLARITY,
        (uint8) UART1_UART_RTS_FIFO_LEVEL,
        (uint8) UART1_UART_RX_BREAK_WIDTH
    };


    /*******************************************************************************
    * Function Name: UART1_UartInit
    ****************************************************************************//**
    *
    *  Configures the UART1 for UART operation.
    *
    *  This function is intended specifically to be used when the UART1
    *  configuration is set to “Unconfigured UART1” in the customizer.
    *  After initializing the UART1 in UART mode using this function,
    *  the component can be enabled using the UART1_Start() or
    * UART1_Enable() function.
    *  This function uses a pointer to a structure that provides the configuration
    *  settings. This structure contains the same information that would otherwise
    *  be provided by the customizer settings.
    *
    *  \param config: pointer to a structure that contains the following list of
    *   fields. These fields match the selections available in the customizer.
    *   Refer to the customizer for further description of the settings.
    *
    *******************************************************************************/
    void UART1_UartInit(const UART1_UART_INIT_STRUCT *config)
    {
        uint32 pinsConfig;

        if (NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due to bad function parameter */
        }
        else
        {
            /* Get direction to configure UART pins: TX, RX or TX+RX */
            pinsConfig  = config->direction;

        #if !(UART1_CY_SCBIP_V0 || UART1_CY_SCBIP_V1)
            /* Add RTS and CTS pins to configure */
            pinsConfig |= (0u != config->rtsRxFifoLevel) ? (UART1_UART_RTS_PIN_ENABLE) : (0u);
            pinsConfig |= (0u != config->enableCts)      ? (UART1_UART_CTS_PIN_ENABLE) : (0u);
        #endif /* !(UART1_CY_SCBIP_V0 || UART1_CY_SCBIP_V1) */

            /* Configure pins */
            UART1_SetPins(UART1_SCB_MODE_UART, config->mode, pinsConfig);

            /* Store internal configuration */
            UART1_scbMode       = (uint8) UART1_SCB_MODE_UART;
            UART1_scbEnableWake = (uint8) config->enableWake;
            UART1_scbEnableIntr = (uint8) config->enableInterrupt;

            /* Set RX direction internal variables */
            UART1_rxBuffer      =         config->rxBuffer;
            UART1_rxDataBits    = (uint8) config->dataBits;
            UART1_rxBufferSize  =         config->rxBufferSize;

            /* Set TX direction internal variables */
            UART1_txBuffer      =         config->txBuffer;
            UART1_txDataBits    = (uint8) config->dataBits;
            UART1_txBufferSize  =         config->txBufferSize;

            /* Configure UART interface */
            if(UART1_UART_MODE_IRDA == config->mode)
            {
                /* OVS settings: IrDA */
                UART1_CTRL_REG  = ((0u != config->enableIrdaLowPower) ?
                                                (UART1_UART_GET_CTRL_OVS_IRDA_LP(config->oversample)) :
                                                (UART1_CTRL_OVS_IRDA_OVS16));
            }
            else
            {
                /* OVS settings: UART and SmartCard */
                UART1_CTRL_REG  = UART1_GET_CTRL_OVS(config->oversample);
            }

            UART1_CTRL_REG     |= UART1_GET_CTRL_BYTE_MODE  (config->enableByteMode)      |
                                             UART1_GET_CTRL_ADDR_ACCEPT(config->multiprocAcceptAddr) |
                                             UART1_CTRL_UART;

            /* Configure sub-mode: UART, SmartCard or IrDA */
            UART1_UART_CTRL_REG = UART1_GET_UART_CTRL_MODE(config->mode);

            /* Configure RX direction */
            UART1_UART_RX_CTRL_REG = UART1_GET_UART_RX_CTRL_MODE(config->stopBits)              |
                                        UART1_GET_UART_RX_CTRL_POLARITY(config->enableInvertedRx)          |
                                        UART1_GET_UART_RX_CTRL_MP_MODE(config->enableMultiproc)            |
                                        UART1_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(config->dropOnParityErr) |
                                        UART1_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(config->dropOnFrameErr)   |
                                        UART1_GET_UART_RX_CTRL_BREAK_WIDTH(config->breakWidth);

            if(UART1_UART_PARITY_NONE != config->parity)
            {
               UART1_UART_RX_CTRL_REG |= UART1_GET_UART_RX_CTRL_PARITY(config->parity) |
                                                    UART1_UART_RX_CTRL_PARITY_ENABLED;
            }

            UART1_RX_CTRL_REG      = UART1_GET_RX_CTRL_DATA_WIDTH(config->dataBits)       |
                                                UART1_GET_RX_CTRL_MEDIAN(config->enableMedianFilter) |
                                                UART1_GET_UART_RX_CTRL_ENABLED(config->direction);

            UART1_RX_FIFO_CTRL_REG = UART1_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(config->rxTriggerLevel);

            /* Configure MP address */
            UART1_RX_MATCH_REG     = UART1_GET_RX_MATCH_ADDR(config->multiprocAddr) |
                                                UART1_GET_RX_MATCH_MASK(config->multiprocAddrMask);

            /* Configure RX direction */
            UART1_UART_TX_CTRL_REG = UART1_GET_UART_TX_CTRL_MODE(config->stopBits) |
                                                UART1_GET_UART_TX_CTRL_RETRY_NACK(config->enableRetryNack);

            if(UART1_UART_PARITY_NONE != config->parity)
            {
               UART1_UART_TX_CTRL_REG |= UART1_GET_UART_TX_CTRL_PARITY(config->parity) |
                                                    UART1_UART_TX_CTRL_PARITY_ENABLED;
            }

            UART1_TX_CTRL_REG      = UART1_GET_TX_CTRL_DATA_WIDTH(config->dataBits)    |
                                                UART1_GET_UART_TX_CTRL_ENABLED(config->direction);

            UART1_TX_FIFO_CTRL_REG = UART1_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(config->txTriggerLevel);

        #if !(UART1_CY_SCBIP_V0 || UART1_CY_SCBIP_V1)
            UART1_UART_FLOW_CTRL_REG = UART1_GET_UART_FLOW_CTRL_CTS_ENABLE(config->enableCts) | \
                                            UART1_GET_UART_FLOW_CTRL_CTS_POLARITY (config->ctsPolarity)  | \
                                            UART1_GET_UART_FLOW_CTRL_RTS_POLARITY (config->rtsPolarity)  | \
                                            UART1_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(config->rtsRxFifoLevel);
        #endif /* !(UART1_CY_SCBIP_V0 || UART1_CY_SCBIP_V1) */

            /* Configure interrupt with UART handler but do not enable it */
            CyIntDisable    (UART1_ISR_NUMBER);
            CyIntSetPriority(UART1_ISR_NUMBER, UART1_ISR_PRIORITY);
            (void) CyIntSetVector(UART1_ISR_NUMBER, &UART1_SPI_UART_ISR);

            /* Configure WAKE interrupt */
        #if(UART1_UART_RX_WAKEUP_IRQ)
            CyIntDisable    (UART1_RX_WAKE_ISR_NUMBER);
            CyIntSetPriority(UART1_RX_WAKE_ISR_NUMBER, UART1_RX_WAKE_ISR_PRIORITY);
            (void) CyIntSetVector(UART1_RX_WAKE_ISR_NUMBER, &UART1_UART_WAKEUP_ISR);
        #endif /* (UART1_UART_RX_WAKEUP_IRQ) */

            /* Configure interrupt sources */
            UART1_INTR_I2C_EC_MASK_REG = UART1_NO_INTR_SOURCES;
            UART1_INTR_SPI_EC_MASK_REG = UART1_NO_INTR_SOURCES;
            UART1_INTR_SLAVE_MASK_REG  = UART1_NO_INTR_SOURCES;
            UART1_INTR_MASTER_MASK_REG = UART1_NO_INTR_SOURCES;
            UART1_INTR_RX_MASK_REG     = config->rxInterruptMask;
            UART1_INTR_TX_MASK_REG     = config->txInterruptMask;

            /* Configure TX interrupt sources to restore. */
            UART1_IntrTxMask = LO16(UART1_INTR_TX_MASK_REG);

            /* Clear RX buffer indexes */
            UART1_rxBufferHead     = 0u;
            UART1_rxBufferTail     = 0u;
            UART1_rxBufferOverflow = 0u;

            /* Clear TX buffer indexes */
            UART1_txBufferHead = 0u;
            UART1_txBufferTail = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: UART1_UartInit
    ****************************************************************************//**
    *
    *  Configures the SCB for the UART operation.
    *
    *******************************************************************************/
    void UART1_UartInit(void)
    {
        /* Configure UART interface */
        UART1_CTRL_REG = UART1_UART_DEFAULT_CTRL;

        /* Configure sub-mode: UART, SmartCard or IrDA */
        UART1_UART_CTRL_REG = UART1_UART_DEFAULT_UART_CTRL;

        /* Configure RX direction */
        UART1_UART_RX_CTRL_REG = UART1_UART_DEFAULT_UART_RX_CTRL;
        UART1_RX_CTRL_REG      = UART1_UART_DEFAULT_RX_CTRL;
        UART1_RX_FIFO_CTRL_REG = UART1_UART_DEFAULT_RX_FIFO_CTRL;
        UART1_RX_MATCH_REG     = UART1_UART_DEFAULT_RX_MATCH_REG;

        /* Configure TX direction */
        UART1_UART_TX_CTRL_REG = UART1_UART_DEFAULT_UART_TX_CTRL;
        UART1_TX_CTRL_REG      = UART1_UART_DEFAULT_TX_CTRL;
        UART1_TX_FIFO_CTRL_REG = UART1_UART_DEFAULT_TX_FIFO_CTRL;

    #if !(UART1_CY_SCBIP_V0 || UART1_CY_SCBIP_V1)
        UART1_UART_FLOW_CTRL_REG = UART1_UART_DEFAULT_FLOW_CTRL;
    #endif /* !(UART1_CY_SCBIP_V0 || UART1_CY_SCBIP_V1) */

        /* Configure interrupt with UART handler but do not enable it */
    #if(UART1_SCB_IRQ_INTERNAL)
        CyIntDisable    (UART1_ISR_NUMBER);
        CyIntSetPriority(UART1_ISR_NUMBER, UART1_ISR_PRIORITY);
        (void) CyIntSetVector(UART1_ISR_NUMBER, &UART1_SPI_UART_ISR);
    #endif /* (UART1_SCB_IRQ_INTERNAL) */

        /* Configure WAKE interrupt */
    #if(UART1_UART_RX_WAKEUP_IRQ)
        CyIntDisable    (UART1_RX_WAKE_ISR_NUMBER);
        CyIntSetPriority(UART1_RX_WAKE_ISR_NUMBER, UART1_RX_WAKE_ISR_PRIORITY);
        (void) CyIntSetVector(UART1_RX_WAKE_ISR_NUMBER, &UART1_UART_WAKEUP_ISR);
    #endif /* (UART1_UART_RX_WAKEUP_IRQ) */

        /* Configure interrupt sources */
        UART1_INTR_I2C_EC_MASK_REG = UART1_UART_DEFAULT_INTR_I2C_EC_MASK;
        UART1_INTR_SPI_EC_MASK_REG = UART1_UART_DEFAULT_INTR_SPI_EC_MASK;
        UART1_INTR_SLAVE_MASK_REG  = UART1_UART_DEFAULT_INTR_SLAVE_MASK;
        UART1_INTR_MASTER_MASK_REG = UART1_UART_DEFAULT_INTR_MASTER_MASK;
        UART1_INTR_RX_MASK_REG     = UART1_UART_DEFAULT_INTR_RX_MASK;
        UART1_INTR_TX_MASK_REG     = UART1_UART_DEFAULT_INTR_TX_MASK;

        /* Configure TX interrupt sources to restore. */
        UART1_IntrTxMask = LO16(UART1_INTR_TX_MASK_REG);

    #if(UART1_INTERNAL_RX_SW_BUFFER_CONST)
        UART1_rxBufferHead     = 0u;
        UART1_rxBufferTail     = 0u;
        UART1_rxBufferOverflow = 0u;
    #endif /* (UART1_INTERNAL_RX_SW_BUFFER_CONST) */

    #if(UART1_INTERNAL_TX_SW_BUFFER_CONST)
        UART1_txBufferHead = 0u;
        UART1_txBufferTail = 0u;
    #endif /* (UART1_INTERNAL_TX_SW_BUFFER_CONST) */
    }
#endif /* (UART1_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: UART1_UartPostEnable
****************************************************************************//**
*
*  Restores HSIOM settings for the UART output pins (TX and/or RTS) to be
*  controlled by the SCB UART.
*
*******************************************************************************/
void UART1_UartPostEnable(void)
{
#if (UART1_SCB_MODE_UNCONFIG_CONST_CFG)
    #if (UART1_TX_SDA_MISO_PIN)
        if (UART1_CHECK_TX_SDA_MISO_PIN_USED)
        {
            /* Set SCB UART to drive the output pin */
            UART1_SET_HSIOM_SEL(UART1_TX_SDA_MISO_HSIOM_REG, UART1_TX_SDA_MISO_HSIOM_MASK,
                                           UART1_TX_SDA_MISO_HSIOM_POS, UART1_TX_SDA_MISO_HSIOM_SEL_UART);
        }
    #endif /* (UART1_TX_SDA_MISO_PIN_PIN) */

    #if !(UART1_CY_SCBIP_V0 || UART1_CY_SCBIP_V1)
        #if (UART1_SS0_PIN)
            if (UART1_CHECK_SS0_PIN_USED)
            {
                /* Set SCB UART to drive the output pin */
                UART1_SET_HSIOM_SEL(UART1_SS0_HSIOM_REG, UART1_SS0_HSIOM_MASK,
                                               UART1_SS0_HSIOM_POS, UART1_SS0_HSIOM_SEL_UART);
            }
        #endif /* (UART1_SS0_PIN) */
    #endif /* !(UART1_CY_SCBIP_V0 || UART1_CY_SCBIP_V1) */

#else
    #if (UART1_UART_TX_PIN)
         /* Set SCB UART to drive the output pin */
        UART1_SET_HSIOM_SEL(UART1_TX_HSIOM_REG, UART1_TX_HSIOM_MASK,
                                       UART1_TX_HSIOM_POS, UART1_TX_HSIOM_SEL_UART);
    #endif /* (UART1_UART_TX_PIN) */

    #if (UART1_UART_RTS_PIN)
        /* Set SCB UART to drive the output pin */
        UART1_SET_HSIOM_SEL(UART1_RTS_HSIOM_REG, UART1_RTS_HSIOM_MASK,
                                       UART1_RTS_HSIOM_POS, UART1_RTS_HSIOM_SEL_UART);
    #endif /* (UART1_UART_RTS_PIN) */
#endif /* (UART1_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Restore TX interrupt sources. */
    UART1_SetTxInterruptMode(UART1_IntrTxMask);
}


/*******************************************************************************
* Function Name: UART1_UartStop
****************************************************************************//**
*
*  Changes the HSIOM settings for the UART output pins (TX and/or RTS) to keep
*  them inactive after the block is disabled. The output pins are controlled by
*  the GPIO data register. Also, the function disables the skip start feature
*  to not cause it to trigger after the component is enabled.
*
*******************************************************************************/
void UART1_UartStop(void)
{
#if(UART1_SCB_MODE_UNCONFIG_CONST_CFG)
    #if (UART1_TX_SDA_MISO_PIN)
        if (UART1_CHECK_TX_SDA_MISO_PIN_USED)
        {
            /* Set GPIO to drive output pin */
            UART1_SET_HSIOM_SEL(UART1_TX_SDA_MISO_HSIOM_REG, UART1_TX_SDA_MISO_HSIOM_MASK,
                                           UART1_TX_SDA_MISO_HSIOM_POS, UART1_TX_SDA_MISO_HSIOM_SEL_GPIO);
        }
    #endif /* (UART1_TX_SDA_MISO_PIN_PIN) */

    #if !(UART1_CY_SCBIP_V0 || UART1_CY_SCBIP_V1)
        #if (UART1_SS0_PIN)
            if (UART1_CHECK_SS0_PIN_USED)
            {
                /* Set output pin state after block is disabled */
                UART1_spi_ss0_Write(UART1_GET_UART_RTS_INACTIVE);

                /* Set GPIO to drive output pin */
                UART1_SET_HSIOM_SEL(UART1_SS0_HSIOM_REG, UART1_SS0_HSIOM_MASK,
                                               UART1_SS0_HSIOM_POS, UART1_SS0_HSIOM_SEL_GPIO);
            }
        #endif /* (UART1_SS0_PIN) */
    #endif /* !(UART1_CY_SCBIP_V0 || UART1_CY_SCBIP_V1) */

#else
    #if (UART1_UART_TX_PIN)
        /* Set GPIO to drive output pin */
        UART1_SET_HSIOM_SEL(UART1_TX_HSIOM_REG, UART1_TX_HSIOM_MASK,
                                       UART1_TX_HSIOM_POS, UART1_TX_HSIOM_SEL_GPIO);
    #endif /* (UART1_UART_TX_PIN) */

    #if (UART1_UART_RTS_PIN)
        /* Set output pin state after block is disabled */
        UART1_rts_Write(UART1_GET_UART_RTS_INACTIVE);

        /* Set GPIO to drive output pin */
        UART1_SET_HSIOM_SEL(UART1_RTS_HSIOM_REG, UART1_RTS_HSIOM_MASK,
                                       UART1_RTS_HSIOM_POS, UART1_RTS_HSIOM_SEL_GPIO);
    #endif /* (UART1_UART_RTS_PIN) */

#endif /* (UART1_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (UART1_UART_WAKE_ENABLE_CONST)
    /* Disable skip start feature used for wakeup */
    UART1_UART_RX_CTRL_REG &= (uint32) ~UART1_UART_RX_CTRL_SKIP_START;
#endif /* (UART1_UART_WAKE_ENABLE_CONST) */

    /* Store TX interrupt sources (exclude level triggered). */
    UART1_IntrTxMask = LO16(UART1_GetTxInterruptMode() & UART1_INTR_UART_TX_RESTORE);
}


/*******************************************************************************
* Function Name: UART1_UartSetRxAddress
****************************************************************************//**
*
*  Sets the hardware detectable receiver address for the UART in the
*  Multiprocessor mode.
*
*  \param address: Address for hardware address detection.
*
*******************************************************************************/
void UART1_UartSetRxAddress(uint32 address)
{
     uint32 matchReg;

    matchReg = UART1_RX_MATCH_REG;

    matchReg &= ((uint32) ~UART1_RX_MATCH_ADDR_MASK); /* Clear address bits */
    matchReg |= ((uint32)  (address & UART1_RX_MATCH_ADDR_MASK)); /* Set address  */

    UART1_RX_MATCH_REG = matchReg;
}


/*******************************************************************************
* Function Name: UART1_UartSetRxAddressMask
****************************************************************************//**
*
*  Sets the hardware address mask for the UART in the Multiprocessor mode.
*
*  \param addressMask: Address mask.
*   - Bit value 0 – excludes bit from address comparison.
*   - Bit value 1 – the bit needs to match with the corresponding bit
*     of the address.
*
*******************************************************************************/
void UART1_UartSetRxAddressMask(uint32 addressMask)
{
    uint32 matchReg;

    matchReg = UART1_RX_MATCH_REG;

    matchReg &= ((uint32) ~UART1_RX_MATCH_MASK_MASK); /* Clear address mask bits */
    matchReg |= ((uint32) (addressMask << UART1_RX_MATCH_MASK_POS));

    UART1_RX_MATCH_REG = matchReg;
}


#if(UART1_UART_RX_DIRECTION)
    /*******************************************************************************
    * Function Name: UART1_UartGetChar
    ****************************************************************************//**
    *
    *  Retrieves next data element from receive buffer.
    *  This function is designed for ASCII characters and returns a char where
    *  1 to 255 are valid characters and 0 indicates an error occurred or no data
    *  is present.
    *  - RX software buffer is disabled: Returns data element retrieved from RX
    *    FIFO.
    *  - RX software buffer is enabled: Returns data element from the software
    *    receive buffer.
    *
    *  \return
    *   Next data element from the receive buffer. ASCII character values from
    *   1 to 255 are valid. A returned zero signifies an error condition or no
    *   data available.
    *
    *  \sideeffect
    *   The errors bits may not correspond with reading characters due to
    *   RX FIFO and software buffer usage.
    *   RX software buffer is enabled: The internal software buffer overflow
    *   is not treated as an error condition.
    *   Check UART1_rxBufferOverflow to capture that error condition.
    *
    *******************************************************************************/
    uint32 UART1_UartGetChar(void)
    {
        uint32 rxData = 0u;

        /* Reads data only if there is data to read */
        if (0u != UART1_SpiUartGetRxBufferSize())
        {
            rxData = UART1_SpiUartReadRxData();
        }

        if (UART1_CHECK_INTR_RX(UART1_INTR_RX_ERR))
        {
            rxData = 0u; /* Error occurred: returns zero */
            UART1_ClearRxInterruptSource(UART1_INTR_RX_ERR);
        }

        return (rxData);
    }


    /*******************************************************************************
    * Function Name: UART1_UartGetByte
    ****************************************************************************//**
    *
    *  Retrieves the next data element from the receive buffer, returns the
    *  received byte and error condition.
    *   - The RX software buffer is disabled: returns the data element retrieved
    *     from the RX FIFO. Undefined data will be returned if the RX FIFO is
    *     empty.
    *   - The RX software buffer is enabled: returns data element from the
    *     software receive buffer.
    *
    *  \return
    *   Bits 7-0 contain the next data element from the receive buffer and
    *   other bits contain the error condition.
    *   - UART1_UART_RX_OVERFLOW - Attempt to write to a full
    *     receiver FIFO.
    *   - UART1_UART_RX_UNDERFLOW    Attempt to read from an empty
    *     receiver FIFO.
    *   - UART1_UART_RX_FRAME_ERROR - UART framing error detected.
    *   - UART1_UART_RX_PARITY_ERROR - UART parity error detected.
    *
    *  \sideeffect
    *   The errors bits may not correspond with reading characters due to
    *   RX FIFO and software buffer usage.
    *   RX software buffer is enabled: The internal software buffer overflow
    *   is not treated as an error condition.
    *   Check UART1_rxBufferOverflow to capture that error condition.
    *
    *******************************************************************************/
    uint32 UART1_UartGetByte(void)
    {
        uint32 rxData;
        uint32 tmpStatus;

        #if (UART1_CHECK_RX_SW_BUFFER)
        {
            UART1_DisableInt();
        }
        #endif

        if (0u != UART1_SpiUartGetRxBufferSize())
        {
            /* Enables interrupt to receive more bytes: at least one byte is in
            * buffer.
            */
            #if (UART1_CHECK_RX_SW_BUFFER)
            {
                UART1_EnableInt();
            }
            #endif

            /* Get received byte */
            rxData = UART1_SpiUartReadRxData();
        }
        else
        {
            /* Reads a byte directly from RX FIFO: underflow is raised in the
            * case of empty. Otherwise the first received byte will be read.
            */
            rxData = UART1_RX_FIFO_RD_REG;


            /* Enables interrupt to receive more bytes. */
            #if (UART1_CHECK_RX_SW_BUFFER)
            {

                /* The byte has been read from RX FIFO. Clear RX interrupt to
                * not involve interrupt handler when RX FIFO is empty.
                */
                UART1_ClearRxInterruptSource(UART1_INTR_RX_NOT_EMPTY);

                UART1_EnableInt();
            }
            #endif
        }

        /* Get and clear RX error mask */
        tmpStatus = (UART1_GetRxInterruptSource() & UART1_INTR_RX_ERR);
        UART1_ClearRxInterruptSource(UART1_INTR_RX_ERR);

        /* Puts together data and error status:
        * MP mode and accept address: 9th bit is set to notify mark.
        */
        rxData |= ((uint32) (tmpStatus << 8u));

        return (rxData);
    }


    #if !(UART1_CY_SCBIP_V0 || UART1_CY_SCBIP_V1)
        /*******************************************************************************
        * Function Name: UART1_UartSetRtsPolarity
        ****************************************************************************//**
        *
        *  Sets active polarity of RTS output signal.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        *  \param polarity: Active polarity of RTS output signal.
        *   - UART1_UART_RTS_ACTIVE_LOW  - RTS signal is active low.
        *   - UART1_UART_RTS_ACTIVE_HIGH - RTS signal is active high.
        *
        *******************************************************************************/
        void UART1_UartSetRtsPolarity(uint32 polarity)
        {
            if(0u != polarity)
            {
                UART1_UART_FLOW_CTRL_REG |= (uint32)  UART1_UART_FLOW_CTRL_RTS_POLARITY;
            }
            else
            {
                UART1_UART_FLOW_CTRL_REG &= (uint32) ~UART1_UART_FLOW_CTRL_RTS_POLARITY;
            }
        }


        /*******************************************************************************
        * Function Name: UART1_UartSetRtsFifoLevel
        ****************************************************************************//**
        *
        *  Sets level in the RX FIFO for RTS signal activation.
        *  While the RX FIFO has fewer entries than the RX FIFO level the RTS signal
        *  remains active, otherwise the RTS signal becomes inactive.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        *  \param level: Level in the RX FIFO for RTS signal activation.
        *   The range of valid level values is between 0 and RX FIFO depth - 1.
        *   Setting level value to 0 disables RTS signal activation.
        *
        *******************************************************************************/
        void UART1_UartSetRtsFifoLevel(uint32 level)
        {
            uint32 uartFlowCtrl;

            uartFlowCtrl = UART1_UART_FLOW_CTRL_REG;

            uartFlowCtrl &= ((uint32) ~UART1_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
            uartFlowCtrl |= ((uint32) (UART1_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK & level));

            UART1_UART_FLOW_CTRL_REG = uartFlowCtrl;
        }
    #endif /* !(UART1_CY_SCBIP_V0 || UART1_CY_SCBIP_V1) */

#endif /* (UART1_UART_RX_DIRECTION) */


#if(UART1_UART_TX_DIRECTION)
    /*******************************************************************************
    * Function Name: UART1_UartPutString
    ****************************************************************************//**
    *
    *  Places a NULL terminated string in the transmit buffer to be sent at the
    *  next available bus time.
    *  This function is blocking and waits until there is a space available to put
    *  requested data in transmit buffer.
    *
    *  \param string: pointer to the null terminated string array to be placed in the
    *   transmit buffer.
    *
    *******************************************************************************/
    void UART1_UartPutString(const char8 string[])
    {
        uint32 bufIndex;

        bufIndex = 0u;

        /* Blocks the control flow until all data has been sent */
        while(string[bufIndex] != ((char8) 0))
        {
            UART1_UartPutChar((uint32) string[bufIndex]);
            bufIndex++;
        }
    }


    /*******************************************************************************
    * Function Name: UART1_UartPutCRLF
    ****************************************************************************//**
    *
    *  Places byte of data followed by a carriage return (0x0D) and line feed
    *  (0x0A) in the transmit buffer.
    *  This function is blocking and waits until there is a space available to put
    *  all requested data in transmit buffer.
    *
    *  \param txDataByte: the data to be transmitted.
    *
    *******************************************************************************/
    void UART1_UartPutCRLF(uint32 txDataByte)
    {
        UART1_UartPutChar(txDataByte);  /* Blocks control flow until all data has been sent */
        UART1_UartPutChar(0x0Du);       /* Blocks control flow until all data has been sent */
        UART1_UartPutChar(0x0Au);       /* Blocks control flow until all data has been sent */
    }


    #if !(UART1_CY_SCBIP_V0 || UART1_CY_SCBIP_V1)
        /*******************************************************************************
        * Function Name: UART1SCB_UartEnableCts
        ****************************************************************************//**
        *
        *  Enables usage of CTS input signal by the UART transmitter.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        *******************************************************************************/
        void UART1_UartEnableCts(void)
        {
            UART1_UART_FLOW_CTRL_REG |= (uint32)  UART1_UART_FLOW_CTRL_CTS_ENABLE;
        }


        /*******************************************************************************
        * Function Name: UART1_UartDisableCts
        ****************************************************************************//**
        *
        *  Disables usage of CTS input signal by the UART transmitter.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        *******************************************************************************/
        void UART1_UartDisableCts(void)
        {
            UART1_UART_FLOW_CTRL_REG &= (uint32) ~UART1_UART_FLOW_CTRL_CTS_ENABLE;
        }


        /*******************************************************************************
        * Function Name: UART1_UartSetCtsPolarity
        ****************************************************************************//**
        *
        *  Sets active polarity of CTS input signal.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        * \param
        * polarity: Active polarity of CTS output signal.
        *   - UART1_UART_CTS_ACTIVE_LOW  - CTS signal is active low.
        *   - UART1_UART_CTS_ACTIVE_HIGH - CTS signal is active high.
        *
        *******************************************************************************/
        void UART1_UartSetCtsPolarity(uint32 polarity)
        {
            if (0u != polarity)
            {
                UART1_UART_FLOW_CTRL_REG |= (uint32)  UART1_UART_FLOW_CTRL_CTS_POLARITY;
            }
            else
            {
                UART1_UART_FLOW_CTRL_REG &= (uint32) ~UART1_UART_FLOW_CTRL_CTS_POLARITY;
            }
        }
    #endif /* !(UART1_CY_SCBIP_V0 || UART1_CY_SCBIP_V1) */


    /*******************************************************************************
    * Function Name: UART1_UartSendBreakBlocking
    ****************************************************************************//**
    *
    * Sends a break condition (logic low) of specified width on UART TX line.
    * Blocks until break is completed. Only call this function when UART TX FIFO
    * and shifter are empty.
    *
    * \param breakWidth
    * Width of break condition. Valid range is 4 to 16 bits.
    *
    * \note
    * Before sending break all UART TX interrupt sources are disabled. The state
    * of UART TX interrupt sources is restored before function returns.
    *
    * \sideeffect
    * If this function is called while there is data in the TX FIFO or shifter that
    * data will be shifted out in packets the size of breakWidth.
    *
    *******************************************************************************/
    void UART1_UartSendBreakBlocking(uint32 breakWidth)
    {
        uint32 txCtrlReg;
        uint32 txIntrReg;

        /* Disable all UART TX interrupt source and clear UART TX Done history */
        txIntrReg = UART1_GetTxInterruptMode();
        UART1_SetTxInterruptMode(0u);
        UART1_ClearTxInterruptSource(UART1_INTR_TX_UART_DONE);

        /* Store TX CTRL configuration */
        txCtrlReg = UART1_TX_CTRL_REG;

        /* Set break width */
        UART1_TX_CTRL_REG = (UART1_TX_CTRL_REG & (uint32) ~UART1_TX_CTRL_DATA_WIDTH_MASK) |
                                        UART1_GET_TX_CTRL_DATA_WIDTH(breakWidth);

        /* Generate break */
        UART1_TX_FIFO_WR_REG = 0u;

        /* Wait for break completion */
        while (0u == (UART1_GetTxInterruptSource() & UART1_INTR_TX_UART_DONE))
        {
        }

        /* Clear all UART TX interrupt sources to  */
        UART1_ClearTxInterruptSource(UART1_INTR_TX_ALL);

        /* Restore TX interrupt sources and data width */
        UART1_TX_CTRL_REG = txCtrlReg;
        UART1_SetTxInterruptMode(txIntrReg);
    }
#endif /* (UART1_UART_TX_DIRECTION) */


#if (UART1_UART_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: UART1_UartSaveConfig
    ****************************************************************************//**
    *
    *  Clears and enables an interrupt on a falling edge of the Rx input. The GPIO
    *  interrupt does not track in the active mode, therefore requires to be
    *  cleared by this API.
    *
    *******************************************************************************/
    void UART1_UartSaveConfig(void)
    {
    #if (UART1_UART_RX_WAKEUP_IRQ)
        /* Set SKIP_START if requested (set by default). */
        if (0u != UART1_skipStart)
        {
            UART1_UART_RX_CTRL_REG |= (uint32)  UART1_UART_RX_CTRL_SKIP_START;
        }
        else
        {
            UART1_UART_RX_CTRL_REG &= (uint32) ~UART1_UART_RX_CTRL_SKIP_START;
        }

        /* Clear RX GPIO interrupt status and pending interrupt in NVIC because
        * falling edge on RX line occurs while UART communication in active mode.
        * Enable interrupt: next interrupt trigger should wakeup device.
        */
        UART1_CLEAR_UART_RX_WAKE_INTR;
        UART1_RxWakeClearPendingInt();
        UART1_RxWakeEnableInt();
    #endif /* (UART1_UART_RX_WAKEUP_IRQ) */
    }


    /*******************************************************************************
    * Function Name: UART1_UartRestoreConfig
    ****************************************************************************//**
    *
    *  Disables the RX GPIO interrupt. Until this function is called the interrupt
    *  remains active and triggers on every falling edge of the UART RX line.
    *
    *******************************************************************************/
    void UART1_UartRestoreConfig(void)
    {
    #if (UART1_UART_RX_WAKEUP_IRQ)
        /* Disable interrupt: no more triggers in active mode */
        UART1_RxWakeDisableInt();
    #endif /* (UART1_UART_RX_WAKEUP_IRQ) */
    }


    #if (UART1_UART_RX_WAKEUP_IRQ)
        /*******************************************************************************
        * Function Name: UART1_UART_WAKEUP_ISR
        ****************************************************************************//**
        *
        *  Handles the Interrupt Service Routine for the SCB UART mode GPIO wakeup
        *  event. This event is configured to trigger on a falling edge of the RX line.
        *
        *******************************************************************************/
        CY_ISR(UART1_UART_WAKEUP_ISR)
        {
        #ifdef UART1_UART_WAKEUP_ISR_ENTRY_CALLBACK
            UART1_UART_WAKEUP_ISR_EntryCallback();
        #endif /* UART1_UART_WAKEUP_ISR_ENTRY_CALLBACK */

            UART1_CLEAR_UART_RX_WAKE_INTR;

        #ifdef UART1_UART_WAKEUP_ISR_EXIT_CALLBACK
            UART1_UART_WAKEUP_ISR_ExitCallback();
        #endif /* UART1_UART_WAKEUP_ISR_EXIT_CALLBACK */
        }
    #endif /* (UART1_UART_RX_WAKEUP_IRQ) */
#endif /* (UART1_UART_RX_WAKEUP_IRQ) */


/* [] END OF FILE */

/***************************************************************************//**
* \file UART1_SPI_UART_INT.c
* \version 4.0
*
* \brief
*  This file provides the source code to the Interrupt Service Routine for
*  the SCB Component in SPI and UART modes.
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

#include "UART1_PVT.h"
#include "UART1_SPI_UART_PVT.h"
#include "cyapicallbacks.h"

#if (UART1_SCB_IRQ_INTERNAL)
/*******************************************************************************
* Function Name: UART1_SPI_UART_ISR
****************************************************************************//**
*
*  Handles the Interrupt Service Routine for the SCB SPI or UART modes.
*
*******************************************************************************/
CY_ISR(UART1_SPI_UART_ISR)
{
#if (UART1_INTERNAL_RX_SW_BUFFER_CONST)
    uint32 locHead;
#endif /* (UART1_INTERNAL_RX_SW_BUFFER_CONST) */

#if (UART1_INTERNAL_TX_SW_BUFFER_CONST)
    uint32 locTail;
#endif /* (UART1_INTERNAL_TX_SW_BUFFER_CONST) */

#ifdef UART1_SPI_UART_ISR_ENTRY_CALLBACK
    UART1_SPI_UART_ISR_EntryCallback();
#endif /* UART1_SPI_UART_ISR_ENTRY_CALLBACK */

    if (NULL != UART1_customIntrHandler)
    {
        UART1_customIntrHandler();
    }

    #if(UART1_CHECK_SPI_WAKE_ENABLE)
    {
        /* Clear SPI wakeup source */
        UART1_ClearSpiExtClkInterruptSource(UART1_INTR_SPI_EC_WAKE_UP);
    }
    #endif

    #if (UART1_CHECK_RX_SW_BUFFER)
    {
        if (UART1_CHECK_INTR_RX_MASKED(UART1_INTR_RX_NOT_EMPTY))
        {
            do
            {
                /* Move local head index */
                locHead = (UART1_rxBufferHead + 1u);

                /* Adjust local head index */
                if (UART1_INTERNAL_RX_BUFFER_SIZE == locHead)
                {
                    locHead = 0u;
                }

                if (locHead == UART1_rxBufferTail)
                {
                    #if (UART1_CHECK_UART_RTS_CONTROL_FLOW)
                    {
                        /* There is no space in the software buffer - disable the
                        * RX Not Empty interrupt source. The data elements are
                        * still being received into the RX FIFO until the RTS signal
                        * stops the transmitter. After the data element is read from the
                        * buffer, the RX Not Empty interrupt source is enabled to
                        * move the next data element in the software buffer.
                        */
                        UART1_INTR_RX_MASK_REG &= ~UART1_INTR_RX_NOT_EMPTY;
                        break;
                    }
                    #else
                    {
                        /* Overflow: through away received data element */
                        (void) UART1_RX_FIFO_RD_REG;
                        UART1_rxBufferOverflow = (uint8) UART1_INTR_RX_OVERFLOW;
                    }
                    #endif
                }
                else
                {
                    /* Store received data */
                    UART1_PutWordInRxBuffer(locHead, UART1_RX_FIFO_RD_REG);

                    /* Move head index */
                    UART1_rxBufferHead = locHead;
                }
            }
            while(0u != UART1_GET_RX_FIFO_ENTRIES);

            UART1_ClearRxInterruptSource(UART1_INTR_RX_NOT_EMPTY);
        }
    }
    #endif


    #if (UART1_CHECK_TX_SW_BUFFER)
    {
        if (UART1_CHECK_INTR_TX_MASKED(UART1_INTR_TX_NOT_FULL))
        {
            do
            {
                /* Check for room in TX software buffer */
                if (UART1_txBufferHead != UART1_txBufferTail)
                {
                    /* Move local tail index */
                    locTail = (UART1_txBufferTail + 1u);

                    /* Adjust local tail index */
                    if (UART1_TX_BUFFER_SIZE == locTail)
                    {
                        locTail = 0u;
                    }

                    /* Put data into TX FIFO */
                    UART1_TX_FIFO_WR_REG = UART1_GetWordFromTxBuffer(locTail);

                    /* Move tail index */
                    UART1_txBufferTail = locTail;
                }
                else
                {
                    /* TX software buffer is empty: complete transfer */
                    UART1_DISABLE_INTR_TX(UART1_INTR_TX_NOT_FULL);
                    break;
                }
            }
            while (UART1_SPI_UART_FIFO_SIZE != UART1_GET_TX_FIFO_ENTRIES);

            UART1_ClearTxInterruptSource(UART1_INTR_TX_NOT_FULL);
        }
    }
    #endif

#ifdef UART1_SPI_UART_ISR_EXIT_CALLBACK
    UART1_SPI_UART_ISR_ExitCallback();
#endif /* UART1_SPI_UART_ISR_EXIT_CALLBACK */

}

#endif /* (UART1_SCB_IRQ_INTERNAL) */


/* [] END OF FILE */

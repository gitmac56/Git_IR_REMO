/***************************************************************************//**
* \file UART1_PM.c
* \version 4.0
*
* \brief
*  This file provides the source code to the Power Management support for
*  the SCB Component.
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

#include "UART1.h"
#include "UART1_PVT.h"

#if(UART1_SCB_MODE_I2C_INC)
    #include "UART1_I2C_PVT.h"
#endif /* (UART1_SCB_MODE_I2C_INC) */

#if(UART1_SCB_MODE_EZI2C_INC)
    #include "UART1_EZI2C_PVT.h"
#endif /* (UART1_SCB_MODE_EZI2C_INC) */

#if(UART1_SCB_MODE_SPI_INC || UART1_SCB_MODE_UART_INC)
    #include "UART1_SPI_UART_PVT.h"
#endif /* (UART1_SCB_MODE_SPI_INC || UART1_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(UART1_SCB_MODE_UNCONFIG_CONST_CFG || \
   (UART1_SCB_MODE_I2C_CONST_CFG   && (!UART1_I2C_WAKE_ENABLE_CONST))   || \
   (UART1_SCB_MODE_EZI2C_CONST_CFG && (!UART1_EZI2C_WAKE_ENABLE_CONST)) || \
   (UART1_SCB_MODE_SPI_CONST_CFG   && (!UART1_SPI_WAKE_ENABLE_CONST))   || \
   (UART1_SCB_MODE_UART_CONST_CFG  && (!UART1_UART_WAKE_ENABLE_CONST)))

    UART1_BACKUP_STRUCT UART1_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: UART1_Sleep
****************************************************************************//**
*
*  Prepares the UART1 component to enter Deep Sleep.
*  The “Enable wakeup from Deep Sleep Mode” selection has an influence on this 
*  function implementation:
*  - Checked: configures the component to be wakeup source from Deep Sleep.
*  - Unchecked: stores the current component state (enabled or disabled) and 
*    disables the component. See SCB_Stop() function for details about component 
*    disabling.
*
*  Call the UART1_Sleep() function before calling the 
*  CyPmSysDeepSleep() function. 
*  Refer to the PSoC Creator System Reference Guide for more information about 
*  power management functions and Low power section of this document for the 
*  selected mode.
*
*  This function should not be called before entering Sleep.
*
*******************************************************************************/
void UART1_Sleep(void)
{
#if(UART1_SCB_MODE_UNCONFIG_CONST_CFG)

    if(UART1_SCB_WAKE_ENABLE_CHECK)
    {
        if(UART1_SCB_MODE_I2C_RUNTM_CFG)
        {
            UART1_I2CSaveConfig();
        }
        else if(UART1_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            UART1_EzI2CSaveConfig();
        }
    #if(!UART1_CY_SCBIP_V1)
        else if(UART1_SCB_MODE_SPI_RUNTM_CFG)
        {
            UART1_SpiSaveConfig();
        }
        else if(UART1_SCB_MODE_UART_RUNTM_CFG)
        {
            UART1_UartSaveConfig();
        }
    #endif /* (!UART1_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        UART1_backup.enableState = (uint8) UART1_GET_CTRL_ENABLED;

        if(0u != UART1_backup.enableState)
        {
            UART1_Stop();
        }
    }

#else

    #if (UART1_SCB_MODE_I2C_CONST_CFG && UART1_I2C_WAKE_ENABLE_CONST)
        UART1_I2CSaveConfig();

    #elif (UART1_SCB_MODE_EZI2C_CONST_CFG && UART1_EZI2C_WAKE_ENABLE_CONST)
        UART1_EzI2CSaveConfig();

    #elif (UART1_SCB_MODE_SPI_CONST_CFG && UART1_SPI_WAKE_ENABLE_CONST)
        UART1_SpiSaveConfig();

    #elif (UART1_SCB_MODE_UART_CONST_CFG && UART1_UART_WAKE_ENABLE_CONST)
        UART1_UartSaveConfig();

    #else

        UART1_backup.enableState = (uint8) UART1_GET_CTRL_ENABLED;

        if(0u != UART1_backup.enableState)
        {
            UART1_Stop();
        }

    #endif /* defined (UART1_SCB_MODE_I2C_CONST_CFG) && (UART1_I2C_WAKE_ENABLE_CONST) */

#endif /* (UART1_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: UART1_Wakeup
****************************************************************************//**
*
*  Prepares the UART1 component for Active mode operation after 
*  Deep Sleep.
*  The “Enable wakeup from Deep Sleep Mode” selection has influence on this 
*  function implementation:
*  - Checked: restores the component Active mode configuration.
*  - Unchecked: enables the component if it was enabled before enter Deep Sleep.
*
*  This function should not be called after exiting Sleep.
*
*  \sideeffect
*   Calling the UART1_Wakeup() function without first calling the 
*   UART1_Sleep() function may produce unexpected behavior.
*
*******************************************************************************/
void UART1_Wakeup(void)
{
#if(UART1_SCB_MODE_UNCONFIG_CONST_CFG)

    if(UART1_SCB_WAKE_ENABLE_CHECK)
    {
        if(UART1_SCB_MODE_I2C_RUNTM_CFG)
        {
            UART1_I2CRestoreConfig();
        }
        else if(UART1_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            UART1_EzI2CRestoreConfig();
        }
    #if(!UART1_CY_SCBIP_V1)
        else if(UART1_SCB_MODE_SPI_RUNTM_CFG)
        {
            UART1_SpiRestoreConfig();
        }
        else if(UART1_SCB_MODE_UART_RUNTM_CFG)
        {
            UART1_UartRestoreConfig();
        }
    #endif /* (!UART1_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != UART1_backup.enableState)
        {
            UART1_Enable();
        }
    }

#else

    #if (UART1_SCB_MODE_I2C_CONST_CFG  && UART1_I2C_WAKE_ENABLE_CONST)
        UART1_I2CRestoreConfig();

    #elif (UART1_SCB_MODE_EZI2C_CONST_CFG && UART1_EZI2C_WAKE_ENABLE_CONST)
        UART1_EzI2CRestoreConfig();

    #elif (UART1_SCB_MODE_SPI_CONST_CFG && UART1_SPI_WAKE_ENABLE_CONST)
        UART1_SpiRestoreConfig();

    #elif (UART1_SCB_MODE_UART_CONST_CFG && UART1_UART_WAKE_ENABLE_CONST)
        UART1_UartRestoreConfig();

    #else

        if(0u != UART1_backup.enableState)
        {
            UART1_Enable();
        }

    #endif /* (UART1_I2C_WAKE_ENABLE_CONST) */

#endif /* (UART1_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */

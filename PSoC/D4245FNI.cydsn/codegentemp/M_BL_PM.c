/*******************************************************************************
* File Name: M_BL.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "M_BL.h"

static M_BL_BACKUP_STRUCT  M_BL_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: M_BL_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function applies only to SIO and USBIO pins.
*  It should not be called for GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet M_BL_SUT.c usage_M_BL_Sleep_Wakeup
*******************************************************************************/
void M_BL_Sleep(void)
{
    #if defined(M_BL__PC)
        M_BL_backup.pcState = M_BL_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            M_BL_backup.usbState = M_BL_CR1_REG;
            M_BL_USB_POWER_REG |= M_BL_USBIO_ENTER_SLEEP;
            M_BL_CR1_REG &= M_BL_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(M_BL__SIO)
        M_BL_backup.sioState = M_BL_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        M_BL_SIO_REG &= (uint32)(~M_BL_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: M_BL_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep(). This 
* function applies only to SIO and USBIO pins. It should not be called for
* GPIO or GPIO_OVT pins.
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to M_BL_Sleep() for an example usage.
*******************************************************************************/
void M_BL_Wakeup(void)
{
    #if defined(M_BL__PC)
        M_BL_PC = M_BL_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            M_BL_USB_POWER_REG &= M_BL_USBIO_EXIT_SLEEP_PH1;
            M_BL_CR1_REG = M_BL_backup.usbState;
            M_BL_USB_POWER_REG &= M_BL_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(M_BL__SIO)
        M_BL_SIO_REG = M_BL_backup.sioState;
    #endif
}


/* [] END OF FILE */

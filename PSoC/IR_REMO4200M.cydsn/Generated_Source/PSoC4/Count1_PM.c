/*******************************************************************************
* File Name: Count1_PM.c
* Version 1.0
*
* Description:
*  This file provides Low power mode APIs for Count7 component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Count1.h"


Count1_BACKUP_STRUCT Count1_backup;


/*******************************************************************************
* Function Name: Count1_SaveConfig
********************************************************************************
*
* Summary:
*  This function saves the component configuration and non-retention registers.
*  This function is called by the Count7_Sleep() function.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  Count1_backup - used to save component configuration and non-
*  retention registers before enter sleep mode.
*
*******************************************************************************/
void Count1_SaveConfig(void) 
{
    Count1_backup.count = Count1_COUNT_REG;
}


/*******************************************************************************
* Function Name: Count1_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred API to prepare the component for low power mode
*  operation. The Count7_Sleep() API saves the current component state using
*  Count7_SaveConfig() and disables the counter.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Count1_Sleep(void) 
{
    if(0u != (Count1_AUX_CONTROL_REG & Count1_COUNTER_START))
    {
        Count1_backup.enableState = 1u;
        Count1_Stop();
    }
    else
    {
        Count1_backup.enableState = 0u;
    }

    Count1_SaveConfig();
}


/*******************************************************************************
* Function Name: Count1_RestoreConfig
********************************************************************************
*
* Summary:
*  This function restores the component configuration and non-retention
*  registers. This function is called by the Count7_Wakeup() function.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  Count1_backup - used to save component configuration and
*  non-retention registers before exit sleep mode.
*
*******************************************************************************/
void Count1_RestoreConfig(void) 
{
    Count1_COUNT_REG = Count1_backup.count;
}


/*******************************************************************************
* Function Name: Count1_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred API to restore the component to the state when
*  Count7_Sleep() was called. The Count7_Wakeup() function calls the
*  Count7_RestoreConfig() function to restore the configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Count1_Wakeup(void) 
{
    Count1_RestoreConfig();

    /* Restore enable state */
    if (Count1_backup.enableState != 0u)
    {
        Count1_Enable();
    }
}


/* [] END OF FILE */

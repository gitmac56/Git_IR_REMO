/*******************************************************************************
* File Name: Ch0.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Ch0_ALIASES_H) /* Pins Ch0_ALIASES_H */
#define CY_PINS_Ch0_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Ch0_0			(Ch0__0__PC)
#define Ch0_0_PS		(Ch0__0__PS)
#define Ch0_0_PC		(Ch0__0__PC)
#define Ch0_0_DR		(Ch0__0__DR)
#define Ch0_0_SHIFT	(Ch0__0__SHIFT)
#define Ch0_0_INTR	((uint16)((uint16)0x0003u << (Ch0__0__SHIFT*2u)))

#define Ch0_INTR_ALL	 ((uint16)(Ch0_0_INTR))


#endif /* End Pins Ch0_ALIASES_H */


/* [] END OF FILE */

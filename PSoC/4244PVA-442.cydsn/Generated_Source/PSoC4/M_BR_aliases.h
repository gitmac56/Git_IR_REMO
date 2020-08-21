/*******************************************************************************
* File Name: M_BR.h  
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

#if !defined(CY_PINS_M_BR_ALIASES_H) /* Pins M_BR_ALIASES_H */
#define CY_PINS_M_BR_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define M_BR_0			(M_BR__0__PC)
#define M_BR_0_PS		(M_BR__0__PS)
#define M_BR_0_PC		(M_BR__0__PC)
#define M_BR_0_DR		(M_BR__0__DR)
#define M_BR_0_SHIFT	(M_BR__0__SHIFT)
#define M_BR_0_INTR	((uint16)((uint16)0x0003u << (M_BR__0__SHIFT*2u)))

#define M_BR_INTR_ALL	 ((uint16)(M_BR_0_INTR))


#endif /* End Pins M_BR_ALIASES_H */


/* [] END OF FILE */

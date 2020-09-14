/*******************************************************************************
* File Name: Ch0.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Ch0_H) /* Pins Ch0_H */
#define CY_PINS_Ch0_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Ch0_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} Ch0_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Ch0_Read(void);
void    Ch0_Write(uint8 value);
uint8   Ch0_ReadDataReg(void);
#if defined(Ch0__PC) || (CY_PSOC4_4200L) 
    void    Ch0_SetDriveMode(uint8 mode);
#endif
void    Ch0_SetInterruptMode(uint16 position, uint16 mode);
uint8   Ch0_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Ch0_Sleep(void); 
void Ch0_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Ch0__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Ch0_DRIVE_MODE_BITS        (3)
    #define Ch0_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Ch0_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Ch0_SetDriveMode() function.
         *  @{
         */
        #define Ch0_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Ch0_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Ch0_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Ch0_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Ch0_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Ch0_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Ch0_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Ch0_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Ch0_MASK               Ch0__MASK
#define Ch0_SHIFT              Ch0__SHIFT
#define Ch0_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Ch0_SetInterruptMode() function.
     *  @{
     */
        #define Ch0_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Ch0_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Ch0_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Ch0_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Ch0__SIO)
    #define Ch0_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Ch0__PC) && (CY_PSOC4_4200L)
    #define Ch0_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Ch0_USBIO_DISABLE              ((uint32)(~Ch0_USBIO_ENABLE))
    #define Ch0_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Ch0_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Ch0_USBIO_ENTER_SLEEP          ((uint32)((1u << Ch0_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Ch0_USBIO_SUSPEND_DEL_SHIFT)))
    #define Ch0_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Ch0_USBIO_SUSPEND_SHIFT)))
    #define Ch0_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Ch0_USBIO_SUSPEND_DEL_SHIFT)))
    #define Ch0_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Ch0__PC)
    /* Port Configuration */
    #define Ch0_PC                 (* (reg32 *) Ch0__PC)
#endif
/* Pin State */
#define Ch0_PS                     (* (reg32 *) Ch0__PS)
/* Data Register */
#define Ch0_DR                     (* (reg32 *) Ch0__DR)
/* Input Buffer Disable Override */
#define Ch0_INP_DIS                (* (reg32 *) Ch0__PC2)

/* Interrupt configuration Registers */
#define Ch0_INTCFG                 (* (reg32 *) Ch0__INTCFG)
#define Ch0_INTSTAT                (* (reg32 *) Ch0__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Ch0_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Ch0__SIO)
    #define Ch0_SIO_REG            (* (reg32 *) Ch0__SIO)
#endif /* (Ch0__SIO_CFG) */

/* USBIO registers */
#if !defined(Ch0__PC) && (CY_PSOC4_4200L)
    #define Ch0_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Ch0_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Ch0_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Ch0_DRIVE_MODE_SHIFT       (0x00u)
#define Ch0_DRIVE_MODE_MASK        (0x07u << Ch0_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Ch0_H */


/* [] END OF FILE */

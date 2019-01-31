/*
 SPC5 RLA - Copyright (C) 2015 STMicroelectronics

 Licensed under the Apache License, Version 2.0 (the "License").
 You may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

/**
 * @file    intc.h
 * @brief   INTC module header.
 *
 * @addtogroup PLATFORM
 * @{
 */

#ifndef _INTC_H_
#define _INTC_H_

/*===========================================================================*/
/* Module constants.                                                         */
/*===========================================================================*/

/**
 * @brief   INTC base address.
 */
#define INTC_BASE                           0xFFF48000U

/*lint -e9048 */
/* The following macros are include in assembler file. So suffixs 'U' or 'UL'
   are not allowed.*/
/**
 * @brief   Interrupt Acknowledge register base address.
 */
#define INTC_IACKR_BASE                     0xFFF48010

/**
 * @brief   End of Interrupt register base address.
 */
#define INTC_EOIR_BASE                      0xFFF48018
/*lint +e9048 */

/**
 * @brief   INTC PSR register definitions
 */
/* TODO    Some platforms support more than 16 priority levels.*/
#define INTC_PSR_PRIO_MASK                  0x000F

/**
 * @brief   Core selection macro for PSR register.
 */
#define INTC_PSR_CORE0                      0x00

/**
 * @brief   Main Core selection macro for PSR register.
 */
#define INTC_PSR_MAINCORE                   INTC_PSR_CORE0

/*===========================================================================*/
/* Module pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Module data structures and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Module macros.                                                            */
/*===========================================================================*/

/**
 * @brief   INTC-related macros
 */
#define INTC_BCR                            (*((volatile uint32_t *)(INTC_BASE + 0U)))
#define INTC_CPR(n)                         (*((volatile uint32_t *)(INTC_BASE + 8U + ((uint8_t)(n) * sizeof (uint32_t)))))
#define INTC_IACKR(n)                       (*((volatile uint32_t *)(INTC_BASE + 0x10U + ((uint8_t)(n) * sizeof (uint32_t)))))
#define INTC_EOIR(n)                        (*((volatile uint32_t *)(INTC_BASE + 0x18U + ((uint8_t)(n) * sizeof (uint32_t)))))
#define INTC_PSR(n)                         (*((volatile uint8_t *)(INTC_BASE + 0x40U + ((uint16_t)(n) * sizeof (uint8_t)))))

/**
 * @brief   PSR register content helper
 */
#define INTC_PSR_ENABLE(cores, prio)        ((uint8_t)(cores) | (uint8_t)(prio))


/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

/*===========================================================================*/
/* Module inline functions.                                                  */
/*===========================================================================*/

#endif /* _INTC_H_ */

/** @} */

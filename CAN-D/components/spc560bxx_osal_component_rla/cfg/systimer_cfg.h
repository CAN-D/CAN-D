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
 * @file    systimer_cfg.h
 * @brief   OSAL configuration macros and structures.
 *
 * @addtogroup OSAL
 * @{
 */

#ifndef _SYSTIMER_CFG_H_
#define _SYSTIMER_CFG_H_

#include "platform.h"

/*===========================================================================*/
/* Module constants.                                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Module pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @brief   System Timer (PIT channel 0) IRQ priority.
 * @note    PIT channel 0 is allocated permanently for system tick
 *          generation.
 */
#if !defined(SPC5_SYSTIMER_IRQ_PRIORITY) || defined(__DOXYGEN__)
#define SPC5_SYSTIMER_IRQ_PRIORITY          4
#endif

/**
 * @brief   Core on which the system timer (PIT channel 0) interrupts are
 *          dispatched.
 */
#if !defined(SPC5_SYSTIMER_CORE) || defined(__DOXYGEN__)
#define SPC5_SYSTIMER_CORE                  INTC_PSR_MAINCORE
#endif

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Module data structures and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Module macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#endif /* _SYSTIMER_CFG_H_ */

/** @} */

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
 * @file    osal_cfg.h
 * @brief   OSAL configuration macros and structures.
 *
 * @addtogroup OSAL
 * @{
 */

#ifndef _OSAL_CFG_H_
#define _OSAL_CFG_H_

/*===========================================================================*/
/* Module constants.                                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Module pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @brief   FreeRTOS Operating System enable switch.
 * @details If set to @p TRUE the support for FreeRTOS Operating System is 
 *          included.
 */
#define OSAL_FREERTOS_ENABLE                TRUE

/**
 * @brief   Operating System enable switch.
 * @details It is set to @p TRUE if one of the supported Operating System is 
 *          included.
 */
#if (OSAL_FREERTOS_ENABLE == TRUE)
#define OSAL_OS_ENABLE                      TRUE
#else
#define OSAL_OS_ENABLE                      FALSE
#endif

/**
 * @brief   IRQ preemption enable switch.
 * @details If set to @p TRUE the IRQ preemption is enabled.
 */
#if !defined(OSAL_ENABLE_IRQ_PREEMPTION)
#define OSAL_ENABLE_IRQ_PREEMPTION          FALSE
#endif

/**
 * @brief   System Timer enable.
 * @details If set to @p TRUE the System Timer is enabled.
 */
#if !defined(OSAL_SYSTIMER_ENABLE) || defined(__DOXYGEN__)
#define OSAL_SYSTIMER_ENABLE                TRUE
#endif

/**
 * @brief   System timer tick frequency [Hz].
 * @details Number of system timer ticks in a second.
 */
#if !defined(OSAL_SYSTIMER_TICK_FREQ_HZ) || defined(__DOXYGEN__)
#define OSAL_SYSTIMER_TICK_FREQ_HZ          1000
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

#endif /* _OSAL_CFG_H_ */

/** @} */

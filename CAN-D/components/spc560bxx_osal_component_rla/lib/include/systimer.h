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
 * @file    systimer.h
 * @brief   OSAL module header.
 *
 * @addtogroup OSAL
 * @{
 */

#ifndef _SYSTIMER_H_
#define _SYSTIMER_H_

#include "irq.h"
#include "clock.h"
#include "platform.h"

/*===========================================================================*/
/* Module constants.                                                         */
/*===========================================================================*/

/**
 * @brief   System Timer (PIT channel 0) IRQ handler.
 * @note    PIT channel 0 is allocated permanently for system tick
 *          generation.
 */
#if !defined(OSAL_SYSTIMER_IRQ_HANDLER) || defined(__DOXYGEN__)
#define SPC5_SYSTIMER_IRQ_HANDLER           SPC_PIT_CH0_HANDLER
#endif

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

/*===========================================================================*/
/* Inline functions.                                                         */
/*===========================================================================*/

/*===========================================================================*/
/* IRQ Handlers                                                              */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/
#ifdef __cplusplus
extern "C" {
#endif
  void sysTimeSetup(uint32_t ticks_per_sec);
  void sysTimeReset(void);
#ifdef __cplusplus
}
#endif
#endif /* _SYSTIMER_H_ */

/** @} */

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
 * @file    irq.c
 * @brief   IRQ module code.
 *
 * @addtogroup IRQ
 * @{
 */

#include "irq.h"

/*===========================================================================*/
/* Module local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Module exported variables.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Module local types.                                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Module local variables.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Module local functions.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Module exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   IRQ module initialization.
 *
 * @api
 */
void irqInit(void) {

  irq_cfg_init();
  
  /* Method of accessing memory-mapped registers at fixed addresses does not 
     comply with MISRA C because it involves converting an integer to a 
	 pointer. */
  /*lint -e9033 */
  /* INTC initialization, software vector mode, 4 bytes vectors, starting
     at priority 0.*/
     
  INTC_BCR = 0;

  /* Configure IRQ for main core.*/
  INTC_CPR(MAIN_CORE)   = 0;
  INTC_IACKR(MAIN_CORE) = (uint32_t)_vectors;

#if defined(BOOT_CORE0) && (BOOT_CORE0 == 1)
  /* Configure IRQ for secondary core 0.*/
  INTC_CPR(0)   = 0;
  INTC_IACKR(0) = (uint32_t)_vectors;
#endif /* BOOT_CORE0 */

#if defined(BOOT_CORE1) && (BOOT_CORE1 == 1)
  /* Configure IRQ for secondary core 1.*/
  INTC_CPR(1)   = 0;
  INTC_IACKR(1) = (uint32_t)_vectors;
#endif /* BOOT_CORE1 */

#if defined(BOOT_CORE2) && (BOOT_CORE2 == 1)
  /* Configure IRQ for secondary core 2.*/
  INTC_CPR(2)   = 0;
  INTC_IACKR(2) = (uint32_t)_vectors;
#endif /* BOOT_CORE2 */

  /*lint +e9033 */
}

/**
 * @brief   System halt 
 *
 * @api
 */

#if !defined(__DOXYGEN__)
__attribute__((weak, noreturn))
#endif
void irqSysHalt(void) {

  irqIsrDisable();
  for ( ; ; ) {
  }
}

/** @} */

/*
    SPC5 RLA - Copyright (C) 2017 STMicroelectronics

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
 * @file    i2c_lld_cfg.h
 * @brief   I2C Driver configuration macros and structures.
 *
 * @addtogroup I2C
 * @{
 */

#ifndef _I2C_LLD_CFG_H_
#define _I2C_LLD_CFG_H_

#if (LLD_USE_I2C == TRUE) || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/
#define I2C_0_DIVIDER 191
#define I2C_0_MASTER 1U
#define I2C_0_IRQ_DRIVEN 0U

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#endif /* LLD_USE_I2C */

#endif /* _I2C_LLD_CFG_H_ */

/** @} */

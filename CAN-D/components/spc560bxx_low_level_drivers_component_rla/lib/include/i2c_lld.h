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
 * @file    i2c_lld.h
 * @brief   SPC5xx I2C low level driver header.
 *
 * @addtogroup I2C
 * @{
 */
#ifndef _I2C_LLD_H_
#define _I2C_LLD_H_

#include "spc5_lld.h"
#include "lldconf.h"

#if (LLD_USE_I2C == TRUE) || defined(__DOXYGEN__)

/*******************************************************************************
* Includes
*******************************************************************************/

/*******************************************************************************
* Constants
*******************************************************************************/

/*******************************************************************************
* Macros 
*******************************************************************************/

/*******************************************************************************
* Types
*******************************************************************************/
/**
 * @brief    I2C computation results
 */
typedef enum
{
	I2C_NO_ERROR,					/**< @brief   no errors. */
	I2C_ERROR_TRANSFER_IN_PROGRESS,	/**< @brief   transfer is on going. */
	I2C_ERROR_NO_ACK,				/**< @brief   acknowledge not received. */
	I2C_ERROR_BUS_BUSY,				/**< @brief   bus is busy. */
	I2C_ERROR_ARBITRATION_LOST,		/**< @brief   arbitration lost notified. */	
	I2C_ERROR_INVALID_ADDRESS,		/**< @brief   slave device not found. */
	I2C_ERROR_INVALID_ARGUMENT,		/**< @brief   wrong input argument. */
	I2C_ERROR_INVALID_STATE			/**< @brief   invalid state machine sequence. */
} i2c_result_t;

/*******************************************************************************
* Global variables
*******************************************************************************/
   
/*******************************************************************************
* Global functions
*******************************************************************************/
void i2c_lld_init(void);
void i2c_lld_deinit(void);
i2c_result_t i2c_lld_start(uint8_t freq_divider);
i2c_result_t i2c_lld_stop(void);
i2c_result_t i2c_lld_write(uint8_t dev_addr, uint16_t reg_addr,
							uint8_t *data, uint8_t ndata_bytes);
i2c_result_t i2c_lld_read(uint8_t dev_addr, uint16_t reg_addr,
							uint8_t *data, uint8_t ndata_bytes);

#endif
#endif
/** @} */

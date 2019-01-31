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
#include "i2c_lld.h"
#include "i2c_lld_cfg.h"

#if (LLD_USE_I2C == TRUE) || defined(__DOXYGEN__)

#if (I2C_0_MASTER != 1U)
#error "I2C driver not ready to be used as slave device"
#endif

/*******************************************************************************
* External objects
*******************************************************************************/

/*******************************************************************************
* Global variables
*******************************************************************************/

/*******************************************************************************
* Constants and macros
*******************************************************************************/
#define I2C_WRITE 0U
#define I2C_READ  1U

/*******************************************************************************
* Local types
*******************************************************************************/
/* 
 * I2C state machine
 */
typedef enum 
{ 
	I2C_WRITE_DATA = 0x10,
	I2C_SEND_REG_ADDRESS_HIGH,
	I2C_SEND_REG_ADDRESS_LOW,
	I2C_REPEATED_START,
	I2C_READ_DUMMY_DATA,
	I2C_TRANSFER_IN_PROGRESS,
	I2C_TRANSFER_COMPLETE
} i2c_state_t;

typedef union
{
    uint16_t W;
    struct{
        uint8_t H;
        uint8_t L;
    } B;
} i2c_addr_t;

/*******************************************************************************
* Local function prototypes
*******************************************************************************/

/*******************************************************************************
* Local variables
*******************************************************************************/
static struct {
	uint8_t		init;
	uint8_t		dev_addr;
	uint8_t 	operation;
	uint8_t 	ndata_bytes;
	uint8_t 	*data;
	i2c_addr_t		reg_addr;
#if (I2C_0_IRQ_DRIVEN == 1U)
	volatile
#endif
	i2c_state_t  	state;
	i2c_result_t	result;
} i2c;

/*******************************************************************************
* Local functions
*******************************************************************************/
static void i2c_lld_irq_handler(void)
{
	uint8_t status = I2C_0.IBSR.R;
	
	if(I2C_0.IBCR.B.MS == 1U)
	{
		/* Master mode selected */
		if(I2C_0.IBCR.B.TX == 1U)
		{
			/* Transmit mode selected */
        	if((status & 1U) == 0U)
    		{
				/* Acknowledge received */
    			switch(i2c.state)
    			{
    				case  I2C_SEND_REG_ADDRESS_HIGH:
    				{
							/* Send upper byte of word address */
	        				I2C_0.IBDR.R = i2c.reg_addr.B.H;
	        				i2c.state = I2C_SEND_REG_ADDRESS_LOW;
	        		}
	        		break;
	        		case  I2C_SEND_REG_ADDRESS_LOW:
    				{
							/* Send lower byte of word address */
	        				I2C_0.IBDR.R = i2c.reg_addr.B.L;
	        				
	        				if(i2c.operation == I2C_WRITE)
								{ i2c.state = I2C_WRITE_DATA; }
	        				else
								{ i2c.state = I2C_REPEATED_START; }
	        	   	}
    				break;
    				
    				case I2C_REPEATED_START:
    				{
    					I2C_0.IBCR.B.RSTA = 1;
						I2C_0.IBDR.R = i2c.dev_addr | I2C_READ;
						i2c.state = I2C_READ_DUMMY_DATA;
    				}
    				break;
    				case I2C_READ_DUMMY_DATA:
    				{
    					I2C_0.IBCR.B.TX = 0;
						if(i2c.ndata_bytes == 1U) {
							I2C_0.IBCR.B.NOACK = 1;
						}
						/* dummy initiates next byte data receiving */
						if (I2C_0.IBDR.R == 0U)	{}
					}
    				break;
    				case I2C_WRITE_DATA:
    				{
    					if(i2c.ndata_bytes != 0U)
    					{
							/* Write next bytes */
    						I2C_0.IBDR.R = *i2c.data++;
    						i2c.ndata_bytes--;
    					}
		        		else
			        	{
							/* I2C transfer completed with success */
			        		I2C_0.IBCR.B.MS = 0;
			        		i2c.state = I2C_TRANSFER_COMPLETE;
			        		i2c.result = I2C_NO_ERROR;
			        		while (I2C_0.IBSR.B.IBB == 1U) {}
			        	}
    				}
    			    break;
					case I2C_TRANSFER_COMPLETE:
					case I2C_TRANSFER_IN_PROGRESS:
					break;
					default:
					;
    			}
    		}
    		else
    		{
    			/* No response from the slave. */
    			I2C_0.IBCR.B.MS = 0;
    			i2c.state = I2C_TRANSFER_COMPLETE;
    			i2c.result = I2C_ERROR_NO_ACK;
    		}
		}
		else
		{
			/* Receive mode selected */
			if((i2c.ndata_bytes - 2U) == 0U)
			{
				 /* NOACK next received byte */
				I2C_0.IBCR.B.NOACK = 1;
			}
			if((i2c.ndata_bytes - 1U) == 0U)
			{
				/* Reset Control Register */
				I2C_0.IBCR.B.MS = 0;
				I2C_0.IBCR.B.NOACK = 0;
				i2c.state = I2C_TRANSFER_COMPLETE;
				i2c.result = I2C_NO_ERROR;
				while (I2C_0.IBSR.B.IBB == 1U) {}
			}
			/* Store data read */
			*(i2c.data++) = I2C_0.IBDR.R;
			i2c.ndata_bytes--;
		}
	}
	else
	{
		/* Slave mode selected */
		if ((status & 16U) == 16U)
		{
			/* Transaction finished with error */
			i2c.state = I2C_TRANSFER_COMPLETE;
			i2c.result = I2C_ERROR_ARBITRATION_LOST;
			/* Write 1 to clear as per specification*/
			I2C_0.IBSR.R = 0x10;
		}
	}
	
	/* Clear IBIF Bus Interrupt flag */
	I2C_0.IBSR.R = 0x2; 
}

/*******************************************************************************
* Global functions
*******************************************************************************/
/**
 * @brief   Enable I2C system peripheral clock
 *
 * @api
 */
void i2c_lld_init(void)
{
	SPC5_I2C_ENABLE_CLOCK();

#if (I2C_0_IRQ_DRIVEN == 1U)
	INTC_PSR(SPC5_I2C_INT_NUMBER) = SPC5_I2C_IRQ_PRIORITY;
#endif

	i2c.init = 1;
}

/**
 * @brief   Disable I2C system peripheral clock
 *
 * @api
 */
void i2c_lld_deinit(void)
{
	i2c.init = 0;
	SPC5_I2C_DISABLE_CLOCK();
}

/**
 * @brief		I2C driver initialization. The module will be initialized with
 *				a default frequency divider and can be changed with a new 
 *				reinitialization value.
 *
 * @param[in]	freq_divider	frequence divider. Valid range is [0x00,0xBF].
 *
 * @return		operation result.
 *
 * @api
 */
i2c_result_t i2c_lld_start(uint8_t freq_divider)
{
	if (i2c.init != 1U) {
		return I2C_ERROR_INVALID_STATE;
	}
	
	/* I2C Bus module cannot be enabled or clock changing 
		in the middle of a byte transfer */
	if (i2c.state == I2C_TRANSFER_IN_PROGRESS) {
		return I2C_ERROR_TRANSFER_IN_PROGRESS;
	}
	
	if (freq_divider > 191U) {
		return I2C_ERROR_INVALID_ARGUMENT;
	}
	
	if (freq_divider == 0U) {
		I2C_0.IBFD.B.IBC = I2C_0_DIVIDER;
	} else {
		I2C_0.IBFD.B.IBC = freq_divider;
	}
	
	/* Clear IBAL, IBIF flags and enable module */
  	I2C_0.IBAD.R = 0x00;
  	I2C_0.IBSR.R = 0x12;
 	I2C_0.IBCR.B.IBIE = I2C_0_IRQ_DRIVEN;
    I2C_0.IBCR.B.MDIS =0;
	
	i2c.init += 1U;
	i2c.state = I2C_TRANSFER_COMPLETE;
	return I2C_NO_ERROR;
}

/**
 * @brief   Disable I2C module.
 *
 * @return		operation result.
 *
 * @api
 */
i2c_result_t i2c_lld_stop(void)
{
	if (i2c.init == 2U) {
		/* Clear IBAL, IBIF flags and module disable */
		I2C_0.IBSR.R = 0x12;
		I2C_0.IBCR.B.MDIS = 1;
		i2c.init -= 1U;
		return I2C_NO_ERROR;
	}
	return I2C_ERROR_INVALID_STATE;
}

/**
 * @brief   I2C Write routine
 *
 * @param[in]	dev_addr	device to address. Valid range [0x08,0x77].
 * @param[in]	reg_addr	internal device register to address.
 * @param[in]	data		pointer to data buffer to send.
 * @param[in]	ndata_bytes	data length in bytes.
 *
 * @return		operation result.
 *
 * @api
 */
i2c_result_t i2c_lld_write(uint8_t dev_addr, uint16_t reg_addr,
						uint8_t *data, uint8_t ndata_bytes)
{
	if (i2c.init != 2U) {
		return I2C_ERROR_INVALID_STATE;
	}
	
	if (ndata_bytes == 0U) {
		return I2C_NO_ERROR;
	}
	
	/* Check for valid address */
	if ((dev_addr == 0U) || ((dev_addr & 1U) == 1U)) {
		return I2C_ERROR_INVALID_ADDRESS;
	}

	if (data == NULL) {
		return I2C_ERROR_INVALID_ARGUMENT;
	}
	
	if(i2c.state == I2C_TRANSFER_COMPLETE) {
		/* Set i2c context */
		i2c.dev_addr = dev_addr | I2C_WRITE;
		i2c.reg_addr.W = reg_addr;
		i2c.data = data;
		i2c.ndata_bytes = ndata_bytes;
		
		if(I2C_0.IBSR.B.IBB == 1U) {
			i2c.result = I2C_ERROR_BUS_BUSY;
			return i2c.result;
		}

		if ((reg_addr & 0xFF00U) != 0U) {
			i2c.state = I2C_SEND_REG_ADDRESS_HIGH;
		} else {
			i2c.state = I2C_SEND_REG_ADDRESS_LOW;
		}
		
	    i2c.operation = I2C_WRITE;
	    i2c.result = I2C_ERROR_TRANSFER_IN_PROGRESS;
    	
		/* Transmit the device address */
	    I2C_0.IBCR.B.MS = I2C_0_MASTER;
	    I2C_0.IBCR.B.TX = 1;
	    I2C_0.IBDR.R = i2c.dev_addr;
	    
		if(I2C_0.IBCR.B.IBIE == 0U)	{
			/* No interrupt driven is used */
			while (i2c.state != I2C_TRANSFER_COMPLETE) {
				/* Waiting for I-bus Interrupt Flag is set */
				while (I2C_0.IBSR.B.IBIF == 0U)
					{};
				i2c_lld_irq_handler();
			}
		}
	}
    
#if (I2C_0_IRQ_DRIVEN == 1U)
	while (i2c.state != I2C_TRANSFER_COMPLETE);
#endif

    return(i2c.result);

}

/**
 * @brief   	I2C read routine
 *
 * @param[in]	dev_addr	device to address. Valid range [0x08,0x77].
 * @param[in]	reg_addr	internal device register to address.
 * @param[in]	ndata_bytes	data length in bytes.
 * @param[out]	data		data buffer to receive.
 *
 * @return		operation result.
 *
 * @api
 */
i2c_result_t i2c_lld_read(uint8_t dev_addr, uint16_t reg_addr,
						uint8_t *data, uint8_t ndata_bytes)
{
	if (i2c.init != 2U) {
		return I2C_ERROR_INVALID_STATE;
	}

	if (ndata_bytes == 0U) {
		return I2C_NO_ERROR;
	}
	
	/* Check for valid address */
	if ((dev_addr == 0U) || ((dev_addr & 1U) == 1U)) {
		return I2C_ERROR_INVALID_ADDRESS;
	}
	
	if (data == NULL) {
		return I2C_ERROR_INVALID_ARGUMENT;
	}
	
	if(i2c.state == I2C_TRANSFER_COMPLETE) {
		/* Set i2c context */
		i2c.dev_addr = dev_addr | I2C_WRITE;
		i2c.reg_addr.W = reg_addr;
		i2c.data = data;
		i2c.ndata_bytes = ndata_bytes;
		
		if(I2C_0.IBSR.B.IBB == 1U) {
			i2c.result = I2C_ERROR_BUS_BUSY;
			return i2c.result;
		}
		
		if ((reg_addr & 0xFF00U) != 0U) {
			i2c.state = I2C_SEND_REG_ADDRESS_HIGH;
		} else {
			i2c.state = I2C_SEND_REG_ADDRESS_LOW;
		}
		
	    i2c.operation = I2C_READ;
	    i2c.result = I2C_ERROR_TRANSFER_IN_PROGRESS;
		
		/* Transmit the device address */
	    I2C_0.IBCR.B.MS = I2C_0_MASTER;
	    I2C_0.IBCR.B.TX = 1;
	    I2C_0.IBDR.R = i2c.dev_addr;
	    
		if(I2C_0.IBCR.B.IBIE == 0U) {
			/* No interrupt driven is used */
			while (i2c.state != I2C_TRANSFER_COMPLETE) {
				/* Waiting for I-bus Interrupt Flag is set */
				while (I2C_0.IBSR.B.IBIF == 0U)
					{};
				i2c_lld_irq_handler();
			}
		}
	}
    
#if (I2C_0_IRQ_DRIVEN == 1U)
	while (i2c.state != I2C_TRANSFER_COMPLETE);
#endif

    return(i2c.result);
}

#if (I2C_0_IRQ_DRIVEN == 1U)
IRQ_HANDLER(SPC5_I2C_HANDLER) {
	IRQ_PROLOGUE();
	osalEnterCriticalFromISR();

	i2c_lld_irq_handler();

	osalExitCriticalFromISR();
	IRQ_EPILOGUE();
}
#endif
#endif /* LLD_USE_I2C */

/**
  ******************************************************************************
  * @file    stm32302c_custom.c
  * @author  Mark Griffith
  * @brief   This file provides firmware functions to manage Leds, push-buttons,  
 *           COM ports, SD card and temperature sensor available on the
 *           CAN-D custom board.
  ******************************************************************************
  */

#include "stm32302c_custom.h"
#include "stm32302c_custom_sd.h"
#include "stm32f302xc.h"
#include <string.h>

/* LINK SD Card */
#define SD_DUMMY_BYTE 0xFF
#define SD_NO_RESPONSE_EXPECTED 0x80

/**
 * @brief LED variables
 */
GPIO_TypeDef* LED_PORT[LEDn] = { LED1_GPIO_PORT,
    LED2_GPIO_PORT,
    LED3_GPIO_PORT };

const uint16_t LED_PIN[LEDn] = { LED1_PIN,
    LED2_PIN,
    LED3_PIN };

/**
 * @brief BUTTON variables
 */
GPIO_TypeDef* BUTTON_PORT[BUTTONn] = { LOG_BUTTON_GPIO_PORT,
    MARK_BUTTON_GPIO_PORT };

const uint16_t BUTTON_PIN[BUTTONn] = { LOG_BUTTON_PIN,
    MARK_BUTTON_PIN };

const uint16_t BUTTON_IRQn[BUTTONn] = { LOG_BUTTON_EXTI_IRQn,
    MARK_BUTTON_EXTI_IRQn };

/**
 * @brief COM variables
 */
#if defined(HAL_UART_MODULE_ENABLED)

/* UART handle. */
UART_HandleTypeDef huart;

/* UART com functions */
static void UARTx_Init(void);
static void UARTx_MspInit(UART_HandleTypeDef* huart);
static void UARTx_WriteChar(char Character);

/* Link functions for GPS peripheral over UART */
void GPS_IO_Init(void);
void GPS_IO_WriteString(char Msg[]);

/* De-init function called in HAL_UART_DeInit() */
void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle);

#endif /* HAL_UART_MODULE_ENABLED) */

#if defined(HAL_SPI_MODULE_ENABLED)

uint32_t SpixTimeout = CUSTOM_SPIx_TIMEOUT_MAX; /*<! Value of Timeout when SPI communication fails */
SPI_HandleTypeDef hspi;

/* SPIx bus functions */
void SPIx_Init(void);
void SPIx_Write(uint8_t Value);
uint32_t SPIx_Read(void);
void SPIx_Error(void);
void SPIx_MspInit(SPI_HandleTypeDef* hspi);

/* Link functions for SD Card peripheral over SPI */
void SD_IO_Init(void);
HAL_StatusTypeDef SD_IO_WriteCmdLegacy(uint8_t Cmd, uint32_t Arg, uint8_t Crc, uint8_t Response);
SD_CmdTypeDef SD_IO_WriteCmd(uint8_t Cmd, uint32_t Arg, uint8_t Crc, uint8_t Response);
HAL_StatusTypeDef SD_IO_WaitResponse(uint8_t Response);
uint8_t SD_IO_ReadData();
void SD_IO_WriteDummy(void);
void SD_IO_WriteByte(uint8_t Data);
uint8_t SD_IO_ReadByte(void);

#endif /* HAL_SPI_MODULE_ENABLED */

/**
  * @brief  Configures LED GPIO.
  * @param  Led Specifies the Led to be configured. 
  *   This parameter can be one of following parameters:
  *     @arg LED1
  *     @arg LED2
  *     @arg LED3
  *     @arg LED4
  * @retval None
  */
void BSP_LED_Init(Led_TypeDef Led)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    /* Enable the GPIO_LED clock */
    LEDx_GPIO_CLK_ENABLE(Led);

    /* Configure the GPIO_LED pin */
    GPIO_InitStruct.Pin = LED_PIN[Led];
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

    HAL_GPIO_Init(LED_PORT[Led], &GPIO_InitStruct);

    HAL_GPIO_WritePin(LED_PORT[Led], LED_PIN[Led], GPIO_PIN_RESET);
}

/**
  * @brief  Turns selected LED On.
  * @param  Led Specifies the Led to be set on. 
  *   This parameter can be one of following parameters:
  *     @arg LED1
  *     @arg LED2
  *     @arg LED3
  *     @arg LED4  
  * @retval None
  */
void BSP_LED_On(Led_TypeDef Led)
{
    HAL_GPIO_WritePin(LED_PORT[Led], LED_PIN[Led], GPIO_PIN_SET);
}

/**
  * @brief  Turns selected LED Off.
  * @param  Led Specifies the Led to be set off. 
  *   This parameter can be one of following parameters:
  *     @arg LED1
  *     @arg LED2
  *     @arg LED3
  *     @arg LED4 
  * @retval None
  */
void BSP_LED_Off(Led_TypeDef Led)
{
    HAL_GPIO_WritePin(LED_PORT[Led], LED_PIN[Led], GPIO_PIN_RESET);
}

/**
  * @brief  Toggles the selected LED.
  * @param  Led Specifies the Led to be toggled. 
  *   This parameter can be one of following parameters:
  *     @arg LED1
  *     @arg LED2
  *     @arg LED3
  *     @arg LED4  
  * @retval None
  */
void BSP_LED_Toggle(Led_TypeDef Led)
{
    HAL_GPIO_TogglePin(LED_PORT[Led], LED_PIN[Led]);
}

/**
  * @brief  Configures push button GPIO and EXTI Line.
  * @param  Button Button to be configured.
  *   This parameter can be one of the following values: 
  *     @arg BUTTON_KEY   : Key Push Button 
  * @param  Button_Mode Button mode requested.
  *   This parameter can be one of the following values:   
  *     @arg BUTTON_MODE_GPIO: Button will be used as simple IO 
  *     @arg BUTTON_MODE_EXTI: Button will be connected to EXTI line
  *                            with interrupt generation capability
  * @retval None
  */
void BSP_PB_Init(Button_TypeDef Button, ButtonMode_TypeDef Button_Mode)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    /* Enable the corresponding Push Button clock */
    BUTTONx_GPIO_CLK_ENABLE(Button);

    /* Configure Push Button pin as input */
    GPIO_InitStruct.Pin = BUTTON_PIN[Button];
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

    if (Button_Mode == BUTTON_MODE_GPIO) {
        /* Configure Button pin as input */
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        HAL_GPIO_Init(BUTTON_PORT[Button], &GPIO_InitStruct);
    }

    if (Button_Mode == BUTTON_MODE_EXTI) {
        if (Button == BUTTON_LOG || Button == BUTTON_MARK) {
            /* Configure Push Button pins as input with External interrupt, falling edge */
            GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
        }

        HAL_GPIO_Init(BUTTON_PORT[Button], &GPIO_InitStruct);

        /* Enable and set Button EXTI Interrupt to the lowest priority */
        HAL_NVIC_SetPriority((IRQn_Type)(BUTTON_IRQn[Button]), 0x0F, 0x00);
        HAL_NVIC_EnableIRQ((IRQn_Type)(BUTTON_IRQn[Button]));
    }
}

/**
  * @brief  Returns the selected button state.
  * @param  Button Button to be checked.
  *   This parameter can be one of the following values:
  *     @arg BUTTON_KEY: Key Push Button 
  * @retval The Button GPIO pin value
  */
uint32_t BSP_PB_GetState(Button_TypeDef Button)
{
    return HAL_GPIO_ReadPin(BUTTON_PORT[Button], BUTTON_PIN[Button]);
}

#if defined(HAL_UART_MODULE_ENABLED)
/******************************* UART Routines **********************************/
/**
  * @brief Initializes UART MSP.
  * @param huart UART handle
  * @retval None
  */
static void UARTx_MspInit(UART_HandleTypeDef* huart)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    /* Enable UART clock */
    GPS_UARTx_CLK_ENABLE();
    /* Enable GPIO clock */
    GPS_UARTx_TX_GPIO_CLK_ENABLE();

    /*** Configure the GPIOs ***/
    /* configure UART TX and RX */
    GPIO_InitStruct.Pin = (GPS_UARTx_TX_PIN | GPS_UARTx_RX_PIN);
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPS_UARTx_RX_AF;
    HAL_GPIO_Init(GPS_UARTx_TX_GPIO_PORT, &GPIO_InitStruct);

    /* USART2 interrupt Init */
    HAL_NVIC_SetPriority(GPS_UARTx_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(GPS_UARTx_IRQn);
}

/**
  * @brief  Initializes UART HAL.
  * @retval None
  */
static void UARTx_Init(void)
{
    if (HAL_UART_GetState(&huart) == HAL_UART_STATE_RESET) {
        /* UART Config */
        huart.Instance = GPS_UARTx;
        huart.Init.BaudRate = GPS_UARTx_BAUD;
        huart.Init.WordLength = UART_WORDLENGTH_8B;
        huart.Init.StopBits = UART_STOPBITS_1;
        huart.Init.Parity = UART_PARITY_NONE;
        huart.Init.Mode = UART_MODE_TX_RX;
        huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
        huart.Init.OverSampling = UART_OVERSAMPLING_16;
        huart.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
        huart.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;

        UARTx_MspInit(&huart);
        HAL_UART_Init(&huart);
    }
}

/**
  * @brief  Unitialize UART HAL.
  * @note   This is called in HAL_UART_DeInit().
  *         User shouldn't call this explicitly.
  * @retval None
  */
void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{
    /* Peripheral clock disable */
    __HAL_RCC_USART2_CLK_DISABLE();

    /* UART GPIO Deinit */
    HAL_GPIO_DeInit(GPIOA, GPS_UARTx_TX_PIN | GPS_UARTx_RX_PIN);

    /* UART interrupt Deinit */
    HAL_NVIC_DisableIRQ(GPS_UARTx_IRQn);
}

/**
  * @brief UART Write a character
  *        to the device.
  * @param Character char to be written
  * @retval None
  */
static void UARTx_WriteChar(char Character)
{
    while ((huart.Instance->ISR & USART_ISR_TXE) == 0) {
        // Wait for TX data buffer to be empty
    }

    // Prime the UART TX Data Register with the
    // character to send
    huart.Instance->TDR = Character;
}

/******************************** LINK GPS Module ********************************/
/**
  * @brief  Initializes the UART periph for the GPS
  * @retval None
  */
void GPS_IO_Init(void)
{
    UARTx_Init();
}

/**
  * @brief  Write a string to the GPS.
  * @param  Msg string to be written.
  * @retval None
  */
void GPS_IO_WriteString(char Msg[])
{
    int len = strlen(Msg);
    int cnt = 0;

    while (cnt < len) {
        UARTx_WriteChar(Msg[cnt]);
        cnt++;
    }
}

#endif /* HAL_UART_MODULE_ENABLED) */

/*******************************************************************************
                            BUS OPERATIONS
*******************************************************************************/
#if defined(HAL_SPI_MODULE_ENABLED)
/******************************* SPI Routines **********************************/
/**
  * @brief Initializes SPI MSP.
  * @param hspi SPI handle
  * @retval None
  */
void HAL_SPI_MspInit(SPI_HandleTypeDef* hspi)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    /*** Configure the SPI peripheral ***/
    /* Enable SPI clock */
    CUSTOM_SPIx_CLK_ENABLE();

    /*** Configure the GPIOs ***/
    /* Enable GPIO clock */
    CUSTOM_SPIx_SCK_GPIO_CLK_ENABLE();
    CUSTOM_SPIx_MISO_MOSI_GPIO_CLK_ENABLE();

    /* configure SPI SCK */
    GPIO_InitStruct.Pin = CUSTOM_SPIx_SCK_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = CUSTOM_SPIx_SCK_AF;
    HAL_GPIO_Init(CUSTOM_SPIx_SCK_GPIO_PORT, &GPIO_InitStruct);

    /* configure SPI MISO and MOSI */
    GPIO_InitStruct.Pin = (CUSTOM_SPIx_MISO_PIN | CUSTOM_SPIx_MOSI_PIN);
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = CUSTOM_SPIx_MISO_MOSI_AF;
    HAL_GPIO_Init(CUSTOM_SPIx_MISO_MOSI_GPIO_PORT, &GPIO_InitStruct);
}

/**
  * @brief  Initializes SPI HAL.
  * @retval None
  */
void SPIx_Init(void)
{
    if (HAL_SPI_GetState(&hspi) == HAL_SPI_STATE_RESET) {
        /* SPI Config */
        hspi.Instance = CUSTOM_SPIx;
        /* SPI baudrate is set to 12 MHz (PCLK2/SPI_BaudRatePrescaler = 24/2 = 12 MHz) */
        hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
        hspi.Init.Direction = SPI_DIRECTION_2LINES;
        hspi.Init.CLKPhase = SPI_PHASE_1EDGE;
        hspi.Init.CLKPolarity = SPI_POLARITY_LOW;
        hspi.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
        hspi.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
        hspi.Init.CRCPolynomial = 7;
        hspi.Init.DataSize = SPI_DATASIZE_8BIT;
        hspi.Init.FirstBit = SPI_FIRSTBIT_MSB;
        hspi.Init.NSS = SPI_NSS_SOFT;
        hspi.Init.TIMode = SPI_TIMODE_DISABLE;
        hspi.Init.Mode = SPI_MODE_MASTER;
        HAL_SPI_Init(&hspi);
    }
}

/**
  * @brief SPI Read 4 bytes from device
  * @retval Read data
*/
uint32_t SPIx_Read(void)
{
    HAL_StatusTypeDef status = HAL_OK;
    uint32_t readvalue = 0;
    uint32_t writevalue = 0xFFFFFFFF;

    status = HAL_SPI_TransmitReceive(&hspi, (uint8_t*)&writevalue, (uint8_t*)&readvalue, 1, SpixTimeout);

    /* Check the communication status */
    if (status != HAL_OK) {
        /* Execute user timeout callback */
        SPIx_Error();
    }

    return readvalue;
}

/**
  * @brief SPI Write a byte to device
  * @param Value value to be written
  * @retval None
  */
void SPIx_Write(uint8_t Value)
{
    HAL_StatusTypeDef status = HAL_OK;

    status = HAL_SPI_Transmit(&hspi, (uint8_t*)&Value, 1, SpixTimeout);

    /* Check the communication status */
    if (status != HAL_OK) {
        /* Execute user timeout callback */
        SPIx_Error();
    }
}

/**
  * @brief SPI error treatment function
  * @retval None
  */
void SPIx_Error(void)
{
    /* De-initialize the SPI communication BUS */
    HAL_SPI_DeInit(&hspi);

    /* Re- Initiaize the SPI communication BUS */
    SPIx_Init();
}

/******************************** LINK SD Card ********************************/
/**
  * @brief  Initializes the SD Card and put it into StandBy State (Ready for 
  *         data transfer).
  * @retval None
  */
void SD_IO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    uint8_t counter;

    /* SD_CS_GPIO and SD_DETECT_GPIO Periph clock enable */
    SD_CS_GPIO_CLK_ENABLE();
    SD_DETECT_GPIO_CLK_ENABLE();

    /* Configure SD_CS_PIN pin: SD Card CS pin */
    GPIO_InitStruct.Pin = SD_CS_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(SD_CS_GPIO_PORT, &GPIO_InitStruct);

    /* Configure SD_DETECT_PIN pin: SD Card detect pin */
    GPIO_InitStruct.Pin = SD_DETECT_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(SD_DETECT_GPIO_PORT, &GPIO_InitStruct);

    /* Enable and set SD EXTI Interrupt to the lowest priority */
    HAL_NVIC_SetPriority(SD_DETECT_EXTI_IRQn, 15, 0);
    HAL_NVIC_EnableIRQ(SD_DETECT_EXTI_IRQn);

    /*------------Put SD in SPI mode--------------*/
    /* SD SPI Config */
    SPIx_Init();

    /* SD chip select high */
    SD_CS_HIGH();

    /* Send dummy byte 0xFF, 10 times with CS high */
    /* Rise CS and MOSI for 80 clocks cycles */
    for (counter = 0; counter <= 9; counter++) {
        /* Send dummy byte 0xFF */
        SD_IO_WriteByte(SD_DUMMY_BYTE);
    }
}

/**
  * @brief  Write a byte on the SD.
  * @param  Data byte to send.
  * @retval None
  */
void SD_IO_WriteByte(uint8_t Data)
{
    /* Send the byte */
    SPIx_Write(Data);
}

/**
  * @brief  Read a byte from the SD.
  * @retval The received byte.
  */
uint8_t SD_IO_ReadByte(void)
{
    uint8_t data = 0;

    /* Get the received data */
    data = SPIx_Read();

    /* Return the shifted data */
    return data;
}

/**
  * @brief  Send 5 bytes command to the SD card and get response
  * @param  Cmd The user expected command to send to SD card.
  * @param  Arg The command argument.
  * @param  Crc The CRC.
  * @param  Response Expected response from the SD card
  * @retval  HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef SD_IO_WriteCmdLegacy(uint8_t Cmd, uint32_t Arg, uint8_t Crc, uint8_t Response)
{
    uint32_t counter = 0x00;
    uint8_t frame[6];

    /* Prepare Frame to send */
    frame[0] = (Cmd | 0x40); /* Construct byte 1 */
    frame[1] = (uint8_t)(Arg >> 24); /* Construct byte 2 */
    frame[2] = (uint8_t)(Arg >> 16); /* Construct byte 3 */
    frame[3] = (uint8_t)(Arg >> 8); /* Construct byte 4 */
    frame[4] = (uint8_t)(Arg); /* Construct byte 5 */
    frame[5] = (Crc); /* Construct CRC: byte 6 */

    /* SD chip select low */
    SD_CS_LOW();

    /* Send Frame */
    for (counter = 0; counter < 6; counter++) {
        SD_IO_WriteByte(frame[counter]); /* Send the Cmd bytes */
    }

    if (Response != SD_NO_RESPONSE_EXPECTED) {
        return SD_IO_WaitResponse(Response);
    }

    return HAL_OK;
}

/**
  * @brief  Send 5 bytes command to the SD card and get response
  * @param  Cmd The user expected command to send to SD card.
  * @param  Arg The command argument.
  * @param  Crc The CRC.
  * @param  Response
  * @retval SD_CmdTypeDef
  */
SD_CmdTypeDef SD_IO_WriteCmd(uint8_t Cmd, uint32_t Arg, uint8_t Crc, uint8_t Response)
{
    uint32_t counter = 0x00;
    uint8_t frame[6];
    SD_CmdTypeDef ret = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

    /* Prepare Frame to send */
    frame[0] = (Cmd | 0x40); /* Construct byte 1 */
    frame[1] = (uint8_t)(Arg >> 24); /* Construct byte 2 */
    frame[2] = (uint8_t)(Arg >> 16); /* Construct byte 3 */
    frame[3] = (uint8_t)(Arg >> 8); /* Construct byte 4 */
    frame[4] = (uint8_t)(Arg); /* Construct byte 5 */
    frame[5] = (Crc); /* Construct CRC: byte 6 */

    /* SD chip select low */
    SD_CS_LOW();

    /* Send Frame */
    for (counter = 0; counter < 6; counter++) {
        SD_IO_WriteByte(frame[counter]); /* Send the Cmd bytes */
    }

    switch (Response) {
    case SD_RESPONSE_R1_EXPECTED:
        ret.r1 = SD_IO_ReadData();
        break;
    case SD_RESPONSE_R1B_EXPECTED:
        ret.r1 = SD_IO_ReadData();
        ret.r2 = SD_IO_ReadByte();
        HAL_Delay(1);
        SD_CS_LOW();
        /* Wait IO line return 0xFF */
        while (SD_IO_ReadData() != SD_DUMMY_BYTE)
            ;
        break;
    case SD_RESPONSE_R2_EXPECTED:
        ret.r1 = SD_IO_ReadData();
        ret.r2 = SD_IO_ReadByte();
        break;
    case SD_RESPONSE_R3_EXPECTED:
    case SD_RESPONSE_R7_EXPECTED:
        ret.r1 = SD_IO_ReadData();
        ret.r2 = SD_IO_ReadByte();
        ret.r3 = SD_IO_ReadByte();
        ret.r4 = SD_IO_ReadByte();
        ret.r5 = SD_IO_ReadByte();
        break;
    case SD_NO_RESPONSE_EXPECTED:
        break;
    }

    // if (Response != SD_NO_RESPONSE_EXPECTED) {
    //     return SD_IO_WaitResponse(Response);
    // }

    return ret;
}

uint8_t SD_IO_ReadData()
{
    uint32_t timeout = 0xFFF;
    uint8_t data = SD_DUMMY_BYTE;

    /* Check if response is got or a timeout is happen */
    while ((data == SD_DUMMY_BYTE) && timeout) {
        timeout--;
        data = SD_IO_ReadByte();
    }

    if (timeout == 0) {
        /* After time out */
        return HAL_TIMEOUT;
    } else {
        /* Right response got */
        return data;
    }
}

/**
  * @brief  Wait response from the SD card
  * @param  Response Expected response from the SD card
  * @retval  HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef SD_IO_WaitResponse(uint8_t Response)
{
    uint32_t timeout = 0xFFF;

    /* Check if response is got or a timeout is happen */
    while ((SD_IO_ReadByte() != Response) && timeout) {
        timeout--;
    }

    if (timeout == 0) {
        /* After time out */
        return HAL_TIMEOUT;
    } else {
        /* Right response got */
        return HAL_OK;
    }
}

/**
  * @brief  Send dummy byte with CS High
  * @retval None
  */
void SD_IO_WriteDummy(void)
{
    /* SD chip select high */
    SD_CS_HIGH();

    /* Send Dummy byte 0xFF */
    SD_IO_WriteByte(SD_DUMMY_BYTE);
}
#endif /* HAL_SPI_MODULE_ENABLED */

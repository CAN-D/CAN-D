/**
  ******************************************************************************
  * @file    stm32f3xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_it.h"
#include "cmsis_os.h"
#include "gps.h" /* for UART message Queues */
#include "main.h"
#include "stm32302c_custom.h" /* for UART handle (huart) */
#include "string.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Exported variables --------------------------------------------------------*/
extern PCD_HandleTypeDef hpcd_USB_FS;
extern CAN_HandleTypeDef hcan;
extern TIM_HandleTypeDef htim2;
extern UART_HandleTypeDef huart;
extern TIM_HandleTypeDef htim1;

/* UART message Queues */
extern osMessageQId UARTGprmcQueueHandle;

/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
    while (1) {
    }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
    while (1) {
    }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
    while (1) {
    }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
    while (1) {
    }
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
}

/******************************************************************************/
/* STM32F3xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f3xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles USB high priority or CAN_TX interrupts.
  */
void USB_HP_CAN_TX_IRQHandler(void)
{
    HAL_CAN_IRQHandler(&hcan);
}

/**
  * @brief This function handles USB low priority or CAN_RX0 interrupts.
  */
void USB_LP_CAN_RX0_IRQHandler(void)
{
    HAL_CAN_IRQHandler(&hcan);
}

/**
  * @brief This function handles CAN RX1 interrupt.
  */
void CAN_RX1_IRQHandler(void)
{
    HAL_CAN_IRQHandler(&hcan);
}

/**
  * @brief This function handles TIM1 update and TIM16 interrupts.
  */
void TIM1_UP_TIM16_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&htim1);
}

/**
  * @brief This function handles TIM2 global interrupt.
  */
void TIM2_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&htim2);
}

/**
  * @brief This function handles USART2 global interrupt,
  *        USART2 RX interrupts, and USART2 wake-up interrupt 
  *        through EXTI line 26.
  */
void USART2_IRQHandler(void)
{
    char rxData[128] = "0";
    uint8_t rx_idx = 0;
    // Check if the UART2 Read Data Register has data
    if (huart.Instance->ISR & USART_ISR_RXNE) {
        // Read the data from the register
        rxData[rx_idx] = huart.Instance->RDR;

        // The GPS RX data will be held between '$' and '\n' characters
        // TODO: BO: This is demo specific code
        // if (rxData[rx_idx] == '$') {
        if (1) {
            // TODO: BO: This is demo specific code
            // if (strncmp("$GPRMC", rxData, sizeof("$GPRMC") - 1) == 0)
            //     APP_GPS_BufferGPSString(rxData, GPS_DATA_LENGTH);
            APP_GPS_BufferGPSString(rxData, GPS_DATA_LENGTH);

            memset(rxData, 0, sizeof(rxData));
        }
    }

    HAL_UART_IRQHandler(&huart);
}

/**
  * @brief This function handles USB low priority interrupt remap.
  */
void USB_LP_IRQHandler(void)
{
    HAL_PCD_IRQHandler(&hpcd_USB_FS);
}

/* Private functions ---------------------------------------------------------*/

/**
  ******************************************************************************
  * @file    stm32f3xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  */

#include "main.h"
#include "stm32f3xx_it.h"
#include "cmsis_os.h"
#include "stm32302c_custom.h" /* for UART handle (huart) */

extern PCD_HandleTypeDef hpcd_USB_FS;
extern CAN_HandleTypeDef hcan;
extern TIM_HandleTypeDef htim2;
extern UART_HandleTypeDef huart;
extern TIM_HandleTypeDef htim1;

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
  while (1) {}
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  while (1) {}
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  while (1) {}
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  while (1) {}
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
  * @brief This function handles USART2 global interrupt / USART2 wake-up interrupt through EXTI line 26.
  */
void USART2_IRQHandler(void)
{
  HAL_UART_IRQHandler(&huart);
}

/**
  * @brief This function handles USB low priority interrupt remap.
  */
void USB_LP_IRQHandler(void)
{
  HAL_PCD_IRQHandler(&hpcd_USB_FS);
}

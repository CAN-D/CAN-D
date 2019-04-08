/**
  ******************************************************************************
  * @file    stm32f3xx_it.h
  * @brief   This file contains the headers of the interrupt handlers.
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F3xx_IT_H
#define __STM32F3xx_IT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Private includes ----------------------------------------------------------*/
#include "main.h"

/* Exported functions prototypes ---------------------------------------------*/
void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void DebugMon_Handler(void);
void USB_HP_CAN_TX_IRQHandler(void);
void USB_LP_CAN_RX0_IRQHandler(void);
void CAN_RX1_IRQHandler(void);
void CAN_RX0_IRQHandler(void);
void TIM1_UP_TIM16_IRQHandler(void);
void TIM2_IRQHandler(void);
void SPI1_IRQHandler(void);
void SPI2_IRQHandler(void);
void USART2_IRQHandler(void);
void USB_LP_IRQHandler(void);
void EXTI15_10_IRQHandler(void);
void HAL_GPIO_EXTI_Callback(uint16_t pin);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F3xx_IT_H */

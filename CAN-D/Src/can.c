/**
  ******************************************************************************
  * File Name          : CAN.c
  * Description        : This file provides code for the configuration
  *                      of the CAN instances.
  ******************************************************************************
  */

#include "can.h"

CAN_HandleTypeDef hcan;


/* CAN init function */
void MX_CAN_Init(void)
{
  hcan.Instance = CAN;
  hcan.Init.Prescaler = 16;
  hcan.Init.Mode = CAN_MODE_NORMAL;
  hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan.Init.TimeSeg1 = CAN_BS1_1TQ;
  hcan.Init.TimeSeg2 = CAN_BS2_1TQ;
  hcan.Init.TimeTriggeredMode = DISABLE;
  hcan.Init.AutoBusOff = DISABLE;
  hcan.Init.AutoWakeUp = DISABLE;
  hcan.Init.AutoRetransmission = DISABLE;
  hcan.Init.ReceiveFifoLocked = DISABLE;
  hcan.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan) != HAL_OK)
  {
    Error_Handler();
  }

  // TODO: configure CAN reception filters using HAL_CAN_ConfigFilter()
}

void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(canHandle->Instance==CAN)
  {
    /* CAN clock enable */
    __HAL_RCC_CAN1_CLK_ENABLE();
  
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**CAN GPIO Configuration    
    PB8     ------> CAN_RX
    PB9     ------> CAN_TX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_CAN;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* CAN interrupt Init */
    // Disabling unused interrupts for now
//    HAL_NVIC_SetPriority(USB_HP_CAN_TX_IRQn, 5, 0);
//    HAL_NVIC_EnableIRQ(USB_HP_CAN_TX_IRQn);
//    HAL_NVIC_SetPriority(USB_LP_CAN_RX0_IRQn, 5, 0);
//    HAL_NVIC_EnableIRQ(USB_LP_CAN_RX0_IRQn);
    HAL_NVIC_SetPriority(CAN_RX1_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(CAN_RX1_IRQn);
  }
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef* canHandle)
{
  if(canHandle->Instance==CAN)
  {
    /* Peripheral clock disable */
    __HAL_RCC_CAN1_CLK_DISABLE();
  
    /**CAN GPIO Configuration    
    PB8     ------> CAN_RX
    PB9     ------> CAN_TX 
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_8|GPIO_PIN_9);

    /* CAN interrupt Deinit */
  /* BEGIN CAN:USB_HP_CAN_TX_IRQn disable */
    /**
    * Uncomment the line below to disable the "USB_HP_CAN_TX_IRQn" interrupt
    * Be aware, disabling shared interrupt may affect other IPs
    */
    /* HAL_NVIC_DisableIRQ(USB_HP_CAN_TX_IRQn); */
  /* END CAN:USB_HP_CAN_TX_IRQn disable */

  /* BEGIN CAN:USB_LP_CAN_RX0_IRQn disable */
    /**
    * Uncomment the line below to disable the "USB_LP_CAN_RX0_IRQn" interrupt
    * Be aware, disabling shared interrupt may affect other IPs
    */
    /* HAL_NVIC_DisableIRQ(USB_LP_CAN_RX0_IRQn); */
  /* END CAN:USB_LP_CAN_RX0_IRQn disable */

    HAL_NVIC_DisableIRQ(CAN_RX1_IRQn);
  }
}

/**
  * @brief  Rx FIFO 0 full callback.
  * @param  CanHandle: pointer to a CAN_HandleTypeDef structure that contains
  *         the configuration information for the specified CAN.
  * @retval None
  */
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef* canHandle)
{
  uint8_t rxData;
  osStatus status;
  HAL_StatusTypeDef err_code = HAL_OK;
  CAN_RxHeaderTypeDef pHeader = {0};

  // Get CAN RX data from the CAN module
  err_code = HAL_CAN_GetRxMessage(canHandle, CAN_RX_FIFO_0, &pHeader, &rxData);
  if (err_code != HAL_OK)
  {
    Error_Handler();
  }

  // Pass the CAN RX data to the CAN RX data queue
  // @see canBridgeTask()
  status = osMessagePut(canDataQueueHandle, (uint32_t)rxData, CAN_RXQ_TIMEOUT_MS);
  if (status != osOK)
  {
    Error_Handler();
  }
}

/**
  * @brief  Rx FIFO 1 full callback.
  * @param  CanHandle: pointer to a CAN_HandleTypeDef structure that contains
  *         the configuration information for the specified CAN.
  * @retval None
  */
void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef* canHandle)
{
  // TODO: Figure out how these fifos work. We currently enabled both FIFO
  //       interrupts (0 and 1) but I'm not sure how to properly handle data
  //       coming from both FIFOs at onee. Maybe just do the same as in
  //       HAL_CAN_RxFifo0MsgPendingCallback() ?
}


/**
  ******************************************************************************
  * File Name          : CAN.c
  * Description        : This file provides code for the configuration
  *                      of the CAN instances.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "can.h"
#include "fatfs.h"
#include "stm32302c_custom.h"
#include "usbd_cdc_if.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define TX_BUFFER_SIZE 8
#define RX_BUFFER_SIZE 8

/* Private variables ---------------------------------------------------------*/
APP_ConfigType mAppConfiguration = { 0 };
/* Threads */
osThreadId bridgeConfigTaskHandle;
osThreadId CANMonitorTaskHandle;
osThreadId CANTransmitTaskHandle;
/* Queues */
osMessageQId CANRxQueueHandle;
osMessageQId CANTxQueueHandle;
/* Data Pools */
osPoolDef(CANTxPool, TX_BUFFER_SIZE, CANTxMessage);
osPoolDef(CANRxPool, RX_BUFFER_SIZE, CANRxMessage);
osPoolId CANTxPool;
osPoolId CANRxPool;

/* Private macro -------------------------------------------------------------*/

/* Exported variables --------------------------------------------------------*/
CAN_HandleTypeDef hcan;
extern USBD_HandleTypeDef hUsbDeviceFS;

/* Private function prototypes -----------------------------------------------*/
void APP_CAN_LogButtonTask(void const* argument);
void APP_CAN_MonitorTask(void const* argument);
void APP_CAN_TransmitTask(void const* argument);

/* Exported functions --------------------------------------------------------*/
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
        Error_Handler();

    if ((CANTxPool = osPoolCreate(osPool(CANTxPool))) == NULL)
        Error_Handler();

    if ((CANRxPool = osPoolCreate(osPool(CANRxPool))) == NULL)
        Error_Handler();

    // TODO: configure CAN reception filters using HAL_CAN_ConfigFilter()
    mAppConfiguration.SDStorage = APP_DISABLE;
    mAppConfiguration.USBStream = APP_DISABLE;
    mAppConfiguration.USBTransfer = APP_DISABLE;
    mAppConfiguration.CANTransmit = APP_DISABLE;
}

void APP_CAN_InitTasks(void)
{
    osThreadDef(bridgeConfigTask, APP_CAN_LogButtonTask, osPriorityNormal, 0, 128);
    bridgeConfigTaskHandle = osThreadCreate(osThread(bridgeConfigTask), NULL);

    osThreadDef(CANMonitorTask, APP_CAN_MonitorTask, osPriorityNormal, 0, 128);
    CANMonitorTaskHandle = osThreadCreate(osThread(CANMonitorTask), NULL);

    osThreadDef(CANTransmitTask, APP_CAN_TransmitTask, osPriorityNormal, 0, 128);
    CANTransmitTaskHandle = osThreadCreate(osThread(CANTransmitTask), NULL);

    osMessageQDef(CANRxQueue, RX_BUFFER_SIZE, CANRxMessage);
    CANRxQueueHandle = osMessageCreate(osMessageQ(CANRxQueue), NULL);

    osMessageQDef(CANTxQueue, TX_BUFFER_SIZE, CANTxMessage);
    CANTxQueueHandle = osMessageCreate(osMessageQ(CANTxQueue), NULL);
}

void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle)
{
    GPIO_InitTypeDef GPIO_InitStruct = { 0 };
    if (canHandle->Instance == CAN) {
        /* CAN clock enable */
        __HAL_RCC_CAN1_CLK_ENABLE();

        __HAL_RCC_GPIOB_CLK_ENABLE();
        /**CAN GPIO Configuration    
            PB8     ------> CAN_RX
            PB9     ------> CAN_TX 
        */
        GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9;
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
    if (canHandle->Instance == CAN) {
        /* Peripheral clock disable */
        __HAL_RCC_CAN1_CLK_DISABLE();

        /**CAN GPIO Configuration    
            PB8     ------> CAN_RX
            PB9     ------> CAN_TX 
        */
        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_8 | GPIO_PIN_9);

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
    CANRxMessage* msg;
    msg = osPoolAlloc(CANRxPool);
    msg->handle = &hcan;

    // Get CAN RX data from the CAN module
    if (HAL_CAN_GetRxMessage(canHandle, CAN_RX_FIFO_0, msg->header, msg->data) != HAL_OK) {
        Error_Handler();
    }

    // Pass CAN RX data to the monitor thread
    osMessagePut(CANRxQueueHandle, (uint32_t)msg, 0);
}

/**
  * @brief  Rx FIFO 1 full callback.
  * @param  canHandle: pointer to a CAN_HandleTypeDef structure that contains
  *         the configuration information for the specified CAN.
  * @retval None
  */
void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef* canHandle)
{
}

/**
  * @brief  Toggles the CAN module.
  * @retval None
  */
void APP_CAN_StartStop(void)
{
    if (hcan.State == HAL_CAN_STATE_LISTENING) {
        HAL_CAN_Stop(&hcan);
        HAL_CAN_DeactivateNotification(&hcan, CAN_IT_START);
    } else if (hcan.State == HAL_CAN_STATE_READY) {
        // Changes the hcan.State to HAL_CAN_STATE_LISTENING
        HAL_CAN_Start(&hcan);
        HAL_CAN_ActivateNotification(&hcan, CAN_IT_START);
    }
}

/**
 * @brief Queue CAN data for transmission.
 * @retval None
 */
void APP_CAN_TransmitData(uint8_t* txData, CAN_TxHeaderTypeDef* header)
{
    CANTxMessage* msg;
    msg = osPoolAlloc(CANTxPool);
    msg->handle = &hcan;
    msg->header = header;
    memcpy(msg->data, txData, CAN_MESSAGE_LENGTH);
    osMessagePut(CANTxQueueHandle, (uint32_t)msg, 0);
}

/**
  * @brief  Sets the APP Configuration
  * @param  newConfig: the configuration to set
  * @retval None
  */
void APP_CAN_SetConfiguration(APP_ConfigType newConfig)
{
    mAppConfiguration = newConfig;
}

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Function implementing the APP_CAN_LogButtonTask thread.
  * @param  argument: Not used
  * @retval None
  */
void APP_CAN_LogButtonTask(void const* argument)
{
    for (;;) {
        // Start/Stop the CAN module on button press
        if (BSP_PB_GetState(BUTTON_LOG) == GPIO_PIN_SET) {
            APP_CAN_StartStop();
        }

        osDelay(1);
    }
}

/**
  * @brief  Function implementing the APP_CAN_MonitorTask thread.
  *         Monitors incoming CAN data.
  * @retval None
  */
void APP_CAN_MonitorTask(void const* argument)
{
    osEvent event;
    CANRxMessage* msg;

    for (;;) {
        // Pend on any CAN Rx data
        event = osMessageGet(CANRxQueueHandle, 0);
        if (event.status == osEventMessage) {
            msg = event.value.p;
            if (mAppConfiguration.SDStorage == APP_ENABLE) {
                // Write data to SD card
                APP_FATFS_WriteSD((const uint8_t*)msg->data, 8, "CAN_data.log");
            }
            if (mAppConfiguration.USBStream == APP_ENABLE) {
                // Fill the USB TX buffer with the CAN data
                while (CDC_Transmit_FS((uint8_t*)msg->data, (uint16_t)8) == 1) {
                    // USB TX State is BUSY. Wait for it to be free.
                }
            }
            osPoolFree(CANRxPool, msg);
        }
        osDelay(1);
    }
}

/**
  * @brief  Function implementing the APP_CAN_TransmitTask thread.
  *         Send outgoing CAN data.
  * @retval None
  */
void APP_CAN_TransmitTask(void const* argument)
{
    osEvent event;
    CANTxMessage* msg;
    uint32_t mailbox;

    for (;;) {
        // Pend on any CAN Tx data
        event = osMessageGet(CANTxQueueHandle, 0);
        if (event.status == osEventMessage) {
            msg = event.value.p;
            if (mAppConfiguration.CANTransmit == APP_ENABLE) {
                if (HAL_CAN_GetTxMailboxesFreeLevel(msg->handle) > 0) {
                    /* Default to sending on MAILBOX0 */
                    mailbox = CAN_TX_MAILBOX0;
                    /* Check Tx Mailbox 1 status */
                    if ((msg->handle->Instance->TSR & CAN_TSR_TME1) != 0U) {
                        mailbox = CAN_TX_MAILBOX1;
                    }
                    /* Check Tx Mailbox 2 status */
                    else if ((msg->handle->Instance->TSR & CAN_TSR_TME2) != 0U) {
                        mailbox = CAN_TX_MAILBOX2;
                    }
                    HAL_CAN_AddTxMessage(msg->handle, msg->header, msg->data, (uint32_t*)mailbox);
                } else {
                    // Dropped a message!
                }
            }
            osPoolFree(CANTxPool, msg);
        }
        osDelay(1);
    }
}
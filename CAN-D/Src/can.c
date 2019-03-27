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
#include "proto_handler.h"
#include "stm32302c_custom.h"
#include "usbd_cdc_if.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define TX_BUFFER_SIZE 8
#define RX_BUFFER_SIZE 8

/* Private variables ---------------------------------------------------------*/
static APP_ConfigType mAppConfiguration = { 0 };
static char canLogIdentifier[] = CAN_LOG_FILENAME;
/* Threads */
static osThreadId CANMonitorTaskHandle;
static osThreadId CANTransmitTaskHandle;
/* Queues */
static osMessageQId CANRxQueueHandle;
static osMessageQId CANTxQueueHandle;
/* Data Pools */
osPoolDef(CANTxPool, TX_BUFFER_SIZE, CANTxMessage);
osPoolDef(CANRxPool, RX_BUFFER_SIZE, CANRxMessage);
static osPoolId CANTxPool;
static osPoolId CANRxPool;

/* Private macro -------------------------------------------------------------*/

/* Exported variables --------------------------------------------------------*/
CAN_HandleTypeDef hcan;

/* Private function prototypes -----------------------------------------------*/
void APP_CAN_MonitorTask(void const* argument);
void APP_CAN_TransmitTask(void const* argument);

/* Exported functions --------------------------------------------------------*/
/* CAN init function */
void APP_CAN_Init(void)
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
    mAppConfiguration.USBTransfer = APP_DISABLE;
    mAppConfiguration.CANTransmit = APP_DISABLE;
}

void APP_CAN_InitTasks(void)
{
    osThreadDef(CANMonitorTask, APP_CAN_MonitorTask, osPriorityNormal, 0, 512);
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
        APP_CAN_Stop();
    } else if (hcan.State == HAL_CAN_STATE_READY) {
        APP_CAN_Start();
    }
}

/**
  * @brief  Starts the CAN module.
  * @retval None
  */
void APP_CAN_Start(void)
{
    // Changes the hcan.State to HAL_CAN_STATE_LISTENING
    if (HAL_CAN_Start(&hcan) == HAL_OK) {
        HAL_CAN_ActivateNotification(&hcan, CAN_IT_START);
        APP_FATFS_StartSession(); // start new log session
    }
}

/**
  * @brief  Stops the CAN module.
  * @retval None
  */
void APP_CAN_Stop(void)
{
    if (HAL_CAN_Stop(&hcan) == HAL_OK) {
        HAL_CAN_DeactivateNotification(&hcan, CAN_IT_START);
        APP_FATFS_StopSession(); // stop log session
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

/**
  * @brief  Function implementing the APP_CAN_MonitorTask thread.
  *         Monitors incoming CAN data.
  * @retval None
  */
void APP_CAN_MonitorTask(void const* argument)
{
    uint8_t usbTxCnt = 0;
    osEvent event;
    CANRxMessage* canRxMsg;
    size_t usbMaxMsgLen = CAN_USB_DATA_SZ_BYTES + 10; // Max length of the serialized data
    uint8_t usbTxMsg[usbMaxMsgLen]; // Serialized (packaged) protobuf data
    FromEmbedded fromEmbeddedMsg = FromEmbedded_init_zero;

    for (;;) {
        /* This is just used to test the SD card functionality */
        // const uint8_t data[] = "YELLOW";
        // APP_FATFS_LogSD(data, 6, CAN_LOG_FILENAME);

        // Pend on any CAN Rx data
        event = osMessageGet(CANRxQueueHandle, 0);
        if (event.status == osEventMessage) {
            canRxMsg = event.value.p;
            if (mAppConfiguration.SDStorage == APP_ENABLE) {
                // Write data to SD card
                APP_FATFS_LogSD((const uint8_t*)canRxMsg->data, CAN_SD_DATA_SZ_BYTES, canLogIdentifier);
            }

            // Construct FromEmbedded protobuf message
            fromEmbeddedMsg.contents.canDataChunk.size = 8;
            fromEmbeddedMsg.which_contents = 1;
            memcpy(fromEmbeddedMsg.contents.canDataChunk.bytes, canRxMsg->data, CAN_USB_DATA_SZ_BYTES);
            APP_PROTO_HANDLE_bufferFromEmbeddedMsg(&fromEmbeddedMsg, (uint8_t*)usbTxMsg, usbMaxMsgLen);

            usbTxCnt = 0;
            while (APP_USB_Transmit(usbTxMsg, CAN_USB_DATA_SZ_BYTES) == 1) {
                // USB TX State is BUSY. Wait for it to be free.
                osDelay(1);
                if (++usbTxCnt >= CAN_USB_TX_MAX_TRY) {
                    break;
                }
            }
            osPoolFree(CANRxPool, canRxMsg);
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

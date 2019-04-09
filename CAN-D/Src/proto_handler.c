/**
  ******************************************************************************
  * File Name          : command.c
  * Description        : This file provides code for the interpretation of 
  *                      protobuf messages.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "proto_handler.h"
#include "can.h"
#include "fatfs.h"
#include "gps.h"
#include "rtc.h"
#include <pb_decode.h>
#include <pb_encode.h>

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Exported variables --------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
void interpretToEmbeddedMessage(ToEmbedded* toEmbeddedMsg);
void interpretControlCommandMessage(ControlCommand* controlCommandMsg);
void interpretCanDataChunk(CanDataChunk* canDataChunk);

/* Exported functions --------------------------------------------------------*/
/**
  * @brief  Function for decoding 'incoming' data to 
  *         a ToEmbedded data type.
  * @param  data incoming byte array
  * @param  data_len number of bytes in data
  * @retval None
  */
void APP_PROTO_HANDLE_interpretData(uint8_t* data, size_t data_len)
{
    ToEmbedded message = ToEmbedded_init_zero;
    pb_istream_t stream = pb_istream_from_buffer(data, data_len);
    pb_decode(&stream, ToEmbedded_fields, &message);
    interpretToEmbeddedMessage(&message);
}

/**
  * @brief  Function for encoding a FromEmbedded message into a
  *         byte buffer.
  * @param  msg the FromEmbedded message to encode
  * @param  buffer the buffer to use. Will be filled with the encoded
  *                message if successful.
  * @param  max_buffer_len maximum number of bytes in buffer
  * @retval Returns the number of bytes encoded to the buffer
  */
size_t APP_PROTO_HANDLE_bufferFromEmbeddedMsg(FromEmbedded* msg, uint8_t* buffer, size_t max_buffer_len)
{
    pb_ostream_t stream = pb_ostream_from_buffer(buffer, max_buffer_len);
    if (pb_encode(&stream, FromEmbedded_fields, msg) == 0)
        return -1;
    return stream.bytes_written;
}

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Interprets messages sent to the embedded device
  * @param  toEmbeddedMsg the incoming protobuf message
  * @retval None
  */
void interpretToEmbeddedMessage(ToEmbedded* toEmbeddedMsg)
{
    if (toEmbeddedMsg->has_command)
        interpretControlCommandMessage(&toEmbeddedMsg->command);
    if (toEmbeddedMsg->has_transmitData)
        interpretCanDataChunk(&toEmbeddedMsg->transmitData);
}

/**
  * @brief  Helper function to delegate the action taken
  *         for specific control commands
  * @param  controlCommandMsg the command to interpret
  * @retval None
  */
void interpretControlCommandMessage(ControlCommand* controlCommandMsg)
{
    if (controlCommandMsg->has_commandType) {
        switch (controlCommandMsg->commandType) {
        case ControlCommandType_STOP_LOG:
            // Stop the log session
            APP_FATFS_StopSession();
            break;
        case ControlCommandType_START_LOG:
            // Start a new log session
            APP_FATFS_StartSession();
            break;
        case ControlCommandType_MARK_LOG:
            // Mark the log file
            APP_CAN_MarkLog();
            break;
        case ControlCommandType_GET_LOGFS_INFO:
            /* code */
            break;
        case ControlCommandType_GET_LOG:
            /* code */
            break;
        case ControlCommandType_DELETE_LOG:
            /* code */
            break;
        default:
            break;
        }
    }
}

/**
  * @brief  Helper function to delegate the action taken
  *         for specific CAN data
  * @param  canDataChunk the CAN data to interpret
  * @retval None
  */
void interpretCanDataChunk(CanDataChunk* canDataChunk)
{
    // Ensure the CAN Data has the required fields
    if (canDataChunk->has_id && canDataChunk->has_data && canDataChunk->has_dlc
        && canDataChunk->dlc > 0 && canDataChunk->dlc <= 8) {
        APP_CAN_TransmitData(canDataChunk->data.bytes, canDataChunk->id, canDataChunk->dlc);
    }
}

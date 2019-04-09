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
void APP_PROTO_HANDLE_interpretData(uint8_t* data, size_t data_len)
{
    ToEmbedded message = ToEmbedded_init_zero;
    pb_istream_t stream = pb_istream_from_buffer(data, data_len);
    pb_decode(&stream, ToEmbedded_fields, &message);
    interpretToEmbeddedMessage(&message);
}

size_t APP_PROTO_HANDLE_bufferFromEmbeddedMsg(FromEmbedded* msg, uint8_t* buffer, size_t max_buffer_len)
{
    pb_ostream_t stream = pb_ostream_from_buffer(buffer, max_buffer_len);
    if (pb_encode(&stream, FromEmbedded_fields, msg) == 0)
        return -1;
    return stream.bytes_written;
}

/* Private functions ---------------------------------------------------------*/
void interpretToEmbeddedMessage(ToEmbedded* toEmbeddedMsg)
{
    if (toEmbeddedMsg->has_command)
        interpretControlCommandMessage(&toEmbeddedMsg->command);
    if (toEmbeddedMsg->has_transmitData)
        interpretCanDataChunk(&toEmbeddedMsg->transmitData);
}

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

void interpretCanDataChunk(CanDataChunk* canDataChunk)
{
    if (canDataChunk->has_id && canDataChunk->has_data && canDataChunk->data.size > 0 && canDataChunk->data.size <= 8) {
        APP_CAN_TransmitData(canDataChunk->data.bytes, canDataChunk->id, canDataChunk->data.size);
    }
}

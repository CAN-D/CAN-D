/**
  ******************************************************************************
  * File Name          : proto_handler.h
  * Description        : This file provides code for the interpretation of 
  *                      protobuf messages.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __proto_handler_H
#define __proto_handler_H
#ifdef __cplusplus
extern "C" {
#endif

#include "can-d.pb-c.h"

typedef enum {
    PROTO_OK,
    PROTO_ERROR,
    PROTO_MSG_TOO_LONG,
    PROTO_NULL_MSG,
} ProtoStatus;

ProtoStatus APP_PROTO_HANDLE_interpretData(uint8_t* data, size_t data_len);
size_t APP_PROTO_HANDLE_bufferFromEmbeddedMsg(FromEmbedded* msg, uint8_t* buffer, size_t max_buffer_len);

#ifdef __cplusplus
}
#endif
#endif /*__proto_handler_H */

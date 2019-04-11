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

#include "can-d.pb.h"

void APP_PROTO_HANDLE_interpretData(uint8_t* data, size_t data_len);
size_t APP_PROTO_HANDLE_bufferFromEmbeddedMsg(FromEmbedded* msg, uint8_t* buffer, size_t max_buffer_len);

#define PROTO_BUFFER_OVERHEAD 10 /* 10 bytes of overhead for encoding protobufs */

#ifdef __cplusplus
}
#endif
#endif /*__proto_handler_H */

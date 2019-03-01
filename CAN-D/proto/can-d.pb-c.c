/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: can-d.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "can-d.pb-c.h"
void from_embedded__init(FromEmbedded* message)
{
    static const FromEmbedded init_value = FROM_EMBEDDED__INIT;
    *message = init_value;
}
size_t from_embedded__get_packed_size(const FromEmbedded* message)
{
    assert(message->base.descriptor == &from_embedded__descriptor);
    return protobuf_c_message_get_packed_size((const ProtobufCMessage*)(message));
}
size_t from_embedded__pack(const FromEmbedded* message,
    uint8_t* out)
{
    assert(message->base.descriptor == &from_embedded__descriptor);
    return protobuf_c_message_pack((const ProtobufCMessage*)message, out);
}
size_t from_embedded__pack_to_buffer(const FromEmbedded* message,
    ProtobufCBuffer* buffer)
{
    assert(message->base.descriptor == &from_embedded__descriptor);
    return protobuf_c_message_pack_to_buffer((const ProtobufCMessage*)message, buffer);
}
FromEmbedded*
from_embedded__unpack(ProtobufCAllocator* allocator,
    size_t len,
    const uint8_t* data)
{
    return (FromEmbedded*)
        protobuf_c_message_unpack(&from_embedded__descriptor,
            allocator, len, data);
}
void from_embedded__free_unpacked(FromEmbedded* message,
    ProtobufCAllocator* allocator)
{
    if (!message)
        return;
    assert(message->base.descriptor == &from_embedded__descriptor);
    protobuf_c_message_free_unpacked((ProtobufCMessage*)message, allocator);
}
void to_embedded__init(ToEmbedded* message)
{
    static const ToEmbedded init_value = TO_EMBEDDED__INIT;
    *message = init_value;
}
size_t to_embedded__get_packed_size(const ToEmbedded* message)
{
    assert(message->base.descriptor == &to_embedded__descriptor);
    return protobuf_c_message_get_packed_size((const ProtobufCMessage*)(message));
}
size_t to_embedded__pack(const ToEmbedded* message,
    uint8_t* out)
{
    assert(message->base.descriptor == &to_embedded__descriptor);
    return protobuf_c_message_pack((const ProtobufCMessage*)message, out);
}
size_t to_embedded__pack_to_buffer(const ToEmbedded* message,
    ProtobufCBuffer* buffer)
{
    assert(message->base.descriptor == &to_embedded__descriptor);
    return protobuf_c_message_pack_to_buffer((const ProtobufCMessage*)message, buffer);
}
ToEmbedded*
to_embedded__unpack(ProtobufCAllocator* allocator,
    size_t len,
    const uint8_t* data)
{
    return (ToEmbedded*)
        protobuf_c_message_unpack(&to_embedded__descriptor,
            allocator, len, data);
}
void to_embedded__free_unpacked(ToEmbedded* message,
    ProtobufCAllocator* allocator)
{
    if (!message)
        return;
    assert(message->base.descriptor == &to_embedded__descriptor);
    protobuf_c_message_free_unpacked((ProtobufCMessage*)message, allocator);
}
void control_command__init(ControlCommand* message)
{
    static const ControlCommand init_value = CONTROL_COMMAND__INIT;
    *message = init_value;
}
size_t control_command__get_packed_size(const ControlCommand* message)
{
    assert(message->base.descriptor == &control_command__descriptor);
    return protobuf_c_message_get_packed_size((const ProtobufCMessage*)(message));
}
size_t control_command__pack(const ControlCommand* message,
    uint8_t* out)
{
    assert(message->base.descriptor == &control_command__descriptor);
    return protobuf_c_message_pack((const ProtobufCMessage*)message, out);
}
size_t control_command__pack_to_buffer(const ControlCommand* message,
    ProtobufCBuffer* buffer)
{
    assert(message->base.descriptor == &control_command__descriptor);
    return protobuf_c_message_pack_to_buffer((const ProtobufCMessage*)message, buffer);
}
ControlCommand*
control_command__unpack(ProtobufCAllocator* allocator,
    size_t len,
    const uint8_t* data)
{
    return (ControlCommand*)
        protobuf_c_message_unpack(&control_command__descriptor,
            allocator, len, data);
}
void control_command__free_unpacked(ControlCommand* message,
    ProtobufCAllocator* allocator)
{
    if (!message)
        return;
    assert(message->base.descriptor == &control_command__descriptor);
    protobuf_c_message_free_unpacked((ProtobufCMessage*)message, allocator);
}
void log_fsinfo__init(LogFSInfo* message)
{
    static const LogFSInfo init_value = LOG_FSINFO__INIT;
    *message = init_value;
}
size_t log_fsinfo__get_packed_size(const LogFSInfo* message)
{
    assert(message->base.descriptor == &log_fsinfo__descriptor);
    return protobuf_c_message_get_packed_size((const ProtobufCMessage*)(message));
}
size_t log_fsinfo__pack(const LogFSInfo* message,
    uint8_t* out)
{
    assert(message->base.descriptor == &log_fsinfo__descriptor);
    return protobuf_c_message_pack((const ProtobufCMessage*)message, out);
}
size_t log_fsinfo__pack_to_buffer(const LogFSInfo* message,
    ProtobufCBuffer* buffer)
{
    assert(message->base.descriptor == &log_fsinfo__descriptor);
    return protobuf_c_message_pack_to_buffer((const ProtobufCMessage*)message, buffer);
}
LogFSInfo*
log_fsinfo__unpack(ProtobufCAllocator* allocator,
    size_t len,
    const uint8_t* data)
{
    return (LogFSInfo*)
        protobuf_c_message_unpack(&log_fsinfo__descriptor,
            allocator, len, data);
}
void log_fsinfo__free_unpacked(LogFSInfo* message,
    ProtobufCAllocator* allocator)
{
    if (!message)
        return;
    assert(message->base.descriptor == &log_fsinfo__descriptor);
    protobuf_c_message_free_unpacked((ProtobufCMessage*)message, allocator);
}
void log_file_info__init(LogFileInfo* message)
{
    static const LogFileInfo init_value = LOG_FILE_INFO__INIT;
    *message = init_value;
}
size_t log_file_info__get_packed_size(const LogFileInfo* message)
{
    assert(message->base.descriptor == &log_file_info__descriptor);
    return protobuf_c_message_get_packed_size((const ProtobufCMessage*)(message));
}
size_t log_file_info__pack(const LogFileInfo* message,
    uint8_t* out)
{
    assert(message->base.descriptor == &log_file_info__descriptor);
    return protobuf_c_message_pack((const ProtobufCMessage*)message, out);
}
size_t log_file_info__pack_to_buffer(const LogFileInfo* message,
    ProtobufCBuffer* buffer)
{
    assert(message->base.descriptor == &log_file_info__descriptor);
    return protobuf_c_message_pack_to_buffer((const ProtobufCMessage*)message, buffer);
}
LogFileInfo*
log_file_info__unpack(ProtobufCAllocator* allocator,
    size_t len,
    const uint8_t* data)
{
    return (LogFileInfo*)
        protobuf_c_message_unpack(&log_file_info__descriptor,
            allocator, len, data);
}
void log_file_info__free_unpacked(LogFileInfo* message,
    ProtobufCAllocator* allocator)
{
    if (!message)
        return;
    assert(message->base.descriptor == &log_file_info__descriptor);
    protobuf_c_message_free_unpacked((ProtobufCMessage*)message, allocator);
}
void data_payload__init(DataPayload* message)
{
    static const DataPayload init_value = DATA_PAYLOAD__INIT;
    *message = init_value;
}
size_t data_payload__get_packed_size(const DataPayload* message)
{
    assert(message->base.descriptor == &data_payload__descriptor);
    return protobuf_c_message_get_packed_size((const ProtobufCMessage*)(message));
}
size_t data_payload__pack(const DataPayload* message,
    uint8_t* out)
{
    assert(message->base.descriptor == &data_payload__descriptor);
    return protobuf_c_message_pack((const ProtobufCMessage*)message, out);
}
size_t data_payload__pack_to_buffer(const DataPayload* message,
    ProtobufCBuffer* buffer)
{
    assert(message->base.descriptor == &data_payload__descriptor);
    return protobuf_c_message_pack_to_buffer((const ProtobufCMessage*)message, buffer);
}
DataPayload*
data_payload__unpack(ProtobufCAllocator* allocator,
    size_t len,
    const uint8_t* data)
{
    return (DataPayload*)
        protobuf_c_message_unpack(&data_payload__descriptor,
            allocator, len, data);
}
void data_payload__free_unpacked(DataPayload* message,
    ProtobufCAllocator* allocator)
{
    if (!message)
        return;
    assert(message->base.descriptor == &data_payload__descriptor);
    protobuf_c_message_free_unpacked((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor from_embedded__field_descriptors[3] = {
    {
        "canDataChunk",
        1,
        PROTOBUF_C_LABEL_NONE,
        PROTOBUF_C_TYPE_MESSAGE,
        offsetof(FromEmbedded, contents_case),
        offsetof(FromEmbedded, candatachunk),
        &data_payload__descriptor,
        NULL,
        0 | PROTOBUF_C_FIELD_FLAG_ONEOF, /* flags */
        0, NULL, NULL /* reserved1,reserved2, etc */
    },
    {
        "gpsDataChunk",
        2,
        PROTOBUF_C_LABEL_NONE,
        PROTOBUF_C_TYPE_MESSAGE,
        offsetof(FromEmbedded, contents_case),
        offsetof(FromEmbedded, gpsdatachunk),
        &data_payload__descriptor,
        NULL,
        0 | PROTOBUF_C_FIELD_FLAG_ONEOF, /* flags */
        0, NULL, NULL /* reserved1,reserved2, etc */
    },
    {
        "logFSInfo",
        3,
        PROTOBUF_C_LABEL_NONE,
        PROTOBUF_C_TYPE_MESSAGE,
        offsetof(FromEmbedded, contents_case),
        offsetof(FromEmbedded, logfsinfo),
        &log_fsinfo__descriptor,
        NULL,
        0 | PROTOBUF_C_FIELD_FLAG_ONEOF, /* flags */
        0, NULL, NULL /* reserved1,reserved2, etc */
    },
};
static const unsigned from_embedded__field_indices_by_name[] = {
    0, /* field[0] = canDataChunk */
    1, /* field[1] = gpsDataChunk */
    2, /* field[2] = logFSInfo */
};
static const ProtobufCIntRange from_embedded__number_ranges[1 + 1] = {
    { 1, 0 },
    { 0, 3 }
};
const ProtobufCMessageDescriptor from_embedded__descriptor = {
    PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
    "FromEmbedded",
    "FromEmbedded",
    "FromEmbedded",
    "",
    sizeof(FromEmbedded),
    3,
    from_embedded__field_descriptors,
    from_embedded__field_indices_by_name,
    1, from_embedded__number_ranges,
    (ProtobufCMessageInit)from_embedded__init,
    NULL, NULL, NULL /* reserved[123] */
};
static const ProtobufCFieldDescriptor to_embedded__field_descriptors[1] = {
    {
        "command",
        1,
        PROTOBUF_C_LABEL_NONE,
        PROTOBUF_C_TYPE_MESSAGE,
        offsetof(ToEmbedded, contents_case),
        offsetof(ToEmbedded, command),
        &control_command__descriptor,
        NULL,
        0 | PROTOBUF_C_FIELD_FLAG_ONEOF, /* flags */
        0, NULL, NULL /* reserved1,reserved2, etc */
    },
};
static const unsigned to_embedded__field_indices_by_name[] = {
    0, /* field[0] = command */
};
static const ProtobufCIntRange to_embedded__number_ranges[1 + 1] = {
    { 1, 0 },
    { 0, 1 }
};
const ProtobufCMessageDescriptor to_embedded__descriptor = {
    PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
    "ToEmbedded",
    "ToEmbedded",
    "ToEmbedded",
    "",
    sizeof(ToEmbedded),
    1,
    to_embedded__field_descriptors,
    to_embedded__field_indices_by_name,
    1, to_embedded__number_ranges,
    (ProtobufCMessageInit)to_embedded__init,
    NULL, NULL, NULL /* reserved[123] */
};
static const ProtobufCFieldDescriptor control_command__field_descriptors[2] = {
    {
        "commandType",
        1,
        PROTOBUF_C_LABEL_NONE,
        PROTOBUF_C_TYPE_ENUM,
        0, /* quantifier_offset */
        offsetof(ControlCommand, commandtype),
        &control_command_type__descriptor,
        NULL,
        0, /* flags */
        0, NULL, NULL /* reserved1,reserved2, etc */
    },
    {
        "logName",
        2,
        PROTOBUF_C_LABEL_NONE,
        PROTOBUF_C_TYPE_STRING,
        offsetof(ControlCommand, info_case),
        offsetof(ControlCommand, logname),
        NULL,
        &protobuf_c_empty_string,
        0 | PROTOBUF_C_FIELD_FLAG_ONEOF, /* flags */
        0, NULL, NULL /* reserved1,reserved2, etc */
    },
};
static const unsigned control_command__field_indices_by_name[] = {
    0, /* field[0] = commandType */
    1, /* field[1] = logName */
};
static const ProtobufCIntRange control_command__number_ranges[1 + 1] = {
    { 1, 0 },
    { 0, 2 }
};
const ProtobufCMessageDescriptor control_command__descriptor = {
    PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
    "ControlCommand",
    "ControlCommand",
    "ControlCommand",
    "",
    sizeof(ControlCommand),
    2,
    control_command__field_descriptors,
    control_command__field_indices_by_name,
    1, control_command__number_ranges,
    (ProtobufCMessageInit)control_command__init,
    NULL, NULL, NULL /* reserved[123] */
};
static const ProtobufCFieldDescriptor log_fsinfo__field_descriptors[1] = {
    {
        "logFiles",
        1,
        PROTOBUF_C_LABEL_REPEATED,
        PROTOBUF_C_TYPE_MESSAGE,
        offsetof(LogFSInfo, n_logfiles),
        offsetof(LogFSInfo, logfiles),
        &log_file_info__descriptor,
        NULL,
        0, /* flags */
        0, NULL, NULL /* reserved1,reserved2, etc */
    },
};
static const unsigned log_fsinfo__field_indices_by_name[] = {
    0, /* field[0] = logFiles */
};
static const ProtobufCIntRange log_fsinfo__number_ranges[1 + 1] = {
    { 1, 0 },
    { 0, 1 }
};
const ProtobufCMessageDescriptor log_fsinfo__descriptor = {
    PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
    "LogFSInfo",
    "LogFSInfo",
    "LogFSInfo",
    "",
    sizeof(LogFSInfo),
    1,
    log_fsinfo__field_descriptors,
    log_fsinfo__field_indices_by_name,
    1, log_fsinfo__number_ranges,
    (ProtobufCMessageInit)log_fsinfo__init,
    NULL, NULL, NULL /* reserved[123] */
};
static const ProtobufCFieldDescriptor log_file_info__field_descriptors[3] = {
    {
        "size",
        1,
        PROTOBUF_C_LABEL_NONE,
        PROTOBUF_C_TYPE_UINT32,
        0, /* quantifier_offset */
        offsetof(LogFileInfo, size),
        NULL,
        NULL,
        0, /* flags */
        0, NULL, NULL /* reserved1,reserved2, etc */
    },
    {
        "unixTime",
        2,
        PROTOBUF_C_LABEL_NONE,
        PROTOBUF_C_TYPE_UINT64,
        0, /* quantifier_offset */
        offsetof(LogFileInfo, unixtime),
        NULL,
        NULL,
        0, /* flags */
        0, NULL, NULL /* reserved1,reserved2, etc */
    },
    {
        "fileName",
        3,
        PROTOBUF_C_LABEL_NONE,
        PROTOBUF_C_TYPE_STRING,
        0, /* quantifier_offset */
        offsetof(LogFileInfo, filename),
        NULL,
        &protobuf_c_empty_string,
        0, /* flags */
        0, NULL, NULL /* reserved1,reserved2, etc */
    },
};
static const unsigned log_file_info__field_indices_by_name[] = {
    2, /* field[2] = fileName */
    0, /* field[0] = size */
    1, /* field[1] = unixTime */
};
static const ProtobufCIntRange log_file_info__number_ranges[1 + 1] = {
    { 1, 0 },
    { 0, 3 }
};
const ProtobufCMessageDescriptor log_file_info__descriptor = {
    PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
    "LogFileInfo",
    "LogFileInfo",
    "LogFileInfo",
    "",
    sizeof(LogFileInfo),
    3,
    log_file_info__field_descriptors,
    log_file_info__field_indices_by_name,
    1, log_file_info__number_ranges,
    (ProtobufCMessageInit)log_file_info__init,
    NULL, NULL, NULL /* reserved[123] */
};
static const ProtobufCFieldDescriptor data_payload__field_descriptors[2] = {
    {
        "dataLength",
        1,
        PROTOBUF_C_LABEL_NONE,
        PROTOBUF_C_TYPE_UINT32,
        0, /* quantifier_offset */
        offsetof(DataPayload, datalength),
        NULL,
        NULL,
        0, /* flags */
        0, NULL, NULL /* reserved1,reserved2, etc */
    },
    {
        "data",
        2,
        PROTOBUF_C_LABEL_NONE,
        PROTOBUF_C_TYPE_BYTES,
        0, /* quantifier_offset */
        offsetof(DataPayload, data),
        NULL,
        NULL,
        0, /* flags */
        0, NULL, NULL /* reserved1,reserved2, etc */
    },
};
static const unsigned data_payload__field_indices_by_name[] = {
    1, /* field[1] = data */
    0, /* field[0] = dataLength */
};
static const ProtobufCIntRange data_payload__number_ranges[1 + 1] = {
    { 1, 0 },
    { 0, 2 }
};
const ProtobufCMessageDescriptor data_payload__descriptor = {
    PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
    "DataPayload",
    "DataPayload",
    "DataPayload",
    "",
    sizeof(DataPayload),
    2,
    data_payload__field_descriptors,
    data_payload__field_indices_by_name,
    1, data_payload__number_ranges,
    (ProtobufCMessageInit)data_payload__init,
    NULL, NULL, NULL /* reserved[123] */
};
static const ProtobufCEnumValue control_command_type__enum_values_by_number[6] = {
    { "STOP_LOG", "CONTROL_COMMAND_TYPE__STOP_LOG", 0 },
    { "START_LOG", "CONTROL_COMMAND_TYPE__START_LOG", 1 },
    { "MARK_LOG", "CONTROL_COMMAND_TYPE__MARK_LOG", 2 },
    { "GET_LOGFS_INFO", "CONTROL_COMMAND_TYPE__GET_LOGFS_INFO", 3 },
    { "GET_LOG", "CONTROL_COMMAND_TYPE__GET_LOG", 4 },
    { "DELETE_LOG", "CONTROL_COMMAND_TYPE__DELETE_LOG", 5 },
};
static const ProtobufCIntRange control_command_type__value_ranges[] = {
    { 0, 0 }, { 0, 6 }
};
static const ProtobufCEnumValueIndex control_command_type__enum_values_by_name[6] = {
    { "DELETE_LOG", 5 },
    { "GET_LOG", 4 },
    { "GET_LOGFS_INFO", 3 },
    { "MARK_LOG", 2 },
    { "START_LOG", 1 },
    { "STOP_LOG", 0 },
};
const ProtobufCEnumDescriptor control_command_type__descriptor = {
    PROTOBUF_C__ENUM_DESCRIPTOR_MAGIC,
    "ControlCommandType",
    "ControlCommandType",
    "ControlCommandType",
    "",
    6,
    control_command_type__enum_values_by_number,
    6,
    control_command_type__enum_values_by_name,
    1,
    control_command_type__value_ranges,
    NULL, NULL, NULL, NULL /* reserved[1234] */
};
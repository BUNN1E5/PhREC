
#include <stdint.h>


//Request Messages
typedef struct {
    uint32_t message_id : 6;
    uint32_t node_id : 8;
    uint32_t config : 2;
    uint32_t node_id_offset : 8;
    uint32_t undefined : 8;
} RequestHardwareId;

typedef struct {
    uint32_t message_id : 6;
    uint32_t node_id : 8;
    uint32_t hw_id : 16;
    uint32_t undefined : 2;
} AssignNodeId;

typedef struct {
    uint32_t message_id : 6;
    uint32_t undefined : 26;
} ValidateNodeIds;

typedef struct {
    uint32_t message_id : 6;
    uint32_t node_id : 8;
    uint32_t config : 2;
    uint32_t undefined : 16;
} RandomizeNodeIds;

typedef struct {
    uint32_t message_id : 6;
    uint32_t node_id : 8;
    uint32_t undefined : 18;
} RequestSensorDepth;

typedef struct {
    uint32_t message_id : 6;
    uint32_t node_id : 8;
    uint32_t sensor_depth : 8;
    uint32_t undefined : 10;
} RequestSensorData;

typedef struct {
    uint32_t message_id : 6;
    uint32_t node_id : 8;
    uint32_t sensor_depth : 8;
    uint32_t undefined : 10;
} RequestSensorDataStream;

typedef struct {
    uint32_t message_id : 6;
    uint32_t node_id : 8;
    uint32_t motor_impulse : 18;
} RequestMotorImpulse;


//Response Messages

typedef struct {
    uint32_t message_id : 6;
    uint32_t node_id : 8;
    uint32_t hw_id : 16;
    uint32_t undefined : 2;
} HardwareIdResponse;

typedef struct {
    uint32_t message_id : 6;
    uint32_t node_id : 8;
    uint32_t random_val : 8;
    uint32_t crc8 : 8;
    uint32_t undefined : 2;
} ValidateNodeIdResponse;

typedef struct {
    uint32_t message_id : 6;
    uint32_t node_id : 8;
    uint32_t crc8 : 8;
    uint32_t undefined : 10;
} RandomizedNodeIdResponse;

typedef struct {
    uint32_t message_id : 6;
    uint32_t node_id : 8;
    uint32_t sensor_depth : 18;
} SensorDepthResponse;

typedef struct {
    uint32_t message_id : 6;
    uint32_t node_id : 8;
    uint32_t sensor_data : 18;
} SensorDataResponse;

typedef struct {
    uint32_t message_id : 6;
    uint32_t node_id : 8;
    uint32_t sensor_count : 18;
} SensorStreamHeader;

typedef struct {
    uint32_t message_id : 6;
    uint32_t sensor_id : 8;
    uint32_t sensor_data : 18;
} SensorStreamData;

//Basic Message Structure
//We use this for packing and unpacking messages
typedef union {
    uint32_t raw;

    struct{
        uint32_t message_id : 6;
    } header;

    //Request Messages
    RequestHardwareId requestHardwareId;
    
    AssignNodeId assignNodeId;
    ValidateNodeIds validateNodeIds;
    RandomizeNodeIds randomizeNodeIds;
    RequestSensorDepth requestSensorDepth;
    RequestSensorData requestSensorData;
    RequestSensorDataStream requestSensorDataStream;
    RequestMotorImpulse requestMotorImpulse;

    //Response Messages
    HardwareIdResponse hardwareIdResponse;
    SensorDepthResponse sensorDepthResponse;
    SensorDataResponse sensorDataResponse;
    ValidateNodeIdResponse validateNodeIdResponse;
    RandomizedNodeIdResponse randomizedNodeIdResponse;
    SensorStreamHeader sensorStreamHeader;
    SensorStreamData sensorStreamData;
} Message;

int HandleMessage(Message *msg);

typedef int (*MessageHandler)(Message *msg);

int HandleHardwareId(Message *msg);
int HandleAssignNodeId(Message *msg);
int HandleValidateNodeIds(Message *msg);
int HandleRandomizeNodeIds(Message *msg);
int HandleRequestSensorDepth(Message *msg);
int HandleRequestSensorData(Message *msg);
int HandleRequestSensorDataStream(Message *msg);
int HandleRequestMotorImpulse(Message *msg);

int HandleHardwareIdResponse(Message *msg);
int HandleSensorDepthResponse(Message *msg);
int HandleSensorDataResponse(Message *msg);
int HandleValidateNodeIdResponse(Message *msg);
int HandleRandomizedNodeIdResponse(Message *msg);
int HandleSensorStreamHeader(Message *msg);
int HandleSensorStreamData(Message *msg);

MessageHandler message_handlers[64]{
    [1] = HandleHardwareId,
    [63 - 1] = HandleHardwareIdResponse,
    [2] = HandleAssignNodeId,
    [63 - 2] = HandleSensorDepthResponse,
    [3] = HandleValidateNodeIds,
    [63 - 3] = HandleSensorDataResponse,
    [4] = HandleRandomizeNodeIds,
    [63 - 4] = HandleValidateNodeIdResponse,
    [5] = HandleRequestSensorDepth,
    [63 - 5] = HandleSensorDepthResponse,
    [10] = HandleRequestSensorData,
    [63 - 10] = HandleSensorDataResponse,
    [11] = HandleRequestSensorDataStream,
    [63 - 11] = HandleSensorStreamHeader,
    [63 - 12] = HandleSensorStreamData,
    [20] = HandleRequestMotorImpulse
};


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

typedef int MessageHandler(Message *msg);

int Message_Handler(Message *msg);

int Hardware_Id_Handler(Message *msg);
int Assign_Node_Id_Handler(Message *msg);
int Validate_Node_Ids_Handler(Message *msg);
int Randomize_Node_Ids_Handler(Message *msg);
int Request_Sensor_Depth_Handler(Message *msg);
int Request_Sensor_Data_Handler(Message *msg);
int Request_Sensor_Data_Stream_Handler(Message *msg);
int Request_Motor_Impulse_Handler(Message *msg);

int Hardware_Id_Response_Handler(Message *msg);
int Assign_Node_Id_Response_Handler(Message *msg);
int Validate_Node_Ids_Response_Handler(Message *msg);
int Randomize_Node_Ids_Response_Handler(Message *msg);
int Request_Sensor_Depth_Response_Handler(Message *msg);
int Request_Sensor_Data_Response_Handler(Message *msg);
int Request_Sensor_Data_Stream_Response_Handler(Message *msg);
int Request_Motor_Impulse_Response_Handler(Message *msg);

MessageHandler *message_handlers[64] = {
    [1] = Hardware_Id_Handler,
    [63 - 1] = Hardware_Id_Response_Handler,
    [2] = Assign_Node_Id_Handler,
    [63 - 2] = Assign_Node_Id_Response_Handler,
    [3] = Validate_Node_Ids_Handler,
    [63 - 3] = Validate_Node_Ids_Response_Handler,
    [4] = Randomize_Node_Ids_Handler,
    [63 - 4] = Randomize_Node_Ids_Response_Handler,
    [5] = Request_Sensor_Depth_Handler,
    [63 - 5] = Request_Sensor_Depth_Response_Handler,
    [10] = Request_Sensor_Data_Handler,
    [63 - 10] = Request_Sensor_Data_Response_Handler,
    [11] = Request_Sensor_Data_Stream_Handler,
    [63 - 11] = Request_Sensor_Data_Stream_Response_Handler,
    [20] = Request_Motor_Impulse_Handler,
};

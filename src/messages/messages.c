#include "messages.h"

MessageHandler message_handlers[64] = {
    // [1] = Hardware_Id_Handler,
    // [63 - 1] = Hardware_Id_Response_Handler,
    // [2] = Assign_Node_Id_Handler,
    // [63 - 2] = Assign_Node_Id_Response_Handler,
    // [3] = Validate_Node_Ids_Handler,
    // [63 - 3] = Validate_Node_Ids_Response_Handler,
    // [4] = Randomize_Node_Ids_Handler,
    // [63 - 4] = Randomize_Node_Ids_Response_Handler,
    // [5] = Request_Sensor_Depth_Handler,
    // [63 - 5] = Request_Sensor_Depth_Response_Handler,
    // [10] = Request_Sensor_Data_Handler,
    // [63 - 10] = Request_Sensor_Data_Response_Handler,
    // [11] = Request_Sensor_Data_Stream_Handler,
    // [63 - 11] = Request_Sensor_Data_Stream_Response_Handler,
    // [20] = Request_Motor_Impulse_Handler,
};


Message Message_Handler(Message msg) {
    return message_handlers[msg.header.message_id](msg);
}
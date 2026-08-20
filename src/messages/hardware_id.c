#include "messages.h"
#include "utils/crc.h"

Message Request_Hardware_Id_Handler(Message msg){
    uint32_t uid1 = HAL_GetUIDw0();
    uint32_t uid2 = HAL_GetUIDw1();
    uint32_t uid3 = HAL_GetUIDw2();

    uint8_t uid_bytes[12];
    //Convert the 3 uint32_t values to bytes
    memcpy(uid_bytes, &uid1, 4);
    memcpy(uid_bytes + 4, &uid2, 4);
    memcpy(uid_bytes + 8, &uid3, 4);

    uint16_t crc = crc16(uid_bytes, 12);

    Message response;
    response.hardwareIdResponse.message_id = 63 - 1;
    response.hardwareIdResponse.node_id = 0;
    response.hardwareIdResponse.hw_id = crc;
    return response;
}

Message Hardware_Id_Response_Handler(Message msg){
    return msg;
}

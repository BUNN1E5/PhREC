#include "messages.h"
#include "utils/crc.h"

Message Assign_Node_Id_Handler(Message msg){
    return msg;
}

//Responses are not implemented on PHRec Node atm so echo msg
Message Assign_Node_Id_Response_Handler(Message msg){ return msg; }


Message Validate_Node_Ids_Handler(Message msg){
    return msg;
}

//Responses are not implemented on PHRec Node atm so echo msg
Message Validate_Node_Ids_Response_Handler(Message msg){
    return msg;
}

Message Randomize_Node_Ids_Handler(Message msg){ return msg; }

//Responses are not implemented on PHRec Node atm so echo msg
Message Randomize_Node_Ids_Response_Handler(Message msg){ return msg; }
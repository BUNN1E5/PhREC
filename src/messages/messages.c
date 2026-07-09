#include "messages.h"

int Message_Handler(Message *msg) {
    return message_handlers[msg->header.message_id](msg);
}
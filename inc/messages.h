
#include <stdint.h>

//Basic Message Structure
struct Message {
    int32_t message_id : 5;
    uint32_t data : 24;
};


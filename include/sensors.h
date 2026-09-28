#include "stdint.h"
#include "messages.h"

//This is currently a C++ class, if we convert the rest of the
//project to C we can convert this to a C struct with function pointers
//But C++ is just easier for now

// Sensor Count is defined in messages.h as 4 bits,
// so we can only have 16 sensors max. If we need more, 
// we can change the message format to allow for more sensors
#define MAX_SENSORS 16

class Sensor{
public:
    static uint8_t next_id;
    static Sensor* sensors[MAX_SENSORS];
    static uint8_t sensor_count;

    Sensor() : id(next_id++) {
        if (sensor_count < MAX_SENSORS) {
            sensors[sensor_count++] = this;
        }
    }

    virtual SensorDataResponse getData() = 0;
    virtual SensorStreamData getStreamData() = 0;
    int id;
    int group_id;

    static uint8_t count() {
        return sensor_count;
    }
    
private:
};

uint8_t Sensor::next_id = 0;
Sensor* Sensor::sensors[MAX_SENSORS];
uint8_t Sensor::sensor_count = 0;


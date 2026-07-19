#include <stdint.h>
#include <messages.h>
#include <Arduino.h>


class Sensor{
public:
    // Sensor ID is defined as the following
    // The SensorStreamData structure requires the sensor ID as the first 4 bits
    virtual SensorStreamData getData() = 0;
    int id;
    int group_id;
    
private:
};




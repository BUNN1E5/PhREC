#include <stdint.h>
#include <messages.h>

class Sensor{
public:
    // Sensor ID is defined as the following
    // The SensorStreamData structure requires the sensor ID as the first 4 bits
    Sensor(int sensor_id, int group_id);
    SensorStreamData getData();
    int id;
    int group_id;
    
private:
};



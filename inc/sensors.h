#include <stdint.h>
#include <messages.h>

//TODO :: Rename Basic Function For Generic Sensor Data
// We pass in a sensor_id cause I want the function to return the SensorStreamData which requires the sensor ID as the first 4 bits
typedef SensorStreamData GetSensorData(int sensor_id);

//Define a sensor structure that can point to a GetSensorData function
typedef struct {
    // Sensor ID is defined as the following
    // The SensorStreamData structure requires the sensor ID as the first 4 bits
    uint8_t id : 4;
    uint8_t group_id : 4;
    GetSensorData *get_data;
} Sensor;


static Sensor Init(int sensor_id, int group_id);
static SensorStreamData Get_Sensor_Data(int sensor_id);


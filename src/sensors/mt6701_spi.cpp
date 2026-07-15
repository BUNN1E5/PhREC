#include "sensors.h"
#include <Arduino.h>
#include "SPI.h"


SPISettings spiSettings(1000000, MSBFIRST, SPI_MODE0);
const PinName spiPins = {
    PA_7,
    PA_6,
    PA_5
};

Sensor::Sensor(int sensor_id, int group_id) {
    this->id = sensor_id;
    this->group_id = group_id;
    SPI.begin();
}

SensorStreamData Sensor::getData() {
    SensorStreamData data;
    data.message_id = -13; // Defined in messages.md
    data.sensor_id = this->id;
    data.sensor_data = 0; // Replace with actual sensor data retrieval logic
    return data;
}
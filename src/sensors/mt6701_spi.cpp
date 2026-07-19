#include "sensors.h"
#include "SPI.h"

//This is temp until I decide to actually give them .h files
class MT6701_SPI : public Sensor{
public:
    MT6701_SPI(PinName NSS, int sensor_id, int group_id);
    SensorStreamData getData() override;
    int id;
    int group_id;
};


//Temp setup for a 4 wire slipring
//For SSI we need 5 wires for MISO, SCK, 3v3, GND, and NSS
//For now we only have 4 wire sliprings so this patch is for that 
#define SSI_4_PIN

SPISettings spiSettings(1000000, MSBFIRST, SPI_MODE0);
const PinName mt6701_spi_pins[] = {
    PA_6,  // MISO
    PA_5,  // SCK
};

PinName nss_pin = PA_2;

MT6701_SPI::MT6701_SPI(PinName NSS, int sensor_id, int group_id) {
    this->id = sensor_id;
    this->group_id = group_id;
    nss_pin = NSS;
    SPI.begin();
    SPI.setDataMode(SPI_MODE2);
}

SensorStreamData MT6701_SPI::getData() {
    SPI.beginTransaction(spiSettings);
    digitalWrite(nss_pin, LOW);

    //
    byte a = SPI.transfer(0x00);
    byte b = SPI.transfer(0x00);
    byte c = SPI.transfer(0x00);

    //MT6701 data bit layout is the following
    // 14 bit angle data
    // 4 bit status
    // 6 bit crc

    //We dont care about the CRC tbh, we just want 18bit alligned data
    //We want the entire 8 bits of a
    //We only want 6 bits of b
    uint32_t sensor_data = (a << 6) | (b >> 2);

    SensorStreamData data;
    data.message_id = -13; // Defined in messages.md
    data.sensor_id = this->id;
    data.sensor_data = sensor_data; // data.sensor_data is 18 bits the crc is truncated
    digitalWrite(nss_pin, HIGH);
    SPI.endTransaction();

    #ifdef SSI_4_PIN
    delayMicroseconds(20);
    #endif

    return data;
}
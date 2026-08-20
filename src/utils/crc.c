#include "utils/crc.h"

uint32_t crc32(uint8_t *data, size_t length){
    uint32_t crc = 0xFFFFFFFF;
    for (size_t i = 0; i < length; i++) {
        crc ^= data[i];
        for (uint8_t j = 0; j < 32; j++) {
            if (crc & 0x00000001) {
                crc >>= 1;
                crc ^= 0xEDB88320;
            } else {
                crc >>= 1;
            }
        }
    }
    return crc;
}

uint16_t crc16(uint8_t *data, size_t length){
    uint16_t crc = 0xFFFF;
    for (uint16_t i = 0; i < length; i++) {
        crc ^= data[i];
        for (uint8_t j = 0; j < 16; j++) {
            if (crc & 0x0001) {
                crc >>= 1;
                crc ^= 0xA001;
            } else {
                crc >>= 1;
            }
        }
    }
    return crc;
}

uint8_t crc8(uint8_t *data, size_t length){
    uint8_t crc = 0xFF;
    for (size_t i = 0; i < length; i++) {
        crc ^= data[i];
        for (uint8_t j = 0; j < 8; j++) {
            if (crc & 0x01) {
                crc >>= 1;
                crc ^= 0x8C;
            } else {
                crc >>= 1;
            }
        }
    }
    return crc;
}

uint8_t crc2(uint8_t *data, size_t length){
    uint8_t crc = 0x03;
    for (size_t i = 0; i < length; i++) {
        crc ^= data[i];
        for (uint8_t j = 0; j < 2; j++) {
            if (crc & 0x01) {
                crc >>= 1;
                crc ^= 0x03;
            } else {
                crc >>= 1;
            }
        }
    }
    return crc;
}
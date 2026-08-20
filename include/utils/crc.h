#include "stdint.h"

typedef unsigned int size_t;
uint32_t crc32(uint8_t *data, size_t length);
uint16_t crc16(uint8_t *data, size_t length);
uint8_t crc8(uint8_t *data, size_t length);
uint8_t crc2(uint8_t *data, size_t length);
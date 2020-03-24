
uint16_t crc_reflect(uint16_t data, int32_t len)
{
    uint16_t ret = data & 0x01;
    for (int32_t i = 1; i < len; i++) {
        data >>= 1;
        ret = (ret << 1) | (data & 0x01);
    }
    return ret;
}

uint16_t calculateCRC(const char *data, int32_t len)
{
    uint16_t crc = 0xFFFF;
    while (len--) {
        const uint8_t c = *data++;
        for (int32_t i = 0x01; i & 0xFF; i <<= 1) {
            bool bit = crc & 0x8000;
            if (c & i)
                bit = !bit;
            crc <<= 1;
            if (bit)
                crc ^= 0x8005;
        }
        crc &= 0xFFFF;
    }
    crc = crc_reflect(crc & 0xFFFF, 16) ^ 0x0000;
    return (crc >> 8) | (crc << 8); // swap bytes
}


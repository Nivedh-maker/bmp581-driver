#include "bmp581.h"

static bmp581_read_function read_register;
static bmp581_write_function write_register;

int bmp581_begin(bmp581_read_function read, bmp581_write_function write)
{
    uint8_t chip_id;
    if (read == 0 || write == 0) return -1;
    read_register = read;
    write_register = write;
    if (read_register(0x01, &chip_id, 1) != 0) return -1;
    return (chip_id == 0x50 || chip_id == 0x51) ? 0 : -1;
}

int bmp581_start(void)
{
    if (write_register == 0) return -1;
    if (write_register(0x36, 0x60) != 0) return -1;
    return write_register(0x37, 0x5F);
}

int bmp581_read(float *pressure_pa, float *temperature_c)
{
    uint8_t data[6];
    int32_t temperature;
    uint32_t pressure;
    if (read_register == 0 || pressure_pa == 0 || temperature_c == 0) return -1;
    if (read_register(0x1D, data, 6) != 0) return -1;
    temperature = (int32_t)data[0] | ((int32_t)data[1] << 8) | ((int32_t)data[2] << 16);
    if (temperature & 0x800000) temperature |= (int32_t)0xFF000000;
    pressure = (uint32_t)data[3] | ((uint32_t)data[4] << 8) | ((uint32_t)data[5] << 16);
    *temperature_c = (float)temperature / 65536.0f;
    *pressure_pa = (float)pressure / 64.0f;
    return 0;
}

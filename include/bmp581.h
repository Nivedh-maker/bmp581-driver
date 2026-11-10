#ifndef BMP581_H
#define BMP581_H

#include <stdint.h>

/* Give these two functions to bmp581_begin(). Return 0 when successful. */
typedef int (*bmp581_read_function)(uint8_t reg, uint8_t *data, uint8_t length);
typedef int (*bmp581_write_function)(uint8_t reg, uint8_t value);

/* Check that a BMP581 is connected. */
int bmp581_begin(bmp581_read_function read, bmp581_write_function write);

/* Start taking pressure and temperature readings at 10 times per second. */
int bmp581_start(void);

/* Get the latest readings. Pressure is in Pa; temperature is in degrees C. */
int bmp581_read(float *pressure_pa, float *temperature_c);

#endif

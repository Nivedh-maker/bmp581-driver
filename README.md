# BMP581 barometer driver

This lightweight C driver reads pressure and temperature from a Bosch BMP581 barometric pressure sensor using I2C.

```c
float pressure;
float temperature;

bmp581_begin(my_i2c_read, my_i2c_write);
bmp581_start();
bmp581_read(&pressure, &temperature);
```

`pressure` is in pascals and `temperature` is in degrees Celsius. The BMP581 I2C address is normally `0x46` or `0x47`.

## What the code does

The driver talks to a BMP581 barometer sensor and gives your program two readings:

- Air pressure in pascals (`pressure`)
- Temperature in degrees Celsius (`temperature`)

Call `bmp581_begin()` first. It connects the driver to your board's I2C read and write functions, then checks that a BMP581 sensor is connected. It returns `0` when successful and `-1` if there is a problem.

Call `bmp581_start()` once to tell the sensor to measure pressure and temperature continuously, ten times per second.

Call `bmp581_read(&pressure, &temperature)` whenever you need data. The BMP581 sends compact raw numbers, and the driver converts them into normal values such as `101325.0` Pa and `22.5` degrees Celsius.

You must write `my_i2c_read` and `my_i2c_write` for your particular microcontroller. Those functions send and receive the sensor data over I2C.

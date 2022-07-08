#ifndef TEMP_SENSOR_H_
#define TEMP_SENSOR_H_

#include <cstdint>

class TempSensor
{
public:
    // Return temperature in degrees C
    virtual float getTempFloat () = 0;

    // Return signed integer temperature in 1/128 deg C per bit
    virtual int16_t getTemp () = 0;
};


#endif // TEMP_SENSOR_H_

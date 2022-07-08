#ifndef MCP9808_H_
#define MCP9808_H_

#include "pico/stdlib.h"
#include "src/include/temp_sensor.h"
#include "hardware/i2c.h"

class MCP9808 : public TempSensor
{
private:
    //hardware registers

    const uint8_t REG_POINTER = 0x00;
    const uint8_t REG_CONFIG = 0x01;
    const uint8_t REG_TEMP_UPPER = 0x02;
    const uint8_t REG_TEMP_LOWER = 0x03;
    const uint8_t REG_TEMP_CRIT = 0x04;
    const uint8_t REG_TEMP_AMB = 0x05;
    const uint8_t REG_RESOLUTION = 0x08;

    uint8_t i2c_address;
    i2c_inst_t * i2CInst;

public:
    MCP9808 (uint8_t i2c_address, uint8_t sda_pin, uint8_t scl_pin, i2c_inst_t * i2CInst)
            : i2c_address(i2c_address), i2CInst(i2CInst)
    {
        i2c_init(i2CInst, 400000);

        gpio_set_function(sda_pin, GPIO_FUNC_I2C);
        gpio_set_function(scl_pin, GPIO_FUNC_I2C);

        gpio_pull_up(sda_pin);
        gpio_pull_up(scl_pin);

        uint8_t tx_buf [3];

        tx_buf[0] = REG_RESOLUTION;
        tx_buf[1] = 0b11;       //  Resultion to set

        i2c_write_blocking(i2CInst, i2c_address+1, tx_buf, 2, true);

    }

    ~MCP9808()
    {
        i2c_deinit(i2CInst);
    }

    // Return temperature in degrees C
    float getTempFloat () override
    {
        return (float) getTemp() / 128.0;
    }

    // Return signed integer temperature in 1/128 deg C per bit
    int16_t getTemp () override
    {
        uint8_t buf[2];

        // Start reading ambient temperature register for 2 bytes
        i2c_write_blocking(i2CInst, i2c_address, &REG_TEMP_AMB, 1, true);
        i2c_read_blocking(i2CInst, i2c_address, buf, 2, false);

        uint16_t upper_byte = buf[0] & 0x1F;
        uint16_t lower_byte = buf[1] & 0xFF;

        return (int16_t) ( ( (upper_byte << 11) | (lower_byte << 3) ) & 0xFFF8 );
    }
};

#endif
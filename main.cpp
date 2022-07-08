#include "pico/stdlib.h"
#include <iostream>
#include "src/include/fan.h"
#include "mcp9808.hpp"
#include "src/include/fan_controller.h"

// Instructions from serial
enum
{
    instrGetOnOff = 0,
    instrSwitchOn = 1,
    instrSwitchOff = 2,
    instrGetSpeed = 3,
    instrGetTemp = 4,
    instrFullBlast = 5,
    instrUnFullBlast = 6
};

int main() {
    stdio_init_all();

    auto fan = Fan (19);
    auto mcp9808 = MCP9808 (0x18, 14, 15, &i2c1_inst);

    auto fan_ctrl = FanController (&fan, &mcp9808);

    while (true)
    {
        fan_ctrl.update();

        printf("{\"temperature\": %f,\"fan_pc\": %d}\n", mcp9808.getTempFloat(), fan.getPercent());

        // Update every 1/2 second
        int received_char = getchar_timeout_us (500000);

        switch (received_char - '0')
        {
            default:
            case PICO_ERROR_TIMEOUT:
                break;

            // Act upon received instruction
            case instrGetOnOff:
                // Return 0 if on or 1 if off
                printf("%d\n", !fan_ctrl.isFanRunning());
                break;

            case instrSwitchOff:
                fan_ctrl.switchOff();
                break;

            case instrSwitchOn:
                fan_ctrl.switchOn();
                break;

            case instrGetSpeed:
                // Return if on or off
                printf("%d\n", fan.getPercent());
                break;

            case instrGetTemp:
                // Return if on or off
                printf("%f\n", mcp9808.getTempFloat());
                break;

            case instrFullBlast:
                fan_ctrl.fullBlast();
                break;

            case instrUnFullBlast:
                fan_ctrl.unFullBlast();
                break;
        }

        // sleep_ms(499);
    }

    return 0;
}

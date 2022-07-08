cmake_minimum_required(VERSION 3.13)

include(lib/pico-sdk/pico_sdk_init.cmake)

project(fan_controller)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

add_executable(fan_example
    main.cpp
        src/fan.cpp
        mcp9808.hpp
        src/fan_controller.cpp
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(fan_example pico_stdlib hardware_pwm hardware_i2c)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(fan_example)

# Enable USB serial
pico_enable_stdio_usb(fan_example 1)
pico_enable_stdio_uart(fan_example 0)
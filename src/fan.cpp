#include "include/fan.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"

Fan::Fan (unsigned int gpio_pwm)
        : gpio_pwm(gpio_pwm)
{
    gpio_set_function(gpio_pwm, GPIO_FUNC_PWM);

    uint8_t slice_num = pwm_gpio_to_slice_num(gpio_pwm);
    uint8_t channel = pwm_gpio_to_channel(gpio_pwm);

    // Go to 25 kHz
    pwm_set_clkdiv_int_frac(slice_num, 5, 0);

    // granularity 1%
    pwm_set_wrap(slice_num, 99);

    // Set to 0% to start
    pwm_set_chan_level(slice_num, channel, 0);
    pwm_percent = 0;

    pwm_set_enabled(slice_num, true);
}

void Fan::setPercent (uint8_t p)
{
    pwm_percent = p;

    pwm_set_gpio_level(gpio_pwm, p);
}

FanWithMOSFET::FanWithMOSFET (uint8_t gpio_pwm, uint8_t gpio_dc)
        : gpio_dc(gpio_dc), Fan(gpio_pwm)
{
    gpio_init(gpio_dc);

    gpio_set_dir(gpio_dc, GPIO_OUT);

    // start off
    turnOff();
}

void FanWithMOSFET::turnOff () const
{
    gpio_put(gpio_dc, false);
}

void FanWithMOSFET::turnOn () const
{
    gpio_put(gpio_dc, true);
}

void FanWithMOSFET::setPercent (uint8_t p)
{
    pwm_percent = p;

    pwm_set_gpio_level(gpio_pwm, p);

    if (p == 0)
    {
        turnOff();
    } else
    {
        turnOn();
    }
}

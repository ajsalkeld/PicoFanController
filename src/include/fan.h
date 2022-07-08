#ifndef FAN_H_
#define FAN_H_

#include <cstdint>

class Fan
{
protected:
    uint8_t gpio_pwm;
    uint8_t pwm_percent;

public:
    explicit Fan (unsigned int gpio_pwm);

    // ~Fan ();

    virtual void setPercent (uint8_t p);

    uint8_t getPercent () const   { return pwm_percent; };

    // void monitorRPM ();
};

class FanWithMOSFET : public Fan
{
protected:
    uint8_t gpio_dc;

public:
    FanWithMOSFET (uint8_t gpio_pwm, uint8_t gpio_dc);

    void setPercent (uint8_t p) override;

    void turnOn () const;

    void turnOff () const;
};


#endif // FAN_H_

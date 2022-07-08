#ifndef FAN_CONTROLLER_FAN_CONTROLLER_H
#define FAN_CONTROLLER_FAN_CONTROLLER_H

#include "fan.h"
#include "temp_sensor.h"

class FanController
{
private:
    Fan * fan;
    TempSensor * tempSensor;

    bool fanCtrlerIsRunning;

public:
    FanController (Fan * fan, TempSensor * tempSensor);

    // Update fan speeds (call in a loop)
    void update ();

    // Switch off
    void switchOff ();

    // Switch on
    void switchOn ();

    // Get state
    bool isFanRunning ();

    // Go full speed
    void fullBlast ();
    void unFullBlast () { switchOn(); };

};


#endif //FAN_CONTROLLER_FAN_CONTROLLER_H

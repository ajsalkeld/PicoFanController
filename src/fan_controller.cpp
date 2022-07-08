#include "include/fan_controller.h"

FanController::FanController (Fan * fan, TempSensor * tempSensor)
    : fan(fan), tempSensor(tempSensor)
{
    fanCtrlerIsRunning = true;
}

void FanController::update ()
{
    int16_t temperature = tempSensor->getTemp();

    if (!fanCtrlerIsRunning) return;  // Keep fan off

    switch (temperature)
    {
        case 0 ... 23*128:
            fan->setPercent(0);
            break;

        case (23*128 +1) ... 35*128:
            fan->setPercent(10*temperature/128 - 250);
            break;

        default:
            fan->setPercent(100);
            break;
    }
}

bool FanController::isFanRunning()
{
    return fanCtrlerIsRunning;
}

void FanController::switchOff()
{
    fanCtrlerIsRunning = false;

    fan->setPercent(0);
}

void FanController::switchOn()
{
    fanCtrlerIsRunning = true;
}

void FanController::fullBlast ()
{
    fanCtrlerIsRunning = false;

    fan->setPercent(100);
}
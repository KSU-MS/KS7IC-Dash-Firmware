// Have to use FastLED because the pins I am using
// 


#include <Arduino.h>
#include "IC_Dash.h"
#include "Metro.h"


uint16_t rpm = 0;

Metro timer = Metro(3);

void setup()
{
    IC_Dash_->initDashLEDs();
}


void loop()
{
    if (timer.check())
    {
        IC_Dash_->handleTachometer(rpm); // Testing tach and indi LEDs
        //rpm++;       
    }
    
    rpm++;

    delayMicroseconds(50);

    if (rpm >= 12000)
    {
        rpm = 0;
    }
}


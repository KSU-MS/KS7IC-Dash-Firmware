// Have to use FastLED because the pins I am using
// 


#include <Arduino.h>
#include "IC_Dash.h"


uint16_t rpm = 0;


void setup()
{
    IC_Dash_->initDashLEDs();
}


void loop()
{
    IC_Dash_->handleTachometer(rpm); // Testing tach and indi LEDs
    
    rpm++;

    if (rpm >= 512)
    {
        rpm = 0;
    }
    Serial.println("Hey!");
}


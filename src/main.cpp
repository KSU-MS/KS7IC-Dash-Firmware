// Have to use FastLED because the pins I am using
// 


#include <Arduino.h>
#include <NeoPixelBus.h>

#include "IC_Dash.h"




void setup()
{
    IC_Dash_->initDashLEDs();
}


void loop()
{
    IC_Dash_->funkyLEDs(); // Testing tach and indi LEDs
    delay(1000);
}


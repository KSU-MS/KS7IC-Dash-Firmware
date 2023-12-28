
#include <Arduino.h>
#include "IC_Dash.h"




void setup()
{
    IC_Dash_->initDashLEDs();
}


void loop()
{
    IC_Dash_->funkyLEDs(); // Testing tach LEDs
    delay(1000);
}

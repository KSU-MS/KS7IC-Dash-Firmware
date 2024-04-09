
#include "IC_Dash.h"
#include "IC_Can.h"
#include "Metro.h"


// uint16_t rpm = 0;
// uint8_t gear = 0;
// uint8_t stat = 0;

Metro main_ = Metro(200);
Metro  can_ = Metro(100);


void setup()
{
    Serial.begin(9600);

    // while (!Serial); // Wait for serial connection before proceeding

    IC_Dash_ = new IC_Dash();
     IC_Can_ = new  IC_Can();

    initDash(IC_Dash_);

    IC_Dash_->blinkStatusLed();
}


void loop()
{ 
    if (can_.check())
    {
        IC_Can_->read_Can(IC_Dash_);
    }
    
    if (main_.check())
    {
        IC_Dash_->dashDriver();
    }
}

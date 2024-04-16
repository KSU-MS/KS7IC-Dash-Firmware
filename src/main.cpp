
#include "IC_Dash.h"
#include "IC_Can.h"
#include "Metro.h"



Metro main_ = Metro(1000);
Metro tach_ = Metro(50);



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
    IC_Can_->read_Can(IC_Dash_);
    
    if (main_.check())
    {
        IC_Dash_->handleCoolantTemp();
        IC_Dash_->handleGear();
        IC_Dash_->handleCheckEngine();
    }

    if (tach_.check())
    {
        IC_Dash_->handleTachometer();
    }
}

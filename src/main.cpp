
#include "IC_Dash.h"
#include "Metro.h"



Metro main_ = Metro(MAIN_METRO_INT);
Metro tach_ = Metro(TACH_METRO_INT);



void setup()
{
    Serial.begin(9600);

    // while (!Serial); // Wait for serial connection before proceeding

    IC_Dash_.initCan();
    IC_Dash_.initDash();

    // IC_Dash_.blinkStatusLed();
}


void loop()
{ 
    IC_Dash_.read_Can();

    IC_Dash_.handleTachometer();
    
    if (main_.check())
    {
        IC_Dash_.handleCoolantTemp();
        IC_Dash_.handleGear();
        IC_Dash_.handleCheckEngine();
    }

    // if (tach_.check())
    // {
    //     IC_Dash_.handleTachometer();
    // }
}

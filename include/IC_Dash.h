
#ifndef IC_DASH.H
#define IC_DASH.H



#include <FastLED.h>
#include "IC_Dash_utils.h"


// BABABOOEY


class IC_Dash
{
private:

    CRGB tachLEDs[TACH_LEDS];
    CRGB indiLEDs[INDI_LEDS];

public:

     IC_Dash();
    ~IC_Dash();

    void initDashLEDs();
    void funkyLEDs(); // Tach and Indi test function

};



static IC_Dash* IC_Dash_ = new IC_Dash();




#endif



#ifndef IC_DASH .H
#define IC_DASH .H

#include <Arduino.h>


#include <FastLED.h>
#include "IC_Dash_utils.h"


// BABABOOEY

class IC_Dash
{
private:

    CRGB tachLEDs[TACH_LEDS] = { 0 };
    CRGB indiLEDs[INDI_LEDS] = { 0 };

public:

     IC_Dash();
    ~IC_Dash();

    void initDashLEDs();
    void handleTachometer(uint16_t rpm);

};



static IC_Dash* IC_Dash_ = new IC_Dash();




#endif



#ifndef IC_DASH.H
#define IC_DASH.H


#include <Arduino.h>
#include <FastLED.h>

#include "IC_Dash_utils.h"




// BABABOOEY

class IC_Dash
{
private:

    CRGB tachLEDs[TACH_LEDS] = { 0 };
    CRGB indiLEDs[INDI_LEDS] = { 0 };

    uint16_t rpm = 0;
    uint8_t gear = 0;

public:

     IC_Dash();
    ~IC_Dash();

    void initDashLEDs();

    void handleTachometer(uint16_t rpm);
    void handleGear(uint8_t num);

    void setRPM(uint16_t rpm_);
    void setGEAR(uint8_t gear_);

    uint16_t getRPM();
    uint8_t getGEAR();
};


static IC_Dash* IC_Dash_ = new IC_Dash();

// static IC_Dash_t* IC_Dash_t_;


#endif


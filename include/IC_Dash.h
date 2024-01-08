
#ifndef IC_DASH.H
#define IC_DASH.H


#include <Arduino.h>
#include <FastLED.h>

#include "IC_Dash_utils.h"


// BABABOOEY

class IC_Dash
{
private:

    CRGB tachLEDs[TACH_LEDS] = {CRGB::Black};
    CRGB statLEDs[STAT_LEDS] = {CRGB::Black};

    uint16_t    rpm;
    uint8_t    gear;
    uint8_t  status;

public:

     IC_Dash(uint16_t _rpm_ = 0, uint8_t _gear_ = 0, uint8_t _status_ = 0);
    ~IC_Dash();

    void initDashLEDs();

    void handleDashTachometer(uint16_t _rpm_);
    void handleDashGear(uint8_t _num_);
    void handleDashStatus(uint8_t _status_);

    void setRPM(uint16_t _rpm_);
    void setGEAR(uint8_t _gear_);
    void setSTATUS(uint8_t _status_);

    uint16_t getRPM();
    uint8_t getGEAR();
    uint8_t getSTATUS();
};


static CFastLED tachLEDs_;
static CFastLED indiLEDs_;

static IC_Dash* IC_Dash_;

void initDash(IC_Dash* _ic_dash_);


#endif


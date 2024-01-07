
#ifndef IC_DASH.H
#define IC_DASH.H



#include <FastLED.h>
#include "IC_Dash_utils.h"


// BABABOOEY


class IC_Dash
{
private:

    uint16_t rpm = 0;
    uint8_t gear = 0;

public:

     IC_Dash();
    ~IC_Dash();


    void setRPM(uint16_t rpm_);
    void setGEAR(uint8_t gear_);

};



static IC_Dash* IC_Dash_ = new IC_Dash();

// static IC_Dash_t* IC_Dash_t_;


#endif


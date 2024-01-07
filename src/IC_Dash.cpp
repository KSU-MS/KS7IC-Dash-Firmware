
#include <Arduino.h>

#include "IC_Dash.h"
#include <FastLED.h>


IC_Dash::IC_Dash()
{
    
}

IC_Dash::~IC_Dash()
{
    
}


void IC_Dash::setRPM(uint16_t rpm_)
{
    this->rpm = rpm_;
}

void IC_Dash::setGEAR(uint8_t gear_)
{
    this->gear = gear_;
}


uint16_t IC_Dash::getRPM()
{
    return this->rpm;
}

uint8_t IC_Dash::getGEAR()
{
    return this->gear;
}
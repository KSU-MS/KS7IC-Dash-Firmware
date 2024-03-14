
#ifndef IC_DASH.H
#define IC_DASH.H


#include <Arduino.h>
#include <FastLED.h>

#include "IC_Dash_utils.h"


// BABABOOEY

class IC_Dash
{
private:

    const char Yippie_[12] = "Y i p p i e";

    CRGB tachLEDs[TACH_LEDS] = {CRGB::Black};
    CRGB statLEDs[STAT_LEDS] = {CRGB::Black};

    const uint32_t sevenSegNumPack[11] = {SEG_NUM_0, SEG_NUM_1, SEG_NUM_2,
                                          SEG_NUM_3, SEG_NUM_4, SEG_NUM_5,
                                          SEG_NUM_6, SEG_NUM_7, SEG_NUM_8,
                                          SEG_NUM_9, SEG_NUM_C};

    uint16_t    rpm;
    uint8_t    gear;
    uint8_t  status;

    uint16_t coolantTemp;
    uint16_t     oilTemp;

public:

     IC_Dash(uint16_t _rpm_ = 0, uint8_t _gear_ = 0, uint8_t _status_ = 0);
    ~IC_Dash();

    void initLEDs();
    void Yippie();
    void blinkStatusLed();

    void handleTachometer();
    void handleGear();
    void handleStatus(uint8_t _status_);

    void setRPM(uint8_t* _rpm_);
    void setGEAR(uint8_t _gear_);
    // void setSTATUS(uint8_t _status_);
    void setCoolantTemp(uint8_t* _coolantTemp_);

    uint16_t getRPM();
    uint8_t getGEAR();
    // uint8_t getSTATUS();
};


static CFastLED tachLEDs_;
static CFastLED statLEDs_;

static IC_Dash* IC_Dash_;

void initDash(IC_Dash* _ic_dash_);


#endif


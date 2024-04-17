
#ifndef IC_DASH.H
#define IC_DASH.H


#include <Arduino.h>
#include <FastLED.h>
#include <FlexCAN_T4.h>

#include "IC_Dash_utils.h"


// Oil Pressure Analog IN 5
// 

// Helper for Dash data
typedef struct IC_DashGuy
{
    uint8_t    gear;
    uint16_t    rpm;

    uint16_t       coolantTemp;
    uint16_t           oilTemp;
    uint16_t    batteryVoltage;
    uint16_t checkEngineStatus;

} IC_DashGuy;


// BAABAA-BOOEY
class IC_Dash
{
private:

    CRGB tachLEDs[TACH_LEDS];
    CRGB statLEDs[STAT_LEDS];

    IC_DashGuy DashGuy_;

    uint8_t height = 0;

    void set_RPM(uint8_t _byte_H_, uint8_t _byte_L_);
    void set_GEAR(uint8_t _gear_);
    void set_CoolantTemp(uint8_t _byte_H_, uint8_t _byte_L_);
    void set_BatteryVoltage(uint8_t _byte_H_, uint8_t _byte_L_);
    void set_CheckEngineStatus(uint8_t _byte_H_, uint8_t _byte_L_);
    
public:

     IC_Dash(uint16_t _rpm_ = 0, uint8_t _gear_ = 0, uint8_t _status_ = 0,
             uint16_t _coolantTemp_ = 0, uint16_t _oilTemp_ = 0, uint16_t _batteryVoltage_ = 0,
             uint16_t _checkEngineStatus_ = 0);

    ~IC_Dash();

    void initDash();
    void initCan(); 

    void read_Can();

    void handleTachometer();
    void handleGear();
    void handleCoolantTemp();
    void handleCheckEngine();

    void initLEDs();
    void Yippie();

    void blinkStatusLed();

    uint16_t getRPM();
    uint8_t getGEAR();
};


static CFastLED tachLEDs_;
static CFastLED statLEDs_;

static IC_Dash IC_Dash_;

static FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> IC_CAN_ORG;

void initDash();
void initCan();


#endif


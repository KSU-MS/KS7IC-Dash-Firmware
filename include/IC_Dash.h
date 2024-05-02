
#ifndef IC_DASH.H
#define IC_DASH.H


#include <Arduino.h>
#include <FastLED.h>
#include <FlexCAN_T4.h>

#include "IC_Dash_utils.h"
#include "shift_points.h"
#include "ksu_device_status.h"
#include "ksu_ev_can.h"


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
    uint16_t       oilPressure;

} IC_DashGuy;

typedef struct shiftLightBlink_t
{
    elapsedMillis shiftLightBlinkTime = 0;
    bool light_on = 0;
} shiftLightBlink_t;


// BAABAA-BOOEY
class IC_Dash
{
private:

    CRGB tachLEDs[TACH_LEDS];
    CRGB statLEDs[STAT_LEDS];

    IC_DashGuy DashGuy_;

    uint8_t height = 0;
    shiftLightBlink_t shiftLightBlinker;
    bool _time_to_shift;
    device_status_t _dash_status;
    can_obj_ksu_ev_can_h_t ksu_can;
    void set_RPM(uint8_t _byte_H_, uint8_t _byte_L_);
    void set_GEAR(uint8_t _gear_);
    void set_CoolantTemp(uint8_t _byte_H_, uint8_t _byte_L_);
    void set_BatteryVoltage(uint8_t _byte_H_, uint8_t _byte_L_);
    void set_CheckEngineStatus(uint8_t _byte_H_, uint8_t _byte_L_);
    void set_OilPressure(uint8_t _byte_H_, uint8_t _byte_L_);
    void ramp_colors_fancy_shift(CRGB startcol, CRGB endcol,CRGB backcolor,int minrpm = 10000, int maxrpm = 11000);
    void initLEDs();
    void Yippie();
    
public:

     IC_Dash(uint16_t _rpm_ = 0, uint8_t _gear_ = 0, uint8_t _status_ = 0,
             uint16_t _coolantTemp_ = 0, uint16_t _oilTemp_ = 0, uint16_t _batteryVoltage_ = 0,
             uint16_t _checkEngineStatus_ = 0, uint16_t _oilPressure_ = 0);

    ~IC_Dash();

    void initDash();
    void initCan(); 

    void read_Can();
    void send_device_status();
    void handleTachometer();
    void handleGear();
    void handleCoolantTempLight();
    void handleCheckEngineLight();
    void handleOilPressureLight();
    int unpack_flexcan_message(CAN_message_t &msg)
    {
        uint64_t data;
        memcpy(&data, msg.buf, sizeof(msg.buf));
        return unpack_message(&ksu_can, msg.id, data, msg.len, millis());
    }
    void blinkStatusLed();
    void setRpm(uint16_t rpm)
    {
        DashGuy_.rpm = rpm;
    }

    // uint16_t getRPM();
    // uint8_t getGEAR();
};


static CFastLED tachLEDs_;
static CFastLED statLEDs_;

static IC_Dash IC_Dash_;

static FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> IC_CAN_ORG;
static FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> IC_CAN_DUP;

void initDash();
void initCan();


#endif


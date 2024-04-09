

#include "IC_Dash.h"
//#include "IC_Can.h"





IC_Dash::IC_Dash(uint16_t _rpm_ = 0, uint8_t _gear_ = 0, uint8_t _status_ = 0,
                 uint16_t _coolantTemp_ = 0, uint16_t _oilTemp_ = 0, uint16_t _batteryVoltage_ = 0,
                 uint16_t _checkEngineStatus_ = 0)
{
    // Probably not idealy how you should do this but whomp whomp.
    
    this->DashGuy_.gear =   _gear_;
    this->DashGuy_.rpm  =    _rpm_;
    // this->status        = _status_;

    this->DashGuy_.coolantTemp       =       _coolantTemp_;
    this->DashGuy_.oilTemp           =           _oilTemp_;
    this->DashGuy_.batteryVoltage    =    _batteryVoltage_;
    this->DashGuy_.checkEngineStatus = _checkEngineStatus_;


    // Serial.println("Initializing DASH..");
}

IC_Dash::~IC_Dash()
{
    // This Class should never go out of scope.
    // Serial.println("Bye Bye..");
}


void IC_Dash::dashDriver()
{
    this->handleTachometer();
    this->handleCoolantTemp();
}


void IC_Dash::initLEDs()
{
    tachLEDs_.addLeds<WS2812, TACH_DPIN, GRB>(this->tachLEDs, TACH_LEDS);
    statLEDs_.addLeds<WS2812, INDI_DPIN, GRB>(this->statLEDs, STAT_LEDS);
    tachLEDs_.setMaxPowerInVoltsAndMilliamps(5, 200);
    statLEDs_.setMaxPowerInVoltsAndMilliamps(5, 200);
    tachLEDs_.setBrightness(LED_MAX_BRIGHTNESS);
    statLEDs_.setBrightness(LED_MAX_BRIGHTNESS);
    tachLEDs_.setMaxRefreshRate(LED_MAX_REFRESHRATE);
    statLEDs_.setMaxRefreshRate(LED_MAX_REFRESHRATE);
}

void IC_Dash::Yippie()
{
    CRGB* tach_leds = this->tachLEDs;
    CRGB* stat_leds = this->statLEDs;

    for (uint8_t i = 0; i < TACH_LEDS; i++)
    {
        tach_leds[i] = CRGB::Red;
        tachLEDs_.show();
        delay(100);
    }
    for (uint8_t i = 0; i < STAT_LEDS; i++)
    {
        stat_leds[i] = CRGB::Red;
        statLEDs_.show();
        delay(100);
    }

    fill_solid(tach_leds, TACH_LEDS, CRGB::Black);
    fill_solid(stat_leds, TACH_LEDS, CRGB::Black);
    tachLEDs_.show();
    statLEDs_.show();
}

void IC_Dash::blinkStatusLed()
{
    digitalWrite(STATUS_LED, HIGH);
    delay(50);
    digitalWrite(STATUS_LED, LOW);
}


void IC_Dash::handleTachometer()
{
    CRGB* leds = this->tachLEDs;

    int height = map(this->DashGuy_.rpm, 0, MAX_RPM, 0, TACH_LEDS + 1);

    fill_gradient(leds, TACH_LEDS - 1, CHSV(0, 255, 255), 0, CHSV(70, 255, 255), SHORTEST_HUES);

    for (int i = 0; i < TACH_LEDS; i++) 
    {
        if (i >= height)
        {
            leds[i] = CRGB::Black;
        }
    }

    tachLEDs_.show();
}

void IC_Dash::handleGear()
{
    digitalWrite(GEAR_EN, LOW);

    delayMicroseconds(200);

    bool led_a_high = this->DashGuy_.gear & 0b0001;
    bool led_b_high = this->DashGuy_.gear & 0b0010;
    bool led_c_high = this->DashGuy_.gear & 0b0100;
    bool led_d_high = this->DashGuy_.gear & 0b1000;

    digitalWrite(BCD_A, led_a_high);
    digitalWrite(BCD_B, led_b_high);
    digitalWrite(BCD_C, led_c_high);
    digitalWrite(BCD_D, led_d_high);

    delayMicroseconds(200);
    digitalWrite(GEAR_EN, HIGH);
    delayMicroseconds(200);
    digitalWrite(GEAR_EN, LOW);
}

// void IC_Dash::handleStatus(uint8_t _status_)
// {
//     CRGB* leds = this->statLEDs;

//     uint8_t mask;

//     fill_solid(leds, STAT_LEDS, CRGB::Black);

//     for (uint8_t bit = 0; bit < STAT_LEDS; bit++)
//     {
//         mask = (1 << bit);

//         switch (_status_ & mask)
//         {
//         case _IC_NO_STATUS_:
//             break;
//         case _IC_OIL_PRESSURE_:
//             leds[0] = CRGB::Red;
//             break;
//         case _IC_OIL_TEMP_:
//             leds[1] = CRGB::Red;
//             break;
//         case _IC_LAUNCH_CONTROL_:
//             leds[2] = CRGB::Blue;
//             break;
//         case _IC_COOLANT_TEMP_:
//             leds[3] = CRGB::Red;
//             break;
//         case _IC_CHECK_ENG_:
//             leds[4] = CRGB::Orange;
//             break;
//         default:
//             break;
//         }
//     }

//     statLEDs_.show();    
// }

void IC_Dash::handleCoolantTemp()
{
    CRGB* leds = this->statLEDs;

    if (this->DashGuy_.coolantTemp < 180.0f)
    {
        leds[3] = CRGB::Blue;
    }
    else if (this->DashGuy_.coolantTemp >= 180.0f || 
             this->DashGuy_.coolantTemp < 220.0f)
    {
        leds[3] = CRGB::Black;
    }
    else if (this->DashGuy_.coolantTemp >= 220.0f ||
             this->DashGuy_.coolantTemp <= 240.0f)
    {
        leds[3] = CRGB::Yellow;
    }
    else leds[3] = CRGB::Red;

    statLEDs_.show();
}


void IC_Dash::set_RPM(uint8_t _byte_H_, uint8_t _byte_L_)
{
    uint16_t can_rpm = 0;

    can_rpm |= (_byte_H_ << 8);
    can_rpm |= (_byte_L_);

    this->DashGuy_.rpm = can_rpm;
}

void IC_Dash::set_GEAR(uint8_t _gear_)
{
    this->DashGuy_.gear = _gear_;
}

// void IC_Dash::setSTATUS(uint8_t _status_)
// {
//     this->status = _status_;
// }

void IC_Dash::set_CoolantTemp(uint8_t _byte_H_, uint8_t _byte_L_)
{
    uint16_t can_coolantTemp = 0;

    can_coolantTemp |= (_byte_H_ << 8);
    can_coolantTemp |= (_byte_L_);

    this->DashGuy_.coolantTemp = can_coolantTemp;
}

void IC_Dash::set_BatteryVoltage(uint8_t _byte_H_, uint8_t _byte_L_)
{
    uint16_t can_batteryVoltage = 0;

    can_batteryVoltage |= (_byte_H_ << 8);
    can_batteryVoltage |= (_byte_L_);

    this->DashGuy_.batteryVoltage = can_batteryVoltage;
}

void IC_Dash::set_CheckEngineStatus(uint8_t _byte_H_, uint8_t _byte_L_)
{
    uint16_t can_checkEngineStatus = 0;

    can_checkEngineStatus |= (_byte_H_ << 8);
    can_checkEngineStatus |= (_byte_L_);

    this->DashGuy_.checkEngineStatus = can_checkEngineStatus;
}


uint16_t IC_Dash::getRPM()
{
    return this->DashGuy_.rpm;
}

uint8_t IC_Dash::getGEAR()
{
    return this->DashGuy_.gear;
}

// uint8_t IC_Dash::getSTATUS()
// {
//     return this->status;
// }


void initDash(IC_Dash* _ic_dash_)
{
    pinMode(LOWV_EN, OUTPUT);
    pinMode(GEAR_EN, OUTPUT);

    pinMode(BCD_A, OUTPUT);
    pinMode(BCD_B, OUTPUT);
    pinMode(BCD_C, OUTPUT);
    pinMode(BCD_D, OUTPUT);

    pinMode(STATUS_LED, OUTPUT);

    digitalWrite(LOWV_EN, HIGH);

    delayMicroseconds(500);

    _ic_dash_->initLEDs();
    _ic_dash_->Yippie();

    // Serial.println("Starting DASH..");
}

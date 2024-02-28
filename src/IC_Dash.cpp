

#include "IC_Dash.h"
#include "IC_Can.h"





IC_Dash::IC_Dash(uint16_t _rpm_ = 0, uint8_t _gear_ = 0, uint8_t _status_ = 0)
{
       this->rpm =    _rpm_;
      this->gear =   _gear_;
    this->status = _status_;

    Serial.println("Initializing DASH..");
}

IC_Dash::~IC_Dash()
{
    Serial.println("Bye Bye..");
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

    // Turn on lights
    fill_solid(this->statLEDs, STAT_LEDS, CRGB::Red);
    this->statLEDs[2] = CRGB::Blue;
}

void IC_Dash::blinkStatusLed()
{
    digitalWrite(STATUS_LED, HIGH);
    delay(2000);
    digitalWrite(STATUS_LED, LOW);
}


void IC_Dash::handleTachometer(uint16_t _rpm_)
{
    CRGB* leds = this->tachLEDs;

    int height = map(_rpm_, 0, MAX_RPM, 0, TACH_LEDS + 1);

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

void IC_Dash::handleGear(uint8_t _num_)
{
    digitalWrite(GEAR_EN, LOW);
    delayMicroseconds(100);

    // I wish I could directly manipulate the ports because
    // it would make this so much simpler but I picked pins 
    // that did not belong to an emulated port on the teensy. 
    // Something I need to take into consideration next time.
    
    switch (_num_)
    {
    case 0:
        digitalWrite(BCD_A, LOW);
        digitalWrite(BCD_B, LOW);
        digitalWrite(BCD_C, LOW);
        digitalWrite(BCD_D, LOW);
        break;
    case 1:
        digitalWrite(BCD_A, HIGH);
        digitalWrite(BCD_B, LOW);
        digitalWrite(BCD_C, LOW);
        digitalWrite(BCD_D, LOW);
        break;
    case 2:
        digitalWrite(BCD_A, LOW);
        digitalWrite(BCD_B, HIGH);
        digitalWrite(BCD_C, LOW);
        digitalWrite(BCD_D, LOW);
        break;
    case 3:
        digitalWrite(BCD_A, HIGH);
        digitalWrite(BCD_B, HIGH);
        digitalWrite(BCD_C, LOW);
        digitalWrite(BCD_D, LOW);
        break;
    case 4:
        digitalWrite(BCD_A, LOW);
        digitalWrite(BCD_B, LOW);
        digitalWrite(BCD_C, HIGH);
        digitalWrite(BCD_D, LOW);
        break;
    case 5:
        digitalWrite(BCD_A, HIGH);
        digitalWrite(BCD_B, LOW);
        digitalWrite(BCD_C, HIGH);
        digitalWrite(BCD_D, LOW);
        break;
    case 6:
        digitalWrite(BCD_A, LOW);
        digitalWrite(BCD_B, HIGH);
        digitalWrite(BCD_C, HIGH);
        digitalWrite(BCD_D, LOW);
        break;
    case 7:
        digitalWrite(BCD_A, HIGH);
        digitalWrite(BCD_B, HIGH);
        digitalWrite(BCD_C, HIGH);
        digitalWrite(BCD_D, LOW);
        break;
    case 8:
        digitalWrite(BCD_A, LOW);
        digitalWrite(BCD_B, LOW);
        digitalWrite(BCD_C, LOW);
        digitalWrite(BCD_D, HIGH);
        break;
    case 9:
        digitalWrite(BCD_A, HIGH);
        digitalWrite(BCD_B, LOW);
        digitalWrite(BCD_C, LOW);
        digitalWrite(BCD_D, HIGH);
        break;
    default:
        break;
    }

    delayMicroseconds(100);
    digitalWrite(GEAR_EN, HIGH);
    delayMicroseconds(100);
}

void IC_Dash::handleStatus(uint8_t _status_)
{
    CRGB* leds = this->statLEDs;

    uint8_t mask;

    fill_solid(leds, STAT_LEDS, CRGB::Black);

    for (uint8_t bit = 0; bit < STAT_LEDS; bit++)
    {
        mask = (1 << bit);

        switch (_status_ & mask)
        {
        case _IC_NO_STATUS_:
            break;
        case _IC_OIL_PRESSURE_:
            leds[0] = CRGB::Red;
            break;
        case _IC_OIL_TEMP_:
            leds[1] = CRGB::Red;
            break;
        case _IC_LAUNCH_CONTROL_:
            leds[2] = CRGB::Blue;
            break;
        case _IC_COOLANT_TEMP_:
            leds[3] = CRGB::Red;
            break;
        case _IC_CHECK_ENG_:
            leds[4] = CRGB::Orange;
            break;
        default:
            break;
        }
    }

    statLEDs_.show();    
}


void IC_Dash::setRPM(uint8_t* _rpm_)
{
    uint16_t can_rpm = 0;

    can_rpm |= (_rpm_[6] << 8);
    can_rpm |= _rpm_[7];

    this->rpm = can_rpm;
}

void IC_Dash::setGEAR(uint8_t _gear_)
{
    this->gear = _gear_;
}

// void IC_Dash::setSTATUS(uint8_t _status_)
// {
//     this->status = _status_;
// }

void IC_Dash::setCoolantTemp(uint8_t* _coolantTemp_)
{
    uint16_t can_coolantTemp = 0;

    can_coolantTemp |= (_coolantTemp_[6] << 8);
    can_coolantTemp |= _coolantTemp_[7];

    this->coolantTemp = can_coolantTemp;
}


uint16_t IC_Dash::getRPM()
{
    return this->rpm;
}

uint8_t IC_Dash::getGEAR()
{
    return this->gear;
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

    Serial.println("Starting DASH..");

    tachLEDs_.show();
    statLEDs_.show();
}

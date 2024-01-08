

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


void IC_Dash::initDashLEDs()
{
    tachLEDs_.addLeds<WS2812, TACH_DPIN, GRB>(this->tachLEDs, TACH_LEDS);
    indiLEDs_.addLeds<WS2812, INDI_DPIN, GRB>(this->statLEDs, STAT_LEDS);
    tachLEDs_.setMaxPowerInVoltsAndMilliamps(5, 200);
    indiLEDs_.setMaxPowerInVoltsAndMilliamps(5, 200);
    tachLEDs_.setBrightness(LED_MAX_BRIGHTNESS);
    indiLEDs_.setBrightness(LED_MAX_BRIGHTNESS);
}


void IC_Dash::handleDashTachometer(uint16_t _rpm_)
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

void IC_Dash::handleDashGear(uint8_t _num_)
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

void IC_Dash::handleDashStatus(uint8_t _status_)
{
    CRGB* leds = this->statLEDs;

    fill_solid(leds, STAT_LEDS, CRGB::Black);

    for (int i = 0; i < STAT_LEDS; i++)
    {
        uint8_t mask = 1 << i;

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

    indiLEDs_.show();    
}


void IC_Dash::setRPM(uint16_t _rpm_)
{
    this->rpm = _rpm_;
}

void IC_Dash::setGEAR(uint8_t _gear_)
{
    this->gear = _gear_;
}

void IC_Dash::setSTATUS(uint8_t _status_)
{
    this->status = _status_;
}


uint16_t IC_Dash::getRPM()
{
    return this->rpm;
}

uint8_t IC_Dash::getGEAR()
{
    return this->gear;
}

uint8_t IC_Dash::getSTATUS()
{
    return this->status;
}


void initDash(IC_Dash* _ic_dash_)
{
    pinMode(LOWV_EN, OUTPUT);
    pinMode(GEAR_EN, OUTPUT);

    pinMode(BCD_A, OUTPUT);
    pinMode(BCD_B, OUTPUT);
    pinMode(BCD_C, OUTPUT);
    pinMode(BCD_D, OUTPUT);

    digitalWrite(LOWV_EN, HIGH);

    delayMicroseconds(500);

    _ic_dash_->initDashLEDs();

    Serial.println("Starting DASH..");
}

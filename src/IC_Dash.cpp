

#include "IC_Dash.h"






IC_Dash::IC_Dash(uint16_t _rpm_ = 0, uint8_t _gear_ = 0, uint8_t _status_ = 0,
                 uint16_t _coolantTemp_ = 0, uint16_t _oilTemp_ = 0, uint16_t _batteryVoltage_ = 0,
                 uint16_t _checkEngineStatus_ = 0, uint16_t _oilPressure_ = 0)
{
    // Probably not the most ideal way to do this but whomp whomp.
    
    this->DashGuy_.gear =   _gear_;
    this->DashGuy_.rpm  =    _rpm_;
    // this->status        = _status_;

    this->DashGuy_.coolantTemp       =       _coolantTemp_;
    this->DashGuy_.oilTemp           =           _oilTemp_;
    this->DashGuy_.batteryVoltage    =    _batteryVoltage_;
    this->DashGuy_.checkEngineStatus = _checkEngineStatus_;
    this->DashGuy_.oilPressure       =       _oilPressure_;
}

IC_Dash::~IC_Dash()
{
    // This Class should never go out of scope.
    // Serial.println("Bye Bye..");
}


void IC_Dash::initDash()
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

    this->initLEDs();
    this->Yippie();

    // Serial.println("Starting DASH..");
}


void IC_Dash::initCan()
{
    IC_CAN_ORG.begin();
    IC_CAN_DUP.begin();

    IC_CAN_ORG.setBaudRate(CAN_BAUD_RATE);
    IC_CAN_DUP.setBaudRate(CAN_BAUD_RATE);

    IC_CAN_ORG.setMaxMB(NUM_RXTX_MAILBOXES);
    IC_CAN_DUP.setMaxMB(NUM_RXTX_MAILBOXES);

    for (uint64_t BOX = 0; BOX < NUM_RXTX_MAILBOXES; BOX++)
    {
        IC_CAN_ORG.setMB((FLEXCAN_MAILBOX)BOX, RX, STD);
        IC_CAN_DUP.setMB((FLEXCAN_MAILBOX)BOX, TX, STD);
    }
}


void IC_Dash::read_Can()
{
    // Would like to see if using a switch case versus
    // an if block is better at catching CAN frames.

    // After testing I think this is better ngl

    CAN_message_t _msg_;
    if (IC_CAN_ORG.read(_msg_))
    {
        unpack_flexcan_message(_msg_);
        switch (_msg_.id)
        {
        case _IC_CAN_MSG_GROUP_0_:
            this->set_RPM(_msg_.buf[6], _msg_.buf[7]);
            // Serial.println("RPM");
            break;
        case _IC_CAN_MSG_GROUP_2_:
            this->set_CoolantTemp(_msg_.buf[6], _msg_.buf[7]); 
            // Serial.println("Coolant Temp");
            break;
        // case _IC_CAN_MSG_GROUP_3_:
        //     this->set_BatteryVoltage(_msg_.buf[2], _msg_.buf[3]);
        //     // Serial.println("Battery Voltage");
        //     break;
        case _IC_CAN_MSG_GROUP_14_:
            this->set_OilPressure(_msg_.buf[2], _msg_.buf[3]);
            break;
        case _IC_CAN_MSG_GROUP_33_:
            decode_can_0x611_gear(&ksu_can,&DashGuy_.gear);
            break;  
        case _IC_CAN_MSG_GROUP_54_:
            decode_can_0x626_cel_status(&ksu_can,&DashGuy_.checkEngineStatus);
            break;
        case CAN_ID_MEGASQUIRT_GP52:
            _time_to_shift = ksu_can.can_0x624_megasquirt_gp52.canout & 0x01;
            break;
        case _IC_CAN_MSG_GROUP_60_:
            break;    
        case _IC_CAN_MSG_SHIFT_INDICATOR:
            this->_time_to_shift = _msg_.buf[0];
            break;  
        default:
            break;
        }

    #if _DEBUG_

        // this->.blinkStatusLed();

    #endif
    }
}

// Immediately transmit the dash status
void IC_Dash::send_device_status()
{
    CAN_message_t msg;
    msg.id = 0x666;
    msg.len = sizeof(this->_dash_status);
    _dash_status.on_time_seconds=millis()/1000;
    memcpy(&msg.buf,&_dash_status,sizeof(_dash_status));
    IC_CAN_ORG.write(msg);
}


void IC_Dash::initLEDs()
{
    tachLEDs_.addLeds<WS2812, TACH_DPIN, GRB>(this->tachLEDs, TACH_LEDS);
    statLEDs_.addLeds<WS2812, INDI_DPIN, GRB>(this->statLEDs, STAT_LEDS);
    tachLEDs_.setMaxPowerInVoltsAndMilliamps(5, 500);
    statLEDs_.setMaxPowerInVoltsAndMilliamps(5, 500);
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
    if (this->DashGuy_.rpm < 50)
    {
        this->height = 0;
    }
    else if (this->DashGuy_.rpm >= 50 && this->DashGuy_.rpm <= 4000)
    {
        this->height = 1;
    }
    else {this->height = map(this->DashGuy_.rpm - 4000, 0, MAX_RPM - 4000, 0, TACH_LEDS + 1);}
    if (DashGuy_.rpm > 10000)
    {
        tachLEDs_.setBrightness(128);
    }
    else {tachLEDs_.setBrightness(LED_MAX_BRIGHTNESS);}
    if (this->DashGuy_.rpm >= 10000 && this->DashGuy_.rpm<=11000)
    {
        ramp_colors_fancy_shift(CRGB::Purple,CRGB::Black,CRGB::Black);
        tachLEDs_.show();
    }
    // if shift flag is true or we are above shift rpm for our current gear anyway
    else if ((this->_time_to_shift) || (this->DashGuy_.rpm >= shiftpointmap.at(this->DashGuy_.gear) && this->DashGuy_.rpm <= REDLINE_RPM))
    {
        // If light on is true, we are showing Yellow
        if (shiftLightBlinker.light_on == true)
        {
        fill_solid(this->tachLEDs, TACH_LEDS, CRGB::Yellow);

        // transition when timer has passed 15ms
        if (shiftLightBlinker.shiftLightBlinkTime >= 30)
        {
            // set light_on false and reset timer
            shiftLightBlinker.light_on = false;
            shiftLightBlinker.shiftLightBlinkTime = 0;
        }
        }
        // if light on false, show black
        else if (shiftLightBlinker.light_on == false)
        {
        fill_solid(this->tachLEDs, TACH_LEDS, CRGB::Black);
        if (shiftLightBlinker.shiftLightBlinkTime >= 20)
        {
            shiftLightBlinker.light_on = true;
            shiftLightBlinker.shiftLightBlinkTime = 0;
        }
        }
        tachLEDs_.show(); 
    }
    else if (this->DashGuy_.rpm > REDLINE_RPM)
    {
        // If light on is true, we are showing red
        if (shiftLightBlinker.light_on == true)
        {
        fill_solid(this->tachLEDs, TACH_LEDS, CRGB::Red);
        // transition when timer has passed 40ms
        if (shiftLightBlinker.shiftLightBlinkTime >= 30)
        {
            // set light_on false and reset timer
            shiftLightBlinker.light_on = false;
            shiftLightBlinker.shiftLightBlinkTime = 0;
        }
        }
        // if light on false, show black
        else if (shiftLightBlinker.light_on == false)
        {
        fill_solid(this->tachLEDs, TACH_LEDS, CRGB::Black);
        if (shiftLightBlinker.shiftLightBlinkTime >= 20)
        {
            shiftLightBlinker.light_on = true;
            shiftLightBlinker.shiftLightBlinkTime = 0;
        }
        }
        tachLEDs_.show();
    }
    else
    {
        fill_solid(this->tachLEDs, TACH_LEDS, CRGB::Red);
        fill_solid(this->tachLEDs, TACH_LEDS - 5, CRGB::Green);

        for (int i = 0; i < TACH_LEDS; i++) 
        {
            if (i >= this->height)
            {
                this->tachLEDs[i] = CRGB::Black;
            }
        }
        tachLEDs_.show();
    }
}

// make 0-6 and 8-15 fade in
void IC_Dash::ramp_colors_fancy_shift(CRGB startcol, CRGB endcol,CRGB backcolor,int minrpm = 10000, int maxrpm = 11000)
{

    uint8_t enabled_leds = map(DashGuy_.rpm,minrpm,maxrpm,0,(TACH_LEDS/2));
    fill_solid(tachLEDs,TACH_LEDS,backcolor);
    fill_gradient_RGB(tachLEDs,0,startcol,enabled_leds,endcol);
    fill_gradient_RGB(tachLEDs,TACH_LEDS-1-enabled_leds,endcol,TACH_LEDS-1,startcol);
    // fill_gradient(tachLEDs,0,startcol,enabled_leds,endcol);

    // for (int i =0; i < enabled_leds; i++)
    // {
    //     tachLEDs[i] = CRGB::Purple;
    //     tachLEDs[TACH_LEDS-1-i] = CRGB::Purple;
    // }

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


void IC_Dash::handleCoolantTempLight()
{
    if (this->DashGuy_.coolantTemp < 180)
    {
        this->statLEDs[3] = CRGB::Blue;
    }
    else if (this->DashGuy_.coolantTemp >= 180.0f && 
             this->DashGuy_.coolantTemp < 220.0f)
    {
        this->statLEDs[3] = CRGB::Black;
    }
    else if (this->DashGuy_.coolantTemp >= 220.0f &&
             this->DashGuy_.coolantTemp <= 240.0f)
    {
        this->statLEDs[3] = CRGB::Yellow;
    }
    else this->statLEDs[3] = CRGB::Red;

    statLEDs_.show();
}

void IC_Dash::handleCheckEngineLight()
{
    if (this->DashGuy_.checkEngineStatus > 0)
    {
        this->statLEDs[4] = CRGB::Orange;
    }
    else this->statLEDs[4] = CRGB::Black;

    statLEDs_.show();
}

void IC_Dash::handleOilPressureLight()
{
    // under 20 black
    // over  40 red
    // green inbetween

    if (this->DashGuy_.oilPressure <= 20)
    {
        this->statLEDs[0] = CRGB::Black;
    }
    else if (this->DashGuy_.oilPressure > 20 && this->DashGuy_.oilPressure < 40)
    {
        this->statLEDs[0] = CRGB::Green;
    }
    else this->statLEDs[0] = CRGB::Red;

    statLEDs_.show();
}

void IC_Dash::set_RPM(uint8_t _byte_H_, uint8_t _byte_L_)
{
    this->DashGuy_.rpm = ((_byte_H_ << 8) | (_byte_L_));
}

void IC_Dash::set_GEAR(uint8_t _gear_)
{
    this->DashGuy_.gear = _gear_;
}

// void IC_Dash::set_STATUS(uint8_t _status_)
// {
//     this->status = _status_;
// }

void IC_Dash::set_CoolantTemp(uint8_t _byte_H_, uint8_t _byte_L_)
{
    this->DashGuy_.coolantTemp = ((_byte_H_ << 8) | (_byte_L_)) / 10;
}

void IC_Dash::set_BatteryVoltage(uint8_t _byte_H_, uint8_t _byte_L_)
{
    this->DashGuy_.batteryVoltage = ((_byte_H_ << 8) | (_byte_L_)) / 10;
}

void IC_Dash::set_CheckEngineStatus(uint8_t _byte_H_, uint8_t _byte_L_)
{
    this->DashGuy_.checkEngineStatus = (_byte_H_ << 8) | (_byte_L_);
}

void IC_Dash::set_OilPressure(uint8_t _byte_H_, uint8_t _byte_L_)
{
    this->DashGuy_.oilPressure = ((_byte_H_ << 8) | (_byte_L_)) / 10;
}


// uint16_t IC_Dash::getRPM()
// {
//     return this->DashGuy_.rpm;
// }

// uint8_t IC_Dash::getGEAR()
// {
//     return this->DashGuy_.gear;
// }

// uint8_t IC_Dash::getSTATUS()
// {
//     return this->status;
// }




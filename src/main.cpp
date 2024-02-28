
#include "IC_Dash.h"
#include "IC_Can.h"
#include "Metro.h"




uint16_t rpm = 0;
uint8_t gear = 0;
uint8_t stat = 0;

Metro gear_ = Metro(100);
Metro main_ = Metro(10);
Metro  can_ = Metro(11);


// CAN_message_t msg;

// uint8_t dat[8] = {0, 1, 2, 3, 4, 5, 6, 7};


void setup()
{
    Serial.begin(9600);

    // while(!Serial); // Wait for serial connection before proceeding

    IC_Dash_ = new IC_Dash();
     IC_Can_ = new  IC_Can();

    initDash(IC_Dash_);
}


void loop()
{
    // As of right now these are just demostrating the final output results
    // These will not be in final build. Loop is reserved for actually doing the shit lol

    if (can_.check())
    {
        IC_Can_->read_Can(IC_Dash_);
    }
    
    if (main_.check())
    {
        IC_Dash_->handleTachometer();
    }

    if (gear_.check())
    {
        IC_Dash_->handleGear();
    }
}

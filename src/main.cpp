
#include "IC_Dash.h"
//#include "IC_Can.h"
#include "Metro.h"




// uint16_t rpm = 0;
uint8_t gear = 0;
// uint8_t stat = 0;

// Metro gear_ = Metro(1000);
// Metro main_ = Metro(10);
// Metro  can_ = Metro(11);





void setup()
{
    Serial.begin(9600);

    // while(!Serial); // Wait for serial connection before proceeding
    
    // Serial.println("BEGIN");

    IC_Dash_ = new IC_Dash();
    // IC_Can_ = new  IC_Can();

    initDash(IC_Dash_);

    IC_Dash_->blinkStatusLed();
}


void loop()
{ 
    IC_Dash_->setGEAR(gear);

    delayMicroseconds(100);

    IC_Dash_->handleGear();

    gear++;

    // As of right now these are just demostrating the final output results
    // These will not be in final build. Loop is reserved for actually doing the shit lol

    // if (can_.check())
    // {
    //     IC_Can_->read_Can(IC_Dash_);
    // }
    
    // if (main_.check())
    // {
    //     IC_Dash_->handleTachometer();
    // }

    // if (gear_.check())
    // {
    //     IC_Dash_->setGEAR(gear);
    //     IC_Dash_->handleGear();
    // }

    if (gear > 9)
    {
        gear = 0;
    }

    // Serial.println(gear);

    delay(1000);
}

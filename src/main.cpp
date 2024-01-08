
#include "IC_Dash.h"
#include "IC_Can.h"
#include "Metro.h"




uint16_t rpm = 0;
uint8_t gear = 0;
uint8_t indi = 0;

Metro timer = Metro(5);
Metro gear_ = Metro(1000);
Metro indi_ = Metro(1000);




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

    if (timer.check())
    {
        // IC_Dash_->handleTachometer(rpm); // Testing tach and indi LEDs     
    }

    if (gear_.check())
    {
        IC_Dash_->handleGear(gear);

        gear++;

        if (gear > 9)
        {
            gear = 0;
        }
    }

    if (indi_.check())
    {
        IC_Dash_->handleIndicators(indi);

        indi++;

        if (indi > 31)
        {
            indi = 0;
        }

    }

    rpm++;

    if (rpm >= MAX_RPM)
    {
        rpm = 0;
    }
}

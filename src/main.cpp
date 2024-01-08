
#include "IC_Dash.h"
#include "IC_Can.h"
#include "Metro.h"




uint16_t rpm = 0;
uint8_t gear = 0;
uint8_t stat = 0;

Metro tach_ = Metro(5);
Metro gear_ = Metro(1000);
Metro stat_ = Metro(1000);




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

    if (tach_.check())
    {
        // IC_Dash_->handleDashTachometer(rpm); // Testing tach and indi LEDs     
    }

    if (gear_.check())
    {
        IC_Dash_->handleDashGear(gear);

        gear++;

        if (gear > 9)
        {
            gear = 0;
        }
    }

    if (stat_.check())
    {
        IC_Dash_->handleDashStatus(stat);

        stat++;

        if (stat > 31)
        {
            stat = 0;
        }

    }

    rpm++;

    if (rpm >= MAX_RPM)
    {
        rpm = 0;
    }
}

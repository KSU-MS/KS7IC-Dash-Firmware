
#include "IC_Dash.h"
#include "IC_Can.h"
#include "Metro.h"




uint16_t rpm = 0;
uint8_t gear = 0;
uint8_t indi = 0;

Metro timer = Metro(2);
Metro gear_ = Metro(1000);
Metro indi_ = Metro(1000);






void setup()
{
    Serial.begin(9600);

    while(!Serial); // Wait for serial connection before proceeding

    static IC_Dash* IC_Dash_ = new IC_Dash();
    static  IC_Can*  IC_Can_ = new  IC_Can();

    initDash(IC_Dash_);
}


void loop()
{
    if (timer.check())
    {
        // IC_Dash_->handleTachometer(rpm); // Testing tach and indi LEDs     
    }

    if (gear_.check())
    {
        // IC_Dash_->handleGear(gear);

        gear++;

        if (gear > 9)
        {
            gear = 0;
        }
    }

    if (indi_.check())
    {
        //IC_Dash_->

    }

    rpm++;

    if (rpm >= MAX_RPM)
    {
        rpm = 0;
    }
}

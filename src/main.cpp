
#include "IC_Dash.h"
#include "Metro.h"




uint16_t rpm = 0;

uint8_t gear = 0;

Metro timer = Metro(3);
Metro gear_ = Metro(1000);






void setup()
{
    Serial.begin(9600);
}


void loop()
{
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

    rpm++;

    if (rpm >= MAX_RPM)
    {
        rpm = 0;
    }
}

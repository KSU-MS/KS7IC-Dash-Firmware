
<<<<<<< Updated upstream
=======
#include <Arduino.h>

>>>>>>> Stashed changes
#include "IC_Dash.h"
#include <FastLED.h>


IC_Dash::IC_Dash()
{
    Serial.begin(9600);
    Serial.println("Yippie");
}

IC_Dash::~IC_Dash()
{
    Serial.println("Bye Bye..");
}


void IC_Dash::initDashLEDs()
{
    FastLED.addLeds<WS2812, TACH_DPIN, RGB>(this->tachLEDs, TACH_LEDS);
    FastLED.addLeds<WS2812, INDI_DPIN, RGB>(this->indiLEDs, INDI_LEDS);
}

void IC_Dash::funkyLEDs()
{
    for (int i = 0; i < TACH_LEDS; i = i + 1)
    {
        this->tachLEDs[i] = CRGB::Red;
        FastLED.show();
        delay(300);
        this->tachLEDs[i] = CRGB::Black;
    }

    for (int i = 0; i < INDI_LEDS; i = i + 1)
    {
        this->indiLEDs[i] = CRGB::Red;
        FastLED.show();
        delay(300);
        this->indiLEDs[i] = CRGB::Black;
    }
}

#include <Arduino.h>

#include "IC_Dash.h"
#include <FastLED.h>


IC_Dash::IC_Dash()
{
    Serial.begin(9600);
    Serial.println("Yippie");

    pinMode(23, OUTPUT);
    digitalWrite(23, HIGH);
}

IC_Dash::~IC_Dash()
{
    Serial.println("Bye Bye..");
}


void IC_Dash::initDashLEDs()
{
    FastLED.addLeds<WS2812, TACH_DPIN, GRB>(this->tachLEDs, TACH_LEDS);
    FastLED.addLeds<WS2812, INDI_DPIN, GRB>(this->indiLEDs, INDI_LEDS);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
    FastLED.setBrightness(10);
}

void IC_Dash::handleTachometer(uint16_t rpm)
{
    CRGB *leds = this->tachLEDs;

    int height = map(rpm, 0, 512, 0, TACH_LEDS + 1);

    fill_gradient(leds, TACH_LEDS - 1, CHSV(0, 255, 255), 0, CHSV(70, 255, 255), SHORTEST_HUES);

    for (int i = 0; i < TACH_LEDS; i++) 
    {
        if(i >= height) leds[i] = CRGB::Black;
    }

    FastLED.show();
}
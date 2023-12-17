
#ifndef IC_DASH.H
#define IC_DASH.H

#include <Arduino.h>



// BABABOOEY

class IC_Dash
{
private:






public:

     IC_Dash();
    ~IC_Dash();

    void tachometerHandler(uint8_t rpm);

    void indicatorHandler();


};


static IC_Dash IC_Dash_;


#endif
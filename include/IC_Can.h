
#ifndef IC_CAN.H
#define IC_CAN.H



#include <FlexCAN_T4.h>

#include "IC_Dash.h"


// BABABOOEY

// CAN USB Interface pinout
// Pin 2 CAN L
// Pin 7 CAN H

class IC_Can
{
private:

    FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> IC_CAN_ORG;
    FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> IC_CAN_DUP;

public:

     IC_Can();
    ~IC_Can();

    // void can_READY();

    void read_Can(IC_Dash* _ic_dash_, uint8_t _can_ = _IC_CAN_ORG_);
    void write_Can(CAN_message_t& _msg_, uint8_t _can_ = _IC_CAN_DUP_);

};


static IC_Can* IC_Can_;


#endif


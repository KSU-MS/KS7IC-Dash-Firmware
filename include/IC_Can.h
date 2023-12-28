
#ifndef IC_CAN.H
#define IC_CAN.H



#include <FlexCAN_T4.h>




// BABABOOEY


class IC_Can
{
private:

    FlexCAN_T4<CAN0, RX_SIZE_256, TX_SIZE_16> IC_CAN_ORG;

    FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> IC_CAN_DUP;

public:

     IC_Can();
    ~IC_Can();

    int read_CAN();
    int write_CAN();


};





static IC_Can* IC_Can_ = new IC_Can();





#endif
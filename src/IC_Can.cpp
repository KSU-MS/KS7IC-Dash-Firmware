
#include "IC_Can.h"




IC_Can::IC_Can()
{
    this->IC_CAN_ORG.begin();
    this->IC_CAN_ORG.setBaudRate(500000);
    this->IC_CAN_ORG.setMaxMB(NUM_TX_MAILBOXES + NUM_RX_MAILBOXES);

    for (int i = 0; i < (NUM_RX_MAILBOXES - 1); i++)
    {
        this->IC_CAN_ORG.setMB((FLEXCAN_MAILBOX)i, RX, STD);
    }

    for (int i = NUM_RX_MAILBOXES; i < (NUM_TX_MAILBOXES + NUM_RX_MAILBOXES); i++)
    {
        this->IC_CAN_ORG.setMB((FLEXCAN_MAILBOX)i, TX, STD);
    }

    this->IC_CAN_ORG.mailboxStatus();


    this->IC_CAN_DUP.begin();
    this->IC_CAN_DUP.setBaudRate(500000);
    this->IC_CAN_DUP.setMaxMB(NUM_TX_MAILBOXES + NUM_RX_MAILBOXES);

    for (int i = 0; i < NUM_RX_MAILBOXES; i++)
    {
        this->IC_CAN_DUP.setMB((FLEXCAN_MAILBOX)i, RX, STD);
    }

    for (int i = NUM_RX_MAILBOXES; i < (NUM_TX_MAILBOXES + NUM_RX_MAILBOXES); i++)
    {
        this->IC_CAN_DUP.setMB((FLEXCAN_MAILBOX)i, TX, STD);
    }

    this->IC_CAN_DUP.mailboxStatus();
}

IC_Can::~IC_Can()
{
    
}


int IC_Can::read_Can(IC_Dash& dash_, uint8_t can = _IC_CAN_ORG_)
{
    CAN_message_t msg;

    if (this->IC_CAN_ORG.read(msg))
    {
        switch (msg.id)
        {
        case _IC_CAN_RPM_:
            dash_.setRPM(msg.buf[0]);
            break;
        case _IC_CAN_GEAR_:
            dash_.setGEAR(msg.buf[0]);
            break;        
        default:
            break;
        }
    }
}

int IC_Can::write_Can(uint8_t can = _IC_CAN_DUP_, CAN_message_t& msg)
{
    switch (can)
    {
    case _IC_CAN_ORG_:
        this->IC_CAN_ORG.write(msg);
        break;
    case _IC_CAN_DUP_:
        this->IC_CAN_DUP.write(msg);
        break;
    default:
        break;
    }
}



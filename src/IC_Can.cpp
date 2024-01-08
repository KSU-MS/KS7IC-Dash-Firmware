
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

    // this->IC_CAN_ORG.mailboxStatus();


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

    // this->IC_CAN_DUP.mailboxStatus();

    Serial.println("Initializing CAN..");
}

IC_Can::~IC_Can()
{
    
}


void IC_Can::read_Can(IC_Dash* _ic_dash_, uint8_t _can_ = _IC_CAN_ORG_)
{
    CAN_message_t _msg_;

    if (this->IC_CAN_ORG.read(_msg_))
    {
        switch (_msg_.id)
        {
        case _IC_CAN_RPM_:
            _ic_dash_->setRPM(_msg_.buf[0]);
            break;
        case _IC_CAN_GEAR_:
            _ic_dash_->setGEAR(_msg_.buf[0]);
            break;
        case _IC_CAN_INDI_:
            _ic_dash_->setSTATUS(_msg_.buf[0]);
            break;        
        default:
            break;
        }
    }
}

void IC_Can::write_Can(CAN_message_t& _msg_, uint8_t _can_ = _IC_CAN_DUP_)
{
    switch (_can_)
    {
    case _IC_CAN_ORG_:
        this->IC_CAN_ORG.write(_msg_);
        break;
    case _IC_CAN_DUP_:
        this->IC_CAN_DUP.write(_msg_);
        break;
    default:
        break;
    }
}



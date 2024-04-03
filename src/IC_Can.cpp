
#include "IC_Can.h"




IC_Can::IC_Can()
{
    this->IC_CAN_ORG.begin();
    this->IC_CAN_DUP.begin();

    this->IC_CAN_ORG.setBaudRate(CAN_BAUD_RATE);
    this->IC_CAN_DUP.setBaudRate(CAN_BAUD_RATE);

    this->IC_CAN_ORG.setMaxMB(NUM_RXTX_MAILBOXES);
    this->IC_CAN_DUP.setMaxMB(NUM_RXTX_MAILBOXES);

    for (uint8_t BOX = 0; BOX < NUM_RXTX_MAILBOXES; BOX++)
    {
        this->IC_CAN_ORG.setMB((FLEXCAN_MAILBOX)BOX, RX, STD);
        this->IC_CAN_DUP.setMB((FLEXCAN_MAILBOX)BOX, TX, STD);
    }

    // this->IC_CAN_ORG.mailboxStatus();
    // this->IC_CAN_DUP.mailboxStatus();

    Serial.println("Initializing CAN..");
}

IC_Can::~IC_Can()
{
    Serial.println("Yeeting CAN..");
}


// void IC_Can::can_READY()
// {
//     digitalWrite(STATUS_LED, HIGH);
//     delay(120);
//     digitalWrite(STATUS_LED, LOW);
// }


void IC_Can::read_Can(IC_Dash* _ic_dash_, uint8_t _can_ = _IC_CAN_ORG_)
{
    // Would like to see if using a switch case versus
    // an if block is better at catching CAN frames.

    // After testing I think this is better ngl

    CAN_message_t _msg_;

    switch (this->IC_CAN_ORG.read(_msg_))
    {
    case _IC_CAN_NONE_:
        break;
    case _IC_CAN_READY_:

        //this->can_READY();

        switch (_msg_.id)
        {
        case _IC_CAN_MSG_GROUP_0_:
            _ic_dash_->setRPM(_msg_.buf);
            break;
        case _IC_CAN_MSG_GROUP_2_:
            _ic_dash_->setCoolantTemp(_msg_.buf);
            break;
        case _IC_CAN_MSG_GROUP_33_:
            _ic_dash_->setGEAR(_msg_.buf[6]);
            break;        
        default:
            break;
        }

#if _DEBUG_

        _ic_dash_->blinkStatusLed();

#endif

        break;
    default:
        break;
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



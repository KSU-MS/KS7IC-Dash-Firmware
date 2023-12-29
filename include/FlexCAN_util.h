
#ifndef FLEXCAN_UTIL.H
#define FLEXCAN_UTIL.H

#include <FlexCAN_T4.h>



void init_CAN();

CAN_message_t& load_CAN(uint32_t id, bool ext, uint8_t buf[8]);

int readCAN(CAN_message_t& msg);
int writeCAN(CAN_message_t& msg);

void update_CAN();



#endif
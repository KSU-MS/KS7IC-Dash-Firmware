
#ifndef IC_DASH_UTILS.H
#define IC_DASH_UTILS.H


#define           _DEBUG_             1


#define           LOWV_EN             23
#define           GEAR_EN             27

#define            BCD_A              38
#define            BCD_B              39
#define            BCD_C              40
#define            BCD_D              41

#define       PORT1_DR_OUTPUT        0x303000000


// Trying to see if this will work for the Seven Seg 

#define          SEG_NUM_C            0xCFCFFFFF
#define          SEG_NUM_0            0x00000000
#define          SEG_NUM_1            0x10000000
#define          SEG_NUM_2            0x20000000           
#define          SEG_NUM_3            0x30000000
#define          SEG_NUM_4            0x00100000
#define          SEG_NUM_5            0x10100000
#define          SEG_NUM_6            0x20100000
#define          SEG_NUM_7            0x30100000
#define          SEG_NUM_8            0x00200000
#define          SEG_NUM_9            0x10200000


#define          SEG_CLEAR            10

#define          TACH_LEDS            15
#define          STAT_LEDS            5

#define          STATUS_LED           2     

#define      LED_MAX_BRIGHTNESS       20
#define     LED_MAX_REFRESHRATE       144

#define          TACH_DPIN            25
#define          INDI_DPIN            26

#define           MAX_RPM             4096

#define        _IC_CAN_NONE_          0
#define       _IC_CAN_READY_          1

#define        _IC_CAN_ORG_           0
#define        _IC_CAN_DUP_           1

#define        _IC_CAN_RPM_           0
#define       _IC_CAN_GEAR_           1
#define       _IC_CAN_INDI_           2
  
#define       _IC_NO_STATUS_          0
#define      _IC_OIL_PRESSURE_        1
#define        _IC_OIL_TEMP_          2
#define     _IC_LAUNCH_CONTROL_       4
#define      _IC_COOLANT_TEMP_        8
#define        _IC_CHECK_ENG_         16

#define       NUM_RXTX_MAILBOXES      8

#define         CAN_BAUD_RATE         250000

#define     _IC_CAN_MSG_GROUP_0_      0x5F0
#define     _IC_CAN_MSG_GROUP_2_      0x5F2
#define     _IC_CAN_MSG_GROUP_3_      0x5F3
#define     _IC_CAN_MSG_GROUP_33_     0x611



#endif



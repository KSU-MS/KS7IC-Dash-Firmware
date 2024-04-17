
#ifndef IC_DASH_UTILS.H
#define IC_DASH_UTILS.H


#define           _DEBUG_             0


#define           LOWV_EN             23
#define           GEAR_EN             27

#define            BCD_A              38
#define            BCD_B              39
#define            BCD_C              40
#define            BCD_D              41

#define       PORT1_DR_OUTPUT        0x303000000

#define          TACH_LEDS            15
#define          STAT_LEDS            5

#define          TACH_METRO_INT       1
#define          MAIN_METRO_INT       1000

#define          STATUS_LED           2     

#define      LED_MAX_BRIGHTNESS       20
#define     LED_MAX_REFRESHRATE       144

#define          TACH_DPIN            25
#define          INDI_DPIN            26

#define           MAX_RPM             12000

#define        _IC_CAN_NONE_          0
#define       _IC_CAN_READY_          1

#define      _METRO_CAN_READY_        0b01
#define      _METRO_MAIN_READY_       0b10
#define        _METRO_READY_          0b11

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

#define       NUM_RXTX_MAILBOXES      4

#define         CAN_BAUD_RATE         1000000

#define     _IC_CAN_MSG_GROUP_0_      0x5F0
#define     _IC_CAN_MSG_GROUP_2_      0x5F2
#define     _IC_CAN_MSG_GROUP_3_      0x5F3
#define     _IC_CAN_MSG_GROUP_33_     0x611
#define     _IC_CAN_MSG_GROUP_60_     0x62C



#endif



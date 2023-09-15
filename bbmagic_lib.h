


#ifndef __BBMAGIC_LIB_H
#define __BBMAGIC_LIB_H

#ifdef __cplusplus
extern "C" {
#endif

//-BBMagic device types
//---------------------------------------------------------------------------------------------
#define BBMAGIC_M_METEO                 1       //-BBMagic meteo module: T, RH, Light
#define BBMAGIC_M_MOTION                2
#define BBMAGIC_M_BUTTON                3
#define BBMAGIC_M_FLOOD                 4
#define BBMAGIC_M_MAGNETO               5

//-BBMagic Lib buffer offsets for all devices
//---------------------------------------------------------------------------------------------
//-BBMagic device ID
#define BBMAGIC_DEVICE_TYPE		    	4
//-Bluetooth device address
#define BBMAGIC_DEVICE_ADDR_5           16
#define BBMAGIC_DEVICE_ADDR_4           17
#define BBMAGIC_DEVICE_ADDR_3           18
#define BBMAGIC_DEVICE_ADDR_2           19
#define BBMAGIC_DEVICE_ADDR_1           20
#define BBMAGIC_DEVICE_ADDR_0           21
//-Bluetooth Radio Sugnal Strength Indicator
#define BBMAGIC_DEVICE_RSSI             22
//-Divider to calculate module supply voltage in Volts
#define BBMAGIC_VCC_DIVIDER             71.0

//-BBMagic Lib buffer offsets
//---------------------------------------------------------------------------------------------
//-BBMagic METEO module
#define BBM_METEO_WORKTIME_0            0
#define BBM_METEO_WORKTIME_1		    1
#define BBM_METEO_WORKTIME_2		    2
#define BBM_METEO_WORKTIME_3            3
#define BBM_METEO_V_SUP			        5
#define BBM_METEO_ADV_TIME              6
#define BBM_METEO_DIN_STATE		        7
#define BBM_METEO_TEMPER_MSB		    8
#define BBM_METEO_TEMPER_LSB		    9
#define BBM_METEO_HUM		            10
#define BBM_METEO_LIGHT   			    11
#define BBM_METEO_ADC_1_MSB             12
#define BBM_METEO_ADC_1_LSB             13
#define BBM_METEO_ADC_2_MSB             14
#define BBM_METEO_ADC_2_LSB             15
//-BBMagic BUTTON module
#define BBM_BUTTON_SIGN_0               0
#define BBM_BUTTON_SIGN_1               1
#define BBM_BUTTON_SIGN_2		        2
#define BBM_BUTTON_SIGN_3               3
#define BBM_BUTTON_V_SUP			    5
#define BBM_BUTTON_BUTTON_FUNCTION      7
#define BBM_BUTTON_INPUT_PINS           8
#define BBM_BUTTON_CHIP_TEMP            9
#define BBM_BUTTON_LIGHT			    10
#define BBM_BUTTON_FIRM_1               14
#define BBM_BUTTON_FIRM_0               15
#define BBM_BUTTON_FN_SINGLE_CLICK      1
#define BBM_BUTTON_FN_DOUBLE_CLICK      2
#define BBM_BUTTON_FN_HOLDING           3
//-BBMagic MOTION module
#define BBM_MOTION_WORKTIME_0           0
#define BBM_MOTION_WORKTIME_1           1
#define BBM_MOTION_WORKTIME_2           2
#define BBM_MOTION_WORKTIME_3           3
#define BBM_MOTION_V_SUP			    5
#define BBM_MOTION_FLAGS	            7
#define BBM_MOTION_CHIP_TEMP            8
#define BBM_MOTION_LIGHT			    9
#define BBM_MOTION_ADC_1_MSB            10
#define BBM_MOTION_ADC_1_LSB            11
#define BBM_MOTION_ADC_2_MSB            12
#define BBM_MOTION_ADC_2_LSB            13
#define BBM_MOTION_FIRM_1               14
#define BBM_MOTION_FIRM_0               15
#define BBM_MOTION_ALERT_MASK           0x80
//-BBMagic FLOOD module
#define BBM_FLOOD_WORKTIME_0    		0
#define BBM_FLOOD_WORKTIME_1	       	1
#define BBM_FLOOD_WORKTIME_2            2
#define BBM_FLOOD_WORKTIME_3            3
#define BBM_FLOOD_V_SUP		           	5
#define BBM_FLOOD_ADV_TIME              6
#define BBM_FLOOD_ALERT_FLAGS		    7
#define BBM_FLOOD_CHIP_TEMP             8
#define BBM_FLOOD_FIRM_1                14
#define BBM_FLOOD_FIRM_0                15
#define BBM_FLOOD_ALERT_MASK            0x01
//-BBMagic MAGNETO module
#define BBM_MAGNETO_WORKTIME_0    		0
#define BBM_MAGNETO_WORKTIME_1	       	1
#define BBM_MAGNETO_WORKTIME_2          2
#define BBM_MAGNETO_WORKTIME_3          3
#define BBM_MAGNETO_V_SUP		        5
#define BBM_MAGNETO_ADV_TIME            6
#define BBM_MAGNETO_FLAGS		        7
#define BBM_MAGNETO_CHIP_TEMP           8
#define BBM_MAGNETO_LIGHT               9
#define BBM_MAGNETO_ADC_1_MSB           10
#define BBM_MAGNETO_ADC_1_LSB           11
#define BBM_MAGNETO_ADC_2_MSB           12
#define BBM_MAGNETO_ADC_2_LSB           13
#define BBM_MAGNETO_FIRM_1              14
#define BBM_MAGNETO_FIRM_0              15
#define BBM_MAGNETO_MAGNET_MASK         0x80
#define BBM_MAGNETO_IN_0_BIT            0x01
#define BBM_MAGNETO_IN_1_BIT            0x02
#define BBM_MAGNETO_IN_2_BIT            0x04
#define BBM_MAGNETO_IN_3_BIT            0x08


//---------------------------------------------------

#define BBLIB_FRAME_SIZE                23
#define BBM_BT_ADDR_SIZE                6

//*******************************************************************************************
//-Public Function: open bt hci and starts bt scanning
//returning values:
// 0 - bbmagic bluetooth opened
// !=0 - some errors occured
//*******************************************************************************************
    int bbm_bt_open(int led_pin) ;

//*******************************************************************************************
//-Public Function: stops bt scanning and closes bt hci
//returning values:
// 0 - bbmagic bluetooth closed
// !=0 - some errors occured
//*******************************************************************************************
    int bbm_bt_close(void) ;

//*******************************************************************************************
//-Public Function: reads data from bbmagic modules
//returning values:
// 0 : no bt data arrived
// >0 : bytes red
//-1 : user break (ctrl+C)
//-2 : data red ; not HCI event pocket
//-4 : red HCI event pocket ; not LE Advertising Report event
//-6 : red HCI event pocket LE Advertising Report event ; not Manufacturer specific data
//-8 : reserved for: wrong Manufacturer ID
//-10 : authentication error
//-12 : other error
//*******************************************************************************************
    int bbm_bt_read(unsigned char *bbm_data) ;

//*******************************************************************************************
//-Public Function: returns version of bbm_bt library
//returning values:
// int - bbm_bt_lib version
//*******************************************************************************************
    int bbm_bt_lib_version(void) ;

#endif  //-ndef __BBMAGIC_LIB_H

/******************************/
/* Author  : El-3fareet       */
/* Version : V1.2.2           */
/* Date    : 28-4-2020        */
/******************************/
#ifndef DIO_CFG_H_
#define DIO_CFG_H_


#define DIO_NUMBER_OF_CHANNEL_GROUPS 				1
#define RGB_LED_PORT_GROUP_1						PORT_A
#define RGB_LED_MASK_GROUP_1						0b00011100
#define RGB_LED_OFFSET_GROUP_1						2
#define RGB_LED										(&ConfigueredChnannelGroups[0])

/*Dio channel*/
#define DIO_NUMBER_OF_CHANNELS 2

/*channels*/
#define MY_LED 0
#define MY_SWITCH 1


/*DIO Ports Symbolic Names
 * OPTIONS:
 * PORT_A  PORT_B  PORT_C  PORT_D */
#define LEDS_PORT                        PORT_A
#define SEVEN_SEGMENT_PORT               PORT_D


/*general dio config container*/

/*Switches the development error detection and notification on or off.
true: detection and notification is enabled.
false: detection and notification is disabled
*/
#define DIO_DEV_ERROR_SETECT TRUE

/*Adds / removes the service Dio_FlipChannel() from the code.*/
#define DIO_FLIP_CHANNEL_API TRUE

/*Adds / removes the service Dio_MaskedWritePort() from the code.*/
#define DIO_MASKED_WRITE_PORT_API TRUE

/*Adds / removes the service Dio_ GetVersionInfo() from the code.*/
#define DIO_VERSION_INFO_API TRUE


#endif




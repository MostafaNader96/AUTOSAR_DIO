#ifndef DIO_CFG_H_
#define DIO_CFG_H_

/*
#define LED_PORT	(Dio_PortType)	 0
#define LED_PIN 	(Dio_ChannelType)2
*/

#define NUMBER_OF_CONFIGURED_GROUPS 				1


#define RGB_LED_PORT_GROUP_1	PORTA_ID
#define RGB_LED_MASK_GROUP_1	0b00011100
#define RGB_LED_OFFSET_GROUP_1	2

#define GROUP_1		(Dio_ChannelGroupType*) Groups[0]


/*DIO Ports Symbolic Names
 * OPTIONS:
 * PORT_A  PORT_B  PORT_C  PORT_D */
#define LEDS_PORT                        PORT_A
#define SEVEN_SEGMENT_PORT               PORT_D




#endif




/******************************/
/* Author  : El-3fareet       */
/* Version : V1.2.2           */
/* Date    : 28-4-2020        */
/******************************/
#include "DIO.h"
#include "DIO_MemMap.h"

#define DDRA_ADRR (uint8*)0x3A
#define DDRB_ADRR (uint8*)0x37
#define DDRC_ADRR (uint8*)0x34
#define DDRD_ADRR (uint8*)0x31


const Dio_ChannelCfgType ConfiguredChannels[DIO_NUMBER_OF_CHANNELS]=
{
	/*PORT			pin*/
	{DDRB_ADRR 	,	5},
	{DDRA_ADRR 	,	3}
};

const Dio_ChannelGroupType ConfiguredChannelGroups[DIO_NUMBER_OF_CHANNEL_GROUPS]=
{
		{
				.PortIndex=RGB_LED_PORT_GROUP_1,
				.mask=	   RGB_LED_MASK_GROUP_1,
				.offset=   RGB_LED_OFFSET_GROUP_1
		}

};


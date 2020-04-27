#include "DIO.h"
#include "DIO_MemMap.h"



Dio_ChannelGroupType Groups[NUMBER_OF_CONFIGURED_GROUPS]=
{
		{
				.PortIndex=RGB_LED_PORT_GROUP_1,
				.mask=	   RGB_LED_MASK_GROUP_1,
				.offset=   RGB_LED_OFFSET_GROUP_1
		}

};

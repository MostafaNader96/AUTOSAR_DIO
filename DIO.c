#include "Det.h"
#include "DIO.h"
#include "DIO_MemMap.h"
#include "SchM_Dio.h"


#define PORTA	(*(volatile uint8*)0x003B)
#define DDRA	(*(volatile uint8*)0x003A)
#define PINA	(*(volatile uint8*)0x0039)
#define PORTB	(*(volatile uint8*)0x0038)
#define DDRB	(*(volatile uint8*)0x0037)
#define PINB	(*(volatile uint8*)0x0036)
#define PORTC	(*(volatile uint8*)0x0035)
#define DDRC	(*(volatile uint8*)0x0034)
#define PINC	(*(volatile uint8*)0x0033)
#define PORTD	(*(volatile uint8*)0x0032)
#define DDRD	(*(volatile uint8*)0x0031)
#define PIND	(*(volatile uint8*)0x0030)


Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId)
{
	Dio_LevelType Level;
	if (32 <= ChannelId)
	{
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,DIO_READ_CHANNEL_SID, DIO_E_PARAM_INVALID_CHANNEL_ID);
	}
	else
	{
		switch( ( ChannelId / 8 ) )
		{
			case:0 Level = PORTA >> ( ChannelId % 8 ) break;
			case:1 Level = PORTB >> ( ChannelId % 8 )  break;
			case:2 Level = PORTC >> ( ChannelId % 8 )  break;
			case:3 Level = PORTD >> ( ChannelId % 8 )  break;
			default: break;
		}
	}
	return Level;
}
void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level)
{
	if (32 <= ChannelId)
	{
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,DIO_WRITE_CHANNEL_SID, DIO_E_PARAM_INVALID_CHANNEL_ID);
	}
	else
	{
		if( STD_HIGH == Level )
		{
			switch( ( ChannelId / 8 ) )
			{
			case:0 PORTA |= 1 << ( ChannelId % 8 ) break;
			case:1 PORTB |= 1 << ( ChannelId % 8 ) break;
			case:2 PORTC |= 1 << ( ChannelId % 8 ) break;
			case:3 PORTD |= 1 << ( ChannelId % 8 ) break;
			default: break;
			}
		}
		else if( STD_LOW == Level )
		{
			switch( ( ChannelId / 8 ) )
			{
			case:0 PORTA &= ~(1 << ( ChannelId % 8 ) ) break;
			case:1 PORTB &= ~(1 << ( ChannelId % 8 ) ) break;
			case:2 PORTC &= ~(1 << ( ChannelId % 8 ) ) break;
			case:3 PORTD &= ~(1 << ( ChannelId % 8 ) ) break;
			default: break;
			}
		}
		else
		{
			/* Do Nothing */
		}
	
	}
		
}

Dio_PortLevelType Dio_ReadChannelGroup(const Dio_ChannelGroupType* ChannelGroupIdPtr )
{
	
}

Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId)
{
	
}

void Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level)
{
	
}

void Dio_WriteChannelGroup(const Dio_ChannelGroupType* ChannelGroupIdPtr,Dio_PortLevelType Level )
{
	
}

Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId)
{
	
}
	
	
	
	
	
	
	
	
	
	
	
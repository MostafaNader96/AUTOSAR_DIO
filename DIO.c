#include "Det.h"
#include "DIO.h"
#include "DIO_MemMap.h"
#include "SchM_Dio.h"


#define PORTA	(*(volatile u8*)0x003B)
#define DDRA	(*(volatile u8*)0x003A)
#define PINA	(*(volatile u8*)0x0039)
#define PORTB	(*(volatile u8*)0x0038)
#define DDRB	(*(volatile u8*)0x0037)
#define PINB	(*(volatile u8*)0x0036)
#define PORTC	(*(volatile u8*)0x0035)
#define DDRC	(*(volatile u8*)0x0034)
#define PINC	(*(volatile u8*)0x0033)
#define PORTD	(*(volatile u8*)0x0032)
#define DDRD	(*(volatile u8*)0x0031)
#define PIND	(*(volatile u8*)0x0030)


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
			case 0: Level = PORTA >> ( ChannelId % 8 );  break;
			case 1: Level = PORTB >> ( ChannelId % 8 );  break;
			case 2: Level = PORTC >> ( ChannelId % 8 );  break;
			case 3: Level = PORTD >> ( ChannelId % 8 );  break;
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
			case 0: PORTA |= 1 << ( ChannelId % 8 ); break;
			case 1: PORTB |= 1 << ( ChannelId % 8 ); break;
			case 2: PORTC |= 1 << ( ChannelId % 8 ); break;
			case 3: PORTD |= 1 << ( ChannelId % 8 ); break;
			default: break;
			}
		}
		else if( STD_LOW == Level )
		{
			switch( ( ChannelId / 8 ) )
			{
			case 0: PORTA &= ~(1 << ( ChannelId % 8 ) ); break;
			case 1: PORTB &= ~(1 << ( ChannelId % 8 ) ); break;
			case 2: PORTC &= ~(1 << ( ChannelId % 8 ) ); break;
			case 3: PORTD &= ~(1 << ( ChannelId % 8 ) ); break;
			default: break;
			}
		}
		else
		{
			/* Do Nothing */
		}
	
	}
		
}

Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId)
{
	Dio_PortLevelType PortLevel;
	
	if (4 <= PortId)
	{
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,DIO_WRITE_PORT_SID, DIO_E_PARAM_INVALID_PORT_ID);
	}	
	else
	{
		switch( PortId )
		{
		case 0: PortLevel = PORTA; break;
		case 1: PortLevel = PORTB; break;
		case 2: PortLevel = PORTC; break;
		case 3: PortLevel = PORTD; break;
		default: break;
		}
	}
		return PortLevel;
}

void Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level)
{
	if (4 <= PortId)
	{
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,DIO_WRITE_PORT_SID, DIO_E_PARAM_INVALID_PORT_ID);
	}	
	else
	{
		switch( PortId )
		{
		case 0: PORTA = Level; break;
		case 1: PORTB = Level; break;
		case 2: PORTC = Level; break;
		case 3: PORTD = Level; break;
		default: break;
		}
	}
	
}

Dio_PortLevelType Dio_ReadChannelGroup(const Dio_ChannelGroupType* ChannelGroupIdPtr )
{
	
}

void Dio_WriteChannelGroup(const Dio_ChannelGroupType* ChannelGroupIdPtr,Dio_PortLevelType Level )
{
	
}

Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId)
{
	
}
	
	
	
	
	
	
	
	
	
	
	

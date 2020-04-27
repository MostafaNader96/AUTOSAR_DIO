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

/************************************************************************************
* Service Name: Dio_ReadChannelGroup
* Service ID[hex]: 0x04
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): ChannelGroupIdPtr - Pointer to ChannelGroup.
* Parameters (inout): None
* Parameters (out): None
* Return value: Dio_PortLevelType
* Description: Function to  read a subset of the adjoining bits of a port.
************************************************************************************/
Dio_PortLevelType Dio_ReadChannelGroup(const Dio_ChannelGroupType* ChannelGroupIdPtr )
{
	Dio_PortLevelType Group;
	uint8 Group_Iterator;
	uint8 Group_Detected=FALSE;

	if(NULL_PTR == ChannelGroupIdPtr)
	{
		Det_ReportError(DIO_MODULE_ID,DIO_INSTANCE_ID,DIO_READ_CHANNEL_GROUP_SID,DIO_E_PARAM_POINTER);
	}
	else
	{
		for(Group_Iterator=0;Group_Iterator<NUMBER_OF_CONFIGURED_GROUPS;Group_Iterator++)
		{
			if(ChannelGroupIdPtr == &Groups[Group_Iterator])
			{
				Group_Detected=TRUE;
			}
			else
			{
				/*Do nothing*/
			}
		}

		if(FALSE == Group_Detected)
		{
			Det_ReportError(DIO_MODULE_ID,DIO_INSTANCE_ID,DIO_READ_CHANNEL_GROUP_SID,DIO_E_PARAM_INVALID_CHANNEL_ID);
		}
		else if(TRUE == Group_Detected)
		{
			switch(ChannelGroupIdPtr->PortIndex)
			{
			case PORTA_ID : Group = (PINA & ChannelGroupIdPtr->mask) >> ChannelGroupIdPtr->offset; break;
			case PORTB_ID : Group = (PINB & ChannelGroupIdPtr->mask) >> ChannelGroupIdPtr->offset; break;
			case PORTC_ID : Group = (PINC & ChannelGroupIdPtr->mask) >> ChannelGroupIdPtr->offset; break;
			case PORTD_ID : Group = (PIND & ChannelGroupIdPtr->mask) >> ChannelGroupIdPtr->offset; break;
			default : Det_ReportError(DIO_MODULE_ID,DIO_INSTANCE_ID,DIO_READ_CHANNEL_GROUP_SID,DIO_E_PARAM_INVALID_PORT_ID); break;
			}
		}
		else
		{
			/*Do nothing*/
		}
	}
	return Group;
}

/************************************************************************************
* Service Name: Dio_WriteChannelGroup
* Service ID[hex]: 0x11
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): ChannelGroupIdPtr - Pointer to ChannelGroup.
* 					Level -Value to be written
* Parameters (inout): None
* Parameters (out): None
* Return value: Dio_PortLevelType
* Description: Function to set a subset of the adjoining bits of a port to a specified level.
************************************************************************************/
void Dio_WriteChannelGroup(const Dio_ChannelGroupType* ChannelGroupIdPtr,Dio_PortLevelType Level )
{
	uint8 Group_Iterator;
	uint8 Group_Detected=FALSE;

	if(NULL_PTR == ChannelGroupIdPtr)
	{
		Det_ReportError(DIO_MODULE_ID,DIO_INSTANCE_ID,DIO_READ_CHANNEL_GROUP_SID,DIO_E_PARAM_POINTER);
	}
	else
	{
		for(Group_Iterator=0;Group_Iterator<NUMBER_OF_CONFIGURED_GROUPS;Group_Iterator++)
		{
			if(ChannelGroupIdPtr == &Groups[Group_Iterator])
			{
				Group_Detected=TRUE;
			}
			else
			{
				/*Do nothing*/
			}
		}

		if(FALSE == Group_Detected)
		{
			Det_ReportError(DIO_MODULE_ID,DIO_INSTANCE_ID,DIO_READ_CHANNEL_GROUP_SID,DIO_E_PARAM_INVALID_CHANNEL_ID);
		}
		else if(TRUE == Group_Detected)
		{
			switch(ChannelGroupIdPtr->PortIndex)
			{
			 /*close sreg*/ /*Critical section*/
			case PORTA_ID : PORTA = (PORTA & ~(ChannelGroupIdPtr->mask)) | (Level << ChannelGroupIdPtr->offset); break;
			case PORTB_ID : PORTB = (PORTB & ~(ChannelGroupIdPtr->mask)) | (Level << ChannelGroupIdPtr->offset); break;
			case PORTC_ID : PORTC = (PORTC & ~(ChannelGroupIdPtr->mask)) | (Level << ChannelGroupIdPtr->offset); break;
			case PORTD_ID : PORTD = (PORTD & ~(ChannelGroupIdPtr->mask)) | (Level << ChannelGroupIdPtr->offset); break;
			default : Det_ReportError(DIO_MODULE_ID,DIO_INSTANCE_ID,DIO_READ_CHANNEL_GROUP_SID,DIO_E_PARAM_INVALID_PORT_ID); break;
			}
			/*open sreg*/
		}
		else
		{
			/*Do nothing*/
		}

	}
}

Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId)
{

}












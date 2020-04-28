#include "DIO.h"
#include "Det.h"
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

typedef struct
{
	u8 PIN;
	u8 DDR;
	u8 PORT;

}DIO_Peripherals;

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

	DIO_Peripherals * DIO = (DIO_Peripherals *) &PIND;
	Dio_LevelType Result = 0x00;

	/*Error Detection is Activated during the Development Time based on the value of DIO_DEV_ERROR_DETECT*/
	#if DIO_DEV_ERROR_DETECT == STD_HIGH
		if(NUM_OF_PORTS <= PortId)
		{
			/*Report error to the DET Module*/
			 Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,DIO_READ_PORT_SID, DIO_E_PARAM_INVALID_PORT_ID);

		}
		else
		{
			/*PortId is valid*/
		}
	#endif

	/* Check if the input argument is right */
	if (PortId < NUM_OF_PORTS)
	{
		/* Entering the Critical Section "Disabling Global Interrupt" */
		DISABLE_GLOBAL_INTERRUPTS();

		/* read the Input Pins and Output Pins separately  */
		Result = ( ( (~(DIO[PortId].DDR) ) & (DIO[PortId].PIN) ) | ( (DIO[PortId].DDR) & (DIO[PortId].PORT) ) );

		/* Exiting the Critical Section "Enabling Global Interrupt" */
		ENABLE_GLOBAL_INTERRUPTS();
	}
	else
	{
		/*Do nothing*/
	}

	return Result;
}

void Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level)
{
	DIO_Peripherals * DIO = (DIO_Peripherals *)  &PIND;

	/*Error Detection is Activated during the Development Time based on the value of DIO_DEV_ERROR_DETECT*/
	#if DIO_DEV_ERROR_DETECT == STD_HIGH
		if(NUM_OF_PORTS <= PortId)
		{
			/*Report error to the DET Module */
			Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,DIO_READ_PORT_SID, DIO_E_PARAM_INVALID_PORT_ID);

		}
		else
		{
			/*PortId is valid*/
		}
	#endif

	/* Check if the input argument is right */
	if (PortId < NUM_OF_PORTS)
	{
		/* Entering the Critical Section "Disabling Global Interrupt" */
		DISABLE_GLOBAL_INTERRUPTS();

		/* Writing the values to the output pins without changing the values of the input pins */
		DIO[PortId].PORT  = ( ( (~(DIO[PortId].DDR)) & (DIO[PortId].PORT) ) | ( (DIO[PortId].DDR) & Level ) ) ;

		/* Exiting the Critical Section "Enabling Global Interrupt" */
		ENABLE_GLOBAL_INTERRUPTS();
	}
	else
	{
		/*Do nothing*/
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












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

#define NUM_OF_PORTS	4

typedef struct
{
	uint8 PIN;
	uint8 DDR;
	uint8 PORT;

}DIO_Peripherals;

Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId)
{

}
void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level)
{

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
			//DISABLE_GLOBAL_INTERRUPTS();

		/* read the Input Pins and Output Pins separately  */
		Result = ( ( (~(DIO[PortId].DDR) ) & (DIO[PortId].PIN) ) | ( (DIO[PortId].DDR) & (DIO[PortId].PORT) ) );

		/* Exiting the Critical Section "Enabling Global Interrupt" */
			//ENABLE_GLOBAL_INTERRUPTS();
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
			//DISABLE_GLOBAL_INTERRUPTS();

		/* Writing the values to the output pins without changing the values of the input pins */
		DIO[PortId].PORT  = ( ( (~(DIO[PortId].DDR)) & (DIO[PortId].PORT) ) | ( (DIO[PortId].DDR) & Level ) ) ;

		/* Exiting the Critical Section "Enabling Global Interrupt" */
			//ENABLE_GLOBAL_INTERRUPTS();
	}
	else
	{
		/*Do nothing*/
	}

}


Dio_PortLevelType Dio_ReadChannelGroup(const Dio_ChannelGroupType* ChannelGroupIdPtr )
{
	Dio_PortLevelType Group;
	uint8 Group_Iterator;
	uint8 Group_Detected=FALSE;
	DIO_Peripherals * DIO;

#if DIO_DEV_ERROR_DETECT == STD_HIGH
	if(NULL_PTR == ChannelGroupIdPtr)
	{
		Det_ReportError(DIO_MODULE_ID,DIO_INSTANCE_ID,DIO_READ_CHANNEL_GROUP_SID,DIO_E_PARAM_POINTER);
	}
	else
	{
		/*Do nothing*/
	}
#endif
	for(Group_Iterator=0;Group_Iterator<DIO_NUMBER_OF_CHANNEL_GROUPS;Group_Iterator++)
	{
		if(ChannelGroupIdPtr == &ConfigueredChnannelGroups[Group_Iterator])
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
		Det_ReportError(DIO_MODULE_ID,DIO_INSTANCE_ID,DIO_READ_CHANNEL_GROUP_SID,DIO_E_PARAM_INVALID_GROUP);
	}
	else if(TRUE == Group_Detected)
	{
		Group = ( ( ( ( (~(DIO[ChannelGroupIdPtr->PortIndex].DDR) ) & (DIO[ChannelGroupIdPtr->PortIndex].PIN) ) | ( (DIO[ChannelGroupIdPtr->PortIndex].DDR) & (DIO[ChannelGroupIdPtr->PortIndex].PORT) ) ) & ChannelGroupIdPtr->mask ) >> ChannelGroupIdPtr->offset );
	}
	else
	{
		/*Do nothing*/
	}

	return Group;
}


void Dio_WriteChannelGroup(const Dio_ChannelGroupType* ChannelGroupIdPtr,Dio_PortLevelType Level )
{
	uint8 Group_Iterator;
	uint8 Group_Detected=FALSE;
	DIO_Peripherals * DIO = (DIO_Peripherals *)  &PIND;

#if DIO_DEV_ERROR_DETECT == STD_HIGH
	if(NULL_PTR == ChannelGroupIdPtr)
	{
		Det_ReportError(DIO_MODULE_ID,DIO_INSTANCE_ID,DIO_READ_CHANNEL_GROUP_SID,DIO_E_PARAM_POINTER);
	}
	else
	{
		/*Do nothing*/
	}
#endif
	for(Group_Iterator=0;Group_Iterator<DIO_NUMBER_OF_CHANNEL_GROUPS;Group_Iterator++)
	{
		if(ChannelGroupIdPtr == &ConfigueredChnannelGroups[Group_Iterator])
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
		Det_ReportError(DIO_MODULE_ID,DIO_INSTANCE_ID,DIO_READ_CHANNEL_GROUP_SID,DIO_E_PARAM_INVALID_GROUP);
	}
	else if(TRUE == Group_Detected)
	{
		/*open sreg*/
		DIO[ChannelGroupIdPtr->PortIndex].PORT = ( DIO[ChannelGroupIdPtr->PortIndex].PORT  & ( ~( ChannelGroupIdPtr->mask ) | ~( DIO[ChannelGroupIdPtr->PortIndex].DDR ) ) ) | ( ( Level << ChannelGroupIdPtr->offset ) & DIO[ChannelGroupIdPtr->PortIndex].DDR );
		/*Close sreg*/
	}
	else
	{
		/*Do Nothing*/
	}

}
Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId)
{

}












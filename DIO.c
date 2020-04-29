/******************************/
/* Author  : El-3fareet       */
/* Version : V1.2.2           */
/* Date    : 28-4-2020        */
/******************************/
#include "DIO.h"
#if DIO_DEV_ERROR_DETECT == STD_HIGH
#include "Det.h"
#endif
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

#define NUM_OF_PORTS		4

#define PIN_PORT_MULT 		2
#define PIN_PORT_SUB 		1
#define SET_BIT				1
#define CLR_BIT				1
#define GET_BIT				1
#define INITIAL_VALUE_ZERO	0
#define OUTPUT				1
#define INPUT				0
#define PORT_REG_OFFSET		0x01
#define UINT8_PTR_STEP		1

typedef struct
{
	uint8 PIN;
	uint8 DDR;
	uint8 PORT;
}DIO_Peripherals;

Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId)
{
	Dio_LevelType Local_Dio_LevelType=STD_LOW;
	uint8 Local_Direction;
	#if DIO_DEV_ERROR_DETECT == STD_HIGH
		if (DIO_NUMBER_OF_CHANNELS<=ChannelId)
		{
			Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,DIO_READ_CHANNEL_SID, DIO_E_PARAM_INVALID_CHANNEL_ID);
		}
		else
		{
			asm("cli");	/*Disable global interrupt*/
			Local_Direction=((*(channels[ChannelId].DDR_ptr)) >> channels[ChannelId].pin) & GET_BIT;
			Local_Dio_LevelType = ((*(channels[ChannelId].DDR_ptr + (PIN_PORT_MULT*Local_Direction - PIN_PORT_SUB))) >> channels[ChannelId].pin )& GET_BIT;
			asm("sei");	/*Enable global interrupt*/
		}
	#elif DIO_DEV_ERROR_DETECT == STD_LOW
		if(NUMBER_OF_CHANNELS>ChannelId)
		{
			asm("cli");	/*Disable global interrupt*/
			Local_Direction=((*(channels[ChannelId].DDR_ptr)) >> channels[ChannelId].pin) & GET_BIT;
			Local_Dio_LevelType = ((*(channels[ChannelId].DDR_ptr + (PIN_PORT_MULT*Local_Direction - PIN_PORT_SUB))) >> channels[ChannelId].pin )& GET_BIT;
			asm("sei");	/*Enable global interrupt*/
		}
	#endif
	if(Local_Dio_LevelType!=STD_LOW)
		Local_Dio_LevelType=STD_HIGH;
	return Local_Dio_LevelType;
}

void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level)
{
	uint8 PinDirection = INITIAL_VALUE_ZERO;
	
	#if DIO_DEV_ERROR_DETECT == STD_HIGH
	
	if (DIO_NUMBER_OF_CHANNELS <= ChannelId)
	{
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,DIO_WRITE_CHANNEL_SID, DIO_E_PARAM_INVALID_CHANNEL_ID);
	}
	else
	{
		PinDirection = *(configueredChannels[ChannelId].DDR_ptr) &  ( GET_BIT <<( configueredChannels[ChannelId].pin ) );
		
		if ( OUTPUT == PinDirection )
		{
			if( STD_HIGH == Level )
			{
				asm("cli");	/*Disable global interrupt*/
				*(configueredChannels[ChannelId].DDR_ptr + PORT_REG_OFFSET ) |= ( SET_BIT << configueredChannels[ChannelId].pin );
				asm("sei");	/*Enable global interrupt*/
			}
			else if( STD_LOW == Level )
			{
				asm("cli");	/*Disable global interrupt*/
				*(configueredChannels[ChannelId].DDR_ptr + PORT_REG_OFFSET ) &= ~ ( CLR_BIT << configueredChannels[ChannelId].pin );
				asm("sei");	/*Enable global interrupt*/
			}
			else
			{
				/* Do Nothing */
			}
		}
		else
		{
			/* Do nothing as the pin is input */
		}
	}
	#elif DIO_DEV_ERROR_DETECT == STD_LOW
	PinDirection = *(configueredChannels[ChannelId].DDR_ptr) &  ( GET_BIT <<( configueredChannels[ChannelId].pin ) );
	
	if ( OUTPUT == PinDirection )
	{
		if( STD_HIGH == Level )
		{
			asm("cli");	/*Disable global interrupt*/
			*(configueredChannels[ChannelId].DDR_ptr + PORT_REG_OFFSET ) |= SET_BIT << configueredChannels[ChannelId].pin;
			asm("sei");	/*Enable global interrupt*/
		}
		else if( STD_LOW == Level )
		{
			asm("cli");	/*Disable global interrupt*/
			*(configueredChannels[ChannelId].DDR_ptr + PORT_REG_OFFSET ) &= ~ ( CLR_BIT << configueredChannels[ChannelId].pin );
			asm("sei");	/*Enable global interrupt*/
		}
		else
		{
			/* Do Nothing */
		}
	}
	else
	{
		/* Do nothing as the pin is input */
	}
	#endif
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
		asm("cli");

		/* read the Input Pins and Output Pins separately  */
		Result = ( ( (~(DIO[PortId].DDR) ) & (DIO[PortId].PIN) ) | ( (DIO[PortId].DDR) & (DIO[PortId].PORT) ) );

		/* Exiting the Critical Section "Enabling Global Interrupt" */
		asm("sei");
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
		asm("cli");

		/* Writing the values to the output pins without changing the values of the input pins */
		DIO[PortId].PORT  = ( ( (~(DIO[PortId].DDR)) & (DIO[PortId].PORT) ) | ( (DIO[PortId].DDR) & Level ) ) ;

		/* Exiting the Critical Section "Enabling Global Interrupt" */
		asm("sei");
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

	if( ( ( (uint16)ConfigueredChnannelGroups ) <= ( (uint16)ChannelGroupIdPtr ) ) &&\
	( ( (uint16)(&ConfigueredChnannelGroups[DIO_NUMBER_OF_CHANNEL_GROUPS-1]) ) >= ( (uint16)ChannelGroupIdPtr ) ) &&\
	!( ( (uint16)ChannelGroupIdPtr - (uint16)ConfigueredChnannelGroups ) % ( (uint16)sizeof(Dio_ChannelGroupType) ) ) )
	{
		/* Entering the Critical Section "Disabling Global Interrupt" */
		asm("cli");

		Group = ( ( ( ( (~(DIO[ChannelGroupIdPtr->PortIndex].DDR) ) & (DIO[ChannelGroupIdPtr->PortIndex].PIN) ) | ( (DIO[ChannelGroupIdPtr->PortIndex].DDR) & (DIO[ChannelGroupIdPtr->PortIndex].PORT) ) ) & ChannelGroupIdPtr->mask ) >> ChannelGroupIdPtr->offset );
		
		/* Exiting the Critical Section "Enabling Global Interrupt" */
		asm("sei");
	}
	else
	{
#if DIO_DEV_ERROR_DETECT == TRUE
		Det_ReportError(DIO_MODULE_ID,DIO_INSTANCE_ID,DIO_READ_CHANNEL_GROUP_SID,DIO_E_PARAM_INVALID_GROUP);
#endif
	}
	return Group;
}


void Dio_WriteChannelGroup(const Dio_ChannelGroupType* ChannelGroupIdPtr,Dio_PortLevelType Level )
{
	uint8 Group_Iterator;
	uint8 Group_Detected=FALSE;
	DIO_Peripherals * DIO = (DIO_Peripherals *)  &PIND;

	if( ( ( (uint16)ConfigueredChnannelGroups ) <= ( (uint16)ChannelGroupIdPtr ) ) &&\
	( ( (uint16)(&ConfigueredChnannelGroups[DIO_NUMBER_OF_CHANNEL_GROUPS-1]) ) >= ( (uint16)ChannelGroupIdPtr ) ) &&\
	!( ( (uint16)ChannelGroupIdPtr - (uint16)ConfigueredChnannelGroups ) % ( (uint16)sizeof(Dio_ChannelGroupType) ) ) )
	{
		asm("cli"); /*Disable global interrupt*/
		DIO[ChannelGroupIdPtr->PortIndex].PORT = ( DIO[ChannelGroupIdPtr->PortIndex].PORT  & ( ~( ChannelGroupIdPtr->mask ) | ~( DIO[ChannelGroupIdPtr->PortIndex].DDR ) ) ) | ( ( Level << ChannelGroupIdPtr->offset ) & DIO[ChannelGroupIdPtr->PortIndex].DDR );
		asm("sei"); /*Enable global interrupt*/
	}
	else
	{
#if DIO_DEV_ERROR_DETECT == TRUE
		Det_ReportError(DIO_MODULE_ID,DIO_INSTANCE_ID,DIO_READ_CHANNEL_GROUP_SID,DIO_E_PARAM_INVALID_GROUP);
#endif
	}

}

#if DIO_VERSION_INFO_API == TRUE

void Dio_GetVersionInfo(Std_VersionInfoType *versioninfo)
{
#if DIO_DEV_ERROR_DETECT == STD_HIGH
	if(NULL_PTR == versioninfo)
	{
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,DIO_GET_VERSION_INFO_SID, DIO_E_PARAM_POINTER);
	}
	else
#endif
	{
		versioninfo->vendorID = DIO_VENDOR_ID;
		versioninfo->moduleID = DIO_MODULE_ID;
		versioninfo->instanceID = DIO_INSTANCE_ID;
		versioninfo->sw_major_version = DIO_SW_MAJOR_VERSION;
		versioninfo->sw_minor_version = DIO_SW_MINOR_VERSION;
		versioninfo->sw_patch_version = DIO_SW_PATCH_VERSION;
	}
}

#endif

#if DIO_FLIP_CHANNEL_API == TRUE

Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId)
{
	Dio_LevelType ChannelLevel=STD_LOW;
	volatile puint8 DDRx;
	volatile puint8 PINx;
	volatile puint8 PORTx;
	uint8 Channel_Num;
	if( DIO_NUMBER_OF_CHANNELS > ChannelId )
	{
		PORTx		= ((ConfigueredChnannels[ChannelId].DDR_ptr)+UINT8_PTR_STEP);
		PINx	    = ((ConfigueredChnannels[ChannelId].DDR_ptr)-UINT8_PTR_STEP);
		DDRx     	= (ConfigueredChnannels[ChannelId].DDR_ptr);
		Channel_Num =  ConfigueredChnannels[ChannelId].pin;
		if(OUTPUT == (*DDRx>>Channel_Num)&GET_BIT)
		{
			/*Disable Global Interrupts*/
			asm("CLI");
			*(PORTx)^=(GET_BIT<<Channel_Num);
			ChannelLevel = (*PORTx >>Channel_Num) & GET_BIT ;
			/*Enable Global Interrupts*/
			asm("SEI");
		}else
		{
			ChannelLevel = (*PINx >>Channel_Num) & GET_BIT;
		}
	}else
	{
		/*Error Detection is Activated during the Development Time based on the value of DIO_DEV_ERROR_DETECT*/
		#if DIO_DEV_ERROR_DETECT == STD_HIGH
			/*Report error to the DET Module */
			Det_ReportError(DIO_MODULE_ID,DIO_INSTANCE_ID,DIO_FLIP_CHANNEL_SID,DIO_E_PARAM_INVALID_CHANNEL_ID);
		#else
			/* Do nothing */
		#endif
	}
	return ChannelLevel;
}

#endif

#if DIO_MASKED_WRITE_PORT_API == TRUE
void Dio_MaskedWritePort ( Dio_PortType PortId, Dio_PortLevelType Level, Dio_PortLevelType Mask )
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
		asm("cli");

		/* Writing the values to the output pins without changing the values of the input pins */
		DIO[PortId].PORT  = Mask & ( ( (~(DIO[PortId].DDR)) & (DIO[PortId].PORT) ) | ( (DIO[PortId].DDR) & Level ) ) ;

		/* Exiting the Critical Section "Enabling Global Interrupt" */
		asm("sei");
	}
	else
	{
		/*Do nothing*/
	}

}
#endif
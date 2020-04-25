#include "Det.h"
#include "DIO.h"
#include "DIO_MemMap.h"
#include "SchM_Dio.h"


#define PORTA_REG	(*(volatile uint8*)0x003B)
#define DDRA_REG	(*(volatile uint8*)0x003A)
#define PINA_REG 	(*(volatile uint8*)0x0039)
#define PORTB_REG	(*(volatile uint8*)0x0038)
#define DDRB_REG	(*(volatile uint8*)0x0037)
#define PINB_REG 	(*(volatile uint8*)0x0036)
#define PORTC_REG	(*(volatile uint8*)0x0035)
#define DDRC_REG	(*(volatile uint8*)0x0034)
#define PINC_REG 	(*(volatile uint8*)0x0033)
#define PORTD_REG	(*(volatile uint8*)0x0032)
#define DDRD_REG	(*(volatile uint8*)0x0031)
#define PIND_REG 	(*(volatile uint8*)0x0030)


Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId)
{
	
}

void Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level)
{
	
}

Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId)
{

}

void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level)
{
	
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
	
	
	
	
	
	
	
	
	
	
	
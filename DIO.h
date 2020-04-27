#ifndef DIO_H_
#define DIO_H_

#include "Std_Types.h"
#include "DIO_Cfg.h"

#define	DIO_MODULE_ID	1
#define	DIO_INSTANCE_ID	0

/* Service IDs */
#define DIO_READ_CHANNEL_SID           (uint8)0x00
#define DIO_WRITE_CHANNEL_SID          (uint8)0x01
#define DIO_READ_PORT_SID              (uint8)0x02
#define DIO_WRITE_PORT_SID             (uint8)0x03
#define DIO_READ_CHANNEL_GROUP_SID     (uint8)0x04
#define DIO_WRITE_CHANNEL_GROUP_SID    (uint8)0x05
#define DIO_FLIP_CHANNEL_SID           (uint8)0x11

/* DET codes  */
#define DIO_E_PARAM_INVALID_CHANNEL_ID (uint8)0x0A
#define DIO_E_PARAM_INVALID_PORT_ID    (uint8)0x14
#define DIO_E_PARAM_INVALID_GROUP      (uint8)0x1F
#define DIO_E_PARAM_POINTER            (uint8)0x20


/* Module Types */
typedef uint8 Dio_ChannelType;		//Pin  Number
typedef uint8 Dio_PortType;			//Port Number
typedef uint8 Dio_LevelType;		//STD_LOW, STD_HIGH
typedef uint8 Dio_PortLevelType;	//Size of Register

typedef struct
{
  uint8 mask;
  uint8 offset;
  Dio_PortType PortIndex;
  
} Dio_ChannelGroupType;

extern Dio_ChannelGroupType Groups[NUMBER_OF_CONFIGURED_GROUPS];


#define PORTA_ID (Dio_PortType)0
#define PORTB_ID (Dio_PortType)1
#define PORTC_ID (Dio_PortType)2
#define PORTD_ID (Dio_PortType)3


Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId);
void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level);
Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId);
void Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level);

Dio_PortLevelType Dio_ReadChannelGroup(const Dio_ChannelGroupType* ChannelGroupIdPtr );
void Dio_WriteChannelGroup(const Dio_ChannelGroupType* ChannelGroupIdPtr,Dio_PortLevelType Level );

Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId);



#endif

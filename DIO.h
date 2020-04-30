/******************************/
/* Author  : El-3fareet       */
/* Version : V1.2.2           */
/* Date    : 28-4-2020        */
/******************************/
#ifndef DIO_H_
#define DIO_H_

#include "Std_Types.h"

#define DIO_VENDOR_ID    				(uint16)1
#define DIO_SW_MAJOR_VERSION           	(uint8)1
#define DIO_SW_MINOR_VERSION           	(uint8)2
#define DIO_SW_PATCH_VERSION           	(uint8)2

#define DIO_DEV_ERROR_DETECT				STD_HIGH
/* Controller Ports */
#define  PORT_A								3
#define  PORT_B								2
#define  PORT_C								1
#define  PORT_D								0
/* Module IDs*/
#define	DIO_MODULE_ID						(uint16)1
#define	DIO_INSTANCE_ID						(uint8)0

/* Service IDs */
#define DIO_READ_CHANNEL_SID           (uint8)0x00
#define DIO_WRITE_CHANNEL_SID          (uint8)0x01
#define DIO_READ_PORT_SID              (uint8)0x02
#define DIO_WRITE_PORT_SID             (uint8)0x03
#define DIO_READ_CHANNEL_GROUP_SID     (uint8)0x04
#define DIO_WRITE_CHANNEL_GROUP_SID    (uint8)0x05
#define DIO_GET_VERSION_INFO_SID	   (uint8)0x12
#define DIO_FLIP_CHANNEL_SID           (uint8)0x11

/* DET codes  */
#define DIO_E_PARAM_INVALID_CHANNEL_ID (uint8)0x0A
#define DIO_E_PARAM_INVALID_PORT_ID    (uint8)0x14
#define DIO_E_PARAM_INVALID_GROUP      (uint8)0x1F
#define DIO_E_PARAM_POINTER            (uint8)0x20

/*configuration types*/
typedef struct
{
	volatile uint8* DDR_ptr;
	uint8 pin;
}Dio_ChannelCfgType;

/* Module Types */
typedef uint8 Dio_ChannelType;
typedef uint8 Dio_PortType;
typedef uint8 Dio_LevelType;
typedef uint8 Dio_PortLevelType;

typedef struct
{
  uint8 mask;
  uint8 offset;
  Dio_PortType PortIndex;
  
} Dio_ChannelGroupType;



#include "DIO_Cfg.h"

/*Default configuration guard*/
#ifndef DIO_DEV_ERROR_SETECT
#define DIO_DEV_ERROR_SETECT FALSE
#endif

#ifndef DIO_FLIP_CHANNEL_API
#define DIO_FLIP_CHANNEL_API FALSE
#endif

#ifndef DIO_MASKED_WRITE_PORT_API
#define DIO_MASKED_WRITE_PORT_API FALSE
#endif

#ifndef DIO_VERSION_INFO_API
#define DIO_VERSION_INFO_API FALSE
#endif

/************************************************************************************
 * Service Name: Dio_ReadChannel 													*
 * Service ID[hex]: 0x00															*
 * Sync/Async: Synchronous 															*
 * Reentrancy: Reentrant 															*
 * Parameters (in): ChannelId -> ID of DIO channel. 								*
 * Parameters (inout): None 														*
 * Parameters (out): None 															*
 * Return value: Dio_LevelType ->  STD_HIGH or STD_LOW								*
 * Description: Function to read the value of the specified DIO channel.    		*
 ************************************************************************************/
Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId);

/************************************************************************************
 * Service Name: Dio_WriteChannel 													*
 * Service ID[hex]: 0x01															*
 * Sync/Async: Synchronous 															*
 * Reentrancy: Reentrant 															*
 * Parameters (in): ChannelId -> ID of DIO channel. 								*
 *  				Level     -> Value to be written.	 							*
 * Parameters (inout): None 														*
 * Parameters (out): None 															*
 * Return value: None																*
 * Description: Function to set the specified Level for the specified channel. 		*
 ************************************************************************************/
void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level);

/*********************************************************************************************************/
/* Service Name: Dio_ReadPort                                                                            */
/* Service ID[hex]: 0x02                                                                                 */
/* Syncronization: Synchronous                                                                           */
/* Reentrancy: Reentrant                                                                                 */
/* Parameters (in): PortId -ID of DIO Port-.                                                             */
/* 				   PortId is refered to as a symbolic name in DIO_Cfg.h and takes range of values        */
/* 				   from the following:                                                                   */
/* 				   [ PORT_A , PORT_B, PORT_C, PORT_D ]                                                   */
/* Parameters (inout): None                                                                              */
/* Parameters (out): None                                                                                */
/* Return value: Dio_PortLevelType -holds the value of the whole port-                                   */
/* Description: Function to Return the level of all channels of that port.                               */
/* SW Requirements Coverage:                                                                             */
/* 		1- SWS_Dio_00051 : The DIO module shall not buffer data when providing read and write services.  */
/* 	    2- SWS_Dio_00005 : NO Interruptible read-modify-write sequences.                                 */
/* 	    3- SWS_Dio_00060 : All read and write functions of the Dio module shall be reentrant.            */
/* 	    4- SWS_Dio_00026 : The configuration process for Dio module shall provide symbolic names.        */
/* 	    5- SWS_DIO_00113 : The Dio module shall publish the symbolic names in the "Dio_Cfg.h".           */
/* 	    6- SWS_Dio_00012 : The Dio module’s read functions shall work on input and output channels.      */
/* 	    7- SWS_Dio_00118 : If development errors are enabled and an error ocurred the Dio                */
/*						   module’s read functions shall return with the value '0'                       */
/* 	    8- SWS_Dio_00013 : The Dio_ReadPort function shall read the levels of all                        */
/*						   channels of one port. A bit value '0' indicates that the corresponding channel*/
/*			      	       is physical STD_LOW, a bit value '1' indicates that the corresponding channel */
/*						   is physical STD_HIGH.                                                         */
/*********************************************************************************************************/
Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId);

/*********************************************************************************************************/
/* Service Name: Dio_WritePort                                                                           */
/* Service ID[hex]: 0x03                                                                                 */
/* Syncronization: Synchronous                                                                           */
/* Reentrancy: Reentrant                                                                                 */
/* Parameters (in): PortId - ID of DIO Port.                                                             */
/*                  Level - Value to be written.                                                         */
/* Parameters (inout): None                                                                              */
/* Parameters (out): None                                                                                */
/* Return value: None                                                                                    */
/* Description: Function to set a value of the port.                                                     */
/* SW Requirements Coverage:                                                                             */
/* 		1- SWS_Dio_00051 : The DIO module shall not buffer data when providing read and write services.  */
/* 	    2- SWS_Dio_00005 : NO Interruptible read-modify-write sequences.                                 */
/* 	    3- SWS_Dio_00060 : All read and write functions of the Dio module shall be reentrant.            */
/* 	    4- SWS_Dio_00026 : The configuration process for Dio module shall provide symbolic names.        */
/* 	    5- SWS_DIO_00113 : The Dio module shall publish the symbolic names in the "Dio_Cfg.h".           */
/* 	    6- SWS_Dio_00064 : The Dio module’s write functions shall work on input and output channels.     */
/* 	    7- SWS_Dio_00070 : If a Dio write function is used on an input channel, it shall have            */
/*                           no effect on the physical output level.                                     */
/*      8- SWS_Dio_00119 : If development errors are enabled and an error occurred, the Dio              */
/*						   module’s write functions shall NOT process the write command.                 */
/* 	 	9- SWS_Dio_00007 : The Dio_WritePort function shall simultaneously set the                       */
/*					   	   levels of all output channels. A bit value '0' sets the corresponding channel */
/*						   to physical STD_LOW, a bit value '1' sets the corresponding channel to        */
/*						   physical STD_HIGH.                                                            */
/*	   10- SWS_Dio_00004 : The Dio_WritePort function shall ensure that the functionality                */
/*						   of the input channels of that port is not affected.                           */
/*********************************************************************************************************/
void Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level);

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
Dio_PortLevelType Dio_ReadChannelGroup(const Dio_ChannelGroupType* ChannelGroupIdPtr );

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
void Dio_WriteChannelGroup(const Dio_ChannelGroupType* ChannelGroupIdPtr,Dio_PortLevelType Level );

#if DIO_VERSION_INFO_API == TRUE
/************************************************************************************
* Service Name: Dio_GetVersionInfo													*
* Service ID[hex]: 0x12																*
* Sync/Async: Synchronous															*
* Reentrancy: Reentrant																*
* Parameters (in): None																*
* Parameters (inout): None 															*
* Parameters (out): VersionInfo -> Pointer to where to store the 					*
								   version information of this module.				*
* Return value: None 																*
* Description: Function to get the version information of this module.				*
************************************************************************************/
void Dio_GetVersionInfo(Std_VersionInfoType *versioninfo);
#endif

#if DIO_FLIP_CHANNEL_API == TRUE
/*********************************************************************************************************/
/* Service Name: Dio_FlipChannel                                                                         */
/* Service ID[hex]: 0x11                                                                                 */
/* Syncronization: Synchronous                                                                           */
/* Reentrancy: Reentrant                                                                                 */
/* Parameters (in): ChannelId -> ID of DIO channel.-.                                                    */
/* Parameters (inout): None                                                                              */
/* Parameters (out): None                                                                                */
/* Return value: Dio_LevelType ->  STD_HIGH or STD_LOW                                                   */
/* Description: Service to flip (change from 1 to 0 or from 0 to 1) the level of a channel and return    */
/*                              the level of the channel after flip.                                     */
/* SW Requirements Coverage:                                                                             */
/* 		  1- SWS_Dio_00191 : If the specified channel is configured as an output channel,                  */
/*                         the Dio_FlipChannel function shall read level of the channel                  */
/*                         (requirements [DIO083] & [DIO084] are applicable) and invert it,              */
/*                         then write the inverted level to the channel.                                 */
/*                         The return value shall be the inverted level of the specified channel.        */
/* 	    2- SWS_Dio_00192 : If the specified channel is configured as an input channel,                   */
/*                         the Dio_FlipChannel function shall have no influence on the physical output.  */
/*                        The return value shall be the level of the specified channel.                  */
/* 	    3- SWS_Dio_00193 : If the specified channel is configured as an input channel,                   */
/*                        the Dio_FlipChannel function shall have no influence on the result             */
/*                        of the next Read-Service.                                                      */
/*********************************************************************************************************/
Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId);
#endif

#if DIO_MASKED_WRITE_PORT_API == TRUE
/********************************************************************************************************/
/*Service Name: 	Dio_MaskedWritePort 																*/
/*Service ID: 		[hex]0x13 																			*/
/*Sync/Async:		Synchronous																			*/
/*Reentrancy:		Reentrant 																			*/
/*Parameters (in):	PortId -> ID of DIO Port 															*/
/*					Level  -> Value to be written 														*/
/*					Mask   -> Channels to be masked in the port 										*/
/*Parameters (inout): None 																				*/
/*Parameters (out): None 																				*/
/*Return value: None 																					*/
/*Description: Service to set the value of a given port with required mask. 							*/
/*Available via: Dio.h 																					*/
/*SW Requirements Coverage: 																			*/
/*	1- [SWS_Dio_00202] ⌈ The Dio_MaskedWritePort function shall set the specified value for 			*/
/*	the channels in the specified port if the corresponding bit in Mask is '1'. ⌋ (SRS_Dio_12003)		*/
/*	2- [SWS_Dio_00203] ⌈When the Dio_MaskedWritePort function is called, DIO Channels that are 			*/
/*	configured as input shall remain unchanged. ⌋ (SRS_Dio_12003) 										*/
/*	3- [SWS_Dio_00204] ⌈ When writing a port which is smaller than the Dio_PortLevelType using the 		*/
/*	Dio_MaskedWritePort function (see [SWS_Dio_00103]), the function shall ignore the MSB.⌋ () 			*/
/********************************************************************************************************/

void Dio_MaskedWritePort ( Dio_PortType PortId, Dio_PortLevelType Level, Dio_PortLevelType Mask );
#endif

#endif

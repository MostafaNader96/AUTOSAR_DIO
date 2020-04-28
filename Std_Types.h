/******************************/
/* Author  : El-3fareet       */
/* Version : V1.0.1           */
/* Date    : 28-4-2020        */
/******************************/
#ifndef STD_TYPES_H_
#define STD_TYPES_H_

#include "Compiler.h"
#include "Platform_Types.h"

typedef uint8  Std_ReturnType;

#define STD_HIGH        1      
#define STD_LOW         0      

typedef struct
{
  uint16  vendorID;
  uint16  moduleID;
  uint8 instanceID;
  uint8 sw_major_version;
  uint8 sw_minor_version;
  uint8 sw_patch_version;
} Std_VersionInfoType;



#endif

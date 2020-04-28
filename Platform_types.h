/******************************/
/* Author  : El-3fareet       */
/* Version : V1.0.0	          */
/* Date    : 28-4-2020        */
/******************************/
#ifndef PLATFORM_TYPES_H_
#define PLATFORM_TYPES_H_

#ifndef FALSE
#define FALSE       0
#endif
#ifndef TRUE
#define TRUE        1
#endif

typedef unsigned char 		uint8;
typedef unsigned short 		uint16;
typedef unsigned long int 	uint32;
typedef signed char 		sint8;
typedef signed short 		sint16;
typedef signed long int 	sint32;
typedef float 				float32 ;
typedef double 				float64 ;
typedef long double 		float128 ;

typedef uint8*  		    puint8;
typedef uint16* 		    puint16;
typedef uint32* 		    puint32;
typedef sint8*  		    psint8;
typedef sint16* 		    psint16;
typedef sint32* 		    psint32;
typedef float32* 		    pfloat32;
typedef float64* 		    pfloat64;


#endif

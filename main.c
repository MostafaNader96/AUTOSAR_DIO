/*
 * main.c
 *
 *  Created on: Apr 26, 2020
 *      Author: El-3fareet
 */
#include <avr/io.h>
#include "DIO.h"

int main (void)
{
	DDRA=0x00;
	Dio_ReadChannelGroup(RGB_LED,0b101);
	while(1);
	return 0;
}

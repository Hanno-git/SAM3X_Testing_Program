/*
 * PIO_SAM.c
 *
 * Created: 2022/03/08 15:10:45
 *  Author: hanno
 */ 

#include "PIO_SAM.h"

void Toggle_Output(Pio *PORT,uint8_t PIN)
{
	static uint32_t t;

	t = (PORT->PIO_ODSR>>(PIN))&(0x1);
	if (t)//tests if LED PIO is active
	{
		PORT->PIO_CODR = 0x1 << PIN;
	}
	else
	{
		PORT->PIO_SODR= 0x1 << PIN;
	}
}
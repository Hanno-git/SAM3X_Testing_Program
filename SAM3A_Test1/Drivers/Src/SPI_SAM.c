/*
 * SPI_SAM.c
 *
 * Created: 2022/03/08 14:19:28
 *  Author: hanno
 */ 
#include "SPI_SAM.h"

void SPI_transfer(const char myString[])
{
	volatile uint32_t temp;
	uint8_t count = 0;
	while (myString[count])
	{
		temp = (SPI0->SPI_SR>>1)&(0x0001);
		while (temp==0)//tests data register is ready
		{
			temp = (SPI0->SPI_SR>>1)&(0x0001);//Data has been written to SPI_TDR and not yet transferred to the serializer
		}
		//set data to be transferred
		SPI0->SPI_TDR |= SPI_TDR_TD(myString[count]);
		
		temp = (SPI0->SPI_SR>>1)&(0x0001);
		while (temp==0)//tests data register is ready
		{
			temp = (SPI0->SPI_SR>>1)&(0x0001);//Data has been written to SPI_TDR and not yet transferred to the serializer
		}
		
		count ++;
	}
	
	
	
}
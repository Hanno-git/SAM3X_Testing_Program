/*
 * SPI_SAM.c
 *
 * Created: 2022/03/08 14:19:28
 *  Author: hanno
 */ 
#include "SPI_SAM.h"

void SPI_transfer(void)
{
	volatile uint32_t temp;
	
	temp = (SPI0->SPI_SR>>1)&(0x0001);
	if (temp==0)//tests data register is ready
	{
		temp = (SPI0->SPI_SR>>1)&(0x0001);//Data has been written to SPI_TDR and not yet transferred to the serializer		
	}
	//set data to be transferred
	SPI0->SPI_TDR |= SPI_TDR_TD(0xA6);
	temp = (SPI0->SPI_SR>>1)&(0x0001);
	if (temp==0)//tests data register is ready
	{
			temp = (SPI0->SPI_SR>>1)&(0x0001);//Data has been written to SPI_TDR and not yet transferred to the serializer		
	}
	
	
}
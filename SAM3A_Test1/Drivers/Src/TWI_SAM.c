/*
 * TWI_SAM.c
 *
 * Created: 2022/03/08 14:23:07
 *  Author: hanno
 */ 

#include "TWI_SAM.h"

void I2C_WRITE_RTC(uint8_t Add_Byte, uint8_t w_Byte)
{
	static uint32_t status_transmit;
	//Set device address
	TWI0->TWI_MMR |= TWI_MMR_DADR(0b11011111);
	//sets Module to write mode
	TWI0->TWI_MMR &= ~(TWI_MMR_MREAD);
	//sets Internal Device Address Size to 1 Byte
	TWI0->TWI_MMR &= ~(TWI_MMR_IADRSZ_Msk);
	TWI0->TWI_MMR |= (TWI_MMR_IADRSZ_1_BYTE);
	//sets address to write to
	TWI0 ->TWI_IADR = 0x000F&Add_Byte;
	//loads data to be transmitted
	TWI0 ->TWI_THR = w_Byte;
	//wait for transmission to finish
	status_transmit = (TWI0->TWI_IMR>>2)&(0x0001);
	while ((~status_transmit)&0X1)
	{
		status_transmit = (TWI0->TWI_IMR>>2)&(0x0001);
	}
	// sends stop condition
	TWI0->TWI_CR |= TWI_CR_STOP;
	//wait for entire transmission completion
	status_transmit = (TWI0->TWI_IMR>>0)&(0x0001);
	while ((~status_transmit)&0X1)
	{
		status_transmit = (TWI0->TWI_IMR>>2)&(0x0001);
	}
	return;
	
}

uint8_t I2C_READ_RTC(uint8_t Add_Byte)
{
	static uint8_t read;
	static uint32_t status_read;
	//Set device address
	TWI0->TWI_MMR |= TWI_MMR_DADR(0b11011110);
	//sets Module to read mode
	TWI0->TWI_MMR |= (TWI_MMR_MREAD);
	//sets Internal Device Address Size to 1 Byte
	TWI0->TWI_MMR &= ~(TWI_MMR_IADRSZ_Msk);
	TWI0->TWI_MMR |= (TWI_MMR_IADRSZ_1_BYTE);
	//sets address to read
	TWI0 ->TWI_IADR = 0x000F&Add_Byte;
	//Start the transfer
	TWI0->TWI_CR = TWI_CR_START;
	//wait for transmission to finish
	status_read = (TWI0->TWI_IMR>>1)&(0x0001);
	while (~status_read)
	{
		status_read = (TWI0->TWI_IMR>>1)&(0x0001);
	}
	//grabs received data byte
	read =TWI0 ->TWI_RHR;
	
	//wait for entire transmission completion
	status_read = (TWI0->TWI_IMR>>0)&(0x0001);
	while (~status_read)
	{
		status_read = (TWI0->TWI_IMR>>0)&(0x0001);
	}
	return read;
}
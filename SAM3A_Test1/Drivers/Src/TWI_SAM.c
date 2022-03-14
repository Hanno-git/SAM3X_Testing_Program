/*
 * TWI_SAM.c
 *
 * Created: 2022/03/08 14:23:07
 *  Author: hanno
 */ 

#include "TWI_SAM.h"

void I2C_WRITE_RTC_single(Twi *I2C, uint32_t Add_Byte, uint8_t w_Byte)
{
	static uint32_t status_transmit;
	
	//sets Module to write mode
	I2C->TWI_MMR &= ~(TWI_MMR_MREAD);
	//sets address to write to
	I2C ->TWI_IADR = Add_Byte;
	//loads data to be transmitted
	I2C ->TWI_THR = w_Byte;
	//wait for transmission to finish
	status_transmit = (I2C->TWI_IMR>>2)&(0x0001);
	while (status_transmit==0)
	{
		status_transmit = (I2C->TWI_IMR>>2)&(0x0001);
	}
	// sends stop condition
	I2C->TWI_CR |= TWI_CR_STOP;
	//wait for transmission to finish
	status_transmit = (I2C->TWI_IMR>>2)&(0x0001);
	while (status_transmit==0)
	{
		status_transmit = (I2C->TWI_IMR>>2)&(0x0001);
	}
	
	//wait for entire transmission completion
	status_transmit = (TWI0->TWI_IMR>>0)&(0x0001);
	while (status_transmit==0)
	{
		status_transmit = (I2C->TWI_IMR>>2)&(0x0001);
	}
	return;
	
}

void I2C_WRITE_RTC_multiple(Twi *I2C, uint32_t Add_Byte, uint8_t *w_Byte, uint32_t w_len)
{
	static uint32_t status_transmit,count=0;
	
	//sets Module to write mode
	I2C->TWI_MMR &= ~(TWI_MMR_MREAD);
	//sets address to write to
	I2C ->TWI_IADR = Add_Byte;
	
	while (count<w_len)//transmits multiple bytes of data
	{
		//loads data to be transmitted
		I2C ->TWI_THR = (w_Byte+count);
		
		//wait for transmission to finish
		status_transmit = (I2C->TWI_IMR>>2)&(0x0001);
		while (status_transmit==0)
		{
			status_transmit = (I2C->TWI_IMR>>2)&(0x0001);
		}
		
		count = count+1;//increment counter
	}

	// sends stop condition
	I2C->TWI_CR |= TWI_CR_STOP;
	//wait for transmission to finish
	status_transmit = (I2C->TWI_IMR>>2)&(0x0001);
	while (status_transmit==0)
	{
		status_transmit = (I2C->TWI_IMR>>2)&(0x0001);
	}
	
	//wait for entire transmission completion
	status_transmit = (TWI0->TWI_IMR>>0)&(0x0001);
	while (status_transmit==0)
	{
		status_transmit = (I2C->TWI_IMR>>2)&(0x0001);
	}
	return;
	
}

uint8_t I2C_READ_RTC_single(Twi *I2C, uint32_t Add_Byte)
{
	static uint8_t read;
	static uint32_t status_read;
	//sets address to write to
	I2C ->TWI_IADR = Add_Byte;
	//sets Module to read mode
	I2C->TWI_MMR |= (TWI_MMR_MREAD);
	
	//Start the transfer
	I2C->TWI_CR = TWI_CR_START;
	//wait for transmission to finish
	status_read = (I2C->TWI_IMR>>1)&(0x0001);
	while (status_read==0)
	{
		status_read = (I2C->TWI_IMR>>1)&(0x0001);
	}
	//grabs received data byte
	read =I2C ->TWI_RHR;
	
	//wait for entire transmission completion
	status_read = (I2C->TWI_IMR>>0)&(0x0001);
	while (status_read==0)
	{
		status_read = (I2C->TWI_IMR>>0)&(0x0001);
	}
	return read;
}

void I2C_READ_RTC_multiple(Twi *I2C, uint32_t Add_Byte, uint8_t *read_lst, uint8_t read_len)
{
	static uint32_t count=0;
	static uint32_t status_read;
	//sets address to write to
	I2C ->TWI_IADR = Add_Byte;
	//sets Module to read mode
	I2C->TWI_MMR |= (TWI_MMR_MREAD);
	
	//Start the transfer
	I2C->TWI_CR = TWI_CR_START;
	while (count<read_len -1)//read multiple bytes
	{
		//wait for transmission to finish
		status_read = (I2C->TWI_IMR>>1)&(0x0001);
		while (status_read==0)
		{
			status_read = (I2C->TWI_IMR>>1)&(0x0001);
		}
		//grabs received data byte
		*(read_lst+count) =I2C ->TWI_RHR;
		
		count=count+1;//increment counter
	}
	
	I2C->TWI_CR = TWI_CR_STOP;//stop transfer when only one byte to read remaining
	
	
	//wait for transmission to finish
	status_read = (I2C->TWI_IMR>>1)&(0x0001);
	while (status_read==0)
	{
		status_read = (I2C->TWI_IMR>>1)&(0x0001);
	}
	*(read_lst+read_len-1) =I2C ->TWI_RHR; //read last byte
	
	
	//wait for entire transmission completion
	status_read = (I2C->TWI_IMR>>0)&(0x0001);
	while (status_read==0)
	{
		status_read = (I2C->TWI_IMR>>0)&(0x0001);
	}
	return;
}
/*
 * pio.c
 *
 * Created: 2022/03/01 
 * Author : hanno
 */ 

#include "pio_init.h"

void PIO_IO_init(uint8_t IO, Pio *PORT, uint8_t PIN, uint8_t PIO)//initialize pin as Input (1) or Output(0); PIO -> 0=PIO control, 1=A peripheral, 2=B peripheral
{
	volatile uint32_t t1;
	// Disables the Write Protect
	PORT ->PIO_WPMR =(PIO_WPMR_WPKEY(0x50494F))|~(PIO_WPMR_WPEN);
	// Grabs PIO Write Protect Status
	t1 =  PORT->PIO_PSR;
	t1 = (t1>>(PIN))&(0x1);//
	t1=(~t1)&(0x1);
	if (t1)//tests if PIO is active
	{
		while (1)
		{
			//fault pins PIO is inactive
		}
	}
	if (PIO==0)
	{
		// Enables the PIO to control
		PORT->PIO_PER |=((0x1u << PIN));//set
		
		// Grabs PIO Controller status for respective pins
		t1 =  PORT->PIO_PSR;
		t1 = (t1>>(PIN)&(0x1));//
		t1=(~t1)&(0x1);
		if (t1)//tests if PIO is active
		{
			while (1)
			{
				//fault pins PIO is inactive
			}
		}
	}
	else
	{
		// Disables the PIO to control
		PORT->PIO_PDR |=((0x1u << PIN));//set
		// Grabs PIO Controller status for respective pin
		t1 = (PORT->PIO_PSR>>(PIN)&(0x1));//
		if (t1)//tests if PIO is active
		{
			while (1)
			{
				//fault pins PIO is inactive
			}
		}
		
		if (PIO == 1)//PIO Peripheral AB
		{
			PORT->PIO_ABSR&=(~0x1)<<PIN;//set peripheral to A
		}
		if (PIO == 2)
		{
			PORT->PIO_ABSR|=(0x1)<<PIN;//set peripheral to B
		}
	}
	
	
	if (IO)
	{	// Disable the output line
		PORT->PIO_ODR |=(0x1u << PIN);//set
		// Grabs PIO Controller Output Status for respective pins
		t1 = (PORT->PIO_OSR>>PIN)&(0x1);
		if (t1)//tests if I/O is set correctly
		{
			while (1)
			{
				//fault I/O incorrectly set
			}
		}	
	} 
	else
	{	//Enable the output line
		PORT->PIO_OER |=((0x1u << PIN));//set
		// Grabs PIO Controller Output Status for respective pins
		t1 = (PORT->PIO_OSR>>PIN);//
		t1=(~(t1&(0x1)))&(0x1);
		if (t1)//tests if I/O is set correctly
		{
			while (1)
			{
				//fault I/O incorrectly set
			}
		}
	}
	
	
	
	// Grabs PIO Controller Input Filter Status for respective pins
	t1 = (PORT->PIO_IFER>>(PIN)&(0x0001));
	if (t1)//test if input glitch filter is disabled on the I/O line 
	{
		while (1)
		{
			//fault input glitch filter is enabled on the I/O line
		}
	}
	
	if ((~IO)&(0x1)&(PIO==0))
	{
		// Enables Output Write Enable Register
		PORT->PIO_OWER |=((0x1u << PIN));//set

		// GrabsPIO Output Write Status Register for respective pins
		t1 = (PORT->PIO_OWSR>>(PIN))&(0x1);
		if ((~t1)&(0x1))// Writing PIO_ODSR affects the I/O line. 
		{
			while (1)
			{
				//fault Writing PIO_ODSR does not affect the I/O line 
			}
		}
	}	
	
}

void LED_PIO_init(void)
{
	//Disable PMC Write Protect Mode Register
	PMC->PMC_WPMR =PMC_WPMR_WPKEY_PASSWD|~(PMC_WPMR_WPEN);
	//Enable Peripheral Clock
	PMC->PMC_PCER0 |= (PMC_PCER0_PID11);//enable clock for port A
	PMC->PMC_PCER0 |= (PMC_PCER0_PID12);//enable clock for port B
	
	PIO_IO_init(Output,RED_PB26_PORT,RED_PB27_PIN,PIO_control);
	PIO_IO_init(Input,GREEN_PA15_PORT,GREEN_PA15_PIN,PIO_control);
	
}

void USART_PIO_init(void)
{
	//Disable PMC Write Protect Mode Register
	PMC->PMC_WPMR =PMC_WPMR_WPKEY_PASSWD|~(PMC_WPMR_WPEN);
	//Enable Peripheral Clock
	PMC->PMC_PCER0 |= (PMC_PCER0_PID17);//enable clock for USART0
	
	PIO_IO_init(Output,TXD0_PA11_PORT,TXD0_PA11_PIN,Peripheral_A);
	PIO_IO_init(Input,RDX0_PA10_PORT,RDX0_PA10_PIN,Peripheral_A);
	
}

void TWI0_PIO_init(void)
{
	//Disable PMC Write Protect Mode Register
	PMC->PMC_WPMR =PMC_WPMR_WPKEY_PASSWD|~(PMC_WPMR_WPEN);
	//Enable Peripheral Clock
	PMC->PMC_PCER0 |= (PMC_PCER0_PID22);//enable clock for TWI0
	
	PIO_IO_init(Output,TWD0_SCL_PA18_PORT,TWD0_SCL_PA18_PIN,Peripheral_A);
	PIO_IO_init(Output,TWD0_SDA_PA17_PORT,TWD0_SDA_PA17_PIN,Peripheral_A);

	
}

void PWM_PIO_init(void)
{
	//Disable PMC Write Protect Mode Register
	PMC->PMC_WPMR =PMC_WPMR_WPKEY_PASSWD|~(PMC_WPMR_WPEN);
	//Enable Peripheral Clock
	PMC->PMC_PCER0 |= (PMC_PCER1_PID36);//enable clock for PWM
	
	
	PIO_IO_init(Output,PWMH3_PB15_PORT,PWMH3_PB15_PIN,Peripheral_B);
	PIO_IO_init(Output,PWML3_PA0_PORT,PWML3_PA0_PIN,Peripheral_B);
	//PIO_IO_init(Output,PWMH0_PB12_PORT,PWMH0_PB12_PIN,Peripheral_B);
	PIO_IO_init(Input,PWMFI1_PA3_PORT,PWMFI1_PA3_PIN,Peripheral_B);
	
}

void SPI_PIO_init(void)
{
	//Disable PMC Write Protect Mode Register
	PMC->PMC_WPMR =PMC_WPMR_WPKEY_PASSWD|~(PMC_WPMR_WPEN);
	//Enable Peripheral Clock
	PMC->PMC_PCER0 |= (PMC_PCER0_PID24);//enable clock for SPI0
	
	PIO_IO_init(Output,SPI0_SPCK_PA27_PORT,SPI0_SPCK_PA27_PIN,Peripheral_A);
	PIO_IO_init(Output,SPI0_MOSI_PA26_PORT,SPI0_MOSI_PA26_PIN,Peripheral_A);
	PIO_IO_init(Input,SPI0_MISO_PA25_PORT,SPI0_MISO_PA25_PIN,Peripheral_A);
	
}


void ADC_PIO_init(void)
{
	//Disable PMC Write Protect Mode Register
	PMC->PMC_WPMR =PMC_WPMR_WPKEY_PASSWD|~(PMC_WPMR_WPEN);
	//Enable Peripheral Clock
	PMC->PMC_PCER0 |= (PMC_PCER1_PID37);//enable clock for SPI0
	
	PIO_IO_init(Input,REF1V65_AD0_PA2_PORT,REF1V65_AD0_PA2_PIN,Alternate_function);
}

void DAC_PIO_init(void)
{
	//Disable PMC Write Protect Mode Register
	PMC->PMC_WPMR =PMC_WPMR_WPKEY_PASSWD|~(PMC_WPMR_WPEN);
	//Enable Peripheral Clock
	PMC->PMC_PCER0 |= (PMC_PCER1_PID38);//enable clock for SPI0
	
	PIO_IO_init(Output,DAC1_PB16_PORT,DAC1_PB16_PIN,Alternate_function);
	
}


void PIO_INIT(void)
{
	LED_PIO_init();
	USART_PIO_init();
	TWI0_PIO_init();
	SPI_PIO_init();
	ADC_PIO_init();
	DAC_PIO_init();
	PWM_PIO_init();
		
}
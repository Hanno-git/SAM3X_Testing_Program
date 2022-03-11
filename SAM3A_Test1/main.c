/*
 * GccApplication1.c
 *
 * Created: 2022/02/28 14:35:07
 * Author : hanno
 */ 
#include "sam.h"
#include "pio_init.h"
#include "PIO_SAM.h"
#include "USART_init_SAM.h"
#include "USART_SAM.h"
#include "PWM_init_SAM.h"
#include "TWI_init_SAM.h"
#include "TWI_SAM.h"
#include "SPI_init_SAM.h"
#include "SPI_SAM.h"
#include "ADC_init_SAM.h"
#include "ADC_SAM.h"
#include "DAC_init_SAM.h"
#include "RTC_init_ISL12022M.h"
#include "RTC_ISL.h"
void DELAY(uint32_t delay);

int main(void)
{
	/* Initialize variables */
	struct time_RTC time; 
	volatile uint32_t a = 0;
    /* Initialize the SAM system */
    SystemInit();
	SystemCoreClockUpdate();

	/* Initialize the peripherals */
	PIO_INIT();//works
	//TWI_init();
	USART0_init();//works
	DAC_init();//works
	ADC_init();//works
	PWM_init();//works  
	/*
	SPI_init();
	RTC_init();*/
	/* Define Time */
	/*
	time.sec= 0;
	time.min= 15;
	time.hour= 10;
	time.pm= 0;
	time.t24_mode= 0;
	time.date= 10;
	time.month_int= 3;
	time.year= 2022;
	time.Day_of_Week_int= 4;*/
	
	
	// Continuously toggle LEDs
    while (1)
    {
		DELAY(1000);
		Toggle_Output(RED_PB26_PORT,RED_PB27_PIN);
		//printString("HELLO World");
		//a = ADC_READ();
		//Get_Time(&time);
		//Set_Time(&time);
		//DELAY(100);
		//Toggle_Output(GREEN_PA15_PORT,GREEN_PA15_PIN);
	}
	    
}

void DELAY(uint32_t delay) //delay in ms
{
	volatile uint32_t cnt = 0;
	if (delay>10000)//overflow protection
	{
		delay = 10000;
	}
	delay = 6666*delay; //adjust delay to represent clock cycles
	while(cnt<=delay)
	{
		cnt =cnt+1;
	}
}
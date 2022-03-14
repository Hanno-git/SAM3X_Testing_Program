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
#include "asf.h"

xTaskHandle Task1_id;
xTaskHandle Task2_id;
void DELAY(uint32_t delay);
void vApplicationMallocFailedHook( void );

static void Task1_task(void *pvParameters)
{
	portTickType xLastWakeTime;
	const portTickType xFrequency = 100;

	// Initialise the xLastWakeTime variable with the current time.
	xLastWakeTime = xTaskGetTickCount();
	for(;;)
	{
		/* task application*/
	
		//DELAY(100);
		vTaskDelayUntil( &xLastWakeTime, xFrequency );
		Toggle_Output(OUT_A1_PA24_PORT,OUT_A1_PA24_PIN);
		
	}
	/* Should never go there */
	vTaskDelete(NULL);
}

static void Task2_task(void *pvParameters)
{
	portTickType xLastWakeTime;
	const portTickType xFrequency = 150;

	// Initialise the xLastWakeTime variable with the current time.
	xLastWakeTime = xTaskGetTickCount();
	for(;;)
	{
		/* task application*/
		
		//DELAY(150);
		vTaskDelayUntil( &xLastWakeTime, xFrequency );
		Toggle_Output(OUT_A0_PA16_PORT,OUT_A0_PA16_PIN);
		
		
		
	}
	/* Should never go there */
	vTaskDelete(NULL);
}



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
	SPI_init();//works
	/*
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
	//xTaskGenericCreate( pdTASK_CODE pxTaskCode, const signed char * const pcName, unsigned short usStackDepth, void *pvParameters, unsigned portBASE_TYPE uxPriority, xTaskHandle *pxCreatedTask, portSTACK_TYPE *puxStackBuffer, const xMemoryRegion * const xRegions ) PRIVILEGED_FUNCTION;
	/* Create Worker 1 task */
	xTaskCreate(Task1_task,NULL,configMINIMAL_STACK_SIZE+400,NULL, 1,& Task1_id);
	xTaskCreate(Task2_task,NULL,configMINIMAL_STACK_SIZE+400,NULL, 2,& Task2_id);
	/*Start Scheduler*/
	vTaskStartScheduler();
	// Continuously toggle LEDs
    while (1)
    {
		a = 0;
		while(a<=500)
		{
		a =a+1;
		}
		//Toggle_Output(RED_PB26_PORT,RED_PB27_PIN);
		SPI_transfer();
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

void vApplicationMallocFailedHook( void )
{
	while(1)
	{
		
	}
}
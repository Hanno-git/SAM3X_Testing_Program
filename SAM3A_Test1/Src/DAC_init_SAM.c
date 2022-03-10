/*
 * DAC_init_SAM.c
 *
 * Created: 2022/03/08 13:31:18
 *  Author: hanno
 */ 
#include "DAC_init_SAM.h"

void DAC_init(void)
{
	volatile uint32_t temp;
	//Disable DAC Write Protect Mode Register
	DACC->DACC_WPMR =DACC_WPMR_WPKEY(0x444143)|~(DACC_WPMR_WPEN);
	//Enable Peripheral Clock
	PMC->PMC_PCER1 |= (PMC_PCER1_PID38);//enable clock for DAC
	/*//Select Channel 1
	DACC->DACC_MR |= DACC_MR_USER_SEL_CHANNEL1;*/
	//set startup time
	DACC->DACC_MR &= ~(DACC_MR_STARTUP_Msk);
	DACC->DACC_MR |= (DACC_MR_STARTUP_1344);
	/*//set refresh period
	DACC->DACC_MR &= ~(DACC_MR_REFRESH_Msk);
	DACC->DACC_MR |= (DACC_MR_REFRESH(0x30));*/
	// Disable channel 0 and enable channel 1
	DACC->DACC_CHDR|= DACC_CHER_CH0;
	DACC->DACC_CHER|= DACC_CHER_CH1;
	
	// check if DACC is ready to accept new conversion requests
	temp = (DACC->DACC_ISR>>0)&(0x0001);
	if (temp==0)//wait for DAC complete
	{
		while (1)
		{
			temp = (DACC->DACC_ISR>>0)&(0x0001);//DAC not complete
		}
	}
	
	// Set data to be converted
	DACC->DACC_CDR |= 0xFF/2; //Vref/2 
	
	// check EOC
	temp = (DACC->DACC_ISR>>0)&(0x0001);
	if (temp==0)//wait for DAC complete
	{
		while (1)
		{
			temp = (DACC->DACC_ISR>>0)&(0x0001);//DAC not complete
		}
	} 
	
	
}
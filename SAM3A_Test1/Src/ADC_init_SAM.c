/*
 * ADC_init_SAM.c
 *
 * Created: 2022/03/08 11:43:14
 *  Author: hanno
 */ 

#include "ADC_init_SAM.h"

void ADC_init(void)
{
	//Disable DAC Write Protect Mode Register
	ADC->ADC_WPMR =ADC_WPMR_WPKEY_PASSWD|~(ADC_WPMR_WPEN);
	//Enable Peripheral Clock
	PMC->PMC_PCER1 |= (PMC_PCER1_PID37);//enable clock for ADC
	// set sampling speed 100us
	ADC -> ADC_MR	&= ~(ADC_MR_PRESCAL_Msk);//reset
	ADC -> ADC_MR	|= ADC_MR_PRESCAL(3999);// set
	// enable AD channel 
	ADC -> ADC_CHDR &= ~(0xFF);//reset
	ADC -> ADC_CHER |= ADC_CHER_CH0;//set AD0
}
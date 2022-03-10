/*
 * ADC_SAM.c
 *
 * Created: 2022/03/08 14:11:46
 *  Author: hanno
 */ 

#include "ADC_init_SAM.h"


uint32_t ADC_READ(void)
{
	volatile uint32_t temp=0;
	// start ADC conversion
	ADC -> ADC_CR   |= ADC_CR_START;
	// check EOC
	/*temp = ADC->ADC_ISR;
	temp = (temp)&(0x1); This function doesn't work for some reason
	if (temp==0)//wait for ADC complete
	{
		while (1)
		{
			temp = (ADC->ADC_ISR>>0)&(0x0001);//ADC not complete
		}
	}*/
	while(temp<=6666)//manual wait ~1ms
	{
		temp =temp+1;
	}
	//return ADC value
	return ADC->ADC_CDR[0];
}
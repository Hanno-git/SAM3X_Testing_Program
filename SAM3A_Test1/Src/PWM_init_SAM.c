/*
 * PWM_init_SAM.c
 *
 * Created: 2022/03/07 12:24:18
 *  Author: hanno
 */ 

#include "PWM_init_SAM.h"
#include "main.h"

void PWM_init(void)
{
	//Disable PMC Write Protect Mode Register
	PMC->PMC_WPMR =PMC_WPMR_WPKEY_PASSWD|~(PMC_WPMR_WPEN);
	//Enable Peripheral Clock
	PMC->PMC_PCER0 |= (PMC_PCER1_PID36);//enable clock for PWM
	//select and divide PWM clock A and B
	PWM ->PWM_CLK = PWM_CLK_DIVA(1)|PWM_CLK_DIVB(1)|PWM_CLK_PREA(0b1010)|PWM_CLK_PREB(0b1010); //0b1010 -> MCK/1024
	//Enable channel 3
	PWM ->PWM_ENA &=~(PWM_ENA_CHID3);//reset
	PWM ->PWM_ENA |=(PWM_ENA_CHID3);//set
	// CHID SR
	// select adc mode synchronous etc
	PWM ->PWM_SCM = PWM_SCM_SYNC3|PWM_SCM_UPDM_MODE2|PWM_SCM_PTRCS(0);
	
	
}
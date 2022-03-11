/*
 * PWM_SAM.c
 *
 * Created: 2022/03/11 11:09:38
 *  Author: hanno
 */ 
#include "PWM_SAM.h"

void Set_Duty_Cycle(uint8_t Duty_Cycle, PWMx *PWM_sel)
{
	volatile uint32_t t ;
	if (Duty_Cycle>100)
	{
		Duty_Cycle=100;
	}
	t=PWM_sel->PWM_CPRDx&0xFFF;//grab channel PWM period
	t = (int)((long)Duty_Cycle*(long)t/100);//calculate Duty Cycle update value as ratio of channel period 
	PWM_sel->PWM_CDTYUPDx &= ~PWM_CDTYUPD_CDTYUPD_Msk;//reset
	PWM_sel->PWM_CDTYUPDx |= PWM_CDTYUPD_CDTYUPD(t);//set PWM
}

void Set_Duty_Cycle_Synchronous_Channels(uint8_t Duty_Cycle, PWMx *PWM_sel)
{
	volatile uint32_t t ;
	if (Duty_Cycle>100)
	{
		Duty_Cycle=100;
	}
	t=PWM0->PWM_CPRDx&0xFFF;//grab channel PWM period
	t = (int)((long)Duty_Cycle*(long)t/100);//calculate Duty Cycle update value as ratio of channel period
	PWM_sel->PWM_CDTYUPDx &= ~PWM_CDTYUPD_CDTYUPD_Msk;//reset
	PWM_sel->PWM_CDTYUPDx |= PWM_CDTYUPD_CDTYUPD(t);//set PWM
}
/*
 * TWI_init_SAM.c
 *
 * Created: 2022/03/07 15:20:46
 *  Author: hanno
 */ 
#include "TWI_init_SAM.h"

void TWI_init(void)
{
	//Disable PMC Write Protect Mode Register
	PMC->PMC_WPMR =PMC_WPMR_WPKEY_PASSWD|~(PMC_WPMR_WPEN);
	//Enable Peripheral Clock
	PMC->PMC_PCER0 |= (PMC_PCER0_PID22);//enable clock for TWI0
	//Set clock period L and H = 1.25e-6
	TWI0->TWI_CWGR = TWI_CWGR_CLDIV(0x30)|TWI_CWGR_CHDIV(0x30)|TWI_CWGR_CKDIV(0x1);
	//Disable Slave mode
	TWI0->TWI_CR |= TWI_CR_SVDIS;
	//Enable Master mode 
	TWI0->TWI_CR |=  TWI_CR_MSEN;
	
}


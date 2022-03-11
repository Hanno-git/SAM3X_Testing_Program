/*
 * PWM_init_SAM.c
 *
 * Created: 2022/03/07 12:24:18
 *  Author: hanno
 */ 

#include "PWM_init_SAM.h"
#include "main.h"
#include "PWM_SAM.h"

void PWM_init_a(void)//asynchronous mode
{
	//select and divide PWM clock A and B.PWM_SCUC UPDULOCK
	//PWM ->PWM_CLK = PWM_CLK_DIVA(4)|PWM_CLK_DIVB(4)|PWM_CLK_PREA(0b1010)|PWM_CLK_PREB(0b1010); //0b1010 -> MCK/1024
	
	//Disable PMC Write Protect Mode Register
	PMC->PMC_WPMR =PMC_WPMR_WPKEY_PASSWD|~(PMC_WPMR_WPEN);
	//Enable Peripheral Clock
	PMC->PMC_PCER1 |= (PMC_PCER1_PID36);//enable clock for PWM
	//Enable channel 3
	PWM->PWM_ENA |= PWM_ENA_CHID3;
	// select mode 
	PWM ->PWM_SCM &= ~PWM_SCM_UPDM_Msk;
	PWM ->PWM_SCM |= PWM_SCM_UPDM_MODE0;
	//PWM Output Override register
	PWM ->PWM_OOV |= PWM_OOV_OOVH3|PWM_OOV_OOVL3;//set
	
	//set frequency of PWM channel
	
	//(MCK_DIV_16)16*(PWM_CPRDUPD_CPRDUPD)0x1f4/(MCK)80e6 =10kHz 
	
	//PWM Channel Period Update Register
	PWM3->PWM_CPRDUPDx |= PWM_CPRDUPD_CPRDUPD(0x1f4);//*(uint32_t *)0x40094270
	//PWM Channel Prescaler
	PWM3->PWM_CMRx  &= ~PWM_CMR_CPRE_Msk;//*(uint32_t *)0x40094260
	PWM3->PWM_CMRx |= PWM_CMR_CPRE_MCK_DIV_16;
	
	//PWM Channel Dead Time Update Register CPRD-CDTY
	PWM3->PWM_DTUPDx= PWM_DTUPD_DTHUPD(0xF)|PWM_DTUPD_DTLUPD(0xF);//*(uint32_t *)0x4009427C
	// Dead Time Generator Enable
	PWM3->PWM_CMRx |= PWM_CMR_DTE; //*(uint32_t *)0x40094260
	//Invert Low signal
	//PWM3->PWM_CMRx |= PWM_CMR_DTLI;
	Set_Duty_Cycle(10,PWM3);
	
	}

void PWM_init_FAULT(void)
{
	PWM->PWM_FMR &= ~PWM_FMR_FPOL(0b1<<1);
	//PWM->PWM_FPE1 |= PWM_FPE1_FPE3(0b1<<1);//enable fault protection for channel 3
	PWM->PWM_FPE1 |= PWM_FPE1_FPE0(0b1<<1);//enable fault protection for channel 0
	//update synchronous channels
	//PWM ->PWM_SCUC |=PWM_SCUC_UPDULOCK;
}
	
void PWM_init(void)//synchronous mode
{
	//select and divide PWM clock A and B.PWM_SCUC UPDULOCK
	//PWM ->PWM_CLK = PWM_CLK_DIVA(4)|PWM_CLK_DIVB(4)|PWM_CLK_PREA(0b1010)|PWM_CLK_PREB(0b1010); //0b1010 -> MCK/1024
	
	//Disable PMC Write Protect Mode Register
	PMC->PMC_WPMR =PMC_WPMR_WPKEY_PASSWD|~(PMC_WPMR_WPEN);
	//Enable Peripheral Clock
	PMC->PMC_PCER1 |= (PMC_PCER1_PID36);//enable clock for PWM
	
	// select mode
	PWM ->PWM_SCM &= ~PWM_SCM_UPDM_Msk;
	PWM ->PWM_SCM |= PWM_SCM_UPDM_MODE0;
	//set channels as synchronous channels
	PWM->PWM_SCM |= PWM_SCM_SYNC1;
	PWM->PWM_SCM |= PWM_SCM_SYNC2;
	PWM->PWM_SCM |= PWM_SCM_SYNC3;
	
	//Enable channel 0
	PWM->PWM_ENA |= PWM_ENA_CHID0;
	//Enable channel 1
	PWM->PWM_ENA |= PWM_ENA_CHID1;
	//Enable channel 2
	PWM->PWM_ENA |= PWM_ENA_CHID2;
	//Enable channel 3
	PWM->PWM_ENA |= PWM_ENA_CHID3;
	
	// Universal Sync settings start------------------------------------------
	//set frequency of PWM channel
	/*
	(MCK_DIV_16)16*(PWM_CPRDUPD_CPRDUPD)0x1f4/(MCK)80e6 =10kHz 
	*/
	//PWM Channel Period Update Register
	PWM0->PWM_CPRDUPDx |= PWM_CPRDUPD_CPRDUPD(0x1f4);//*(uint32_t *)0x40094270
	//PWM Channel Prescaler
	PWM0->PWM_CMRx  &= ~PWM_CMR_CPRE_Msk;//*(uint32_t *)0x40094260
	PWM0->PWM_CMRx |= PWM_CMR_CPRE_MCK_DIV_16;
	
	//Channel Alignment
	PWM0->PWM_CMRx |= PWM_CMR_CALG;
	// Universal Sync settings stop-------------------------------------------
	
	//PWM Channel Dead Time Update Register CPRD-CDTY
	PWM3->PWM_DTUPDx= PWM_DTUPD_DTHUPD(0xF)|PWM_DTUPD_DTLUPD(0xF);//*(uint32_t *)0x4009427C
	// Dead Time Generator Enable
	PWM3->PWM_CMRx |= PWM_CMR_DTE; //*(uint32_t *)0x40094260
	//Invert Low signal
	//PWM3->PWM_CMRx |= PWM_CMR_DTLI;

	//PWM Channel Dead Time Update Register CPRD-CDTY
	PWM0->PWM_DTUPDx= PWM_DTUPD_DTHUPD(0xF)|PWM_DTUPD_DTLUPD(0xF);//*(uint32_t *)0x4009427C
	// Dead Time Generator Enable
	PWM0->PWM_CMRx |= PWM_CMR_DTE; //*(uint32_t *)0x40094260
	
	//update synchronous channels
	PWM ->PWM_SCUC |=PWM_SCUC_UPDULOCK;
	
	Set_Duty_Cycle_Synchronous_Channels(10,PWM0);
	Set_Duty_Cycle_Synchronous_Channels(10,PWM3);
	//update synchronous channels
	PWM ->PWM_SCUC |=PWM_SCUC_UPDULOCK;
	PWM_init_FAULT();
	}
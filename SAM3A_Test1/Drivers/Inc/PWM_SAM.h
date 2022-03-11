/*
 * PWM_SAM.h
 *
 * Created: 2022/03/11 11:10:18
 *  Author: hanno
 */ 


#ifndef PWM_SAM_H_
#define PWM_SAM_H_


#include "main.h"

typedef struct {
	__IO	uint32_t PWM_CMRx;      
	__IO	uint32_t PWM_CDTYx;       
	__O		uint32_t  PWM_CDTYUPDx;       
	__IO	uint32_t PWM_CPRDx;
	__O		uint32_t PWM_CPRDUPDx;      
	__I		uint32_t PWM_CCNTx;       
	__IO	uint32_t PWM_DTx;
	__O		uint32_t PWM_DTUPDx;
	
} PWMx;

#define PWM0       ((PWMx    *)0x40094200) /**< \brief (PWM_CMR0      ) Base Address */
#define PWM1       ((PWMx    *)0x40094220) 
#define PWM2       ((PWMx    *)0x40094240) 
#define PWM3       ((PWMx    *)0x40094260) 
#define PWM4       ((PWMx    *)0x40094280) 
#define PWM5       ((PWMx    *)0x400942A0) 
#define PWM6       ((PWMx    *)0x400942C0) 
#define PWM7       ((PWMx    *)0x400942E0) 

void Set_Duty_Cycle(uint8_t Duty_Cycle, PWMx *PWM_sel);
void Set_Duty_Cycle_Synchronous_Channels(uint8_t Duty_Cycle, PWMx *PWM_sel);
void Set_Frequency(uint32_t Frequency, PWMx *PWM_sel);

#endif /* PWM_SAM_H_ */
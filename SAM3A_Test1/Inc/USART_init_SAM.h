/*
 * USART_init_SAM.h
 *
 * Created: 2022/03/07 10:54:09
 *  Author: hanno
 */ 


#ifndef USART_INIT_SAM_H_
#define USART_INIT_SAM_H_

#include "main.h"

#define USART0_SERIAL                 USART0
#define USART0_SERIAL_ID              ID_USART0  
#define USART0_SERIAL_ISR_HANDLER     USART0_Handler
#define USART0_SERIAL_BAUDRATE        115200
#define USART0_SERIAL_CHAR_LENGTH     US_MR_CHRL_8_BIT
#define USART0_SERIAL_PARITY          US_MR_PAR_NO
#define USART0_SERIAL_STOP_BIT        US_MR_NBSTOP_1_BIT


void USART0_init(void);



#endif /* USART_INIT_SAM_H_ */
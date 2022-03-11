/*
 * USART_init.c
 *
 * Created: 2022/03/07 10:53:36
 *  Author: hanno
 */ 

#include "USART_init_SAM.h"

void USART0_init(void)//w
{
	volatile uint32_t t1;
	//clear write protect
	USART0->US_WPMR =US_WPMR_WPKEY_PASSWD|~(PMC_WPMR_WPEN);
	//select MCK as clock
	USART0->US_MR &= ~(US_MR_USCLKS_Msk);//reset
	USART0->US_MR |= (US_MR_USCLKS_MCK);//set
	//set usart to normal mode
	USART0->US_MR &=~(US_MR_USART_MODE_Msk);
	USART0->US_MR |=US_MR_USART_MODE_NORMAL;
	//set character length to 8 bits
	USART0->US_MR &=~(US_MR_CHRL_Msk);
	USART0->US_MR |=US_MR_CHRL_8_BIT;
	//set parity type to no parity
	USART0->US_MR &=~(US_MR_PAR_Msk);
	USART0->US_MR |=US_MR_PAR_NO;
	//set baud rate
	USART0->US_BRGR &=~(US_BRGR_CD_Msk);
	USART0->US_BRGR |=0x2B;//115200
	t1= USART0->US_BRGR ;
	//enable transmit and receive
	USART0->US_CR |=US_CR_RSTRX;//reset receive
	USART0->US_CR &=~US_CR_RSTRX;
	USART0->US_CR &=~US_CR_RXDIS;//reset disable
	USART0->US_CR |=US_CR_RXEN;//enable receive
	USART0->US_CR |=US_CR_RSTTX;//reset transmit
	USART0->US_CR &=~US_CR_RSTTX;
	USART0->US_CR &=~US_CR_TXDIS;//reset disable
	USART0->US_CR |=US_CR_TXEN;//enable transmit
	

}




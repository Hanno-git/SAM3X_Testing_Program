/*
 * USART_SAM.c
 *
 * Created: 2022/03/08 14:16:09
 *  Author: hanno
 */ 
#include "USART_SAM.h"

void transmitByte(uint8_t data){
	volatile uint32_t t1;
	//wait for ready
	t1 = (USART0->US_CSR>>1)&0x1;
	while ((~t1)&0x1){
		t1 = (USART0->US_CSR>>1)&0x1;}//#SR	
	t1 = (USART0->US_CSR>>9)&0x1;
	while (!( UART_SR_TXEMPTY)){
	t1 = (USART0->US_CSR>>9)&0x1;
	};
	
	//load data to be transmitted
	USART0->US_THR |= data;
}

void USART_Transfer(const char myString[]) {//w
	uint8_t i = 0;
	while (myString[i]) {
		transmitByte(myString[i]);
		i++;
	}
}
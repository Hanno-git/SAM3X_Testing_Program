/*
 * pio_init.h 
 *
 * Created: 2022/03/01 16:24:14
 *  Author: hanno
 */ 


#ifndef pio_init_H_
#define pio_init_H_

#include "main.h"
#define PIO_control  0
#define Peripheral_B 2
#define Peripheral_A 1
#define Alternate_function 3
#define Input		 1
#define Output		 0 

#define RED_PB26_PORT	PIOB//adjusted for 3x
#define RED_PB27_PIN	27//

#define GREEN_PA15_PORT	PIOA//defined as input for testing
#define GREEN_PA15_PIN	15

#define RDX0_PA10_PORT	PIOA
#define RDX0_PA10_PIN	10
#define TXD0_PA11_PORT	PIOA
#define TXD0_PA11_PIN	11

#define PWMH3_PB15_PIN	15
#define PWMH3_PB15_PORT PIOB //per B
#define PWML3_PA0_PIN	0
#define PWML3_PA0_PORT	PIOA //per B

#define PWMH0_PB12_PIN	12
#define PWMH0_PB12_PORT	PIOB //per B

#define PWMFI1_PA3_PIN	5
#define PWMFI1_PA3_PORT	PIOA //per B

#define TWD0_SCL_PA18_PIN		18//same 3x & 3a
#define TWD0_SCL_PA18_PORT		PIOA //per A
#define TWD0_SDA_PA17_PIN		17
#define TWD0_SDA_PA17_PORT		PIOA //per A

#define SPI0_SPCK_PA27_PIN		27
#define SPI0_MOSI_PA26_PIN		26
#define SPI0_MISO_PA25_PIN		25
#define SPI0_SPCK_PA27_PORT		PIOA
#define SPI0_MOSI_PA26_PORT		PIOA
#define SPI0_MISO_PA25_PORT		PIOA

#define REF1V65_AD0_PA2_PIN		2
#define REF1V65_AD0_PA2_PORT	PIOA

#define DAC1_PB16_PIN			16			
#define DAC1_PB16_PORT			PIOB 

void PIO_INIT(void);



#endif /* INCFILE1_H_ */
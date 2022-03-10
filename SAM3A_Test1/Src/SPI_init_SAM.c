/*
 * SPI_init_SAM.c
 *
 * Created: 2022/03/08 07:53:15
 *  Author: hanno
 */ 

#include "SPI_init_SAM.h"

void SPI_init(void)
{
	//Enable Peripheral Clock
	PMC->PMC_PCER0 |= (PMC_PCER0_PID24);//enable clock for SPI0
	//SCBR: Serial Clock Baud Rate
	SPI0->SPI_CSR[1] &= ~(SPI_CSR_SCBR_Msk);
	SPI0->SPI_CSR[1] |= SPI_CSR_SCBR(16);
	//SPI is in Master mode
	SPI0->SPI_MR |= SPI_MR_MSTR;
	//The Peripheral Chip Select does not rise after the last transfer is achieved
	//It remains active until a new transfer is requested on a different chip select.
	SPI0->SPI_CSR[1] |= SPI_CSR_CSAAT;
	//Fixed Peripheral Select.
	SPI0->SPI_MR &= ~SPI_MR_PS;
	//Delay Between Chip Selects
	SPI0->SPI_MR |= SPI_MR_PCS_Msk;//reset
	SPI0->SPI_MR &= ~SPI_MR_DLYBCS_Msk;//reset
	SPI0->SPI_MR |= SPI_MR_DLYBCS(6);//set delay
	//Peripheral Chip Select
	SPI0->SPI_MR &= ~SPI_MR_PCS_Msk;//reset
	SPI0->SPI_MR |= SPI_MR_PCS(0b1101);//select
	
	
	
	
}

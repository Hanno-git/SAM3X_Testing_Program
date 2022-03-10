/*
 * RTC_init_ISL12022M.c
 *
 * Created: 2022/03/09 12:10:51
 *  Author: hanno
 */ 
#include "RTC_init_ISL12022M.h"

void RTC_init(void)
{
	I2C_WRITE_RTC(0x0D,0b10000000);//enables Temperature Sensing and Correction
}
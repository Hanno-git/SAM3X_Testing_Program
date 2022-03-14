/*
 * TWI_SAM.h
 * Driver for the ISL12022M RTC
 * Created: 2022/03/08 14:22:52
 *  Author: hanno
 */ 


#ifndef TWI_SAM_H_
#define TWI_SAM_H_

#include "main.h"
#include "pio_init.h"
 
void I2C_WRITE_RTC_multiple(Twi *I2C, uint32_t Add_Byte, uint8_t *w_Byte, uint32_t w_len);
void I2C_WRITE_RTC_single(Twi *I2C, uint32_t Add_Byte, uint8_t w_Byte);
void I2C_READ_RTC_multiple(Twi *I2C, uint32_t Add_Byte, uint8_t *read_lst, uint8_t read_len);
uint8_t I2C_READ_RTC_single(Twi *I2C, uint32_t Add_Byte);


#endif /* TWI_SAM_H_ */
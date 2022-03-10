/*
 * RTC_ISL.h
 *
 * Created: 2022/03/09 08:54:40
 *  Author: hanno
 */ 


#ifndef RTC_ISL_H_
#define RTC_ISL_H_

#include "main.h"
#include "TWI_SAM.h"

struct time_RTC{ 
	uint8_t sec;//1-60
	uint8_t min;//1-60
	uint8_t hour;//0-24
	uint8_t pm;// 1/0
	uint8_t t24_mode;// 1/0
	uint8_t date;//1-31
	uint8_t month_int;//1-12
	uint16_t year;//2000-2099
	uint8_t Day_of_Week_int;//1-7
};

void Get_Time(struct time_RTC *time);
void int_to_str(uint8_t input_int,char *input_str,uint8_t char_leng);
void int_DW_to_str_DW(uint8_t DW_int,char *p_DW_str);
void int_month_to_str_month(uint8_t month_int,char *p_month_str);
void Set_Time(struct time_RTC *time);

#endif /* RTC_ISL_H_ */
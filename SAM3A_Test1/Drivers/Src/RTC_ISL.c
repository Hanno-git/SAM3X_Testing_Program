/*
 * RTC_ISL.c
 *
 * Created: 2022/03/09 08:54:25
 *  Author: hanno
 */ 

#include "RTC_ISL.h"

void swap_date(char *p_m,char *p_n_m)
{
	uint8_t i;
	for (i = 0; i < 9; ++i)
	{
		*(p_m+i)= *(p_n_m+i);
	}
	
}

void int_month_to_str_month(uint8_t month_int,char *p_month_str)//p_month_str-> where to store char ex. input:1->output:January
{
	char m0[9] = "Error    ";
	char m1[9] = "January  ";
	char m2[9] = "February ";
	char m3[9] = "March    ";
	char m4[9] = "April    ";
	char m5[9] = "May      ";
	char m6[9] = "June     ";
	char m7[9] = "July     ";
	char m8[9] = "August   ";
	char m9[9] = "September";
	char m10[9]= "October  ";
	char m11[9]= "November ";
	char m12[9]= "December ";

	switch(month_int)
	{
		case 1:
			swap_date(p_month_str,m1);
			break;
		case 2:
			swap_date(p_month_str,m2);
			break;
		case 3:
			swap_date(p_month_str,m3);
			break;
		case 4:
			swap_date(p_month_str,m4);
			break;
		case 5:
			swap_date(p_month_str,m5);
			break;
		case 6:
			swap_date(p_month_str,m6);
			break;
		case 7:
			swap_date(p_month_str,m7);
			break;
		case 8:
			swap_date(p_month_str,m8);
			break;
		case 9:
			swap_date(p_month_str,m9);
			break;
		case 10:
			swap_date(p_month_str,m10);
			break;
		case 11:
			swap_date(p_month_str,m11);
			break;
		case 12:
			swap_date(p_month_str,m12);
			break;
		default:
			swap_date(p_month_str,m0);
			// month doesn't match any case
	}
}

void int_DW_to_str_DW(uint8_t DW_int,char *p_DW_str)//p_DW_str-> where to store string ex input:1->output:Monday
{
	char m0[9] = "Error    ";
	char m1[9] = "Monday   ";
	char m2[9] = "Tuesday  ";
	char m3[9] = "Wednesday";
	char m4[9] = "Thursday ";
	char m5[9] = "Friday   ";
	char m6[9] = "Saturday ";
	char m7[9] = "Sunday   ";


	switch(DW_int)
	{
		case 1:
		swap_date(p_DW_str,m1);
		break;
		case 2:
		swap_date(p_DW_str,m2);
		break;
		case 3:
		swap_date(p_DW_str,m3);
		break;
		case 4:
		swap_date(p_DW_str,m4);
		break;
		case 5:
		swap_date(p_DW_str,m5);
		break;
		case 6:
		swap_date(p_DW_str,m6);
		break;
		case 7:
		swap_date(p_DW_str,m7);
		break;
		default:
		swap_date(p_DW_str,m0);
		// month doesn't match any case
	}
}

void int_to_str(uint8_t input_int,char *input_str,uint8_t char_leng)
{
	uint8_t i,i_rightmost,i_t;
	i_t = input_int;
	
	for (i = 0; i < char_leng; ++i)
	{
		i_rightmost = i_t%10;//grabs right most digit
		i_t = i_t/10;//removes right most digit
		*(input_str+char_leng-1-i) = 48+i_rightmost; //converts from int to ascii and saves to year string char
	}
	return;
}
/*
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
};*/


void Get_Time(struct time_RTC *time)
{
	uint8_t SC = 0,MN= 0,HR= 0,DT= 0,MO= 0,YR= 0,DW= 0,t;
	//read data from RTC
	SC = I2C_READ_RTC(0x00);
	MN = I2C_READ_RTC(0x01);
	HR = I2C_READ_RTC(0x02);
	DT = I2C_READ_RTC(0x03);
	MO = I2C_READ_RTC(0x04);
	YR = I2C_READ_RTC(0x05);
	DW = I2C_READ_RTC(0x06);
	//
	time->sec = SC;//grabs sec
	time->min = MN;//grabs min
	t = HR&0b10000000>>7;//check if 24 hour mode
	if (t)
	{
		time->hour = HR&0b00111111;//grabs hour
		time->t24_mode = 1;
	}
	else
	{
		time->hour = HR&0b00001111;//grabs hour
		time->pm   = HR&0b00100000>>5;//grabs am/pm
		time->t24_mode = 0;
	}
	
	time->date = DT;//grabs day of month
	time->month_int =MO;//grabs month
	//int_month_to_str_month(MO,ct);//converts int to str def
	
	time->year = YR;//grabs year
	time->Day_of_Week_int = DW;//grabs day of week
	//int_DW_to_str_DW(DW,ct);//converts int to str def
}

void Set_Time(struct time_RTC *time)
{
	uint8_t SC = 0,MN= 0,HR= 0,DT= 0,MO= 0,YR= 0,DW= 0,t,t2;
	//read data from RTC
	SC = time->sec;
	MN = time->min;
	//
	t = time->t24_mode;//check if 24 hour mode
	if (t)
	{
		HR = (time->hour&0b00111111)|0b10000000;//sets hour
		time->t24_mode = 1;
	}
	else
	{
		t2 = time->pm;//checks if pm or am
		if (t2)
		{
			HR = (time->hour&0b00001111)|0b00100000;//sets hour
		}
		else
		{
			HR = time->hour&0b00001111;//sets hour
		}
	}
	
	DT=time->date;//sets day of month
	MO= time->month_int;//sets month
	YR = time->year;//sets year
	DW = time->Day_of_Week_int;//sets day of week
	I2C_WRITE_RTC(0x00,SC);
	I2C_WRITE_RTC(0x01,MN);
	I2C_WRITE_RTC(0x02,HR);
	I2C_WRITE_RTC(0x03,DT);
	I2C_WRITE_RTC(0x04,MO);
	I2C_WRITE_RTC(0x05,YR);
	I2C_WRITE_RTC(0x06,DW);
}
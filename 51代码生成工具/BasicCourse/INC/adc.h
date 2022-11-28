#ifndef ADC_H
#define ADC_H
#include "STC51.h"
//注意独立按键和矩阵按键也用了，注意资源冲突
sbit ADWR_GPIO=P3^6;
sbit ADRD_GPIO=P3^7;
sbit AD_U1=P2^6;//段选
sbit AD_U2=P2^7;//位选
typedef struct my_adc
{
	 uint8 adc_val;
	 uint8 adc_flag;
	 uint8 adc_time_i;
	 uint8 (*read_adc_value)(void);
	 void (*begin_adc_change)(void);
	
}create_adc;
void adc_init(create_adc*adc_object);
#endif 

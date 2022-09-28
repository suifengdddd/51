#ifndef ADC_H
#define ADC_H
#include "STC51.h"
//注意独立按键和矩阵按键也用了，注意资源冲突
sbit ADWR_GPIO=P3^6;
sbit ADRD_GPIO=P3^7;
typedef struct my_adc
{
	 uint8 adc_val;
	 uint8 (*read_adc_value)(void);
	
}create_adc;
void adc_init(create_adc*adc_object);
#endif 

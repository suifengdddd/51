#ifndef ADC_H
#define ADC_H
#include "STC51.h"
//ע����������;��󰴼�Ҳ���ˣ�ע����Դ��ͻ
sbit ADWR_GPIO=P3^6;
sbit ADRD_GPIO=P3^7;
typedef struct my_adc
{
	 uint8 adc_val;
	 uint8 (*read_adc_value)(void);
	
}create_adc;
void adc_init(create_adc*adc_object);
#endif 

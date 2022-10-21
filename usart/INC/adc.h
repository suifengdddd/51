#ifndef ADC_H
#define ADC_H
#include "STC51.h"
//ע����������;��󰴼�Ҳ���ˣ�ע����Դ��ͻ
sbit ADWR_GPIO=P3^6;
sbit ADRD_GPIO=P3^7;
sbit AD_U1=P2^6;//��ѡ
sbit AD_U2=P2^7;//λѡ
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

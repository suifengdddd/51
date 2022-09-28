#include "adc.h"
static uint8 read_adc_value(void);
void adc_init(create_adc*adc_object)
{
	adc_object->read_adc_value=read_adc_value;
	adc_object->adc_val=0;
	U2=1;
	P0=0x7f;
	U2=0;
}
static uint8 read_adc_value(void)
{
	 uint8 val=0;
	 ADWR_GPIO=1;
	 _nop_();
	 ADWR_GPIO=0;
	_nop_();
	ADWR_GPIO=1;
	delayms(150);
	P1=0xff;
	ADRD_GPIO=1;
	_nop_();
	ADRD_GPIO=0;
	_nop_();
	val=P1;
	ADRD_GPIO=1;
	return val;
}
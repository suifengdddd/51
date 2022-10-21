#include "adc.h"
static uint8 read_adc_value(void);
static void begin_adc_change(void);
void adc_init(create_adc*adc_object)
{
	adc_object->read_adc_value=read_adc_value;
	adc_object->begin_adc_change=begin_adc_change;
	adc_object->adc_val=0;
	adc_object->adc_flag=0;
	adc_object->adc_time_i=0;
	AD_U2=1;
	P0=0x7f;
	AD_U2=0;
}
static void begin_adc_change(void)
{
		
    AD_U2=1;
    P0=0;                       //选通ADCS ,AD写入（随便写个什么都行，主要是为了启动AD转换）
    ADWR_GPIO=0;			        
    _nop_();
    ADWR_GPIO=1;
    P0=0xff;                    //关闭ADCS
    ad_delay(10);
    AD_U2=0;    
	
		
}
static uint8 read_adc_value(void)
{
	uint8 ret=0;
	AD_U2=1;                   //重新打开有AD片选信号锁存器的锁存端
  P1=0xff;                  //读取P1口之前先给其写全1
  P0=0x7f;                  //选通ADCS (锁存器的bit7位为0)
  ADRD_GPIO=0;              //AD读使能
	ad_delay(1);              //注意读的时候尽量延时稍微长一点，_nop_不够
  ret=P1;					          //AD数据读取赋给P1口
  ADRD_GPIO=1;
  P0=0xff;                  //关闭ADCS
  ADWR_GPIO=0;
  P1=~ret;                  //让LED显示ADC值

  return ret;
}
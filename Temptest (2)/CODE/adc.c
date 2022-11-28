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
    P0=0;                       //ѡͨADCS ,ADд�루���д��ʲô���У���Ҫ��Ϊ������ADת����
    ADWR_GPIO=0;			        
    _nop_();
    ADWR_GPIO=1;
    P0=0xff;                    //�ر�ADCS
    ad_delay(10);
    AD_U2=0;    
	
		
}
static uint8 read_adc_value(void)
{
	uint8 ret=0;
	AD_U2=1;                   //���´���ADƬѡ�ź��������������
  P1=0xff;                  //��ȡP1��֮ǰ�ȸ���дȫ1
  P0=0x7f;                  //ѡͨADCS (��������bit7λΪ0)
  ADRD_GPIO=0;              //AD��ʹ��
	ad_delay(1);              //ע�����ʱ������ʱ��΢��һ�㣬_nop_����
  ret=P1;					          //AD���ݶ�ȡ����P1��
  ADRD_GPIO=1;
  P0=0xff;                  //�ر�ADCS
  ADWR_GPIO=0;
  P1=~ret;                  //��LED��ʾADCֵ

  return ret;
}
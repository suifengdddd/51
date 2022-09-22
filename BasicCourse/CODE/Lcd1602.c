#include "Lcd1602.h"
#if LCD1602_
static void write_com(uint8 com);
static void write_data(uint8 data_);
static void show_data(uint8 *lcd_data,uint8 location)reentrant;
/**
  * @brief          LCD1602��ʼ����
  * @param[in]      lcd_object��LCD1602����ָ��
  * @retval         NULL
  */
void lcd1602_init(create_lcd *lcd_object)
{
	lcd_object->write_com=write_com;
	lcd_object->show_data=show_data;
	lcden=0;
	U1=0;
	U2=0;
	write_com(0x38);
	write_com(0x0c);
	write_com(0x06);
	write_com(0x01);
	
}
	/**
  * @brief          LCD1602�����������
  * @param[in]      com��LCD1602����
  * @retval         NULL
  */
static void write_com(uint8 com)
{
	lcdrs=0;
	P0=com;
	delay(5);
	lcden=1;
	delay(5);
	lcden=0;
}
static void write_data(uint8 data_)
{
	lcdrs=1;
	P0=data_;
	delay(5);
	lcden=1;
	delay(5);
	lcden=0;
}
	/**
  * @brief          LCD1602��ʾ���ݺ���
  * @param[in]      com��*lcd_dataҪ��ʾ������ָ�루���Դ����������֣�Ҳ�������ַ�����
	*                 location ��ʾλ��
  * @retval         NULL
  */
static void show_data(uint8 *lcd_data,uint8 location)reentrant
{
	  int count=0;
	  int i=0;
	  uint8 * temp=lcd_data;

	   while(*temp)
		 {
			 count++;
			 temp++;
		 }
		 write_com(location);
		 for(i=0;i<count;i++)
		{
			 write_data(lcd_data[i]);
			 delay(5);
		}
}
#endif
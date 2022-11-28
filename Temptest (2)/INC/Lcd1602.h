#ifndef LCD1602_H
#define LCD1602_H
#include "STC51.h"
#if LCD1602_
#if SMG_==0
sbit U1=P2^6;//��ѡ
sbit U2=P2^7;//λѡ
#endif
#if _C51==1
sbit lcden=P3^4;
sbit lcdrs=P3^5;
#else
sbit lcden=P2^7;
sbit lcdrs=P2^6;
#endif

typedef struct my_lcd1602
{
	/**
  * @brief          LCD1602�����������
  * @param[in]      com��LCD1602����
  * @retval         NULL
  */
  void (*write_com)(uint8 com);
	/**
  * @brief          LCD1602��ʾ���ݺ���
  * @param[in]      com��*lcd_dataҪ��ʾ������ָ�루���Դ����������֣�Ҳ����ר���ַ�����
	*                 location ��ʾλ��
  * @retval         NULL
  */
	void (*show_data)(uint8 *lcd_data,uint8 location)reentrant;
}create_lcd;	

	/**
  * @brief          LCD1602��ʼ����
  * @param[in]      lcd_object��LCD1602����ָ��
  * @retval         NULL
  */
void lcd1602_init(create_lcd *lcd_object);
#endif
#endif

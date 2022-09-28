#ifndef LCD1602_H
#define LCD1602_H
#include "STC51.h"
#if LCD1602_
#if SMG_==0
sbit U1=P2^6;//段选
sbit U2=P2^7;//位选
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
  * @brief          LCD1602命令操作函数
  * @param[in]      com：LCD1602命令
  * @retval         NULL
  */
  void (*write_com)(uint8 com);
	/**
  * @brief          LCD1602显示数据函数
  * @param[in]      com：*lcd_data要显示的数据指针（可以传入数组名字，也可以专是字符串）
	*                 location 显示位置
  * @retval         NULL
  */
	void (*show_data)(uint8 *lcd_data,uint8 location)reentrant;
}create_lcd;	

	/**
  * @brief          LCD1602初始函数
  * @param[in]      lcd_object：LCD1602对象指针
  * @retval         NULL
  */
void lcd1602_init(create_lcd *lcd_object);
#endif
#endif

#ifndef LED_H
#define LED_H
#include "STC51.h"
#if LED_
#if _C51==1
sbit GPIO_1_0=P1^0;
sbit GPIO_1_1=P1^1;
sbit GPIO_1_2=P1^2;
sbit GPIO_1_3=P1^3;
sbit GPIO_1_4=P1^4;
sbit GPIO_1_5=P1^5;
sbit GPIO_1_6=P1^6;
sbit GPIO_1_7=P1^7;
#else
sbit GPIO_1_0=P2^0;
sbit GPIO_1_1=P2^1;
sbit GPIO_1_2=P2^2;
sbit GPIO_1_3=P2^3;
sbit GPIO_1_4=P2^4;
sbit GPIO_1_5=P2^5;
sbit GPIO_1_6=P2^6;
sbit GPIO_1_7=P2^7;
#endif
#define LED1  1
#define LED2  2
#define LED3  3
#define LED4  4
#define LED5  5
#define LED6  6
#define LED7  7
#define LED8  8
#define OFF   0
typedef struct my_led
{
	 /**
  * @brief          点亮led
  * @param[in]      number：要点亮的led
  * @retval         NULL
  */
	 void (*led_on)(int number);
	
	
	 /**
   * @brief          关闭led
   * @param[in]      number：要关闭的led
   * @retval         NULL
  */
	 void (*led_off)(int number);
	
	
	
	/**
  * @brief          让led闪烁
  * @param[in]      number：         要闪烁的led
  *                 interval_time:   闪烁时间间隔 
  *                 time:            闪烁总时间
  *                 注意不要在定时器中断函数内使用
	*                 和定时器使用时请设置定时器中断时间在50ms不然此函数无法执行
  * @retval         NULL
  */
	 void  (*led_flicker)(int number,int interval_time,int time)reentrant;
	 
	 
/**
  * @brief          让多个led闪烁
  * @param[in]      arr：            要闪烁的led数组（1-8）
  *                 interval_time:   闪烁时间间隔 
  *                 time:            闪烁总时间
	*                 注意不要在定时器中断函数内使用
	*                 和定时器使用时请设置定时器中断时间在50ms不然此函数无法执行
  * @retval         NULL
  */
	 void  (*leds_flicker)(int *arr,int interval_time,int time)reentrant;
	 /*
	  *让1-4闪烁，4-8灭
	  *int arr[8]={LED1,LED2,LED3,LED4,OFF,OFF,OFF,OFF}
		*c51_led.leds_flicker(arr,100,500);
		*
	  *
	 */
	 
	 /**
  * @brief          关闭所有led
  * @param[in]      NULL
  * @retval         NULL
  */
	 void  (*led_all_off)(void);	
	 
}create_led;

/**
  * @brief          初始化led对象
  * @param[in]      led_object：led对象指针
  * @retval         NULL
  */
void led_init(create_led * led_object);
extern create_led c51_led;

#endif
#endif

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
  * @brief          ����led
  * @param[in]      number��Ҫ������led
  * @retval         NULL
  */
	 void (*led_on)(int number);
	
	
	 /**
   * @brief          �ر�led
   * @param[in]      number��Ҫ�رյ�led
   * @retval         NULL
  */
	 void (*led_off)(int number);
	
	
	
	/**
  * @brief          ��led��˸
  * @param[in]      number��         Ҫ��˸��led
  *                 interval_time:   ��˸ʱ���� 
  *                 time:            ��˸��ʱ��
  *                 ע�ⲻҪ�ڶ�ʱ���жϺ�����ʹ��
	*                 �Ͷ�ʱ��ʹ��ʱ�����ö�ʱ���ж�ʱ����50ms��Ȼ�˺����޷�ִ��
  * @retval         NULL
  */
	 void  (*led_flicker)(int number,int interval_time,int time)reentrant;
	 
	 
/**
  * @brief          �ö��led��˸
  * @param[in]      arr��            Ҫ��˸��led���飨1-8��
  *                 interval_time:   ��˸ʱ���� 
  *                 time:            ��˸��ʱ��
	*                 ע�ⲻҪ�ڶ�ʱ���жϺ�����ʹ��
	*                 �Ͷ�ʱ��ʹ��ʱ�����ö�ʱ���ж�ʱ����50ms��Ȼ�˺����޷�ִ��
  * @retval         NULL
  */
	 void  (*leds_flicker)(int *arr,int interval_time,int time)reentrant;
	 /*
	  *��1-4��˸��4-8��
	  *int arr[8]={LED1,LED2,LED3,LED4,OFF,OFF,OFF,OFF}
		*c51_led.leds_flicker(arr,100,500);
		*
	  *
	 */
	 
	 /**
  * @brief          �ر�����led
  * @param[in]      NULL
  * @retval         NULL
  */
	 void  (*led_all_off)(void);	
	 
}create_led;

/**
  * @brief          ��ʼ��led����
  * @param[in]      led_object��led����ָ��
  * @retval         NULL
  */
void led_init(create_led * led_object);
extern create_led c51_led;

#endif
#endif

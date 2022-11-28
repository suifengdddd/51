#ifndef KEY_H
#define KEY_H
#include "STC51.h"
#if KEY_
#if _C51==1
#define GPIO_KEY  P3
sbit GPIO_KEY2=P3^4;
sbit GPIO_KEY3=P3^5;
sbit GPIO_KEY4=P3^6;
sbit GPIO_KEY5=P3^7;
enum _key
{
	KEY2=2,
	KEY3,
	KEY4,
	KEY5,
};
#else
enum _key
{
	KEY2=1,
	KEY3,
	KEY4,
	KEY5,
};
#define GPIO_KEY  P1
sbit GPIO_KEY2=P3^1;
sbit GPIO_KEY3=P3^0;
sbit GPIO_KEY4=P3^2;
sbit GPIO_KEY5=P3^3;
#endif
typedef struct my_key
{
	
/**
  * @brief          判断那个按键被按下
  * @param[in]      NULL
  * @retval         按键标号(2-21)
  */
	  int (*whitch_key_down)(void);
	  unsigned char key_val;
	  
}create_key;
/**
  * @brief          初始化key对象
  * @param[in]      key_object：key对象指针
  * @retval         NULL
  */
void key_init(create_key *key_object);
extern create_key c51_key; 
#endif
#endif

#ifndef BEEP_H
#define BEEP_H
#include "STC51.h"
#if BEEP_
#if _C51==1
sbit BEEP_GPIO=P2^3;
#else
sbit BEEP_GPIO=P1^5;
#endif
typedef struct my_beep
{
	/**
  * @brief          打开嗡鸣器
  * @param[in]      NUUL
  * @retval         NULL
  */
	 void (*beep_on)(void);
	/**
  * @brief          关闭嗡鸣器
  * @param[in]      NUUL
  * @retval         NULL
  */
	 void (*beep_off)(void);
	/**
  * @brief          让嗡鸣器以ms为周期，duty_cycle为占空比响
  * @param[in]      ms：             周期(注意要大于定时器定时周期)
  *                 duty_cycle:      占空比
  *             
	*             
	*                 注意如果：同时使用两个定时器请指定定时器定时周期(这个函数在哪里运行就指定那个)
  * @retval         NULL
  */
   void (*in_time_interrupt)(int ms,int duty_cycle)reentrant;
	
	 unsigned long int inpt_time;
}create_beep;
void beep_init(create_beep *beep_object);
extern create_beep c51_beep;
#endif
#endif
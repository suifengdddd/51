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
  * @brief          ��������
  * @param[in]      NUUL
  * @retval         NULL
  */
	 void (*beep_on)(void);
	/**
  * @brief          �ر�������
  * @param[in]      NUUL
  * @retval         NULL
  */
	 void (*beep_off)(void);
	/**
  * @brief          ����������msΪ���ڣ�duty_cycleΪռ�ձ���
  * @param[in]      ms��             ����(ע��Ҫ���ڶ�ʱ����ʱ����)
  *                 duty_cycle:      ռ�ձ�
  *             
	*             
	*                 ע�������ͬʱʹ��������ʱ����ָ����ʱ����ʱ����(����������������о�ָ���Ǹ�)
  * @retval         NULL
  */
   void (*in_time_interrupt)(int ms,int duty_cycle)reentrant;
	
	 unsigned long int inpt_time;
}create_beep;
void beep_init(create_beep *beep_object);
extern create_beep c51_beep;
#endif
#endif
#ifndef TIME_H
#define TIME_H
#include "STC51.h"
#if TIME_
#define ms_10 10
#define TIMER_NUMBER 3
#define TIME0ON 1 
#define TIME1ON 2 
#define TIME0OFF 0
#define TIME1OFF 0
#define TIME0   1
#define TIME1   2
typedef struct my_time
{
	 //��ʱ��0��ʱ����ʱ����
	 int time0_ms;
	 //��ʱ��1��ʱ����ʱ����
	 int time1_ms;
	 //��ʱ��0���ؿ���
	 int time0;
	//��ʱ��1���ؿ���
	 int time1;
	 //��ʱ���жϱ��
	 int time_type;
	 //��ʱ����ʱ����
	 uint16 time1_i;
	 //��ʱ���жϻص�����
	 void (*time_run_func_handle)(void)reentrant;
	 /**
  * @brief          �������THX��TLX
  * @param[in]      time_object��time����ָ��
  * @retval         NULL
  */
	 void (*time_again_init)(struct my_time * time_object);
}create_time;
typedef struct Timer
{
	create_time *time;
	uint16 time_ms_i;
  uint8 time_i;
	uint8 flag;
	uint8 (*time_out)(struct Timer*object);
}create_Timer;
/**
  * @brief          ��ʼ��time����
  * @param[in]      time_object��time����ָ��
  * @retval         NULL
  */
void time_init(create_time *time_object);
//create_Timer * create_timer(uint8 time_ms,create_time *time);
extern void time_run_func_handle(void)reentrant;
extern create_time c51_time;
//extern create_Timer * timer_arr[TIMER_NUMBER]; 
//extern uint8 time_point_number;
#endif
#endif 

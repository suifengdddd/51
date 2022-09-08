#ifndef TIME_H
#define TIME_H
#include "STC51.h"
#if TIME_
#define ms_10 10
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
	 //��ʱ���жϻص�����
	 void (*time_run_func_handle)(void);
	 /**
  * @brief          �������THX��TLX
  * @param[in]      time_object��time����ָ��
  * @retval         NULL
  */
	 void (*time_again_init)(struct my_time * time_object);
}create_time;
/**
  * @brief          ��ʼ��time����
  * @param[in]      time_object��time����ָ��
  * @retval         NULL
  */
void time_init(create_time *time_object);
extern void time_run_func_handle(void);
extern create_time c51_time;
#endif
#endif 

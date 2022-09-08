#ifndef TIME_H
#define TIME_H
#include "STC51.h"
#if TIME_
#define ms_10 10
#define TIME0ON 1 
#define TIME1ON 1  
#define TIME0OFF 0
#define TIME1OFF 0 
#define TIME0   1
#define TIME1   2
typedef struct my_time
{
	 //��ʱ��0��ʱ����ʱ����
	 unsigned int time0_ms;
	 //��ʱ��1��ʱ����ʱ����
	 unsigned int time1_ms;
	 //��ʱ��0���ؿ���
	 unsigned char  time0;
	//��ʱ��1���ؿ���
	 unsigned char time1;
	 //��ʱ���жϱ��
	 unsigned char time_type;
	 //��ʱ���жϻص�����
	 int time0_i;
	 int time1_i;
	 void (*time_run_func_handle)(void);
	 int (*time_out)(int ms);
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
int time_out(int ms);
extern create_time c51_time;
#endif
#endif 

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
	 //定时器0定时器定时周期
	 int time0_ms;
	 //定时器1定时器定时周期
	 int time1_ms;
	 //定时器0开关控制
	 int time0;
	//定时器1开关控制
	 int time1;
	 //定时器中断标号
	 int time_type;
	 //定时器中断回调函数
	 void (*time_run_func_handle)(void);
	 /**
  * @brief          重新填充THX和TLX
  * @param[in]      time_object：time对象指针
  * @retval         NULL
  */
	 void (*time_again_init)(struct my_time * time_object);
}create_time;
/**
  * @brief          初始化time对象
  * @param[in]      time_object：time对象指针
  * @retval         NULL
  */
void time_init(create_time *time_object);
extern void time_run_func_handle(void);
extern create_time c51_time;
#endif
#endif 

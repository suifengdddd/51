#include "BEEP.h"
#if BEEP_
static void beep_on(void);
static void beep_off(void);
static void in_time_interrupt(int ms,int duty_cycle)reentrant;
/**
  * @brief          初始化beep对象
  * @param[in]      beep_object：beep对象指针
  * @retval         NULL
  */
void beep_init(create_beep *beep_object)
{
	 beep_object->beep_on=beep_on;
	 beep_object->beep_off=beep_off;
	 beep_object->in_time_interrupt=in_time_interrupt;
	 beep_object->inpt_time=10;

	 
}
/**
  * @brief          打开嗡鸣器
  * @param[in]      NUUL
  * @retval         NULL
  */
static void beep_on(void)
{
	 BEEP_GPIO=0;
}
/**
  * @brief          关闭嗡鸣器
  * @param[in]      NUUL
  * @retval         NULL
  */
static void beep_off(void)
{
	BEEP_GPIO=1;
}
/**
  * @brief          让嗡鸣器以ms为周期，duty_cycle为占空比响
  * @param[in]      ms：             周期(注意要大于定时器定时周期)
  *                 duty_cycle:      占空比
  *             
	*             
	*                 注意如果：同时使用两个定时器请指定定时器定时周期(这个函数在哪里运行就指定那个)
  * @retval         NULL
  */
#if TIME_
static void in_time_interrupt(int ms,int duty_cycle)reentrant
{


	  static unsigned int i=0;
	  int inpt_time=0;
	
	  int high_time=0;
	  if(c51_time.time0==TIME0ON&&c51_time.time1==TIME1OFF)
		{
			 inpt_time=c51_time.time0_ms;
		}
		else if (c51_time.time0==TIME0OFF&&c51_time.time1==TIME1ON)
		{
			 inpt_time=c51_time.time1_ms;
		}
		else
		{
			inpt_time = c51_beep.inpt_time;
		}
		
	  high_time=duty_cycle*ms;//高电平执行时间
	
			 if(i*inpt_time<=high_time)
			{
				 BEEP_GPIO=0;
				 
			}
			else if (high_time<i*inpt_time&&i*inpt_time<=ms)
			{
				 BEEP_GPIO=1;
			}
			

	 i++;
		if(i*inpt_time>ms)
		{
			i=0;
		}		    
	}
#endif
#endif
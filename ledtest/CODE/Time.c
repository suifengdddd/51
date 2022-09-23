#include "Time.h"
/*注意当time0和time1同时打开时请设置
 *c51_time.time0_ms
 *c51_time.time1_ms
 *两个都要大于3
 *此时如果有动态数码管那么会看到明显闪烁
 *平常使用时尽量只开一个定时器
 */
#if TIME_

static void time_again_init(create_time * time_object);
/**
  * @brief          初始化time对象
  * @param[in]      time_object：time对象指针
  * @retval         NULL
  */
void time_init(create_time *time_object)
{
	 time_object->time_run_func_handle=time_run_func_handle;
	 time_object->time_again_init=time_again_init;
	
	
	 if(time_object->time0==TIME0ON&&time_object->time1==TIME1OFF)
	 {
		  
		 TMOD=0x01;//设置定时器0为工作方式1
		 TH0=(65536-(921600/(1000/time_object->time0_ms)))/256;
		 TL0=(65536-(921600/(1000/time_object->time0_ms)))%256;
		 EA=1;//中断总控制位
		 ET0=1;//定时器中断运行位
		 TR0=1;//定时器0运行控制位
		 
	 }
	 else if(time_object->time0==TIME0OFF&&time_object->time1==TIME1ON)
	 {
		  
		 TMOD=0x10;//设置定时器1为工作方式1
		 TH1=(65536-(921600/(1000/time_object->time1_ms)))/256;
		 TL1=(65536-(921600/(1000/time_object->time1_ms)))%256;
		 EA=1;//中断总控制位
		 ET1=1;//定时器中断运行位
		 TR1=1;//定时器0运行控制位
		
	 }
	 else if(time_object->time0==TIME0ON&&time_object->time1==TIME1ON)
	 {
		 EA=0;//中断总控制位
		 TMOD=0x11;//设置定时器1为工作方式1
	 
		 
		 TH1=(65536-(921600/(1000/time_object->time1_ms)))/256;
		 TL1=(65536-(921600/(1000/time_object->time1_ms)))%256;
		 ET1=1;//定时器中断运行位
		 TR1=1;//定时器0运行控制位
		 
		 TH0=(65536-(921600/(1000.0/time_object->time0_ms)))/256;
		 TL0=(65536-(921600/(1000/time_object->time0_ms)))%256;
		 
		 ET0=1;//定时器中断运行位
		 TR0=1;//定时器0运行控制位
  	 EA=1;//中断总控制位
		
	 }
	
}
/**
  * @brief          重新填充THX和TLX
  * @param[in]      time_object：time对象指针
  * @retval         NULL
  */
static void time_again_init(create_time * time_object)
{
	if(time_object->time0==TIME0ON&&time_object->time_type==TIME0)
	{
	
		 TH0=(65536-(921600/(1000/time_object->time0_ms)))/256;
		 TL0=(65536-(921600/(1000/time_object->time0_ms)))%256;
		
	}
	else if(time_object->time1==TIME1ON&&time_object->time_type==TIME1)
	{
		
		  TH1=(65536-(921600/(1000/time_object->time1_ms)))/256;
		 TL1=(65536-(921600/(1000/time_object->time1_ms)))%256;


		 
	}
	
	

}
//定时器0中断函数
void T0_time() interrupt 1
{
	
	  c51_time.time_type=TIME0;
	  c51_time.time_again_init(&c51_time);
	  c51_time.time_run_func_handle();

}
//定时器1中断函数
void T1_time() interrupt 3
{  

	  
	  c51_time.time_type=TIME1;
	  c51_time.time_again_init(&c51_time);
	  c51_time.time_run_func_handle();
	
}
#endif

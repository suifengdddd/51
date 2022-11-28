#include "Time.h"
//定时器中断回调函数
extern unsigned char alarm_data[4];
void time_run_func_handle(void)reentrant
{
	 static int time0_i=0,time0_5s_i=0;
	 static int time1_i=0;
	 //定时器0中断有关请写在这里
	if(c51_time.time_type==TIME0)
	{
		  if(c51_ds18b20.temp>c51_ds18b20.temp_max&&time0_i==10)
		 {
			 //led报警
			 GPIO_1_0=~GPIO_1_0;
			 //蜂鸣器报警
//			 BEEP_GPIO=~BEEP_GPIO;
			
		 }
		 
		  if(c51_ds18b20.temp>c51_ds18b20.temp_max&&time0_5s_i==100)
		 {
			 //串口发送温度值
			 c51_usart.send_data(alarm_data,sizeof(alarm_data));
			 //发送换行
			 c51_usart.send_data("\r\n",sizeof("\r\n"));
			
		 }
	  
			if(time0_i>10)
			{
				time0_i=0;
			}
			if(time0_5s_i>100)
			{
				time0_5s_i=0;
			}
	    time0_i++;
			time0_5s_i++;

	}
	//定时器1中断有关请写在这里
	else if(c51_time.time_type==TIME1)
	{


	
	   time1_i++;

	}


	c51_time.time_type=0;
}
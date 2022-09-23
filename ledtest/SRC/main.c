#include "STC51.h"
/*在开始写代码之前请思考需要使用什么外设*/
/*****然后再STC51.h里打开相应外设*******/
/***********这里不要改变哦**************/
/*************开始*********************/
#if TIME_
create_time c51_time;
#endif

#if KEY_
create_key c51_key; 
#endif

#if LED_
create_led c51_led;
#endif

#if BEEP_
create_beep c51_beep;
#endif

#if SMG_
create_nixie_tube c51_nixie_tube;
#endif

#if USART
create_usart c51_usart;
#endif

#if DS18B20_
create_temp c51_ds18b20;
#endif
		
#if LCD1602_
create_lcd c51_lcd1602;
#endif
/***************结束*********************/
void main()
{
    
/***********这里对各外设进行初始化**************/
/********************开始**********************/   
	  #if LED_//led
	  led_init(&c51_led);
	  #endif
	
	  #if KEY_//按键
	  key_init(&c51_key);
	  #endif
	
	  #if BEEP_//嗡鸣器
    beep_init(&c51_beep);
	  #endif
	
    #if SMG_//数码管
    nixie_tube_init(&c51_nixie_tube);	
	  #endif
	
	  #if DS18B20_//ds18b20
	  temp_init(&c51_ds18b20);
	  #endif
		
		#if LCD1602_//LCD
		lcd1602_init(&c51_lcd1602);
		#endif
/********************结束**********************/	

/****************定时器初始化******************/
#if TIME_	
    //打开/关闭定时器0		
	  c51_time.time0=TIME0ON;
		 //定时器0中断周期（1-70）
	  c51_time.time0_ms=50;
	  //打开/关闭定时器1	
	  c51_time.time1=TIME1ON;
		//定时器1中断周期（1-70）
	  c51_time.time1_ms=30;
	  c51_time.time_type=0;
	  time_init(&c51_time);
#endif
/******************结束***********************/	

/****************串口初始化*******************/
#if USART
    //设置波特率为9600
	  c51_usart.baud_rate=9600;
	  usart_init(&c51_usart);
#endif		
/******************结束***********************/	

		


   

		while(1)
		{
		   
		}

	
		
	
}
#if USART
void usart_rx_func_handle (void)
{
	  
	  		 
}
#endif
#if TIME_	 
void time_run_func_handle(void)
{
	 static int time0_i=0;
	 static int time1_i=0;
	if(c51_time.time_type==TIME0)
	{
		

     

		
	
	   time0_i++;

		 if(time0_i<=10)
		 {
			 c51_led.led_on(1);
		 }
		 else if(time0_i>10&&time0_i<=20)
		 {
			  c51_led.led_off(1);
		 }
		 if(time0_i>20)
		 {
			 time0_i=0;
		 }
		
	}
	else if(c51_time.time_type==TIME1)
	{
   

		 if(time1_i<=10)
		 {
			 c51_led.led_on(3);
		 }
		 else if(time1_i>10&&time1_i<=20)
		 {
			  c51_led.led_off(3);
		 }
		 if(time1_i>20)
		 {
			 time1_i=0;
		 }
	
	  time1_i++;


	
	}
	
	
	c51_time.time_type=0;
	
}
#endif

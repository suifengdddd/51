#include "STC51.h"
#if TIME_
create_time c51_time;
create_Timer *my_time;
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

#if LCD1602_
create_lcd c51_lcd1602;
#endif

#if DS18B20_
create_temp c51_ds18b20;
#endif

#if ADC_
create_adc c51_adc;
#endif

main()
{
    
	
	  #if LED_
	  led_init(&c51_led);
	  #endif
	  #if KEY_
	  key_init(&c51_key);
	  #endif
	  #if BEEP_
    beep_init(&c51_beep);
	  #endif
    #if SMG_
    nixie_tube_init(&c51_nixie_tube);	
	  #endif
#if TIME_	
		
    //打开定时器0		
	  c51_time.time0=TIME0ON;
		 //10ms一个中断
	  c51_time.time0_ms=50;
	  //关闭定时器1
	  c51_time.time1=TIME1OFF;
	  c51_time.time1_ms=50;
	
	  c51_time.time_type=0;
	  time_init(&c51_time);
		//my_time=create_timer(500,&c51_time);
#endif
	
#if USART
    //设置波特率为9600
	  c51_usart.baud_rate=4800;
	  usart_init(&c51_usart);
#endif		

#if LCD1602_
lcd1602_init(&c51_lcd1602);
#endif

#if DS18B20_
temp_init(&c51_ds18b20);
#endif

#if ADC_
adc_init(&c51_adc);

#endif
   
	
		
		while(1)
		{
		  
				c51_usart.my_printf("okkk",strlen("okkk"));
			  delayms(1000);
		}

	
		
	
}
#if USART
void usart_rx_func_handle (void)
{
	 c51_usart.USART_RX_BUF[c51_usart.USART_RX_STA]=SBUF;
	 if(c51_usart.USART_RX_STA<USART_REC_LEN)
	 {
			c51_usart.USART_RX_STA++;
	 }		 
}
#endif
#if TIME_	 
void time_run_func_handle(void)reentrant
{
	 static int time0_i=0;
	 static int time1_i=0;
	if(c51_time.time_type==TIME0)
	{
	   time0_i++;
  		
		 #if ADC_
		 //AD定时150ms,c51_time.time0_ms为定时器0定时周期
		 c51_adc.adc_time_i++;
		 if(c51_adc.adc_time_i>=150/c51_time.time0_ms)
		 {
	     c51_adc.adc_flag=1;
			 c51_adc.adc_time_i=0;
		 }
		 #endif
	}
	else if(c51_time.time_type==TIME1)
	{
   
	
//	 
//		for(i=0;i<TIMER_NUMBER;i++)
//		{
//			 if(timer_arr[i]!=NULL)
//			 {
//				 if(timer_arr[i]->time_i==timer_arr[i]->time_ms_i)
//				 {
//					  timer_arr[i]->flag=1;
//					  timer_arr[i]->time_i=0;
//				 }
//				 timer_arr[i]->time_i++;
//				
//				 
//			 }
//		}
   
	
	}
	
	
	c51_time.time_type=0;
	
}
#endif

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
int i_led=0;
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
	  c51_time.time1=TIME1ON;
	  c51_time.time1_ms=50;
	
	  c51_time.time_type=0;
	  time_init(&c51_time);
		//my_time=create_timer(500,&c51_time);
#endif
	
#if USART
    //设置波特率为9600
	  c51_usart.baud_rate=9600;
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
			 c51_nixie_tube.arr[0]=200/1000%10;
			 c51_nixie_tube.arr[1]=200/100%10;
			 c51_nixie_tube.arr[2]=200/10%10;
			 c51_nixie_tube.arr[3]=200/1%10;
//			if(my_time->time_out(my_time))
//			{
//				 i_led=~i_led;
//			}
			if(i_led==1)
			{
				c51_led.led_on(1);
			}
			else
			{
				 c51_led.led_off(1);
			}
			c51_nixie_tube.dynamic_display(1,4,c51_nixie_tube.arr);
      		
		}

	
		
	
}
#if USART
void usart_rx_func_handle (void)
{
	 c51_usart.USART_RX_BUF[USART_RX_STA]=SBUF;
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
	 uint8 i=0;
	 
	 


	if(c51_time.time_type==TIME0)
	{
		

     

		
	   if(time0_i==20)
		 {
			  time1_i=!time1_i;
		 }
		 	if(time1_i==1)
			{
				c51_led.led_on(2);
			}
			else
			{
				 c51_led.led_off(2);
			}
	   time0_i++;
  
		 if(time0_i>20)
		 {
			 time0_i=0;
		 }
		
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

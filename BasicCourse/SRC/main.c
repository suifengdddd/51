#include "STC51.h"
//注意本代码只打开了led和数码管，要打开其它外设请到STC51.h里配置
#if TIME_
create_time c51_time;
//create_Timer *my_time;
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

void main()
{
    
	  uint8 i=0;
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
			//led1开
      c51_led.led_on(1);
			delayms(500);
			//led1关
			c51_led.led_off(1);
			delayms(500);
			//填充数码管显示数组
			c51_nixie_tube.arr[0]=i/100%10;
			c51_nixie_tube.arr[1]=i/10%10;
			c51_nixie_tube.arr[2]=i/1%10;
			//调用数码管动态显示函数
			c51_nixie_tube.dynamic_display(1,3,c51_nixie_tube.arr);
			if(i<=999)
			{
				i++;
			}
			else
			{
				 i=0;
			}
		}

	
		
	
}
//串口接收中断回调函数
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
//定时器中断回调函数
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
		 if(c51_adc.adc_time_i>=ADC_TIME/c51_time.time0_ms)
		 {
	     c51_adc.adc_flag=1;
			 c51_adc.adc_time_i=0;
		 }
		 #endif
	}
	else if(c51_time.time_type==TIME1)
	{
   
	   time1_i++;
	
	}
	
	
	c51_time.time_type=0;
	
}
#endif

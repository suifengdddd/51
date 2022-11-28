#include "STC51.h"
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

#if LCD1602_
create_lcd c51_lcd1602;
#endif

#if DS18B20_
create_temp c51_ds18b20;
#endif
main()
{
    
	  
	  #if LED_
	  int arr[8]={LED1,OFF,LED3,OFF,0,0,0,0};
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
	  c51_time.time0=TIME0OFF;
		 //10ms一个中断
	  c51_time.time0_ms=50;
	  //关闭定时器1
	  c51_time.time1=TIME1OFF;
	  c51_time.time1_ms=50;
	
	  c51_time.time_type=0;
	  time_init(&c51_time);
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


   
		c51_lcd1602.show_data("LiShuiXueYuan",0x80);
		c51_lcd1602.show_data("QiangDaBiSai",0x80+0x40);
		delayms(2000);
//		c51_lcd1602.write_com(0x01);
//		c51_lcd1602.show_data("Hello  everyone!",0x80);
//		c51_lcd1602.show_data("Welcome to here!",0x80+0x40);
		
		while(1)
		{
		  
		}

	
		
	
}
#if USART
void usart_rx_func_handle (void)
{
	  unsigned  char  res;
	  RI=0;
	  c51_led.led_on(1);
	  res =SBUF;
	  	if((c51_usart.USART_RX_STA&0x8000)==0)//接收未完成
		{
			if(c51_usart.USART_RX_STA&0x4000)//接收到了0x0d
			{
				if(res!=0x0a)c51_usart.USART_RX_STA=0;//接收错误,重新开始
				else c51_usart.USART_RX_STA|=0x8000;	//接收完成了 
			}else //还没收到0X0D
			{	
				if(res==0x0d)c51_usart.USART_RX_STA|=0x4000;
				else
				{
					c51_usart.USART_RX_BUF[c51_usart.USART_RX_STA&0X3FFF]=res;
					c51_usart.USART_RX_STA++;
					if(c51_usart.USART_RX_STA>(USART_REC_LEN-1))c51_usart.USART_RX_STA=0;//接收数据错误,重新开始接收	  
				}		 
			}
		}
	  		 
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

		 if(time0_i>20)
		 {
			 time0_i=0;
		 }
		
	}
	else if(c51_time.time_type==TIME1)
	{
   

		 if(time0_i%50==0)
		 {
		    //c51_led.led_on(2);
		}
		else
		{
			 //c51_led.led_off(2);
		}
	
	  time1_i++;


	
	}
	
	
	c51_time.time_type=0;
	
}
#endif

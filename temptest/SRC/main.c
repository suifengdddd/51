#include "STC51.h"
#define SHOW_TEMP 1
#define SHOW_ALARM_TEMP 0
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
create_temp c51_temp;
#endif

main()
{
	
    int flag=SHOW_TEMP;
	  int tepm_c=280;
    int arr[6]={0};
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
#endif
	
#if USART
    //设置波特率为9600
	  c51_usart.baud_rate=9600;
	  usart_init(&c51_usart);
#endif		

#if DS18B20_
    temp_init(&c51_temp);
#endif
		

    
	while(1)
	{
	
		EA=0;
    c51_temp.begin_temp_change();
		c51_temp.get_temp(&c51_temp);
		EA=1;
		c51_key.key=c51_key.whitch_key_down(&c51_key);
		if(c51_key.key==KEY3)
		{
			tepm_c=tepm_c+5;
			c51_key.key=0;
	
		}
		else if(c51_key.key==KEY4)
		{
			tepm_c=tepm_c-5;
			c51_key.key=0;
			
			
		}
		else if(c51_key.key==KEY2)
		{
			flag=~flag;
			c51_key.key=0;
		}
		else if(c51_key.key==KEY5)
		{
			c51_temp.temp_max=tepm_c;
			c51_key.key=0;
			
		}
		if(flag==SHOW_TEMP)
		{
		  arr[0]=c51_temp.temp/100%10;
		  arr[1]=c51_temp.temp/10%10;
		  arr[2]=c51_temp.temp/1%10;
		}
		else 
		{
			 arr[0]=tepm_c/100%10;
		  arr[1]=tepm_c/10%10;
		  arr[2]=tepm_c/1%10;
		   
		}
		
		  if(c51_temp.temp<=c51_temp.temp_max)
			{
				GPIO_1_0=1;
			  BEEP_GPIO=1;
			}
			
		c51_nixie_tube.dynamic_display(1,3,arr);
		
		
	   

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
		

     if(c51_temp.temp>c51_temp.temp_max&&time0_i==10)
		 {
			
			
			 GPIO_1_0=~GPIO_1_0;
			 BEEP_GPIO=~BEEP_GPIO;
			
		 }
		 
	
	  
			if(time0_i>10)
			{
				time0_i=0;
			}
			time0_i++;

		
		
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

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

main()
{
	
    int time_i=0,add=0;
    
	  #if LED_
	  int arr[8]={0};
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
		

    
	while(1)
	{
	
		   //数码管第1到4位显示0-10000
		   if(time_i==1000)
			 {
				 add++;
			 }
			 arr[0]=add/10000%10;
			 arr[1]=add/1000%10;
			 arr[2]=add/100%10;
			 arr[3]=add/10%10;
			 c51_led.led_on(arr[0]/8);
			 c51_nixie_tube.dynamic_display(1,4,arr);
       delayms(1);
		   time_i++;
			 if(time_i>1000)
			 {
				 time_i=0;
				 c51_led.led_all_off();
				 
			 }
			 if(add>10000)
			 {
				 add=0;
			 }
		
			 
			 

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
		

     
//		 c51_beep.inpt_time=20;
//		 c51_beep.in_time_interrupt(100,0.5);
	   c51_key.key=c51_key.whitch_key_down();
		 c51_nixie_tube.arr[0]=c51_key.key/10;
		 c51_nixie_tube.arr[1]=c51_key.key%10;
		 if(time0_i%2==0)
		 {
		 c51_nixie_tube.show_number(1,c51_nixie_tube.arr[0]);
		 }
		 else
		 {
		 c51_nixie_tube.show_number(2,c51_nixie_tube.arr[1]);
		 }

		
	
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

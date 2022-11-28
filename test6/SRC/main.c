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
int arr[6]={7,6,5,4,3,2};//数码管显示数字数组
int hello_arr[6]={16,14,17,17,0};//数码管显示HELLO数组
int led_i=1;//led移位
int falg=0;//任务步骤标志位
int on_off=0;//led闪烁标志位
void led_control(void)
{
	  int i=1;
	//led移动
		if(falg==0)
		{
		  c51_led.led_on(led_i);
		}
		//led闪烁
		else if(falg==1)
		{
			 
			if(on_off==0)
			{
				for(i=1;i<=8;i++)
				{
					c51_led.led_on(i);
				}
			}
			else
			{
				for(i=1;i<=8;i++)
				{
					c51_led.led_off(i);
				}
			}
		}
		else 
		{
			 c51_led.led_all_off();
		}
}
void sms_control(void)
{
	
		
		//显示数字
	  if(falg!=2)
		{
			c51_nixie_tube.dynamic_display(1,6,arr);
		}
		//显示HELLO
		else if(falg==2)
		{
			c51_nixie_tube.dynamic_display(1,5,hello_arr);
		}
}
void main(void)
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
#endif
	
#if USART
    //设置波特率为9600
	  c51_usart.baud_rate=9600;
	  usart_init(&c51_usart);
#endif		
		

    
	while(1)
	{
		
	  led_control();
		sms_control();
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
	 static int time_sms_i=0,sms_i=432,time_led_i=0,time_i=0,once=1,time_3s_i=0;
	 
	if(c51_time.time_type==TIME0)
	{
			//控制led移动
		  if(time_led_i==5&&sms_i>398)
		 {
			   led_i++;
			   time_led_i=0;
			   if(led_i>8)
				 {
					 led_i=0;
				 }
				 c51_led.led_all_off();
				 
		 }
		
		  //控制led闪烁
		  if(time_i==10&&time_3s_i<=60)
		 {
			 time_i=0;
			 on_off=~on_off; 
		 }
		  time_led_i++;
		 
	}
	else if(c51_time.time_type==TIME1)
	{
   
     //步骤1 控制数码管
	   if(time_sms_i==2&&sms_i>398)
		 {
			   sms_i--;
			   time_sms_i=0;
			
		 }
		 
		
		 //步骤2
		 if(sms_i==398&&once==1)
		 {
			  falg=1;	 
			  time_i=0;
			  once=0;
			  time_3s_i=0;
			  
		 }
		 
		 
		 //步骤3显示Hell0
		 if(time_3s_i==60)
		 {
			  falg=2;
		 }
		 
		 arr[3]=sms_i/100%10;
		 arr[4]=sms_i/10%10;
		 arr[5]=sms_i/1%10;
	   time_sms_i++;
		 time_i++;
		 if(falg==1)
		 {
		   time_3s_i++;
		 }

	
	
	}
	
	
	c51_time.time_type=0;
	
}
#endif

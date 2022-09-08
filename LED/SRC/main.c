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
	
    int i,j,k;
    
	  #if LED_
	  int arr[8]={LED1,LED2,LED3,LED4,LED5,LED6,LED7,LED8};
		int arr1[8]={LED1,0,LED3,0,LED5,0,LED7,0};
		int arr2[8]={0,LED2,0,LED4,0,LED6,0,LED8};
		int *arr_list[2]={arr1,arr2};
		
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
	
       //从左到右依次点亮，间隔200ms
		   for(i=1;i<=8;i++)
		   {
				  c51_led.led_on(i);
				  delayms(200);
			 }
			 c51_led.led_all_off();
			 delayms(2000);
			 
			 
			 //从右到左依次点亮，间隔200ms
			  for(i=8;i>=1;i--)
		   {
				  c51_led.led_on(i);
				  delayms(200);
			 }
			 c51_led.led_all_off();
			 delayms(2000);
			 
			 
			 //从中间到两边依次点亮三次，间隔200ms
			 for(i=0;i<=2;i++)
			 {
				  for(j=4,k=5;j>=1;j--,k++)
				 {
					 c51_led.led_on(j);
					 c51_led.led_on(k);
				   delayms(200);
				 }
				 c51_led.led_all_off();
			 }
			 delayms(2000);
			 
			 
			 //从两边到中间依次点亮三次，间隔200ms
			 for(i=0;i<=2;i++)
			 {
				  for(j=1,k=8;j<=4;j++,k--)
				 {
					 c51_led.led_on(j);
					 c51_led.led_on(k);
				   delayms(200);
					 
				 }
				 c51_led.led_all_off();
			 }
			 delayms(2000);
			 
			 //全亮全灭三次
			 for(i=0;i<=2;i++)
			 {
			   c51_led.leds_flicker(arr,200,400);
			 }
			 
			  c51_led.led_all_off();
			 delayms(2000);
			 
			 //第一个灯闪烁1次，第二个灯闪烁2次，依次类推。
			 for(i=1;i<=8;i++)
			 {
				  c51_led.led_flicker(i,200,i*200); 
			 }
			 
			  c51_led.led_all_off();
			 delayms(2000);
			 
			 //1 3 5 7    2 4 6 8交叉亮 
			 for(i=0;i<=2;i++)
			 {
				 for(j=0;j<=1;j++)
				 {
			      c51_led.leds_flicker(arr_list[j],200,400);
				 }
				  c51_led.led_all_off();
			 }
			  c51_led.led_all_off();
			  delayms(2000);
			 
			 

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

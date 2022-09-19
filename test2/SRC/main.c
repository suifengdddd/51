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
	
    int i=1;
    int arr[3]={0};
    int key_val=0;
    
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
    //�򿪶�ʱ��0		
	  c51_time.time0=TIME0OFF;
		 //10msһ���ж�
	  c51_time.time0_ms=50;
	  //�رն�ʱ��1
	  c51_time.time1=TIME1OFF;
	  c51_time.time1_ms=50;
	
	  c51_time.time_type=0;
	  time_init(&c51_time);
#endif
	
#if USART
    //���ò�����Ϊ9600
	  c51_usart.baud_rate=9600;
	  usart_init(&c51_usart);
#endif		
		c51_led.led_all_off();
    
	while(1)
	{
	

		 c51_key.key=c51_key.whitch_key_down();

			if(c51_key.key!=0)
			{
				 i++;
				if(i>8)
				{
							i=1;
					   c51_led.led_off(8);
				}
			key_val=c51_key.key;
			}
			
			c51_led.led_on(i);
			c51_led.led_off(i-1);
			if(key_val==0)
			{
			   arr[0]=0;
			  arr[1]=0;
			  arr[2]=0;
			}
			else
			{
				arr[0]=(key_val-5)*(key_val-5)/100%10;
			  arr[1]=(key_val-5)*(key_val-5)/10%10;
			  arr[2]=(key_val-5)*(key_val-5)/1%10;
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
	  	if((c51_usart.USART_RX_STA&0x8000)==0)//����δ���
		{
			if(c51_usart.USART_RX_STA&0x4000)//���յ���0x0d
			{
				if(res!=0x0a)c51_usart.USART_RX_STA=0;//���մ���,���¿�ʼ
				else c51_usart.USART_RX_STA|=0x8000;	//��������� 
			}else //��û�յ�0X0D
			{	
				if(res==0x0d)c51_usart.USART_RX_STA|=0x4000;
				else
				{
					c51_usart.USART_RX_BUF[c51_usart.USART_RX_STA&0X3FFF]=res;
					c51_usart.USART_RX_STA++;
					if(c51_usart.USART_RX_STA>(USART_REC_LEN-1))c51_usart.USART_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
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

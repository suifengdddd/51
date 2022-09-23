#include "STC51.h"
/*�ڿ�ʼд����֮ǰ��˼����Ҫʹ��ʲô����*/
/*****Ȼ����STC51.h�����Ӧ����*******/
/***********���ﲻҪ�ı�Ŷ**************/
/*************��ʼ*********************/
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
/***************����*********************/
void main()
{
    
/***********����Ը�������г�ʼ��**************/
/********************��ʼ**********************/   
	  #if LED_//led
	  led_init(&c51_led);
	  #endif
	
	  #if KEY_//����
	  key_init(&c51_key);
	  #endif
	
	  #if BEEP_//������
    beep_init(&c51_beep);
	  #endif
	
    #if SMG_//�����
    nixie_tube_init(&c51_nixie_tube);	
	  #endif
	
	  #if DS18B20_//ds18b20
	  temp_init(&c51_ds18b20);
	  #endif
		
		#if LCD1602_//LCD
		lcd1602_init(&c51_lcd1602);
		#endif
/********************����**********************/	

/****************��ʱ����ʼ��******************/
#if TIME_	
    //��/�رն�ʱ��0		
	  c51_time.time0=TIME0ON;
		 //��ʱ��0�ж����ڣ�1-70��
	  c51_time.time0_ms=50;
	  //��/�رն�ʱ��1	
	  c51_time.time1=TIME1ON;
		//��ʱ��1�ж����ڣ�1-70��
	  c51_time.time1_ms=30;
	  c51_time.time_type=0;
	  time_init(&c51_time);
#endif
/******************����***********************/	

/****************���ڳ�ʼ��*******************/
#if USART
    //���ò�����Ϊ9600
	  c51_usart.baud_rate=9600;
	  usart_init(&c51_usart);
#endif		
/******************����***********************/	

		


   

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

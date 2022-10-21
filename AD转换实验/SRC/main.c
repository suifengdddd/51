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
		
    //�򿪶�ʱ��0		
	  c51_time.time0=TIME0ON;
		 //10msһ���ж�
	  c51_time.time0_ms=50;
	  //�رն�ʱ��1
	  c51_time.time1=TIME1OFF;
	  c51_time.time1_ms=50;
	
	  c51_time.time_type=0;
	  time_init(&c51_time);
		//my_time=create_timer(500,&c51_time);
#endif
	
#if USART
    //���ò�����Ϊ9600
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
			 //��ʼADת��
			 c51_adc.begin_adc_change();
			 //�ж�ת���Ƿ����(������ö�ʱ���ж�ʵ��,��ʱ����ʱ����Ϊ50ms)
			 if(c51_adc.adc_flag==1)
			 {
				  //���ת������ǾͶ�ȡADC��ֵ
					c51_adc.adc_val=c51_adc.read_adc_value();
				  c51_adc.adc_flag=0;
			 }
			 //��������ֵ��ֵ���������ʾ����
			 c51_nixie_tube.arr[0]=c51_adc.adc_val/100;
	     c51_nixie_tube.arr[1]=c51_adc.adc_val%100/10;
	     c51_nixie_tube.arr[2]=c51_adc.adc_val%10;
			 //��������ܶ�̬��ʾ������ʾADC��ֵ
			// c51_nixie_tube.dynamic_display(1,3,c51_nixie_tube.arr);

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
	if(c51_time.time_type==TIME0)
	{
	   time0_i++;
  		
		 #if ADC_
		 //AD��ʱ150ms,c51_time.time0_msΪ��ʱ��0��ʱ����
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
   
	   
	
	}
	
	
	c51_time.time_type=0;
	
}
#endif

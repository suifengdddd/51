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
int arr[6]={7,6,5,4,3,2};//�������ʾ��������
int hello_arr[6]={16,14,17,17,0};//�������ʾHELLO����
int led_i=1;//led��λ
int falg=0;//�������־λ
int on_off=0;//led��˸��־λ
void led_control(void)
{
	  int i=1;
	//led�ƶ�
		if(falg==0)
		{
		  c51_led.led_on(led_i);
		}
		//led��˸
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
	
		
		//��ʾ����
	  if(falg!=2)
		{
			c51_nixie_tube.dynamic_display(1,6,arr);
		}
		//��ʾHELLO
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
    //�򿪶�ʱ��0		
	  c51_time.time0=TIME0ON;
		 //10msһ���ж�
	  c51_time.time0_ms=50;
	  //�رն�ʱ��1
	  c51_time.time1=TIME1ON;
	  c51_time.time1_ms=50;
	
	  c51_time.time_type=0;
	  time_init(&c51_time);
#endif
	
#if USART
    //���ò�����Ϊ9600
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
	 static int time_sms_i=0,sms_i=432,time_led_i=0,time_i=0,once=1,time_3s_i=0;
	 
	if(c51_time.time_type==TIME0)
	{
			//����led�ƶ�
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
		
		  //����led��˸
		  if(time_i==10&&time_3s_i<=60)
		 {
			 time_i=0;
			 on_off=~on_off; 
		 }
		  time_led_i++;
		 
	}
	else if(c51_time.time_type==TIME1)
	{
   
     //����1 ���������
	   if(time_sms_i==2&&sms_i>398)
		 {
			   sms_i--;
			   time_sms_i=0;
			
		 }
		 
		
		 //����2
		 if(sms_i==398&&once==1)
		 {
			  falg=1;	 
			  time_i=0;
			  once=0;
			  time_3s_i=0;
			  
		 }
		 
		 
		 //����3��ʾHell0
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

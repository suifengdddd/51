#include "Time.h"
//��ʱ���жϻص�����
extern unsigned char alarm_data[4];
void time_run_func_handle(void)reentrant
{
	 static int time0_i=0,time0_5s_i=0;
	 static int time1_i=0;
	 //��ʱ��0�ж��й���д������
	if(c51_time.time_type==TIME0)
	{
		  if(c51_ds18b20.temp>c51_ds18b20.temp_max&&time0_i==10)
		 {
			 //led����
			 GPIO_1_0=~GPIO_1_0;
			 //����������
//			 BEEP_GPIO=~BEEP_GPIO;
			
		 }
		 
		  if(c51_ds18b20.temp>c51_ds18b20.temp_max&&time0_5s_i==100)
		 {
			 //���ڷ����¶�ֵ
			 c51_usart.send_data(alarm_data,sizeof(alarm_data));
			 //���ͻ���
			 c51_usart.send_data("\r\n",sizeof("\r\n"));
			
		 }
	  
			if(time0_i>10)
			{
				time0_i=0;
			}
			if(time0_5s_i>100)
			{
				time0_5s_i=0;
			}
	    time0_i++;
			time0_5s_i++;

	}
	//��ʱ��1�ж��й���д������
	else if(c51_time.time_type==TIME1)
	{


	
	   time1_i++;

	}


	c51_time.time_type=0;
}
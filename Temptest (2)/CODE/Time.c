#include "Time.h"
/*ע�⵱time0��time1ͬʱ��ʱ������
 *c51_time.time0_ms
 *c51_time.time1_ms
 *������Ҫ����3
 *��ʱ����ж�̬�������ô�ῴ��������˸
 *ƽ��ʹ��ʱ����ֻ��һ����ʱ��
 */
#if TIME_
static void time_again_init(create_time * time_object);
//static uint8 time_out(struct Timer*object);
//create_Timer * timer_arr[TIMER_NUMBER]={0}; 
//uint8 time_point_number=0;
/**
  * @brief          ��ʼ��time����
  * @param[in]      time_object��time����ָ��
  * @retval         NULL
  */
void time_init(create_time *time_object)
{
	 uint8 i=0;
	 time_object->time_run_func_handle=time_run_func_handle;
	 time_object->time_again_init=time_again_init;
	 time_object->time1_i=0;
//	 for(i=0;i<TIMER_NUMBER;i++)
//	{
//		timer_arr[i]=NULL;
//	}
	
	 if(time_object->time0==TIME0ON&&time_object->time1==TIME1OFF)
	 {
		  
		 TMOD=0x01;//���ö�ʱ��0Ϊ������ʽ1
		 TH0=(65536-(921600/(1000/time_object->time0_ms)))/256;
		 TL0=(65536-(921600/(1000/time_object->time0_ms)))%256;
		 EA=1;//�ж��ܿ���λ
		 ET0=1;//��ʱ���ж�����λ
		 TR0=1;//��ʱ��0���п���λ
		 
	 }
	 else if(time_object->time0==TIME0OFF&&time_object->time1==TIME1ON)
	 {
		  
		 TMOD=0x10;//���ö�ʱ��1Ϊ������ʽ1
		 TH1=(65536-(921600/(1000/time_object->time1_ms)))/256;
		 TL1=(65536-(921600/(1000/time_object->time1_ms)))%256;
		 EA=1;//�ж��ܿ���λ
		 ET1=1;//��ʱ���ж�����λ
		 TR1=1;//��ʱ��0���п���λ
		
	 }
	 else if(time_object->time0==TIME0ON&&time_object->time1==TIME1ON)
	 {
		 EA=0;//�ж��ܿ���λ
		 TMOD=0x11;//���ö�ʱ��1Ϊ������ʽ1
	 
		 
		 TH1=(65536-(921600/(1000/time_object->time1_ms)))/256;
		 TL1=(65536-(921600/(1000/time_object->time1_ms)))%256;
		 ET1=1;//��ʱ���ж�����λ
		 TR1=1;//��ʱ��0���п���λ
		 
		 TH0=(65536-(921600/(1000.0/time_object->time0_ms)))/256;
		 TL0=(65536-(921600/(1000/time_object->time0_ms)))%256;
		 
		 ET0=1;//��ʱ���ж�����λ
		 TR0=1;//��ʱ��0���п���λ
  	 EA=1;//�ж��ܿ���λ
		
	 }
	
}
/**
  * @brief          ��ʼ����ʱ����ʱ����
  * @param[in]      time_object����ʱ����ʱ����ָ��
  * @retval         NULL
  */
//create_Timer * create_timer(uint8 time_ms,create_time *time)
//{
//	 if (time_point_number>TIMER_NUMBER)
//	 {
//		 return NULL;
//	 }
//	 //�̳�c51��ʱ��
//	 timer_arr[time_point_number]->time=time;
//	 //��ʱ������ʱ������
//	 timer_arr[time_point_number]->time_ms_i=time_ms/time->time1_ms;
//	 timer_arr[time_point_number]->time_i=0;
//	 timer_arr[time_point_number]->flag=0;
//	 timer_arr[time_point_number]->time_out=time_out;
//	 time_point_number++;
//	 return timer_arr[time_point_number];
//	 
//}
//static uint8 time_out(struct Timer*object)
//{
//	  if(object->flag==1)
//		{
//			 object->flag=0;
//			 return 1;
//		}
//		else
//		{
//			return 0;
//		}
//}
/**
  * @brief          �������THX��TLX
  * @param[in]      time_object��time����ָ��
  * @retval         NULL
  */
static void time_again_init(create_time * time_object)
{
	if(time_object->time0==TIME0ON&&time_object->time_type==TIME0)
	{
	
		 TH0=(65536-(921600/(1000/time_object->time0_ms)))/256;
		 TL0=(65536-(921600/(1000/time_object->time0_ms)))%256;
		
	}
	else if(time_object->time1==TIME1ON&&time_object->time_type==TIME1)
	{
		
		  TH1=(65536-(921600/(1000/time_object->time1_ms)))/256;
		 TL1=(65536-(921600/(1000/time_object->time1_ms)))%256;


		 
	}
	
	

}

//��ʱ��0�жϺ���
void T0_time() interrupt 1
{
	
	  c51_time.time_type=TIME0;
	  c51_time.time_again_init(&c51_time);
	  c51_time.time_run_func_handle();

}
//��ʱ��1�жϺ���
void T1_time() interrupt 3
{  

	  
	  c51_time.time_type=TIME1;
	  c51_time.time_again_init(&c51_time);
	  c51_time.time_run_func_handle();
	
}
#endif

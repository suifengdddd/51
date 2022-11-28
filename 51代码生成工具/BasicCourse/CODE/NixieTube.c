#include "NixieTube.h"
#if SMG_
static void show_number (int location,int number);
static void dynamic_display(int begin_location,int over_location,int *arr)reentrant;
unsigned char code table[]={0x3f,0x06,0x5b,0x4f,
	                     0x66,0x6d,0x7d,0x07,
                       0x7f,0x6f,0x77,0x7c,
                       0x39,0x5e,0x79,0x71};
unsigned char code location_arr[]={0xff,0xfe,0xfd,0xfb,0xf7,0xef,0xdf};
/**
  * @brief          ��ʼ������ܶ���
  * @param[in]      object������ܶ���ָ��
  * @retval         NULL
  */
void nixie_tube_init(create_nixie_tube *object)
{
	unsigned char i=5;
	for(i=0;i<=5;i++)
	{
		object->arr[i]=0;
	}
	object->show_number=show_number;
	object->dynamic_display=dynamic_display;
	
}
/**
  * @brief          ��̬��ʾ����
  * @param[in]      location��Ҫ��ʾ�������λ�ã�1-6��
  *                 number����ʾ������
  * @retval         NULL
  */
static void show_number (int location,int number)
{
#if _C51==1
	    U1=1;
	    P0=table[number];
	    U1=0;
	
	    U2=0;
	    P0=location_arr[0];
	    U2=1;
	    P0=location_arr[location];
	    U2=0;
#else
		switch(location)	 //λѡ��ѡ�����������ܣ�
		{
		   case(1):
				LSA=1;LSB=1;LSC=1; break;//��ʾ��0λ
			case(2):
				LSA=0;LSB=1;LSC=1; break;//��ʾ��1λ
			case(3):
				LSA=1;LSB=0;LSC=1; break;//��ʾ��2λ
			case(4):	
				LSA=0;LSB=0;LSC=1; break;//��ʾ��3λ
			case(5):
				LSA=1;LSB=1;LSC=0; break;//��ʾ��4λ
			case(6):
				LSA=0;LSB=1;LSC=0; break;//��ʾ��5λ
			case(7):
				LSA=1;LSB=0;LSC=0; break;//��ʾ��6λ
			case(8):
				LSA=0;LSB=0;LSC=0; break;//��ʾ��7λ	
		}
		P0=table[number];//���Ͷ���
	
#endif	
	    
}
/**
  * @brief          ��̬��ʾ����
  * @param[in]      begin_location���������ʼ
  *                 over_location�� ����ܽ���  
  *                 arr������ָ�룺Ҫ��ʾ�����������
 	*                 ע��˺�����Ҫ�ڶ�ʱ���ж���ʹ��
  * @retval         NULL
  */
static void dynamic_display(int begin_location,int over_location,int *arr)reentrant
{
	 int i=1;
	 for(i=begin_location;i<=over_location;i++)
	{
		  show_number(i,arr[i-1]);
		  delayms(1);
	}


}
#endif

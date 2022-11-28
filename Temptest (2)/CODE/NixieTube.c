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
  * @brief          初始化数码管对象
  * @param[in]      object：数码管对象指针
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
  * @brief          静态显示数字
  * @param[in]      location：要显示的数码管位置（1-6）
  *                 number：显示的数字
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
		switch(location)	 //位选，选择点亮的数码管，
		{
		   case(1):
				LSA=1;LSB=1;LSC=1; break;//显示第0位
			case(2):
				LSA=0;LSB=1;LSC=1; break;//显示第1位
			case(3):
				LSA=1;LSB=0;LSC=1; break;//显示第2位
			case(4):	
				LSA=0;LSB=0;LSC=1; break;//显示第3位
			case(5):
				LSA=1;LSB=1;LSC=0; break;//显示第4位
			case(6):
				LSA=0;LSB=1;LSC=0; break;//显示第5位
			case(7):
				LSA=1;LSB=0;LSC=0; break;//显示第6位
			case(8):
				LSA=0;LSB=0;LSC=0; break;//显示第7位	
		}
		P0=table[number];//发送段码
	
#endif	
	    
}
/**
  * @brief          动态显示数字
  * @param[in]      begin_location：数码管起始
  *                 over_location： 数码管结束  
  *                 arr：数组指针：要显示的数组放这里
 	*                 注意此函数不要在定时器中断里使用
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

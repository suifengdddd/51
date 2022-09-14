#include "KEY.h"
#if KEY_
static int whitch_key_down (void);
/**
  * @brief          初始化key对象
  * @param[in]      key_object：key对象指针
  * @retval         NULL
  */
void key_init(create_key *key_object)
{
	 key_object->whitch_key_down=whitch_key_down;
	 key_object->key=0;
}
/**
  * @brief          判断那个按键被按下
  * @param[in]      NULL
  * @retval         按键标号(2-21)
  */

static int whitch_key_down (void)
{
	int  KeyValue=0;
  int a=0;
  GPIO_KEY=0xFF;
	
	if(GPIO_KEY2==0)
	{
		 delayms(10);
		 if(GPIO_KEY2==0)
		 {
			 while(!GPIO_KEY2);
			  return KEY2;
		 }
	}
	if(GPIO_KEY3==0)
	{
		 delayms(10);
		 if(GPIO_KEY3==0)
		 {
			 
			  while(!GPIO_KEY3);
			  return KEY3;
		 }
	}
	if(GPIO_KEY4==0)
	{
		 delayms(10);
		 if(GPIO_KEY4==0)
		 {
			 while(!GPIO_KEY4);
			  return KEY4;
		 }
	}
	if(GPIO_KEY5==0)
	{
		 delayms(10);
		 if(GPIO_KEY5==0)
		 {
			while(!GPIO_KEY5);
			  return KEY5;
		 }
	}
#if _C51==1
	  GPIO_KEY=0x0f;
	if(GPIO_KEY!=0x0f)//读取按键是否按下
	{
		delayms(10);//延时10ms进行消抖
		if(GPIO_KEY!=0x0f)//再次检测键盘是否按下
		{	
			//测试列
			GPIO_KEY=0X0F;
			switch(GPIO_KEY)
			{
				case(0X0e):	KeyValue=6;break;
				case(0X0d):	KeyValue=10;break;
				case(0X0b): KeyValue=14;break;
				case(0X07):	KeyValue=18;break;
			}
			//测试行
			GPIO_KEY=0XF0;
			switch(GPIO_KEY)
			{
				case(0Xe0):	KeyValue=KeyValue;break;
				case(0Xd0):	KeyValue=KeyValue+1;break;
				case(0Xb0): KeyValue=KeyValue+2;break;
				case(0X70):	KeyValue=KeyValue+3;break;
			}
			
		}
	}
#else	
		GPIO_KEY=0x0f;
	if(GPIO_KEY!=0x0f)//读取按键是否按下
	{
		delayms(10);//延时10ms进行消抖
		if(GPIO_KEY!=0x0f)//再次检测键盘是否按下
		{	
			//测试列
			GPIO_KEY=0X0F;
			switch(GPIO_KEY)
			{
				case(0X07):	KeyValue=1;break;
				case(0X0b):	KeyValue=2;break;
				case(0X0d): KeyValue=3;break;
				case(0X0e):	KeyValue=4;break;
			}
			//测试行
			GPIO_KEY=0XF0;
			switch(GPIO_KEY)
			{
				case(0X70):	KeyValue=KeyValue;break;
				case(0Xb0):	KeyValue=KeyValue+4;break;
				case(0Xd0): KeyValue=KeyValue+8;break;
				case(0Xe0):	KeyValue=KeyValue+12;break;
			}
			
		}
	}
#endif
	while((a<100)&&(GPIO_KEY!=0xf0))	 //检测按键松手检测
	{
		delayms(1);
		a++;
	}
	return KeyValue;
}

#endif

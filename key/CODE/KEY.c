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
	 key_object->key_val=0;
}
/**
  * @brief          判断那个按键被按下
  * @param[in]      NULL
  * @retval         按键标号(2-21)
  */

static int whitch_key_down (void)
{
	uint8  KeyValue=0;
  uint8 a=0,i=0,temp=0,j=0;
	uint8 gpio_out_put_arr[4]={0xef,0xdf,0xbf,0x7f};
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
	#if   0
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
	while((a<100)&&(GPIO_KEY!=0xf0))	 //检测按键松手检测
	{
		delayms(1);
		a++;
	}
	}
	#else
	for(i=0;i<=4;i++)//逐列扫描法
	{
		GPIO_KEY=gpio_out_put_arr[i];//这个数组储存了每一行要给P3的值
		temp=GPIO_KEY;
		temp=temp&0x0f;
		if(temp!=0x0f)
		{
			delayms(10);//消抖
			temp=GPIO_KEY;//GPIO_KEY就是P3
			temp=temp&0x0f;
			if(temp!=0x0f)
			{
				temp=GPIO_KEY;
		    temp=temp&0x0f;//只用看低位就好
				switch(temp)
				{
					case 0x0e:KeyValue=i+6;break;//i记录列，每行键值相差4
					case 0x0d:KeyValue=i+10;break;
					case 0x0b:KeyValue=i+14;break;
					case 0x07:KeyValue=i+18;break;
				}
				while(temp!=0x0f&&j<100)//松手操作，要有超时判断
				{
					temp=GPIO_KEY;
					temp=temp&0x0f;
					delayms(1);
					j++;
				}
			}		
		}	
	}
	
	#endif
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
		while((a<100)&&(GPIO_KEY!=0xf0))	 //检测按键松手检测
	{
		delayms(1);
		a++;
	}
	}
#endif
	
	return KeyValue;
}

#endif

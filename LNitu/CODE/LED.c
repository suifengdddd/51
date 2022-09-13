#include "LED.h"
#if LED_
static void led_on(int number);
static void led_off(int number);
static void led_flicker(int number,int interval_time,int time)reentrant;
static void leds_flicker(int *arr,int interval_time,int time)reentrant;
static void led_all_off(void);	

/**
  * @brief          初始化led对象
  * @param[in]      led_object：led对象指针
  * @retval         NULL
  */
void led_init(create_led * led_object)
{
	  led_object->led_on=led_on;
	  led_object->led_off=led_off;
	  led_object->led_flicker=led_flicker;
	  led_object->leds_flicker=leds_flicker;
	  led_object->led_all_off=led_all_off;
	  led_all_off();
	   
}
/**
  * @brief          点亮led
  * @param[in]      number：要点亮的led
  * @retval         NULL
  */
static void led_on(int number)
{
	  switch(number)
		{
			case 1:GPIO_1_0=0;break;
			case 2:GPIO_1_1=0;break;
			case 3:GPIO_1_2=0;break;
			case 4:GPIO_1_3=0;break;
			case 5:GPIO_1_4=0;break;
			case 6:GPIO_1_5=0;break;
			case 7:GPIO_1_6=0;break;
			case 8:GPIO_1_7=0;break;
		}
}
/**
  * @brief          关闭led
  * @param[in]      number：要关闭的led
  * @retval         NULL
  */
static void led_off(int number)
{
	  switch(number)
		{
			case 1:GPIO_1_0=1;break;
			case 2:GPIO_1_1=1;break;
			case 3:GPIO_1_2=1;break;
			case 4:GPIO_1_3=1;break;
			case 5:GPIO_1_4=1;break;
			case 6:GPIO_1_5=1;break;
			case 7:GPIO_1_6=1;break;
			case 8:GPIO_1_7=1;break;
		}
	
}
	
/**
  * @brief          让led闪烁
  * @param[in]      number：         要闪烁的led
  *                 interval_time:   闪烁时间间隔 
  *                 time:            闪烁总时间
  *                 注意不要在定时器中断函数内使用
  * @retval         NULL
  */	
 static void led_flicker(int number,int interval_time,int time)reentrant
{
	  int add=0;
	  while(1)
		{
	
			 switch(number)
			{
				case 1:GPIO_1_0=0;break;
				case 2:GPIO_1_1=0;break;
				case 3:GPIO_1_2=0;break;
				case 4:GPIO_1_3=0;break;
				case 5:GPIO_1_4=0;break;
				case 6:GPIO_1_5=0;break;
				case 7:GPIO_1_6=0;break;
				case 8:GPIO_1_7=0;break;
			}

			delayms(interval_time);

			switch(number)
			{
				case 1:GPIO_1_0=1;break;
				case 2:GPIO_1_1=1;break;
				case 3:GPIO_1_2=1;break;
				case 4:GPIO_1_3=1;break;
				case 5:GPIO_1_4=1;break;
				case 6:GPIO_1_5=1;break;
				case 7:GPIO_1_6=1;break;
				case 8:GPIO_1_7=1;break;
			}

			delayms(interval_time);
			add++;
			if(interval_time*add>=time&&time!=0)
			{
				break;
			}
	}
		

		
}
/**
  * @brief          让多个led闪烁
  * @param[in]      arr：            要闪烁的led数组（1-8）
  *                 interval_time:   闪烁时间间隔 
  *                 time:            闪烁总时间
  *                 注意不要在定时器中断函数内使用
  * @retval         NULL
  */
static void leds_flicker(int *arr,int interval_time,int time)reentrant
{
		int i=0;
		int add=0;
		int led1=0;
		int led2=0;
		int led3=0;
		int led4=0;
		int led5=0;
		int led6=0;
		int led7=0;
		int led8=0;

		for(i=0;i<8;i++)
		{
			switch(arr[i])
			{
				case LED1:led1++;break;
				case LED2:led2++;break;
				case LED3:led3++;break;
				case LED4:led4++;break;
				case LED5:led5++;break;
				case LED6:led6++;break;
				case LED7:led7++;break;
				case LED8:led8++;break;
			
			}
		}	
		while(1)
		{
			if(led1)
			{
				GPIO_1_0=0;
			}
			if(led2)
			{
				GPIO_1_1=0;
			}
			if(led3)
			{
				GPIO_1_2=0;
			}
			if(led4)
			{
				GPIO_1_3=0;
			}
			if(led5)
			{
				GPIO_1_4=0;
			}
			if(led6)
			{
				GPIO_1_5=0;
			}
			if(led7)
			{
				GPIO_1_6=0;
			}
			if(led8)
			{
				GPIO_1_7=0;
			}
			delayms(interval_time);
				if(led1)
			{
				GPIO_1_0=1;
			}
			if(led2)
			{
				GPIO_1_1=1;
			}
			if(led3)
			{
				GPIO_1_2=1;
			}
			if(led4)
			{
				GPIO_1_3=1;
			}
			if(led5)
			{
				GPIO_1_4=1;
			}
			if(led6)
			{
				GPIO_1_5=1;
			}
			if(led7)
			{
				GPIO_1_6=1;
			}
			if(led8)
			{
				GPIO_1_7=1;
			}
			delayms(interval_time);
			add=add+1;
			if(interval_time*add>=time&&time!=0)
			{
				break;
			}
	}
	
}
/**
  * @brief          关闭所有led
  * @param[in]      NULL
  * @retval         NULL
  */
static void led_all_off(void)
{
	    GPIO_1_0=1;
			GPIO_1_1=1;
			GPIO_1_2=1;
			GPIO_1_3=1;
			GPIO_1_4=1;
			GPIO_1_5=1;
			GPIO_1_6=1;
			GPIO_1_7=1;
}
#endif
	

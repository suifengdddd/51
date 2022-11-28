#include "STC51.h"
//注意在这个文件下添加代码请在BEGIN和END之间否则下次生成代码时会被清除
/* USER CODE BEGIN 1 Includes */
/********用户自定义头文件*********/
#define SHOW_TEMP 1
#define SHOW_ALARM_TEMP 0
/* USER CODE END 1 Includes */

//创建定时器对象
create_time c51_time;
//创建按键对象
create_key c51_key;
//创建led对象
create_led c51_led;
//创建嗡鸣器对象
create_beep c51_beep;
//创建数码管对象
create_nixie_tube c51_nixie_tube;
//创建串口对象
create_usart c51_usart;
//创建ds18b20对象
create_temp c51_ds18b20;

/* USER CODE BEGIN PV */
/********用户自定义变量*********/
 int flag=SHOW_TEMP;
 int tepm_c=280;
 int arr[6]={0};
 unsigned char alarm_data[5]={'2','8','.','0'};
/* USER CODE END PV */

void main()
{
    //实例化led对象
    led_init(&c51_led);
    //实例化按键对象
    key_init(&c51_key);
    //实例化嗡鸣器对象
    beep_init(&c51_beep);
    //实例化数码管对象
    nixie_tube_init(&c51_nixie_tube);
    //实例化定时器对象
    //打开定时器0
    c51_time.time0=TIME0ON;
   //设置定时器0的中断周期
    c51_time.time0_ms=50;
   //关闭定时器1
    c51_time.time1=TIME1OFF;
   //设置定时器1的中断周期
    c51_time.time1_ms=50;
    c51_time.time_type=0;
    time_init(&c51_time);

    //实例化串口对象
    c51_usart.baud_rate=9600;
    usart_init(&c51_usart);

    //实例化ds18b20对象
    temp_init(&c51_ds18b20);

     all_delay();
    /* USER CODE BEGIN 2 Init */
    /********用户代码初始化*********/

    /* USER CODE END 2 Init */
		while(1)
		{
        /* USER CODE BEGIN 3 While */
        /********用户代码实现*********/
				//开始温度转换
				c51_ds18b20.begin_temp_change();
				//读取ds18b20温度
				c51_ds18b20.get_temp(&c51_ds18b20);
				//判断有无按键被按下
				c51_key.key_val=c51_key.whitch_key_down();
				//警报值加0.5摄氏度
				if(c51_key.key_val==KEY3)
				{
					tepm_c=tepm_c+5;
					c51_key.key_val=0;
			
				}
				//警报值减0.5摄氏度
				else if(c51_key.key_val==KEY4)
				{
					tepm_c=tepm_c-5;
					c51_key.key_val=0;
					
					
				}
				//切换数码管显示
				else if(c51_key.key_val==KEY2)
				{
					flag=~flag;
					c51_key.key_val=0;
				}
				//保存温度报警值
				else if(c51_key.key_val==KEY5)
				{
					c51_ds18b20.temp_max=tepm_c;
					c51_key.key_val=0;
					
				}
				//显示温度
				if(flag==SHOW_TEMP)
				{
					arr[0]=c51_ds18b20.temp/100%10;
					arr[1]=c51_ds18b20.temp/10%10;
					arr[2]=c51_ds18b20.temp/1%10;
				}
				//显示报警温度
				else 
				{
					 arr[0]=tepm_c/100%10;
					arr[1]=tepm_c/10%10;
					arr[2]=tepm_c/1%10;
					 
				}
				
					if(c51_ds18b20.temp<=c51_ds18b20.temp_max)
					{
						GPIO_1_0=1;
						BEEP_GPIO=1;
					}
					//填充串口发送数组
					alarm_data[0]=(c51_ds18b20.temp/100%10)+'0';
					alarm_data[1]=(c51_ds18b20.temp/10%10)+'0';
					alarm_data[3]=(c51_ds18b20.temp/1%10)+'0';
					//数码管显示
					c51_nixie_tube.dynamic_display(1,3,arr);
       		 	/* USER CODE END 3 While */
		}
}




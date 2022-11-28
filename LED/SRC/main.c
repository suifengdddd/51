#include "STC51.h"
#if LED_
create_led c51_led;
#endif
main()
{
	
    int i,j,k;
    
	  #if LED_
	  int arr[8]={LED1,LED2,LED3,LED4,LED5,LED6,LED7,LED8};
		int arr1[8]={LED1,0,LED3,0,LED5,0,LED7,0};
		int arr2[8]={0,LED2,0,LED4,0,LED6,0,LED8};
		int *arr_list[2]={arr1,arr2};
		
	  led_init(&c51_led);
	 

    
	while(1)
	{
	
       //从左到右依次点亮，间隔200ms
		   for(i=1;i<=8;i++)
		   {
				  c51_led.led_on(i);
				  delayms(200);
			 }
			 c51_led.led_all_off();
			 delayms(2000);
			 
			 
			 //从右到左依次点亮，间隔200ms
			  for(i=8;i>=1;i--)
		   {
				  c51_led.led_on(i);
				  delayms(200);
			 }
			 c51_led.led_all_off();
			 delayms(2000);
			 
			 
			 //从中间到两边依次点亮三次，间隔200ms
			 for(i=0;i<=2;i++)
			 {
				  for(j=4,k=5;j>=1;j--,k++)
				 {
					 c51_led.led_on(j);
					 c51_led.led_on(k);
				   delayms(200);
				 }
				 c51_led.led_all_off();
			 }
			 delayms(2000);
			 
			 
			 //从两边到中间依次点亮三次，间隔200ms
			 for(i=0;i<=2;i++)
			 {
				  for(j=1,k=8;j<=4;j++,k--)
				 {
					 c51_led.led_on(j);
					 c51_led.led_on(k);
				   delayms(200);
					 
				 }
				 c51_led.led_all_off();
			 }
			 delayms(2000);
			 
			 //全亮全灭三次
			 for(i=0;i<=2;i++)
			 {
			   c51_led.leds_flicker(arr,200,400);
			 }
			 
			  c51_led.led_all_off();
			 delayms(2000);
			 
			 //第一个灯闪烁1次，第二个灯闪烁2次，依次类推。
			 for(i=1;i<=8;i++)
			 {
				  c51_led.led_flicker(i,200,i*200); 
			 }
			 
			  c51_led.led_all_off();
			 delayms(2000);
			 
			 //1 3 5 7    2 4 6 8交叉亮 
			 for(i=0;i<=2;i++)
			 {
				 for(j=0;j<=1;j++)
				 {
			      c51_led.leds_flicker(arr_list[j],200,400);
				 }
				  c51_led.led_all_off();
			 }
			  c51_led.led_all_off();
			  delayms(2000);
			 
			 

	}
		
	
}


//#include "STC51.h"
//void led_test(void)
//{
//		int i;
//	  int led_control_arr1[8]={OFF,LED2,OFF,LED4,OFF,LED6,OFF,LED8};
//		int led_control_arr2[8]={LED1,OFF,LED3,OFF,LED5,OFF,LED7,OFF};
//		int *led_control_arr[2]={led_control_arr1,led_control_arr2};
//		create_led c51_led;
//		led_init(&c51_led);
//		c51_led.led_all_off();
//		for(i=1;i<=8;i++)
//		{
//			  c51_led.led_on(i);
//			  delayms(500);
//		}
//		for(i=8;i>=1;i--)
//		{
//			  c51_led.led_off(i);
//			  delayms(500);
//		}
//		c51_led.led_all_off();
//		delayms(1500);
//		for(i=1;i<=8;i++)
//		{
//			  c51_led.led_flicker(i,100,200);
//			  delayms(200);
//		}
//		c51_led.led_all_off();
//		  delayms(1500);
//		for(i=1;i>=0;i--)
//		{
//	    c51_led.leds_flicker(led_control_arr[i],100,2000);
//		}
//	}	
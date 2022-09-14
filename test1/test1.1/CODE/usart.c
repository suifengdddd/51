#include "usart.h"
#if USART
static void my_printf(char*s);

void usart_init(create_usart *object)
{
	   unsigned short i=0;
	   for(i=0;i<USART_REC_LEN;i++)
	{
		  object->USART_RX_BUF[i]=0;
	}
     object->my_printf=my_printf;
	   object->usart_rx_func_handle=usart_rx_func_handle;
	   object->USART_RX_STA=0;
	  
#if TIME_	 
	  if(c51_time.time1==TIME1ON)
		{
			  ET1=0;
			  c51_time.time1=TIME1OFF;
			 
		}
#endif
		 TMOD=TMOD &(~(0x3<<4)) | (0x2<<4);
		 TH1=256-(28800/object->baud_rate);
		 TH1=256-(28800/object->baud_rate);
		 TR1=1;
		 SM0=0;
		 SM1=1;
		 REN=1;
		 EA=1;
		 ES=1;
		 PCON=0x80;
		 
		 
}
static void my_printf(char*s)
{
	printf("%s\n",s);
}
void _uasrt_interrupt() interrupt 4
{
	c51_usart.usart_rx_func_handle();
}
#endif
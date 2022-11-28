#include "usart.h"
#if USART
static void send_data(char*s,uint8 number);

void usart_init(create_usart *object)
{
	   unsigned short i=0;
	   for(i=0;i<USART_REC_LEN;i++)
	{
		  object->USART_RX_BUF[i]=0;
	}
     object->send_data=send_data;
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
		 TL1=256-(28800/object->baud_rate);
		 TR1=1;
		 SM0=0;
		 SM1=1;
		 REN=1;
		 EA=1;
		 ES=1;
	
		 
		 
}
static void send_data(char*s,uint8 number)
{
	  uint8 i;
	  ES=0;
	  for(i=0;i<number;i++)
		{
			SBUF=s[i];
			while(!TI);
			TI=0;
			
		}
		ES=1;
}
void _uasrt_interrupt() interrupt 4
{
	RI=0;
	c51_usart.usart_rx_func_handle();
}
#endif
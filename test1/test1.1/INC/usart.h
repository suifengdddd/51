#ifndef USART_H
#define USART_H
#include "STC51.h"
//串口还不能使用
#if USART
#define USART_REC_LEN  			15	//定义最大接收字节数 200
typedef struct my_usart
{ 
	 //定时器发送函数
	 void  (*my_printf)(char*s);
	 //定时器接收中断回调函数函数
	 void  (*usart_rx_func_handle)(void);
	 //波特率
	 int    baud_rate;
	 unsigned   short  USART_RX_STA;
	 unsigned char USART_RX_BUF[USART_REC_LEN]; 
}create_usart;
void usart_init(create_usart*object);
void usart_rx_func_handle (void);
extern create_usart c51_usart;
#endif
#endif

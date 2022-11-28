#include "usart.h"
//串口接收中断回调函数
void usart_rx_func_handle (void)
{
	 c51_usart.USART_RX_BUF[c51_usart.USART_RX_STA]=SBUF;
	 if(c51_usart.USART_RX_STA<USART_REC_LEN)
	 {
			c51_usart.USART_RX_STA++;
	 }
}
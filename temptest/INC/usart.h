#ifndef USART_H
#define USART_H
#include "STC51.h"
//���ڻ�����ʹ��
#if USART
#define USART_REC_LEN  			15	//�����������ֽ��� 200
typedef struct my_usart
{ 
	 //��ʱ�����ͺ���
	 void  (*my_printf)(char*s);
	 //��ʱ�������жϻص���������
	 void  (*usart_rx_func_handle)(void);
	 //������
	 int    baud_rate;
	 unsigned   short  USART_RX_STA;
	 unsigned char USART_RX_BUF[USART_REC_LEN]; 
}create_usart;
void usart_init(create_usart*object);
void usart_rx_func_handle (void);
extern create_usart c51_usart;
#endif
#endif

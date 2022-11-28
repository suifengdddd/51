#ifndef USART_H
#define USART_H
#include "STC51.h"
//���ڻ�����ʹ��
#if USART
#define USART_REC_LEN  			15	//�����������ֽ��� 15
typedef struct my_usart
{ 
	 //��ʱ�����ͺ���
	 void  (*send_data)(char*s,uint8 number);
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

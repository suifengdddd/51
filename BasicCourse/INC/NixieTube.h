#ifndef NIXIETUBE_H
#define NIXIETUBE_H
#include "STC51.h"
#if SMG_
#if _C51==1
sbit U1=P2^6;//��ѡ
sbit U2=P2^7;//λѡ
#else
sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;
#endif

typedef struct my_nixie_tube
{
	/**
  * @brief          ��̬��ʾ����
  * @param[in]      location��Ҫ��ʾ�������λ�ã�1-6��
  *                 number����ʾ������
  * @retval         NULL
  */
	 void(*show_number)(int location,int number);
	/**
  * @brief          ��̬��ʾ����
  * @param[in]      begin_location���������ʼ
  *                 over_location�� ����ܽ���  
  *                 arr������ָ�룺Ҫ��ʾ�����������
	*                 ע��˺�����Ҫ�ڶ�ʱ���ж���ʹ��
  * @retval         NULL
  */
	 void(*dynamic_display)(int begin_location,int over_location,int *arr)reentrant;
	 int  arr[6];
}create_nixie_tube; 
/**
  * @brief          ��ʼ������ܶ���
  * @param[in]      object������ܶ���ָ��
  * @retval         NULL
  */
void nixie_tube_init(create_nixie_tube *object);
extern create_nixie_tube c51_nixie_tube;
#endif
#endif

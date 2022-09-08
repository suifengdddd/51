#ifndef NIXIETUBE_H
#define NIXIETUBE_H
#include "STC51.h"
#if SMG_
#if _C51==1
sbit U1=P2^6;//段选
sbit U2=P2^7;//位选
#else
sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;
#endif

typedef struct my_nixie_tube
{
	/**
  * @brief          静态显示数字
  * @param[in]      location：要显示的数码管位置（1-6）
  *                 number：显示的数字
  * @retval         NULL
  */
	 void(*show_number)(int location,int number);
	/**
  * @brief          动态显示数字
  * @param[in]      begin_location：数码管起始
  *                 over_location： 数码管结束  
  *                 arr：数组指针：要显示的数组放这里
	*                 注意此函数不要在定时器中断里使用
  * @retval         NULL
  */
	 void(*dynamic_display)(int begin_location,int over_location,int *arr)reentrant;
	 int  arr[6];
}create_nixie_tube; 
/**
  * @brief          初始化数码管对象
  * @param[in]      object：数码管对象指针
  * @retval         NULL
  */
void nixie_tube_init(create_nixie_tube *object);
extern create_nixie_tube c51_nixie_tube;
#endif
#endif

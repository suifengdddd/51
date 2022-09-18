#ifndef STC51_H
#define STC51_H
//1为天翔单片机
//0普中单片机
#define STC51   1
#if STC51
#define _C51    1
#else
#define _C51    2
#endif
#define uint8  unsigned char 	
#define uint16 unsigned int 
//对应为1 打开相应外设（串口不能用）
#define TIME_   1    //26
#define USART   0   //52
#define BEEP_   1   //18
#define KEY_    1   //6
#define SMG_    1   //19
#define LED_    0   //22
#define DS18B20_ 1

#include <reg52.h>
#include <intrins.h>
#include <stdio.h>
#include "Delay.h"
#include "LED.h"
#include "KEY.h"
#include "BEEP.h"
#include "NixieTube.h"
#include "Time.h"
#include "usart.h"
#include "Ds18b20.h"


#endif
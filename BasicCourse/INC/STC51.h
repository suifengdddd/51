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
//对应为1 打开相应外设（串口不能用）
#define TIME_   1    //26 8 
#define USART   0   //52  8
#define BEEP_   1   //18 1
#define KEY_    1   //6  1
#define SMG_    1   //19 2
#define LED_    1   //22 5

#include <reg52.h>
#include "Delay.h"
#include "LED.h"
#include "KEY.h"
#include "BEEP.h"
#include "NixieTube.h"
#include "Time.h"
#include "usart.h"
#endif
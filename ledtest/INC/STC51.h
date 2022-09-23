#ifndef STC51_H
#define STC51_H
//1为天翔单片机
//0普中单片机
#define STC51   1
#define OPEN    1
#define CLOSE   0
#if STC51
#define _C51    1
#else
#define _C51    2
#endif
//对应为1 打开相应外设（串口不能用）
#define TIME_   			OPEN    //定时器
#define USART   			CLOSE   //串口
#define BEEP_   			CLOSE   //嗡鸣器
#define KEY_    			OPEN    //按键
#define SMG_    			OPEN    //数码管
#define LED_     			OPEN    //led
#define DS18B20_ 			CLOSE   //DS18b20
#define LCD1602_ 			CLOSE   //LCD1602

typedef unsigned int uint16;
typedef unsigned char uint8;
#include <reg52.h>
#include <stdio.h>
#include "Delay.h"
#include "LED.h"
#include "KEY.h"
#include "BEEP.h"
#include "NixieTube.h"
#include "Time.h"
#include "usart.h"
#include "Lcd1602.h"
#include "Ds18b20.h"
#endif
#ifndef STC51_H
#define STC51_H
//1为天翔单片机
//0普中单片机
//注意：LCD1602,Ds18b20,ADC未对普中单片机适配
#define STC51   1
#if STC51
#define _C51    1
#else
#define _C51    2
#endif
#define CLOSE  0
#define OPEN   1
#define LED_       CLOSE
#define KEY_       CLOSE//6
#define SMG_       CLOSE
#define BEEP_      CLOSE
#define TIME_      CLOSE
#define USART      CLOSE
#define DS18B20_   CLOSE
#define LCD1602_   CLOSE
#define ADC_       CLOSE
//对应为1 打开相应外设
typedef unsigned int uint16;
typedef unsigned char uint8;
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
#include "Lcd1602.h"
#include "Ds18b20.h"
#include "adc.h"
#include "ADC0804.h"
#endif
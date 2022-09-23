#ifndef STC51_H
#define STC51_H
//1Ϊ���赥Ƭ��
//0���е�Ƭ��
#define STC51   1
#define OPEN    1
#define CLOSE   0
#if STC51
#define _C51    1
#else
#define _C51    2
#endif
//��ӦΪ1 ����Ӧ���裨���ڲ����ã�
#define TIME_   			OPEN    //��ʱ��
#define USART   			CLOSE   //����
#define BEEP_   			CLOSE   //������
#define KEY_    			OPEN    //����
#define SMG_    			OPEN    //�����
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
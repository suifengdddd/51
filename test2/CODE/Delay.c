#include "Delay.h"
void delay1ms(void)   //Îó²î 0us
{
    unsigned char a,b,c;
    for(c=1;c>0;c--)
        for(b=142;b>0;b--)
            for(a=2;a>0;a--);
}
void delayx10us(int number)
{
	while(number--)
	{
		delay10us();
	}
}
void delayms(int number)
{
	while(number--)
	{
		delay1ms();
	}
}

void delay10us(void)   //Îó²î 0us
{
    unsigned char a,b;
    for(b=1;b>0;b--)
        for(a=2;a>0;a--);
}


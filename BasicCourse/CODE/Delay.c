#include "Delay.h"
void delay1ms(void)   //Îó²î 0us
{
    unsigned char a,b,c;
    for(c=1;c>0;c--)
        for(b=142;b>0;b--)
            for(a=2;a>0;a--);
}
void delayms(uint16 number)
{
	while(number--)
	{
		delay1ms();
	}
}
void delay(uint16 number)
{
	uint16 x,y;
	for(x=number;x>0;x--)
		for(y=110;y>0;y--);
}
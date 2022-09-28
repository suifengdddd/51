#include "Ds18b20.h"
#if DS18B20_
static void ds18b20_init(void);
static bit read_temp_bit(void);
static uint8 read_temp_byte(void);
static void write_temp_byte(uint8 dat);
static void begin_temp_change(void);
static void get_temp(struct my_ds18b20 *temp_object);
static void ds18b20_init(void)
{
	uint8 i=0;
	DS_GPIO=0;
	i=103;
	while(i>0)
	{
		i--;
	}
	DS_GPIO=1;
	i=4;
	while(i>0)
	{
		i--;
	}
}
static bit read_temp_bit(void)
{
	 uint8 i=0;
	 bit dat;
	 DS_GPIO=0;
	 i++;
	 DS_GPIO=1;
	 i++;
	 i++;
	 dat=DS_GPIO;
	 i=8;
	while(i>0)
	{
		i--;
	}
	return dat;
	 
	
	
}

static uint8 read_temp_byte(void)
{
	 uint8 i,j,dat;
	 dat=0;
	for(i=1;i<=8;i++)
	{
		j=read_temp_bit();
		dat=(j<<7)|(dat>>1);
	}
	return dat;
}
static void write_temp_byte(uint8 dat)
{
	 uint16 i;
	 uint8 j;
 	bit testb;
	for(j=1;j<=8;j++)
	{
		 testb=dat &0x01;
		 dat=dat>>1;
		if(testb)
		{
			DS_GPIO=0;
			i++;
			DS_GPIO=1;
			i=8;
			while(i>0)
			{
				i--;
			}
		}
		else
		{
			DS_GPIO=0;
			i=8;
			while(i>0)
			{
				i--;
			}
			DS_GPIO=1;
			i++;
			i++;
			
		}
	}
}
static void begin_temp_change(void)
{
	
		ds18b20_init();
		delayms(1);
	  write_temp_byte(0xcc);
	  write_temp_byte(0x44);
	  
}
static void get_temp(struct my_ds18b20 *temp_object)
{
	uint8 data_L=0,data_H=0;
	uint8 i=0;
	float f_temp=0;
	ds18b20_init();
	delayms(1);
	write_temp_byte(0xcc);
	write_temp_byte(0xbe);
	data_L=read_temp_byte();
	data_H=read_temp_byte();
	temp_object->temp=data_H;
	temp_object->temp=temp_object->temp<<8;
	temp_object->temp=temp_object->temp|data_L;
	f_temp=	temp_object->temp*0.0625;
	temp_object->temp=f_temp*10+0.5;
	
	
}
void temp_init(create_temp *temp_object)
{
	temp_object->temp=0;
	temp_object->temp_max=280;
	temp_object->temp_mix=260;
	temp_object->begin_temp_change=begin_temp_change;
	temp_object->get_temp=get_temp;
	
	
}
#endif

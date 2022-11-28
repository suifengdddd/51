#ifndef DS18B200_H
#define DS18B200_H
#include "STC51.h"
#if DS18B20_
sbit DS_GPIO =P2^2;
typedef struct my_ds18b20
{
	 uint16 temp;
	 uint16 temp_max;
	 uint16 temp_mix;
	 void (*begin_temp_change)(void);
   void (*get_temp)(struct my_ds18b20 *temp_object);
}create_temp;
void temp_init(create_temp *temp_object);
extern create_temp c51_ds18b20;
#endif

#endif

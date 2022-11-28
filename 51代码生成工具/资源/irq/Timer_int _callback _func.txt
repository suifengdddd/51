#include "Time.h"
//定时器中断回调函数
void time_run_func_handle(void)reentrant
{
	 static int time0_i=0;
	 static int time1_i=0;
	 //定时器0中断有关请写在这里
	if(c51_time.time_type==TIME0)
	{


	    time0_i++;


	}
	//定时器1中断有关请写在这里
	else if(c51_time.time_type==TIME1)
	{



	   time1_i++;

	}


	c51_time.time_type=0;
}
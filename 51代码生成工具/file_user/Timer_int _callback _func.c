#include "Time.h"
//��ʱ���жϻص�����
void time_run_func_handle(void)reentrant
{
	 static int time0_i=0;
	 static int time1_i=0;
	 //��ʱ��0�ж��й���д������
	if(c51_time.time_type==TIME0)
	{


	    time0_i++;


	}
	//��ʱ��1�ж��й���д������
	else if(c51_time.time_type==TIME1)
	{



	   time1_i++;

	}


	c51_time.time_type=0;
}
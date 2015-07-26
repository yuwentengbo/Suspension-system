#include "copy.h"
#include "math.h"
#include "usart.h"
#include "run.h"
#include "Infrared.h"
#include "delay.h"

my_cur my_cur_data[9*9];
double old_l[81];
double old_r[81];
extern u8 left_run_flag;
extern u8 right_run_flag;
extern int left_step,right_step;
extern int left_time,right_time;
extern u8 tar;
u16 finall_cur[4];
u8 finall_cur_step = 0;
my_cur finall_my_cur_data[4];
void my_scan()
{
	u16 i = 0;
	float x = 0,y = 0;
	double left =0.0,right = 0.0; 
	double left_cha = 0.0,right_cha = 0.0;
	float temp_left,temp_right;
	//1
	x = 0;
	for(i = 0;i <81; i++)
	{
		
		if(i<9)
		{
			y = 0;
			left = sqrt((16.5+x)*(16.5+x)+(55.5+y)*(55.5+y));
			right = sqrt((65.5-x)*(65.5-x)+(55.5+y)*(55.5+y));
			old_l[i] = left;
			old_r[i] = right;
			x++;
			//printf("left %lf right %lf\n",left,right);
			continue;
		}
		else if(i<18)
		{
			y = 1;
			left = sqrt((16.5+x)*(16.5+x)+(55.5-y)*(55.5-y));
			right = sqrt((65.5-x)*(65.5-x)+(55.5-y)*(55.5-y));
			old_l[i] = left;
			old_r[i] = right;
			x--;
			//printf("left %lf right %lf\n",left,right);
			continue;
		}
		else if(i<27)
		{
			y = 2;
			left = sqrt((16.5+x)*(16.5+x)+(55.5-y)*(55.5-y));
			right = sqrt((65.5-x)*(65.5-x)+(55.5-y)*(55.5-y));
			old_l[i] = left;
			old_r[i] = right;
			x++;
			//printf("left %lf right %lf\n",left,right);
			continue;
		}
		else if(i<36)
		{
			y = 3;
			left = sqrt((16.5+x)*(16.5+x)+(55.5-y)*(55.5-y));
			right = sqrt((65.5-x)*(65.5-x)+(55.5-y)*(55.5-y));
			old_l[i] = left;
			old_r[i] = right;
			x--;
			//printf("left %lf right %lf\n",left,right);
			continue;
		}
		else if(i<45)
		{
			y = 4;
			left = sqrt((16.5+x)*(16.5+x)+(55.5-y)*(55.5-y));
			right = sqrt((65.5-x)*(65.5-x)+(55.5-y)*(55.5-y));
			old_l[i] = left;
			old_r[i] = right;
			x++;
			//printf("left %lf right %lf\n",left,right);
			continue;
		}
		else if(i<54)
		{
			y = 5;
			left = sqrt((16.5+x)*(16.5+x)+(55.5-y)*(55.5-y));
			right = sqrt((65.5-x)*(65.5-x)+(55.5-y)*(55.5-y));
			old_l[i] = left;
			old_r[i] = right;
			x--;
			//printf("left %lf right %lf\n",left,right);
			continue;
		}
		else if(i<63)
		{
			y = 6;
			left = sqrt((16.5+x)*(16.5+x)+(55.5-y)*(55.5-y));
			right = sqrt((65.5-x)*(65.5-x)+(55.5-y)*(55.5-y));
			old_l[i] = left;
			old_r[i] = right;
			x++;
			//printf("left %lf right %lf\n",left,right);
			continue;
		}
		else if(i<72)
		{
			y = 7;
			left = sqrt((16.5+x)*(16.5+x)+(55.5-y)*(55.5-y));
			right = sqrt((65.5-x)*(65.5-x)+(55.5-y)*(55.5-y));
			old_l[i] = left;
			old_r[i] = right;
			x--;
			//printf("left %lf right %lf\n",left,right);
			continue;
		}
		else if(i<81)
		{
			y = 8;
			left = sqrt((16.5+x)*(16.5+x)+(55.5-y)*(55.5-y));
			right = sqrt((65.5-x)*(65.5-x)+(55.5-y)*(55.5-y));
			old_l[i] = left;
			old_r[i] = right;
			x++;
			//printf("left %lf right %lf\n",left,right);
			continue;
		}
	}
	
	for(i=0;i<80;i++)
	{
		
		left_cha = old_l[i+1] - old_l[i];
		right_cha = old_r[i+1] - old_r[i];
		
		if(left_cha > 0)
		{
			left_run_flag = 1;
		}
		else if(left_cha < 0)
		{
			left_run_flag = 0; 
		}
		
		if(right_cha > 0)
		{
			right_run_flag = 0;
		}
		else if(right_cha < 0)
		{
			right_run_flag = 1; 
		}
		
		left_cha = fabs(left_cha);
		right_cha = fabs(right_cha);
		printf("left cha %lf  right cha %lf   ",left_cha,right_cha);
		
		/*if(left_cha < 0.2 || right_cha < 0.2)
		{
			
		}*/
		
		left_step = (int)((left_cha*100.00)/(STEP_LEN*100.00));
		right_step = (int)((right_cha*100.00)/(STEP_LEN*100.00));
		printf("left_step %d  right_step %d   ",left_step,right_step);
		
		if(left_step > right_step)
		{
			temp_left = 10;
			temp_right = (int)(left_step * 10.0)/(right_step*1.0);
		}
		else
		{
			temp_right = 10;
			temp_left = (int)(right_step * 10.0)/(left_step*1.0);
		}
		
		left_time = (int)((temp_left));
		right_time = (int)((temp_right));
		
		printf("left_time %d  right_time %d  \n",left_time,right_time);
		tar = 0;
		TIM_Cmd(TIM2,ENABLE);
		TIM_Cmd(TIM3,ENABLE);
		while(1)
		{
			if(tar == 2)
			{
				tar = 0;
				break;
			}
		}
		get_infrared_value(i,i%9,i/9);
		delay_ms(500);

	}
}

void get_infrared_value(int cur,int x,int y)
{
	u16 i =0;
	float value = 0.0;
MY_STEP1:
	value = 0.0;	
	for(i = 0;i < 10 ;i++)
	{
		value += Infrared_scan();
		delay_ms(10);
	}
	value = value/(10*1.0);
	if(value > 0.7)
	{
		my_cur_data[cur].x = x;
		my_cur_data[cur].y = y;
	}
	else if(value < 0.3)
	{
		my_cur_data[cur].x = -1;
		my_cur_data[cur].y = -1;
	}
	else
	{
		goto MY_STEP1;
	}
}

void get_line()
{
	u16 i,j,k;
	u8 cnt = 0;
	u8 line_cnt = 0;
	
	for(i = 0; i < 9; i++)		//hang scan
	{
		cnt = 0;
		for(j = 0; j< 9;j++)
		{
			if(my_cur_data[i*9+j].x != -1)
			{
				cnt ++;
			}
		}
		
		if(cnt > 2)
		{
			line_cnt++;
			for(k = 0;k < 9;k++)
			{
				if(my_cur_data[k*9+j].x != -1)
				{
					finall_cur[finall_cur_step ]= k*9+j;
					break;
				}
			}
			for(k = 8;k >= 0;k--)
			{
				if(my_cur_data[k*9+j].x != -1)
				{
					finall_cur[finall_cur_step ]= k*9+j;
					break;
				}
			}
			finall_cur_step ++;
		}
	}
	
	for(i = 0; i < 9; i++)		//lie scan
	{
		cnt = 0;
		for(j = 0; j< 9;j++)
		{
			if(my_cur_data[i+j*9].x != -1)
			{
				cnt ++;
			}
		}
		
		if(cnt > 2)
		{
			line_cnt++;
			for(k = 0;k < 9;k++)
			{
				if(my_cur_data[i+k*9].x != -1)
				{
					finall_cur[finall_cur_step ]=i+k*9;
					break;
				}
			}
			for(k = 8;k >= 0;k--)
			{
				if(my_cur_data[i+k*9].x != -1)
				{
					finall_cur[finall_cur_step ]= i+k*9;
					break;
				}
			}
			finall_cur_step ++;
		}
	}
	while(1)
	{
		if(line_cnt == 3)
		{
			break;
		}
	}
	
}

void cal_cur(my_cur *finall_my_cur_data)
{
	u8 i;
	for(i = 0;i < 4; i++)
	{
		(*finall_my_cur_data).x = finall_cur[i]%9;
		(*finall_my_cur_data).y = finall_cur[i]/9;
	}
	
	
}
void my_copy()
{
	
}
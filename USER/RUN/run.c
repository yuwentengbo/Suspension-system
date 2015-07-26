#include "run.h"
#include "usart.h"
#include "math.h"
#include "delay.h"
#include "uart_1602.h"
#include "matrix_key.h"
#include "copy.h"

#define OLD_L  58.2
#define OLD_R  86.56

extern u8 tar;
u8 show_cont[] = "please input cur";
u8 err_cont[] = "error cur";
void getXY_cur(float *x,float *y);
void goto_cur(float x,float y);
void draw_line(float x, float y);
void draw_cirle(float x, float y);


void run1()
{
	float x = 0.0, y = 0.0;
	getXY_cur(&x,&y);
	printf("%f  %f",x*1.0,y*1.0);
	goto_cur(x,y);
	while(1)
	{
		if(tar == 2)
		{
			tar = 0;
			break;
		}
	}
	x = 10.0;
	y = 10.0;
	delay_ms(3000);
	draw_line(x,y);
	delay_ms(3000);
}


void run2()
{
	draw_cirle(25.0, 20.0);
	delay_ms(3000);
}


void run3()
{
	 my_scan();
}

void getXY_cur(float *x,float *y)
{
	u8 i,j,k,flag = 0;
	u8 key_value = 0;
	u8 show_postion = 0;
	u8 value[2];
MY_STEP:
	clearLCD();
	for(i=0;i<16; i++)
		UART_Write(show_cont[i]);
	UART_Write('x');
	UART_Write(':');
	lcdPosition(1, 8);
	UART_Write('y');
	UART_Write(':');

	for(k = 0; k < 2;k ++)
	{
		for(i = 0;i < 2;i ++)
		{
			while(1)
			{
				key_value = MATRIX_KEY_Scan();
				if(key_value)	break;
			}
			if(0 < key_value && key_value < 11)
			{
				if(flag == 0)
				{
					show_postion = 3+i;
				}
				else
				{
					show_postion = 10+i;
				}
				lcdPosition(1, show_postion);
				if(key_value == 10)
				{
					key_value = 0;
				}
				UART_Write(key_value + '0');
				value[i] = key_value;
			}
			else
			{
				clearLCD();
				for(j=0;j<9;j++)
				UART_Write(err_cont[j]);
				key_value = 0;
				i = 0;
				j = 0;
				flag = 0;
				value[0] = 0;
				value [1] = 0;
				delay_ms(1000);
				goto MY_STEP;
			}
			key_value = 0;
		}
		if(flag == 0)
		{
			*x = value[0]*10+value[1];
		}
		else
		{
			*y = value[0]*10+value[1];
		}
		flag ++;
	}
	
	while(1)
	{
		key_value = MATRIX_KEY_Scan();
		if(key_value == MATRIX_KEYOK_PRES)	break;
	}

}
int left_step = 0, right_step = 0;
u8 right_run_flag = 0,left_run_flag = 0;
int right_time = 0,left_time = 0;

void goto_cur(float x,float y)
{
	float temp_left,temp_right;
	double left_len = 0.0,right_len = 0.0;
	double left_cha = 0.0,right_cha = 0.0;
	
	left_len = (double)sqrt((x+16)*(x+16)+(56-y)*(56-y));
	right_len = (double)sqrt((66-x)*(66-x)+(56-y)*(56-y));
	//printf("%lf  %lf",left_len,right_len);
	//printf("%f",STEP_LEN);
	
	left_cha = OLD_L - left_len;
	right_cha = OLD_R - right_len;
	
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
	//printf("%lf  %lf",left_cha,right_cha);
	
	left_step = (int)left_cha/STEP_LEN;
	right_step = (int)right_cha /STEP_LEN;
	//printf("left_step %d  right_step %d",left_step,right_step);
	
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
	
	//printf("left_time %d  right_time %d",left_time,right_time);
	TIM_Cmd(TIM2,ENABLE);
	TIM_Cmd(TIM3,ENABLE);
}


double old_left1 = 0.0,old_right1 = 0;

void draw_line(float x1, float y1)			//draw line y=y1
{
	u8 i;
	double old_left = 0.0,old_right = 0.0;
	double now_left = 0.0,now_right = 0.0;
	double left_cha = 0.0,right_cha = 0.0;
	double temp_left = 0.0,temp_right = 0.0;
	double x,y;
	
	old_left = (double)sqrt((x1+16)*(x1+16)+(56-y1)*(56-y1));
	old_right =(double)sqrt((66-x1)*(66-x1)+(56-y1)*(56-y1));
	
	x = x1;
	y = y1;
	
	for(i = 0; i < 50;i ++)
	{
		x = x +0.4;
		y = y1;
		
		now_left = (double)sqrt((x+16)*(x+16)+(56-y)*(56-y));
		now_right =(double)sqrt((66-x)*(66-x)+(56-y)*(56-y));
		
		left_cha = old_left - now_left;
		right_cha = old_right - now_right;
		
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
		//printf("%lf  %lf",old_left,old_right);
		printf("%lf  %lf",left_cha,right_cha);
		
		left_step = (int)((left_cha/STEP_LEN)*1.0);
		right_step = (int)((right_cha /STEP_LEN)*1.0);
		printf("left_step %d  right_step %d",left_step,right_step);
		
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
		
		printf("left_time %d  right_time %d",left_time,right_time);
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
		
		old_left = now_left;
		old_right = now_right;
	}
	old_left1 = old_right;
	old_right1 = old_right;
	
}

void draw_cirle(float x1, float y1)
{
	
	u16 i;
	double old_left = 0.0,old_right = 0.0;
	double now_left = 0.0,now_right = 0.0;
	double left_cha = 0.0,right_cha = 0.0;
	double temp_left = 0.0,temp_right = 0.0;
	double x,y;
	double cul = 0.0;
	
	printf("nihao");
	x = x1 - 15;
	y = y1;
	
	old_left = (double)sqrt((x+16)*(x+16)+(56-y)*(56-y));
	old_right =(double)sqrt((66-x)*(66-x)+(56-y)*(56-y));
	
	left_cha = old_left1 - old_left;
	right_cha = old_right1 - old_right;
	
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
	//printf("%lf  %lf",left_cha,right_cha);
	
	left_step = (int)left_cha/STEP_LEN;
	right_step = (int)right_cha /STEP_LEN;
	//printf("left_step %d  right_step %d",left_step,right_step);
	
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
	
	//printf("left_time %d  right_time %d",left_time,right_time);
	TIM_Cmd(TIM2,ENABLE);
	TIM_Cmd(TIM3,ENABLE);
	
	old_left = old_left1;
	old_right = old_right1;
	//while(1);
	
	
	for(; x < 40 ;)
	{
		if(x < 13 || x>37)
		{
			cul = 1.0;
		}
		else if(x < 17 || x > 33)
		{
			cul = 2.0;
		}
		else
		{
			cul = 3.0;
		}
		x = x +cul;
		y = sqrt(((15*15)-((x-25)*(x-25))));
		y = y + 20;
		
		now_left = (double)sqrt((x+16)*(x+16)+(56-y)*(56-y));
		now_right =(double)sqrt((66-x)*(66-x)+(56-y)*(56-y));
		
		left_cha = old_left - now_left;
		right_cha = old_right - now_right;
		
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
		//printf("%lf  %lf",old_left,old_right);
		printf("left cha %lf right cha %lf",left_cha,right_cha);
		
		left_step = (int)((left_cha/STEP_LEN)*1.0);
		right_step = (int)((right_cha /STEP_LEN)*1.0);
		printf("left_step %d  right_step %d",left_step,right_step);
		
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
		
		printf("left_time %d  right_time %d\n",left_time,right_time);
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
		
		old_left = now_left;
		old_right = now_right;
	}
	
	x = 40;
	for(; x > 10 ;)
	{
		if(x < 13 || x>37)
		{
			cul = 1.0;
		}
		else if(x < 17 || x > 33)
		{
			cul = 2.0;
		}
		else
		{
			cul = 3.0;
		}
		x = x -cul;
		y = sqrt(((15*15)-((x-25)*(x-25))));
		y = 20 -y;
		
		now_left = (double)sqrt((x+16)*(x+16)+(56-y)*(56-y));
		now_right =(double)sqrt((66-x)*(66-x)+(56-y)*(56-y));
		
		left_cha = old_left - now_left;
		right_cha = old_right - now_right;
		
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
		//printf("%lf  %lf",old_left,old_right);
		printf("left cha %lf right cha %lf",left_cha,right_cha);
		
		left_step = (int)((left_cha/STEP_LEN)*1.0);
		right_step = (int)((right_cha /STEP_LEN)*1.0);
		printf("left_step %d  right_step %d",left_step,right_step);
		
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
		
		printf("left_time %d  right_time %d\n",left_time,right_time);
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
		
		old_left = now_left;
		old_right = now_right;
	}
	
}
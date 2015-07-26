#include "delay.h"
#include "usart.h"
#include "timer.h"
#include "bujin.h"
#include "uart_1602.h"
#include "matrix_key.h"
#include "Infrared.h"
#include "key.h"
#include "run.h"
#include "copy.h"
u8 select_cont[] = "please choose 1,2,3";
int cur_x = 0,cur_y = 0;

void System_init()
{
	NVIC_Configuration();
	delay_init();
	uart_init(9600);
	KEY_Init();
	MATRIX_KEY_Init();
	UART_1602_Init();
	Infrared_Init();
	bujin_init();
	TIM3_Int_Init(9,7199);		//1ms	
}

int main(void)
{	
	u8 key_value = 0;
	int i =0;
	
	System_init();
	
	/*my_scan();
	while(1)
	{
		i = Infrared_scan();
		printf("%d\n",i);
		
		delay_ms(200);
	}
	
	while(key_value == 0)
	{
		key_value = KEY_Scan(0);
		delay_ms(10);
	}
	
	my_scan();
	while(1);
	*/
	while(1)
	{
		clearLCD();
		for(i = 0; i< 19;i ++)
		{
			UART_Write(select_cont[i]);
		}
		while(1)
		{
			key_value = MATRIX_KEY_Scan();
			if(key_value)	break;
		}

		switch(key_value)
		{
			case 1:		run1();		break;			//»­Ö±Ïß
			case 2:		run2();		break;			//»­Ô²
			case 3:		run3();		break;			//¸´ÖÆ
			default:				break;
		}
		
		key_value = 0;
	}

	return 0;
}

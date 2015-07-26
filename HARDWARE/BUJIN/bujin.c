#include "bujin.h"
#include "delay.h"

/*
	步进电机初始化
*/
void bujin_init()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_Init(GPIOC,&GPIO_InitStruct);

}

//left停止
void Bujin_Left_Stop()
{
	PCout(6) = 0; PCout(7) = 0; PCout(8) = 0; PCout(9) = 0;
}

//right停止
void Bujin_Right_Stop()
{
	PAout(4) = 0; PAout(5) = 0; PAout(6) = 0; PAout(7) = 0;
}



	

/*
PC67	一相
PC89
步进角0.9度
flag  正转反转
x	   细分到每一步
*/	

u8 bujin_flag = 0;
void Bujin_Left_Go(u8 x)
{
	switch(x)
	{
			case 0:	PCout(6) = 1;  PCout(7) = 0;  PCout(8) = 0;  PCout(9) = 1;	
					break;
			case 1:	PCout(6) = 0;  PCout(7)  = 0; PCout(8) = 0;  PCout(9) = 1;	
					break;
			case 2:	PCout(6) = 0; PCout(7) = 1;  PCout(8) = 0; PCout(9) = 1;		
					break;
			case 3:	PCout(6) = 0; PCout(7)  = 1; PCout(8) = 0; PCout(9) = 0;	
					break;
			case 4:	PCout(6) = 0; PCout(7)  = 1; PCout(8) = 1; PCout(9) = 0;	
					break;
			case 5:	PCout(6) = 0; PCout(7)  = 0; PCout(8) = 1; PCout(9) = 0;	
					break;
			case 6:	PCout(6) = 1; PCout(7) = 0; PCout(8) = 1; PCout(9) = 0;	
					break;
			case 7:	PCout(6) = 1; PCout(7)  = 0; PCout(8) = 0; PCout(9) = 0;
					break;
	}
	
}

void Bujin_Right_Go(u8 x)
{
	switch(x)
	{
			case 0: PAout(4) = 1;  PAout(5) = 0;  PAout(6) = 0;  PAout(7) = 1;
					break;
			case 1:	PAout(4) = 0;  PAout(5) = 0;  PAout(6) = 0;  PAout(7) = 1;	
					break;
			case 2:	PAout(4)  = 0; PAout(5) = 1; PAout(6) = 0; PAout(7)= 1;
					break;
			case 3:	PAout(4)  = 0; PAout(5) = 1;  PAout(6) = 0; PAout(7) = 0;	
					break;
			case 4: PAout(4)  = 0;  PAout(5) = 1;  PAout(6) = 1; PAout(7) = 0;
					break;
			case 5:	PAout(4) = 0;  PAout(5) = 0;  PAout(6) = 1; PAout(7) = 0;
					break;
			case 6:	PAout(4)  = 1;  PAout(5) = 0;  PAout(6)= 1; PAout(7) = 0;	
					break;
			case 7:	PAout(4)  = 1; PAout(5) = 0;  PAout(6) = 0; PAout(7) = 0;
			break;
	}

}

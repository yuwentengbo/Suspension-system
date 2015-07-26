#include "Infrared.h"

void Infrared_Init(void)
{
	 GPIO_InitTypeDef  GPIO_InitStructure;
		
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PB,PE端口时钟
		
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;	//LED0-->PB.5 端口配置
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 		 
	 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
	 GPIO_ResetBits(GPIOB,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8);						 //PB.5 输出高
		
}

#define INF0 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)
#define INF1 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)
#define INF2 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)
#define INF3 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3)
#define INF4 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)
#define INF5 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)
#define INF6 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)
#define INF7 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)
#define INF8 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)

u16 Infrared_scan()		//meet black return 1
{
	u16 value = 0;
	if(1 == INF0)
	{
		//value |= 0x01;
		value = 1;
	}
	/*if(1 == INF1)
	{
		value |= (0x01<<1);
	}
	if(1 == INF2)
	{
		value |= (0x01<<2);
	}
	if(1 == INF3)
	{
		value |= (0x01<<3);
	}
	if(1 == INF4)
	{
		value |= (0x01<<4);
	}
	if(1 == INF5)
	{
		value |= (0x01<<5);
	}
	if(1 == INF6)
	{
		value |= (0x01<<6);
	}
	if(1 == INF7)
	{
		value |= (0x01<<7);
	}
	if(1 == INF8)
	{
		value |= (0x01<<8);
	}*/
	
	return value;
}



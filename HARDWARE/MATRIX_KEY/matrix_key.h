#ifndef __MYKEY_H
#define __MYKEY_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK miniSTM32开发板
//按键驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/3
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   	 
 

#define MATRIX_KEY0  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0)//读取按键0
#define MATRIX_KEY1  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)//读取按键0
#define MATRIX_KEY2  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6)//读取按键0
#define MATRIX_KEY3(value) if(value) GPIO_SetBits(GPIOC,GPIO_Pin_3); else  GPIO_ResetBits(GPIOC,GPIO_Pin_3);
#define MATRIX_KEY4(value) if(value) GPIO_SetBits(GPIOC,GPIO_Pin_4); else  GPIO_ResetBits(GPIOC,GPIO_Pin_4);
#define MATRIX_KEY5(value) if(value) GPIO_SetBits(GPIOC,GPIO_Pin_5); else  GPIO_ResetBits(GPIOC,GPIO_Pin_5);

#define  MATRIX_KEY1_PRES  1
#define  MATRIX_KEY2_PRES  2
#define  MATRIX_KEY3_PRES  3
#define  MATRIX_KEY4_PRES  4
#define  MATRIX_KEY5_PRES  5
#define  MATRIX_KEY6_PRES  6
#define  MATRIX_KEY7_PRES  7
#define  MATRIX_KEY8_PRES  8
#define  MATRIX_KEY9_PRES  9
#define  MATRIX_KEY0_PRES  10
#define  MATRIX_KEYOK_PRES  11
#define  MATRIX_KEYBACK_PRES  12

void MATRIX_KEY_Init(void);     //IO初始化
u8 MATRIX_KEY_Scan();  	//按键扫描函数					    
#endif

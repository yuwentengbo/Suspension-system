#ifndef __MYKEY_H
#define __MYKEY_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK miniSTM32������
//������������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   	 
 

#define MATRIX_KEY0  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0)//��ȡ����0
#define MATRIX_KEY1  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)//��ȡ����0
#define MATRIX_KEY2  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6)//��ȡ����0
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

void MATRIX_KEY_Init(void);     //IO��ʼ��
u8 MATRIX_KEY_Scan();  	//����ɨ�躯��					    
#endif

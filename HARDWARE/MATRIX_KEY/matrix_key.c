#include "matrix_key.h"
#include "delay.h"
#include "usart.h"

void MATRIX_KEY_Init(void)
{
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_ADC1, ENABLE );	 
 
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   

	                    
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		
	GPIO_Init(GPIOA, &GPIO_InitStructure);	

	ADC_DeInit(ADC1);  

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	
	ADC_InitStructure.ADC_NbrOfChannel = 1;	
	ADC_Init(ADC1, &ADC_InitStructure);	

  
	ADC_Cmd(ADC1, ENABLE);
	
	ADC_ResetCalibration(ADC1);	
	 
	while(ADC_GetResetCalibrationStatus(ADC1));	
	
	ADC_StartCalibration(ADC1);	 
 
	while(ADC_GetCalibrationStatus(ADC1));	 
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_ADC1, ENABLE );	 
 
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   

	                    
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		
	GPIO_Init(GPIOA, &GPIO_InitStructure);	

	ADC_DeInit(ADC1);  

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	
	ADC_InitStructure.ADC_NbrOfChannel = 1;	
	ADC_Init(ADC1, &ADC_InitStructure);	

  
	ADC_Cmd(ADC1, ENABLE);
	
	ADC_ResetCalibration(ADC1);	
	 
	while(ADC_GetResetCalibrationStatus(ADC1));	
	
	ADC_StartCalibration(ADC1);	 
 
	while(ADC_GetCalibrationStatus(ADC1));	///
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_ADC2, ENABLE );	 
 
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   

	                    
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		
	GPIO_Init(GPIOA, &GPIO_InitStructure);	

	ADC_DeInit(ADC2);  

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	
	ADC_InitStructure.ADC_NbrOfChannel = 1;	
	ADC_Init(ADC2, &ADC_InitStructure);	

  
	ADC_Cmd(ADC2, ENABLE);
	
	ADC_ResetCalibration(ADC2);	
	 
	while(ADC_GetResetCalibrationStatus(ADC2));	
	
	ADC_StartCalibration(ADC2);	 
 
	while(ADC_GetCalibrationStatus(ADC2));	/////
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_ADC3, ENABLE );	 
 
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   

	                    
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		
	GPIO_Init(GPIOA, &GPIO_InitStructure);	

	ADC_DeInit(ADC3);  

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	
	ADC_InitStructure.ADC_NbrOfChannel = 1;	
	ADC_Init(ADC3, &ADC_InitStructure);	

  
	ADC_Cmd(ADC3, ENABLE);
	
	ADC_ResetCalibration(ADC3);	
	 
	while(ADC_GetResetCalibrationStatus(ADC3));	
	
	ADC_StartCalibration(ADC3);	 
 
	while(ADC_GetCalibrationStatus(ADC3));	
 
} 

u32 Get_Adc(u8 ch)   
{
  	
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );		  			    
  
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));

	return ADC_GetConversionValue(ADC1);	
}

u32 Get_Adc_Average(u8 ch,u8 times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc(ch);
		delay_ms(4);
	}
	return temp_val/times;
} 	 


u8 MATRIX_KEY_Scan()
{	
	u32 temp = 0;
	float value;
	u8 key_value = 0;
	static u8 key_up =1;
	
	temp = Get_Adc_Average(ADC_Channel_1,5);
	value=(float)temp*(3.3/4096);
	//printf("%f\n",value);
	
	if(value >-0.001 && value < 0.001)
	{
		//return MATRIX_KEY1_PRES;
		key_value = MATRIX_KEY1_PRES;
	}
	else if(value > 1.6 && value < 1.7)
	{
		//return MATRIX_KEY4_PRES;
		key_value = MATRIX_KEY4_PRES;
	}
	else if(value > 1.8 && value < 2.28)
	{
		//return MATRIX_KEY7_PRES;
		key_value = MATRIX_KEY7_PRES;
	}
	else if(value > 2.3 && value < 2.6)
	{
		//return MATRIX_KEY0_PRES;
		key_value = MATRIX_KEY0_PRES;
	}
	
	value = 0;
	temp = 0;
	temp = Get_Adc_Average(ADC_Channel_2,5);
	value=(float)temp*(3.3/4096);
	//printf("%f\n",value);
	
	if(value >-0.001 && value < 0.001)
	{
		//return MATRIX_KEY2_PRES;
		key_value = MATRIX_KEY2_PRES;
	}
	else if(value > 1.6 && value < 1.7)
	{
		//return MATRIX_KEY5_PRES;
		key_value = MATRIX_KEY5_PRES;
	}
	else if(value > 1.8 && value < 2.28)
	{
		//return MATRIX_KEY8_PRES;
		key_value = MATRIX_KEY8_PRES;
	}
	else if(value > 2.3 && value < 2.6)
	{
		//return MATRIX_KEYOK_PRES;
		key_value = MATRIX_KEYOK_PRES;
	}
	
	value = 0;
	temp = 0;
	temp = Get_Adc_Average(ADC_Channel_3,5);
	value=(float)temp*(3.3/4096);
	//printf("%f\n",value);
	
	if(value >-0.001 && value < 0.001)
	{
		//return MATRIX_KEY3_PRES;
		key_value = MATRIX_KEY3_PRES;
	}
	else if(value > 1.6 && value < 1.7)
	{
		//return MATRIX_KEY6_PRES;
		key_value = MATRIX_KEY6_PRES;
	}
	else if(value > 1.8 && value < 2.28)
	{
		//return MATRIX_KEY9_PRES;
		key_value = MATRIX_KEY9_PRES;
	}
	else if(value > 2.3 && value < 2.6)
	{
		//return MATRIX_KEYBACK_PRES;
		key_value = MATRIX_KEYBACK_PRES;
	}

	if(key_value == 0)
	{
		key_up = 1;
		return 0;
	}
	
	delay_ms(10);
	
	if(key_up)
	{
		key_up = 0;
		switch(key_value)
		{
			case MATRIX_KEY1_PRES:	return MATRIX_KEY1_PRES;
			case MATRIX_KEY2_PRES:	return MATRIX_KEY2_PRES;
			case MATRIX_KEY3_PRES:	return MATRIX_KEY3_PRES;
			case MATRIX_KEY4_PRES:	return MATRIX_KEY4_PRES;
			case MATRIX_KEY5_PRES:	return MATRIX_KEY5_PRES;
			case MATRIX_KEY6_PRES:	return MATRIX_KEY6_PRES;
			case MATRIX_KEY7_PRES:	return MATRIX_KEY7_PRES;
			case MATRIX_KEY8_PRES:	return MATRIX_KEY8_PRES;
			case MATRIX_KEY9_PRES:	return MATRIX_KEY9_PRES;
			case MATRIX_KEY0_PRES:	return MATRIX_KEY0_PRES;
			case MATRIX_KEYOK_PRES:	return MATRIX_KEYOK_PRES;
			case MATRIX_KEYBACK_PRES:	return MATRIX_KEYBACK_PRES;
			default:	break;
		}
		
	}
	return 0;// 无按键按下
}

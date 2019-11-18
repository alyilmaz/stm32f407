#include "adc.h"

void adc_ini(void){
	
	GPIO_InitTypeDef GPIO_Init_LED;
	ADC_InitTypeDef  ADC_Init_user;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	GPIO_Init_LED.GPIO_Pin=GPIO_Pin_6;
	GPIO_Init_LED.GPIO_Mode=GPIO_Mode_AN;
	GPIO_Init_LED.GPIO_Speed=GPIO_Speed_2MHz;
	GPIO_Init_LED.GPIO_OType=GPIO_OType_PP;
	GPIO_Init_LED.GPIO_PuPd=GPIO_PuPd_NOPULL;
	
	GPIO_Init(GPIOA,&GPIO_Init_LED);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC,ENABLE);
	
	ADC_Init_user.ADC_Resolution = ADC_Resolution_12b;
  ADC_Init_user.ADC_ScanConvMode = DISABLE;
  ADC_Init_user.ADC_ContinuousConvMode = DISABLE;
  ADC_Init_user.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_Init_user.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
  ADC_Init_user.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_Init_user.ADC_NbrOfConversion = 1;
	
	ADC_Init(ADC1,&ADC_Init_user);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_6,1,ADC_SampleTime_56Cycles);
	NVIC_EnableIRQ(ADC_IRQn);  		//stm32f4xx.h dosyasinda 
	//Kesme yapilandirmasi
	ADC_ITConfig(ADC1,ADC_IT_EOC,ENABLE);
	ADC_Cmd(ADC1,ENABLE);
	
}
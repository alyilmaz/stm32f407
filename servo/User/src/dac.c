#include "dac.h"

//https://www.youtube.com/watch?v=IEz5zpHWnCI&list=PL8OgDYWys_b6XtOjCejd37aVv0ic24jqV&index=59
/*
Kullanimi main icine 
dac_ini();
	DAC_SetChannel1Data(DAC_Align_12b_R,(1000*1.365));
	yazilir
*/
void dac_ini(void){
	
	GPIO_InitTypeDef GPIO_Init_DAC;
	DAC_InitTypeDef   DAC_Init_user;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	
	GPIO_Init_DAC.GPIO_Pin=GPIO_Pin_4;
	GPIO_Init_DAC.GPIO_Mode=GPIO_Mode_AF;
	GPIO_Init_DAC.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init_DAC.GPIO_OType=GPIO_OType_PP;
	GPIO_Init_DAC.GPIO_PuPd=GPIO_PuPd_UP;
	
	GPIO_Init(GPIOA,&GPIO_Init_DAC);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC,ENABLE);
	
	DAC_Init_user.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;
	DAC_Init_user.DAC_OutputBuffer=DAC_OutputBuffer_Disable;
	DAC_Init_user.DAC_Trigger=DAC_Trigger_None;
	DAC_Init_user.DAC_WaveGeneration=DAC_WaveGeneration_None;
	
	DAC_Init(DAC_Channel_1,&DAC_Init_user);
	DAC_Cmd( DAC_Channel_1,ENABLE);
}
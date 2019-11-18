#include "stm32f4xx.h"                  // Device header
#include "led.h"

void led_basla(void){
	GPIO_InitTypeDef GPIO_Init_LED;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	GPIO_Init_LED.GPIO_Pin=GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_Init_LED.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_Init_LED.GPIO_Speed=GPIO_Speed_2MHz;
	GPIO_Init_LED.GPIO_OType=GPIO_OType_PP;
	GPIO_Init_LED.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD,&GPIO_Init_LED);
}

void buton_basla(void){
	GPIO_InitTypeDef GPIO_Init_Button;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	GPIO_Init_Button.GPIO_Pin=GPIO_Pin_0;
	GPIO_Init_Button.GPIO_Mode=GPIO_Mode_IN;
	GPIO_Init_Button.GPIO_Speed=GPIO_Speed_2MHz;
	GPIO_Init_Button.GPIO_OType=GPIO_OType_PP;
	GPIO_Init_Button.GPIO_PuPd=GPIO_PuPd_DOWN;
	GPIO_Init(GPIOD,&GPIO_Init_Button);
}
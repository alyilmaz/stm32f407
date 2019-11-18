#include "delay.h"
uint16_t delay_count=0;
void SysTick_Handler(void){
	if(delay_count>0){
	delay_count--;
	}	
}


void delay_ms(uint16_t delay_temp){
	delay_count=delay_temp;
	while(delay_count){}
}

void delay_us(uint16_t delay_temp){
	delay_count=delay_temp;
	while(delay_count){}
}
#include "main.h"
#include <stdio.h>

int main(void){
	led_basla();
	buton_basla();
	SysTick_Config(SystemCoreClock/1000); //1ms delay
  usart_basla(9600);
	
	while(1){
		if(buton_oku){
			yesil_on;
		}else if(!buton_oku){
			yesil_off;
		}
		kirmizi_on;
		sari_on;
		mavi_on;
		delay_ms(1000);
		mavi_off;
		delay_ms(1000);
	}	
		
}

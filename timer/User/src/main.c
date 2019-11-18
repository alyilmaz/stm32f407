#include "main.h"
#include <stdio.h>

uint16_t i;

//startup_stm32f407xx.s dosyasinda kesme vektorunu bulup fonksiyon olusturuyoruz
void USART2_IRQHandler (){
	
	if(USART_GetITStatus(USART2,USART_IT_RXNE)){
		
		static uint8_t cnt = 0; // this counter is used to determine the string length
		char t = USART2->DR; // the character from the USART1 data register is saved in t
		
		/* check if the received character is not the LF character (used to determine end of string) 
		 * or the if the maximum string length has been been reached 
		 */
		if( (t != '\n') && (cnt < MAX_STRLEN) ){ 
			received_string[cnt] = t;
			cnt++;
		}
		else{ // otherwise reset the character counter and print the received string
			cnt = 0;
			USART_puts(USART2, received_string);
			led_veri=received_string[0];
			USART_SendData(USART2,'\n');
		}		
	}
}

int main(void){
	char str[10];
	led_basla();
	buton_basla();
	SysTick_Config(SystemCoreClock/1000); //1ms delay
   usart_basla(9600);
	timer2_ini(); 
	timer3_ini();
	 USART_puts(USART2, "Init complete! Hello World!\r\n"); // just send a message to indicate that it works
	while(1){
		
		
	}	
		
}
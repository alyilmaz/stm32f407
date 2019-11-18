#include "main.h"
#include <stdio.h>

uint16_t delay_count=0;
uint8_t spi_en=0,key_num;
uint16_t i;

void SysTick_Handler(void){
	if(delay_count>0){
	delay_count--;
	}	
}


void delay_ms(uint16_t delay_temp){
	delay_count=delay_temp;
	while(delay_count){}
}

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


/*---------------------------------------------------------------------------
/
------------------------------------------------------------------------------*/


//-----------------------------------------------------------
uint16_t data_adc;
void ADC_IRQHandler(void){
	
		if(ADC_GetITStatus( ADC1,ADC_IT_EOC)==SET){
		ADC_ClearITPendingBit(ADC1,ADC_IT_EOC);
		data_adc=ADC_GetConversionValue(ADC1);	
	}
}

int main(void){
	char str[10];
	led_basla();
	buton_basla();
	SysTick_Config(SystemCoreClock/1000); //1ms delay
   usart_basla(9600);
	timer_ini(); 
	delay_ms(400);
	 USART_puts(USART2, "Init complete! Hello World!\r\n"); // just send a message to indicate that it works
	Hard_PWM();
	while(1){
		
		TIM_SetCompare4(TIM4,900);
		if(i<1000){
			i++;
		}else{
			i=0;
		}
		delay_ms(10);
	}	
		
}

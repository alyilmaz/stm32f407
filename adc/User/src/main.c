#include "main.h"
#include <stdio.h>

uint8_t i;
float analog;
uint8_t analog_data[2];
unsigned char Buffer_length= 0;
char rx;
unsigned char Rx_Buffer[150];


//startup_stm32f407xx.s dosyasinda kesme vektorunu bulup fonksiyon olusturuyoruz
void USART2_IRQHandler (){
	
	if(USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET){
		
		//USART_ClearITPendingBit (USART2, USART_IT_RXNE);
      rx =  USART_ReceiveData (USART2);        //receive a char
      Rx_Buffer[Buffer_length] = rx;
      Buffer_length++;
		if(rx =='\n'){ // otherwise reset the character counter and print the received string
			Buffer_length = 0;
			USART_puts(USART2,"received\r\n");
			
		}		
	}
}


//-----------------------------------------------------------
uint16_t data_adc;
void ADC_IRQHandler(void){
	
		if(ADC_GetITStatus( ADC1,ADC_IT_EOC)==SET){
		ADC_ClearITPendingBit(ADC1,ADC_IT_EOC);
		data_adc=ADC_GetConversionValue(ADC1);	//datalar1n al1ndigi satir
	}
}

int main(void){
	led_basla();
	buton_basla();
	SysTick_Config(SystemCoreClock/1000); //1ms delay
  usart_basla(9600);
	adc_ini();
	USART_puts(USART2, "Init complete! Hello World!\r\n"); // just send a message to indicate that it works
	
	
	while(1){
		
		analog_data[1]=(uint8_t)data_adc&0xff;
		analog_data[0]=(uint8_t)(data_adc>>8)&0xff;
		ADC_SoftwareStartConv(ADC1);
		
		for(i=0;i<2;i++){
		SendChar(analog_data[i]);
		}
		delay_ms(1000);
	}	
		
}


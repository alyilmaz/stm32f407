#include "main.h"
#include <stdio.h>

uint16_t i;
unsigned char Buffer_length= 0;
char rx;
unsigned char Rx_Buffer[150];
uint8_t send_buffer[10]={0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39};

//startup_stm32f407xx.s dosyasinda kesme vektorunu bulup fonksiyon olusturuyoruz
void USART2_IRQHandler (){
	
	if(USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET){
		
		//USART_ClearITPendingBit (USART2, USART_IT_RXNE);
      rx =  USART_ReceiveData (USART2);        //receive a char
      Rx_Buffer[Buffer_length] = rx;
      Buffer_length++;
		if(rx =='2'){ // *********Bitis Byte Char
			Buffer_length = 0;
			USART_puts(USART2,"received\r\n");
			
		}		
	}
}

int main(void){

	led_basla();
	buton_basla();
	SysTick_Config(SystemCoreClock/1000); //1ms delay
  usart_basla(9600);
	timer_ini(); 
	
	 //USART_puts(USART2, "Init complete! Hello World!\r\n"); // just send a message to indicate that it works
	while(1){
		
		if(Rx_Buffer[0]=='1'){
			sari_on;
	}else{
		sari_off;
	}
	if(Rx_Buffer[1]=='1'){
    yesil_on;
	}else{
		yesil_off;
	}		
	if(Rx_Buffer[2]=='1'){
    kirmizi_on;
	}else{
		kirmizi_off;
	}		
	if(Rx_Buffer[3]=='1'){
    mavi_on;
	}else{
		mavi_off;
	}		
	
	
	USART_puts(USART2,send_buffer);
	delay_ms(3000);
	//yesil_off;
	//sari_off;
	
	
}	
}

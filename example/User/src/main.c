#include "main.h"
#include <stdio.h>

uint16_t delay_count=0;
uint8_t spi_en=0,key_num;
uint16_t i;

void SysTick_Handler(void){
	if(delay_count>0){
	delay_count--;
	}
	if(spi_en==1){
	CS_ON;
	DMA_Cmd(DMA2_Stream0,ENABLE);
	DMA_Cmd(DMA2_Stream3,ENABLE);
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
//Kesme vektorunu startup dosyasinda bulundu	
void DMA1_Stream6_IRQHandler(void){
	if(DMA_GetITStatus( DMA1_Stream6,DMA_IT_TCIF6)==SET){
		DMA_ClearITPendingBit(DMA1_Stream6,DMA_IT_TCIF6);
	}
}

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
	uint8_t spi_readdata;
	led_basla();
	buton_basla();
	SysTick_Config(SystemCoreClock/1000); //1ms delay
   usart_basla(9600);
	dma_basla();
	timer_ini(); 
	adc_ini();
	delay_ms(400);
	 USART_puts(USART2, "Init complete! Hello World!\r\n"); // just send a message to indicate that it works
	
	/*
   spi_basla();
	 spi_DMA_init();
	
	 SetSpi_Out(0,0x8f);  //ID
	 SetSpi_Out(1,0x00);
	 startSPI(2);
	 SPIwait();
	
	if(GetSPI_In(1)==0x3b){
		kirmizi_on;
	}else if(GetSPI_In(1)==0x3f){  //Data sheet den gelen default degeri
		yesil_on;
		
		
	 SetSpi_Out(0,0x20);  // Set semple rate
	 SetSpi_Out(1,0x97);	//1600Hz
	 startSPI(2);
	 SPIwait();
		
	 SetSpi_Out(0,0xA8);  // 
	 SetSpi_Out(1,0x00);	//
	 DMA_SetCurrDataCounter(DMA2_Stream0,7);
	DMA_SetCurrDataCounter(DMA2_Stream3,7);
	 spi_en=1;
	}*/
	/*
	CS_ON;
	SPI_I2S_SendData(SPI1,0x8f);
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_BSY)==SET){}
	spi_readdata=SPI_I2S_ReceiveData(SPI1);	
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_BSY)==SET){}
	SPI_I2S_SendData(SPI1,0x00);	
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_BSY)==SET){}
	spi_readdata=SPI_I2S_ReceiveData(SPI1);	
	CS_OFF;
		
	if(spi_readdata==0x3b){
		kirmizi_on;
	}else if(spi_readdata==0x3f){
		yesil_on;
	}
	*/
	while(1){
		
		ADC_SoftwareStartConv(ADC1);
	}	
		
}

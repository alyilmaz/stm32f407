#include "stm32f4xx.h"                  // Device header
#include "usart.h"


/*kullanim sekli
USART_puts(USART2, "Init complete! Hello World!\r\n"); // just send a message to indicate that it works
USART_SendData(USART2,0x55);
*/
void USART_puts(USART_TypeDef* USARTx, volatile char *s){

	while(*s){
		// wait until data register is empty
		while( !(USARTx->SR & 0x00000040) ); 
		USART_SendData(USARTx, *s);
		*s++;
	}
}

void usart_basla(uint16_t Baudrate){
	
	GPIO_InitTypeDef GPIO_Init_USART;
	USART_InitTypeDef  Usart2_inituser;
	NVIC_InitTypeDef NVIC_InitStructure; // this is used to configure the NVIC (nested vector interrupt controller)
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	
	GPIO_Init_USART.GPIO_Pin=GPIO_Pin_2|GPIO_Pin_3;
	GPIO_Init_USART.GPIO_Mode=GPIO_Mode_AF;
	GPIO_Init_USART.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init_USART.GPIO_OType=GPIO_OType_PP;
	GPIO_Init_USART.GPIO_PuPd=GPIO_PuPd_UP;
	
	GPIO_Init(GPIOA,&GPIO_Init_USART);
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	
	Usart2_inituser.USART_BaudRate=Baudrate;
	Usart2_inituser.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	Usart2_inituser.USART_Mode=USART_Mode_Tx | USART_Mode_Rx;
	Usart2_inituser.USART_Parity=USART_Parity_No;
	Usart2_inituser.USART_StopBits=USART_StopBits_1;
	Usart2_inituser.USART_WordLength=USART_WordLength_8b;
	USART_Init(USART2,&Usart2_inituser);
	
	
	NVIC_EnableIRQ(USART2_IRQn);						//CMSIS 'de system_stm32f4xx.c altinda core_cm4.h dosyasinda bu fonksiyonu bulup usart2 kesmesinin fonksiyon adini ekliyoruz
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);	//STdPerhp klasorunde stm32f4xx_usart.c altinda stm32f4xx_usart.h dosyasinda kesme fonksiyonu aliyoruz
	
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;		 // we want to configure the USART1 interrupts
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;// this sets the priority group of the USART1 interrupts
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		 // this sets the subpriority inside the group
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			 // the USART1 interrupts are globally enabled
	NVIC_Init(&NVIC_InitStructure);							 // the properties are passed to the NVIC_Init function which takes care of the low level stuff	
	
	USART_Cmd(USART2, ENABLE);
	
	
}
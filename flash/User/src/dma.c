#include "stm32f4xx.h"
#include "dma.h"

char buffer[]="I am DMA\n";

/*
Kullanim sekli
//DMA_Cmd(DMA1_Stream6, ENABLE);
*/


void dma_basla(void){
DMA_InitTypeDef dma_ini_usart;
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1,ENABLE);	
dma_ini_usart.DMA_Channel=DMA_Channel_4; // Datasheet de usart2 icin channel 4 belirtilmis
dma_ini_usart.DMA_PeripheralBaseAddr=(uint32_t)&(USART2->DR);
dma_ini_usart.DMA_Memory0BaseAddr=(uint32_t)buffer;
dma_ini_usart.DMA_DIR=DMA_DIR_MemoryToPeripheral;
dma_ini_usart.DMA_BufferSize=(uint16_t)sizeof(buffer);
dma_ini_usart.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
dma_ini_usart.DMA_MemoryInc=DMA_MemoryInc_Enable;
dma_ini_usart.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;
dma_ini_usart.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;
dma_ini_usart.DMA_Mode=DMA_Mode_Normal;
dma_ini_usart.DMA_Priority=DMA_Priority_Medium ;
dma_ini_usart.DMA_FIFOMode=DMA_FIFOMode_Disable;
dma_ini_usart.DMA_FIFOThreshold=DMA_FIFOThreshold_1QuarterFull;
dma_ini_usart.DMA_MemoryBurst=DMA_MemoryBurst_Single;
dma_ini_usart.DMA_PeripheralBurst=DMA_PeripheralBurst_Single;
	
DMA_Init(DMA1_Stream6,&dma_ini_usart);	///Datasheet den stream degerleri yaziyor
	
USART_DMACmd(USART2,USART_DMAReq_Tx,ENABLE); //..usart.h kutuphanesinde bulundu

NVIC_EnableIRQ(DMA1_Stream6_IRQn);	
DMA_ITConfig(DMA1_Stream6, DMA_IT_TC,ENABLE);
}
#include "spi.h"

uint8_t SPI_In[7];
uint8_t SPI_Out[7];
uint8_t SPI_work=0;
extern char buffer[8];

//-------------------------------------------------------------------------------------
void startSPI(uint8_t number){
	
	DMA_SetCurrDataCounter(DMA2_Stream0,number);
	DMA_SetCurrDataCounter(DMA2_Stream3,number);
	
	SPI_work=1;
	CS_ON;
	DMA_Cmd(DMA2_Stream0,ENABLE);
	DMA_Cmd(DMA2_Stream3,ENABLE);
}

//-------------------------------------------------------------------------------------
void SPIwait(void){
	
			while(SPI_work){}
}

//-------------------------------------------------------------------------------------
void SetSpi_Out(uint8_t Adr,uint8_t Data){
	
		if(Adr<7){
		SPI_Out[Adr]=Data;
		}
}


//-------------------------------------------------------------------------------------
uint8_t GetSPI_In(uint8_t Adr){
	
	 return SPI_In[Adr];	
}

//-------------------------------------------------------------------------------------
//RX
void DMA2_Stream0_IRQHandler(void){
	uint16_t temp;
	
	if(DMA_GetITStatus(DMA2_Stream0,DMA_IT_TCIF0)==SET){
		DMA_ClearITPendingBit(DMA2_Stream0,DMA_IT_TCIF0);
		CS_OFF;
		SPI_work=0;
		
		buffer[0]=0xAA;
		buffer[1]=0xBB;
		
		temp=((uint16_t)SPI_In[2]<<8)|((uint16_t)SPI_In[1]);//X
		if(temp>=0x8000){
			temp=temp-0x8000;
		}else{
			temp=temp+0x8000;
		}
		
		buffer[2]=(uint8_t)temp>>8; 
		buffer[3]=(uint8_t)temp;
		
		
		temp=((uint16_t)SPI_In[4]<<8)|((uint16_t)SPI_In[3]);//Y
		if(temp>=0x8000){
			temp=temp-0x8000;
		}else{
			temp=temp+0x8000;
		}
		
		buffer[4]=(uint8_t)temp>>8; //
		buffer[5]=(uint8_t)temp;
		
		temp=((uint16_t)SPI_In[6]<<8)|((uint16_t)SPI_In[5]);//Z
		if(temp>=0x8000){
			temp=temp-0x8000;
		}else{
			temp=temp+0x8000;
		}
		
		buffer[6]=(uint8_t)temp>>8; //
		buffer[7]=(uint8_t)temp;
		
		DMA_SetCurrDataCounter(DMA1_Stream6,8);
		DMA_Cmd(DMA1_Stream6,ENABLE);
	}
}
//-------------------------------------------------------------------------------------
//Tx
void DMA2_Stream3_IRQHandler(void){
	
		
	if(DMA_GetITStatus(DMA2_Stream3,DMA_IT_TCIF3)==SET){
		DMA_ClearITPendingBit(DMA2_Stream3,DMA_IT_TCIF3);
	}
}



//-------------------------------------------------------------------------------------
void spi_basla(void)
{
	
	GPIO_InitTypeDef GPIO_Init_LED;
	SPI_InitTypeDef  SPI_Init_user;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	GPIO_Init_LED.GPIO_Pin=GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_Init_LED.GPIO_Mode=GPIO_Mode_AF;
	GPIO_Init_LED.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init_LED.GPIO_OType=GPIO_OType_PP;
	GPIO_Init_LED.GPIO_PuPd=GPIO_PuPd_NOPULL;
	
	GPIO_Init(GPIOA,&GPIO_Init_LED);
	
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource5,GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_SPI1);
	
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	GPIO_Init_LED.GPIO_Pin=GPIO_Pin_3;
	GPIO_Init_LED.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_Init_LED.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init_LED.GPIO_OType=GPIO_OType_PP;
	GPIO_Init_LED.GPIO_PuPd=GPIO_PuPd_NOPULL;
	
	GPIO_Init(GPIOE,&GPIO_Init_LED);
	CS_OFF;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);  //..rcc.h dosyasinda alindi

	SPI_Init_user.SPI_Direction=SPI_Direction_2Lines_FullDuplex;
	SPI_Init_user.SPI_Mode=SPI_Mode_Master;
	SPI_Init_user.SPI_DataSize=SPI_DataSize_8b;
	SPI_Init_user.SPI_CPOL=SPI_CPOL_High;
	SPI_Init_user.SPI_CPHA=SPI_CPHA_2Edge;
	SPI_Init_user.SPI_NSS=SPI_NSS_Soft;
	SPI_Init_user.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_64;
	SPI_Init_user.SPI_FirstBit=SPI_FirstBit_MSB;
	SPI_Init_user.SPI_CRCPolynomial=7;
	
	SPI_Init(SPI1,&SPI_Init_user);
	SPI_Cmd(SPI1,ENABLE);

}

//------------------------------------------------------------------------------------------------------------
void spi_DMA_init(void){
	
		DMA_InitTypeDef DMA_Init_SPI;
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);	
		
		//TX	
		DMA_Init_SPI.DMA_Channel=DMA_Channel_3; // Datasheet de spi icin channel 4 belirtilmis
		DMA_Init_SPI.DMA_PeripheralBaseAddr=(uint32_t)&(SPI1->DR);
		DMA_Init_SPI.DMA_Memory0BaseAddr=(uint32_t)SPI_Out;
		DMA_Init_SPI.DMA_DIR=DMA_DIR_MemoryToPeripheral;
		DMA_Init_SPI.DMA_BufferSize=2;
		DMA_Init_SPI.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
		DMA_Init_SPI.DMA_MemoryInc=DMA_MemoryInc_Enable;
		DMA_Init_SPI.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;
		DMA_Init_SPI.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;
		DMA_Init_SPI.DMA_Mode=DMA_Mode_Normal;
		DMA_Init_SPI.DMA_Priority=DMA_Priority_Medium ;
		DMA_Init_SPI.DMA_FIFOMode=DMA_FIFOMode_Disable;
		DMA_Init_SPI.DMA_FIFOThreshold=DMA_FIFOThreshold_1QuarterFull;
		DMA_Init_SPI.DMA_MemoryBurst=DMA_MemoryBurst_Single;
		DMA_Init_SPI.DMA_PeripheralBurst=DMA_PeripheralBurst_Single;
			
		DMA_Init(DMA2_Stream3,&DMA_Init_SPI);	///Datasheet den stream degerleri yaziyor
			
		NVIC_EnableIRQ(DMA2_Stream3_IRQn);	
		DMA_ITConfig(DMA2_Stream3, DMA_IT_TC,ENABLE);
		
		SPI_I2S_DMACmd(SPI1,SPI_I2S_DMAReq_Tx,ENABLE);
		
				//RX	
		DMA_Init_SPI.DMA_Channel=DMA_Channel_3; // Datasheet de spi icin channel 4 belirtilmis
		DMA_Init_SPI.DMA_PeripheralBaseAddr=(uint32_t)&(SPI1->DR);
		DMA_Init_SPI.DMA_Memory0BaseAddr=(uint32_t)SPI_In;
		DMA_Init_SPI.DMA_DIR=DMA_DIR_PeripheralToMemory;
		DMA_Init_SPI.DMA_BufferSize=2;
		DMA_Init_SPI.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
		DMA_Init_SPI.DMA_MemoryInc=DMA_MemoryInc_Enable;
		DMA_Init_SPI.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;
		DMA_Init_SPI.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;
		DMA_Init_SPI.DMA_Mode=DMA_Mode_Normal;
		DMA_Init_SPI.DMA_Priority=DMA_Priority_Medium ;
		DMA_Init_SPI.DMA_FIFOMode=DMA_FIFOMode_Disable;
		DMA_Init_SPI.DMA_FIFOThreshold=DMA_FIFOThreshold_1QuarterFull;
		DMA_Init_SPI.DMA_MemoryBurst=DMA_MemoryBurst_Single;
		DMA_Init_SPI.DMA_PeripheralBurst=DMA_PeripheralBurst_Single;
			
		DMA_Init(DMA2_Stream0,&DMA_Init_SPI);	///Datasheet den stream degerleri yaziyor
			
		NVIC_EnableIRQ(DMA2_Stream0_IRQn);	
		DMA_ITConfig(DMA2_Stream0, DMA_IT_TC,ENABLE);
		
		SPI_I2S_DMACmd(SPI1,SPI_I2S_DMAReq_Rx,ENABLE);
}
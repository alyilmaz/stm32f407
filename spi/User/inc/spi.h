#ifndef SPI_H
#define SPI_H
#include "stm32f4xx.h"

#define CS_ON		GPIO_ResetBits(GPIOE,GPIO_Pin_3)
#define CS_OFF	GPIO_SetBits(GPIOE,GPIO_Pin_3)
void spi_basla(void);
void spi_DMA_init(void);
void startSPI(uint8_t number);
void SPIwait(void);
void SetSpi_Out(uint8_t Adr,uint8_t Data);
uint8_t GetSPI_In(uint8_t Adr);
#endif
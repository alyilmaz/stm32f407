#ifndef FLASH_H
#define FLASH_H
#define ADDRESS 0x08020000
#include "stm32f4xx.h"

uint32_t Read_Flash(uint32_t Data_adr);
void Write_Flash(uint32_t Data_adr,uint32_t Data);

#endif
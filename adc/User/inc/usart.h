#ifndef USART_H
#define USART_H


void usart_basla(uint16_t Baudrate);
void USART_puts(USART_TypeDef* USARTx, volatile char *s);
void SendChar (char Tx);

#endif
#ifndef PWM_H
#define PWM_H

#include "stm32f4xx.h"
#include "led.h"

void SysTick_PWM(void);
void PWM_Led_On(void);
void PWM_Led_Off(void);
void Led_On(void);
void Led_Off(void);
void Hard_PWM(void);

#endif
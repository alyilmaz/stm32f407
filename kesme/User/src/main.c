#include "main.h"
#include <stdio.h>
int i;

/* Set interrupt handlers */
/* Handle PD0 interrupt */
void EXTI0_IRQHandler(void) {
	/* Make sure that interrupt flag is set */
	if (EXTI_GetITStatus(EXTI_Line0) != RESET) {
		/* Do your stuff when PD0 is changed */
		sari_toggle;
		for(i=0;i<1000000;i++){}
		/* Clear interrupt flag */
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

/* Handle PB12 interrupt */
void EXTI1_IRQHandler(void) {
	/* Make sure that interrupt flag is set */
	if (EXTI_GetITStatus(EXTI_Line1) != RESET) {
		/* Do your stuff when PB1 is changed */
		kirmizi_toggle;
		for(i=0;i<1000000;i++){}
		/* Clear interrupt flag */
		EXTI_ClearITPendingBit(EXTI_Line1);
	}
}

/* Handle PB12 interrupt */
void EXTI15_10_IRQHandler(void) {
	/* Make sure that interrupt flag is set */
	if (EXTI_GetITStatus(EXTI_Line12) != RESET) {
		/* Do your stuff when PB1 is changed */
		yesil_toggle;
		for(i=0;i<1000000;i++){}
		/* Clear interrupt flag */
		EXTI_ClearITPendingBit(EXTI_Line12);
	}else if(EXTI_GetITStatus(EXTI_Line11) != RESET) {
		/* Do your stuff when PB1 is changed */
		mavi_toggle;
		for(i=0;i<1000000;i++){}
		/* Clear interrupt flag */
		EXTI_ClearITPendingBit(EXTI_Line11);
	}
}


int main(void){
	led_basla();
	buton_basla();
	/* System init */
	SystemInit();
	led_basla();
	/* Configure PD0 as interrupt */
	Configure_PD0();
	/* Configure PB1 as interrupt */
	Configure_PB1();
/* Configure PB12 as interrupt */	
	Configure_PB12();
	/* Configure PB11 as interrupt */	
	Configure_PB11();
	SysTick_Config(SystemCoreClock/1000); //1ms delay
  usart_basla(9600);
	
	while(1){

		mavi_toggle;
		delay_ms(100);
	
		
	}	
		
}

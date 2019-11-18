#include "pwm.h"

/*
Donanimsal OLMAYAN PWM UYGULAMSI icin
	SysTick_PWM();
	PWM_Led_On();
	PWM_Led_Off();
	
	bu fokssiyonlar SysTickHandler fonksiyonda yazilmali main icindde
	
			Led_On();
			delay_ms(1000);
			Led_Off();
			delay_ms(1000);
			
		bu fonksiyonlarda sonsuz foks icinde yazilir
	

*/
uint8_t pwm_counter=0;
uint8_t PWM_A=1,PWM_B=20;

uint8_t PWM_Led_On_Counter=0;
uint8_t PWM_Led_Off_Counter=0;

uint8_t PWM_Led_On_flag=0;
uint8_t PWM_Led_Off_flag=0;

void SysTick_PWM(void){
	
		if(pwm_counter>=PWM_B){
			pwm_counter=0;
			mavi_on;
		}else if(pwm_counter==PWM_A){
			pwm_counter++;
			mavi_off;
		}else{
		pwm_counter++;
		}
}

void PWM_Led_On(void){

	if(PWM_Led_On_flag==1){
		if(PWM_Led_On_Counter>=20){
			PWM_Led_On_Counter=0;
			
				if(PWM_A<PWM_B){
					PWM_A++;
				}else{
					PWM_Led_On_flag=0;
				}
		}else{
		PWM_Led_On_Counter++;
		}
	}
}


void PWM_Led_Off(void){

	if(PWM_Led_Off_flag==1){
		if(PWM_Led_Off_Counter>=20){
			
			PWM_Led_Off_Counter=0;
			
				if(PWM_A>0){
					PWM_A--;
				}else{
					PWM_Led_Off_flag=0;
				}
		}else{
		PWM_Led_Off_Counter++;
		}
	}
}

void Led_On(void){
	PWM_Led_On_flag=1;
}

void Led_Off(void){
	
	PWM_Led_Off_flag=1;
}



//-------------------------------------------------

/*
donanimsal PWM kullanmak icin
sonsuz donguye 

	TIM_SetCompare4(TIM4,i);
		if(i<1000){
			i++;
		}else{
			i=0;
		}
		delay_ms(10);

main fonksiyounu icine
Hard_PWM();
yazilir
kodlari yazarak duty cycle her 10ms de %0.1 artirarak 0 sifirliyoruz

*/
void Hard_PWM(void){
	
		  TIM_TimeBaseInitTypeDef TIM_Time_user;
			GPIO_InitTypeDef GPIO_Init_LED;
			TIM_OCInitTypeDef Hard_PWM_ini;
	
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
			
			TIM_Time_user.TIM_Prescaler=0;
			TIM_Time_user.TIM_CounterMode=TIM_CounterMode_Up;
			TIM_Time_user.TIM_Period=1000;
			TIM_Time_user.TIM_ClockDivision=TIM_CKD_DIV1;  //TIM_RepetitionCounter parametre sadece tim1 ve tim8 kullanilabilir oldugu icin burda kullanmiyoruz			
			TIM_TimeBaseInit( TIM4,&TIM_Time_user );

	
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
			GPIO_Init_LED.GPIO_Pin=GPIO_Pin_15;
			GPIO_Init_LED.GPIO_Mode=GPIO_Mode_AF;
			GPIO_Init_LED.GPIO_Speed=GPIO_Speed_100MHz;
			GPIO_Init_LED.GPIO_OType=GPIO_OType_PP;
			GPIO_Init_LED.GPIO_PuPd=GPIO_PuPd_NOPULL;
			GPIO_Init(GPIOD,&GPIO_Init_LED);	
			GPIO_PinAFConfig(GPIOD,GPIO_PinSource15,GPIO_AF_TIM4);
			
			Hard_PWM_ini.TIM_OCMode=TIM_OCMode_PWM1;
			Hard_PWM_ini.TIM_OutputState=TIM_OutputState_Enable;
			//Hard_PWM_ini.TIM_OutputNState=;  tim1 ve tim8 kullanilir
			Hard_PWM_ini.TIM_Pulse=100;               	//Pwm duty Cycle ayarlama
			Hard_PWM_ini.TIM_OCPolarity=TIM_OCPolarity_High;
			//Hard_PWM_ini.TIM_OCNPolarity=;tim1 ve tim8 kullanilir
			//Hard_PWM_ini.TIM_OCIdleState=;
			//Hard_PWM_ini.TIM_OCNIdleState=;
			
			TIM_OC4Init(TIM4, &Hard_PWM_ini);

			
			TIM_Cmd(TIM4,ENABLE);

}

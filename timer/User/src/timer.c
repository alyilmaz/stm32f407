#include "timer.h"
uint16_t tim=0;
uint16_t tim1=0;
//Kesme Vektoru 1saniye
void TIM2_IRQHandler(void){
	
		if(TIM_GetITStatus(TIM2,TIM_IT_Update)){
				TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
			  tim++;
				//mavi_toggle;
			  kirmizi_off;
			  if(tim==100){
				kirmizi_on;
				tim=0;	
				}
		}
}

//Kesme Vektoru 1saniye
void TIM3_IRQHandler(void){
	
		if(TIM_GetITStatus(TIM3,TIM_IT_Update)){
				TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
			  tim1++;
				//mavi_toggle;
			  yesil_off;
			  if(tim1==75){
				yesil_on;
				tim1=0;	 
				}
		}
}

//Timer2 Configure 
void timer2_ini(void){
	
	TIM_TimeBaseInitTypeDef TIM_Time_user;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	TIM_Time_user.TIM_Prescaler=20000-1;
	TIM_Time_user.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_Time_user.TIM_Period=20;
	TIM_Time_user.TIM_ClockDivision=TIM_CKD_DIV1;  //TIM_RepetitionCounter parametre sadece tim1 ve tim8 kullanilabilir oldugu icin burda kullanmiyoruz
	TIM_TimeBaseInit( TIM2,&TIM_Time_user );
	NVIC_EnableIRQ(TIM2_IRQn);
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM2,ENABLE);
}

//Timer3 Configure 
void timer3_ini(void){
	
	TIM_TimeBaseInitTypeDef TIM_Time_user;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	TIM_Time_user.TIM_Prescaler=20000-1;
	TIM_Time_user.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_Time_user.TIM_Period=20;  //2000 olursa 1sn
	TIM_Time_user.TIM_ClockDivision=TIM_CKD_DIV1;  //TIM_RepetitionCounter parametre sadece tim1 ve tim8 kullanilabilir oldugu icin burda kullanmiyoruz
	TIM_TimeBaseInit( TIM3,&TIM_Time_user );
	NVIC_EnableIRQ(TIM3_IRQn);
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM3,ENABLE);
}

#ifndef LED_H
#define LED_H
#define sari_on 		GPIO_SetBits(GPIOD,GPIO_Pin_13)
#define sari_off		GPIO_ResetBits(GPIOD,GPIO_Pin_13)
#define kirmizi_on	GPIO_SetBits(GPIOD,GPIO_Pin_14)
#define kirmizi_off	GPIO_ResetBits(GPIOD,GPIO_Pin_14)
#define mavi_on			GPIO_SetBits(GPIOD,GPIO_Pin_15)
#define mavi_off		GPIO_ResetBits(GPIOD,GPIO_Pin_15)
#define yesil_on		GPIO_SetBits(GPIOD,GPIO_Pin_12)
#define yesil_off		GPIO_ResetBits(GPIOD,GPIO_Pin_12)
#define mavi_toggle	GPIO_ToggleBits(GPIOD,GPIO_Pin_15)
#define buton_oku		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)
void led_basla(void);
void buton_basla(void);
#endif
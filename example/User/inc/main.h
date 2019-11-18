#ifndef MAIN_H
#define MAIN_H
#include "stm32f4xx.h"                  // Device header
#include "delay.h"
#include "usart.h"
#include "delay.h"
#include "led.h"
#include "dma.h"
#include "flash.h"
#include "spi.h"
#include "timer.h"
#include "pwm.h"
#include "keyboard.h"
#include "dac.h"
#include "adc.h"


#define MAX_STRLEN 12 // this is the maximum string length of our string in characters
volatile char received_string[MAX_STRLEN+1]; // this will hold the recieved string
 char led_veri;
 
/*
Proje olustutulurken new  project yapip daha sonra startup_stm32f407.s eklenir.
Bu dosyayi startup adli klasor olusturup oraya kopyalayabiliriz.
Editorde proje ye sag tiklanip add group deyip klasor ekleyebiliriz
CMSIS
StdPeriph
User 
klasorler eklenir
Daha sonra ST Microeletronic sitesinde standart ceveresel kutuphanesi indirilir rar li olarak
arsivin icindeki CMSIS ve STM32F4xx_StdPeriph_Driver klasorlerini kopyalayip proje dosyasinin icine yapistirilir
CMSIS klasorunda Device ve Include klasorleri disinda kalan dosyalar silinir
CMSIS-Device-St/--/ icindeki stm32f4xx.h ve system_stm32f4xx.h dosyalari salt okunuru iptal ediyoruz
Proje klasorunde User klasoru olusturup orda da inc ve src adli iki klasor daha olusturuyoruz
src klasorde c dosyalari  (main.c...)
inc klasorunde *h dosyalari bulunmalidir(main.h...)
arsivde ki project klasorun icinde STM32F4xx_StdPeriphLib_Example-ADC-ADC_DMA da bulunan stm32f4xx_conf.h dosyasini
bizim proje dosyasindaki stdPeriph driver klasorun icine atiyoruz
simdi sirada editorde olusturulan klasorlerin proje klasorune kopyalanan dosyalarla esletitilmesi
editorde ilk once CMSIS klasorune cift tiklanir acilan dizinde CMSIS-Device-St--/source/templates da system_stm32f4xx.c eklenip kapatilir
StdPeriph klasoru de ayni sekilde cift tiklanip stdPeriph driver klasorunde src klasorunde bulunan butun dosyalar secilip eklenir
eklenen dosyalar arasinda editorden stm32f4xx_fmc.c dosyasi silinip cikartilir 
Onun yerine StdPeriph klasorune tekrar cift tiklanip stdPeriph driver klasorun icine az once attigimiz stm32f4xx_conf.h dosyasin ekliyoruz
Sira User klasorune cift tiklanip user klasorunde src klasorunde *c dosyalari ekelenir
Editorde user klasorundeki main.c dosyasini secip sag tiklayip stm32f4xx.h kutuphanesi include edilir
Daha sonra main while dongusu yazilir
Simdi sira kutuphane yollarini belirlemede editorde proje sag tiklanip option secilir ordan c/c++ tab basilir
add path penceri acilinca ekledigimiz klasorleri tek tek ekliyoruz
User/src
User/inc
CMSIS/Device/ST/..//src
CMSIS/Device/ST/..//inc
CMSIS/iclude

vb
daha sonra stm32f4xx.h dosyasi acip bazi yorum komutlari aktif ediyoruz bunlar
70 satirdaki #define STM32F40_41xxx yorumlari kaldirip aktif etmek
126 satir daki #define USE_STDPERIPH_DRIVER aktif olacak
son olarak da 139 stairdaki #define HSE_VALUE 8000000 yapiyoruz

Delay ayarlari icinde olusan kesme SystemCoreClock sag tiklanip tanimlandigi yere giderek degerini 48000..00
yapilmasi gerekiyor onun icinde o dosya salt okunur ozelligi kapatilmalidir

*/
#endif
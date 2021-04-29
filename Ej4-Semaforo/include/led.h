#ifndef LED_H //Revisa que otro archivo no haya llamado a led.h
#define LED_H

#include "driver/gpio.h"

#define Verde GPIO_NUM_25     //me permite pasarle argumento a prender/apagar led
#define Amarillo GPIO_NUM_32
#define Rojo GPIO_NUM_26


//void ConfigurarLed(gpio_int_type_t LedRojo, gpio_int_type_t LedAmarillo, gpio_int_type_t LedVerde); //gpio_int_type_t me permite ...
void ConfigurarLed(); 
void PrenderLed(gpio_int_type_t Led);

void ApagarLed(gpio_int_type_t Led);


#endif
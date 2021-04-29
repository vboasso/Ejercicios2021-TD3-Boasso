#include "../include/led.h"


//void ConfigurarLed(gpio_int_type_t LedRojo, gpio_int_type_t LedAmarillo, gpio_int_type_t LedVerde) //Implemento la función declarada en led.h
void ConfigurarLed() //Implemento la función declarada en led.h
{
    gpio_pad_select_gpio(Rojo);
    gpio_set_direction(Rojo, GPIO_MODE_OUTPUT);

    gpio_pad_select_gpio(Amarillo);
    gpio_set_direction(Amarillo, GPIO_MODE_OUTPUT);

    gpio_pad_select_gpio(Verde);
    gpio_set_direction(Verde, GPIO_MODE_OUTPUT);
}

void PrenderLed(gpio_int_type_t Led)
{
    gpio_set_level(Led, 1);
}

void ApagarLed(gpio_int_type_t Led)
{
    gpio_set_level(Led, 0);

}
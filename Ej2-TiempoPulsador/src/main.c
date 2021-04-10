#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h" //importante para los delays
#include "freertos/task.h"
#include "sdkconfig.h"

#define Led1 GPIO_NUM_12 
#define Led2 GPIO_NUM_14


#define Pulsador1 GPIO_NUM_2
#define Pulsador2 GPIO_NUM_4

#define T_ON		10/portTICK_PERIOD_MS

long int cont1;
long int cont2;

void app_main() {

    //Configuro los puertos I/O

    gpio_pad_select_gpio(Led1);
	gpio_set_direction(Led1, GPIO_MODE_OUTPUT);
	gpio_pad_select_gpio(Led2);
	gpio_set_direction(Led2, GPIO_MODE_OUTPUT);
	
	gpio_pad_select_gpio(Pulsador1);
	gpio_set_direction(Pulsador1, GPIO_MODE_INPUT);
	gpio_pad_select_gpio(Pulsador2);
	gpio_set_direction(Pulsador2, GPIO_MODE_INPUT);

    while (1)
    {
        //Detecto pulsador y cuento
        while (gpio_get_level(Pulsador1)==1)
        {
            vTaskDelay(T_ON);
            cont1+=T_ON;
        }

        while (gpio_get_level(Pulsador2)==1)
        {
            vTaskDelay(T_ON);
            cont2+=T_ON;
        }

        //Veo que contador se incrementó y enciendo su respectivo led
        if (cont1>0)
        {
            gpio_set_level(Led1,1);
            vTaskDelay(cont1);
            gpio_set_level(Led1,0);
            cont1=0;
        }
        
        if (cont2>0)
        {
            gpio_set_level(Led2,1);
            vTaskDelay(cont2);
            gpio_set_level(Led2,0);
            cont2=0;
        }
    
    } //Llave while

} //Llave main
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include <driver/adc.h>
#include <driver/dac.h>

#define LedVerde GPIO_NUM_12 
#define LedRojo GPIO_NUM_14

void app_main()
{
    adc1_config_width(ADC_WIDTH_12Bit); //configuro resoluncion

    adc1_config_channel_atten (ADC1_CHANNEL_0 ,ADC_ATTEN_11db);// esta atenuación me permite leer de 0 a 3,3 V (0 a 2.5 es óptimo)
   
    //Configuro puertos
    
    gpio_pad_select_gpio(LedVerde);
	gpio_set_direction(LedVerde, GPIO_MODE_OUTPUT);
	gpio_pad_select_gpio(LedRojo);
	gpio_set_direction(LedRojo, GPIO_MODE_OUTPUT);

    //Variables
    float voltaje=0 ;

    while(true)
    {
        int lectura = adc1_get_raw(ADC1_CHANNEL_0); // tomo la medición (en este caso del pin 36)
        printf("El voltaje en ADC1 es %.2f\n",voltaje);// muestro la medición en terminal mediante el puerto serie

        
        vTaskDelay(500/portTICK_PERIOD_MS); // lo coloco para no mostrar tantos datos rápidamente   

        voltaje = (lectura * (3.3/4096)); //convierto la lectura a voltaje

        if (voltaje < 1.5)
        {
            gpio_set_level(LedRojo, 0);
            gpio_set_level(LedVerde, 1);
        }
        else if (voltaje >= 1.5)
        {
            gpio_set_level(LedRojo, 1);
            gpio_set_level(LedVerde, 0);
        }
        

    }

}

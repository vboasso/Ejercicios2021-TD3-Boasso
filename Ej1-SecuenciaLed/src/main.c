#include "../driver/include/driver/gpio.h"
#include "freertos/FreeRTOS.h" //importante para los delays
#include "freertos/task.h"

#define Led1 GPIO_NUM_12 
#define Led2 GPIO_NUM_14
#define Led3 GPIO_NUM_27

#define Pulsador1 GPIO_NUM_2
#define Pulsador2 GPIO_NUM_4

#define T_ON		500/portTICK_PERIOD_MS


void app_main() {
    //Configuro los puertos I/O

    gpio_pad_select_gpio(Led1);
	gpio_set_direction(Led1, GPIO_MODE_OUTPUT);
	gpio_pad_select_gpio(Led2);
	gpio_set_direction(Led2, GPIO_MODE_OUTPUT);
	gpio_pad_select_gpio(Led3);
	gpio_set_direction(Led3, GPIO_MODE_OUTPUT);

	gpio_pad_select_gpio(Pulsador1);
	gpio_set_direction(Pulsador1, GPIO_MODE_INPUT);
	gpio_pad_select_gpio(Pulsador2);
	gpio_set_direction(Pulsador2, GPIO_MODE_INPUT);

    //Variables:
    int cont = 0;
    int Sentido_giro = 0;

    while (1)
    {
        // Leo el Pulsador que se presiona
        if(gpio_get_level(Pulsador1)==0){
            Sentido_giro = 1;
        }
        else if(gpio_get_level(Pulsador2)==0){
            Sentido_giro = 0;
        }

        //Prendo/apago los Leds
        if ( cont == 0 ){
			gpio_set_level(Led1, 1);
			gpio_set_level(Led2, 0);
			gpio_set_level(Led3, 0);
        }

        if ( cont == 1 ){
			gpio_set_level(Led1, 0);
			gpio_set_level(Led2, 1);
			gpio_set_level(Led3, 0);
        }

        if ( cont == 2 ){
			gpio_set_level(Led1, 0);
			gpio_set_level(Led2, 0);
			gpio_set_level(Led3, 1);
        }

        if (Sentido_giro==0){

            cont++;
            if (cont>2)
            {
                cont=0;
            }
            
        }
        
        if (Sentido_giro==1){
            
            cont--;
            if (cont<0)
            {
                cont=2;
            }
            
        }
        vTaskDelay(T_ON);

    } //Llave while
    
} // Llave del main
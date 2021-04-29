#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "../include/led.h"
#include "../include/semaforo.h"

void app_main() {

    ConfigurarLed(); //Pin donde se conectarán los leds
    IniciarSemaforo();

    while (1)
    {

        RefrescarSemaforo();

    } //llave while inf
    

} //llave main
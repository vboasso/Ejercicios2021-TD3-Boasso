#include "../include/led.h"
#include "../include/semaforo.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void IniciarSemaforo()
{

}

void RefrescarSemaforo()
{
    PrenderLed(Rojo);
    vTaskDelay(300);

    PrenderLed(Amarillo);
    vTaskDelay(50);

    ApagarLed(Rojo);
    ApagarLed(Amarillo);
    PrenderLed(Verde);
    vTaskDelay(150);

    ApagarLed(Verde);
    PrenderLed(Amarillo);
    vTaskDelay(50);

    ApagarLed(Amarillo);
    
}
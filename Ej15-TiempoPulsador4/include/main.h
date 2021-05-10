#include <stdio.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/FreeRTOSConfig.h"
#include "driver/gpio.h"

#define LED1        GPIO_NUM_25
#define PULSADOR1   GPIO_NUM_14
#define PROCESADORA 0
#define TW          5

//Prototipos de funciones
void TareaPulsador( void* taskParmPtr ); 
void InicializarIOs();
void ActualizarIOs();
void PrenderSalida();
void BorrarTarea();


typedef enum
{
    ESTADO_ESPERA,
    ESTADO_PULSADO,
    ESTADO_ALTO,
} estadoMEF_t;

// Variable de estado (global)
estadoMEF_t estadoActual;
TaskHandle_t xHandle1 = NULL; 
#include <stdio.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/FreeRTOSConfig.h"
#include "driver/gpio.h"

#define LED1        GPIO_NUM_25
#define PULSADOR1   GPIO_NUM_14
#define PERIODO_MS  1000
#define PERIODO     pdMS_TO_TICKS(PERIODO_MS)
#define PROCESADORA 0
#define PROCESADORB 1
#define TICKSMAX    (PERIODO)

void TareaDestellar( void* taskParmPtr ); //Prototipo de la función de la tarea

void TareaPulsador( void* taskParmPtr ); //Prototipo de la función de la tarea

typedef enum
{
    ESTADO_ESPERA,
    ESTADO_PULSADO,
    ESTADO_ALTO,
} estadoMEF_t;

// Variable de estado (global)
estadoMEF_t estadoActual;
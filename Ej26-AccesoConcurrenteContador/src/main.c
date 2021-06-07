// DE EJ 14

#include <stdio.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/FreeRTOSConfig.h"
#include "driver/gpio.h"
#include "pulsador.h"

#define T_ESPERA_MS  40
#define T_ESPERA     pdMS_TO_TICKS(T_ESPERA_MS)
#define PROCESADORA 0
#define PROCESADORB 1

gpio_int_type_t led [N_PULSADOR] = {GPIO_NUM_25, GPIO_NUM_26, GPIO_NUM_27};

void TareaDestello1( void* taskParmPtr ); //Prototipo de la función de la tarea led con un periodo igual al valor de contador y un duty del 50%.
void TareaDestello2( void* taskParmPtr ); // led con un periodo de 2 s y un tiempo de encendido de 2xcontador ms. En cada ciclo deberá decrementar el contador en 100.

void tarea_tecla( void* taskParmPtr ); //Borrar

void app_main()
{
    // Crear tarea en freeRTOS
    // Devuelve pdPASS si la tarea fue creada y agregada a la lista ready
    // En caso contrario devuelve pdFAIL.
    inicializarPulsador();

    for(int i = 0; i< N_PULSADOR; i++)
    {
        BaseType_t res = xTaskCreatePinnedToCore(
                TareaDestello1,                     	// Funcion de la tarea a ejecutar
                "Destello",   	                // Nombre de la tarea como String amigable para el usuario
                configMINIMAL_STACK_SIZE, 		// Cantidad de stack de la tarea
                i,                          	// Parametros de tarea
                tskIDLE_PRIORITY+i,         	// Prioridad de la tarea -> Queremos que este un nivel encima de IDLE
                NULL,                          		// Puntero a la tarea creada en el sistema
                PROCESADORA
         );
        // Gestion de errores
        if(res == pdFAIL)
        {
            printf( "Error al crear la tarea.\r\n" );
            while(true);					// si no pudo crear la tarea queda en un bucle infinito
        }
    }
}

// Implementacion de funcion de la tarea
void destello( void* taskParmPtr )
{
    // ---------- Configuraciones ------------------------------
    uint8_t indice = ( uint8_t ) taskParmPtr;
    
    gpio_pad_select_gpio(led[indice]);
    gpio_set_direction(led[indice], GPIO_MODE_OUTPUT);

    TickType_t dif;

    // ---------- Bucle infinito --------------------------
    while( true )
    {
        dif = obtenerDiferencia(indice);

        if( dif > TIEMPO_NO_VALIDO )
        {
            gpio_set_level( led[indice], 1 );
            vTaskDelay( dif );
            gpio_set_level( led[indice], 0 );
            borrarDiferencia(indice);
        }
        else
        {
            vTaskDelay( T_ESPERA );
        }
      
    } 
}













//TOMADO DE EJ 24


#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/FreeRTOSConfig.h"
/*==================[definiciones y macros]==================================*/

#include "freertos/semphr.h"

/*==================[declaraciones de funciones]====================*/
SemaphoreHandle_t mutex;

// Prototipo de funcion de la tarea
void tareaA( void* parametroTarea );
void tareaB( void* parametroTarea );

/*==================[funcion principal]======================================*/

void app_main()
{
    BaseType_t res;

    // ---------- CONFIGURACIONES ------------------------------

    res = xTaskCreatePinnedToCore (
              tareaA,                     // Funcion de la tarea a ejecutar
              ( const char * )"Tarea A",   	// Nombre de la tarea como String amigable para el usuario
              configMINIMAL_STACK_SIZE*2, 	// Cantidad de stack de la tarea
              NULL,                          	// Parametros de tarea
              tskIDLE_PRIORITY+1,         	// Prioridad de la tarea -> Queremos que este un nivel encima de IDLE
              NULL,                          		// Puntero a la tarea creada en el sistema
              0
          );

    configASSERT( res == pdPASS ); // gestion de errores

    res = xTaskCreatePinnedToCore (
              tareaB,                     // Funcion de la tarea a ejecutar
              ( const char * )"Tarea B",   	// Nombre de la tarea como String amigable para el usuario
              configMINIMAL_STACK_SIZE*2, 	// Cantidad de stack de la tarea
              NULL,                          	// Parametros de tarea
              tskIDLE_PRIORITY+1,         	// Prioridad de la tarea -> Queremos que este un nivel encima de IDLE
              NULL,                          		// Puntero a la tarea creada en el sistema
              1
          );

    configASSERT( res == pdPASS ); // gestion de errores

    mutex = xSemaphoreCreateMutex();
}

/*==================[definiciones de funciones]=====================*/

// Implementacion de funcion de la tarea
void tareaA( void* parametroTarea )
{
    while( true )
    {
        xSemaphoreTake( mutex , portMAX_DELAY ); //abrir seccion critica
        printf( "Hola, soy la tarea A " );
        printf( "y estoy ejecuntadome en el procesador numero 0\n" );
        xSemaphoreGive( mutex );	//cerrar seccion critica

        vTaskDelay( 1 / portTICK_RATE_MS );
    }
}

void tareaB( void* parametroTarea )
{
    while( true )
    {
        xSemaphoreTake( mutex , portMAX_DELAY ); //abrir seccion critica
        printf( "Hola, soy la tarea B " );
        printf( "y estoy ejecuntadome en el procesador numero 1\n" );
        xSemaphoreGive( mutex );	//cerrar seccion critica

        vTaskDelay( 1 / portTICK_RATE_MS );
    }
}


#endif


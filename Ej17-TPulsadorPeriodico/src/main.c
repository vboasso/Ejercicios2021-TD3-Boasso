#include "main.h"

//Variables globales
uint16_t tpulsado = 0;
uint16_t duty = 0;
TickType_t conteoTicksInicio = 0;
TickType_t conteoTicksFinal = 0;


void app_main() {

    // Crear tarea en freeRTOS
    // Devuelve pdPASS si la tarea fue creada y agregada a la lista ready
    // En caso contrario devuelve pdFAIL.
    BaseType_t res1 = xTaskCreatePinnedToCore(
    	TareaDestellar,                     	// Funcion de la tarea a ejecutar
        "Tarea led destellando",   	                // Nombre de la tarea como String amigable para el usuario
        configMINIMAL_STACK_SIZE, 		// Cantidad de stack de la tarea
        NULL,                          	// Parametros de tarea
        tskIDLE_PRIORITY+1,         	// Prioridad de la tarea -> Queremos que este un nivel encima de IDLE
        NULL,                          		// Puntero a la tarea creada en el sistema
        PROCESADORA
    );
    
    BaseType_t res2 = xTaskCreatePinnedToCore(
    	TareaPulsador,                     	// Funcion de la tarea a ejecutar
        "Tarea contar tiempo pulsado",   	                // Nombre de la tarea como String amigable para el usuario
        configMINIMAL_STACK_SIZE, 		// Cantidad de stack de la tarea
        NULL,                          	// Parametros de tarea
        tskIDLE_PRIORITY+1,         	// Prioridad de la tarea -> Queremos que este un nivel encima de IDLE
        NULL,                          		// Puntero a la tarea creada en el sistema
        PROCESADORB
    );

// Gestion de errores
	if(res1 == pdFAIL)
	{
		printf( "Error al crear la tarea destellar.\r\n" );
		while(true);					// si no pudo crear la tarea queda en un bucle infinito
	}
    if(res2 == pdFAIL)
	{
		printf( "Error al crear la tarea pulsador.\r\n" );
		while(true);					// si no pudo crear la tarea queda en un bucle infinito
	}
} //Llave main

// Implementacion de funcion de la tarea
void TareaDestellar( void* taskParmPtr )
{
    // ---------- Configuraciones ------------------------------
    gpio_pad_select_gpio(LED1);
    gpio_set_direction(LED1, GPIO_MODE_OUTPUT);

    TickType_t xPeriodicity =  PERIODO;			// Tarea periodica cada 1000 ms

    TickType_t xLastWakeTime = xTaskGetTickCount();

    
    

    // ---------- Bucle infinito --------------------------
    while( true )
    {
        duty = tpulsado;

        if ( duty > MAX_INC )
        {
            duty = 0;
            printf("El tiempo pulsado es mayor al ciclo de trabajo \n");
        }

        else
        {
            gpio_set_level(LED1, 1);
            vTaskDelay (duty);
            gpio_set_level(LED1, 0);
        }
        

        // Envia la tarea al estado bloqueado durante xPeriodicity (delay periodico)
        vTaskDelayUntil( &xLastWakeTime , xPeriodicity );
    }
}

void TareaPulsador( void* taskParmPtr )
{
    // ---------- Configuraciones ------------------------------
    gpio_pad_select_gpio(PULSADOR1);
    gpio_set_direction(PULSADOR1, GPIO_MODE_INPUT);

    while( true )
    {
        if(gpio_get_level(PULSADOR1)==1)
        {
            conteoTicksInicio = xTaskGetTickCount();
            while (gpio_get_level(PULSADOR1)==1)
            {
                /* code */
            }
            conteoTicksFinal = xTaskGetTickCount();
        }
        duty= conteoTicksFinal-conteoTicksInicio;

       
    }
}
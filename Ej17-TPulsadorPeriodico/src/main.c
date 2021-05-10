#include "main.h"

//Variables globales
int checkup=0;
int checkdown=0;
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


        if ( duty > TICKSMAX )
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
        

        
        vTaskDelayUntil( &xLastWakeTime , xPeriodicity ); // Envia la tarea al estado bloqueado durante xPeriodicity (delay periodico)
    }
}

void TareaPulsador( void* taskParmPtr )
{
    // ---------- Configuraciones ------------------------------
    gpio_pad_select_gpio(PULSADOR1);
    gpio_set_direction(PULSADOR1, GPIO_MODE_INPUT);
    gpio_set_pull_mode(PULSADOR1, GPIO_PULLDOWN_ONLY);

    while( true )
    {
        switch (estadoActual) {
		    case ESTADO_ESPERA:
            {
			    if(gpio_get_level(PULSADOR1)==1)
                {
				 estadoActual = ESTADO_PULSADO;
			    }
		    }
		    break;
		    case ESTADO_PULSADO:{
                if(checkup >= TW)
                {
		    	    conteoTicksInicio = xTaskGetTickCount();
                    estadoActual = ESTADO_ALTO;
                    checkup = 0;
                }
                else
                {
                    estadoActual = ESTADO_ESPERA;
                    checkup++;
                }
		    }
		    break;
		    case ESTADO_ALTO:{
		    	if(gpio_get_level(PULSADOR1)==0)
                {
                    if(checkdown >= TW)
                    {
                        conteoTicksFinal = xTaskGetTickCount();
                        duty = conteoTicksFinal-conteoTicksInicio;
                        estadoActual = ESTADO_ESPERA;
                        checkdown = 0;
                    }
                    checkdown++;
                }
		    }
		    break;
		    default:
            {		    	
		    	estadoActual = ESTADO_ESPERA;//Si cae en un estado no valido, reinicio
		    }
		    break;
	}

       
    }
}
#ifndef PULSADOR_H_
#define PULSADOR_H_
/*==================[ Inclusiones ]============================================*/
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "freertos/semphr.h" //incluyo la libreria del semaforo
#include "freertos/queue.h"

/*==================[ Definiciones ]===================================*/
#define TIEMPO_NO_VALIDO   0
#define N_PULSADOR      3                           //Cantidad de pulsadores

QueueHandle_t cola;

typedef enum
{
    ALTO,
    BAJO,
    DESCENDENTE,
    ASCENDENTE
} estadoPulsador;

typedef struct
{
    gpio_int_type_t tecla;
    estadoPulsador estado;   //variables
    TickType_t tiempoBajo;		//tiempo de la última transición del estado alto a bajo
    TickType_t tiempoAlto;		    //tiempo de la última transición del estado bajo a alto
    TickType_t diferenciaTiempo;	    //variables
} pulsadorInfo;

typedef struct //Estructura con los datos a enviar mediante la cola
{
    u_int8_t IndiceLed;
    TickType_t TiempoMedido;
} SendInfo;


/*==================[Prototipos de funciones]======================*/
void inicializarPulsador(  void );
TickType_t obtenerDiferencia( uint8_t  indice);
void borrarDiferencia( uint8_t  indice );

#endif
/*------------------------------------------------------------------*
 * nr_constants.h													*
 *																	*
 * Autor:	Ricardo Losada                                          *
 *                                                                  *
 * Constantes NR                                                    *
 *------------------------------------------------------------------*/

// Tiempo asignado a un salto en ticks
#define MAX_JUMP_TICKS      10 

// Costo maximo de una ruta
#define MAX_ROUTE_COST      100

// Maxima cantidad de entradas en la tabla de ruteo de un NR donde se almacenan rutas a SE (servidores externos)
#define MAX_NR_ROUTE_ENTRIES 10     

// Maxima cantidad de mensajes DATA en transito en un NR. Un NR debe recibir un mensaje, enviar un ACK y tranmistir el mensaje al proximo salto. Esto
// no es inmediato sino que es un proceso que lleva un tiempo. Este valor especifica la cantidad de mensajes diferentes que pueden se procesados "simulataneamente"
// Si se llega al maximo, los mensajes siguientes son descartados y el NR enviara un NACK a quien lo envio para informarle que por el momento no puede procesarlo
#define MAX_DATA_IN_TRANSIT 5//1024      

// Usado para almacenar momentaneamente los mensajes DATA codificados
#define MAX_BUFFER_SIZE 256

// Maximo valor asignado a un identificador de mensaje
#define MAX_MSG_ID                      128  

#define TICKS_CALM_MAX                  5   // Maxima cantidad de ticks que se aguarda entre sucesivas transmisiones
#define TICKS_CALM_MIN                  0   // Minima cantidad de ticks que se aguarda entre sucesivas transmisiones

#define TICKS_WAIT_NEXT_MAX             200 // Maxima cantidad de ticks entre sucesivos mensajes de un mismo origen para mantener la entrada en el fitro
#define TICKS_WAIT_NEXT_MIN              10 // Minima cantidad de ticks entre sucesivos mensajes de un mismo origen para mantener la entrada en el fitro

#define TICKS_ROUTE_VALID_MAX            600  // Maxima cantidad permitida de ticks que una ruta permanece valida 
#define TICKS_ROUTE_VALID_MIN            60  // Minima cantidad permitida de ticks que una ruta permanece valida 

#define TICKS_WAIT_ACK_MAX              60  // Maxima cantidad permitida de ticks que se espera por un ACK
#define TICKS_WAIT_ACK_MIN              5  // Minima cantidad permitida de ticks que se espera por un ACK

#define TICKS_ROUTE_BROADCAST_MAX  120  // Maxima cantidad permitida de ticks que se espera para publicar las rutas
#define TICKS_ROUTE_BROADCAST_MIN  60   // Minma cantidad permitida de ticks que se espera para publicar las rutas

#define RETRIES_MAX                      5  // Maxima cantidad permitida de reintentos (no incluye el primer intento) de envio de un DATO y espera del ACK
#define RETRIES_MIN                      0  // Minima cantidad permitida de reintentos (no incluye el primer intento) de envio de un DATO y espera del ACK

#define LOST_ADV_COUNT_MAX               3  // Maxima cantidad permitida de advertisments de ruta invalida a realizar antes de volver a aceptarla
#define LOST_ADV_COUNT_MIN               1  // Minima cantidad permitida de advertisments de ruta invalida a realizar antes de volver a aceptarla

#define SE_BIT_FOR_HOST_MAX              3  // Maxima cantidad permitida de bits que se pueden usar para codificar un host
#define SE_BIT_FOR_HOST_MIN              0  // Maxima cantidad permitida de bits que se pueden usar para codificar un host

#define TICKS_CHANNEL_RESERVED_MAX       10 // Maxima cantidad de ticks que se reserva el canal
#define TICKS_CHANNEL_RESERVED_MIN       5  // Minima cantidad de ticks que se reserva el canal

#define TICKS_ROUTE_BACKOFF_MAX       10 // Maxima cantidad de ticks de backoff
#define TICKS_ROUTE_BACKOFF_MIN       5  // Minima cantidad de ticks de backoff

#define TICKS_JUMP_DELAY_MAX             60 // Maxima cantidad de ticks para asignar al tiempo que demora un mensaje en saltar de un nodo al proximo
#define TICKS_JUMP_DELAY_MIN             10 // Minima cantidad de ticks para asignar al tiempo que demora un mensaje en saltar de un nodo al proximo
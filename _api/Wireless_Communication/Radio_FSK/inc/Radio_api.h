#ifndef __RADIO_API_H__
#define __RADIO_API_H__

#include "FSK.h"

#define FRAME_MESSAGE	0
#define FRAME_DATA		1

// Definición de la estructura _FskChart
typedef struct _FskChart {
    uint8_t *packet0;    // Puntero al primer conjunto de datos
    uint8_t *packet1;    // Puntero al primer conjunto de datos
    uint8_t *packet2;    // Puntero al segundo conjunto de datos
    uint8_t *packet3;    // Puntero al tercer conjunto de datos
    uint8_t *packet4;    // Puntero al cuarto conjunto de datos
    uint8_t *packet5;    // Puntero al n conjunto de datos
    uint8_t *packet6;    // Puntero al n conjunto de datos
    uint8_t *packet7;    // Puntero al n conjunto de datos
    uint8_t *packet8;    // Puntero al n conjunto de datos
    uint8_t *packet9;    // extra packet 
}FskChart;

#define PacketsCounts 9

enum FskApiStates
{
	SENDING_CHART,
	SENDING_MESSAGE,
	WAITING,
};

void RadioInit(void);
EMIC:define(inits.RadioInit,RadioInit)

void RadioPoll(void);
EMIC:define(polls.RadioPoll,RadioPoll)

void pFSKD();
void pFSKM(char* message);
void RadioSleep(void);
void RadioWakeUp(void);

#endif
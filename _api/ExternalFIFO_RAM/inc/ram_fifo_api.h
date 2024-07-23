/******************************************************************************

  @file     RAM_api.h

  @brief    API Library to use RAM module

  @author   Ramiro Alarcon Lasagno

  @date     26/10/2023

  @version  v0.0.1

 ******************************************************************************/

#ifndef _RAM_API_H_
#define _RAM_API_H_

#include <xc.h>
//#include <stdint.h>

// Definiciones para el tamaño del buffer y las direcciones de inicio en la RAM
#define TOTAL_PAGES 8192
#define PAGE_SIZE 1024  // Cada página tiene 1024 bytes

#define RAM1_START 0x0000
#define RAM1_END (RAM1_START + (TOTAL_PAGES * PAGE_SIZE) - 1)

#define RAM2_START 0x0000  // Asumiendo que RAM2 tiene la misma configuración que RAM1
#define RAM2_END (RAM2_START + (TOTAL_PAGES * PAGE_SIZE) - 1)

// Funciones de inicialización
void RAM_api_Init(void);

EMIC:define(inits.RAM_api_Init,RAM_api_Init)

// Funciones de escritura y lectura en la cola circular
void FIFO_Push_Single(uint8_t cs, char data);

char FIFO_Pop_Single(uint8_t cs);

void FIFO_Push(uint8_t cs, uint32_t *data, uint8_t length);

void FIFO_Pop(uint8_t cs, uint32_t *buffer, uint8_t length);

void RAM_Reset(void);

#endif
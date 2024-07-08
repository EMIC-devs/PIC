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

// Definiciones para el tamaño del buffer y la dirección de inicio en la RAM
#define TOTAL_PAGES 8192
#define HALF_PAGE_COUNT (TOTAL_PAGES / 2)
#define PAGE_SIZE 1024  // Cada página tiene 1024 bytes
// Se divide la RAM en dos mitades.
#define FIRST_HALF_START 0x0000
#define FIRST_HALF_END (FIRST_HALF_START + (HALF_PAGE_COUNT * PAGE_SIZE) - 1)

#define SECOND_HALF_START (FIRST_HALF_END + 1)
#define SECOND_HALF_END (SECOND_HALF_START + (HALF_PAGE_COUNT * PAGE_SIZE) - 1)

// Funciones de inicialización
void RAM_api_Init(void);

EMIC:define(inits.RAM_api_Init,RAM_api_Init)

// Funciones de escritura y lectura en la cola circular
void FIFO_Push(uint8_t half, char *data, uint8_t length);

void FIFO_Pull(uint8_t half, char *buffer, uint8_t length);

void RAM_Reset(void);

#endif
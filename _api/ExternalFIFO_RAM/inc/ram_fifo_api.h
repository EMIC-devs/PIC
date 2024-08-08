/******************************************************************************

  @file     RAM_api.h

  @brief    API Library to use RAM module

  @author   Ramiro Alarcon Lasagno

  @date     26/10/2023

  @version  v0.0.1

 ******************************************************************************/

#ifndef _RAM_API_H_
#define _RAM_API_H_

/*==================[inclusions]=============================================*/
#include <xc.h>

// Definiciones para el tamaño del buffer y las direcciones de inicio en la RAM
#define TOTAL_PAGES 8192
#define PAGE_SIZE 1024  // Cada página tiene 1024 bytes

#define RAM1_START 0x0000
#define RAM1_END (RAM1_START + (TOTAL_PAGES * PAGE_SIZE) - 1)

#define RAM2_START 0x0000  // Asumiendo que RAM2 tiene la misma configuración que RAM1
#define RAM2_END (RAM2_START + (TOTAL_PAGES * PAGE_SIZE) - 1)

EMIC:define(inits.RAM_api_Init,RAM_api_Init)

/* // Declaraciones de funciones para el RAM driver
void RAM_Driver_writeUInt16_RAM1(uint16_t data);
void RAM_Driver_writeUInt16_RAM2(uint16_t data);
uint16_t RAM_Driver_readUInt16_RAM1(void);
uint16_t RAM_Driver_readUInt16_RAM2(void);
uint16_t RAM_Driver_dataCount_RAM1(void);
uint16_t RAM_Driver_dataCount_RAM2(void);

// Declaraciones de funciones para FIFO
void FIFO_Push_Format(uint8_t cs, char* format_, ...);
void FIFO_Push_Single(uint8_t cs, uint16_t data);
uint16_t FIFO_Pop_Single(uint8_t cs); */

/*==================[internal functions declaration]===========================*/
void FIFO_Push_Single_8(uint8_t cs, uint8_t data);
uint8_t FIFO_Pop_Single_8(uint8_t cs);
void FIFO_Push_Single_16(uint8_t cs, uint16_t data);
uint16_t FIFO_Pop_Single_16(uint8_t cs);
void FIFO_Push_Single_32(uint8_t cs, uint32_t data);
uint32_t FIFO_Pop_Single_32(uint8_t cs);

// Declaraciones de funciones de inicialización y reseteo

void RAM_Reset(void);
void RAM_api_Init(void);

#endif // _RAM_API_H_

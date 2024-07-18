/***************************************************************************

  @file     RAM_api.c

  @brief    API Library to use RAM module

  @autor    Ramiro Alarcon Lasagno

  @fecha    26/10/2023

  @version  v0.0.1
  
 ******************************************************************************/
//#include <stdint.h>
#include <xc.h>
#include "inc/ram_fifo_api.h"



//##################################################################################//
// Punteros de FIFO para cada mitad
uint32_t fifo_write_pointer_1 = RAM1_START;
uint32_t fifo_read_pointer_1 = RAM1_START;
uint32_t fifo_write_pointer_2 = RAM2_START;
uint32_t fifo_read_pointer_2 = RAM2_START;
//##################################################################################//
// Función de inicialización de la RAM
void RAM_api_Init(void) {
    RAM_Driver_Init();  // Inicializa el driver de la RAM asegurándote que no resetee los punteros
    RAM_Reset();
}
//##################################################################################//
// Función para añadir datos al FIFO
void FIFO_Push(uint8_t cs, char *data, uint8_t length) {
    if (cs != 1 && cs != 2) {
        // Manejo de error: cs no es válido
        return;
    }

    uint32_t *write_pointer = (cs == 1) ? &fifo_write_pointer_1 : &fifo_write_pointer_2;
    uint32_t end_address = (cs == 1) ? RAM1_END : RAM2_END;

    for (uint32_t i = 0; i < length; i++) {
        if (*write_pointer > end_address) {
            break;  // Detiene la escritura si el buffer está lleno
        }
        RAM_Driver_writeData(cs, *write_pointer, (const uint32_t*)&data[i], 1);
        (*write_pointer)++;
    }
}
//##################################################################################//
// Función para retirar datos del FIFO
void FIFO_Pop(uint8_t cs, char *buffer, uint8_t length) {
    if (cs != 1 && cs != 2) {
        // Manejo de error: cs no es válido
        return;
    }

    uint32_t *read_pointer = (cs == 1) ? &fifo_read_pointer_1 : &fifo_read_pointer_2;
    uint32_t write_pointer = (cs == 1) ? fifo_write_pointer_1 : fifo_write_pointer_2;
    uint32_t bytes_read = 0;

    while (bytes_read < length && *read_pointer < write_pointer) {
        RAM_Driver_readData(cs, *read_pointer, (uint32_t*)&buffer[bytes_read], 1);
        (*read_pointer)++;
        bytes_read++;
    }
}
//##################################################################################//
// Función para resetear la RAM
void RAM_Reset(void) {
    fifo_write_pointer_1 = RAM1_START;
    fifo_read_pointer_1 = RAM1_START;
    fifo_write_pointer_2 = RAM2_START;
    fifo_read_pointer_2 = RAM2_START;
}

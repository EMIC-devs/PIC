/***************************************************************************

  @file     RAM_api.c

  @brief    API Library to use RAM module

  @autor    Ramiro Alarcon Lasagno

  @fecha    26/10/2023

  @version  v0.0.1
  
 ******************************************************************************/
#include <xc.h>
#include <stdarg.h>
#include <stdio.h>
/* #include "inc/stream.h"
#include "inc/streamIn.h"
#include "inc/streamOut.h" */
#include "inc/ram_fifo_api.h"

//##################################################################################//
// Punteros de FIFO para cada mitad
uint32_t fifo_write_pointer_1 = RAM1_START;
uint32_t fifo_read_pointer_1 = RAM1_START;
uint32_t fifo_write_pointer_2 = RAM2_START;
uint32_t fifo_read_pointer_2 = RAM2_START;

//##################################################################################//
// Función para inicializar la API de RAM
void RAM_api_Init(void) {
    RAM_Driver_Init();  // Inicializa el driver de la RAM asegurándote que no resetee los punteros
    RAM_Reset();
}

//##################################################################################//
// Función para añadir un solo dato de tipo char a la FIFO
void FIFO_Push_Single_8(uint8_t cs, uint8_t data) {
    if (cs != 1 && cs != 2) {
        // Manejo de error: cs no es válido
        return;
    }

    uint32_t *write_pointer = (cs == 1) ? &fifo_write_pointer_1 : &fifo_write_pointer_2;
    uint32_t end_address = (cs == 1) ? RAM1_END : RAM2_END;

    if (*write_pointer <= end_address) {
        RAM_Driver_writeData8(cs, *write_pointer, &data, 1);
        (*write_pointer)++;
    }
}

//##################################################################################//
// Función para retirar un solo dato de tipo char de la FIFO
uint8_t FIFO_Pop_Single_8(uint8_t cs) {
    if (cs != 1 && cs != 2) {
        // Manejo de error: cs no es válido
        return 0;  // Retornar un valor por defecto
    }

    uint32_t *read_pointer = (cs == 1) ? &fifo_read_pointer_1 : &fifo_read_pointer_2;
    uint32_t write_pointer = (cs == 1) ? fifo_write_pointer_1 : fifo_write_pointer_2;

    if (*read_pointer < write_pointer) {
        uint8_t temp_data;
        RAM_Driver_readData8(cs, *read_pointer, &temp_data, 1);
        (*read_pointer)++;
        return temp_data;
    } else {
        // Manejo de error: no hay datos para leer
        return 0;  // Retornar un valor por defecto
    }
}

//##################################################################################//
// Función para añadir un solo dato de tipo uint16_t a la FIFO
void FIFO_Push_Single_16(uint8_t cs, uint16_t data) {
    if (cs != 1 && cs != 2) {
        // Manejo de error: cs no es válido
        return;
    }

    uint32_t *write_pointer = (cs == 1) ? &fifo_write_pointer_1 : &fifo_write_pointer_2;
    uint32_t end_address = (cs == 1) ? RAM1_END : RAM2_END;

    if (*write_pointer <= end_address) {
        RAM_Driver_writeData16(cs, *write_pointer, &data, 1);
        (*write_pointer)++;
    }
}

//##################################################################################//
// Función para retirar un solo dato de tipo uint16_t de la FIFO
uint16_t FIFO_Pop_Single_16(uint8_t cs) {
    if (cs != 1 && cs != 2) {
        // Manejo de error: cs no es válido
        return 0;  // Retornar un valor por defecto
    }

    uint32_t *read_pointer = (cs == 1) ? &fifo_read_pointer_1 : &fifo_read_pointer_2;
    uint32_t write_pointer = (cs == 1) ? fifo_write_pointer_1 : fifo_write_pointer_2;

    if (*read_pointer < write_pointer) {
        uint16_t temp_data;
        RAM_Driver_readData16(cs, *read_pointer, &temp_data, 1);
        (*read_pointer)++;
        return temp_data;
    } else {
        // Manejo de error: no hay datos para leer
        return 0;  // Retornar un valor por defecto
    }
}

//##################################################################################//
// Función para añadir un solo dato de tipo uint32_t a la FIFO
void FIFO_Push_Single_32(uint8_t cs, uint32_t data) {
    if (cs != 1 && cs != 2) {
        // Manejo de error: cs no es válido
        return;
    }

    uint32_t *write_pointer = (cs == 1) ? &fifo_write_pointer_1 : &fifo_write_pointer_2;
    uint32_t end_address = (cs == 1) ? RAM1_END : RAM2_END;

    if (*write_pointer <= end_address) {
        RAM_Driver_writeData32(cs, *write_pointer, &data, 1);
        (*write_pointer)++;
    }
}

//##################################################################################//
// Función para retirar un solo dato de tipo uint32_t de la FIFO
uint32_t FIFO_Pop_Single_32(uint8_t cs) {
    if (cs != 1 && cs != 2) {
        // Manejo de error: cs no es válido
        return 0;  // Retornar un valor por defecto
    }

    uint32_t *read_pointer = (cs == 1) ? &fifo_read_pointer_1 : &fifo_read_pointer_2;
    uint32_t write_pointer = (cs == 1) ? fifo_write_pointer_1 : fifo_write_pointer_2;

    if (*read_pointer < write_pointer) {
        uint32_t temp_data;
        RAM_Driver_readData32(cs, *read_pointer, &temp_data, 1);
        (*read_pointer)++;
        return temp_data;
    } else {
        // Manejo de error: no hay datos para leer
        return 0;  // Retornar un valor por defecto
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


/* //##################################################################################//
// Definir estructuras de stream
const streamOut_t streamOut_RAM1 = {RAM_Driver_writeUInt16_RAM1, RAM_Driver_dataCount_RAM1};
const streamOut_t streamOut_RAM2 = {RAM_Driver_writeUInt16_RAM2, RAM_Driver_dataCount_RAM2};
const streamIn_t streamIn_RAM1 = {RAM_Driver_readUInt16_RAM1, RAM_Driver_dataCount_RAM1};
const streamIn_t streamIn_RAM2 = {RAM_Driver_readUInt16_RAM2, RAM_Driver_dataCount_RAM2};

//##################################################################################//
// ********** Funciones de escritura y lectura para RAM Driver ************

// Escribe un solo uint16_t en la RAM1
void RAM_Driver_writeUInt16_RAM1(uint16_t data) {
    if (fifo_write_pointer_1 <= RAM1_END) {
        RAM_Driver_writeData16(1, fifo_write_pointer_1, &data, 1);
        fifo_write_pointer_1 += sizeof(uint16_t);
    }
}

// Escribe un solo uint16_t en la RAM2
void RAM_Driver_writeUInt16_RAM2(uint16_t data) {
    if (fifo_write_pointer_2 <= RAM2_END) {
        RAM_Driver_writeData16(2, fifo_write_pointer_2, &data, 1);
        fifo_write_pointer_2 += sizeof(uint16_t);
    }
}

// Lee un solo uint16_t desde la RAM1
uint16_t RAM_Driver_readUInt16_RAM1(void) {
    if (fifo_read_pointer_1 < fifo_write_pointer_1) {
        uint16_t temp_data;
        RAM_Driver_readData16(1, fifo_read_pointer_1, &temp_data, 1);
        fifo_read_pointer_1 += sizeof(uint16_t);
        return temp_data;
    } else {
        return 0;  // No hay datos para leer
    }
}

// Lee un solo uint16_t desde la RAM2
uint16_t RAM_Driver_readUInt16_RAM2(void) {
    if (fifo_read_pointer_2 < fifo_write_pointer_2) {
        uint16_t temp_data;
        RAM_Driver_readData16(2, fifo_read_pointer_2, &temp_data, 1);
        fifo_read_pointer_2 += sizeof(uint16_t);
        return temp_data;
    } else {
        return 0;  // No hay datos para leer
    }
}

// Devuelve el número de datos disponibles para leer en la RAM1
uint16_t RAM_Driver_dataCount_RAM1(void) {
    return (fifo_write_pointer_1 - fifo_read_pointer_1) / sizeof(uint16_t);
}

// Devuelve el número de datos disponibles para leer en la RAM2
uint16_t RAM_Driver_dataCount_RAM2(void) {
    return (fifo_write_pointer_2 - fifo_read_pointer_2) / sizeof(uint16_t);
}

//##################################################################################//
// Función para añadir datos formateados a la FIFO
void FIFO_Push_Format(uint8_t cs, char* format_, ...) {
    if (cs != 1 && cs != 2) {
        // Manejo de error: cs no es válido
        return;
    }

    const streamOut_t *streamOut_RAM = (cs == 1) ? &streamOut_RAM1 : &streamOut_RAM2;

    va_list arg;
    va_start(arg, format_);

    //uint16_t data = va_arg(arg, int);

    sendDataToStream(streamOut_RAM, format_, arg);
    va_end(arg);
}

//##################################################################################//
// Función para añadir un solo dato de tipo uint32_t a la FIFO
void FIFO_Push_Single(uint8_t cs, uint16_t data) {
    FIFO_Push_Format(cs, "%u", data);
}

//##################################################################################//
// Función para retirar un solo dato de tipo uint16_t de la FIFO
uint16_t FIFO_Pop_Single(uint8_t cs) {
    if (cs != 1 && cs != 2) {
        // Manejo de error: cs no es válido
        return 0;  // Retornar un valor por defecto
    }

    const streamIn_t *streamIn_RAM = (cs == 1) ? &streamIn_RAM1 : &streamIn_RAM2;
    return streamIn_RAM->get();
} */
/***************************************************************************

  @file     RAM_api.c

  @brief    API Library to use RAM module

  @author   Ramiro Alarcon Lasagno

  @date     26/10/2023

  @version  v0.0.1
  
 ******************************************************************************/
//#include <stdint.h>

//##################################################################################//
// Punteros de FIFO para cada mitad
uint32_t fifo_write_pointer_1 = FIRST_HALF_START;
uint32_t fifo_read_pointer_1 = FIRST_HALF_START;
uint32_t fifo_write_pointer_2 = SECOND_HALF_START;
uint32_t fifo_read_pointer_2 = SECOND_HALF_START;
//##################################################################################//
// Función de inicialización de la RAM
void RAM_api_Init(void) {
    RAM_Driver_Init();  // Inicializa el driver de la RAM asegurándote que no resetee los punteros
    fifo_write_pointer_1 = FIRST_HALF_START;
    fifo_read_pointer_1 = FIRST_HALF_START;
    fifo_write_pointer_2 = SECOND_HALF_START;
    fifo_read_pointer_2 = SECOND_HALF_START;
}
//##################################################################################//
void FIFO_Push(uint8_t half, char *data, uint8_t length) {
    if (half != 1 && half != 2) {
        return 0;  // Retorna 0 si el número de mitad es inválido
    }

    uint32_t *write_pointer = (half == 1) ? &fifo_write_pointer_1 : &fifo_write_pointer_2;
    uint32_t end_address = (half == 1) ? FIRST_HALF_END : SECOND_HALF_END;

    for (uint32_t i = 0; i < length; i++) {
        if (*write_pointer > end_address) {
            break;  // Detiene la escritura si el buffer está lleno
        }
        RAM_Driver_writeData(*write_pointer, data[i]);
        (*write_pointer)++;
    }

}
//##################################################################################//
void FIFO_Pull(uint8_t half, char *buffer, uint8_t length) {
    if (half != 1 && half != 2) {
        return 0;  // Retorna 0 si el número de mitad es inválido
    }

    uint32_t *read_pointer = (half == 1) ? &fifo_read_pointer_1 : &fifo_read_pointer_2;
    uint32_t write_pointer = (half == 1) ? fifo_write_pointer_1 : fifo_write_pointer_2;

    while (bytes_read < length && *read_pointer < write_pointer) {
        buffer[bytes_read] = RAM_Driver_readData(*read_pointer);
        (*read_pointer)++;
    }

}
//##################################################################################//
void RAM_Reset(void) {
    // Resetear los punteros FIFO para cada mitad
    fifo_write_pointer_1 = FIRST_HALF_START;
    fifo_read_pointer_1 = FIRST_HALF_START;
    fifo_write_pointer_2 = SECOND_HALF_START;
    fifo_read_pointer_2 = SECOND_HALF_START;
}
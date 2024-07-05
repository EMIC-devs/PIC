/*************************************************************************//**
  @file     APS6404L.c

  @brief    Biblioteca de controlador para utilizar RAM

  @author   Ramiro Alarcón Lasagno basado en "Ram memory driver" de Rottoli Luciano Gabriel

  @date     22/10/2023

  @version  v0.0.1 - Versión inicial.

 ******************************************************************************/
#ifndef _APS6404L_H_.{port}._C__
#define _APS6404L_H_.{port}._C__

/*==================[inclusions]=============================================*/
#include <xc.h>
#include "spi.{port}.h"
#include "stream.h"
#include "streamOut.h"
#include "streamIn.h"

/*==================[internal functions implementations]======================*/
/***********************************************************************************************************************/
// Función de inicialización de la RAM
/***********************************************************************************************************************/
/**
 * @brief Initializes the Ram module.
 */
void RAM_Driver_Init(void)
{
    // Configura los pines base del ecometro como digitales
    //_ANSC14 = 0x00;
    //_ANSC13 = 0x00;

    // Configura SIO2 como salida GPIO (actualmente no se usa para bloqueo de escritura)
    HAL_GPIO_PinCfg(RAM_SIO2, GPIO_OUTPUT);     // SIO2 IS WRITE LOCK, currently not in use, **CHANGE THIS IF OTHERWISE**
    HAL_GPIO_PinSet(RAM_SIO2, GPIO_HIGH);       // Establece SIO2 en alto

    // Configura nHOLD como salida GPIO y lo establece en alto
    HAL_GPIO_PinCfg(nHOLD, GPIO_OUTPUT);
    HAL_GPIO_PinSet(nHOLD, GPIO_HIGH);

    // Configura RAM_SIO0 como salida GPIO (MOSI)
    HAL_GPIO_PinCfg(RAM_SIO0, GPIO_INPUT);     // MOSI
    // Configura RAM_SIO1 como entrada GPIO (MISO)
    HAL_GPIO_PinCfg(RAM_SIO1, GPIO_OUTPUT);      // MISO
    // Configura RAM_CS como salida GPIO
    HAL_GPIO_PinCfg(RAM_CS, GPIO_OUTPUT);
    HAL_GPIO_PinSet(RAM_CS, GPIO_HIGTH);         // Establece RAM_CS en alto

    // Configura RAM_SCK como salida GPIO
    HAL_GPIO_PinCfg(RAM_SCK, GPIO_OUTPUT);

    // Inicializa el módulo SPI4 en modo de 8 bits, sin estructura de trama y sin interrupciones
    SPI4_init(0, 0);

    // Espera 1 milisegundo para asegurar que las configuraciones previas se completen
    __delay_ms(1);

}
/***********************************************************************************************************************/
// Escribe datos en la RAM
/***********************************************************************************************************************/
/**
 * @brief Writes data to the Ram memory.
 * @param address Memory address to write to.
 * @param data Pointer to the data buffer.
 * @param length Number of bytes to write.
 */
void RAM_Driver_writeData(uint32_t address, const uint8_t *data, uint16_t length)
{
    HAL_GPIO_PinSet(RAM_CS, GPIO_LOW);  // Activar la selección del chip

    xchangeSPI4b_8(RAM_WRITE_CMD);  // Enviar comando de escritura
    xchangeSPI4b_8((address >> 16) & 0xFF);  // Parte alta de la dirección
    xchangeSPI4b_8((address >> 8) & 0xFF);   // Parte media de la dirección
    xchangeSPI4b_8(address & 0xFF);          // Parte baja de la dirección

    for (uint16_t i = 0; i < length; i++)
    {
        xchangeSPI4b_8(data[i]);  // Enviar datos
    }

    HAL_GPIO_PinSet(RAM_CS, GPIO_HIGH);  // Desactivar la selección del chip
}
/***********************************************************************************************************************/
// Lee datos de la RAM
/***********************************************************************************************************************/
/**
 * @brief Reads data from the Ram memory.
 * @param address Memory address to read from.
 * @param buffer Pointer to the buffer to store the read data.
 * @param length Number of bytes to read.
 */
void RAM_Driver_readData(uint32_t address, uint8_t *buffer, uint16_t length)
{
    HAL_GPIO_PinSet(RAM_CS, GPIO_LOW);  // Activar la selección del chip

    xchangeSPI4b_8(RAM_READ_CMD);  // Enviar comando de lectura

    xchangeSPI4b_8((address >> 16) & 0xFF);  // Parte alta de la dirección
    xchangeSPI4b_8((address >> 8) & 0xFF);   // Parte media de la dirección
    xchangeSPI4b_8(address & 0xFF);          // Parte baja de la dirección

    for (uint16_t i = 0; i < length; i++)
    {
        buffer[i] = xchangeSPI4b_8(0);  // Leer datos
    }

    HAL_GPIO_PinSet(RAM_CS, GPIO_HIGH);  // Desactivar la selección del chip
}
/***********************************************************************************************************************/
// Resetea la RAM
/***********************************************************************************************************************/
/**
 * @brief Resets the Ram memory.
 */
void RAM_Driver_reset(void)
{
    HAL_GPIO_PinSet(RAM_CS, GPIO_LOW);     // Chip select activo
    
    xchangeSPI4b_8(RAM_RSTEN);             // Envía comando de habilitación de reset
    // Según la especificación, los comandos deben enviarse rápidamente uno tras otro
    xchangeSPI4b_8(RAM_RST);               // Envía comando de reset

    HAL_GPIO_PinSet(RAM_CS, GPIO_HIGH);    // Chip select inactivo

    __delay_us(50);                        // Espera un tiempo suficiente para que el reset se complete
}

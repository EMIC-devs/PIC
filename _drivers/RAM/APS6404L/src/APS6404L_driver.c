/*************************************************************************//**
  @file     APS6404L.c

  @brief    Biblioteca de controlador para utilizar RAM

  @autor    Ramiro Alarcón Lasagno basado en "Ram memory driver" de Rottoli Luciano Gabriel

  @date     22/10/2023

  @version  v0.0.1 - Versión inicial.

 ******************************************************************************/
#ifndef _APS6404L_H_.{port}._C__
#define _APS6404L_H_.{port}._C__

/*==================[inclusions]=============================================*/
#include <xc.h>
#include "inc/spi.{port}..h"
#include "inc/GPIO.h"
#include <libpic30.h>

/* Spi driver name adaptation */
// @{
/* #define RPOUT_MEM_CS_RAM1     RPOUT_MEM_CS_RAM1 //44
#define RPOUT_MEM_CS_RAM2     RPOUT_MEM_CS_RAM2 //45
#define RPOUT_RAM_MOSI    RPOUT_MEM_MOSI //46
#define RPOUT_RAM_MISO    RPIN_MEM_MISO //47
#define RPOUT_RAM_CLK     RPOUT_MEM_CLK //49

#define TRIS_RAM_MOSI     TRIS_MEM_MOSI
#define TRIS_RAM_CLK      TRIS_MEM_CLK
#define TRIS_MEM_CS_RAM1      TRIS_MEM_CS_RAM1
#define TRIS_MEM_CS_RAM2      TRIS_MEM_CS_RAM2
#define TRIS_RAM_MISO     TRIS_MEM_MISO
#define PIN_MEM_CS_RAM1       PIN_MEM_CS_RAM1
#define PIN_MEM_CS_RAM2       PIN_MEM_CS_RAM2 */
// }

/* SPI Ram macros */
#define RAM_RSTEN         0x66    // Habilita el reinicio del dispositivo (Reset Enable)
#define RAM_RST           0x99    // Reinicia la memoria RAM (Reset Memory)
#define RAM_READ_CMD      0x03    // Lee datos de la memoria (Read Memory)
#define RAM_WRITE_CMD     0x02    // Habilita las operaciones de escritura (Write Enable)

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
    HAL_GPIO_PinCfg(MEM_SIO2, GPIO_OUTPUT);     // SIO2 IS WRITE LOCK, currently not in use, **CHANGE THIS IF OTHERWISE**
    HAL_GPIO_PinSet(MEM_SIO2, GPIO_HIGH);       // Establece SIO2 en alto

    // Configura MEM_HOLD como salida GPIO y lo establece en alto
    HAL_GPIO_PinCfg(MEM_HOLD, GPIO_OUTPUT);
    HAL_GPIO_PinSet(MEM_HOLD, GPIO_HIGH);

    // Configura MEM_MOSI como salida GPIO (MOSI)
    HAL_GPIO_PinCfg(MEM_MOSI, GPIO_INPUT);     // MOSI
    // Configura MEM_MISO como entrada GPIO (MISO)
    HAL_GPIO_PinCfg(MEM_MISO, GPIO_OUTPUT);      // MISO
    // Configura MEM_CS_RAM1 y MEM_CS_RAM2 como salida GPIO
    HAL_GPIO_PinCfg(MEM_CS_RAM1, GPIO_OUTPUT);
    HAL_GPIO_PinCfg(MEM_CS_RAM2, GPIO_OUTPUT);
    HAL_GPIO_PinSet(MEM_CS_RAM1, GPIO_HIGH);         // Establece MEM_CS_RAM1 en alto
    HAL_GPIO_PinSet(MEM_CS_RAM2, GPIO_HIGH);         // Establece MEM_CS_RAM2 en alto

    // Configura MEM_CLK como salida GPIO
    HAL_GPIO_PinCfg(MEM_CLK, GPIO_OUTPUT);

    // Inicializa el módulo SPI4 en modo de 8 bits, sin estructura de trama y sin interrupciones
    SPI.{port}._init(0, 0);

    // Espera 1 milisegundo para asegurar que las configuraciones previas se completen
    __delay_ms(1);
}
/***********************************************************************************************************************/
// Escribe datos en la RAM
/***********************************************************************************************************************/
/**
 * @brief Writes data to the Ram memory.
 * @param cs Chip select (1 o 2).
 * @param address Memory address to write to.
 * @param data Pointer to the data buffer.
 * @param length Number of bytes to write.
 */
void RAM_Driver_writeData(uint8_t cs, uint32_t address, const uint32_t *data, uint16_t length)
{
    if (cs == 1) {
        HAL_GPIO_PinSet(MEM_CS_RAM1, GPIO_LOW);  // Activar la selección del chip 1
    } else if (cs == 2) {
        HAL_GPIO_PinSet(MEM_CS_RAM2, GPIO_LOW);  // Activar la selección del chip 2
    } else {
        // Manejo de error: cs no es válido
        return;
    }

    xchangeSPI.{port}.b_8(RAM_WRITE_CMD);  // Enviar comando de escritura
    xchangeSPI.{port}.b_8((address >> 16) & 0xFF);  // Parte alta de la dirección
    xchangeSPI.{port}.b_8((address >> 8) & 0xFF);   // Parte media de la dirección
    xchangeSPI.{port}.b_8(address & 0xFF);          // Parte baja de la dirección

    for (uint16_t i = 0; i < length; i++)
    {
        xchangeSPI.{port}.b_8(data[i]);  // Enviar datos
    }

    if (cs == 1) {
        HAL_GPIO_PinSet(MEM_CS_RAM1, GPIO_HIGH);  // Desactivar la selección del chip 1
    } else if (cs == 2) {
        HAL_GPIO_PinSet(MEM_CS_RAM2, GPIO_HIGH);  // Desactivar la selección del chip 2
    }
}
/***********************************************************************************************************************/
// Lee datos de la RAM
/***********************************************************************************************************************/
/**
 * @brief Reads data from the Ram memory.
 * @param cs Chip select (1 o 2).
 * @param address Memory address to read from.
 * @param buffer Pointer to the buffer to store the read data.
 * @param length Number of bytes to read.
 */
void RAM_Driver_readData(uint8_t cs, uint32_t address, uint32_t *buffer, uint16_t length)
{
    if (cs == 1) {
        HAL_GPIO_PinSet(MEM_CS_RAM1, GPIO_LOW);  // Activar la selección del chip 1
    } else if (cs == 2) {
        HAL_GPIO_PinSet(MEM_CS_RAM2, GPIO_LOW);  // Activar la selección del chip 2
    } else {
        // Manejo de error: cs no es válido
        return;
    }

    xchangeSPI.{port}.b_8(RAM_READ_CMD);  // Enviar comando de lectura

    xchangeSPI.{port}.b_8((address >> 16) & 0xFF);  // Parte alta de la dirección
    xchangeSPI.{port}.b_8((address >> 8) & 0xFF);   // Parte media de la dirección
    xchangeSPI.{port}.b_8(address & 0xFF);          // Parte baja de la dirección

    for (uint16_t i = 0; i < length; i++)
    {
        buffer[i] = xchangeSPI.{port}.b_8(0);  // Leer datos
    }

    if (cs == 1) {
        HAL_GPIO_PinSet(MEM_CS_RAM1, GPIO_HIGH);  // Desactivar la selección del chip 1
    } else if (cs == 2) {
        HAL_GPIO_PinSet(MEM_CS_RAM2, GPIO_HIGH);  // Desactivar la selección del chip 2
    }
}
/***********************************************************************************************************************/
// Resetea la RAM
/***********************************************************************************************************************/
/**
 * @brief Resets the Ram memory.
 */
void RAM_Driver_reset(void)
{
    HAL_GPIO_PinSet(MEM_CS_RAM1, GPIO_LOW);     // Chip select activo
    HAL_GPIO_PinSet(MEM_CS_RAM2, GPIO_LOW);     // Chip select activo
    
    xchangeSPI.{port}.b_8(RAM_RSTEN);             // Envía comando de habilitación de reset
    // Según la especificación, los comandos deben enviarse rápidamente uno tras otro
    xchangeSPI.{port}.b_8(RAM_RST);               // Envía comando de reset

    HAL_GPIO_PinSet(MEM_CS_RAM1, GPIO_HIGH);    // Chip select inactivo
    HAL_GPIO_PinSet(MEM_CS_RAM2, GPIO_HIGH);    // Chip select inactivo

    __delay_us(50);                        // Espera un tiempo suficiente para que el reset se complete
}

#endif // _APS6404L_H_.{port}._C__

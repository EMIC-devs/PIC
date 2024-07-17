/*************************************************************************//**
  @file     APS6404L.h

  @brief    Driver Library to use RAM

  @author   Ramiro Alarcon Lasagno

  @date     25/10/2023

  @version  v0.0.1 - Initial release.
 ******************************************************************************/
#ifndef _APS6404L_H_
#define _APS6404L_H_

/*==================[inclusions]=============================================*/
#include <xc.h>
#include "spi.{port}.h"

/*==================[typedef]================================================*/
/* Spi driver name adaptation */
// @{
#define RPOUT_CSB1        RPOUT_SRAM_CS1 //44
#define RPOUT_CSB2        RPOUT_SRAM_CS2 //45
#define RPOUT_RAM_MOSI    RPOUT_RAM_SIO0 //46
#define RPOUT_RAM_MISO    RPIN_RAM_SIO1 //47
#define RPOUT_RAM_CLK     RPOUT_RAM_SCK //49


#define TRIS_RAM_MOSI     TRIS_RAM_SIO0
#define TRIS_RAM_CLK      TRIS_RAM_SCK
#define TRIS_CSB1         TRIS_SRAM_CS
#define TRIS_CSB2         TRIS_SRAM_CS2
#define TRIS_RAM_MISO     TRIS_RAM_SIO1
#define PIN_CSB1          PIN_SRAM_CS
#define PIN_CSB2          PIN_SRAM_CS2
// }

/* SPI Ram macros */
#define RAM_RSTEN         0x66    // Habilita el reinicio del dispositivo (Reset Enable)
#define RAM_RST           0x99    // Reinicia la memoria RAM (Reset Memory)
#define RAM_READ_CMD      0x03    // Lee datos de la memoria (Read Memory)
#define RAM_WRITE_CMD     0x02    // Habilita las operaciones de escritura (Write Enable)


/*==================[internal functions declaration]===========================*/
/**
 * @brief Initializes the Ram module.
 */
/*-------------------------------------------------*/
void RAM_Driver_Init(void);
/*-------------------------------------------------*/

/**
 * @brief Writes data to the Ram memory.
 * @param address Memory address to write to.
 * @param data Pointer to the data buffer.
 * @param length Number of bytes to write.
 */
/*-------------------------------------------------*/
void RAM_Driver_writeData(uint32_t address, char *data, uint16_t length);
/*-------------------------------------------------*/

/**
 * @brief Reads data from the Ram memory.
 * @param address Memory address to read from.
 * @param buffer Pointer to the buffer to store the read data.
 * @param length Number of bytes to read.
 */
/*-------------------------------------------------*/
void RAM_Driver_readData(uint32_t address, char *buffer, uint16_t length);
/*-------------------------------------------------*/

/**
 * @brief Resets the Ram memory.
 */
/*-------------------------------------------------*/
void RAM_Driver_reset(void);
/*-------------------------------------------------*/

/*==================[end of file]============================================*/
#endif /* #ifndef _APS6404L_H_ */
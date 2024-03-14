/*************************************************************************//**

  @file     spi.h

  @brief    Hardware Library to use SPI

  @author   Luciano Rottoli (based on Tomas Pentacolo)

  @date     29/02/2024

  @version  v0.0.1 - Initial release.
 
 ******************************************************************************/
 
#ifndef _PIC_SPI.{port}._SLAVE_H_
#define _PIC_SPI.{port}._SLAVE_H_

/*==================[inclusions]=============================================*/
#include <xc.h>

/*==================[macros]=================================================*/

/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

/**
 * @brief Inicializacion del bus SPI
 * @param void
 */
void SPI.{port}._init (uint8_t mode16, uint8_t spi_mode);

/**
 * @brief Deshabilita el bus SPI para ahorrar energia en modo sleep
 */
void SPI.{port}._disable();

/**
 * @brief Habilita el bus SPI
 */
void SPI.{port}._enable();

/**
**@brief lee y/o escribe un byte en el bus SPI
**@param data byte a enviar por el bus SPI
**@return byte recibido por el bus SPI
*/
unsigned short writeSPI.{port}.( unsigned short data );

EMIC:ifdef(SPI.{port}._CALLBACK)
extern void ISR_SPI.{port}._CALLBACK(data);
EMIC:endif
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif 
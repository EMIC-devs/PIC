/*************************************************************************//**
  @file     I2C.h

  @brief    Hardware Library to use I2C

  @author   Tomas Pentacolo (TP)

  @date     29/02/2024

  @version  v0.0.1 - Initial release.
 ******************************************************************************/

#ifndef __PIC_I2C.{port}._H__
#define __PIC_I2C.{port}._H__

/*==================[inclusions]=============================================*/

#include <xc.h>

/*==================[macros]=================================================*/


/*==================[typedef]================================================*/

enum
{
    I2C_SLAVE_MODE,
    I2C_MASTER_MODE
};

typedef struct
{
    const uint8_t mode;             // 0 = slave mode; 1 = master mode
    const uint16_t frec;            // In KHz
    const uint8_t address;          // own address
    const uint8_t i2c_channel;      // 1 = I2C; 2 = I2C2
    const uint8_t en_interrupt;     // 0 = no interrupt; 1 = interrupt enable
    const uint8_t pull_up;          // 0 = pull up disable; 1 = pull up enable
} i2c_config_t;

/*==================[internal function declaration]==========================*/

/**
 * @brief Initializes the I2C module with the provided configuration.
 *
 * This function initializes the I2C module based on the provided configuration.
 *
 * @param config The configuration structure for the I2C module.
 * @return None
 */
void Init_I2C(i2c_config_t config);

/**
 * @brief Resets the collision flag in the I2C module.
 *
 * This function resets the collision flag in the I2C module for a specific port.
 *
 * @param config The configuration structure for the I2C module.
 * @return None
 */
void CollisionReset_I2C.{port}.();

/**
 * @brief Resets the overflow flag in the I2C module.
 *
 * This function resets the overflow flag in the I2C module for a specific port.
 *
 * @param config The configuration structure for the I2C module.
 * @return None
 */
void OverflowReset_I2C.{port}.();
void Start_I2C.{port}.();
void Stop_I2C.{port}.();
void Write_I2C.{port}.(unsigned char byte);

/**
 * @brief Reads data from the I2C module.
 *
 * This function reads data from the I2C module for a specific port.
 *
 * @param config The configuration structure for the I2C module.
 * @param Ack Flag to indicate whether to send an acknowledgment or not after receiving data.
 * @return The data read from the I2C module.
 */
uint8_t Read_I2C.{port}.(uint8_t Ack);

/**
 * @brief Checks if the I2C bus is in the start condition.
 *
 * This function checks if the I2C bus is in the start condition for a specific port.
 *
 * @param config The configuration structure for the I2C module.
 * @return 1 if the start condition is detected, 0 otherwise.
 */
uint8_t IsStartI2c.{port}.();

/**
 * @brief Checks if collision is detected in the I2C module.
 *
 * This function checks if collision is detected in the I2C module for a specific port.
 *
 * @param config The configuration structure for the I2C module.
 * @return 1 if collision is detected, 0 otherwise.
 */
uint8_t IsCollisionDetectI2c.{port}.();

/**
 * @brief Checks if the I2C bus is in the stop condition.
 *
 * This function checks if the I2C bus is in the stop condition for a specific port.
 *
 * @param config The configuration structure for the I2C module.
 * @return 1 if the stop condition is detected, 0 otherwise.
 */
uint8_t IsStopI2c.{port}.();

/**
 * @brief Checks if the I2C receive buffer is full.
 *
 * This function checks if the I2C receive buffer is full for a specific port.
 *
 * @param config The configuration structure for the I2C module.
 * @return 1 if the receive buffer is full, 0 otherwise.
 */
uint8_t IsReceiveBufferFullI2c.{port}.();

/**
 * @brief Checks if the received data is a data byte or an address byte.
 *
 * This function checks if the received data is a data byte or an address byte for a specific port.
 *
 * @param config The configuration structure for the I2C module.
 * @return 1 if the received data is a data byte, 0 if it's an address byte.
 */
uint8_t IsDataOrAddressI2c.{port}.();

/**
 * @brief Checks if overflow is detected in the I2C receive buffer.
 *
 * This function checks if overflow is detected in the I2C receive buffer for a specific port.
 *
 * @param config The configuration structure for the I2C module.
 * @return 1 if overflow is detected, 0 otherwise.
 */
uint8_t IsReceiveOverflowI2c.{port}.();

extern void ISR_I2C.{port}._CALLBACK_SLAVE(void);
extern void ISR_I2C.{port}._CALLBACK_MASTER(void);

/*==================[end of file]============================================*/
#endif

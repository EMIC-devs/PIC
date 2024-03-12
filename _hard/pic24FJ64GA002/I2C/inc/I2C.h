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

#define ISR_I2C.{port}._SLAVE_CALLBACK	__attribute__((interrupt(auto_psv))) _SI2C.{port}._Interrupt
#define ISR_I2C.{port}._MASTER_CALLBACK	__attribute__((interrupt(auto_psv))) _MI2C.{port}._Interrupt

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
void CollisionReset_I2C(i2c_config_t config);

/**
 * @brief Resets the overflow flag in the I2C module.
 *
 * This function resets the overflow flag in the I2C module for a specific port.
 *
 * @param config The configuration structure for the I2C module.
 * @return None
 */
void OverflowReset_I2C(i2c_config_t config);
void Start_I2C(i2c_config_t config);
void Stop_I2C(i2c_config_t config);
void Write_I2C(unsigned char byte, i2c_config_t config);

/**
 * @brief Reads data from the I2C module.
 *
 * This function reads data from the I2C module for a specific port.
 *
 * @param config The configuration structure for the I2C module.
 * @param Ack Flag to indicate whether to send an acknowledgment or not after receiving data.
 * @return The data read from the I2C module.
 */
uint8_t Read_I2C(i2c_config_t config,uint8_t Ack);

/**
 * @brief Checks if the I2C bus is in the start condition.
 *
 * This function checks if the I2C bus is in the start condition for a specific port.
 *
 * @param config The configuration structure for the I2C module.
 * @return 1 if the start condition is detected, 0 otherwise.
 */
uint8_t IsI2cStart(i2c_config_t config);

/**
 * @brief Checks if collision is detected in the I2C module.
 *
 * This function checks if collision is detected in the I2C module for a specific port.
 *
 * @param config The configuration structure for the I2C module.
 * @return 1 if collision is detected, 0 otherwise.
 */
uint8_t IsI2cCollisionDetect(i2c_config_t config);

/**
 * @brief Checks if the I2C bus is in the stop condition.
 *
 * This function checks if the I2C bus is in the stop condition for a specific port.
 *
 * @param config The configuration structure for the I2C module.
 * @return 1 if the stop condition is detected, 0 otherwise.
 */
uint8_t IsI2cStop(i2c_config_t config);

/**
 * @brief Checks if the I2C receive buffer is full.
 *
 * This function checks if the I2C receive buffer is full for a specific port.
 *
 * @param config The configuration structure for the I2C module.
 * @return 1 if the receive buffer is full, 0 otherwise.
 */
uint8_t IsI2cReceiveBufferFull(i2c_config_t config);

/**
 * @brief Checks if the received data is a data byte or an address byte.
 *
 * This function checks if the received data is a data byte or an address byte for a specific port.
 *
 * @param config The configuration structure for the I2C module.
 * @return 1 if the received data is a data byte, 0 if it's an address byte.
 */
uint8_t IsI2cDataOrAddress(i2c_config_t config);

/**
 * @brief Checks if overflow is detected in the I2C receive buffer.
 *
 * This function checks if overflow is detected in the I2C receive buffer for a specific port.
 *
 * @param config The configuration structure for the I2C module.
 * @return 1 if overflow is detected, 0 otherwise.
 */
uint8_t IsI2cReceiveOverflow(i2c_config_t config);

/*==================[end of file]============================================*/
#endif

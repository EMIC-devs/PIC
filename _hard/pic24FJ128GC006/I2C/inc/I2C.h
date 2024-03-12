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

void Init_I2C(i2c_config_t config);
void CollisionReset_I2C(i2c_config_t config);
void OverflowReset_I2C(i2c_config_t config);
void Start_I2C(i2c_config_t config);
void Stop_I2C(i2c_config_t config);
void Write_I2C(unsigned char byte, i2c_config_t config);
uint8_t Read_I2C(i2c_config_t config,uint8_t Ack);

uint8_t IsI2cStart(i2c_config_t config);
uint8_t IsI2cCollisionDetect(i2c_config_t config);
uint8_t IsI2cStop(i2c_config_t config);
uint8_t IsI2cReceiveBufferFull(i2c_config_t config);
uint8_t IsI2cDataOrAddress(i2c_config_t config);
uint8_t IsI2cReceiveOverflow(i2c_config_t config);

/*==================[end of file]============================================*/
#endif

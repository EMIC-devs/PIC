/*************************************************************************//**
  @file     I2C_driver.h

  @brief    Driver Library to use I2C

  @author   Tomas Pentacolo (TP)

  @date     29/02/2024

  @version  v0.0.1 - Initial release.
 ******************************************************************************/

#ifndef __DRIVER_I2C.{port}._H__
#define __DRIVER_I2C.{port}._H__

/*==================[inclusions]=============================================*/

/*==================[typedef]================================================*/

enum{
	I2C_ESTADO_IDLE,
	I2C_ESTADO_SENDING,
	I2C_ESTADO_END
};

enum{
	I2C_ESTADO_RCV_IDLE,
	I2C_ESTADO_PKT_ID,
	I2C_ESTADO_RCV_ID,
	I2C_ESTADO_RCV_DATA
};

/*==================[internal functions declaration]===========================*/

void ISR_I2C.{port}._SLAVE_CALLBACK(void);
void ISR_I2C.{port}._MASTER_CALLBACK(void);

void 		Init_I2C_Driver(void);
void 		ini_I2C_IN(void);
void 		ini_I2C_OUT(void);
void 		ini_I2C_OUT_FM(void);
void 		push_I2C_IN(char dato);
void 		push_I2C_OUT(char dato);
char 		pop_I2C_IN(void);
char 		pop_I2C_OUT(void);
void 		pop_I2C_OUT_FM(void);
void 		reset_I2C_FRAME(void);
void 		I2C_Begin_Transmision(void);
uint16_t	countI2cStreamIn(void);
char 		getI2cStreamIn(void);
void		setI2cStreamOut(char);
d
uint16_t 	getAvailable_out_count(void);

void i2cCloseWriteFrame(stream_t* stream);
void i2cOpenReadFrame(stream_t* stream);

/*==================[end of file]============================================*/
#endif
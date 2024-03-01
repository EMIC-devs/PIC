/*************************************************************************//**
  @file     I2C.c

  @brief    Hardware Library to use I2C

  @author   Tomas Pentacolo (TP)

  @date     29/02/2024

  @version  v0.0.1 - Initial release.
 ******************************************************************************/

#ifndef __PIC_I2C.{port}._C__
#define __PIC_I2C.{port}._C__

/*==================[inclusions]=============================================*/

#include <inc/I2C.{port}..h>

/*==================[function implementation]================================*/

/**
 * @brief Initializes the I2C module with the provided configuration.
 *
 * This function initializes the I2C module based on the provided configuration.
 *
 * @param config The configuration structure for the I2C module.
 * @return None
 */
void Init_I2C(i2c_config_t config)
{
    if (config.pull_up)
    {
        //Configurar el pull up, requiere de la informacion de los pines
    }

	if (config.mode == I2C_MASTER_MODE)
	{

        //seteo el baudrate
        I2C.{port}.BRG = FCY / ((uint32_t)((uint32_t)config.frec * 1000) + 1 + ((float)FCY / 10000000));

        I2C.{port}.CONbits.SEN = 0;         //Start condition is not in progress
        I2C.{port}.CONbits.PEN = 0;
        I2C.{port}.CONbits.RSEN = 0;        //Initiates Repeated Start condition on SDAx and SCLx pins. Hardware is clear at the end of master Repeated Start sequence
        I2C.{port}.CONbits.RCEN = 0;
        I2C.{port}.CONbits.ACKEN = 0;
        I2C.{port}.CONbits.ACKDT = 0;       //1 = Sends a NACK during Acknowledge
                                            //0 = Sends an ACK during Acknowledge
        I2C.{port}.CONbits.STREN = 0;	    //1 : Enables software or receive clock stretching
                                            //0 : Disables software or receive clock stretching
        if (config.en_interrupt == 1)       // interrupt enable
        {
            I2C.{port}.CONbits.GCEN = 1;
        }
        else
        {
            I2C.{port}.CONbits.GCEN = 0;
        }
        I2C.{port}.CONbits.SMEN = 0;
        I2C.{port}.CONbits.DISSLW = 1;      //Slew rate control is disabled
        I2C.{port}.CONbits.A10M = 0;
        I2C.{port}.CONbits.IPMIEN = 0;
        I2C.{port}.CONbits.SCLREL = 1;
        I2C.{port}.CONbits.I2CSIDL = 1;     // Discontinues module operation when device enters an Idle mode
        I2C1ADD = config.address;
        I2C1RCV = 0x0000;
        I2C1TRN = 0x0000;
        I2C.{port}.CONbits.I2CEN = 1;       // Enables the I2Cx module and configures the SDAx and SCLx pins as serial port pins
        if (config.en_interrupt == 1)
        {
            _MI2C.{port}.IE = 1;            //enable interrupt
            _SI2C.{port}.IE = 1;            //enable interrupt
        }
    }
}

/**
 * @brief Resets the collision flag in the I2C module.
 *
 * This function resets the collision flag in the I2C module for a specific port.
 *
 * @param config The configuration structure for the I2C module.
 * @return None
 */
void CollisionReset_I2C(i2c_config_t config)
{
    I2C.{port}.STATbits.BCL = 0;
}

/**
 * @brief Resets the overflow flag in the I2C module.
 *
 * This function resets the overflow flag in the I2C module for a specific port.
 *
 * @param config The configuration structure for the I2C module.
 * @return None
 */
void OverflowReset_I2C(i2c_config_t config)
{
    I2C.{port}.STATbits.I2COV = 0;
}

/**
 * @brief Checks if the I2C bus is in the start condition.
 *
 * This function checks if the I2C bus is in the start condition for a specific port.
 *
 * @param config The configuration structure for the I2C module.
 * @return 1 if the start condition is detected, 0 otherwise.
 */
uint8_t IsI2cStart(i2c_config_t config)
{
    return I2C.{port}.STATbits.S;
}

/**
 * @brief Checks if collision is detected in the I2C module.
 *
 * This function checks if collision is detected in the I2C module for a specific port.
 *
 * @param config The configuration structure for the I2C module.
 * @return 1 if collision is detected, 0 otherwise.
 */
uint8_t IsI2cCollisionDetect(i2c_config_t config)
{
    return I2C.{port}.STATbits.BCL;
}

/**
 * @brief Checks if the I2C bus is in the stop condition.
 *
 * This function checks if the I2C bus is in the stop condition for a specific port.
 *
 * @param config The configuration structure for the I2C module.
 * @return 1 if the stop condition is detected, 0 otherwise.
 */
uint8_t IsI2cStop(i2c_config_t config)
{
    return I2C.{port}.STATbits.P;
}

/**
 * @brief Checks if the I2C receive buffer is full.
 *
 * This function checks if the I2C receive buffer is full for a specific port.
 *
 * @param config The configuration structure for the I2C module.
 * @return 1 if the receive buffer is full, 0 otherwise.
 */
uint8_t IsI2cReceiveBufferFull(i2c_config_t config)
{
    return I2C.{port}.STATbits.RBF;
}

/**
 * @brief Checks if the received data is a data byte or an address byte.
 *
 * This function checks if the received data is a data byte or an address byte for a specific port.
 *
 * @param config The configuration structure for the I2C module.
 * @return 1 if the received data is a data byte, 0 if it's an address byte.
 */
uint8_t IsI2cDataOrAddress(i2c_config_t config)
{
    return I2C.{port}.STATbits.D_A;
}

/**
 * @brief Checks if overflow is detected in the I2C receive buffer.
 *
 * This function checks if overflow is detected in the I2C receive buffer for a specific port.
 *
 * @param config The configuration structure for the I2C module.
 * @return 1 if overflow is detected, 0 otherwise.
 */
uint8_t IsI2cReceiveOverflow(i2c_config_t config)
{
    return I2C.{port}.STATbits.I2COV;
}

void Start_I2C(i2c_config_t config)
{
	//This function generates an I2C start condition and returns status
	//of the Start.
    I2C.{port}.CONbits.SEN = 1;     //Generate Start Condition
    while (I2C.{port}.CONbits.SEN);

}

void Stop_I2C(i2c_config_t config)
{
	//This function generates an I2C stop condition and returns status
	//of the Stop.
	I2C.{port}.CONbits.PEN = 1;     //Generate Stop Condition
	while (I2C.{port}.CONbits.PEN);
}
void Write_I2C(unsigned char byte, i2c_config_t config)
{
	//This function transmits the byte passed to the function
	//while (I2C.{port}.STATbits.TBF);		//wait for data transmission
    I2C.{port}.TRN = byte;					//Load byte to I2C1 Transmit buffer
    if (config.en_interrupt == 0)
    {
        while (I2C.{port}.STATbits.TRSTAT);	//Wait for bus to be idle
    }
}

/**
 * @brief Reads data from the I2C module.
 *
 * This function reads data from the I2C module for a specific port.
 *
 * @param config The configuration structure for the I2C module.
 * @param Ack Flag to indicate whether to send an acknowledgment or not after receiving data.
 * @return The data read from the I2C module.
 */
uint8_t Read_I2C(i2c_config_t config, uint8_t Ack)
{
	uint8_t data = 0;
    if (config.en_interrupt == 0)
    {
        I2C.{port}.CONbits.RCEN = 1;			//Enable Master receive
        Nop();
        while (!I2C.{port}.STATbits.RBF);		//Wait for receive bufer to be full
        data = I2C.{port}.RCV;
        if(Ack)
            I2C.{port}.CONbits.ACKDT = 1;
        else
            I2C.{port}.CONbits.ACKDT = 0;
        I2C.{port}.CONbits.ACKEN = 1;
        while (I2C.{port}.CONbits.ACKEN);
    }
    else
    {
        data = I2C.{port}.RCV;
        I2C.{port}.CONbits.SCLREL = 1;
    }
    return(data);				//Return data in buffer
}

/*==================[end of file]============================================*/
#endif
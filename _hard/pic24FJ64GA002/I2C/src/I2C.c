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
#include <xc.h>
#include "inc/I2C.{port}..h"
#include "inc/system.h"

/*==================[function implementation]================================*/

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

void CollisionReset_I2C.{port}.()
{
    I2C.{port}.STATbits.BCL = 0;
}

void OverflowReset_I2C.{port}.()
{
    I2C.{port}.STATbits.I2COV = 0;
}

uint8_t IsStartI2c.{port}.()
{
    return I2C.{port}.STATbits.S;
}

uint8_t IsCollisionDetectI2c.{port}.()
{
    return I2C.{port}.STATbits.BCL;
}

uint8_t IsStopI2c.{port}.()
{
    return I2C.{port}.STATbits.P;
}

uint8_t IsReceiveBufferFullI2c.{port}.()
{
    return I2C.{port}.STATbits.RBF;
}

uint8_t IsDataOrAddressI2c.{port}.()
{
    return I2C.{port}.STATbits.D_A;
}

uint8_t IsReceiveOverflowI2c.{port}.()
{
    return I2C.{port}.STATbits.I2COV;
}

void Start_I2C.{port}.()
{
	//This function generates an I2C start condition and returns status
	//of the Start.
    I2C.{port}.CONbits.SEN = 1;     //Generate Start Condition
    while (I2C.{port}.CONbits.SEN);

}

void Stop_I2C.{port}.()
{
	//This function generates an I2C stop condition and returns status
	//of the Stop.
	I2C.{port}.CONbits.PEN = 1;     //Generate Stop Condition
	while (I2C.{port}.CONbits.PEN);
}
void Write_I2C.{port}.(unsigned char byte)
{
	//This function transmits the byte passed to the function
	//while (I2C.{port}.STATbits.TBF);		//wait for data transmission
    I2C.{port}.TRN = byte;					//Load byte to I2C1 Transmit buffer
    if (config.en_interrupt == 0)
    {
        while (I2C.{port}.STATbits.TRSTAT);	//Wait for bus to be idle
    }
}

uint8_t Read_I2C.{port}.(uint8_t Ack)
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

void __attribute__((interrupt(auto_psv))) _SI2C.{port}.Interrupt( void )
{
    _SI2C.{port}.IF = 0;
    EMIC:ifdef(I2C.{port}._CALLBACK_SLAVE)
    ISR_I2C.{port}._CALLBACK_SLAVE();
    EMIC:endif
}

void __attribute__((interrupt(auto_psv))) _MI2C.{port}.Interrupt( void )
{
    _MI2C.{port}.IF = 0;
    EMIC:ifdef(I2C.{port}._CALLBACK_MASTER)
    ISR_I2C.{port}._CALLBACK_MASTER();
    EMIC:endif
}

/*==================[end of file]============================================*/
#endif
/*************************************************************************//**

  @file     spi_slave.c

  @brief    Hardware Library to use SPI

  @author   Luciano Rottoli (based on Tomas Pentacolo)

  @date     29/02/2024

  @version  v0.0.1 - Initial release.
 
 ******************************************************************************/
 

 /*==================[inclusions]=============================================*/
#include <xc.h>
#include "inc/gpio.h"
#include "inc/spi.{port}..h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

void __attribute__((__interrupt__)) _SPI.{port}.Interrupt( void )	
{
	_SPI.{port}.IF      = 0;             //Clear flag interrupt
	uint16_t data = 0;
	data = SPI.{port}.BUF;
	EMIC:ifdef(SPI.{port}._CALLBACK)
	ISR_SPI.{port}._CALLBACK(data);
	EMIC:endif
}


void SPI.{port}._init (uint8_t mode16, uint8_t spi_mode)
{
	HAL_GPIO_PinCfg(.{pin}._MOSI, GPIO_OUTPUT);
	HAL_GPIO_PinCfg(.{pin}._CLK, GPIO_OUTPUT);
    HAL_GPIO_PinCfg(.{pin}._MISO, GPIO_INPUT);
	HAL_GPIO_PinCfg(.{pin}._CS, GPIO_INPUT);

	__builtin_write_OSCCONL(OSCCON & 0xbf); // unlock PPS	

	RPOUT_.{pin}._MOSI	= _RPOUT_SDO.{port}.;
	RPOUT_.{pin}._CLK	= _RPOUT_SCK.{port}.OUT;
	_SDI.{port}.R = RPIN_.{pin}._MISO;
	_SS.{port}.R = RPIN_.{pin}._CS;

	__builtin_write_OSCCONL(OSCCON | 0x40); // lock PPS

	SPI.{port}.STATbits.SPIEN   = 0;            //Disable SPI port
	SPI.{port}.STATbits.SPISIDL = 0;            //Continue module operation in Idle mode
    SPI.{port}.BUF              = 0;            //Clear SPI buffer data Slave
    _SPI.{port}.IF      = 0;             		//Clear flag interrupt
    _SPI.{port}.IE      = 1;             		//Enable Interrupt
    SPI.{port}.CON1bits.DISSCK  = 0;             //Internal SPI Clock is Enabled
    SPI.{port}.CON1bits.DISSDO  = 0;             //SDOx pin is controlled by the module (Enable SDO)
	SPI.{port}.CON1bits.SMP = 0; 				//SMP must be cleared when SPIx is used in Slave mode.
    SPI.{port}.CON1bits.MODE16  = 1;             //Communication is word-wide 
    /*switch (spi_mode)
    {
    case 0:
    	SPI1CON1bits.CKP     = 0;             //CKP and CKE is subject to change
    	SPI1CON1bits.CKE     = 1;             //Serial output data changes on transition from
    	break;
    case 1:
    	SPI1CON1bits.CKP     = 1;             //CKP and CKE is subject to change
    	SPI1CON1bits.CKE     = 0;             //Serial output data changes on transition from
    	break;
    case 2:
    	SPI1CON1bits.CKP     = 0;             //CKP and CKE is subject to change
    	SPI1CON1bits.CKE     = 1;             //Serial output data changes on transition from
    	break;
    case 3:
    	SPI1CON1bits.CKP     = 1;             //CKP and CKE is subject to change
    	SPI1CON1bits.CKE     = 0;             //Serial output data changes on transition from
    	break;
    }*/
	SPI.{port}.CON1bits.CKP     = 0;                //Idle state for the clock is a high level; active state is a low level
    SPI.{port}.CON1bits.CKE     = 0;                //Serial output data changes on transition from active clock state to Idle clock state
	SPI.{port}.CON1bits.SSEN     = 1;				 //SSx pin is used for Slave mode
    SPI.{port}.STATbits.SPIROV  = 0;  				//No overflow has occurred
	

    //SPI1CON1bits.SPRE    = 6;         // secondary prescale as  SPRE=4 4:1 -- SPRE=7 1:1 --SPRE=6 2:1
    //SPI1CON1bits.PPRE    = 3; 		  // Primary prescale as  PPRE=2 4:1 -- PPRE=3 1:1
    SPI.{port}.CON1bits.MSTEN   = 0;             //Master Mode Disable-Slave Mode Slave
    //SPI1CON2             = 0;             //non-framed mode

    SPI.{port}.STATbits.SPIEN   = 1;             //Enable SPI Module

}
void SPI.{port}._enable(){
    SPI.{port}.STATbits.SPIEN   = 1;             //Enable SPI port
}

void SPI.{port}._disable(){
    SPI.{port}.STATbits.SPIEN   = 0;             //Disable SPI port
}

unsigned short writeSPI.{port}.( unsigned short data )
{
    SPI.{port}.BUF = data;					// write to buffer for TX
    while(!SPI.{port}.STATbits.SPIRBF);	// wait for transfer to complete
    return SPI.{port}.BUF;    				// read the received value
}

/** @} doxygen end group definition */
/*==================[end of file]============================================*/


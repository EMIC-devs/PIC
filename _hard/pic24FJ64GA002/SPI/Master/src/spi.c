/*************************************************************************//**

  @file     spi.c

  @brief    Hardware Library to use SPI

  @author   Luciano Rottoli (based on Tomas Pentacolo)

  @date     29/02/2024

  @version  v0.0.1 - Initial release.
 
 ******************************************************************************/

/*==================[inclusions]=============================================*/
#include <xc.h>
#include "inc/gpio.h"
#include "inc/spi.{port}..h"

/*==================[data declaration]==============================*/
uint8_t * spi.{port}._pending_data;
uint8_t spi.{port}._response_data[32];

uint8_t spi.{port}._package_size = 8;
uint8_t spi.{port}._ready = 1;
int spi.{port}._indice = 0;
/******************************************************************************/

void (*spi.{port}._fun_ptr)(uint8_t *, uint8_t);

void SPI.{port}._init (uint8_t mode16, uint8_t spi_mode)
{
    HAL_GPIO_PinCfg(.{pin}._MOSI, GPIO_OUTPUT);
	HAL_GPIO_PinCfg(.{pin}._CLK, GPIO_OUTPUT);
    HAL_GPIO_PinCfg(.{pin}._MISO, GPIO_INPUT);

	__builtin_write_OSCCONL(OSCCON & 0xbf); // unlock PPS

	RPOUT_.{pin}._MOSI	= _RPOUT_SDO.{port}.;
	RPOUT_.{pin}._CLK	= _RPOUT_SCK.{port}.OUT;
	_SDI.{port}.R = RPIN_.{pin}._MISO;

	__builtin_write_OSCCONL(OSCCON | 0x40); // lock PPS

	SPI.{port}.STATbits.SPIEN   = 0;             //Disable SPI port
	SPI.{port}.STATbits.SPISIDL = 0;             //Continue module operation in Idle mode
    SPI.{port}.BUF              = 0;             //Clear SPI buffer data Master
    _SPI.{port}.IF      = 0;             //Clear flag interrupt
    _SPI.{port}.IE      = 0;             //Disable Interrupt
    _SPI.{port}.IP      = 1;             //Set the interrupt priority to low
    SPI.{port}.CON1bits.DISSCK  = 0;             //Internal SPI Clock is Enabled
    SPI.{port}.CON1bits.DISSDO  = 0;             //SDOx pin is controlled by the module (Enable SDO)
    SPI.{port}.CON1bits.MODE16  = mode16;        //Communication is word-wide (8 bits or 16 bits)
    switch (spi_mode)
    {
    case 0:
    	SPI.{port}.CON1bits.SMP     = 0;             //Input Data is sampled at the middle of data output time
    	SPI.{port}.CON1bits.CKP     = 0;             //Idle state for the clock is a low level; active state is a high level
    	SPI.{port}.CON1bits.CKE     = 1;             //Serial output data changes on transition from active clock state to Idle clock state
    	break;
    case 1:
    	SPI.{port}.CON1bits.SMP     = 0;             //Input Data is sampled at the middle of data output time
    	SPI.{port}.CON1bits.CKP     = 1;             //Idle state for the clock is a high level; active state is a low level
    	SPI.{port}.CON1bits.CKE     = 0;             //Serial output data changes on transition from Idle clock state to active clock state
    	break;
    case 2:
    	SPI.{port}.CON1bits.SMP     = 1;             //Input Data is sampled at the end of data output time
    	SPI.{port}.CON1bits.CKP     = 0;             //Idle state for the clock is a low level; active state is a high level
    	SPI.{port}.CON1bits.CKE     = 1;             //Serial output data changes on transition from active clock state to Idle clock state
    	break;
    case 3:
    	SPI.{port}.CON1bits.SMP     = 1;             //Input Data is sampled at the end of data output time
    	SPI.{port}.CON1bits.CKP     = 1;             //Idle state for the clock is a high level; active state is a low level
    	SPI.{port}.CON1bits.CKE     = 0;             //Serial output data changes on transition from Idle clock state to active clock state
    	break;
    }
    SPI.{port}.CON1bits.SSEN    = 0;
    SPI.{port}.CON1bits.SPRE    = 6;         // secondary prescale as  SPRE=7 1:1 -- SPRE=6 2:1 ... SPRE=0 8:1
    SPI.{port}.CON1bits.PPRE    = 3; 		  // Primary prescale as   PPRE=3 1:1 -- PPRE=2 4:1 -- PPRE=1 16:1 -- PPRE=0 64:1
    SPI.{port}.CON1bits.MSTEN   = 1;         //Master Mode Enabled
    SPI.{port}.CON2             = 0;         //non-framed mode

    SPI.{port}.STATbits.SPIEN   = 1;         //Enable SPI Module

}

void SPI.{port}._enable(){
    SPI.{port}.STATbits.SPIEN   = 1;             //Enable SPI port
}

void SPI.{port}._disable(){
    SPI.{port}.STATbits.SPIEN   = 0;             //Disable SPI port
}

#define spi.{port}._put(data) SPI.{port}.BUF=data
#define spi.{port}._get() SPI.{port}.BUF

uint8_t xchangeSPI.{port}.b_8(uint8_t data)
{
    SPI.{port}.BUF = data;					    // write to buffer for TX
    while(!SPI.{port}.STATbits.SPIRBF);        // wait for transfer to complete
    uint8_t ret = SPI.{port}.BUF;
    return ret;    				        // read the received value
}

uint16_t xchangeSPI.{port}.b_16(uint16_t data)
{
    SPI.{port}.BUF = data;					    // write to buffer for TX
    while(!SPI.{port}.STATbits.SPIRBF);        // wait for transfer to complete
    uint16_t ret = SPI.{port}.BUF;
    return ret;    				        // read the received value
}


void SPI.{port}._clr()
{
    uint8_t damy;
    while(SPI.{port}.STATbits.SPIRBF)
    {
        damy = SPI.{port}.BUF;
    }

}


uint8_t SPI.{port}._send_async(uint8_t * new_data, uint8_t package_size, uint8_t * proccess_function)
{
    if (spi.{port}._ready)
    {
        _SPI.{port}.IE      = 1;             //Enable Interrupt
        spi.{port}._fun_ptr = (void*)proccess_function;              //revisar cambios realizados --Luciano 19/02
        spi.{port}._package_size = package_size;
        spi.{port}._pending_data = new_data;
        spi.{port}._indice = 0;
        spi.{port}._ready = 0;
        SPI.{port}.BUF = spi.{port}._pending_data[spi.{port}._indice];
        spi.{port}._indice++;
        return 1;
    }
    return 0;
}

void __attribute__((interrupt(auto_psv))) _SPI.{port}.Interrupt (void)
{
    if (!spi.{port}._ready)
    {
        spi.{port}._response_data[spi.{port}._indice - 1] = SPI.{port}.BUF;
        if (spi.{port}._indice < spi.{port}._package_size)
        {
            SPI.{port}.BUF = spi.{port}._pending_data[spi.{port}._indice];
            spi.{port}._indice++;
            return;
        }
        else
        {
            if (spi.{port}._fun_ptr)
            {
                (*spi.{port}._fun_ptr)(spi.{port}._response_data, spi.{port}._package_size);
            }
            spi.{port}._ready = 1;
            _SPI.{port}.IE      = 0;             //Disable Interrupt
        }
    }  
}

/** @} doxygen end group definition */
/*==================[end of file]============================================*/
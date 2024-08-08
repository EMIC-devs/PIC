/*****************************************************************************

  @file     rs232.h

  @brief    RS232 interface

  @author   Francisco Martinez (based on Tomas Pentacolo and Rottoli Luciano)

  @version  v0.0.1  

  @date		02/08/2024   

 ******************************************************************************/

/*==================[inclusions]=============================================*/
#include "inc/rs232.h"
#include <xc.h>
#include "inc/streamIn.h"
#include "inc/UART.{port}..h"
#include "inc/gpio.h"
#include <stdarg.h>
#include "inc/userFncFile.h"


static uint8_t frameFlag = 0;
#define RS232FrameLf '.{frameLf}.'

void RS232_Init()
{
    HAL_GPIO_PinCfg(RS232_TTL_RX,GPIO_INPUT);
    HAL_GPIO_PinCfg(RS232_TTL_TX,GPIO_OUTPUT);
    HAL_GPIO_PinCfg(RS232_TTL_RTS,GPIO_OUTPUT);
    HAL_GPIO_PinSet(RS232_TTL_RTS,GPIO_HIGH);
	UART.{port}._init();
}

void pRS232(char* format,...)
{
	va_list arg;
    va_start(arg, format);

	sendDataToStream(&streamOut_Uart.{port}.,format,arg);

	va_end(arg);
	UART.{port}._OUT_push(RS232FrameLf); 

}



void Poll_RS232(void)
{

	EMIC:ifdef usedEvent.eRS232
	if(frameFlag)
	{
		frameFlag = 0;
		
		EMIC:if(.{config.RS232prot}.=="EMIC_message")

		char tag[20];
		char d;
		uint8_t i = 0;
	
		d = UART.{port}._IN_pop();
		while (!UART.{port}._is_empty(&UART.{port}._IN_fifo) && d != '\t' && i < 20)
		{
			tag[i++] = d;
			d = UART.{port}._IN_pop();
		}
		
		tag[i] = 0;
		
		eRS232(tag,&streamIn_Uart.{port}.);

		EMIC:endif

		EMIC:if(.{config.RS232prot}.=="TEXT_line")
		
		eRS232(&streamIn_Uart.{port}.);

		EMIC:endif
		
	}
	EMIC:endif

EMIC:ifdef usedEvent.eBeRS232
	if(UART.{port}._is_empty(&UART.{port}._OUT_fifo)) 
	{
		eBeRS232();
	}
EMIC:endif
}

void ISR_UART.{port}._CALLBACK(char d)
{
	if(d == RS232FrameLf)
	{
		frameFlag = 1;
	}
}


uint16_t RS232_sendCount(void)
{
	return UART.{port}._count(&UART.{port}._OUT_fifo);
}

/*****************************************************************************

  @file     USB_API.c

  @brief    USB interface

  @author   Rottoli Luciano (based on Tomas Pentacolo)

  @version  v0.0.1  

  @date		04/03/2024   

 ******************************************************************************/

/*==================[inclusions]=============================================*/
#include "inc/USB_API.h"
#include <xc.h>
#include "inc/.{driver}..h"
#include "inc/streamIn.h"
#include "inc/UART.{port}..h"
#include <stdarg.h>
 #include "inc/userFncFile.h"

//#if USBprot=="EMIC_message"
    #define USBFrameLf '.{frameLf}.'
//#endif
static frameFlag = 0;

void USB_Init()
{
	Init_USBDriver();
}

// #if USBprot=="EMIC_message"

void pUSB(char* format,...)
{
	va_list arg;
    va_start(arg, format);

	sendDataToStream(&streamOut_Uart.{port}.,format,arg);

	va_end(arg);
	UART.{port}._OUT_push(USBFrameLf); 

}


// #else
// void pUSB(char* msg)
// {
// 	char *r;
	
// 	for (r = char* msg;*r > 0; r++) 
// 	{
// 		UARTX.{port}._OUT_push(*r);
// 	}
// 	UARTX.{port}._OUT_push(USBFrameLf);
// }
// #endif

void Poll_USB(void)
{

	#ifdef event_eUSB_active // deberia ser EMIC:ifdef usedEvent.eUSB

	// if (UART.{port}._peek(&UART.{port}._IN_fifo) == USBFrameLf)
	if(frameFlag)
	{
		frameFlag = 0;
		// #if USBprot=="EMIC_message"
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
		
		eUSB(tag,&streamIn_Uart.{port}.);
		// #endif
		
		
		
	}
	#endif // deberia ser EMIC:endif

#ifdef event_eBeUSB_active
	if(UART.{port}._is_empty(&UART.{port}._OUT_fifo)) 
	{
		//UARTX_{puerto}__bufferEmpty=0;
		eBeUSB();
		//puts_f("#eBeUSB;\r"); //se vacio el buffer tx
	}
#endif
}

void ISR_UART.{port}._CALLBACK(char d)
{
	if(d == USBFrameLf)
	{
		frameFlag = 1;
	}
}


uint16_t USB_sendCount(void)
{
	return UART.{port}._count(&UART.{port}._OUT_fifo);
}

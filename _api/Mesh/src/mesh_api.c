/*****************************************************************************

  @file     mesh_API.c

  @brief    mesh interface

  @author   Rottoli Luciano (based on Tomas Pentacolo)

  @version  v0.0.1  

  @date		04/03/2024   

 ******************************************************************************/

/*==================[inclusions]=============================================*/
#include "inc/mesh_API.h"
#include <xc.h>
#include "inc/.{driver}..h"
#include "inc/streamOut.h"
#include "inc/streamIn.h"
#include "inc/UART.{port}..h"
#include <stdarg.h>
 #include "inc/userFncFile.h"

static frameFlag = 0;

void mesh_Init()
{
	Init_meshDriver();
}

// #if meshprot=="EMIC_message"

void pMesh(char* format,...)
{
	va_list arg;
    va_start(arg, format);

	sendDataToStream(&streamOut_Uart.{port}.,format,arg);

	va_end(arg);
	UART.{port}._OUT_push(meshFrameLf); 

}



void Poll_mesh(void)
{

	EMIC:ifdef usedEvent.eMesh

	if(frameFlag)
	{
		frameFlag = 0;
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
		eMesh(tag,&streamIn_Uart.{port}.);
	}
	EMIC:endif
}

void ISR_UART.{port}._CALLBACK(char d)
{
	if(d == meshFrameLf)
	{
		frameFlag = 1;
	}
}


uint16_t mesh_sendCount(void)
{
	return UART.{port}._count(&UART.{port}._OUT_fifo);
}

/*****************************************************************************

  @file     USB_API.h

  @brief    USB interface

  @author   Rottoli Luciano (based on Tomas Pentacolo)

  @version  v0.0.1  

  @date		  04/03/2024   

 ******************************************************************************/

#ifndef _USB_API_H_
#define _USB_API_H_

/*==================[public functions definition]==========================*/
void USB_Init(void);
EMIC:define(inits.USB_Init,USB_Init)


void pUSB(char* format,...);

void Poll_USB(void);
EMIC:define(polls.Poll_USB,Poll_USB)

void ISR_UART.{port}._CALLBACK(char d);

#endif
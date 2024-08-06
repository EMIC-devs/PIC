/*****************************************************************************

  @file     rs232.h

  @brief    RS232 interface

  @author   Francisco Martinez (based on Tomas Pentacolo and Rottoli Luciano)

  @version  v0.0.1  

  @date		02/08/2024   

 ******************************************************************************/

#ifndef _USB_API_H_
#define _USB_API_H_

/*==================[public functions definition]==========================*/
void RS232_Init(void);
EMIC:define(inits.RS232_Init,RS232_Init)

void pRS232(char* format,...);

void Poll_RS232(void);
EMIC:define(polls.Poll_RS232,Poll_RS232)

void ISR_UART.{port}._CALLBACK(char d);

#endif
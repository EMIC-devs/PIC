/*****************************************************************************

  @file     USB_API.h

  @brief    USB interface

  @author   Rottoli Luciano (based on Tomas Pentacolo)

  @version  v0.0.1  

  @date		  04/03/2024   

 ******************************************************************************/

#ifndef _USB_API_H_
#define _USB_API_H_

//#if USBprot=="EMIC_message"
    #define USBFrameLf '.{frameLf}.'
//#endif

void USB_Init(void);
EMIC:define(inits.USB_Init,USB_Init)


void pUSB(char* format,...);

void Poll_USB(void);
EMIC:define(polls.Poll_USB,Poll_USB)

#endif
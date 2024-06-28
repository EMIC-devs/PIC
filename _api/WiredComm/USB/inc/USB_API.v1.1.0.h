/*************************************************************************//**

  @file     USB_MCP2200.h

  @brief    Driver Library to use USB

  @author   Tomas Pentacolo (based on Pablo Llull (PL))

  @date     23/11/2022

  @version  v0.0.1 - Initial release.
  
 ******************************************************************************/

#ifndef _USB_H_
#define _USB_H_

#if USBprot=="EMIC_message"
    #define USBFrameLf '\n'
#endif

#include <stdarg.h>

void USB_Init(void);
EMIC:define(inits.USB_Init,USB_Init)


void pUSB(char* format,...);
//doCMDf(pUSB)


//#if USBprot=="STREAM"
//  void gUSB(void);
//#endif 

void Poll_USB(void);
EMIC:define(polls.Poll_USB,Poll_USB)

#endif
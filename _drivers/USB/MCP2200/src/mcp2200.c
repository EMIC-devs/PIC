/*************************************************************************//**

  @file     USB_MCP2200.c

  @brief    Driver Library to use USB

  @author   Tomas Pentacolo (based on Pablo Llull (PL))

  @date     23/11/2022

  @version  v0.0.1 - Initial release.
  
 ******************************************************************************/
#include "inc/gpio.h"
#include "inc/MCP2200.h"

void Init_USBDriver()
{
	#ifdef PORT_MCP2200_RST
    HAL_GPIO_PinCfg(MCP2200_RX,GPIO_INPUT);
    HAL_GPIO_PinCfg(MCP2200_TX,GPIO_OUTPUT);
    HAL_GPIO_PinCfg(MCP2200_RST,GPIO_OUTPUT);
    HAL_GPIO_PinSet(MCP2200_RST,GPIO_HIGH);
	#endif
	UARTX.{port}._init();
}


void Poll_USBDriver(void)
{
}

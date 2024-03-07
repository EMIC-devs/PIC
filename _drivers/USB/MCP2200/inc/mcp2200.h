/*************************************************************************//**

  @file     MCP2200.h

  @brief    Driver Library to use USB

  @author   Tomas Pentacolo (based on Pablo Llull (PL))

  @date     23/11/2022

  @version  v0.0.1 - Initial release.
  
 ******************************************************************************/

#ifndef _mcp2200_H_
#define _mcp2200_H_

#define RPOUT_U.{port}._TX	RPOUT_MCP2200_TX
#define RPIN_U.{port}._RX		RPIN_MCP2200_RX

#define RPIN_U.{port}._CTS 	RPIN_MCP2200_CTS
#define RPOUT_U.{port}._RTS	RPOUT_MCP2200_RTS

void Init_USBDriver(void);
void Poll_USBDriver(void);

#endif
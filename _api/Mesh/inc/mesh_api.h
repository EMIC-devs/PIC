/*****************************************************************************

  @file     Mesh_api.h

  @brief    Mesh interface

  @author   Rottoli Luciano (based on Tomas Pentacolo)

  @version  v0.0.1  

  @date		  04/03/2024   

 ******************************************************************************/

#ifndef _Mesh_api_H_
#define _Mesh_api_H_

//#if Meshprot=="EMIC_message"
    #define MeshFrameLf '.{frameLf}.'
//#endif

/*==================[public functions definition]==========================*/
void Mesh_Init(void);
EMIC:define(inits.Mesh_Init,Mesh_Init)


void pMesh(char* format,...);

void Poll_Mesh(void);
EMIC:define(polls.Poll_Mesh,Poll_Mesh)

void ISR_UART.{port}._CALLBACK(char d);

#endif
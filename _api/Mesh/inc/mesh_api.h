/*****************************************************************************

  @file     Mesh_api.h

  @brief    Mesh interface

  @author   Rottoli Luciano (based on Tomas Pentacolo)

  @version  v0.0.1  

  @date		  04/03/2024   

 ******************************************************************************/


#ifndef _Mesh_api_H_
#define _Mesh_api_H_

#define MeshFrameLf '\n'

/*==================[public functions definition]==========================*/
void init_mesh(void);
void pMesh(char* format,...);
void poll_mesh(void);
void Mesh_set(uint16_t myID,uint16_t targetID);

#endif
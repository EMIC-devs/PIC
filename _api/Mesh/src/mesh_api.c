/*****************************************************************************

  @file     mesh_API.c

  @brief    mesh interface

  @author   Rottoli Luciano (based on Tomas Pentacolo)

  @version  v0.0.1  

  @date		04/03/2024   

 ******************************************************************************/

/*==================[inclusions]=============================================*/
#include <xc.h>
#include <stdarg.h>

#include "inc/mesh_API.h"
#include "inc/mesh.h"
//#include "inc/phyMesh.h"


// #include "inc/streamOut.h"
// #include "inc/streamIn.h"
// #include "inc/userFncFile.h"
// 
// static int frameFlag = 0;

void init_mesh()
{
	init_meshDriver();
}

void pMesh(char* format,...)
{
	va_list arg;
    va_start(arg, format);

	//sendDataToStream(&streamOut_phyMesh,format,arg);

	va_end(arg);
	//phyMesh_OUT_push(meshFrameLf); 

}

void Mesh_set(uint16_t myID,uint16_t targetID)
{

}



void poll_mesh(void)
{

	poll_meshDriver();

	EMIC:ifdef usedEvent.eMesh

	//if(frameFlag)
	//{
	//	frameFlag = 0;
	//	char tag[20];
	//	char d;
	//	uint8_t i = 0;
	//
	//	d = phyMesh_IN_pop();
	//	while (!phyMesh_is_empty(&phyMesh_IN_fifo) && d != '\t' && i < 20)
	//	{
	//		tag[i++] = d;
	//		d = phyMesh_IN_pop();
	//	}
	//	
	//	tag[i] = 0;
	//	eMesh(tag,&streamIn_phyMesh);
	//}
	EMIC:endif
}

//void ISR_phyMesh_CALLBACK(char d)
//{
//	if(d == meshFrameLf)
//	{
//		frameFlag = 1;
//	}
//}


//uint16_t mesh_sendCount(void)
//{
//	return phyMesh_count(&phyMesh_OUT_fifo);
//}

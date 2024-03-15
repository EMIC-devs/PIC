/*************************************************************************//**
  @file     phyMesh.c

  @brief    Hardware Library to use UART

  @author   Rottoli Luciano

  @version  v0.0.1  

  @date		01/03/2024  

 ******************************************************************************/

/*==================[inclusions]=============================================*/
#include <xc.h>
#include "inc/streamOut.h"
#include "inc/streamIn.h"
#include "inc/PhyMesh.h"
#include "inc/system.h"


/*==================[internal data definition]===============================*/
const streamIn_t  streamIn_phyMesh  = {PhyMesh_IN_pop, PhyMesh_IN_count};
const streamOut_t streamOut_phyMesh = {PhyMesh_OUT_push, PhyMesh_OUT_count};


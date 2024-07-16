/*************************************************************************//**
  @file     timer.h

  @brief    Hardware Library to use TIMER

  @author   Mariano Hunkeler Based on Pablo Lull?s Code

  @version  1.0.0
 ******************************************************************************/

#ifndef PIC_timer_H_
#define PIC_timer_H_

/*==================[inclusions]=============================================*/

#include <xc.h>

/*==================[external data declaration]==============================*/

typedef void (*Timer4_Callbak_t)(void);

void timer4_init (Timer4_Callbak_t);

/*==================[end of file]============================================*/
#endif
